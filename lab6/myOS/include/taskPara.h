#ifndef __TASK_PATA_H__
#define __TASK_PATA_H__

struct myTCB;
typedef struct myTCB myTCB;

//option for setTskPara()/getTskPara
#define PRIORITY	 1
#define EXETIME		 2
#define ARRTIME		 3
#define SCHED_POLICY 4

#define UNDEF_PRIORITY 0xFFFFFFFF
#define MAX_EXETIME	0xFFFFFFFF

#ifdef MAX_USER_PRIORITY_NUM
// idle = MAX_USER_PRIORITY_NUM+1
#define MAX_PRIORITY_NUM MAX_USER_PRIORITY_NUM+1
#else
#define MAX_PRIORITY_NUM UNDEF_PRIORITY
#endif

// struct for tskPara
typedef struct tskPara{
	unsigned int priority;
	unsigned int exeTime;
	unsigned int arrTime;
	unsigned int schedPolicy;
} tskPara;

extern tskPara defaultTskPara;
tskPara initTsk_para;

void _setTskPara(myTCB *task, tskPara *para);

/*task schedule policy*/
#define SCHED_UNDEF   0x0000
#define SCHED_FCFS    0x0010
#define SCHED_SJF     0x0020
#define SCHED_PRIO    0x0030
#define SCHED_RR      0x0040
#define SCHED_RT_FCFS 0x0050
#define SCHED_RT_RR   0x0060
#define SCHED_IDLE    0x0070
void initTskPara(tskPara *buffer);
void setTskPara(unsigned int option, unsigned int value, tskPara *buffer);
void getTskPara(unsigned option, unsigned int *para);
#endif