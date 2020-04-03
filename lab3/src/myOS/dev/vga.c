//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用

extern int myPrintk(int color, const char *format, ...);
#include "../i386/io.h"

#define vga_base 0xB8000
#define srceen_width 80
#define srceen_height 25

// 全局变量
unsigned short int *port;       // 指向当前输出的地址
unsigned int p;                 // 当前输出的地址的值
unsigned char row = 0, col = 0; // 行列

unsigned char rd_row(void);                                 // 读取 光标所在的行（高8位）
unsigned char rd_col(void);                                 // 读取 光标所在的列（低8位）
void move(void);                                            // 滚屏：将VGA中内容向上移动一行
void wr_row(unsigned char row_in);                          // 写入 光标所在的行（高8位）
void wr_col(unsigned char col_in);                          // 写入 光标所在的列（低8位）
void wr_cursor(unsigned char row_in, unsigned char col_in); // 写入 光标位置

void clear_screen(void)
{
    int i;
    port = (unsigned short int *)vga_base;             //指针指向 第0行 第0列
    p = vga_base;                                      //指针对应地址
    for (i = 0; i < srceen_width * srceen_height; i++) //输出空格 实现清屏
    {

        *port = 0x0f20;
        p = p + 2;
        port = (unsigned short int *)p;
    }
    p = vga_base; //指针对应地址 置为 0xB8000
    row = 0;      //行列置零
    col = 0;
    wr_cursor(row, col); //光标置零
}

void append2screen(char *str, int color)
{
    int i, j, c;
    unsigned short int output;
    for (i = 0;; i++)
    {
        if (str[i] != '\0') //字符串是否结束
        {
            if (str[i] != '\n') //是否换行
            {
                output = color * 16 * 16 + str[i];
                //颜色 ：前8位   ASCII码： 后8位
                port = (unsigned short int *)(vga_base + row * 2 * srceen_width + col * 2);
                //把指针指向 当前行列所指位置
                *port = output;               //赋值
                col++;                        //列移动
                if (col > (srceen_width - 1)) //判断是否需要换行
                {
                    row++;
                    col = 0;
                }
            }
            else
            {
                row++;
                col = 0;
            }
        }
        else
        {
            break;
        }
        if (row == srceen_height - 1) //是否需要滚屏
        {
            move();
            row = 23;
            col = 0;
        }
        c = row * 80 + col;
        wr_cursor(c / 256, c % 256); //光标移动
    }
}
void append2srceen_info(char *str, int color)
{
    int i = 0;
    for (i = 0;; i++)
    {
        if (str[i] != '\0')
        {
            port = (unsigned short int *)(vga_base + 24 * 2 * srceen_width + i * 2);
            *port = color * 16 * 16 + str[i];
        }
        else
            break;
    }
    for (; i < 72; i++)
    {
        port = (unsigned short int *)(vga_base + 24 * 2 * srceen_width + i * 2);
        *port = 0x0f20;
    }
}
void clear_char(void)
{
    int c;
    if (col == 0)
    {
        col = 79;
        row--;
    }
    else
    {
        col--;
    }
    port = (unsigned short int *)(vga_base + row * 2 * srceen_width + col * 2);
    *port = 0x0f20;
    c = row * 80 + col;
    wr_cursor(c / 256, c % 256); //光标移动
}
void move()
{
    int i, j;
    unsigned short int *tmp;
    unsigned short int a;
    for (i = 0; i < srceen_height - 1; i++) //将内容向上移动一行
    {
        for (j = 0; j < srceen_width; j++)
        {
            tmp = (unsigned short int *)(vga_base + (i + 1) * 160 + 2 * j); //指针指向第i行第j列
            a = *tmp;                                                       //取值
            tmp = (unsigned short int *)(tmp - 80);                         //指向第（i-1）行第j列
            *tmp = a;                                                       //赋值
        }
    }
    for (j = 0; j < srceen_width; j++) //最后一行 全部置为空格
    {
        tmp = (unsigned short int *)(vga_base + 23 * 160 + 2 * j);
        *tmp = 0x0f20;
    }
}

unsigned char rd_row(void)
{
    outb(0x3D4, 0xE);
    return inb(0x3D5);
}

unsigned char rd_col(void)
{
    outb(0x3D4, 0xF);
    return inb(0x3D5);
}

void wr_row(unsigned char row_in)
{
    outb(0x3D4, (unsigned char)0xE);
    outb(0x3D5, row_in);
}
void wr_col(unsigned char col_in)
{
    outb(0x3D4, (unsigned char)0xF);
    outb(0x3D5, col_in);
}

void wr_cursor(unsigned char row_in, unsigned char col_in)
{
    wr_row(row_in);
    wr_col(col_in);
}