multiline_comment|/*&n; *&t;linux/kernel/ioport.c&n; *&n; * This contains the io-permission bitmap code - written by obz, with changes&n; * by Linus.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;errno.h&gt;
DECL|macro|_IODEBUG
mdefine_line|#define _IODEBUG
macro_line|#ifdef IODEBUG
DECL|function|ios
r_static
r_char
op_star
id|ios
c_func
(paren
r_int
r_int
id|l
)paren
(brace
r_static
r_char
id|str
(braket
l_int|33
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|mask
op_assign
l_int|0x80000000
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
op_increment
id|i
comma
id|mask
op_rshift_assign
l_int|1
)paren
id|str
(braket
id|i
)braket
op_assign
(paren
id|l
op_amp
id|mask
)paren
ques
c_cond
l_char|&squot;1&squot;
suffix:colon
l_char|&squot;0&squot;
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
DECL|function|dump_io_bitmap
r_static
r_void
id|dump_io_bitmap
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|numl
op_assign
r_sizeof
(paren
id|current-&gt;tss.io_bitmap
)paren
op_rshift
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|numl
suffix:semicolon
op_increment
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%4d [%3x]: &quot;
comma
l_int|64
op_star
id|i
comma
l_int|64
op_star
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|ios
c_func
(paren
id|current-&gt;tss.io_bitmap
(braket
id|j
op_increment
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|numl
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ios
c_func
(paren
id|current-&gt;tss.io_bitmap
(braket
id|j
op_increment
)braket
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * this changes the io permissions bitmap in the current task.&n; */
DECL|function|sys_ioperm
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|turn_on
)paren
(brace
r_int
r_int
id|froml
comma
id|lindex
comma
id|tnum
comma
id|numl
comma
id|rindex
comma
id|mask
suffix:semicolon
r_int
r_int
op_star
id|iop
suffix:semicolon
id|froml
op_assign
id|from
op_rshift
l_int|5
suffix:semicolon
id|lindex
op_assign
id|from
op_amp
l_int|0x1f
suffix:semicolon
id|tnum
op_assign
id|lindex
op_plus
id|num
suffix:semicolon
id|numl
op_assign
(paren
id|tnum
op_plus
l_int|0x1f
)paren
op_rshift
l_int|5
suffix:semicolon
id|rindex
op_assign
id|tnum
op_amp
l_int|0x1f
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
r_if
c_cond
(paren
id|froml
op_star
l_int|32
op_plus
id|tnum
OG
r_sizeof
(paren
id|current-&gt;tss.io_bitmap
)paren
op_star
l_int|8
op_minus
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#ifdef IODEBUG
id|printk
c_func
(paren
l_string|&quot;io: from=%d num=%d %s&bslash;n&quot;
comma
id|from
comma
id|num
comma
(paren
id|turn_on
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|numl
)paren
(brace
id|iop
op_assign
(paren
r_int
r_int
op_star
)paren
id|current-&gt;tss.io_bitmap
op_plus
id|froml
suffix:semicolon
r_if
c_cond
(paren
id|lindex
op_ne
l_int|0
)paren
(brace
id|mask
op_assign
(paren
op_complement
l_int|0
op_lshift
id|lindex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|numl
op_eq
l_int|0
op_logical_and
id|rindex
)paren
id|mask
op_and_assign
op_complement
(paren
op_complement
l_int|0
op_lshift
id|rindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|turn_on
)paren
op_star
id|iop
op_increment
op_and_assign
op_complement
id|mask
suffix:semicolon
r_else
op_star
id|iop
op_increment
op_or_assign
id|mask
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numl
)paren
(brace
r_if
c_cond
(paren
id|rindex
)paren
op_decrement
id|numl
suffix:semicolon
id|mask
op_assign
(paren
id|turn_on
ques
c_cond
l_int|0
suffix:colon
op_complement
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|numl
op_decrement
)paren
op_star
id|iop
op_increment
op_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|numl
op_logical_and
id|rindex
)paren
(brace
id|mask
op_assign
op_complement
(paren
op_complement
l_int|0
op_lshift
id|rindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|turn_on
)paren
op_star
id|iop
op_increment
op_and_assign
op_complement
id|mask
suffix:semicolon
r_else
op_star
id|iop
op_increment
op_or_assign
id|mask
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
