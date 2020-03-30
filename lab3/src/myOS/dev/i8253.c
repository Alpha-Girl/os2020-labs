extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);
extern int myPrintk(int color,const char *format, ...);
void enable_irq(unsigned int irq_no);
void enable_interrupt(void);
void disable_interrupt(void);
#define TIMER_FREQ 1193180
#define FREQUENCY 100
void init8253(void)
{
    disable_interrupt();
    unsigned int divisor = TIMER_FREQ / FREQUENCY;
	outb(0x43,0x34);
    unsigned char low, high;
    low = (divisor & 0xFF);
    high = ( (divisor >> 8) & 0xFF);
    outb(0x40,low);
    outb(0x40,high);
    myPrintk(0x2,"8253");
    unsigned char mask = inb(0x21) ;
    mask= mask & 0xfe;
    outb(0x21,mask);
    enable_interrupt();
}

void enable_irq(unsigned int irq_no) {
	unsigned char mask = 0;
	myPrintk(0x2, "enable_irq mask: %X", mask);
	if(irq_no >= 40) {
		mask = ( (inb(0xA1) ) & (~(1 << (irq_no % 8) ) ) );
		outb(0xA1 , mask);
	} else {
		mask = ( (inb(0x21) ) & (~(1 << (irq_no % 8) ) ) );
		outb(0x21 , mask);
	}
}