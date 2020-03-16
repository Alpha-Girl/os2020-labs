//实现myPrint功能，需要调用到格式化输出的function（vsprintf）
extern void append2screen(char *str,int color);
extern void uart_put_chars(char *str);
extern int vsprintf(char *buf, const char *fmt, ...);
char kBuf[400];  //TODO: fix me
int myPrintk(int color,const char *format, ...){
    vsprintf(kBuf,format);
    uart_put_chars(kBuf);
    return 0;
}

char uBuf[400];  //TODO: fix me
int myPrintf(int color,const char *format, ...){
    vsprintf(uBuf,format);
    append2screen(uBuf,color);
    return 0;
}