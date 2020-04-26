// NOTE: 以下框架仅供参考。可以推翻重写。
#define NULL 0
#define num_of_cmds 2
#define ENTER 0xd
#define BACKSPACE 127
// 命令处理函数
#include "../myOS/lib/string.h"
#include "../myOS/dev/uart_vga.h"
extern int myPrintk(int color, const char *format, ...);
int cmd_handler(int, char **);
int help_handler(int, char **);
void arg(char *str);
void help_help(void);

unsigned char sBuf[400];
int n_argc;
char *p_argv[20];

struct command
{
	char *cmd;
	int (*func)(int argc, char **argv);
	void (*help_func)(void);
	char *desc;
} cmds[num_of_cmds] = {
	{"cmd", cmd_handler, NULL, "list all commands"},
	{"help", help_handler, help_help, "help [cmd]"},
};

// help 的帮助
void help_help(void)
{
	myPrintk(0x7, "Type `help name' to find out more about the function `name'.\n");
}

// help 命令处理函数
int help_handler(int argc, char *argv[])
{
	int i;
	void (*f)(void);
	for (i = 0; i < num_of_cmds; i++)
	{
		//若help [cmd]对应的cmd在cmds[]中
		//调用该指令对应的 help_func
		if (strcmp(argv[1], cmds[i].cmd) == 0)
		{
			f = cmds[i].help_func;
			if (f != NULL)
				f();
			break;
		}
	}
	//该指令不在cmd中，或未输入cmd
	//打印错误信息
	if (i == num_of_cmds)
	{
		myPrintk(0x4, "The cmd is not defined. Type 'cmd' to see the command list.\n");
	}
	return 0;
}

// cmd 命令处理函数
int cmd_handler(int argc, char *argv[])
{
	int i = 0;
	myPrintk(0x7, "My shell, version 1.0.0\n");
	myPrintk(0x7, "These shell commands are defined. Type 'cmd' to see this list.\n");
	myPrintk(0x7, "command name: description\n");
	//按 命令：命令描述 格式输出所有指令
	for (i = 0; i < num_of_cmds; i++)
	{
		myPrintk(0x7, cmds[i].cmd);
		myPrintk(0x7, " : ");
		myPrintk(0x7, cmds[i].desc);
		myPrintk(0x7, "\n");
	}
	return 0;
}

void startShell(void)
{
	unsigned char c[2];
	int (*f)(int argc, char **argv);
	int i = 0, j;
	c[1] = '\0';
	myPrintk(0x2, "YixiangHu@Desktop:");
	c[0] = uart_get_char();
	sBuf[i++] = c[0];
	for (;;)
	{
		//回车
		if (c[0] == ENTER)
		{
			myPrintk(0x7, "\n");
			sBuf[--i] = '\0';
			arg(sBuf); //对字符串进行处理，并将p_argv指向对应位置
			for (j = 0; j < num_of_cmds; j++)
			{
				//与cmds[]逐一比较，判断该指令是否在命令列表
				if (strcmp(p_argv[0], cmds[j].cmd) == 0)
				{
					//若在命令列表
					//输出 命令描述
					myPrintk(0x7, "USAGE: ");
					myPrintk(0x7, cmds[j].desc);
					myPrintk(0x7, "\n");
					//调用 命令处理函数
					f = cmds[j].func;
					f(n_argc, p_argv);
					break;
				}
			}
			if (j == num_of_cmds)
			{
				//输出错误信息
				myPrintk(0x7, "Unknown command.\n");
			}
			//等待 下一条指令的输入
			myPrintk(0x2, "YixiangHu@Desktop:");
			c[0] = uart_get_char();
			i = 0;
			sBuf[i++] = c[0];
		}
		//退格（BackSpace）处理
		else if (c[0] == BACKSPACE)
		{
			if (i > 1)
			{
				clear_char();
			}
			if (i == 1)
			{
				i = 0;
			}
			else
			{
				i = i - 2;
			}
			c[0] = uart_get_char();
			sBuf[i++] = c[0];
		}
		else
		{
			myPrintk(0x7, c);
			c[0] = uart_get_char();
			sBuf[i++] = c[0];
		}
	}
}

//arg函数功能：
//将p_argv[]指向对应字符串起始位置
//对字符串结尾空格进行处理
//修改n_argc
void arg(char *str)
{
	int i = 0, k = 0, flag_space = 0, flag_qm = 0;
	//flag_space = 1表示 上一字符为空格
	//flag_qm =1 表示 当前字符属于 引号内部内容
	n_argc = 0;
	p_argv[0] = &str[0];
	for (;; i++)
	{
		if (str[i] == '\0')
		{
			//处理结束，退出循环
			break;
		}
		else if (str[i] == 34)
		{
			//引号（quotation marks）处理
			flag_qm = !flag_qm; //flag翻转
			if (flag_qm == 1)
			{
				p_argv[++n_argc] = &str[i + 1];
			}
			else if (flag_qm == 0)
			{
				str[i] == '\0';
			}
		}
		else if (str[i] == ' ')
		{
			if (flag_qm == 0 && flag_space == 0)
			{
				str[i] = '\0';
				flag_space = 1;
			}
			else if (flag_qm == 0 && flag_space == 1)
			{
				str[i] = '\0';
			}
		}
		else if (flag_space == 1 && flag_qm == 0)
		{
			p_argv[++n_argc] = &str[i];
			flag_space = 0;
		}
	}
}