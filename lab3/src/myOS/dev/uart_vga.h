#ifndef __UART_VGA_H__
#define __UART_VGA_H__

void uart_put_char(unsigned char c);                        // 实现串口输出 单个字符
unsigned char uart_get_char(void);                          // 实现串口输入 单个字符
void uart_put_chars(char *str);                             // 实现串口输出 字符串
unsigned char rd_row(void);                                 // 读取 光标所在的行（高8位）
unsigned char rd_col(void);                                 // 读取 光标所在的列（低8位）
void move(void);                                            // 滚屏：将VGA中内容向上移动一行
void wr_row(unsigned char row_in);                          // 写入 光标所在的行（高8位）
void wr_col(unsigned char col_in);                          // 写入 光标所在的列（低8位）
void wr_cursor(unsigned char row_in, unsigned char col_in); // 写入 光标位置
void clear_screen(void);                                    //清屏（0-23行）
void append2screen(char *str, int color);                   //在当前光标位置输出
void append2srceen_info(char *str, int color);              //输出中断信息
void clear_char(void);                                      //退格（TODO）

#endif