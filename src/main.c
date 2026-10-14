#include"stm32f103xb.h"
#include"usart.h"

void setup(){
    usart_init(USART1, 8);
}
void loop(){
    usart_send_char(USART1, 'freddy');
}