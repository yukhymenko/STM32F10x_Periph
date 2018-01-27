#ifndef __USART_LIB_H___
#define __USART_LIB_H___

#include "stm32f10x_gpio.h"

#define USART1_PORT 	GPIOA
#define USART1_TX_PIN	GPIO_Pin_9
#define USART1_RX_PIN	GPIO_Pin_10

#define USART1_BAUD_RATE	115200

#define TX_BUFFER_SIZE	255
#define RX_BUFFER_SIZE	255

#define CR		'\r'
#define LF		'\n'
#define BS		'\b'
#define SPACE	' '

// #define END_TX_WITH_CR
// #define END_TX_WITH_LF
#define END_TX_WITH_CR_LF

// #define END_RX_WITH_CR
// #define END_RX_WITH_LF
#define END_RX_WITH_CR_LF


typedef char TX_BUFFER_t[TX_BUFFER_SIZE + 1];
typedef char RX_BUFFER_t[RX_BUFFER_SIZE + 1];


void initUSART1(void);
void sendByte(char _byte);
void sendString(const char *pStr);
void execReadStr(void);

#endif
