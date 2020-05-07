#include "../../include/myPrintk.h"
#include "../../include/mem.h"
#include "../../include/io.h"
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
    int i;
    unsigned long addr;
    unsigned char save[4];
    addr=start;
    for(i=0;;i++){
        save[0]=inb(addr);
        save[1]=inb(addr+1);
        save[2]=inb(addr+grainSize-2);
        save[3]=inb(addr+grainSize-1);

        outb(addr,0xaa);
        outb(addr+1,0x55);
        if(inb(addr)!=0xaa)
            break;
        if(inb(addr+1)!=0x55)
            break;
        outb(addr,0x55);
        outb(addr+1,0xaa);
        if(inb(addr)!=0x55)
            break;
        if(inb(addr+1)!=0xaa)
            break;

        outb(addr+grainSize-2,0xaa);
        outb(addr+grainSize-1,0x55);
        if(inb(addr+grainSize-2)!=0xaa)
            break;
        if(inb(addr+grainSize-1)!=0x55)
            break;
        outb(addr+grainSize-2,0x55);
        outb(addr+grainSize-1,0xaa);
        if(inb(addr+grainSize-2)!=0x55)
            break;
        if(inb(addr+grainSize-1)!=0xaa)
            break;
        
        outb(addr,save[0]);
        outb(addr+1,save[1]);
        outb(addr+grainSize-2,save[2]);
        outb(addr+grainSize-1,save[3]);
        addr=addr+grainSize;
    }
	//最后，输出可用的内存的起始地只和大小，别忘记赋值给上面的全局变量
    pMemStart=start;
    pMemSize=addr-start;
	myPrintk(0x7,"MemStart: %x  \n",pMemStart);
	myPrintk(0x7,"MemSize:  %x  \n",pMemSize);
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
