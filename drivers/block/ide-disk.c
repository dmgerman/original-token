multiline_comment|/*&n; *  linux/drivers/block/ide-disk.c&t;Version 1.0  Oct   6, 1996&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors (see below)&n; */
multiline_comment|/*&n; *  Maintained by Mark Lord  &lt;mlord@pobox.com&gt;&n; *            and Gadi Oxman &lt;gadio@netvision.net.il&gt;&n; *&n; * This is the IDE/ATA disk driver, as evolved from hd.c and ide.c.&n; *&n; *  From hd.c:&n; *  |&n; *  | It traverses the request-list, using interrupts to jump between functions.&n; *  | As nearly all functions can be called within interrupts, we may not sleep.&n; *  | Special care is recommended.  Have Fun!&n; *  |&n; *  | modified by Drew Eckhardt to check nr of hd&squot;s from the CMOS.&n; *  |&n; *  | Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug&n; *  | in the early extended-partition checks and added DM partitions.&n; *  |&n; *  | Early work on error handling by Mika Liljeberg (liljeber@cs.Helsinki.FI).&n; *  |&n; *  | IRQ-unmask, drive-id, multiple-mode, support for &quot;&gt;16 heads&quot;,&n; *  | and general streamlining by Mark Lord (mlord@pobox.com).&n; *&n; *  October, 1994 -- Complete line-by-line overhaul for linux 1.1.x, by:&n; *&n; *&t;Mark Lord&t;(mlord@pobox.com)&t;&t;(IDE Perf.Pkg)&n; *&t;Delman Lee&t;(delman@mipg.upenn.edu)&t;&t;(&quot;Mr. atdisk2&quot;)&n; *&t;Scott Snyder&t;(snyder@fnald0.fnal.gov)&t;(ATAPI IDE cd-rom)&n; *&n; *  This was a rewrite of just about everything from hd.c, though some original&n; *  code is still sprinkled about.  Think of it as a major evolution, with&n; *  inspiration from lots of linux users, esp.  hamish@zot.apana.org.au&n; *&n; * Version 1.0&t;&t;move disk only code from ide.c to ide-disk.c&n; *&t;&t;&t;support optional byte-swapping of all data&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide.h&quot;
DECL|function|idedisk_bswap_data
r_static
r_void
id|idedisk_bswap_data
(paren
r_void
op_star
id|buffer
comma
r_int
id|wcount
)paren
(brace
id|u16
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|wcount
op_decrement
)paren
(brace
op_star
id|p
op_increment
op_assign
op_star
id|p
op_lshift
l_int|8
op_or
op_star
id|p
op_rshift
l_int|8
suffix:semicolon
op_star
id|p
op_increment
op_assign
op_star
id|p
op_lshift
l_int|8
op_or
op_star
id|p
op_rshift
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|idedisk_input_data
r_static
r_inline
r_void
id|idedisk_input_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|ide_input_data
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;bswap
)paren
id|idedisk_bswap_data
c_func
(paren
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
DECL|function|idedisk_output_data
r_static
r_inline
r_void
id|idedisk_output_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|ide_output_data
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;bswap
)paren
id|idedisk_bswap_data
c_func
(paren
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lba_capacity_is_ok() performs a sanity check on the claimed &quot;lba_capacity&quot;&n; * value for this drive (from its reported identification information).&n; *&n; * Returns:&t;1 if lba_capacity looks sensible&n; *&t;&t;0 otherwise&n; */
DECL|function|lba_capacity_is_ok
r_static
r_int
id|lba_capacity_is_ok
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
r_int
r_int
id|lba_sects
op_assign
id|id-&gt;lba_capacity
suffix:semicolon
r_int
r_int
id|chs_sects
op_assign
id|id-&gt;cyls
op_star
id|id-&gt;heads
op_star
id|id-&gt;sectors
suffix:semicolon
r_int
r_int
id|_10_percent
op_assign
id|chs_sects
op_div
l_int|10
suffix:semicolon
multiline_comment|/* perform a rough sanity check on lba_sects:  within 10% is &quot;okay&quot; */
r_if
c_cond
(paren
(paren
id|lba_sects
op_minus
id|chs_sects
)paren
OL
id|_10_percent
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* lba_capacity is good */
multiline_comment|/* some drives have the word order reversed */
id|lba_sects
op_assign
(paren
id|lba_sects
op_lshift
l_int|16
)paren
op_or
(paren
id|lba_sects
op_rshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lba_sects
op_minus
id|chs_sects
)paren
OL
id|_10_percent
)paren
(brace
id|id-&gt;lba_capacity
op_assign
id|lba_sects
suffix:semicolon
multiline_comment|/* fix it */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* lba_capacity is (now) good */
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* lba_capacity value is bad */
)brace
multiline_comment|/*&n; * read_intr() is the handler for disk read/multread interrupts&n; */
DECL|function|read_intr
r_static
r_void
id|read_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|msect
comma
id|nsect
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|OK_STAT
c_func
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
comma
id|DATA_READY
comma
id|BAD_R_STAT
)paren
)paren
(brace
id|ide_error
c_func
(paren
id|drive
comma
l_string|&quot;read_intr&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|msect
op_assign
id|drive-&gt;mult_count
suffix:semicolon
id|read_next
suffix:colon
id|rq
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
suffix:semicolon
r_if
c_cond
(paren
id|msect
)paren
(brace
r_if
c_cond
(paren
(paren
id|nsect
op_assign
id|rq-&gt;current_nr_sectors
)paren
OG
id|msect
)paren
id|nsect
op_assign
id|msect
suffix:semicolon
id|msect
op_sub_assign
id|nsect
suffix:semicolon
)brace
r_else
id|nsect
op_assign
l_int|1
suffix:semicolon
id|idedisk_input_data
c_func
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|nsect
op_star
id|SECTOR_WORDS
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s:  read: sectors(%ld-%ld), buffer=0x%08lx, remaining=%ld&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rq-&gt;sector
comma
id|rq-&gt;sector
op_plus
id|nsect
op_minus
l_int|1
comma
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
op_plus
(paren
id|nsect
op_lshift
l_int|9
)paren
comma
id|rq-&gt;nr_sectors
op_minus
id|nsect
)paren
suffix:semicolon
macro_line|#endif
id|rq-&gt;sector
op_add_assign
id|nsect
suffix:semicolon
id|rq-&gt;buffer
op_add_assign
id|nsect
op_lshift
l_int|9
suffix:semicolon
id|rq-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
(paren
id|rq-&gt;nr_sectors
op_sub_assign
id|nsect
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;current_nr_sectors
op_sub_assign
id|nsect
)paren
op_le
l_int|0
)paren
id|ide_end_request
c_func
(paren
l_int|1
comma
id|HWGROUP
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|msect
)paren
r_goto
id|read_next
suffix:semicolon
id|ide_set_handler
(paren
id|drive
comma
op_amp
id|read_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * write_intr() is the handler for disk write interrupts&n; */
DECL|function|write_intr
r_static
r_void
id|write_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
id|hwgroup-&gt;rq
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
comma
id|DRIVE_READY
comma
id|drive-&gt;bad_wstat
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: write: sector %ld, buffer=0x%08lx, remaining=%ld&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rq-&gt;sector
comma
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
comma
id|rq-&gt;nr_sectors
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|rq-&gt;nr_sectors
op_eq
l_int|1
)paren
op_xor
(paren
(paren
id|stat
op_amp
id|DRQ_STAT
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|rq-&gt;sector
op_increment
suffix:semicolon
id|rq-&gt;buffer
op_add_assign
l_int|512
suffix:semicolon
id|rq-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
op_decrement
id|rq-&gt;nr_sectors
suffix:semicolon
op_decrement
id|rq-&gt;current_nr_sectors
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;current_nr_sectors
op_le
l_int|0
)paren
id|ide_end_request
c_func
(paren
l_int|1
comma
id|hwgroup
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|idedisk_output_data
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|SECTOR_WORDS
)paren
suffix:semicolon
id|ide_set_handler
(paren
id|drive
comma
op_amp
id|write_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
id|ide_error
c_func
(paren
id|drive
comma
l_string|&quot;write_intr&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ide_multwrite() transfers a block of up to mcount sectors of data&n; * to a drive as part of a disk multiple-sector write operation.&n; */
DECL|function|ide_multwrite
r_void
id|ide_multwrite
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|mcount
)paren
(brace
r_struct
id|request
op_star
id|rq
op_assign
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|wrq
suffix:semicolon
r_do
(brace
r_int
r_int
id|nsect
op_assign
id|rq-&gt;current_nr_sectors
suffix:semicolon
r_if
c_cond
(paren
id|nsect
OG
id|mcount
)paren
id|nsect
op_assign
id|mcount
suffix:semicolon
id|mcount
op_sub_assign
id|nsect
suffix:semicolon
id|idedisk_output_data
c_func
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|nsect
op_lshift
l_int|7
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: multwrite: sector %ld, buffer=0x%08lx, count=%d, remaining=%ld&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rq-&gt;sector
comma
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
comma
id|nsect
comma
id|rq-&gt;nr_sectors
op_minus
id|nsect
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|rq-&gt;nr_sectors
op_sub_assign
id|nsect
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;current_nr_sectors
op_sub_assign
id|nsect
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|rq-&gt;bh
op_assign
id|rq-&gt;bh-&gt;b_reqnext
)paren
op_ne
l_int|NULL
)paren
(brace
id|rq-&gt;current_nr_sectors
op_assign
id|rq-&gt;bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|rq-&gt;buffer
op_assign
id|rq-&gt;bh-&gt;b_data
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;%s: buffer list corrupted&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|rq-&gt;buffer
op_add_assign
id|nsect
op_lshift
l_int|9
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|mcount
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * multwrite_intr() is the handler for disk multwrite interrupts&n; */
DECL|function|multwrite_intr
r_static
r_void
id|multwrite_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
op_amp
id|hwgroup-&gt;wrq
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
comma
id|DRIVE_READY
comma
id|drive-&gt;bad_wstat
)paren
)paren
(brace
r_if
c_cond
(paren
id|stat
op_amp
id|DRQ_STAT
)paren
(brace
r_if
c_cond
(paren
id|rq-&gt;nr_sectors
)paren
(brace
id|ide_multwrite
c_func
(paren
id|drive
comma
id|drive-&gt;mult_count
)paren
suffix:semicolon
id|ide_set_handler
(paren
id|drive
comma
op_amp
id|multwrite_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|rq-&gt;nr_sectors
)paren
(brace
multiline_comment|/* all done? */
id|rq
op_assign
id|hwgroup-&gt;rq
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|rq-&gt;nr_sectors
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
)paren
(brace
id|i
op_sub_assign
id|rq-&gt;current_nr_sectors
suffix:semicolon
id|ide_end_request
c_func
(paren
l_int|1
comma
id|hwgroup
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
)brace
id|ide_error
c_func
(paren
id|drive
comma
l_string|&quot;multwrite_intr&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set_multmode_intr() is invoked on completion of a WIN_SETMULT cmd.&n; */
DECL|function|set_multmode_intr
r_static
r_void
id|set_multmode_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
id|stat
comma
id|READY_STAT
comma
id|BAD_STAT
)paren
)paren
(brace
id|drive-&gt;mult_count
op_assign
id|drive-&gt;mult_req
suffix:semicolon
)brace
r_else
(brace
id|drive-&gt;mult_req
op_assign
id|drive-&gt;mult_count
op_assign
l_int|0
suffix:semicolon
id|drive-&gt;special.b.recalibrate
op_assign
l_int|1
suffix:semicolon
(paren
r_void
)paren
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;set_multmode&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * set_geometry_intr() is invoked on completion of a WIN_SPECIFY cmd.&n; */
DECL|function|set_geometry_intr
r_static
r_void
id|set_geometry_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|OK_STAT
c_func
(paren
id|stat
comma
id|READY_STAT
comma
id|BAD_STAT
)paren
)paren
id|ide_error
c_func
(paren
id|drive
comma
l_string|&quot;set_geometry_intr&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * recal_intr() is invoked on completion of a WIN_RESTORE (recalibrate) cmd.&n; */
DECL|function|recal_intr
r_static
r_void
id|recal_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|OK_STAT
c_func
(paren
id|stat
comma
id|READY_STAT
comma
id|BAD_STAT
)paren
)paren
id|ide_error
c_func
(paren
id|drive
comma
l_string|&quot;recal_intr&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * do_rw_disk() issues READ and WRITE commands to a disk,&n; * using LBA if supported, or CHS otherwise, to address sectors.&n; * It also takes care of issuing special DRIVE_CMDs.&n; */
DECL|function|do_rw_disk
r_static
r_void
id|do_rw_disk
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
comma
r_int
r_int
id|block
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_PROMISE
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
id|use_promise_io
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_PROMISE */
id|OUT_BYTE
c_func
(paren
id|drive-&gt;ctl
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rq-&gt;nr_sectors
comma
id|IDE_NSECTOR_REG
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_PROMISE
r_if
c_cond
(paren
id|IS_PROMISE_DRIVE
)paren
(brace
r_if
c_cond
(paren
id|hwif-&gt;is_promise2
op_logical_or
id|rq-&gt;cmd
op_eq
id|READ
)paren
(brace
id|use_promise_io
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|drive-&gt;select.b.lba
op_logical_or
id|use_promise_io
)paren
(brace
macro_line|#else /* !CONFIG_BLK_DEV_PROMISE */
r_if
c_cond
(paren
id|drive-&gt;select.b.lba
)paren
(brace
macro_line|#endif /* CONFIG_BLK_DEV_PROMISE */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %sing: LBAsect=%ld, sectors=%ld, buffer=0x%08lx&bslash;n&quot;
comma
id|drive-&gt;name
comma
(paren
id|rq-&gt;cmd
op_eq
id|READ
)paren
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;writ&quot;
comma
id|block
comma
id|rq-&gt;nr_sectors
comma
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
)paren
suffix:semicolon
macro_line|#endif
id|OUT_BYTE
c_func
(paren
id|block
comma
id|IDE_SECTOR_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|block
op_rshift_assign
l_int|8
comma
id|IDE_LCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|block
op_rshift_assign
l_int|8
comma
id|IDE_HCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
(paren
(paren
id|block
op_rshift
l_int|8
)paren
op_amp
l_int|0x0f
)paren
op_or
id|drive-&gt;select.all
comma
id|IDE_SELECT_REG
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|sect
comma
id|head
comma
id|cyl
comma
id|track
suffix:semicolon
id|track
op_assign
id|block
op_div
id|drive-&gt;sect
suffix:semicolon
id|sect
op_assign
id|block
op_mod
id|drive-&gt;sect
op_plus
l_int|1
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|sect
comma
id|IDE_SECTOR_REG
)paren
suffix:semicolon
id|head
op_assign
id|track
op_mod
id|drive-&gt;head
suffix:semicolon
id|cyl
op_assign
id|track
op_div
id|drive-&gt;head
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|cyl
comma
id|IDE_LCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|cyl
op_rshift
l_int|8
comma
id|IDE_HCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|head
op_or
id|drive-&gt;select.all
comma
id|IDE_SELECT_REG
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: %sing: CHS=%d/%d/%d, sectors=%ld, buffer=0x%08lx&bslash;n&quot;
comma
id|drive-&gt;name
comma
(paren
id|rq-&gt;cmd
op_eq
id|READ
)paren
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;writ&quot;
comma
id|cyl
comma
id|head
comma
id|sect
comma
id|rq-&gt;nr_sectors
comma
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_BLK_DEV_PROMISE
r_if
c_cond
(paren
id|use_promise_io
)paren
(brace
id|do_promise_io
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_PROMISE */
r_if
c_cond
(paren
id|rq-&gt;cmd
op_eq
id|READ
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_TRITON
r_if
c_cond
(paren
id|drive-&gt;using_dma
op_logical_and
op_logical_neg
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_read
comma
id|drive
)paren
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_TRITON */
id|ide_set_handler
c_func
(paren
id|drive
comma
op_amp
id|read_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|drive-&gt;mult_count
ques
c_cond
id|WIN_MULTREAD
suffix:colon
id|WIN_READ
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rq-&gt;cmd
op_eq
id|WRITE
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_TRITON
r_if
c_cond
(paren
id|drive-&gt;using_dma
op_logical_and
op_logical_neg
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_write
comma
id|drive
)paren
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_TRITON */
id|OUT_BYTE
c_func
(paren
id|drive-&gt;mult_count
ques
c_cond
id|WIN_MULTWRITE
suffix:colon
id|WIN_WRITE
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_wait_stat
c_func
(paren
id|drive
comma
id|DATA_READY
comma
id|drive-&gt;bad_wstat
comma
id|WAIT_DRQ
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no DRQ after issuing %s&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;mult_count
ques
c_cond
l_string|&quot;MULTWRITE&quot;
suffix:colon
l_string|&quot;WRITE&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;unmask
)paren
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;mult_count
)paren
(brace
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|wrq
op_assign
op_star
id|rq
suffix:semicolon
multiline_comment|/* scratchpad */
id|ide_set_handler
(paren
id|drive
comma
op_amp
id|multwrite_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
id|ide_multwrite
c_func
(paren
id|drive
comma
id|drive-&gt;mult_count
)paren
suffix:semicolon
)brace
r_else
(brace
id|ide_set_handler
(paren
id|drive
comma
op_amp
id|write_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
id|idedisk_output_data
c_func
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|SECTOR_WORDS
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad command: %d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rq-&gt;cmd
)paren
suffix:semicolon
id|ide_end_request
c_func
(paren
l_int|0
comma
id|HWGROUP
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
)brace
DECL|function|idedisk_open
r_static
r_int
id|idedisk_open
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;removable
op_logical_and
id|drive-&gt;usage
op_eq
l_int|1
)paren
(brace
id|byte
id|door_lock
(braket
)braket
op_assign
(brace
id|WIN_DOORLOCK
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|request
id|rq
suffix:semicolon
id|check_disk_change
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|ide_init_drive_cmd
(paren
op_amp
id|rq
)paren
suffix:semicolon
id|rq.buffer
op_assign
id|door_lock
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ignore the return code from door_lock,&n;&t;&t; * since the open() has already succeeded,&n;&t;&t; * and the door_lock is irrelevant at this point.&n;&t;&t; */
(paren
r_void
)paren
id|ide_do_drive_cmd
c_func
(paren
id|drive
comma
op_amp
id|rq
comma
id|ide_wait
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idedisk_release
r_static
r_void
id|idedisk_release
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;removable
op_logical_and
op_logical_neg
id|drive-&gt;usage
)paren
(brace
id|byte
id|door_unlock
(braket
)braket
op_assign
(brace
id|WIN_DOORUNLOCK
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|request
id|rq
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|ide_init_drive_cmd
(paren
op_amp
id|rq
)paren
suffix:semicolon
id|rq.buffer
op_assign
id|door_unlock
suffix:semicolon
(paren
r_void
)paren
id|ide_do_drive_cmd
c_func
(paren
id|drive
comma
op_amp
id|rq
comma
id|ide_wait
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|idedisk_media_change
r_static
r_int
id|idedisk_media_change
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
id|drive-&gt;removable
suffix:semicolon
multiline_comment|/* if removable, always assume it was changed */
)brace
multiline_comment|/*&n; * current_capacity() returns the capacity (in sectors) of a drive&n; * according to its current geometry/LBA settings.&n; */
DECL|function|idedisk_capacity
r_static
r_int
r_int
id|idedisk_capacity
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
r_int
id|capacity
op_assign
id|drive-&gt;cyl
op_star
id|drive-&gt;head
op_star
id|drive-&gt;sect
suffix:semicolon
id|drive-&gt;select.b.lba
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Determine capacity, and use LBA if the drive properly supports it */
r_if
c_cond
(paren
id|id
op_ne
l_int|NULL
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|2
)paren
op_logical_and
id|lba_capacity_is_ok
c_func
(paren
id|id
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;lba_capacity
op_ge
id|capacity
)paren
(brace
id|capacity
op_assign
id|id-&gt;lba_capacity
suffix:semicolon
id|drive-&gt;select.b.lba
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
(paren
id|capacity
op_minus
id|drive-&gt;sect0
)paren
suffix:semicolon
)brace
DECL|function|idedisk_special
r_static
r_void
id|idedisk_special
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|special_t
op_star
id|s
op_assign
op_amp
id|drive-&gt;special
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;b.set_geometry
)paren
(brace
id|s-&gt;b.set_geometry
op_assign
l_int|0
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|drive-&gt;sect
comma
id|IDE_SECTOR_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|drive-&gt;cyl
comma
id|IDE_LCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|drive-&gt;cyl
op_rshift
l_int|8
comma
id|IDE_HCYL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
(paren
(paren
id|drive-&gt;head
op_minus
l_int|1
)paren
op_or
id|drive-&gt;select.all
)paren
op_amp
l_int|0xBF
comma
id|IDE_SELECT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_PROMISE_DRIVE
)paren
id|ide_cmd
c_func
(paren
id|drive
comma
id|WIN_SPECIFY
comma
id|drive-&gt;sect
comma
op_amp
id|set_geometry_intr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;b.recalibrate
)paren
(brace
id|s-&gt;b.recalibrate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_PROMISE_DRIVE
)paren
id|ide_cmd
c_func
(paren
id|drive
comma
id|WIN_RESTORE
comma
id|drive-&gt;sect
comma
op_amp
id|recal_intr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;b.set_multmode
)paren
(brace
id|s-&gt;b.set_multmode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;id
op_logical_and
id|drive-&gt;mult_req
OG
id|drive-&gt;id-&gt;max_multsect
)paren
id|drive-&gt;mult_req
op_assign
id|drive-&gt;id-&gt;max_multsect
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_PROMISE_DRIVE
)paren
id|ide_cmd
c_func
(paren
id|drive
comma
id|WIN_SETMULT
comma
id|drive-&gt;mult_req
comma
op_amp
id|set_multmode_intr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;all
)paren
(brace
r_int
id|special
op_assign
id|s-&gt;all
suffix:semicolon
id|s-&gt;all
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad special flag: 0x%02x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|special
)paren
suffix:semicolon
)brace
)brace
DECL|function|idedisk_pre_reset
r_static
r_void
id|idedisk_pre_reset
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|drive-&gt;special.all
op_assign
l_int|0
suffix:semicolon
id|drive-&gt;special.b.set_geometry
op_assign
l_int|1
suffix:semicolon
id|drive-&gt;special.b.recalibrate
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|OK_TO_RESET_CONTROLLER
)paren
id|drive-&gt;mult_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;keep_settings
)paren
id|drive-&gt;mult_req
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;mult_req
op_ne
id|drive-&gt;mult_count
)paren
id|drive-&gt;special.b.set_multmode
op_assign
l_int|1
suffix:semicolon
)brace
r_int
id|idedisk_init
(paren
r_void
)paren
suffix:semicolon
DECL|variable|idedisk_module
r_static
id|ide_module_t
id|idedisk_module
op_assign
(brace
id|IDE_DRIVER_MODULE
comma
id|idedisk_init
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;IDE subdriver functions, registered with ide.c&n; */
DECL|variable|idedisk_driver
r_static
id|ide_driver_t
id|idedisk_driver
op_assign
(brace
id|ide_disk
comma
multiline_comment|/* media */
l_int|0
comma
multiline_comment|/* busy */
l_int|1
comma
multiline_comment|/* supports_dma */
l_int|NULL
comma
multiline_comment|/* cleanup */
id|do_rw_disk
comma
multiline_comment|/* do_request */
l_int|NULL
comma
multiline_comment|/* end_request */
l_int|NULL
comma
multiline_comment|/* ioctl */
id|idedisk_open
comma
multiline_comment|/* open */
id|idedisk_release
comma
multiline_comment|/* release */
id|idedisk_media_change
comma
multiline_comment|/* media_change */
id|idedisk_pre_reset
comma
multiline_comment|/* pre_reset */
id|idedisk_capacity
comma
multiline_comment|/* capacity */
id|idedisk_special
multiline_comment|/* special */
)brace
suffix:semicolon
DECL|function|idedisk_cleanup
r_static
r_int
id|idedisk_cleanup
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
id|ide_unregister_subdriver
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|idedisk_identify_device
r_static
r_int
id|idedisk_identify_device
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* SunDisk drives: force one unit */
r_if
c_cond
(paren
id|id-&gt;model
(braket
l_int|0
)braket
op_eq
l_char|&squot;S&squot;
op_logical_and
id|id-&gt;model
(braket
l_int|1
)braket
op_eq
l_char|&squot;u&squot;
op_logical_and
(paren
id|drive-&gt;select.all
op_amp
(paren
l_int|1
op_lshift
l_int|4
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idedisk_setup
r_static
r_void
id|idedisk_setup
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
r_int
id|capacity
comma
id|check
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* check for removable disks (eg. SYQUEST), ignore &squot;WD&squot; drives */
r_if
c_cond
(paren
id|id-&gt;config
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
(brace
multiline_comment|/* removable disk ? */
r_if
c_cond
(paren
id|id-&gt;model
(braket
l_int|0
)braket
op_ne
l_char|&squot;W&squot;
op_logical_or
id|id-&gt;model
(braket
l_int|1
)braket
op_ne
l_char|&squot;D&squot;
)paren
id|drive-&gt;removable
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* SunDisk drives: treat as non-removable */
r_if
c_cond
(paren
id|id-&gt;model
(braket
l_int|0
)braket
op_eq
l_char|&squot;S&squot;
op_logical_and
id|id-&gt;model
(braket
l_int|1
)braket
op_eq
l_char|&squot;u&squot;
)paren
id|drive-&gt;removable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Extract geometry if we did not already have one for the drive */
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;cyl
op_logical_or
op_logical_neg
id|drive-&gt;head
op_logical_or
op_logical_neg
id|drive-&gt;sect
)paren
(brace
id|drive-&gt;cyl
op_assign
id|drive-&gt;bios_cyl
op_assign
id|id-&gt;cyls
suffix:semicolon
id|drive-&gt;head
op_assign
id|drive-&gt;bios_head
op_assign
id|id-&gt;heads
suffix:semicolon
id|drive-&gt;sect
op_assign
id|drive-&gt;bios_sect
op_assign
id|id-&gt;sectors
suffix:semicolon
)brace
multiline_comment|/* Handle logical geometry translation by the drive */
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|1
)paren
op_logical_and
id|id-&gt;cur_cyls
op_logical_and
id|id-&gt;cur_heads
op_logical_and
(paren
id|id-&gt;cur_heads
op_le
l_int|16
)paren
op_logical_and
id|id-&gt;cur_sectors
)paren
(brace
multiline_comment|/*&n;&t;&t; * Extract the physical drive geometry for our use.&n;&t;&t; * Note that we purposely do *not* update the bios info.&n;&t;&t; * This way, programs that use it (like fdisk) will&n;&t;&t; * still have the same logical view as the BIOS does,&n;&t;&t; * which keeps the partition table from being screwed.&n;&t;&t; *&n;&t;&t; * An exception to this is the cylinder count,&n;&t;&t; * which we reexamine later on to correct for 1024 limitations.&n;&t;&t; */
id|drive-&gt;cyl
op_assign
id|id-&gt;cur_cyls
suffix:semicolon
id|drive-&gt;head
op_assign
id|id-&gt;cur_heads
suffix:semicolon
id|drive-&gt;sect
op_assign
id|id-&gt;cur_sectors
suffix:semicolon
multiline_comment|/* check for word-swapped &quot;capacity&quot; field in id information */
id|capacity
op_assign
id|drive-&gt;cyl
op_star
id|drive-&gt;head
op_star
id|drive-&gt;sect
suffix:semicolon
id|check
op_assign
(paren
id|id-&gt;cur_capacity0
op_lshift
l_int|16
)paren
op_or
id|id-&gt;cur_capacity1
suffix:semicolon
r_if
c_cond
(paren
id|check
op_eq
id|capacity
)paren
(brace
multiline_comment|/* was it swapped? */
multiline_comment|/* yes, bring it into little-endian order: */
id|id-&gt;cur_capacity0
op_assign
(paren
id|capacity
op_rshift
l_int|0
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|id-&gt;cur_capacity1
op_assign
(paren
id|capacity
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
)brace
multiline_comment|/* Use physical geometry if what we have still makes no sense */
r_if
c_cond
(paren
(paren
op_logical_neg
id|drive-&gt;head
op_logical_or
id|drive-&gt;head
OG
l_int|16
)paren
op_logical_and
id|id-&gt;heads
op_logical_and
id|id-&gt;heads
op_le
l_int|16
)paren
(brace
id|drive-&gt;cyl
op_assign
id|id-&gt;cyls
suffix:semicolon
id|drive-&gt;head
op_assign
id|id-&gt;heads
suffix:semicolon
id|drive-&gt;sect
op_assign
id|id-&gt;sectors
suffix:semicolon
)brace
multiline_comment|/* Correct the number of cyls if the bios value is too small */
r_if
c_cond
(paren
id|drive-&gt;sect
op_eq
id|drive-&gt;bios_sect
op_logical_and
id|drive-&gt;head
op_eq
id|drive-&gt;bios_head
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;cyl
OG
id|drive-&gt;bios_cyl
)paren
id|drive-&gt;bios_cyl
op_assign
id|drive-&gt;cyl
suffix:semicolon
)brace
(paren
r_void
)paren
id|idedisk_capacity
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* initialize LBA selection */
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: %.40s, %ldMB w/%dkB Cache, %sCHS=%d/%d/%d%s&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|id-&gt;model
comma
id|idedisk_capacity
c_func
(paren
id|drive
)paren
op_div
l_int|2048L
comma
id|id-&gt;buf_size
op_div
l_int|2
comma
id|drive-&gt;select.b.lba
ques
c_cond
l_string|&quot;LBA, &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|drive-&gt;bios_cyl
comma
id|drive-&gt;bios_head
comma
id|drive-&gt;bios_sect
comma
id|drive-&gt;using_dma
ques
c_cond
l_string|&quot;, DMA&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|drive-&gt;mult_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;max_multsect
)paren
(brace
id|drive-&gt;mult_req
op_assign
id|INITIAL_MULT_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;mult_req
OG
id|id-&gt;max_multsect
)paren
id|drive-&gt;mult_req
op_assign
id|id-&gt;max_multsect
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;mult_req
op_logical_or
(paren
(paren
id|id-&gt;multsect_valid
op_amp
l_int|1
)paren
op_logical_and
id|id-&gt;multsect
)paren
)paren
id|drive-&gt;special.b.set_multmode
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|idedisk_init
r_int
id|idedisk_init
(paren
r_void
)paren
(brace
id|ide_drive_t
op_star
id|drive
suffix:semicolon
r_int
id|failed
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_while
c_loop
(paren
(paren
id|drive
op_assign
id|ide_scan_devices
(paren
id|ide_disk
comma
l_int|NULL
comma
id|failed
op_increment
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|idedisk_identify_device
(paren
id|drive
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ide_register_subdriver
(paren
id|drive
comma
op_amp
id|idedisk_driver
comma
id|IDE_SUBDRIVER_VERSION
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;ide-disk: %s: Failed to register the driver with ide.c&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|idedisk_setup
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|drive-&gt;head
op_logical_or
id|drive-&gt;head
OG
l_int|16
)paren
op_logical_and
op_logical_neg
id|drive-&gt;select.b.lba
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: INVALID GEOMETRY: %d PHYSICAL HEADS?&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;head
)paren
suffix:semicolon
(paren
r_void
)paren
id|idedisk_cleanup
c_func
(paren
id|drive
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|failed
op_decrement
suffix:semicolon
)brace
id|ide_register_module
c_func
(paren
op_amp
id|idedisk_module
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_return
id|idedisk_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
id|ide_drive_t
op_star
id|drive
suffix:semicolon
r_int
id|failed
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|drive
op_assign
id|ide_scan_devices
(paren
id|ide_disk
comma
op_amp
id|idedisk_driver
comma
id|failed
)paren
)paren
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
id|idedisk_cleanup
(paren
id|drive
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;%s: cleanup_module() called while still busy&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|failed
op_increment
suffix:semicolon
)brace
id|ide_unregister_module
c_func
(paren
op_amp
id|idedisk_module
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
