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

typedef struct arrivingNode{
    /* node should be here*/
    dLink_node theNode;

    /* node body */
    unsigned int arrTime; //ralative to arrTimeBase
    myTCB* theTCB;
}arrNode;
arrNode arrPool[TASK_NUM];
arrNode * tcb2Arr(myTCB* tsk){
    return &arrPool[tsk->tcbIndex];
}

dLinkedList arrList;

void initArrList(void){
    dLinkListInit(&arrList);
}

/* arrTime: small --> big */
void ArrListEnqueue(myTCB* tsk){    
    //本函数需要实现！！！
    //根据tsk新建一个节点 按照arrTime小到大的顺序插入到链表的对应位置
    //同时arrPool也要有tsk

}

void tskStartDelayed(myTCB* tsk){
    //disable_interrupt();
    ArrListEnqueue(tsk);
    //enable_interrupt();
}

void tick_hook_arr(void){
    if (dLinkListIsEmpty(&arrList)) return;
    else {
        arrNode *tmp = (arrNode*)dLinkListFirstNode(&arrList);
        while(tmp->arrTime + arrTimeBase <= getTick() ){
            dLinkDeleteFifo(&arrList);

            tskStart(tmp->theTCB);

            if (dLinkListIsEmpty(&arrList)) break;
            tmp = (arrNode*)dLinkListFirstNode(&arrList);
        }
    }         
}