multiline_comment|/*&n; *  linux/drivers/block/dtc2278.c       Version 0.02  Feb 10, 1996&n; *&n; *  Copyright (C) 1996  Linus Torvalds &amp; author (see below)&n; */
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
multiline_comment|/*&n; * Changing this #undef to #define may solve start up problems in some systems.&n; */
DECL|macro|ALWAYS_SET_DTC2278_PIO_MODE
macro_line|#undef ALWAYS_SET_DTC2278_PIO_MODE
multiline_comment|/*&n; * From: andy@cercle.cts.com (Dyan Wile)&n; *&n; * Below is a patch for DTC-2278 - alike software-programmable controllers&n; * The code enables the secondary IDE controller and the PIO4 (3?) timings on&n; * the primary (EIDE). You may probably have to enable the 32-bit support to&n; * get the full speed. You better get the disk interrupts disabled ( hdparm -u0&n; * /dev/hd.. ) for the drives connected to the EIDE interface. (I get my&n; * filesystem  corrupted with -u1, but under heavy disk load only :-)&n; *&n; * This card is now forced to use the &quot;serialize&quot; feature,&n; * and irq-unmasking is disallowed.  If io_32bit is enabled,&n; * it must be done for BOTH drives on each interface.&n; *&n; * This code was written for the DTC2278E, but might work with any of these:&n; *&n; * DTC2278S has only a single IDE interface.&n; * DTC2278D has two IDE interfaces and is otherwise identical to the S version.&n; * DTC2278E has onboard BIOS, while the others do not.&n; *&n; * There may be a fourth controller type. The S and D versions use the&n; * Winbond chip, and I think the E version does also.&n; *&n; */
DECL|function|sub22
r_static
r_void
id|sub22
(paren
r_char
id|b
comma
r_char
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
op_increment
id|i
)paren
(brace
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|b
comma
l_int|0xb0
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|c
comma
l_int|0xb4
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
l_int|0xb4
)paren
op_eq
id|c
)paren
(brace
id|outb_p
c_func
(paren
l_int|7
comma
l_int|0xb0
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* success */
)brace
)brace
)brace
DECL|function|tune_dtc2278
r_static
r_void
id|tune_dtc2278
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
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_ge
l_int|3
)paren
(brace
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
multiline_comment|/*&n;&t;&t; * This enables PIO mode4 (3?) on the first interface&n;&t;&t; */
id|sub22
c_func
(paren
l_int|1
comma
l_int|0xc3
)paren
suffix:semicolon
id|sub22
c_func
(paren
l_int|0
comma
l_int|0xa0
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we don&squot;t know how to set it back again.. */
)brace
multiline_comment|/*&n;&t; * 32bit I/O has to be enabled for *both* drives at the same time.&n;&t; */
id|drive-&gt;io_32bit
op_assign
l_int|1
suffix:semicolon
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drives
(braket
op_logical_neg
id|drive-&gt;select.b.unit
)braket
dot
id|io_32bit
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|init_dtc2278
r_void
id|init_dtc2278
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
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
multiline_comment|/*&n;&t; * This enables the second interface&n;&t; */
id|outb_p
c_func
(paren
l_int|4
comma
l_int|0xb0
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x20
comma
l_int|0xb4
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0x3f6
)paren
suffix:semicolon
macro_line|#ifdef ALWAYS_SET_DTC2278_PIO_MODE
multiline_comment|/*&n;&t; * This enables PIO mode4 (3?) on the first interface&n;&t; * and may solve start-up problems for some people.&n;&t; */
id|sub22
c_func
(paren
l_int|1
comma
l_int|0xc3
)paren
suffix:semicolon
id|sub22
c_func
(paren
l_int|0
comma
l_int|0xa0
)paren
suffix:semicolon
macro_line|#endif
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_dtc2278
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_assign
id|ide_dtc2278
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_dtc2278
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
)brace
eof
