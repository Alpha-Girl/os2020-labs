#ifndef __TASK_H__
#define __TASK_H__

#ifndef USER_TASK_NUM
#include "../../userApp/userApp.h"
#endif

#define TASK_NUM (2 + USER_TASK_NUM)   // at least: 0-idle, 1-init

#define initTskBody myMain         // connect initTask with myMain

void initTskBody(void);

void CTX_SW(void*prev_stkTop, void*next_stkTop);

#error "TODO: 为 myTCB 增补合适的字段"
typedef struct myTCB {
     unsigned long *stkTop;     /* 栈顶指针 */
} myTCB;

myTCB tcbPool[TASK_NUM];

myTCB * idleTsk;                /* idle 任务 */
myTCB * currentTsk;             /* 当前任务 */
myTCB * firstFreeTsk;           /* 下一个空 TCB */

void TaskManagerInit(void);

#endif
