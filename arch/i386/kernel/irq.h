macro_line|#ifndef __irq_h
DECL|macro|__irq_h
mdefine_line|#define __irq_h
multiline_comment|/*&n; * Various low-level irq details needed by irq.c and smp.c&n; *&n; * Interrupt entry/exit code at both C and assembly level&n; */
macro_line|#ifdef __SMP__
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
mdefine_line|#define SAVE_ALL &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %esi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(__KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %dx,%es&bslash;n&bslash;t&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT &bslash;&n;&t;&quot;movl %esp, %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andl $-8192, %ebx&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
multiline_comment|/*&n; *&t;SMP has a few special interrupts for IPI messages&n; */
DECL|macro|BUILD_SMP_INTERRUPT
mdefine_line|#define BUILD_SMP_INTERRUPT(x) &bslash;&n;asmlinkage void x(void); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-1&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
DECL|macro|BUILD_SMP_TIMER_INTERRUPT
mdefine_line|#define BUILD_SMP_TIMER_INTERRUPT(x) &bslash;&n;asmlinkage void x(struct pt_regs * regs); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $-1&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;movl %esp,%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $4,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
macro_line|#endif /* __SMP__ */
DECL|macro|BUILD_COMMON_IRQ
mdefine_line|#define BUILD_COMMON_IRQ() &bslash;&n;__asm__( &bslash;&n;&t;&quot;&bslash;n&quot; __ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;&t;&quot;common_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;pushl $ret_from_intr&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp &quot;SYMBOL_NAME_STR(do_IRQ));
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot;#nr&quot;-256&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp common_interrupt&quot;);
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
multiline_comment|/*&n;&t;&t; * Dont ignore out-of-bounds EIP values silently,&n;&t;&t; * put them into the last histogram slot, so if&n;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t; */
r_if
c_cond
(paren
id|eip
OG
id|prof_len
op_minus
l_int|1
)paren
id|eip
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
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
)brace
)brace
macro_line|#endif
eof
