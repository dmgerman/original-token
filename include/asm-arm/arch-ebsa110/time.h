multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/time.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * No real time clock on the evalulation board!&n; *&n; * Changelog:&n; *  10-Oct-1996&t;RMK&t;Created&n; *  04-Dec-1997&t;RMK&t;Updated for new arch/arm/kernel/time.c&n; *  07-Aug-1998&t;RMK&t;Updated for arch/arm/kernel/leds.c&n; *  28-Dec-1998&t;APH&t;Made leds code optional&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
DECL|macro|MCLK_47_8
mdefine_line|#define MCLK_47_8
macro_line|#if defined(MCLK_42_3)
DECL|macro|PIT1_COUNT
mdefine_line|#define PIT1_COUNT 0xecbe
macro_line|#elif defined(MCLK_47_8)
multiline_comment|/*&n; * This should be 0x10B43, but that doesn&squot;t exactly fit.&n; * We run the timer interrupt at 5ms, and then divide it by&n; * two in software...  This is so that the user processes&n; * see exactly the same model whichever ARM processor they&squot;re&n; * running on.&n; */
DECL|macro|PIT1_COUNT
mdefine_line|#define PIT1_COUNT 0x85A1
DECL|macro|DIVISOR
mdefine_line|#define DIVISOR 2
macro_line|#endif
DECL|function|timer_interrupt
r_static
r_void
id|timer_interrupt
c_func
(paren
r_int
id|irq
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
op_star
id|PIT_T1
op_assign
(paren
id|PIT1_COUNT
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|PIT_T1
op_assign
(paren
id|PIT1_COUNT
)paren
op_rshift
l_int|8
suffix:semicolon
macro_line|#ifdef DIVISOR
(brace
r_static
r_int
r_int
id|divisor
suffix:semicolon
r_if
c_cond
(paren
id|divisor
op_decrement
)paren
r_return
suffix:semicolon
id|divisor
op_assign
id|DIVISOR
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|setup_timer
r_extern
id|__inline__
r_void
id|setup_timer
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Timer 1, mode 0, 16-bit, autoreload&n;&t; */
op_star
id|PIT_CTRL
op_assign
l_int|0x70
suffix:semicolon
multiline_comment|/*&n;&t; * Refresh counter clocked at 47.8MHz/7 = 146.4ns&n;&t; * We want centi-second interrupts&n;&t; */
op_star
id|PIT_T1
op_assign
(paren
id|PIT1_COUNT
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|PIT_T1
op_assign
(paren
id|PIT1_COUNT
)paren
op_rshift
l_int|8
suffix:semicolon
id|timer_irq.handler
op_assign
id|timer_interrupt
suffix:semicolon
id|setup_arm_irq
c_func
(paren
id|IRQ_EBSA110_TIMER0
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
eof
