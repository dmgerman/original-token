macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
DECL|macro|NR_BLK_DEV
mdefine_line|#define NR_BLK_DEV&t;7
DECL|macro|NR_REQUEST
mdefine_line|#define NR_REQUEST&t;64
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
DECL|member|next
r_struct
id|request
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IN_ORDER
mdefine_line|#define IN_ORDER(s1,s2) &bslash;&n;((s1)-&gt;dev &lt; (s2)-&gt;dev || ((s1)-&gt;dev == (s2)-&gt;dev &amp;&amp; &bslash;&n;(s1)-&gt;sector &lt; (s2)-&gt;sector))
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
macro_line|#ifdef MAJOR_NR
multiline_comment|/*&n; * Add entries as needed. Currently the only block devices&n; * supported are hard-disks and floppies.&n; */
macro_line|#if (MAJOR_NR == 2)
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
multiline_comment|/* harddisk */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;harddisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_hd
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_hd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device)/5)
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
id|DEVICE_OFF
c_func
(paren
id|CURRENT-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;bh
)paren
(brace
id|CURRENT-&gt;bh-&gt;b_uptodate
op_assign
id|uptodate
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|CURRENT-&gt;bh
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
id|CURRENT-&gt;dev
comma
id|CURRENT-&gt;bh-&gt;b_blocknr
)paren
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|CURRENT-&gt;waiting
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
id|CURRENT-&gt;dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|CURRENT
op_assign
id|CURRENT-&gt;next
suffix:semicolon
)brace
DECL|macro|INIT_REQUEST
mdefine_line|#define INIT_REQUEST &bslash;&n;repeat: &bslash;&n;&t;if (!CURRENT) &bslash;&n;&t;&t;return; &bslash;&n;&t;if (MAJOR(CURRENT-&gt;dev) != MAJOR_NR) &bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;); &bslash;&n;&t;if (CURRENT-&gt;bh) &bslash;&n;&t;&t;if (!CURRENT-&gt;bh-&gt;b_lock) &bslash;&n;&t;&t;&t;panic(DEVICE_NAME &quot;: block not locked&quot;); &bslash;&n;&t;&t;else { &bslash;&n;&t;&t;&t;CURRENT-&gt;bh-&gt;b_dirt = 0; &bslash;&n;&t;&t;&t;CURRENT-&gt;bh-&gt;b_uptodate = 0; &bslash;&n;&t;&t;}
macro_line|#endif
macro_line|#endif
eof
