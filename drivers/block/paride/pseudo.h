multiline_comment|/* &n;        pseudo.h    (c) 1997-8  Grant R. Guenther &lt;grant@torque.net&gt;&n;                                Under the terms of the GNU public license.&n;&n;&t;This is the &quot;pseudo-interrupt&quot; logic for parallel port drivers.&n;&n;        This module is #included into each driver.  It makes one&n;        function available:&n;&n;&t;&t;ps_set_intr( void (*continuation)(void),&n;&t;&t;&t;     int  (*ready)(void),&n;&t;&t;&t;     int timeout,&n;&t;&t;&t;     int nice )&n;&n;&t;Which will arrange for ready() to be evaluated frequently and&n;&t;when either it returns true, or timeout jiffies have passed,&n;&t;continuation() will be invoked.&n;&n;&t;If nice is true, the test will done approximately once a&n;&t;jiffy.  If nice is 0, the test will also be done whenever&n;&t;the scheduler runs (by adding it to a task queue).&n;&n;*/
multiline_comment|/* Changes:&n;&n;&t;1.01&t;1998.05.03&t;Switched from cli()/sti() to spinlocks&n;&n;*/
DECL|macro|PS_VERSION
mdefine_line|#define PS_VERSION&t;&quot;1.01&quot;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
r_static
r_void
id|ps_timer_int
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_static
r_void
id|ps_tq_int
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|variable|ps_use_tq
r_static
r_int
id|ps_use_tq
op_assign
l_int|1
suffix:semicolon
DECL|variable|ps_continuation
r_static
r_void
(paren
op_star
id|ps_continuation
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|ps_ready
r_static
r_int
(paren
op_star
id|ps_ready
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|ps_then
r_static
r_int
id|ps_then
suffix:semicolon
DECL|variable|ps_timeout
r_static
r_int
id|ps_timeout
suffix:semicolon
DECL|variable|ps_timer_active
r_static
r_int
id|ps_timer_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|ps_tq_active
r_static
r_int
id|ps_tq_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|ps_spinlock
r_static
id|spinlock_t
id|ps_spinlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|ps_timer
r_static
r_struct
id|timer_list
id|ps_timer
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|ps_timer_int
)brace
suffix:semicolon
DECL|variable|ps_tq
r_static
r_struct
id|tq_struct
id|ps_tq
op_assign
(brace
l_int|0
comma
l_int|0
comma
id|ps_tq_int
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|ps_set_intr
r_static
r_void
id|ps_set_intr
c_func
(paren
r_void
(paren
op_star
id|continuation
)paren
(paren
r_void
)paren
comma
r_int
(paren
op_star
id|ready
)paren
(paren
r_void
)paren
comma
r_int
id|timeout
comma
r_int
id|nice
)paren
(brace
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
id|ps_continuation
op_assign
id|continuation
suffix:semicolon
id|ps_ready
op_assign
id|ready
suffix:semicolon
id|ps_then
op_assign
id|jiffies
suffix:semicolon
id|ps_timeout
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
id|ps_use_tq
op_assign
op_logical_neg
id|nice
suffix:semicolon
r_if
c_cond
(paren
id|ps_use_tq
op_logical_and
op_logical_neg
id|ps_tq_active
)paren
(brace
macro_line|#ifdef HAVE_DISABLE_HLT
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ps_tq_active
op_assign
l_int|1
suffix:semicolon
id|queue_task
c_func
(paren
op_amp
id|ps_tq
comma
op_amp
id|tq_scheduler
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ps_timer_active
)paren
(brace
id|ps_timer_active
op_assign
l_int|1
suffix:semicolon
id|ps_timer.expires
op_assign
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ps_timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ps_tq_int
r_static
r_void
id|ps_tq_int
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_void
(paren
op_star
id|con
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
id|con
op_assign
id|ps_continuation
suffix:semicolon
macro_line|#ifdef HAVE_DISABLE_HLT
id|enable_hlt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ps_tq_active
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|con
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ps_ready
op_logical_or
id|ps_ready
c_func
(paren
)paren
op_logical_or
(paren
id|jiffies
op_ge
id|ps_timeout
)paren
)paren
(brace
id|ps_continuation
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
id|con
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef HAVE_DISABLE_HLT
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ps_tq_active
op_assign
l_int|1
suffix:semicolon
id|queue_task
c_func
(paren
op_amp
id|ps_tq
comma
op_amp
id|tq_scheduler
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ps_timer_int
r_static
r_void
id|ps_timer_int
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_void
(paren
op_star
id|con
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
id|con
op_assign
id|ps_continuation
suffix:semicolon
id|ps_timer_active
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|con
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ps_ready
op_logical_or
id|ps_ready
c_func
(paren
)paren
op_logical_or
(paren
id|jiffies
op_ge
id|ps_timeout
)paren
)paren
(brace
id|ps_continuation
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
id|con
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ps_timer_active
op_assign
l_int|1
suffix:semicolon
id|ps_timer.expires
op_assign
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ps_timer
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* end of pseudo.h */
eof
