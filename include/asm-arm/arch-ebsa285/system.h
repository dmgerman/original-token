multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#include &lt;asm/dec21285.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle()&t;&t;cpu_do_idle()
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
DECL|function|arch_reset
r_extern
id|__inline__
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
l_char|&squot;s&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t; * Jump into the ROM&n;&t;&t; */
id|cpu_reset
c_func
(paren
l_int|0x41000000
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* open up the SuperIO chip&n;&t;&t;&t; */
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* aux function group 1 (logical device 7)&n;&t;&t;&t; */
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* set GP16 for WD-TIMER output&n;&t;&t;&t; */
id|outb
c_func
(paren
l_int|0xe6
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* set a RED LED and toggle WD_TIMER for rebooting&n;&t;&t;&t; */
id|outb
c_func
(paren
l_int|0xc4
comma
l_int|0x338
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* To reboot, we set up the 21285 watchdog and&n;&t;&t;&t; * enable it.  We then wait for it to timeout.&n;&t;&t;&t; */
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
)brace
)brace
)brace
eof
