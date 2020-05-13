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
	pdP->size = totalSize + sizeof(struct dPartition) + sizeof(struct EMB);
	pdP->firstFreeStart = start + sizeof(struct dPartition) + sizeof(struct EMB);
	struct EMB *pEMB = (struct EMB *)(start + sizeof(struct dPartition));
	pEMB->size = totalSize;
	pEMB->nextStart = start + pdP->size;
	return start;
}

void dPartitionWalkByAddr(unsigned long dp)
{
	//本函数需要实现！！！
	/*本函数遍历输出EMB 方便调试
	先打印dP的信息，可调用上面的showdPartition。
	然后按地址的大小遍历EMB，对于每一个EMB，可以调用上面的showEMB输出其信息
	*/
}

//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
**/
unsigned long dPartitionAllocFirstFit(unsigned long dp, unsigned long size)
{
	//本函数需要实现！！！
	/*
	使用firstfit的算法分配空间，当然也可以使用其他fit，不限制。
	最后，成功分配返回首地址，不成功返回0
	注意的地方：
	1、和eFPartition一样，要注意实际分配的block的大小和传入的参数size是不一样的。要注意字节对齐的问题，还有它最小值不是0，因为EMB数据结构有大小。在比较所需要的大小和block的size时候，也用的是实际分配需要的大小而非传入的参数size。
	2、分配就好像是链表的一个块分裂成两个，注意边界情况。
	*/
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
