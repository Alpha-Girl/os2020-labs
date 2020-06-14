extern void oneTickUpdateWallClock(void);       //TODO: to be generalized

#include "../include/watchdog.h"
#include "../include/task_sched.h"  // for scheduler_tick
#include "../include/task_arr.h"	// for tick_hook_arr

//#ifndef __TICK_HOOK__
//#define __TICK_HOOK__
void (*tick_hook)(void) = 0; //{};
//#endif

int tick_number = 0;
int getTick(void){ return tick_number; }

void tick(void){
	int temp_col, temp_row;	
	tick_number++;	
	//myPrintk(0x4,"tick::%d\n",tick_number);
	tick_hook_arr(); 
	oneTickUpdateWallClock();

	// call hooks 
	//scheduler_tick();  // RR
	 // arriving	

	if(watchdogTimer_func) watchdogTimer_func(); 

	if(tick_hook) tick_hook();  //user defined   
}

//n second
void busy_n_second(int n){
	int second = 0x3000000;// 1秒内大约多少条乘法指令 毛估估
	int a=21,b=31,c;
	for(int i=0;i<n;i++)
		for(int j=0;j<second;j++) c=a*b;  //about 1sec
}

//n ms
void busy_n_ms(int n){
	int second = 0x8000;// 1秒内大约多少条乘法指令 毛估估
	int a=21,b=31,c;
	for(int i=0;i<n;i++)
		for(int j=0;j<second;j++) c=a*b;  //about 1m
}
