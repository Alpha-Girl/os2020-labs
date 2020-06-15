#include "../include/dLinkList.h"
#include "../include/tcb.h"

/*

本框架中的task使用双向链表链接起来，链表的定义及操作可参考./lib/dLinkList.c
task按照arrTime从小到大排列
*/

/* for task arriving */
typedef struct myTCB myTCB;
extern void tskStart(myTCB *tsk);

extern int getTick(void);

/* time unit: tick */
/* zero arriving time: x ticks*/
unsigned int arrTimeBase = 0x0;

typedef struct arrivingNode
{
    /* node should be here*/
    dLink_node theNode;

    /* node body */
    unsigned int arrTime; //ralative to arrTimeBase
    myTCB *theTCB;
} arrNode;
arrNode arrPool[TASK_NUM];
arrNode *tcb2Arr(myTCB *tsk)
{
    return &arrPool[tsk->tcbIndex];
}

dLinkedList arrList;

void initArrList(void)
{
    dLinkListInit(&arrList);
}

/* arrTime: small --> big */
void ArrListEnqueue(myTCB *tsk)
{

    arrNode *p, *tmp;
    p = tcb2Arr(tsk);
    p->theTCB = tsk;
    p->arrTime = tsk->para.arrTime;
    tmp = (arrNode *)dLinkListFirstNode(&arrList);
    if (dLinkListIsEmpty(&arrList))
        //队列为空的情形
        dLinkInsertBefore(&arrList, &(tmp->theNode), &(p->theNode));
    else
    {
        //队列不空时，先找到应插入的位置
        while (tmp->theNode.next != &arrList)
        {
            if (tmp->arrTime > p->arrTime)
                break;
            tmp = (arrNode *)(tmp->theNode.next);
        }
        //根据arrtime判断插在查询结束时的节点前/后
        if (tmp->arrTime <= p->arrTime)
            //当arrtime相同且策略为PRIO时，插入顺序还与priority有关
            if (tmp->arrTime == p->arrTime && p->theTCB->para.schedPolicy == SCHED_PRIO)
            {
                while (tmp->theTCB->para.priority > p->theTCB->para.priority && tmp->arrTime == p->arrTime)
                    tmp = (arrNode *)(tmp->theNode.prev);
                dLinkInsertAfter(&arrList, &(tmp->theNode), &(p->theNode));
            }
            else
                dLinkInsertAfter(&arrList, &(tmp->theNode), &(p->theNode));
        else
            dLinkInsertBefore(&arrList, &(tmp->theNode), &(p->theNode));
    }
}

void tskStartDelayed(myTCB *tsk)
{
    ArrListEnqueue(tsk);
}

void tick_hook_arr(void)
{
    if (dLinkListIsEmpty(&arrList))
        return;
    else
    {
        arrNode *tmp = (arrNode *)dLinkListFirstNode(&arrList);
        while (tmp->arrTime + arrTimeBase <= getTick())
        {
            dLinkDeleteFifo(&arrList);
            tskStart(tmp->theTCB);
            if (dLinkListIsEmpty(&arrList))
                break;
            tmp = (arrNode *)dLinkListFirstNode(&arrList);
        }
    }
}