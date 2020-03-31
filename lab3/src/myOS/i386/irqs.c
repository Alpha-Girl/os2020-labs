//string.c
extern void uart_put_chars(char *str);
extern void append2screen_info(char *str,int color);
void ignoreIntBody(void){
    //uart_put_chars("Unknown interrupt1\0");
    append2srceen_info("Unknown interrupt1\0",0x4);
    return;
}
