multiline_comment|/*&n; * queue.c: queue handling primitives&n; *&n; * (c) 1997 Russell King&n; *&n; * Changelog:&n; *  15-Sep-1997 RMK&t;Created.&n; *  11-Oct-1997&t;RMK&t;Corrected problem with queue_remove_exclude&n; *&t;&t;&t;not updating internal linked list properly&n; *&t;&t;&t;(was causing commands to go missing).&n; */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE 512
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCSI command queueing&quot;
)paren
suffix:semicolon
DECL|struct|queue_entry
r_typedef
r_struct
id|queue_entry
(brace
DECL|member|next
r_struct
id|queue_entry
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|queue_entry
op_star
id|prev
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
DECL|typedef|QE_t
)brace
id|QE_t
suffix:semicolon
DECL|macro|QUEUE_MAGIC_FREE
mdefine_line|#define QUEUE_MAGIC_FREE&t;0xf7e1c9a3
DECL|macro|QUEUE_MAGIC_USED
mdefine_line|#define QUEUE_MAGIC_USED&t;0xf7e1cc33
macro_line|#include &quot;queue.h&quot;
multiline_comment|/*&n; * Function: void queue_initialise (Queue_t *queue)&n; * Purpose : initialise a queue&n; * Params  : queue - queue to initialise&n; */
DECL|function|queue_initialise
r_int
id|queue_initialise
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_int
r_int
id|nqueues
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
id|queue-&gt;alloc
op_assign
id|queue-&gt;free
op_assign
id|q
op_assign
(paren
id|QE_t
op_star
)paren
id|kmalloc
(paren
id|SECTOR_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
id|nqueues
op_assign
id|SECTOR_SIZE
op_div
r_sizeof
(paren
id|QE_t
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|nqueues
suffix:semicolon
id|q
op_increment
comma
id|nqueues
op_decrement
)paren
(brace
id|q-&gt;next
op_assign
id|q
op_plus
l_int|1
suffix:semicolon
id|q-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_FREE
suffix:semicolon
id|q-&gt;SCpnt
op_assign
l_int|NULL
suffix:semicolon
)brace
id|q-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void queue_free (Queue_t *queue)&n; * Purpose : free a queue&n; * Params  : queue - queue to free&n; */
DECL|function|queue_free
r_void
id|queue_free
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_if
c_cond
(paren
id|queue-&gt;alloc
)paren
id|kfree
(paren
id|queue-&gt;alloc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_add_cmd_ordered (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : Add a new command onto a queue, adding REQUEST_SENSE to head.&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; * Returns : 0 on error, !0 on success&n; */
DECL|function|queue_add_cmd_ordered
r_int
id|queue_add_cmd_ordered
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
id|q
op_assign
id|queue-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
id|queue-&gt;free
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_FREE
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;scsi queues corrupted - queue entry not free&quot;
)paren
suffix:semicolon
)brace
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_USED
suffix:semicolon
id|q-&gt;SCpnt
op_assign
id|SCpnt
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|REQUEST_SENSE
)paren
(brace
multiline_comment|/* request_sense gets put on the queue head */
r_if
c_cond
(paren
id|queue-&gt;head
)paren
(brace
id|q-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;next
op_assign
id|queue-&gt;head
suffix:semicolon
id|queue-&gt;head-&gt;prev
op_assign
id|q
suffix:semicolon
id|queue-&gt;head
op_assign
id|q
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
op_assign
id|q-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
id|q
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* others get put on the tail */
r_if
c_cond
(paren
id|queue-&gt;tail
)paren
(brace
id|q-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;prev
op_assign
id|queue-&gt;tail
suffix:semicolon
id|queue-&gt;tail-&gt;next
op_assign
id|q
suffix:semicolon
id|queue-&gt;tail
op_assign
id|q
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
op_assign
id|q-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
id|q
suffix:semicolon
)brace
)brace
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_add_cmd_tail (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : Add a new command onto a queue, adding onto tail of list&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; * Returns : 0 on error, !0 on success&n; */
DECL|function|queue_add_cmd_tail
r_int
id|queue_add_cmd_tail
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
id|q
op_assign
id|queue-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
id|queue-&gt;free
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_FREE
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;scsi queues corrupted - queue entry not free&quot;
)paren
suffix:semicolon
)brace
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_USED
suffix:semicolon
id|q-&gt;SCpnt
op_assign
id|SCpnt
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;tail
)paren
(brace
id|q-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;prev
op_assign
id|queue-&gt;tail
suffix:semicolon
id|queue-&gt;tail-&gt;next
op_assign
id|q
suffix:semicolon
id|queue-&gt;tail
op_assign
id|q
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
op_assign
id|q-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
id|q
suffix:semicolon
)brace
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_exclude (queue, exclude)&n; * Purpose : remove a SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; *&t;     exclude - bit array of target&amp;lun which is busy&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
DECL|function|queue_remove_exclude
id|Scsi_Cmnd
op_star
id|queue_remove_exclude
(paren
id|Queue_t
op_star
id|queue
comma
r_int
r_char
op_star
id|exclude
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|QE_t
op_star
id|q
comma
op_star
id|prev
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|queue-&gt;head
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|exclude
op_logical_and
op_logical_neg
id|test_bit
(paren
id|q-&gt;SCpnt-&gt;target
op_star
l_int|8
op_plus
id|q-&gt;SCpnt-&gt;lun
comma
id|exclude
)paren
)paren
r_break
suffix:semicolon
id|prev
op_assign
id|q
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_USED
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;q_remove_exclude: scsi queues corrupted - queue entry not used&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q-&gt;prev
op_ne
id|prev
)paren
id|panic
(paren
l_string|&quot;q_remove_exclude: scsi queues corrupted - q-&gt;prev != prev&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
)paren
(brace
id|queue-&gt;head
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;head
)paren
id|queue-&gt;head-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;next
)paren
id|prev-&gt;next-&gt;prev
op_assign
id|prev
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
id|prev
suffix:semicolon
)brace
id|SCpnt
op_assign
id|q-&gt;SCpnt
suffix:semicolon
id|q-&gt;next
op_assign
id|queue-&gt;free
suffix:semicolon
id|queue-&gt;free
op_assign
id|q
suffix:semicolon
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_FREE
suffix:semicolon
)brace
r_else
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove (queue)&n; * Purpose : removes first SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
DECL|function|queue_remove
id|Scsi_Cmnd
op_star
id|queue_remove
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
id|q
op_assign
id|queue-&gt;head
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
id|queue-&gt;head
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;head
)paren
id|queue-&gt;head-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_USED
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;scsi queues corrupted - queue entry not used&quot;
)paren
suffix:semicolon
)brace
id|SCpnt
op_assign
id|q-&gt;SCpnt
suffix:semicolon
id|q-&gt;next
op_assign
id|queue-&gt;free
suffix:semicolon
id|queue-&gt;free
op_assign
id|q
suffix:semicolon
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_FREE
suffix:semicolon
)brace
r_else
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_tgtluntag (queue, target, lun, tag)&n; * Purpose : remove a SCSI command from the queue for a specified target/lun/tag&n; * Params  : queue  - queue to remove command from&n; *&t;     target - target that we want&n; *&t;     lun    - lun on device&n; *&t;     tag    - tag on device&n; * Returns : Scsi_Cmnd if successful, or NULL if no command satisfies requirements&n; */
DECL|function|queue_remove_tgtluntag
id|Scsi_Cmnd
op_star
id|queue_remove_tgtluntag
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
comma
r_int
id|tag
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|QE_t
op_star
id|q
comma
op_star
id|prev
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|queue-&gt;head
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;SCpnt-&gt;target
op_eq
id|target
op_logical_and
id|q-&gt;SCpnt-&gt;lun
op_eq
id|lun
op_logical_and
id|q-&gt;SCpnt-&gt;tag
op_eq
id|tag
)paren
r_break
suffix:semicolon
id|prev
op_assign
id|q
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_USED
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;q_remove_tgtluntag: scsi queues corrupted - queue entry not used&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q-&gt;prev
op_ne
id|prev
)paren
id|panic
(paren
l_string|&quot;q_remove_tgtluntag: scsi queues corrupted - q-&gt;prev != prev&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
)paren
(brace
id|queue-&gt;head
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;head
)paren
id|queue-&gt;head-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;next
)paren
id|prev-&gt;next-&gt;prev
op_assign
id|prev
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
id|prev
suffix:semicolon
)brace
id|SCpnt
op_assign
id|q-&gt;SCpnt
suffix:semicolon
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_FREE
suffix:semicolon
id|q-&gt;next
op_assign
id|queue-&gt;free
suffix:semicolon
id|queue-&gt;free
op_assign
id|q
suffix:semicolon
)brace
r_else
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_probetgtlun (queue, target, lun)&n; * Purpose : check to see if we have a command in the queue for the specified&n; *&t;     target/lun.&n; * Params  : queue  - queue to look in&n; *&t;     target - target we want to probe&n; *&t;     lun    - lun on target&n; * Returns : 0 if not found, != 0 if found&n; */
DECL|function|queue_probetgtlun
r_int
id|queue_probetgtlun
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
)paren
(brace
id|QE_t
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|queue-&gt;head
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
r_if
c_cond
(paren
id|q-&gt;SCpnt-&gt;target
op_eq
id|target
op_logical_and
id|q-&gt;SCpnt-&gt;lun
op_eq
id|lun
)paren
r_break
suffix:semicolon
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_cmdonqueue (queue, SCpnt)&n; * Purpose : check to see if we have a command on the queue&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found, != 0 if found&n; */
DECL|function|queue_cmdonqueue
r_int
id|queue_cmdonqueue
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|QE_t
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|queue-&gt;head
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
r_if
c_cond
(paren
id|q-&gt;SCpnt
op_eq
id|SCpnt
)paren
r_break
suffix:semicolon
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_removecmd (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : remove a specific command from the queues&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found&n; */
DECL|function|queue_removecmd
r_int
id|queue_removecmd
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|QE_t
op_star
id|q
comma
op_star
id|prev
suffix:semicolon
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|queue-&gt;head
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;SCpnt
op_eq
id|SCpnt
)paren
r_break
suffix:semicolon
id|prev
op_assign
id|q
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;magic
op_ne
id|QUEUE_MAGIC_USED
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;q_removecmd: scsi queues corrupted - queue entry not used&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q-&gt;prev
op_ne
id|prev
)paren
id|panic
(paren
l_string|&quot;q_removecmd: scsi queues corrupted - q-&gt;prev != prev&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
)paren
(brace
id|queue-&gt;head
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;head
)paren
id|queue-&gt;head-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;next
)paren
id|prev-&gt;next-&gt;prev
op_assign
id|prev
suffix:semicolon
r_else
id|queue-&gt;tail
op_assign
id|prev
suffix:semicolon
)brace
id|q-&gt;magic
op_assign
id|QUEUE_MAGIC_FREE
suffix:semicolon
id|q-&gt;next
op_assign
id|queue-&gt;free
suffix:semicolon
id|queue-&gt;free
op_assign
id|q
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|q
op_ne
l_int|NULL
suffix:semicolon
)brace
DECL|variable|queue_initialise
id|EXPORT_SYMBOL
c_func
(paren
id|queue_initialise
)paren
suffix:semicolon
DECL|variable|queue_free
id|EXPORT_SYMBOL
c_func
(paren
id|queue_free
)paren
suffix:semicolon
DECL|variable|queue_remove
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove
)paren
suffix:semicolon
DECL|variable|queue_remove_exclude
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove_exclude
)paren
suffix:semicolon
DECL|variable|queue_add_cmd_ordered
id|EXPORT_SYMBOL
c_func
(paren
id|queue_add_cmd_ordered
)paren
suffix:semicolon
DECL|variable|queue_add_cmd_tail
id|EXPORT_SYMBOL
c_func
(paren
id|queue_add_cmd_tail
)paren
suffix:semicolon
DECL|variable|queue_remove_tgtluntag
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove_tgtluntag
)paren
suffix:semicolon
DECL|variable|queue_probetgtlun
id|EXPORT_SYMBOL
c_func
(paren
id|queue_probetgtlun
)paren
suffix:semicolon
DECL|variable|queue_cmdonqueue
id|EXPORT_SYMBOL
c_func
(paren
id|queue_cmdonqueue
)paren
suffix:semicolon
DECL|variable|queue_removecmd
id|EXPORT_SYMBOL
c_func
(paren
id|queue_removecmd
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
