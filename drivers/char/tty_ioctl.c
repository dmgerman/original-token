multiline_comment|/*&n; *  linux/kernel/drivers/char/tty_ioctl.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; * Modified by Fred N. van Kempen, 01/29/93, to add line disciplines&n; * which can be dynamically activated and de-activated by the line&n; * discipline handling modules (like SLIP).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|DEBUG
macro_line|#undef&t;DEBUG
macro_line|#ifdef DEBUG
DECL|macro|PRINTK
macro_line|# define&t;PRINTK(x)&t;printk (x)
macro_line|#else
DECL|macro|PRINTK
macro_line|# define&t;PRINTK(x)&t;/**/
macro_line|#endif
r_extern
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
r_extern
r_int
id|do_screendump
c_func
(paren
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|kill_pg
c_func
(paren
r_int
id|pgrp
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SELECTION
r_extern
r_int
id|set_selection
c_func
(paren
r_const
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|paste_selection
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SELECTION */
r_static
r_int
id|tty_set_ldisc
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|ldisc
)paren
suffix:semicolon
DECL|function|flush_input
r_void
id|flush_input
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|tty-&gt;read_q.head
op_assign
id|tty-&gt;read_q.tail
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;secondary.head
op_assign
id|tty-&gt;secondary.tail
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;canon_head
op_assign
id|tty-&gt;canon_data
op_assign
id|tty-&gt;erasing
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tty-&gt;readq_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;readq_flags
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tty-&gt;secondary_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;secondary_flags
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
op_logical_neg
id|tty-&gt;link
)paren
r_return
suffix:semicolon
multiline_comment|/* No cli() since ptys don&squot;t use interrupts. */
id|tty-&gt;link-&gt;write_q.head
op_assign
id|tty-&gt;link-&gt;write_q.tail
op_assign
l_int|0
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;write_q.proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;link-&gt;packet
)paren
(brace
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_FLUSHREAD
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;secondary.proc_list
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_output
r_void
id|flush_output
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|tty-&gt;write_q.head
op_assign
id|tty-&gt;write_q.tail
op_assign
l_int|0
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_q.proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;link
)paren
r_return
suffix:semicolon
multiline_comment|/* No cli() since ptys don&squot;t use interrupts. */
id|tty-&gt;link-&gt;read_q.head
op_assign
id|tty-&gt;link-&gt;read_q.tail
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;link-&gt;secondary.head
op_assign
id|tty-&gt;link-&gt;secondary.tail
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;link-&gt;canon_head
op_assign
id|tty-&gt;link-&gt;canon_data
op_assign
id|tty-&gt;link-&gt;erasing
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tty-&gt;link-&gt;readq_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;readq_flags
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tty-&gt;link-&gt;secondary_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;secondary_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;link-&gt;packet
)paren
(brace
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_FLUSHWRITE
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;secondary.proc_list
)paren
suffix:semicolon
)brace
)brace
DECL|function|wait_until_sent
r_void
id|wait_until_sent
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
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
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EMPTY
c_func
(paren
op_amp
id|tty-&gt;write_q
)paren
)paren
r_return
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|tty-&gt;write_q.proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* make us low-priority */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_break
suffix:semicolon
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EMPTY
c_func
(paren
op_amp
id|tty-&gt;write_q
)paren
)paren
r_break
suffix:semicolon
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
id|tty-&gt;write_q.proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
DECL|function|do_get_ps_info
r_static
r_int
id|do_get_ps_info
c_func
(paren
r_int
id|arg
)paren
(brace
r_struct
id|tstruct
(brace
r_int
id|flag
suffix:semicolon
r_int
id|present
(braket
id|NR_TASKS
)braket
suffix:semicolon
r_struct
id|task_struct
id|tasks
(braket
id|NR_TASKS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|tstruct
op_star
id|ts
op_assign
(paren
r_struct
id|tstruct
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_char
op_star
id|c
comma
op_star
id|d
suffix:semicolon
r_int
id|i
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|tstruct
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|FIRST_TASK
suffix:semicolon
id|p
op_le
op_amp
id|LAST_TASK
suffix:semicolon
id|p
op_increment
comma
id|n
op_increment
)paren
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|c
op_assign
(paren
r_char
op_star
)paren
(paren
op_star
id|p
)paren
suffix:semicolon
id|d
op_assign
(paren
r_char
op_star
)paren
(paren
id|ts-&gt;tasks
op_plus
id|n
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
r_struct
id|task_struct
)paren
suffix:semicolon
id|i
op_increment
)paren
id|put_fs_byte
c_func
(paren
op_star
id|c
op_increment
comma
id|d
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|1
comma
(paren
r_int
r_int
op_star
)paren
(paren
id|ts-&gt;present
op_plus
id|n
)paren
)paren
suffix:semicolon
)brace
r_else
id|put_fs_long
c_func
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
(paren
id|ts-&gt;present
op_plus
id|n
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unset_locked_termios
r_static
r_void
id|unset_locked_termios
c_func
(paren
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termios
op_star
id|old
comma
r_struct
id|termios
op_star
id|locked
)paren
(brace
r_int
id|i
suffix:semicolon
DECL|macro|NOSET_MASK
mdefine_line|#define NOSET_MASK(x,y,z) (x = ((x) &amp; ~(z)) | ((y) &amp; (z)))
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning?!? termios_locked is NULL.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_iflag
comma
id|old-&gt;c_iflag
comma
id|locked-&gt;c_iflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_oflag
comma
id|old-&gt;c_oflag
comma
id|locked-&gt;c_oflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_cflag
comma
id|old-&gt;c_cflag
comma
id|locked-&gt;c_cflag
)paren
suffix:semicolon
id|NOSET_MASK
c_func
(paren
id|termios-&gt;c_lflag
comma
id|old-&gt;c_lflag
comma
id|locked-&gt;c_lflag
)paren
suffix:semicolon
id|termios-&gt;c_line
op_assign
id|locked-&gt;c_line
ques
c_cond
id|old-&gt;c_line
suffix:colon
id|termios-&gt;c_line
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NCCS
suffix:semicolon
id|i
op_increment
)paren
id|termios-&gt;c_cc
(braket
id|i
)braket
op_assign
id|locked-&gt;c_cc
(braket
id|i
)braket
ques
c_cond
id|old-&gt;c_cc
(braket
id|i
)braket
suffix:colon
id|termios-&gt;c_cc
(braket
id|i
)braket
suffix:semicolon
)brace
DECL|function|check_change
r_int
id|check_change
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|channel
)paren
(brace
multiline_comment|/* If we try to set the state of terminal and we&squot;re not in the&n;&t;   foreground, send a SIGTTOU.  If the signal is blocked or&n;&t;   ignored, go ahead and perform the operation.  POSIX 7.2) */
r_if
c_cond
(paren
id|current-&gt;tty
op_ne
id|channel
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;pgrp
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;check_change: tty-&gt;pgrp &lt;= 0!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;pgrp
op_eq
id|tty-&gt;pgrp
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_ignored
c_func
(paren
id|SIGTTOU
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
(paren
r_void
)paren
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|SIGTTOU
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
DECL|function|set_termios_2
r_static
r_int
id|set_termios_2
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|termios
)paren
(brace
r_struct
id|termios
id|old_termios
op_assign
op_star
id|tty-&gt;termios
suffix:semicolon
r_int
id|canon_change
suffix:semicolon
id|canon_change
op_assign
(paren
id|old_termios.c_lflag
op_xor
id|termios-&gt;c_lflag
)paren
op_amp
id|ICANON
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|tty-&gt;termios
op_assign
op_star
id|termios
suffix:semicolon
r_if
c_cond
(paren
id|canon_change
)paren
(brace
id|memset
c_func
(paren
op_amp
id|tty-&gt;secondary_flags
comma
l_int|0
comma
r_sizeof
id|tty-&gt;secondary_flags
)paren
suffix:semicolon
id|tty-&gt;canon_head
op_assign
id|tty-&gt;secondary.tail
suffix:semicolon
id|tty-&gt;canon_data
op_assign
l_int|0
suffix:semicolon
id|tty-&gt;erasing
op_assign
l_int|0
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|canon_change
op_logical_and
op_logical_neg
(paren
id|tty-&gt;termios-&gt;c_lflag
op_amp
id|ICANON
)paren
op_logical_and
op_logical_neg
id|EMPTY
c_func
(paren
op_amp
id|tty-&gt;secondary
)paren
)paren
multiline_comment|/* Get characters left over from canonical mode. */
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;secondary.proc_list
)paren
suffix:semicolon
multiline_comment|/* see if packet mode change of state */
multiline_comment|/* The BSD man page pty.4 says that TIOCPKT_NOSTOP should be sent&n;&t;   if the new state differs from ^S/^Q, but that&squot;s a bad way of&n;&t;   detecting a new flow control scheme.  Instead, a status byte&n;&t;   is only sent if IXON has changed. */
r_if
c_cond
(paren
id|tty-&gt;link
op_logical_and
id|tty-&gt;link-&gt;packet
op_logical_and
(paren
id|old_termios.c_iflag
op_xor
id|tty-&gt;termios-&gt;c_iflag
)paren
op_amp
id|IXON
)paren
(brace
id|tty-&gt;ctrl_status
op_and_assign
op_complement
(paren
id|TIOCPKT_DOSTOP
op_or
id|TIOCPKT_NOSTOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;termios-&gt;c_iflag
op_amp
id|IXON
)paren
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_DOSTOP
suffix:semicolon
r_else
id|tty-&gt;ctrl_status
op_or_assign
id|TIOCPKT_NOSTOP
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;secondary.proc_list
)paren
suffix:semicolon
)brace
id|unset_locked_termios
c_func
(paren
id|tty-&gt;termios
comma
op_amp
id|old_termios
comma
id|termios_locked
(braket
id|tty-&gt;line
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;set_termios
)paren
(paren
op_star
id|tty-&gt;set_termios
)paren
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_termios
r_static
r_int
id|set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|termios
comma
r_int
id|channel
)paren
(brace
r_struct
id|termios
id|tmp_termios
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|tmp_termios
comma
id|termios
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_return
id|set_termios_2
c_func
(paren
id|tty
comma
op_amp
id|tmp_termios
)paren
suffix:semicolon
)brace
DECL|function|get_termio
r_static
r_int
id|get_termio
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termio
op_star
id|termio
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|termio
id|tmp_termio
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|termio
comma
r_sizeof
(paren
r_struct
id|termio
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|tmp_termio.c_iflag
op_assign
id|tty-&gt;termios-&gt;c_iflag
suffix:semicolon
id|tmp_termio.c_oflag
op_assign
id|tty-&gt;termios-&gt;c_oflag
suffix:semicolon
id|tmp_termio.c_cflag
op_assign
id|tty-&gt;termios-&gt;c_cflag
suffix:semicolon
id|tmp_termio.c_lflag
op_assign
id|tty-&gt;termios-&gt;c_lflag
suffix:semicolon
id|tmp_termio.c_line
op_assign
id|tty-&gt;termios-&gt;c_line
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NCC
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp_termio.c_cc
(braket
id|i
)braket
op_assign
id|tty-&gt;termios-&gt;c_cc
(braket
id|i
)braket
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|termio
comma
op_amp
id|tmp_termio
comma
r_sizeof
(paren
r_struct
id|termio
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_termio
r_static
r_int
id|set_termio
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termio
op_star
id|termio
comma
r_int
id|channel
)paren
(brace
r_struct
id|termio
id|tmp_termio
suffix:semicolon
r_struct
id|termios
id|tmp_termios
suffix:semicolon
id|tmp_termios
op_assign
op_star
id|tty-&gt;termios
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|tmp_termio
comma
id|termio
comma
r_sizeof
(paren
r_struct
id|termio
)paren
)paren
suffix:semicolon
DECL|macro|SET_LOW_BITS
mdefine_line|#define SET_LOW_BITS(x,y)&t;((x) = (0xffff0000 &amp; (x)) | (y))
id|SET_LOW_BITS
c_func
(paren
id|tmp_termios.c_iflag
comma
id|tmp_termio.c_iflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|tmp_termios.c_oflag
comma
id|tmp_termio.c_oflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|tmp_termios.c_cflag
comma
id|tmp_termio.c_cflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|tmp_termios.c_lflag
comma
id|tmp_termio.c_lflag
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp_termios.c_cc
comma
op_amp
id|tmp_termio.c_cc
comma
id|NCC
)paren
suffix:semicolon
DECL|macro|SET_LOW_BITS
macro_line|#undef SET_LOW_BITS
r_return
id|set_termios_2
c_func
(paren
id|tty
comma
op_amp
id|tmp_termios
)paren
suffix:semicolon
)brace
DECL|function|set_window_size
r_static
r_int
id|set_window_size
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|winsize
op_star
id|ws
)paren
(brace
r_struct
id|winsize
id|tmp_ws
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|tmp_ws
comma
id|ws
comma
r_sizeof
(paren
r_struct
id|winsize
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|tmp_ws
comma
op_amp
id|tty-&gt;winsize
comma
r_sizeof
(paren
r_struct
id|winsize
)paren
)paren
op_logical_and
id|tty-&gt;pgrp
OG
l_int|0
)paren
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGWINCH
comma
l_int|1
)paren
suffix:semicolon
id|tty-&gt;winsize
op_assign
id|tmp_ws
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set the discipline of a tty line. */
DECL|function|tty_set_ldisc
r_static
r_int
id|tty_set_ldisc
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|ldisc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ldisc
OL
id|N_TTY
)paren
op_logical_or
(paren
id|ldisc
op_ge
id|NR_LDISCS
)paren
op_logical_or
op_logical_neg
(paren
id|ldiscs
(braket
id|ldisc
)braket
dot
id|flags
op_amp
id|LDISC_FLAG_DEFINED
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;disc
op_eq
id|ldisc
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* We are already in the desired discipline */
multiline_comment|/* Shutdown the current discipline. */
id|wait_until_sent
c_func
(paren
id|tty
)paren
suffix:semicolon
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|close
)paren
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|close
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/* Now set up the new line discipline. */
id|tty-&gt;disc
op_assign
id|ldisc
suffix:semicolon
id|tty-&gt;termios-&gt;c_line
op_assign
id|ldisc
suffix:semicolon
r_if
c_cond
(paren
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|open
)paren
r_return
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|open
c_func
(paren
id|tty
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inq_canon
r_static
r_int
r_int
id|inq_canon
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|nr
comma
id|head
comma
id|tail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;canon_data
)paren
r_return
l_int|0
suffix:semicolon
id|head
op_assign
id|tty-&gt;canon_head
suffix:semicolon
id|tail
op_assign
id|tty-&gt;secondary.tail
suffix:semicolon
id|nr
op_assign
(paren
id|head
op_minus
id|tail
)paren
op_amp
(paren
id|TTY_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Skip EOF-chars.. */
r_while
c_loop
(paren
id|head
op_ne
id|tail
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|tail
comma
op_amp
id|tty-&gt;secondary_flags
)paren
op_logical_and
id|tty-&gt;secondary.buf
(braket
id|tail
)braket
op_eq
id|__DISABLED_CHAR
)paren
id|nr
op_decrement
suffix:semicolon
id|INC
c_func
(paren
id|tail
)paren
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|tty_ioctl
r_int
id|tty_ioctl
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
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_struct
id|tty_struct
op_star
id|other_tty
suffix:semicolon
r_struct
id|tty_struct
op_star
id|termios_tty
suffix:semicolon
id|pid_t
id|pgrp
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_int
id|termios_dev
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|file-&gt;f_rdev
)paren
op_ne
id|TTY_MAJOR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tty_ioctl: tty pseudo-major != TTY_MAJOR&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_rdev
)paren
suffix:semicolon
id|tty
op_assign
id|TTY_TABLE
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|IS_A_PTY
c_func
(paren
id|dev
)paren
)paren
id|other_tty
op_assign
id|tty_table
(braket
id|PTY_OTHER
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_else
id|other_tty
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|IS_A_PTY_MASTER
c_func
(paren
id|dev
)paren
)paren
(brace
id|termios_tty
op_assign
id|other_tty
suffix:semicolon
id|termios_dev
op_assign
id|PTY_OTHER
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|termios_tty
op_assign
id|tty
suffix:semicolon
id|termios_dev
op_assign
id|dev
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TCGETS
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|memcpy_tofs
c_func
(paren
(paren
r_struct
id|termios
op_star
)paren
id|arg
comma
id|termios_tty-&gt;termios
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TCSETSF
suffix:colon
r_case
id|TCSETSW
suffix:colon
r_case
id|TCSETS
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|termios_tty
comma
id|termios_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|TCSETSF
op_logical_or
id|cmd
op_eq
id|TCSETSW
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|TCSETSF
)paren
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
id|wait_until_sent
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_return
id|set_termios
c_func
(paren
id|termios_tty
comma
(paren
r_struct
id|termios
op_star
)paren
id|arg
comma
id|termios_dev
)paren
suffix:semicolon
r_case
id|TCGETA
suffix:colon
r_return
id|get_termio
c_func
(paren
id|termios_tty
comma
(paren
r_struct
id|termio
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|TCSETAF
suffix:colon
r_case
id|TCSETAW
suffix:colon
r_case
id|TCSETA
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|termios_tty
comma
id|termios_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|TCSETAF
op_logical_or
id|cmd
op_eq
id|TCSETAW
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|TCSETAF
)paren
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
id|wait_until_sent
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_return
id|set_termio
c_func
(paren
id|termios_tty
comma
(paren
r_struct
id|termio
op_star
)paren
id|arg
comma
id|termios_dev
)paren
suffix:semicolon
r_case
id|TCXONC
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|tty
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|arg
)paren
(brace
r_case
id|TCOOFF
suffix:colon
id|stop_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCOON
suffix:colon
id|start_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCIOFF
suffix:colon
r_if
c_cond
(paren
id|STOP_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
id|put_tty_queue
c_func
(paren
id|STOP_CHAR
c_func
(paren
id|tty
)paren
comma
op_amp
id|tty-&gt;write_q
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCION
suffix:colon
r_if
c_cond
(paren
id|START_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
id|put_tty_queue
c_func
(paren
id|START_CHAR
c_func
(paren
id|tty
)paren
comma
op_amp
id|tty-&gt;write_q
)paren
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
r_case
id|TCFLSH
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|tty
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|arg
)paren
(brace
r_case
id|TCIFLUSH
suffix:colon
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCIOFLUSH
suffix:colon
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|TCOFLUSH
suffix:colon
id|flush_output
c_func
(paren
id|tty
)paren
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
r_case
id|TIOCEXCL
suffix:colon
id|set_bit
c_func
(paren
id|TTY_EXCLUSIVE
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCNXCL
suffix:colon
id|clear_bit
c_func
(paren
id|TTY_EXCLUSIVE
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSCTTY
suffix:colon
r_if
c_cond
(paren
id|current-&gt;leader
op_logical_and
(paren
id|current-&gt;session
op_eq
id|tty-&gt;session
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The process must be a session leader and&n;&t;&t;&t; * not have a controlling tty already.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;leader
op_logical_or
(paren
id|current-&gt;tty
op_ge
l_int|0
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;session
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * This tty is already the controlling&n;&t;&t;&t;&t; * tty for another session group!&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|arg
op_eq
l_int|1
)paren
op_logical_and
id|suser
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Steal it away&n;&t;&t;&t;&t;&t; */
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
r_if
c_cond
(paren
id|p-&gt;tty
op_eq
id|dev
)paren
id|p-&gt;tty
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|current-&gt;tty
op_assign
id|dev
suffix:semicolon
id|tty-&gt;session
op_assign
id|current-&gt;session
suffix:semicolon
id|tty-&gt;pgrp
op_assign
id|current-&gt;pgrp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCGPGRP
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|pid_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|put_fs_long
c_func
(paren
id|termios_tty-&gt;pgrp
comma
(paren
id|pid_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSPGRP
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|tty
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;tty
OL
l_int|0
)paren
op_logical_or
(paren
id|current-&gt;tty
op_ne
id|termios_dev
)paren
op_logical_or
(paren
id|termios_tty-&gt;session
op_ne
id|current-&gt;session
)paren
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
id|pgrp
op_assign
id|get_fs_long
c_func
(paren
(paren
id|pid_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgrp
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
id|session_of_pgrp
c_func
(paren
id|pgrp
)paren
op_ne
id|current-&gt;session
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|termios_tty-&gt;pgrp
op_assign
id|pgrp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCOUTQ
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|put_fs_long
c_func
(paren
id|CHARS
c_func
(paren
op_amp
id|tty-&gt;write_q
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCINQ
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|L_ICANON
c_func
(paren
id|tty
)paren
)paren
id|put_fs_long
c_func
(paren
id|inq_canon
c_func
(paren
id|tty
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_else
id|put_fs_long
c_func
(paren
id|CHARS
c_func
(paren
op_amp
id|tty-&gt;secondary
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSTI
suffix:colon
r_if
c_cond
(paren
(paren
id|current-&gt;tty
op_ne
id|dev
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|put_tty_queue
c_func
(paren
id|get_fs_byte
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
comma
op_amp
id|tty-&gt;read_q
)paren
suffix:semicolon
id|TTY_READ_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCGWINSZ
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|winsize
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|memcpy_tofs
c_func
(paren
(paren
r_struct
id|winsize
op_star
)paren
id|arg
comma
op_amp
id|tty-&gt;winsize
comma
r_sizeof
(paren
r_struct
id|winsize
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSWINSZ
suffix:colon
r_if
c_cond
(paren
id|IS_A_PTY_MASTER
c_func
(paren
id|dev
)paren
)paren
id|set_window_size
c_func
(paren
id|other_tty
comma
(paren
r_struct
id|winsize
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
id|set_window_size
c_func
(paren
id|tty
comma
(paren
r_struct
id|winsize
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|TIOCLINUX
suffix:colon
r_switch
c_cond
(paren
id|get_fs_byte
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|do_screendump
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
id|do_get_ps_info
c_func
(paren
id|arg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SELECTION
r_case
l_int|2
suffix:colon
r_return
id|set_selection
c_func
(paren
id|arg
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
id|paste_selection
c_func
(paren
id|tty
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SELECTION */
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|TIOCCONS
suffix:colon
r_if
c_cond
(paren
id|IS_A_CONSOLE
c_func
(paren
id|dev
)paren
)paren
(brace
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
id|redirect
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|redirect
)paren
r_return
op_minus
id|EBUSY
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
id|IS_A_PTY_MASTER
c_func
(paren
id|dev
)paren
)paren
id|redirect
op_assign
id|other_tty
suffix:semicolon
r_else
r_if
c_cond
(paren
id|IS_A_PTY_SLAVE
c_func
(paren
id|dev
)paren
)paren
id|redirect
op_assign
id|tty
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIONBIO
suffix:colon
id|arg
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|file-&gt;f_flags
op_or_assign
id|O_NONBLOCK
suffix:semicolon
r_else
id|file-&gt;f_flags
op_and_assign
op_complement
id|O_NONBLOCK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCNOTTY
suffix:colon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|file-&gt;f_rdev
)paren
op_ne
id|current-&gt;tty
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;leader
)paren
id|disassociate_ctty
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|current-&gt;tty
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCGETD
suffix:colon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tty-&gt;disc
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSETD
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|tty
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|arg
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
id|tty_set_ldisc
c_func
(paren
id|tty
comma
id|arg
)paren
suffix:semicolon
r_case
id|TIOCGLCKTRMIOS
suffix:colon
id|arg
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|memcpy_tofs
c_func
(paren
(paren
r_struct
id|termios
op_star
)paren
id|arg
comma
op_amp
id|termios_locked
(braket
id|termios_dev
)braket
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCSLCKTRMIOS
suffix:colon
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
id|arg
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|termios_locked
(braket
id|termios_dev
)braket
comma
(paren
r_struct
id|termios
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|termios
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCPKT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|IS_A_PTY_MASTER
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|get_fs_long
c_func
(paren
id|arg
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;packet
)paren
(brace
id|tty-&gt;packet
op_assign
l_int|1
suffix:semicolon
id|tty-&gt;ctrl_status
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
id|tty-&gt;packet
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TCSBRK
suffix:colon
r_case
id|TCSBRKP
suffix:colon
id|retval
op_assign
id|check_change
c_func
(paren
id|tty
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|wait_until_sent
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;ioctl
)paren
r_return
l_int|0
suffix:semicolon
id|tty
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|tty
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|tty-&gt;ioctl
)paren
(brace
id|retval
op_assign
(paren
id|tty-&gt;ioctl
)paren
(paren
id|tty
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
op_minus
id|EINVAL
)paren
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|ioctl
)paren
(brace
id|retval
op_assign
(paren
id|ldiscs
(braket
id|tty-&gt;disc
)braket
dot
id|ioctl
)paren
(paren
id|tty
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof
