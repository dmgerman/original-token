multiline_comment|/*&n; * indy_int.c: Routines for generic manipulation of the INT[23] ASIC&n; *             found on INDY workstations..&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * $Id: indy_int.c,v 1.2 1997/06/30 15:53:01 ralf Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sgi.h&gt;
macro_line|#include &lt;asm/sgihpc.h&gt;
macro_line|#include &lt;asm/sgint23.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
multiline_comment|/* #define DEBUG_SGINT */
DECL|variable|sgi_i2regs
r_struct
id|sgi_int2_regs
op_star
id|sgi_i2regs
suffix:semicolon
DECL|variable|sgi_i3regs
r_struct
id|sgi_int3_regs
op_star
id|sgi_i3regs
suffix:semicolon
DECL|variable|ioc_icontrol
r_struct
id|sgi_ioc_ints
op_star
id|ioc_icontrol
suffix:semicolon
DECL|variable|ioc_timers
r_struct
id|sgi_ioc_timers
op_star
id|ioc_timers
suffix:semicolon
DECL|variable|ioc_tclear
r_volatile
r_int
r_char
op_star
id|ioc_tclear
suffix:semicolon
DECL|variable|lc0msk_to_irqnr
r_static
r_char
id|lc0msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc1msk_to_irqnr
r_static
r_char
id|lc1msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc2msk_to_irqnr
r_static
r_char
id|lc2msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc3msk_to_irqnr
r_static
r_char
id|lc3msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|indyIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REMOTE_DEBUG
r_extern
r_void
id|rs_kgdb_hook
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|spurious_count
r_int
r_int
id|spurious_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Local IRQ&squot;s are layed out logically like this:&n; *&n; * 0  --&gt; 7   ==   local 0 interrupts&n; * 8  --&gt; 15  ==   local 1 interrupts&n; * 16 --&gt; 23  ==   vectored level 2 interrupts&n; * 24 --&gt; 31  ==   vectored level 3 interrupts (not used)&n; */
DECL|function|disable_local_irq
r_void
id|disable_local_irq
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq_nr
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_case
l_int|7
suffix:colon
id|ioc_icontrol-&gt;imask0
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|10
suffix:colon
r_case
l_int|11
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|13
suffix:colon
r_case
l_int|14
suffix:colon
r_case
l_int|15
suffix:colon
id|ioc_icontrol-&gt;imask1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
r_case
l_int|17
suffix:colon
r_case
l_int|18
suffix:colon
r_case
l_int|19
suffix:colon
r_case
l_int|20
suffix:colon
r_case
l_int|21
suffix:colon
r_case
l_int|22
suffix:colon
r_case
l_int|23
suffix:colon
id|ioc_icontrol-&gt;cmeimask0
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|16
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* This way we&squot;ll see if anyone would ever want vectored&n;&t;&t; * level 3 interrupts.  Highly unlikely.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;Yeeee, got passed irq_nr %d at disable_irq&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;INVALID IRQ level!&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_local_irq
r_void
id|enable_local_irq
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq_nr
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_case
l_int|7
suffix:colon
id|ioc_icontrol-&gt;imask0
op_or_assign
(paren
l_int|1
op_lshift
id|irq_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|10
suffix:colon
r_case
l_int|11
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|13
suffix:colon
r_case
l_int|14
suffix:colon
r_case
l_int|15
suffix:colon
id|ioc_icontrol-&gt;imask1
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
r_case
l_int|17
suffix:colon
r_case
l_int|18
suffix:colon
r_case
l_int|19
suffix:colon
r_case
l_int|20
suffix:colon
r_case
l_int|21
suffix:colon
r_case
l_int|22
suffix:colon
r_case
l_int|23
suffix:colon
id|enable_local_irq
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|ioc_icontrol-&gt;cmeimask0
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|16
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
l_string|&quot;Yeeee, got passed irq_nr %d at disable_irq&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;INVALID IRQ level!&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|disable_gio_irq
r_void
id|disable_gio_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
multiline_comment|/* XXX TODO XXX */
)brace
DECL|function|enable_gio_irq
r_void
id|enable_gio_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
multiline_comment|/* XXX TODO XXX */
)brace
DECL|function|disable_hpcdma_irq
r_void
id|disable_hpcdma_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
multiline_comment|/* XXX TODO XXX */
)brace
DECL|function|enable_hpcdma_irq
r_void
id|enable_hpcdma_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
multiline_comment|/* XXX TODO XXX */
)brace
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
id|n
op_assign
id|irq_nr
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_END
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;whee, invalid irq_nr %d&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;IRQ, you lose...&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_LOCAL0
op_logical_and
id|n
OL
id|SGINT_GIO
)paren
(brace
id|disable_local_irq
c_func
(paren
id|n
op_minus
id|SGINT_LOCAL0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_GIO
op_logical_and
id|n
OL
id|SGINT_HPCDMA
)paren
(brace
id|disable_gio_irq
c_func
(paren
id|n
op_minus
id|SGINT_GIO
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_HPCDMA
op_logical_and
id|n
OL
id|SGINT_END
)paren
(brace
id|disable_hpcdma_irq
c_func
(paren
id|n
op_minus
id|SGINT_HPCDMA
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;how did I get here?&quot;
)paren
suffix:semicolon
)brace
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
id|n
op_assign
id|irq_nr
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_END
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;whee, invalid irq_nr %d&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;IRQ, you lose...&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_LOCAL0
op_logical_and
id|n
OL
id|SGINT_GIO
)paren
(brace
id|enable_local_irq
c_func
(paren
id|n
op_minus
id|SGINT_LOCAL0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_GIO
op_logical_and
id|n
OL
id|SGINT_HPCDMA
)paren
(brace
id|enable_gio_irq
c_func
(paren
id|n
op_minus
id|SGINT_GIO
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ge
id|SGINT_HPCDMA
op_logical_and
id|n
OL
id|SGINT_END
)paren
(brace
id|enable_hpcdma_irq
c_func
(paren
id|n
op_minus
id|SGINT_HPCDMA
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;how did I get here?&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0
multiline_comment|/*&n; * Currently unused.&n; */
r_static
r_void
id|local_unex
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Whee: unexpected local IRQ at %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_epc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;DUMP: stat0&lt;%x&gt; stat1&lt;%x&gt; vmeistat&lt;%x&gt;&bslash;n&quot;
comma
id|ioc_icontrol-&gt;istat0
comma
id|ioc_icontrol-&gt;istat1
comma
id|ioc_icontrol-&gt;vmeistat
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|local_irq_action
r_static
r_struct
id|irqaction
op_star
id|local_irq_action
(braket
l_int|24
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|setup_indy_irq
r_int
id|setup_indy_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_indy_irq: Yeee, don&squot;t know how to setup irq&lt;%d&gt; for %s  %p&bslash;n&quot;
comma
id|irq
comma
r_new
op_member_access_from_pointer
id|name
comma
r_new
op_member_access_from_pointer
id|handler
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|r4ktimer_action
r_static
r_struct
id|irqaction
id|r4ktimer_action
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;R4000 timer/counter&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|indy_berr_action
r_static
r_struct
id|irqaction
id|indy_berr_action
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;IP22 Bus Error&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
l_int|16
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|indy_berr_action
comma
op_amp
id|r4ktimer_action
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
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
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
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
id|num
op_increment
)paren
(brace
id|action
op_assign
id|irq_action
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
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
l_string|&quot;%2d: %8d %c %s&quot;
comma
id|num
comma
id|kstat.interrupts
(braket
id|num
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
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; [on-chip]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|24
suffix:semicolon
id|i
op_increment
comma
id|num
op_increment
)paren
(brace
id|action
op_assign
id|local_irq_action
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
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
l_string|&quot;%2d: %8d %c %s&quot;
comma
id|num
comma
id|kstat.interrupts
(braket
id|num
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
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; [local]&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|variable|__mips_bh_counter
id|atomic_t
id|__mips_bh_counter
suffix:semicolon
macro_line|#ifdef __SMP__
macro_line|#error Send superfluous SMP boxes to ralf@uni-koblenz.de
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)     (++local_irq_count[cpu])
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)      (--local_irq_count[cpu])
macro_line|#endif
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
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Got irq %d, press a key.&quot;
comma
id|irq
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
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
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Got irq %d, press a key.&quot;
comma
id|irq
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
l_int|NULL
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|request_local_irq
r_int
id|request_local_irq
c_func
(paren
r_int
r_int
id|lirq
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|iflags
comma
r_const
r_char
op_star
id|dname
comma
r_void
op_star
id|devid
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
id|lirq
op_sub_assign
id|SGINT_LOCAL0
suffix:semicolon
r_if
c_cond
(paren
id|lirq
op_ge
l_int|24
op_logical_or
op_logical_neg
id|func
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|action-&gt;handler
op_assign
id|func
suffix:semicolon
id|action-&gt;flags
op_assign
id|iflags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|dname
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|devid
suffix:semicolon
id|action-&gt;next
op_assign
l_int|0
suffix:semicolon
id|local_irq_action
(braket
id|lirq
)braket
op_assign
id|action
suffix:semicolon
id|enable_irq
c_func
(paren
id|lirq
op_plus
id|SGINT_LOCAL0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_local_irq
r_void
id|free_local_irq
c_func
(paren
r_int
r_int
id|lirq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
id|lirq
op_sub_assign
id|SGINT_LOCAL0
suffix:semicolon
r_if
c_cond
(paren
id|lirq
op_ge
l_int|24
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Aieee: trying to free bogus local irq %d&bslash;n&quot;
comma
id|lirq
op_plus
id|SGINT_LOCAL0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|action
op_assign
id|local_irq_action
(braket
id|lirq
)braket
suffix:semicolon
id|local_irq_action
(braket
id|lirq
)braket
op_assign
l_int|NULL
suffix:semicolon
id|disable_irq
c_func
(paren
id|lirq
op_plus
id|SGINT_LOCAL0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
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
r_void
op_star
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
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|SGINT_END
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
op_ge
id|SGINT_LOCAL0
)paren
op_logical_and
(paren
id|irq
OL
id|SGINT_GIO
)paren
)paren
(brace
r_return
id|request_local_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_return
op_minus
id|ENOMEM
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
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|retval
op_assign
id|setup_indy_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
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
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|SGINT_END
)paren
(brace
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
(paren
id|irq
op_ge
id|SGINT_LOCAL0
)paren
op_logical_and
(paren
id|irq
OL
id|SGINT_GIO
)paren
)paren
(brace
id|free_local_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
(paren
id|action
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now free it */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
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
id|set_int_vector
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
id|irq_setup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|indy_local0_irqdispatch
r_void
id|indy_local0_irqdispatch
c_func
(paren
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
suffix:semicolon
r_int
r_char
id|mask
op_assign
id|ioc_icontrol-&gt;istat0
suffix:semicolon
r_int
r_char
id|mask2
op_assign
l_int|0
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|mask
op_and_assign
id|ioc_icontrol-&gt;imask0
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|ISTAT0_LIO2
)paren
(brace
id|mask2
op_assign
id|ioc_icontrol-&gt;vmeistat
suffix:semicolon
id|mask2
op_and_assign
id|ioc_icontrol-&gt;cmeimask0
suffix:semicolon
id|irq
op_assign
id|lc2msk_to_irqnr
(braket
id|mask2
)braket
suffix:semicolon
id|action
op_assign
id|local_irq_action
(braket
id|irq
)braket
suffix:semicolon
)brace
r_else
(brace
id|irq
op_assign
id|lc0msk_to_irqnr
(braket
id|mask
)braket
suffix:semicolon
id|action
op_assign
id|local_irq_action
(braket
id|irq
)braket
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;local0_dispatch: got irq %d mask %2x mask2 %2x&bslash;n&quot;
comma
id|irq
comma
id|mask
comma
id|mask2
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|kstat.interrupts
(braket
id|irq
op_plus
l_int|16
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
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|indy_local1_irqdispatch
r_void
id|indy_local1_irqdispatch
c_func
(paren
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
suffix:semicolon
r_int
r_char
id|mask
op_assign
id|ioc_icontrol-&gt;istat1
suffix:semicolon
r_int
r_char
id|mask2
op_assign
l_int|0
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|mask
op_and_assign
id|ioc_icontrol-&gt;imask1
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|ISTAT1_LIO3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WHee: Got an LIO3 irq, winging it...&bslash;n&quot;
)paren
suffix:semicolon
id|mask2
op_assign
id|ioc_icontrol-&gt;vmeistat
suffix:semicolon
id|mask2
op_and_assign
id|ioc_icontrol-&gt;cmeimask1
suffix:semicolon
id|irq
op_assign
id|lc3msk_to_irqnr
(braket
id|ioc_icontrol-&gt;vmeistat
)braket
suffix:semicolon
id|action
op_assign
id|local_irq_action
(braket
id|irq
)braket
suffix:semicolon
)brace
r_else
(brace
id|irq
op_assign
id|lc1msk_to_irqnr
(braket
id|mask
)braket
suffix:semicolon
id|action
op_assign
id|local_irq_action
(braket
id|irq
)braket
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;local1_dispatch: got irq %d mask %2x mask2 %2x&bslash;n&quot;
comma
id|irq
comma
id|mask
comma
id|mask2
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|kstat.interrupts
(braket
id|irq
op_plus
l_int|24
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
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|indy_buserror_irq
r_void
id|indy_buserror_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|kstat.interrupts
(braket
l_int|6
)braket
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Got a bus error IRQ, shouldn&squot;t happen yet&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Spinning...&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/* Misc. crap just to keep the kernel linking... */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
r_return
l_int|0
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sgint_init
r_void
id|sgint_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_REMOTE_DEBUG
r_char
op_star
id|ctype
suffix:semicolon
macro_line|#endif
id|sgi_i2regs
op_assign
(paren
r_struct
id|sgi_int2_regs
op_star
)paren
(paren
id|KSEG1
op_plus
id|SGI_INT2_BASE
)paren
suffix:semicolon
id|sgi_i3regs
op_assign
(paren
r_struct
id|sgi_int3_regs
op_star
)paren
(paren
id|KSEG1
op_plus
id|SGI_INT3_BASE
)paren
suffix:semicolon
multiline_comment|/* Init local mask --&gt; irq tables. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_amp
l_int|0x80
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|7
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|15
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|23
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|31
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x40
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|6
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|14
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|22
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|30
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x20
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|5
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|13
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|21
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|29
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x10
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|4
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|12
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|20
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|28
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x08
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|3
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|11
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|19
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|27
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x04
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|2
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|10
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|18
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|26
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x02
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|9
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|17
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|25
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x01
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|8
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|16
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|24
suffix:semicolon
)brace
r_else
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|ioc_icontrol
op_assign
op_amp
id|sgi_i3regs-&gt;ints
suffix:semicolon
id|ioc_timers
op_assign
op_amp
id|sgi_i3regs-&gt;timers
suffix:semicolon
id|ioc_tclear
op_assign
op_amp
id|sgi_i3regs-&gt;tclear
suffix:semicolon
multiline_comment|/* Mask out all interrupts. */
id|ioc_icontrol-&gt;imask0
op_assign
l_int|0
suffix:semicolon
id|ioc_icontrol-&gt;imask1
op_assign
l_int|0
suffix:semicolon
id|ioc_icontrol-&gt;cmeimask0
op_assign
l_int|0
suffix:semicolon
id|ioc_icontrol-&gt;cmeimask1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now safe to set the exception vector. */
id|set_except_vector
c_func
(paren
l_int|0
comma
id|indyIRQ
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REMOTE_DEBUG
id|ctype
op_assign
id|prom_getcmdline
c_func
(paren
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
id|strlen
c_func
(paren
id|ctype
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ctype
(braket
id|i
)braket
op_eq
l_char|&squot;k&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;g&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|2
)braket
op_eq
l_char|&squot;d&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|3
)braket
op_eq
l_char|&squot;b&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|4
)braket
op_eq
l_char|&squot;=&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|5
)braket
op_eq
l_char|&squot;t&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|6
)braket
op_eq
l_char|&squot;t&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|7
)braket
op_eq
l_char|&squot;y&squot;
op_logical_and
id|ctype
(braket
id|i
op_plus
l_int|8
)braket
op_eq
l_char|&squot;d&squot;
op_logical_and
(paren
id|ctype
(braket
id|i
op_plus
l_int|9
)braket
op_eq
l_char|&squot;1&squot;
op_logical_or
id|ctype
(braket
id|i
op_plus
l_int|9
)braket
op_eq
l_char|&squot;2&squot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: Using serial line /dev/ttyd%d for &quot;
l_string|&quot;session&bslash;n&quot;
comma
(paren
id|ctype
(braket
id|i
op_plus
l_int|9
)braket
op_minus
l_char|&squot;0&squot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctype
(braket
id|i
op_plus
l_int|9
)braket
op_eq
l_char|&squot;1&squot;
)paren
(brace
id|rs_kgdb_hook
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ctype
(braket
id|i
op_plus
l_int|9
)braket
op_eq
l_char|&squot;2&squot;
)paren
(brace
id|rs_kgdb_hook
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: whoops bogon tty line &quot;
l_string|&quot;requested, disabling session&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
)brace
eof
