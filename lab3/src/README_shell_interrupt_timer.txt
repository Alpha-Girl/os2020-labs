本实验实现shell,intertupt,timer

主要功能模块：
1.基本功能；
2.中断处理；
3.shell；

TO DO：

1.修改 start32.S 增加 IDT 初始化，此时尚不启动时钟中断
2.编写 irq.S 和 irqs.c，实现 enable_interrupt、disable_interrupt 和 ignoreIntBody
3.编写 dev/i8253.c 和 dev/i8259A.c
4.修改 osStart.c，调⽤初始化函数并启动中断
5.编写 kernel/tick.c 和 kernel/wallClock.c
6.修改 start32.S，启动时钟中断
7.修改 userApp/main.c 进⾏测试，确认时钟中断⼯作正常
8.编写 userApp/shell.c，并修改 userApp/main.c 调⽤ startShell，确认 shell ⼯作正常
编写 shell 时，可能会遇到⼀些⽐较复杂的字符串操作，这时可以编写 lib/string.c 等辅助⽂件，⽅便未来使⽤
9.编写 source2img.sh。
10.编写实验报告。

运行命令:
qemu-system-i386 -kernel myOS.elf -serial pty &