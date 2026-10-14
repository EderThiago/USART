#include"stm32f103xb.h"
#include"usart.h"
#include "clk_maximizer.h"

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){
float div;
int mantissa;//entero
float fraction;
if(USARTx==USART1){
    if(USARTx==USART1){
        RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
        clock_72MHz();
                      }
    if(USARTx==USART2){
        RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
                      }
    if(USARTx==USART3){
        RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
                      }

        USARTx->CR1|=USART_CR1_UE;
        USARTx->CR1&=~USART_CR1_M;
        USARTx->CR1|=USART_CR1_TE;
        USARTx->CR1|=USART_CR1_RE;
        USARTx->CR2&=~USART_CR2_STOP;
        if(USARTx==USART1){
            div =(16*baudrate)/72000000;
        }else{
            div =(16*baudrate)/36000000;
        }
        mantissa=div;
        fraction=(div-mantissa)*100;
        USARTx->BRR=(mantissa<<4)/fraction;

        if(USARTx=USART1){
            RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
            GPIOA->CRH&=~(0xf<<((9*4)%8));
            GPIOA->CRH|=(0xb<<((9*4)%8));
            GPIOA->CRH&=~(0xf<<((10*4)%8));
            GPIOA->CRH|=(0x4<<((10*4)%8));
        }
        if(USARTx=USART2){
            RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
            GPIOA->CRL&=~(0xf<<((2*4)));
            GPIOA->CRL|=(0xb<<((2*4)));
            GPIOA->CRL&=~(0xf<<((3*4)));
            GPIOA->CRL|=(0x4<<((3*4)));
        }
        if(USARTx=USART3){
            RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
            GPIOB->CRH&=~(0xf<<((10*4)%8));
            GPIOB->CRH|=(0xb<<((10*4)%8)); //funcion alternativa push pull
            GPIOB->CRH&=~(0xf<<((11*4)%8));
            GPIOB->CRH|=(0x4<<((11*4)%8));
        }
}

}
void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    while(!(USARTx->SR&USART_SR_TXE)){}
    USARTx->DR = data;
    
}
void usart_send_string(USART_TypeDef* USARTx, char* string){
while(!(USARTx->SR&USART_SR_TXE)){}

while(*string){
    usart_send_char(USARTx, *string);
    string++;//como es puntero, se desplaza en direccion de memoria
             }
    
}
uint8_t usart_receive_char(USART_TypeDef * USARTx){
while(USARTx->SR&USART_SR_RXNE ){}
    char lectura=USARTx->DR;
    return lectura;

    
}