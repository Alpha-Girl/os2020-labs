extern void outb (unsigned short int port_to, unsigned char value);
void enable_interrupt(void);
void disable_interrupt(void);
extern int myPrintk(int color,const char *format, ...);
void init8259A(void)
{
    
	outb(0x20,0x11);
    outb(0x21,0x20);
    outb(0x21,0x04);
    outb(0x21,0x3);
    outb(0xA0,0x11);
    outb(0xA1,0x28);
    outb(0xA1,0x02);
    outb(0xA1,0x01);
    outb(0x21,0xFF);
    outb(0xA1,0xFF);
    enable_interrupt();
}
