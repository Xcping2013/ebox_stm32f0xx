<<<<<<< HEAD
/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

/*
ADC测试
*/
#include "ebox.h"


Analog AD(&PA0);
Analog AD2(&PA2);
Analog AD8(&PB1);

// DMA模式采集
AnalogDMA ADINS(5);


void setup()
{
	ebox_init();
	uart1.begin(115200);
	uart1.printf("begin \r\n");
	PA5.mode(OUTPUT_PP);
//    ewwd.begin(36208);
  // DMA模式下添加需要采集的通道。采集结果按照ADC通道从低到高排列，和加入顺序无关
	ADINS.Add(&PA0);
	ADINS.Add(&PA2);
	ADINS.Add(&PA1);
=======
/**
  ******************************************************************************
  * @file   : *.cpp
  * @author : shentq
  * @version: V1.2
  * @date   : 2016/08/14

  * @brief   ebox application example .
  *
  * Copyright 2016 shentq. All Rights Reserved.
  ******************************************************************************
 */
/**
 * -LQM (2016/9/18)
 *     STM32F0RTC例程，注意，和F1系列不通用
 *     1 创建rtc对象
 * 	   2 调用begin()初始化时钟。1 LSE  0 LSI
 *	   3 设置时钟
 *	   4 设置闹铃，附加闹铃中断回调函数
 */

#include "ebox.h"
#include "bsp.h"

Rtc rtc;

void exit()
{
	Time_T time;
	uart1.printf("\r\n 闹铃");
	rtc.get_time(&time);
	uart1.printf(" %2d:%02d:%2d ",time.Hours,time.Minutes,time.Seconds);
}

void setup()
{
	Date_T date = {LL_RTC_WEEKDAY_WEDNESDAY, 13, LL_RTC_MONTH_SEPTEMBER, 16};
	Time_T time = {LL_RTC_TIME_FORMAT_AM_OR_24, 12, 1, 1};

	ebox_init();
	uart1.begin(115200);

	uart1.printf("\r\n");
	uart1.printf("\n\r **** RTC Test**** ");
// EOK,初始化成功，并且RTC时间在运行，不需要设置日期，时间。否则需要设置
	if (rtc.begin(1) != EOK)
	{
		rtc.set_Date(date);
		rtc.set_time(time);
	}
	delay_ms(100);
	// 设置闹铃
	time.Minutes += 2;
	rtc.set_alarm(time);
	rtc.attach_alarm_interrupt(&exit);
>>>>>>> 71abb22d27f3e1a1f8582fcafce00402d13f7271
}

int main(void)
{
	// date_time_t 声明在common.h中，包含年月日时分秒星期信息
	date_time_t dtime;
	setup();
	while (1)
	{
<<<<<<< HEAD
		i = AD.read();
		uart1.printf("PA2 = %d ---",i);
		ADINS.read();
		uart1.printf("DMA = %d %d %d %d %d ---",ADINS.Buffer[0],ADINS.Buffer[1],ADINS.Buffer[2],ADINS.Buffer[3],ADINS.Buffer[4]);
	
		i = AD8.read();
		uart1.printf("PB8 = %d ---",i);

		i = AD.read_voltage();
		uart1.printf("PA0 V = %d mv ---",i);
		PA5.toggle();
		delay_ms(3000);
		uart1.printf("cpu temperature: %.2f \r\n",sys.get_cpu_temperature());
=======
		rtc.get_date_time(&dtime);
		uart1.printf("\n\r %2d:%02d:%2d秒",dtime.hour,dtime.min,dtime.sec);
		uart1.printf("\n\r 20%2d年%02d月%2d日 星期%02d",dtime.year,dtime.min,dtime.date,dtime.week);
		delay_ms(30000);
>>>>>>> 71abb22d27f3e1a1f8582fcafce00402d13f7271
	}
}


