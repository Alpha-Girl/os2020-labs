#include "../../include/myPrintk.h"

//dPartition 是整个动态分区内存的数据结构
struct dPartition
{
	unsigned long size;
	unsigned long firstFreeStart;
};

void showdPartition(struct dPartition *dp)
{
	myPrintk(0x5, "dPartition(start=0x%x, size=0x%x, firstFreeStart=0x%x)\n", dp, dp->size, dp->firstFreeStart);
}

// EMB每一个block的数据结构，userdata可以暂时不用管。
struct EMB
{
	unsigned long size;
	union {
		unsigned long nextStart; // if free: pointer to next block
		unsigned long userData;	 // if allocated, blongs to user
	};
};

void showEMB(struct EMB *emb)
{
	myPrintk(0x3, "EMB(start=0x%x, size=0x%x, nextStart=0x%x)\n", emb, emb->size, emb->nextStart);
}

unsigned long dPartitionInit(unsigned long start, unsigned long totalSize)
{
	//totalsize大小判断
	if (totalSize < (sizeof(struct dPartition) + sizeof(struct EMB)))
		return 0;
	struct dPartition *pdP = (struct dPartition *)start;
	pdP->size = totalSize - sizeof(struct dPartition);
	pdP->firstFreeStart = start + sizeof(struct dPartition);
	struct EMB *pEMB = (struct EMB *)(pdP->firstFreeStart);
	pEMB->size = totalSize - sizeof(struct dPartition) - sizeof(struct EMB);
	pEMB->nextStart = NULL;
	return start;
}

void dPartitionWalkByAddr(unsigned long dp)
{
	//打印dP的信息
	showdPartition((struct dPartition *)dp);
	struct EMB *pEMB = (struct EMB *)(((struct dPartition *)dp)->firstFreeStart);
	while (pEMB != 0)
	{
		//打印EMB的信息
		showEMB(pEMB);
		pEMB = (struct EMB *)(pEMB->nextStart);
	}
}

//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
**/
unsigned long dPartitionAllocFirstFit(unsigned long dp, unsigned long size)
{
	//大小判断
	if (size < sizeof(struct EMB))
		size = sizeof(struct EMB);
	//32字节对齐
	if (size % 32)
		size = ((size >> 5) + 1) << 5;
	struct EMB *pEMB = (struct EMB *)(((struct dPartition *)dp)->firstFreeStart);
	while (pEMB != 0)
	{
		//判断大小是否满足
		if (pEMB->size > (size + sizeof(struct EMB)))
		{
			//分配
			struct EMB *n_pEMB = (struct EMB *)((unsigned long)pEMB + size + sizeof(struct EMB));
			n_pEMB->size = pEMB->size - size - 2 * sizeof(struct EMB);
			n_pEMB->nextStart = pEMB->nextStart;
			pEMB->nextStart = (unsigned long)n_pEMB;
			pEMB->size = size;
			return (unsigned long)pEMB + sizeof(struct EMB);
		}
		//寻找下一空闲块
		pEMB = (struct EMB *)pEMB->nextStart;
	}
	//分配失败
	return 0;
}

/*
 *r
 */
unsigned long dPartitionFreeFirstFit(unsigned long dp, unsigned long start)
{
	//本函数需要实现！！！
	/*按照对应的fit的算法释放空间
	注意检查要释放的start~end这个范围是否在dp有效分配范围内
	返回1 没问题
	返回0 error
	*/
}

//wrap: we select firstFit, you can select another one
//user need not know this
unsigned long dPartitionAlloc(unsigned long dp, unsigned long size)
{
	return dPartitionAllocFirstFit(dp, size);
}

unsigned long dPartitionFree(unsigned long dp, unsigned long start)
{
	return dPartitionFreeFirstFit(dp, start);
}
