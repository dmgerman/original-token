multiline_comment|/*&n; * Microsoft busmouse driver based on Logitech driver (see busmouse.c)&n; *&n; * Microsoft BusMouse support by Teemu Rantanen (tvr@cs.hut.fi) (02AUG92)&n; *&n; * Microsoft Bus Mouse support modified by Derrick Cole (cole@concert.net)&n; *    8/28/92&n; *&n; * Microsoft Bus Mouse support folded into 0.97pl4 code&n; *    by Peter Cervasio (pete%q106fm.uucp@wupost.wustl.edu) (08SEP92)&n; * Changes:  Logitech and Microsoft support in the same kernel.&n; *           Defined new constants in busmouse.h for MS mice.&n; *           Added int mse_busmouse_type to distinguish busmouse types&n; *           Added a couple of new functions to handle differences in using&n; *             MS vs. Logitech (where the int variable wasn&squot;t appropriate).&n; *&n; * Modified by Peter Cervasio (address above) (26SEP92)&n; * Changes:  Included code to (properly?) detect when a Microsoft mouse is&n; *           really attached to the machine.  Don&squot;t know what this does to&n; *           Logitech bus mice, but all it does is read ports.&n; *&n; * version 0.3&n; */
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
DECL|function|ms_mouse_interrupt
r_static
r_void
id|ms_mouse_interrupt
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
comma
id|buttons
suffix:semicolon
id|outb
c_func
(paren
id|MS_MSE_COMMAND_MODE
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|MS_MSE_DATA_PORT
)paren
op_or
l_int|0x20
)paren
comma
id|MS_MSE_DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MS_MSE_READ_X
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|dx
op_assign
id|inb
c_func
(paren
id|MS_MSE_DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MS_MSE_READ_Y
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|dy
op_assign
id|inb
c_func
(paren
id|MS_MSE_DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MS_MSE_READ_BUTTONS
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|buttons
op_assign
op_complement
(paren
id|inb
c_func
(paren
id|MS_MSE_DATA_PORT
)paren
)paren
op_amp
l_int|0x07
suffix:semicolon
id|outb
c_func
(paren
id|MS_MSE_COMMAND_MODE
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|MS_MSE_DATA_PORT
)paren
op_amp
l_int|0xdf
)paren
comma
id|MS_MSE_DATA_PORT
)paren
suffix:semicolon
id|mouse.buttons
op_assign
id|buttons
suffix:semicolon
id|mouse.latch_buttons
op_or_assign
id|buttons
suffix:semicolon
id|mouse.dx
op_add_assign
id|dx
suffix:semicolon
id|mouse.dy
op_add_assign
id|dy
suffix:semicolon
id|mouse.ready
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mouse.wait
)paren
suffix:semicolon
)brace
DECL|function|release_mouse
r_static
r_void
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
id|MS_MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
id|mouse.active
op_assign
l_int|0
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|free_irq
c_func
(paren
id|MOUSE_IRQ
)paren
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
id|mouse.active
op_assign
l_int|1
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
id|mouse.latch_buttons
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|MOUSE_IRQ
comma
id|ms_mouse_interrupt
)paren
)paren
(brace
id|mouse.active
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb
c_func
(paren
id|MS_MSE_START
comma
id|MS_MSE_CONTROL_PORT
)paren
suffix:semicolon
id|MS_MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|i
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
id|put_fs_byte
c_func
(paren
id|mouse.latch_buttons
op_or
l_int|0x80
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dx
OL
op_minus
l_int|127
)paren
id|mouse.dx
op_assign
op_minus
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dx
OG
l_int|127
)paren
id|mouse.dx
op_assign
l_int|127
suffix:semicolon
id|put_fs_byte
c_func
(paren
(paren
r_char
)paren
id|mouse.dx
comma
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dy
OL
op_minus
l_int|127
)paren
id|mouse.dy
op_assign
op_minus
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|mouse.dy
OG
l_int|127
)paren
id|mouse.dy
op_assign
l_int|127
suffix:semicolon
id|put_fs_byte
c_func
(paren
(paren
r_char
)paren
op_minus
id|mouse.dy
comma
id|buffer
op_plus
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
id|put_fs_byte
c_func
(paren
l_int|0x00
comma
id|buffer
op_plus
id|i
)paren
suffix:semicolon
id|mouse.dx
op_assign
l_int|0
suffix:semicolon
id|mouse.dy
op_assign
l_int|0
suffix:semicolon
id|mouse.latch_buttons
op_assign
id|mouse.buttons
suffix:semicolon
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|sel_type
op_ne
id|SEL_IN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mouse.ready
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
c_func
(paren
op_amp
id|mouse.wait
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ms_bus_mouse_fops
r_struct
id|file_operations
id|ms_bus_mouse_fops
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
id|release_mouse
comma
)brace
suffix:semicolon
DECL|macro|MS_DELAY
mdefine_line|#define MS_DELAY 100000
DECL|function|ms_bus_mouse_init
r_int
r_int
id|ms_bus_mouse_init
c_func
(paren
r_int
r_int
id|kmem_start
)paren
(brace
r_register
r_int
id|mse_byte
suffix:semicolon
r_int
id|i
comma
id|delay_val
comma
id|msfound
op_assign
l_int|1
suffix:semicolon
id|mouse.present
op_assign
l_int|0
suffix:semicolon
id|mouse.active
op_assign
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|mouse.buttons
op_assign
id|mouse.latch_buttons
op_assign
l_int|0x80
suffix:semicolon
id|mouse.dx
op_assign
id|mouse.dy
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
id|inb
c_func
(paren
id|MS_MSE_SIGNATURE_PORT
)paren
op_eq
l_int|0xde
)paren
(brace
r_for
c_loop
(paren
id|delay_val
op_assign
l_int|0
suffix:semicolon
id|delay_val
OL
id|MS_DELAY
suffix:semicolon
)paren
id|delay_val
op_increment
suffix:semicolon
id|mse_byte
op_assign
id|inb
c_func
(paren
id|MS_MSE_SIGNATURE_PORT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|delay_val
op_assign
l_int|0
suffix:semicolon
id|delay_val
OL
id|MS_DELAY
suffix:semicolon
)paren
id|delay_val
op_increment
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|delay_val
op_assign
l_int|0
suffix:semicolon
id|delay_val
OL
id|MS_DELAY
suffix:semicolon
)paren
id|delay_val
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|MS_MSE_SIGNATURE_PORT
)paren
op_eq
l_int|0xde
)paren
(brace
r_for
c_loop
(paren
id|delay_val
op_assign
l_int|0
suffix:semicolon
id|delay_val
OL
id|MS_DELAY
suffix:semicolon
)paren
id|delay_val
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|MS_MSE_SIGNATURE_PORT
)paren
op_eq
id|mse_byte
)paren
id|msfound
op_assign
l_int|0
suffix:semicolon
r_else
id|msfound
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|msfound
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|msfound
op_eq
l_int|1
)paren
(brace
r_return
id|kmem_start
suffix:semicolon
)brace
id|MS_MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
id|mouse.present
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Microsoft Bus mouse detected and installed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
eof
