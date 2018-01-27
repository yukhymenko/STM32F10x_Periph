#include "stm32f10x.h"
#include "usart_lib.h"
#include "button_lib.h"

extern TX_BUFFER_t 	_TX_BUFFER;

int main(void) {
	initUSART1();
    initButton();
	
    sendString("System start :)");
	
	
	while(1);
}
