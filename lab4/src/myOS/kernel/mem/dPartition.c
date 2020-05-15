#include "../../include/myPrintk.h"
#include "../../include/mem.h"

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
	//内存初始化
	struct dPartition *pdp = (struct dPartition *)start;
	pdp->size = totalSize - sizeof(struct dPartition);
	pdp->firstFreeStart = start + sizeof(struct dPartition);
	struct EMB *pemb = (struct EMB *)(pdp->firstFreeStart);
	pemb->size = sizeof(struct EMB);
	pemb->nextStart = start + totalSize;
	return start;
}

void dPartitionWalkByAddr(unsigned long dp)
{
	//打印dP
	showdPartition((struct dPartition *)dp);
	struct EMB *pemb = (struct EMB *)(((struct dPartition *)dp)->firstFreeStart);
	//打印EMB
	while (pemb != 0)
	{
		showEMB(pemb);
		pemb = (struct EMB *)pemb->nextStart;
	}
}

//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
**/
unsigned long dPartitionAllocFirstFit(unsigned long dp, unsigned long size)
{
	//判断
	if (size > pMemSize)
		return 0;
	//对齐
	if(size%4)
	size = ((1+(size >> 2)) << 2);
	struct EMB *pemb = (struct EMB *)(((struct dPartition *)dp)->firstFreeStart);
	while (pemb != 0)
	{
		if (pemb->size + size <= pemb->nextStart - (unsigned long)pemb)
		{
			//大小满足，分配
			pemb->size += size;
			if (pemb->size + sizeof(struct EMB) <= pemb->nextStart - (unsigned long)pemb)
			{
				struct EMB *pemb1 = (struct EMB *)((unsigned long)pemb + pemb->size + sizeof(struct EMB));
				pemb1->nextStart = pemb->nextStart;
				pemb->nextStart = (unsigned long)pemb1;
				pemb1->size = sizeof(struct EMB);
			}
			return (unsigned long)pemb + sizeof(struct EMB);
		}
		pemb = (struct EMB *)pemb->nextStart;
	}
	return 0;
}

/*
 *r
 */
unsigned long dPartitionFreeFirstFit(unsigned long dp, unsigned long start)
{
	struct dPartition *pdp = (struct dPartition *)dp;
	//判断
	if (start > dp + pdp->size)
		return 0;
	struct EMB *pemb = (struct EMB *)(pdp->firstFreeStart);
	struct EMB *pemb1 = 0;
	while (pemb != 0 && (unsigned long)pemb + pemb->size < start)
	{
		pemb1 = pemb;
		pemb = (struct EMB *)(pemb->nextStart);
	}
	//释放
	if (pemb != 0)
	{
		pemb->size = start - (unsigned long)pemb;
		if (pemb->size == sizeof(struct EMB))
		{
			pemb1->size += pemb->nextStart - pemb1->nextStart;
			pemb1->nextStart = pemb->nextStart;
		}
	}
	return 1;
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
