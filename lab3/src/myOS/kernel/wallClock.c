int hh=0, mm=0, ss=0, ms=0;
void WallClock_append(int h, int m, int s);
void setWallClock(int h, int m, int s)
{
	hh = h;
	mm = m;
	ss = s;
	WallClock_append(hh,mm,ss);
}

void getWallClock(int *h, int *m, int *s)
{
        *h = hh;
        *m = mm;
        *s = ss;
}

void setWallClockHook(void (*func)(void)) 
{
	// TODO 请填写代码
}

void maybeUpdateWallClock(void)
{
	if(ss < 59){
		ss++;
	}
	else if(mm < 59){
		ss = 0;
		mm++;
	}
	else if(hh < 23){
		mm = ss = 0;
		hh++;
	}
	else{
		hh = mm = ss = 0;
	}
	WallClock_append(hh,mm,ss);
}

void WallClock_append(int h, int m, int s){
	unsigned short int *p;
	p = (unsigned short int *)(0xB8000 + 24 * 160 + 2 * 72);
	*p = 0x2f00 + 0x30 +(unsigned short int)(h/10);
	p = p + 1;
	*p = 0x2f00 + 0x30 +(unsigned short int)(h%10);
	p = p + 1;
	*p = 0x2f00 + 0x3a;
	p = p + 1;
	*p = 0x2f00 + 0x30+(unsigned short int)(m/10);
	p = p + 1;
	*p = 0x2f00 + 0x30+(unsigned short int)(m%10);
	p = p + 1;
	*p = 0x2f00 + 0x3a;
	p = p + 1;
	*p = 0x2f00 + 0x30+(unsigned short int)(s/10);
	p = p + 1;
	*p = 0x2f00 + 0x30+(unsigned short int)(s%10);
}