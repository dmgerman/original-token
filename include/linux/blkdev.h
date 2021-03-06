macro_line|#ifndef _LINUX_BLKDEV_H
DECL|macro|_LINUX_BLKDEV_H
mdefine_line|#define _LINUX_BLKDEV_H
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/list.h&gt;
r_struct
id|request_queue
suffix:semicolon
DECL|typedef|request_queue_t
r_typedef
r_struct
id|request_queue
id|request_queue_t
suffix:semicolon
r_struct
id|elevator_s
suffix:semicolon
DECL|typedef|elevator_t
r_typedef
r_struct
id|elevator_s
id|elevator_t
suffix:semicolon
multiline_comment|/*&n; * Ok, this is an expanded form so that we can use the same&n; * request for paging requests when that is implemented. In&n; * paging, &squot;bh&squot; is NULL, and the semaphore is used to wait&n; * for read/write completion.&n; */
DECL|struct|request
r_struct
id|request
(brace
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|elevator_sequence
r_int
id|elevator_sequence
suffix:semicolon
DECL|member|table
r_struct
id|list_head
id|table
suffix:semicolon
DECL|member|free_list
r_struct
id|list_head
op_star
id|free_list
suffix:semicolon
DECL|member|rq_status
r_volatile
r_int
id|rq_status
suffix:semicolon
multiline_comment|/* should split this into a few status bits */
DECL|macro|RQ_INACTIVE
mdefine_line|#define RQ_INACTIVE&t;&t;(-1)
DECL|macro|RQ_ACTIVE
mdefine_line|#define RQ_ACTIVE&t;&t;1
DECL|macro|RQ_SCSI_BUSY
mdefine_line|#define RQ_SCSI_BUSY&t;&t;0xffff
DECL|macro|RQ_SCSI_DONE
mdefine_line|#define RQ_SCSI_DONE&t;&t;0xfffe
DECL|macro|RQ_SCSI_DISCONNECTING
mdefine_line|#define RQ_SCSI_DISCONNECTING&t;0xffe0
DECL|member|rq_dev
id|kdev_t
id|rq_dev
suffix:semicolon
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
DECL|member|hard_sector
DECL|member|hard_nr_sectors
r_int
r_int
id|hard_sector
comma
id|hard_nr_sectors
suffix:semicolon
DECL|member|nr_segments
r_int
r_int
id|nr_segments
suffix:semicolon
DECL|member|nr_hw_segments
r_int
r_int
id|nr_hw_segments
suffix:semicolon
DECL|member|current_nr_sectors
r_int
r_int
id|current_nr_sectors
suffix:semicolon
DECL|member|special
r_void
op_star
id|special
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
op_star
id|sem
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
DECL|member|q
id|request_queue_t
op_star
id|q
suffix:semicolon
DECL|member|e
id|elevator_t
op_star
id|e
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;linux/elevator.h&gt;
DECL|typedef|merge_request_fn
r_typedef
r_int
(paren
id|merge_request_fn
)paren
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
)paren
suffix:semicolon
DECL|typedef|merge_requests_fn
r_typedef
r_int
(paren
id|merge_requests_fn
)paren
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
comma
r_struct
id|request
op_star
id|req2
comma
r_int
)paren
suffix:semicolon
DECL|typedef|request_fn_proc
r_typedef
r_void
(paren
id|request_fn_proc
)paren
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
DECL|typedef|queue_proc
r_typedef
id|request_queue_t
op_star
(paren
id|queue_proc
)paren
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
DECL|typedef|make_request_fn
r_typedef
r_int
(paren
id|make_request_fn
)paren
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|typedef|plug_device_fn
r_typedef
r_void
(paren
id|plug_device_fn
)paren
(paren
id|request_queue_t
op_star
id|q
comma
id|kdev_t
id|device
)paren
suffix:semicolon
DECL|typedef|unplug_device_fn
r_typedef
r_void
(paren
id|unplug_device_fn
)paren
(paren
r_void
op_star
id|q
)paren
suffix:semicolon
multiline_comment|/*&n; * Default nr free requests per queue&n; */
DECL|macro|QUEUE_NR_REQUESTS
mdefine_line|#define QUEUE_NR_REQUESTS&t;256
DECL|struct|request_queue
r_struct
id|request_queue
(brace
multiline_comment|/*&n;&t; * the queue request freelist, one for reads and one for writes&n;&t; */
DECL|member|request_freelist
r_struct
id|list_head
id|request_freelist
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Together with queue_head for cacheline sharing&n;&t; */
DECL|member|queue_head
r_struct
id|list_head
id|queue_head
suffix:semicolon
DECL|member|elevator
id|elevator_t
id|elevator
suffix:semicolon
DECL|member|request_fn
id|request_fn_proc
op_star
id|request_fn
suffix:semicolon
DECL|member|back_merge_fn
id|merge_request_fn
op_star
id|back_merge_fn
suffix:semicolon
DECL|member|front_merge_fn
id|merge_request_fn
op_star
id|front_merge_fn
suffix:semicolon
DECL|member|merge_requests_fn
id|merge_requests_fn
op_star
id|merge_requests_fn
suffix:semicolon
DECL|member|make_request_fn
id|make_request_fn
op_star
id|make_request_fn
suffix:semicolon
DECL|member|plug_device_fn
id|plug_device_fn
op_star
id|plug_device_fn
suffix:semicolon
multiline_comment|/*&n;&t; * The queue owner gets to use this for whatever they like.&n;&t; * ll_rw_blk doesn&squot;t touch it.&n;&t; */
DECL|member|queuedata
r_void
op_star
id|queuedata
suffix:semicolon
multiline_comment|/*&n;&t; * This is used to remove the plug when tq_disk runs.&n;&t; */
DECL|member|plug_tq
r_struct
id|tq_struct
id|plug_tq
suffix:semicolon
multiline_comment|/*&n;&t; * Boolean that indicates whether this queue is plugged or not.&n;&t; */
DECL|member|plugged
r_char
id|plugged
suffix:semicolon
multiline_comment|/*&n;&t; * Boolean that indicates whether current_request is active or&n;&t; * not.&n;&t; */
DECL|member|head_active
r_char
id|head_active
suffix:semicolon
multiline_comment|/*&n;&t; * Is meant to protect the queue in the future instead of&n;&t; * io_request_lock&n;&t; */
DECL|member|request_lock
id|spinlock_t
id|request_lock
suffix:semicolon
multiline_comment|/*&n;&t; * Tasks wait here for free request&n;&t; */
DECL|member|wait_for_request
id|wait_queue_head_t
id|wait_for_request
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|blk_dev_struct
r_struct
id|blk_dev_struct
(brace
multiline_comment|/*&n;&t; * queue_proc has to be atomic&n;&t; */
DECL|member|request_queue
id|request_queue_t
id|request_queue
suffix:semicolon
DECL|member|queue
id|queue_proc
op_star
id|queue
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
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
multiline_comment|/*&n; * Used to indicate the default queue for drivers that don&squot;t bother&n; * to implement multiple queues.  We have this access macro here&n; * so as to eliminate the need for each and every block device&n; * driver to know about the internal structure of blk_dev[].&n; */
DECL|macro|BLK_DEFAULT_QUEUE
mdefine_line|#define BLK_DEFAULT_QUEUE(_MAJOR)  &amp;blk_dev[_MAJOR].request_queue
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
r_void
id|grok_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|drive
comma
r_int
id|minors
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|register_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
comma
id|kdev_t
id|first
comma
r_int
id|minors
comma
r_struct
id|block_device_operations
op_star
id|ops
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|generic_make_request
c_func
(paren
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
id|request_queue_t
op_star
id|blk_get_queue
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|blkdev_release_request
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Access functions for manipulating queue properties&n; */
r_extern
r_void
id|blk_init_queue
c_func
(paren
id|request_queue_t
op_star
comma
id|request_fn_proc
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_cleanup_queue
c_func
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_headactive
c_func
(paren
id|request_queue_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_pluggable
c_func
(paren
id|request_queue_t
op_star
comma
id|plug_device_fn
op_star
)paren
suffix:semicolon
r_extern
r_void
id|blk_queue_make_request
c_func
(paren
id|request_queue_t
op_star
comma
id|make_request_fn
op_star
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
op_star
id|hardsect_size
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_int
op_star
id|max_readahead
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_int
op_star
id|max_sectors
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
r_extern
r_int
op_star
id|max_segments
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
DECL|macro|MAX_SECTORS
mdefine_line|#define MAX_SECTORS 254
DECL|macro|MAX_SEGMENTS
mdefine_line|#define MAX_SEGMENTS MAX_SECTORS
DECL|macro|PageAlignSize
mdefine_line|#define PageAlignSize(size) (((size) + PAGE_SIZE -1) &amp; PAGE_MASK)
multiline_comment|/* read-ahead in pages.. */
DECL|macro|MAX_READAHEAD
mdefine_line|#define MAX_READAHEAD&t;31
DECL|macro|MIN_READAHEAD
mdefine_line|#define MIN_READAHEAD&t;3
DECL|macro|blkdev_entry_to_request
mdefine_line|#define blkdev_entry_to_request(entry) list_entry((entry), struct request, queue)
DECL|macro|blkdev_entry_next_request
mdefine_line|#define blkdev_entry_next_request(entry) blkdev_entry_to_request((entry)-&gt;next)
DECL|macro|blkdev_entry_prev_request
mdefine_line|#define blkdev_entry_prev_request(entry) blkdev_entry_to_request((entry)-&gt;prev)
DECL|macro|blkdev_next_request
mdefine_line|#define blkdev_next_request(req) blkdev_entry_to_request((req)-&gt;queue.next)
DECL|macro|blkdev_prev_request
mdefine_line|#define blkdev_prev_request(req) blkdev_entry_to_request((req)-&gt;queue.prev)
r_extern
r_void
id|drive_stat_acct
(paren
id|kdev_t
id|dev
comma
r_int
id|rw
comma
r_int
r_int
id|nr_sectors
comma
r_int
id|new_io
)paren
suffix:semicolon
DECL|function|get_hardsect_size
r_static
r_inline
r_int
id|get_hardsect_size
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_extern
r_int
op_star
id|hardsect_size
(braket
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hardsect_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_ne
l_int|NULL
)paren
r_return
id|hardsect_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_else
r_return
l_int|512
suffix:semicolon
)brace
macro_line|#endif
eof
