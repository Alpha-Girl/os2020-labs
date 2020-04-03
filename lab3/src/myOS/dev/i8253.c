#include "../i386/io.h"
extern int myPrintk(int color, const char *format, ...);
void enable_interrupt(void);
void disable_interrupt(void);
#define TIMER_FREQ 1193180 //i8253频率
#define FREQUENCY 100      //时钟中断频率
void init8253(void)
{
    disable_interrupt();
    unsigned int divisor = TIMER_FREQ / FREQUENCY; //分频参数
    //初始化
    outb(0x43, 0x34);
    unsigned char low, high;
    //拆分分频参数的低字节和高字节
    low = (divisor & 0xFF);
    high = ((divisor >> 8) & 0xFF);
    //分别写入低字节和高字节
    outb(0x40, low);
    outb(0x40, high);
    myPrintk(0x2, "init8253\n");
    //允许时钟中断
    unsigned char mask = inb(0x21);
    mask = mask & 0xfe;
    outb(0x21, mask);
    enable_interrupt();
}
