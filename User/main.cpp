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








