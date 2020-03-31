// NOTE: 以下框架仅供参考。可以推翻重写。
#define NULL 0
#define FLAG_EXT 0x00  // Normal function keys
#define num_of_cmds 3
// Special keys
#define ESC  (0x01 & FLAG_EXT) // Esc
#define TAB  (0x02 & FLAG_EXT) // Tab
#define ENTER  (0x03 & FLAG_EXT) // Enter
#define BACKSPACE (0x04 & FLAG_EXT) // BackSpace
// 命令处理函数
extern char strcmp(const char * src, const char * dest);
extern void clear_char(void);
extern void append2screen(char *str,int color);
extern unsigned char uart_get_char(void);
extern void clear_screen(void);
extern int myPrintk(int color,const char *format, ...);
int cmd_handler(int, char **);
int help_handler(int, char **);
unsigned char sBuf[400];
// 帮助处理函数
void help_help(void);

struct command {
	char *cmd;
	int (*func)(int argc, char *argv[]);
	void (*help_func)(void);
	char *desc;
} cmds[num_of_cmds] = {
	{"cmd", cmd_handler, NULL, "list all commands"},
	{"help", help_handler, help_help, "help [cmd]"},
	{"", NULL, NULL, ""}
};


// help 的帮助
void help_help(void)
{
	// TODO
}

// help 命令处理函数
int help_handler(int argc, char *argv[])
{
	// TODO
	return 0;
}

// cmd 命令处理函数
int cmd_handler(int argc, char **argv)
{
	// TODO
	return 0;
}

void startShell(void)
{
	unsigned char c[2];
	void (*f)(void);
	int i=0,j;
	c[1]='\0';

	myPrintk(0x2,"YixiangHu@Desktop:");
	c[0]=uart_get_char();
	sBuf[i++]=c[0];
	for(;;){
		if(c[0]==0xd){
			myPrintk(0x7,"\n");
			sBuf[--i]='\0';
			for(j=0;j<num_of_cmds;j++){
				//myPrintk(0x2,sBuf);
				//myPrintk(0x2,cmds[j].cmd);
				//myPrintk(0x2,"%d",strcmp(sBuf,cmds[j].cmd));
				if(strcmp(sBuf,cmds[j].cmd)==0){
					f=cmds[j].func;
					f();
					myPrintk(0x7,cmds[j].desc);
					myPrintk(0x7,"\n");
					break;
				}
			}
			myPrintk(0x2,"YixiangHu@Desktop:");
			c[0]=uart_get_char();
			i=0;
			sBuf[i++]=c[0];
		}
		else if(c[0] == 0xa){
			if(i>0){
				i--;
				clear_char();
			}
			c[0]=uart_get_char();
			sBuf[i++]=c[0];
		}
		else {
			myPrintk(0x7,c);
			c[0]=uart_get_char();
			sBuf[i++]=c[0];
		}
	}
}