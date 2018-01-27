#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#include "button_lib.h"
#include "usart_lib.h"


void initButton(void) {
	GPIO_InitTypeDef _gpio0;
    EXTI_InitTypeDef _exti0;
	NVIC_InitTypeDef _nvic0;

	_gpio0.GPIO_Mode = GPIO_Mode_IPD;
	_gpio0.GPIO_Pin = BUTTON_PIN;
	_gpio0.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BUTTON_PORT, &_gpio0);
    
    // Init interrupt from pin PA0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	_nvic0.NVIC_IRQChannel = EXTI0_IRQn;
	_nvic0.NVIC_IRQChannelCmd = ENABLE;
	_nvic0.NVIC_IRQChannelPreemptionPriority = 0x00;
	_nvic0.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&_nvic0);

	_exti0.EXTI_Line = EXTI_Line0;
	_exti0.EXTI_LineCmd = ENABLE;
	_exti0.EXTI_Mode = EXTI_Mode_Interrupt;
	_exti0.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&_exti0);
}

void EXTI0_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		sendString("External interrupt 0 detected");

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
