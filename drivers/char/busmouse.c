multiline_comment|/*&n; * Logitech Bus Mouse Driver for Linux&n; * by James Banks&n; *&n; * Mods by Matthew Dillon&n; *   calls verify_area()&n; *   tracks better when X is busy or paging&n; *&n; * Heavily modified by David Giller&n; *   changed from queue- to counter- driven&n; *   hacked out a (probably incorrect) mouse_select&n; *&n; * Modified again by Nathan Laredo to interface with&n; *   0.96c-pl1 IRQ handling changes (13JUL92)&n; *   didn&squot;t bother touching select code.&n; *&n; * Modified the select() code blindly to conform to the VFS&n; *   requirements. 92.07.14 - Linus. Somebody should test it out.&n; *&n; * Modified by Johan Myreen to make room for other mice (9AUG92)&n; *   removed assignment chr_fops[10] = &amp;mouse_fops; see mouse.c&n; *   renamed mouse_fops =&gt; bus_mouse_fops, made bus_mouse_fops public.&n; *   renamed this file mouse.c =&gt; busmouse.c&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/busmouse.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
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
DECL|function|bmouse_setup
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
id|unused
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
id|MSE_INT_OFF
c_func
(paren
)paren
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
)brace
id|MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * close access to the mouse (can deal with multiple&n; * opens if allowed in the future)&n; */
DECL|function|close_mouse
r_static
r_void
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
r_if
c_cond
(paren
op_decrement
id|mouse.active
op_eq
l_int|0
)paren
(brace
id|MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|mouse_irq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * open access to the mouse, currently only one open is&n; * allowed.&n; */
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
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
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
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|mouse_irq
comma
id|mouse_interrupt
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|mouse.active
op_assign
l_int|1
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
r_int
id|write_mouse
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
id|buffer
comma
r_int
id|count
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
r_int
id|read_mouse
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
id|buffer
comma
r_int
id|count
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
multiline_comment|/*&n;&t; * Obtain the current mouse parameters and limit as appropriate for&n;&t; * the return data format.  Interrupts are only disabled while &n;&t; * obtaining the parameters, NOT during the puts_fs_byte() calls,&n;&t; * so paging in put_fs_byte() does not effect mouse tracking.&n;&t; */
id|MSE_INT_OFF
c_func
(paren
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
id|MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|buttons
op_or
l_int|0x80
comma
id|buffer
)paren
suffix:semicolon
id|put_fs_byte
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
id|put_fs_byte
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
id|put_fs_byte
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
multiline_comment|/*&n; * select for mouse input, must disable the mouse interrupt while checking&n; * mouse.ready/select_wait() to avoid race condition (though in reality&n; * such a condition is not fatal to the proper operation of the mouse since&n; * multiple interrupts generally occur).&n; */
DECL|function|mouse_select
r_static
r_int
id|mouse_select
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
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sel_type
op_eq
id|SEL_IN
)paren
(brace
id|MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse.ready
)paren
(brace
id|r
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|select_wait
c_func
(paren
op_amp
id|mouse.wait
comma
id|wait
)paren
suffix:semicolon
)brace
id|MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|r
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
id|mouse_select
comma
multiline_comment|/* mouse_select */
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
)brace
suffix:semicolon
DECL|function|bus_mouse_init
r_int
r_int
id|bus_mouse_init
c_func
(paren
r_int
r_int
id|kmem_start
)paren
(brace
r_int
id|i
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* busy loop */
suffix:semicolon
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
id|kmem_start
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
l_string|&quot;Logitech Bus mouse detected and installed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
eof