multiline_comment|/*&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) Vijay Chander(vijay@engr.sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * The format of &quot;screen_info&quot; is strange, and due to early i386-setup&n; * code. This is just enough to make the console code think we&squot;re on a&n; * VGA color display.&n; */
DECL|variable|sn1_screen_info
r_struct
id|screen_info
id|sn1_screen_info
op_assign
(brace
id|orig_x
suffix:colon
l_int|0
comma
id|orig_y
suffix:colon
l_int|0
comma
id|orig_video_mode
suffix:colon
l_int|3
comma
id|orig_video_cols
suffix:colon
l_int|80
comma
id|orig_video_ega_bx
suffix:colon
l_int|3
comma
id|orig_video_lines
suffix:colon
l_int|25
comma
id|orig_video_isVGA
suffix:colon
l_int|1
comma
id|orig_video_points
suffix:colon
l_int|16
)brace
suffix:semicolon
multiline_comment|/*&n; * This is here so we can use the CMOS detection in ide-probe.c to&n; * determine what drives are present.  In theory, we don&squot;t need this&n; * as the auto-detection could be done via ide-probe.c:do_probe() but&n; * in practice that would be much slower, which is painful when&n; * running in the simulator.  Note that passing zeroes in DRIVE_INFO&n; * is sufficient (the IDE driver will autodetect the drive geometry).&n; */
DECL|variable|drive_info
r_char
id|drive_info
(braket
l_int|4
op_star
l_int|16
)braket
suffix:semicolon
r_int
r_int
DECL|function|sn1_map_nr
id|sn1_map_nr
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|MAP_NR_SN1
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
r_void
DECL|function|sn1_setup
id|sn1_setup
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0301
)paren
suffix:semicolon
multiline_comment|/* default to first IDE drive */
macro_line|#if !defined (CONFIG_IA64_SOFTSDV_HACKS)
multiline_comment|/* &n;&t; * Program the timer to deliver timer ticks.  0x40 is the I/O port&n;&t; * address of PIT counter 0, 0x43 is the I/O port address of the &n;&t; * PIT control word. &n;&t; */
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* Control word */
id|outb
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|printk
c_func
(paren
l_string|&quot;PIT: LATCH at 0x%x%x for %d HZ&bslash;n&quot;
comma
id|LATCH
op_rshift
l_int|8
comma
id|LATCH
op_amp
l_int|0xff
comma
id|HZ
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|init_smp_config
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|screen_info
op_assign
id|sn1_screen_info
suffix:semicolon
)brace
eof
