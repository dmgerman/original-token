multiline_comment|/*&n; * ATI XL Bus Mouse Driver for Linux&n; * by Bob Harris (rth@sparta.com)&n; *&n; * Uses VFS interface for linux 0.98 (01OCT92)&n; *&n; * Modified by Chris Colohan (colohan@eecg.toronto.edu)&n; * Modularised 8-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt;&n; *&n; * version 0.3a&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|ATIXL_MOUSE_IRQ
mdefine_line|#define ATIXL_MOUSE_IRQ&t;&t;5 /* H/W interrupt # set up on ATIXL board */
DECL|macro|ATIXL_BUSMOUSE
mdefine_line|#define ATIXL_BUSMOUSE&t;&t;3 /* Minor device # (mknod c 10 3 /dev/bm) */
multiline_comment|/* ATI XL Inport Busmouse Definitions */
DECL|macro|ATIXL_MSE_DATA_PORT
mdefine_line|#define&t;ATIXL_MSE_DATA_PORT&t;&t;0x23d
DECL|macro|ATIXL_MSE_SIGNATURE_PORT
mdefine_line|#define&t;ATIXL_MSE_SIGNATURE_PORT&t;0x23e
DECL|macro|ATIXL_MSE_CONTROL_PORT
mdefine_line|#define&t;ATIXL_MSE_CONTROL_PORT&t;&t;0x23c
DECL|macro|ATIXL_MSE_READ_BUTTONS
mdefine_line|#define&t;ATIXL_MSE_READ_BUTTONS&t;&t;0x00
DECL|macro|ATIXL_MSE_READ_X
mdefine_line|#define&t;ATIXL_MSE_READ_X&t;&t;0x01
DECL|macro|ATIXL_MSE_READ_Y
mdefine_line|#define&t;ATIXL_MSE_READ_Y&t;&t;0x02
multiline_comment|/* Some nice ATI XL macros */
multiline_comment|/* Select IR7, HOLD UPDATES (INT ENABLED), save X,Y */
DECL|macro|ATIXL_MSE_DISABLE_UPDATE
mdefine_line|#define ATIXL_MSE_DISABLE_UPDATE() { outb( 0x07, ATIXL_MSE_CONTROL_PORT ); &bslash;&n;&t;outb( (0x20 | inb( ATIXL_MSE_DATA_PORT )), ATIXL_MSE_DATA_PORT ); }
multiline_comment|/* Select IR7, Enable updates (INT ENABLED) */
DECL|macro|ATIXL_MSE_ENABLE_UPDATE
mdefine_line|#define ATIXL_MSE_ENABLE_UPDATE() { outb( 0x07, ATIXL_MSE_CONTROL_PORT ); &bslash;&n;&t; outb( (0xdf &amp; inb( ATIXL_MSE_DATA_PORT )), ATIXL_MSE_DATA_PORT ); }
multiline_comment|/* Select IR7 - Mode Register, NO INTERRUPTS */
DECL|macro|ATIXL_MSE_INT_OFF
mdefine_line|#define ATIXL_MSE_INT_OFF() { outb( 0x07, ATIXL_MSE_CONTROL_PORT ); &bslash;&n;&t;outb( (0xe7 &amp; inb( ATIXL_MSE_DATA_PORT )), ATIXL_MSE_DATA_PORT ); }
multiline_comment|/* Select IR7 - Mode Register, DATA INTERRUPTS ENABLED */
DECL|macro|ATIXL_MSE_INT_ON
mdefine_line|#define ATIXL_MSE_INT_ON() { outb( 0x07, ATIXL_MSE_CONTROL_PORT ); &bslash;&n;&t;outb( (0x08 | inb( ATIXL_MSE_DATA_PORT )), ATIXL_MSE_DATA_PORT ); }
multiline_comment|/* Same general mouse structure */
DECL|struct|mouse_status
r_static
r_struct
id|mouse_status
(brace
DECL|member|buttons
r_char
id|buttons
suffix:semicolon
DECL|member|latch_buttons
r_char
id|latch_buttons
suffix:semicolon
DECL|member|dx
r_int
id|dx
suffix:semicolon
DECL|member|dy
r_int
id|dy
suffix:semicolon
DECL|member|present
r_int
id|present
suffix:semicolon
DECL|member|ready
r_int
id|ready
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|variable|mouse
)brace
id|mouse
suffix:semicolon
DECL|function|mouse_interrupt
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
comma
id|buttons
suffix:semicolon
id|ATIXL_MSE_DISABLE_UPDATE
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Note that interrupts are still enabled */
id|outb
c_func
(paren
id|ATIXL_MSE_READ_X
comma
id|ATIXL_MSE_CONTROL_PORT
)paren
suffix:semicolon
multiline_comment|/* Select IR1 - X movement */
id|dx
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ATIXL_MSE_READ_Y
comma
id|ATIXL_MSE_CONTROL_PORT
)paren
suffix:semicolon
multiline_comment|/* Select IR2 - Y movement */
id|dy
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_DATA_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ATIXL_MSE_READ_BUTTONS
comma
id|ATIXL_MSE_CONTROL_PORT
)paren
suffix:semicolon
multiline_comment|/* Select IR0 - Button Status */
id|buttons
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_DATA_PORT
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
id|mouse.latch_buttons
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
id|mouse.fasync
)paren
id|kill_fasync
c_func
(paren
id|mouse.fasync
comma
id|SIGIO
)paren
suffix:semicolon
)brace
id|ATIXL_MSE_ENABLE_UPDATE
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
id|inode
op_star
id|inode
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
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|inode
comma
id|filp
comma
id|on
comma
op_amp
id|mouse.fasync
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
id|fasync_mouse
c_func
(paren
id|inode
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
id|mouse.active
)paren
r_return
suffix:semicolon
id|ATIXL_MSE_INT_OFF
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Interrupts are really shut down here */
id|mouse.ready
op_assign
l_int|0
suffix:semicolon
id|free_irq
c_func
(paren
id|ATIXL_MOUSE_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
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
id|ATIXL_MOUSE_IRQ
comma
id|mouse_interrupt
comma
l_int|0
comma
l_string|&quot;ATIXL mouse&quot;
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
id|mouse.latch_buttons
op_assign
l_int|0
suffix:semicolon
id|ATIXL_MSE_INT_ON
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Interrupts are really enabled here */
id|MOD_INC_USE_COUNT
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
r_const
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
id|ATIXL_MSE_DISABLE_UPDATE
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Allowed interrupts to occur during data gathering - shouldn&squot;t hurt */
id|put_user
c_func
(paren
(paren
r_char
)paren
(paren
op_complement
id|mouse.latch_buttons
op_amp
l_int|7
)paren
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
id|put_user
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
id|put_user
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
(brace
id|put_user
c_func
(paren
l_int|0x00
comma
id|buffer
op_plus
id|i
)paren
suffix:semicolon
)brace
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
id|ATIXL_MSE_ENABLE_UPDATE
c_func
(paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
multiline_comment|/* i data bytes returned */
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
DECL|variable|atixl_busmouse_fops
r_struct
id|file_operations
id|atixl_busmouse_fops
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
l_int|NULL
comma
id|fasync_mouse
comma
)brace
suffix:semicolon
DECL|variable|atixl_mouse
r_static
r_struct
id|miscdevice
id|atixl_mouse
op_assign
(brace
id|ATIXL_BUSMOUSE
comma
l_string|&quot;atixl&quot;
comma
op_amp
id|atixl_busmouse_fops
)brace
suffix:semicolon
DECL|function|atixl_busmouse_init
r_int
id|atixl_busmouse_init
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|a
comma
id|b
comma
id|c
suffix:semicolon
id|a
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_SIGNATURE_PORT
)paren
suffix:semicolon
multiline_comment|/* Get signature */
id|b
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_SIGNATURE_PORT
)paren
suffix:semicolon
id|c
op_assign
id|inb
c_func
(paren
id|ATIXL_MSE_SIGNATURE_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_ne
id|b
)paren
op_logical_and
(paren
id|a
op_eq
id|c
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nATI Inport &quot;
)paren
suffix:semicolon
r_else
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
l_int|0x80
comma
id|ATIXL_MSE_CONTROL_PORT
)paren
suffix:semicolon
multiline_comment|/* Reset the Inport device */
id|outb
c_func
(paren
l_int|0x07
comma
id|ATIXL_MSE_CONTROL_PORT
)paren
suffix:semicolon
multiline_comment|/* Select Internal Register 7 */
id|outb
c_func
(paren
l_int|0x0a
comma
id|ATIXL_MSE_DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Data Interrupts 8+, 1=30hz, 2=50hz, 3=100hz, 4=200hz rate */
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
id|mouse.latch_buttons
op_assign
l_int|0
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
id|printk
c_func
(paren
l_string|&quot;Bus mouse detected and installed.&bslash;n&quot;
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|atixl_mouse
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
id|atixl_busmouse_init
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
id|atixl_mouse
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
