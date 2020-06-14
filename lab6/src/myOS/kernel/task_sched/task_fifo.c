#include "../../include/task_sched.h"


//本文件实现了调度算法 这里已FIFO既FCFS给出一个例子 
//参照本例实现其他的两个算法 请在对应的.c 文件里实现
//最终目标都是实现一个scheduler（如本文件最后的那个）供别的地方调用
myTCB *rqFIFO;  //ready queue

void rqFIFOInit(void) {
	rqFIFO = idleTsk;	// head <- idleTsk
	dLinkListInit((dLinkedList *)(&(rqFIFO->thisNode)));
}

myTCB * nextFIFOTsk(void) {
	return (myTCB*)dLinkListFirstNode((dLinkedList*)rqFIFO);	
}

/*
 *tskEnqueueFIFO: insert into the tail node
 */
void tskEnqueueFIFO(myTCB *tsk){
	dLinkInsertFifo((dLinkedList*)rqFIFO,(dLink_node*)tsk);	
}

/*
 *tskDequeueFIFO: delete the first node
 */
void tskDequeueFIFO(myTCB *tsk){
	dLinkDelete((dLinkedList*)rqFIFO,(dLink_node*)tsk);	
}

/*===========================================
 *======FCFS=================================
 *===========================================*/
void schedulerInit_FCFS(void){
    rqFIFOInit();

	/* default for all task except idleTsk*/
	defaultTskPara.schedPolicy = SCHED_FCFS;

	/* special for idleTsk*/
	_setTskPara(idleTsk,&defaultTskPara);
	idleTsk->para.schedPolicy = SCHED_IDLE;
}

struct scheduler scheduler_FCFS = {
    .type = SCHEDULER_FCFS,
    .nextTsk_func = nextFIFOTsk,
    .enqueueTsk_func = tskEnqueueFIFO,
    .dequeueTsk_func = tskDequeueFIFO,
    .schedulerInit_func = schedulerInit_FCFS,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};

struct scheduler scheduler_FMQ = {
    .type = SCHEDULER_FCFS,
    .nextTsk_func = nextFIFOTsk,
    .enqueueTsk_func = tskEnqueueFIFO,
    .dequeueTsk_func = tskDequeueFIFO,
    .schedulerInit_func = schedulerInit_FCFS,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};

struct scheduler scheduler_SJF = {
    .type = SCHEDULER_FCFS,
    .nextTsk_func = nextFIFOTsk,
    .enqueueTsk_func = tskEnqueueFIFO,
    .dequeueTsk_func = tskDequeueFIFO,
    .schedulerInit_func = schedulerInit_FCFS,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};
struct scheduler scheduler_RR = {
    .type = SCHEDULER_FCFS,
    .nextTsk_func = nextFIFOTsk,
    .enqueueTsk_func = tskEnqueueFIFO,
    .dequeueTsk_func = tskDequeueFIFO,
    .schedulerInit_func = schedulerInit_FCFS,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};

struct scheduler scheduler_MQ = {
    .type = SCHEDULER_FCFS,
    .nextTsk_func = nextFIFOTsk,
    .enqueueTsk_func = tskEnqueueFIFO,
    .dequeueTsk_func = tskDequeueFIFO,
    .schedulerInit_func = schedulerInit_FCFS,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};