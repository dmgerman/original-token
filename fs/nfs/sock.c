multiline_comment|/*&n; *  linux/fs/nfs/sock.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  low-level nfs remote procedure call interface&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;../../net/kern_sock.h&quot;
r_extern
r_struct
id|socket
op_star
id|socki_lookup
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/*&n; * We violate some modularity principles here by poking around&n; * in some socket internals.  Besides having to call socket&n; * functions from kernel-space instead of user space, the socket&n; * interface does not lend itself well to being cleanly called&n; * without a file descriptor.  Since the nfs calls can run on&n; * behalf of any process, the superblock maintains a file pointer&n; * to the server socket.&n; */
DECL|function|do_nfs_rpc_call
r_static
r_int
id|do_nfs_rpc_call
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_int
op_star
id|start
comma
r_int
op_star
id|end
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_int
r_int
id|fs
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_int
id|len
suffix:semicolon
id|select_table
id|wait_table
suffix:semicolon
r_struct
id|select_table_entry
id|entry
suffix:semicolon
r_int
(paren
op_star
id|select
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
id|select_table
op_star
)paren
suffix:semicolon
r_int
id|init_timeout
comma
id|max_timeout
suffix:semicolon
r_int
id|timeout
suffix:semicolon
r_int
id|retrans
suffix:semicolon
r_int
id|major_timeout_seen
suffix:semicolon
r_char
op_star
id|server_name
suffix:semicolon
r_int
id|n
suffix:semicolon
id|xid
op_assign
id|start
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
(paren
(paren
r_char
op_star
)paren
id|end
)paren
op_minus
(paren
(paren
r_char
op_star
)paren
id|start
)paren
suffix:semicolon
id|file
op_assign
id|server-&gt;file
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_inode
suffix:semicolon
id|select
op_assign
id|file-&gt;f_op-&gt;select
suffix:semicolon
id|sock
op_assign
id|socki_lookup
c_func
(paren
id|inode
)paren
suffix:semicolon
id|init_timeout
op_assign
id|server-&gt;timeo
suffix:semicolon
id|max_timeout
op_assign
id|NFS_MAX_RPC_TIMEOUT
op_star
id|HZ
op_div
l_int|10
suffix:semicolon
id|retrans
op_assign
id|server-&gt;retrans
suffix:semicolon
id|major_timeout_seen
op_assign
l_int|0
suffix:semicolon
id|server_name
op_assign
id|server-&gt;hostname
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_rpc_call: socki_lookup failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|__asm__
c_func
(paren
l_string|&quot;mov %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
l_int|0x10
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|timeout
op_assign
id|init_timeout
suffix:semicolon
suffix:semicolon
id|n
op_increment
comma
id|timeout
op_lshift_assign
l_int|1
)paren
(brace
id|result
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|send
c_func
(paren
id|sock
comma
(paren
r_void
op_star
)paren
id|start
comma
id|len
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_rpc_call: send error = %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|re_select
suffix:colon
id|wait_table.nr
op_assign
l_int|0
suffix:semicolon
id|wait_table.entry
op_assign
op_amp
id|entry
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|select
c_func
(paren
id|inode
comma
id|file
comma
id|SEL_IN
comma
op_amp
id|wait_table
)paren
op_logical_and
op_logical_neg
id|select
c_func
(paren
id|inode
comma
id|file
comma
id|SEL_IN
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|timeout
OG
id|max_timeout
)paren
id|timeout
op_assign
id|max_timeout
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|entry.wait_address
comma
op_amp
id|entry.wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
macro_line|#if 0
multiline_comment|/* doesn&squot;t work yet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|server-&gt;flags
op_amp
id|NFS_MOUNT_INTR
)paren
)paren
r_goto
id|re_select
suffix:semicolon
macro_line|#endif
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;timeout
)paren
(brace
r_if
c_cond
(paren
id|n
OL
id|retrans
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;flags
op_amp
id|NFS_MOUNT_SOFT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS server %s not responding, &quot;
l_string|&quot;timed out&quot;
comma
id|server_name
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|n
op_assign
l_int|0
suffix:semicolon
id|timeout
op_assign
id|init_timeout
suffix:semicolon
id|init_timeout
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|major_timeout_seen
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS server %s not responding, &quot;
l_string|&quot;still trying&bslash;n&quot;
comma
id|server_name
)paren
suffix:semicolon
)brace
id|major_timeout_seen
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|wait_table.nr
)paren
id|remove_wait_queue
c_func
(paren
id|entry.wait_address
comma
op_amp
id|entry.wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|result
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|recv
c_func
(paren
id|sock
comma
(paren
r_void
op_star
)paren
id|start
comma
l_int|4096
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_rpc_call: bad select ready&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|re_select
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_ne
op_minus
id|ERESTARTSYS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_rpc_call: recv error = %d&bslash;n&quot;
comma
op_minus
id|result
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|start
op_eq
id|xid
)paren
(brace
r_if
c_cond
(paren
id|major_timeout_seen
)paren
id|printk
c_func
(paren
l_string|&quot;NFS server %s OK&bslash;n&quot;
comma
id|server_name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;nfs_rpc_call: XID mismatch&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * For now we lock out other simulaneous nfs calls for the same filesytem&n; * because we are single-threaded and don&squot;t want to get mismatched&n; * RPC replies.&n; */
DECL|function|nfs_rpc_call
r_int
id|nfs_rpc_call
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_int
op_star
id|start
comma
r_int
op_star
id|end
)paren
(brace
r_int
id|result
suffix:semicolon
r_while
c_loop
(paren
id|server-&gt;lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|server-&gt;wait
)paren
suffix:semicolon
id|server-&gt;lock
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
id|do_nfs_rpc_call
c_func
(paren
id|server
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|server-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|server-&gt;wait
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof