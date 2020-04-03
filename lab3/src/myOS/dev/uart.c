//调用inb和outb函数，实现下面的uart的三个函数
#include "../i386/io.h"

#define uart_base 0x3F8
// 实现串口输出 单个字符
void uart_put_char(unsigned char c)
{
    outb(uart_base, c);
}

// 实现串口输入 单个字符
unsigned char uart_get_char(void)
{
    while (!(inb(uart_base + 5) & 1))
        ;
    return inb(uart_base);
}

// 实现串口输出 字符串
void uart_put_chars(char *str)
{
    int i = 0;
    for (i = 0;; i++)
    {
        if (str[i] != '\0' && str[i] != '\n')
            outb(uart_base, str[i]);
        else if (str[i] == '\n')
        {
            outb(uart_base, '\n');
            outb(uart_base, '\r');
        }
        else
            break;
    }
}