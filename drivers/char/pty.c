multiline_comment|/*&n; *  linux/drivers/char/pty.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *&t;pty.c&n; *&n; * This module exports the following pty function:&n; * &n; * &t;int  pty_open(struct tty_struct * tty, struct file * filp);&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|struct|pty_struct
r_struct
id|pty_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PTY_MAGIC
mdefine_line|#define PTY_MAGIC 0x5001
DECL|macro|PTY_BUF_SIZE
mdefine_line|#define PTY_BUF_SIZE PAGE_SIZE/2
multiline_comment|/*&n; * tmp_buf is used as a temporary buffer by pty_write.  We need to&n; * lock it in case the memcpy_fromfs blocks while swapping in a page,&n; * and some other program tries to do a pty write at the same time.&n; * Since the lock will only come under contention when the system is&n; * swapping and available memory is low, it makes sense to share one&n; * buffer across all the PTY&squot;s, since it significantly saves memory if&n; * large numbers of PTY&squot;s are open.&n; */
DECL|variable|tmp_buf
r_static
r_int
r_char
op_star
id|tmp_buf
suffix:semicolon
DECL|variable|tmp_buf_sem
r_static
r_struct
id|semaphore
id|tmp_buf_sem
op_assign
id|MUTEX
suffix:semicolon
DECL|variable|pty_driver
DECL|variable|pty_slave_driver
r_struct
id|tty_driver
id|pty_driver
comma
id|pty_slave_driver
suffix:semicolon
DECL|variable|pty_refcount
r_static
r_int
id|pty_refcount
suffix:semicolon
DECL|variable|pty_table
r_static
r_struct
id|tty_struct
op_star
id|pty_table
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|pty_termios
r_static
r_struct
id|termios
op_star
id|pty_termios
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|pty_termios_locked
r_static
r_struct
id|termios
op_star
id|pty_termios_locked
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|ttyp_table
r_static
r_struct
id|tty_struct
op_star
id|ttyp_table
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|ttyp_termios
r_static
r_struct
id|termios
op_star
id|ttyp_termios
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|ttyp_termios_locked
r_static
r_struct
id|termios
op_star
id|ttyp_termios_locked
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|variable|pty_state
r_static
r_struct
id|pty_struct
id|pty_state
(braket
id|NR_PTYS
)braket
suffix:semicolon
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
DECL|function|pty_close
r_static
r_void
id|pty_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver.subtype
op_eq
id|PTY_TYPE_MASTER
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;count
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;master pty_close: count = %d!!&bslash;n&quot;
comma
id|tty-&gt;count
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tty-&gt;count
OG
l_int|2
)paren
r_return
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;read_wait
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
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
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;read_wait
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;link-&gt;write_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver.subtype
op_eq
id|PTY_TYPE_MASTER
)paren
id|tty_hangup
c_func
(paren
id|tty-&gt;link
)paren
suffix:semicolon
r_else
(brace
id|start_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_SLAVE_CLOSED
comma
op_amp
id|tty-&gt;link-&gt;flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The unthrottle routine is called by the line discipline to signal&n; * that it can receive more characters.  For PTY&squot;s, the TTY_THROTTLED&n; * flag is always set, to force the line discipline to always call the&n; * unthrottle routine when there are fewer than TTY_THRESHOLD_UNTHROTTLE &n; * characters in the queue.  This is necessary since each time this&n; * happens, we need to wake up any sleeping processes that could be&n; * (1) trying to send data to the pty, or (2) waiting in wait_until_sent()&n; * for the pty buffer to be drained.&n; */
DECL|function|pty_unthrottle
r_static
r_void
id|pty_unthrottle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|o_tty
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o_tty
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o_tty-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
)paren
op_logical_and
id|o_tty-&gt;ldisc.write_wakeup
)paren
(paren
id|o_tty-&gt;ldisc.write_wakeup
)paren
(paren
id|o_tty
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|o_tty-&gt;write_wait
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|pty_write
r_static
r_int
id|pty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_int
id|c
op_assign
l_int|0
comma
id|n
comma
id|r
suffix:semicolon
r_char
op_star
id|temp_buffer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
id|tty-&gt;stopped
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
id|down
c_func
(paren
op_amp
id|tmp_buf_sem
)paren
suffix:semicolon
id|temp_buffer
op_assign
id|tmp_buf
op_plus
(paren
(paren
id|tty-&gt;driver.subtype
op_minus
l_int|1
)paren
op_star
id|PTY_BUF_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|n
op_assign
id|MIN
c_func
(paren
id|count
comma
id|PTY_BUF_SIZE
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|temp_buffer
comma
id|buf
comma
id|n
)paren
suffix:semicolon
id|r
op_assign
id|to-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|n
op_assign
id|MIN
c_func
(paren
id|n
comma
id|r
)paren
suffix:semicolon
id|to-&gt;ldisc
dot
id|receive_buf
c_func
(paren
id|to
comma
id|temp_buffer
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|c
op_add_assign
id|n
suffix:semicolon
id|count
op_sub_assign
id|n
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|tmp_buf_sem
)paren
suffix:semicolon
)brace
r_else
(brace
id|c
op_assign
id|MIN
c_func
(paren
id|count
comma
id|to-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|to
)paren
)paren
suffix:semicolon
id|to-&gt;ldisc
dot
id|receive_buf
c_func
(paren
id|to
comma
id|buf
comma
l_int|0
comma
id|c
)paren
suffix:semicolon
)brace
r_return
id|c
suffix:semicolon
)brace
DECL|function|pty_write_room
r_static
r_int
id|pty_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
id|tty-&gt;stopped
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|to-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|to
)paren
suffix:semicolon
)brace
DECL|function|pty_chars_in_buffer
r_static
r_int
id|pty_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
op_logical_or
op_logical_neg
id|to-&gt;ldisc.chars_in_buffer
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|to-&gt;ldisc
dot
id|chars_in_buffer
c_func
(paren
id|to
)paren
suffix:semicolon
)brace
DECL|function|pty_flush_buffer
r_static
r_void
id|pty_flush_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|tty_struct
op_star
id|to
op_assign
id|tty-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;ldisc.flush_buffer
)paren
id|to-&gt;ldisc
dot
id|flush_buffer
c_func
(paren
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;packet
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
id|to-&gt;read_wait
)paren
suffix:semicolon
)brace
)brace
DECL|function|pty_open
r_int
id|pty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|line
suffix:semicolon
r_struct
id|pty_struct
op_star
id|pty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
op_logical_or
op_logical_neg
id|tty-&gt;link
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|line
op_assign
id|MINOR
c_func
(paren
id|tty-&gt;device
)paren
op_minus
id|tty-&gt;driver.minor_start
suffix:semicolon
r_if
c_cond
(paren
(paren
id|line
OL
l_int|0
)paren
op_logical_or
(paren
id|line
op_ge
id|NR_PTYS
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pty
op_assign
id|pty_state
op_plus
id|line
suffix:semicolon
id|tty-&gt;driver_data
op_assign
id|pty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_buf
)paren
(brace
id|tmp_buf
op_assign
(paren
r_int
r_char
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tty-&gt;driver.subtype
op_eq
id|PTY_TYPE_SLAVE
)paren
id|clear_bit
c_func
(paren
id|TTY_SLAVE_CLOSED
comma
op_amp
id|tty-&gt;link-&gt;flags
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|pty-&gt;open_wait
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
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
id|pty-&gt;open_wait
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
DECL|function|pty_init
r_int
id|pty_init
c_func
(paren
r_int
id|kmem_start
)paren
(brace
id|memset
c_func
(paren
op_amp
id|pty_state
comma
l_int|0
comma
r_sizeof
(paren
id|pty_state
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pty_driver
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tty_driver
)paren
)paren
suffix:semicolon
id|pty_driver.magic
op_assign
id|TTY_DRIVER_MAGIC
suffix:semicolon
id|pty_driver.name
op_assign
l_string|&quot;pty&quot;
suffix:semicolon
id|pty_driver.major
op_assign
id|TTY_MAJOR
suffix:semicolon
id|pty_driver.minor_start
op_assign
l_int|128
suffix:semicolon
id|pty_driver.num
op_assign
id|NR_PTYS
suffix:semicolon
id|pty_driver.type
op_assign
id|TTY_DRIVER_TYPE_PTY
suffix:semicolon
id|pty_driver.subtype
op_assign
id|PTY_TYPE_MASTER
suffix:semicolon
id|pty_driver.init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|pty_driver.init_termios.c_iflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver.init_termios.c_oflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver.init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|pty_driver.init_termios.c_lflag
op_assign
l_int|0
suffix:semicolon
id|pty_driver.flags
op_assign
id|TTY_DRIVER_RESET_TERMIOS
op_or
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|pty_driver.refcount
op_assign
op_amp
id|pty_refcount
suffix:semicolon
id|pty_driver.table
op_assign
id|pty_table
suffix:semicolon
id|pty_driver.termios
op_assign
id|pty_termios
suffix:semicolon
id|pty_driver.termios_locked
op_assign
id|pty_termios_locked
suffix:semicolon
id|pty_driver.other
op_assign
op_amp
id|pty_slave_driver
suffix:semicolon
id|pty_driver.open
op_assign
id|pty_open
suffix:semicolon
id|pty_driver.close
op_assign
id|pty_close
suffix:semicolon
id|pty_driver.write
op_assign
id|pty_write
suffix:semicolon
id|pty_driver.write_room
op_assign
id|pty_write_room
suffix:semicolon
id|pty_driver.flush_buffer
op_assign
id|pty_flush_buffer
suffix:semicolon
id|pty_driver.chars_in_buffer
op_assign
id|pty_chars_in_buffer
suffix:semicolon
id|pty_driver.unthrottle
op_assign
id|pty_unthrottle
suffix:semicolon
id|pty_slave_driver
op_assign
id|pty_driver
suffix:semicolon
id|pty_slave_driver.name
op_assign
l_string|&quot;ttyp&quot;
suffix:semicolon
id|pty_slave_driver.subtype
op_assign
id|PTY_TYPE_SLAVE
suffix:semicolon
id|pty_slave_driver.minor_start
op_assign
l_int|192
suffix:semicolon
id|pty_slave_driver.init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|pty_slave_driver.init_termios.c_cflag
op_assign
id|B38400
op_or
id|CS8
op_or
id|CREAD
suffix:semicolon
id|pty_slave_driver.table
op_assign
id|ttyp_table
suffix:semicolon
id|pty_slave_driver.termios
op_assign
id|ttyp_termios
suffix:semicolon
id|pty_slave_driver.termios_locked
op_assign
id|ttyp_termios_locked
suffix:semicolon
id|pty_slave_driver.other
op_assign
op_amp
id|pty_driver
suffix:semicolon
id|tmp_buf
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
op_amp
id|pty_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register pty driver&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
op_amp
id|pty_slave_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register pty slave driver&quot;
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
eof
