#include "../include/task.h"
#include "../include/myPrintk.h"

void schedule(void);
void destroyTsk(int takIndex);

/**
 * 内部接口参考
 */
#define TSK_RDY 0
typedef struct rdyQueueFCFS{
     myTCB * head;
     myTCB * tail;
     myTCB * idleTsk;
} rdyQueueFCFS;

rdyQueueFCFS rqFCFS;

void rqFCFSInit(myTCB* idleTsk) {
}

int rqFCFSIsEmpty(void) {
}

myTCB * nextFCFSTsk(void) {
}

/* tskEnqueueFCFS: insert into the tail node */
void tskEnqueueFCFS(myTCB *tsk) {
     if(rqFCFSIsEmpty()){
          rqFCFS.head=tsk;
     }
     else
     rqFCFS.tail->next=tsk;
     rqFCFS.tail=tsk;
}

/* tskDequeueFCFS: delete the first node */
void tskDequeueFCFS(myTCB *tsk) {
     rqFCFS.head=rqFCFS.head->next;
     if(tsk==rqFCFS.tail)
          rqFCFS.tail=(void *)0;
}

// 用于初始化新创建的 task 的栈
// 这样切换到该任务时不会 stack underflow
void stack_init(unsigned long **stk, void (*task)(void)){
}

/**
 * 必须实现的外部接口
 */
void tskStart(myTCB *tsk){
#error "TODO: 实现本函数"
}

void tskEnd(void){
#error "TODO: 实现本函数"
}

/* createTsk
 * tskBody():
 * return value: taskIndex or, if failed, -1
 */
int createTsk(void (*tskBody)(void)) {
#error "TODO: 实现本函数"
}

/* destroyTsk
 * takIndex:
 * return value: void
 */
void destroyTsk(int takIndex) {
#error "TODO: 实现本函数"
}

unsigned long **prevTSK_StackPtr;
unsigned long *nextTSK_StackPtr;
void context_switch(myTCB *prevTsk, myTCB *nextTsk) {
#error "TODO: 实现本函数"
}

void scheduleFCFS(void) {
#error "TODO: 实现本函数"
}

void schedule(void) {
     scheduleFCFS();
}

/**
 * idle 任务
 */
void tskIdleBdy(void) {
#error "TODO: 实现本函数"
}

unsigned long BspContextBase[STACK_SIZE];
unsigned long *BspContext;

//start multitasking
void startMultitask(void) {
     BspContext = BspContextBase + STACK_SIZE -1;
     prevTSK_StackPtr = &BspContext;
     currentTsk = nextFCFSTsk();
     nextTSK_StackPtr = currentTsk->stkTop;
     CTX_SW(prevTSK_StackPtr,nextTSK_StackPtr);
}

void TaskManagerInit(void) {
#error "TODO: 实现本函数"
     // 初始化 TCB 数组
     // 创建 idle 任务
     // 创建 init 任务（使用 initTskBody）
     // 切入多任务状态
     int i;
     myTCB *thisTCB;
     for (i=0;i<TASK_NUM;i++){
          thisTCB=&tcbPool[i];
          thisTCB->tcbIndex=i;
          if(i==TASK_NUM-1)
               thisTCB->next=(myTCB *)0;
          else
               thisTCB->next=&tcbPool[i+1];
          thisTCB->stkTop=thisTCB->stack +STACK_SIZE -1;

     }
     idleTsk=&tcbPool[0];
     stack_init(&(idleTsk->stkTop),tskIdleBdy);
     rqFCFSInit(idleTsk);
     firstFreeTsk=&tcbPool[1];
     createTsk(initTskBody);
     myPrintk(0x2,"START MULTITASKING......\n");
     startMultitask();
     myPrintk(0x2,"STOP MULTITASKING......ShutDown\n");
}
