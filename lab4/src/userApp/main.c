#include "../myOS/dev/uart_vga.h"
extern void startShell();
extern int myPrintf(int color,const char *format, ...);
extern int myPrintk(int color,const char *format, ...);
void myMain(void){    
    int i;
    clear_screen();
    startShell();
    return;
}
