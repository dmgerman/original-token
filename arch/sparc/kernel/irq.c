multiline_comment|/*  arch/sparc/kernel/irq.c:  Interrupt request handling routines. On the&n; *                            Sparc the IRQ&squot;s are basically &squot;cast in stone&squot;&n; *                            and you are supposed to probe the prom&squot;s device&n; *                            node trees to find out who&squot;s got which IRQ.&n; *&n; *  Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; *&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * The same sigaction struct is used, and with similar semantics (ie there&n; * is a SA_INTERRUPT flag etc). Naturally it&squot;s not a 1:1 relation, but there&n; * are similarities.&n; *&n; * sa_handler(int irq_NR) is the default function called (0 if no).&n; * sa_mask is horribly ugly (I won&squot;t even mention it)&n; * sa_flags contains various info: SA_INTERRUPT etc&n; * sa_restorer is the unused&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
op_star
id|int_reg
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We have mapped the irq enable register in head.S and all we&n;   * have to do here is frob the bits.&n;   */
id|int_reg
op_assign
(paren
r_char
op_star
)paren
id|IRQ_ENA_ADR
suffix:semicolon
r_switch
c_cond
(paren
id|irq_nr
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x02
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x04
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x08
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x10
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x20
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_amp
(paren
op_complement
(paren
l_int|0x80
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AIEEE, Illegal interrupt disable requested irq=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|irq_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|int_reg
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We have mapped the irq enable register in head.S and all we&n;   * have to do here is frob the bits.&n;   */
id|int_reg
op_assign
(paren
r_int
r_int
op_star
)paren
id|IRQ_ENA_ADR
suffix:semicolon
r_switch
c_cond
(paren
id|irq_nr
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x04
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x08
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
op_star
id|int_reg
op_assign
(paren
(paren
op_star
id|int_reg
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AIEEE, Illegal interrupt enable requested irq=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|irq_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Initial irq handlers.&n; */
DECL|struct|irqaction
r_struct
id|irqaction
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|irq_action
r_static
r_struct
id|irqaction
id|irq_action
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|get_irq_list
r_int
id|get_irq_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
op_assign
id|irq_action
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
comma
id|action
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|action-&gt;handler
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d: %8d %c %s&bslash;n&quot;
comma
id|i
comma
id|kstat.interrupts
(braket
id|i
)braket
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|14
)paren
(brace
multiline_comment|/* 14 irq levels on the sparc */
id|printk
c_func
(paren
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|action-&gt;handler
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|action-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|handle_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NMI, probably due to bus-parity error.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC=%08lx, SP=%08lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;sp
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|unexpected_irq
r_static
r_void
id|unexpected_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IO device interrupt, irq = %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC = %08lx NPC = %08lx SP=%08lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
comma
id|regs-&gt;sp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Expecting: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irq_action
(braket
id|i
)braket
dot
id|handler
)paren
id|printk
c_func
(paren
l_string|&quot;[%s:%d] &quot;
comma
id|irq_action
(braket
id|i
)braket
dot
id|name
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;AIEEE&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|handler_irq
r_static
r_inline
r_void
id|handler_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action-&gt;handler
)paren
(brace
id|unexpected_irq
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * do_IRQ handles IRQ&squot;s that have been installed without the&n; * SA_INTERRUPT flag: it uses the full signal-handling return&n; * and runs with other interrupts enabled. All relatively slow&n; * IRQ&squot;s should use this format: notably the keyboard/timer&n; * routines.&n; */
DECL|function|do_IRQ
id|asmlinkage
r_void
id|do_IRQ
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * do_fast_IRQ handles IRQ&squot;s that don&squot;t need the fancy interrupt return&n; * stuff - the handler is also running with interrupts disabled unless&n; * it explicitly enables them later.&n; */
DECL|function|do_fast_IRQ
id|asmlinkage
r_void
id|do_fast_IRQ
c_func
(paren
r_int
id|irq
)paren
(brace
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Got FAST_IRQ number %04lx&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|14
)paren
(brace
multiline_comment|/* Only levels 1-14 are valid on the Sparc. */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
(brace
multiline_comment|/* sched_init() requesting the timer IRQ */
id|irq
op_assign
l_int|14
suffix:semicolon
)brace
id|action
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;handler
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
r_int
r_int
id|irqs
op_assign
l_int|0
suffix:semicolon
r_return
id|irqs
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_int
id|probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|init_IRQ
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
eof
