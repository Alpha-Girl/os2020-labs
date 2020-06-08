#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__
void initWatchDogTimer(void);
void setWatchDogTimer(void);
void (*watchdogTimer_func)(void);
#endif