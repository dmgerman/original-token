multiline_comment|/*&n; * linux/include/asm-arm/arch-vnc/system.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; * Copyright (c) 1998 Corel Computer Corp.&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/dec21285.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* open up the SuperIO chip&n;&t; */
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
multiline_comment|/* aux function group 1 (Logical Device 7)&n;&t; */
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
multiline_comment|/* set GP16 for WD-TIMER output&n;&t; */
id|outb
c_func
(paren
l_int|0xE6
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
multiline_comment|/* set a RED LED and toggle WD_TIMER for rebooting...&n;&t; */
id|outb
c_func
(paren
l_int|0xC4
comma
l_int|0x338
)paren
suffix:semicolon
)brace
DECL|macro|arch_start_idle
mdefine_line|#define arch_start_idle()&t;leds_event(led_idle_start)
DECL|macro|arch_end_idle
mdefine_line|#define arch_end_idle()&t;&t;leds_event(led_idle_end)
eof
