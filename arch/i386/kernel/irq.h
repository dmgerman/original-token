macro_line|#ifndef __irq_h
DECL|macro|__irq_h
mdefine_line|#define __irq_h
multiline_comment|/*&n; * Various low-level irq details needed by irq.c and smp.c&n; *&n; * Interrupt entry/exit code at both C and assembly level&n; */
macro_line|#ifdef __SMP__
DECL|macro|INIT_STUCK
macro_line|#undef INIT_STUCK
DECL|macro|INIT_STUCK
mdefine_line|#define INIT_STUCK 200000000
DECL|macro|STUCK
macro_line|#undef STUCK
DECL|macro|STUCK
mdefine_line|#define STUCK &bslash;&n;if (!--stuck) {printk(&quot;irq_enter stuck (irq=%d, cpu=%d, global=%d)&bslash;n&quot;,irq,cpu,global_irq_holder); stuck = INIT_STUCK;}
DECL|function|irq_enter
r_static
r_inline
r_void
id|irq_enter
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
r_int
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
id|hardirq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|cpu
op_eq
id|global_irq_holder
)paren
(brace
r_static
r_int
id|printed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|printed
)paren
id|printk
c_func
(paren
l_string|&quot;BAD! Local interrupts enabled, global disabled&bslash;n&quot;
)paren
suffix:semicolon
id|printed
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|STUCK
suffix:semicolon
multiline_comment|/* nothing */
suffix:semicolon
)brace
)brace
DECL|function|irq_exit
r_static
r_inline
r_void
id|irq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|hardirq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|release_irqlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;(++local_irq_count[cpu])
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;(--local_irq_count[cpu])
macro_line|#endif
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %esi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot;
multiline_comment|/*&n; * These are used just for the &quot;bad&quot; interrupt handlers, &n; * which just clear the mask and return..&n; */
DECL|macro|SAVE_MOST
mdefine_line|#define SAVE_MOST &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot;
DECL|macro|RESTORE_MOST
mdefine_line|#define RESTORE_MOST &bslash;&n;&t;&quot;popl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;popl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;popl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pop %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pop %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;iret&quot;
multiline_comment|/*&n; * The &quot;inb&quot; instructions are not needed, but seem to change the timings&n; * a bit - without them it seems that the harddisk driver won&squot;t work on&n; * all hardware. Arghh.&n; */
DECL|macro|ACK_FIRST
mdefine_line|#define ACK_FIRST(mask,nr) &bslash;&n;&t;&quot;inb $0x21,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,&quot;SYMBOL_NAME_STR(cache_21)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_21)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x21&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|ACK_SECOND
mdefine_line|#define ACK_SECOND(mask,nr) &bslash;&n;&t;&quot;inb $0xA1,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;torb $&quot; #mask &quot;,&quot;SYMBOL_NAME_STR(cache_A1)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_A1)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovb $0x20,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;toutb %al,$0x20&bslash;n&bslash;t&quot;
DECL|macro|UNBLK_FIRST
mdefine_line|#define UNBLK_FIRST(mask) &bslash;&n;&t;&quot;inb $0x21,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tandb $~(&quot; #mask &quot;),&quot;SYMBOL_NAME_STR(cache_21)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_21)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0x21&bslash;n&bslash;t&quot;
DECL|macro|UNBLK_SECOND
mdefine_line|#define UNBLK_SECOND(mask) &bslash;&n;&t;&quot;inb $0xA1,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tandb $~(&quot; #mask &quot;),&quot;SYMBOL_NAME_STR(cache_A1)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb &quot;SYMBOL_NAME_STR(cache_A1)&quot;,%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;outb %al,$0xA1&bslash;n&bslash;t&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|BAD_IRQ_NAME
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT &bslash;&n;&t;&quot;movl %esp, %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andl $-8192, %ebx&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
multiline_comment|/*&n; *&t;SMP has a few special interrupts for IPI messages&n; */
DECL|macro|BUILD_SMP_INTERRUPT
mdefine_line|#define BUILD_SMP_INTERRUPT(x) &bslash;&n;asmlinkage void x(void); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-1&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
DECL|macro|BUILD_SMP_TIMER_INTERRUPT
mdefine_line|#define BUILD_SMP_TIMER_INTERRUPT(x) &bslash;&n;asmlinkage void x(struct pt_regs * regs); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-1&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;movl %esp,%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $4,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
macro_line|#endif /* __SMP__ */
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;asmlinkage void BAD_IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-&quot;#nr&quot;-2&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;ACK_##chip(mask,(nr&amp;7)) &bslash;&n;&t;&quot;movl %esp,%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot; #nr &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(do_IRQ)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $8,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;UNBLK_##chip(mask) &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot; &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(bad_IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_MOST &bslash;&n;&t;ACK_##chip(mask,(nr&amp;7)) &bslash;&n;&t;RESTORE_MOST);
DECL|macro|BUILD_TIMER_IRQ
mdefine_line|#define BUILD_TIMER_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;asmlinkage void BAD_IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(bad_IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;SYMBOL_NAME_STR(IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-&quot;#nr&quot;-2&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;ACK_##chip(mask,(nr&amp;7)) &bslash;&n;&t;&quot;movl %esp,%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot; #nr &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(do_IRQ)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $8,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;UNBLK_##chip(mask) &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
multiline_comment|/*&n; * x86 profiling function, SMP safe. We might want to do this in&n; * assembly totally?&n; */
DECL|function|x86_do_profile
r_static
r_inline
r_void
id|x86_do_profile
(paren
r_int
r_int
id|eip
)paren
(brace
r_if
c_cond
(paren
id|prof_buffer
op_logical_and
id|current-&gt;pid
)paren
(brace
r_extern
r_int
id|_stext
suffix:semicolon
id|eip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|eip
op_rshift_assign
id|prof_shift
suffix:semicolon
r_if
c_cond
(paren
id|eip
OL
id|prof_len
)paren
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|eip
)braket
)paren
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t; * Dont ignore out-of-bounds EIP values silently,&n;&t;&t; * put them into the last histogram slot, so if&n;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t; */
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|prof_len
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
