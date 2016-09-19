#include <stdio.h>
#include <stdarg.h>
#include "stdlib.h"
#include "printf.h"
//#include <malloc.h>

#define IsDigital(c)		((c>='0') && (c<='9'))//判断是否为数字 

static char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
char *strbuf;
void ReverseStr(char *str);
int mystrlen(char *str)//求字符串长度
{
	int i=0;
	while(*(str++))
		i++;
	return i;
} 
int Str2Digital(const char **str)//将字符串转换成整数
{
	int i=0;
	while(IsDigital(**str))
		i = i*10+*((*str)++) - '0';
	return i;
}
void Float2Str(float num,char *str,int precision)//浮点数转换成字符串
{
	int m;
	float n;
	int k=0;//控制指针走向
	m = (int)num;
	n = num-(float)m;	
	while(m)
	{
			*str= *(m%10 +digits);
			m=m/10;
			k++;
			str++;
	}
	*str = '\0';
	ReverseStr(str-k);//整数倒置
	*(str++)='.';
	n = n*10.0;
	while(precision-- && n)
	{
		m = (int)n;
		*str= *(m+digits);
		n=(n-(float)m)*10.0;
		str++;
	}
	*str='\0';
}
void Int2Str(int num,char *str)//整数转换成字符串
{
	int k=0;
	if(num <0)
	{	
		num = -num;
		*str++='-';
	}
	while(num)
	{
			*str= *(num%10 +digits);
			num=num/10;
			str++;
			k++;
	}
	*str = '\0';
	ReverseStr(str-k);	
}
void ReverseStr(char *str)//字符串倒置
{
	char tmp;
	int i,len;
	
	len = mystrlen(str);
	for(i=0;i<len/2;i++)
	{
		tmp =*(str+i);
		*(str+i) = *(str+len-1-i);
		*(str+len-1-i) = tmp;		
	}
}
void Convert(int num,int n , char *str)//十进制转换成任意进制
{
	while(num)
	{
			*str= *(num%n +digits);
			num=num/n;
			str++;
	}
	*str = '\0';
}

char * AddBuf(char *buf,char *str,int precision,int width,int flag)//字符串添加到buf里
{
	int len = 0;
	int i;
	len =mystrlen(str);
//	printf("len:%dstr:%s",len,str);
	
	if( precision < 0)
		precision = len;
	else if(len > precision)
		len =precision;
	if(!flag)
		while(--width >0 && width-len > 0)
			*buf++ = ' ';
	for(i=0;i<len;i++)
		*buf++ = *str++;
	while(--width>0 && width-len>0)
		*buf++ = ' ';
	return buf;
}
int MyVsprintf(char *buf,const char *format,va_list args)
{
	
	int width;//字符宽度
	int precision;//精确度
	int qualifier;//修饰符
	int flag=0;//标号 标志对齐方式,为0时表示右对齐方式
	//int len=0;//用于记录str长度
	char *str;
//	int i;
	//char *pbuf=buf;
	str =(char *)malloc(20);	
	while(*format)
	{

		if(*format !='%')
			*buf++ = *format++;
		else//format =='%'
			{
				format++;
				//检查对齐方式
				if(*format == '-')
				{
					flag=1;//左对齐方式
					format++;
				}
				//检查字符宽度
				width = -1;
				if(IsDigital(*format))
					width = Str2Digital(&format);
				else if(*format == '*')
				{
					width = va_arg(args,int);
					if(width <0)
					{
						width = -width;
						flag =1;
					}
					format++;
				}	
				//检查精确度
				precision= -1;
				if(*format == '.')
				{
					format++;
					if(IsDigital(*format))
						precision = Str2Digital(&format);
					else if(*format == '*')
					{
						precision = va_arg(args,int);
						if(precision < 0)
							precision = 0;
						format++;
					}
				}
				//检查修饰符
				qualifier = -1;
				if(*format == 'h' ||*format == 'l' ||*format == 'L')
				{
					qualifier = *format;
					format ++;
				}
				//检查格式打印字符			
				
				switch(*format)
				{
						case 'c':
							if(!flag)//右对齐方式							
								while(--width>0)
									*buf++ = ' ';
							*(buf++) = va_arg(args,int);
							while(--width>0)//左对齐
									*buf++ = ' ';			

							break;
						case 's':
							str = va_arg(args,char *);
							buf=AddBuf(buf,str,precision,width, flag);
							break;
						case 'o':
							Convert(va_arg(args,int), 8, str);
							ReverseStr(str);
							buf=AddBuf(buf,str,precision,width, flag);
							break;
						case 'd':
							Int2Str(va_arg(args,int),str);
							buf =AddBuf(buf,str,precision,width, flag);
							break;
						case 'x':
							Convert(va_arg(args,int),16,str);
							ReverseStr(str);
							buf=AddBuf(buf,str,precision,width,flag);						
							break;
						case 'f':
							Float2Str(va_arg(args,double),str,8);
							buf=AddBuf(buf,str,precision,width,flag);
							break;
						default:
							break;
				}
				format++;
				continue;
			}
			
	}
	*buf = '\0';		
	free(str);
	return mystrlen(buf);
}
//int MyPrintf(const char *format,...)
//{
//	va_list args;
//	char PrintBuf[100];
//	int n ;
//	char *p;

//	p = PrintBuf;
//	va_start(args,format);
//	n =MyVsprintf(PrintBuf,format,args);	
//	while(*p)
//	{
//		putchar(*p);
//		p++;
//	}
//	va_end(args);
//	return n;
//}


