extern int myPrintk(int color,const char *format, ...);
extern void clear_screen(void);
extern void myMain(void);
extern void init8259A(void);
extern void init8253(void);
extern void setWallClock(int h, int m, int s);

void osStart(void){
	clear_screen();
	init8259A();
	init8253();
	setWallClock(0, 0, 0);
	
	myPrintk(0x2,"START RUNNING......\n");
	myMain();
	myPrintk(0x2, "STOP RUNNING......ShutDown\n");
	while(1);
}