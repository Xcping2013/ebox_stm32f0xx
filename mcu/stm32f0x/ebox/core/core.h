/**
  ******************************************************************************
  * @file    core.h
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief   ���ļ�Ϊebox�����ļ�,�ṩ�����ǳ���Ҫ�Ľӿ�,���Ա���׼��c�ļ����á�
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
 * -shentq                  -version 1.2(2016/08/17)
 *      *�޸���оƬ��Ƶֻ������Ϊ72Mhz�����ƣ�֧��������Ƶ
 *      *������cpu����Ϣ��ȡ��������������ʱ�ӣ�оƬ������оƬ����Ӽӵ�����
 * -LQM
 *      *��ֲ��F0
 */


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __CORE_H
#define __CORE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_adc.h"
#include "stm32f0xx_ll_iwdg.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_RTC.h"

#define interrupts() 		__enable_irq()//���������ж�
#define no_interrupts() 	__disable_irq()//��ֹ�����ж�
	
typedef struct
{
	uint32_t pll_vco;
	uint32_t core;		// SYSCLK ϵͳʱ��
	uint32_t hclk;		// AHB����ʱ�ӣ���ϵͳʱ�ӷ�Ƶ�õ���һ�㲻��Ƶ������ϵͳʱ��
	//uint32_t pclk2;		// APB2����ʱ��,F0û��
	uint32_t pclk1;		// APB1����ʱ��
}cpu_clock_t; 

typedef struct
{
	uint32_t    ability;//cpu calculate plus per second;
	cpu_clock_t	clock;
	uint32_t    chip_id[3];
	uint16_t    flash_size;
	char        company[8];
}cpu_t;

extern cpu_t cpu;


/*!< 2 bits for pre-emption priority
2 bits for subpriority */
//#define NVIC_GROUP_CONFIG NVIC_PriorityGroup_2//�Ժ�NVIC_PriorityGroupConfig()��������Ҫ�ٱ����á����������Է�NVIC_GROUP_CONFIGֵ������


typedef void (*callback_fun_type)(void);

///////ȫ�ֱ���������///////////////////////////////////////////////
extern __IO uint64_t millis_seconds;//�ṩһ��mills()��Ч��ȫ�ֱ���������cpu���ÿ���

void ebox_init(void); //eboxϵͳ��ʼ��
uint32_t get_cpu_calculate_per_sec();//��ȡcpu�ڲ��ܲ���ϵͳ������µļ�������������ͳ��cpu����ʹ����

uint64_t micros(void);//��ȡϵͳ��ǰ�����˶೤ʱ�䡣��λ��us
uint64_t millis(void);//��ȡϵͳ��ǰ�����˶೤ʱ�䡣��λ��ms
void delay_ms(uint64_t ms);//��ʱn���롣�������������ʹ�ã�������ֹ�����жϵ��������������1us��
void delay_us(uint64_t us);//��ʱn΢�롣�������������ʹ�ã�������ֹ�����жϵ��������������1us��
void set_systick_user_event_per_sec(uint16_t frq);//�趨�û��ж��¼�����ӦƵ�ʡ�frq[1,1000],frq�����2�ı���
void attach_systick_user_event(void (*callback_fun)(void));//��systick�жϵ��ú���������Ƶ�����û�������Ƶ��Ϊ1hz-1000hz


static void get_system_clock(cpu_clock_t *clock);
static void get_chip_info();

#ifdef __cplusplus
}
#endif
#endif