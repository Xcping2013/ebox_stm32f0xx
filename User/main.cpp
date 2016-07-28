/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

/*
ADC����
*/
#include "ebox.h"


Analog AD(&PA0);
Analog AD2(&PA2);
Analog AD8(&PB1);

// DMAģʽ�ɼ�
AnalogDMA ADINS(5);


void setup()
{
	ebox_init();
	uart1.begin(115200);
	uart1.printf("begin \r\n");
	PA5.mode(OUTPUT_PP);
//    ewwd.begin(36208);
  // DMAģʽ�������Ҫ�ɼ���ͨ�����ɼ��������ADCͨ���ӵ͵������У��ͼ���˳���޹�
	ADINS.Add(&PA0);
	ADINS.Add(&PA2);
	ADINS.Add(&PA1);
}

int main(void)
{
	__IO uint16_t i;
	setup();
	while (1)
	{
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
	}
}








