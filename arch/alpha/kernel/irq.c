multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/irq.c&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ    8
macro_line|#ifdef CONFIG_RTC
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ  0        /* timer is the pit */
macro_line|#else
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ  RTC_IRQ  /* the timer is, in fact, the rtc */
macro_line|#endif
macro_line|#if NR_IRQS &gt; 64
macro_line|#  error Unable to handle more than 64 irq levels.
macro_line|#endif
multiline_comment|/* Reserved interrupts.  These must NEVER be requested by any driver!&n; */
DECL|macro|IS_RESERVED_IRQ
mdefine_line|#define&t;IS_RESERVED_IRQ(irq)&t;((irq)==2)&t;/* IRQ 2 used by hw cascade */
multiline_comment|/*&n; * Shadow-copy of masked interrupts.&n; *  The bits are used as follows:&n; *&t; 0.. 7&t;first (E)ISA PIC (irq level 0..7)&n; *&t; 8..15&t;second (E)ISA PIC (irq level 8..15)&n; *   Systems with PCI interrupt lines managed by GRU (e.g., Alcor, XLT):&n; *&t;16..47&t;PCI interrupts 0..31 (int at GRU_INT_MASK)&n; *   Mikasa:&n; *&t;16..31&t;PCI interrupts 0..15 (short at I/O port 536)&n; *   Other systems (not Mikasa) with 16 PCI interrupt lines:&n; *&t;16..23&t;PCI interrupts 0.. 7 (char at I/O port 26)&n; *&t;24..31&t;PCI interrupts 8..15 (char at I/O port 27)&n; *   Systems with 17 PCI interrupt lines (e.g., Cabriolet and eb164):&n; *&t;16..32&t;PCI interrupts 0..31 (int at I/O port 804)&n; */
DECL|variable|irq_mask
r_static
r_int
r_int
id|irq_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
multiline_comment|/*&n; * Update the hardware with the irq mask passed in MASK.  The function&n; * exploits the fact that it is known that only bit IRQ has changed.&n; */
DECL|function|update_hw
r_static
r_void
id|update_hw
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
)paren
(brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
macro_line|#if NR_IRQS == 48
r_default
suffix:colon
multiline_comment|/* note inverted sense of mask bits: */
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_MASK
op_assign
op_complement
(paren
id|mask
op_rshift
l_int|16
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#elif NR_IRQS == 33
r_default
suffix:colon
id|outl
c_func
(paren
id|mask
op_rshift
l_int|16
comma
l_int|0x804
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_MIKASA)
r_default
suffix:colon
id|outw
c_func
(paren
op_complement
(paren
id|mask
op_rshift
l_int|16
)paren
comma
l_int|0x536
)paren
suffix:semicolon
multiline_comment|/* note invert */
r_break
suffix:semicolon
macro_line|#elif NR_IRQS == 32
r_case
l_int|16
dot
dot
dot
l_int|23
suffix:colon
id|outb
c_func
(paren
id|mask
op_rshift
l_int|16
comma
l_int|0x26
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|outb
c_func
(paren
id|mask
op_rshift
l_int|24
comma
l_int|0x27
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
multiline_comment|/* handle ISA irqs last---fast devices belong on PCI... */
r_case
l_int|0
dot
dot
dot
l_int|7
suffix:colon
multiline_comment|/* ISA PIC1 */
id|outb
c_func
(paren
id|mask
comma
l_int|0x21
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
dot
dot
dot
l_int|15
suffix:colon
multiline_comment|/* ISA PIC2 */
id|outb
c_func
(paren
id|mask
op_rshift
l_int|8
comma
l_int|0xA1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|mask_irq
r_static
r_inline
r_void
id|mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_mask
op_or_assign
(paren
l_int|1UL
op_lshift
id|irq
)paren
suffix:semicolon
id|update_hw
c_func
(paren
id|irq
comma
id|irq_mask
)paren
suffix:semicolon
)brace
DECL|function|unmask_irq
r_static
r_inline
r_void
id|unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|irq
)paren
suffix:semicolon
id|update_hw
c_func
(paren
id|irq
comma
id|irq_mask
)paren
suffix:semicolon
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
id|flags
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
id|mask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initial irq handlers.&n; */
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
id|NR_IRQS
)braket
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
id|NR_IRQS
suffix:semicolon
id|i
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
l_string|&quot;%2d: %10u %c %s&quot;
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|ack_irq
r_static
r_inline
r_void
id|ack_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
OL
l_int|16
)paren
(brace
multiline_comment|/* ACK the interrupt making it the lowest priority */
multiline_comment|/*  First the slave .. */
r_if
c_cond
(paren
id|irq
OG
l_int|7
)paren
(brace
id|outb
c_func
(paren
l_int|0xE0
op_or
(paren
id|irq
op_minus
l_int|8
)paren
comma
l_int|0xa0
)paren
suffix:semicolon
id|irq
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* .. then the master */
id|outb
c_func
(paren
l_int|0xE0
op_or
id|irq
comma
l_int|0x20
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_ALCOR) || defined(CONFIG_ALPHA_XLT)
multiline_comment|/* on ALCOR/XLT, need to dismiss interrupt via GRU */
op_star
(paren
r_int
op_star
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0x80000000
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0x00000000
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* ALCOR || XLT */
)brace
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
id|shared
op_assign
l_int|0
suffix:semicolon
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
id|NR_IRQS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|IS_RESERVED_IRQ
c_func
(paren
id|irq
)paren
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
id|p
op_assign
id|irq_action
op_plus
id|irq
suffix:semicolon
id|action
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|irqflags
op_amp
id|SA_SHIRQ
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Can&squot;t share interrupts unless both are same type */
r_if
c_cond
(paren
(paren
id|action-&gt;flags
op_xor
id|irqflags
)paren
op_amp
id|SA_INTERRUPT
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|action-&gt;next
suffix:semicolon
id|action
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_eq
id|TIMER_IRQ
)paren
id|action
op_assign
op_amp
id|timer_irq
suffix:semicolon
r_else
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
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|rand_initialize_irq
c_func
(paren
id|irq
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
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
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
op_star
id|p
op_assign
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
id|unmask_irq
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
id|NR_IRQS
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
id|IS_RESERVED_IRQ
c_func
(paren
id|irq
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free reserved IRQ %d&bslash;n&quot;
comma
id|irq
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
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq
(braket
id|irq_action
)braket
)paren
id|mask_irq
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
DECL|function|handle_nmi
r_static
r_inline
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
l_string|&quot;Whee.. NMI received. Probable hardware error&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;61=%02x, 461=%02x&bslash;n&quot;
comma
id|inb
c_func
(paren
l_int|0x61
)paren
comma
id|inb
c_func
(paren
l_int|0x461
)paren
)paren
suffix:semicolon
)brace
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__alpha_bh_counter
id|atomic_t
id|__alpha_bh_counter
suffix:semicolon
macro_line|#ifdef __SMP__
macro_line|#error Me no hablo Alpha SMP
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;(++local_irq_count[cpu])
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;(--local_irq_count[cpu])
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
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
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
l_string|&quot;PC = %016lx PS=%04lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;ps
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
(paren
id|action
op_assign
id|irq_action
(braket
id|i
)braket
)paren
)paren
r_while
c_loop
(paren
id|action-&gt;handler
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[%s:%d] &quot;
comma
id|action-&gt;name
comma
id|i
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_JENSEN)
id|printk
c_func
(paren
l_string|&quot;64=%02x, 60=%02x, 3fa=%02x 2fa=%02x&bslash;n&quot;
comma
id|inb
c_func
(paren
l_int|0x64
)paren
comma
id|inb
c_func
(paren
l_int|0x60
)paren
comma
id|inb
c_func
(paren
l_int|0x3fa
)paren
comma
id|inb
c_func
(paren
l_int|0x2fa
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0c
comma
l_int|0x3fc
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0c
comma
l_int|0x2fc
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x61
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x461
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|handle_irq
r_static
r_inline
r_void
id|handle_irq
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
id|irq_action
(braket
id|irq
)braket
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
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
)brace
r_else
(brace
r_do
(brace
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
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
)brace
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|device_interrupt
r_static
r_inline
r_void
id|device_interrupt
c_func
(paren
r_int
id|irq
comma
r_int
id|ack
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
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|irq
OG
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;device_interrupt: unexpected interrupt %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|irq_enter
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * For normal interrupts, we mask it out, and then ACK it.&n;&t; * This way another (more timing-critical) interrupt can&n;&t; * come through while we&squot;re doing this one.&n;&t; *&n;&t; * Note! A irq without a handler gets masked and acked, but&n;&t; * never unmasked. The autoirq stuff depends on this (it looks&n;&t; * at the masks before and after doing the probing).&n;&t; */
id|mask_irq
c_func
(paren
id|ack
)paren
suffix:semicolon
id|ack_irq
c_func
(paren
id|ack
)paren
suffix:semicolon
r_if
c_cond
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
r_do
(brace
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
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|ack
)paren
suffix:semicolon
)brace
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n; * Handle ISA interrupt via the PICs.&n; */
DECL|function|isa_device_interrupt
r_static
r_inline
r_void
id|isa_device_interrupt
c_func
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
macro_line|#if defined(CONFIG_ALPHA_APECS)
DECL|macro|IACK_SC
macro_line|#&t;define IACK_SC&t;APECS_IACK_SC
macro_line|#elif defined(CONFIG_ALPHA_LCA)
macro_line|#&t;define IACK_SC&t;LCA_IACK_SC
macro_line|#elif defined(CONFIG_ALPHA_CIA)
macro_line|#&t;define IACK_SC&t;CIA_IACK_SC
macro_line|#else
multiline_comment|/*&n;&t; * This is bogus but necessary to get it to compile&n;&t; * on all platforms.  If you try to use this on any&n;&t; * other than the intended platforms, you&squot;ll notice&n;&t; * real fast...&n;&t; */
macro_line|#&t;define IACK_SC&t;1L
macro_line|#endif
r_int
id|j
suffix:semicolon
macro_line|#if 1
multiline_comment|/*&n;&t; * Generate a PCI interrupt acknowledge cycle.  The PIC will&n;&t; * respond with the interrupt vector of the highest priority&n;&t; * interrupt that is pending.  The PALcode sets up the&n;&t; * interrupts vectors such that irq level L generates vector&n;&t; * L.&n;&t; */
id|j
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
id|IACK_SC
suffix:semicolon
id|j
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
l_int|7
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|0x80
)paren
)paren
(brace
multiline_comment|/* it&squot;s only a passive release... */
r_return
suffix:semicolon
)brace
)brace
id|device_interrupt
c_func
(paren
id|j
comma
id|j
comma
id|regs
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|pic
suffix:semicolon
multiline_comment|/*&n;&t; * It seems to me that the probability of two or more *device*&n;&t; * interrupts occurring at almost exactly the same time is&n;&t; * pretty low.  So why pay the price of checking for&n;&t; * additional interrupts here if the common case can be&n;&t; * handled so much easier?&n;&t; */
multiline_comment|/* &n;&t; *  The first read of gives you *all* interrupting lines.&n;&t; *  Therefore, read the mask register and and out those lines&n;&t; *  not enabled.  Note that some documentation has 21 and a1 &n;&t; *  write only.  This is not true.&n;&t; */
id|pic
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0xA0
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* read isr */
id|pic
op_and_assign
op_complement
id|irq_mask
suffix:semicolon
multiline_comment|/* apply mask */
id|pic
op_and_assign
l_int|0xFFFB
suffix:semicolon
multiline_comment|/* mask out cascade &amp; hibits */
r_while
c_loop
(paren
id|pic
)paren
(brace
id|j
op_assign
id|ffz
c_func
(paren
op_complement
id|pic
)paren
suffix:semicolon
id|pic
op_and_assign
id|pic
op_minus
l_int|1
suffix:semicolon
id|device_interrupt
c_func
(paren
id|j
comma
id|j
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_ALPHA_ALCOR) || defined(CONFIG_ALPHA_XLT)
multiline_comment|/* we have to conditionally compile this because of GRU_xxx symbols */
DECL|function|alcor_and_xlt_device_interrupt
r_static
r_inline
r_void
id|alcor_and_xlt_device_interrupt
c_func
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
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* read the interrupt summary register of the GRU */
id|pld
op_assign
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_REQ
)paren
op_amp
id|GRU_INT_REQ_BITS
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[0x%08lx/0x%04x]&quot;
comma
id|pld
comma
id|inb
c_func
(paren
l_int|0x20
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0xA0
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;         * Now for every possible bit set, work through them and call&n;         * the appropriate interrupt handler.&n;         */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|31
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|device_interrupt
c_func
(paren
l_int|16
op_plus
id|i
comma
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* ALCOR || XLT */
DECL|function|cabriolet_and_eb66p_device_interrupt
r_static
r_inline
r_void
id|cabriolet_and_eb66p_device_interrupt
c_func
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
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* read the interrupt summary registers */
id|pld
op_assign
id|inb
c_func
(paren
l_int|0x804
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x805
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x806
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[0x%04X/0x%04X]&quot;
comma
id|pld
comma
id|inb
c_func
(paren
l_int|0x20
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0xA0
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Now for every possible bit set, work through them and call&n;&t; * the appropriate interrupt handler.&n;&t; */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|4
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|device_interrupt
c_func
(paren
l_int|16
op_plus
id|i
comma
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|mikasa_device_interrupt
r_static
r_inline
r_void
id|mikasa_device_interrupt
c_func
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
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* read the interrupt summary registers */
id|pld
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
(paren
op_complement
id|inw
c_func
(paren
l_int|0x534
)paren
)paren
op_amp
l_int|0x0000ffffUL
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|inb
c_func
(paren
l_int|0xa0
)paren
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|inb
c_func
(paren
l_int|0x20
)paren
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[0x%08lx]&quot;
comma
id|pld
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;         * Now for every possible bit set, work through them and call&n;         * the appropriate interrupt handler.&n;         */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
OL
l_int|16
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|device_interrupt
c_func
(paren
id|i
comma
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|eb66_and_eb64p_device_interrupt
r_static
r_inline
r_void
id|eb66_and_eb64p_device_interrupt
c_func
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
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* read the interrupt summary registers */
id|pld
op_assign
id|inb
c_func
(paren
l_int|0x26
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x27
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, for every possible bit set, work through&n;&t; * them and call the appropriate interrupt handler.&n;&t; */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|5
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|device_interrupt
c_func
(paren
l_int|16
op_plus
id|i
comma
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/*&n; * Jensen is special: the vector is 0x8X0 for EISA interrupt X, and&n; * 0x9X0 for the local motherboard interrupts..&n; *&n; *&t;0x660 - NMI&n; *&n; *&t;0x800 - IRQ0  interval timer (not used, as we use the RTC timer)&n; *&t;0x810 - IRQ1  line printer (duh..)&n; *&t;0x860 - IRQ6  floppy disk&n; *&t;0x8E0 - IRQ14 SCSI controller&n; *&n; *&t;0x900 - COM1&n; *&t;0x920 - COM2&n; *&t;0x980 - keyboard&n; *&t;0x990 - mouse&n; *&n; * PCI-based systems are more sane: they don&squot;t have the local&n; * interrupts at all, and have only normal PCI interrupts from&n; * devices.  Happily it&squot;s easy enough to do a sane mapping from the&n; * Jensen..  Note that this means that we may have to do a hardware&n; * &quot;ack&quot; to a different interrupt than we report to the rest of the&n; * world.&n; */
DECL|function|srm_device_interrupt
r_static
r_inline
r_void
id|srm_device_interrupt
c_func
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
id|irq
comma
id|ack
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ack
op_assign
id|irq
op_assign
(paren
id|vector
op_minus
l_int|0x800
)paren
op_rshift
l_int|4
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_JENSEN
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
l_int|0x660
suffix:colon
id|handle_nmi
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* local device interrupts: */
r_case
l_int|0x900
suffix:colon
id|handle_irq
c_func
(paren
l_int|4
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* com1 -&gt; irq 4 */
r_case
l_int|0x920
suffix:colon
id|handle_irq
c_func
(paren
l_int|3
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* com2 -&gt; irq 3 */
r_case
l_int|0x980
suffix:colon
id|handle_irq
c_func
(paren
l_int|1
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* kbd -&gt; irq 1 */
r_case
l_int|0x990
suffix:colon
id|handle_irq
c_func
(paren
l_int|9
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* mouse -&gt; irq 9 */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|vector
OG
l_int|0x900
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unknown local interrupt %lx&bslash;n&quot;
comma
id|vector
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* irq1 is supposed to be the keyboard, silly Jensen (is this really needed??) */
r_if
c_cond
(paren
id|irq
op_eq
l_int|1
)paren
id|irq
op_assign
l_int|7
suffix:semicolon
macro_line|#endif /* CONFIG_ALPHA_JENSEN */
id|device_interrupt
c_func
(paren
id|irq
comma
id|ack
comma
id|regs
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start listening for interrupts..&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|irqs
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
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
(brace
id|enable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
id|irqs
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Wait about 100ms for spurious interrupts to mask themselves&n;&t; * out again...&n;&t; */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|delay
OG
id|jiffies
suffix:semicolon
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* now filter out any obviously spurious interrupts */
r_return
id|irqs
op_amp
op_complement
id|irq_mask
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the result of the IRQ probe.. A negative result means that&n; * we have several candidates (but we return the lowest-numbered&n; * one).&n; */
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|irqs
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* as irq 0 &amp; 8 handling don&squot;t use this function, i didn&squot;t&n;&t; * bother changing the following: */
id|irqs
op_and_assign
id|irq_mask
op_amp
op_complement
l_int|1
suffix:semicolon
multiline_comment|/* always mask out irq 0---it&squot;s the unused timer */
macro_line|#ifdef CONFIG_ALPHA_P2K
id|irqs
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* mask out irq 8 since that&squot;s the unused RTC input to PIC */
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|irqs
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|irqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqs
op_ne
(paren
l_int|1UL
op_lshift
id|i
)paren
)paren
id|i
op_assign
op_minus
id|i
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|machine_check
r_static
r_void
id|machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if defined(CONFIG_ALPHA_LCA)
r_extern
r_void
id|lca_machine_check
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|lca_machine_check
c_func
(paren
id|vector
comma
id|la
comma
id|regs
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_APECS)
r_extern
r_void
id|apecs_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|apecs_machine_check
c_func
(paren
id|vector
comma
id|la
comma
id|regs
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_CIA)
r_extern
r_void
id|cia_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|cia_machine_check
c_func
(paren
id|vector
comma
id|la
comma
id|regs
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;Machine check&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|do_entInt
id|asmlinkage
r_void
id|do_entInt
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Interprocessor interrupt? You must be kidding&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|handle_irq
c_func
(paren
id|RTC_IRQ
comma
op_amp
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
id|machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
op_amp
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
macro_line|#if defined(CONFIG_ALPHA_JENSEN) || defined(CONFIG_ALPHA_NONAME) || &bslash;&n;    defined(CONFIG_ALPHA_P2K) || defined(CONFIG_ALPHA_SRM)
id|srm_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#elif NR_IRQS == 48
id|alcor_and_xlt_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#elif NR_IRQS == 33
id|cabriolet_and_eb66p_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_MIKASA)
id|mikasa_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#elif NR_IRQS == 32
id|eb66_and_eb64p_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#elif NR_IRQS == 16
id|isa_device_interrupt
c_func
(paren
id|vector
comma
op_amp
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Performance counter interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Hardware intr %ld %lx? Huh?&bslash;n&quot;
comma
id|type
comma
id|vector
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PC = %016lx PS=%04lx&bslash;n&quot;
comma
id|regs.pc
comma
id|regs.ps
)paren
suffix:semicolon
)brace
r_extern
id|asmlinkage
r_void
id|entInt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_IRQ
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
id|wrent
c_func
(paren
id|entInt
comma
l_int|0
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA1_RESET_REG
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA2_RESET_REG
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA1_CLR_MASK_REG
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA2_CLR_MASK_REG
)paren
suffix:semicolon
macro_line|#if NR_IRQS == 48
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_MASK
op_assign
op_complement
(paren
id|irq_mask
op_rshift
l_int|16
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* invert */
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_EDGE
op_assign
l_int|0UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all are level */
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_HILO
op_assign
l_int|0x80000000UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ISA only HI */
op_star
(paren
r_int
r_int
op_star
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all clear */
id|enable_irq
c_func
(paren
l_int|16
op_plus
l_int|31
)paren
suffix:semicolon
multiline_comment|/* enable (E)ISA PIC cascade */
macro_line|#elif NR_IRQS == 33
id|outl
c_func
(paren
id|irq_mask
op_rshift
l_int|16
comma
l_int|0x804
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|16
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* enable SIO cascade */
macro_line|#elif defined(CONFIG_ALPHA_MIKASA)
id|outw
c_func
(paren
op_complement
(paren
id|irq_mask
op_rshift
l_int|16
)paren
comma
l_int|0x536
)paren
suffix:semicolon
multiline_comment|/* note invert */
macro_line|#elif NR_IRQS == 32
id|outb
c_func
(paren
id|irq_mask
op_rshift
l_int|16
comma
l_int|0x26
)paren
suffix:semicolon
id|outb
c_func
(paren
id|irq_mask
op_rshift
l_int|24
comma
l_int|0x27
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|16
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* enable SIO cascade */
macro_line|#endif
id|enable_irq
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* enable cascade */
)brace
eof
