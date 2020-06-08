#ifndef __BITMAP_H__
#define __BITMAP_H__

/*without malloc, user should define the bitmap first*/
/* how many characters for a bitmap with size equal to nBits bits?*/
#define nBits2NChar(nbits) (((unsigned int)nbits + 7) / 8)

void initBitMap(unsigned char *bitmap, unsigned int nbits);
void setBitMap(unsigned char *bitmap, unsigned int theBitIndex, unsigned int nbits);
void clearBitMap(unsigned char *bitmap, unsigned int theBitIndex, unsigned int nbits);
unsigned int first1BitIndex(unsigned char *bitmap, unsigned int nbits);
#endif