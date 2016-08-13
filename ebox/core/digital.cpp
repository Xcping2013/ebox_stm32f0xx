/*
file   : digital.cpp
author : shentq
version: V1.1
date   : 2015/7/5
date   : 2016/7/5 LQM移植到STM32F0平台,使用HAL库LL层

Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#include "common.h"

/**
 *@name     GPIO(GPIO_TypeDef *port,uint16_t pin)
 *@brief    GPIO构造函数
 *@param    port:   GPIOA,B,C,D,E,F,G
 *          pin:    GPIO_Pin_0...15
 *@retval   None
*/
GPIO::GPIO(GPIO_TypeDef *port, uint16_t pin)
{
    this->port = port;
    this->pin = pin;
}

void GPIO::mode(PIN_MODE mode)
{
	GPIO::mode(mode,40);
}
/**
 *@name     void GPIO::mode(PIN_MODE mode)
 *@brief    GPIO模式设置
 *@param    mode:   PIN_MODE枚举变量类型
 *@retval   None
*/
void GPIO::mode(PIN_MODE mode, uint8_t af_configration)
{  
	switch ((uint32_t)this->port)
	{
	case (uint32_t)GPIOA_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		break;
	case (uint32_t)GPIOB_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		break;
	case (uint32_t)GPIOC_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		break;
	case (uint32_t)GPIOD_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		break;
#if !(defined(STM32F030x6)||defined(STM32F031x6))
	case (uint32_t)GPIOE_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		break;
#endif
	case (uint32_t)GPIOF_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		break;
	}

	switch ((uint8_t)mode)
	{
		/*analog input mode
		*/
	case AIN:
		// GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ANALOG);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		
		break;

		/* digital input mode
		*/
	case INPUT:
		// GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case INPUT_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		
				LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		break;

	case INPUT_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
				LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		break;

		/*digital output mode
		*/
	case OUTPUT_OD:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case OUTPUT_OD_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);;
		break;

	case OUTPUT_OD_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		break;

	case OUTPUT_PP:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case OUTPUT_PP_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		break;

	case OUTPUT_PP_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		

		break;


		/*af mode
		*/
	case AF_OD:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_OD_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_OD_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_PP:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_NOPULL;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}

		break;

	case AF_PP_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		// GPIO_InitStructure.Alternate = af_configration;
		
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_PP_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		

		break;
		/* if parament is other mode,set as INPUT mode
		*/
	default:
		//GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	    //GPIO_InitStructure.Pull = GPIO_NOPULL;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
	
		break;
	}
}
/**
 *@name     void GPIO::set()
 *@brief    GPIO输出高电平
 *@param    NONE
 *@retval   NONE
*/
void GPIO::set()
{
    this->port->BSRR = this->pin;
}

/**
 *@name     void GPIO::reset()
 *@brief    GPIO输出低电平
 *@param    NONE
 *@retval   NONE
*/
void GPIO::reset()
{
    this->port->BRR = this->pin;
}


/**
 *@name     void GPIO::write(uint8_t val)
 *@brief    GPIO输出设置
 *@param    val：1：输出高电平；0：输出低电平
 *@retval   NONE
*/
void GPIO::write(uint8_t val)
{
    if(val == 0)
        this->port->BRR = this->pin;
    else
        this->port->BSRR = this->pin;
}


/**
 *@name     void GPIO::set()
 *@brief    GPIO输出高电平
 *@param    NONE
 *@retval   NONE
*/
void GPIO::read(uint8_t *val)
{
    *val = this->port->IDR & this->pin;
}


/**
 *@name     uint8_t GPIO::read(void)
 *@brief    读取GPIO引脚状态
 *@param    NONE
 *@retval   返回引脚当前的电平状态
*/
uint8_t GPIO::read(void)
{
    if(this->port->IDR & this->pin)
        return 1;
    return  0;
}

/**
 *@name     void GPIO::toggle()
 *@brief    GPIO输出电平翻转
 *@param    NONE
 *@retval   NONE
*/
void GPIO::toggle()
{
    port->ODR ^= this->pin;
}

