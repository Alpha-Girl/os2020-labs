//string.c
extern void uart_put_chars(char *str);
void ignoreIntBody(void){
    uart_put_chars("Unknown interrupt1\0");
    //append2srceen_info("Unknown interrupt\0",)
}
