multiline_comment|/*&n; *  linux/drivers/block/ll_rw_blk.c&n; *&n; * Copyright (C) 1991, 1992 Linus Torvalds&n; * Copyright (C) 1994,      Karl Keyte: Added support for disk statistics&n; */
multiline_comment|/*&n; * This handles all read/write requests to block devices&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;blk.h&quot;
multiline_comment|/*&n; * The request-struct contains all necessary data&n; * to load a nr of sectors into memory&n; */
DECL|variable|all_requests
r_static
r_struct
id|request
id|all_requests
(braket
id|NR_REQUEST
)braket
suffix:semicolon
multiline_comment|/*&n; * used to wait on when there are no free requests&n; */
DECL|variable|wait_for_request
r_struct
id|wait_queue
op_star
id|wait_for_request
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* This specifies how many sectors to read ahead on the disk.  */
DECL|variable|read_ahead
r_int
id|read_ahead
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* blk_dev_struct is:&n; *&t;do_request-address&n; *&t;next-request&n; */
DECL|variable|blk_dev
r_struct
id|blk_dev_struct
id|blk_dev
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 0 no_dev */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 1 dev mem */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 2 dev fd */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 3 dev ide0 or hd */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 4 dev ttyx */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 5 dev tty */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 6 dev lp */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 7 dev pipes */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 8 dev sd */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 9 dev st */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 10 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 11 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 12 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 13 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 14 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 15 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 16 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 17 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 18 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 19 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 20 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* 21 */
(brace
l_int|NULL
comma
l_int|NULL
)brace
multiline_comment|/* 22 dev ide1 */
)brace
suffix:semicolon
multiline_comment|/*&n; * blk_size contains the size of all block-devices in units of 1024 byte&n; * sectors:&n; *&n; * blk_size[MAJOR][MINOR]&n; *&n; * if (!blk_size[MAJOR]) then no minor size checking is done.&n; */
DECL|variable|blk_size
r_int
op_star
id|blk_size
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * blksize_size contains the size of all block-devices:&n; *&n; * blksize_size[MAJOR][MINOR]&n; *&n; * if (!blksize_size[MAJOR]) then 1024 bytes is assumed.&n; */
DECL|variable|blksize_size
r_int
op_star
id|blksize_size
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * hardsect_size contains the size of the hardware sector of a device.&n; *&n; * hardsect_size[MAJOR][MINOR]&n; *&n; * if (!hardsect_size[MAJOR])&n; *&t;&t;then 512 bytes is assumed.&n; * else&n; *&t;&t;sector_size is hardsect_size[MAJOR][MINOR]&n; * This is currently set by some scsi device and read by the msdos fs driver&n; * This might be a some uses later.&n; */
DECL|variable|hardsect_size
r_int
op_star
id|hardsect_size
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * look for a free request in the first N entries.&n; * NOTE: interrupts must be disabled on the way in, and will still&n; *       be disabled on the way out.&n; */
DECL|function|get_request
r_static
r_inline
r_struct
id|request
op_star
id|get_request
c_func
(paren
r_int
id|n
comma
r_int
id|dev
)paren
(brace
r_static
r_struct
id|request
op_star
id|prev_found
op_assign
l_int|NULL
comma
op_star
id|prev_limit
op_assign
l_int|NULL
suffix:semicolon
r_register
r_struct
id|request
op_star
id|req
comma
op_star
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;get_request(%d): impossible!&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
id|limit
op_assign
id|all_requests
op_plus
id|n
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_ne
id|prev_limit
)paren
(brace
id|prev_limit
op_assign
id|limit
suffix:semicolon
id|prev_found
op_assign
id|all_requests
suffix:semicolon
)brace
id|req
op_assign
id|prev_found
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|req
op_assign
(paren
(paren
id|req
OG
id|all_requests
)paren
ques
c_cond
id|req
suffix:colon
id|limit
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;dev
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
id|prev_found
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
id|prev_found
op_assign
id|req
suffix:semicolon
id|req-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
multiline_comment|/*&n; * wait until a free request in the first N entries is available.&n; * NOTE: interrupts must be disabled on the way in, and will still&n; *       be disabled on the way out.&n; */
DECL|function|get_request_wait
r_static
r_inline
r_struct
id|request
op_star
id|get_request_wait
c_func
(paren
r_int
id|n
comma
r_int
id|dev
)paren
(brace
r_register
r_struct
id|request
op_star
id|req
suffix:semicolon
r_while
c_loop
(paren
(paren
id|req
op_assign
id|get_request
c_func
(paren
id|n
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
id|sleep_on
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
multiline_comment|/* RO fail safe mechanism */
DECL|variable|ro_bits
r_static
r_int
id|ro_bits
(braket
id|MAX_BLKDEV
)braket
(braket
l_int|8
)braket
suffix:semicolon
DECL|function|is_read_only
r_int
id|is_read_only
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|minor
comma
id|major
suffix:semicolon
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|major
OL
l_int|0
op_logical_or
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ro_bits
(braket
id|major
)braket
(braket
id|minor
op_rshift
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|minor
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_device_ro
r_void
id|set_device_ro
c_func
(paren
r_int
id|dev
comma
r_int
id|flag
)paren
(brace
r_int
id|minor
comma
id|major
suffix:semicolon
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|major
OL
l_int|0
op_logical_or
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|ro_bits
(braket
id|major
)braket
(braket
id|minor
op_rshift
l_int|5
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|minor
op_amp
l_int|31
)paren
suffix:semicolon
r_else
id|ro_bits
(braket
id|major
)braket
(braket
id|minor
op_rshift
l_int|5
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|minor
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * add-request adds a request to the linked list.&n; * It disables interrupts so that it can muck with the&n; * request-lists in peace.&n; */
DECL|function|add_request
r_static
r_void
id|add_request
c_func
(paren
r_struct
id|blk_dev_struct
op_star
id|dev
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|request
op_star
id|tmp
suffix:semicolon
r_int
id|disk_index
suffix:semicolon
r_switch
c_cond
(paren
id|MAJOR
c_func
(paren
id|req-&gt;dev
)paren
)paren
(brace
r_case
id|SCSI_DISK_MAJOR
suffix:colon
id|disk_index
op_assign
(paren
id|MINOR
c_func
(paren
id|req-&gt;dev
)paren
op_amp
l_int|0x0070
)paren
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|disk_index
OL
l_int|4
)paren
id|kstat.dk_drive
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HD_MAJOR
suffix:colon
r_case
id|XT_DISK_MAJOR
suffix:colon
id|disk_index
op_assign
(paren
id|MINOR
c_func
(paren
id|req-&gt;dev
)paren
op_amp
l_int|0x0040
)paren
op_rshift
l_int|6
suffix:semicolon
id|kstat.dk_drive
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IDE1_MAJOR
suffix:colon
id|disk_index
op_assign
(paren
(paren
id|MINOR
c_func
(paren
id|req-&gt;dev
)paren
op_amp
l_int|0x0040
)paren
op_rshift
l_int|6
)paren
op_plus
l_int|2
suffix:semicolon
id|kstat.dk_drive
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;bh
)paren
id|mark_buffer_clean
c_func
(paren
id|req-&gt;bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
id|dev-&gt;current_request
)paren
)paren
(brace
id|dev-&gt;current_request
op_assign
id|req
suffix:semicolon
(paren
id|dev-&gt;request_fn
)paren
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|tmp-&gt;next
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
id|IN_ORDER
c_func
(paren
id|tmp
comma
id|req
)paren
op_logical_or
op_logical_neg
id|IN_ORDER
c_func
(paren
id|tmp
comma
id|tmp-&gt;next
)paren
)paren
op_logical_and
id|IN_ORDER
c_func
(paren
id|req
comma
id|tmp-&gt;next
)paren
)paren
r_break
suffix:semicolon
)brace
id|req-&gt;next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|tmp-&gt;next
op_assign
id|req
suffix:semicolon
multiline_comment|/* for SCSI devices, call request_fn unconditionally */
r_if
c_cond
(paren
id|scsi_major
c_func
(paren
id|MAJOR
c_func
(paren
id|req-&gt;dev
)paren
)paren
)paren
(paren
id|dev-&gt;request_fn
)paren
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|make_request
r_static
r_void
id|make_request
c_func
(paren
r_int
id|major
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
r_int
id|sector
comma
id|count
suffix:semicolon
r_struct
id|request
op_star
id|req
suffix:semicolon
r_int
id|rw_ahead
comma
id|max_req
suffix:semicolon
multiline_comment|/* WRITEA/READA is special case - it is not really needed, so if the */
multiline_comment|/* buffer is locked, we just forget about it, else it&squot;s a normal read */
id|rw_ahead
op_assign
(paren
id|rw
op_eq
id|READA
op_logical_or
id|rw
op_eq
id|WRITEA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw_ahead
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_lock
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READA
)paren
id|rw
op_assign
id|READ
suffix:semicolon
r_else
id|rw
op_assign
id|WRITE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rw
op_ne
id|READ
op_logical_and
id|rw
op_ne
id|WRITE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad block dev command, must be R/W/RA/WA&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|count
op_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|sector
op_assign
id|bh-&gt;b_blocknr
op_star
id|count
suffix:semicolon
r_if
c_cond
(paren
id|blk_size
(braket
id|major
)braket
)paren
r_if
c_cond
(paren
id|blk_size
(braket
id|major
)braket
(braket
id|MINOR
c_func
(paren
id|bh-&gt;b_dev
)paren
)braket
OL
(paren
id|sector
op_plus
id|count
)paren
op_rshift
l_int|1
)paren
(brace
id|bh-&gt;b_dirt
op_assign
id|bh-&gt;b_uptodate
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_req
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Uhhuh.. Nasty dead-lock possible here.. */
r_if
c_cond
(paren
id|bh-&gt;b_lock
)paren
r_return
suffix:semicolon
multiline_comment|/* Maybe the above fixes it, and maybe it doesn&squot;t boot. Life is interesting */
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rw
op_eq
id|WRITE
op_logical_and
op_logical_neg
id|bh-&gt;b_dirt
)paren
op_logical_or
(paren
id|rw
op_eq
id|READ
op_logical_and
id|bh-&gt;b_uptodate
)paren
)paren
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* we don&squot;t allow the write-requests to fill up the queue completely:&n; * we want some room for reads: they take precedence. The last third&n; * of the requests are only for reads.&n; */
id|max_req
op_assign
(paren
id|rw
op_eq
id|READ
)paren
ques
c_cond
id|NR_REQUEST
suffix:colon
(paren
(paren
id|NR_REQUEST
op_star
l_int|2
)paren
op_div
l_int|3
)paren
suffix:semicolon
multiline_comment|/* big loop: look for a free request. */
id|repeat
suffix:colon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The scsi disk drivers and the IDE driver completely remove the request&n; * from the queue when they start processing an entry.  For this reason&n; * it is safe to continue to add links to the top entry for those devices.&n; */
r_if
c_cond
(paren
(paren
id|major
op_eq
id|IDE0_MAJOR
multiline_comment|/* same as HD_MAJOR */
op_logical_or
id|major
op_eq
id|IDE1_MAJOR
op_logical_or
id|major
op_eq
id|FLOPPY_MAJOR
op_logical_or
id|major
op_eq
id|SCSI_DISK_MAJOR
op_logical_or
id|major
op_eq
id|SCSI_CDROM_MAJOR
)paren
op_logical_and
(paren
id|req
op_assign
id|blk_dev
(braket
id|major
)braket
dot
id|current_request
)paren
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_HD
r_if
c_cond
(paren
id|major
op_eq
id|HD_MAJOR
op_logical_or
id|major
op_eq
id|FLOPPY_MAJOR
)paren
macro_line|#else
r_if
c_cond
(paren
id|major
op_eq
id|FLOPPY_MAJOR
)paren
macro_line|#endif CONFIG_BLK_DEV_HD
id|req
op_assign
id|req-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|req
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;dev
op_eq
id|bh-&gt;b_dev
op_logical_and
op_logical_neg
id|req-&gt;sem
op_logical_and
id|req-&gt;cmd
op_eq
id|rw
op_logical_and
id|req-&gt;sector
op_plus
id|req-&gt;nr_sectors
op_eq
id|sector
op_logical_and
id|req-&gt;nr_sectors
OL
l_int|244
)paren
(brace
id|req-&gt;bhtail-&gt;b_reqnext
op_assign
id|bh
suffix:semicolon
id|req-&gt;bhtail
op_assign
id|bh
suffix:semicolon
id|req-&gt;nr_sectors
op_add_assign
id|count
suffix:semicolon
id|mark_buffer_clean
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;dev
op_eq
id|bh-&gt;b_dev
op_logical_and
op_logical_neg
id|req-&gt;sem
op_logical_and
id|req-&gt;cmd
op_eq
id|rw
op_logical_and
id|req-&gt;sector
op_minus
id|count
op_eq
id|sector
op_logical_and
id|req-&gt;nr_sectors
OL
l_int|244
)paren
(brace
id|req-&gt;nr_sectors
op_add_assign
id|count
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
id|req-&gt;bh
suffix:semicolon
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
id|req-&gt;current_nr_sectors
op_assign
id|count
suffix:semicolon
id|req-&gt;sector
op_assign
id|sector
suffix:semicolon
id|mark_buffer_clean
c_func
(paren
id|bh
)paren
suffix:semicolon
id|req-&gt;bh
op_assign
id|bh
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|req
op_assign
id|req-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/* find an unused request. */
id|req
op_assign
id|get_request
c_func
(paren
id|max_req
comma
id|bh-&gt;b_dev
)paren
suffix:semicolon
multiline_comment|/* if no request available: if rw_ahead, forget it; otherwise try again. */
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
r_if
c_cond
(paren
id|rw_ahead
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sleep_on
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* we found a request. */
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* fill up the request-info, and add it to the queue */
id|req-&gt;cmd
op_assign
id|rw
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|req-&gt;sector
op_assign
id|sector
suffix:semicolon
id|req-&gt;nr_sectors
op_assign
id|count
suffix:semicolon
id|req-&gt;current_nr_sectors
op_assign
id|count
suffix:semicolon
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
id|req-&gt;sem
op_assign
l_int|NULL
suffix:semicolon
id|req-&gt;bh
op_assign
id|bh
suffix:semicolon
id|req-&gt;bhtail
op_assign
id|bh
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|add_request
c_func
(paren
id|major
op_plus
id|blk_dev
comma
id|req
)paren
suffix:semicolon
)brace
DECL|function|ll_rw_page
r_void
id|ll_rw_page
c_func
(paren
r_int
id|rw
comma
r_int
id|dev
comma
r_int
id|page
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_int
r_int
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
op_logical_or
op_logical_neg
(paren
id|blk_dev
(braket
id|major
)braket
dot
id|request_fn
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to read nonexistent block-device %04x (%d)&bslash;n&quot;
comma
id|dev
comma
id|page
op_star
l_int|8
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rw
op_ne
id|READ
op_logical_and
id|rw
op_ne
id|WRITE
)paren
id|panic
c_func
(paren
l_string|&quot;Bad block dev command, must be R/W&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
op_logical_and
id|is_read_only
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t page to read-only device 0x%X&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
op_assign
id|get_request_wait
c_func
(paren
id|NR_REQUEST
comma
id|dev
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* fill up the request-info, and add it to the queue */
id|req-&gt;cmd
op_assign
id|rw
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|req-&gt;sector
op_assign
id|page
op_lshift
l_int|3
suffix:semicolon
id|req-&gt;nr_sectors
op_assign
l_int|8
suffix:semicolon
id|req-&gt;current_nr_sectors
op_assign
l_int|8
suffix:semicolon
id|req-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|req-&gt;sem
op_assign
op_amp
id|sem
suffix:semicolon
id|req-&gt;bh
op_assign
l_int|NULL
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|add_request
c_func
(paren
id|major
op_plus
id|blk_dev
comma
id|req
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/* This function can be used to request a number of buffers from a block&n;   device. Currently the only restriction is that all buffers must belong to&n;   the same device */
DECL|function|ll_rw_block
r_void
id|ll_rw_block
c_func
(paren
r_int
id|rw
comma
r_int
id|nr
comma
r_struct
id|buffer_head
op_star
id|bh
(braket
)braket
)paren
(brace
r_int
r_int
id|major
suffix:semicolon
r_struct
id|request
id|plug
suffix:semicolon
r_int
id|plugged
suffix:semicolon
r_int
id|correct_size
suffix:semicolon
r_struct
id|blk_dev_struct
op_star
id|dev
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#if defined(CONFIG_CDU535) &amp;&amp; defined(CONFIG_CDU31A)
r_int
id|sonycd_save_mem_start
suffix:semicolon
macro_line|#endif
multiline_comment|/* Make sure that the first block contains something reasonable */
r_while
c_loop
(paren
op_logical_neg
op_star
id|bh
)paren
(brace
id|bh
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|nr
op_le
l_int|0
)paren
r_return
suffix:semicolon
)brace
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|major
op_assign
id|MAJOR
c_func
(paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
)paren
OL
id|MAX_BLKDEV
)paren
id|dev
op_assign
id|blk_dev
op_plus
id|major
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;request_fn
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_block: Trying to read nonexistent block-device %04lX (%ld)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
comma
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_blocknr
)paren
suffix:semicolon
r_goto
id|sorry
suffix:semicolon
)brace
multiline_comment|/* Determine correct block size for this device.  */
id|correct_size
op_assign
id|BLOCK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|major
)braket
)paren
(brace
id|i
op_assign
id|blksize_size
(braket
id|major
)braket
(braket
id|MINOR
c_func
(paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|correct_size
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* Verify requested block sizes.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
op_logical_and
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_size
op_ne
id|correct_size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_block: only %d-char blocks implemented (%lu)&bslash;n&quot;
comma
id|correct_size
comma
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_size
)paren
suffix:semicolon
r_goto
id|sorry
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|rw
op_eq
id|WRITE
op_logical_or
id|rw
op_eq
id|WRITEA
)paren
op_logical_and
id|is_read_only
c_func
(paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t write to read-only device 0x%X&bslash;n&quot;
comma
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
suffix:semicolon
r_goto
id|sorry
suffix:semicolon
)brace
multiline_comment|/* If there are no pending requests for this device, then we insert&n;&t;   a dummy request for that device.  This will prevent the request&n;&t;   from starting until we have shoved all of the blocks into the&n;&t;   queue, and then we let it rip.  */
id|plugged
op_assign
l_int|0
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;current_request
op_logical_and
id|nr
OG
l_int|1
)paren
(brace
id|dev-&gt;current_request
op_assign
op_amp
id|plug
suffix:semicolon
id|plug.dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|plug.next
op_assign
l_int|NULL
suffix:semicolon
id|plugged
op_assign
l_int|1
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
)paren
(brace
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_req
op_assign
l_int|1
suffix:semicolon
id|make_request
c_func
(paren
id|major
comma
id|rw
comma
id|bh
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
op_logical_or
id|rw
op_eq
id|READA
)paren
id|kstat.pgpgin
op_increment
suffix:semicolon
r_else
id|kstat.pgpgout
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|plugged
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;current_request
op_assign
id|plug.next
suffix:semicolon
(paren
id|dev-&gt;request_fn
)paren
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|sorry
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
)paren
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_dirt
op_assign
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_uptodate
op_assign
l_int|0
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|ll_rw_swap_file
r_void
id|ll_rw_swap_file
c_func
(paren
r_int
id|rw
comma
r_int
id|dev
comma
r_int
r_int
op_star
id|b
comma
r_int
id|nb
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|buffersize
suffix:semicolon
r_struct
id|request
op_star
id|req
suffix:semicolon
r_int
r_int
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
op_logical_or
op_logical_neg
(paren
id|blk_dev
(braket
id|major
)braket
dot
id|request_fn
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_swap_file: trying to swap nonexistent block-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rw
op_ne
id|READ
op_logical_and
id|rw
op_ne
id|WRITE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_swap: bad block dev command, must be R/W&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
op_logical_and
id|is_read_only
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t swap to read-only device 0x%X&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|buffersize
op_assign
id|PAGE_SIZE
op_div
id|nb
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
id|nb
suffix:semicolon
id|i
op_increment
comma
id|buf
op_add_assign
id|buffersize
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
op_assign
id|get_request_wait
c_func
(paren
id|NR_REQUEST
comma
id|dev
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|req-&gt;cmd
op_assign
id|rw
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|req-&gt;sector
op_assign
(paren
id|b
(braket
id|i
)braket
op_star
id|buffersize
)paren
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;nr_sectors
op_assign
id|buffersize
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;current_nr_sectors
op_assign
id|buffersize
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;buffer
op_assign
id|buf
suffix:semicolon
id|req-&gt;sem
op_assign
op_amp
id|sem
suffix:semicolon
id|req-&gt;bh
op_assign
l_int|NULL
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|add_request
c_func
(paren
id|major
op_plus
id|blk_dev
comma
id|req
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|blk_dev_init
r_int
id|blk_dev_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|mem_end
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
id|req
op_assign
id|all_requests
op_plus
id|NR_REQUEST
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|req
op_ge
id|all_requests
)paren
(brace
id|req-&gt;dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ro_bits
comma
l_int|0
comma
r_sizeof
(paren
id|ro_bits
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_HD
id|mem_start
op_assign
id|hd_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|mem_start
op_assign
id|ide_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_XD
id|mem_start
op_assign
id|xd_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_CDU535) &amp;&amp; defined(CONFIG_CDU31A)
(brace
multiline_comment|/* since controllers for 535 and 31A can be at same location&n;&t;    * we have to be careful.&n;&t;    */
id|sonycd_save_mem_start
op_assign
id|mem_start
suffix:semicolon
id|mem_start
op_assign
id|cdu31a_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_start
op_eq
id|sonycd_save_mem_start
)paren
(brace
multiline_comment|/* CDU31A not found */
id|mem_start
op_assign
id|sony535_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
macro_line|#ifdef CONFIG_CDU31A
id|mem_start
op_assign
id|cdu31a_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CDU535
id|mem_start
op_assign
id|sony535_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif  /* CONFIG_CDU31A &amp;&amp; CONFIG_CDU535 */
macro_line|#ifdef CONFIG_MCD
id|mem_start
op_assign
id|mcd_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AZTCD
id|mem_start
op_assign
id|aztcd_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|floppy_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|outb_p
c_func
(paren
l_int|0xc
comma
l_int|0x3f2
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SBPCD
id|mem_start
op_assign
id|sbpcd_init
c_func
(paren
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
macro_line|#endif CONFIG_SBPCD
r_if
c_cond
(paren
id|ramdisk_size
)paren
id|mem_start
op_add_assign
id|rd_init
c_func
(paren
id|mem_start
comma
id|ramdisk_size
op_star
l_int|1024
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
eof
