/*
file   : wdg.cpp
author : shentq
version: V1.1
date   : 2015/7/5
date   : 2016/7/24 LQM��ֲ��STM32F0ƽ̨,ʹ��HAL��LL��
Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#include "wdg.h"

const uint16_t PR[7] = {4,8,16,32,64,128,256};

void EBOX_IWDG::begin(uint16_t ms)
{

	uint8_t pr  = 0;
	uint16_t rlr = 0;

	for (pr = 0; pr < 7; pr++)
	{
  rlr = ms * 40 / PR[pr];
	if (rlr <= 0x0fff) break;
	}
	if (pr > 7 || rlr > 0x0fff)
	{
	pr = 6;
	rlr = 0xfff;
	}


  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
  }

  /* Configure the IWDG with window option disabled */
  /* ------------------------------------------------------- */
  /* (1) Enable the IWDG by writing 0x0000 CCCC in the IWDG_KR register */
  /* (2) Enable register access by writing 0x0000 5555 in the IWDG_KR register */
  /* (3) Write the IWDG prescaler by programming IWDG_PR from 0 to 7 - LL_IWDG_PRESCALER_4 (0) is lowest divider*/
  /* (4) Write the reload register (IWDG_RLR) */
  LL_IWDG_Enable(IWDG);                             /* (1) */
  LL_IWDG_EnableWriteAccess(IWDG);                  /* (2) */
  LL_IWDG_SetPrescaler(IWDG, pr);                   /* (3) */
  LL_IWDG_SetReloadCounter(IWDG, rlr);              /* (4) */
}
void EBOX_IWDG::feed()
{
  /*reload*/
	LL_IWDG_ReloadCounter(IWDG);
}
