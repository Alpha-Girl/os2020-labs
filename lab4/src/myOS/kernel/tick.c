int n_tick = 0;
extern void maybeUpdateWallClock(void);
extern int myPrintk(int color, const char *format, ...);
void tick(void)
{
	n_tick++;
	//计数至100表明，已过一秒，须刷新时间
	if (n_tick == 100)
	{
		n_tick = 0;
		maybeUpdateWallClock();
	}
}
