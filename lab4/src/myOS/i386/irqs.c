#include "../dev/uart_vga.h"
void ignoreIntBody(void){
    append2srceen_info("Unknown interrupt1\0",0x4);
    return;
}
