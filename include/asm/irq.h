macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992 Linus Torvalds&n; */
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %gs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %esi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $0x10,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $0x17,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%fs&bslash;n&bslash;t&quot;
DECL|macro|ACK_FIRST
mdefine_line|#define ACK_FIRST(mask) &bslash;&n;&t;&quot;inb $0x21,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x21&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|ACK_SECOND
mdefine_line|#define ACK_SECOND(mask) &bslash;&n;&t;&quot;inb $0xA1,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA0&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;toutb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt()
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;extern void IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n.align 2&bslash;n&quot; &bslash;&n;&quot;.globl _IRQ&quot; #nr &quot;_interrupt&bslash;n&quot; &bslash;&n;&quot;_IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-1&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;cli&bslash;n&bslash;t&quot; &bslash;&n;&t;ACK_##chip(mask) &bslash;&n;&t;&quot;sti&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %esp,%ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot; #nr &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call _do_IRQ&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $8,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_sys_call&quot;);
macro_line|#endif
eof
