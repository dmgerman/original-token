multiline_comment|/*&n; *  scsi_queue.c Copyright (C) 1997 Eric Youngdale&n; *&n; *  generic mid-level SCSI queueing.&n; *&n; *  The point of this is that we need to track when hosts are unable to&n; *  accept a command because they are busy.  In addition, we track devices&n; *  that cannot accept a command because of a QUEUE_FULL condition.  In both&n; *  of these cases, we enter the command in the queue.  At some later point,&n; *  we attempt to remove commands from the queue and retry them.&n; */
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
multiline_comment|/*&n; * TODO:&n; *      1) Prevent multiple traversals of list to look for commands to&n; *         queue.&n; *      2) Protect against multiple insertions of list at the same time.&n; * DONE:&n; *      1) Set state of scsi command to a new state value for ml queue.&n; *      2) Insert into queue when host rejects command.&n; *      3) Make sure status code is properly passed from low-level queue func&n; *         so that internal_cmnd properly returns the right value.&n; *      4) Insert into queue when QUEUE_FULL.&n; *      5) Cull queue in bottom half handler.&n; *      6) Check usage count prior to queue insertion.  Requeue if usage&n; *         count is 0.&n; *      7) Don&squot;t send down any more commands if the host/device is busy.&n; */
DECL|variable|RCSid
r_static
r_const
r_char
id|RCSid
(braket
)braket
op_assign
l_string|&quot;$Header: /mnt/ide/home/eric/CVSROOT/linux/drivers/scsi/scsi_queue.c,v 1.1 1997/10/21 11:16:38 eric Exp $&quot;
suffix:semicolon
multiline_comment|/*&n; * Lock used to prevent more than one process from frobbing the list at the&n; * same time.  FIXME(eric) - there should be separate spinlocks for each host.&n; * This will reduce contention.&n; */
DECL|variable|scsi_mlqueue_lock
id|spinlock_t
id|scsi_mlqueue_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|scsi_mlqueue_remove_lock
id|spinlock_t
id|scsi_mlqueue_remove_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Function:    scsi_mlqueue_insert()&n; *&n; * Purpose:     Insert a command in the midlevel queue.&n; *&n; * Arguments:   cmd    - command that we are adding to queue.&n; *              reason - why we are inserting command to queue.&n; *&n; * Returns:     Nothing.&n; *&n; * Notes:       We do this for one of two cases.  Either the host is busy&n; *              and it cannot accept any more commands for the time being,&n; *              or the device returned QUEUE_FULL and can accept no more&n; *              commands.&n; * Notes:       This could be called either from an interrupt context or a&n; *              normal process context.&n; */
DECL|function|scsi_mlqueue_insert
r_int
id|scsi_mlqueue_insert
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|reason
)paren
(brace
id|Scsi_Cmnd
op_star
id|cpnt
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;Inserting command %p into mlqueue&bslash;n&quot;
comma
id|cmd
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are inserting the command into the ml queue.  First, we&n;&t; * cancel the timer, so it doesn&squot;t time out.&n;&t; */
id|scsi_delete_timer
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|host
op_assign
id|cmd-&gt;host
suffix:semicolon
multiline_comment|/*&n;&t; * Next, set the appropriate busy bit for the device/host.&n;&t; */
r_if
c_cond
(paren
id|reason
op_eq
id|SCSI_MLQUEUE_HOST_BUSY
)paren
(brace
multiline_comment|/*&n;&t;&t; * Protect against race conditions.  If the host isn&squot;t busy,&n;&t;&t; * assume that something actually completed, and that we should&n;&t;&t; * be able to queue a command now.  Note that there is an implicit&n;&t;&t; * assumption that every host can always queue at least one command.&n;&t;&t; * If a host is inactive and cannot queue any commands, I don&squot;t see&n;&t;&t; * how things could possibly work anyways.&n;&t;&t; */
r_if
c_cond
(paren
id|host-&gt;host_busy
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|scsi_retry_command
c_func
(paren
id|cmd
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|host-&gt;host_blocked
op_assign
id|TRUE
suffix:semicolon
id|cmd-&gt;host_wait
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Protect against race conditions.  If the device isn&squot;t busy,&n;&t;&t; * assume that something actually completed, and that we should&n;&t;&t; * be able to queue a command now.  Note that there is an implicit&n;&t;&t; * assumption that every host can always queue at least one command.&n;&t;&t; * If a host is inactive and cannot queue any commands, I don&squot;t see&n;&t;&t; * how things could possibly work anyways.&n;&t;&t; */
r_if
c_cond
(paren
id|cmd-&gt;device-&gt;device_busy
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|scsi_retry_command
c_func
(paren
id|cmd
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|cmd-&gt;device-&gt;device_busy
op_assign
id|TRUE
suffix:semicolon
id|cmd-&gt;device_wait
op_assign
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Register the fact that we own the thing for now.&n;&t; */
id|cmd-&gt;state
op_assign
id|SCSI_STATE_MLQUEUE
suffix:semicolon
id|cmd-&gt;owner
op_assign
id|SCSI_OWNER_MIDLEVEL
suffix:semicolon
id|cmd-&gt;bh_next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * As a performance enhancement, look to see whether the list is&n;&t; * empty.  If it is, then we can just atomicly insert the command&n;&t; * in the list and return without locking.&n;&t; */
r_if
c_cond
(paren
id|host-&gt;pending_commands
op_eq
l_int|NULL
)paren
(brace
id|cpnt
op_assign
id|xchg
c_func
(paren
op_amp
id|host-&gt;pending_commands
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpnt
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Rats.  Something slipped in while we were exchanging.&n;&t;&t; * Swap it back and fall through to do it the hard way.&n;&t;&t; */
id|cmd
op_assign
id|xchg
c_func
(paren
op_amp
id|host-&gt;pending_commands
comma
id|cpnt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Next append the command to the list of pending commands.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|scsi_mlqueue_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cpnt
op_assign
id|host-&gt;pending_commands
suffix:semicolon
id|cpnt
op_logical_and
id|cpnt-&gt;bh_next
suffix:semicolon
id|cpnt
op_assign
id|cpnt-&gt;bh_next
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpnt
op_ne
l_int|NULL
)paren
(brace
id|cpnt-&gt;bh_next
op_assign
id|cmd
suffix:semicolon
)brace
r_else
(brace
id|host-&gt;pending_commands
op_assign
id|cmd
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|scsi_mlqueue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_mlqueue_finish()&n; *&n; * Purpose:     Try and queue commands from the midlevel queue.&n; *&n; * Arguments:   host    - host that just finished a command.&n; *              device  - device that just finished a command.&n; *&n; * Returns:     Nothing.&n; *&n; * Notes:       This could be called either from an interrupt context or a&n; *              normal process context.&n; */
DECL|function|scsi_mlqueue_finish
r_int
id|scsi_mlqueue_finish
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Device
op_star
id|device
)paren
(brace
id|Scsi_Cmnd
op_star
id|cpnt
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|next
suffix:semicolon
id|Scsi_Cmnd
op_star
id|prev
suffix:semicolon
r_int
id|reason
op_assign
l_int|0
suffix:semicolon
r_int
id|rtn
suffix:semicolon
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|2
comma
id|printk
c_func
(paren
l_string|&quot;scsi_mlqueue_finish starting&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First, clear the flag for the host/device.  We will then start&n;&t; * pushing commands through until either something else blocks, or&n;&t; * the queue is empty.&n;&t; */
r_if
c_cond
(paren
id|host-&gt;host_blocked
)paren
(brace
id|reason
op_assign
id|SCSI_MLQUEUE_HOST_BUSY
suffix:semicolon
id|host-&gt;host_blocked
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|device-&gt;device_busy
)paren
(brace
id|reason
op_assign
id|SCSI_MLQUEUE_DEVICE_BUSY
suffix:semicolon
id|device-&gt;device_busy
op_assign
id|FALSE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Walk the list of commands to see if there is anything we can&n;&t; * queue.  This probably needs to be optimized for performance at&n;&t; * some point.&n;&t; */
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|scsi_mlqueue_remove_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cpnt
op_assign
id|host-&gt;pending_commands
suffix:semicolon
id|cpnt
suffix:semicolon
id|cpnt
op_assign
id|next
)paren
(brace
id|next
op_assign
id|cpnt-&gt;bh_next
suffix:semicolon
multiline_comment|/*&n;&t;&t; * First, see if this command is suitable for being retried now.&n;&t;&t; */
r_if
c_cond
(paren
id|reason
op_eq
id|SCSI_MLQUEUE_HOST_BUSY
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The host was busy, but isn&squot;t any more.  Thus we may be&n;&t;&t;&t; * able to queue the command now, but we were waiting for&n;&t;&t;&t; * the device, then we should keep waiting.  Similarily, if&n;&t;&t;&t; * the device is now busy, we should also keep waiting.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|cpnt-&gt;host_wait
op_eq
id|FALSE
)paren
op_logical_or
(paren
id|device-&gt;device_busy
op_eq
id|TRUE
)paren
)paren
(brace
id|prev
op_assign
id|cpnt
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|reason
op_eq
id|SCSI_MLQUEUE_DEVICE_BUSY
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The device was busy, but isn&squot;t any more.  Thus we may be&n;&t;&t;&t; * able to queue the command now, but we were waiting for&n;&t;&t;&t; * the host, then we should keep waiting.  Similarily, if&n;&t;&t;&t; * the host is now busy, we should also keep waiting.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|cpnt-&gt;device_wait
op_eq
id|FALSE
)paren
op_logical_or
(paren
id|host-&gt;host_blocked
op_eq
id|TRUE
)paren
)paren
(brace
id|prev
op_assign
id|cpnt
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * First, remove the command from the list.&n;&t;&t; */
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
id|host-&gt;pending_commands
op_assign
id|next
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;bh_next
op_assign
id|next
suffix:semicolon
)brace
id|cpnt-&gt;bh_next
op_assign
l_int|NULL
suffix:semicolon
id|rtn
op_assign
id|scsi_retry_command
c_func
(paren
id|cpnt
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we got a non-zero return value, it means that the host rejected&n;&t;&t; * the command.  The internal_cmnd function will have added the&n;&t;&t; * command back to the end of the list, so we don&squot;t have anything&n;&t;&t; * more to do here except return.&n;&t;&t; */
r_if
c_cond
(paren
id|rtn
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|scsi_mlqueue_remove_lock
comma
id|flags
)paren
suffix:semicolon
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;Unable to remove command %p from mlqueue&bslash;n&quot;
comma
id|cpnt
)paren
)paren
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;Removed command %p from mlqueue&bslash;n&quot;
comma
id|cpnt
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|scsi_mlqueue_remove_lock
comma
id|flags
)paren
suffix:semicolon
id|finish
suffix:colon
id|SCSI_LOG_MLQUEUE
c_func
(paren
l_int|2
comma
id|printk
c_func
(paren
l_string|&quot;scsi_mlqueue_finish returning&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
