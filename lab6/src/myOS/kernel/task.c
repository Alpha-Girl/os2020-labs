#include "../include/task.h"
#include "../include/task_sched.h"
#include "../include/irq.h"
#include "../include/watchdog.h"
#include "../include/myPrintk.h"
#define TSK_RDY 0

extern void busy_n_second(int n);

#include "../include/tcb.h"
extern tskPara initTsk_para;
extern void _setTskPara(myTCB *task, tskPara *para);

extern void initArrList(void);
extern void tskStartDelayed(myTCB* tsk);

extern void schedulerInit(void);
extern void schedule(void);
extern void createTsk_hook(myTCB *created);
extern myTCB *nextTsk(void);

void destroyTsk(int tskIndex);



void tskStart(myTCB *tsk){
	tsk->state = TSK_RDY;
	enqueueTsk(tsk);
}

void tskEnd(void){
	dequeueTsk(currentTsk);
	destroyTsk(currentTsk->tcbIndex);
}

void stack_init(unsigned long** stk,void (*task)(void)){
  *(*stk)-- = (unsigned long) 0x08;        // CS 高地址
  *(*stk)-- = (unsigned long) task;        // eip
  *(*stk)-- = (unsigned long) 0x0202;      // init eflags: IF=1, BIT1=1

  *(*stk)-- = (unsigned long) 0xAAAAAAAA;  // EAX 
  *(*stk)-- = (unsigned long) 0xCCCCCCCC;  // ECX
  *(*stk)-- = (unsigned long) 0xDDDDDDDD;  // EDX 
  *(*stk)-- = (unsigned long) 0xBBBBBBBB;  // EBX

  *(*stk)-- = (unsigned long) 0x44444444;  // ESP
  *(*stk)-- = (unsigned long) 0x55555555;  // EBP
  *(*stk)-- = (unsigned long) 0x66666666;  // ESI
  *(*stk)   = (unsigned long) 0x77777777;  // EDI 低地址    
}

void show_stack(unsigned long* stk){
	myPrintk(0x3,"%x::%x\n",stk,*stk++);  //低地址
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);

	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);
	myPrintk(0x3,"%x::%x\n",stk,*stk++);  //高地址	
}

unsigned long **prevTSK_StackPtr;
unsigned long *nextTSK_StackPtr;
void context_switch(myTCB *prevTsk, myTCB *nextTsk){
	prevTSK_StackPtr = &(prevTsk->stkTop);
	nextTSK_StackPtr = nextTsk->stkTop;	
	CTX_SW(prevTSK_StackPtr,nextTSK_StackPtr);
}

/* createTsk
 * tskBody():
 * return value: taskIndex or, if failed, -1
 */
int createTsk(void (*tskBody)(void), tskPara *para){

	myTCB * allocated=firstFreeTsk;

	if (firstFreeTsk == (void*)0) return -1;

	firstFreeTsk = allocated->next;		
	allocated->next = (void*)0;

	_setTskPara(allocated,para);

	stack_init(&(allocated->stkTop),tskBody);

	createTsk_hook(allocated);

	if (allocated->para.arrTime==0) tskStart(allocated);
	else tskStartDelayed(allocated);

	return allocated->tcbIndex;
}

/* destroyTsk
 * takIndex:
 * return value: void
 */
void destroyTsk(int tskIndex){

	// back to freelist
	tcbPool[tskIndex].next = firstFreeTsk;
	firstFreeTsk = &tcbPool[tskIndex]; 	
	schedule();
}

void tskIdleBdy(void){
	int i=0;
	while(1) {
		myPrintk(0x7,"********IDLE LOOP...................%d.\n",i++);		
		busy_n_second(4);
		//setWatchDogTimer();  //watchdog for poweroff VM
		schedule();
	}
}

unsigned long BspContextBase[STACK_SIZE];
unsigned long *BspContext;

//start multitasking
void startMultitask(void){
	BspContext = BspContextBase + STACK_SIZE -1;
	prevTSK_StackPtr = &BspContext;
	currentTsk = nextTsk();
	nextTSK_StackPtr = currentTsk->stkTop;
	CTX_SW(prevTSK_StackPtr,nextTSK_StackPtr);
}

extern void userSetting_sched(void);
void TaskManagerInit(void){
	int i;
	myTCB *thisTCB;
	
	for (i=0;i<TASK_NUM;i++){
	  thisTCB=&tcbPool[i];

		// init index
		thisTCB->tcbIndex = i;
		
		// init freelist
		if (i==TASK_NUM-1)
			thisTCB->next = (myTCB *)0;
		else
			thisTCB->next = &tcbPool[i+1];

		// init stkTop
		thisTCB->stkTop = thisTCB->stack + STACK_SIZE -1;		
	}

	//task0:idle, create and start, manually
	idleTsk = &tcbPool[0];
	stack_init(&(idleTsk->stkTop),tskIdleBdy);	
	
	firstFreeTsk = &tcbPool[1];		
	
	initArrList();       //for task arriving
	schedulerInit();

	enable_interrupt();   // timer start
	//task1:init
  	createTsk(initTskBody,&initTsk_para);	

	myPrintk(0x2,"START MULTITASKING......\n");	
	startMultitask();
	myPrintk(0x2, "STOP MULTITASKING......ShutDown\n");	
}
