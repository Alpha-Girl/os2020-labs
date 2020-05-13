#include "../../include/myPrintk.h"
#include "../../include/mem.h"
unsigned long pMemStart; //可用的内存的起始地址
unsigned long pMemSize;	 //可用的大小

void memTest(unsigned long start, unsigned long grainSize)
{
	unsigned short *p, save;
	unsigned long max_addr;
	//对开始的地址 和 grainSize 做判断
	if (start < (1 << 20))
		start = 1 << 20;
	if (grainSize < (1 << 10))
		grainSize = 1 << 10;
	p = (unsigned short *)start;
	while (1)
	{
		//对grain的前两个字节进行读写
		save = *p;
		*p = 0xaa55;
		if (*p != 0xaa55)
			break;
		*p = 0x55aa;
		if (*p != 0x55aa)
			break;
		*p = save;

		p = (unsigned short *)(p + grainSize - sizeof(unsigned short));
		//对grain的后两个字节进行读写
		save = *p;
		*p = 0xaa55;
		if (*p != 0xaa55)
			break;
		*p = 0x55aa;
		if (*p != 0x55aa)
			break;
		*p = save;

		p = (unsigned short *)(p + sizeof(unsigned short));
		max_addr = (unsigned long)p;
	}
	//输出可用的内存的起始地址和大小，赋值给全局变量
	pMemStart = start;
	pMemSize = max_addr - pMemStart;
	myPrintk(0x7, "MemStart: %x  \n", pMemStart);
	myPrintk(0x7, "MemSize:  %x  \n", pMemSize);
}

extern unsigned long _end;
void pMemInit(void)
{
	unsigned long _end_addr = (unsigned long)&_end;
	memTest(0x100000, 0x1000);
	myPrintk(0x7, "_end:  %x  \n", _end_addr);
	if (pMemStart <= _end_addr)
	{
		pMemSize -= _end_addr - pMemStart;
		pMemStart = _end_addr;
	}

	pMemHandler = dPartitionInit(pMemStart, pMemSize);
}
