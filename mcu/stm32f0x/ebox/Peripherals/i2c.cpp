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
 * -LQM                  
 *     *��ֲ��STM32F0,����HAL��LL��  2016��10��18��
 */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
/* Timing register value is computed with the STM32CubeMX Tool,
  * Fast Mode @400kHz with I2CCLK = 48 MHz,
  * rise time = 100ns, fall time = 10ns
  * Timing Value = (uint32_t)0x00901850
  */
//#define I2C_TIMING               0x00901850
//#define I2C_TIMING               0xF000F3FF
// ��Ƶ�����������֣��ߵ�ƽ���͵�ƽ
#define I2C_TIMING    __LL_I2C_CONVERT_TIMINGS(0xb, 0xc7, 0xc3, 0x02, 0x04)

/**
 *@name     I2c(I2C_TypeDef *I2Cx, Gpio *scl_pin, Gpio *sda_pin)
 *@brief      I2C���캯��
 *@param    I2Cx:  I2C1,I2C2
 *          scl_pin:  ʱ��Pin
 *          sda_pin:  ����Pin
 *@retval   None
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
 *@brief    ����I2C
 *@param    speed:  ����
 *@retval   None
*/
void  I2c::begin(uint32_t speed)
{
    this->speed = speed;

    if (I2Cx == I2C1)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
        LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_SYSCLK);
        sda_pin->mode(AF_PP_PU,LL_GPIO_AF_1);
        scl_pin->mode(AF_PP_PU,LL_GPIO_AF_1);
    }
    else if (I2Cx == I2C2)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
        sda_pin->mode(AF_PP_PU,LL_GPIO_AF_1);
        scl_pin->mode(AF_PP_PU,LL_GPIO_AF_1);
    }
    config(speed);
}

void I2c::config(uint32_t speed)
{
    this->speed = speed;

    LL_I2C_Disable(I2Cx);
    LL_I2C_SetTiming(I2Cx,I2C_TIMING);
    LL_I2C_Enable(I2Cx);
}
uint32_t I2c::read_config()
{
    return this->speed;
}
int8_t I2c::start()
{
//    uint16_t times = 1000;
//    int8_t err = 0;
//    I2C_GenerateSTART(I2Cx, ENABLE);

//    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
//    {
//        times--;
//        if(times == 0)
//        {
//            err = -1;
//            break;
//        }
//    }
    return 0;
}
int8_t I2c::stop()
{
//    int8_t err = 0;
//    I2C_GenerateSTOP(I2Cx, ENABLE);
    return 0;
}
int8_t I2c::send_no_ack()
{
//    int8_t err = 0;
//    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    return 0;
}
int8_t I2c::send_ack()
{
//    int8_t err = 0;
//    I2C_AcknowledgeConfig(I2Cx, ENABLE);
    return 0;
}


int8_t I2c::send_byte(uint8_t data)
{
//    uint16_t times = 1000;
//    int8_t err = 0;
//    I2C_SendData(I2Cx, data);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
//    {
//        times--;
//        if(times == 0)
//        {
//            err = -2;
//            break;
//        }
//    }
    return 0;
}
int8_t I2c::send_7bits_address(uint8_t slave_address)
{
//    uint16_t times = 5000;
//    int8_t err = 0;
//    if(slave_address & 0x01)
//    {
//        I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Receiver);
//        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
//        {
//            times--;
//            if(times == 0)
//            {
//                err = -3;
//                break;
//            }
//        }
//    }
//    else
//    {
//        I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Transmitter);
//        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//        {
//            times--;
//            if(times == 0)
//            {
//                err = -4;
//                break;
//            }
//        }
//    }
    return 0;

}
int8_t I2c::receive_byte(uint8_t *data)
{
//    uint16_t times = 1000;
//    int8_t err = 0;
//    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
//    {
//        times--;
//        if(times == 0)
//        {
//            err = -5;
//            break;
//        }
//    }
//    *data = I2C_ReceiveData(I2Cx);//�����Ĵ�������
    return 0;
}


int8_t I2c::write_byte(uint8_t slave_address, uint8_t reg_address, uint8_t data)
{
    uint16_t err = 0;
    // ����ַ�Ĵ�����Ҫд������ݱ�����������
    uint8_t  da[2] = {reg_address,data};
    // д���ַ�Ĵ���������
    LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,2,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE);

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            LL_I2C_TransmitData8(I2Cx,da[err++]);
        }
    }
    LL_I2C_ClearFlag_STOP(I2Cx);

    return err;
}

int8_t I2c::write_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data, uint16_t num_to_write)
{
    // ���͵�ַ�Ĵ��� 
    LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,1,LL_I2C_MODE_RELOAD,LL_I2C_GENERATE_START_WRITE);

    while (!LL_I2C_IsActiveFlag_TCR(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            LL_I2C_TransmitData8(I2Cx,reg_address);
        }
    }
    // ���ŷ���ָ�����ȵ����ݵ��豸
    LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,num_to_write,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_NOSTARTSTOP);

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            LL_I2C_TransmitData8(I2Cx,*data++);
        }
    }
    LL_I2C_ClearFlag_STOP(I2Cx);

    return 0;
}

int8_t I2c::read_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data)
{
    read_byte(slave_address,reg_address,data,1);
    return 0;
}

int8_t I2c::read_byte(uint8_t slave_address, uint8_t reg_address, uint8_t *data, uint16_t num_to_read)
{
    // ���͵�ַ�Ĵ���
    LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,1,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE);
    
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            LL_I2C_TransmitData8(I2Cx,reg_address);
        }
    }
    LL_I2C_ClearFlag_STOP(I2Cx);
    // ���Ͷ�ָ��ӵ�ǰ��ַ��ʼ��ȡ����
    LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,num_to_read,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_READ);
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_RXNE(I2Cx))
        {
            *data++ = LL_I2C_ReceiveData8(I2Cx);
        }
    }
    LL_I2C_ClearFlag_STOP(I2Cx);
    
    return 0;
}

/**
 *@name     wait_dev_busy(uint8_t slave_address)
 *@brief    �ȴ��豸���С���ָ���豸����startָ�����豸æ���򷵻�NACK,���򷵻�ACK,���豸����stopָ��
 *@param    slave_address:  �豸��ַ
 *@retval   None
*/
int8_t I2c::wait_dev_busy(uint8_t slave_address)
{
    uint8_t tryg = 0;
    uint8_t i = 255;
    
    do
    {
        // clear STOP & NACK flag
        SET_BIT(I2Cx->ICR,LL_I2C_ICR_NACKCF | LL_I2C_ICR_STOPCF);
        
        LL_I2C_HandleTransfer(I2Cx,slave_address,LL_I2C_ADDRESSING_MODE_7BIT,0,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE);
        
        while (i--);
        
        if (tryg++ == 254)
        {
            return 1;
        }
    }while(LL_I2C_IsActiveFlag_NACK(I2Cx) == 1); //�������Ӧ��������ȴ�
    
    LL_I2C_ClearFlag_STOP(I2Cx);
    
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
