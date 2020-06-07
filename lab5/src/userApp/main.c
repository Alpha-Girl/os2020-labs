#include "../myOS/userInterface.h" //interface from kernel

#include "shell.h"

void myTsk0(void);
void myTsk1(void);
void myTsk2(void);
void startShell(void);

// init task 入口
void myMain(void)
{
     //clear_screen();
     createTsk(myTsk0);
     createTsk(myTsk1);
     createTsk(myTsk2);

     initShell();
     memTestCaseInit();
     createTsk(startShell);
     tskEnd();
}
