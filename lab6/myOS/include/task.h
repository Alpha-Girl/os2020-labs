#ifndef __TASK_H__
#define __TASK_H__

#include "tcb.h"

#ifndef USER_TASK_NUM
#include "../../userApp/userApp.h"
#endif
#define TASK_NUM (2 + USER_TASK_NUM)   // at least: 0-idle, 1-init

#define initTskBody myMain
void initTskBody(void);

void CTX_SW(void*prev_stkTop, void*next_stkTop);

int createTsk(void (*tskBody)(void), tskPara *para);
void tskEnd(void);

void TaskManagerInit(void);
#endif