#include "../../include/task_sched.h"

//本文件实现了调度算法 这里已FIFO既FCFS给出一个例子
//参照本例实现其他的两个算法 请在对应的.c 文件里实现
//最终目标都是实现一个scheduler（如本文件最后的那个）供别的地方调用
myTCB *rqPRIO; //ready queue

void rqPRIOInit(void)
{
    rqPRIO = idleTsk; // head <- idleTsk
    dLinkListInit((dLinkedList *)(&(rqPRIO->thisNode)));
}

myTCB *nextPRIOTsk(void)
{
    return (myTCB *)dLinkListFirstNode((dLinkedList *)rqPRIO);
}

/*
 *tskEnqueueFIFO: insert into the tail node
 */
void tskEnqueuePRIO(myTCB *tsk)
{
    //根据优先级插入任务队列
    myTCB *point;
    point = rqPRIO;
    if (point == NULL)
        //空队列的处理
        dLinkInsertBefore((dLinkedList *)point, (dLink_node *)point, (dLink_node *)tsk);
    else
    {
        //找到应插入的节点
        while (tsk->para.priority > point->para.priority && point->next != 0)
            point = point->next;
        if (tsk->para.priority >= point->para.priority)
            dLinkInsertAfter((dLinkedList *)point, (dLink_node *)point, (dLink_node *)tsk);
        else
            dLinkInsertBefore((dLinkedList *)point, (dLink_node *)point, (dLink_node *)tsk);
    }
}

/*
 *tskDequeueFIFO: delete the first node
 */
void tskDequeuePRIO(myTCB *tsk)
{
    dLinkDelete((dLinkedList *)rqPRIO, (dLink_node *)tsk);
}

/*===========================================
 *======FCFS=================================
 *===========================================*/
void schedulerInit_PRIO(void)
{
    rqPRIOInit();

    /* default for all task except idleTsk*/
    defaultTskPara.schedPolicy = SCHED_PRIO;

    /* special for idleTsk*/
    _setTskPara(idleTsk, &defaultTskPara);
    idleTsk->para.schedPolicy = SCHED_IDLE;
}

struct scheduler scheduler_PRIO = {
    .type = SCHEDULER_PRIORITY,
    .nextTsk_func = nextPRIOTsk,
    .enqueueTsk_func = tskEnqueuePRIO,
    .dequeueTsk_func = tskDequeuePRIO,
    .schedulerInit_func = schedulerInit_PRIO,
    .createTsk_hook = NULL,
    .tick_hook = NULL};
