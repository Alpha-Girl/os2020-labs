#ifndef __TCB_H__
#define __TCB_H__

#include "../../userApp/userApp.h"
#include "taskPara.h"
#include "dLinkList.h"
#define TSK_RUN 1
#define NULL (void*)0

#define STACK_SIZE	512  // 1024*4
typedef struct myTCB {
	/* node should be the 1st element*/
	struct dLink_node thisNode;

	/* node body */
	unsigned long state;  // 0:rdy
	int tcbIndex;
	struct myTCB * next;
	unsigned long* stkTop;
	unsigned long stack[STACK_SIZE]; 
	tskPara para; 	
	unsigned int leftSlice; // for SCHED_RR or SCHED_RT_RR policy
} myTCB;

#define TASK_NUM (2 + USER_TASK_NUM)   // at least: 0-idle, 1-init
myTCB tcbPool[TASK_NUM];

myTCB * idleTsk;
myTCB * currentTsk;

#endif