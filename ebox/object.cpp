/*
file   : object.cpp
author : shentq
version: V1.0
date   : 2015/7/5
date   : 2016/7/5 LQM移植到STM32F0平台,使用HAL库LL层
Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/


#include "ebox.h"


GPIO PA0(GPIOA, LL_GPIO_PIN_0);
GPIO PA1(GPIOA, LL_GPIO_PIN_1);
GPIO PA2(GPIOA, LL_GPIO_PIN_2);
GPIO PA3(GPIOA, LL_GPIO_PIN_3);
GPIO PA4(GPIOA, LL_GPIO_PIN_4);
GPIO PA5(GPIOA, LL_GPIO_PIN_5);
GPIO PA6(GPIOA, LL_GPIO_PIN_6);
GPIO PA7(GPIOA, LL_GPIO_PIN_7);
GPIO PA8(GPIOA, LL_GPIO_PIN_8);
GPIO PA9(GPIOA, LL_GPIO_PIN_9);
GPIO PA10(GPIOA, LL_GPIO_PIN_10);
GPIO PA11(GPIOA, LL_GPIO_PIN_11);
GPIO PA12(GPIOA, LL_GPIO_PIN_12);
GPIO PA13(GPIOA, LL_GPIO_PIN_13);
GPIO PA14(GPIOA, LL_GPIO_PIN_14);
GPIO PA15(GPIOA, LL_GPIO_PIN_15);

//GPIO PB0(GPIOB, LL_GPIO_PIN_0);
//GPIO PB1(GPIOB, LL_GPIO_PIN_1);
//GPIO PB2(GPIOB, LL_GPIO_PIN_2);
//GPIO PB3(GPIOB, LL_GPIO_PIN_3);
//GPIO PB4(GPIOB, LL_GPIO_PIN_4);
//GPIO PB5(GPIOB, LL_GPIO_PIN_5);
//GPIO PB6(GPIOB, LL_GPIO_PIN_6);
//GPIO PB7(GPIOB, LL_GPIO_PIN_7);
//GPIO PB8(GPIOB, LL_GPIO_PIN_8);
//GPIO PB9(GPIOB, LL_GPIO_PIN_9);
//GPIO PB10(GPIOB, LL_GPIO_PIN_10);
//GPIO PB11(GPIOB, LL_GPIO_PIN_11);
//GPIO PB12(GPIOB, LL_GPIO_PIN_12);
//GPIO PB13(GPIOB, LL_GPIO_PIN_13);
//GPIO PB14(GPIOB, LL_GPIO_PIN_14);
//GPIO PB15(GPIOB, LL_GPIO_PIN_15);


//GPIO PC0(GPIOC, LL_GPIO_PIN_0);
//GPIO PC1(GPIOC, LL_GPIO_PIN_1);
//GPIO PC2(GPIOC, LL_GPIO_PIN_2);
//GPIO PC3(GPIOC, LL_GPIO_PIN_3);
//GPIO PC4(GPIOC, LL_GPIO_PIN_4);
//GPIO PC5(GPIOC, LL_GPIO_PIN_5);
//GPIO PC6(GPIOC, LL_GPIO_PIN_6);
//GPIO PC7(GPIOC, LL_GPIO_PIN_7);
//GPIO PC8(GPIOC, LL_GPIO_PIN_8);
//GPIO PC9(GPIOC, LL_GPIO_PIN_9);
//GPIO PC10(GPIOC, LL_GPIO_PIN_10);
//GPIO PC11(GPIOC, LL_GPIO_PIN_11);
//GPIO PC12(GPIOC, LL_GPIO_PIN_12);
//GPIO PC13(GPIOC, LL_GPIO_PIN_13);
//GPIO PC14(GPIOC, LL_GPIO_PIN_14);
//GPIO PC15(GPIOC, LL_GPIO_PIN_15);


//GPIO PD0(GPIOD, LL_GPIO_PIN_0);
//GPIO PD1(GPIOD, LL_GPIO_PIN_1);
//GPIO PD2(GPIOD, LL_GPIO_PIN_2);
//GPIO PD3(GPIOD, LL_GPIO_PIN_3);
//GPIO PD4(GPIOD, LL_GPIO_PIN_4);
//GPIO PD5(GPIOD, LL_GPIO_PIN_5);
//GPIO PD6(GPIOD, LL_GPIO_PIN_6);
//GPIO PD7(GPIOD, LL_GPIO_PIN_7);
//GPIO PD8(GPIOD, LL_GPIO_PIN_8);
//GPIO PD9(GPIOD, LL_GPIO_PIN_9);
//GPIO PD10(GPIOD, LL_GPIO_PIN_10);
//GPIO PD11(GPIOD, LL_GPIO_PIN_11);
//GPIO PD12(GPIOD, LL_GPIO_PIN_12);
//GPIO PD13(GPIOD, LL_GPIO_PIN_13);
//GPIO PD14(GPIOD, LL_GPIO_PIN_14);
//GPIO PD15(GPIOD, LL_GPIO_PIN_15);

//GPIO PE0(GPIOE, LL_GPIO_PIN_0);
//GPIO PE1(GPIOE, LL_GPIO_PIN_1);
//GPIO PE2(GPIOE, LL_GPIO_PIN_2);
//GPIO PE3(GPIOE, LL_GPIO_PIN_3);
//GPIO PE4(GPIOE, LL_GPIO_PIN_4);
//GPIO PE5(GPIOE, LL_GPIO_PIN_5);
//GPIO PE6(GPIOE, LL_GPIO_PIN_6);
//GPIO PE7(GPIOE, LL_GPIO_PIN_7);
//GPIO PE8(GPIOE, LL_GPIO_PIN_8);
//GPIO PE9(GPIOE, LL_GPIO_PIN_9);
//GPIO PE10(GPIOE, LL_GPIO_PIN_10);
//GPIO PE11(GPIOE, LL_GPIO_PIN_11);
//GPIO PE12(GPIOE, LL_GPIO_PIN_12);
//GPIO PE13(GPIOE, LL_GPIO_PIN_13);
//GPIO PE14(GPIOE, LL_GPIO_PIN_14);
//GPIO PE15(GPIOE, LL_GPIO_PIN_15);

//GPIO PF0(GPIOF, LL_GPIO_PIN_0);
//GPIO PF1(GPIOF, LL_GPIO_PIN_1);
//GPIO PF2(GPIOF, LL_GPIO_PIN_2);
//GPIO PF3(GPIOF, LL_GPIO_PIN_3);
//GPIO PF4(GPIOF, LL_GPIO_PIN_4);
//GPIO PF5(GPIOF, LL_GPIO_PIN_5);
//GPIO PF6(GPIOF, LL_GPIO_PIN_6);
//GPIO PF7(GPIOF, LL_GPIO_PIN_7);
//GPIO PF8(GPIOF, LL_GPIO_PIN_8);
//GPIO PF9(GPIOF, LL_GPIO_PIN_9);
//GPIO PF10(GPIOF, LL_GPIO_PIN_10);
//GPIO PF11(GPIOF, LL_GPIO_PIN_11);
//GPIO PF12(GPIOF, LL_GPIO_PIN_12);
//GPIO PF13(GPIOF, LL_GPIO_PIN_13);
//GPIO PF14(GPIOF, LL_GPIO_PIN_14);
//GPIO PF15(GPIOF, LL_GPIO_PIN_15);

//GPIO PG0(GPIOG, LL_GPIO_PIN_0);
//GPIO PG1(GPIOG, LL_GPIO_PIN_1);
//GPIO PG2(GPIOG, LL_GPIO_PIN_2);
//GPIO PG3(GPIOG, LL_GPIO_PIN_3);
//GPIO PG4(GPIOG, LL_GPIO_PIN_4);
//GPIO PG5(GPIOG, LL_GPIO_PIN_5);
//GPIO PG6(GPIOG, LL_GPIO_PIN_6);
//GPIO PG7(GPIOG, LL_GPIO_PIN_7);
//GPIO PG8(GPIOG, LL_GPIO_PIN_8);
//GPIO PG9(GPIOG, LL_GPIO_PIN_9);
//GPIO PG10(GPIOG, LL_GPIO_PIN_10);
//GPIO PG11(GPIOG, LL_GPIO_PIN_11);
//GPIO PG12(GPIOG, LL_GPIO_PIN_12);
//GPIO PG13(GPIOG, LL_GPIO_PIN_13);
//GPIO PG14(GPIOG, LL_GPIO_PIN_14);
//GPIO PG15(GPIOG, LL_GPIO_PIN_15);

////串口
//USART uart1(USART1, &PA9, &PA10);
//USART uart2(USART2, &PA2, &PA3);
//USART uart3(USART3, &PB10, &PB11);
//USART uart4(UART4, &PC10, &PC11);
//USART uart5(UART5, &PC12, &PD2);

////spi
//SPI     spi1(SPI1, &PA5, &PA6, &PA7);
//SPI     spi2(SPI2, &PB13, &PB14, &PB15);
//SPI     spi3(SPI3, &PB3, &PB4, &PB5);
//SOFTSPI	sspi1(&PA5, &PA6, &PA7);

////i2c
//I2C     i2c1(I2C1, &PB6, &PB7);
//I2C     i2c2(I2C2, &PB10, &PB11);
//SOFTI2C si2c(&PA4, &PA5);
//SOFTI2C si2c1(&PB6, &PB7);
//SOFTI2C si2c2(&PB10, &PB11);

////can
//CAN can1(CAN1, &PA11, &PA12);
