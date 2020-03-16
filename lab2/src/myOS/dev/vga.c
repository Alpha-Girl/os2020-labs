//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用
#define screen_size 25*80
//extern void disable_interrupt(void);
//extern void enable_interrupt(void);

extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);
int port=0xB8000;
void clear_screen(void) {
    int i;
    //disable_interrupt();
    for(i = 0; i < screen_size; i++);
    {
        __asm__ __volatile__ ("movl $0x2f302f30,%%eax"::"Nd" (port));
        port = port + 4;
    }	
    //enable_interrupt();
}

void append2screen(char *str,int color){
    int i, output;
    //disable_interrupt();
    for(i = 0; ; i++)
    {
        if(str[i] != '\n')
        {
            output = 0x2f002f00+str[i]+str[i+1]*16*16*16*16;
            __asm__ __volatile__ ("movl %%eax,%%ebx"::"a" (output),"Nd"(port));
            port = port + 2;
        }
        else
            break;
    }
    //enable_interrupt();
}