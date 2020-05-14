#include "../../include/mem.h"

unsigned long malloc(unsigned long size)
{
    dPartitionAlloc(pMemStart, size);
}

unsigned long free(unsigned long start)
{
    dPartitionFree(pMemStart, start);
}

unsigned long kmalloc(unsigned long size)
{
    dPartitionAlloc(pMemStart, size);
}

unsigned long kfree(unsigned long start)
{
    dPartitionFree(pMemStart, start);
}