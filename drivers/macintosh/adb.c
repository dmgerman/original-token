multiline_comment|/*&n; * Device driver for the /dev/adb device on macintoshes.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/cuda.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|ADB_MAJOR
mdefine_line|#define ADB_MAJOR&t;56&t;/* major number for /dev/adb */
r_extern
r_void
id|adbdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|adbdev_state
r_struct
id|adbdev_state
(brace
DECL|member|req
r_struct
id|cuda_request
id|req
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|adb_wait
r_static
r_struct
id|wait_queue
op_star
id|adb_wait
suffix:semicolon
DECL|function|adb_wait_reply
r_static
r_int
id|adb_wait_reply
c_func
(paren
r_struct
id|adbdev_state
op_star
id|state
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|adb_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|state-&gt;req.got_reply
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
id|ret
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
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
id|ret
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
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|adb_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|adb_write_done
r_static
r_void
id|adb_write_done
c_func
(paren
r_struct
id|cuda_request
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|req-&gt;got_reply
)paren
(brace
id|req-&gt;reply_len
op_assign
l_int|0
suffix:semicolon
id|req-&gt;got_reply
op_assign
l_int|1
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|adb_wait
)paren
suffix:semicolon
)brace
DECL|function|adb_open
r_static
r_int
id|adb_open
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
id|adbdev_state
op_star
id|state
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
OG
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|adbdev_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|file-&gt;private_data
op_assign
id|state
suffix:semicolon
id|state-&gt;req.reply_expected
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adb_release
r_static
r_int
id|adb_release
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
id|adbdev_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
(brace
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;req.reply_expected
op_logical_and
op_logical_neg
id|state-&gt;req.got_reply
)paren
r_if
c_cond
(paren
id|adb_wait_reply
c_func
(paren
id|state
comma
id|file
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adb_lseek
r_static
r_int
r_int
id|adb_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|function|adb_read
r_static
r_int
id|adb_read
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
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|adbdev_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
r_sizeof
(paren
id|state-&gt;req.reply
)paren
)paren
id|count
op_assign
r_sizeof
(paren
id|state-&gt;req.reply
)paren
suffix:semicolon
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;req.reply_expected
)paren
r_return
l_int|0
suffix:semicolon
id|ret
op_assign
id|adb_wait_reply
c_func
(paren
id|state
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|ret
op_assign
id|state-&gt;req.reply_len
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
id|state-&gt;req.reply
comma
id|ret
)paren
suffix:semicolon
id|state-&gt;req.reply_expected
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|adb_write
r_static
r_int
id|adb_write
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
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|adbdev_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|count
template_param
r_sizeof
(paren
id|state-&gt;req.data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;req.reply_expected
op_logical_and
op_logical_neg
id|state-&gt;req.got_reply
)paren
(brace
multiline_comment|/* A previous request is still being processed.&n;&t;&t;   Wait for it to finish. */
id|ret
op_assign
id|adb_wait_reply
c_func
(paren
id|state
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
id|state-&gt;req.nbytes
op_assign
id|count
suffix:semicolon
id|state-&gt;req.done
op_assign
id|adb_write_done
suffix:semicolon
id|copy_from_user
c_func
(paren
id|state-&gt;req.data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|state-&gt;req.reply_expected
op_assign
l_int|1
suffix:semicolon
id|state-&gt;req.got_reply
op_assign
l_int|0
suffix:semicolon
id|cuda_send_request
c_func
(paren
op_amp
id|state-&gt;req
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|adb_fops
r_static
r_struct
id|file_operations
id|adb_fops
op_assign
(brace
id|adb_lseek
comma
id|adb_read
comma
id|adb_write
comma
l_int|NULL
comma
multiline_comment|/* no readdir */
l_int|NULL
comma
multiline_comment|/* no poll yet */
l_int|NULL
comma
multiline_comment|/* no ioctl yet */
l_int|NULL
comma
multiline_comment|/* no mmap */
id|adb_open
comma
id|adb_release
)brace
suffix:semicolon
DECL|function|adbdev_init
r_void
id|adbdev_init
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|ADB_MAJOR
comma
l_string|&quot;adb&quot;
comma
op_amp
id|adb_fops
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;adb: unable to get major %d&bslash;n&quot;
comma
id|ADB_MAJOR
)paren
suffix:semicolon
)brace
eof
