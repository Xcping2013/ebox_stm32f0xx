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

AnalogS ADINS(5);

EBOX_IWDG ewwd;

void setup()
{
    ebox_init();
    uart1.begin(115200);
    uart1.printf("begin \r\n");
    PA5.mode(OUTPUT_PP);
//    ewwd.begin(36208);
	ADINS.AnalogS_Add(&PA0);
    
}

int main(void)
{
	__IO uint16_t i;
	setup();
	while (1)
	{
		i = AD.read();
		uart1.printf("PA2 = %d \r\n",i);
		ADINS.read();
		uart1.printf("DMA = %d %d %d %d %d \r\n",ADINS.Buffer[0],ADINS.Buffer[1],ADINS.Buffer[2],ADINS.Buffer[3],ADINS.Buffer[4]);
		//ewwd.feed();
		// i = AD8.read();
		// uart1.printf("PB8 = %d \r\n",i);
		//i = PA2.pin;
		// i = AD.read_voltage();
		// uart1.printf("PA0 V = %d mv \r\n",i);
//		ewwd.feed();
		PA5.toggle();
		delay_ms(3000);
		//uart1.printf("cpu temperature: %f \r\n",sys.get_cpu_temperature());
	}
}








