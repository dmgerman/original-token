multiline_comment|/*&n; *  linux/drivers/block/cmos-probe.c&t;Version 1.00  August 16, 1999&n; *&n; *  Copyright (C) 1994-1999  Linus Torvalds &amp; authors (see below)&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * We query CMOS about hard disks : it could be that we have a SCSI/ESDI/etc&n; * controller that is BIOS compatible with ST-506, and thus showing up in our&n; * BIOS table, but not register compatible, and therefore not present in CMOS.&n; *&n; * Furthermore, we will assume that our ST-506 drives &lt;if any&gt; are the primary&n; * drives in the system -- the ones reflected as drive 1 or 2.  The first&n; * drive is stored in the high nibble of CMOS byte 0x12, the second in the low&n; * nibble.  This will be either a 4 bit drive type or 0xf indicating use byte&n; * 0x19 for an 8 bit type, drive 1, 0x1a for drive 2 in CMOS.  A non-zero value&n; * means we have an AT controller hard disk for that drive.&n; *&n; * Of course, there is no guarantee that either drive is actually on the&n; * &quot;primary&quot; IDE interface, but we don&squot;t bother trying to sort that out here.&n; * If a drive is not actually on the primary interface, then these parameters&n; * will be ignored.  This results in the user having to supply the logical&n; * drive geometry as a boot parameter for each drive not on the primary i/f.&n; *&n; * The only &quot;perfect&quot; way to handle this would be to modify the setup.[cS] code&n; * to do BIOS calls Int13h/Fn08h and Int13h/Fn48h to get all of the drive info&n; * for us during initialization.  I have the necessary docs -- any takers?  -ml&n; */
DECL|function|probe_cmos_for_drives
r_void
id|probe_cmos_for_drives
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
macro_line|#ifdef __i386__
r_extern
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
id|byte
id|cmos_disks
comma
op_star
id|BIOS
op_assign
(paren
id|byte
op_star
)paren
op_amp
id|drive_info
suffix:semicolon
r_int
id|unit
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_PDC4030
r_if
c_cond
(paren
id|hwif-&gt;chipset
op_eq
id|ide_pdc4030
op_logical_and
id|hwif-&gt;channel
op_ne
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_PDC4030 */
id|outb_p
c_func
(paren
l_int|0x12
comma
l_int|0x70
)paren
suffix:semicolon
multiline_comment|/* specify CMOS address 0x12 */
id|cmos_disks
op_assign
id|inb_p
c_func
(paren
l_int|0x71
)paren
suffix:semicolon
multiline_comment|/* read the data from 0x12 */
multiline_comment|/* Extract drive geometry from CMOS+BIOS if not already setup */
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|MAX_DRIVES
suffix:semicolon
op_increment
id|unit
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|unit
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmos_disks
op_amp
(paren
l_int|0xf0
op_rshift
(paren
id|unit
op_star
l_int|4
)paren
)paren
)paren
op_logical_and
op_logical_neg
id|drive-&gt;present
op_logical_and
op_logical_neg
id|drive-&gt;nobios
)paren
(brace
id|drive-&gt;cyl
op_assign
id|drive-&gt;bios_cyl
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|BIOS
suffix:semicolon
id|drive-&gt;head
op_assign
id|drive-&gt;bios_head
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|2
)paren
suffix:semicolon
id|drive-&gt;sect
op_assign
id|drive-&gt;bios_sect
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|14
)paren
suffix:semicolon
id|drive-&gt;ctl
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|8
)paren
suffix:semicolon
id|drive-&gt;present
op_assign
l_int|1
suffix:semicolon
)brace
id|BIOS
op_add_assign
l_int|16
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
