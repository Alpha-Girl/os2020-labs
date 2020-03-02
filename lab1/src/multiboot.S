/*multiboot.S*/

#define MULTIBOOT_HEADER_MAGIC                  0x1BADB002

#define MULTIBOOT_HEADER_FLAGS                  0x00000000

        .text

        .globl  start, _start
start:
_start:
        jmp     multiboot_entry

        /* Align 32 bits boundary. */
        .align  4

        /* Multiboot header. */
multiboot_header:
        /* magic */
        .long   MULTIBOOT_HEADER_MAGIC
        /* flags */
        .long   MULTIBOOT_HEADER_FLAGS
        /* checksum */
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

multiboot_entry:

/*UART output part*/
        movb $0x48,%al/* 输出字母H */
        movw $0x3F8,%dx
        outb %al,%dx

        movb $0x45,%al/* 输出字母E */
        outb %al,%dx

        movb $0x4C,%al/* 输出字母L */
        outb %al,%dx

        outb %al,%dx/* 输出字母L*/

        movb $0x4F,%al/* 输出字母O*/
        outb %al,%dx

        movb $0x57,%al/* 输出字母W */
        outb %al,%dx

        movb $0x4F,%al/* 输出字母O */
        outb %al,%dx

        movb $0x52,%al/* 输出字母R*/
        outb %al,%dx

        movb $0x4C,%al/* 输出字母L*/
        outb %al,%dx

        movb $0x44,%al/* 输出字母D */
        outb %al,%dx

        movb $0x5F,%al/* 输出符号_*/
        outb %al,%dx

        movb $0x50,%al/* 输出字母P*/
        outb %al,%dx

        movb $0x42, %al /* 输出字母B */
        outb %al,%dx

        movb $0x31, %al /* 输出数字1 */
        outb %al,%dx

        movb $0x38, %al /* 输出数字8 */
        outb %al,%dx

        movb $0x30, %al /* 输出数字0 */
        outb %al,%dx

        outb %al,%dx /* 输出数字0 */

        outb %al,%dx /* 输出字母0 */

        movb $0x32, %al /* 输出数字2 */
        outb %al,%dx

        movb $0x39, %al /* 输出数字9 */
        outb %al,%dx

        movb $0x30, %al /* 输出字母0 */
        outb %al,%dx

        movb $0x5F,%al/* 输出符号_*/
        outb %al,%dx

        movb $0x48,%al/* 输出字母H */
        outb %al,%dx

        movb $0x75,%al/* 输出字母u */
        outb %al,%dx

        movb $0x79,%al/* 输出字母y */
        outb %al,%dx

        movb $0x69,%al/* 输出字母i */
        outb %al,%dx

        movb $0x78,%al/* 输出字母x */
        outb %al,%dx

        movb $0x69,%al/* 输出字母i */
        outb %al,%dx

        movb $0x61,%al/* 输出字母a */
        outb %al,%dx

        movb $0x6e,%al/* 输出字母n */
        outb %al,%dx

        movb $0x67,%al/* 输出字母g */
        outb %al,%dx

/*VGA output part*/

/*绿底白字*/

        movl $0x2f652f68, 0xB8000  /*输出 E H*/
        movl $0x2f6c2f6c, 0xB8004  /*输出 L L*/
        movl $0x2f772f6f, 0xB8008  /*输出 W O*/
        movl $0x2f722f6f, 0xB800c  /*输出 R O*/
        movl $0x2f642f6c, 0xB8010  /*输出 D L*/
        movl $0x2f292f3a, 0xB8014  /*输出 ) :*/
        movl $0x2f422f50, 0xB8018  /*输出 B P*/
        movl $0x2f382f31, 0xB801c  /*输出 8 1*/
        movl $0x2f302f30, 0xB8020  /*输出 0 0*/
        movl $0x2f322f30, 0xB8024  /*输出 2 0*/
        movl $0x2f302f39, 0xB8028  /*输出 0 9*/
        movl $0x2f482f5f, 0xB802c  /*输出 H _*/
        movl $0x2f792f75, 0xB8030  /*输出 y u*/
        movl $0x2f782f69, 0xB8034  /*输出 x i*/
        movl $0x2f612f69, 0xB8038  /*输出 a i*/
        movl $0x2f672f6e, 0xB803c  /*输出 g n*/

loop:   hlt
        jmp     loop

