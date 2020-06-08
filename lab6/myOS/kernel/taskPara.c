#include "../include/tcb.h"
#include "../include/taskPara.h"
#include "../include/task_sched.h"

extern void initLeftExeTime_sjf(myTCB* tsk);

// may modified during scheduler_init
tskPara defaultTskPara = {
    .priority = MAX_PRIORITY_NUM,
    .exeTime = MAX_EXETIME,
    .arrTime = 0,
    .schedPolicy = SCHED_UNDEF
}; //task设计调度的一些参数的默认值

void _setTskPara(myTCB *task, tskPara *para){

    //本函数需要实现！！！
    //将para的中的参数值赋值给task的对应参数
    //注意para为null的处理
    //注意task_sched.h中schedule policy和scheme的定义有区别 所以para中的schedPolicy不能直接赋值给task
}

void initTskPara(tskPara *buffer){
    //本函数需要实现！！！
    //功能是将任务buffer的参数设置为默认值
}

void setTskPara(unsigned int option, unsigned int value, tskPara *buffer){
    //本函数需要实现！！！
    //设置task的设计调度的四个参数
    //option控制buffer的哪个参数要被赋值，value是具体的数值

}

void getTskPara(unsigned option, unsigned int *para){
    //本函数需要实现！！！
    //查看task的设计调度的四个参数
    //option控制buffer的哪个参数要查看 赋值给para

}
