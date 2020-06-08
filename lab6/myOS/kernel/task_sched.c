#include "../include/tcb.h"
#include "../include/task_sched.h"
#include "../include/irq.h"

extern myTCB * currentTsk;

unsigned int defaultSlice = 10; 
unsigned int defaultRtSlice = 50; 
/*RR    */ extern struct scheduler scheduler_RR;
/*FCFS  */ extern struct scheduler scheduler_FCFS;
/*SJF   */ extern struct scheduler scheduler_SJF;
/*PRIO0 */ extern struct scheduler scheduler_PRIO0;
/*PRIO  */ extern struct scheduler scheduler_PRIO;
/*MQ    */ extern struct scheduler scheduler_MQ;
/*FMQ   */ extern struct scheduler scheduler_FMQ;

//这里列举了常见的所有的调度算法 本实验只要求实现两个即可（不包含FCFS）

extern void context_switch(myTCB *prevTsk, myTCB *nextTsk);

struct scheduler *sysScheduler = &scheduler_FCFS;  // default

unsigned int getSysScheduler(void){
    return sysScheduler->type;
}

void setSysScheduler(unsigned int what){    
    ////本函数需要实现！！！
    //设置*sysScheduler使用最上面列举的哪种调度器

}

//由于RR涉及到设置时间片大小 所以需要如下的两个函数getSysSchedulerPara setSysSchedulerPara
//其他调度器则不需要
void getSysSchedulerPara(unsigned int who, unsigned int *para){
    switch (who){
        case SCHED_RR_SLICE: *para = defaultSlice; break;
        case SCHED_RT_RR_SLICE: *para = defaultRtSlice; break;
        default :;
    }

}

void setSysSchedulerPara(unsigned int who, unsigned int para){
//本函数需要实现！！！
//和上面的get函数是对应的，设置两个参数
}

//每一个调度器中集成了几个函数 参考./task_sched/task_fifo.c中的scheduler scheduler_FCFS的结构
//实现以下的nextTsk enqueueTsk dequeueTsk schedulerInit scheduler_tick
myTCB *nextTsk(void){ 
    
}

void enqueueTsk(myTCB *tsk){

}

void dequeueTsk(myTCB *tsk){

}

void createTsk_hook(myTCB *created){
    if(sysScheduler->createTsk_hook)
        sysScheduler->createTsk_hook(created);
}

extern void scheduler_hook_main(void);

void schedulerInit(void){
   //注意除了调用调度器中的函数 还需要设置一下SysScheduler的调度算法使用哪个
}

void scheduler_tick(void){

}

void schedule(void){
	static int idle_times=0;
	myTCB * prevTsk;

    disable_interrupt();

	//此处实现调度功能！！
    //调度不可被中断
    //可参考实验五的scheduleFCFS的实现

    enable_interrupt();
}