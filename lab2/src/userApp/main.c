
extern int myPrintf(int color,const char *format, ...);
extern int myPrintk(int color,const char *format, ...);
void myMain(void){    
    int i;

    myPrintk(0x7,"main\n");
    for (i=1;i<30;i++) myPrintf(i,"%d\n",i);
    myPrintf(0x7,"main,PB18000290_HuYixiang\n");
    return;
}
