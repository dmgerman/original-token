multiline_comment|/* $Id: irq.c,v 1.8 2000/02/08 02:01:17 grundler Exp $&n; *&n; * Code to handle x86 style IRQs plus some generic interrupt stuff.&n; *&n; * This is not in any way SMP-clean.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998 Ralf Baechle&n; * Copyright (C) 1999 SuSE GmbH (Author: Philipp Rumpf, prumpf@tux.org)&n; * Copyright (C) 2000 Hewlett Packard Corp (Co-Author: Grant Grundler, grundler@cup.hp.com)&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
DECL|macro|DEBUG_IRQ
macro_line|#undef DEBUG_IRQ
r_extern
r_void
id|timer_interrupt
c_func
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
suffix:semicolon
r_extern
r_void
id|ipi_interrupt
c_func
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
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
DECL|macro|DBG_IRQ
mdefine_line|#define DBG_IRQ(x...)   printk(x)
macro_line|#else /* DEBUG_IRQ */
DECL|macro|DBG_IRQ
mdefine_line|#define DBG_IRQ(x...)
macro_line|#endif /* DEBUG_IRQ */
DECL|macro|EIEM_MASK
mdefine_line|#define EIEM_MASK(irq) (1L&lt;&lt;(MAX_CPU_IRQ-IRQ_OFFSET(irq)))
DECL|macro|CLEAR_EIEM_BIT
mdefine_line|#define CLEAR_EIEM_BIT(irq) set_eiem(get_eiem() &amp; ~EIEM_MASK(irq))
DECL|macro|SET_EIEM_BIT
mdefine_line|#define SET_EIEM_BIT(irq) set_eiem(get_eiem() | EIEM_MASK(irq))
DECL|function|disable_cpu_irq
r_static
r_void
id|disable_cpu_irq
c_func
(paren
r_void
op_star
id|unused
comma
r_int
id|irq
)paren
(brace
id|CLEAR_EIEM_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|enable_cpu_irq
r_static
r_void
id|enable_cpu_irq
c_func
(paren
r_void
op_star
id|unused
comma
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
id|EIEM_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|mtctl
c_func
(paren
id|mask
comma
l_int|23
)paren
suffix:semicolon
id|SET_EIEM_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|cpu_irq_actions
r_static
r_struct
id|irqaction
id|cpu_irq_actions
(braket
id|IRQ_PER_REGION
)braket
op_assign
(brace
(braket
id|IRQ_OFFSET
c_func
(paren
id|TIMER_IRQ
)paren
)braket
(brace
id|timer_interrupt
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
(braket
id|IRQ_OFFSET
c_func
(paren
id|IPI_IRQ
)paren
)braket
(brace
id|ipi_interrupt
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;IPI&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|variable|cpu_irq_region
r_struct
id|irq_region
id|cpu_irq_region
op_assign
(brace
(brace
id|disable_cpu_irq
comma
id|enable_cpu_irq
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
(brace
op_amp
id|cpu_data
(braket
l_int|0
)braket
comma
l_string|&quot;PA-PIC&quot;
comma
id|IRQ_REG_MASK
op_or
id|IRQ_REG_DIS
comma
id|IRQ_FROM_REGION
c_func
(paren
id|CPU_IRQ_REGION
)paren
)brace
comma
id|cpu_irq_actions
)brace
suffix:semicolon
DECL|variable|irq_region
r_struct
id|irq_region
op_star
id|irq_region
(braket
id|NR_IRQ_REGS
)braket
op_assign
(brace
(braket
l_int|0
)braket
l_int|NULL
comma
multiline_comment|/* abuse will data page fault (aka code 15) */
(braket
id|CPU_IRQ_REGION
)braket
op_amp
id|cpu_irq_region
comma
)brace
suffix:semicolon
multiline_comment|/* we special-case the real IRQs here, which feels right given the relatively&n; * high cost of indirect calls.  If anyone is bored enough to benchmark this&n; * and find out whether I am right, feel free to.   prumpf */
DECL|function|mask_irq
r_static
r_inline
r_void
id|mask_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|irq
op_ne
id|TIMER_IRQ
)paren
macro_line|#endif
id|DBG_IRQ
c_func
(paren
l_string|&quot;mask_irq(%d) %d+%d&bslash;n&quot;
comma
id|irq
comma
id|IRQ_REGION
c_func
(paren
id|irq
)paren
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IRQ_REGION
c_func
(paren
id|irq
)paren
op_ne
id|CPU_IRQ_REGION
)paren
(brace
id|region
op_assign
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;data.flags
op_amp
id|IRQ_REG_MASK
)paren
(brace
id|region-&gt;ops
dot
id|mask_irq
c_func
(paren
id|region-&gt;data.dev
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|CLEAR_EIEM_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|function|unmask_irq
r_static
r_inline
r_void
id|unmask_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|irq
op_ne
id|TIMER_IRQ
)paren
macro_line|#endif
id|DBG_IRQ
c_func
(paren
l_string|&quot;unmask_irq(%d) %d+%d&bslash;n&quot;
comma
id|irq
comma
id|IRQ_REGION
c_func
(paren
id|irq
)paren
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IRQ_REGION
c_func
(paren
id|irq
)paren
op_ne
id|CPU_IRQ_REGION
)paren
(brace
id|region
op_assign
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;data.flags
op_amp
id|IRQ_REG_MASK
)paren
(brace
id|region-&gt;ops
dot
id|unmask_irq
c_func
(paren
id|region-&gt;data.dev
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|SET_EIEM_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|irq
op_ne
id|TIMER_IRQ
)paren
macro_line|#endif
id|DBG_IRQ
c_func
(paren
l_string|&quot;disable_irq(%d) %d+%d&bslash;n&quot;
comma
id|irq
comma
id|IRQ_REGION
c_func
(paren
id|irq
)paren
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|region
op_assign
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;data.flags
op_amp
id|IRQ_REG_DIS
)paren
(brace
id|region-&gt;ops
dot
id|disable_irq
c_func
(paren
id|region-&gt;data.dev
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
r_else
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|irq
op_ne
id|TIMER_IRQ
)paren
macro_line|#endif
id|DBG_IRQ
c_func
(paren
l_string|&quot;enable_irq(%d) %d+%d&bslash;n&quot;
comma
id|irq
comma
id|IRQ_REGION
c_func
(paren
id|irq
)paren
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|region
op_assign
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;data.flags
op_amp
id|IRQ_REG_DIS
)paren
(brace
id|region-&gt;ops
dot
id|enable_irq
c_func
(paren
id|region-&gt;data.dev
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
r_else
id|BUG
c_func
(paren
)paren
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
macro_line|#ifdef CONFIG_PROC_FS
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|regnr
comma
id|irq_no
suffix:semicolon
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
comma
op_star
id|mainaction
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
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
id|smp_num_cpus
suffix:semicolon
id|j
op_increment
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|j
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_for
c_loop
(paren
id|regnr
op_assign
l_int|0
suffix:semicolon
id|regnr
OL
id|NR_IRQ_REGS
suffix:semicolon
id|regnr
op_increment
)paren
(brace
id|region
op_assign
id|irq_region
(braket
id|regnr
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region
op_logical_or
op_logical_neg
id|region-&gt;action
)paren
r_continue
suffix:semicolon
id|mainaction
op_assign
id|region-&gt;action
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|MAX_CPU_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
id|action
op_assign
id|mainaction
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
op_logical_or
op_logical_neg
id|action-&gt;name
)paren
r_continue
suffix:semicolon
id|irq_no
op_assign
id|IRQ_FROM_REGION
c_func
(paren
id|regnr
)paren
op_plus
id|i
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%3d: &quot;
comma
id|irq_no
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|irq_no
)paren
)paren
suffix:semicolon
macro_line|#else
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|smp_num_cpus
suffix:semicolon
id|j
op_increment
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat.irqs
(braket
id|cpu_logical_map
c_func
(paren
id|j
)paren
)braket
(braket
id|irq_no
)braket
)paren
suffix:semicolon
macro_line|#endif
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot; %14s&quot;
comma
id|region-&gt;data.name
ques
c_cond
id|region-&gt;data.name
suffix:colon
l_string|&quot;N/A&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;  %s&quot;
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if CONFIG_SMP
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;LOC: &quot;
)paren
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
id|smp_num_cpus
suffix:semicolon
id|j
op_increment
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|apic_timer_irqs
(braket
id|cpu_logical_map
c_func
(paren
id|j
)paren
)braket
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|p
op_minus
id|buf
suffix:semicolon
macro_line|#else&t;/* CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
macro_line|#endif&t;/* CONFIG_PROC_FS */
)brace
multiline_comment|/*&n;** The following form a &quot;set&quot;: Virtual IRQ, Transaction Address, Trans Data.&n;** Respectively, these map to IRQ region+EIRR, Processor HPA, EIRR bit.&n;**&n;** To use txn_XXX() interfaces, get a Virtual IRQ first.&n;** Then use that to get the Transaction address and data.&n;*/
r_int
DECL|function|txn_alloc_irq
id|txn_alloc_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/* never return irq 0 cause that&squot;s the interval timer */
r_for
c_loop
(paren
id|irq
op_assign
l_int|1
suffix:semicolon
id|irq
op_le
id|MAX_CPU_IRQ
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_irq_region.action
(braket
id|irq
)braket
dot
id|handler
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
id|IRQ_FROM_REGION
c_func
(paren
id|CPU_IRQ_REGION
)paren
op_plus
id|irq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* unlikely, but be prepared */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|txn_claim_irq
id|txn_claim_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
op_member_access_from_pointer
id|action
(braket
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)braket
dot
id|handler
op_eq
l_int|NULL
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/* unlikely, but be prepared */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
r_int
DECL|function|txn_alloc_addr
id|txn_alloc_addr
c_func
(paren
r_int
id|virt_irq
)paren
(brace
r_struct
id|cpuinfo_parisc
op_star
id|dev
op_assign
(paren
r_struct
id|cpuinfo_parisc
op_star
)paren
(paren
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|virt_irq
)paren
)braket
op_member_access_from_pointer
id|data.dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;txn_alloc_addr(0x%x): CPU IRQ region? dev %p&bslash;n&quot;
comma
id|virt_irq
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0UL
suffix:semicolon
)brace
r_return
(paren
id|dev-&gt;txn_addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** The alloc process needs to accept a parameter to accomodate limitations&n;** of the HW/SW which use these bits:&n;** Legacy PA I/O (GSC/NIO): 5 bits (architected EIM register)&n;** V-class (EPIC):          6 bits&n;** N/L-class/A500:          8 bits (iosapic)&n;** PCI 2.2 MSI:             16 bits (I think)&n;** Existing PCI devices:    32-bits (NCR c720/ATM/GigE/HyperFabric)&n;**&n;** On the service provider side:&n;** o PA 1.1 (and PA2.0 narrow mode)     5-bits (width of EIR register)&n;** o PA 2.0 wide mode                   6-bits (per processor)&n;** o IA64                               8-bits (0-256 total)&n;**&n;** So a Legacy PA I/O device on a PA 2.0 box can&squot;t use all&n;** the bits supported by the processor...and the N/L-class&n;** I/O subsystem supports more bits than PA2.0 has. The first&n;** case is the problem.&n;*/
r_int
r_int
DECL|function|txn_alloc_data
id|txn_alloc_data
c_func
(paren
r_int
id|virt_irq
comma
r_int
r_int
id|bits_wide
)paren
(brace
multiline_comment|/* XXX FIXME : bits_wide indicates how wide the transaction&n;&t;** data is allowed to be...we may need a different virt_irq&n;&t;** if this one won&squot;t work. Another reason to index virtual&n;&t;** irq&squot;s into a table which can manage CPU/IRQ bit seperately.&n;&t;*/
r_if
c_cond
(paren
id|IRQ_OFFSET
c_func
(paren
id|virt_irq
)paren
OG
(paren
l_int|1
op_lshift
(paren
id|bits_wide
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Sorry -- didn&squot;t allocate valid IRQ for this device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|IRQ_OFFSET
c_func
(paren
id|virt_irq
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: SMP, flags, bottom halves, rest */
DECL|function|do_irq
r_void
id|do_irq
c_func
(paren
r_struct
id|irqaction
op_star
id|action
comma
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
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|irq
op_ne
id|TIMER_IRQ
)paren
macro_line|#endif
id|DBG_IRQ
c_func
(paren
l_string|&quot;do_irq(%d) %d+%d&bslash;n&quot;
comma
id|irq
comma
id|IRQ_REGION
c_func
(paren
id|irq
)paren
comma
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;handler
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No handler for interrupt %d !&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|action
op_logical_and
id|action-&gt;handler
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
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
)brace
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* don&squot;t need to care about unmasking and stuff */
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_irq_mask
r_void
id|do_irq_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_struct
id|irq_region
op_star
id|region
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|bit
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IRQ
r_if
c_cond
(paren
id|mask
op_ne
(paren
l_int|1L
op_lshift
id|MAX_CPU_IRQ
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;do_irq_mask %08lx %p %p&bslash;n&quot;
comma
id|mask
comma
id|region
comma
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|bit
op_assign
(paren
l_int|1L
op_lshift
id|MAX_CPU_IRQ
)paren
comma
id|irq
op_assign
l_int|0
suffix:semicolon
id|mask
op_logical_and
id|bit
suffix:semicolon
id|bit
op_rshift_assign
l_int|1
comma
id|irq
op_increment
)paren
(brace
r_int
id|irq_num
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bit
op_amp
id|mask
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|irq_num
op_assign
id|region-&gt;data.irqbase
op_plus
id|irq
suffix:semicolon
op_increment
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|IRQ_FROM_REGION
c_func
(paren
id|CPU_IRQ_REGION
)paren
op_or
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|IRQ_REGION
c_func
(paren
id|irq_num
)paren
op_ne
id|CPU_IRQ_REGION
)paren
op_increment
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|irq_num
)braket
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq_num
)paren
suffix:semicolon
id|do_irq
c_func
(paren
op_amp
id|region-&gt;action
(braket
id|irq
)braket
comma
id|irq_num
comma
id|regs
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq_num
)paren
suffix:semicolon
)brace
)brace
DECL|function|alloc_irqregion
r_static
r_inline
r_int
id|alloc_irqregion
c_func
(paren
r_void
)paren
(brace
r_int
id|irqreg
suffix:semicolon
r_for
c_loop
(paren
id|irqreg
op_assign
l_int|1
suffix:semicolon
id|irqreg
op_le
(paren
id|NR_IRQ_REGS
)paren
suffix:semicolon
id|irqreg
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_region
(braket
id|irqreg
)braket
op_eq
l_int|NULL
)paren
(brace
r_return
id|irqreg
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_irq_region
r_struct
id|irq_region
op_star
id|alloc_irq_region
c_func
(paren
r_int
id|count
comma
r_struct
id|irq_region_ops
op_star
id|ops
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|dev
)paren
(brace
r_struct
id|irq_region
op_star
id|region
suffix:semicolon
r_int
id|index
suffix:semicolon
id|index
op_assign
id|alloc_irqregion
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|IRQ_REGION
c_func
(paren
id|count
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|IRQ_PER_REGION
)paren
(brace
id|DBG_IRQ
c_func
(paren
l_string|&quot;alloc_irq_region() using minimum of %d irq lines for %s (%d)&bslash;n&quot;
comma
id|IRQ_PER_REGION
comma
id|name
comma
id|count
)paren
suffix:semicolon
id|count
op_assign
id|IRQ_PER_REGION
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_REG_MASK
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;mask_irq
op_logical_and
id|ops-&gt;unmask_irq
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_REG_DIS
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|ops-&gt;disable_irq
op_logical_and
id|ops-&gt;enable_irq
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|irq_region
(braket
id|index
)braket
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|region
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|region
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|region-&gt;action
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|region-&gt;action
op_star
id|count
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|region-&gt;action
)paren
(brace
id|kfree
c_func
(paren
id|region
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|region-&gt;action
comma
l_int|0
comma
r_sizeof
op_star
id|region-&gt;action
op_star
id|count
)paren
suffix:semicolon
id|region-&gt;ops
op_assign
op_star
id|ops
suffix:semicolon
id|region-&gt;data.irqbase
op_assign
id|IRQ_FROM_REGION
c_func
(paren
id|index
)paren
suffix:semicolon
id|region-&gt;data.flags
op_assign
id|flags
suffix:semicolon
id|region-&gt;data.name
op_assign
id|name
suffix:semicolon
id|region-&gt;data.dev
op_assign
id|dev
suffix:semicolon
id|irq_region
(braket
id|index
)braket
op_assign
id|region
suffix:semicolon
r_return
id|irq_region
(braket
id|index
)braket
suffix:semicolon
)brace
multiline_comment|/* FIXME: SMP, flags, bottom halves, rest */
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
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;request_irq(%d, %p, 0x%lx, %s, %p)&bslash;n&quot;
comma
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
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_irq(%d,...): Augh! No handler for irq!&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|IRQ_REGION
c_func
(paren
id|irq
)paren
op_eq
l_int|0
)paren
op_logical_or
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;** Bug catcher for drivers which use &quot;char&quot; or u8 for&n;&t;&t;** the IRQ number. They lose the region number which&n;&t;&t;** is in pcidev-&gt;irq (an int).&n;&t;&t;*/
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%p (%s?) called request_irq with an invalid irq %d&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|devname
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|action
op_assign
op_amp
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
op_member_access_from_pointer
id|action
(braket
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;handler
)paren
(brace
r_while
c_loop
(paren
id|action-&gt;next
)paren
(brace
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
id|action-&gt;next
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|action
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_irq():Augh! No action!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|enable_irq
c_func
(paren
id|irq
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
id|action
op_assign
op_amp
id|irq_region
(braket
id|IRQ_REGION
c_func
(paren
id|irq
)paren
)braket
op_member_access_from_pointer
id|action
(braket
id|IRQ_OFFSET
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;dev_id
op_eq
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;next
op_eq
l_int|NULL
)paren
(brace
id|action-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|action
comma
id|action-&gt;next
comma
r_sizeof
op_star
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|action-&gt;next
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
r_for
c_loop
(paren
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
op_star
id|p
op_assign
id|action-&gt;next
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
id|KERN_ERR
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
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
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
)brace
eof
