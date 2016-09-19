#ifndef     __PRINT_H_
#define    __PRINT_H_
#ifdef __cplusplus
extern "C" {
#endif
void    print(char* fmt, ...);
void    printch(char ch);
void    printdec(int dec);
void    printflt(double flt);
void    printbin(int bin);
void    printhex(int hex);
void    printstr(char* str);
int LCDPrintf (char *p,const char* fmt,...);

#define console_print(ch)    putchar(ch)
#ifdef __cplusplus
}
#endif
#endif    /*#ifndef __PRINT_H_*/