multiline_comment|/*&n; * Logitech Bus Mouse Driver for Linux&n; * by James Banks&n; *&n; * Mods by Matthew Dillon&n; *   calls verify_area()&n; *   tracks better when X is busy or paging&n; *&n; * Heavily modified by David Giller&n; *   changed from queue- to counter- driven&n; *   hacked out a (probably incorrect) mouse_select&n; *&n; * Modified again by Nathan Laredo to interface with&n; *   0.96c-pl1 IRQ handling changes (13JUL92)&n; *   didn&squot;t bother touching select code.&n; *&n; * Modified the select() code blindly to conform to the VFS&n; *   requirements. 92.07.14 - Linus. Somebody should test it out.&n; *&n; * Modified by Johan Myreen to make room for other mice (9AUG92)&n; *   removed assignment chr_fops[10] = &amp;mouse_fops; see mouse.c&n; *   renamed mouse_fops =&gt; bus_mouse_fops, made bus_mouse_fops public.&n; *   renamed this file mouse.c =&gt; busmouse.c&n; *&n; * Minor addition by Cliff Matthews&n; *   added fasync support&n; *&n; * Modularised 6-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt; &n; *&n; * Replaced dumb busy loop with udelay()  16 Nov 95&n; *   Nathan Laredo &lt;laredo@gnu.ai.mit.edu&gt;&n; *&n; * Track I/O ports with request_region().  12 Dec 95 Philip Blundell &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/busmouse.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|variable|mouse
r_static
r_struct
id|mouse_status
id|mouse
suffix:semicolon
DECL|variable|mouse_irq
r_static
r_int
id|mouse_irq
op_assign
id|MOUSE_IRQ
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|bmouse_setup
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
OG
l_int|0
)paren
id|mouse_irq
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|mouse_interrupt
r_static
r_void
id|mouse_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_char
id|dx
comma
id|dy
suffix:semicolon
r_int
r_char
id|buttons
suffix:semicolon
id|outb
c_func
(paren
id|MSE_READ_X_LOW
comma
id|MSE_CONTROL_PORT
)paren
suffix:semicolon
id|dx
op_assign
(paren
id|inb
c_func
(paren
id|MSE_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MSE_READ_X_HIGH
comma
id|MSE_CONTROL_PORT
)paren
suffix:semicolon
id|dx
op_or_assign
(paren
id|inb
c_func
(paren
id|MSE_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
op_lshift
l_int|4
suffix:semicolon
id|outb
c_func
(paren
id|MSE_READ_Y_LOW
comma
id|MSE_CONTROL_PORT
)paren
suffix:semicolon
id|dy
op_assign
(paren
id|inb
c_func
(paren
id|MSE_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MSE_READ_Y_HIGH
comma
id|MSE_CONTROL_PORT
)paren
suffix:semicolon
id|buttons
op_assign
id|inb
c_func
(paren
id|MSE_DATA_PORT
)paren
suffix:semicolon
id|dy
op_or_assign
(paren
id|buttons
op_amp
l_int|0xf
)paren
op_lshift
l_int|4
suffix:semicolon
id|buttons
op_assign
(paren
(paren
id|buttons
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dx
op_ne
l_int|0
op_logical_or
id|dy
op_ne
l_int|0
op_logical_or
id|buttons
op_ne
id|mouse.buttons
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
id|mouse.buttons
op_assign
id|buttons
suffix:semicolon
id|mouse.dx
op_add_assign
id|dx
suffix:semicolon
id|mouse.dy
op_sub_assign
id|dy
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
multiline_comment|/*&n;&t;   * keep dx/dy reasonable, but still able to track when X (or&n;&t;   * whatever) must page or is busy (i.e. long waits between&n;&t;   * reads)&n;&t;   */
r_if
c_cond
(paren
id|mouse.dx
OL
op_minus
l_int|2048
)paren
id|mouse.dx
op_assign
op_minus
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dx
OG
l_int|2048
)paren
id|mouse.dx
op_assign
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dy
OL
op_minus
l_int|2048
)paren
id|mouse.dy
op_assign
op_minus
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dy
OG
l_int|2048
)paren
id|mouse.dy
op_assign
l_int|2048
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
id|MSE_INT_ON
c_func
(paren
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
multiline_comment|/*&n; * close access to the mouse&n; */
DECL|function|close_mouse
r_static
r_int
id|close_mouse
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
id|MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|mouse_irq
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * open access to the mouse&n; */
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
op_logical_neg
id|mouse.present
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|mouse.active
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|mouse_irq
comma
id|mouse_interrupt
comma
l_int|0
comma
l_string|&quot;busmouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|mouse.active
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|mouse.dx
op_assign
l_int|0
suffix:semicolon
id|mouse.dy
op_assign
l_int|0
suffix:semicolon
id|mouse.buttons
op_assign
l_int|0x87
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * writes are disallowed&n; */
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
multiline_comment|/*&n; * read mouse data.  Currently never blocks.&n; */
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
id|r
suffix:semicolon
r_int
id|dx
suffix:semicolon
r_int
id|dy
suffix:semicolon
r_int
r_char
id|buttons
suffix:semicolon
multiline_comment|/* long flags; */
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
(paren
id|r
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buffer
comma
id|count
)paren
)paren
)paren
r_return
id|r
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
multiline_comment|/*&n;&t; * Obtain the current mouse parameters and limit as appropriate for&n;&t; * the return data format.  Interrupts are only disabled while &n;&t; * obtaining the parameters, NOT during the puts_fs_byte() calls,&n;&t; * so paging in put_user() does not effect mouse tracking.&n;&t; */
multiline_comment|/* save_flags(flags); cli(); */
id|disable_irq
c_func
(paren
id|mouse_irq
)paren
suffix:semicolon
id|dx
op_assign
id|mouse.dx
suffix:semicolon
id|dy
op_assign
id|mouse.dy
suffix:semicolon
r_if
c_cond
(paren
id|dx
OL
op_minus
l_int|127
)paren
id|dx
op_assign
op_minus
l_int|127
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
r_if
c_cond
(paren
id|dy
OL
op_minus
l_int|127
)paren
id|dy
op_assign
op_minus
l_int|127
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
id|buttons
op_assign
id|mouse.buttons
suffix:semicolon
id|mouse.dx
op_sub_assign
id|dx
suffix:semicolon
id|mouse.dy
op_sub_assign
id|dy
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|enable_irq
c_func
(paren
id|mouse_irq
)paren
suffix:semicolon
multiline_comment|/* restore_flags(flags); */
id|put_user
c_func
(paren
id|buttons
op_or
l_int|0x80
comma
id|buffer
)paren
suffix:semicolon
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dx
comma
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
id|put_user
c_func
(paren
(paren
r_char
)paren
id|dy
comma
id|buffer
op_plus
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|3
suffix:semicolon
id|r
OL
id|count
suffix:semicolon
id|r
op_increment
)paren
id|put_user
c_func
(paren
l_int|0x00
comma
id|buffer
op_plus
id|r
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * poll for mouse input&n; */
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
DECL|variable|bus_mouse_fops
r_struct
id|file_operations
id|bus_mouse_fops
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
multiline_comment|/* mouse_poll */
l_int|NULL
comma
multiline_comment|/* mouse_ioctl */
l_int|NULL
comma
multiline_comment|/* mouse_mmap */
id|open_mouse
comma
id|close_mouse
comma
l_int|NULL
comma
id|fasync_mouse
comma
)brace
suffix:semicolon
DECL|variable|bus_mouse
r_static
r_struct
id|miscdevice
id|bus_mouse
op_assign
(brace
id|LOGITECH_BUSMOUSE
comma
l_string|&quot;busmouse&quot;
comma
op_amp
id|bus_mouse_fops
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|bus_mouse_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|LOGIBM_BASE
comma
id|LOGIBM_EXTENT
)paren
)paren
(brace
id|mouse.present
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|outb
c_func
(paren
id|MSE_CONFIG_BYTE
comma
id|MSE_CONFIG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MSE_SIGNATURE_BYTE
comma
id|MSE_SIGNATURE_PORT
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100L
)paren
suffix:semicolon
multiline_comment|/* wait for reply from mouse */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|MSE_SIGNATURE_PORT
)paren
op_ne
id|MSE_SIGNATURE_BYTE
)paren
(brace
id|mouse.present
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|outb
c_func
(paren
id|MSE_DEFAULT_MODE
comma
id|MSE_CONFIG_PORT
)paren
suffix:semicolon
id|MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|LOGIBM_BASE
comma
id|LOGIBM_EXTENT
comma
l_string|&quot;busmouse&quot;
)paren
suffix:semicolon
id|mouse.present
op_assign
l_int|1
suffix:semicolon
id|mouse.active
op_assign
l_int|0
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|mouse.buttons
op_assign
l_int|0x87
suffix:semicolon
id|mouse.dx
op_assign
l_int|0
suffix:semicolon
id|mouse.dy
op_assign
l_int|0
suffix:semicolon
id|mouse.wait
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Logitech bus mouse detected, using IRQ %d.&bslash;n&quot;
comma
id|mouse_irq
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|bus_mouse
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
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
id|bus_mouse
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|LOGIBM_BASE
comma
id|LOGIBM_EXTENT
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
