multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/irq.h&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * This file contains declarations and inline functions for interfacing&n; * with the IRQ handling routines in irq.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|STANDARD_INIT_IRQ_PROLOG
mdefine_line|#define STANDARD_INIT_IRQ_PROLOG&t;&bslash;&n;&t;outb(0, DMA1_RESET_REG);&t;&bslash;&n;&t;outb(0, DMA2_RESET_REG);&t;&bslash;&n;&t;outb(0, DMA1_CLR_MASK_REG);&t;&bslash;&n;&t;outb(0, DMA2_CLR_MASK_REG)
r_extern
r_int
r_int
id|alpha_irq_mask
suffix:semicolon
r_extern
r_void
id|generic_ack_irq
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
eof
