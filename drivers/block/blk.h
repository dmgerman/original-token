macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
multiline_comment|/*&n; * NR_REQUEST is the number of entries in the request-queue.&n; * NOTE that writes may use only the low 2/3 of these: reads&n; * take precedence.&n; *&n; * 32 seems to be a reasonable number: enough to get some benefit&n; * from the elevator-mechanism, but not so much as to lock a lot of&n; * buffers when they are in the queue. 64 seems to be too many (easily&n; * long pauses in reading when heavy writing/syncing is going on)&n; */
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
DECL|member|current_nr_sectors
r_int
r_int
id|current_nr_sectors
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
mdefine_line|#define IN_ORDER(s1,s2) &bslash;&n;((s1)-&gt;cmd &lt; (s2)-&gt;cmd || ((s1)-&gt;cmd == (s2)-&gt;cmd &amp;&amp; &bslash;&n;((s1)-&gt;dev &lt; (s2)-&gt;dev || (((s1)-&gt;dev == (s2)-&gt;dev &amp;&amp; &bslash;&n;(s1)-&gt;sector &lt; (s2)-&gt;sector)))))
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
DECL|struct|sec_size
r_struct
id|sec_size
(brace
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|block_size_bits
r_int
id|block_size_bits
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * These will have to be changed to be aware of different buffer&n; * sizes etc.. It actually needs a major cleanup.&n; */
DECL|macro|SECTOR_MASK
mdefine_line|#define SECTOR_MASK (blksize_size[MAJOR_NR] &amp;&amp;     &bslash;&n;&t;blksize_size[MAJOR_NR][MINOR(CURRENT-&gt;dev)] ? &bslash;&n;&t;((blksize_size[MAJOR_NR][MINOR(CURRENT-&gt;dev)] &gt;&gt; 9) - 1) :  &bslash;&n;&t;((BLOCK_SIZE &gt;&gt; 9)  -  1))
DECL|macro|SUBSECTOR
mdefine_line|#define SUBSECTOR(block) (CURRENT-&gt;current_nr_sectors &gt; 0)
r_extern
r_struct
id|sec_size
op_star
id|blk_sec
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_struct
id|blk_dev_struct
id|blk_dev
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_struct
id|wait_queue
op_star
id|wait_for_request
suffix:semicolon
r_extern
r_void
id|resetup_one_dev
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|drive
)paren
suffix:semicolon
r_extern
r_int
op_star
id|blk_size
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_int
op_star
id|blksize_size
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_int
r_int
id|hd_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
r_extern
r_int
r_int
id|cdu31a_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mcd_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SBPCD
r_extern
r_int
r_int
id|sbpcd_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif CONFIG_SBPCD
r_extern
r_int
id|is_read_only
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|rd_load
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rd_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|ramdisk_size
suffix:semicolon
r_extern
r_int
r_int
id|xd_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
DECL|macro|RO_IOCTLS
mdefine_line|#define RO_IOCTLS(dev,where) &bslash;&n;  case BLKROSET: if (!suser()) return -EPERM; &bslash;&n;&t;&t; set_device_ro((dev),get_fs_long((long *) (where))); return 0; &bslash;&n;  case BLKROGET: { int __err = verify_area(VERIFY_WRITE, (void *) (where), sizeof(long)); &bslash;&n;&t;&t;   if (!__err) put_fs_long(is_read_only(dev),(long *) (where)); return __err; }
macro_line|#ifdef MAJOR_NR
multiline_comment|/*&n; * Add entries as needed. Currently the only block devices&n; * supported are hard-disks and floppies.&n; */
macro_line|#if (MAJOR_NR == MEM_MAJOR)
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
macro_line|#elif (MAJOR_NR == FLOPPY_MAJOR)
r_static
r_void
id|floppy_on
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_static
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
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
macro_line|#elif (MAJOR_NR == HD_MAJOR)
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
macro_line|#elif (MAJOR_NR == SCSI_DISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsidisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_sd  
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE 200
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 4)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SCSI_TAPE_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsitape&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_st  
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SCSI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CD-ROM&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_sr
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sr_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == XT_DISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;xt disk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_xd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 6)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == CDU31A_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CDU31A&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cdu31a_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MITSUMI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Mitsumi CD-ROM&quot;
multiline_comment|/* #define DEVICE_INTR do_mcd */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#else
macro_line|#error &quot;unknown blk device&quot;
macro_line|#endif
macro_line|#if (MAJOR_NR != SCSI_TAPE_MAJOR)
macro_line|#ifndef CURRENT
DECL|macro|CURRENT
mdefine_line|#define CURRENT (blk_dev[MAJOR_NR].current_request)
macro_line|#endif
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
mdefine_line|#define SET_INTR(x) &bslash;&n;if ((DEVICE_INTR = (x)) != NULL) &bslash;&n;&t;SET_TIMER; &bslash;&n;else &bslash;&n;&t;CLEAR_TIMER;
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
multiline_comment|/* end_request() - SCSI devices have their own version */
macro_line|#if ! SCSI_MAJOR(MAJOR_NR)
DECL|function|end_request
r_static
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
id|req
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|req
op_assign
id|CURRENT
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
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
l_string|&quot; I/O error&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dev %04lX, sector %lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|req-&gt;dev
comma
id|req-&gt;sector
)paren
suffix:semicolon
id|req-&gt;nr_sectors
op_decrement
suffix:semicolon
id|req-&gt;nr_sectors
op_and_assign
op_complement
id|SECTOR_MASK
suffix:semicolon
id|req-&gt;sector
op_add_assign
(paren
id|BLOCK_SIZE
op_div
l_int|512
)paren
suffix:semicolon
id|req-&gt;sector
op_and_assign
op_complement
id|SECTOR_MASK
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
id|uptodate
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;current_nr_sectors
op_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;nr_sectors
OL
id|req-&gt;current_nr_sectors
)paren
(brace
id|req-&gt;nr_sectors
op_assign
id|req-&gt;current_nr_sectors
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;end_request: buffer-list destroyed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|DEVICE_OFF
c_func
(paren
id|req-&gt;dev
)paren
suffix:semicolon
id|CURRENT
op_assign
id|req-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|req-&gt;waiting
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;waiting
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;counter
OG
id|current-&gt;counter
)paren
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
id|req-&gt;dev
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
macro_line|#endif
macro_line|#ifdef DEVICE_INTR
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR SET_INTR(NULL)
macro_line|#else
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR
macro_line|#endif
DECL|macro|INIT_REQUEST
mdefine_line|#define INIT_REQUEST &bslash;&n;&t;if (!CURRENT) {&bslash;&n;&t;&t;CLEAR_INTR; &bslash;&n;&t;&t;return; &bslash;&n;&t;} &bslash;&n;&t;if (MAJOR(CURRENT-&gt;dev) != MAJOR_NR) &bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;); &bslash;&n;&t;if (CURRENT-&gt;bh) { &bslash;&n;&t;&t;if (!CURRENT-&gt;bh-&gt;b_lock) &bslash;&n;&t;&t;&t;panic(DEVICE_NAME &quot;: block not locked&quot;); &bslash;&n;&t;}
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
