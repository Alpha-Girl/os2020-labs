//实现myPrint功能，需要调用到格式化输出的function（vsprintf）
extern void append2screen(char *str, int color);
extern void uart_put_chars(char *str);
#include "types.h"
extern int vsprintf(char *buf, const char *fmt, va_list args);
char kBuf[400]; //TODO: fix me
int myPrintk(int color, const char *format, ...)
{
    va_list args;
    int i;
    va_start(args, format);
    i = vsprintf(kBuf, format, args); //格式化字符串format，输出到kBuf
    va_end(args);
    uart_put_chars(kBuf);       //串口输出
    append2screen(kBuf, color); //VGA输出
    return 0;
}

char uBuf[400]; //TODO: fix me
int myPrintf(int color, const char *format, ...)
{
    va_list args;
    int i;
    va_start(args, format);
    i = vsprintf(uBuf, format, args);
    va_end(args);
    uart_put_chars(uBuf);
    append2screen(uBuf, color);
    return 0;
}
