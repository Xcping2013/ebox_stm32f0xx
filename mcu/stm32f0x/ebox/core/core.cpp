/**
  ******************************************************************************
  * @file    core.cpp
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
 * -LQM (2016/8/25)
 *      *修改数据类型 u16 - uint16_t
 */

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#define systick_no_interrupt()  SysTick->CTRL &=0xfffffffd
#define systick_interrupt()     SysTick->CTRL |=0x0002
extern "C" {

    cpu_t cpu;
	
			__weak void SystemClock_Config()
	{
		/* Configuration will allow to reach a SYSCLK frequency set to 24MHz:
		 Syst freq = ((HSI_VALUE * PLLMUL)/ PLLDIV)
		             ((8MHz * 12)/ 4)                  = 24MHz             */
		LL_UTILS_PLLInitTypeDef sUTILS_PLLInitStruct = {LL_RCC_PLL_MUL_12 , LL_RCC_PREDIV_DIV_2}; ;

		/* Variable to store AHB and APB buses clock configuration */
		/* Settings to have HCLK set to 12MHz and APB to 6 MHz */
		LL_UTILS_ClkInitTypeDef sUTILS_ClkInitStruct = {LL_RCC_SYSCLK_DIV_1, LL_RCC_APB1_DIV_1};

		/* Switch to PLL with HSI as clock source             */
		LL_PLL_ConfigSystemClock_HSI(&sUTILS_PLLInitStruct, &sUTILS_ClkInitStruct);
	}


    //extern uint16_t  AD_value[];

    __IO uint64_t millis_seconds;//提供一个mills()等效的全局变量。降低cpu调用开销


    void ebox_init(void)
    {
		    SystemClock_Config();
		
        get_system_clock(&cpu.clock);
        get_chip_info();
        cpu.company[0] = 'S';
        cpu.company[1] = 'T';
        cpu.company[2] = '\0';


        SysTick_Config(cpu.clock.core/1000);//  每隔 1ms产生一次中断
		    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);//systemticks clock；
       
        
        //统计cpu计算能力//////////////////
        cpu.ability = 0;
        millis_seconds = 0;
        do
        {
            cpu.ability++;//统计cpu计算能力
        }
        while(millis_seconds < 100);
        cpu.ability = cpu.ability * 10;
        ////////////////////////////////
//        ADC1_init();

//        NVIC_PriorityGroupConfig(NVIC_GROUP_CONFIG);

        //将pb4默认设置为IO口，禁用jtag
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
        set_systick_user_event_per_sec(1000);
//        random_seed(AD_value[0]);//初始化随机数种子
				//get_system_clock(&cpu.clock);

    }

    uint64_t micros(void)
    {
        if((SysTick->CTRL & (1 << 16)) && (__get_PRIMASK())) //如果此时屏蔽了所有中断且发生了systick溢出，需要对millis_secend进行补偿
        {
            millis_seconds++;
        }
        return  (millis_seconds * 1000 + (1000 - (SysTick->VAL / cpu.clock.core)*1000000));
    }
    uint64_t millis( void )
    {
        return millis_seconds;
    }

    void delay_ms(uint64_t ms)
    {
        uint64_t end ;
        end = micros() + ms * 1000 - 3;
        while(micros() < end);
    }
    void delay_us(uint64_t us)
    {
        uint64_t end = micros() + us - 3;
        while(micros() < end);
    }


    callback_fun_type systick_cb_table[1] = {0};
    __IO uint16_t systick_user_event_per_sec;//真实的值
    __IO uint16_t _systick_user_event_per_sec;//用于被millis_second取余数

    void set_systick_user_event_per_sec(uint16_t frq)
    {
        _systick_user_event_per_sec = 1000 / frq;
        systick_user_event_per_sec = frq;
    }

    void attach_systick_user_event(void (*callback_fun)(void))
    {
        systick_cb_table[0] = callback_fun;
    }
    void SysTick_Handler(void)//systick中断
    {
        millis_seconds++;
        if((millis_seconds % _systick_user_event_per_sec) == 0)
        {
            if(systick_cb_table[0] != 0)
            {
                systick_cb_table[0]();
            }
        }

    }
/**
 *@brief    获取系统时钟
 *@param    *clock：  时钟指针，返回系统时钟
 *@retval   none
*/
	static void get_system_clock(cpu_clock_t *clock)
    {
		LL_RCC_ClocksTypeDef RCC_Clock;
		
		SystemCoreClockUpdate();
		LL_RCC_GetSystemClocksFreq(&RCC_Clock);
		
        clock->core = RCC_Clock.SYSCLK_Frequency;
        clock->hclk = RCC_Clock.HCLK_Frequency;
        //clock->pclk2 = clock->core;
        clock->pclk1 = RCC_Clock.PCLK1_Frequency;          
    }

/**
 *@brief    获取系统信息，CPU_ID,flashsize
 *@param    *clock：  时钟指针，返回系统时钟
 *@retval   none
*/    
    static void get_chip_info()
    {
        cpu.chip_id[2] = LL_GetUID_Word0(); //低字节
        cpu.chip_id[1] = LL_GetUID_Word1(); //
        cpu.chip_id[0] = LL_GetUID_Word2(); //高字节

        cpu.flash_size = LL_GetFlashSize();   //芯片flash容量
		
    }
    
    uint32_t get_cpu_calculate_per_sec()
    {
        return cpu.ability;
    }


}
