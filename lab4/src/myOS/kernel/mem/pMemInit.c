#include "../../include/myPrintk.h"
#include "../../include/mem.h"
unsigned long pMemStart; //可用的内存的起始地址
unsigned long pMemSize;	 //可用的大小

void memTest(unsigned long start, unsigned long grainsize)
{
	//大小判断
	start = start > (1 << 20) ? start : (1 << 20);
	grainsize = grainsize >= (1 << 10) ? grainsize : (1 << 10);
	pMemStart = start;
	pMemSize = 0;
	unsigned long position = start;
	unsigned short *pus = (unsigned short *)start;
	//内存检查
	while (1)
	{
		unsigned short save = *pus;
		*pus = 0xAA55;
		if (*pus != 0xAA55)
			break;
		*pus = 0x55AA;
		if (*pus != 0x55AA)
			break;
		*pus = save;

		pus = (unsigned short *)((unsigned long)pus + grainsize - sizeof(unsigned short));
		save = *pus;
		*pus = 0xAA55;
		if (*pus != 0xAA55)
			break;
		*pus = 0x55AA;
		if (*pus != 0x55AA)
			break;
		*pus = save;

		pus = (unsigned short *)((unsigned long)pus + sizeof(unsigned short));
		position = (unsigned long)pus;
	}
	pMemSize = position - pMemStart;
	//输出可用的内存的起始地址和大小
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
