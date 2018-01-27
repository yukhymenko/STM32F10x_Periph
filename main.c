#include "stm32f10x.h"
#include "usart_lib.h"


int main(void) {
	initUSART1();
	sendString("System start :)");
	
	
	while(1);
}
