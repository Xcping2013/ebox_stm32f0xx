/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

/*
输入捕获实验-测量周期和频率
本例程为使用输入捕获模式测量一个PWM信号的周期和频率
请将PA0和PB6使用跳线链接起来
*/
#include "ebox.h"


Analog AD(&PA0);
Analog AD2(&PA2);
Analog AD8(&PB1);
EBOX_IWDG ewwd;

void setup()
{
    ebox_init();
    uart1.begin(115200);
    uart1.printf("begin \r\n");
    PA5.mode(OUTPUT_PP);
//    ewwd.begin(36208);
    
}

int main(void)
{
	__IO uint16_t i;
	setup();
	while (1)
	{
		i = AD2.read();
		uart1.printf("PA2 = %d \r\n",i);
		//ewwd.feed();
		i = AD8.read();
		uart1.printf("PB8 = %d \r\n",i);
//      i = PA2.pin;
		i = AD.read_voltage();
		uart1.printf("PA0 V = %d mv \r\n",i);
//		ewwd.feed();
		PA5.toggle();
		delay_ms(i);
    uart1.printf("cpu temperature: %f \r\n",sys.get_cpu_temperature());
	}
}








