#include"stm32f103xb.h"
#include"usart.h"

int main(){
    usart_init(USART1, 9600);
    usart_send_string(USART1, "soy eder");
    while(1){
    }
    }
