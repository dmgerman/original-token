multiline_comment|/*&n; *  linux/kernel/tty_io.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;tty_io.c&squot; gives an orthogonal feeling to tty&squot;s, be they consoles&n; * or rs-channels. It also implements echoing, cooked mode etc.&n; *&n; * Kill-line thanks to John T Kohl, who also corrected VMIN = VTIME = 0.&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;fcntl.h&gt;
DECL|macro|ALRMMASK
mdefine_line|#define ALRMMASK (1&lt;&lt;(SIGALRM-1))
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;sys/kd.h&gt;
macro_line|#include &quot;vt_kern.h&quot;
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
macro_line|#endif
DECL|macro|QUEUES
mdefine_line|#define QUEUES&t;(3*(NR_CONSOLES+NR_SERIALS+2*NR_PTYS))
DECL|variable|tty_queues
r_static
r_struct
id|tty_queue
op_star
id|tty_queues
suffix:semicolon
DECL|variable|tty_table
r_struct
id|tty_struct
id|tty_table
(braket
l_int|256
)braket
suffix:semicolon
DECL|macro|con_queues
mdefine_line|#define con_queues tty_queues
DECL|macro|rs_queues
mdefine_line|#define rs_queues ((3*NR_CONSOLES) + tty_queues)
DECL|macro|mpty_queues
mdefine_line|#define mpty_queues ((3*(NR_CONSOLES+NR_SERIALS)) + tty_queues)
DECL|macro|spty_queues
mdefine_line|#define spty_queues ((3*(NR_CONSOLES+NR_SERIALS+NR_PTYS)) + tty_queues)
DECL|macro|con_table
mdefine_line|#define con_table tty_table
DECL|macro|rs_table
mdefine_line|#define rs_table (64+tty_table)
DECL|macro|mpty_table
mdefine_line|#define mpty_table (128+tty_table)
DECL|macro|spty_table
mdefine_line|#define spty_table (192+tty_table)
multiline_comment|/*&n; * fg_console is the current virtual console,&n; * redirect is the pseudo-tty that console output&n; * is redirected to if asked by TIOCCONS.&n; */
DECL|variable|fg_console
r_int
id|fg_console
op_assign
l_int|0
suffix:semicolon
DECL|variable|redirect
r_struct
id|tty_struct
op_star
id|redirect
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * these are the tables used by the machine code handlers.&n; * you can implement virtual consoles.&n; */
DECL|variable|table_list
r_struct
id|tty_queue
op_star
id|table_list
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|change_console
r_void
id|change_console
c_func
(paren
r_int
r_int
id|new_console
)paren
(brace
r_if
c_cond
(paren
id|vt_cons
(braket
id|fg_console
)braket
dot
id|vt_mode
op_eq
id|KD_GRAPHICS
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|new_console
op_eq
id|fg_console
op_logical_or
id|new_console
op_ge
id|NR_CONSOLES
)paren
r_return
suffix:semicolon
id|table_list
(braket
l_int|0
)braket
op_assign
id|con_queues
op_plus
l_int|0
op_plus
id|new_console
op_star
l_int|3
suffix:semicolon
id|table_list
(braket
l_int|1
)braket
op_assign
id|con_queues
op_plus
l_int|1
op_plus
id|new_console
op_star
l_int|3
suffix:semicolon
id|update_screen
c_func
(paren
id|new_console
)paren
suffix:semicolon
)brace
DECL|function|sleep_if_empty
r_static
r_void
id|sleep_if_empty
c_func
(paren
r_struct
id|tty_queue
op_star
id|queue
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
op_logical_and
id|EMPTY
c_func
(paren
id|queue
)paren
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|wait_for_keypress
r_void
id|wait_for_keypress
c_func
(paren
r_void
)paren
(brace
id|sleep_if_empty
c_func
(paren
id|tty_table
(braket
id|fg_console
)braket
dot
id|secondary
)paren
suffix:semicolon
)brace
DECL|function|copy_to_cooked
r_void
id|copy_to_cooked
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tty
op_logical_and
id|tty-&gt;write
op_logical_and
id|tty-&gt;read_q
op_logical_and
id|tty-&gt;write_q
op_logical_and
id|tty-&gt;secondary
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;copy_to_cooked: missing queues&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|EMPTY
c_func
(paren
id|tty-&gt;read_q
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|FULL
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;secondary-&gt;proc_list
)paren
r_if
c_cond
(paren
id|tty-&gt;secondary-&gt;proc_list
op_ne
id|current
)paren
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c
op_assign
id|GETCH
c_func
(paren
id|tty-&gt;read_q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|I_STRP
c_func
(paren
id|tty
)paren
)paren
id|c
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|13
)paren
(brace
r_if
c_cond
(paren
id|I_CRNL
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
l_int|10
suffix:semicolon
r_else
r_if
c_cond
(paren
id|I_NOCR
c_func
(paren
id|tty
)paren
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_int|10
op_logical_and
id|I_NLCR
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
l_int|13
suffix:semicolon
r_if
c_cond
(paren
id|I_UCLC
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
id|tolower
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|L_CANON
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|KILL_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|KILL_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
multiline_comment|/* deal with killing the input line */
r_while
c_loop
(paren
op_logical_neg
(paren
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
op_logical_or
(paren
id|c
op_assign
id|LAST
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
op_eq
l_int|10
op_logical_or
(paren
(paren
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|EOF_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|L_ECHO
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
OL
l_int|32
)paren
(brace
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_char|&squot; &squot;
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_char|&squot; &squot;
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
id|DEC
c_func
(paren
id|tty-&gt;secondary-&gt;head
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ERASE_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|ERASE_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
op_logical_or
(paren
id|c
op_assign
id|LAST
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
op_eq
l_int|10
op_logical_or
(paren
(paren
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|EOF_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|L_ECHO
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
OL
l_int|32
)paren
(brace
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_char|&squot; &squot;
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|32
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|8
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
id|DEC
c_func
(paren
id|tty-&gt;secondary-&gt;head
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|I_IXON
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|STOP_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|STOP_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
id|tty-&gt;stopped
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|START_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|START_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
id|tty-&gt;stopped
op_assign
l_int|0
suffix:semicolon
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|L_ISIG
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|INTR_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|INTR_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGINT
comma
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|QUIT_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|QUIT_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGQUIT
comma
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|SUSPEND_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
)paren
op_logical_and
(paren
id|c
op_eq
id|SUSPEND_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_orphaned_pgrp
c_func
(paren
id|tty-&gt;pgrp
)paren
)paren
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGTSTP
comma
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|c
op_eq
l_int|10
op_logical_or
(paren
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
op_logical_and
id|c
op_eq
id|EOF_CHAR
c_func
(paren
id|tty
)paren
)paren
)paren
id|tty-&gt;secondary-&gt;data
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|L_ECHO
c_func
(paren
id|tty
)paren
op_logical_or
(paren
id|L_CANON
c_func
(paren
id|tty
)paren
op_logical_and
id|L_ECHONL
c_func
(paren
id|tty
)paren
)paren
)paren
op_logical_and
(paren
id|c
op_eq
l_int|10
)paren
)paren
(brace
id|PUTCH
c_func
(paren
l_int|10
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|13
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|L_ECHO
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
OL
l_int|32
op_logical_and
id|L_ECHOCTL
c_func
(paren
id|tty
)paren
)paren
(brace
id|PUTCH
c_func
(paren
l_char|&squot;^&squot;
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
id|PUTCH
c_func
(paren
id|c
op_plus
l_int|64
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
r_else
id|PUTCH
c_func
(paren
id|c
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
id|PUTCH
c_func
(paren
id|c
comma
id|tty-&gt;secondary
)paren
suffix:semicolon
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|tty-&gt;secondary-&gt;proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LEFT
c_func
(paren
id|tty-&gt;write_q
)paren
OG
id|TTY_BUF_SIZE
op_div
l_int|2
)paren
id|wake_up
c_func
(paren
op_amp
id|tty-&gt;write_q-&gt;proc_list
)paren
suffix:semicolon
)brace
DECL|function|is_ignored
r_int
id|is_ignored
c_func
(paren
r_int
id|sig
)paren
(brace
r_return
(paren
(paren
id|current-&gt;blocked
op_amp
(paren
l_int|1
op_lshift
(paren
id|sig
op_minus
l_int|1
)paren
)paren
)paren
op_logical_or
(paren
id|current-&gt;sigaction
(braket
id|sig
op_minus
l_int|1
)braket
dot
id|sa_handler
op_eq
id|SIG_IGN
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when we need to send a SIGTTIN or SIGTTOU to our process&n; * group&n; * &n; * We only request that a system call be restarted if there was if the &n; * default signal handler is being used.  The reason for this is that if&n; * a job is catching SIGTTIN or SIGTTOU, the signal handler may not want &n; * the system call to be restarted blindly.  If there is no way to reset the&n; * terminal pgrp back to the current pgrp (perhaps because the controlling&n; * tty has been released on logout), we don&squot;t want to be in an infinite loop&n; * while restarting the system call, and have it always generate a SIGTTIN&n; * or SIGTTOU.  The default signal handler will cause the process to stop&n; * thus avoiding the infinite loop problem.  Presumably the job-control&n; * cognizant parent will fix things up before continuging its child process.&n; */
DECL|function|tty_signal
r_int
id|tty_signal
c_func
(paren
r_int
id|sig
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
(paren
r_void
)paren
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|sig
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;sigaction
(braket
id|sig
op_minus
l_int|1
)braket
dot
id|sa_handler
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* We _will_ be interrupted :-) */
r_else
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
multiline_comment|/* We _will_ be interrupted :-) */
multiline_comment|/* (but restart after we continue) */
)brace
DECL|function|read_chan
r_static
r_int
id|read_chan
c_func
(paren
r_int
r_int
id|channel
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
id|nr
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
op_assign
l_int|NULL
suffix:semicolon
r_int
id|c
suffix:semicolon
r_char
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_int
id|minimum
comma
id|time
suffix:semicolon
r_if
c_cond
(paren
id|channel
OG
l_int|255
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|tty
op_assign
id|TTY_TABLE
c_func
(paren
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tty-&gt;read_q
op_logical_and
id|tty-&gt;secondary
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tty-&gt;pgrp
OG
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;tty
op_eq
id|channel
)paren
op_logical_and
(paren
id|tty-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
)paren
r_if
c_cond
(paren
id|is_ignored
c_func
(paren
id|SIGTTIN
)paren
op_logical_or
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
r_else
r_return
id|tty_signal
c_func
(paren
id|SIGTTIN
comma
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel
op_amp
l_int|0x80
)paren
id|other_tty
op_assign
id|tty_table
op_plus
(paren
id|channel
op_xor
l_int|0x40
)paren
suffix:semicolon
id|time
op_assign
l_int|10L
op_star
id|tty-&gt;termios.c_cc
(braket
id|VTIME
)braket
suffix:semicolon
id|minimum
op_assign
id|tty-&gt;termios.c_cc
(braket
id|VMIN
)braket
suffix:semicolon
r_if
c_cond
(paren
id|L_CANON
c_func
(paren
id|tty
)paren
)paren
(brace
id|minimum
op_assign
id|nr
suffix:semicolon
id|current-&gt;timeout
op_assign
l_int|0xffffffff
suffix:semicolon
id|time
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|minimum
)paren
id|current-&gt;timeout
op_assign
l_int|0xffffffff
suffix:semicolon
r_else
(brace
id|minimum
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|time
)paren
id|current-&gt;timeout
op_assign
id|time
op_plus
id|jiffies
suffix:semicolon
id|time
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
id|time
op_assign
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|minimum
OG
id|nr
)paren
id|minimum
op_assign
id|nr
suffix:semicolon
id|TTY_READ_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|other_tty
op_logical_and
id|other_tty-&gt;write
)paren
id|TTY_WRITE_FLUSH
c_func
(paren
id|other_tty
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
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
op_logical_or
(paren
id|L_CANON
c_func
(paren
id|tty
)paren
op_logical_and
op_logical_neg
id|FULL
c_func
(paren
id|tty-&gt;read_q
)paren
op_logical_and
op_logical_neg
id|tty-&gt;secondary-&gt;data
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;timeout
)paren
r_break
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
r_if
c_cond
(paren
id|IS_A_PTY_SLAVE
c_func
(paren
id|channel
)paren
op_logical_and
id|C_HUP
c_func
(paren
id|other_tty
)paren
)paren
r_break
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|tty-&gt;secondary-&gt;proc_list
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|TTY_READ_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|c
op_assign
id|GETCH
c_func
(paren
id|tty-&gt;secondary
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
op_logical_and
id|c
op_eq
id|EOF_CHAR
c_func
(paren
id|tty
)paren
)paren
op_logical_or
id|c
op_eq
l_int|10
)paren
id|tty-&gt;secondary-&gt;data
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_ne
id|__DISABLED_CHAR
op_logical_and
id|c
op_eq
id|EOF_CHAR
c_func
(paren
id|tty
)paren
)paren
op_logical_and
id|L_CANON
c_func
(paren
id|tty
)paren
)paren
r_break
suffix:semicolon
r_else
(brace
id|put_fs_byte
c_func
(paren
id|c
comma
id|b
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|nr
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_int|10
op_logical_and
id|L_CANON
c_func
(paren
id|tty
)paren
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nr
OG
l_int|0
op_logical_and
op_logical_neg
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
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
id|L_CANON
c_func
(paren
id|tty
)paren
op_logical_or
id|b
op_minus
id|buf
op_ge
id|minimum
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|time
)paren
id|current-&gt;timeout
op_assign
id|time
op_plus
id|jiffies
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|TTY_READ_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|other_tty
op_logical_and
id|other_tty-&gt;write
)paren
id|TTY_WRITE_FLUSH
c_func
(paren
id|other_tty
)paren
suffix:semicolon
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|b
op_minus
id|buf
)paren
r_return
id|b
op_minus
id|buf
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
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_chan
r_static
r_int
id|write_chan
c_func
(paren
r_int
r_int
id|channel
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
id|nr
)paren
(brace
r_static
id|cr_flag
op_assign
l_int|0
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_char
id|c
comma
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|channel
OG
l_int|255
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|tty
op_assign
id|TTY_TABLE
c_func
(paren
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|L_TOSTOP
c_func
(paren
id|tty
)paren
op_logical_and
(paren
id|tty-&gt;pgrp
OG
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;tty
op_eq
id|channel
)paren
op_logical_and
(paren
id|tty-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_orphaned_pgrp
c_func
(paren
id|tty-&gt;pgrp
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_ignored
c_func
(paren
id|SIGTTOU
)paren
)paren
r_return
id|tty_signal
c_func
(paren
id|SIGTTOU
comma
id|tty
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
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
id|nr
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|redirect
op_logical_and
id|tty
op_eq
id|TTY_TABLE
c_func
(paren
l_int|0
)paren
)paren
id|tty
op_assign
id|redirect
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tty-&gt;write_q
op_logical_and
id|tty-&gt;write
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_while
c_loop
(paren
id|nr
OG
l_int|0
)paren
(brace
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
r_if
c_cond
(paren
id|FULL
c_func
(paren
id|tty-&gt;write_q
)paren
)paren
(brace
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
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
id|FULL
c_func
(paren
id|tty-&gt;write_q
)paren
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|tty-&gt;write_q-&gt;proc_list
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
r_while
c_loop
(paren
id|nr
OG
l_int|0
op_logical_and
op_logical_neg
id|FULL
c_func
(paren
id|tty-&gt;write_q
)paren
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|O_POST
c_func
(paren
id|tty
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
op_logical_and
id|O_CRNL
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|O_NLRET
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|cr_flag
op_logical_and
id|O_NLCR
c_func
(paren
id|tty
)paren
)paren
(brace
id|cr_flag
op_assign
l_int|1
suffix:semicolon
id|PUTCH
c_func
(paren
l_int|13
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|O_LCUC
c_func
(paren
id|tty
)paren
)paren
id|c
op_assign
id|toupper
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
id|b
op_increment
suffix:semicolon
id|nr
op_decrement
suffix:semicolon
id|cr_flag
op_assign
l_int|0
suffix:semicolon
id|PUTCH
c_func
(paren
id|c
comma
id|tty-&gt;write_q
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
OG
l_int|0
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|TTY_WRITE_FLUSH
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_minus
id|buf
)paren
r_return
id|b
op_minus
id|buf
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tty_read
r_static
r_int
id|tty_read
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
id|i
suffix:semicolon
id|i
op_assign
id|read_chan
c_func
(paren
id|current-&gt;tty
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ttyx_read
r_static
r_int
id|ttyx_read
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
id|i
suffix:semicolon
id|i
op_assign
id|read_chan
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|tty_write
r_static
r_int
id|tty_write
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
id|i
suffix:semicolon
id|i
op_assign
id|write_chan
c_func
(paren
id|current-&gt;tty
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ttyx_write
r_static
r_int
id|ttyx_write
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
id|i
suffix:semicolon
id|i
op_assign
id|write_chan
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|tty_lseek
r_static
r_int
id|tty_lseek
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
id|orig
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
multiline_comment|/*&n; * tty_open and tty_release keep up the tty count that contains the&n; * number of opens done on a tty. We cannot use the inode-count, as&n; * different inodes might point to the same tty.&n; *&n; * Open-counting is needed for pty masters, as well as for keeping&n; * track of serial lines: DTR is dropped when the last close happens.&n; */
DECL|function|tty_open
r_static
r_int
id|tty_open
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
id|filp
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|dev
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_eq
l_int|5
)paren
id|dev
op_assign
id|current-&gt;tty
suffix:semicolon
r_else
id|dev
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
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
id|IS_A_PTY_MASTER
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;count
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|tty-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_NOCTTY
)paren
op_logical_and
id|current-&gt;leader
op_logical_and
id|current-&gt;tty
OL
l_int|0
op_logical_and
id|tty-&gt;session
op_eq
l_int|0
)paren
(brace
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
)brace
r_if
c_cond
(paren
id|IS_A_SERIAL
c_func
(paren
id|dev
)paren
)paren
id|serial_open
c_func
(paren
id|dev
op_minus
l_int|64
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tty_release
r_static
r_void
id|tty_release
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
id|filp
)paren
(brace
r_int
id|dev
suffix:semicolon
r_int
r_int
id|port
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
comma
op_star
id|slave
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_eq
l_int|5
)paren
id|dev
op_assign
id|current-&gt;tty
suffix:semicolon
r_else
id|dev
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
)paren
r_return
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
op_decrement
id|tty-&gt;count
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_eq
id|redirect
)paren
id|redirect
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|port
op_assign
id|tty-&gt;read_q-&gt;data
)paren
id|outb
c_func
(paren
l_int|0x0c
comma
id|port
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* reset DTR, RTS, */
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
id|slave
op_assign
id|tty_table
op_plus
id|PTY_OTHER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;pgrp
OG
l_int|0
)paren
id|kill_pg
c_func
(paren
id|slave-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|variable|tty_fops
r_static
r_struct
id|file_operations
id|tty_fops
op_assign
(brace
id|tty_lseek
comma
id|tty_read
comma
id|tty_write
comma
l_int|NULL
comma
multiline_comment|/* tty_readdir */
l_int|NULL
comma
multiline_comment|/* tty_select */
id|tty_ioctl
comma
id|tty_open
comma
id|tty_release
)brace
suffix:semicolon
DECL|variable|ttyx_fops
r_static
r_struct
id|file_operations
id|ttyx_fops
op_assign
(brace
id|tty_lseek
comma
id|ttyx_read
comma
id|ttyx_write
comma
l_int|NULL
comma
multiline_comment|/* ttyx_readdir */
l_int|NULL
comma
multiline_comment|/* ttyx_select */
id|tty_ioctl
comma
multiline_comment|/* ttyx_ioctl */
id|tty_open
comma
id|tty_release
)brace
suffix:semicolon
DECL|function|tty_init
r_int
id|tty_init
c_func
(paren
r_int
id|kmem_start
)paren
(brace
r_int
id|i
suffix:semicolon
id|tty_queues
op_assign
(paren
r_struct
id|tty_queue
op_star
)paren
id|kmem_start
suffix:semicolon
id|kmem_start
op_add_assign
id|QUEUES
op_star
(paren
r_sizeof
(paren
r_struct
id|tty_queue
)paren
)paren
suffix:semicolon
id|table_list
(braket
l_int|0
)braket
op_assign
id|con_queues
op_plus
l_int|0
suffix:semicolon
id|table_list
(braket
l_int|1
)braket
op_assign
id|con_queues
op_plus
l_int|1
suffix:semicolon
id|chrdev_fops
(braket
l_int|4
)braket
op_assign
op_amp
id|ttyx_fops
suffix:semicolon
id|chrdev_fops
(braket
l_int|5
)braket
op_assign
op_amp
id|tty_fops
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
id|QUEUES
suffix:semicolon
id|i
op_increment
)paren
id|tty_queues
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|0
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x3f8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|1
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x3f8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|3
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x2f8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|4
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x2f8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|6
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x3e8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|7
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x3e8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|9
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x2e8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
id|rs_queues
(braket
l_int|10
)braket
op_assign
(paren
r_struct
id|tty_queue
)paren
(brace
l_int|0x2e8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;&quot;
)brace
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tty_table
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_struct
)paren
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|INIT_C_CC
)brace
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
)brace
id|kmem_start
op_assign
id|con_init
c_func
(paren
id|kmem_start
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
id|NR_CONSOLES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|con_table
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_struct
)paren
(brace
(brace
id|ICRNL
comma
multiline_comment|/* change incoming CR to NL */
id|OPOST
op_or
id|ONLCR
comma
multiline_comment|/* change outgoing NL to CRNL */
id|B38400
op_or
id|CS8
comma
id|IXON
op_or
id|ISIG
op_or
id|ICANON
op_or
id|ECHO
op_or
id|ECHOCTL
op_or
id|ECHOKE
comma
l_int|0
comma
multiline_comment|/* console termio */
id|INIT_C_CC
)brace
comma
op_minus
l_int|1
comma
multiline_comment|/* initial pgrp */
l_int|0
comma
multiline_comment|/* initial session */
l_int|0
comma
multiline_comment|/* initial stopped */
l_int|0
comma
multiline_comment|/* initial busy */
l_int|0
comma
multiline_comment|/* initial count */
(brace
id|video_num_lines
comma
id|video_num_columns
comma
l_int|0
comma
l_int|0
)brace
comma
id|con_write
comma
id|con_queues
op_plus
l_int|0
op_plus
id|i
op_star
l_int|3
comma
id|con_queues
op_plus
l_int|1
op_plus
id|i
op_star
l_int|3
comma
id|con_queues
op_plus
l_int|2
op_plus
id|i
op_star
l_int|3
)brace
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_SERIALS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rs_table
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_struct
)paren
(brace
(brace
l_int|0
comma
multiline_comment|/* no translation */
l_int|0
comma
multiline_comment|/* no translation */
id|B2400
op_or
id|CS8
comma
l_int|0
comma
l_int|0
comma
id|INIT_C_CC
)brace
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|25
comma
l_int|80
comma
l_int|0
comma
l_int|0
)brace
comma
id|rs_write
comma
id|rs_queues
op_plus
l_int|0
op_plus
id|i
op_star
l_int|3
comma
id|rs_queues
op_plus
l_int|1
op_plus
id|i
op_star
l_int|3
comma
id|rs_queues
op_plus
l_int|2
op_plus
id|i
op_star
l_int|3
)brace
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_PTYS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mpty_table
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_struct
)paren
(brace
(brace
l_int|0
comma
multiline_comment|/* no translation */
l_int|0
comma
multiline_comment|/* no translation */
id|B9600
op_or
id|CS8
comma
l_int|0
comma
l_int|0
comma
id|INIT_C_CC
)brace
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|25
comma
l_int|80
comma
l_int|0
comma
l_int|0
)brace
comma
id|mpty_write
comma
id|mpty_queues
op_plus
l_int|0
op_plus
id|i
op_star
l_int|3
comma
id|mpty_queues
op_plus
l_int|1
op_plus
id|i
op_star
l_int|3
comma
id|mpty_queues
op_plus
l_int|2
op_plus
id|i
op_star
l_int|3
)brace
suffix:semicolon
id|spty_table
(braket
id|i
)braket
op_assign
(paren
r_struct
id|tty_struct
)paren
(brace
(brace
l_int|0
comma
multiline_comment|/* no translation */
l_int|0
comma
multiline_comment|/* no translation */
id|B9600
op_or
id|CS8
comma
id|IXON
op_or
id|ISIG
op_or
id|ICANON
comma
l_int|0
comma
id|INIT_C_CC
)brace
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|25
comma
l_int|80
comma
l_int|0
comma
l_int|0
)brace
comma
id|spty_write
comma
id|spty_queues
op_plus
l_int|0
op_plus
id|i
op_star
l_int|3
comma
id|spty_queues
op_plus
l_int|1
op_plus
id|i
op_star
l_int|3
comma
id|spty_queues
op_plus
l_int|2
op_plus
id|i
op_star
l_int|3
)brace
suffix:semicolon
)brace
id|kmem_start
op_assign
id|rs_init
c_func
(paren
id|kmem_start
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d virtual consoles&bslash;n&bslash;r&quot;
comma
id|NR_CONSOLES
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pty&squot;s&bslash;n&bslash;r&quot;
comma
id|NR_PTYS
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
eof
