// NOTE: 以下框架仅供参考。可以推翻重写。
#define NULL 0
// 命令处理函数
int cmd_handler(int, char **);
int help_handler(int, char **);

// 帮助处理函数
void help_help(void);

struct command {
	char *cmd;
	int (*func)(int argc, char *argv[]);
	void (*help_func)(void);
	char *desc;
} cmds[] = {
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
	// TODO
}