#include "../i386/io.h"
void enable_interrupt(void);
void disable_interrupt(void);
extern int myPrintk(int color, const char *format, ...);
void init8259A(void)
{
    //主片初始化
    outb(0x20, 0x11);
    outb(0x21, 0x20); //设置主片从32号中断开始
    outb(0x21, 0x04); //设置从片接入引脚
    outb(0x21, 0x03); //设置中断结束方式
    outb(0xA0, 0x11);
    outb(0xA1, 0x28); //设置从片从40号中断开始
    outb(0xA1, 0x02); //从片输出引脚和主片相连
    outb(0xA1, 0x01); //设置中断结束方式
    //屏蔽所有中断源
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    myPrintk(0x2, "init8259A\n");
    enable_interrupt();
}
