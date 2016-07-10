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
#include "analog.h"

Analog AD(&PA0);
Analog AD2(&PA2);

void setup()
{
    ebox_init();
    uart1.begin(115200);
    PA5.mode(OUTPUT_PP);
}

int main(void)
{
	__IO uint16_t i;
	setup();
	while (1)
	{
		i = AD2.read();
    uart1.printf("PA0 = %d \r\n",i);
//      i = PA2.pin;
		i = AD.read();
    uart1.printf("PA2 = %d \r\n",i);
		PA5.toggle();
		delay_ms(i);
	}
}








