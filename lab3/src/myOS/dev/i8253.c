extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

void init8253(void)
{
    unsigned char c;
	outb(0x43,0x34);
    outb(0x40,0x9c);
    outb(0x40,0x2e);
    c=inb(0x21);
    c = (c >> 1);
    c = (c << 1);
    outb(0x21,c);
}