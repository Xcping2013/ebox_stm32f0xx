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



//Ĭ�Ͽ���16ͨ�� ����DMA+ADC����ת��ģʽ���ṩAD�ɼ�����
//ֻ�轫IO����ΪAINģʽ���ɶ�ȡ������Ӧ�ĵ�ѹ
#define CH 1
volatile uint16_t  AD_value[1];   //�������ADCת�������Ҳ��DMA��Ŀ���ַ

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
 *@brief    ADC���ã���ADC1����Ϊ16ͨ�������������������28.5�����ڣ�10bit����
 *@param    NONE
 *@retval   NONE
*/
//void ADC1_configuration(void)
//{

//    ADC_InitTypeDef  ADC_InitStructure;

//    ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

//    /* ADC1 configuration ------------------------------------------------------*/
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
//    ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת��������ɨ��ģʽ
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ����ת���ر�
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
//    ADC_InitStructure.ADC_NbrOfChannel = CH;	//˳����й���ת����ADCͨ������Ŀ
//    ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

//    /* ADC1 regular channel11 configuration */
//    //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
//    //ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����

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

//    // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
//    ADC_DMACmd(ADC1, ENABLE);

//    /* Enable ADC1 */
//    ADC_Cmd(ADC1, ENABLE);	   //ʹ��ָ����ADC1
//    /* Enable ADC1 reset calibaration register */
//    ADC_ResetCalibration(ADC1);	  //��λָ����ADC1��У׼�Ĵ���
//    /* Check the end of ADC1 reset calibration register */
//    while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�

//    /* Start ADC1 calibaration */
//    ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
//    /* Check the end of ADC1 calibration */
//    while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�

//}
/**
 *@name     void DMA_configuration(void)
 *@brief    ADC��DMA���ã���ADC1����ΪDMA�Զ�����ģʽ��ת������Զ��Ĵ��䵽�ڴ�
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
 *@brief    ADC��ʼ��
 *@param    NONE
 *@retval   NONE
*/
//void ADC1_init(void)
//{

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE );	  //ʹ��ADC1ͨ��ʱ�ӣ������ܽ�ʱ��
//    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����

//    ADC1_configuration();
//    DMA_configuration();
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE);	 //����DMAͨ��
//}
/**
 *@name     uint16_t analog_read(GPIO *pin)
 *@brief    ��ȡADC1ĳ�������ϵ�ģ��ת�����
 *@param    pin��ADC1ĳͨ��ӳ�������
 *@retval   ���������ȷ�򷵻ظ����ŵ�ģ���ѹֵ����Ӧ��10bit��ADCת�����
            ������Ŵ��󷵻�0��
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
 *@brief    ADC��ʼ��
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
		/* Set ADC group regular trigger polarity �ⲿ�������� */
		// LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
		/* Set ADC group regular conversion data transfer */
		// LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
		/* Set ADC group regular overrun behavior */
		LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

		/* Set ADC group regular sequencer */
		/* Set ADC group regular continuous mode һ�δ���ת�������е�����ͨ��*/
    	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
//		LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);
		LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

		/* Set ADC group regular continuous mode һ�δ�����˳��ת�������е�һ��ͨ��*/
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
 *@brief    ��ȡADC1ĳ�������ϵ�ģ��ת�����
 *@param    channel��ADC1 ͨ��
 *@retval   ���������ȷ�򷵻ظ����ŵ�ģ���ѹֵ����Ӧ��12bit��ADCת�����
            ������Ŵ��󷵻�0��
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
 *@brief    ��ȡĳ�������ϵ�ģ���ѹ
 *@param    channel��ADC1���Ŷ�Ӧ��ͨ��
 *@retval   ���������ȷ�򷵻ظ����ŵ�ģ���ѹֵ����Ӧ��ģ���ѹ��Ĭ�ϲο���ѹΪ3.3V
            ������Ŵ��󷵻�0��
*/
uint16_t analogin_read_voltage(uint32_t *channel){
	return __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI,analogin_read(channel),LL_ADC_RESOLUTION_12B);
}

/**
 *@name     uint16_t analog_read_temperature(void)
 *@brief    ��ȡ�ڲ��¶ȴ�����
 *@param    void
 *@retval   �¶�ֵ
*/
uint16_t analog_read_temperature(void){
	uint32_t  channel;
	channel = LL_ADC_CHANNEL_TEMPSENSOR;
	return __LL_ADC_CALC_TEMPERATURE(VDDA_APPLI,analogin_read(&channel),LL_ADC_RESOLUTION_12B);
}
