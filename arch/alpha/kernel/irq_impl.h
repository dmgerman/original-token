multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/irq.h&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * This file contains declarations and inline functions for interfacing&n; * with the IRQ handling routines in irq.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|STANDARD_INIT_IRQ_PROLOG
mdefine_line|#define STANDARD_INIT_IRQ_PROLOG&t;&bslash;&n;&t;outb(0, DMA1_RESET_REG);&t;&bslash;&n;&t;outb(0, DMA2_RESET_REG);&t;&bslash;&n;&t;outb(0, DMA1_CLR_MASK_REG);&t;&bslash;&n;&t;outb(0, DMA2_CLR_MASK_REG)
r_extern
r_int
r_int
id|_alpha_irq_masks
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|alpha_irq_mask
mdefine_line|#define alpha_irq_mask _alpha_irq_masks[0]
r_extern
r_void
id|common_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|handle_irq
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
suffix:semicolon
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ    8
macro_line|#ifdef CONFIG_RTC
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ  0&t;&t;&t; /* timer is the pit */
macro_line|#else
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ  RTC_IRQ&t;&t; /* timer is the rtc */
macro_line|#endif
multiline_comment|/*&n; * PROBE_MASK is the bitset of irqs that we consider for autoprobing.&n; */
multiline_comment|/* NOTE: we only handle the first 64 IRQs in this code. */
multiline_comment|/* The normal mask includes all the IRQs except timer IRQ 0.  */
DECL|macro|_PROBE_MASK
mdefine_line|#define _PROBE_MASK(nr_irqs)&t;&bslash;&n;&t;(((nr_irqs &gt; 63) ? ~0UL : ((1UL &lt;&lt; (nr_irqs &amp; 63)) - 1)) &amp; ~1UL)
multiline_comment|/* Mask out unused timer irq 0 and RTC irq 8. */
DECL|macro|P2K_PROBE_MASK
mdefine_line|#define P2K_PROBE_MASK&t;&t;(_PROBE_MASK(16) &amp; ~0x101UL)
multiline_comment|/* Mask out unused timer irq 0, &quot;irqs&quot; 20-30, and the EISA cascade. */
DECL|macro|ALCOR_PROBE_MASK
mdefine_line|#define ALCOR_PROBE_MASK&t;(_PROBE_MASK(48) &amp; ~0xfff000000001UL)
multiline_comment|/* Leave timer IRQ 0 in the mask.  */
DECL|macro|RUFFIAN_PROBE_MASK
mdefine_line|#define RUFFIAN_PROBE_MASK&t;(_PROBE_MASK(48) | 1UL)
multiline_comment|/* Do not probe/enable beyond the PCI devices. */
DECL|macro|TSUNAMI_PROBE_MASK
mdefine_line|#define TSUNAMI_PROBE_MASK&t;_PROBE_MASK(48)
macro_line|#if defined(CONFIG_ALPHA_GENERIC)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;alpha_mv.irq_probe_mask
macro_line|#elif defined(CONFIG_ALPHA_P2K)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;P2K_PROBE_MASK
macro_line|#elif defined(CONFIG_ALPHA_ALCOR) || defined(CONFIG_ALPHA_XLT)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;ALCOR_PROBE_MASK
macro_line|#elif defined(CONFIG_ALPHA_RUFFIAN)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;RUFFIAN_PROBE_MASK
macro_line|#elif defined(CONFIG_ALPHA_DP264)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;TSUNAMI_PROBE_MASK
macro_line|#else
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;_PROBE_MASK(NR_IRQS)
macro_line|#endif
r_extern
r_char
id|_stext
suffix:semicolon
DECL|function|alpha_do_profile
r_static
r_inline
r_void
id|alpha_do_profile
(paren
r_int
r_int
id|pc
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
id|pc
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|pc
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t ignore out-of-bounds PC values silently,&n;&t;&t; * put them into the last histogram slot, so if&n;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t; */
r_if
c_cond
(paren
id|pc
OG
id|prof_len
op_minus
l_int|1
)paren
id|pc
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
id|pc
)braket
)paren
suffix:semicolon
)brace
)brace
eof
