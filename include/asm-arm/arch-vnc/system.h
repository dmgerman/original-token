multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/system.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
multiline_comment|/* To reboot, we set up the 21285 watchdog and enable it.&n; * We then wait for it to timeout.&n; */
DECL|function|arch_hard_reset
r_extern
id|__inline__
r_void
id|arch_hard_reset
(paren
r_void
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_LOAD
op_assign
l_int|0x8000
suffix:semicolon
op_star
id|CSR_TIMER4_CNTL
op_assign
id|TIMER_CNTL_ENABLE
op_or
id|TIMER_CNTL_AUTORELOAD
op_or
id|TIMER_CNTL_DIV16
suffix:semicolon
op_star
id|CSR_SA110_CNTL
op_or_assign
l_int|1
op_lshift
l_int|13
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
DECL|macro|ARCH_IDLE_OK
mdefine_line|#define ARCH_IDLE_OK
DECL|macro|arch_start_idle
mdefine_line|#define arch_start_idle()&t;leds_event(led_idle_start)
DECL|macro|arch_end_idle
mdefine_line|#define arch_end_idle()&t;&t;leds_event(led_idle_end)
eof
