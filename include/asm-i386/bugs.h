multiline_comment|/*&n; *  include/asm-i386/bugs.h&n; *&n; *  Copyright (C) 1994  Linus Torvalds&n; */
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
DECL|macro|CONFIG_BUGi386
mdefine_line|#define CONFIG_BUGi386
DECL|function|no_halt
r_static
r_void
id|no_halt
c_func
(paren
r_char
op_star
id|s
comma
r_int
op_star
id|ints
)paren
(brace
id|hlt_works_ok
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|no_387
r_static
r_void
id|no_387
c_func
(paren
r_char
op_star
id|s
comma
r_int
op_star
id|ints
)paren
(brace
id|hard_math
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orl $0xE,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%eax,%%cr0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
DECL|variable|fpu_error
r_static
r_char
id|fpu_error
op_assign
l_int|0
suffix:semicolon
DECL|function|copro_timeout
r_static
r_void
id|copro_timeout
c_func
(paren
r_void
)paren
(brace
id|fpu_error
op_assign
l_int|1
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
l_int|100
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|COPRO_TIMER
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;387 failed: trying to reset&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|last_task_used_math
comma
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xf1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xf0
)paren
suffix:semicolon
)brace
DECL|function|check_fpu
r_static
r_void
id|check_fpu
c_func
(paren
r_void
)paren
(brace
r_static
r_float
id|x
op_assign
l_float|4195835.0
suffix:semicolon
r_static
r_float
id|y
op_assign
l_float|3145727.0
suffix:semicolon
r_int
r_int
id|control_word
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hard_math
)paren
(brace
macro_line|#ifndef CONFIG_MATH_EMULATION
id|printk
c_func
(paren
l_string|&quot;No coprocessor found and no math emulation present.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Giving up.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * check if exception 16 works correctly.. This is truly evil&n;&t; * code: it disables the high 8 interrupts to make sure that&n;&t; * the irq13 doesn&squot;t happen. But as this will lead to a lockup&n;&t; * if no exception16 arrives, it depends on the fact that the&n;&t; * high 8 interrupts will be re-enabled by the next timer tick.&n;&t; * So the irq13 will happen eventually, but the exception 16&n;&t; * should get there first..&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Checking 386/387 coupling... &quot;
)paren
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
l_int|50
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|fn
op_assign
id|copro_timeout
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|COPRO_TIMER
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;clts ; fninit ; fnstcw %0 ; fwait&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
op_amp
id|control_word
)paren
)paren
suffix:semicolon
id|control_word
op_and_assign
l_int|0xffc0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fldcw %0 ; fwait&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|control_word
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
l_int|0x21
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fldz ; fld1 ; fdiv %st,%st(1) ; fwait&quot;
)paren
suffix:semicolon
id|timer_active
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|COPRO_TIMER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpu_error
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ignore_irq13
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ok, fpu using old IRQ13 error reporting&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__asm__
c_func
(paren
l_string|&quot;fninit&bslash;n&bslash;t&quot;
l_string|&quot;fldl %1&bslash;n&bslash;t&quot;
l_string|&quot;fdivl %2&bslash;n&bslash;t&quot;
l_string|&quot;fmull %2&bslash;n&bslash;t&quot;
l_string|&quot;fldl %1&bslash;n&bslash;t&quot;
l_string|&quot;fsubp %%st,%%st(1)&bslash;n&bslash;t&quot;
l_string|&quot;fistpl %0&bslash;n&bslash;t&quot;
l_string|&quot;fwait&bslash;n&bslash;t&quot;
l_string|&quot;fninit&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
op_amp
id|fdiv_bug
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|y
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fdiv_bug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ok, fpu using exception 16 error reporting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Hmm, FDIV bug i%c86 system&bslash;n&quot;
comma
l_char|&squot;0&squot;
op_plus
id|x86
)paren
suffix:semicolon
)brace
DECL|function|check_hlt
r_static
r_void
id|check_hlt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Checking &squot;hlt&squot; instruction... &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hlt_works_ok
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;hlt ; hlt ; hlt ; hlt&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Ok.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|check_bugs
r_static
r_void
id|check_bugs
c_func
(paren
r_void
)paren
(brace
id|check_fpu
c_func
(paren
)paren
suffix:semicolon
id|check_hlt
c_func
(paren
)paren
suffix:semicolon
id|system_utsname.machine
(braket
l_int|1
)braket
op_assign
l_char|&squot;0&squot;
op_plus
id|x86
suffix:semicolon
)brace
eof
