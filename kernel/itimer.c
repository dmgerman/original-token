multiline_comment|/*&n; * linux/kernel/itimer.c&n; *&n; * Copyright (C) 1992 Darren Senn&n; */
multiline_comment|/* These are all the functions necessary to implement itimers */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * change timeval to jiffies, trying to avoid the &n; * most obvious overflows..&n; *&n; * The tv_*sec values are signed, but nothing seems to &n; * indicate whether we really should use them as signed values&n; * when doing itimers. POSIX doesn&squot;t mention this (but if&n; * alarm() uses itimers without checking, we have to use unsigned&n; * arithmetic).&n; */
DECL|function|tvtojiffies
r_static
r_int
r_int
id|tvtojiffies
c_func
(paren
r_struct
id|timeval
op_star
id|value
)paren
(brace
r_int
r_int
id|sec
op_assign
(paren
r_int
)paren
id|value-&gt;tv_sec
suffix:semicolon
r_int
r_int
id|usec
op_assign
(paren
r_int
)paren
id|value-&gt;tv_usec
suffix:semicolon
r_if
c_cond
(paren
id|sec
OG
(paren
id|ULONG_MAX
op_div
id|HZ
)paren
)paren
r_return
id|ULONG_MAX
suffix:semicolon
id|usec
op_add_assign
l_int|1000000
op_div
id|HZ
op_minus
l_int|1
suffix:semicolon
id|usec
op_div_assign
l_int|1000000
op_div
id|HZ
suffix:semicolon
r_return
id|HZ
op_star
id|sec
op_plus
id|usec
suffix:semicolon
)brace
DECL|function|jiffiestotv
r_static
r_void
id|jiffiestotv
c_func
(paren
r_int
r_int
id|jiffies
comma
r_struct
id|timeval
op_star
id|value
)paren
(brace
id|value-&gt;tv_usec
op_assign
(paren
id|jiffies
op_mod
id|HZ
)paren
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|jiffies
op_div
id|HZ
suffix:semicolon
)brace
DECL|function|do_getitimer
r_int
id|do_getitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
id|value
)paren
(brace
r_register
r_int
r_int
id|val
comma
id|interval
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|ITIMER_REAL
suffix:colon
id|interval
op_assign
id|current-&gt;it_real_incr
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|current-&gt;real_timer
)paren
)paren
(brace
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
id|val
op_assign
id|current-&gt;real_timer.expires
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|current-&gt;real_timer
)paren
suffix:semicolon
multiline_comment|/* look out for negative/zero itimer.. */
r_if
c_cond
(paren
id|val
op_le
id|now
)paren
id|val
op_assign
id|now
op_plus
l_int|1
suffix:semicolon
id|val
op_sub_assign
id|now
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ITIMER_VIRTUAL
suffix:colon
id|val
op_assign
id|current-&gt;it_virt_value
suffix:semicolon
id|interval
op_assign
id|current-&gt;it_virt_incr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITIMER_PROF
suffix:colon
id|val
op_assign
id|current-&gt;it_prof_value
suffix:semicolon
id|interval
op_assign
id|current-&gt;it_prof_incr
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|jiffiestotv
c_func
(paren
id|val
comma
op_amp
id|value-&gt;it_value
)paren
suffix:semicolon
id|jiffiestotv
c_func
(paren
id|interval
comma
op_amp
id|value-&gt;it_interval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* SMP: Only we modify our itimer values. */
DECL|function|sys_getitimer
id|asmlinkage
r_int
id|sys_getitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
id|value
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_struct
id|itimerval
id|get_buffer
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|error
op_assign
id|do_getitimer
c_func
(paren
id|which
comma
op_amp
id|get_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|copy_to_user
c_func
(paren
id|value
comma
op_amp
id|get_buffer
comma
r_sizeof
(paren
id|get_buffer
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|it_real_fn
r_void
id|it_real_fn
c_func
(paren
r_int
r_int
id|__data
)paren
(brace
r_struct
id|task_struct
op_star
id|p
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
id|__data
suffix:semicolon
r_int
r_int
id|interval
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGALRM
comma
id|p
comma
l_int|1
)paren
suffix:semicolon
id|interval
op_assign
id|p-&gt;it_real_incr
suffix:semicolon
r_if
c_cond
(paren
id|interval
)paren
(brace
r_int
r_int
id|timeout
op_assign
id|jiffies
op_plus
id|interval
suffix:semicolon
multiline_comment|/* check for overflow */
r_if
c_cond
(paren
id|timeout
OL
id|interval
)paren
id|timeout
op_assign
id|ULONG_MAX
suffix:semicolon
id|p-&gt;real_timer.expires
op_assign
id|timeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|p-&gt;real_timer
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_setitimer
r_int
id|do_setitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
id|value
comma
r_struct
id|itimerval
op_star
id|ovalue
)paren
(brace
r_register
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|k
suffix:semicolon
id|i
op_assign
id|tvtojiffies
c_func
(paren
op_amp
id|value-&gt;it_interval
)paren
suffix:semicolon
id|j
op_assign
id|tvtojiffies
c_func
(paren
op_amp
id|value-&gt;it_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ovalue
op_logical_and
(paren
id|k
op_assign
id|do_getitimer
c_func
(paren
id|which
comma
id|ovalue
)paren
)paren
OL
l_int|0
)paren
r_return
id|k
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|ITIMER_REAL
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|current-&gt;real_timer
)paren
suffix:semicolon
id|current-&gt;it_real_value
op_assign
id|j
suffix:semicolon
id|current-&gt;it_real_incr
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
r_break
suffix:semicolon
id|i
op_assign
id|j
op_plus
id|jiffies
suffix:semicolon
multiline_comment|/* check for overflow.. */
r_if
c_cond
(paren
id|i
OL
id|j
)paren
id|i
op_assign
id|ULONG_MAX
suffix:semicolon
id|current-&gt;real_timer.expires
op_assign
id|i
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|current-&gt;real_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITIMER_VIRTUAL
suffix:colon
r_if
c_cond
(paren
id|j
)paren
id|j
op_increment
suffix:semicolon
id|current-&gt;it_virt_value
op_assign
id|j
suffix:semicolon
id|current-&gt;it_virt_incr
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITIMER_PROF
suffix:colon
r_if
c_cond
(paren
id|j
)paren
id|j
op_increment
suffix:semicolon
id|current-&gt;it_prof_value
op_assign
id|j
suffix:semicolon
id|current-&gt;it_prof_incr
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* SMP: Again, only we play with our itimers, and signals are SMP safe&n; *      now so that is not an issue at all anymore.&n; */
DECL|function|sys_setitimer
id|asmlinkage
r_int
id|sys_setitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
id|value
comma
r_struct
id|itimerval
op_star
id|ovalue
)paren
(brace
r_struct
id|itimerval
id|set_buffer
comma
id|get_buffer
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|value
comma
r_sizeof
(paren
op_star
id|value
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|set_buffer
comma
id|value
comma
r_sizeof
(paren
id|set_buffer
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|set_buffer
comma
l_int|0
comma
r_sizeof
(paren
id|set_buffer
)paren
)paren
suffix:semicolon
id|error
op_assign
id|do_setitimer
c_func
(paren
id|which
comma
op_amp
id|set_buffer
comma
id|ovalue
ques
c_cond
op_amp
id|get_buffer
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|ovalue
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ovalue
comma
op_amp
id|get_buffer
comma
r_sizeof
(paren
id|get_buffer
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
