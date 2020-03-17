//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用

extern int myPrintk(int color,const char *format, ...);
extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);
#define vga_base 0xB8000
unsigned short int *port,*tmp;
unsigned int p,st;
unsigned char row=0,col=0;
void wr_row(unsigned char in_row);
void wr_col(unsigned char in_col);
unsigned char gt_row(unsigned char out_row);
unsigned char gt_col(unsigned char out_col);
void clear_screen(void) {
    int i;
    int a;
    a=25*80;
    port=vga_base;
    p=vga_base;
    for(i = 0; i < a; i++)
    {
        
        *port = 0x0020;
        p=p+2;
        port=p;
    }
    p=vga_base;	
}

void append2screen(char *str,int color){
    int i,j;
    unsigned short int output;
    //disable_interrupt();
    for(i = 0; ; i++)
    {
        if(str[i] != '\0')
        {
            if(str[i]!='\n')
            {
                if(row==25)
                {
                    move();
                    row=24;
                    col=0;
                }
                output = color*16*16+str[i];
                port=vga_base+row*160+col*2;
                *port = output;
                col++;
                if(col>79)
                {
                row++;
                col=0;
                }
            }
            else
            {
                row++;
                col=0;
            }
            
        }
        else
        {
            break;
        }
        
    }
    //enable_interrupt();
}
void move()
{
    int i,j;
    unsigned short int a;
    for(i=0;i<25;i++)
    {
        for(j=0;j<80;j++)
            {
                tmp=vga_base+(i+1)*160+2*j;
                a=*tmp;
                tmp=tmp-80;
                *tmp=a;
            }
    }
    for(j=0;j<80;j++)
    {
        tmp=vga_base+24*160+2*j;
        *tmp=0x0020;
    }
}