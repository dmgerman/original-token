macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
DECL|macro|NR_BLK_DEV
mdefine_line|#define NR_BLK_DEV&t;10
multiline_comment|/*&n; * NR_REQUEST is the number of entries in the request-queue.&n; * NOTE that writes may use only the low 2/3 of these: reads&n; * take precedence.&n; *&n; * 32 seems to be a reasonable number: enough to get some benefit&n; * from the elevator-mechanism, but not so much as to lock a lot of&n; * buffers when they are in the queue. 64 seems to be too many (easily&n; * long pauses in reading when heavy writing/syncing is going on)&n; */
DECL|macro|NR_REQUEST
mdefine_line|#define NR_REQUEST&t;32
multiline_comment|/*&n; * Ok, this is an expanded form so that we can use the same&n; * request for paging requests when that is implemented. In&n; * paging, &squot;bh&squot; is NULL, and &squot;waiting&squot; is used to wait for&n; * read/write completion.&n; */
DECL|struct|request
r_struct
id|request
(brace
DECL|member|dev
r_int
id|dev
suffix:semicolon
multiline_comment|/* -1 if no request */
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* READ or WRITE */
DECL|member|errors
r_int
id|errors
suffix:semicolon
DECL|member|sector
r_int
r_int
id|sector
suffix:semicolon
DECL|member|nr_sectors
r_int
r_int
id|nr_sectors
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|waiting
r_struct
id|task_struct
op_star
id|waiting
suffix:semicolon
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
DECL|member|bhtail
r_struct
id|buffer_head
op_star
id|bhtail
suffix:semicolon
DECL|member|next
r_struct
id|request
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is used in the elevator algorithm: Note that&n; * reads always go before writes. This is natural: reads&n; * are much more time-critical than writes.&n; */
DECL|macro|IN_ORDER
mdefine_line|#define IN_ORDER(s1,s2) &bslash;&n;((s1)-&gt;cmd&lt;(s2)-&gt;cmd || ((s1)-&gt;cmd==(s2)-&gt;cmd &amp;&amp; &bslash;&n;((s1)-&gt;dev &lt; (s2)-&gt;dev || (((s1)-&gt;dev == (s2)-&gt;dev &amp;&amp; &bslash;&n;(s1)-&gt;sector &lt; (s2)-&gt;sector)))))
DECL|struct|blk_dev_struct
r_struct
id|blk_dev_struct
(brace
DECL|member|request_fn
r_void
(paren
op_star
id|request_fn
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|current_request
r_struct
id|request
op_star
id|current_request
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|blk_dev_struct
id|blk_dev
(braket
id|NR_BLK_DEV
)braket
suffix:semicolon
r_extern
r_struct
id|request
id|request
(braket
id|NR_REQUEST
)braket
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|wait_for_request
suffix:semicolon
r_extern
r_int
op_star
id|blk_size
(braket
id|NR_BLK_DEV
)braket
suffix:semicolon
macro_line|#ifdef MAJOR_NR
multiline_comment|/*&n; * Add entries as needed. Currently the only block devices&n; * supported are hard-disks and floppies.&n; */
macro_line|#if (MAJOR_NR == 1)
multiline_comment|/* ram disk */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ramdisk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_rd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) ((device) &amp; 7)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) 
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == 2)
multiline_comment|/* floppy */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;floppy&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_floppy
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_fd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) ((device) &amp; 3)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) floppy_on(DEVICE_NR(device))
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device) floppy_off(DEVICE_NR(device))
macro_line|#elif (MAJOR_NR == 3)
multiline_comment|/* harddisk: timeout is 6 seconds.. */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;harddisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_hd
DECL|macro|DEVICE_TIMEOUT
mdefine_line|#define DEVICE_TIMEOUT HD_TIMER
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE 600
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_hd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device)&gt;&gt;6)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == 8)
multiline_comment|/* scsi disk */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsidisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_sd  
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 4)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == 9)
multiline_comment|/* scsi tape */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsitape&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_st  
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_st_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif
multiline_comment|/* unknown blk device */
macro_line|#error &quot;unknown blk device&quot;
macro_line|#endif
DECL|macro|CURRENT
mdefine_line|#define CURRENT (blk_dev[MAJOR_NR].current_request)
DECL|macro|CURRENT_DEV
mdefine_line|#define CURRENT_DEV DEVICE_NR(CURRENT-&gt;dev)
macro_line|#ifdef DEVICE_INTR
DECL|variable|DEVICE_INTR
r_void
(paren
op_star
id|DEVICE_INTR
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEVICE_TIMEOUT
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER &bslash;&n;((timer_table[DEVICE_TIMEOUT].expires = jiffies + TIMEOUT_VALUE), &bslash;&n;(timer_active |= 1&lt;&lt;DEVICE_TIMEOUT))
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER &bslash;&n;timer_active &amp;= ~(1&lt;&lt;DEVICE_TIMEOUT)
DECL|macro|SET_INTR
mdefine_line|#define SET_INTR(x) &bslash;&n;if (DEVICE_INTR = (x)) &bslash;&n;&t;SET_TIMER; &bslash;&n;else &bslash;&n;&t;CLEAR_TIMER;
macro_line|#else
DECL|macro|SET_INTR
mdefine_line|#define SET_INTR(x) (DEVICE_INTR = (x))
macro_line|#endif
r_static
r_void
(paren
id|DEVICE_REQUEST
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|unlock_buffer
r_extern
r_inline
r_void
id|unlock_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_lock
)paren
id|printk
c_func
(paren
id|DEVICE_NAME
l_string|&quot;: free buffer being unlocked&bslash;n&quot;
)paren
suffix:semicolon
id|bh-&gt;b_lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|bh-&gt;b_wait
)paren
suffix:semicolon
)brace
DECL|function|end_request
r_extern
r_inline
r_void
id|end_request
c_func
(paren
r_int
id|uptodate
)paren
(brace
r_struct
id|request
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|CURRENT
suffix:semicolon
id|DEVICE_OFF
c_func
(paren
id|tmp-&gt;dev
)paren
suffix:semicolon
id|CURRENT
op_assign
id|tmp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;bh
)paren
(brace
id|tmp-&gt;bh-&gt;b_uptodate
op_assign
id|uptodate
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|tmp-&gt;bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
(brace
id|printk
c_func
(paren
id|DEVICE_NAME
l_string|&quot; I/O error&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dev %04x, block %d&bslash;n&bslash;r&quot;
comma
id|tmp-&gt;dev
comma
id|tmp-&gt;bh-&gt;b_blocknr
)paren
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|tmp-&gt;waiting
)paren
suffix:semicolon
id|tmp-&gt;dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
)brace
DECL|function|next_buffer
r_extern
r_inline
r_void
id|next_buffer
c_func
(paren
r_int
id|uptodate
)paren
(brace
r_struct
id|buffer_head
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|CURRENT-&gt;bh
suffix:semicolon
id|CURRENT-&gt;bh
op_assign
id|tmp-&gt;b_reqnext
suffix:semicolon
id|tmp-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|tmp-&gt;b_uptodate
op_assign
id|uptodate
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
(brace
id|printk
c_func
(paren
id|DEVICE_NAME
l_string|&quot; I/O error&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dev %04x, block %d&bslash;n&bslash;r&quot;
comma
id|tmp-&gt;b_dev
comma
id|tmp-&gt;b_blocknr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|CURRENT-&gt;bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;next_buffer: request buffer list destroyed&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|CURRENT-&gt;buffer
op_assign
id|CURRENT-&gt;bh-&gt;b_data
suffix:semicolon
id|CURRENT-&gt;errors
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEVICE_INTR
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR SET_INTR(NULL)
macro_line|#else
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR
macro_line|#endif
DECL|macro|INIT_REQUEST
mdefine_line|#define INIT_REQUEST &bslash;&n;repeat: &bslash;&n;&t;if (!CURRENT) {&bslash;&n;&t;&t;CLEAR_INTR; &bslash;&n;&t;&t;return; &bslash;&n;&t;} &bslash;&n;&t;if (MAJOR(CURRENT-&gt;dev) != MAJOR_NR) &bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;); &bslash;&n;&t;if (CURRENT-&gt;bh) { &bslash;&n;&t;&t;if (!CURRENT-&gt;bh-&gt;b_lock) &bslash;&n;&t;&t;&t;panic(DEVICE_NAME &quot;: block not locked&quot;); &bslash;&n;&t;}
macro_line|#endif
macro_line|#endif
eof
