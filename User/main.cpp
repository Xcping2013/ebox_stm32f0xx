/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

/*
���벶��ʵ��-�������ں�Ƶ��
������Ϊʹ�����벶��ģʽ����һ��PWM�źŵ����ں�Ƶ��
�뽫PA0��PB6ʹ��������������
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








