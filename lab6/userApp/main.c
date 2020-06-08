#include "../myOS/userInterface.h"   //interface from kernel

#include "shell.h"
#include "memTestCase.h"

void wallClock_hook_main(void){
	int _h, _m, _s;
	char hhmmss[]="hh:mm:ss\0\0\0\0";

	getWallClock(&_h,&_m,&_s);
	sprintf(hhmmss,"%02d:%02d:%02d",_h,_m,_s);
	put_chars(hhmmss,0x7E,24,72);
}

// should be named as scheduler_hook_main
// Be executed very early
void scheduler_hook_main(void){
//prior settings
	setSysScheduler(SCHEDULER_FCFS);
//改变上面的参数来设置使用哪个调度算法
}

void doSomeTestBefore(void){		
	setWallClock(18,59,59);		//set time 18:59:59
    setWallClockHook(&wallClock_hook_main);	
}

void myTSK0(void){
	int j=1;	
	while(j<=10){		
		myPrintf(0x7,"myTSK0::%d    \n",j);
		busy_n_ms(120);
		j++;
	}	
	tskEnd();   //the task is end
}

void myTSK1(void){
	int j=1;	
	while(j<=10){
		myPrintf(0x7,"myTSK1::%d    \n",j);		
		busy_n_ms(120);
		j++;
	}	
	tskEnd();   //the task is end
}

void myTSK2(void){
	int j=1;	
	while(j<=10){
		myPrintf(0x7,"myTSK2::%d    \n",j);		
		busy_n_ms(120);
		j++;
	}	
	tskEnd();   //the task is end
}

void testSchedulerFCFS(void){  //FCFS or RR or SJF or PRIORITY0
	tskPara tskParas[4];
	int i;

	if(getSysScheduler()!=SCHEDULER_FCFS) {
		myPrintf(0x3,"NEED scheduler: SCHEDULER_FCFS!!!!!!STOPED!!!!!!!!");
		return;
	}
	//确认调度算法 如果不使用的FCFS 需要改变if条件
	for(i=0;i<4;i++) initTskPara(&tskParas[i]);
	//创建task 并且根据调度算法 设置task的参数 比如FCFS需要设置到达时间

	setTskPara(ARRTIME,50,&tskParas[0]);
	createTsk(myTSK0,&tskParas[0]);

	setTskPara(ARRTIME,100,&tskParas[1]);
	createTsk(myTSK1,&tskParas[1]);

	setTskPara(ARRTIME,0,&tskParas[2]);
	createTsk(myTSK2,&tskParas[2]);

	initShell();
    memTestCaseInit();
	setTskPara(ARRTIME,120,&tskParas[3]);
	createTsk(startShell,&tskParas[3]);  //    startShell();
}

void myMain(void){    //main is our init task
    clear_screen();

    doSomeTestBefore();

	myPrintf(0x7,"********INIT START\n\n");	
	testSchedulerFCFS();	
 	myPrintf(0x7,"********INIT END\n\n");	

    tskEnd();  // init end	
}