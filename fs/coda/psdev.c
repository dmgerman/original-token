multiline_comment|/*&n; *      &t;An implementation of a loadable kernel mode driver providing&n; *&t;&t;multiple kernel/user space bidirectional communications links.&n; *&n; * &t;&t;Author: &t;Alan Cox &lt;alan@redhat.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; * &n; *              Adapted to become the Linux 2.0 Coda pseudo device&n; *              Peter  Braam  &lt;braam@maths.ox.ac.uk&gt; &n; *              Michael Callahan &lt;mjc@emmy.smith.edu&gt;           &n; *&n; *              Changes for Linux 2.1&n; *              Copyright (c) 1997 Carnegie-Mellon University&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/lp.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_proc.h&gt;
multiline_comment|/* &n; * Coda stuff&n; */
r_extern
r_struct
id|file_system_type
id|coda_fs_type
suffix:semicolon
multiline_comment|/* statistics */
DECL|variable|coda_hard
r_int
id|coda_hard
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* allows signals during upcalls */
DECL|variable|coda_timeout
r_int
r_int
id|coda_timeout
op_assign
l_int|30
suffix:semicolon
multiline_comment|/* .. secs, then signals will dequeue */
DECL|variable|coda_comms
r_struct
id|venus_comm
id|coda_comms
(braket
id|MAX_CODADEVS
)braket
suffix:semicolon
multiline_comment|/*&n; * Device operations&n; */
DECL|function|coda_psdev_poll
r_static
r_int
r_int
id|coda_psdev_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|venus_comm
op_star
id|vcp
op_assign
(paren
r_struct
id|venus_comm
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|vcp-&gt;vc_waitq
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|vcp-&gt;vc_pending
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|coda_psdev_ioctl
r_static
r_int
id|coda_psdev_ioctl
c_func
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|CIOC_KERNEL_VERSION
suffix:colon
id|data
op_assign
id|CODA_KERNEL_VERSION
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|data
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Receive a message written by Venus to the psdev&n; */
DECL|function|coda_psdev_write
r_static
id|ssize_t
id|coda_psdev_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|venus_comm
op_star
id|vcp
op_assign
(paren
r_struct
id|venus_comm
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|upc_req
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|coda_in_hdr
id|hdr
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* Peek at the opcode, uniquefier */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|hdr
comma
id|buf
comma
l_int|2
op_star
r_sizeof
(paren
id|u_long
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;(process,opc,uniq)=(%d,%ld,%ld), nbytes %ld&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|hdr.opcode
comma
id|hdr.unique
comma
(paren
r_int
)paren
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DOWNCALL
c_func
(paren
id|hdr.opcode
)paren
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
l_int|NULL
suffix:semicolon
r_union
id|outputArgs
op_star
id|dcbuf
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
op_star
id|dcbuf
)paren
suffix:semicolon
id|sb
op_assign
id|vcp-&gt;vc_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;coda_psdev_write: downcall, no SB!&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_assign
id|nbytes
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;handling downcall&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
r_sizeof
(paren
r_struct
id|coda_out_hdr
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_downcall opc %ld uniq %ld, not enough!&bslash;n&quot;
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|count
op_assign
id|nbytes
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nbytes
OG
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Coda: downcall opc %ld, uniq %ld, too much!&quot;
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|nbytes
op_assign
id|size
suffix:semicolon
)brace
id|CODA_ALLOC
c_func
(paren
id|dcbuf
comma
r_union
id|outputArgs
op_star
comma
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|dcbuf
comma
id|buf
comma
id|nbytes
)paren
)paren
(brace
id|CODA_FREE
c_func
(paren
id|dcbuf
comma
id|nbytes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* what downcall errors does Venus handle ? */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|coda_downcall
c_func
(paren
id|hdr.opcode
comma
id|dcbuf
comma
id|sb
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|dcbuf
comma
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_write: coda_downcall error: %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
id|retval
op_assign
id|error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|count
op_assign
id|nbytes
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Look for the message on the processing queue. */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|lh
op_assign
op_amp
id|vcp-&gt;vc_processing
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|vcp-&gt;vc_processing
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|uc_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;uc_unique
op_eq
id|hdr.unique
)paren
(brace
id|req
op_assign
id|tmp
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;uc_chain
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Eureka: uniq %ld on queue!&bslash;n&quot;
comma
id|hdr.unique
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_write: msg (%ld, %ld) not found&bslash;n&quot;
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* move data into response buffer. */
r_if
c_cond
(paren
id|req-&gt;uc_outSize
OL
id|nbytes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_write: too much cnt: %d, cnt: %ld, opc: %ld, uniq: %ld.&bslash;n&quot;
comma
id|req-&gt;uc_outSize
comma
(paren
r_int
)paren
id|nbytes
comma
id|hdr.opcode
comma
id|hdr.unique
)paren
suffix:semicolon
id|nbytes
op_assign
id|req-&gt;uc_outSize
suffix:semicolon
multiline_comment|/* don&squot;t have more space! */
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|req-&gt;uc_data
comma
id|buf
comma
id|nbytes
)paren
)paren
(brace
id|req-&gt;uc_flags
op_or_assign
id|REQ_ABORT
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;uc_sleep
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* adjust outsize. is this usefull ?? */
id|req-&gt;uc_outSize
op_assign
id|nbytes
suffix:semicolon
id|req-&gt;uc_flags
op_or_assign
id|REQ_WRITE
suffix:semicolon
id|count
op_assign
id|nbytes
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Found! Count %ld for (opc,uniq)=(%ld,%ld), upc_req at %p&bslash;n&quot;
comma
(paren
r_int
)paren
id|count
comma
id|hdr.opcode
comma
id|hdr.unique
comma
op_amp
id|req
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;uc_sleep
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|count
ques
c_cond
id|count
suffix:colon
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Read a message from the kernel to Venus&n; */
DECL|function|coda_psdev_read
r_static
id|ssize_t
id|coda_psdev_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|off
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|venus_comm
op_star
id|vcp
op_assign
(paren
r_struct
id|venus_comm
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|vcp-&gt;vc_waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list_empty
c_func
(paren
op_amp
id|vcp-&gt;vc_pending
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|vcp-&gt;vc_waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|vcp-&gt;vc_pending.next
comma
r_struct
id|upc_req
comma
id|uc_chain
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;uc_chain
)paren
suffix:semicolon
multiline_comment|/* Move the input args into userspace */
id|count
op_assign
id|req-&gt;uc_inSize
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
id|req-&gt;uc_inSize
)paren
(brace
id|printk
(paren
l_string|&quot;psdev_read: Venus read %ld bytes of %d in message&bslash;n&quot;
comma
(paren
r_int
)paren
id|nbytes
comma
id|req-&gt;uc_inSize
)paren
suffix:semicolon
id|count
op_assign
id|nbytes
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|req-&gt;uc_data
comma
id|count
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|free_out
suffix:semicolon
)brace
multiline_comment|/* If request was not a signal, enqueue and don&squot;t free */
r_if
c_cond
(paren
id|req-&gt;uc_opcode
op_ne
id|CODA_SIGNAL
)paren
(brace
id|req-&gt;uc_flags
op_or_assign
id|REQ_READ
suffix:semicolon
id|list_add
c_func
(paren
op_amp
(paren
id|req-&gt;uc_chain
)paren
comma
id|vcp-&gt;vc_processing.prev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;vcread: signal msg (%d, %d)&bslash;n&quot;
comma
id|req-&gt;uc_opcode
comma
id|req-&gt;uc_unique
)paren
suffix:semicolon
id|free_out
suffix:colon
id|CODA_FREE
c_func
(paren
id|req-&gt;uc_data
comma
r_sizeof
(paren
r_struct
id|coda_in_hdr
)paren
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|req
comma
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|count
ques
c_cond
id|count
suffix:colon
id|retval
)paren
suffix:semicolon
)brace
DECL|function|coda_psdev_open
r_static
r_int
id|coda_psdev_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|venus_comm
op_star
id|vcp
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|ENTRY
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|idx
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|MAX_CODADEVS
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|vcp
op_assign
op_amp
id|coda_comms
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vcp-&gt;vc_inuse
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|vcp-&gt;vc_inuse
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vcp-&gt;vc_pending
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vcp-&gt;vc_processing
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|vcp-&gt;vc_waitq
)paren
suffix:semicolon
id|vcp-&gt;vc_sb
op_assign
l_int|0
suffix:semicolon
id|vcp-&gt;vc_seq
op_assign
l_int|0
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|vcp
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;device %i - inuse: %d&bslash;n&quot;
comma
id|idx
comma
id|vcp-&gt;vc_inuse
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_psdev_release
r_static
r_int
id|coda_psdev_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|venus_comm
op_star
id|vcp
op_assign
(paren
r_struct
id|venus_comm
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|next
suffix:semicolon
id|ENTRY
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp-&gt;vc_inuse
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;psdev_release: Not open.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;psdev_release: inuse %d&bslash;n&quot;
comma
id|vcp-&gt;vc_inuse
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|vcp-&gt;vc_inuse
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Wakeup clients so they can return. */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;wake up pending clients&bslash;n&quot;
)paren
suffix:semicolon
id|lh
op_assign
id|vcp-&gt;vc_pending.next
suffix:semicolon
id|next
op_assign
id|lh
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|next
)paren
op_ne
op_amp
id|vcp-&gt;vc_pending
)paren
(brace
id|next
op_assign
id|lh-&gt;next
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|uc_chain
)paren
suffix:semicolon
multiline_comment|/* Async requests need to be freed here */
r_if
c_cond
(paren
id|req-&gt;uc_flags
op_amp
id|REQ_ASYNC
)paren
(brace
id|CODA_FREE
c_func
(paren
id|req-&gt;uc_data
comma
r_sizeof
(paren
r_struct
id|coda_in_hdr
)paren
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|req
comma
(paren
id|u_int
)paren
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|req-&gt;uc_flags
op_or_assign
id|REQ_ABORT
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;uc_sleep
)paren
suffix:semicolon
)brace
id|lh
op_assign
op_amp
id|vcp-&gt;vc_processing
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;wake up processing clients&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lh
op_assign
id|lh-&gt;next
)paren
op_ne
op_amp
id|vcp-&gt;vc_processing
)paren
(brace
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|uc_chain
)paren
suffix:semicolon
id|req-&gt;uc_flags
op_or_assign
id|REQ_ABORT
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;uc_sleep
)paren
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|coda_psdev_fops
r_static
r_struct
id|file_operations
id|coda_psdev_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|coda_psdev_read
comma
id|write
suffix:colon
id|coda_psdev_write
comma
id|poll
suffix:colon
id|coda_psdev_poll
comma
id|ioctl
suffix:colon
id|coda_psdev_ioctl
comma
id|open
suffix:colon
id|coda_psdev_open
comma
id|release
suffix:colon
id|coda_psdev_release
comma
)brace
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
op_assign
l_int|NULL
suffix:semicolon
DECL|function|init_coda_psdev
r_static
r_int
id|init_coda_psdev
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|devfs_register_chrdev
c_func
(paren
id|CODA_PSDEV_MAJOR
comma
l_string|&quot;coda_psdev&quot;
comma
op_amp
id|coda_psdev_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;coda_psdev: unable to get major %d&bslash;n&quot;
comma
id|CODA_PSDEV_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;coda&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register_series
(paren
id|devfs_handle
comma
l_string|&quot;%u&quot;
comma
id|MAX_CODADEVS
comma
id|DEVFS_FL_NONE
comma
id|CODA_PSDEV_MAJOR
comma
l_int|0
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|coda_psdev_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|coda_sysctl_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Peter J. Braam &lt;braam@cs.cmu.edu&gt;&quot;
)paren
suffix:semicolon
DECL|function|init_coda
r_static
r_int
id|__init
id|init_coda
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Coda Kernel/Venus communications, v5.3.9, coda@cs.cmu.edu&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|init_coda_psdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Problem (%d) in init_coda_psdev&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|status
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|coda_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda: failed in init_coda_fs!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|exit_coda
r_static
r_void
id|__exit
id|exit_coda
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|ENTRY
suffix:semicolon
id|err
op_assign
id|unregister_filesystem
c_func
(paren
op_amp
id|coda_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda: failed to unregister filesystem&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|devfs_unregister
(paren
id|devfs_handle
)paren
suffix:semicolon
id|devfs_unregister_chrdev
c_func
(paren
id|CODA_PSDEV_MAJOR
comma
l_string|&quot;coda_psdev&quot;
)paren
suffix:semicolon
id|coda_sysctl_clean
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_coda
id|module_init
c_func
(paren
id|init_coda
)paren
suffix:semicolon
DECL|variable|exit_coda
id|module_exit
c_func
(paren
id|exit_coda
)paren
suffix:semicolon
eof
