multiline_comment|/*&n; * split in two parts for better support of different hardware&n; * by Joerg Dorchain (dorchain@mpi-sb.mpg.de)&n; *&n; * Amiga printer device by Michael Rausch (linux@uni-koblenz.de);&n; * Atari support added by Andreas Schwab (schwab@ls5.informatik.uni-dortmund.de);&n; * based upon work from&n; *&n; * Copyright (C) 1992 by Jim Weigand and Linus Torvalds&n; * Copyright (C) 1992,1993 by Michael K. Johnson&n; * - Thanks much to Gunter Windau for pointing out to me where the error&n; *   checking ought to be.&n; * Copyright (C) 1993 by Nigel Gamble (added interrupt code)&n; */
multiline_comment|/* 01/17/95: Matthias Welwarsky (dg8y@rs11.hrz.th-darmstadt.de)&n; * lp_write(): rewritten from scratch&n; * lp_interrupt(): fixed cli()/sti()-bug&n; * &n; * 95/05/28: Andreas Schwab (schwab@issan.informatik.uni-dortmund.de)&n; * lp_write() fixed to make it work again.&n; * 95/08/18: Andreas Schwab&n; * lp_write_interrupt: fix race condition&n; *&n; *  * CAUTION, please do check! *    &n; * &n; *  on 68000-based machines sti() must NEVER appear in interrupt driven&n; *  code. The 68k-CPU has a priority-based interrupt scheme. while an interrupt&n; *  with a certain priority is executed, all requests with lower or same&n; *  priority get locked out. executing the sti()-macro allows ANY interrupt&n; *  to be served. this really causes BIG trouble!&n; *  to protect an interrupt driven routine against being interrupted &n; *  (if absolutely needed!) one should use save_flags();cli()/restore_flags()!&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#ifdef CONFIG_MULTIFACE_III_LP
macro_line|#include &lt;linux/lp_mfc.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/lp_m68k.h&gt;
macro_line|#include &lt;linux/lp_intern.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; *  why bother around with the pio driver when the interrupt works;&n; *  so, for &quot;security&quot; reasons only, it&squot;s configurable here.&n; *  saves some bytes, at least ...&n; */
DECL|macro|FORCE_POLLING
mdefine_line|#define FORCE_POLLING&t; 0
DECL|macro|FORCE_INTERRUPT
mdefine_line|#define FORCE_INTERRUPT&t; 1
DECL|macro|PREFER_INTERRUPT
mdefine_line|#define PREFER_INTERRUPT 2
DECL|macro|WHICH_DRIVER
mdefine_line|#define WHICH_DRIVER&t;FORCE_INTERRUPT
DECL|macro|MAX_LP
mdefine_line|#define MAX_LP 3 /* the maximum number of devices */
DECL|variable|lp_table
r_struct
id|lp_struct
id|lp_table
(braket
id|MAX_LP
)braket
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|max_lp
r_static
r_int
id|max_lp
suffix:semicolon
multiline_comment|/* the real number of devices */
multiline_comment|/* &n; * All my debugging code assumes that you debug with only one printer at&n; * a time. RWWH&n; */
DECL|macro|LP_DEBUG
mdefine_line|#define LP_DEBUG 
DECL|macro|LP_DEBUG
macro_line|#undef LP_DEBUG 
macro_line|#if WHICH_DRIVER != FORCE_INTERRUPT
macro_line|#ifdef LP_DEBUG
DECL|variable|lp_max_count
r_static
r_int
id|lp_max_count
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
DECL|function|lp_char_polled
r_static
r_int
id|lp_char_polled
c_func
(paren
r_char
id|lpchar
comma
r_int
id|dev
)paren
(brace
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_busy
c_func
(paren
id|dev
)paren
op_logical_and
id|count
OL
id|lp_table
(braket
id|dev
)braket
dot
id|chars
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
id|lp_table
(braket
id|dev
)braket
dot
id|chars
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we timed out, and the character was /not/ printed */
)brace
macro_line|#ifdef LP_DEBUG
r_if
c_cond
(paren
id|count
OG
id|lp_max_count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lp success after %d counts.&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|lp_max_count
op_assign
id|count
suffix:semicolon
)brace
macro_line|#endif
id|lp_table
(braket
id|dev
)braket
dot
id|lp_out
c_func
(paren
id|lpchar
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef LP_DEBUG
DECL|variable|lp_total_chars
r_int
r_int
id|lp_total_chars
op_assign
l_int|0
suffix:semicolon
DECL|variable|lp_last_call
r_int
r_int
id|lp_last_call
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if WHICH_DRIVER != FORCE_POLLING
DECL|function|lp_char_interrupt
r_static
id|__inline__
r_int
id|lp_char_interrupt
c_func
(paren
r_char
id|lpchar
comma
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_busy
c_func
(paren
id|dev
)paren
)paren
(brace
id|lp_table
(braket
id|dev
)braket
dot
id|lp_out
c_func
(paren
id|lpchar
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lp_error
r_static
r_int
id|lp_error
suffix:semicolon
DECL|function|lp_interrupt
r_static
r_void
id|lp_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
comma
r_void
op_star
id|dummy
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
l_int|0
suffix:semicolon
id|dev
OL
id|max_lp
suffix:semicolon
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_my_interrupt
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
)paren
(brace
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_char_interrupt
c_func
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_buffer
(braket
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
)braket
comma
id|dev
)paren
)paren
(brace
op_decrement
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
suffix:semicolon
op_increment
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|lp_error
op_assign
l_int|1
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|lp_table
(braket
id|dev
)braket
dot
id|lp_wait_q
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|0
suffix:semicolon
id|lp_error
op_assign
l_int|0
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|lp_table
(braket
id|dev
)braket
dot
id|lp_wait_q
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#if WHICH_DRIVER == FORCE_INTERRUPT
DECL|function|lp_write
r_static
r_int
id|lp_write
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
id|count
)paren
macro_line|#else
r_static
r_int
id|lp_write_interrupt
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
id|count
)paren
macro_line|#endif
(brace
r_int
r_int
id|total_bytes_written
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_do
(brace
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable lp_interrupt()   */
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* init buffer read-pointer */
id|lp_error
op_assign
l_int|0
suffix:semicolon
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
op_assign
(paren
id|count
op_le
id|LP_BUFFER_SIZE
ques
c_cond
id|count
suffix:colon
id|LP_BUFFER_SIZE
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_buffer
comma
id|buf
comma
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* no interrupts now */
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* enable lp_interrupt() */
r_if
c_cond
(paren
id|lp_char_interrupt
c_func
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_buffer
(braket
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
)braket
comma
id|dev
)paren
)paren
(brace
op_increment
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
suffix:semicolon
op_decrement
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
suffix:semicolon
id|lp_error
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* something went wrong   */
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable lp_interrupt() */
id|lp_error
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* printer caused error   */
)brace
r_if
c_cond
(paren
id|lp_error
)paren
(brace
multiline_comment|/* something blocked printing, so we don&squot;t want to sleep too long,&n;&t;     in case we have to rekick the interrupt */
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_POLLED
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_INTERRUPT
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|lp_table
(braket
id|dev
)braket
dot
id|lp_wait_q
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* we&squot;re up again and running. we first disable lp_interrupt(), then&n;&t; check what happened meanwhile */
id|lp_table
(braket
id|dev
)braket
dot
id|do_print
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|total_bytes_written
op_plus
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
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
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
r_else
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp_error
)paren
(brace
multiline_comment|/* an error has occurred, maybe in lp_interrupt().&n;&t;   figure out the type of error, exit on request or if nothing has &n;&t;   been printed at all. */
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_has_pout
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: paper-out&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_online
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: off-line&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_busy
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: on fire&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_ABORT
)paren
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* check if our buffer was completely printed, if not, most likely&n;&t; an unsolved error blocks the printer. As we can`t do anything&n;&t; against, we start all over again. Else we set the read-pointer&n;&t; of the buffer and count the printed characters */
r_if
c_cond
(paren
op_logical_neg
id|lp_table
(braket
id|dev
)braket
dot
id|copy_size
)paren
(brace
id|total_bytes_written
op_add_assign
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
suffix:semicolon
id|buf
op_add_assign
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
suffix:semicolon
id|count
op_sub_assign
id|lp_table
(braket
id|dev
)braket
dot
id|bytes_written
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
suffix:semicolon
r_return
id|total_bytes_written
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if WHICH_DRIVER != FORCE_INTERRUPT
macro_line|#if WHICH_DRIVER == FORCE_POLLING
DECL|function|lp_write
r_static
r_int
id|lp_write
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
id|count
)paren
macro_line|#else
r_static
r_int
id|lp_write_polled
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
id|count
)paren
macro_line|#endif
(brace
r_char
op_star
id|temp
op_assign
id|buf
suffix:semicolon
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
macro_line|#ifdef LP_DEBUG
r_if
c_cond
(paren
id|jiffies
op_minus
id|lp_last_call
OG
id|lp_table
(braket
id|dev
)braket
dot
id|time
)paren
(brace
id|lp_total_chars
op_assign
l_int|0
suffix:semicolon
id|lp_max_count
op_assign
l_int|1
suffix:semicolon
)brace
id|lp_last_call
op_assign
id|jiffies
suffix:semicolon
macro_line|#endif
id|temp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|lp_char_polled
c_func
(paren
id|get_user
c_func
(paren
id|temp
)paren
comma
id|dev
)paren
)paren
(brace
multiline_comment|/* only update counting vars if character was printed */
id|count
op_decrement
suffix:semicolon
id|temp
op_increment
suffix:semicolon
macro_line|#ifdef LP_DEBUG
id|lp_total_chars
op_increment
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* if printer timed out */
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_has_pout
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: out of paper&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_ABORT
)paren
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|ENOSPC
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_POLLED
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_online
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: off-line&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_ABORT
)paren
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|EIO
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_POLLED
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* not offline or out of paper. on fire? */
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|lp_is_busy
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lp%d: on fire&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_ABORT
)paren
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_POLLED
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* check for signals before going to sleep */
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
r_if
c_cond
(paren
id|temp
op_ne
id|buf
)paren
r_return
id|temp
op_minus
id|buf
suffix:semicolon
r_else
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
macro_line|#ifdef LP_DEBUG
id|printk
c_func
(paren
l_string|&quot;lp sleeping at %d characters for %d jiffies&bslash;n&quot;
comma
id|lp_total_chars
comma
id|lp_table
(braket
id|dev
)braket
dot
id|time
)paren
suffix:semicolon
id|lp_total_chars
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|lp_table
(braket
id|dev
)braket
dot
id|time
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|temp
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|lp_irq
r_static
r_int
r_int
id|lp_irq
op_assign
l_int|0
suffix:semicolon
macro_line|#if WHICH_DRIVER == PREFER_INTERRUPT
DECL|function|lp_write
r_static
r_int
id|lp_write
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
id|count
)paren
(brace
r_if
c_cond
(paren
id|lp_irq
)paren
r_return
id|lp_write_interrupt
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_else
r_return
id|lp_write_polled
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|lp_lseek
r_static
r_int
id|lp_lseek
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
id|off_t
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
DECL|function|lp_open
r_static
r_int
id|lp_open
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
r_int
id|dev
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
id|dev
op_ge
id|max_lp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_EXIST
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_amp
id|LP_BUSY
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|lp_table
(braket
id|dev
)braket
dot
id|flags
op_or_assign
id|LP_BUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lp_release
r_static
r_void
id|lp_release
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
id|lp_table
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|flags
op_and_assign
op_complement
id|LP_BUSY
suffix:semicolon
)brace
DECL|function|lp_ioctl
r_static
r_int
id|lp_ioctl
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
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef LP_DEBUG
id|printk
c_func
(paren
l_string|&quot;lp%d ioctl, cmd: 0x%x, arg: 0x%x&bslash;n&quot;
comma
id|minor
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|minor
op_ge
id|max_lp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lp_table
(braket
id|minor
)braket
dot
id|flags
op_amp
id|LP_EXIST
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|LPTIME
suffix:colon
id|lp_table
(braket
id|minor
)braket
dot
id|time
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPCHAR
suffix:colon
id|lp_table
(braket
id|minor
)braket
dot
id|chars
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPABORT
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|lp_table
(braket
id|minor
)braket
dot
id|flags
op_or_assign
id|LP_ABORT
suffix:semicolon
r_else
id|lp_table
(braket
id|minor
)braket
dot
id|flags
op_and_assign
op_complement
id|LP_ABORT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPWAIT
suffix:colon
id|lp_table
(braket
id|minor
)braket
dot
id|wait
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPSETIRQ
suffix:colon
r_case
id|LPGETIRQ
suffix:colon
id|retval
op_assign
id|lp_irq
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|lp_fops
r_static
r_struct
id|file_operations
id|lp_fops
op_assign
(brace
id|lp_lseek
comma
l_int|NULL
comma
multiline_comment|/* lp_read */
id|lp_write
comma
l_int|NULL
comma
multiline_comment|/* lp_readdir */
l_int|NULL
comma
multiline_comment|/* lp_select */
id|lp_ioctl
comma
l_int|NULL
comma
multiline_comment|/* lp_mmap */
id|lp_open
comma
id|lp_release
)brace
suffix:semicolon
DECL|function|lp_init
r_int
id|lp_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;par&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|LP_MAJOR
comma
l_string|&quot;lp&quot;
comma
op_amp
id|lp_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for line printer&bslash;n&quot;
comma
id|LP_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
macro_line|#if WHICH_DRIVER == FORCE_POLLING
id|lp_irq
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp_init: lp using polling driver&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|AMI_PARALLEL
)paren
)paren
id|lp_irq
op_assign
id|add_isr
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|lp_interrupt
comma
l_int|0
comma
l_int|NULL
comma
l_string|&quot;printer&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|lp_irq
op_assign
id|add_isr
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|lp_interrupt
comma
id|IRQ_TYPE_SLOW
comma
l_int|NULL
comma
l_string|&quot;printer&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lp_irq
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp_init: lp using interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_else
macro_line|#if WHICH_DRIVER == PREFER_INTERRUPT
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp_init: lp using polling driver&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lp_init: can&squot;t get interrupt, and polling driver not configured&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
id|max_lp
op_assign
l_int|0
suffix:semicolon
id|max_lp
op_add_assign
id|lp_internal_init
c_func
(paren
id|lp_table
comma
id|max_lp
comma
id|MAX_LP
comma
id|WHICH_DRIVER
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MULTIFACE_III_LP
id|max_lp
op_add_assign
id|lp_mfc_init
c_func
(paren
id|lp_table
comma
id|max_lp
comma
id|MAX_LP
comma
id|WHICH_DRIVER
)paren
suffix:semicolon
macro_line|#if WHICH_DRIVER != FORCE_POLLING
id|add_isr
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|lp_interrupt
comma
l_int|0
comma
l_int|NULL
comma
l_string|&quot;Multiface III printer&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Currently we do not accept any lp-parameters, but that may change.&n; */
DECL|function|lp_setup
r_void
id|lp_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
)brace
eof