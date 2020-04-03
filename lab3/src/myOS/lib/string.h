#ifndef __STRING_H__
#define __STRING_H__

// string.c

#include "../printk/types.h"

// 获取字符串长度
size_t strlen(const char *str);
// 如果 src > dest, 则返回值大于 0，如果 src = dest, 则返回值等于 0，
// 如果 srd  < dest ,则返回值小于 0。
int8_t strcmp(const char *src, const char *dest);
char *strcpy(char *dest, const char *src);
void backspace(char *src);
void append(char *src, char dest);
char *strcat(char *dest, const char *src);
void memcpy(void *dest, void *src, uint32_t len);
void memset(void *dest, uint8_t val, uint32_t len);
void bzero(void *dest, uint32_t len);

#endif