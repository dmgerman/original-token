multiline_comment|/*&n; *&t;Video4Linux: Colour QuickCam driver&n; *&n; *&t;Philip Blundell &lt;philb@gnu.org&gt;, December 30 1997&n; *&n; *&t;Largely untested (seems to work at 24bpp with a bidirectional port,&n; *&t;though). &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;c-qcam.h&quot;
DECL|function|qcam_set_ack
r_static
id|__inline__
r_void
id|qcam_set_ack
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
r_int
id|i
)paren
(brace
multiline_comment|/* note: the QC specs refer to the PCAck pin by voltage, not&n;&t;   software level.  PC ports have builtin inverters. */
id|parport_frob_control
c_func
(paren
id|qcam-&gt;pport
comma
l_int|8
comma
id|i
ques
c_cond
l_int|8
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|qcam_ready1
r_static
id|__inline__
r_int
r_int
id|qcam_ready1
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
r_return
(paren
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
op_amp
l_int|0x8
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_ready2
r_static
id|__inline__
r_int
r_int
id|qcam_ready2
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
r_return
(paren
id|parport_read_data
c_func
(paren
id|qcam-&gt;pport
)paren
op_amp
l_int|0x1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_await_ready1
r_static
r_inline
r_int
r_int
id|qcam_await_ready1
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|oldjiffies
op_assign
id|jiffies
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|oldjiffies
op_assign
id|jiffies
suffix:semicolon
(paren
id|jiffies
op_minus
id|oldjiffies
)paren
OL
(paren
id|HZ
op_div
l_int|25
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
id|qcam_ready1
c_func
(paren
id|qcam
)paren
op_eq
id|value
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* If the camera didn&squot;t respond within 1/25 second, poll slowly &n;&t;   for a while. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|qcam_ready1
c_func
(paren
id|qcam
)paren
op_eq
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Probably somebody pulled the plug out.  Not much we can do. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;c-qcam: ready1 timeout (%d) %x %x&bslash;n&quot;
comma
id|value
comma
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
comma
id|parport_read_control
c_func
(paren
id|qcam-&gt;pport
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|qcam_await_ready2
r_static
r_inline
r_int
r_int
id|qcam_await_ready2
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|oldjiffies
op_assign
id|jiffies
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|oldjiffies
op_assign
id|jiffies
suffix:semicolon
(paren
id|jiffies
op_minus
id|oldjiffies
)paren
OL
(paren
id|HZ
op_div
l_int|25
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
id|qcam_ready2
c_func
(paren
id|qcam
)paren
op_eq
id|value
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* If the camera didn&squot;t respond within 1/25 second, poll slowly &n;&t;   for a while. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|qcam_ready2
c_func
(paren
id|qcam
)paren
op_eq
id|value
)paren
r_return
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Probably somebody pulled the plug out.  Not much we can do. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;c-qcam: ready2 timeout (%d) %x %x %x&bslash;n&quot;
comma
id|value
comma
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
comma
id|parport_read_control
c_func
(paren
id|qcam-&gt;pport
)paren
comma
id|parport_read_data
c_func
(paren
id|qcam-&gt;pport
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|qcam_read_data
r_static
r_inline
r_int
id|qcam_read_data
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
r_int
r_int
id|idata
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|qcam
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|qcam
comma
l_int|1
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|idata
op_assign
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
op_amp
l_int|0xf0
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|qcam
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|qcam
comma
l_int|0
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|idata
op_or_assign
(paren
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
r_return
id|idata
suffix:semicolon
)brace
DECL|function|qcam_write_data
r_static
r_int
id|qcam_write_data
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|idata
suffix:semicolon
id|parport_write_data
c_func
(paren
id|qcam-&gt;pport
comma
id|data
)paren
suffix:semicolon
id|idata
op_assign
id|qcam_read_data
c_func
(paren
id|qcam
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_ne
id|idata
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cqcam: sent %x but received %x&bslash;n&quot;
comma
id|data
comma
id|idata
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_set
r_static
r_inline
r_int
id|qcam_set
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|qcam_write_data
c_func
(paren
id|qcam
comma
id|cmd
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|qcam_write_data
c_func
(paren
id|qcam
comma
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_get
r_static
r_inline
r_int
id|qcam_get
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
comma
r_int
r_int
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|qcam_write_data
c_func
(paren
id|qcam
comma
id|cmd
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|qcam_read_data
c_func
(paren
id|qcam
)paren
suffix:semicolon
)brace
DECL|function|qc_detect
r_static
r_int
id|qc_detect
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
r_int
r_int
id|stat
comma
id|ostat
comma
id|i
comma
id|count
op_assign
l_int|0
suffix:semicolon
id|parport_write_control
c_func
(paren
id|qcam-&gt;pport
comma
l_int|0xc
)paren
suffix:semicolon
multiline_comment|/* look for a heartbeat */
id|ostat
op_assign
id|stat
op_assign
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
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
l_int|250
suffix:semicolon
id|i
op_increment
)paren
(brace
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|stat
op_assign
id|parport_read_status
c_func
(paren
id|qcam-&gt;pport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ostat
op_ne
id|stat
)paren
(brace
r_if
c_cond
(paren
op_increment
id|count
op_ge
l_int|3
)paren
r_return
l_int|1
suffix:semicolon
id|ostat
op_assign
id|stat
suffix:semicolon
)brace
)brace
multiline_comment|/* no (or flatline) camera, give up */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qc_reset
r_static
r_void
id|qc_reset
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
id|parport_write_control
c_func
(paren
id|qcam-&gt;pport
comma
l_int|0xc
)paren
suffix:semicolon
id|parport_write_control
c_func
(paren
id|qcam-&gt;pport
comma
l_int|0x8
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|parport_write_control
c_func
(paren
id|qcam-&gt;pport
comma
l_int|0xc
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
multiline_comment|/* Reset the QuickCam and program for brightness, contrast,&n; * white-balance, and resolution. */
DECL|function|qc_setup
r_static
r_void
id|qc_setup
c_func
(paren
r_struct
id|qcam_device
op_star
id|q
)paren
(brace
id|qc_reset
c_func
(paren
id|q
)paren
suffix:semicolon
multiline_comment|/* Set the brightness.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|11
comma
id|q-&gt;brightness
)paren
suffix:semicolon
multiline_comment|/* Set the height.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|17
comma
id|q-&gt;height
)paren
suffix:semicolon
multiline_comment|/* Set the width.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|19
comma
id|q-&gt;width
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Set top and left.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|0xd
comma
id|q-&gt;top
)paren
suffix:semicolon
id|qcam_set
c_func
(paren
id|q
comma
l_int|0xf
comma
id|q-&gt;left
)paren
suffix:semicolon
multiline_comment|/* Set contrast and white balance.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|0x19
comma
id|q-&gt;contrast
)paren
suffix:semicolon
id|qcam_set
c_func
(paren
id|q
comma
l_int|0x1f
comma
id|q-&gt;whitebal
)paren
suffix:semicolon
multiline_comment|/* Set the speed.  */
id|qcam_set
c_func
(paren
id|q
comma
l_int|45
comma
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* Read some bytes from the camera and put them in the buffer. &n;   nbytes should be a multiple of 3, because bidirectional mode gives&n;   us three bytes at a time.  */
DECL|function|qcam_read_bytes
r_static
r_int
r_int
id|qcam_read_bytes
c_func
(paren
r_struct
id|qcam_device
op_star
id|q
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|nbytes
)paren
(brace
r_int
r_int
id|bytes
op_assign
l_int|0
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;bidirectional
)paren
(brace
multiline_comment|/* It&squot;s a bidirectional port */
r_while
c_loop
(paren
id|bytes
OL
id|nbytes
)paren
(brace
r_int
r_int
id|lo1
comma
id|hi1
comma
id|lo2
comma
id|hi2
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready2
c_func
(paren
id|q
comma
l_int|1
)paren
)paren
r_return
id|bytes
suffix:semicolon
id|lo1
op_assign
id|parport_read_data
c_func
(paren
id|q-&gt;pport
)paren
op_rshift
l_int|1
suffix:semicolon
id|hi1
op_assign
(paren
(paren
id|parport_read_status
c_func
(paren
id|q-&gt;pport
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x1f
)paren
op_xor
l_int|0x10
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready2
c_func
(paren
id|q
comma
l_int|0
)paren
)paren
r_return
id|bytes
suffix:semicolon
id|lo2
op_assign
id|parport_read_data
c_func
(paren
id|q-&gt;pport
)paren
op_rshift
l_int|1
suffix:semicolon
id|hi2
op_assign
(paren
(paren
id|parport_read_status
c_func
(paren
id|q-&gt;pport
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x1f
)paren
op_xor
l_int|0x10
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
id|buf
(braket
id|bytes
op_increment
)braket
op_assign
(paren
id|lo1
op_or
(paren
(paren
id|hi1
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|buf
(braket
id|bytes
op_increment
)braket
op_assign
(paren
(paren
id|hi1
op_amp
l_int|0x1e
)paren
op_lshift
l_int|3
)paren
op_or
(paren
(paren
id|hi2
op_amp
l_int|0x1e
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|buf
(braket
id|bytes
op_increment
)braket
op_assign
(paren
id|lo2
op_or
(paren
(paren
id|hi2
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* It&squot;s a unidirectional port */
r_while
c_loop
(paren
id|bytes
OL
id|nbytes
)paren
(brace
r_int
r_int
id|hi
comma
id|lo
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|1
)paren
)paren
r_return
id|bytes
suffix:semicolon
id|hi
op_assign
(paren
id|parport_read_status
c_func
(paren
id|q-&gt;pport
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|0
)paren
)paren
r_return
id|bytes
suffix:semicolon
id|lo
op_assign
(paren
id|parport_read_status
c_func
(paren
id|q-&gt;pport
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* flip some bits; cqcam gets this wrong */
id|buf
(braket
id|bytes
op_increment
)braket
op_assign
(paren
id|hi
op_or
id|lo
)paren
op_xor
l_int|0x88
suffix:semicolon
)brace
)brace
r_return
id|bytes
suffix:semicolon
)brace
multiline_comment|/* Convert the data the camera gives us into the desired output format. &n;   At the moment this is a no-op because read_bytes() does all the &n;   required stuff, for 24bpp at least.  */
DECL|function|qcam_munge_buffer
r_static
r_int
id|qcam_munge_buffer
c_func
(paren
r_struct
id|qcam_device
op_star
id|q
comma
r_char
op_star
id|inbuf
comma
r_int
id|inlen
comma
r_char
op_star
id|outbuf
comma
r_int
id|outlen
)paren
(brace
r_int
id|outptr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|q-&gt;bpp
)paren
(brace
r_case
l_int|24
suffix:colon
r_while
c_loop
(paren
id|inlen
op_logical_and
(paren
id|outptr
op_le
(paren
id|outlen
op_minus
l_int|3
)paren
)paren
)paren
(brace
r_int
r_char
id|r
comma
id|g
comma
id|b
suffix:semicolon
id|r
op_assign
id|inbuf
(braket
l_int|0
)braket
suffix:semicolon
id|g
op_assign
id|inbuf
(braket
l_int|1
)braket
suffix:semicolon
id|b
op_assign
id|inbuf
(braket
l_int|2
)braket
suffix:semicolon
id|put_user
c_func
(paren
id|r
comma
id|outbuf
op_plus
(paren
id|outptr
op_increment
)paren
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|g
comma
id|outbuf
op_plus
(paren
id|outptr
op_increment
)paren
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|b
comma
id|outbuf
op_plus
(paren
id|outptr
op_increment
)paren
)paren
suffix:semicolon
id|inlen
op_sub_assign
l_int|3
suffix:semicolon
id|inbuf
op_add_assign
l_int|3
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;c-qcam: can&squot;t convert this format (%d).&bslash;n&quot;
comma
id|q-&gt;bpp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|outptr
suffix:semicolon
)brace
DECL|function|qc_capture
r_static
r_int
id|qc_capture
c_func
(paren
r_struct
id|qcam_device
op_star
id|q
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|tbpp
op_assign
l_int|0
comma
id|tdecimation
op_assign
l_int|0
comma
id|lines
comma
id|pixelsperline
comma
id|bitsperxfer
suffix:semicolon
r_int
r_int
id|is_bi_dir
op_assign
id|q-&gt;bidirectional
suffix:semicolon
r_int
id|wantlen
comma
id|outptr
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|tmpbuf
op_assign
id|kmalloc
c_func
(paren
l_int|768
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpbuf
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cqcam: couldn&squot;t allocate a buffer.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Wait for camera to become ready */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|i
op_assign
id|qcam_get
c_func
(paren
id|q
comma
l_int|41
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
op_minus
l_int|1
)paren
(brace
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_amp
l_int|0x80
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|q-&gt;bpp
)paren
(brace
r_case
l_int|24
suffix:colon
id|tbpp
op_assign
id|QC_24BPP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|tbpp
op_assign
id|QC_32BPP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|tbpp
op_assign
id|QC_16BPP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;qcam: Bad bpp.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|q-&gt;transfer_scale
)paren
(brace
r_case
l_int|1
suffix:colon
id|tdecimation
op_assign
id|QC_1_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tdecimation
op_assign
id|QC_2_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|tdecimation
op_assign
id|QC_4_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;qcam: Bad decimation.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|qcam_set
c_func
(paren
id|q
comma
l_int|7
comma
(paren
id|tbpp
op_or
id|tdecimation
)paren
op_plus
(paren
(paren
id|is_bi_dir
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|lines
op_assign
id|q-&gt;height
op_div
id|q-&gt;transfer_scale
suffix:semicolon
id|pixelsperline
op_assign
id|q-&gt;width
op_div
id|q-&gt;transfer_scale
suffix:semicolon
id|bitsperxfer
op_assign
(paren
id|is_bi_dir
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|is_bi_dir
)paren
(brace
multiline_comment|/* Turn the port around */
id|parport_frob_control
c_func
(paren
id|q-&gt;pport
comma
l_int|0x20
comma
l_int|0x20
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|3000
)paren
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|1
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|0
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
id|wantlen
op_assign
id|lines
op_star
id|pixelsperline
op_star
id|q-&gt;bpp
op_div
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|wantlen
)paren
(brace
r_int
id|t
comma
id|s
comma
id|o
suffix:semicolon
id|s
op_assign
(paren
id|wantlen
OG
l_int|768
)paren
ques
c_cond
l_int|768
suffix:colon
id|wantlen
suffix:semicolon
id|t
op_assign
id|qcam_read_bytes
c_func
(paren
id|q
comma
id|tmpbuf
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outptr
OL
id|len
)paren
(brace
id|o
op_assign
id|qcam_munge_buffer
c_func
(paren
id|q
comma
id|tmpbuf
comma
id|t
comma
id|buf
op_plus
id|outptr
comma
id|len
op_minus
id|outptr
)paren
suffix:semicolon
id|outptr
op_add_assign
id|o
suffix:semicolon
)brace
id|wantlen
op_sub_assign
id|t
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
id|s
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|len
op_assign
id|outptr
suffix:semicolon
r_if
c_cond
(paren
id|wantlen
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qcam: short read.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bi_dir
)paren
id|parport_frob_control
c_func
(paren
id|q-&gt;pport
comma
l_int|0x20
comma
l_int|0
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_bi_dir
)paren
(brace
r_int
id|l
suffix:semicolon
r_do
(brace
id|l
op_assign
id|qcam_read_bytes
c_func
(paren
id|q
comma
id|tmpbuf
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|l
op_logical_and
(paren
id|tmpbuf
(braket
l_int|0
)braket
op_eq
l_int|0x7e
op_logical_or
id|tmpbuf
(braket
l_int|1
)braket
op_eq
l_int|0x7e
op_logical_or
id|tmpbuf
(braket
l_int|2
)braket
op_eq
l_int|0x7e
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpbuf
(braket
l_int|0
)braket
op_ne
l_int|0xe
op_logical_or
id|tmpbuf
(braket
l_int|1
)braket
op_ne
l_int|0x0
op_logical_or
id|tmpbuf
(braket
l_int|2
)braket
op_ne
l_int|0xf
)paren
id|printk
c_func
(paren
l_string|&quot;qcam: bad EOF&bslash;n&quot;
)paren
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qcam: no ack after EOF&bslash;n&quot;
)paren
suffix:semicolon
id|parport_frob_control
c_func
(paren
id|q-&gt;pport
comma
l_int|0x20
comma
l_int|0
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|parport_frob_control
c_func
(paren
id|q-&gt;pport
comma
l_int|0x20
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|3000
)paren
suffix:semicolon
id|qcam_set_ack
c_func
(paren
id|q
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam_await_ready1
c_func
(paren
id|q
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qcam: no ack to port turnaround&bslash;n&quot;
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
id|l
suffix:semicolon
r_do
(brace
id|l
op_assign
id|qcam_read_bytes
c_func
(paren
id|q
comma
id|tmpbuf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|l
op_logical_and
id|tmpbuf
(braket
l_int|0
)braket
op_eq
l_int|0x7e
)paren
suffix:semicolon
id|l
op_assign
id|qcam_read_bytes
c_func
(paren
id|q
comma
id|tmpbuf
op_plus
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpbuf
(braket
l_int|0
)braket
op_ne
l_int|0xe
op_logical_or
id|tmpbuf
(braket
l_int|1
)braket
op_ne
l_int|0x0
op_logical_or
id|tmpbuf
(braket
l_int|2
)braket
op_ne
l_int|0xf
)paren
id|printk
c_func
(paren
l_string|&quot;qcam: bad EOF&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
id|qcam_write_data
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Video4linux interfacing&n; */
DECL|function|qcam_open
r_static
r_int
id|qcam_open
c_func
(paren
r_struct
id|video_device
op_star
id|dev
comma
r_int
id|flags
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_close
r_static
r_void
id|qcam_close
c_func
(paren
r_struct
id|video_device
op_star
id|dev
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|qcam_init_done
r_static
r_int
id|qcam_init_done
c_func
(paren
r_struct
id|video_device
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_write
r_static
r_int
id|qcam_write
c_func
(paren
r_struct
id|video_device
op_star
id|v
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_int
id|noblock
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|qcam_ioctl
r_static
r_int
id|qcam_ioctl
c_func
(paren
r_struct
id|video_device
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|qcam_device
op_star
id|qcam
op_assign
(paren
r_struct
id|qcam_device
op_star
)paren
id|dev
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOCGCAP
suffix:colon
(brace
r_struct
id|video_capability
id|b
suffix:semicolon
id|strcpy
c_func
(paren
id|b.name
comma
l_string|&quot;Quickcam&quot;
)paren
suffix:semicolon
id|b.type
op_assign
id|VID_TYPE_CAPTURE
op_or
id|VID_TYPE_SCALES
suffix:semicolon
id|b.channels
op_assign
l_int|1
suffix:semicolon
id|b.audios
op_assign
l_int|0
suffix:semicolon
id|b.maxwidth
op_assign
l_int|320
suffix:semicolon
id|b.maxheight
op_assign
l_int|240
suffix:semicolon
id|b.minwidth
op_assign
l_int|80
suffix:semicolon
id|b.minheight
op_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGCHAN
suffix:colon
(brace
r_struct
id|video_channel
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.channel
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|v.flags
op_assign
l_int|0
suffix:semicolon
id|v.tuners
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Good question.. its composite or SVHS so.. */
id|v.type
op_assign
id|VIDEO_TYPE_CAMERA
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Camera&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSCHAN
suffix:colon
(brace
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGTUNER
suffix:colon
(brace
r_struct
id|video_tuner
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Format&quot;
)paren
suffix:semicolon
id|v.rangelow
op_assign
l_int|0
suffix:semicolon
id|v.rangehigh
op_assign
l_int|0
suffix:semicolon
id|v.flags
op_assign
l_int|0
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSTUNER
suffix:colon
(brace
r_struct
id|video_tuner
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.mode
op_ne
id|VIDEO_MODE_AUTO
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGPICT
suffix:colon
(brace
r_struct
id|video_picture
id|p
suffix:semicolon
id|p.colour
op_assign
l_int|0x8000
suffix:semicolon
id|p.hue
op_assign
l_int|0x8000
suffix:semicolon
id|p.brightness
op_assign
id|qcam-&gt;brightness
op_lshift
l_int|8
suffix:semicolon
id|p.contrast
op_assign
id|qcam-&gt;contrast
op_lshift
l_int|8
suffix:semicolon
id|p.whiteness
op_assign
id|qcam-&gt;whitebal
op_lshift
l_int|8
suffix:semicolon
id|p.depth
op_assign
id|qcam-&gt;bpp
suffix:semicolon
id|p.palette
op_assign
id|VIDEO_PALETTE_RGB24
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|p
comma
r_sizeof
(paren
id|p
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSPICT
suffix:colon
(brace
r_struct
id|video_picture
id|p
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|p
comma
id|arg
comma
r_sizeof
(paren
id|p
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p.palette
op_ne
id|VIDEO_PALETTE_RGB24
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Now load the camera.&n;&t;&t;&t; */
id|qcam-&gt;brightness
op_assign
id|p.brightness
op_rshift
l_int|8
suffix:semicolon
id|qcam-&gt;contrast
op_assign
id|p.contrast
op_rshift
l_int|8
suffix:semicolon
id|qcam-&gt;whitebal
op_assign
id|p.whiteness
op_rshift
l_int|8
suffix:semicolon
id|qcam-&gt;bpp
op_assign
id|p.depth
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|qcam
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSWIN
suffix:colon
(brace
r_struct
id|video_window
id|vw
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|vw
comma
id|arg
comma
r_sizeof
(paren
id|vw
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vw.flags
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vw.clipcount
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vw.height
l_int|240
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vw.width
l_int|320
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|qcam-&gt;width
op_assign
l_int|320
suffix:semicolon
id|qcam-&gt;height
op_assign
l_int|240
suffix:semicolon
id|qcam-&gt;transfer_scale
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|vw.width
op_ge
l_int|160
op_logical_and
id|vw.height
op_ge
l_int|120
)paren
(brace
id|qcam-&gt;transfer_scale
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vw.width
op_ge
l_int|320
op_logical_and
id|vw.height
op_ge
l_int|240
)paren
(brace
id|qcam-&gt;width
op_assign
l_int|320
suffix:semicolon
id|qcam-&gt;height
op_assign
l_int|240
suffix:semicolon
id|qcam-&gt;transfer_scale
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Ok we figured out what to use from our wide choice */
id|parport_claim_or_block
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|qc_setup
c_func
(paren
id|qcam
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGWIN
suffix:colon
(brace
r_struct
id|video_window
id|vw
suffix:semicolon
id|vw.x
op_assign
l_int|0
suffix:semicolon
id|vw.y
op_assign
l_int|0
suffix:semicolon
id|vw.width
op_assign
id|qcam-&gt;width
op_div
id|qcam-&gt;transfer_scale
suffix:semicolon
id|vw.height
op_assign
id|qcam-&gt;height
op_div
id|qcam-&gt;transfer_scale
suffix:semicolon
id|vw.chromakey
op_assign
l_int|0
suffix:semicolon
id|vw.flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|vw
comma
r_sizeof
(paren
id|vw
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCCAPTURE
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCGFBUF
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCSFBUF
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCKEY
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|VIDIOCGFREQ
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCSFREQ
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCGAUDIO
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|VIDIOCSAUDIO
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qcam_read
r_static
r_int
id|qcam_read
c_func
(paren
r_struct
id|video_device
op_star
id|v
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_int
id|noblock
)paren
(brace
r_struct
id|qcam_device
op_star
id|qcam
op_assign
(paren
r_struct
id|qcam_device
op_star
)paren
id|v
suffix:semicolon
r_int
id|len
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
multiline_comment|/* Probably should have a semaphore against multiple users */
id|len
op_assign
id|qc_capture
c_func
(paren
id|qcam
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* video device template */
DECL|variable|qcam_template
r_static
r_struct
id|video_device
id|qcam_template
op_assign
(brace
l_string|&quot;Colour Quickcam&quot;
comma
id|VID_TYPE_CAPTURE
comma
id|VID_HARDWARE_QCAM_C
comma
id|qcam_open
comma
id|qcam_close
comma
id|qcam_read
comma
id|qcam_write
comma
id|qcam_ioctl
comma
l_int|NULL
comma
id|qcam_init_done
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Initialize the QuickCam driver control structure. */
DECL|function|qcam_init
r_static
r_struct
id|qcam_device
op_star
id|qcam_init
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|qcam_device
op_star
id|q
suffix:semicolon
id|q
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|qcam_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|q-&gt;pport
op_assign
id|port
suffix:semicolon
id|q-&gt;pdev
op_assign
id|parport_register_device
c_func
(paren
id|port
comma
l_string|&quot;c-qcam&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|q-&gt;bidirectional
op_assign
(paren
id|q-&gt;pport-&gt;modes
op_amp
id|PARPORT_MODE_PCPS2
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;pdev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;c-qcam: couldn&squot;t register for %s.&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|q-&gt;vdev
comma
op_amp
id|qcam_template
comma
r_sizeof
(paren
id|qcam_template
)paren
)paren
suffix:semicolon
id|q-&gt;width
op_assign
l_int|320
suffix:semicolon
id|q-&gt;height
op_assign
l_int|240
suffix:semicolon
id|q-&gt;bpp
op_assign
l_int|32
suffix:semicolon
id|q-&gt;transfer_scale
op_assign
l_int|1
suffix:semicolon
id|q-&gt;contrast
op_assign
l_int|192
suffix:semicolon
id|q-&gt;brightness
op_assign
l_int|240
suffix:semicolon
id|q-&gt;whitebal
op_assign
l_int|128
suffix:semicolon
id|q-&gt;top
op_assign
l_int|1
suffix:semicolon
id|q-&gt;left
op_assign
l_int|14
suffix:semicolon
r_return
id|q
suffix:semicolon
)brace
DECL|macro|MAX_CAMS
mdefine_line|#define MAX_CAMS 4
DECL|variable|qcams
r_static
r_struct
id|qcam_device
op_star
id|qcams
(braket
id|MAX_CAMS
)braket
suffix:semicolon
DECL|variable|num_cams
r_static
r_int
r_int
id|num_cams
op_assign
l_int|0
suffix:semicolon
DECL|function|init_cqcam
r_int
id|init_cqcam
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|qcam_device
op_star
id|qcam
suffix:semicolon
r_if
c_cond
(paren
id|num_cams
op_eq
id|MAX_CAMS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Too many Quickcams (max %d)&bslash;n&quot;
comma
id|MAX_CAMS
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|qcam
op_assign
id|qcam_init
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcam
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|parport_claim_or_block
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|qc_reset
c_func
(paren
id|qcam
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qc_detect
c_func
(paren
id|qcam
)paren
op_eq
l_int|0
)paren
(brace
id|parport_release
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|qcam
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|qc_setup
c_func
(paren
id|qcam
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Connectix Colour Quickcam on %s&bslash;n&quot;
comma
id|qcam-&gt;pport-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|qcam-&gt;vdev
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|parport_unregister_device
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|qcam
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|qcams
(braket
id|num_cams
op_increment
)braket
op_assign
id|qcam
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|close_cqcam
r_void
id|close_cqcam
c_func
(paren
r_struct
id|qcam_device
op_star
id|qcam
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|qcam-&gt;vdev
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|qcam-&gt;pdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|qcam
)paren
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
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|init_cqcam
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
(paren
id|num_cams
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
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
r_int
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
id|num_cams
suffix:semicolon
id|i
op_increment
)paren
id|close_cqcam
c_func
(paren
id|qcams
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_colour_qcams
c_func
(paren
r_struct
id|video_init
op_star
id|unused
)paren
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|init_cqcam
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof