multiline_comment|/*&n; * Copyright (C) 1999-2000 by David Brownell &lt;david-b@pacbell.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * USB driver for Kodak DC-2XX series digital still cameras&n; *&n; * The protocol here is the same as the one going over a serial line, but&n; * it uses USB for speed.  Set up /dev/kodak, get gphoto (www.gphoto.org),&n; * and have fun!&n; *&n; * This should also work for a number of other digital (non-Kodak) cameras,&n; * by adding the vendor and product IDs to the table below.  They&squot;ll need&n; * to be the sort using USB just as a fast bulk data channel.&n; */
multiline_comment|/*&n; * HISTORY&n; *&n; * 26 August, 1999 -- first release (0.1), works with my DC-240.&n; * &t;The DC-280 (2Mpixel) should also work, but isn&squot;t tested.&n; *&t;If you use gphoto, make sure you have the USB updates.&n; *&t;Lives in a 2.3.14 or so Linux kernel, in drivers/usb.&n; * 31 August, 1999 -- minor update to recognize DC-260 and handle&n; *&t;its endpoints being in a different order.  Note that as&n; *&t;of gPhoto 0.36pre, the USB updates are integrated.&n; * 12 Oct, 1999 -- handle DC-280 interface class (0xff not 0x0);&n; *&t;added timeouts to bulk_msg calls.  Minor updates, docs.&n; * 03 Nov, 1999 -- update for 2.3.25 kernel API changes.&n; * 08 Jan, 2000 .. multiple camera support&n; *&n; * Thanks to:  the folk who&squot;ve provided USB product IDs, sent in&n; * patches, and shared their sucesses!&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/usb.h&gt;
multiline_comment|/* current USB framework handles max of 16 USB devices per driver */
DECL|macro|MAX_CAMERAS
mdefine_line|#define&t;MAX_CAMERAS&t;&t;8
multiline_comment|/* USB char devs use USB_MAJOR and from USB_CAMERA_MINOR_BASE up */
DECL|macro|USB_CAMERA_MINOR_BASE
mdefine_line|#define&t;USB_CAMERA_MINOR_BASE&t;80
singleline_comment|// XXX remove packet size limit, now that bulk transfers seem fixed
multiline_comment|/* Application protocol limit is 0x8002; USB has disliked that limit! */
DECL|macro|MAX_PACKET_SIZE
mdefine_line|#define&t;MAX_PACKET_SIZE&t;&t;0x2000&t;&t;/* e.g. image downloading */
DECL|macro|MAX_READ_RETRY
mdefine_line|#define&t;MAX_READ_RETRY&t;&t;5&t;&t;/* times to retry reads */
DECL|macro|MAX_WRITE_RETRY
mdefine_line|#define&t;MAX_WRITE_RETRY&t;&t;5&t;&t;/* times to retry writes */
DECL|macro|RETRY_TIMEOUT
mdefine_line|#define&t;RETRY_TIMEOUT&t;&t;(HZ)&t;&t;/* sleep between retries */
multiline_comment|/* table of cameras that work through this driver */
DECL|struct|camera
r_static
r_const
r_struct
id|camera
(brace
DECL|member|idVendor
r_int
r_int
id|idVendor
suffix:semicolon
DECL|member|idProduct
r_int
r_int
id|idProduct
suffix:semicolon
multiline_comment|/* plus hooks for camera-specific info if needed */
DECL|variable|cameras
)brace
id|cameras
(braket
)braket
op_assign
(brace
multiline_comment|/* These have the same application level protocol */
(brace
l_int|0x040a
comma
l_int|0x0120
)brace
comma
singleline_comment|// Kodak DC-240
(brace
l_int|0x040a
comma
l_int|0x0130
)brace
comma
singleline_comment|// Kodak DC-280
multiline_comment|/* These have a different application level protocol which&n;&t; * is part of the Flashpoint &quot;DigitaOS&quot;.  That supports some&n;&t; * non-camera devices, and some non-Kodak cameras.&n;&t; */
(brace
l_int|0x040a
comma
l_int|0x0100
)brace
comma
singleline_comment|// Kodak DC-220
(brace
l_int|0x040a
comma
l_int|0x0110
)brace
comma
singleline_comment|// Kodak DC-260
(brace
l_int|0x040a
comma
l_int|0x0111
)brace
comma
singleline_comment|// Kodak DC-265
(brace
l_int|0x040a
comma
l_int|0x0112
)brace
comma
singleline_comment|// Kodak DC-290
(brace
l_int|0xf003
comma
l_int|0x6002
)brace
comma
singleline_comment|// HP PhotoSmart C500
multiline_comment|/* Other USB devices may well work here too, so long as they&n;&t; * just stick to half duplex bulk packet exchanges.  That&n;&t; * means, among other things, no iso or interrupt endpoints.&n;&t; */
)brace
suffix:semicolon
DECL|struct|camera_state
r_struct
id|camera_state
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* USB device handle */
DECL|member|inEP
r_int
id|inEP
suffix:semicolon
multiline_comment|/* read endpoint */
DECL|member|outEP
r_int
id|outEP
suffix:semicolon
multiline_comment|/* write endpoint */
DECL|member|info
r_const
r_struct
id|camera
op_star
id|info
suffix:semicolon
multiline_comment|/* DC-240, etc */
DECL|member|subminor
r_int
id|subminor
suffix:semicolon
multiline_comment|/* which minor dev #? */
DECL|member|isActive
r_int
id|isActive
suffix:semicolon
multiline_comment|/* I/O taking place? */
multiline_comment|/* this is non-null iff the device is open */
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* buffer for I/O */
multiline_comment|/* always valid */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* for timed waits */
)brace
suffix:semicolon
multiline_comment|/* Support multiple cameras, possibly of different types.  */
DECL|variable|minor_data
r_static
r_struct
id|camera_state
op_star
id|minor_data
(braket
id|MAX_CAMERAS
)braket
suffix:semicolon
DECL|function|camera_read
r_static
id|ssize_t
id|camera_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|camera_state
op_star
id|camera
suffix:semicolon
r_int
id|retries
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|MAX_PACKET_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|camera
op_assign
(paren
r_struct
id|camera_state
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|camera-&gt;isActive
op_increment
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Big reads are common, for image downloading.  Smaller ones&n;&t; * are also common (even &quot;directory listing&quot; commands don&squot;t&n;&t; * send very much data).  We preserve packet boundaries here,&n;&t; * they matter in the application protocol.&n;&t; */
r_for
c_loop
(paren
id|retries
op_assign
l_int|0
suffix:semicolon
id|retries
OL
id|MAX_READ_RETRY
suffix:semicolon
id|retries
op_increment
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;dev
)paren
(brace
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|result
op_assign
id|usb_bulk_msg
(paren
id|camera-&gt;dev
comma
id|usb_rcvbulkpipe
(paren
id|camera-&gt;dev
comma
id|camera-&gt;inEP
)paren
comma
id|camera-&gt;buf
comma
id|len
comma
op_amp
id|count
comma
id|HZ
op_star
l_int|10
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;read (%d) - 0x%x %d&quot;
comma
id|len
comma
id|result
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buf
comma
id|camera-&gt;buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_ne
id|USB_ST_TIMEOUT
)paren
r_break
suffix:semicolon
id|interruptible_sleep_on_timeout
(paren
op_amp
id|camera-&gt;wait
comma
id|RETRY_TIMEOUT
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;read (%d) - retry&quot;
comma
id|len
)paren
suffix:semicolon
)brace
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|camera_write
r_static
id|ssize_t
id|camera_write
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|camera_state
op_star
id|camera
suffix:semicolon
id|ssize_t
id|bytes_written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|MAX_PACKET_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|camera
op_assign
(paren
r_struct
id|camera_state
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|camera-&gt;isActive
op_increment
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* most writes will be small: simple commands, sometimes with&n;&t; * parameters.  putting images (like borders) into the camera&n;&t; * would be the main use of big writes.&n;&t; */
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_char
op_star
id|obuf
op_assign
id|camera-&gt;buf
suffix:semicolon
r_int
id|maxretry
op_assign
id|MAX_WRITE_RETRY
suffix:semicolon
r_int
r_int
id|copy_size
comma
id|thistime
suffix:semicolon
multiline_comment|/* it&squot;s not clear that retrying can do any good ... or that&n;&t;&t; * fragmenting application packets into N writes is correct.&n;&t;&t; */
id|thistime
op_assign
id|copy_size
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|obuf
comma
id|buf
comma
id|copy_size
)paren
)paren
(brace
id|bytes_written
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|thistime
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
id|bytes_written
op_assign
op_minus
id|EINTR
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
id|bytes_written
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|result
op_assign
id|usb_bulk_msg
(paren
id|camera-&gt;dev
comma
id|usb_sndbulkpipe
(paren
id|camera-&gt;dev
comma
id|camera-&gt;outEP
)paren
comma
id|obuf
comma
id|thistime
comma
op_amp
id|count
comma
id|HZ
op_star
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|dbg
(paren
l_string|&quot;write USB err - %x&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|obuf
op_add_assign
id|count
suffix:semicolon
id|thistime
op_sub_assign
id|count
suffix:semicolon
id|maxretry
op_assign
id|MAX_WRITE_RETRY
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|USB_ST_TIMEOUT
)paren
(brace
multiline_comment|/* NAK - delay a bit */
r_if
c_cond
(paren
op_logical_neg
id|maxretry
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
id|bytes_written
op_assign
op_minus
id|ETIME
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|interruptible_sleep_on_timeout
(paren
op_amp
id|camera-&gt;wait
comma
id|RETRY_TIMEOUT
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
id|bytes_written
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|bytes_written
op_add_assign
id|copy_size
suffix:semicolon
id|len
op_sub_assign
id|copy_size
suffix:semicolon
id|buf
op_add_assign
id|copy_size
suffix:semicolon
)brace
id|done
suffix:colon
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
id|dbg
(paren
l_string|&quot;wrote %d&quot;
comma
id|bytes_written
)paren
suffix:semicolon
r_return
id|bytes_written
suffix:semicolon
)brace
DECL|function|camera_open
r_static
r_int
id|camera_open
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
id|camera_state
op_star
id|camera
suffix:semicolon
r_int
id|subminor
suffix:semicolon
id|subminor
op_assign
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|USB_CAMERA_MINOR_BASE
suffix:semicolon
r_if
c_cond
(paren
id|subminor
OL
l_int|0
op_logical_or
id|subminor
op_ge
id|MAX_CAMERAS
op_logical_or
op_logical_neg
(paren
id|camera
op_assign
id|minor_data
(braket
id|subminor
)braket
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|camera-&gt;buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
(paren
id|MAX_PACKET_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;open&quot;
)paren
suffix:semicolon
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
id|file-&gt;private_data
op_assign
id|camera
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|camera_release
r_static
r_int
id|camera_release
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
id|camera_state
op_star
id|camera
suffix:semicolon
id|camera
op_assign
(paren
r_struct
id|camera_state
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|kfree
(paren
id|camera-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* If camera was unplugged with open file ... */
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;dev
)paren
(brace
id|minor_data
(braket
id|camera-&gt;subminor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
(paren
id|camera
)paren
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;close&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* XXX should define some ioctls to expose camera type&n;&t; * to applications ... what USB exposes should suffice.&n;&t; * apps should be able to see the camera type.&n;&t; */
DECL|variable|usb_camera_fops
r_static
multiline_comment|/* const */
r_struct
id|file_operations
id|usb_camera_fops
op_assign
(brace
multiline_comment|/* Uses GCC initializer extension; simpler to maintain */
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|camera_read
comma
id|write
suffix:colon
id|camera_write
comma
id|open
suffix:colon
id|camera_open
comma
id|release
suffix:colon
id|camera_release
comma
)brace
suffix:semicolon
DECL|function|camera_probe
r_static
r_void
op_star
id|camera_probe
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
r_int
id|i
suffix:semicolon
r_const
r_struct
id|camera
op_star
id|camera_info
op_assign
l_int|NULL
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
r_int
id|direction
comma
id|ep
suffix:semicolon
r_struct
id|camera_state
op_star
id|camera
suffix:semicolon
multiline_comment|/* Is it a supported camera? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|cameras
)paren
op_div
r_sizeof
(paren
r_struct
id|camera
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cameras
(braket
id|i
)braket
dot
id|idVendor
op_ne
id|dev-&gt;descriptor.idVendor
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cameras
(braket
id|i
)braket
dot
id|idProduct
op_ne
id|dev-&gt;descriptor.idProduct
)paren
r_continue
suffix:semicolon
id|camera_info
op_assign
op_amp
id|cameras
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|camera_info
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* these have one config, one interface */
r_if
c_cond
(paren
id|dev-&gt;descriptor.bNumConfigurations
op_ne
l_int|1
op_logical_or
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|bNumInterfaces
op_ne
l_int|1
)paren
(brace
id|dbg
(paren
l_string|&quot;Bogus camera config info&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* models differ in how they report themselves */
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
r_if
c_cond
(paren
(paren
id|interface-&gt;bInterfaceClass
op_ne
id|USB_CLASS_PER_INTERFACE
op_logical_and
id|interface-&gt;bInterfaceClass
op_ne
id|USB_CLASS_VENDOR_SPEC
)paren
op_logical_or
id|interface-&gt;bInterfaceSubClass
op_ne
l_int|0
op_logical_or
id|interface-&gt;bInterfaceProtocol
op_ne
l_int|0
op_logical_or
id|interface-&gt;bNumEndpoints
op_ne
l_int|2
)paren
(brace
id|dbg
(paren
l_string|&quot;Bogus camera interface info&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* select &quot;subminor&quot; number (part of a minor number) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CAMERAS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|minor_data
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|MAX_CAMERAS
)paren
(brace
id|info
(paren
l_string|&quot;Ignoring additional USB Camera&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* allocate &amp; init camera state */
id|camera
op_assign
id|minor_data
(braket
id|i
)braket
op_assign
id|kmalloc
(paren
r_sizeof
op_star
id|camera
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|camera
)paren
(brace
id|err
(paren
l_string|&quot;no memory!&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|camera-&gt;info
op_assign
id|camera_info
suffix:semicolon
id|camera-&gt;subminor
op_assign
id|i
suffix:semicolon
id|camera-&gt;isActive
op_assign
l_int|0
suffix:semicolon
id|camera-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
(paren
op_amp
id|camera-&gt;wait
)paren
suffix:semicolon
id|info
(paren
l_string|&quot;USB Camera #%d connected&quot;
comma
id|camera-&gt;subminor
)paren
suffix:semicolon
multiline_comment|/* get input and output endpoints (either order) */
id|endpoint
op_assign
id|interface-&gt;endpoint
suffix:semicolon
id|camera-&gt;outEP
op_assign
id|camera-&gt;inEP
op_assign
op_minus
l_int|1
suffix:semicolon
id|ep
op_assign
id|endpoint
(braket
l_int|0
)braket
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
id|direction
op_assign
id|endpoint
(braket
l_int|0
)braket
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_DIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
id|camera-&gt;inEP
op_assign
id|ep
suffix:semicolon
r_else
id|camera-&gt;outEP
op_assign
id|ep
suffix:semicolon
id|ep
op_assign
id|endpoint
(braket
l_int|1
)braket
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
id|direction
op_assign
id|endpoint
(braket
l_int|1
)braket
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_DIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
id|camera-&gt;inEP
op_assign
id|ep
suffix:semicolon
r_else
id|camera-&gt;outEP
op_assign
id|ep
suffix:semicolon
r_if
c_cond
(paren
id|camera-&gt;outEP
op_eq
op_minus
l_int|1
op_logical_or
id|camera-&gt;inEP
op_eq
op_minus
l_int|1
op_logical_or
id|endpoint
(braket
l_int|0
)braket
dot
id|bmAttributes
op_ne
id|USB_ENDPOINT_XFER_BULK
op_logical_or
id|endpoint
(braket
l_int|1
)braket
dot
id|bmAttributes
op_ne
id|USB_ENDPOINT_XFER_BULK
)paren
(brace
id|dbg
(paren
l_string|&quot;Bogus endpoints&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usb_set_configuration
(paren
id|dev
comma
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|bConfigurationValue
)paren
)paren
(brace
id|err
(paren
l_string|&quot;Failed usb_set_configuration&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|camera-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
id|camera
suffix:semicolon
id|error
suffix:colon
id|minor_data
(braket
id|camera-&gt;subminor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
(paren
id|camera
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|camera_disconnect
r_static
r_void
id|camera_disconnect
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
id|camera_state
op_star
id|camera
op_assign
(paren
r_struct
id|camera_state
op_star
)paren
id|ptr
suffix:semicolon
r_int
id|subminor
op_assign
id|camera-&gt;subminor
suffix:semicolon
multiline_comment|/* If camera&squot;s not opened, we can clean up right away.&n;&t; * Else apps see a disconnect on next I/O; the release cleans.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|camera-&gt;buf
)paren
(brace
id|minor_data
(braket
id|subminor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
(paren
id|camera
)paren
suffix:semicolon
)brace
r_else
id|camera-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|info
(paren
l_string|&quot;USB Camera #%d disconnected&quot;
comma
id|subminor
)paren
suffix:semicolon
)brace
DECL|variable|camera_driver
r_static
multiline_comment|/* const */
r_struct
id|usb_driver
id|camera_driver
op_assign
(brace
l_string|&quot;dc2xx&quot;
comma
id|camera_probe
comma
id|camera_disconnect
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
op_amp
id|usb_camera_fops
comma
id|USB_CAMERA_MINOR_BASE
)brace
suffix:semicolon
DECL|function|usb_dc2xx_init
r_int
id|__init
id|usb_dc2xx_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|usb_register
(paren
op_amp
id|camera_driver
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_dc2xx_cleanup
r_void
id|__exit
id|usb_dc2xx_cleanup
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
(paren
op_amp
id|camera_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Brownell, david-b@pacbell.net&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;USB Camera Driver for Kodak DC-2xx series cameras&quot;
)paren
suffix:semicolon
DECL|variable|usb_dc2xx_init
id|module_init
(paren
id|usb_dc2xx_init
)paren
suffix:semicolon
DECL|variable|usb_dc2xx_cleanup
id|module_exit
(paren
id|usb_dc2xx_cleanup
)paren
suffix:semicolon
eof
