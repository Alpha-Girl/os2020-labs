extern int myPrintf(int color,const char *format, ...);

void myMain(void)
{
    int i;

    myPrintf(0x7,"main\n");
    for(i=1;i<30;i++) myPrintf(i,"%d\n",i);

    return;
}