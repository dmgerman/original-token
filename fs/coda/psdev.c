multiline_comment|/*&n; *      &t;An implementation of a loadable kernel mode driver providing&n; *&t;&t;multiple kernel/user space bidirectional communications links.&n; *&n; * &t;&t;Author: &t;Alan Cox &lt;alan@cymru.net&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; * &n; *              Adapted to become the Linux 2.0 Coda pseudo device&n; *              Peter  Braam  &lt;braam@maths.ox.ac.uk&gt; &n; *              Michael Callahan &lt;mjc@emmy.smith.edu&gt;           &n; *&n; *              Changes for Linux 2.1&n; *              Copyright (c) 1997 Carnegie-Mellon University&n; */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_PROC_FS */
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
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_cnode.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
macro_line|#include &lt;linux/coda_sysctl.h&gt;
multiline_comment|/*&n; * Where is the prototype?&n; */
r_int
id|proc_register_dynamic
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
r_struct
id|proc_dir_entry
op_star
id|dp
)paren
suffix:semicolon
multiline_comment|/* &n; * Coda stuff&n; */
r_extern
r_struct
id|file_system_type
id|coda_fs_type
suffix:semicolon
r_extern
r_int
id|init_coda_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cfsnc_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
suffix:semicolon
r_extern
r_int
id|cfsnc_nc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
suffix:semicolon
multiline_comment|/* statistics */
DECL|variable|coda_callstats
r_struct
id|coda_upcallstats
id|coda_callstats
suffix:semicolon
DECL|variable|coda_hard
r_int
id|coda_hard
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* introduces a timeout on upcalls */
DECL|variable|coda_timeout
r_int
r_int
id|coda_timeout
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* .. secs, then signals will dequeue */
r_extern
r_struct
id|coda_sb_info
id|coda_super_info
(braket
id|MAX_CODADEVS
)braket
suffix:semicolon
DECL|variable|psdev_vcomm
r_struct
id|vcomm
id|psdev_vcomm
(braket
id|MAX_CODADEVS
)braket
suffix:semicolon
multiline_comment|/* queue stuff for the messages */
DECL|function|init_queue
r_static
r_inline
r_void
id|init_queue
c_func
(paren
r_struct
id|queue
op_star
id|head
)paren
(brace
id|head-&gt;forw
op_assign
id|head
suffix:semicolon
id|head-&gt;back
op_assign
id|head
suffix:semicolon
)brace
DECL|function|q_getnext
r_static
r_inline
r_struct
id|vmsg
op_star
id|q_getnext
c_func
(paren
r_struct
id|queue
op_star
id|elt
)paren
(brace
r_return
(paren
r_struct
id|vmsg
op_star
)paren
(paren
id|elt-&gt;forw
)paren
suffix:semicolon
)brace
DECL|function|q_end
r_static
r_inline
r_int
id|q_end
c_func
(paren
r_struct
id|vmsg
op_star
id|msg
comma
r_struct
id|queue
op_star
id|queue
)paren
(brace
r_return
(paren
r_struct
id|queue
op_star
)paren
id|msg
op_eq
id|queue
suffix:semicolon
)brace
DECL|function|q_empty
r_static
r_inline
r_int
id|q_empty
c_func
(paren
r_struct
id|queue
op_star
id|queue
)paren
(brace
r_return
id|queue-&gt;forw
op_eq
id|queue
suffix:semicolon
)brace
multiline_comment|/* insert before head, ie. at the tail */
DECL|function|coda_q_insert
r_void
id|coda_q_insert
c_func
(paren
r_struct
id|queue
op_star
id|el
comma
r_struct
id|queue
op_star
id|head
)paren
(brace
id|el-&gt;forw
op_assign
id|head-&gt;back-&gt;forw
suffix:semicolon
id|el-&gt;back
op_assign
id|head-&gt;back
suffix:semicolon
id|head-&gt;back-&gt;forw
op_assign
id|el
suffix:semicolon
id|head-&gt;back
op_assign
id|el
suffix:semicolon
)brace
DECL|function|coda_q_remove
r_void
id|coda_q_remove
c_func
(paren
r_struct
id|queue
op_star
id|el
)paren
(brace
id|el-&gt;forw-&gt;back
op_assign
id|el-&gt;back
suffix:semicolon
id|el-&gt;back-&gt;forw
op_assign
id|el-&gt;forw
suffix:semicolon
)brace
DECL|function|coda_psdev2vcomm
r_static
r_struct
id|vcomm
op_star
id|coda_psdev2vcomm
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|vcomm
op_star
id|vcp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|minor
op_ge
l_int|0
)paren
op_logical_and
(paren
id|minor
OL
id|MAX_CODADEVS
)paren
)paren
id|vcp
op_assign
op_amp
id|psdev_vcomm
(braket
id|minor
)braket
suffix:semicolon
r_return
id|vcp
suffix:semicolon
)brace
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
id|vcomm
op_star
id|vcp
op_assign
id|coda_psdev2vcomm
c_func
(paren
id|file
)paren
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
(paren
id|vcp-&gt;vc_waitq
)paren
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q_empty
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
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
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|vcomm
op_star
id|vcp
op_assign
id|coda_psdev2vcomm
c_func
(paren
id|file
)paren
suffix:semicolon
r_struct
id|vmsg
op_star
id|vmp
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|size
suffix:semicolon
id|u_long
id|uniq
suffix:semicolon
id|u_long
id|opcode
suffix:semicolon
id|u_long
id|opcodebuf
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* Peek at the opcode, uniquefier */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|opcodebuf
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
id|opcode
op_assign
id|opcodebuf
(braket
l_int|0
)braket
suffix:semicolon
id|uniq
op_assign
id|opcodebuf
(braket
l_int|1
)braket
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;(process,opc,uniq)=(%d,%ld,%ld)&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|opcode
comma
id|uniq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DOWNCALL
c_func
(paren
id|opcode
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
id|printk
c_func
(paren
l_string|&quot;coda_psdev_write: downcall, no SB!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|count
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
id|count
OL
r_sizeof
(paren
r_struct
id|cfs_out_hdr
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_downcall opc %ld uniq %ld, not enough!&bslash;n&quot;
comma
id|opcode
comma
id|uniq
)paren
suffix:semicolon
r_return
id|count
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
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Coda: downcall opc %ld, uniq %ld, too much!&quot;
comma
id|opcode
comma
id|uniq
)paren
suffix:semicolon
id|count
op_assign
id|size
suffix:semicolon
)brace
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
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* what downcall errors does Venus handle ? */
id|error
op_assign
id|coda_downcall
c_func
(paren
id|opcode
comma
id|dcbuf
comma
id|sb
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
r_return
l_int|0
suffix:semicolon
)brace
id|CODA_FREE
c_func
(paren
id|dcbuf
comma
id|size
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* Look for the message on the processing queue. */
r_for
c_loop
(paren
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
op_logical_neg
id|q_end
c_func
(paren
id|vmp
comma
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|vmp-&gt;vm_unique
op_eq
id|uniq
)paren
(brace
r_break
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Eureka: uniq %ld on queue!&bslash;n&quot;
comma
id|uniq
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|q_end
c_func
(paren
id|vmp
comma
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_write: msg (%ld, %ld) not found&bslash;n&quot;
comma
id|opcode
comma
id|uniq
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
multiline_comment|/* Remove the message from the processing queue */
id|coda_q_remove
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
)paren
suffix:semicolon
multiline_comment|/* move data into response buffer. */
r_if
c_cond
(paren
id|vmp-&gt;vm_outSize
OL
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_write: too much cnt: %d, cnt: %d, opc: %ld, uniq: %ld.&bslash;n&quot;
comma
id|vmp-&gt;vm_outSize
comma
id|count
comma
id|opcode
comma
id|uniq
)paren
suffix:semicolon
id|count
op_assign
id|vmp-&gt;vm_outSize
suffix:semicolon
multiline_comment|/* don&squot;t have more space! */
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|vmp-&gt;vm_data
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* adjust outsize. is this usefull ?? */
id|vmp-&gt;vm_outSize
op_assign
id|count
suffix:semicolon
id|vmp-&gt;vm_flags
op_or_assign
id|VM_WRITE
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Found! Count %d for (opc,uniq)=(%ld,%ld), vmsg at %x&bslash;n&quot;
comma
id|count
comma
id|opcode
comma
id|uniq
comma
(paren
r_int
)paren
op_amp
id|vmp
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|vmp-&gt;vm_sleep
)paren
suffix:semicolon
r_return
id|count
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
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|vcomm
op_star
id|vcp
op_assign
id|coda_psdev2vcomm
c_func
(paren
id|file
)paren
suffix:semicolon
r_struct
id|vmsg
op_star
id|vmp
suffix:semicolon
r_int
id|result
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* Get message at head of request queue. */
r_if
c_cond
(paren
id|q_empty
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
)paren
suffix:semicolon
id|coda_q_remove
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
)paren
suffix:semicolon
multiline_comment|/* Move the input args into userspace */
r_if
c_cond
(paren
id|vmp-&gt;vm_inSize
op_le
id|count
)paren
id|result
op_assign
id|vmp-&gt;vm_inSize
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|vmp-&gt;vm_inSize
)paren
(brace
id|printk
(paren
l_string|&quot;psdev_read: Venus read %d bytes of %d in message&bslash;n&quot;
comma
id|count
comma
id|vmp-&gt;vm_inSize
)paren
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
id|vmp-&gt;vm_data
comma
id|result
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|vmp-&gt;vm_chain.forw
op_eq
l_int|0
op_logical_or
id|vmp-&gt;vm_chain.back
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;coda_psdev_read: bad chain&quot;
)paren
suffix:semicolon
multiline_comment|/* If request was a signal, don&squot;t enqueue */
r_if
c_cond
(paren
id|vmp-&gt;vm_opcode
op_eq
id|CFS_SIGNAL
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;vcread: signal msg (%d, %d)&bslash;n&quot;
comma
id|vmp-&gt;vm_opcode
comma
id|vmp-&gt;vm_unique
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|vmp-&gt;vm_data
comma
r_sizeof
(paren
r_struct
id|cfs_in_hdr
)paren
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|vmp
comma
r_sizeof
(paren
r_struct
id|vmsg
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
id|vmp-&gt;vm_flags
op_or_assign
id|VM_READ
suffix:semicolon
id|coda_q_insert
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
comma
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
r_return
id|result
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
r_register
r_struct
id|vcomm
op_star
id|vcp
op_assign
l_int|NULL
suffix:semicolon
id|ENTRY
suffix:semicolon
id|vcp
op_assign
id|coda_psdev2vcomm
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|vcp-&gt;vc_inuse
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|memset
c_func
(paren
id|vcp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vcomm
)paren
)paren
suffix:semicolon
id|vcp-&gt;vc_inuse
op_assign
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|init_queue
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
)paren
suffix:semicolon
id|init_queue
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|coda_callstats
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|coda_upcallstats
)paren
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|coda_psdev_release
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
id|vcomm
op_star
id|vcp
suffix:semicolon
r_struct
id|vmsg
op_star
id|vmp
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
id|ENTRY
suffix:semicolon
id|vcp
op_assign
id|coda_psdev2vcomm
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcp
op_logical_or
op_logical_neg
id|vcomm_open
c_func
(paren
id|vcp
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;psdev_release: not open&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* flush the name cache so that we can unmount */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Flushing the cache.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* cfsnc_flush(); */
multiline_comment|/* cfsnc_use = 0; */
id|CDEBUG
c_func
(paren
id|D_PSDEV
comma
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* if operations are in progress perhaps the kernel&n;&t;   can profit from setting the C_DYING flag on the root &n;&t;   cnode of Coda filesystems */
r_if
c_cond
(paren
id|coda_super_info
(braket
id|minor
)braket
dot
id|sbi_root
)paren
(brace
r_struct
id|cnode
op_star
id|cnp
op_assign
id|ITOC
c_func
(paren
id|coda_super_info
(braket
id|minor
)braket
dot
id|sbi_root
)paren
suffix:semicolon
id|cnp-&gt;c_flags
op_or_assign
id|C_DYING
suffix:semicolon
)brace
r_else
id|vcp-&gt;vc_inuse
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Wakeup clients so they can return. */
r_for
c_loop
(paren
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
)paren
suffix:semicolon
op_logical_neg
id|q_end
c_func
(paren
id|vmp
comma
op_amp
(paren
id|vcp-&gt;vc_pending
)paren
)paren
suffix:semicolon
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
)paren
)paren
(brace
multiline_comment|/* Free signal request messages and don&squot;t wakeup cause&n;                 no one is waiting. */
r_if
c_cond
(paren
id|vmp-&gt;vm_opcode
op_eq
id|CFS_SIGNAL
)paren
(brace
id|CODA_FREE
c_func
(paren
id|vmp-&gt;vm_data
comma
r_sizeof
(paren
r_struct
id|cfs_in_hdr
)paren
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|vmp
comma
(paren
id|u_int
)paren
r_sizeof
(paren
r_struct
id|vmsg
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|vmp-&gt;vm_sleep
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
op_logical_neg
id|q_end
c_func
(paren
id|vmp
comma
op_amp
(paren
id|vcp-&gt;vc_processing
)paren
)paren
suffix:semicolon
id|vmp
op_assign
id|q_getnext
c_func
(paren
op_amp
(paren
id|vmp-&gt;vm_chain
)paren
)paren
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|vmp-&gt;vm_sleep
)paren
suffix:semicolon
)brace
id|mark_vcomm_closed
c_func
(paren
id|vcp
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|EXIT
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
l_int|NULL
comma
multiline_comment|/* llseek */
id|coda_psdev_read
comma
multiline_comment|/* read */
id|coda_psdev_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* coda_psdev_readdir */
id|coda_psdev_poll
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* coda_psdev_mmap */
id|coda_psdev_open
comma
multiline_comment|/* open */
id|coda_psdev_release
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
multiline_comment|/* lock */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_coda
r_struct
id|proc_dir_entry
id|proc_coda
op_assign
(brace
l_int|0
comma
l_int|4
comma
l_string|&quot;coda&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IWUSR
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_net_inode_operations
comma
)brace
suffix:semicolon
DECL|variable|proc_coda_ncstats
r_struct
id|proc_dir_entry
id|proc_coda_ncstats
op_assign
(brace
l_int|0
comma
l_int|12
comma
l_string|&quot;coda-ncstats&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_net_inode_operations
comma
id|cfsnc_nc_info
)brace
suffix:semicolon
macro_line|#endif
DECL|function|init_coda_psdev
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
id|register_chrdev
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
id|memset
c_func
(paren
id|psdev_vcomm
comma
l_int|0
comma
r_sizeof
(paren
id|psdev_vcomm
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|coda_super_info
comma
l_int|0
comma
r_sizeof
(paren
id|coda_super_info
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|coda_callstats
comma
l_int|0
comma
r_sizeof
(paren
id|coda_callstats
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_coda
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_coda
comma
op_amp
id|proc_coda_ncstats
)paren
suffix:semicolon
id|coda_sysctl_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif 
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Peter J. Braam &lt;braam@cs.cmu.edu&gt;&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
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
l_string|&quot;Coda Kernel/User communications module 1.0&bslash;n&quot;
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
id|init_coda_fs
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
l_string|&quot;coda: failed in init_coda_fs!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|unregister_filesystem
c_func
(paren
op_amp
id|coda_fs_type
)paren
)paren
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
id|unregister_chrdev
c_func
(paren
id|CODA_PSDEV_MAJOR
comma
l_string|&quot;coda_psdev&quot;
)paren
suffix:semicolon
macro_line|#if CONFIG_PROC_FS
id|coda_sysctl_clean
c_func
(paren
)paren
suffix:semicolon
id|proc_unregister
c_func
(paren
op_amp
id|proc_coda
comma
id|proc_coda_ncstats.low_ino
)paren
suffix:semicolon
id|proc_unregister
c_func
(paren
op_amp
id|proc_root
comma
id|proc_coda.low_ino
)paren
suffix:semicolon
macro_line|#endif 
)brace
macro_line|#endif
eof
