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
void arg(char *str);
unsigned char sBuf[400];
char aBuf[10][10];
// 帮助处理函数
void help_help(void);
int n_argc;
char *p_argv[20];
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
	
}

// help 命令处理函数
int help_handler(int argc, char *argv[])
{
	int i;
	void (*f)(void);
	for(i=0;i<num_of_cmds;i++){
		if(strcmp(argv[1],cmds[i].cmd)==0){
			f=cmds[i].help_func;
			if(f!=NULL)
				f();
			break;
		}
	}
	if(i==num_of_cmds){
		myPrintk(0x4,"The cmd is not defined. Type 'cmd' to see the command list.\n");
	}
	return 0;
}

// cmd 命令处理函数
int cmd_handler(int argc, char *argv[])
{
	int i=0;
	myPrintk(0x7,"My shell, version 1.0.0\n");
	myPrintk(0x7,"These shell commands are defined. Type 'cmd' to see this list.\n");
	myPrintk(0x7,"command name: description");
	for(i=0;i<num_of_cmds-1;i++){
		myPrintk(0x7,"\n");
		myPrintk(0x7,cmds[i].cmd);
		myPrintk(0x7," : ");
		myPrintk(0x7,cmds[i].desc);
	}
	myPrintk(0x7,"\n");
	return 0;
}

void startShell(void)
{
	unsigned char c[2];
	int a;
	void (*f)(int argc,char **argv);
	int i=0,j,k,l;
	c[1]='\0';
	myPrintk(0x2,"YixiangHu@Desktop:");
	c[0]=uart_get_char();
	sBuf[i++]=c[0];
	for(;;){
		if(c[0]==0xd){
			myPrintk(0x7,"\n");
			sBuf[--i]='\0';
			arg(sBuf);
			/*myPrintk(0x4,"%d",n_argc);
			for(i=0;i<=n_argc;i++){
				myPrintk(0x4,p_argv[i]);
				myPrintk(0x4,"\n");
			}*/
			for(j=0;j<num_of_cmds;j++){
				//myPrintk(0x2,sBuf);
				//myPrintk(0x2,cmds[j].cmd);
				//myPrintk(0x2,"%d",strcmp(sBuf,cmds[j].cmd));
				if(strcmp(p_argv[0],cmds[j].cmd)==0){
					myPrintk(0x7,"USAGE: ");
					myPrintk(0x7,cmds[j].desc);
					myPrintk(0x7,"\n");
					f=cmds[j].func;
					f(n_argc,p_argv);
					
					
					break;
				}
			}
			if(j==num_of_cmds){
				myPrintk(0x7,"Unknown command.\n");
			}
			myPrintk(0x2,"YixiangHu@Desktop:");
			c[0]=uart_get_char();
			i=0;
			sBuf[i++]=c[0];
		}
		else if(c[0] == 0x8){
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
void arg(char *str){
	int i=0,k=0, flag_space = 0,flag_qm=0;
	n_argc=0;

	p_argv[0]=&str[0];
	for(;;i++){
		if(str[i]=='\0'){
			break;
		}
		else if(str[i]==34){
   			flag_qm = ! flag_qm;
		}

		else if(str[i]==' '){
			if(flag_qm == 0 && flag_space == 0){
				
				str[i]='\0';
				flag_space=1;
			}
			else if(flag_qm == 0 && flag_space==1){
				str[i]='\0';
			}
		}
		else if(flag_space==1 && flag_qm==0){
			p_argv[++n_argc]=&str[i];
			flag_space=0;
		}
	}
}