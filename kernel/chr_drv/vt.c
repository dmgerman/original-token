multiline_comment|/*&n; *  kernel/chr_drv/vt.c&n; *&n; *  Copyright (C) 1992 obz under the linux copyright&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/keyboard.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/vt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;vt_kern.h&quot;
multiline_comment|/*&n; * Console (vt and kd) routines, as defined by USL SVR4 manual&n; *&n; * One point of difference: SYSV vt&squot;s are /dev/vtX, which X &gt;= 0, and&n; * /dev/console is a separate ttyp. Under Linux, /dev/tty0 is /dev/console,&n; * and the vc start at /dev/ttyX, X &gt;= 1. We maintain that here, so we will&n; * always treat our set of vt as numbered 1..NR_CONSOLES (corresponding to&n; * ttys 0..NR_CONSOLES-1).&n; *&n; * Mostly done for X386, but with some slight differences and omissions.&n; * Should be useable by other SYSV programs in the future.&n; */
DECL|variable|vt_cons
r_struct
id|vt_cons
id|vt_cons
(braket
id|NR_CONSOLES
)braket
suffix:semicolon
r_extern
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
id|on
)paren
suffix:semicolon
r_extern
r_void
id|set_leds
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|change_console
c_func
(paren
r_int
r_int
id|new_console
)paren
suffix:semicolon
r_extern
r_void
id|complete_change_console
c_func
(paren
r_int
r_int
id|new_console
)paren
suffix:semicolon
multiline_comment|/*&n; * these are the valid i/o ports we&squot;re allowed to change. they map all the&n; * video ports&n; */
DECL|macro|GPFIRST
mdefine_line|#define GPFIRST 0x3b4
DECL|macro|GPLAST
mdefine_line|#define GPLAST 0x3df
DECL|macro|GPNUM
mdefine_line|#define GPNUM (GPLAST - GPFIRST + 1)
multiline_comment|/*&n; * Generates sound of some count for some number of clock ticks&n; * [count = 1193180 / frequency]&n; *&n; * If freq is 0, will turn off sound, else will turn it on for that time.&n; * If msec is 0, will return immediately, else will sleep for msec time, then&n; * turn sound off.&n; *&n; * We use the BEEP_TIMER vector since we&squot;re using the same method to&n; * generate sound, and we&squot;ll overwrite any beep in progress. That may&n; * be something to fix later, if we like.&n; *&n; * We also return immediately, which is what was implied within the X&n; * comments - KDMKTONE doesn&squot;t put the process to sleep.&n; */
r_void
DECL|function|kd_nosound
id|kd_nosound
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* disable counter 2 */
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x61
)paren
op_amp
l_int|0xFC
comma
l_int|0x61
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|kd_mksound
id|kd_mksound
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|ticks
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
multiline_comment|/* enable counter 2 */
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x61
)paren
op_or
l_int|3
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* set command for counter 2, 2 byte write */
id|outb_p
c_func
(paren
l_int|0xB6
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* select desired HZ */
id|outb_p
c_func
(paren
id|count
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ticks
)paren
(brace
id|timer_table
(braket
id|BEEP_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
id|ticks
suffix:semicolon
id|timer_table
(braket
id|BEEP_TIMER
)braket
dot
id|fn
op_assign
id|kd_nosound
suffix:semicolon
id|timer_active
op_or_assign
(paren
l_int|1
op_lshift
id|BEEP_TIMER
)paren
suffix:semicolon
)brace
)brace
r_else
id|kd_nosound
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * We handle the console-specific ioctl&squot;s here.  We allow the&n; * capability to modify any console, not just the fg_console. &n; */
DECL|function|vt_ioctl
r_int
id|vt_ioctl
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
id|console
comma
id|i
suffix:semicolon
r_int
r_char
id|ucval
suffix:semicolon
r_struct
id|kbd_struct
op_star
id|kbd
suffix:semicolon
id|console
op_assign
id|tty-&gt;line
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|console
OL
l_int|0
op_logical_or
id|console
op_ge
id|NR_CONSOLES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kbd
op_assign
id|kbd_table
op_plus
id|console
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|KIOCSOUND
suffix:colon
id|kd_mksound
c_func
(paren
(paren
r_int
r_int
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|KDMKTONE
suffix:colon
(brace
r_int
r_int
id|ticks
op_assign
id|HZ
op_star
(paren
(paren
id|arg
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
op_div
l_int|1000
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Generate the tone for the appropriate number of ticks.&n;&t;&t; * If the time is zero, turn off sound ourselves.&n;&t;&t; */
id|kd_mksound
c_func
(paren
id|arg
op_amp
l_int|0xffff
comma
id|ticks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ticks
op_eq
l_int|0
)paren
id|kd_nosound
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|KDGKBTYPE
suffix:colon
multiline_comment|/*&n;&t;&t; * this is naive.&n;&t;&t; */
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_char
)paren
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|KB_101
comma
(paren
r_int
r_char
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|KDADDIO
suffix:colon
r_case
id|KDDELIO
suffix:colon
multiline_comment|/*&n;&t;&t; * KDADDIO and KDDELIO may be able to add ports beyond what&n;&t;&t; * we reject here, but to be safe...&n;&t;&t; */
r_if
c_cond
(paren
id|arg
template_param
id|GPLAST
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sys_ioperm
c_func
(paren
id|arg
comma
l_int|1
comma
(paren
id|cmd
op_eq
id|KDADDIO
)paren
)paren
ques
c_cond
op_minus
id|ENXIO
suffix:colon
l_int|0
suffix:semicolon
r_case
id|KDENABIO
suffix:colon
r_case
id|KDDISABIO
suffix:colon
r_return
id|sys_ioperm
c_func
(paren
id|GPFIRST
comma
id|GPNUM
comma
(paren
id|cmd
op_eq
id|KDENABIO
)paren
)paren
ques
c_cond
op_minus
id|ENXIO
suffix:colon
l_int|0
suffix:semicolon
r_case
id|KDSETMODE
suffix:colon
multiline_comment|/*&n;&t;&t; * currently, setting the mode from KD_TEXT to KD_GRAPHICS&n;&t;&t; * doesn&squot;t do a whole lot. i&squot;m not sure if it should do any&n;&t;&t; * restoration of modes or what...&n;&t;&t; */
r_switch
c_cond
(paren
id|arg
)paren
(brace
r_case
id|KD_GRAPHICS
suffix:colon
r_break
suffix:semicolon
r_case
id|KD_TEXT0
suffix:colon
r_case
id|KD_TEXT1
suffix:colon
id|arg
op_assign
id|KD_TEXT
suffix:semicolon
r_case
id|KD_TEXT
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vc_mode
op_eq
(paren
r_int
r_char
)paren
id|arg
)paren
r_return
l_int|0
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vc_mode
op_assign
(paren
r_int
r_char
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|console
op_ne
id|fg_console
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * explicitly blank/unblank the screen if switching modes&n;&t;&t; */
r_if
c_cond
(paren
id|arg
op_eq
id|KD_TEXT
)paren
id|unblank_screen
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|timer_active
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|BLANK_TIMER
)paren
suffix:semicolon
id|blank_screen
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|KDGETMODE
suffix:colon
id|verify_area
c_func
(paren
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
id|put_fs_long
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vc_mode
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
id|KDMAPDISP
suffix:colon
r_case
id|KDUNMAPDISP
suffix:colon
multiline_comment|/*&n;&t;&t; * these work like a combination of mmap and KDENABIO.&n;&t;&t; * this could be easily finished.&n;&t;&t; */
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|KDSKBMODE
suffix:colon
r_if
c_cond
(paren
id|arg
op_eq
id|K_RAW
)paren
(brace
id|set_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_RAW
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
op_eq
id|K_XLATE
)paren
(brace
id|clr_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_RAW
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
id|flush_input
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|KDGKBMODE
suffix:colon
id|verify_area
c_func
(paren
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
id|ucval
op_assign
id|vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_RAW
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ucval
ques
c_cond
id|K_RAW
suffix:colon
id|K_XLATE
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
id|KDGETLED
suffix:colon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_char
)paren
)paren
suffix:semicolon
id|ucval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_SCROLLOCK
)paren
)paren
id|ucval
op_or_assign
id|LED_SCR
suffix:semicolon
r_if
c_cond
(paren
id|vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_NUMLOCK
)paren
)paren
id|ucval
op_or_assign
id|LED_NUM
suffix:semicolon
r_if
c_cond
(paren
id|vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_CAPSLOCK
)paren
)paren
id|ucval
op_or_assign
id|LED_CAP
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|ucval
comma
(paren
r_int
r_char
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|KDSETLED
suffix:colon
r_if
c_cond
(paren
id|arg
op_amp
op_complement
l_int|7
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_amp
id|LED_SCR
)paren
id|set_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_SCROLLOCK
)paren
suffix:semicolon
r_else
id|clr_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_SCROLLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_amp
id|LED_NUM
)paren
id|set_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_NUMLOCK
)paren
suffix:semicolon
r_else
id|clr_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_NUMLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_amp
id|LED_CAP
)paren
id|set_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_CAPSLOCK
)paren
suffix:semicolon
r_else
id|clr_vc_kbd_flag
c_func
(paren
id|kbd
comma
id|VC_CAPSLOCK
)paren
suffix:semicolon
id|set_leds
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|VT_SETMODE
suffix:colon
(brace
r_struct
id|vt_mode
op_star
id|vtmode
op_assign
(paren
r_struct
id|vt_mode
op_star
)paren
id|arg
suffix:semicolon
r_char
id|mode
suffix:semicolon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|vtmode
comma
r_sizeof
(paren
r_struct
id|vt_mode
)paren
)paren
suffix:semicolon
id|mode
op_assign
id|get_fs_byte
c_func
(paren
op_amp
id|vtmode-&gt;mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_ne
id|VT_AUTO
op_logical_and
id|mode
op_ne
id|VT_PROCESS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.mode
op_assign
id|mode
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.waitv
op_assign
id|get_fs_byte
c_func
(paren
op_amp
id|vtmode-&gt;waitv
)paren
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.relsig
op_assign
id|get_fs_word
c_func
(paren
op_amp
id|vtmode-&gt;relsig
)paren
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.acqsig
op_assign
id|get_fs_word
c_func
(paren
op_amp
id|vtmode-&gt;acqsig
)paren
suffix:semicolon
multiline_comment|/* the frsig is ignored, so we set it to 0 */
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.frsig
op_assign
l_int|0
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_newvt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VT_GETMODE
suffix:colon
(brace
r_struct
id|vt_mode
op_star
id|vtmode
op_assign
(paren
r_struct
id|vt_mode
op_star
)paren
id|arg
suffix:semicolon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|vt_mode
)paren
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.mode
comma
op_amp
id|vtmode-&gt;mode
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.waitv
comma
op_amp
id|vtmode-&gt;waitv
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.relsig
comma
op_amp
id|vtmode-&gt;relsig
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.acqsig
comma
op_amp
id|vtmode-&gt;acqsig
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.frsig
comma
op_amp
id|vtmode-&gt;frsig
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Returns the first available (non-opened) console.&n;&t; */
r_case
id|VT_OPENQRY
suffix:colon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|NR_CONSOLES
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
op_logical_neg
id|tty_table
(braket
id|i
)braket
op_logical_or
id|tty_table
(braket
id|i
)braket
op_member_access_from_pointer
id|count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|put_fs_long
c_func
(paren
id|i
op_le
id|NR_CONSOLES
ques
c_cond
id|i
suffix:colon
op_minus
l_int|1
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
multiline_comment|/*&n;&t; * ioctl(fd, VT_ACTIVATE, num) will cause us to switch to vt # num,&n;&t; * with num &gt;= 1 (switches to vt 0, our console) are not allowed, just&n;&t; * to preserve sanity.&n;&t; */
r_case
id|VT_ACTIVATE
suffix:colon
r_if
c_cond
(paren
id|arg
op_eq
l_int|0
op_logical_or
id|arg
OG
id|NR_CONSOLES
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|change_console
c_func
(paren
id|arg
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If a vt is under process control, the kernel will not switch to it&n;&t; * immediately, but postpone the operation until the process calls this&n;&t; * ioctl, allowing the switch to complete.&n;&t; *&n;&t; * XXX Under X, the switching code calls VT_RELDISP with an arg of 2&n;&t; * when it has switched back to it&squot;s vt. That&squot;s not kosher according&n;&t; * to my documentation, which says this is only called when releasing&n;&t; * the vt under your control.&n;&t; */
r_case
id|VT_RELDISP
suffix:colon
r_if
c_cond
(paren
id|vt_cons
(braket
id|console
)braket
dot
id|vt_mode.mode
op_ne
id|VT_PROCESS
op_logical_or
id|vt_cons
(braket
id|console
)braket
dot
id|vt_newvt
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
id|arg
op_ne
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If arg is nonzero, the current vt has been released,&n;&t;&t;&t; * so we can go ahead and complete the switch.&n;&t;&t;&t; */
r_int
id|newvt
op_assign
id|vt_cons
(braket
id|console
)braket
dot
id|vt_newvt
suffix:semicolon
id|vt_cons
(braket
id|console
)braket
dot
id|vt_newvt
op_assign
op_minus
l_int|1
suffix:semicolon
id|complete_change_console
c_func
(paren
id|newvt
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Mark that we&squot;ve performed our part and return.&n;&t;&t;&t; */
id|vt_cons
(braket
id|console
)braket
dot
id|vt_newvt
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof
