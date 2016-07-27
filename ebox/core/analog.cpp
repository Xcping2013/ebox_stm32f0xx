/*
file   : analog.cpp
author : shentq
version: V1.1
date   : 2015/7/5
brief  : analog read function

Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#include "common.h"



//默认开启16通道 采用DMA+ADC连续转换模式。提供AD采集服务
//只需将IO设置为AIN模式即可读取引脚相应的电压
#define CH 1
volatile uint16_t  AD_value[1];   //用来存放ADC转换结果，也是DMA的目标地址

/* Definitions of environment analog values */
/* Value of analog reference voltage (Vref+), connected to analog voltage   */
/* supply Vdda (unit: mV).                                                  */
#define VDDA_APPLI                       ((uint32_t)3300)
/* Init variable out of expected ADC conversion data range */
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)
/* Variables for ADC conversion data */
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE; /* ADC group regular conversion data */

/* Variables for ADC conversion data computation to physical values */
__IO uint16_t hADCxConvertedData_Temperature_DegreeCelsius = 0;  /* Value of temperature calculated from ADC conversion data (unit: degree Celcius) */
/* Variables for ADC conversion data computation to physical values */
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;  /* Value of voltage calculated from ADC conversion data (unit: mV) */

/**
 *@name     void ADC1_configuration(void)
 *@brief    ADC配置，将ADC1配置为16通道规则采样，采样周期28.5个周期，10bit精度
 *@param    NONE
 *@retval   NONE
*/
//void ADC1_configuration(void)
//{

//    ADC_InitTypeDef  ADC_InitStructure;

//    ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值

//    /* ADC1 configuration ------------------------------------------------------*/
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
//    ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在扫描模式
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//外部触发转换关闭
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
//    ADC_InitStructure.ADC_NbrOfChannel = CH;	//顺序进行规则转换的ADC通道的数目
//    ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

//    /* ADC1 regular channel11 configuration */
//    //设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
//    //ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期

//    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_28Cycles5 );
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_28Cycles5 );

//    // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
//    ADC_DMACmd(ADC1, ENABLE);

//    /* Enable ADC1 */
//    ADC_Cmd(ADC1, ENABLE);	   //使能指定的ADC1
//    /* Enable ADC1 reset calibaration register */
//    ADC_ResetCalibration(ADC1);	  //复位指定的ADC1的校准寄存器
//    /* Check the end of ADC1 reset calibration register */
//    while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1复位校准寄存器的状态,设置状态则等待

//    /* Start ADC1 calibaration */
//    ADC_StartCalibration(ADC1);		//开始指定ADC1的校准状态
//    /* Check the end of ADC1 calibration */
//    while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待

//}
/**
 *@name     void DMA_configuration(void)
 *@brief    ADC的DMA配置，将ADC1配置为DMA自动传输模式。转换结果自动的传输到内存
 *@param    NONE
 *@retval   NONE
*/
void DMA_configuration(void)
{
	/*## Configuration of NVIC #################################################*/
	/* Configure NVIC to enable DMA interruptions */
//  NVIC_SetPriority(DMA1_Channel1_IRQn, 1); /* DMA IRQ lower priority than ADC IRQ */
//  NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	/*## Configuration of DMA ##################################################*/
	/* Enable the peripheral clock of DMA */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	/* Configure the DMA transfer */
	/*  - DMA transfer in circular mode to match with ADC configuration:        */
	/*    DMA unlimited requests.                                               */
	/*  - DMA transfer from ADC without address increment.                      */
	/*  - DMA transfer to memory with address increment.                        */
	/*  - DMA transfer from ADC by half-word to match with ADC configuration:   */
	/*    ADC resolution 12 bits.                                               */
	/*  - DMA transfer to memory by half-word to match with ADC conversion data */
	/*    buffer variable type: half-word.                                      */
	LL_DMA_ConfigTransfer(DMA1,
	                      LL_DMA_CHANNEL_1,
	                      LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
	                      LL_DMA_MODE_CIRCULAR              |
	                      LL_DMA_PERIPH_NOINCREMENT         |
	                      LL_DMA_MEMORY_INCREMENT           |
	                      LL_DMA_PDATAALIGN_HALFWORD        |
	                      LL_DMA_MDATAALIGN_HALFWORD        |
	                      LL_DMA_PRIORITY_HIGH               );

	/* Set DMA transfer addresses of source and destination */
	LL_DMA_ConfigAddresses(DMA1,LL_DMA_CHANNEL_1,LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
	                       (uint32_t)AD_value,
	                       LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	/* Set DMA transfer size */
	LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_1,CH);

	/*## Activation of DMA #####################################################*/
	LL_ADC_REG_SetDMATransfer(ADC1,LL_ADC_REG_DMA_TRANSFER_LIMITED);
	/* Enable the DMA transfer */
	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
}


/**
 *@name     void ADC1_init(void)
 *@brief    ADC初始化
 *@param    NONE
 *@retval   NONE
*/
//void ADC1_init(void)
//{

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE );	  //使能ADC1通道时钟，各个管脚时钟
//    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输

//    ADC1_configuration();
//    DMA_configuration();
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE);	 //启动DMA通道
//}
/**
 *@name     uint16_t analog_read(GPIO *pin)
 *@brief    读取ADC1某个引脚上的模拟转换结果
 *@param    pin：ADC1某通道映射的引脚
 *@retval   如果引脚正确则返回该引脚的模拟电压值所对应的10bit的ADC转换结果
            如果引脚错误返回0；
*/
//uint16_t analog_read(GPIO *pin)
//{
//    switch((uint32_t)pin->port)
//    {
//    case  (uint32_t)GPIOA_BASE:
//        switch(pin->pin)
//        {
//        case GPIO_Pin_0:
//            return AD_value[0];
//        case GPIO_Pin_1:
//            return AD_value[1];
//        case GPIO_Pin_2:
//            return AD_value[2];
//        case GPIO_Pin_3:
//            return AD_value[3];
//        case GPIO_Pin_4:
//            return AD_value[4];
//        case GPIO_Pin_5:
//            return AD_value[5];
//        case GPIO_Pin_6:
//            return AD_value[6];
//        case GPIO_Pin_7:
//            return AD_value[7];
//        }
//    case (uint32_t)GPIOB_BASE:
//        switch(pin->pin)
//        {
//        case GPIO_Pin_0:
//            return AD_value[8];
//        case GPIO_Pin_1:
//            return AD_value[9];
//        }
//    case (uint32_t)GPIOC_BASE:
//        switch(pin->pin)
//        {
//        case GPIO_Pin_0:
//            return AD_value[10];
//        case GPIO_Pin_1:
//            return AD_value[11];
//        case GPIO_Pin_2:
//            return AD_value[12];
//        case GPIO_Pin_3:
//            return AD_value[13];
//        case GPIO_Pin_4:
//            return AD_value[14];
//        case GPIO_Pin_5:
//            return AD_value[15];
//        }
//    }

//    return 0;
//}

/**
 *@name     void ADC1_init(void)
 *@brief    ADC初始化
 *@param    NONE
 *@retval   NONE
*/
void ADC1_init()
{
	/*## Configuration of ADC hierarchical scope: ADC instance #################*/
	/*       ADC must be disabled.                                              */
	if (LL_ADC_IsEnabled(ADC1) == 0)
	{
		/* Enable ADC clock (core clock) */
		LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);
		// ADC Initial
		/* Set ADC clock (conversion clock) */
		LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV2);
		/* Set ADC data resolution */
		LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);
		/* Set ADC conversion data alignment */
		LL_ADC_SetResolution(ADC1, LL_ADC_DATA_ALIGN_RIGHT);
		/* Set ADC low power mode */
		LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

		/* Set ADC group regular trigger source */
		LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
		/* Set ADC group regular trigger polarity 外部触法极性 */
		// LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
		/* Set ADC group regular conversion data transfer */
		// LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
		/* Set ADC group regular overrun behavior */
		LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

		/* Set ADC group regular sequencer */
		/* Set ADC group regular continuous mode 一次触发转换序列中的所有通道*/
    	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
