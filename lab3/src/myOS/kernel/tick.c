int n_tick = 0;
void maybeUpdateWallClock(void);
extern int myPrintk(int color,const char *format, ...);
void tick(void)
{
	n_tick++;
	if(n_tick == 100){
		n_tick = 0;
		//myPrintk(0x2,"tick");
		maybeUpdateWallClock();
	}
}
