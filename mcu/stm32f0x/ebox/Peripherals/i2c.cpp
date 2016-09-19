/**
  ******************************************************************************
  * @file    i2c.cpp
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief   
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */
/**
 * Modification History:
 * -LQM (2016/9/11)
 *      *移植到STM32F0,基于HAL库LL层
 */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/**
 *@name     I2c(I2C_TypeDef *I2Cx, Gpio *scl_pin, Gpio *sda_pin)
 *@brief    I2c构造函数
 *@param    *I2c -- I2C端口
 *			*scl_pin -- 时钟pin； *sda_pin -- 数据pin
 *@retval   NONE
*/
I2c::I2c(I2C_TypeDef *I2Cx, Gpio *scl_pin, Gpio *sda_pin)
{
    busy = 0;
    this->I2Cx = I2Cx;
    this->scl_pin = scl_pin;
    this->sda_pin = sda_pin;

}

/**
 *@name     begin(uint32_t speed)
 *@brief    
 *@param    speed -- i2c速度
 *@retval   NONE
*/
void  I2c::begin(uint32_t speed)
{
	this->speed = speed;
//    I2C_InitTypeDef I2C_InitStructure;

	if (I2Cx == I2C1){
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
#ifdef (STM32F030x6)
		sda_pin->mode(AF_OD_PU,LL_GPIO_AF_4);
		scl_pin->mode(AF_OD_PU,LL_GPIO_AF_4);
#else
		sda_pin->mode(AF_OD_PU,LL_GPIO_AF_1);
		scl_pin->mode(AF_OD_PU,LL_GPIO_AF_1);
	}
#endif
#ifdef I2C2
	if (I2Cx == I2C2)	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2)
		sda_pin->mode(AF_OD_PU,LL_GPIO_AF_1);
		scl_pin->mode(AF_OD_PU,LL_GPIO_AF_1);
	}
#endif
	LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_SYSCLK);


	/* I2c 配置 */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	//I2C_InitStructure.I2C_OwnAddress1 = SlaveAddress;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = this->speed;

	/* I2C1 初始化 */
	I2C_DeInit(I2Cx);
	I2C_Init(I2Cx, &I2C_InitStructure);

	/* 使能 I2C1 */
	I2C_Cmd  (I2Cx, ENABLE);

	/* Disable I2C1 prior modifying configuration registers */
	LL_I2C_Disable(I2C1);
	/* Configure the SDA setup, hold time and the SCL high, low period */
	/* (uint32_t)0x00901850 = I2C_TIMING*/
	LL_I2C_SetTiming(I2C1, I2C_TIMING);

	/* Configure the Own Address1                   */
	/* Reset Values of :
	 *     - OwnAddress1 is 0x00
	 *     - OwnAddrSize is LL_I2C_OWNADDRESS1_7BIT
	 *     - Own Address1 is disabled
	 */
	//LL_I2C_SetOwnAddress1(I2C1, 0x00, LL_I2C_OWNADDRESS1_7BIT);
	//LL_I2C_DisableOwnAddress1(I2C1);

	/* Enable Clock stretching */
	/* Reset Value is Clock stretching enabled */
	//LL_I2C_EnableClockStretching(I2C1);

	/* Configure Digital Noise Filter */
	/* Reset Value is 0x00            */
	//LL_I2C_SetDigitalFilter(I2C1, 0x00);

	/* Enable Analog Noise Filter           */
	/* Reset Value is Analog Filter enabled */
	//LL_I2C_EnableAnalogFilter(I2C1);

	/* Enable General Call                  */
	/* Reset Value is General Call disabled */
	//LL_I2C_EnableGeneralCall(I2C1);

	/* Configure the 7bits Own Address2               */
	/* Reset Values of :
	 *     - OwnAddress2 is 0x00
	 *     - OwnAddrMask is LL_I2C_OWNADDRESS2_NOMASK
	 *     - Own Address2 is disabled
	 */
	//LL_I2C_SetOwnAddress2(I2C1, 0x00, LL_I2C_OWNADDRESS2_NOMASK);
	//LL_I2C_DisableOwnAddress2(I2C1);

	/* Configure the Master to operate in 7-bit or 10-bit addressing mode */
	/* Reset Value is LL_I2C_ADDRESSING_MODE_7BIT                         */
	//LL_I2C_SetMasterAddressingMode(I2C1, LL_I2C_ADDRESSING_MODE_7BIT);

	/* Enable Peripheral in I2C mode */
	/* Reset Value is I2C mode */
	LL_I2C_SetMode(I2C1, LL_I2C_MODE_I2C);

	/* (4) Enable I2C1 **********************************************************/
	LL_I2C_Enable(I2C1);

}

