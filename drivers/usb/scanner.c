multiline_comment|/* -*- linux-c -*- */
multiline_comment|/* &n; * Driver for USB Scanners (linux-2.3.41)&n; *&n; * Copyright (C) 1999, 2000 David E. Nelson&n; *&n; * Portions may be copyright Brad Keryan and Michael Gee.&n; *&n; * David E. Nelson (dnelson@jump.net)&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Originally based upon mouse.c (Brad Keryan) and printer.c (Michael Gee).&n; *&n; * History&n; *&n; *  0.1  8/31/1999&n; *&n; *    Developed/tested using linux-2.3.15 with minor ohci.c changes to&n; *    support short packes during bulk xfer mode.  Some testing was&n; *    done with ohci-hcd but the performace was low.  Very limited&n; *    testing was performed with uhci but I was unable to get it to&n; *    work.  Initial relase to the linux-usb development effort.&n; *&n; *&n; *  0.2  10/16/1999&n; *&n; *    - Device can&squot;t be opened unless a scanner is plugged into the USB.&n; *    - Finally settled on a reasonable value for the I/O buffer&squot;s.&n; *    - Cleaned up write_scanner()&n; *    - Disabled read/write stats&n; *    - A little more code cleanup&n; *&n; *&n; *  0.3  10/18/1999&n; *&n; *    - Device registration changed to reflect new device&n; *      allocation/registration for linux-2.3.22+.&n; *    - Adopted David Brownell&squot;s &lt;david-b@pacbell.net&gt; technique for &n; *      assigning bulk endpoints.&n; *    - Removed unnessesary #include&squot;s&n; *    - Scanner model now reported via syslog INFO after being detected &n; *      *and* configured.&n; *    - Added user specified verdor:product USB ID&squot;s which can be passed &n; *      as module parameters.&n; *&n; *&n; *  0.3.1&n; *&n; *    - Applied patches for linux-2.3.25.&n; *    - Error number reporting changed to reflect negative return codes.&n; *&n; *&n; *  0.3.2&n; *&n; *    - Applied patches for linux-2.3.26 to scanner_init().&n; *    - Debug read/write stats now report values as signed decimal.&n; *&n; *&n; *  0.3.3&n; *&n; *    - Updated the bulk_msg() calls to usb usb_bulk_msg().&n; *    - Added a small delay in the write_scanner() method to aid in&n; *      avoiding NULL data reads on HP scanners.  We&squot;ll see how this works.&n; *    - Return values from usb_bulk_msg() now ignore positive values for&n; *      use with the ohci driver.&n; *    - Added conditional debugging instead of commenting/uncommenting&n; *      all over the place.&n; *    - kfree()&squot;d the pointer after using usb_string() as documented in&n; *      linux-usb-api.txt.&n; *    - Added usb_set_configuration().  It got lost in version 0.3 -- ack!&n; *    - Added the HP 5200C USB Vendor/Product ID&squot;s.&n; *&n; *&n; *  0.3.4&n; *&n; *    - Added Greg K-H&squot;s &lt;greg@kroah.com&gt; patch for better handling of &n; *      Product/Vendor detection.&n; *    - The driver now autoconfigures its endpoints including interrupt&n; *      endpoints if one is detected.  The concept was originally based&n; *      upon David Brownell&squot;s method.&n; *    - Added some Seiko/Epson ID&squot;s. Thanks to Karl Heinz &n; *      Kremer &lt;khk@khk.net&gt;.&n; *    - Added some preliminary ioctl() calls for the PV8630 which is used&n; *      by the HP4200. The ioctl()&squot;s still have to be registered. Thanks &n; *      to Adrian Perez Jorge &lt;adrianpj@easynews.com&gt;.&n; *    - Moved/migrated stuff to scanner.h&n; *    - Removed the usb_set_configuration() since this is handled by&n; *      the usb_new_device() routine in usb.c.&n; *    - Added the HP 3300C.  Thanks to Bruce Tenison.&n; *    - Changed user specified vendor/product id so that root hub doesn&squot;t&n; *      get falsely attached to. Thanks to Greg K-H.&n; *    - Added some Mustek ID&squot;s. Thanks to Gernot Hoyler &n; *      &lt;Dr.Hoyler@t-online.de&gt;.&n; *    - Modified the usb_string() reporting.  See kfree() comment above.&n; *    - Added Umax Astra 2000U. Thanks to Doug Alcorn.&n; *    - Updated the printk()&squot;s to use the info/warn/dbg macros.&n; *    - Updated usb_bulk_msg() argument types to correct gcc warnings.&n; *&n; *&n; *  TODO&n; *&n; *    - Simultaneous multiple device attachment&n; *&n; *&n; *  Thanks to:&n; *&n; *    - All the folks on the linux-usb list who put up with me. :)  This &n; *      has been a great learning experience for me.&n; *    - To Linus Torvalds for this great OS.&n; *    - The GNU folks.&n; *    - The folks that forwarded Vendor:Product ID&squot;s to me.&n; *    - And anybody else who chimed in with reports and suggestions.&n; *&n; *  Performance:&n; *&n; *    System: Pentium 120, 80 MB RAM, OHCI, Linux 2.3.23, HP 4100C USB Scanner&n; *            300 dpi scan of the entire bed&n; *      24 Bit Color ~ 70 secs - 3.6 Mbit/sec&n; *       8 Bit Gray  ~ 17 secs - 4.2 Mbit/sec&n; * */
macro_line|#include &quot;scanner.h&quot;
r_static
r_int
DECL|function|open_scanner
id|open_scanner
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
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|hps-&gt;hpscan_dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
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
id|hps-&gt;present
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
id|hps-&gt;isopen
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|hps-&gt;isopen
op_assign
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|close_scanner
id|close_scanner
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
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
id|hps-&gt;isopen
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|write_scanner
id|write_scanner
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
r_struct
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
id|ssize_t
id|bytes_written
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|copy_size
suffix:semicolon
r_int
id|partial
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|obuf
op_assign
id|hps-&gt;obuf
suffix:semicolon
id|dev
op_assign
id|hps-&gt;hpscan_dev
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
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
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|copy_size
op_assign
(paren
id|count
OG
id|OBUF_SIZE
)paren
ques
c_cond
id|OBUF_SIZE
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|hps-&gt;obuf
comma
id|buffer
comma
id|copy_size
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
id|usb_bulk_msg
c_func
(paren
id|dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dev
comma
id|hps-&gt;bulk_out_ep
)paren
comma
id|obuf
comma
id|copy_size
comma
op_amp
id|partial
comma
l_int|60
op_star
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;write stats: result:%d copy_size:%d partial:%d&quot;
comma
id|result
comma
id|copy_size
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|USB_ST_TIMEOUT
)paren
(brace
multiline_comment|/* NAK -- shouldn&squot;t happen */
id|warn
c_func
(paren
l_string|&quot;write_scanner: NAK recieved.&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ETIME
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
multiline_comment|/* We should not get any I/O errors */
id|warn
c_func
(paren
l_string|&quot;write_scanner: funky result: %d. Please notify the maintainer.&quot;
comma
id|result
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef WR_DATA_DUMP
r_if
c_cond
(paren
id|partial
)paren
(brace
r_int
r_char
id|cnt
comma
id|cnt_max
suffix:semicolon
id|cnt_max
op_assign
(paren
id|partial
OG
l_int|24
)paren
ques
c_cond
l_int|24
suffix:colon
id|partial
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dump: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|cnt_max
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%X &quot;
comma
id|obuf
(braket
id|cnt
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|partial
op_ne
id|copy_size
)paren
(brace
multiline_comment|/* Unable to write complete amount */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
)paren
(brace
multiline_comment|/* Data written */
id|obuf
op_add_assign
id|partial
suffix:semicolon
id|count
op_sub_assign
id|partial
suffix:semicolon
id|bytes_written
op_add_assign
id|partial
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No data written */
id|ret
op_assign
l_int|0
suffix:semicolon
id|bytes_written
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
id|bytes_written
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|read_scanner
id|read_scanner
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
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
id|ssize_t
id|read_count
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|partial
suffix:semicolon
r_int
id|this_read
suffix:semicolon
r_int
id|result
suffix:semicolon
r_char
op_star
id|ibuf
op_assign
id|hps-&gt;ibuf
suffix:semicolon
id|dev
op_assign
id|hps-&gt;hpscan_dev
suffix:semicolon
id|read_count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
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
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|this_read
op_assign
(paren
id|count
OG
id|IBUF_SIZE
)paren
ques
c_cond
id|IBUF_SIZE
suffix:colon
id|count
suffix:semicolon
id|result
op_assign
id|usb_bulk_msg
c_func
(paren
id|dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dev
comma
id|hps-&gt;bulk_in_ep
)paren
comma
id|ibuf
comma
id|this_read
comma
op_amp
id|partial
comma
l_int|60
op_star
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;read stats: result:%d this_read:%d partial:%d&quot;
comma
id|result
comma
id|this_read
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|USB_ST_TIMEOUT
)paren
(brace
multiline_comment|/* NAK -- shouldn&squot;t happen */
id|warn
c_func
(paren
l_string|&quot;read_scanner: NAK received&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ETIME
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|result
OL
l_int|0
)paren
op_logical_and
(paren
id|result
op_ne
id|USB_ST_DATAUNDERRUN
)paren
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;read_scanner: funky result: %d. Please notify the maintainer.&quot;
comma
(paren
r_int
)paren
id|result
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef RD_DATA_DUMP
r_if
c_cond
(paren
id|partial
)paren
(brace
r_int
r_char
id|cnt
comma
id|cnt_max
suffix:semicolon
id|cnt_max
op_assign
(paren
id|partial
OG
l_int|24
)paren
ques
c_cond
l_int|24
suffix:colon
id|partial
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dump: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|cnt_max
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%X &quot;
comma
id|ibuf
(braket
id|cnt
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|partial
)paren
(brace
multiline_comment|/* Data returned */
id|count
op_assign
id|this_read
op_assign
id|partial
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|read_count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_read
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|ibuf
comma
id|this_read
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|count
op_sub_assign
id|this_read
suffix:semicolon
id|read_count
op_add_assign
id|this_read
suffix:semicolon
id|buffer
op_add_assign
id|this_read
suffix:semicolon
)brace
)brace
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
id|read_count
suffix:semicolon
)brace
r_static
r_void
op_star
DECL|function|probe_scanner
id|probe_scanner
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
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
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
id|ep_cnt
suffix:semicolon
r_char
id|valid_device
op_assign
l_int|0
suffix:semicolon
r_char
id|have_bulk_in
comma
id|have_bulk_out
comma
id|have_intr
suffix:semicolon
id|hps-&gt;present
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_ne
op_minus
l_int|1
op_logical_and
id|product
op_ne
op_minus
l_int|1
)paren
(brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: User specified USB scanner -- Vendor:Product - %x:%x&quot;
comma
id|vendor
comma
id|product
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * 1. Check Vendor/Product&n; * 2. Determine/Assign Bulk Endpoints&n; * 3. Determine/Assign Intr Endpoint&n; */
multiline_comment|/* &n; * There doesn&squot;t seem to be an imaging class defined in the USB&n; * Spec. (yet).  If there is, HP isn&squot;t following it and it doesn&squot;t&n; * look like anybody else is either.  Therefore, we have to test the&n; * Vendor and Product ID&squot;s to see what we have.  Also, other scanners&n; * may be able to use this driver by specifying both vendor and&n; * product ID&squot;s as options to the scanner module in conf.modules.&n; *&n; * NOTE: Just because a product is supported here does not mean that&n; * applications exist that support the product.  It&squot;s in the hopes&n; * that this will allow developers a means to produce applications&n; * that will support USB products.&n; *&n; * Until we detect a device which is pleasing, we silently punt.  */
r_do
(brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
l_int|0x03f0
)paren
(brace
multiline_comment|/* Hewlett Packard */
r_if
c_cond
(paren
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0205
op_logical_or
multiline_comment|/* 3300C */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0101
op_logical_or
multiline_comment|/* 4100C */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0105
op_logical_or
multiline_comment|/* 4200C */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0202
op_logical_or
multiline_comment|/* PhotoSmart S20 */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0401
op_logical_or
multiline_comment|/* 5200C */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0201
op_logical_or
multiline_comment|/* 6200C */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0601
)paren
(brace
multiline_comment|/* 6300C */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
l_int|0x06bd
op_logical_and
multiline_comment|/* AGFA */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0001
)paren
(brace
multiline_comment|/* SnapScan 1212U */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
l_int|0x1606
op_logical_and
multiline_comment|/* Umax */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0030
)paren
(brace
multiline_comment|/* Astra 2000U */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
l_int|0x04b8
)paren
(brace
multiline_comment|/* Seiko/Epson Corp. */
r_if
c_cond
(paren
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0101
op_logical_or
multiline_comment|/* Perfection 636 */
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0104
)paren
(brace
multiline_comment|/* Perfection 1200U */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
l_int|0x055f
)paren
(brace
multiline_comment|/* Mustek */
r_if
c_cond
(paren
id|dev-&gt;descriptor.idProduct
op_eq
l_int|0x0001
)paren
(brace
multiline_comment|/* 1200 CU */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.idVendor
op_eq
id|vendor
op_logical_and
multiline_comment|/* User specified */
id|dev-&gt;descriptor.idProduct
op_eq
id|product
)paren
(brace
multiline_comment|/* User specified */
id|valid_device
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valid_device
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * After this point we can be a little noisy about what we are trying to&n; *  configure.&n; */
r_if
c_cond
(paren
id|dev-&gt;descriptor.bNumConfigurations
op_ne
l_int|1
)paren
(brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: Only one configuration is supported.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
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
id|info
c_func
(paren
l_string|&quot;probe_scanner: Only one interface is supported.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|interface
op_assign
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|interface
(braket
l_int|0
)braket
dot
id|altsetting
suffix:semicolon
id|endpoint
op_assign
id|interface
(braket
l_int|0
)braket
dot
id|endpoint
suffix:semicolon
multiline_comment|/* &n; * Start checking for two bulk endpoints OR two bulk endpoints *and* one&n; * interrupt endpoint. If we have an interrupt endpoint go ahead and&n; * setup the handler. FIXME: This is a future enhancement...&n; */
id|dbg
c_func
(paren
l_string|&quot;probe_scanner: Number of Endpoints: %d&quot;
comma
(paren
r_int
)paren
id|interface-&gt;bNumEndpoints
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|interface-&gt;bNumEndpoints
op_ne
l_int|2
)paren
op_logical_and
(paren
id|interface-&gt;bNumEndpoints
op_ne
l_int|3
)paren
)paren
(brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: Only two or three endpoints supported.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ep_cnt
op_assign
id|have_bulk_in
op_assign
id|have_bulk_out
op_assign
id|have_intr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ep_cnt
OL
id|interface-&gt;bNumEndpoints
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|have_bulk_in
op_logical_and
id|IS_EP_BULK_IN
c_func
(paren
id|endpoint
(braket
id|ep_cnt
)braket
)paren
)paren
(brace
id|have_bulk_in
op_assign
l_int|1
suffix:semicolon
id|hps-&gt;bulk_in_ep
op_assign
id|ep_cnt
op_plus
l_int|1
suffix:semicolon
id|ep_cnt
op_increment
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;probe_scanner: bulk_in_ep: %d&quot;
comma
(paren
r_int
)paren
id|hps-&gt;bulk_in_ep
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_bulk_out
op_logical_and
id|IS_EP_BULK_OUT
c_func
(paren
id|endpoint
(braket
id|ep_cnt
)braket
)paren
)paren
(brace
id|have_bulk_out
op_assign
l_int|1
suffix:semicolon
id|hps-&gt;bulk_out_ep
op_assign
id|ep_cnt
op_plus
l_int|1
suffix:semicolon
id|ep_cnt
op_increment
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;probe_scanner: bulk_out_ep: %d&quot;
comma
(paren
r_int
)paren
id|hps-&gt;bulk_out_ep
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_intr
op_logical_and
id|IS_EP_INTR
c_func
(paren
id|endpoint
(braket
id|ep_cnt
)braket
)paren
)paren
(brace
id|have_intr
op_assign
l_int|1
suffix:semicolon
id|hps-&gt;intr_ep
op_assign
id|ep_cnt
op_plus
l_int|1
suffix:semicolon
id|ep_cnt
op_increment
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;probe_scanner: intr_ep: %d&quot;
comma
(paren
r_int
)paren
id|hps-&gt;intr_ep
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: Undetected endpoint. Notify the maintainer.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Shouldn&squot;t ever get here unless we have something weird */
)brace
r_switch
c_cond
(paren
id|interface-&gt;bNumEndpoints
)paren
(brace
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|have_bulk_in
op_logical_or
op_logical_neg
id|have_bulk_out
)paren
(brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: Two bulk endpoints required.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|have_bulk_in
op_logical_or
op_logical_neg
id|have_bulk_out
op_logical_or
op_logical_neg
id|have_intr
)paren
(brace
id|info
c_func
(paren
l_string|&quot;probe_scanner: Two bulk endpoints and one interrupt endpoint required.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|info
c_func
(paren
l_string|&quot;probe_scanner: Endpoint determination failed.  Notify the maintainer.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|hps-&gt;present
op_assign
l_int|1
suffix:semicolon
id|hps-&gt;hpscan_dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hps-&gt;obuf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|OBUF_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hps-&gt;ibuf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|IBUF_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|hps
suffix:semicolon
)brace
r_static
r_void
DECL|function|disconnect_scanner
id|disconnect_scanner
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
id|hpscan_usb_data
op_star
id|hps
op_assign
(paren
r_struct
id|hpscan_usb_data
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|hps-&gt;isopen
)paren
(brace
multiline_comment|/* better let it finish - the release will do whats needed */
id|hps-&gt;hpscan_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|hps-&gt;ibuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hps-&gt;obuf
)paren
suffix:semicolon
id|hps-&gt;present
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ioctl_scanner
id|ioctl_scanner
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dev
op_assign
id|hps-&gt;hpscan_dev
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PV8630_RECEIVE
suffix:colon
(brace
r_struct
(brace
r_int
r_char
id|data
suffix:semicolon
id|__u16
id|value
suffix:semicolon
id|__u16
id|index
suffix:semicolon
)brace
id|args
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|args
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|args
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
l_int|0x0
comma
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
op_or
id|USB_DIR_IN
comma
id|args.value
comma
id|args.index
comma
op_amp
id|args.data
comma
l_int|1
comma
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ioctl_scanner recv: args.data:%x args.value:%x args.index:%x&quot;
comma
id|args.data
comma
id|args.value
comma
id|args.index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|args
comma
r_sizeof
(paren
id|args
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ioctl_scanner recv: result:%d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_case
id|PV8630_SEND
suffix:colon
(brace
r_struct
(brace
id|__u16
id|value
suffix:semicolon
id|__u16
id|index
suffix:semicolon
)brace
id|args
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|args
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|args
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ioctl_scanner send: args.value:%x args.index:%x&quot;
comma
id|args.value
comma
id|args.index
)paren
suffix:semicolon
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
l_int|0x1
multiline_comment|/* Vendor Specific bRequest */
comma
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
op_or
id|USB_DIR_OUT
multiline_comment|/* 0x40 */
comma
id|args.value
comma
id|args.index
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ioctl_scanner send: result:%d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
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
r_static
r_struct
DECL|variable|usb_scanner_fops
id|file_operations
id|usb_scanner_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* seek */
id|read_scanner
comma
id|write_scanner
comma
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
id|ioctl_scanner
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|open_scanner
comma
l_int|NULL
comma
multiline_comment|/* flush */
id|close_scanner
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* fasync */
)brace
suffix:semicolon
r_static
r_struct
DECL|variable|scanner_driver
id|usb_driver
id|scanner_driver
op_assign
(brace
l_string|&quot;usbscanner&quot;
comma
id|probe_scanner
comma
id|disconnect_scanner
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
op_amp
id|usb_scanner_fops
comma
l_int|48
)brace
suffix:semicolon
r_int
DECL|function|usb_scanner_init
id|usb_scanner_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|scanner_driver
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USB Scanner support registered.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|usb_scanner_cleanup
id|usb_scanner_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|hpscan_usb_data
op_star
id|hps
op_assign
op_amp
id|hpscan
suffix:semicolon
id|hps-&gt;present
op_assign
l_int|0
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|scanner_driver
)paren
suffix:semicolon
)brace
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
id|usb_scanner_init
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
id|usb_scanner_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
