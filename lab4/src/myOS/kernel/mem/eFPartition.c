#include "../../include/myPrintk.h"
// 一个EEB表示一个空闲可用的Block
struct EEB {
	unsigned long next_start;
};

void showEEB(struct EEB *eeb){
	myPrintk(0x7,"EEB(start=0x%x, next=0x%x)\n", eeb, eeb->next_start);
}

//eFPartition是表示整个内存的数据结构
struct eFPartition{
	unsigned long totalN;
	unsigned long perSize;  //unit: byte	
	unsigned long firstFree;
};

void showeFPartition(struct eFPartition *efp){
	myPrintk(0x5,"eFPartition(start=0x%x, totalN=0x%x, perSize=0x%x, firstFree=0x%x)\n", efp, efp->totalN, efp->perSize, efp->firstFree);
}

void eFPartitionWalkByAddr(unsigned long efpHandler){
	//本函数需要实现！！！
	/*本函数是为了方便查看和调试的。功能：1、打印eFPartiiton结构体的信息，可以调用上面的showeFPartition函数。2、遍历每一个EEB，打印出他们的地址以及下一个EEB的地址（可以调用上面的函数showEEB）

	*/

}


unsigned long eFPartitionTotalSize(unsigned long perSize, unsigned long n){
	//本函数需要实现！！！
	/*根据参数persize（每个大小）和n个数计算总大小，注意persize的对齐，例如persize是31字节，你想8字节对齐，那么计算大小实际代入的一个块的大小就是32字节。
	最后别忘记加上eFPartition这个数据结构的大小，因为它也占一定的空间

	*/
}

unsigned long eFPartitionInit(unsigned long start, unsigned long perSize, unsigned long n){
	//本函数需要实现！！！
	/*初始化内存
	第一步需要创建一个eFPartition结构体，需要注意的是结构体的persize不是直接传入的参数perSize，需要对齐。结构体的nextStart也是需要考虑一下结构体本身的大小。
	第二步就是对每一块的内存创建一个EEB，将他们连起来构成一个链。注意最后一块的EEB的nextstart应该是0
	*/
}


unsigned long eFPartitionAlloc(unsigned long EFPHandler){
	//本函数需要实现！！！
	/*本函数分配一个空闲块的内存并返回相应的地址，EFPHandler表示整个内存的首地址
	*/

}


unsigned long eFPartitionFree(unsigned long EFPHandler,unsigned long mbStart){
	//本函数需要实现！！！
	/*初始化内存
	free掉mbstart之前的内存，mbstart为第一个空闲块的地址。也要更新EBB组成的链表。
	*/
	return 1;
}
