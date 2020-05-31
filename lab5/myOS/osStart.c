#include "include/i8253.h"
#include "include/i8259.h"
#include "include/irq.h"
#include "include/uart.h"
#include "include/vga.h"
#include "include/mem.h"
#include "include/task.h"
#include "include/myPrintk.h"

void osStart(void){
     //pressAnyKeyToStart(); // prepare for uart device
     init8259A();
     init8253();
     enable_interrupt();

     clear_screen();

#error "TODO: 初始化内存和任务管理"

     while(1);
}
