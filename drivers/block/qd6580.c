multiline_comment|/*&n; *  linux/drivers/block/qd6580.c       Version 0.02  Feb 09, 1996&n; *&n; *  Copyright (C) 1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; * QDI QD6580 EIDE controller fast support by Colten Edwards.&n; * No net access, but (maybe) can be reached at pje120@cs.usask.ca&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO           /* most systems can safely undef this */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide.h&quot;
macro_line|#include &quot;ide_modes.h&quot;
multiline_comment|/*&n; * Register 0xb3 looks like:&n; *&t;0x4f is fast&t;&t;mode3 ?&n; *&t;0x3f is medium&t;&t;mode2 ?&n; *&t;0x2f is slower&t;&t;mode1 ?&n; *&t;0x1f is slower yet&t;mode0 ?&n; *&t;0x0f ???&t;&t;???&n; *&n; * Don&squot;t know whether this sets BOTH drives, or just the first drive.&n; * Don&squot;t know if there is a separate setting for the second drive.&n; *&n; * Feel free to patch this if you have one of these beasts&n; * and can work out the answers!&n; *&n; * I/O ports are 0xb0 0xb2 and 0xb3&n; */
DECL|function|tune_qd6580
r_static
r_void
id|tune_qd6580
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
id|pio
op_assign
id|ide_get_best_pio_mode
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|3
)paren
id|pio
op_assign
l_int|3
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x8d
comma
l_int|0xb0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0
comma
l_int|0xb2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
(paren
id|pio
op_plus
l_int|1
)paren
op_lshift
l_int|4
)paren
op_or
l_int|0x0f
comma
l_int|0xb3
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|init_qd6580
r_void
id|init_qd6580
(paren
r_void
)paren
(brace
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_qd6580
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_qd6580
suffix:semicolon
)brace
eof
