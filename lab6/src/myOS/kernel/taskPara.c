#include "../include/tcb.h"
#include "../include/taskPara.h"
#include "../include/task_sched.h"

extern void initLeftExeTime_sjf(myTCB *tsk);

// may modified during scheduler_init
tskPara defaultTskPara = {
    .priority = MAX_PRIORITY_NUM,
    .exeTime = MAX_EXETIME,
    .arrTime = 0,
    .schedPolicy = SCHED_UNDEF}; //task设计调度的一些参数的默认值

void _setTskPara(myTCB *task, tskPara *para)
{
    if(para==NULL){
        initTskPara(&(task->para));
        task->para.schedPolicy=SCHEDULER_FCFS;
    }
    else
    {
        task->para.arrTime=para->arrTime;
        task->para.exeTime=para->exeTime;
        task->para.priority=para->priority;
        switch (getSysScheduler())
        {
        case SCHEDULER_FCFS:
            task->para.schedPolicy=SCHED_FCFS;
            break;
        case SCHEDULER_SJF:
            task->para.schedPolicy=SCHED_SJF;
            break;
        case SCHEDULER_PRIORITY0:
        case SCHEDULER_PRIORITY:
            task->para.schedPolicy=SCHED_PRIO;
            break;
        case SCHEDULER_RR:
            task->para.schedPolicy=SCHED_RR;
            break;
        case SCHEDULER_MQ:
            task->para.schedPolicy=SCHED_RT_FCFS;
            break;
        case SCHEDULER_FMQ:
            task->para.schedPolicy=SCHED_RT_RR;
            break;
        default:
            task->para.schedPolicy=SCHED_FCFS;
            break;
        }
    }
    
    //本函数需要实现！！！
    //将para的中的参数值赋值给task的对应参数
    //注意para为null的处理
    //注意task_sched.h中schedule policy和scheme的定义有区别 所以para中的schedPolicy不能直接赋值给task
}

void initTskPara(tskPara *buffer)
{
    //功能是将任务buffer的参数设置为默认值
    buffer->priority = defaultTskPara.priority;
    buffer->exeTime = defaultTskPara.exeTime;
    buffer->arrTime = defaultTskPara.arrTime;
    buffer->schedPolicy = defaultTskPara.schedPolicy; 
}

void setTskPara(unsigned int option, unsigned int value, tskPara *buffer)
{
    //设置task的设计调度的四个参数
    //option控制buffer的哪个参数要被赋值，value是具体的数值
    switch (option)
    {
    case PRIORITY:
        buffer->priority=value;
        break;
    case EXETIME:
        buffer->exeTime=value;
        break;
    case ARRTIME:
        buffer->arrTime=value;
        break;
    case SCHED_POLICY:
        buffer->schedPolicy=value;
        break;
    default:
        break;
    }
}

void getTskPara(unsigned option, unsigned int *para)
{
    //查看task的设计调度的四个参数
    //option控制buffer的哪个参数要查看 赋值给para
    switch (option)
    {
    case PRIORITY:
        *para=currentTsk->para.priority;
        break;
    case ARRTIME:
        *para=currentTsk->para.arrTime;
        break;
    case EXETIME:
        *para=currentTsk->para.exeTime;
        break;
    case SCHED_POLICY:
        *para=currentTsk->para.schedPolicy;
        break;
    default:
        break;
    }
}
