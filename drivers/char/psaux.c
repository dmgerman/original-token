multiline_comment|/*&n; * linux/drivers/char/psaux.c&n; *&n; * Driver for PS/2 type mouse by Johan Myreen.&n; *&n; * Supports pointing devices attached to a PS/2 type&n; * Keyboard and Auxiliary Device Controller.&n; *&n; * Corrections in device setup for some laptop mice &amp; trackballs.&n; * 02Feb93  (troyer@saifr00.cfsat.Honeywell.COM,mch@wimsey.bc.ca)&n; *&n; * Changed to prevent keyboard lockups on AST Power Exec.&n; * 28Jul93  Brad Bosch - brad@lachman.com&n; *&n; * Modified by Johan Myreen (jem@pandora.pp.fi) 04Aug93&n; *   to include support for QuickPort mouse.&n; *&n; * Changed references to &quot;QuickPort&quot; with &quot;82C710&quot; since &quot;QuickPort&quot;&n; * is not what this driver is all about -- QuickPort is just a&n; * connector type, and this driver is for the mouse port on the Chips&n; * &amp; Technologies 82C710 interface chip. 15Nov93 jem@pandora.pp.fi&n; *&n; * Added support for SIGIO. 28Jul95 jem@pandora.pp.fi&n; *&n; * Rearranged SIGIO support to use code from tty_io.  9Sept95 ctm@ardi.com&n; *&n; * Modularised 8-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt;&n; */
multiline_comment|/* Uncomment the following line if your mouse needs initialization. */
multiline_comment|/* #define INITIALIZE_DEVICE */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PSMOUSE_MINOR
mdefine_line|#define PSMOUSE_MINOR      1            /* minor device # for this mouse */
multiline_comment|/* aux controller ports */
DECL|macro|AUX_INPUT_PORT
mdefine_line|#define AUX_INPUT_PORT&t;0x60&t;&t;/* Aux device output buffer */
DECL|macro|AUX_OUTPUT_PORT
mdefine_line|#define AUX_OUTPUT_PORT&t;0x60&t;&t;/* Aux device input buffer */
DECL|macro|AUX_COMMAND
mdefine_line|#define AUX_COMMAND&t;0x64&t;&t;/* Aux device command buffer */
DECL|macro|AUX_STATUS
mdefine_line|#define AUX_STATUS&t;0x64&t;&t;/* Aux device status reg */
multiline_comment|/* aux controller status bits */
DECL|macro|AUX_OBUF_FULL
mdefine_line|#define AUX_OBUF_FULL&t;0x21&t;&t;/* output buffer (from device) full */
DECL|macro|AUX_IBUF_FULL
mdefine_line|#define AUX_IBUF_FULL&t;0x02&t;&t;/* input buffer (to device) full */
multiline_comment|/* aux controller commands */
DECL|macro|AUX_CMD_WRITE
mdefine_line|#define AUX_CMD_WRITE&t;0x60&t;&t;/* value to write to controller */
DECL|macro|AUX_MAGIC_WRITE
mdefine_line|#define AUX_MAGIC_WRITE&t;0xd4&t;&t;/* value to send aux device data */
DECL|macro|AUX_INTS_ON
mdefine_line|#define AUX_INTS_ON&t;0x47&t;&t;/* enable controller interrupts */
DECL|macro|AUX_INTS_OFF
mdefine_line|#define AUX_INTS_OFF&t;0x65&t;&t;/* disable controller interrupts */
DECL|macro|AUX_DISABLE
mdefine_line|#define AUX_DISABLE&t;0xa7&t;&t;/* disable aux */
DECL|macro|AUX_ENABLE
mdefine_line|#define AUX_ENABLE&t;0xa8&t;&t;/* enable aux */
multiline_comment|/* aux device commands */
DECL|macro|AUX_SET_RES
mdefine_line|#define AUX_SET_RES&t;0xe8&t;&t;/* set resolution */
DECL|macro|AUX_SET_SCALE11
mdefine_line|#define AUX_SET_SCALE11&t;0xe6&t;&t;/* set 1:1 scaling */
DECL|macro|AUX_SET_SCALE21
mdefine_line|#define AUX_SET_SCALE21&t;0xe7&t;&t;/* set 2:1 scaling */
DECL|macro|AUX_GET_SCALE
mdefine_line|#define AUX_GET_SCALE&t;0xe9&t;&t;/* get scaling factor */
DECL|macro|AUX_SET_STREAM
mdefine_line|#define AUX_SET_STREAM&t;0xea&t;&t;/* set stream mode */
DECL|macro|AUX_SET_SAMPLE
mdefine_line|#define AUX_SET_SAMPLE&t;0xf3&t;&t;/* set sample rate */
DECL|macro|AUX_ENABLE_DEV
mdefine_line|#define AUX_ENABLE_DEV&t;0xf4&t;&t;/* enable aux device */
DECL|macro|AUX_DISABLE_DEV
mdefine_line|#define AUX_DISABLE_DEV&t;0xf5&t;&t;/* disable aux device */
DECL|macro|AUX_RESET
mdefine_line|#define AUX_RESET&t;0xff&t;&t;/* reset aux device */
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES&t;60&t;&t;/* some aux operations take long time*/
macro_line|#if defined(__alpha__) &amp;&amp; !defined(CONFIG_PCI)
DECL|macro|AUX_IRQ
macro_line|# define AUX_IRQ&t;9&t;&t;/* Jensen is odd indeed */
macro_line|#else
DECL|macro|AUX_IRQ
macro_line|# define AUX_IRQ&t;12
macro_line|#endif
DECL|macro|AUX_BUF_SIZE
mdefine_line|#define AUX_BUF_SIZE&t;2048
multiline_comment|/* 82C710 definitions */
DECL|macro|QP_DATA
mdefine_line|#define QP_DATA         0x310&t;&t;/* Data Port I/O Address */
DECL|macro|QP_STATUS
mdefine_line|#define QP_STATUS       0x311&t;&t;/* Status Port I/O Address */
DECL|macro|QP_DEV_IDLE
mdefine_line|#define QP_DEV_IDLE     0x01&t;&t;/* Device Idle */
DECL|macro|QP_RX_FULL
mdefine_line|#define QP_RX_FULL      0x02&t;&t;/* Device Char received */
DECL|macro|QP_TX_IDLE
mdefine_line|#define QP_TX_IDLE      0x04&t;&t;/* Device XMIT Idle */
DECL|macro|QP_RESET
mdefine_line|#define QP_RESET        0x08&t;&t;/* Device Reset */
DECL|macro|QP_INTS_ON
mdefine_line|#define QP_INTS_ON      0x10&t;&t;/* Device Interrupt On */
DECL|macro|QP_ERROR_FLAG
mdefine_line|#define QP_ERROR_FLAG   0x20&t;&t;/* Device Error */
DECL|macro|QP_CLEAR
mdefine_line|#define QP_CLEAR        0x40&t;&t;/* Device Clear */
DECL|macro|QP_ENABLE
mdefine_line|#define QP_ENABLE       0x80&t;&t;/* Device Enable */
DECL|macro|QP_IRQ
mdefine_line|#define QP_IRQ          12
r_extern
r_int
r_char
id|aux_device_present
suffix:semicolon
r_extern
r_int
r_char
id|kbd_read_mask
suffix:semicolon
multiline_comment|/* from keyboard.c */
DECL|struct|aux_queue
r_struct
id|aux_queue
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|proc_list
r_struct
id|wait_queue
op_star
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|AUX_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|queue
r_static
r_struct
id|aux_queue
op_star
id|queue
suffix:semicolon
DECL|variable|aux_ready
r_static
r_int
id|aux_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|aux_count
r_static
r_int
id|aux_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|aux_present
r_static
r_int
id|aux_present
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|poll_aux_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|poll_aux_status_nosleep
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|fasync_aux
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
suffix:semicolon
macro_line|#ifdef CONFIG_82C710_MOUSE
DECL|variable|qp_present
r_static
r_int
id|qp_present
op_assign
l_int|0
suffix:semicolon
DECL|variable|qp_count
r_static
r_int
id|qp_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|qp_data
r_static
r_int
id|qp_data
op_assign
id|QP_DATA
suffix:semicolon
DECL|variable|qp_status
r_static
r_int
id|qp_status
op_assign
id|QP_STATUS
suffix:semicolon
r_static
r_int
id|poll_qp_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|probe_qp
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Write to aux device&n; */
DECL|function|aux_write_dev
r_static
r_void
id|aux_write_dev
c_func
(paren
r_int
id|val
)paren
(brace
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_MAGIC_WRITE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
multiline_comment|/* write magic cookie */
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|AUX_OUTPUT_PORT
)paren
suffix:semicolon
multiline_comment|/* write data */
)brace
multiline_comment|/*&n; * Write to device &amp; handle returned ack&n; */
macro_line|#if defined INITIALIZE_DEVICE
DECL|function|aux_write_ack
r_static
r_int
id|aux_write_ack
c_func
(paren
r_int
id|val
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_MAGIC_WRITE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|AUX_OUTPUT_PORT
)paren
suffix:semicolon
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|AUX_STATUS
)paren
op_amp
id|AUX_OBUF_FULL
)paren
op_eq
id|AUX_OBUF_FULL
)paren
(brace
r_return
(paren
id|inb
c_func
(paren
id|AUX_INPUT_PORT
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* INITIALIZE_DEVICE */
multiline_comment|/*&n; * Write aux device command&n; */
DECL|function|aux_write_cmd
r_static
r_void
id|aux_write_cmd
c_func
(paren
r_int
id|val
)paren
(brace
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_CMD_WRITE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|AUX_OUTPUT_PORT
)paren
suffix:semicolon
)brace
DECL|function|get_from_queue
r_static
r_int
r_int
id|get_from_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|queue-&gt;buf
(braket
id|queue-&gt;tail
)braket
suffix:semicolon
id|queue-&gt;tail
op_assign
(paren
id|queue-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|queue_empty
r_static
r_inline
r_int
id|queue_empty
c_func
(paren
r_void
)paren
(brace
r_return
id|queue-&gt;head
op_eq
id|queue-&gt;tail
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupt from the auxiliary device: a character&n; * is waiting in the keyboard/aux controller.&n; */
DECL|function|aux_interrupt
r_static
r_void
id|aux_interrupt
c_func
(paren
r_int
id|cpl
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
r_int
id|head
op_assign
id|queue-&gt;head
suffix:semicolon
r_int
id|maxhead
op_assign
(paren
id|queue-&gt;tail
op_minus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|AUX_STATUS
)paren
op_amp
id|AUX_OBUF_FULL
)paren
op_ne
id|AUX_OBUF_FULL
)paren
r_return
suffix:semicolon
id|add_mouse_randomness
c_func
(paren
id|queue-&gt;buf
(braket
id|head
)braket
op_assign
id|inb
c_func
(paren
id|AUX_INPUT_PORT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|maxhead
)paren
(brace
id|head
op_increment
suffix:semicolon
id|head
op_and_assign
id|AUX_BUF_SIZE
op_minus
l_int|1
suffix:semicolon
)brace
id|queue-&gt;head
op_assign
id|head
suffix:semicolon
id|aux_ready
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;fasync
)paren
id|kill_fasync
c_func
(paren
id|queue-&gt;fasync
comma
id|SIGIO
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupt handler for the 82C710 mouse port. A character&n; * is waiting in the 82C710.&n; */
macro_line|#ifdef CONFIG_82C710_MOUSE
DECL|function|qp_interrupt
r_static
r_void
id|qp_interrupt
c_func
(paren
r_int
id|cpl
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
r_int
id|head
op_assign
id|queue-&gt;head
suffix:semicolon
r_int
id|maxhead
op_assign
(paren
id|queue-&gt;tail
op_minus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|add_mouse_randomness
c_func
(paren
id|queue-&gt;buf
(braket
id|head
)braket
op_assign
id|inb
c_func
(paren
id|qp_data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|maxhead
)paren
(brace
id|head
op_increment
suffix:semicolon
id|head
op_and_assign
id|AUX_BUF_SIZE
op_minus
l_int|1
suffix:semicolon
)brace
id|queue-&gt;head
op_assign
id|head
suffix:semicolon
id|aux_ready
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;fasync
)paren
id|kill_fasync
c_func
(paren
id|queue-&gt;fasync
comma
id|SIGIO
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|release_aux
r_static
r_void
id|release_aux
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
id|fasync_aux
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
id|aux_count
)paren
r_return
suffix:semicolon
id|aux_write_cmd
c_func
(paren
id|AUX_INTS_OFF
)paren
suffix:semicolon
multiline_comment|/* disable controller ints */
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_DISABLE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Disable Aux device */
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|AUX_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_82C710_MOUSE
DECL|function|release_qp
r_static
r_void
id|release_qp
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
r_int
r_char
id|status
suffix:semicolon
id|fasync_aux
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
id|qp_count
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: Mouse device busy in release_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|inb_p
c_func
(paren
id|qp_status
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
op_amp
op_complement
(paren
id|QP_ENABLE
op_or
id|QP_INTS_ON
)paren
comma
id|qp_status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: Mouse device busy in release_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|QP_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fasync_aux
r_static
r_int
id|fasync_aux
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
id|queue-&gt;fasync
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
multiline_comment|/*&n; * Install interrupt handler.&n; * Enable auxiliary device.&n; */
DECL|function|open_aux
r_static
r_int
id|open_aux
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
id|aux_present
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|aux_count
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_aux_status
c_func
(paren
)paren
)paren
(brace
id|aux_count
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|AUX_IRQ
comma
id|aux_interrupt
comma
l_int|0
comma
l_string|&quot;PS/2 Mouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|aux_count
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_ENABLE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Enable Aux */
id|aux_write_dev
c_func
(paren
id|AUX_ENABLE_DEV
)paren
suffix:semicolon
multiline_comment|/* enable aux device */
id|aux_write_cmd
c_func
(paren
id|AUX_INTS_ON
)paren
suffix:semicolon
multiline_comment|/* enable controller ints */
id|poll_aux_status
c_func
(paren
)paren
suffix:semicolon
id|aux_ready
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_82C710_MOUSE
multiline_comment|/*&n; * Install interrupt handler.&n; * Enable the device, enable interrupts. &n; */
DECL|function|open_qp
r_static
r_int
id|open_qp
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
r_int
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qp_present
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|qp_count
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
id|QP_IRQ
comma
id|qp_interrupt
comma
l_int|0
comma
l_string|&quot;PS/2 Mouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|qp_count
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|status
op_assign
id|inb_p
c_func
(paren
id|qp_status
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|QP_ENABLE
op_or
id|QP_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|QP_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
id|status
op_or_assign
id|QP_INTS_ON
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts */
r_while
c_loop
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error: Mouse device busy in open_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|qp_count
op_decrement
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|QP_ENABLE
op_or
id|QP_INTS_ON
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|QP_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|AUX_ENABLE_DEV
comma
id|qp_data
)paren
suffix:semicolon
multiline_comment|/* Wake up mouse */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Write to the aux device.&n; */
DECL|function|write_aux
r_static
r_int
id|write_aux
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
r_int
id|i
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|poll_aux_status
c_func
(paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_MAGIC_WRITE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_aux_status
c_func
(paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|outb_p
c_func
(paren
id|get_user
c_func
(paren
id|buffer
op_increment
)paren
comma
id|AUX_OUTPUT_PORT
)paren
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_82C710_MOUSE
multiline_comment|/*&n; * Write to the 82C710 mouse device.&n; */
DECL|function|write_qp
r_static
r_int
id|write_qp
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
r_int
id|i
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|outb_p
c_func
(paren
id|get_user
c_func
(paren
id|buffer
op_increment
)paren
comma
id|qp_data
)paren
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Put bytes from input queue to buffer.&n; */
DECL|function|read_aux
r_static
r_int
id|read_aux
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
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|i
op_assign
id|count
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
)paren
(brace
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
id|add_wait_queue
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
op_logical_and
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
)paren
(brace
id|schedule
c_func
(paren
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
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|queue_empty
c_func
(paren
)paren
)paren
(brace
id|c
op_assign
id|get_from_queue
c_func
(paren
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
id|aux_ready
op_assign
op_logical_neg
id|queue_empty
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_minus
id|i
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
op_minus
id|i
suffix:semicolon
)brace
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
DECL|function|aux_select
r_static
r_int
id|aux_select
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
id|aux_ready
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|psaux_fops
r_struct
id|file_operations
id|psaux_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* seek */
id|read_aux
comma
id|write_aux
comma
l_int|NULL
comma
multiline_comment|/* readdir */
id|aux_select
comma
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|open_aux
comma
id|release_aux
comma
l_int|NULL
comma
id|fasync_aux
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize driver. First check for a 82C710 chip; if found&n; * forget about the Aux port and use the *_qp functions.&n; */
DECL|variable|psaux_mouse
r_static
r_struct
id|miscdevice
id|psaux_mouse
op_assign
(brace
id|PSMOUSE_MINOR
comma
l_string|&quot;ps2aux&quot;
comma
op_amp
id|psaux_fops
)brace
suffix:semicolon
DECL|function|psaux_init
r_int
id|psaux_init
c_func
(paren
r_void
)paren
(brace
r_int
id|qp_found
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_82C710_MOUSE
r_if
c_cond
(paren
(paren
id|qp_found
op_assign
id|probe_qp
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;82C710 type pointing device detected -- driver installed.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&t;&t;printk(&quot;82C710 address = %x (should be 0x310)&bslash;n&quot;, qp_data); */
id|qp_present
op_assign
l_int|1
suffix:semicolon
id|psaux_fops.write
op_assign
id|write_qp
suffix:semicolon
id|psaux_fops.open
op_assign
id|open_qp
suffix:semicolon
id|psaux_fops.release
op_assign
id|release_qp
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|aux_device_present
op_eq
l_int|0xaa
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PS/2 auxiliary pointing device detected -- driver installed.&bslash;n&quot;
)paren
suffix:semicolon
id|aux_present
op_assign
l_int|1
suffix:semicolon
id|kbd_read_mask
op_assign
id|AUX_OBUF_FULL
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|misc_register
c_func
(paren
op_amp
id|psaux_mouse
)paren
suffix:semicolon
id|queue
op_assign
(paren
r_struct
id|aux_queue
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|queue
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|queue
)paren
)paren
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
id|queue-&gt;proc_list
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qp_found
)paren
(brace
macro_line|#if defined INITIALIZE_DEVICE
id|outb_p
c_func
(paren
id|AUX_ENABLE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Enable Aux */
id|aux_write_ack
c_func
(paren
id|AUX_SET_SAMPLE
)paren
suffix:semicolon
id|aux_write_ack
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* 100 samples/sec */
id|aux_write_ack
c_func
(paren
id|AUX_SET_RES
)paren
suffix:semicolon
id|aux_write_ack
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* 8 counts per mm */
id|aux_write_ack
c_func
(paren
id|AUX_SET_SCALE21
)paren
suffix:semicolon
multiline_comment|/* 2:1 scaling */
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* INITIALIZE_DEVICE */
id|outb_p
c_func
(paren
id|AUX_DISABLE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Disable Aux device */
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|AUX_CMD_WRITE
comma
id|AUX_COMMAND
)paren
suffix:semicolon
id|poll_aux_status_nosleep
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts */
id|outb_p
c_func
(paren
id|AUX_INTS_OFF
comma
id|AUX_OUTPUT_PORT
)paren
suffix:semicolon
multiline_comment|/*  on the controller */
)brace
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
id|psaux_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*?? Bjorn */
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
id|psaux_mouse
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|poll_aux_status
r_static
r_int
id|poll_aux_status
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|AUX_STATUS
)paren
op_amp
l_int|0x03
)paren
op_logical_and
id|retries
OL
id|MAX_RETRIES
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|AUX_STATUS
)paren
op_amp
id|AUX_OBUF_FULL
)paren
op_eq
id|AUX_OBUF_FULL
)paren
id|inb_p
c_func
(paren
id|AUX_INPUT_PORT
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
(paren
l_int|5
op_star
id|HZ
op_plus
l_int|99
)paren
op_div
l_int|100
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|retries
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
(paren
id|retries
op_eq
id|MAX_RETRIES
)paren
suffix:semicolon
)brace
DECL|function|poll_aux_status_nosleep
r_static
r_int
id|poll_aux_status_nosleep
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|AUX_STATUS
)paren
op_amp
l_int|0x03
)paren
op_logical_and
id|retries
OL
l_int|1000000
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|AUX_STATUS
)paren
op_amp
id|AUX_OBUF_FULL
)paren
op_eq
id|AUX_OBUF_FULL
)paren
id|inb_p
c_func
(paren
id|AUX_INPUT_PORT
)paren
suffix:semicolon
id|retries
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
(paren
id|retries
op_eq
l_int|1000000
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_82C710_MOUSE
multiline_comment|/*&n; * Wait for device to send output char and flush any input char.&n; */
DECL|function|poll_qp_status
r_static
r_int
id|poll_qp_status
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|qp_status
)paren
op_amp
(paren
id|QP_RX_FULL
op_or
id|QP_TX_IDLE
op_or
id|QP_DEV_IDLE
)paren
)paren
op_ne
(paren
id|QP_DEV_IDLE
op_or
id|QP_TX_IDLE
)paren
op_logical_and
id|retries
OL
id|MAX_RETRIES
)paren
(brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|qp_status
)paren
op_amp
(paren
id|QP_RX_FULL
)paren
)paren
id|inb_p
c_func
(paren
id|qp_data
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
(paren
l_int|5
op_star
id|HZ
op_plus
l_int|99
)paren
op_div
l_int|100
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|retries
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
(paren
id|retries
op_eq
id|MAX_RETRIES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function to read register in 82C710.&n; */
DECL|function|read_710
r_static
r_inline
r_int
r_char
id|read_710
c_func
(paren
r_int
r_char
id|index
)paren
(brace
id|outb_p
c_func
(paren
id|index
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Write index */
r_return
id|inb_p
c_func
(paren
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* Read the data */
)brace
multiline_comment|/*&n; * See if we can find a 82C710 device. Read mouse address.&n; */
DECL|function|probe_qp
r_static
r_int
id|probe_qp
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x55
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Any value except 9, ff or 36 */
id|outb_p
c_func
(paren
l_int|0xaa
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of 55 */
id|outb_p
c_func
(paren
l_int|0x36
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Address the chip */
id|outb_p
c_func
(paren
l_int|0xe4
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* 390/4; 390 = config address */
id|outb_p
c_func
(paren
l_int|0x1b
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of e4 */
r_if
c_cond
(paren
id|read_710
c_func
(paren
l_int|0x0f
)paren
op_ne
l_int|0xe4
)paren
multiline_comment|/* Config address found? */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No: no 82C710 here */
id|qp_data
op_assign
id|read_710
c_func
(paren
l_int|0x0d
)paren
op_star
l_int|4
suffix:semicolon
multiline_comment|/* Get mouse I/O address */
id|qp_status
op_assign
id|qp_data
op_plus
l_int|1
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x390
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* Close config mode */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
