multiline_comment|/*&n; *  scsi_lib.c Copyright (C) 1999 Eric Youngdale&n; *&n; *  SCSI queueing library.&n; *      Initial versions: Eric Youngdale (eric@andante.org).&n; *                        Based upon conversations with large numbers&n; *                        of people at Linux Expo.&n; */
multiline_comment|/*&n; * The fundamental purpose of this file is to contain a library of utility&n; * routines that can be used by low-level drivers.   Ultimately the idea&n; * is that there should be a sufficiently rich number of functions that it&n; * would be possible for a driver author to fashion a queueing function for&n; * a low-level driver if they wished.   Note however that this file also&n; * contains the &quot;default&quot; versions of these functions, as we don&squot;t want to&n; * go through and retrofit queueing functions into all 30 some-odd drivers.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;constants.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
multiline_comment|/*&n; * This entire source file deals with the new queueing code.&n; */
multiline_comment|/*&n; * Function:    scsi_insert_special_cmd()&n; *&n; * Purpose:     Insert pre-formed command into request queue.&n; *&n; * Arguments:   SCpnt   - command that is ready to be queued.&n; *              at_head - boolean.  True if we should insert at head&n; *                        of queue, false if we should insert at tail.&n; *&n; * Lock status: Assumed that lock is not held upon entry.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       This function is called from character device and from&n; *              ioctl types of functions where the caller knows exactly&n; *              what SCSI command needs to be issued.   The idea is that&n; *              we merely inject the command into the queue (at the head&n; *              for now), and then call the queue request function to actually&n; *              process it.&n; */
DECL|function|scsi_insert_special_cmd
r_int
id|scsi_insert_special_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|at_head
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|request_queue_t
op_star
id|q
suffix:semicolon
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The SCpnt already contains a request structure - we will doctor the&n;&t; * thing up with the appropriate values and use that in the actual&n;&t; * request queue.&n;&t; */
id|q
op_assign
op_amp
id|SCpnt-&gt;device-&gt;request_queue
suffix:semicolon
id|SCpnt-&gt;request.cmd
op_assign
id|SPECIAL
suffix:semicolon
id|SCpnt-&gt;request.special
op_assign
(paren
r_void
op_star
)paren
id|SCpnt
suffix:semicolon
multiline_comment|/*&n;&t; * For the moment, we insert at the head of the queue.   This may turn&n;&t; * out to be a bad idea, but we will see about that when we get there.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|at_head
)paren
(brace
id|SCpnt-&gt;request.next
op_assign
id|q-&gt;current_request
suffix:semicolon
id|q-&gt;current_request
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * FIXME(eric) - we always insert at the tail of the list.  Otherwise&n;&t;&t; * ioctl commands would always take precedence over normal I/O.&n;&t;&t; */
id|SCpnt-&gt;request.next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;current_request
op_eq
l_int|NULL
)paren
(brace
id|q-&gt;current_request
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
)brace
r_else
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_for
c_loop
(paren
id|req
op_assign
id|q-&gt;current_request
suffix:semicolon
id|req
suffix:semicolon
id|req
op_assign
id|req-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;next
op_eq
l_int|NULL
)paren
(brace
id|req-&gt;next
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Now hit the requeue function for the queue.   If the host is already&n;&t; * busy, so be it - we have nothing special to do.   If the host can queue&n;&t; * it, then send it off.&n;&t; */
id|q
op_member_access_from_pointer
id|request_fn
c_func
(paren
id|q
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_init_cmd_errh()&n; *&n; * Purpose:     Initialize SCpnt fields related to error handling.&n; *&n; * Arguments:   SCpnt   - command that is ready to be queued.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       This function has the job of initializing a number of&n; *              fields related to error handling.   Typically this will&n; *              be called once for each command, as required.&n; */
DECL|function|scsi_init_cmd_errh
r_int
id|scsi_init_cmd_errh
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|0
)paren
suffix:semicolon
id|SCpnt-&gt;owner
op_assign
id|SCSI_OWNER_MIDLEVEL
suffix:semicolon
id|SCpnt-&gt;reset_chain
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt-&gt;serial_number
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;serial_number_at_timeout
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;retries
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;abort_reason
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|SCpnt-&gt;sense_buffer
comma
l_int|0
comma
r_sizeof
id|SCpnt-&gt;sense_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;cmd_len
op_eq
l_int|0
)paren
id|SCpnt-&gt;cmd_len
op_assign
id|COMMAND_SIZE
c_func
(paren
id|SCpnt-&gt;cmnd
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need saved copies of a number of fields - this is because&n;&t; * error handling may need to overwrite these with different values&n;&t; * to run different commands, and once error handling is complete,&n;&t; * we will need to restore these values prior to running the actual&n;&t; * command.&n;&t; */
id|SCpnt-&gt;old_use_sg
op_assign
id|SCpnt-&gt;use_sg
suffix:semicolon
id|SCpnt-&gt;old_cmd_len
op_assign
id|SCpnt-&gt;cmd_len
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|SCpnt-&gt;data_cmnd
comma
(paren
r_const
r_void
op_star
)paren
id|SCpnt-&gt;cmnd
comma
r_sizeof
(paren
id|SCpnt-&gt;cmnd
)paren
)paren
suffix:semicolon
id|SCpnt-&gt;buffer
op_assign
id|SCpnt-&gt;request_buffer
suffix:semicolon
id|SCpnt-&gt;bufflen
op_assign
id|SCpnt-&gt;request_bufflen
suffix:semicolon
id|SCpnt-&gt;reset_chain
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt-&gt;internal_timeout
op_assign
id|NORMAL_TIMEOUT
suffix:semicolon
id|SCpnt-&gt;abort_reason
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_queue_next_request()&n; *&n; * Purpose:     Handle post-processing of completed commands.&n; *&n; * Arguments:   SCpnt   - command that may need to be requeued.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       After command completion, there may be blocks left&n; *              over which weren&squot;t finished by the previous command&n; *              this can be for a number of reasons - the main one is&n; *              that a medium error occurred, and the sectors after&n; *              the bad block need to be re-read.&n; *&n; *              If SCpnt is NULL, it means that the previous command&n; *              was completely finished, and we should simply start&n; *              a new command, if possible.&n; */
DECL|function|scsi_queue_next_request
r_void
id|scsi_queue_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
id|all_clear
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Device
op_star
id|SDpnt
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|SHpnt
suffix:semicolon
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * For some reason, we are not done with this request.&n;&t;&t; * This happens for I/O errors in the middle of the request,&n;&t;&t; * in which case we need to request the blocks that come after&n;&t;&t; * the bad sector.&n;&t;&t; */
id|SCpnt-&gt;request.next
op_assign
id|q-&gt;current_request
suffix:semicolon
id|q-&gt;current_request
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
id|SCpnt-&gt;request.special
op_assign
(paren
r_void
op_star
)paren
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Just hit the requeue function for the queue.&n;&t; * FIXME - if this queue is empty, check to see if we might need to&n;&t; * start requests for other devices attached to the same host.&n;&t; */
id|q
op_member_access_from_pointer
id|request_fn
c_func
(paren
id|q
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now see whether there are other devices on the bus which&n;&t; * might be starved.  If so, hit the request function.  If we&n;&t; * don&squot;t find any, then it is safe to reset the flag.  If we&n;&t; * find any device that it is starved, it isn&squot;t safe to reset the&n;&t; * flag as the queue function releases the lock and thus some&n;&t; * other device might have become starved along the way.&n;&t; */
id|SDpnt
op_assign
(paren
id|Scsi_Device
op_star
)paren
id|q-&gt;queuedata
suffix:semicolon
id|SHpnt
op_assign
id|SDpnt-&gt;host
suffix:semicolon
id|all_clear
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|SHpnt-&gt;some_device_starved
)paren
(brace
r_for
c_loop
(paren
id|SDpnt
op_assign
id|SHpnt-&gt;host_queue
suffix:semicolon
id|SDpnt
suffix:semicolon
id|SDpnt
op_assign
id|SDpnt-&gt;next
)paren
(brace
id|request_queue_t
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
(paren
id|SHpnt-&gt;can_queue
OG
l_int|0
op_logical_and
(paren
id|SHpnt-&gt;host_busy
op_ge
id|SHpnt-&gt;can_queue
)paren
)paren
op_logical_or
(paren
id|SHpnt-&gt;host_blocked
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SDpnt-&gt;device_blocked
op_logical_or
op_logical_neg
id|SDpnt-&gt;starved
)paren
(brace
r_continue
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|SDpnt-&gt;request_queue
suffix:semicolon
id|q
op_member_access_from_pointer
id|request_fn
c_func
(paren
id|q
)paren
suffix:semicolon
id|all_clear
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SDpnt
op_eq
l_int|NULL
op_logical_and
id|all_clear
)paren
(brace
id|SHpnt-&gt;some_device_starved
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_end_request()&n; *&n; * Purpose:     Post-processing of completed commands called from interrupt&n; *              handler.&n; *&n; * Arguments:   SCpnt    - command that is complete.&n; *              uptodate - 1 if I/O indicates success, 0 for I/O error.&n; *              sectors  - number of sectors we want to mark.&n; *&n; * Lock status: Assumed that lock is not held upon entry.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       This is called for block device requests in order to&n; *              mark some number of sectors as complete.&n; */
DECL|function|scsi_end_request
id|Scsi_Cmnd
op_star
id|scsi_end_request
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|uptodate
comma
r_int
id|sectors
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
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|0
)paren
suffix:semicolon
id|req
op_assign
op_amp
id|SCpnt-&gt;request
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
l_string|&quot; I/O error: dev %s, sector %lu&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|req-&gt;rq_dev
)paren
comma
id|req-&gt;sector
)paren
suffix:semicolon
)brace
r_do
(brace
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
id|req-&gt;nr_sectors
op_sub_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;sector
op_add_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|sectors
op_sub_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|bh
op_member_access_from_pointer
id|b_end_io
c_func
(paren
id|bh
comma
id|uptodate
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
l_string|&quot;scsi_end_request: buffer-list destroyed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_while
c_loop
(paren
id|sectors
op_logical_and
id|bh
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If there are blocks left over at the end, set up the command&n;&t; * to queue the remainder of them.&n;&t; */
r_if
c_cond
(paren
id|req-&gt;bh
)paren
(brace
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This request is done.  If there is someone blocked waiting for this&n;&t; * request, wake them up.  Typically used to wake up processes trying&n;&t; * to swap a page into memory.&n;&t; */
r_if
c_cond
(paren
id|req-&gt;sem
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|req-&gt;sem
)paren
suffix:semicolon
)brace
id|add_blkdev_randomness
c_func
(paren
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)paren
suffix:semicolon
id|scsi_release_command
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_io_completion()&n; *&n; * Purpose:     Completion processing for block device I/O requests.&n; *&n; * Arguments:   SCpnt   - command that is finished.&n; *&n; * Lock status: Assumed that no lock is held upon entry.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       This function is matched in terms of capabilities to&n; *              the function that created the scatter-gather list.&n; *              In other words, if there are no bounce buffers&n; *              (the normal case for most drivers), we don&squot;t need&n; *              the logic to deal with cleaning up afterwards.&n; */
DECL|function|scsi_io_completion
r_void
id|scsi_io_completion
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|good_sectors
comma
r_int
id|block_sectors
)paren
(brace
r_int
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
r_int
id|this_count
op_assign
id|SCpnt-&gt;bufflen
op_rshift
l_int|9
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|SCpnt-&gt;device-&gt;request_queue
suffix:semicolon
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Free up any indirection buffers we allocated for DMA purposes. &n;&t; * For the case of a READ, we need to copy the data out of the&n;&t; * bounce buffer and into the real buffer.&n;&t; */
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sgpnt
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;buffer
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
id|SCpnt-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
)paren
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;request.cmd
op_eq
id|READ
)paren
(brace
id|memcpy
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
)brace
id|scsi_free
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
)brace
)brace
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;sglist_len
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;buffer
op_ne
id|SCpnt-&gt;request.buffer
)paren
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;request.cmd
op_eq
id|READ
)paren
(brace
id|memcpy
c_func
(paren
id|SCpnt-&gt;request.buffer
comma
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;bufflen
)paren
suffix:semicolon
)brace
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;bufflen
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Zero these out.  They now point to freed memory, and it is&n;&t; * dangerous to hang onto the pointers.&n;&t; */
id|SCpnt-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt-&gt;bufflen
op_assign
l_int|0
suffix:semicolon
id|SCpnt-&gt;request_buffer
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt-&gt;request_bufflen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Next deal with any sectors which we were able to correctly&n;&t; * handle.&n;&t; */
r_if
c_cond
(paren
id|good_sectors
OG
l_int|0
)paren
(brace
id|SCSI_LOG_HLCOMPLETE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;%ld sectors total, %d sectors done.&bslash;n&quot;
comma
id|SCpnt-&gt;request.nr_sectors
comma
id|good_sectors
)paren
)paren
suffix:semicolon
id|SCSI_LOG_HLCOMPLETE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;use_sg is %d&bslash;n &quot;
comma
id|SCpnt-&gt;use_sg
)paren
)paren
suffix:semicolon
id|SCpnt-&gt;request.errors
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If multiple sectors are requested in one buffer, then&n;&t;&t; * they will have been finished off by the first command.&n;&t;&t; * If not, then we have a multi-buffer command.&n;&t;&t; */
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|1
comma
id|good_sectors
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the command completed without error, then either finish off the&n;&t;&t; * rest of the command, or start a new one.&n;&t;&t; */
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Now, if we were good little boys and girls, Santa left us a request&n;&t; * sense buffer.  We can extract information from this, so we&n;&t; * can choose a block to remap, etc.&n;&t; */
r_if
c_cond
(paren
id|driver_byte
c_func
(paren
id|result
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|suggestion
c_func
(paren
id|result
)paren
op_eq
id|SUGGEST_REMAP
)paren
(brace
macro_line|#ifdef REMAP
multiline_comment|/*&n;&t;&t;&t; * Not yet implemented.  A read will fail after being remapped,&n;&t;&t;&t; * a write will call the strategy routine again.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|SCpnt-&gt;device-&gt;remap
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x70
op_logical_and
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
op_eq
id|UNIT_ATTENTION
)paren
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;device-&gt;removable
)paren
(brace
multiline_comment|/* detected disc change.  set a bit and quietly refuse&n;&t;&t;&t;&t; * further access.&n;&t;&t;&t;&t; */
id|SCpnt-&gt;device-&gt;changed
op_assign
l_int|1
suffix:semicolon
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Must have been a power glitch, or a bus reset.&n;&t;&t;&t;&t; * Could not have been a media change, so we just retry&n;&t;&t;&t;&t; * the request and see what happens.&n;&t;&t;&t;&t; */
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* If we had an ILLEGAL REQUEST returned, then we may have&n;&t;&t; * performed an unsupported command.  The only thing this should be&n;&t;&t; * would be a ten byte read where only a six byte read was supported.&n;&t;&t; * Also, on a system where READ CAPACITY failed, we have have read&n;&t;&t; * past the end of the disk.&n;&t;&t; */
r_switch
c_cond
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
)paren
(brace
r_case
id|ILLEGAL_REQUEST
suffix:colon
r_if
c_cond
(paren
id|SCpnt-&gt;device-&gt;ten
)paren
(brace
id|SCpnt-&gt;device-&gt;ten
op_assign
l_int|0
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NOT_READY
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Device %x not ready.&bslash;n&quot;
comma
id|SCpnt-&gt;request.rq_dev
)paren
suffix:semicolon
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEDIUM_ERROR
suffix:colon
r_case
id|VOLUME_OVERFLOW
suffix:colon
id|printk
c_func
(paren
l_string|&quot;scsi%d: ERROR on channel %d, id %d, lun %d, CDB: &quot;
comma
id|SCpnt-&gt;host-&gt;host_no
comma
(paren
r_int
)paren
id|SCpnt-&gt;channel
comma
(paren
r_int
)paren
id|SCpnt-&gt;target
comma
(paren
r_int
)paren
id|SCpnt-&gt;lun
)paren
suffix:semicolon
id|print_command
c_func
(paren
id|SCpnt-&gt;cmnd
)paren
suffix:semicolon
id|print_sense
c_func
(paren
l_string|&quot;sd&quot;
comma
id|SCpnt
)paren
suffix:semicolon
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|block_sectors
)paren
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* driver byte != 0 */
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SCSI disk error : host %d channel %d id %d lun %d return code = %x&bslash;n&quot;
comma
id|SCpnt-&gt;device-&gt;host-&gt;host_no
comma
id|SCpnt-&gt;device-&gt;channel
comma
id|SCpnt-&gt;device-&gt;id
comma
id|SCpnt-&gt;device-&gt;lun
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driver_byte
c_func
(paren
id|result
)paren
op_amp
id|DRIVER_SENSE
)paren
id|print_sense
c_func
(paren
l_string|&quot;sd&quot;
comma
id|SCpnt
)paren
suffix:semicolon
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.current_nr_sectors
)paren
suffix:semicolon
id|scsi_queue_next_request
c_func
(paren
id|q
comma
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function:    scsi_get_request_dev()&n; *&n; * Purpose:     Find the upper-level driver that is responsible for this&n; *              request&n; *&n; * Arguments:   request   - I/O request we are preparing to queue.&n; *&n; * Lock status: No locks assumed to be held, but as it happens the&n; *              io_request_lock is held when this is called.&n; *&n; * Returns:     Nothing&n; *&n; * Notes:       The requests in the request queue may have originated&n; *              from any block device driver.  We need to find out which&n; *              one so that we can later form the appropriate command.&n; */
DECL|function|scsi_get_request_dev
r_struct
id|Scsi_Device_Template
op_star
id|scsi_get_request_dev
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|Scsi_Device_Template
op_star
id|spnt
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|req-&gt;rq_dev
suffix:semicolon
r_int
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|spnt
op_assign
id|scsi_devicelist
suffix:semicolon
id|spnt
suffix:semicolon
id|spnt
op_assign
id|spnt-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;&t; * Search for a block device driver that supports this&n;&t;&t; * major.&n;&t;&t; */
r_if
c_cond
(paren
id|spnt-&gt;blk
op_logical_and
id|spnt-&gt;major
op_eq
id|major
)paren
(brace
r_return
id|spnt
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_request_fn()&n; *&n; * Purpose:     Generic version of request function for SCSI hosts.&n; *&n; * Arguments:   q       - Pointer to actual queue.&n; *&n; * Returns:     Nothing&n; *&n; * Lock status: IO request lock assumed to be held when called.&n; *&n; * Notes:       The theory is that this function is something which individual&n; *              drivers could also supply if they wished to.   The problem&n; *              is that we have 30 some odd low-level drivers in the kernel&n; *              tree already, and it would be most difficult to retrofit&n; *              this crap into all of them.   Thus this function has the job&n; *              of acting as a generic queue manager for all of those existing&n; *              drivers.&n; */
DECL|function|scsi_request_fn
r_void
id|scsi_request_fn
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|Scsi_Device
op_star
id|SDpnt
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|SHpnt
suffix:semicolon
r_struct
id|Scsi_Device_Template
op_star
id|STpnt
suffix:semicolon
id|ASSERT_LOCK
c_func
(paren
op_amp
id|io_request_lock
comma
l_int|1
)paren
suffix:semicolon
id|SDpnt
op_assign
(paren
id|Scsi_Device
op_star
)paren
id|q-&gt;queuedata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SDpnt
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Missing device&quot;
)paren
suffix:semicolon
)brace
id|SHpnt
op_assign
id|SDpnt-&gt;host
suffix:semicolon
multiline_comment|/*&n;&t; * If the host for this device is in error recovery mode, don&squot;t&n;&t; * do anything at all here.  When the host leaves error recovery&n;&t; * mode, it will automatically restart things and start queueing&n;&t; * commands again.  Same goes if the queue is actually plugged,&n;&t; * if the device itself is blocked, or if the host is fully&n;&t; * occupied.&n;&t; */
r_if
c_cond
(paren
id|SHpnt-&gt;in_recovery
op_logical_or
id|q-&gt;plugged
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * To start with, we keep looping until the queue is empty, or until&n;&t; * the host is no longer able to accept any more requests.&n;&t; */
r_while
c_loop
(paren
l_int|1
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the host cannot accept another request, then quit.&n;&t;&t; */
r_if
c_cond
(paren
id|SDpnt-&gt;device_blocked
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|SHpnt-&gt;can_queue
OG
l_int|0
op_logical_and
(paren
id|SHpnt-&gt;host_busy
op_ge
id|SHpnt-&gt;can_queue
)paren
)paren
op_logical_or
(paren
id|SHpnt-&gt;host_blocked
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If we are unable to process any commands at all for this&n;&t;&t;&t; * device, then we consider it to be starved.  What this means&n;&t;&t;&t; * is that there are no outstanding commands for this device&n;&t;&t;&t; * and hence we need a little help getting it started again&n;&t;&t;&t; * once the host isn&squot;t quite so busy.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|SDpnt-&gt;device_busy
op_eq
l_int|0
)paren
(brace
id|SDpnt-&gt;starved
op_assign
l_int|1
suffix:semicolon
id|SHpnt-&gt;some_device_starved
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|SDpnt-&gt;starved
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Loop through all of the requests in this queue, and find&n;&t;&t; * one that is queueable.&n;&t;&t; */
id|req
op_assign
id|q-&gt;current_request
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we couldn&squot;t find a request that could be queued, then we&n;&t;&t; * can also quit.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Find the actual device driver associated with this command.&n;&t;&t; * The SPECIAL requests are things like character device or&n;&t;&t; * ioctls, which did not originate from ll_rw_blk.  Note that&n;&t;&t; * the special field is also used to indicate the SCpnt for&n;&t;&t; * the remainder of a partially fulfilled request that can &n;&t;&t; * come up when there is a medium error.  We have to treat&n;&t;&t; * these two cases differently.  We differentiate by looking&n;&t;&t; * at request.cmd, as this tells us the real story.&n;&t;&t; */
r_if
c_cond
(paren
id|req-&gt;cmd
op_eq
id|SPECIAL
)paren
(brace
id|STpnt
op_assign
l_int|NULL
suffix:semicolon
id|SCpnt
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|req-&gt;special
suffix:semicolon
)brace
r_else
(brace
id|STpnt
op_assign
id|scsi_get_request_dev
c_func
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|STpnt
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to find device associated with request&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Now try and find a command block that we can use.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|req-&gt;special
op_ne
l_int|NULL
)paren
(brace
id|SCpnt
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|req-&gt;special
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * We need to recount the number of&n;&t;&t;&t;&t; * scatter-gather segments here - the&n;&t;&t;&t;&t; * normal case code assumes this to be&n;&t;&t;&t;&t; * correct, as it would be a performance&n;&t;&t;&t;&t; * lose to always recount.  Handling&n;&t;&t;&t;&t; * errors is always unusual, of course.&n;&t;&t;&t;&t; */
id|recount_segments
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
)brace
r_else
(brace
id|SCpnt
op_assign
id|scsi_allocate_device
c_func
(paren
id|SDpnt
comma
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * If so, we are ready to do something.  Bump the count&n;&t;&t;&t; * while the queue is locked and then break out of the loop.&n;&t;&t;&t; * Otherwise loop around and try another request.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|SCpnt
)paren
(brace
r_break
suffix:semicolon
)brace
id|SHpnt-&gt;host_busy
op_increment
suffix:semicolon
id|SDpnt-&gt;device_busy
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * FIXME(eric)&n;&t;&t; * I am not sure where the best place to do this is.  We need&n;&t;&t; * to hook in a place where we are likely to come if in user&n;&t;&t; * space.   Technically the error handling thread should be&n;&t;&t; * doing this crap, but the error handler isn&squot;t used by&n;&t;&t; * most hosts.&n;&t;&t; */
r_if
c_cond
(paren
id|SDpnt-&gt;was_reset
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We need to relock the door, but we might&n;&t;&t;&t; * be in an interrupt handler.  Only do this&n;&t;&t;&t; * from user space, since we do not want to&n;&t;&t;&t; * sleep from an interrupt.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|SDpnt-&gt;removable
op_logical_and
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|io_request_lock
)paren
suffix:semicolon
id|scsi_ioctl
c_func
(paren
id|SDpnt
comma
id|SCSI_IOCTL_DOORLOCK
comma
l_int|0
)paren
suffix:semicolon
id|SDpnt-&gt;was_reset
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|io_request_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|SDpnt-&gt;was_reset
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Finally, before we release the lock, we copy the&n;&t;&t; * request to the command block, and remove the&n;&t;&t; * request from the request list.   Note that we always&n;&t;&t; * operate on the queue head - there is absolutely no&n;&t;&t; * reason to search the list, because all of the commands&n;&t;&t; * in this queue are for the same device.&n;&t;&t; */
id|q-&gt;current_request
op_assign
id|req-&gt;next
suffix:semicolon
id|SCpnt-&gt;request.next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|req
op_ne
op_amp
id|SCpnt-&gt;request
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|SCpnt-&gt;request
comma
id|req
comma
r_sizeof
(paren
r_struct
id|request
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We have copied the data out of the request block - it is now in&n;&t;&t;&t; * a field in SCpnt.  Release the request block.&n;&t;&t;&t; */
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|req-&gt;rq_status
op_assign
id|RQ_INACTIVE
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Now it is finally safe to release the lock.  We are&n;&t;&t; * not going to noodle the request list until this&n;&t;&t; * request has been queued and we loop back to queue&n;&t;&t; * another.  &n;&t;&t; */
id|req
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|io_request_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;request.cmd
op_ne
id|SPECIAL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This will do a couple of things:&n;&t;&t;&t; *  1) Fill in the actual SCSI command.&n;&t;&t;&t; *  2) Fill in any other upper-level specific fields (timeout).&n;&t;&t;&t; *&n;&t;&t;&t; * If this returns 0, it means that the request failed (reading&n;&t;&t;&t; * past end of disk, reading offline device, etc).   This won&squot;t&n;&t;&t;&t; * actually talk to the device, but some kinds of consistency&n;&t;&t;&t; * checking may cause the request to be rejected immediately.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|STpnt
op_eq
l_int|NULL
)paren
(brace
id|STpnt
op_assign
id|scsi_get_request_dev
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t;&t;&t; * This sets up the scatter-gather table (allocating if&n;&t;&t;&t; * required).  Hosts that need bounce buffers will also&n;&t;&t;&t; * get those allocated here.  &n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|SDpnt
op_member_access_from_pointer
id|scsi_init_io_fn
c_func
(paren
id|SCpnt
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Initialize the actual SCSI command for this request.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|STpnt
op_member_access_from_pointer
id|init_command
c_func
(paren
id|SCpnt
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Finally, initialize any error handling parameters, and set up&n;&t;&t; * the timers for timeouts.&n;&t;&t; */
id|scsi_init_cmd_errh
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Dispatch the command to the low-level driver.&n;&t;&t; */
id|scsi_dispatch_cmd
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now we need to grab the lock again.  We are about to mess with&n;&t;&t; * the request queue and try to find another command.&n;&t;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|io_request_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If this is a single-lun device, and we are currently finished&n;&t; * with this device, then see if we need to get another device&n;&t; * started.&n;&t; */
r_if
c_cond
(paren
id|SDpnt-&gt;single_lun
op_logical_and
id|q-&gt;current_request
op_eq
l_int|NULL
op_logical_and
id|SDpnt-&gt;device_busy
op_eq
l_int|0
)paren
(brace
id|request_queue_t
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|SDpnt
op_assign
id|SHpnt-&gt;host_queue
suffix:semicolon
id|SDpnt
suffix:semicolon
id|SDpnt
op_assign
id|SDpnt-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|SHpnt-&gt;can_queue
OG
l_int|0
)paren
op_logical_and
(paren
id|SHpnt-&gt;host_busy
op_ge
id|SHpnt-&gt;can_queue
)paren
)paren
op_logical_or
(paren
id|SHpnt-&gt;host_blocked
)paren
op_logical_or
(paren
id|SDpnt-&gt;device_blocked
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|SDpnt-&gt;request_queue
suffix:semicolon
id|q
op_member_access_from_pointer
id|request_fn
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
)brace
)brace
eof
