#ifndef __TASK_SCHED_H__
#define __TASK_SCHED_H__

#include "tcb.h"

/*scheduler scheme*/
#define SCHEDULER_FCFS		0
#define SCHEDULER_SJF		1
#define SCHEDULER_PRIORITY0	2
#define SCHEDULER_RR		3
#define SCHEDULER_PRIORITY	4
#define SCHEDULER_MQ		5
#define SCHEDULER_FMQ		6

/*task schedule policy*/
#define SCHED_UNDEF   0x0000
#define SCHED_FCFS    0x0010
#define SCHED_SJF     0x0020
#define SCHED_PRIO    0x0030
#define SCHED_RR      0x0040
#define SCHED_RT_FCFS 0x0050
#define SCHED_RT_RR   0x0060
#define SCHED_IDLE    0x0070

#define SCHED_RR_SLICE		0x1000
#define SCHED_RT_RR_SLICE	0x2000

extern unsigned int defaultSlice, defaultRtSlice;
struct scheduler {
    unsigned int type;  

    myTCB* (*nextTsk_func)(void);
    void (*enqueueTsk_func)(myTCB *tsk);
    void (*dequeueTsk_func)(myTCB *tsk);
    void (*schedulerInit_func)(void);    
    void (*createTsk_hook)(myTCB* created);  //if set, will be call in createTsk (before tskStart)
    void (*tick_hook)(void);  //if set, tick_hook will be called every tick
};

unsigned int getSysScheduler(void);
void setSysScheduler(unsigned int what);

void getSysSchedulerPara(unsigned int who, unsigned int *para);
void setSysSchedulerPara(unsigned int who, unsigned int para);

void setSchedulerHook(void (*func)(void));

/* wrapped interfaces */
myTCB *nextTsk(void);
void enqueueTsk(myTCB *tsk);
void dequeueTsk(myTCB *tsk);
void schedulerInit();
void createTsk_hook(myTCB *created);
void scheduler_tick(void);  // run every tick

void schedule(void);
#endif