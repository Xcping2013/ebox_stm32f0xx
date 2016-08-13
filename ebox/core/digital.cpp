/*
file   : digital.cpp
author : shentq
version: V1.1
date   : 2015/7/5
date   : 2016/7/5 LQM��ֲ��STM32F0ƽ̨,ʹ��HAL��LL��

Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#include "common.h"

/**
 *@name     GPIO(GPIO_TypeDef *port,uint16_t pin)
 *@brief    GPIO���캯��
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
 *@brief    GPIOģʽ����
 *@param    mode:   PIN_MODEö�ٱ�������
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
 *@brief    GPIO����ߵ�ƽ
 *@param    NONE
 *@retval   NONE
*/
void GPIO::set()
{
    this->port->BSRR = this->pin;
}

/**
 *@name     void GPIO::reset()
 *@brief    GPIO����͵�ƽ
 *@param    NONE
 *@retval   NONE
*/
void GPIO::reset()
{
    this->port->BRR = this->pin;
}


/**
 *@name     void GPIO::write(uint8_t val)
 *@brief    GPIO�������
 *@param    val��1������ߵ�ƽ��0������͵�ƽ
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
 *@brief    GPIO����ߵ�ƽ
 *@param    NONE
 *@retval   NONE
*/
void GPIO::read(uint8_t *val)
{
    *val = this->port->IDR & this->pin;
}


/**
 *@name     uint8_t GPIO::read(void)
 *@brief    ��ȡGPIO����״̬
 *@param    NONE
 *@retval   �������ŵ�ǰ�ĵ�ƽ״̬
*/
uint8_t GPIO::read(void)
{
    if(this->port->IDR & this->pin)
        return 1;
    return  0;
}

/**
 *@name     void GPIO::toggle()
 *@brief    GPIO�����ƽ��ת
 *@param    NONE
 *@retval   NONE
*/
void GPIO::toggle()
{
    port->ODR ^= this->pin;
}

/**
 *@name     void PARALLEL_GPIO::all_mode(PIN_MODE mode)
 *@brief    GPIO��ģʽ����
 *@param    mode:   PIN_MODEö�ٱ�������
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
 *@brief    GPIO���������
 *@param    data���������
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
 *@brief    ��ȡGPIO����������
 *@param    NONE
 *@retval   ��ȡGPIO�������
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
 *@brief    GPIO�����λ�������
 *@param    data����Ҫ��������ݣ�����λ��Ч
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
 *@brief    ��ȡGPIO�����λ��������
 *@param    NONE
 *@retval   ��ȡGPIO�����λ�����ݣ�����λΪ0��
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
 *@brief    GPIO����ʱ���������һ��u8���͵����ݣ����ڴ���ͨ�š�
 *@param    data_pin��  ������������
            clock_pin:  ʱ���źŵ�����
            bit_order:  ���ݴ�С�˿���LSB_FIRST����λ�ȷ��ͣ�MSB_FIRST��λ�ȷ���
 *@retval   ���յ�������
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
 *@brief    GPIO����ʱ���������һ��u8���͵����ݣ����ڴ���ͨ�š�
 *@param    data_pin��  �����������
            clock_pin:  ʱ���źŵ�����
            bit_order:  ���ݴ�С�˿���LSB_FIRST����λ�ȷ��ͣ�MSB_FIRST��λ�ȷ���
            val��       Ҫ���͵�����
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

