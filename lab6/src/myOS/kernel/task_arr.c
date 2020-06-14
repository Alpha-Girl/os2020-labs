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
    //本函数需要实现！！！
    //根据tsk新建一个节点 按照arrTime小到大的顺序插入到链表的对应位置
    //同时arrPool也要有tsk
    arrNode *p, *tmp;
    p = tcb2Arr(tsk);
    p->theTCB = tsk;
    p->arrTime = tsk->para.arrTime;
    tmp = (arrNode *)dLinkListFirstNode(&arrList);
    if (dLinkListIsEmpty(&arrList))
        dLinkInsertBefore(&arrList, &(tmp->theNode), &(p->theNode));
    else
    {
        while (tmp->theNode.next != &arrList)
        {
            if (tmp->arrTime > p->arrTime)
                break;
            tmp = (arrNode *)(tmp->theNode.next);
        }
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
    { //myPrintk(0x2,"empty\n");
        return;
    }
    else
    {
        arrNode *tmp = (arrNode *)dLinkListFirstNode(&arrList);
        //myPrintk(0x2,"%d %d\n",tmp->arrTime,getTick());
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