//		LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);
		LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

		/* Set ADC group regular continuous mode 一次触发按顺序转换序列中的一个通道*/
//    	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
//    	LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_1RANK );

		/* Set ADC channels sampling time */
		/* Note: On this STM32 serie, sampling time is common to all channels     */
		/*       of the entire ADC instance.                                      */
		/*       See sampling time configured above, at ADC instance scope.       */
		LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);
	}
  
  	if (__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE() == 0)
	{
		/* Set ADC measurement path to internal channels */
		LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR|LL_ADC_PATH_INTERNAL_VREFINT);
	}

	if (LL_ADC_IsEnabled(ADC1) == 0)
	{
		/* Run ADC self calibration */
		LL_ADC_StartCalibration(ADC1);
		while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
		{
		}
		/* Enable ADC */
		LL_ADC_Enable(ADC1);
		/* Poll for ADC ready to convert */
		while (LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0)
		{
		}
	}
    //DMA_configuration();
}

/**
 *@name     uint16_t analog_read(uint32_t *channel)
 *@brief    读取ADC1某个引脚上的模拟转换结果
 *@param    channel：ADC1 通道
 *@retval   如果引脚正确则返回该引脚的模拟电压值所对应的12bit的ADC转换结果
            如果引脚错误返回0；
*/
uint16_t analogin_read(uint32_t *channel)
{
//	LL_ADC_ClearFlag_EOS(ADC1);
	LL_ADC_REG_SetSequencerChannels(ADC1, *channel);

	LL_ADC_REG_StartConversion(ADC1);
//	while (!LL_ADC_IsActiveFlag_EOS(ADC1));
	while (!LL_ADC_IsActiveFlag_EOC(ADC1));
//	LL_ADC_REG_SetSequencerChannels(ADC1,LL_ADC_CHANNEL_VREFINT);
//	LL_ADC_REG_StartConversion(ADC1);
//	while (LL_ADC_IsActiveFlag_EOC(ADC1) == 0)
//	{
//	}
//	uhADCxConvertedData_Voltage_mVolt = LL_ADC_REG_ReadConversionData12(ADC1);
//	hADCxConvertedData_Temperature_DegreeCelsius = __LL_ADC_CALC_VREFANALOG_VOLTAGE(uhADCxConvertedData_Voltage_mVolt,LL_ADC_RESOLUTION_12B);
//
//  return hADCxConvertedData_Temperature_DegreeCelsius;
	return LL_ADC_REG_ReadConversionData12(ADC1);
//		AD_value[4] = (AD_value[5] + AD_value[6])/2;
	//return AD_value[0];
}

/**
 *@name     uint16_t analog_read_voltage(uint32_t *channel)
 *@brief    读取某个引脚上的模拟电压
 *@param    channel：ADC1引脚对应的通道
 *@retval   如果引脚正确则返回该引脚的模拟电压值所对应的模拟电压，默认参考电压为3.3V
            如果引脚错误返回0；
*/
uint16_t analogin_read_voltage(uint32_t *channel){
	return __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI,analogin_read(channel),LL_ADC_RESOLUTION_12B);
}

/**
 *@name     uint16_t analog_read_temperature(void)
 *@brief    读取内部温度传感器
 *@param    void
 *@retval   温度值
*/
uint16_t analog_read_temperature(void){
	uint32_t  channel;
	channel = LL_ADC_CHANNEL_TEMPSENSOR;
	return __LL_ADC_CALC_TEMPERATURE(VDDA_APPLI,analogin_read(&channel),LL_ADC_RESOLUTION_12B);
}
