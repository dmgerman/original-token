multiline_comment|/*&n; *  linux/kernel/chr_drv/pty.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; *&t;pty.c&n; *&n; * This module implements the pty functions&n; *&t;void mpty_write(struct tty_struct * queue);&n; *&t;void spty_write(struct tty_struct * queue);&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|pty_open
r_int
id|pty_open
c_func
(paren
r_int
r_int
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
id|tty
op_assign
id|tty_table
op_plus
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;link
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|tty-&gt;read_q-&gt;proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NDELAY
)paren
r_return
l_int|0
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
id|tty-&gt;link-&gt;count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|tty-&gt;link-&gt;count
op_logical_and
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|tty-&gt;link-&gt;read_q-&gt;proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;link-&gt;count
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pty_close
r_void
id|pty_close
c_func
(paren
r_int
r_int
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
id|tty
op_assign
id|tty_table
op_plus
id|dev
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|tty-&gt;read_q-&gt;proc_list
)paren
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
id|tty-&gt;link-&gt;count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;link-&gt;pgrp
OG
l_int|0
)paren
id|kill_pg
c_func
(paren
id|tty-&gt;link-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|pty_copy
r_static
r_inline
r_void
id|pty_copy
c_func
(paren
r_struct
id|tty_struct
op_star
id|from
comma
r_struct
id|tty_struct
op_star
id|to
)paren
(brace
r_int
id|c
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|from-&gt;stopped
op_logical_and
op_logical_neg
id|EMPTY
c_func
(paren
id|from-&gt;write_q
)paren
)paren
(brace
r_if
c_cond
(paren
id|FULL
c_func
(paren
id|to-&gt;read_q
)paren
)paren
(brace
r_if
c_cond
(paren
id|FULL
c_func
(paren
id|to-&gt;secondary
)paren
)paren
r_break
suffix:semicolon
id|TTY_READ_FLUSH
c_func
(paren
id|to
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|c
op_assign
id|GETCH
c_func
(paren
id|from-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
id|c
comma
id|to-&gt;read_q
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
r_break
suffix:semicolon
)brace
id|TTY_READ_FLUSH
c_func
(paren
id|to
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|from-&gt;write_q-&gt;proc_list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine gets called when tty_write has put something into&n; * the write_queue. It copies the input to the output-queue of it&squot;s&n; * slave.&n; */
DECL|function|mpty_write
r_void
id|mpty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;link
)paren
id|pty_copy
c_func
(paren
id|tty
comma
id|tty-&gt;link
)paren
suffix:semicolon
)brace
DECL|function|spty_write
r_void
id|spty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;link
)paren
id|pty_copy
c_func
(paren
id|tty
comma
id|tty-&gt;link
)paren
suffix:semicolon
)brace
eof
