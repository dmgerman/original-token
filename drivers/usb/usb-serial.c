multiline_comment|/*&n; * USB Serial Converter driver&n; *&n; * Greg Kroah-Hartman (greg@kroah.com)&n; *&n; * This was based on the ACM driver by Armin Fuerst (which was based&n; * on a driver by Brad Keryan)&n; *&n; * Currently only works for the Belkin and Peracom Serial converters.&n; * Should also work on the Etek serial converter, if anyone knows the&n; * vendor and device ids for that device.&n; *&n; * &n; * version 0.1.2 (10/25/99) gkh&n; *  Fixed bug in detecting device.&n; *&n; * version 0.1.1 (10/05/99) gkh&n; *  Changed the major number to not conflict with anything else.&n; *&n; * version 0.1 (09/28/99) gkh&n; *  Can recognize the two different devices and start up a read from&n; * device when asked to. Writes also work. No control signals yet, this&n; * all is vendor specific data (i.e. no spec), also no control for&n; * different baud rates or other bit settings.&n; * Currently we are using the same devid as the acm driver. This needs&n; * to change.&n; * &n; * (C) Copyright 1999 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;usb.h&quot;
multiline_comment|/*#define SERIAL_DEBUG 1*/
macro_line|#ifdef SERIAL_DEBUG
DECL|macro|debug_info
mdefine_line|#define debug_info(message); printk(message);
macro_line|#else
DECL|macro|debug_info
mdefine_line|#define debug_info(message);
macro_line|#endif
multiline_comment|/* USB Serial devices vendor ids and device ids that this driver supports */
DECL|macro|BELKIN_VENDOR_ID
mdefine_line|#define BELKIN_VENDOR_ID&t;&t;0x056c
DECL|macro|BELKIN_SERIAL_CONVERTER
mdefine_line|#define BELKIN_SERIAL_CONVERTER&t;&t;0x8007
DECL|macro|PERACOM_VENDOR_ID
mdefine_line|#define PERACOM_VENDOR_ID&t;&t;0x0565
DECL|macro|PERACOM_SERIAL_CONVERTER
mdefine_line|#define PERACOM_SERIAL_CONVERTER&t;0x0001
DECL|macro|SERIAL_MAJOR
mdefine_line|#define SERIAL_MAJOR&t;240
DECL|macro|NUM_PORTS
mdefine_line|#define NUM_PORTS&t;4&t;/* Have to pick a number for now. Need to look */
multiline_comment|/* into dynamically creating them at insertion time. */
r_static
r_void
op_star
id|usb_serial_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
)paren
suffix:semicolon
r_static
r_void
id|usb_serial_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|unknown
id|unknown
op_assign
l_int|0
comma
DECL|enumerator|Belkin
id|Belkin
op_assign
l_int|1
comma
DECL|enumerator|Peracom
id|Peracom
op_assign
l_int|2
DECL|typedef|SERIAL_TYPE
)brace
id|SERIAL_TYPE
suffix:semicolon
DECL|struct|usb_serial_state
r_struct
id|usb_serial_state
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|type
id|SERIAL_TYPE
id|type
suffix:semicolon
multiline_comment|/* what manufacturer&squot;s type of converter */
DECL|member|irq_handle
r_void
op_star
id|irq_handle
suffix:semicolon
DECL|member|irqpipe
r_int
r_int
id|irqpipe
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* the coresponding tty for this device */
DECL|member|present
r_char
id|present
suffix:semicolon
DECL|member|active
r_char
id|active
suffix:semicolon
DECL|member|interrupt_in_inuse
r_char
id|interrupt_in_inuse
suffix:semicolon
DECL|member|interrupt_in_endpoint
id|__u8
id|interrupt_in_endpoint
suffix:semicolon
DECL|member|interrupt_in_interval
id|__u8
id|interrupt_in_interval
suffix:semicolon
DECL|member|interrupt_in_size
id|__u16
id|interrupt_in_size
suffix:semicolon
DECL|member|interrupt_in_pipe
r_int
r_int
id|interrupt_in_pipe
suffix:semicolon
DECL|member|interrupt_in_buffer
r_int
r_char
op_star
id|interrupt_in_buffer
suffix:semicolon
DECL|member|interrupt_in_transfer
r_void
op_star
id|interrupt_in_transfer
suffix:semicolon
DECL|member|bulk_in_inuse
r_char
id|bulk_in_inuse
suffix:semicolon
DECL|member|bulk_in_endpoint
id|__u8
id|bulk_in_endpoint
suffix:semicolon
DECL|member|bulk_in_interval
id|__u8
id|bulk_in_interval
suffix:semicolon
DECL|member|bulk_in_size
id|__u16
id|bulk_in_size
suffix:semicolon
DECL|member|bulk_in_pipe
r_int
r_int
id|bulk_in_pipe
suffix:semicolon
DECL|member|bulk_in_buffer
r_int
r_char
op_star
id|bulk_in_buffer
suffix:semicolon
DECL|member|bulk_in_transfer
r_void
op_star
id|bulk_in_transfer
suffix:semicolon
DECL|member|bulk_out_inuse
r_char
id|bulk_out_inuse
suffix:semicolon
DECL|member|bulk_out_endpoint
id|__u8
id|bulk_out_endpoint
suffix:semicolon
DECL|member|bulk_out_interval
id|__u8
id|bulk_out_interval
suffix:semicolon
DECL|member|bulk_out_size
id|__u16
id|bulk_out_size
suffix:semicolon
DECL|member|bulk_out_pipe
r_int
r_int
id|bulk_out_pipe
suffix:semicolon
DECL|member|bulk_out_buffer
r_int
r_char
op_star
id|bulk_out_buffer
suffix:semicolon
DECL|member|bulk_out_transfer
r_void
op_star
id|bulk_out_transfer
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|usb_serial_driver
r_static
r_struct
id|usb_driver
id|usb_serial_driver
op_assign
(brace
l_string|&quot;serial&quot;
comma
id|usb_serial_probe
comma
id|usb_serial_disconnect
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|serial_refcount
r_static
r_int
id|serial_refcount
suffix:semicolon
DECL|variable|serial_tty_driver
r_static
r_struct
id|tty_driver
id|serial_tty_driver
suffix:semicolon
DECL|variable|serial_tty
r_static
r_struct
id|tty_struct
op_star
id|serial_tty
(braket
id|NUM_PORTS
)braket
suffix:semicolon
DECL|variable|serial_termios
r_static
r_struct
id|termios
op_star
id|serial_termios
(braket
id|NUM_PORTS
)braket
suffix:semicolon
DECL|variable|serial_termios_locked
r_static
r_struct
id|termios
op_star
id|serial_termios_locked
(braket
id|NUM_PORTS
)braket
suffix:semicolon
DECL|variable|serial_state_table
r_static
r_struct
id|usb_serial_state
id|serial_state_table
(braket
id|NUM_PORTS
)braket
suffix:semicolon
DECL|function|serial_read_irq
r_static
r_int
id|serial_read_irq
(paren
r_int
id|state
comma
r_void
op_star
id|buffer
comma
r_int
id|count
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|serial-&gt;tty
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|buffer
suffix:semicolon
r_int
id|i
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB: serial_read_irq&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef SERIAL_DEBUG
r_if
c_cond
(paren
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%d %s&bslash;n&quot;
comma
id|count
comma
id|data
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|count
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
id|data
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
multiline_comment|/* Continue transfer */
multiline_comment|/* return (1); */
multiline_comment|/* No more transfer, let the irq schedule us again */
id|serial-&gt;bulk_in_inuse
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|serial_write_irq
r_static
r_int
id|serial_write_irq
(paren
r_int
id|state
comma
r_void
op_star
id|buffer
comma
r_int
id|count
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|serial-&gt;tty
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_write_irq&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;bulk_out_inuse
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: write irq for a finished pipe?&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|usb_terminate_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_out_transfer
)paren
suffix:semicolon
id|serial-&gt;bulk_out_inuse
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tty-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
)paren
op_logical_and
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_serial_irq
r_static
r_int
id|usb_serial_irq
(paren
r_int
id|state
comma
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_void
op_star
id|dev_id
)paren
(brace
singleline_comment|//&t;struct usb_serial_state *serial = (struct usb_serial_state *) dev_id;
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: usb_serial_irq&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* ask for a bulk read */
singleline_comment|//&t;serial-&gt;bulk_in_inuse = 1;
singleline_comment|//&t;serial-&gt;bulk_in_transfer = usb_request_bulk (serial-&gt;dev, serial-&gt;bulk_in_pipe, serial_read_irq, serial-&gt;bulk_in_buffer, serial-&gt;bulk_in_size, serial);
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* tty interface functions */
DECL|function|serial_open
r_static
r_int
id|serial_open
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
r_struct
id|usb_serial_state
op_star
id|serial
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB: serial_open&bslash;n&quot;
)paren
suffix:semicolon
id|serial
op_assign
op_amp
id|serial_state_table
(braket
id|MINOR
c_func
(paren
id|tty-&gt;device
)paren
op_minus
id|tty-&gt;driver.minor_start
)braket
suffix:semicolon
id|tty-&gt;driver_data
op_assign
id|serial
suffix:semicolon
id|serial-&gt;tty
op_assign
id|tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
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
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device already open&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|serial-&gt;active
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*Start reading from the device*/
id|serial-&gt;bulk_in_inuse
op_assign
l_int|1
suffix:semicolon
id|serial-&gt;bulk_in_transfer
op_assign
id|usb_request_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_in_pipe
comma
id|serial_read_irq
comma
id|serial-&gt;bulk_in_buffer
comma
id|serial-&gt;bulk_in_size
comma
id|serial
)paren
suffix:semicolon
multiline_comment|/* Need to do device specific setup here (control lines, baud rate, etc.) */
multiline_comment|/* FIXME!!! */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|serial_close
r_static
r_void
id|serial_close
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
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB: serial_close&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device already open&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Need to change the control lines here */
multiline_comment|/* FIXME */
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
id|usb_terminate_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_out_transfer
)paren
suffix:semicolon
id|serial-&gt;bulk_out_inuse
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_in_inuse
)paren
(brace
id|usb_terminate_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_in_transfer
)paren
suffix:semicolon
id|serial-&gt;bulk_in_inuse
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* release the irq? */
id|serial-&gt;active
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|serial_write
r_static
r_int
id|serial_write
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_const
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
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
r_int
id|written
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_write&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: device not registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not opened&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: already writing&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|written
op_assign
(paren
id|count
OG
id|serial-&gt;bulk_out_size
)paren
ques
c_cond
id|serial-&gt;bulk_out_size
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
id|copy_from_user
c_func
(paren
id|serial-&gt;bulk_out_buffer
comma
id|buf
comma
id|written
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
(paren
id|serial-&gt;bulk_out_buffer
comma
id|buf
comma
id|written
)paren
suffix:semicolon
)brace
multiline_comment|/* send the data out the bulk port */
id|serial-&gt;bulk_out_inuse
op_assign
l_int|1
suffix:semicolon
id|serial-&gt;bulk_out_transfer
op_assign
id|usb_request_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_out_pipe
comma
id|serial_write_irq
comma
id|serial-&gt;bulk_out_buffer
comma
id|written
comma
id|serial
)paren
suffix:semicolon
r_return
(paren
id|written
)paren
suffix:semicolon
)brace
DECL|function|serial_put_char
r_static
r_void
id|serial_put_char
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
id|ch
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_put_char&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not open&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: already writing&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* send the single character out the bulk port */
id|serial-&gt;bulk_out_buffer
(braket
l_int|0
)braket
op_assign
id|ch
suffix:semicolon
id|serial-&gt;bulk_out_inuse
op_assign
l_int|1
suffix:semicolon
id|serial-&gt;bulk_out_transfer
op_assign
id|usb_request_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_out_pipe
comma
id|serial_write_irq
comma
id|serial-&gt;bulk_out_buffer
comma
l_int|1
comma
id|serial
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|serial_write_room
r_static
r_int
id|serial_write_room
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_write_room&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not open&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|serial-&gt;bulk_out_size
suffix:semicolon
)brace
DECL|function|serial_chars_in_buffer
r_static
r_int
id|serial_chars_in_buffer
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_chars_in_buffer&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not open&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
r_return
(paren
id|serial-&gt;bulk_out_size
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|serial_throttle
r_static
r_void
id|serial_throttle
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_throttle&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not open&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Change the control signals */
multiline_comment|/* FIXME!!! */
r_return
suffix:semicolon
)brace
DECL|function|serial_unthrottle
r_static
r_void
id|serial_unthrottle
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: serial_unthrottle&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: no device registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;active
)paren
(brace
id|debug_info
(paren
l_string|&quot;USB Serial: device not open&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Change the control signals */
multiline_comment|/* FIXME!!! */
r_return
suffix:semicolon
)brace
DECL|function|Get_Free_Serial
r_static
r_int
id|Get_Free_Serial
(paren
r_void
)paren
(brace
r_int
id|i
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
id|NUM_PORTS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|serial_state_table
(braket
id|i
)braket
dot
id|present
)paren
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_probe
r_static
r_void
op_star
id|usb_serial_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
id|SERIAL_TYPE
id|type
suffix:semicolon
r_int
id|serial_num
suffix:semicolon
singleline_comment|//&t;int ret;
r_int
id|i
suffix:semicolon
multiline_comment|/* look at the device descriptor to see if it is a type that we&t;recognize */
id|type
op_assign
id|unknown
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;descriptor.idVendor
op_eq
id|BELKIN_VENDOR_ID
)paren
op_logical_and
(paren
id|dev-&gt;descriptor.idProduct
op_eq
id|BELKIN_SERIAL_CONVERTER
)paren
)paren
(brace
multiline_comment|/* This is the Belkin serial convertor */
id|type
op_assign
id|Belkin
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dev-&gt;descriptor.idVendor
op_eq
id|PERACOM_VENDOR_ID
)paren
op_logical_and
(paren
id|dev-&gt;descriptor.idProduct
op_eq
id|PERACOM_SERIAL_CONVERTER
)paren
)paren
(brace
multiline_comment|/* This is the Peracom serial convertor */
id|type
op_assign
id|Peracom
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|unknown
)paren
r_return
l_int|NULL
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;USB serial converter detected.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
(paren
id|serial_num
op_assign
id|Get_Free_Serial
c_func
(paren
)paren
)paren
)paren
(brace
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: Too many devices connected&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|serial
op_assign
op_amp
id|serial_state_table
(braket
id|serial_num
)braket
suffix:semicolon
id|memset
c_func
(paren
id|serial
comma
l_int|0
comma
r_sizeof
(paren
id|serial
)paren
)paren
suffix:semicolon
id|serial-&gt;dev
op_assign
id|dev
suffix:semicolon
id|serial-&gt;type
op_assign
id|type
suffix:semicolon
multiline_comment|/* we should have 1 bulk in, 1 bulk out, and 1 interrupt in endpoints */
id|interface
op_assign
op_amp
id|dev-&gt;actconfig-&gt;interface
(braket
id|ifnum
)braket
dot
id|altsetting
(braket
l_int|0
)braket
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
id|interface-&gt;bNumEndpoints
suffix:semicolon
op_increment
id|i
)paren
(brace
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_eq
l_int|0x02
)paren
)paren
(brace
multiline_comment|/* we found the bulk in endpoint */
id|serial-&gt;bulk_in_inuse
op_assign
l_int|0
suffix:semicolon
id|serial-&gt;bulk_in_endpoint
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
id|serial-&gt;bulk_in_size
op_assign
id|endpoint-&gt;wMaxPacketSize
suffix:semicolon
id|serial-&gt;bulk_in_interval
op_assign
id|endpoint-&gt;bInterval
suffix:semicolon
id|serial-&gt;bulk_in_pipe
op_assign
id|usb_rcvbulkpipe
(paren
id|dev
comma
id|serial-&gt;bulk_in_endpoint
)paren
suffix:semicolon
id|serial-&gt;bulk_in_buffer
op_assign
id|kmalloc
(paren
id|serial-&gt;bulk_in_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;bulk_in_buffer
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Serial: Couldn&squot;t allocate bulk_in_buffer&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|probe_error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_eq
l_int|0x00
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_eq
l_int|0x02
)paren
)paren
(brace
multiline_comment|/* we found the bulk out endpoint */
id|serial-&gt;bulk_out_inuse
op_assign
l_int|0
suffix:semicolon
id|serial-&gt;bulk_out_endpoint
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
id|serial-&gt;bulk_out_size
op_assign
id|endpoint-&gt;wMaxPacketSize
suffix:semicolon
id|serial-&gt;bulk_out_interval
op_assign
id|endpoint-&gt;bInterval
suffix:semicolon
id|serial-&gt;bulk_out_pipe
op_assign
id|usb_rcvbulkpipe
(paren
id|dev
comma
id|serial-&gt;bulk_out_endpoint
)paren
suffix:semicolon
id|serial-&gt;bulk_out_buffer
op_assign
id|kmalloc
(paren
id|serial-&gt;bulk_out_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;bulk_out_buffer
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Serial: Couldn&squot;t allocate bulk_out_buffer&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|probe_error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_eq
l_int|0x03
)paren
)paren
(brace
multiline_comment|/* we found the interrupt in endpoint */
id|serial-&gt;interrupt_in_inuse
op_assign
l_int|0
suffix:semicolon
id|serial-&gt;interrupt_in_endpoint
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
id|serial-&gt;interrupt_in_size
op_assign
id|endpoint-&gt;wMaxPacketSize
suffix:semicolon
id|serial-&gt;interrupt_in_interval
op_assign
id|endpoint-&gt;bInterval
suffix:semicolon
multiline_comment|/* serial-&gt;interrupt_in_pipe = usb_rcvbulkpipe (dev, serial-&gt;bulk_in_endpoint); */
id|serial-&gt;interrupt_in_buffer
op_assign
id|kmalloc
(paren
id|serial-&gt;bulk_in_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;interrupt_in_buffer
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Serial: Couldn&squot;t allocate interrupt_in_buffer&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|probe_error
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* verify that we found all of the endpoints that we need */
r_if
c_cond
(paren
(paren
op_logical_neg
id|serial-&gt;bulk_in_buffer
)paren
op_logical_or
(paren
op_logical_neg
id|serial-&gt;bulk_out_buffer
)paren
op_logical_or
(paren
op_logical_neg
id|serial-&gt;interrupt_in_buffer
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Serial: did not find all of the required endpoints&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|probe_error
suffix:semicolon
)brace
multiline_comment|/* set up an interrupt for out bulk in pipe */
multiline_comment|/* ask for a bulk read */
singleline_comment|//&t;serial-&gt;bulk_in_inuse = 1;
singleline_comment|//&t;serial-&gt;bulk_in_transfer = usb_request_bulk (serial-&gt;dev, serial-&gt;bulk_in_pipe, serial_read_irq, serial-&gt;bulk_in_buffer, serial-&gt;bulk_in_size, serial);
multiline_comment|/* set up our interrupt to be the time for the bulk in read */
singleline_comment|//&t;ret = usb_request_irq (dev, serial-&gt;bulk_in_pipe, usb_serial_irq, serial-&gt;bulk_in_interval, serial, &amp;serial-&gt;irq_handle);
singleline_comment|//&t;if (ret) {
singleline_comment|//&t;&t;printk(KERN_INFO &quot;USB Serial failed usb_request_irq (0x%x)&bslash;n&quot;, ret);
singleline_comment|//&t;&t;goto probe_error;
singleline_comment|//&t;}
id|serial-&gt;present
op_assign
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
id|serial
suffix:semicolon
id|probe_error
suffix:colon
r_if
c_cond
(paren
id|serial
)paren
(brace
r_if
c_cond
(paren
id|serial-&gt;bulk_in_buffer
)paren
id|kfree
(paren
id|serial-&gt;bulk_in_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;bulk_out_buffer
)paren
id|kfree
(paren
id|serial-&gt;bulk_out_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;interrupt_in_buffer
)paren
id|kfree
(paren
id|serial-&gt;interrupt_in_buffer
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|usb_serial_disconnect
r_static
r_void
id|usb_serial_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|usb_serial_state
op_star
id|serial
op_assign
(paren
r_struct
id|usb_serial_state
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|serial
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|serial-&gt;present
)paren
(brace
multiline_comment|/* something strange is going on */
id|debug_info
c_func
(paren
l_string|&quot;USB Serial: disconnect but not present?&bslash;n&quot;
)paren
r_return
suffix:semicolon
)brace
multiline_comment|/* need to stop any transfers...*/
r_if
c_cond
(paren
id|serial-&gt;bulk_in_inuse
)paren
(brace
id|usb_terminate_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_in_transfer
)paren
suffix:semicolon
id|serial-&gt;bulk_in_inuse
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;bulk_out_inuse
)paren
(brace
id|usb_terminate_bulk
(paren
id|serial-&gt;dev
comma
id|serial-&gt;bulk_out_transfer
)paren
suffix:semicolon
id|serial-&gt;bulk_out_inuse
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// usb_release_irq (serial-&gt;dev, serial-&gt;irq_handle, serial-&gt;bulk_in_pipe);
r_if
c_cond
(paren
id|serial-&gt;bulk_in_buffer
)paren
id|kfree
(paren
id|serial-&gt;bulk_in_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;bulk_out_buffer
)paren
id|kfree
(paren
id|serial-&gt;bulk_out_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;interrupt_in_buffer
)paren
id|kfree
(paren
id|serial-&gt;interrupt_in_buffer
)paren
suffix:semicolon
id|serial-&gt;present
op_assign
l_int|0
suffix:semicolon
id|serial-&gt;active
op_assign
l_int|0
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;USB Serial device disconnected.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_init
r_int
id|usb_serial_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Initalize our global data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_PORTS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|memset
c_func
(paren
op_amp
id|serial_state_table
(braket
id|i
)braket
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|usb_serial_state
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* register the tty driver */
id|memset
(paren
op_amp
id|serial_tty_driver
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
id|serial_tty_driver.magic
op_assign
id|TTY_DRIVER_MAGIC
suffix:semicolon
id|serial_tty_driver.driver_name
op_assign
l_string|&quot;usb&quot;
suffix:semicolon
id|serial_tty_driver.name
op_assign
l_string|&quot;ttyUSB&quot;
suffix:semicolon
id|serial_tty_driver.major
op_assign
id|SERIAL_MAJOR
suffix:semicolon
id|serial_tty_driver.minor_start
op_assign
l_int|0
suffix:semicolon
id|serial_tty_driver.num
op_assign
id|NUM_PORTS
suffix:semicolon
id|serial_tty_driver.type
op_assign
id|TTY_DRIVER_TYPE_SERIAL
suffix:semicolon
id|serial_tty_driver.subtype
op_assign
id|SERIAL_TYPE_NORMAL
suffix:semicolon
id|serial_tty_driver.init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|serial_tty_driver.init_termios.c_cflag
op_assign
id|B9600
op_or
id|CS8
op_or
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
id|serial_tty_driver.flags
op_assign
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|serial_tty_driver.refcount
op_assign
op_amp
id|serial_refcount
suffix:semicolon
id|serial_tty_driver.table
op_assign
id|serial_tty
suffix:semicolon
id|serial_tty_driver.termios
op_assign
id|serial_termios
suffix:semicolon
id|serial_tty_driver.termios_locked
op_assign
id|serial_termios_locked
suffix:semicolon
id|serial_tty_driver.open
op_assign
id|serial_open
suffix:semicolon
id|serial_tty_driver.close
op_assign
id|serial_close
suffix:semicolon
id|serial_tty_driver.write
op_assign
id|serial_write
suffix:semicolon
id|serial_tty_driver.put_char
op_assign
id|serial_put_char
suffix:semicolon
id|serial_tty_driver.flush_chars
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_flush_chars;
id|serial_tty_driver.write_room
op_assign
id|serial_write_room
suffix:semicolon
id|serial_tty_driver.ioctl
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_ioctl;
id|serial_tty_driver.set_termios
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_set_termios;
id|serial_tty_driver.set_ldisc
op_assign
l_int|NULL
suffix:semicolon
id|serial_tty_driver.throttle
op_assign
id|serial_throttle
suffix:semicolon
id|serial_tty_driver.unthrottle
op_assign
id|serial_unthrottle
suffix:semicolon
id|serial_tty_driver.stop
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_stop;
id|serial_tty_driver.start
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_start;
id|serial_tty_driver.hangup
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_hangup;
id|serial_tty_driver.break_ctl
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_break;
id|serial_tty_driver.wait_until_sent
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_wait_until_sent;
id|serial_tty_driver.send_xchar
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_send_xchar;
id|serial_tty_driver.read_proc
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_read_proc;
id|serial_tty_driver.chars_in_buffer
op_assign
id|serial_chars_in_buffer
suffix:semicolon
id|serial_tty_driver.flush_buffer
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//serial_flush_buffer;
r_if
c_cond
(paren
id|tty_register_driver
(paren
op_amp
id|serial_tty_driver
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;USB Serial: failed to register tty driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* register the USB driver */
id|usb_register
c_func
(paren
op_amp
id|usb_serial_driver
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;USB Serial support registered.&bslash;n&quot;
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
id|usb_serial_init
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
id|tty_unregister_driver
c_func
(paren
op_amp
id|serial_tty_driver
)paren
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|usb_serial_driver
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
