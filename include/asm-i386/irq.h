macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 16
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %gs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %esi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(USER_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%fs&bslash;n&bslash;t&quot;   &bslash;&n;&t;&quot;movl $0,%edx&bslash;n&bslash;t&quot;  &bslash;&n;&t;&quot;movl %edx,%db7&bslash;n&bslash;t&quot;
multiline_comment|/*&n; * SAVE_MOST/RESTORE_MOST is used for the faster version of IRQ handlers,&n; * installed by using the SA_INTERRUPT flag. These kinds of IRQ&squot;s don&squot;t&n; * call the routines that do signal handling etc on return, and can have&n; * more relaxed register-saving etc. They are also atomic, and are thus&n; * suited for small, fast interrupts like the serial lines or the harddisk&n; * drivers, which don&squot;t actually need signal handling etc.&n; *&n; * Also note that we actually save only those registers that are used in&n; * C subroutines (%eax, %edx and %ecx), so if you do something weird,&n; * you&squot;re on your own. The only segments that are saved (not counting the&n; * automatic stack and code segment handling) are %ds and %es, and they&n; * point to kernel space. No messing around with %fs here.&n; */
DECL|macro|SAVE_MOST
mdefine_line|#define SAVE_MOST &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot;
DECL|macro|RESTORE_MOST
mdefine_line|#define RESTORE_MOST &bslash;&n;&t;&quot;popl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;popl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;popl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pop %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pop %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;iret&quot;
multiline_comment|/*&n; * The &quot;inb&quot; instructions are not needed, but seem to change the timings&n; * a bit - without them it seems that the harddisk driver won&squot;t work on&n; * all hardware. Arghh.&n; */
DECL|macro|ACK_FIRST
mdefine_line|#define ACK_FIRST(mask) &bslash;&n;&t;&quot;inb $0x21,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,&quot;SYMBOL_NAME_STR(cache_21)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_21)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x21&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|ACK_SECOND
mdefine_line|#define ACK_SECOND(mask) &bslash;&n;&t;&quot;inb $0xA1,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,&quot;SYMBOL_NAME_STR(cache_A1)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_A1)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;toutb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|UNBLK_FIRST
mdefine_line|#define UNBLK_FIRST(mask) &bslash;&n;&t;&quot;inb $0x21,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tandb $~(&quot; #mask &quot;),&quot;SYMBOL_NAME_STR(cache_21)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_21)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x21&bslash;n&bslash;t&quot;
DECL|macro|UNBLK_SECOND
mdefine_line|#define UNBLK_SECOND(mask) &bslash;&n;&t;&quot;inb $0xA1,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tandb $~(&quot; #mask &quot;),&quot;SYMBOL_NAME_STR(cache_A1)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_A1)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA1&bslash;n&bslash;t&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|FAST_IRQ_NAME
mdefine_line|#define FAST_IRQ_NAME(nr) IRQ_NAME2(fast_IRQ##nr)
DECL|macro|BAD_IRQ_NAME
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;asmlinkage void FAST_IRQ_NAME(nr); &bslash;&n;asmlinkage void BAD_IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-&quot;#nr&quot;-2&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;ACK_##chip(mask) &bslash;&n;&t;&quot;incl &quot;SYMBOL_NAME_STR(intr_count)&quot;&bslash;n&bslash;t&quot;&bslash;&n;&t;&quot;sti&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %esp,%ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot; #nr &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(do_IRQ)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $8,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;cli&bslash;n&bslash;t&quot; &bslash;&n;&t;UNBLK_##chip(mask) &bslash;&n;&t;&quot;decl &quot;SYMBOL_NAME_STR(intr_count)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_sys_call&bslash;n&quot; &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(fast_IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_MOST &bslash;&n;&t;ACK_##chip(mask) &bslash;&n;&t;&quot;incl &quot;SYMBOL_NAME_STR(intr_count)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot; #nr &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(do_fast_IRQ)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $4,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;cli&bslash;n&bslash;t&quot; &bslash;&n;&t;UNBLK_##chip(mask) &bslash;&n;&t;&quot;decl &quot;SYMBOL_NAME_STR(intr_count)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;RESTORE_MOST &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(bad_IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_MOST &bslash;&n;&t;ACK_##chip(mask) &bslash;&n;&t;RESTORE_MOST);
macro_line|#endif
eof
