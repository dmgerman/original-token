multiline_comment|/*  arch/sparc/kernel/irq.c:  Interrupt request handling routines. On the&n; *                            Sparc the IRQ&squot;s are basically &squot;cast in stone&squot;&n; *                            and you are supposed to probe the prom&squot;s device&n; *                            node trees to find out who&squot;s got which IRQ.&n; *&n; *  Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; *&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * The same sigaction struct is used, and with similar semantics (ie there&n; * is a SA_INTERRUPT flag etc). Naturally it&squot;s not a 1:1 relation, but there&n; * are similarities.&n; *&n; * sa_handler(int irq_NR) is the default function called (0 if no).&n; * sa_mask is horribly ugly (I won&squot;t even mention it)&n; * sa_flags contains various info: SA_INTERRUPT etc&n; * sa_restorer is the unused&n; */
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
id|save_flags
c_func
(paren
id|flags
)paren
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
id|save_flags
c_func
(paren
id|flags
)paren
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
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
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
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
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
r_return
suffix:semicolon
)brace
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE SA_ONESHOT
multiline_comment|/*&n; * Using &quot;struct sigaction&quot; is slightly silly, but there&n; * are historical reasons and it works well, so..&n; */
DECL|function|irqaction
r_static
r_int
id|irqaction
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|sigaction
op_star
id|new_sa
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
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
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
)paren
(brace
r_return
id|irqaction
c_func
(paren
id|irq
comma
op_amp
id|sa
)paren
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
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
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
DECL|function|math_error_irq
r_static
r_void
id|math_error_irq
c_func
(paren
r_int
id|cpl
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|no_action
r_static
r_void
id|no_action
c_func
(paren
r_int
id|cpl
)paren
(brace
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
r_int
id|i
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
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|i
comma
id|bad_interrupt
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
