multiline_comment|/*&n; * linux/arch/ia64/kernel/irq.c&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 1999-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; *  6/10/99: Updated to bring in sync with x86 version to facilitate&n; *&t;     support for SMP and different interrupt controllers.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/random.h&gt;&t;/* for rand_initialize_irq() */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#ifdef CONFIG_KDB
macro_line|# include &lt;linux/kdb.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_ITANIUM_ASTEP_SPECIFIC
DECL|variable|ivr_read_lock
id|spinlock_t
id|ivr_read_lock
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Legacy IRQ to IA-64 vector translation table.  Any vector not in&n; * this table maps to itself (ie: irq 0x30 =&gt; IA64 vector 0x30)&n; */
DECL|variable|isa_irq_to_vector_map
id|__u8
id|isa_irq_to_vector_map
(braket
id|IA64_MIN_VECTORED_IRQ
)braket
op_assign
(brace
multiline_comment|/* 8259 IRQ translation, first 16 entries */
l_int|0x60
comma
l_int|0x50
comma
l_int|0x0f
comma
l_int|0x51
comma
l_int|0x52
comma
l_int|0x53
comma
l_int|0x43
comma
l_int|0x54
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x57
comma
l_int|0x58
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x40
comma
l_int|0x41
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM_ASTEP_SPECIFIC
DECL|variable|usbfix
r_int
id|usbfix
suffix:semicolon
r_static
r_int
id|__init
DECL|function|usbfix_option
id|usbfix_option
(paren
r_char
op_star
id|str
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;irq: enabling USB workaround&bslash;n&quot;
)paren
suffix:semicolon
id|usbfix
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;usbfix&quot;
comma
id|usbfix_option
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ITANIUM_ASTEP_SPECIFIC */
multiline_comment|/*&n; * That&squot;s where the IVT branches when we get an external&n; * interrupt. This branches to the correct hardware IRQ handler via&n; * function ptr.&n; */
r_void
DECL|function|ia64_handle_irq
id|ia64_handle_irq
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|bsp
comma
id|sp
comma
id|saved_tpr
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM_ASTEP_SPECIFIC
macro_line|# ifndef CONFIG_SMP
r_static
r_int
r_int
id|max_prio
op_assign
l_int|0
suffix:semicolon
macro_line|# endif
r_int
r_int
id|prev_prio
suffix:semicolon
r_int
r_int
id|eoi_ptr
suffix:semicolon
macro_line|# ifdef CONFIG_USB
r_extern
r_void
id|reenable_usb
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_usb
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usbfix
)paren
id|disable_usb
c_func
(paren
)paren
suffix:semicolon
macro_line|# endif
multiline_comment|/*&n;&t; * Stop IPIs by getting the ivr_read_lock&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|ivr_read_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable PCI writes&n;&t; */
id|outl
c_func
(paren
l_int|0x80ff81c0
comma
l_int|0xcf8
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x73002188
comma
l_int|0xcfc
)paren
suffix:semicolon
id|eoi_ptr
op_assign
id|inl
c_func
(paren
l_int|0xcfc
)paren
suffix:semicolon
id|vector
op_assign
id|ia64_get_ivr
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable PCI writes&n;&t; */
id|outl
c_func
(paren
l_int|0x73182188
comma
l_int|0xcfc
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ivr_read_lock
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_USB
r_if
c_cond
(paren
id|usbfix
)paren
id|reenable_usb
c_func
(paren
)paren
suffix:semicolon
macro_line|# endif
macro_line|# ifndef CONFIG_SMP
id|prev_prio
op_assign
id|max_prio
suffix:semicolon
r_if
c_cond
(paren
id|vector
OL
id|max_prio
)paren
(brace
id|printk
(paren
l_string|&quot;ia64_handle_irq: got vector %lu while %u was in progress!&bslash;n&quot;
comma
id|vector
comma
id|max_prio
)paren
suffix:semicolon
)brace
r_else
id|max_prio
op_assign
id|vector
suffix:semicolon
macro_line|# endif /* !CONFIG_SMP */
macro_line|#endif /* CONFIG_ITANIUM_ASTEP_SPECIFIC */
multiline_comment|/*&n;&t; * Always set TPR to limit maximum interrupt nesting depth to&n;&t; * 16 (without this, it would be ~240, which could easily lead&n;&t; * to kernel stack overflows.&n;&t; */
id|saved_tpr
op_assign
id|ia64_get_tpr
c_func
(paren
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|ia64_set_tpr
c_func
(paren
id|vector
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;mov %0=ar.bsp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bsp
)paren
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;mov %0=sp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sp
op_minus
id|bsp
)paren
OL
l_int|1024
)paren
(brace
r_static
r_int
id|last_time
suffix:semicolon
r_static
r_int
r_char
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|5
op_logical_and
id|jiffies
op_minus
id|last_time
OG
l_int|5
op_star
id|HZ
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|5
)paren
(brace
id|last_time
op_assign
id|jiffies
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ia64_handle_irq: DANGER: less than 1KB of free stack space!!&bslash;n&quot;
l_string|&quot;(bsp=0x%lx, sp=%lx)&bslash;n&quot;
comma
id|bsp
comma
id|sp
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KDB
id|kdb
c_func
(paren
id|KDB_REASON_PANIC
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
macro_line|#endif&t;&t;
)brace
multiline_comment|/*&n;&t; * The interrupt is now said to be in service&n;&t; */
r_if
c_cond
(paren
id|vector
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;handle_irq: invalid vector %lu&bslash;n&quot;
comma
id|vector
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|do_IRQ
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
id|out
suffix:colon
macro_line|#ifdef CONFIG_ITANIUM_ASTEP_SPECIFIC
(brace
r_int
id|pEOI
suffix:semicolon
id|asm
(paren
l_string|&quot;mov %0=0;; (p1) mov %0=1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pEOI
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pEOI
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Yikes: ia64_handle_irq() without pEOI!!&bslash;n&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;cmp.eq p1,p0=r0,r0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pEOI
)paren
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_KDB
id|kdb
c_func
(paren
id|KDB_REASON_PANIC
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
macro_line|# endif
)brace
)brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
macro_line|# ifndef CONFIG_SMP
r_if
c_cond
(paren
id|max_prio
op_eq
id|vector
)paren
id|max_prio
op_assign
id|prev_prio
suffix:semicolon
macro_line|# endif /* !CONFIG_SMP */
macro_line|#endif /* CONFIG_ITANIUM_ASTEP_SPECIFIC */
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|ia64_set_tpr
c_func
(paren
id|saved_tpr
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_void
id|__init
DECL|function|init_IRQ_SMP
id|init_IRQ_SMP
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IPI_IRQ
comma
id|handle_IPI
comma
l_int|0
comma
l_string|&quot;IPI&quot;
comma
l_int|NULL
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate IPI Interrupt Handler!&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
id|__init
DECL|function|init_IRQ
id|init_IRQ
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Disable all local interrupts&n;&t; */
id|ia64_set_itv
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|ia64_set_lrr0
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|ia64_set_lrr1
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|handler
op_assign
op_amp
id|irq_type_ia64_internal
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* &n;&t; * Configure the IPI vector and handler&n;&t; */
id|irq_desc
(braket
id|IPI_IRQ
)braket
dot
id|handler
op_assign
op_amp
id|irq_type_ia64_internal
suffix:semicolon
id|init_IRQ_SMP
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ia64_set_pmv
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_set_cmcv
c_func
(paren
id|CMC_IRQ
)paren
suffix:semicolon
multiline_comment|/* XXX fix me */
id|platform_irq_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clear TPR to enable all interrupt classes: */
id|ia64_set_tpr
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* TBD:&n; * &t;Certain IA64 platforms can have inter-processor interrupt support.&n; * &t;This interface is supposed to default to the IA64 IPI block-based&n; * &t;mechanism if the platform doesn&squot;t provide a separate mechanism&n; *&t;for IPIs.&n; *&t;Choices : (1) Extend hw_interrupt_type interfaces &n; *&t;&t;  (2) Use machine vector mechanism&n; *&t;For now defining the following interface as a place holder.&n; */
r_void
DECL|function|ipi_send
id|ipi_send
(paren
r_int
id|cpu
comma
r_int
id|vector
comma
r_int
id|delivery_mode
)paren
(brace
)brace
eof
