#include "../../include/task_sched.h"


//本文件实现了调度算法 这里已FIFO既FCFS给出一个例子 
//参照本例实现其他的两个算法 请在对应的.c 文件里实现
//最终目标都是实现一个scheduler（如本文件最后的那个）供别的地方调用
myTCB *rqPRIO0;  //ready queue

void rqPRIO0Init(void) {
	rqPRIO0 = idleTsk;	// head <- idleTsk
	dLinkListInit((dLinkedList *)(&(rqPRIO0->thisNode)));
}

myTCB * nextPRIO0Tsk(void) {
	return (myTCB*)dLinkListFirstNode((dLinkedList*)rqPRIO0);	
}

/*
 *tskEnqueueFIFO: insert into the tail node
 */
void tskEnqueuePRIO0(myTCB *tsk){
    myTCB *point;
    point=rqPRIO0;
    while(tsk->para.priority>point->para.priority&&point->next!=0)
        point=point->next;
    if(tsk->para.priority>point->para.priority)
	    dLinkInsertAfter((dLinkedList*)point,(dLink_node*)point,(dLink_node*)tsk);	
    else
        dLinkInsertBefore((dLinkedList*)point,(dLink_node*)point,(dLink_node*)tsk);
}

/*
 *tskDequeueFIFO: delete the first node
 */
void tskDequeuePRIO0(myTCB *tsk){
	dLinkDelete((dLinkedList*)rqPRIO0,(dLink_node*)tsk);	
}

/*===========================================
 *======FCFS=================================
 *===========================================*/
void schedulerInit_PRIO0(void){
    rqPRIO0Init();

	/* default for all task except idleTsk*/
	defaultTskPara.schedPolicy = SCHED_PRIO;

	/* special for idleTsk*/
	_setTskPara(idleTsk,&defaultTskPara);
	idleTsk->para.schedPolicy = SCHED_IDLE;
}

struct scheduler SCHEDULER_PRIO0 = {
    .type = SCHEDULER_PRIORITY0,
    .nextTsk_func = nextPRIO0Tsk,
    .enqueueTsk_func = tskEnqueuePRIO0,
    .dequeueTsk_func = tskDequeuePRIO0,
    .schedulerInit_func = schedulerInit_PRIO0,
	.createTsk_hook = NULL,
    .tick_hook = NULL
};

