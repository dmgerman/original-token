multiline_comment|/*&n; *  linux/arch/m68k/hp300/config.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific initialisation code.  It gets&n; *  called by setup.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/blinken.h&gt;
macro_line|#include &lt;asm/io.h&gt;                               /* readb() and writeb() */
macro_line|#include &lt;asm/hwtest.h&gt;                           /* hwreg_present() */
macro_line|#include &quot;ints.h&quot;
macro_line|#include &quot;time.h&quot;
r_extern
r_void
id|hp300_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hp300_hil_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|function|hp300_pulse
r_static
r_void
id|hp300_pulse
c_func
(paren
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
id|x
)paren
id|blinken_leds
c_func
(paren
l_int|0xfe
)paren
suffix:semicolon
r_else
id|blinken_leds
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|hp300_kbdrate
r_static
r_int
id|hp300_kbdrate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|k
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp300_kbd_leds
r_static
r_void
id|hp300_kbd_leds
c_func
(paren
r_int
r_int
id|leds
)paren
(brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|config_hp300
c_func
(paren
r_void
)paren
)paren
(brace
id|mach_sched_init
op_assign
id|hp300_sched_init
suffix:semicolon
id|mach_keyb_init
op_assign
id|hp300_hil_init
suffix:semicolon
id|mach_kbdrate
op_assign
id|hp300_kbdrate
suffix:semicolon
id|mach_kbd_leds
op_assign
id|hp300_kbd_leds
suffix:semicolon
id|mach_init_IRQ
op_assign
id|hp300_init_IRQ
suffix:semicolon
id|mach_request_irq
op_assign
id|hp300_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|hp300_free_irq
suffix:semicolon
macro_line|#if 0
id|mach_get_model
op_assign
id|hp300_get_model
suffix:semicolon
id|mach_get_irq_list
op_assign
id|hp300_get_irq_list
suffix:semicolon
macro_line|#endif
id|mach_gettimeoffset
op_assign
id|hp300_gettimeoffset
suffix:semicolon
macro_line|#if 0
id|mach_gettod
op_assign
id|hp300_gettod
suffix:semicolon
macro_line|#endif
id|mach_reset
op_assign
id|hp300_reset
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
id|mach_heartbeat
op_assign
id|hp300_pulse
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB
id|conswitchp
op_assign
op_amp
id|fb_con
suffix:semicolon
macro_line|#endif
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
multiline_comment|/* for &quot;kbd-reset&quot; cmdline param */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|kbd_reset_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
)paren
(brace
)brace
eof