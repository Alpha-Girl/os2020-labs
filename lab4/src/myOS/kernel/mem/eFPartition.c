#include "../../include/myPrintk.h"
// 一个EEB表示一个空闲可用的Block
struct EEB
{
	unsigned long next_start;
};

void showEEB(struct EEB *eeb)
{
	myPrintk(0x7, "EEB(start=0x%x, next=0x%x)\n", eeb, eeb->next_start);
}

//eFPartition是表示整个内存的数据结构
struct eFPartition
{
	unsigned long totalN;
	unsigned long perSize; //unit: byte
	unsigned long firstFree;
};

void showeFPartition(struct eFPartition *efp)
{
	myPrintk(0x5, "eFPartition(start=0x%x, totalN=0x%x, perSize=0x%x, firstFree=0x%x)\n", efp, efp->totalN, efp->perSize, efp->firstFree);
}

void eFPartitionWalkByAddr(unsigned long efpHandler)
{
	struct eFPartition *peFP = (struct eFPartition *)efpHandler;
	showeFPartition(peFP);
	struct EEB *pEEB = (struct EEB *)(peFP->firstFree);
	while (pEEB != 0)
	{
		showEEB(pEEB);
		pEEB = (struct EEB *)(pEEB->next_start);
	}
}

unsigned long eFPartitionTotalSize(unsigned long perSize, unsigned long n)
{
	if (perSize % 32)
		perSize = (perSize >> 5 + 1) << 5;
	return (perSize * n + sizeof(struct eFPartition));
}

unsigned long eFPartitionInit(unsigned long start, unsigned long perSize, unsigned long n)
{
	struct eFPartition *peFP = (struct eFPartition *)start;
	peFP->totalN = n;
	//对齐
	if (perSize % 32)
		perSize = (perSize >> 5 + 1) << 5;
	peFP->perSize = perSize;
	unsigned long n_posi = start + sizeof(struct eFPartition);
	peFP->firstFree = n_posi;
	struct EEB *pEEB = (struct EEB *)n_posi;
	//连接成链
	for (int i = 0; i < n - 1; i++)
	{
		pEEB->next_start = n_posi + perSize;
		pEEB = (struct EEB *)(pEEB->next_start);
	}
	pEEB->next_start = 0;
	return 1;
}

unsigned long eFPartitionAlloc(unsigned long EFPHandler)
{
	struct eFPartition *peFP = (struct eFPartition *)EFPHandler;
	unsigned long save = peFP->firstFree;
	struct EEB *pEEB = (struct EEB *)save;
	peFP->firstFree = pEEB->next_start;
	return save;
}

unsigned long eFPartitionFree(unsigned long EFPHandler, unsigned long mbStart)
{
	struct eFPartition *peFP = (struct eFPartition *)EFPHandler;
	unsigned long point = (EFPHandler + sizeof(struct eFPartition));
	struct EEB *pEEB = (struct EEB *)point;
	while (point <= mbStart)
	{
		pEEB->next_start = peFP->firstFree;
		peFP->firstFree = point;
		point = point + peFP->perSize;
	}
	return 1;
}
