#include <stdio.h>
#include <stdarg.h>
#include "print.h"
#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
#define IsLower(c)	(((c)>='a')&&((c)<='z'))
#define IsDigit(c)	(((c)>='0')&&((c)<='9'))

//int main(void)
//{
//    print("print: %c\n", 'c');
//    print("print %d\n", 1234567);
//    print("print: %f\n", 1234567.1234567);
//    print("print: %s\n", "string test");
//    print("print: %b\n", 0x12345ff);
//    print("print: %x\n", 0xabcdef);
//    print("print: %%\n");
//    return 0;
//}
int LCDPrintf (char *p,const char* fmt,...)
{
	va_list arp;
	char f, r;
	unsigned int i, w,j;
	unsigned long val;
	char c, d, s[16];
	unsigned short xinc=0;

	va_start(arp, fmt);

	while(1) 
	{
		c = *fmt++;
		if (c == 0) break;			
		if (c != '%') //�������%�����������ַ���ֱ�Ӵ�ӡ
		{		
            *p++ = c;
			continue;
		}
		w = f = 0;
		c = *fmt++;
		if (c == '0') //���c=0;��������ǰ����ʾ0
		{				
			f = 1; c = *fmt++;
		}
		while (IsDigit(c))//�ж� 
		{		
			w = w * 10 + c - '0';
			c = *fmt++;
		}
		if (c == 'l' || c == 'L') //�ж��Ƿ��ǳ���������
		{	
			f |= 2; c = *fmt++;
		}
		if (c == 0) break;//�����ʽ���ַ���
		d = c;
		if (IsLower(d)) d -= 0x20;//��Сд��ĸת��Ϊ��д��ĸ
		switch (d) 
		{				/* Type is... */
			case 'S' :					/* String */
			p = va_arg(arp, char*);
			for (j = 0; p[j]; j++) ;
			if (!(f & 2)) {
				while (j++ < w) p[j] = c;
			}

			continue;
            //				 LCDShowString(x+xinc,y,va_arg(arp, char*));
                continue;
			case 'C' :					/* Character */
                 *p++ = (char)va_arg(arp, int);
//				 LCDShowChar(x+xinc,y,(char)va_arg(arp, int), 16,0,color); xinc+=8;continue;
			case 'B' :					/* Binary */
				r = 2; break;
			case 'O' :					/* Octal */
				r = 8; break;
			case 'D' :					/* Signed decimal */
			case 'U' :					/* Unsigned decimal */
				r = 10; break;
			case 'X' :					/* Hexdecimal */
				r = 16; break;
			case 'F' :					/* Hexdecimal */
				r = 11; break;
			default:					/* Unknown */
                            *p++ = c;

//				LCDShowChar(x+xinc,y,c,16,0,color); xinc+=8; continue;
		}
		val = (f & 2) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : va_arg(arp, unsigned int));
		if (d == 'D' && (val & 0x80000000))
		{
			val = 0 - val;
			f |= 4;
		}
		i = 0;
		do 
		{
			d = (char)(val % r); val /= r;
			if (d > 9) 
			{
				d += 7;
				if (c == 'x') d += 0x20;//�����Сд��x����ʾСд��ʮ��������
			}
			s[i++] = d + '0';
		} while (val && i < sizeof(s) / sizeof(s[0]));//�����ݴ���s
		if (f & 4) s[i++] = '-';//�Ը����Ĵ���
		while (i < w--) //��ӡ�ַ�ǰ�˵ġ�0�����߿ո�
		{
            *p++ = (char)((f & 1) ? '0' : ' ');

			//LCDShowChar(x+xinc,y,(char)((f & 1) ? '0' : ' '),16,0,color);
			xinc+=8;
		}
		do //��ӡҪ���������
		{
            *p++ = s[--i];
			//LCDShowChar(x+xinc,y,s[--i], 16,0,color); 
			//xinc+=8;	
		} while (i);
		break;
	}
	va_end(arp);
}




























void    print(char* fmt, ...)
{
    double vargflt = 0;
    int  vargint = 0;
    char* vargpch = NULL;
    char vargch = 0;
    char* pfmt = NULL;
    va_list vp;

    va_start(vp, fmt);
    pfmt = fmt;

    while(*pfmt)
    {
        if(*pfmt == '%')
        {
            switch(*(++pfmt))
            {
                
                case 'c':
                    vargch = va_arg(vp, int); 
                    /*    va_arg(ap, type), if type is narrow type (char, short, float) an error is given in strict ANSI
                        mode, or a warning otherwise.In non-strict ANSI mode, 'type' is allowed to be any expression. */
                    printch(vargch);
                    break;
                case 'd':
                case 'i':
                    vargint = va_arg(vp, int);
                    printdec(vargint);
                    break;
                case 'f':
                    vargflt = va_arg(vp, double);
                    /*    va_arg(ap, type), if type is narrow type (char, short, float) an error is given in strict ANSI
                        mode, or a warning otherwise.In non-strict ANSI mode, 'type' is allowed to be any expression. */
                    printflt(vargflt);
                    break;
                case 's':
                    vargpch = va_arg(vp, char*);
                    printstr(vargpch);
                    break;
                case 'b':
                case 'B':
                    vargint = va_arg(vp, int);
                    printbin(vargint);
                    break;
                case 'x':
                case 'X':
                    vargint = va_arg(vp, int);
                    printhex(vargint);
                    break;
                case '%':
                    printch('%');
                    break;
                default:
                    break;
            }
            pfmt++;
        }
        else
        {
            printch(*pfmt++);
        }
    }
    va_end(vp);
}

void    printch(char ch)
{
    console_print(ch);
}

void    printdec(int dec)
{
    if(dec==0)
    {
        return;
    }
    printdec(dec/10);
    printch( (char)(dec%10 + '0'));
}

void    printflt(double flt)
{
    int icnt = 0;
    int tmpint = 0;
    
    tmpint = (int)flt;
    printdec(tmpint);
    printch('.');
    flt = flt - tmpint;
    tmpint = (int)(flt * 1000000);
    printdec(tmpint);
}

void    printstr(char* str)
{
    while(*str)
    {
        printch(*str++);
    }
}

void    printbin(int bin)
{
    if(bin == 0)
    {
        printstr("0b");
        return;
    }
    printbin(bin/2);
    printch( (char)(bin%2 + '0'));
}

void    printhex(int hex)
{
    if(hex==0)
    {
        printstr("0x");
        return;
    }
    printhex(hex/16);
    if(hex < 10)
    {
        printch((char)(hex%16 + '0'));
    }
    else
    {
        printch((char)(hex%16 - 10 + 'a' ));
    }
}