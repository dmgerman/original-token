multiline_comment|/*&n; * Macintosh ADB Mouse driver for Linux&n; *&n; * 27 Oct 1997 Michael Schmitz&n; * logitech fixes by anthony tong&n; *&n; * Apple mouse protocol according to:&n; *&n; * Device code shamelessly stolen from:&n; */
multiline_comment|/*&n; * Atari Mouse Driver for Linux&n; * by Robert de Vries (robert@and.nl) 19Jul93&n; *&n; * 16 Nov 1994 Andreas Schwab&n; * Compatibility with busmouse&n; * Support for three button mouse (shamelessly stolen from MiNT)&n; * third button wired to one of the joystick directions on joystick 1&n; *&n; * 1996/02/11 Andreas Schwab&n; * Module support&n; * Allow multiple open&squot;s&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/adb_mouse.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|variable|mouse
r_static
r_struct
id|mouse_status
id|mouse
suffix:semicolon
DECL|variable|adb_mouse_x_threshold
DECL|variable|adb_mouse_y_threshold
r_static
r_int
id|adb_mouse_x_threshold
op_assign
l_int|2
comma
id|adb_mouse_y_threshold
op_assign
l_int|2
suffix:semicolon
DECL|variable|adb_mouse_buttons
r_static
r_int
id|adb_mouse_buttons
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
(paren
op_star
id|adb_mouse_interrupt_hook
)paren
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|console_loglevel
suffix:semicolon
multiline_comment|/*&n; *&t;XXX: need to figure out what ADB mouse packets mean ... &n; *&t;This is the stuff stolen from the Atari driver ...&n; */
DECL|function|adb_mouse_interrupt
r_static
r_void
id|adb_mouse_interrupt
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|nb
)paren
(brace
r_static
r_int
id|buttons
op_assign
l_int|7
suffix:semicolon
multiline_comment|/*&n;    Handler 1 -- 100cpi original Apple mouse protocol.&n;    Handler 2 -- 200cpi original Apple mouse protocol.&n;&n;    For Apple&squot;s standard one-button mouse protocol the data array will&n;    contain the following values:&n;&n;                BITS    COMMENTS&n;    data[0] = 0000 0000 ADB packet identifer.&n;    data[1] = ???? ???? (?)&n;    data[2] = ???? ??00 Bits 0-1 should be zero for a mouse device.&n;    data[3] = bxxx xxxx First button and x-axis motion.&n;    data[4] = byyy yyyy Second button and y-axis motion.&n;&n;    NOTE: data[0] is confirmed by the parent function and need not be&n;    checked here.&n;  */
multiline_comment|/*&n;    Handler 4 -- Apple Extended mouse protocol.&n;&n;    For Apple&squot;s 3-button mouse protocol the data array will contain the&n;    following values:&n;&n;&t;&t;BITS    COMMENTS&n;    data[0] = 0000 0000 ADB packet identifer.&n;    data[1] = 0100 0000 Extended protocol register.&n;&t;      Bits 6-7 are the device id, which should be 1.&n;&t;      Bits 4-5 are resolution which is in &quot;units/inch&quot;.&n;&t;      The Logitech MouseMan returns these bits clear but it has&n;&t;      200/300cpi resolution.&n;&t;      Bits 0-3 are unique vendor id.&n;    data[2] = 0011 1100 Bits 0-1 should be zero for a mouse device.&n;&t;      Bits 2-3 should be 8 + 4.&n;&t;&t;      Bits 4-7 should be 3 for a mouse device.&n;    data[3] = bxxx xxxx Left button and x-axis motion.&n;    data[4] = byyy yyyy Second button and y-axis motion.&n;    data[5] = byyy bxxx Third button and fourth button.  &n;    &t;      Y is additiona. high bits of y-axis motion.  &n;    &t;      X is additional high bits of x-axis motion.&n;&n;    NOTE: data[0] and data[2] are confirmed by the parent function and&n;    need not be checked here.&n;  */
multiline_comment|/*&n;     * &squot;buttons&squot; here means &squot;button down&squot; states!&n;     * Button 1 (left)  : bit 2, busmouse button 3&n;     * Button 2 (right) : bit 0, busmouse button 1&n;     * Button 3 (middle): bit 1, busmouse button 2&n;     */
multiline_comment|/* x/y and buttons swapped */
r_if
c_cond
(paren
id|nb
OG
l_int|0
)paren
(brace
multiline_comment|/* real packet : use buttons? */
r_if
c_cond
(paren
id|console_loglevel
op_ge
l_int|8
)paren
id|printk
c_func
(paren
l_string|&quot;adb_mouse: real data; &quot;
)paren
suffix:semicolon
multiline_comment|/* button 1 (left, bit 2) : always significant ! */
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|3
)paren
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 1+2 unchanged */
multiline_comment|/* button 2 (middle) */
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|5
)paren
op_or
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 2+3 unchanged */
multiline_comment|/* button 3 (right) present?&n;&t; *  on a logitech mouseman, the right and mid buttons sometimes behave&n;&t; *  strangely until they both have been pressed after booting. */
multiline_comment|/* data valid only if extended mouse format ! (buf[3] = 0 else) */
r_if
c_cond
(paren
id|nb
op_eq
l_int|6
)paren
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|6
)paren
op_or
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 1+3 unchanged */
)brace
r_else
(brace
multiline_comment|/* fake packet : use 2+3 */
r_if
c_cond
(paren
id|console_loglevel
op_ge
l_int|8
)paren
id|printk
c_func
(paren
l_string|&quot;adb_mouse: fake data; &quot;
)paren
suffix:semicolon
multiline_comment|/* we only see state changes here, but the fake driver takes care&n;&t; * to preserve state... button 1 state must stay unchanged! */
id|buttons
op_assign
(paren
id|buttons
op_amp
l_int|4
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_or
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
id|add_mouse_randomness
c_func
(paren
(paren
(paren
op_complement
id|buttons
op_amp
l_int|7
)paren
op_lshift
l_int|16
)paren
op_plus
(paren
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
op_lshift
l_int|8
)paren
op_plus
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
id|mouse.buttons
op_assign
id|buttons
op_amp
l_int|7
suffix:semicolon
id|mouse.dx
op_add_assign
(paren
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
OL
l_int|64
ques
c_cond
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
suffix:colon
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
op_minus
l_int|128
)paren
suffix:semicolon
id|mouse.dy
op_sub_assign
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
OL
l_int|64
ques
c_cond
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
suffix:colon
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_minus
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console_loglevel
op_ge
l_int|8
)paren
id|printk
c_func
(paren
l_string|&quot; %X %X %X buttons %x dx %d dy %d &bslash;n&quot;
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
comma
id|mouse.buttons
comma
id|mouse.dx
comma
id|mouse.dy
)paren
suffix:semicolon
id|mouse.ready
op_assign
l_int|1
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|mouse.wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse.fasyncptr
)paren
id|kill_fasync
c_func
(paren
id|mouse.fasyncptr
comma
id|SIGIO
)paren
suffix:semicolon
)brace
DECL|function|fasync_mouse
r_static
r_int
id|fasync_mouse
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|filp
comma
id|on
comma
op_amp
id|mouse.fasyncptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_mouse
r_static
r_int
id|release_mouse
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
id|fasync_mouse
c_func
(paren
id|file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|mouse.active
)paren
r_return
l_int|0
suffix:semicolon
id|adb_mouse_interrupt_hook
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_mouse
r_static
r_int
id|open_mouse
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
r_if
c_cond
(paren
id|mouse.active
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|mouse.dx
op_assign
id|mouse.dy
op_assign
l_int|0
suffix:semicolon
id|adb_mouse_buttons
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|adb_mouse_interrupt_hook
op_assign
id|adb_mouse_interrupt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_mouse
r_static
id|ssize_t
id|write_mouse
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|read_mouse
r_static
id|ssize_t
id|read_mouse
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|dx
comma
id|dy
comma
id|buttons
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mouse.ready
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|dx
op_assign
id|mouse.dx
suffix:semicolon
id|dy
op_assign
id|mouse.dy
suffix:semicolon
id|buttons
op_assign
id|mouse.buttons
suffix:semicolon
r_if
c_cond
(paren
id|dx
OG
l_int|127
)paren
id|dx
op_assign
l_int|127
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dx
OL
op_minus
l_int|128
)paren
id|dx
op_assign
op_minus
l_int|128
suffix:semicolon
r_if
c_cond
(paren
id|dy
OG
l_int|127
)paren
id|dy
op_assign
l_int|127
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dy
OL
op_minus
l_int|128
)paren
id|dy
op_assign
op_minus
l_int|128
suffix:semicolon
id|mouse.dx
op_sub_assign
id|dx
suffix:semicolon
id|mouse.dy
op_sub_assign
id|dy
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dx
op_eq
l_int|0
op_logical_and
id|mouse.dy
op_eq
l_int|0
)paren
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|buttons
op_or
l_int|0x80
comma
id|buffer
op_increment
)paren
op_logical_or
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dx
comma
id|buffer
op_increment
)paren
op_logical_or
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dy
comma
id|buffer
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|3
)paren
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buffer
comma
id|count
op_minus
l_int|3
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mouse_poll
r_static
r_int
r_int
id|mouse_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|mouse.wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse.ready
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|adb_mouse_fops
r_struct
id|file_operations
id|adb_mouse_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* mouse_seek */
id|read_mouse
comma
id|write_mouse
comma
l_int|NULL
comma
multiline_comment|/* mouse_readdir */
id|mouse_poll
comma
l_int|NULL
comma
multiline_comment|/* mouse_ioctl */
l_int|NULL
comma
multiline_comment|/* mouse_mmap */
id|open_mouse
comma
id|release_mouse
comma
l_int|NULL
comma
id|fasync_mouse
comma
)brace
suffix:semicolon
DECL|macro|ADB_MOUSE_MINOR
mdefine_line|#define ADB_MOUSE_MINOR&t;10
DECL|variable|adb_mouse
r_static
r_struct
id|miscdevice
id|adb_mouse
op_assign
(brace
id|ADB_MOUSE_MINOR
comma
l_string|&quot;adbmouse&quot;
comma
op_amp
id|adb_mouse_fops
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|adb_mouse_init
c_func
(paren
r_void
)paren
)paren
(brace
id|mouse.active
op_assign
l_int|0
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|mouse.wait
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_machine
op_ne
id|_MACH_chrp
)paren
op_logical_and
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Macintosh ADB mouse installed.&bslash;n&quot;
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|adb_mouse
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MIN_THRESHOLD
mdefine_line|#define&t;MIN_THRESHOLD 1
DECL|macro|MAX_THRESHOLD
mdefine_line|#define&t;MAX_THRESHOLD 20&t;/* more seems not reasonable... */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|adb_mouse_setup
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
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;adb_mouse_setup: no arguments!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;adb_mouse_setup: too many arguments&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|1
)braket
template_param
id|MAX_THRESHOLD
)paren
id|printk
c_func
(paren
l_string|&quot;adb_mouse_setup: bad threshold value (ignored)&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|adb_mouse_x_threshold
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
id|adb_mouse_y_threshold
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|2
)braket
template_param
id|MAX_THRESHOLD
)paren
id|printk
c_func
(paren
l_string|&quot;adb_mouse_setup: bad threshold value (ignored)&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|adb_mouse_y_threshold
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef MODULE
macro_line|#include &lt;asm/setup.h&gt;
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|adb_mouse_init
c_func
(paren
)paren
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
id|misc_deregister
c_func
(paren
op_amp
id|adb_mouse
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
