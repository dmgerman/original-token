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
macro_line|#include &lt;linux/blk.h&gt;
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
multiline_comment|/* blk_dev_struct is:&n; *&t;*request_fn&n; *&t;*current_request&n; */
DECL|variable|blk_dev
r_struct
id|blk_dev_struct
id|blk_dev
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
multiline_comment|/* initialized by blk_dev_init() */
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
multiline_comment|/*&n; * remove the plug and let it rip..&n; */
DECL|function|unplug_device
r_static
r_void
id|unplug_device
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|blk_dev_struct
op_star
id|dev
op_assign
(paren
r_struct
id|blk_dev_struct
op_star
)paren
id|data
suffix:semicolon
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
id|dev-&gt;current_request
op_assign
id|dev-&gt;plug.next
suffix:semicolon
id|dev-&gt;plug.next
op_assign
l_int|NULL
suffix:semicolon
(paren
id|dev-&gt;request_fn
)paren
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * &quot;plug&quot; the device if there are no outstanding requests: this will&n; * force the transfer to start only after we have put all the requests&n; * on the list.&n; *&n; * Note! We can do the check without interrupts off, because interrupts&n; * will never add a new request to the queue, only take requests off.. &n; */
DECL|function|plug_device
r_static
r_inline
r_void
id|plug_device
c_func
(paren
r_struct
id|blk_dev_struct
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;current_request
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
id|dev-&gt;current_request
op_assign
op_amp
id|dev-&gt;plug
suffix:semicolon
id|queue_task_irq_off
c_func
(paren
op_amp
id|dev-&gt;plug_tq
comma
op_amp
id|tq_scheduler
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
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
id|kdev_t
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
id|req-&gt;rq_status
op_eq
id|RQ_INACTIVE
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
id|req-&gt;rq_status
op_assign
id|RQ_ACTIVE
suffix:semicolon
id|req-&gt;rq_dev
op_assign
id|dev
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
multiline_comment|/*&n; * wait until a free request in the first N entries is available.&n; */
DECL|function|__get_request_wait
r_static
r_struct
id|request
op_star
id|__get_request_wait
c_func
(paren
r_int
id|n
comma
id|kdev_t
id|dev
)paren
(brace
r_register
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|wait_for_request
comma
op_amp
id|wait
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
op_assign
id|get_request
c_func
(paren
id|n
comma
id|dev
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|wait_for_request
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
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
id|kdev_t
id|dev
)paren
(brace
r_register
r_struct
id|request
op_star
id|req
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
op_assign
id|get_request
c_func
(paren
id|n
comma
id|dev
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
)paren
r_return
id|req
suffix:semicolon
r_return
id|__get_request_wait
c_func
(paren
id|n
comma
id|dev
)paren
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
id|kdev_t
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
id|kdev_t
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
DECL|function|drive_stat_acct
r_static
r_inline
r_void
id|drive_stat_acct
c_func
(paren
r_int
id|cmd
comma
r_int
r_int
id|nr_sectors
comma
r_int
id|disk_index
)paren
(brace
id|kstat.dk_drive
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|kstat.dk_drive_rio
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
id|kstat.dk_drive_rblk
(braket
id|disk_index
)braket
op_add_assign
id|nr_sectors
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
op_eq
id|WRITE
)paren
(brace
id|kstat.dk_drive_wio
(braket
id|disk_index
)braket
op_increment
suffix:semicolon
id|kstat.dk_drive_wblk
(braket
id|disk_index
)braket
op_add_assign
id|nr_sectors
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;drive_stat_acct: cmd not R/W?&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * add-request adds a request to the linked list.&n; * It disables interrupts so that it can muck with the&n; * request-lists in peace.&n; *&n; * By this point, req-&gt;cmd is always either READ/WRITE, never READA/WRITEA,&n; * which is important for drive_stat_acct() above.&n; */
DECL|variable|request_lock
r_struct
id|semaphore
id|request_lock
op_assign
id|MUTEX
suffix:semicolon
DECL|function|add_request
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
id|down
(paren
op_amp
id|request_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
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
id|req-&gt;rq_dev
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
id|drive_stat_acct
c_func
(paren
id|req-&gt;cmd
comma
id|req-&gt;nr_sectors
comma
id|disk_index
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IDE0_MAJOR
suffix:colon
multiline_comment|/* same as HD_MAJOR */
r_case
id|XT_DISK_MAJOR
suffix:colon
id|disk_index
op_assign
(paren
id|MINOR
c_func
(paren
id|req-&gt;rq_dev
)paren
op_amp
l_int|0x0040
)paren
op_rshift
l_int|6
suffix:semicolon
id|drive_stat_acct
c_func
(paren
id|req-&gt;cmd
comma
id|req-&gt;nr_sectors
comma
id|disk_index
)paren
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
id|req-&gt;rq_dev
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
id|drive_stat_acct
c_func
(paren
id|req-&gt;cmd
comma
id|req-&gt;nr_sectors
comma
id|disk_index
)paren
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
op_logical_and
id|req-&gt;bh-&gt;b_dev
op_eq
id|req-&gt;bh-&gt;b_rdev
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
id|up
(paren
op_amp
id|request_lock
)paren
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
id|up
(paren
op_amp
id|request_lock
)paren
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
id|req-&gt;rq_dev
)paren
)paren
op_logical_and
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
)paren
op_ne
id|MD_MAJOR
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
id|bh-&gt;b_state
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;attempt to access beyond end of device&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: rw=%d, want=%d, limit=%d&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|bh-&gt;b_dev
)paren
comma
id|rw
comma
(paren
id|sector
op_plus
id|count
)paren
op_rshift
l_int|1
comma
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
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Uhhuh.. Nasty dead-lock possible here.. */
r_if
c_cond
(paren
id|buffer_locked
c_func
(paren
id|bh
)paren
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
id|rw_ahead
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* normal case; gets changed below for READA/WRITEA */
r_switch
c_cond
(paren
id|rw
)paren
(brace
r_case
id|READA
suffix:colon
id|rw_ahead
op_assign
l_int|1
suffix:semicolon
id|rw
op_assign
id|READ
suffix:semicolon
multiline_comment|/* drop into READ */
r_case
id|READ
suffix:colon
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* Hmmph! Already have it */
r_return
suffix:semicolon
)brace
id|kstat.pgpgin
op_increment
suffix:semicolon
id|max_req
op_assign
id|NR_REQUEST
suffix:semicolon
multiline_comment|/* reads take precedence */
r_break
suffix:semicolon
r_case
id|WRITEA
suffix:colon
id|rw_ahead
op_assign
l_int|1
suffix:semicolon
id|rw
op_assign
id|WRITE
suffix:semicolon
multiline_comment|/* drop into WRITE */
r_case
id|WRITE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* Hmmph! Nothing to write */
r_return
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t allow the write-requests to fill up the&n;&t;&t;&t; * queue completely:  we want some room for reads,&n;&t;&t;&t; * as they take precedence. The last third of the&n;&t;&t;&t; * requests are only for reads.&n;&t;&t;&t; */
id|kstat.pgpgout
op_increment
suffix:semicolon
id|max_req
op_assign
(paren
id|NR_REQUEST
op_star
l_int|2
)paren
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;make_request: bad block dev cmd, must be R/W/RA/WA&bslash;n&quot;
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
multiline_comment|/* look for a free request. */
id|down
(paren
op_amp
id|request_lock
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The scsi disk and cdrom drivers completely remove the request&n; * from the queue when they start processing an entry.  For this reason&n; * it is safe to continue to add links to the top entry for those devices.&n; */
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
id|MD_MAJOR
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
op_logical_or
id|major
op_eq
id|IDE2_MAJOR
op_logical_or
id|major
op_eq
id|IDE3_MAJOR
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
r_if
c_cond
(paren
id|major
op_ne
id|SCSI_DISK_MAJOR
op_logical_and
id|major
op_ne
id|SCSI_CDROM_MAJOR
op_logical_and
id|major
op_ne
id|MD_MAJOR
)paren
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
id|req-&gt;rq_dev
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
id|up
(paren
op_amp
id|request_lock
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
id|req-&gt;rq_dev
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
id|up
(paren
op_amp
id|request_lock
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
id|req
op_assign
id|req-&gt;next
suffix:semicolon
)brace
)brace
id|up
(paren
op_amp
id|request_lock
)paren
suffix:semicolon
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
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if no request available: if rw_ahead, forget it; otherwise try again blocking.. */
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
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|req
op_assign
id|__get_request_wait
c_func
(paren
id|max_req
comma
id|bh-&gt;b_dev
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_BLK_DEV_MD
DECL|function|get_md_request
r_struct
id|request
op_star
id|get_md_request
(paren
r_int
id|max_req
comma
id|kdev_t
id|dev
)paren
(brace
r_return
(paren
id|get_request_wait
(paren
id|max_req
comma
id|dev
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Swap partitions are now read via brw_page.  ll_rw_page is an&n; * asynchronous function now --- we must call wait_on_page afterwards&n; * if synchronous IO is required.  &n; */
DECL|function|ll_rw_page
r_void
id|ll_rw_page
c_func
(paren
r_int
id|rw
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|page
comma
r_char
op_star
id|buffer
)paren
(brace
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
r_int
id|block
op_assign
id|page
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
l_string|&quot;Trying to read nonexistent block-device %s (%ld)&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|rw
)paren
(brace
r_case
id|READ
suffix:colon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
r_if
c_cond
(paren
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
l_string|&quot;Can&squot;t page to read-only device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;ll_rw_page: bad block dev cmd, must be R/W&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|buffer
)paren
)braket
dot
id|locked
)paren
id|panic
(paren
l_string|&quot;ll_rw_page: page already locked&quot;
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|buffer
)paren
)braket
dot
id|locked
op_assign
l_int|1
suffix:semicolon
id|brw_page
c_func
(paren
id|rw
comma
(paren
r_int
r_int
)paren
id|buffer
comma
id|dev
comma
op_amp
id|block
comma
id|PAGE_SIZE
comma
l_int|0
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
l_string|&quot;ll_rw_block: Trying to read nonexistent block-device %s (%ld)&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
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
l_string|&quot;ll_rw_block: device %s: &quot;
l_string|&quot;only %d-char blocks implemented (%lu)&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_dev
)paren
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
l_string|&quot;Can&squot;t write to read-only device %s&bslash;n&quot;
comma
id|kdevname
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
suffix:semicolon
r_goto
id|sorry
suffix:semicolon
)brace
multiline_comment|/* If there are no pending requests for this device, then we insert&n;&t;   a dummy request for that device.  This will prevent the request&n;&t;   from starting until we have shoved all of the blocks into the&n;&t;   queue, and then we let it rip.  */
id|plug_device
c_func
(paren
id|dev
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
id|set_bit
c_func
(paren
id|BH_Req
comma
op_amp
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
multiline_comment|/* Md needs this for error recovery */
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_rdev
op_assign
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_dev
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
)brace
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
(brace
id|clear_bit
c_func
(paren
id|BH_Dirty
comma
op_amp
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BH_Uptodate
comma
op_amp
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
)brace
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
id|kdev_t
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
comma
id|j
suffix:semicolon
r_int
id|buffersize
suffix:semicolon
r_struct
id|request
op_star
id|req
(braket
l_int|8
)braket
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
r_switch
c_cond
(paren
id|rw
)paren
(brace
r_case
id|READ
suffix:colon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
r_if
c_cond
(paren
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
l_string|&quot;Can&squot;t swap to read-only device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;ll_rw_swap: bad block dev cmd, must be R/W&quot;
)paren
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
id|j
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
l_int|8
op_logical_and
id|i
OL
id|nb
suffix:semicolon
id|j
op_increment
comma
id|i
op_increment
comma
id|buf
op_add_assign
id|buffersize
)paren
(brace
r_if
c_cond
(paren
id|j
op_eq
l_int|0
)paren
(brace
id|req
(braket
id|j
)braket
op_assign
id|get_request_wait
c_func
(paren
id|NR_REQUEST
comma
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
(braket
id|j
)braket
op_assign
id|get_request
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
r_if
c_cond
(paren
id|req
(braket
id|j
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|cmd
op_assign
id|rw
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|errors
op_assign
l_int|0
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|sector
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
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|nr_sectors
op_assign
id|buffersize
op_rshift
l_int|9
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|current_nr_sectors
op_assign
id|buffersize
op_rshift
l_int|9
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|buffer
op_assign
id|buf
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|sem
op_assign
op_amp
id|sem
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|req
(braket
id|j
)braket
op_member_access_from_pointer
id|next
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
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|j
OG
l_int|0
)paren
(brace
id|j
op_decrement
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
)brace
DECL|function|blk_dev_init
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|blk_dev_struct
op_star
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|blk_dev
op_plus
id|MAX_BLKDEV
suffix:semicolon
id|dev
op_decrement
op_ne
id|blk_dev
suffix:semicolon
)paren
(brace
id|dev-&gt;request_fn
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;current_request
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;plug.rq_status
op_assign
id|RQ_INACTIVE
suffix:semicolon
id|dev-&gt;plug.cmd
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;plug.next
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;plug_tq.routine
op_assign
op_amp
id|unplug_device
suffix:semicolon
id|dev-&gt;plug_tq.data
op_assign
id|dev
suffix:semicolon
)brace
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
id|req-&gt;rq_status
op_assign
id|RQ_INACTIVE
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
macro_line|#ifdef CONFIG_BLK_DEV_RAM
id|rd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_LOOP
id|loop_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* this MUST preceed hd_init */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_HD
id|hd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_XD
id|xd_init
c_func
(paren
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
macro_line|#ifdef CONFIG_CDI_INIT
id|cdi_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDI_INIT
macro_line|#ifdef CONFIG_CDU31A
id|cdu31a_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDU31A
macro_line|#ifdef CONFIG_MCD
id|mcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_MCD
macro_line|#ifdef CONFIG_MCDX
id|mcdx_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_MCDX
macro_line|#ifdef CONFIG_SBPCD
id|sbpcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_SBPCD
macro_line|#ifdef CONFIG_AZTCD
id|aztcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_AZTCD
macro_line|#ifdef CONFIG_CDU535
id|sony535_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDU535
macro_line|#ifdef CONFIG_GSCD
id|gscd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_GSCD
macro_line|#ifdef CONFIG_CM206
id|cm206_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_OPTCD
id|optcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_OPTCD
macro_line|#ifdef CONFIG_SJCD
id|sjcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_SJCD
macro_line|#ifdef CONFIG_BLK_DEV_MD
id|md_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_BLK_DEV_MD
r_return
l_int|0
suffix:semicolon
)brace
eof
