multiline_comment|/*&n; * linux/drivers/char/mouse.c&n; *&n; * Copyright (C) 1995 - 1998 Russell King&n; *  Protocol taken from busmouse.c&n; *  read() waiting taken from psaux.c&n; *&n; * Medium-level interface for quadrature or bus mice.&n; *&n; * Currently, the majority of kernel busmice drivers in the&n; * kernel common code to talk to userspace.  This driver&n; * attempts to rectify this situation by presenting a&n; * simple and safe interface to the mice and user.&n; *&n; * This driver:&n; *  - is SMP safe&n; *  - handles multiple opens&n; *  - handles the wakeups and locking&n; *  - has optional blocking reads&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;busmouse.h&quot;
multiline_comment|/* Uncomment this if your mouse drivers expect the kernel to&n; * return with EAGAIN if the mouse does not have any events&n; * available, even if the mouse is opened in nonblocking mode.&n; *&n; * Should this be on a per-mouse basis?  If so, add an entry to&n; * the struct busmouse structure and add the relevent flag to&n; * the drivers.&n; */
multiline_comment|/*#define BROKEN_MOUSE*/
r_extern
r_int
id|adb_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|logi_busmouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ms_bus_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atixl_busmouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|amiga_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atari_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sun_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mouse_rpc_init
(paren
r_void
)paren
suffix:semicolon
DECL|struct|busmouse_data
r_struct
id|busmouse_data
(brace
DECL|member|miscdev
r_struct
id|miscdevice
id|miscdev
suffix:semicolon
DECL|member|ops
r_struct
id|busmouse
op_star
id|ops
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|fasyncptr
r_struct
id|fasync_struct
op_star
id|fasyncptr
suffix:semicolon
DECL|member|active
r_char
id|active
suffix:semicolon
DECL|member|buttons
r_char
id|buttons
suffix:semicolon
DECL|member|latch_buttons
r_char
id|latch_buttons
suffix:semicolon
DECL|member|ready
r_char
id|ready
suffix:semicolon
DECL|member|dxpos
r_int
id|dxpos
suffix:semicolon
DECL|member|dypos
r_int
id|dypos
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NR_MICE
mdefine_line|#define NR_MICE&t;&t;&t;15
DECL|macro|FIRST_MOUSE
mdefine_line|#define FIRST_MOUSE&t;&t;0
DECL|macro|DEV_TO_MOUSE
mdefine_line|#define DEV_TO_MOUSE(dev)&t;MINOR_TO_MOUSE(MINOR(dev))
DECL|macro|MINOR_TO_MOUSE
mdefine_line|#define MINOR_TO_MOUSE(minor)&t;((minor) - FIRST_MOUSE)
DECL|variable|busmouse_data
r_static
r_struct
id|busmouse_data
op_star
id|busmouse_data
(braket
id|NR_MICE
)braket
suffix:semicolon
multiline_comment|/* a mouse driver just has to interface with these functions&n; *  These are !!!OLD!!!  Do not use!!!&n; */
DECL|function|add_mouse_movement
r_void
id|add_mouse_movement
c_func
(paren
r_int
id|dx
comma
r_int
id|dy
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
id|busmouse_data
(braket
id|MINOR_TO_MOUSE
c_func
(paren
l_int|6
)paren
)braket
suffix:semicolon
id|mse-&gt;dxpos
op_add_assign
id|dx
suffix:semicolon
id|mse-&gt;dypos
op_add_assign
id|dy
suffix:semicolon
id|mse-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mse-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|add_mouse_buttonchange
r_int
id|add_mouse_buttonchange
c_func
(paren
r_int
id|set
comma
r_int
id|value
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
id|busmouse_data
(braket
id|MINOR_TO_MOUSE
c_func
(paren
l_int|6
)paren
)braket
suffix:semicolon
id|mse-&gt;buttons
op_assign
(paren
id|mse-&gt;buttons
op_amp
op_complement
id|set
)paren
op_xor
id|value
suffix:semicolon
id|mse-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mse-&gt;wait
)paren
suffix:semicolon
r_return
id|mse-&gt;buttons
suffix:semicolon
)brace
multiline_comment|/* New interface.  !!! Use this one !!!&n; * These routines will most probably be called from interrupt.&n; */
r_void
DECL|function|busmouse_add_movementbuttons
id|busmouse_add_movementbuttons
c_func
(paren
r_int
id|mousedev
comma
r_int
id|dx
comma
r_int
id|dy
comma
r_int
id|buttons
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
id|busmouse_data
(braket
id|mousedev
)braket
suffix:semicolon
r_int
id|changed
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mse-&gt;lock
)paren
suffix:semicolon
id|changed
op_assign
(paren
id|dx
op_ne
l_int|0
op_logical_or
id|dy
op_ne
l_int|0
op_logical_or
id|mse-&gt;buttons
op_ne
id|buttons
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed
)paren
(brace
id|add_mouse_randomness
c_func
(paren
(paren
id|buttons
op_lshift
l_int|16
)paren
op_plus
(paren
id|dy
op_lshift
l_int|8
)paren
op_plus
id|dx
)paren
suffix:semicolon
id|mse-&gt;buttons
op_assign
id|buttons
suffix:semicolon
singleline_comment|//&t;&t;mse-&gt;latch_buttons |= buttons;
id|mse-&gt;dxpos
op_add_assign
id|dx
suffix:semicolon
id|mse-&gt;dypos
op_add_assign
id|dy
suffix:semicolon
id|mse-&gt;ready
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * keep dx/dy reasonable, but still able to track when X (or&n;&t;&t; * whatever) must page or is busy (i.e. long waits between&n;&t;&t; * reads)&n;&t;&t; */
r_if
c_cond
(paren
id|mse-&gt;dxpos
OL
op_minus
l_int|2048
)paren
id|mse-&gt;dxpos
op_assign
op_minus
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;dxpos
OG
l_int|2048
)paren
id|mse-&gt;dxpos
op_assign
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;dypos
OL
op_minus
l_int|2048
)paren
id|mse-&gt;dypos
op_assign
op_minus
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;dypos
OG
l_int|2048
)paren
id|mse-&gt;dypos
op_assign
l_int|2048
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mse-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|mse-&gt;wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;fasyncptr
)paren
id|kill_fasync
c_func
(paren
id|mse-&gt;fasyncptr
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|busmouse_add_movement
id|busmouse_add_movement
c_func
(paren
r_int
id|mousedev
comma
r_int
id|dx
comma
r_int
id|dy
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
id|busmouse_data
(braket
id|mousedev
)braket
suffix:semicolon
id|busmouse_add_movementbuttons
c_func
(paren
id|mousedev
comma
id|dx
comma
id|dy
comma
id|mse-&gt;buttons
)paren
suffix:semicolon
)brace
r_void
DECL|function|busmouse_add_buttons
id|busmouse_add_buttons
c_func
(paren
r_int
id|mousedev
comma
r_int
id|clear
comma
r_int
id|eor
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
id|busmouse_data
(braket
id|mousedev
)braket
suffix:semicolon
id|busmouse_add_movementbuttons
c_func
(paren
id|mousedev
comma
l_int|0
comma
l_int|0
comma
(paren
id|mse-&gt;buttons
op_amp
op_complement
id|clear
)paren
op_xor
id|eor
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|busmouse_fasync
id|busmouse_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_struct
id|busmouse_data
op_star
id|mse
op_assign
(paren
r_struct
id|busmouse_data
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|mse-&gt;fasyncptr
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
r_static
r_int
DECL|function|busmouse_release
id|busmouse_release
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
r_struct
id|busmouse_data
op_star
id|mse
op_assign
(paren
r_struct
id|busmouse_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|busmouse_fasync
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|mse-&gt;active
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|mse-&gt;ops
op_logical_and
id|mse-&gt;ops-&gt;release
)paren
id|ret
op_assign
id|mse-&gt;ops
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
id|mse-&gt;ready
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|busmouse_open
id|busmouse_open
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
r_struct
id|busmouse_data
op_star
id|mse
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|mousedev
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|mousedev
op_assign
id|DEV_TO_MOUSE
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mousedev
op_ge
id|NR_MICE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mse
op_assign
id|busmouse_data
(braket
id|mousedev
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mse
)paren
multiline_comment|/* shouldn&squot;t happen, but... */
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;ops
op_logical_and
id|mse-&gt;ops-&gt;open
)paren
id|ret
op_assign
id|mse-&gt;ops
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|file-&gt;private_data
op_assign
id|mse
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;active
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|mse-&gt;ready
op_assign
l_int|0
suffix:semicolon
id|mse-&gt;dxpos
op_assign
l_int|0
suffix:semicolon
id|mse-&gt;dypos
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;ops
)paren
id|mse-&gt;buttons
op_assign
id|mse-&gt;ops-&gt;init_button_state
suffix:semicolon
r_else
id|mse-&gt;buttons
op_assign
l_int|7
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|busmouse_write
id|busmouse_write
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
r_static
id|ssize_t
DECL|function|busmouse_read
id|busmouse_read
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
r_struct
id|busmouse_data
op_star
id|mse
op_assign
(paren
r_struct
id|busmouse_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|dxpos
comma
id|dypos
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mse-&gt;ready
)paren
(brace
macro_line|#ifdef BROKEN_MOUSE
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|add_wait_queue
c_func
(paren
op_amp
id|mse-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mse-&gt;ready
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_goto
id|repeat
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
id|mse-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
macro_line|#endif
)brace
id|dxpos
op_assign
id|mse-&gt;dxpos
suffix:semicolon
id|dypos
op_assign
id|mse-&gt;dypos
suffix:semicolon
id|buttons
op_assign
id|mse-&gt;buttons
suffix:semicolon
singleline_comment|//&t;mse-&gt;latch_buttons = mse-&gt;buttons;
r_if
c_cond
(paren
id|dxpos
OL
op_minus
l_int|127
)paren
id|dxpos
op_assign
op_minus
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|dxpos
OG
l_int|127
)paren
id|dxpos
op_assign
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|dypos
OL
op_minus
l_int|127
)paren
id|dypos
op_assign
op_minus
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|dypos
OG
l_int|127
)paren
id|dypos
op_assign
l_int|127
suffix:semicolon
id|mse-&gt;dxpos
op_sub_assign
id|dxpos
suffix:semicolon
id|mse-&gt;dypos
op_sub_assign
id|dypos
suffix:semicolon
multiline_comment|/* This is something that many drivers have apparantly&n;&t; * forgotten...  If the X and Y positions still contain&n;&t; * information, we still have some info ready for the&n;&t; * user program...&n;&t; */
id|mse-&gt;ready
op_assign
id|mse-&gt;dxpos
op_logical_or
id|mse-&gt;dypos
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mse-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Write out data to the user.  Format is:&n;&t; *   byte 0 - identifer (0x80) and (inverted) mouse buttons&n;&t; *   byte 1 - X delta position +/- 127&n;&t; *   byte 2 - Y delta position +/- 127&n;&t; */
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
r_char
)paren
id|buttons
op_or
l_int|128
comma
id|buffer
)paren
op_logical_or
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dxpos
comma
id|buffer
op_plus
l_int|1
)paren
op_logical_or
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dypos
comma
id|buffer
op_plus
l_int|2
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
op_logical_and
id|clear_user
c_func
(paren
id|buffer
op_plus
l_int|3
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
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|busmouse_poll
id|busmouse_poll
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
r_struct
id|busmouse_data
op_star
id|mse
op_assign
(paren
r_struct
id|busmouse_data
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|mse-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mse-&gt;ready
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
DECL|variable|busmouse_fops
r_struct
id|file_operations
id|busmouse_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* busmouse_seek */
id|busmouse_read
comma
id|busmouse_write
comma
l_int|NULL
comma
multiline_comment|/* busmouse_readdir */
id|busmouse_poll
comma
l_int|NULL
comma
multiline_comment|/* busmouse_ioctl */
l_int|NULL
comma
multiline_comment|/* busmouse_mmap */
id|busmouse_open
comma
l_int|NULL
comma
multiline_comment|/* busmouse_flush */
id|busmouse_release
comma
l_int|NULL
comma
id|busmouse_fasync
comma
)brace
suffix:semicolon
r_int
DECL|function|register_busmouse
id|register_busmouse
c_func
(paren
r_struct
id|busmouse
op_star
id|ops
)paren
(brace
r_int
r_int
id|msedev
op_assign
id|MINOR_TO_MOUSE
c_func
(paren
id|ops-&gt;minor
)paren
suffix:semicolon
r_struct
id|busmouse_data
op_star
id|mse
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|msedev
op_ge
id|NR_MICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;busmouse: trying to allocate mouse on minor %d&bslash;n&quot;
comma
id|ops-&gt;minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|busmouse_data
(braket
id|msedev
)braket
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|mse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mse
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mse
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|mse
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mse
)paren
)paren
suffix:semicolon
id|mse-&gt;miscdev.minor
op_assign
id|ops-&gt;minor
suffix:semicolon
id|mse-&gt;miscdev.name
op_assign
id|ops-&gt;name
suffix:semicolon
id|mse-&gt;miscdev.fops
op_assign
op_amp
id|busmouse_fops
suffix:semicolon
id|mse-&gt;ops
op_assign
id|ops
suffix:semicolon
id|mse-&gt;lock
op_assign
(paren
id|spinlock_t
)paren
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mse-&gt;wait
)paren
suffix:semicolon
id|busmouse_data
(braket
id|msedev
)braket
op_assign
id|mse
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|mse-&gt;miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|msedev
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|unregister_busmouse
id|unregister_busmouse
c_func
(paren
r_int
id|mousedev
)paren
(brace
r_if
c_cond
(paren
id|mousedev
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mousedev
op_ge
id|NR_MICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;busmouse: trying to free mouse on&quot;
l_string|&quot; mousedev %d&bslash;n&quot;
comma
id|mousedev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|busmouse_data
(braket
id|mousedev
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;busmouse: trying to free free mouse&quot;
l_string|&quot; on mousedev %d&bslash;n&quot;
comma
id|mousedev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|busmouse_data
(braket
id|mousedev
)braket
op_member_access_from_pointer
id|active
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;busmouse: trying to free active mouse&quot;
l_string|&quot; on mousedev %d&bslash;n&quot;
comma
id|mousedev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|busmouse_data
(braket
id|mousedev
)braket
op_member_access_from_pointer
id|miscdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|busmouse_data
(braket
id|mousedev
)braket
)paren
suffix:semicolon
id|busmouse_data
(braket
id|mousedev
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|bus_mouse_init
id|bus_mouse_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_LOGIBUSMOUSE
id|logi_busmouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MS_BUSMOUSE
id|ms_bus_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATIXL_BUSMOUSE
id|atixl_busmouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGAMOUSE
id|amiga_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARIMOUSE
id|atari_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN_MOUSE
id|sun_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ADB_MOUSE
id|adb_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RPCMOUSE
id|mouse_rpc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|busmouse_add_movementbuttons
id|EXPORT_SYMBOL
c_func
(paren
id|busmouse_add_movementbuttons
)paren
suffix:semicolon
DECL|variable|busmouse_add_movement
id|EXPORT_SYMBOL
c_func
(paren
id|busmouse_add_movement
)paren
suffix:semicolon
DECL|variable|busmouse_add_buttons
id|EXPORT_SYMBOL
c_func
(paren
id|busmouse_add_buttons
)paren
suffix:semicolon
DECL|variable|register_busmouse
id|EXPORT_SYMBOL
c_func
(paren
id|register_busmouse
)paren
suffix:semicolon
DECL|variable|unregister_busmouse
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_busmouse
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|bus_mouse_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
