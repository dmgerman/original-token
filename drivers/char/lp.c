multiline_comment|/*&n; * Copyright (C) 1992 by Jim Weigand and Linus Torvalds&n; * Copyright (C) 1992,1993 by Michael K. Johnson&n; * - Thanks much to Gunter Windau for pointing out to me where the error&n; *   checking ought to be.&n; * Copyright (C) 1993 by Nigel Gamble (added interrupt code)&n; * Copyright (C) 1994 by Alan Cox (Modularised it)&n; * LPCAREFUL, LPABORT, LPGETSTATUS added by Chris Metcalf, metcalf@lcs.mit.edu&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/lp.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* the BIOS manuals say there can be up to 4 lpt devices&n; * but I have not seen a board where the 4th address is listed&n; * if you have different hardware change the table below &n; * please let me know if you have different equipment&n; * if you have more than 3 printers, remember to increase LP_NO&n; */
DECL|variable|lp_table
r_struct
id|lp_struct
id|lp_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x3bc
comma
l_int|0
comma
l_int|0
comma
id|LP_INIT_CHAR
comma
id|LP_INIT_TIME
comma
id|LP_INIT_WAIT
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
comma
(brace
l_int|0x378
comma
l_int|0
comma
l_int|0
comma
id|LP_INIT_CHAR
comma
id|LP_INIT_TIME
comma
id|LP_INIT_WAIT
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
comma
(brace
l_int|0x278
comma
l_int|0
comma
l_int|0
comma
id|LP_INIT_CHAR
comma
id|LP_INIT_TIME
comma
id|LP_INIT_WAIT
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
DECL|macro|LP_NO
mdefine_line|#define LP_NO 3
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
multiline_comment|/* Test if printer is ready (and optionally has no error conditions) */
DECL|macro|LP_READY
mdefine_line|#define LP_READY(minor, status) &bslash;&n;  ((LP_F(minor) &amp; LP_CAREFUL) ? _LP_CAREFUL_READY(status) : (status &amp; LP_PBUSY))
DECL|macro|LP_CAREFUL_READY
mdefine_line|#define LP_CAREFUL_READY(minor, status) &bslash;&n;  ((LP_F(minor) &amp; LP_CAREFUL) ? _LP_CAREFUL_READY(status) : 1)
DECL|macro|_LP_CAREFUL_READY
mdefine_line|#define _LP_CAREFUL_READY(status) &bslash;&n;   (status &amp; (LP_PBUSY|LP_POUTPA|LP_PSELECD|LP_PERRORP)) == &bslash;&n;      (LP_PBUSY|LP_PSELECD|LP_PERRORP) 
multiline_comment|/* &n; * All my debugging code assumes that you debug with only one printer at&n; * a time. RWWH&n; */
DECL|macro|LP_DEBUG
macro_line|#undef LP_DEBUG
DECL|function|lp_reset
r_static
r_int
id|lp_reset
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
id|testvalue
suffix:semicolon
r_int
r_char
id|command
suffix:semicolon
id|command
op_assign
id|LP_PSELECP
op_or
id|LP_PINITP
suffix:semicolon
multiline_comment|/* reset value */
id|outb_p
c_func
(paren
l_int|0
comma
id|LP_C
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|testvalue
op_assign
l_int|0
suffix:semicolon
id|testvalue
OL
id|LP_DELAY
suffix:semicolon
id|testvalue
op_increment
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|LP_C
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
r_return
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
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
id|minor
)paren
(brace
r_int
id|status
op_assign
l_int|0
comma
id|wait
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
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
op_logical_neg
id|LP_READY
c_func
(paren
id|minor
comma
id|status
)paren
op_logical_and
id|count
OL
id|LP_CHAR
c_func
(paren
id|minor
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
id|LP_CHAR
c_func
(paren
id|minor
)paren
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
id|outb_p
c_func
(paren
id|lpchar
comma
id|LP_B
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
multiline_comment|/* must wait before taking strobe high, and after taking strobe&n;&t;   low, according spec.  Some printers need it, others don&squot;t. */
r_while
c_loop
(paren
id|wait
op_ne
id|LP_WAIT
c_func
(paren
id|minor
)paren
)paren
(brace
id|wait
op_increment
suffix:semicolon
)brace
multiline_comment|/* control port takes strobe high */
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
op_or
id|LP_PSTROBE
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|wait
)paren
(brace
id|wait
op_decrement
suffix:semicolon
)brace
multiline_comment|/* take strobe low */
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|lp_char_interrupt
r_static
r_int
id|lp_char_interrupt
c_func
(paren
r_char
id|lpchar
comma
r_int
id|minor
)paren
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
)paren
op_amp
id|LP_PACK
)paren
op_logical_or
(paren
id|status
op_amp
id|LP_PBUSY
)paren
op_logical_or
op_logical_neg
(paren
(paren
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
)paren
op_amp
id|LP_PACK
)paren
op_logical_or
(paren
id|status
op_amp
id|LP_PBUSY
)paren
op_logical_or
op_logical_neg
(paren
(paren
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
)paren
op_amp
id|LP_PACK
)paren
op_logical_or
(paren
id|status
op_amp
id|LP_PBUSY
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|LP_CAREFUL_READY
c_func
(paren
id|minor
comma
id|status
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|outb_p
c_func
(paren
id|lpchar
comma
id|LP_B
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
multiline_comment|/* must wait before taking strobe high, and after taking strobe&n;&t;&t;   low, according spec.  Some printers need it, others don&squot;t. */
r_while
c_loop
(paren
id|wait
op_ne
id|LP_WAIT
c_func
(paren
id|minor
)paren
)paren
(brace
id|wait
op_increment
suffix:semicolon
)brace
multiline_comment|/* control port takes strobe high */
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
op_or
id|LP_PSTROBE
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|wait
)paren
(brace
id|wait
op_decrement
suffix:semicolon
)brace
multiline_comment|/* take strobe low */
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
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
DECL|function|lp_interrupt
r_static
r_void
id|lp_interrupt
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|lp_struct
op_star
id|lp
op_assign
op_amp
id|lp_table
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|lp_struct
op_star
id|lp_end
op_assign
op_amp
id|lp_table
(braket
id|LP_NO
)braket
suffix:semicolon
r_while
c_loop
(paren
id|irq
op_ne
id|lp-&gt;irq
)paren
(brace
r_if
c_cond
(paren
op_increment
id|lp
op_ge
id|lp_end
)paren
r_return
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|lp-&gt;lp_wait_q
)paren
suffix:semicolon
)brace
DECL|function|lp_write_interrupt
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
r_char
op_star
id|buf
comma
r_int
id|count
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
r_int
id|copy_size
suffix:semicolon
r_int
r_int
id|total_bytes_written
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|bytes_written
suffix:semicolon
r_struct
id|lp_struct
op_star
id|lp
op_assign
op_amp
id|lp_table
(braket
id|minor
)braket
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_do
(brace
id|bytes_written
op_assign
l_int|0
suffix:semicolon
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
id|lp-&gt;lp_buffer
comma
id|buf
comma
id|copy_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|copy_size
)paren
(brace
r_if
c_cond
(paren
id|lp_char_interrupt
c_func
(paren
id|lp-&gt;lp_buffer
(braket
id|bytes_written
)braket
comma
id|minor
)paren
)paren
(brace
op_decrement
id|copy_size
suffix:semicolon
op_increment
id|bytes_written
suffix:semicolon
)brace
r_else
(brace
r_int
id|rc
op_assign
id|total_bytes_written
op_plus
id|bytes_written
suffix:semicolon
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|LP_POUTPA
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d out of paper&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
r_return
id|rc
ques
c_cond
id|rc
suffix:colon
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|LP_PSELECD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d off-line&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
r_return
id|rc
ques
c_cond
id|rc
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|LP_PERRORP
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lp%d printer error&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
r_return
id|rc
ques
c_cond
id|rc
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
op_or
id|LP_PINTEN
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|status
op_amp
id|LP_PACK
)paren
op_logical_or
(paren
id|status
op_amp
id|LP_PBUSY
)paren
)paren
op_logical_and
id|LP_CAREFUL_READY
c_func
(paren
id|minor
comma
id|status
)paren
)paren
(brace
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|LP_TIMEOUT_INTERRUPT
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|lp-&gt;lp_wait_q
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
)paren
comma
(paren
id|LP_C
c_func
(paren
id|minor
)paren
)paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
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
id|total_bytes_written
op_plus
id|bytes_written
)paren
r_return
id|total_bytes_written
op_plus
id|bytes_written
suffix:semicolon
r_else
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
)brace
id|total_bytes_written
op_add_assign
id|bytes_written
suffix:semicolon
id|buf
op_add_assign
id|bytes_written
suffix:semicolon
id|count
op_sub_assign
id|bytes_written
suffix:semicolon
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
DECL|function|lp_write_polled
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|retval
suffix:semicolon
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
r_char
id|c
comma
op_star
id|temp
op_assign
id|buf
suffix:semicolon
macro_line|#ifdef LP_DEBUG
r_if
c_cond
(paren
id|jiffies
op_minus
id|lp_last_call
OG
id|LP_TIME
c_func
(paren
id|minor
)paren
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
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|temp
)paren
suffix:semicolon
id|retval
op_assign
id|lp_char_polled
c_func
(paren
id|c
comma
id|minor
)paren
suffix:semicolon
multiline_comment|/* only update counting vars if character was printed */
r_if
c_cond
(paren
id|retval
)paren
(brace
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
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
multiline_comment|/* if printer timed out */
r_int
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|LP_POUTPA
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d out of paper&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
(brace
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
)brace
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
(paren
id|status
op_amp
id|LP_PSELECD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d off-line&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
(brace
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
)brace
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
op_logical_neg
(paren
id|status
op_amp
id|LP_PERRORP
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lp%d reported invalid error status (on fire, eh?)&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORT
)paren
(brace
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
)brace
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
id|LP_TIME
c_func
(paren
id|minor
)paren
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
id|LP_TIME
c_func
(paren
id|minor
)paren
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
id|LP_IRQ
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
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
id|ret
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|LP_NO
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_EXIST
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_BUSY
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* If ABORTOPEN is set and the printer is offline or out of paper,&n;&t;   we may still want to open it to perform ioctl()s.  Therefore we&n;&t;   have commandeered O_NONBLOCK, even though it is being used in&n;&t;   a non-standard manner.  This is strictly a Linux hack, and&n;&t;   should most likely only ever be used by the tunelp application. */
r_if
c_cond
(paren
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_ABORTOPEN
)paren
op_logical_and
op_logical_neg
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
(brace
r_int
id|status
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|LP_POUTPA
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d out of paper&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|LP_PSELECD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;lp%d off-line&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|LP_PERRORP
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lp%d printer error&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|irq
op_assign
id|LP_IRQ
c_func
(paren
id|minor
)paren
)paren
)paren
(brace
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|LP_BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|lp_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;printer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree_s
c_func
(paren
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
comma
id|LP_BUFFER_SIZE
)paren
suffix:semicolon
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lp%d unable to use interrupt %d, error %d&bslash;n&quot;
comma
id|minor
comma
id|irq
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_BUSY
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif&t;
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
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
op_assign
id|LP_IRQ
c_func
(paren
id|minor
)paren
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
comma
id|LP_BUFFER_SIZE
)paren
suffix:semicolon
id|lp_table
(braket
id|minor
)braket
dot
id|lp_buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_BUSY
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif&t;&t;
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
id|LP_NO
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_EXIST
)paren
op_eq
l_int|0
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
id|LP_TIME
c_func
(paren
id|minor
)paren
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPCHAR
suffix:colon
id|LP_CHAR
c_func
(paren
id|minor
)paren
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
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_ABORT
suffix:semicolon
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_ABORT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPABORTOPEN
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_ABORTOPEN
suffix:semicolon
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_ABORTOPEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPCAREFUL
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_CAREFUL
suffix:semicolon
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_CAREFUL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPWAIT
suffix:colon
id|LP_WAIT
c_func
(paren
id|minor
)paren
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPSETIRQ
suffix:colon
(brace
r_int
id|oldirq
suffix:semicolon
r_int
id|newirq
op_assign
id|arg
suffix:semicolon
r_struct
id|lp_struct
op_star
id|lp
op_assign
op_amp
id|lp_table
(braket
id|minor
)braket
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
id|oldirq
op_assign
id|LP_IRQ
c_func
(paren
id|minor
)paren
suffix:semicolon
multiline_comment|/* Allocate buffer now if we are going to need it */
r_if
c_cond
(paren
op_logical_neg
id|oldirq
op_logical_and
id|newirq
)paren
(brace
id|lp-&gt;lp_buffer
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|LP_BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;lp_buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldirq
)paren
(brace
id|free_irq
c_func
(paren
id|oldirq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newirq
)paren
(brace
multiline_comment|/* Install new irq */
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|request_irq
c_func
(paren
id|newirq
comma
id|lp_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;printer&quot;
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|oldirq
)paren
(brace
multiline_comment|/* restore old irq */
id|request_irq
c_func
(paren
id|oldirq
comma
id|lp_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;printer&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We don&squot;t need the buffer */
id|kfree_s
c_func
(paren
id|lp-&gt;lp_buffer
comma
id|LP_BUFFER_SIZE
)paren
suffix:semicolon
id|lp-&gt;lp_buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|oldirq
op_logical_and
op_logical_neg
id|newirq
)paren
(brace
multiline_comment|/* We don&squot;t need the buffer */
id|kfree_s
c_func
(paren
id|lp-&gt;lp_buffer
comma
id|LP_BUFFER_SIZE
)paren
suffix:semicolon
id|lp-&gt;lp_buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|LP_IRQ
c_func
(paren
id|minor
)paren
op_assign
id|newirq
suffix:semicolon
id|lp_reset
c_func
(paren
id|minor
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|LPGETIRQ
suffix:colon
id|retval
op_assign
id|LP_IRQ
c_func
(paren
id|minor
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LPGETSTATUS
suffix:colon
id|retval
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
multiline_comment|/* in range 0..255 */
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
macro_line|#ifndef MODULE
DECL|function|lp_init
r_int
id|lp_init
c_func
(paren
r_int
id|kmem_start
)paren
(brace
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|testvalue
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
l_int|0
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
id|kmem_start
suffix:semicolon
)brace
multiline_comment|/* take on all known port values */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|LP_NO
suffix:semicolon
id|offset
op_increment
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
comma
l_int|3
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* write to port &amp; read back to check */
id|outb_p
c_func
(paren
id|LP_DUMMY
comma
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|testvalue
op_assign
l_int|0
suffix:semicolon
id|testvalue
OL
id|LP_DELAY
suffix:semicolon
id|testvalue
op_increment
)paren
suffix:semicolon
id|testvalue
op_assign
id|inb_p
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|testvalue
op_eq
id|LP_DUMMY
)paren
(brace
id|LP_F
c_func
(paren
id|offset
)paren
op_or_assign
id|LP_EXIST
suffix:semicolon
id|lp_reset
c_func
(paren
id|offset
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lp%d at 0x%04x, &quot;
comma
id|offset
comma
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
comma
l_int|3
comma
l_string|&quot;lp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_IRQ
c_func
(paren
id|offset
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;using IRQ%d&bslash;n&quot;
comma
id|LP_IRQ
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;using polling driver&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;lp_init: no lp devices found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
macro_line|#else
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
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
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|testvalue
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
l_int|0
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
id|EIO
suffix:semicolon
)brace
multiline_comment|/* take on all known port values */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|LP_NO
suffix:semicolon
id|offset
op_increment
)paren
(brace
multiline_comment|/* write to port &amp; read back to check */
id|outb_p
c_func
(paren
id|LP_DUMMY
comma
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|testvalue
op_assign
l_int|0
suffix:semicolon
id|testvalue
OL
id|LP_DELAY
suffix:semicolon
id|testvalue
op_increment
)paren
suffix:semicolon
id|testvalue
op_assign
id|inb_p
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|testvalue
op_eq
id|LP_DUMMY
)paren
(brace
id|LP_F
c_func
(paren
id|offset
)paren
op_or_assign
id|LP_EXIST
suffix:semicolon
id|lp_reset
c_func
(paren
id|offset
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lp%d at 0x%04x, &quot;
comma
id|offset
comma
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
comma
l_int|3
comma
l_string|&quot;lp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LP_IRQ
c_func
(paren
id|offset
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;using IRQ%d&bslash;n&quot;
comma
id|LP_IRQ
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;using polling driver&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;lp_init: no lp devices found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
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
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lp: busy - remove delayed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|unregister_chrdev
c_func
(paren
id|LP_MAJOR
comma
l_string|&quot;lp&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|LP_NO
suffix:semicolon
id|offset
op_increment
)paren
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|offset
)paren
op_logical_and
id|LP_EXIST
)paren
(brace
id|release_region
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
comma
l_int|3
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
