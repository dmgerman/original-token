multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/waitq.c&n; *&n; *  Copyright 1997 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
multiline_comment|/* We make this a static variable rather than a part of the superblock; it&n;   is better if we don&squot;t reassign numbers easily even across filesystems */
DECL|variable|autofs_next_wait_queue
r_static
r_int
id|autofs_next_wait_queue
op_assign
l_int|1
suffix:semicolon
DECL|function|autofs_catatonic_mode
r_void
id|autofs_catatonic_mode
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
comma
op_star
id|nwq
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: entering catatonic mode&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sbi-&gt;catatonic
op_assign
l_int|1
suffix:semicolon
id|wq
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Erase all wait queues */
r_while
c_loop
(paren
id|wq
)paren
(brace
id|nwq
op_assign
id|wq-&gt;next
suffix:semicolon
id|wq-&gt;status
op_assign
op_minus
id|ENOENT
suffix:semicolon
multiline_comment|/* Magic is gone - report failure */
id|kfree
c_func
(paren
id|wq-&gt;name
)paren
suffix:semicolon
id|wq-&gt;name
op_assign
l_int|NULL
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
id|wq
op_assign
id|nwq
suffix:semicolon
)brace
id|fput
c_func
(paren
id|sbi-&gt;pipe
)paren
suffix:semicolon
multiline_comment|/* Close the pipe */
)brace
DECL|function|autofs_write
r_static
r_int
id|autofs_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_void
op_star
id|addr
comma
r_int
id|bytes
)paren
(brace
r_int
r_int
id|fs
comma
id|sigpipe
comma
id|flags
suffix:semicolon
r_const
r_char
op_star
id|data
op_assign
(paren
r_const
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ssize_t
id|wr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/** WARNING: this is not safe for writing more than PIPE_BUF bytes! **/
id|sigpipe
op_assign
id|sigismember
c_func
(paren
op_amp
id|current-&gt;signal
comma
id|SIGPIPE
)paren
suffix:semicolon
multiline_comment|/* Save pointer to user space and point back to kernel space */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bytes
op_logical_and
(paren
id|wr
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|data
comma
id|bytes
comma
op_amp
id|file-&gt;f_pos
)paren
)paren
OG
l_int|0
)paren
(brace
id|data
op_add_assign
id|wr
suffix:semicolon
id|bytes
op_sub_assign
id|wr
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
multiline_comment|/* Keep the currently executing process from receiving a&n;&t;   SIGPIPE unless it was already supposed to get one */
r_if
c_cond
(paren
id|wr
op_eq
op_minus
id|EPIPE
op_logical_and
op_logical_neg
id|sigpipe
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|sigdelset
c_func
(paren
op_amp
id|current-&gt;signal
comma
id|SIGPIPE
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
(paren
id|bytes
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|autofs_notify_daemon
r_static
r_void
id|autofs_notify_daemon
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|autofs_wait_queue
op_star
id|wq
)paren
(brace
r_struct
id|autofs_packet_missing
id|pkt
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_wait: wait id = 0x%08lx, name = &quot;
comma
id|wq-&gt;wait_queue_token
)paren
)paren
suffix:semicolon
id|autofs_say
c_func
(paren
id|wq-&gt;name
comma
id|wq-&gt;len
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pkt
comma
l_int|0
comma
r_sizeof
id|pkt
)paren
suffix:semicolon
multiline_comment|/* For security reasons */
id|pkt.hdr.proto_version
op_assign
id|AUTOFS_PROTO_VERSION
suffix:semicolon
id|pkt.hdr.type
op_assign
id|autofs_ptype_missing
suffix:semicolon
id|pkt.wait_queue_token
op_assign
id|wq-&gt;wait_queue_token
suffix:semicolon
id|pkt.len
op_assign
id|wq-&gt;len
suffix:semicolon
id|memcpy
c_func
(paren
id|pkt.name
comma
id|wq-&gt;name
comma
id|pkt.len
)paren
suffix:semicolon
id|pkt.name
(braket
id|pkt.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|autofs_write
c_func
(paren
id|sbi-&gt;pipe
comma
op_amp
id|pkt
comma
r_sizeof
(paren
r_struct
id|autofs_packet_missing
)paren
)paren
)paren
id|autofs_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
DECL|function|autofs_wait
r_int
id|autofs_wait
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
suffix:semicolon
r_int
id|status
suffix:semicolon
r_for
c_loop
(paren
id|wq
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|wq
suffix:semicolon
id|wq
op_assign
id|wq-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|wq-&gt;hash
op_eq
id|name-&gt;hash
op_logical_and
id|wq-&gt;len
op_eq
id|name-&gt;len
op_logical_and
id|wq-&gt;name
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|wq-&gt;name
comma
id|name-&gt;name
comma
id|name-&gt;len
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
(brace
multiline_comment|/* Create a new wait queue */
id|wq
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|autofs_wait_queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|wq-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|name-&gt;len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wq-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|wq-&gt;wait_queue_token
op_assign
id|autofs_next_wait_queue
op_increment
suffix:semicolon
id|init_waitqueue
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
id|wq-&gt;hash
op_assign
id|name-&gt;hash
suffix:semicolon
id|wq-&gt;len
op_assign
id|name-&gt;len
suffix:semicolon
id|wq-&gt;status
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* Status return if interrupted */
id|memcpy
c_func
(paren
id|wq-&gt;name
comma
id|name-&gt;name
comma
id|name-&gt;len
)paren
suffix:semicolon
id|wq-&gt;next
op_assign
id|sbi-&gt;queues
suffix:semicolon
id|sbi-&gt;queues
op_assign
id|wq
suffix:semicolon
multiline_comment|/* autofs_notify_daemon() may block */
id|wq-&gt;wait_ctr
op_assign
l_int|2
suffix:semicolon
id|autofs_notify_daemon
c_func
(paren
id|sbi
comma
id|wq
)paren
suffix:semicolon
)brace
r_else
id|wq-&gt;wait_ctr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|wq-&gt;name
)paren
(brace
multiline_comment|/* wq-&gt;name is NULL if and only if the lock is released */
id|interruptible_sleep_on
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
)brace
r_else
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_wait: skipped sleeping&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|status
op_assign
id|wq-&gt;status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|wq-&gt;wait_ctr
)paren
multiline_comment|/* Are we the last process to need status? */
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|autofs_wait_release
r_int
id|autofs_wait_release
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
r_int
id|wait_queue_token
comma
r_int
id|status
)paren
(brace
r_struct
id|autofs_wait_queue
op_star
id|wq
comma
op_star
op_star
id|wql
suffix:semicolon
r_for
c_loop
(paren
id|wql
op_assign
op_amp
id|sbi-&gt;queues
suffix:semicolon
(paren
id|wq
op_assign
op_star
id|wql
)paren
suffix:semicolon
id|wql
op_assign
op_amp
id|wq-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|wq-&gt;wait_queue_token
op_eq
id|wait_queue_token
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|wq
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|wql
op_assign
id|wq-&gt;next
suffix:semicolon
multiline_comment|/* Unlink from chain */
id|kfree
c_func
(paren
id|wq-&gt;name
)paren
suffix:semicolon
id|wq-&gt;name
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Do not wait on this queue */
id|wq-&gt;status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|wq-&gt;wait_ctr
)paren
multiline_comment|/* Is anyone still waiting for this guy? */
id|kfree
c_func
(paren
id|wq
)paren
suffix:semicolon
r_else
id|wake_up
c_func
(paren
op_amp
id|wq-&gt;queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
