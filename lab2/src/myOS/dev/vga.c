//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用

extern void disable_interrupt(void);
extern void enable_interrupt(void);

extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

void clear_screen(void) {	
}

void append2screen(char *str,int color){ 

}