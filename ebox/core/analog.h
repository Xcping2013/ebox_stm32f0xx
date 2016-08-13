/*
file   : analog.h
author : LQM
version: V1.0
date   : 2016/7/15 STM32F0平台,使用HAL库LL层.ADC1 0-15通道

Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#ifndef __ANALOG_H
#define __ANALOG_H

#include "common.h"
#include "stdlib.h"

extern void ADC1_init(void);
extern uint16_t analogin_read(uint32_t *channel);
extern void analogin_read(uint32_t *channel,uint16_t *buffer, uint16_t size);
extern uint16_t analogin_read_voltage(uint32_t *channel);
extern void DMA_configuration(void);
extern uint16_t analog_read_temperature(void);

class Analog{
public:
    /** Create an AnalogIn, connected to the specified pin
     *
     * @param pin AnalogIn pin to connect to
     * @param name (optional) A string to identify the object
     */
	Analog(GPIO *pin) {
		pin->mode(AIN);

		switch ((uint32_t)pin->port)
		{
		case (uint32_t)GPIOA_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel = LL_ADC_CHANNEL_0 ;
				break;
			case LL_GPIO_PIN_1:
				Channel = LL_ADC_CHANNEL_1 ;
				break;
			case LL_GPIO_PIN_2:
				Channel = LL_ADC_CHANNEL_2 ;
				break;
			case LL_GPIO_PIN_3:
				Channel = LL_ADC_CHANNEL_3 ;
				break;
			case LL_GPIO_PIN_4:
				Channel = LL_ADC_CHANNEL_4 ;
				break;
			case LL_GPIO_PIN_5:
				Channel = LL_ADC_CHANNEL_5 ;
				break;
			case LL_GPIO_PIN_6:
				Channel = LL_ADC_CHANNEL_6 ;
				break;
			case LL_GPIO_PIN_7:
				Channel = LL_ADC_CHANNEL_7 ;
				break;
			default:
				break;
			}
			break;
		case (uint32_t)GPIOB_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel = LL_ADC_CHANNEL_8 ;
				break;
			case LL_GPIO_PIN_1:
				Channel = LL_ADC_CHANNEL_9 ;
				break;
			default:
				break;
			}
			break;
		case (uint32_t)GPIOC_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel = LL_ADC_CHANNEL_10 ;
				break;
			case LL_GPIO_PIN_1:
				Channel = LL_ADC_CHANNEL_11 ;
				break;
			case LL_GPIO_PIN_2:
				Channel = LL_ADC_CHANNEL_12 ;
				break;
			case LL_GPIO_PIN_3:
				Channel = LL_ADC_CHANNEL_13 ;
				break;
			case LL_GPIO_PIN_4:
				Channel = LL_ADC_CHANNEL_14 ;
				break;
			case LL_GPIO_PIN_5:
				Channel = LL_ADC_CHANNEL_15 ;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		ADC1_init();
	}

    /** Read the input voltage, represented as a float in the range [0.0, 1.0]
     *
     * @returns A floating-point value representing the current input voltage, measured as a percentage
     */
    uint16_t read() {
        return analogin_read( &Channel);
    }

    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalised to a 16-bit value
     */
    uint16_t read_voltage() {
        return analogin_read_voltage(&Channel);
    }

private:
	uint32_t Channel;	
};


class AnalogDMA{
public:
	/** DMA模式采集ADC数据， unit为采集的组数。DMA的实际长度 = 通道数 * 组数
	 */
	AnalogDMA(uint16_t unit)
	{
		UnitNum = unit;
		BufferSize = 0;
		ADC1_init();
		DMA_configuration();
	}

	void Add(GPIO *pin) {
		pin->mode(AIN);
		ChannelNum ++;
		switch ((uint32_t)pin->port)
		{
		case (uint32_t)GPIOA_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel |= LL_ADC_CHANNEL_0 ;
				break;
			case LL_GPIO_PIN_1:
				Channel |= LL_ADC_CHANNEL_1 ;
				break;
			case LL_GPIO_PIN_2:
				Channel |= LL_ADC_CHANNEL_2 ;
				break;
			case LL_GPIO_PIN_3:
				Channel |= LL_ADC_CHANNEL_3 ;
				break;
			case LL_GPIO_PIN_4:
				Channel |= LL_ADC_CHANNEL_4 ;
				break;
			case LL_GPIO_PIN_5:
				Channel |= LL_ADC_CHANNEL_5 ;
				break;
			case LL_GPIO_PIN_6:
				Channel |= LL_ADC_CHANNEL_6 ;
				break;
			case LL_GPIO_PIN_7:
				Channel |= LL_ADC_CHANNEL_7 ;
				break;
			default:
				break;
			}
			break;
		case (uint32_t)GPIOB_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel |= LL_ADC_CHANNEL_8 ;
				break;
			case LL_GPIO_PIN_1:
				Channel |= LL_ADC_CHANNEL_9 ;
				break;
			default:
				break;
			}
			break;
		case (uint32_t)GPIOC_BASE:
			switch (pin->pin)
			{
			case LL_GPIO_PIN_0:
				Channel |= LL_ADC_CHANNEL_10 ;
				break;
			case LL_GPIO_PIN_1:
				Channel |= LL_ADC_CHANNEL_11 ;
				break;
			case LL_GPIO_PIN_2:
				Channel |= LL_ADC_CHANNEL_12 ;
				break;
			case LL_GPIO_PIN_3:
				Channel |= LL_ADC_CHANNEL_13 ;
				break;
			case LL_GPIO_PIN_4:
				Channel |= LL_ADC_CHANNEL_14 ;
				break;
			case LL_GPIO_PIN_5:
				Channel |= LL_ADC_CHANNEL_15 ;
				break;
			default:
				break;
			}
			break;
		default:
			ChannelNum --;
			break;
		}
		
		free(Buffer);
		BufferSize = ChannelNum*UnitNum;
		Buffer = (uint16_t*)malloc(BufferSize);

	}

	/** 读取指定组ADC值
	 */
	uint16_t read() {
		if (BufferSize == 0)
		{
			return 0;
		}
		analogin_read( &Channel,Buffer,BufferSize);
		return  1;
	}
  
 /** ADC转换结果
	 */
	uint16_t *Buffer;		// 保存都取结果
  uint32_t BufferSize;
private:
	uint32_t Channel;			// 要读取的通道
	uint16_t ChannelNum;	// 要读取的通道数
	uint16_t UnitNum ;		// 读几组数据	
};

#endif
