multiline_comment|/*&n; *  linux/kernel/printk.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|variable|buf
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
suffix:semicolon
r_extern
r_void
id|console_print
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|variable|log_page
r_static
r_int
r_int
id|log_page
op_assign
l_int|0
suffix:semicolon
DECL|variable|log_start
r_static
r_int
r_int
id|log_start
op_assign
l_int|0
suffix:semicolon
DECL|variable|log_size
r_static
r_int
r_int
id|log_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|log_wait
r_static
r_struct
id|wait_queue
op_star
id|log_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|function|sys_syslog
r_int
id|sys_syslog
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
id|i
op_assign
id|log_page
suffix:semicolon
id|log_page
op_assign
l_int|0
suffix:semicolon
id|free_page
c_func
(paren
id|i
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|log_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
id|i
op_assign
id|get_free_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_page
)paren
(brace
id|free_page
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|log_page
op_assign
id|i
)paren
(brace
id|log_start
op_assign
id|log_size
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
id|verify_area
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|log_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|log_page
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|log_size
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|log_wait
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|log_size
op_logical_and
id|len
)paren
(brace
id|c
op_assign
op_star
(paren
(paren
r_char
op_star
)paren
id|log_page
op_plus
id|log_start
)paren
suffix:semicolon
id|log_start
op_increment
suffix:semicolon
id|log_size
op_decrement
suffix:semicolon
id|log_start
op_and_assign
l_int|4095
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|c
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|printk
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
op_logical_and
id|log_page
suffix:semicolon
id|j
op_increment
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|log_page
op_plus
(paren
l_int|4095
op_amp
(paren
id|log_start
op_plus
id|log_size
)paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|buf
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|log_size
OL
l_int|4096
)paren
id|log_size
op_increment
suffix:semicolon
r_else
id|log_start
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|log_page
)paren
id|wake_up
c_func
(paren
op_amp
id|log_wait
)paren
suffix:semicolon
id|console_print
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
