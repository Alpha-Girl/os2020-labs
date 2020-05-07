#include "../../include/myPrintk.h"
#include "../../include/mem.h"
unsigned long pMemStart;//可用的内存的起始地址
unsigned long pMemSize;//可用的大小

void memTest(unsigned long start, unsigned long grainSize){
	/*本函数需要实现！！！*/
	/*
	这一个函数对应实验讲解ppt中的第一大功能-内存检测。
	本函数的功能是检测从某一个地址开始的内存是否可用，具体算法就可以用ppt上说的写了读看是否一致。
	注意点两个：
	1、开始的地址要大于1M，需要做一个if判断。
	2、grainsize不能太小，也要做一个if判断
	*/

	//最后，输出可用的内存的起始地只和大小，别忘记赋值给上面的全局变量
	myPrintk(0x7,"MemStart: %x  \n",？？？？);
	myPrintk(0x7,"MemSize:  %x  \n",？？？？？);
}

extern unsigned long _end;
void pMemInit(void){
	unsigned long _end_addr = (unsigned long) &_end;
	memTest(0x100000,0x1000);
	myPrintk(0x7,"_end:  %x  \n", _end_addr);
	if (pMemStart <= _end_addr) {
		pMemSize -= _end_addr - pMemStart;
		pMemStart = _end_addr;
	}

	pMemHandler = dPartitionInit(pMemStart,pMemSize);	
}
