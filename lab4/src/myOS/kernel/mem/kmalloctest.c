#include "../../include/kmalloc.h"
#include "../../include/myPrintk.h"
#define NULL 0
extern void addNewCmd(	unsigned char *cmd,
			int (*func)(int argc, unsigned char **argv),
			void (*help_func)(void),
			unsigned char* description);
int testCase3(int argc, unsigned char **argv){
	//======for kmalloc===============================
	char*buf1 = (char*)kmalloc(11);
	char*buf2 = (char*)kmalloc(21);

	for(int i=0;i<9;i++) *(buf1+i) = '+';
	*(buf1+9) = '\n';
	*(buf1+10) = '\000';

	for(int i=0;i<19;i++) *(buf2+i) = ',';
	*(buf2+19) = '\n';
	*(buf2+20) = '\000';

	myPrintk(0x5, "We allocated 2 buffers.\n");
	myPrintk(0x5, "BUF1(size=9, addr=0x%x) filled with 9(+): ",(unsigned long)buf1);
	myPrintk(0x7,buf1);
	myPrintk(0x5, "BUF2(size=19, addr=0x%x) filled with 19(,): ", (unsigned long)buf2);
	myPrintk(0x7,buf2);

	myPrintk(0x7,"\n");

	kfree((unsigned long)buf1);
	kfree((unsigned long)buf2);

	return 0;
}
void kmemTestCaseInit(void){	
addNewCmd("testkMalloc1\0", testCase3, NULL, "kMalloc, write and read.\0");	
}