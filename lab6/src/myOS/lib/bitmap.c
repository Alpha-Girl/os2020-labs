
#include "../include/bitmap.h"

extern int myPrintf(int color,const char *format, ...);

void initBitMap(unsigned char *bitmap, unsigned int nbits) {
    unsigned int i;

    for (i=0; i< nBits2NChar(nbits); i++){
        bitmap[i] = (unsigned char)0x0;
    }
}

void setBitMap(unsigned char *bitmap, unsigned int theBitIndex, unsigned int nbits){
    if (theBitIndex >= nbits) return;       //do nothing

    bitmap[theBitIndex / 8] |= 0x01 << (theBitIndex % 8);
}

void clearBitMap(unsigned char *bitmap, unsigned int theBitIndex, unsigned int nbits){
    if (theBitIndex >= nbits) return;       //do nothing    

    bitmap[theBitIndex / 8] &= ~(0x01 << (theBitIndex % 8));
}

unsigned int first1BitIndex(unsigned char *bitmap, unsigned int nbits){
    unsigned int i,j;
    unsigned char temp;

    for (i=0; i<nBits2NChar(nbits); i++){
        if (bitmap[i] > (unsigned char)0x0)
            break;    
    }

    if (i==nBits2NChar(nbits)){
        myPrintf(0x3,"bitmap all zero!!!");
        while(1);
    }

    temp = bitmap[i];
    j = 0;
    while(temp){
        if (temp & (unsigned char)0x01) break;
        
        temp = temp >> 1;
        j++;
    }

    return (i<<3)+j;
}
