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


void setup()
{
    ebox_init();
    PA5.mode(OUTPUT_PP);
}

int main(void)
{
    setup();
    while(1)
    {
      PA5.toggle();
      delay_ms(5000);
    }
}