void I2c::config(uint32_t speed)
{
    this->speed = speed;
    I2C_InitTypeDef I2C_InitStructure;

    /* I2c 配置 */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    //I2C_InitStructure.I2C_OwnAddress1 = SlaveAddress;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    I2C_InitStructure.I2C_ClockSpeed = this->speed;
    I2C_Init(I2Cx, &I2C_InitStructure);
    /* 使能 I2C1 */
    I2C_Cmd  (I2Cx, ENABLE);
    /*允许应答模式*/
    I2C_AcknowledgeConfig(I2Cx, ENABLE);

}
uint32_t I2c::read_config()
{
    return this->speed;
}
int8_t I2c::start()
{
    uint16_t times = 1000;
    int8_t err = 0;
    I2C_GenerateSTART(I2Cx, ENABLE);

    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        times--;
        if(times == 0)
        {
            err = -1;
            break;
        }
    }
    return err;
}
int8_t I2c::stop()
{
    int8_t err = 0;
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return err;
}
int8_t I2c::send_no_ack()
{
    int8_t err = 0;
    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    return err;
}
int8_t I2c::send_ack()
{
    int8_t err = 0;
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
    return err;
}


int8_t I2c::send_byte(uint8_t data)
{
    uint16_t times = 1000;
    int8_t err = 0;
    I2C_SendData(I2Cx, data);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        times--;
        if(times == 0)
        {
            err = -2;
            break;
        }
    }
    return err;
}
int8_t I2c::send_7bits_address(uint8_t slave_address)
{
    uint16_t times = 5000;
    int8_t err = 0;
    if(slave_address & 0x01)
    {
        I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Receiver);
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        {
            times--;
            if(times == 0)
            {
                err = -3;
                break;
            }
        }
    }
    else
    {
        I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        {
            times--;
            if(times == 0)
            {
                err = -4;
                break;
            }
        }
    }
    return err;

}
int8_t I2c::receive_byte(uint8_t *data)
{
    uint16_t times = 1000;
    int8_t err = 0;
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
        times--;
        if(times == 0)
        {
            err = -5;
            break;
        }
    }
    *data = I2C_ReceiveData(I2Cx);//读出寄存器数据
    return err;
}


int8_t I2c::write_byte(uint8_t slave_address, uint8_t reg_address, uint8_t data)
{
    uint16_t err = 0;

    start();
    send_7bits_address(slave_address);
    send_byte(reg_address);
    send_byte(data);
    stop();

    return err;

}
int8_t I2c::write_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data, uint16_t num_to_write)
{
    uint16_t err = 0;

    start();
    send_7bits_address(slave_address);
    send_byte(reg_address);
    while(num_to_write--)
    {
        send_byte(*data);
        data++;
    }
    stop();

    return err;

}
int8_t I2c::read_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data)
{
    start();
    send_7bits_address(slave_address);
    I2C_Cmd(I2Cx, ENABLE);
    send_byte(reg_address);
    start();
    send_7bits_address(slave_address + 1);
    send_no_ack();
    stop();
    receive_byte(data);
    send_ack();
    return 0;
}

int8_t I2c::read_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data, uint16_t num_to_read)
{
    uint8_t i = 0;
    start();
    send_7bits_address(slave_address);
    I2C_Cmd(I2Cx, ENABLE);
    send_byte(reg_address);
    start();
    send_7bits_address(slave_address + 1);

    while(num_to_read)
    {
        if(num_to_read == 1)
        {
            send_no_ack();
            stop();
        }
        receive_byte(data);
        data++;
        num_to_read--;
        i++;
    }
    send_ack();

    return i;
}

int8_t I2c::wait_dev_busy(uint8_t slave_address)
{
    int8_t ret;
    uint8_t i = 0;
    do
    {
        start();
        ret = send_7bits_address(slave_address);
        send_ack();
        send_byte(slave_address);
        stop();
        if(i++ == 100)
        {
            return -1;
        }
    }
    while(ret != 0); //如果返回值不是0，继续等待
    return 0;
}
int8_t I2c::take_i2c_right(uint32_t speed)
{
    while(busy == 1)
    {
        delay_ms(1);
    }
    this->speed = speed;
    config(this->speed);
    busy = 1;
    return 0;
}
int8_t I2c::release_i2c_right(void)
{
    busy = 0;
    return 0;
}
