//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用
#define screen_size 25*80
extern void disable_interrupt(void);
extern void enable_interrupt(void);

extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

// 开启中断

static inline void cpu_sti(void) {

	__asm__ volatile ("sti");

	return;

}



// 关闭中断

static inline void cpu_cli(void) {

	__asm__ volatile ("cli" ::: "memory");

	return;

}

unsigned short int *port;
unsigned int p=0xB8000;
void clear_screen(void) {
    int i;
    int a;
    a=25*80;
    port=p;/*
    *port=0x2f302f30;
    p=p+4;
    port=p;
    *port=0x2f202f30;*/
    for(i = 0; i < a; i++)
    {
        
        *port = 0x0020;
        p=p+2;
        port=p;
    }	
}

void append2screen(char *str,int color){
    int i, output;
    //disable_interrupt();
    for(i = 0; ; i++)
    {
        if(str[i] != '\n')
        {
            output = color*16*16+str[i];
            *port = output;
            p=p+2;
            port=p;
        }
        else
            break;
    }
    //enable_interrupt();
}