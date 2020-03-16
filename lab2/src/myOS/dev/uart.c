//调用inb和outb函数，实现下面的uart的三个函数
extern unsigned char inb(unsigned short int port_from);
extern void outb (unsigned short int port_to, unsigned char value);

#define uart_base 0x3F8

void uart_put_char(unsigned char c){
    outb(uart_base,c);
}

unsigned char uart_get_char(void){
    return inb(uart_base);
}

void uart_put_chars(char *str){
    int i = 0;
    for(i = 0; ; i++)
    {
        if(str[i] != '\n')
            outb(uart_base,str[i]);
        else
            break;
    } 
}