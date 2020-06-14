/* ref: https://elixir.bootlin.com/linux/v3.8/source/drivers/watchdog/ib700wdt.c*/
#include "watchdog.h"

#define TimeSec0_L1     0x0F
#define TimeSec2_L2     0x0E
#define TimeSec4_L3     0x0D
#define TimeSec6_L4     0x0C
#define TimeSec8_L5     0x0B
#define TimeSec10_L6    0x0A
#define TimeSec12_L7    0x09
#define TimeSec14_L8    0x08
#define TimeSec16_L9    0x07
#define TimeSec18_L10   0x06
#define TimeSec20_L11   0x05
#define TimeSec22_L12   0x04
#define TimeSec24_L13   0x03
#define TimeSec26_L14   0x02
#define TimeSec28_L15   0x01
#define TimeSec30_L16   0x00

void outb (unsigned short int port_to, unsigned char value);

void enable_watchdog(void){
    outb(0x443,TimeSec0_L1);  //write a value to port 0x441, the value is related to the interval of timer
}

void disable_watchdog(void){
    outb(0x441,0);  //write any value to port 0x441
}

unsigned int watchdogTimer;  //ticks
void watchdog_tick_hook(void){
    if (--watchdogTimer==0) enable_watchdog(); 
}

void initWatchDogTimer(void){
    watchdogTimer_func=(void*)0;
}
void setWatchDogTimer(void){
    watchdogTimer=50;
    watchdogTimer_func=watchdog_tick_hook;
}