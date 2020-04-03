#ifndef __I386_IO_H__
#define __I386_IO_H__

unsigned char inb(unsigned short int port_from);            //从port_from端口读取一个字节 并将对应值存至_in_value
void outb(unsigned short int port_to, unsigned char value); //将value的值输出到port_to端口

#endif