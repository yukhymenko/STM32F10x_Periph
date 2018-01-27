#ifndef __BUTTON_LIB_H__
#define __BUTTON_LIB_H__

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define BUTTON_PORT GPIOA
#define BUTTON_PIN GPIO_Pin_0


void initButton(void);

#endif
