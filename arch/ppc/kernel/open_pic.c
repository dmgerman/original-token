multiline_comment|/*&n; *  arch/ppc/kernel/openpic.c -- OpenPIC Interrupt Handling&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &quot;local_irq.h&quot;
DECL|variable|OpenPIC
r_volatile
r_struct
id|OpenPIC
op_star
id|OpenPIC
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
id|u_int
id|OpenPIC_NumInitSenses
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
id|u_char
op_star
id|OpenPIC_InitSenses
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|open_pic_irq_offset
r_int
id|open_pic_irq_offset
suffix:semicolon
r_extern
r_int
id|use_of_interrupt_tree
suffix:semicolon
r_void
id|chrp_mask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|chrp_unmask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|find_ISUs
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|NumProcessors
r_static
id|u_int
id|NumProcessors
suffix:semicolon
DECL|variable|NumSources
r_static
id|u_int
id|NumSources
suffix:semicolon
DECL|variable|ISU
id|OpenPIC_Source
op_star
id|ISU
suffix:semicolon
multiline_comment|/*&n; * We should use this if we have &gt; 1 ISU.&n; * We can just point each entry to the&n; * appropriate source regs but it wastes a lot of space&n; * so until we have &gt;1 ISU I&squot;ll leave it unimplemented.&n; * -- Cort&n;OpenPIC_Source ISU[128];&n;*/
DECL|variable|open_pic
r_struct
id|hw_interrupt_type
id|open_pic
op_assign
(brace
l_string|&quot; OpenPIC  &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|openpic_enable_irq
comma
id|openpic_disable_irq
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; *  Accesses to the current processor&squot;s registers&n; */
macro_line|#ifndef __powerpc__
DECL|macro|THIS_CPU
mdefine_line|#define THIS_CPU&t;&t;Private
DECL|macro|CHECK_THIS_CPU
mdefine_line|#define CHECK_THIS_CPU&t;&t;do {} while (0)
macro_line|#else
DECL|macro|THIS_CPU
mdefine_line|#define THIS_CPU&t;&t;Processor[cpu]
DECL|macro|CHECK_THIS_CPU
mdefine_line|#define CHECK_THIS_CPU&t;&t;check_arg_cpu(cpu)
macro_line|#endif
macro_line|#if 1
DECL|macro|check_arg_ipi
mdefine_line|#define check_arg_ipi(ipi) &bslash;&n;    if (ipi &lt; 0 || ipi &gt;= OPENPIC_NUM_IPI) &bslash;&n;&t;printk(&quot;openpic.c:%d: illegal ipi %d&bslash;n&quot;, __LINE__, ipi);
DECL|macro|check_arg_timer
mdefine_line|#define check_arg_timer(timer) &bslash;&n;    if (timer &lt; 0 || timer &gt;= OPENPIC_NUM_TIMERS) &bslash;&n;&t;printk(&quot;openpic.c:%d: illegal timer %d&bslash;n&quot;, __LINE__, timer);
DECL|macro|check_arg_vec
mdefine_line|#define check_arg_vec(vec) &bslash;&n;    if (vec &lt; 0 || vec &gt;= OPENPIC_NUM_VECTORS) &bslash;&n;&t;printk(&quot;openpic.c:%d: illegal vector %d&bslash;n&quot;, __LINE__, vec);
DECL|macro|check_arg_pri
mdefine_line|#define check_arg_pri(pri) &bslash;&n;    if (pri &lt; 0 || pri &gt;= OPENPIC_NUM_PRI) &bslash;&n;&t;printk(&quot;openpic.c:%d: illegal priority %d&bslash;n&quot;, __LINE__, pri);
multiline_comment|/*&n; * I changed this to return to keep us from from trying to use irq #&squot;s&n; * that we&squot;re using for IPI&squot;s.&n; *   -- Cort&n; */
DECL|macro|check_arg_irq
mdefine_line|#define check_arg_irq(irq) &bslash;&n;    /*if (irq &lt; 0 || irq &gt;= (NumSources+open_pic_irq_offset)) &bslash;&n;      printk(&quot;openpic.c:%d: illegal irq %d&bslash;n&quot;, __LINE__, irq);*/
DECL|macro|check_arg_cpu
mdefine_line|#define check_arg_cpu(cpu) &bslash;&n;    if (cpu &lt; 0 || cpu &gt;= NumProcessors) &bslash;&n;&t;printk(&quot;openpic.c:%d: illegal cpu %d&bslash;n&quot;, __LINE__, cpu);
macro_line|#else
DECL|macro|check_arg_ipi
mdefine_line|#define check_arg_ipi(ipi)&t;do {} while (0)
DECL|macro|check_arg_timer
mdefine_line|#define check_arg_timer(timer)&t;do {} while (0)
DECL|macro|check_arg_vec
mdefine_line|#define check_arg_vec(vec)&t;do {} while (0)
DECL|macro|check_arg_pri
mdefine_line|#define check_arg_pri(pri)&t;do {} while (0)
DECL|macro|check_arg_irq
mdefine_line|#define check_arg_irq(irq)&t;do {} while (0)
DECL|macro|check_arg_cpu
mdefine_line|#define check_arg_cpu(cpu)&t;do {} while (0)
macro_line|#endif
DECL|function|no_action
r_static
r_void
id|no_action
c_func
(paren
r_int
id|ir1
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
macro_line|#ifdef __SMP__
DECL|function|openpic_ipi_action
r_void
id|openpic_ipi_action
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|smp_message_recv
c_func
(paren
id|cpl
op_minus
id|OPENPIC_VEC_IPI
)paren
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
macro_line|#ifdef __i386__
DECL|function|in_le32
r_static
r_inline
id|u_int
id|in_le32
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|function|out_le32
r_static
r_inline
r_void
id|out_le32
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|val
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
macro_line|#endif
DECL|function|openpic_read
id|u_int
id|openpic_read
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
)paren
(brace
id|u_int
id|val
suffix:semicolon
id|val
op_assign
id|in_le32
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|openpic_write
r_static
r_inline
r_void
id|openpic_write
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|openpic_readfield
r_static
r_inline
id|u_int
id|openpic_readfield
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|mask
)paren
(brace
id|u_int
id|val
op_assign
id|openpic_read
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|val
op_amp
id|mask
suffix:semicolon
)brace
DECL|function|openpic_writefield
r_inline
r_void
id|openpic_writefield
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|mask
comma
id|u_int
id|field
)paren
(brace
id|u_int
id|val
op_assign
id|openpic_read
c_func
(paren
id|addr
)paren
suffix:semicolon
id|openpic_write
c_func
(paren
id|addr
comma
(paren
id|val
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|field
op_amp
id|mask
)paren
)paren
suffix:semicolon
)brace
DECL|function|openpic_clearfield
r_static
r_inline
r_void
id|openpic_clearfield
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|mask
)paren
(brace
id|openpic_writefield
c_func
(paren
id|addr
comma
id|mask
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|openpic_setfield
r_static
r_inline
r_void
id|openpic_setfield
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|mask
)paren
(brace
id|openpic_writefield
c_func
(paren
id|addr
comma
id|mask
comma
id|mask
)paren
suffix:semicolon
)brace
DECL|function|openpic_safe_writefield
r_static
r_void
id|openpic_safe_writefield
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
comma
id|u_int
id|mask
comma
id|u_int
id|field
)paren
(brace
id|openpic_setfield
c_func
(paren
id|addr
comma
id|OPENPIC_MASK
)paren
suffix:semicolon
multiline_comment|/* wait until it&squot;s not in use */
multiline_comment|/* BenH: Is this code really enough ? I would rather check the result&n;&t; *       and eventually retry ...&n;&t; */
r_while
c_loop
(paren
id|openpic_read
c_func
(paren
id|addr
)paren
op_amp
id|OPENPIC_ACTIVITY
)paren
suffix:semicolon
id|openpic_writefield
c_func
(paren
id|addr
comma
id|mask
op_or
id|OPENPIC_MASK
comma
id|field
op_or
id|OPENPIC_MASK
)paren
suffix:semicolon
)brace
DECL|function|openpic_init
r_void
id|__init
id|openpic_init
c_func
(paren
r_int
id|main_pic
)paren
(brace
id|u_int
id|t
comma
id|i
suffix:semicolon
id|u_int
id|timerfreq
suffix:semicolon
r_const
r_char
op_star
id|version
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|OpenPIC
)paren
id|panic
c_func
(paren
l_string|&quot;No OpenPIC found&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic enter&quot;
comma
l_int|0x122
)paren
suffix:semicolon
id|t
op_assign
id|openpic_read
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Feature_Reporting0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|t
op_amp
id|OPENPIC_FEATURE_VERSION_MASK
)paren
(brace
r_case
l_int|1
suffix:colon
id|version
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|version
op_assign
l_string|&quot;1.2&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|version
op_assign
l_string|&quot;1.3&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|version
op_assign
l_string|&quot;?&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|NumProcessors
op_assign
(paren
(paren
id|t
op_amp
id|OPENPIC_FEATURE_LAST_PROCESSOR_MASK
)paren
op_rshift
id|OPENPIC_FEATURE_LAST_PROCESSOR_SHIFT
)paren
op_plus
l_int|1
suffix:semicolon
id|NumSources
op_assign
(paren
(paren
id|t
op_amp
id|OPENPIC_FEATURE_LAST_SOURCE_MASK
)paren
op_rshift
id|OPENPIC_FEATURE_LAST_SOURCE_SHIFT
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OpenPIC Version %s (%d CPUs and %d IRQ sources) at %p&bslash;n&quot;
comma
id|version
comma
id|NumProcessors
comma
id|NumSources
comma
id|OpenPIC
)paren
suffix:semicolon
id|timerfreq
op_assign
id|openpic_read
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Timer_Frequency
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OpenPIC timer frequency is &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timerfreq
)paren
id|printk
c_func
(paren
l_string|&quot;%d MHz&bslash;n&quot;
comma
id|timerfreq
op_rshift
l_int|20
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;not set&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|main_pic
)paren
(brace
multiline_comment|/* Initialize timer interrupts */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic timer&quot;
comma
l_int|0x3ba
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
id|OPENPIC_NUM_TIMERS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Disabled, Priority 0 */
id|openpic_inittimer
c_func
(paren
id|i
comma
l_int|0
comma
id|OPENPIC_VEC_TIMER
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* No processor */
id|openpic_maptimer
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize IPI interrupts */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic ipi&quot;
comma
l_int|0x3bb
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
id|OPENPIC_NUM_IPI
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Disabled, Priority 8 */
id|openpic_initipi
c_func
(paren
id|i
comma
l_int|8
comma
id|OPENPIC_VEC_IPI
op_plus
id|i
)paren
suffix:semicolon
)brace
id|find_ISUs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
(brace
multiline_comment|/* Initialize external interrupts */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic ext&quot;
comma
l_int|0x3bc
)paren
suffix:semicolon
multiline_comment|/* SIOint (8259 cascade) is special */
id|openpic_initirq
c_func
(paren
l_int|0
comma
l_int|8
comma
id|open_pic_irq_offset
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|openpic_mapirq
c_func
(paren
l_int|0
comma
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NumSources
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Enabled, Priority 8 */
id|openpic_initirq
c_func
(paren
id|i
comma
l_int|8
comma
id|open_pic_irq_offset
op_plus
id|i
comma
l_int|0
comma
id|i
OL
id|OpenPIC_NumInitSenses
ques
c_cond
id|OpenPIC_InitSenses
(braket
id|i
)braket
suffix:colon
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Processor 0 */
id|openpic_mapirq
c_func
(paren
id|i
comma
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Prevent any interrupt from occuring during initialisation.&n;&t;&t;&t; * Hum... I believe this is not necessary, Apple does that in&n;&t;&t;&t; * Darwin&squot;s PowerExpress code.&n;&t;&t;&t; */
id|openpic_set_priority
c_func
(paren
l_int|0
comma
l_int|0xf
)paren
suffix:semicolon
multiline_comment|/* First disable all interrupts and map them to CPU 0 */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NumSources
suffix:semicolon
id|i
op_increment
)paren
(brace
id|openpic_disable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
id|openpic_mapirq
c_func
(paren
id|i
comma
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* If we use the device tree, then lookup all interrupts and&n;&t;&t;&t; * initialize them according to sense infos found in the tree&n;&t;&t;&t; */
r_if
c_cond
(paren
id|use_of_interrupt_tree
)paren
(brace
r_struct
id|device_node
op_star
id|np
op_assign
id|find_all_nodes
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|np
)paren
(brace
r_int
id|j
comma
id|pri
suffix:semicolon
id|pri
op_assign
id|strcmp
c_func
(paren
id|np-&gt;name
comma
l_string|&quot;programmer-switch&quot;
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|7
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|np-&gt;n_intrs
suffix:semicolon
id|j
op_increment
)paren
id|openpic_initirq
c_func
(paren
id|np-&gt;intrs
(braket
id|j
)braket
dot
id|line
comma
id|pri
comma
id|np-&gt;intrs
(braket
id|j
)braket
dot
id|line
comma
id|np-&gt;intrs
(braket
id|j
)braket
dot
id|sense
comma
id|np-&gt;intrs
(braket
id|j
)braket
dot
id|sense
)paren
suffix:semicolon
id|np
op_assign
id|np-&gt;next
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Initialize the spurious interrupt */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic spurious&quot;
comma
l_int|0x3bd
)paren
suffix:semicolon
id|openpic_set_spurious
c_func
(paren
id|OPENPIC_VEC_SPURIOUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|_machine
op_logical_and
(paren
id|_MACH_gemini
op_or
id|_MACH_Pmac
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_8259_CASCADE
comma
id|no_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;82c59 cascade&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get OpenPIC IRQ 0 for cascade&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|openpic_set_priority
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|openpic_disable_8259_pass_through
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;openpic exit&quot;
comma
l_int|0x222
)paren
suffix:semicolon
)brace
DECL|function|find_ISUs
r_void
id|find_ISUs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC64
multiline_comment|/* hardcode this for now since the IBM 260 is the only thing with&n;&t; * a distributed openpic right now.  -- Cort&n;&t; */
id|ISU
op_assign
(paren
id|OpenPIC_Source
op_star
)paren
l_int|0xfeff7c00
suffix:semicolon
id|NumSources
op_assign
l_int|0x10
suffix:semicolon
macro_line|#else
multiline_comment|/* for non-distributed OpenPIC implementations it&squot;s in the IDU -- Cort */
id|ISU
op_assign
id|OpenPIC-&gt;Source
suffix:semicolon
macro_line|#endif
)brace
DECL|function|openpic_reset
r_void
id|openpic_reset
c_func
(paren
r_void
)paren
(brace
id|openpic_setfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Global_Configuration0
comma
id|OPENPIC_CONFIG_RESET
)paren
suffix:semicolon
)brace
DECL|function|openpic_enable_8259_pass_through
r_void
id|openpic_enable_8259_pass_through
c_func
(paren
r_void
)paren
(brace
id|openpic_clearfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Global_Configuration0
comma
id|OPENPIC_CONFIG_8259_PASSTHROUGH_DISABLE
)paren
suffix:semicolon
)brace
DECL|function|openpic_disable_8259_pass_through
r_void
id|openpic_disable_8259_pass_through
c_func
(paren
r_void
)paren
(brace
id|openpic_setfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Global_Configuration0
comma
id|OPENPIC_CONFIG_8259_PASSTHROUGH_DISABLE
)paren
suffix:semicolon
)brace
macro_line|#ifndef __i386__
multiline_comment|/*&n; *  Find out the current interrupt&n; */
DECL|function|openpic_irq
id|u_int
id|openpic_irq
c_func
(paren
id|u_int
id|cpu
)paren
(brace
id|u_int
id|vec
suffix:semicolon
id|check_arg_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|vec
op_assign
id|openpic_readfield
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU.Interrupt_Acknowledge
comma
id|OPENPIC_VECTOR_MASK
)paren
suffix:semicolon
r_return
id|vec
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __powerpc__
DECL|function|openpic_eoi
r_void
id|openpic_eoi
c_func
(paren
r_void
)paren
macro_line|#else
r_void
id|openpic_eoi
c_func
(paren
id|u_int
id|cpu
)paren
macro_line|#endif
(brace
id|check_arg_cpu
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|openpic_write
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU.EOI
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Handle PCI write posting */
(paren
r_void
)paren
id|openpic_read
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU.EOI
)paren
suffix:semicolon
)brace
macro_line|#ifndef __powerpc__
DECL|function|openpic_get_priority
id|u_int
id|openpic_get_priority
c_func
(paren
r_void
)paren
macro_line|#else
id|u_int
id|openpic_get_priority
c_func
(paren
id|u_int
id|cpu
)paren
macro_line|#endif
(brace
id|CHECK_THIS_CPU
suffix:semicolon
r_return
id|openpic_readfield
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU.Current_Task_Priority
comma
id|OPENPIC_CURRENT_TASK_PRIORITY_MASK
)paren
suffix:semicolon
)brace
macro_line|#ifndef __powerpc__
DECL|function|openpic_set_priority
r_void
id|openpic_set_priority
c_func
(paren
id|u_int
id|pri
)paren
macro_line|#else
r_void
id|openpic_set_priority
c_func
(paren
id|u_int
id|cpu
comma
id|u_int
id|pri
)paren
macro_line|#endif
(brace
id|CHECK_THIS_CPU
suffix:semicolon
id|check_arg_pri
c_func
(paren
id|pri
)paren
suffix:semicolon
id|openpic_writefield
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU.Current_Task_Priority
comma
id|OPENPIC_CURRENT_TASK_PRIORITY_MASK
comma
id|pri
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get/set the spurious vector&n; */
DECL|function|openpic_get_spurious
id|u_int
id|openpic_get_spurious
c_func
(paren
r_void
)paren
(brace
r_return
id|openpic_readfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Spurious_Vector
comma
id|OPENPIC_VECTOR_MASK
)paren
suffix:semicolon
)brace
DECL|function|openpic_set_spurious
r_void
id|openpic_set_spurious
c_func
(paren
id|u_int
id|vec
)paren
(brace
id|check_arg_vec
c_func
(paren
id|vec
)paren
suffix:semicolon
id|openpic_writefield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Spurious_Vector
comma
id|OPENPIC_VECTOR_MASK
comma
id|vec
)paren
suffix:semicolon
)brace
DECL|function|openpic_init_processor
r_void
id|openpic_init_processor
c_func
(paren
id|u_int
id|cpumask
)paren
(brace
id|openpic_write
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Processor_Initialization
comma
id|cpumask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialize an interprocessor interrupt (and disable it)&n; *&n; *  ipi: OpenPIC interprocessor interrupt number&n; *  pri: interrupt source priority&n; *  vec: the vector it will produce&n; */
DECL|function|openpic_initipi
r_void
id|openpic_initipi
c_func
(paren
id|u_int
id|ipi
comma
id|u_int
id|pri
comma
id|u_int
id|vec
)paren
(brace
id|check_arg_timer
c_func
(paren
id|ipi
)paren
suffix:semicolon
id|check_arg_pri
c_func
(paren
id|pri
)paren
suffix:semicolon
id|check_arg_vec
c_func
(paren
id|vec
)paren
suffix:semicolon
id|openpic_safe_writefield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global
dot
id|IPI_Vector_Priority
c_func
(paren
id|ipi
)paren
comma
id|OPENPIC_PRIORITY_MASK
op_or
id|OPENPIC_VECTOR_MASK
comma
(paren
id|pri
op_lshift
id|OPENPIC_PRIORITY_SHIFT
)paren
op_or
id|vec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Send an IPI to one or more CPUs&n; */
macro_line|#ifndef __powerpc__
DECL|function|openpic_cause_IPI
r_void
id|openpic_cause_IPI
c_func
(paren
id|u_int
id|ipi
comma
id|u_int
id|cpumask
)paren
macro_line|#else
r_void
id|openpic_cause_IPI
c_func
(paren
id|u_int
id|cpu
comma
id|u_int
id|ipi
comma
id|u_int
id|cpumask
)paren
macro_line|#endif
(brace
id|CHECK_THIS_CPU
suffix:semicolon
id|check_arg_ipi
c_func
(paren
id|ipi
)paren
suffix:semicolon
id|openpic_write
c_func
(paren
op_amp
id|OpenPIC-&gt;THIS_CPU
dot
id|IPI_Dispatch
c_func
(paren
id|ipi
)paren
comma
id|cpumask
)paren
suffix:semicolon
)brace
DECL|function|openpic_enable_IPI
r_void
id|openpic_enable_IPI
c_func
(paren
id|u_int
id|ipi
)paren
(brace
id|check_arg_ipi
c_func
(paren
id|ipi
)paren
suffix:semicolon
id|openpic_clearfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global
dot
id|IPI_Vector_Priority
c_func
(paren
id|ipi
)paren
comma
id|OPENPIC_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do per-cpu setup for SMP systems.&n; *&n; * Get IPI&squot;s working and start taking interrupts.&n; *   -- Cort&n;  */
DECL|function|do_openpic_setup_cpu
r_void
id|do_openpic_setup_cpu
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
id|OPENPIC_NUM_IPI
suffix:semicolon
id|i
op_increment
)paren
id|openpic_enable_IPI
c_func
(paren
id|i
)paren
suffix:semicolon
macro_line|#if 0&t;
multiline_comment|/* let the openpic know we want intrs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NumSources
suffix:semicolon
id|i
op_increment
)paren
id|openpic_mapirq
c_func
(paren
id|i
comma
id|openpic_read
c_func
(paren
id|ISU
(braket
id|i
)braket
dot
id|Destination
)paren
op_or
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif&t;
id|openpic_set_priority
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialize a timer interrupt (and disable it)&n; *&n; *  timer: OpenPIC timer number&n; *  pri: interrupt source priority&n; *  vec: the vector it will produce&n; */
DECL|function|openpic_inittimer
r_void
id|openpic_inittimer
c_func
(paren
id|u_int
id|timer
comma
id|u_int
id|pri
comma
id|u_int
id|vec
)paren
(brace
id|check_arg_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|check_arg_pri
c_func
(paren
id|pri
)paren
suffix:semicolon
id|check_arg_vec
c_func
(paren
id|vec
)paren
suffix:semicolon
id|openpic_safe_writefield
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Timer
(braket
id|timer
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_PRIORITY_MASK
op_or
id|OPENPIC_VECTOR_MASK
comma
(paren
id|pri
op_lshift
id|OPENPIC_PRIORITY_SHIFT
)paren
op_or
id|vec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Map a timer interrupt to one or more CPUs&n; */
DECL|function|openpic_maptimer
r_void
id|openpic_maptimer
c_func
(paren
id|u_int
id|timer
comma
id|u_int
id|cpumask
)paren
(brace
id|check_arg_timer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|openpic_write
c_func
(paren
op_amp
id|OpenPIC-&gt;Global.Timer
(braket
id|timer
)braket
dot
id|Destination
comma
id|cpumask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Enable/disable an interrupt source&n; */
DECL|function|openpic_enable_irq
r_void
id|openpic_enable_irq
c_func
(paren
id|u_int
id|irq
)paren
(brace
id|check_arg_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|openpic_clearfield
c_func
(paren
op_amp
id|ISU
(braket
id|irq
op_minus
id|open_pic_irq_offset
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_MASK
)paren
suffix:semicolon
multiline_comment|/* make sure mask gets to controller before we return to user */
r_do
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* sync is probably useless here */
)brace
r_while
c_loop
(paren
id|openpic_readfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Source
(braket
id|irq
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_MASK
)paren
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|openpic_disable_irq
r_void
id|openpic_disable_irq
c_func
(paren
id|u_int
id|irq
)paren
(brace
id|check_arg_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|openpic_setfield
c_func
(paren
op_amp
id|ISU
(braket
id|irq
op_minus
id|open_pic_irq_offset
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_MASK
)paren
suffix:semicolon
multiline_comment|/* make sure mask gets to controller before we return to user */
r_do
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* sync is probably useless here */
)brace
r_while
c_loop
(paren
op_logical_neg
id|openpic_readfield
c_func
(paren
op_amp
id|OpenPIC-&gt;Source
(braket
id|irq
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_MASK
)paren
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Initialize an interrupt source (and disable it!)&n; *&n; *  irq: OpenPIC interrupt number&n; *  pri: interrupt source priority&n; *  vec: the vector it will produce&n; *  pol: polarity (1 for positive, 0 for negative)&n; *  sense: 1 for level, 0 for edge&n; */
DECL|function|openpic_initirq
r_void
id|openpic_initirq
c_func
(paren
id|u_int
id|irq
comma
id|u_int
id|pri
comma
id|u_int
id|vec
comma
r_int
id|pol
comma
r_int
id|sense
)paren
(brace
id|check_arg_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|check_arg_pri
c_func
(paren
id|pri
)paren
suffix:semicolon
id|check_arg_vec
c_func
(paren
id|vec
)paren
suffix:semicolon
id|openpic_safe_writefield
c_func
(paren
op_amp
id|ISU
(braket
id|irq
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_PRIORITY_MASK
op_or
id|OPENPIC_VECTOR_MASK
op_or
id|OPENPIC_SENSE_MASK
op_or
id|OPENPIC_POLARITY_MASK
comma
(paren
id|pri
op_lshift
id|OPENPIC_PRIORITY_SHIFT
)paren
op_or
id|vec
op_or
(paren
id|pol
ques
c_cond
id|OPENPIC_POLARITY_POSITIVE
suffix:colon
id|OPENPIC_POLARITY_NEGATIVE
)paren
op_or
(paren
id|sense
ques
c_cond
id|OPENPIC_SENSE_LEVEL
suffix:colon
id|OPENPIC_SENSE_EDGE
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Map an interrupt source to one or more CPUs&n; */
DECL|function|openpic_mapirq
r_void
id|openpic_mapirq
c_func
(paren
id|u_int
id|irq
comma
id|u_int
id|cpumask
)paren
(brace
id|check_arg_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|openpic_write
c_func
(paren
op_amp
id|ISU
(braket
id|irq
)braket
dot
id|Destination
comma
id|cpumask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Set the sense for an interrupt source (and disable it!)&n; *&n; *  sense: 1 for level, 0 for edge&n; */
DECL|function|openpic_set_sense
r_void
id|openpic_set_sense
c_func
(paren
id|u_int
id|irq
comma
r_int
id|sense
)paren
(brace
id|check_arg_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|openpic_safe_writefield
c_func
(paren
op_amp
id|ISU
(braket
id|irq
)braket
dot
id|Vector_Priority
comma
id|OPENPIC_SENSE_LEVEL
comma
(paren
id|sense
ques
c_cond
id|OPENPIC_SENSE_LEVEL
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
eof
