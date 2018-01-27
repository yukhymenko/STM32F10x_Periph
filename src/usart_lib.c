#include <stdlib.h>

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#include "usart_lib.h"

/*
 * Globals
 */
TX_BUFFER_t 	_TX_BUFFER;
RX_BUFFER_t 	_RX_BUFFER;
uint16_t		_RX_BUFFER_COUNTER;

/*
 * 
 */
void initUSART1(void) {
	GPIO_InitTypeDef    _gpio;
	USART_InitTypeDef   _usart;

	_RX_BUFFER_COUNTER = 0;

	// Enable clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

	// Set configuration for Rx and Tx pins
	_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	// Rx
	_gpio.GPIO_Mode = GPIO_Mode_IPU;
	_gpio.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_PORT, &_gpio);
	// Tx
	_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	_gpio.GPIO_Pin = USART1_TX_PIN;
	GPIO_Init(USART1_PORT, &_gpio);

	// Set configuration for USART1
	USART_StructInit(&_usart);
	_usart.USART_BaudRate = USART1_BAUD_RATE;
	USART_Init(USART1, &_usart);

	// Set configuration for USART1 Interrupt
	// Enable interrupt when receive data
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);

	// Turn on USART1
	USART_Cmd(USART1, ENABLE);
}

/*
 * 
 */
void sendByte(char _byte) {
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TC));
	USART_SendData(USART1, _byte);
}

/*
 * 
 */
void sendString(const char *pStr) {
	if (pStr == NULL) {
		return;
	}

	while (*pStr) {
		sendByte((uint16_t)*pStr++);
	}

	#ifdef END_TX_WITH_CR
		sendByte((uint16_t)CR);
	#endif

	#ifdef END_TX_WITH_LF
		sendByte((uint16_t)LF);
	#endif

	#ifdef END_TX_WITH_CR_LF
		sendByte((uint16_t)CR); sendByte((uint16_t)LF);
	#endif
}

/*
 * Handler for received data in format "Some data\r\n"
 */
void USART1_IRQHandler()
{
	char recByte;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		recByte = USART_ReceiveData(USART1);

		/*
		 * [ECHO] Return received byte back to terminal
		 */
		switch (recByte){
		default:
			sendByte(recByte);
		}

		if (_RX_BUFFER_COUNTER < RX_BUFFER_SIZE) {
			_RX_BUFFER[_RX_BUFFER_COUNTER++] = recByte;
		}

		if ((recByte == LF) || (_RX_BUFFER_COUNTER == RX_BUFFER_SIZE)) {
			_RX_BUFFER[_RX_BUFFER_COUNTER] = 0;
			execReadStr();
		}

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

/*
 * 
 */
void execReadStr(void) {
	sendString("\r\nFrom Host:");
	sendString((char*)_RX_BUFFER);

	_RX_BUFFER_COUNTER = 0;
}
