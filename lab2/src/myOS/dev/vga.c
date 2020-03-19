//本文件实现vga的相关功能，清屏和屏幕输出，clear_screen和append2screen必须按照如下实现，可以增加其他函数供clear_screen和append2screen调用

extern int myPrintk(int color,const char *format, ...);
extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);
void move(void);
#define vga_base 0xB8000
#define srceen_width 80
#define srceen_height 25
unsigned short int *port,*tmp;
unsigned int p;
unsigned char row=0,col=0;
unsigned char rd_row(void);
unsigned char rd_col(void);
void wr_row(unsigned char row_in);
void wr_col(unsigned char col_in);
void wr_cursor(unsigned char row_in,unsigned char col_in);


void clear_screen(void) {
    int i;
    port = vga_base;
    p = vga_base;
    for(i = 0; i < srceen_width * srceen_height; i++)
    {
        
        *port = 0x0f20;
        p = p + 2;
        port = p;
    }
    p = vga_base;
    row = 0;
    col = 0;
    //wr_cursor(row,col);	
}

void append2screen(char *str,int color){
    int i,j,c;
    unsigned short int output;
    for(i = 0; ; i++)
    {
        if(str[i] != '\0')
        {
            if(str[i] != '\n')
            {
                
                output = color * 16 * 16 + str[i];
                port = vga_base + row * 2 * srceen_width +col*2;
                *port = output;
                col++;
                if(col > (srceen_width - 1))
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
        if(row == srceen_height)
            {
                    move();
                    row = 24;
                    col = 0;
            }
        //myPrintk(0x7,"row: %d, col: %d\n",rd_row(),rd_col());
        c=row*80+col;
        wr_cursor(c/256,c%256);
    }
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
        *tmp=0x0f20;
    }
}

unsigned char rd_row(void){
    outb(0x3D4,0xE);
    return inb(0x3D5);
}

unsigned char rd_col(void){
    outb(0x3D4,0xF);
    return inb(0x3D5);
}

void wr_row(unsigned char row_in){
    outb(0x3D4,(unsigned char)0xE);
    outb(0x3D5,row_in);
}
void wr_col(unsigned char col_in){
    outb(0x3D4,(unsigned char)0xF);
    outb(0x3D5,col_in);
}

void wr_cursor(unsigned char row_in,unsigned char col_in){
    wr_row(row_in);
    wr_col(col_in);
}