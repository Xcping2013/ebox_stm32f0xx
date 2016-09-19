/***************************************************************************************************************
Copyright (c) 2005 Embedded Internet Solutions, Inc
All rights reserved. You are not allowed to copy or distribute
the code without permission.
FileName: malloc.c
Author: 何飞                              Version : 1.0                              Date:2009-3-18
Description: 模拟操作系统的格式输出
Version: 	无
Function List: printf	格式输出到终端显示
			vsprintf	格式输出到buf			
**************************************************************************************************************/
#ifndef _PRINTF_H
#define _PRINTF_H

#ifdef _cplusplus
extern "C"{
#endif
int MyVsprintf(char *buf,const char *format,va_list args);
//int MyVsprintf(char *buf,const char * format,...);//格式输出到buf
//extern char * MyPrintf(const char *format,...);//格式输出到终端
extern int Str2Digital(const char **str);
extern void Int2Str(int num , char *str);
//extern char * Int2Str(int num);
extern void ReverseStr(char *str);
extern void Convert(int num,int n , char *str);
extern void Float2Str(float num,char *str,int precision);
extern int mystrlen(char *str);
#ifdef _cplusplus
}
#endif
#endif