/**
 *@name     void PARALLEL_GPIO::all_mode(PIN_MODE mode)
 *@brief    GPIO组模式设置
 *@param    mode:   PIN_MODE枚举变量类型
 *@retval   None
*/
void PARALLEL_GPIO::all_mode(PIN_MODE mode)
{
    bit[0]->mode(mode);
    bit[1]->mode(mode);
    bit[2]->mode(mode);
    bit[3]->mode(mode);
    bit[4]->mode(mode);
    bit[5]->mode(mode);
    bit[6]->mode(mode);
    bit[7]->mode(mode);
}

/**
 *@name     void PARALLEL_GPIO::write(uint8_t data)
 *@brief    GPIO组输出数据
 *@param    data：输出数据
 *@retval   NONE
*/
void PARALLEL_GPIO::write(uint8_t data)
{
    bit[0]->write(data & (0x01 << 0));
    bit[1]->write(data & (0x01 << 1));
    bit[2]->write(data & (0x01 << 2));
    bit[3]->write(data & (0x01 << 3));
    bit[4]->write(data & (0x01 << 4));
    bit[5]->write(data & (0x01 << 5));
    bit[6]->write(data & (0x01 << 6));
    bit[7]->write(data & (0x01 << 7));
}

/**
 *@name     void PARALLEL_GPIO::write(uint8_t data)
 *@brief    读取GPIO组输入数据
 *@param    NONE
 *@retval   读取GPIO组的数据
*/
uint8_t PARALLEL_GPIO::read()
{
    uint8_t data = 0;
    data |= *bit[0] << 0;
    data |= *bit[1] << 1;
    data |= *bit[2] << 2;
    data |= *bit[3] << 3;
    data |= *bit[4] << 4;
    data |= *bit[5] << 5;
    data |= *bit[6] << 6;
    data |= *bit[7] << 7;
    return data;
}

/**
 *@name     void PARALLEL_GPIO::write(uint8_t data)
 *@brief    GPIO组低四位输出数据
 *@param    data：需要输出的数据，低四位有效
 *@retval   NONE
*/
void PARALLEL_GPIO::write_low_4_4bit(uint8_t data)
{
    bit[0]->write(data & (0x01 << 0));
    bit[1]->write(data & (0x01 << 1));
    bit[2]->write(data & (0x01 << 2));
    bit[3]->write(data & (0x01 << 3));
}

/**
 *@name     void PARALLEL_GPIO::write(uint8_t data)
 *@brief    读取GPIO组低四位输入数据
 *@param    NONE
 *@retval   读取GPIO组低四位的数据，高四位为0；
*/
uint8_t PARALLEL_GPIO::read_low_4_bit()
{
    uint8_t data = 0;
    data |= *bit[0] << 0;
    data |= *bit[1] << 1;
    data |= *bit[2] << 2;
    data |= *bit[3] << 3;
    return data;
}

/**
 *@name     uint8_t shift_in(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order)
 *@brief    GPIO按照时钟连续输出一个u8类型的数据，用于串行通信。
 *@param    data_pin：  数据输入引脚
            clock_pin:  时钟信号的引脚
            bit_order:  数据大小端控制LSB_FIRST：低位先发送；MSB_FIRST高位先发送
 *@retval   接收到的数据
*/
uint8_t shift_in(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order)
{
    uint8_t value = 0;
    uint8_t i;

    for (i = 0; i < 8; ++i)
    {
        clock_pin->write(HIGH);
        if (bit_order == LSB_FIRST)
            value |= data_pin->read() << i;
        else
            value |= data_pin->read() << (7 - i);
        clock_pin->write(LOW);
    }
    return value;
}

/**
 *@name     uint8_t shift_in(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order)
 *@brief    GPIO按照时钟连续输出一个u8类型的数据，用于串行通信。
 *@param    data_pin：  数据输出引脚
            clock_pin:  时钟信号的引脚
            bit_order:  数据大小端控制LSB_FIRST：低位先发送；MSB_FIRST高位先发送
            val：       要发送的数据
 *@retval   NONE
*/
void shift_out(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order, uint8_t val)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (bit_order == LSB_FIRST)
            data_pin->write(!!(val & (1 << i)));
        else
            data_pin->write(!!(val & (1 << (7 - i))));

        clock_pin->write(HIGH);
        clock_pin->write(LOW);

    }
}

