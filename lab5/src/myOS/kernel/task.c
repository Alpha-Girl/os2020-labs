#include "../include/task.h"
#include "../include/myPrintk.h"
#include "../include/mem.h"
void schedule(void);
void destroyTsk(int takIndex);

/**
 * 内部接口参考
 */
#define TSK_RDY 0
#define TSK_RUN 1
#define TSK_STOP 2
typedef struct rdyQueueFCFS
{
     myTCB *head;
     myTCB *tail;
     myTCB *idleTsk;
} rdyQueueFCFS;

rdyQueueFCFS rqFCFS;

void rqFCFSInit(myTCB *idleTsk)
{
     rqFCFS.head = (void *)0;
     rqFCFS.tail = (void *)0;
     rqFCFS.idleTsk = idleTsk;
}

int rqFCFSIsEmpty(void)
{
     return ((rqFCFS.head == (void *)0) && (rqFCFS.tail == (void *)0));
}

myTCB *nextFCFSTsk(void)
{
     if (rqFCFSIsEmpty())
          return rqFCFS.idleTsk;
     else
          return rqFCFS.head;
}

/* tskEnqueueFCFS: insert into the tail node */
void tskEnqueueFCFS(myTCB *tsk)
{
     if (rqFCFSIsEmpty())
          rqFCFS.head = tsk;
     else
          rqFCFS.tail->next = tsk;
     rqFCFS.tail = tsk;
}

/* tskDequeueFCFS: delete the first node */
void tskDequeueFCFS(myTCB *tsk)
{
     rqFCFS.head = rqFCFS.head->next;
     if (tsk == rqFCFS.tail)
          rqFCFS.tail = (void *)0;
}

// 用于初始化新创建的 task 的栈
// 这样切换到该任务时不会 stack underflow
void stack_init(unsigned long **stk, void (*task)(void))
{
     *(*stk)-- = (unsigned long)0x08;
     *(*stk)-- = (unsigned long)task;
     *(*stk)-- = (unsigned long)0x0202;

     *(*stk)-- = (unsigned long)0xAAAAAAAA;
     *(*stk)-- = (unsigned long)0xCCCCCCCC;
     *(*stk)-- = (unsigned long)0xDDDDDDDD;
     *(*stk)-- = (unsigned long)0xBBBBBBBB;

     *(*stk)-- = (unsigned long)0x44444444;
     *(*stk)-- = (unsigned long)0x55555555;
     *(*stk)-- = (unsigned long)0x66666666;
     *(*stk) = (unsigned long)0x77777777;
}

/**
 * 必须实现的外部接口
 */
void tskStart(myTCB *tsk)
{

     tsk->state = TSK_RDY;
     tskEnqueueFCFS(tsk);
}

void tskEnd(void)
{
     tskDequeueFCFS(currentTsk);
     destroyTsk(currentTsk->tcbIndex);
     schedule();
}

/* createTsk
 * tskBody():
 * return value: taskIndex or, if failed, -1
 */
int createTsk(void (*tskBody)(void))
{
     myTCB *allocted = firstFreeTsk;
     if (allocted == 0)
          return -1;
     stack_init(&(firstFreeTsk->stkTop), tskBody);
     firstFreeTsk = firstFreeTsk->next;
     tskStart(allocted);
     return allocted->tcbIndex;
}

/* destroyTsk
 * takIndex:
 * return value: void
 */
void destroyTsk(int tskIndex)
{
     tcbPool[tskIndex].next = firstFreeTsk;
     firstFreeTsk = &tcbPool[tskIndex];
}

unsigned long **prevTSK_StackPtr;
unsigned long *nextTSK_StackPtr;
void context_switch(myTCB *prevTsk, myTCB *nextTsk)
{
     prevTSK_StackPtr = &(prevTsk->stkTop);
     nextTSK_StackPtr = nextTsk->stkTop;
     CTX_SW(prevTSK_StackPtr, nextTSK_StackPtr);
}

void scheduleFCFS(void)
{
     myTCB *pretsk;
     pretsk = currentTsk;
     currentTsk = nextFCFSTsk();
     currentTsk->state = TSK_RUN;
     context_switch(pretsk, currentTsk);
}

void schedule(void)
{
     scheduleFCFS();
}

/**
 * idle 任务
 */
void tskIdleBdy(void)
{
     while (1)
     {
          schedule();
     }
}

unsigned long BspContextBase[STACK_SIZE];
unsigned long *BspContext;

//start multitasking
void startMultitask(void)
{
     BspContext = BspContextBase + STACK_SIZE - 1;
     prevTSK_StackPtr = &BspContext;
     currentTsk = nextFCFSTsk();
     nextTSK_StackPtr = currentTsk->stkTop;
     CTX_SW(prevTSK_StackPtr, nextTSK_StackPtr);
}
extern unsigned long _end;
unsigned long s[TASK_NUM * STACK_SIZE];
void TaskManagerInit(void)
{
     int i;
     myTCB *thisTCB;
     // 初始化 TCB 数组
     unsigned long *a;
     for (i = 0; i < TASK_NUM; i++)
     {
          thisTCB = &tcbPool[i];
          thisTCB->tcbIndex = i;
          if (i == TASK_NUM - 1)
               thisTCB->next = (myTCB *)0;
          else
               thisTCB->next = &tcbPool[i + 1];
          thisTCB->stack = &s[i * STACK_SIZE];
          thisTCB->stkTop = thisTCB->stack + STACK_SIZE - 1;
     }
     // 创建 idle 任务
     idleTsk = &tcbPool[0];
     stack_init(&(idleTsk->stkTop), tskIdleBdy);

     rqFCFSInit(idleTsk);
     firstFreeTsk = &tcbPool[1];
     // 创建 init 任务（使用 initTskBody）
     createTsk(initTskBody);

     // 切入多任务状态
     myPrintk(0x2, "START MULTITASKING......\n");
     startMultitask();
     myPrintk(0x2, "STOP MULTITASKING......ShutDown\n");
}