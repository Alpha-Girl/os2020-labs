int hh = 0, mm = 0, ss = 0, ms = 0;
#define MAX_NUM 20
typedef void (*funcs)(void);
extern int myPrintk(int color, const char *format, ...);
void WallClock_append(int h, int m, int s);

//初始时间设置
void setWallClock(int h, int m, int s)
{
	hh = h;
	mm = m;
	ss = s;
	//显示时间
	WallClock_append(hh, mm, ss);
}

//读取当前时间
void getWallClock(int *h, int *m, int *s)
{
	*h = hh;
	*m = mm;
	*s = ss;
}

int No_funcs_in_Hook = 0;  //当前hook函数数量
funcs func_array[MAX_NUM]; //hook函数指针数组
//设置WallClockHook
void setWallClockHook(void (*func)(void))
{
	if (No_funcs_in_Hook < MAX_NUM - 1) //hook函数指针数组未满
	{
		func_array[No_funcs_in_Hook] = func;
		No_funcs_in_Hook++;
		myPrintk(0x2, "SetWallClockHook succeed.\n");
	}
	else
	{
		myPrintk(0x2, "SetWallClockHook failed.\n");
	}
}

//更新时间（由tick调用）
void maybeUpdateWallClock(void)
{
	int i = 0;
	for (i = 0; i < No_funcs_in_Hook; i++) //调用hook函数指针数组中的函数
	{
		func_array[i]();
	}
	//设置刷新时间
	if (ss < 59)
	{
		ss++;
	}
	else if (mm < 59)
	{
		ss = 0;
		mm++;
	}
	else if (hh < 23)
	{
		mm = ss = 0;
		hh++;
	}
	else
	{
		hh = mm = ss = 0;
	}
	//屏幕显示时间刷新
	WallClock_append(hh, mm, ss);
}

//将时间显示在屏幕右下角
void WallClock_append(int h, int m, int s)
{
	unsigned short int *p;
	p = (unsigned short int *)(0xB8000 + 24 * 160 + 2 * 72);
	*p = 0x2f00 + 0x30 + (unsigned short int)(h / 10);
	p = p + 1;
	*p = 0x2f00 + 0x30 + (unsigned short int)(h % 10);
	p = p + 1;
	*p = 0x2f00 + 0x3a;
	p = p + 1;
	*p = 0x2f00 + 0x30 + (unsigned short int)(m / 10);
	p = p + 1;
	*p = 0x2f00 + 0x30 + (unsigned short int)(m % 10);
	p = p + 1;
	*p = 0x2f00 + 0x3a;
	p = p + 1;
	*p = 0x2f00 + 0x30 + (unsigned short int)(s / 10);
	p = p + 1;
	*p = 0x2f00 + 0x30 + (unsigned short int)(s % 10);
}