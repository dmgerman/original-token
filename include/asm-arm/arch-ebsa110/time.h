multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/time.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * No real time clock on the evalulation board!&n; *&n; * Changelog:&n; *  10-Oct-1996&t;RMK&t;Created&n; *  04-Dec-1997&t;RMK&t;Updated for new arch/arm/kernel/time.c&n; *  07-Aug-1998&t;RMK&t;Updated for arch/arm/kernel/leds.c&n; *  28-Dec-1998&t;APH&t;Made leds code optional&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER IRQ_EBSA110_TIMER0
DECL|macro|MCLK_47_8
mdefine_line|#define MCLK_47_8
macro_line|#if defined(MCLK_42_3)
DECL|macro|PIT1_COUNT
mdefine_line|#define PIT1_COUNT 0xecbe
macro_line|#elif defined(MCLK_47_8)
multiline_comment|/*&n; * This should be 0x10AE1, but that doesn&squot;t exactly fit.&n; * We run the timer interrupt at 5ms, and then divide it by&n; * two in software...  This is so that the user processes&n; * see exactly the same model whichever ARM processor they&squot;re&n; * running on.&n; */
DECL|macro|PIT1_COUNT
mdefine_line|#define PIT1_COUNT 0x8570
DECL|macro|DIVISOR
mdefine_line|#define DIVISOR 2
macro_line|#endif
DECL|function|gettimeoffset
r_extern
id|__inline__
r_int
r_int
id|gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef DIVISOR
DECL|function|reset_timer
r_extern
id|__inline__
r_int
id|reset_timer
(paren
r_void
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
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|function|reset_timer
r_extern
id|__inline__
r_int
id|reset_timer
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|divisor
suffix:semicolon
macro_line|#ifdef CONFIG_LEDS&t;
r_static
r_int
id|count
op_assign
l_int|50
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_LEDS
r_if
c_cond
(paren
op_decrement
id|count
op_eq
l_int|0
)paren
(brace
id|count
op_assign
l_int|50
suffix:semicolon
id|leds_event
c_func
(paren
id|led_timer
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|divisor
op_eq
l_int|0
)paren
(brace
id|divisor
op_assign
id|DIVISOR
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|divisor
op_sub_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * We don&squot;t have a RTC to update!&n; */
DECL|macro|update_rtc
mdefine_line|#define update_rtc()
multiline_comment|/*&n; * Set up timer interrupt, and return the current time in seconds.&n; */
DECL|function|setup_timer
r_extern
id|__inline__
r_int
r_int
id|setup_timer
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
id|reset_timer
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Default the date to 1 Jan 1970 0:0:0&n;&t; * You will have to run a time daemon to set the&n;&t; * clock correctly at bootup&n;&t; */
r_return
id|mktime
c_func
(paren
l_int|1970
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
