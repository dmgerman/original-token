multiline_comment|/*&n; * Driver for USB Scanners (linux-2.4.0test1-ac7)&n; *&n; * Copyright (C) 1999, 2000 David E. Nelson&n; *&n; * David E. Nelson (dnelson@jump.net)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
singleline_comment|// #define DEBUG
macro_line|#include &lt;linux/usb.h&gt;
DECL|variable|vendor
DECL|variable|product
r_static
id|__s32
id|vendor
op_assign
op_minus
l_int|1
comma
id|product
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David E. Nelson, dnelson@jump.net, http://www.jump.net/~dnelson&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;USB Scanner Driver&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vendor
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vendor
comma
l_string|&quot;User specified USB idVendor&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|product
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|product
comma
l_string|&quot;User specified USB idProduct&quot;
)paren
suffix:semicolon
multiline_comment|/* Enable to activate the ioctl interface.  This is mainly meant for */
multiline_comment|/* development purposes until an ioctl number is officially registered */
singleline_comment|// #define SCN_IOCTL
multiline_comment|/* WARNING: These DATA_DUMP&squot;s can produce a lot of data. Caveat Emptor. */
singleline_comment|// #define RD_DATA_DUMP /* Enable to dump data - limited to 24 bytes */
singleline_comment|// #define WR_DATA_DUMP /* DEBUG does not have to be defined. */
DECL|macro|IS_EP_BULK
mdefine_line|#define IS_EP_BULK(ep)  ((ep).bmAttributes == USB_ENDPOINT_XFER_BULK ? 1 : 0)
DECL|macro|IS_EP_BULK_IN
mdefine_line|#define IS_EP_BULK_IN(ep) (IS_EP_BULK(ep) &amp;&amp; ((ep).bEndpointAddress &amp; USB_ENDPOINT_DIR_MASK) == USB_DIR_IN)
DECL|macro|IS_EP_BULK_OUT
mdefine_line|#define IS_EP_BULK_OUT(ep) (IS_EP_BULK(ep) &amp;&amp; ((ep).bEndpointAddress &amp; USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT)
DECL|macro|IS_EP_INTR
mdefine_line|#define IS_EP_INTR(ep) ((ep).bmAttributes == USB_ENDPOINT_XFER_INT ? 1 : 0)
DECL|macro|USB_SCN_MINOR
mdefine_line|#define USB_SCN_MINOR(X) MINOR((X)-&gt;i_rdev) - SCN_BASE_MNR
macro_line|#ifdef DEBUG
DECL|macro|SCN_DEBUG
mdefine_line|#define SCN_DEBUG(X) X
macro_line|#else
DECL|macro|SCN_DEBUG
mdefine_line|#define SCN_DEBUG(X)
macro_line|#endif
DECL|macro|IBUF_SIZE
mdefine_line|#define IBUF_SIZE 32768
DECL|macro|OBUF_SIZE
mdefine_line|#define OBUF_SIZE 4096
multiline_comment|/* read_scanner timeouts -- RD_NAK_TIMEOUT * RD_EXPIRE = Number of seconds */
DECL|macro|RD_NAK_TIMEOUT
mdefine_line|#define RD_NAK_TIMEOUT (10*HZ)&t;/* Number of X seconds to wait */
DECL|macro|RD_EXPIRE
mdefine_line|#define RD_EXPIRE 12&t;&t;/* Number of attempts to wait X seconds */
multiline_comment|/* FIXME: These are NOT registered ioctls()&squot;s */
DECL|macro|PV8630_IOCTL_INREQUEST
mdefine_line|#define PV8630_IOCTL_INREQUEST 69
DECL|macro|PV8630_IOCTL_OUTREQUEST
mdefine_line|#define PV8630_IOCTL_OUTREQUEST 70
DECL|macro|SCN_MAX_MNR
mdefine_line|#define SCN_MAX_MNR 16&t;&t;/* We&squot;re allocated 16 minors */
DECL|macro|SCN_BASE_MNR
mdefine_line|#define SCN_BASE_MNR 48&t;&t;/* USB Scanners start at minor 48 */
DECL|struct|scn_usb_data
r_struct
id|scn_usb_data
(brace
DECL|member|scn_dev
r_struct
id|usb_device
op_star
id|scn_dev
suffix:semicolon
DECL|member|scn_irq
r_struct
id|urb
id|scn_irq
suffix:semicolon
DECL|member|ifnum
r_int
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* Interface number of the USB device */
DECL|member|scn_minor
id|kdev_t
id|scn_minor
suffix:semicolon
multiline_comment|/* Scanner minor - used in disconnect() */
DECL|member|button
r_int
r_char
id|button
suffix:semicolon
multiline_comment|/* Front panel buffer */
DECL|member|isopen
r_char
id|isopen
suffix:semicolon
multiline_comment|/* Not zero if the device is open */
DECL|member|present
r_char
id|present
suffix:semicolon
multiline_comment|/* Not zero if device is present */
DECL|member|obuf
DECL|member|ibuf
r_char
op_star
id|obuf
comma
op_star
id|ibuf
suffix:semicolon
multiline_comment|/* transfer buffers */
DECL|member|bulk_in_ep
DECL|member|bulk_out_ep
DECL|member|intr_ep
r_char
id|bulk_in_ep
comma
id|bulk_out_ep
comma
id|intr_ep
suffix:semicolon
multiline_comment|/* Endpoint assignments */
DECL|member|rd_wait_q
id|wait_queue_head_t
id|rd_wait_q
suffix:semicolon
multiline_comment|/* read timeouts */
)brace
suffix:semicolon
DECL|variable|p_scn_table
r_static
r_struct
id|scn_usb_data
op_star
id|p_scn_table
(braket
id|SCN_MAX_MNR
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
multiline_comment|/* table of scanners that may work with this driver */
DECL|struct|scanner_device
r_static
r_const
r_struct
id|scanner_device
(brace
DECL|member|idVendor
id|__u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__u16
id|idProduct
suffix:semicolon
DECL|variable|scanner_device_ids
)brace
id|scanner_device_ids
(braket
)braket
op_assign
(brace
multiline_comment|/* Acer */
(brace
l_int|0x04a5
comma
l_int|0x2060
)brace
comma
multiline_comment|/* Prisa Acerscan 620U &amp; 640U (!) */
(brace
l_int|0x04a5
comma
l_int|0x2040
)brace
comma
multiline_comment|/* Prisa AcerScan 620U (!) */
multiline_comment|/* Agfa */
(brace
l_int|0x06bd
comma
l_int|0x0001
)brace
comma
multiline_comment|/* SnapScan 1212U */
(brace
l_int|0x06bd
comma
l_int|0x2061
)brace
comma
multiline_comment|/* Another SnapScan 1212U (?) */
(brace
l_int|0x06bd
comma
l_int|0x0100
)brace
comma
multiline_comment|/* SnapScan Touch */
multiline_comment|/* Colorado -- See Primax/Colorado below */
multiline_comment|/* Epson -- See Seiko/Epson below */
multiline_comment|/* Genius */
(brace
l_int|0x0458
comma
l_int|0x2001
)brace
comma
multiline_comment|/* ColorPage-Vivid Pro */
multiline_comment|/* Hewlett Packard */
(brace
l_int|0x03f0
comma
l_int|0x0205
)brace
comma
multiline_comment|/* 3300C */
(brace
l_int|0x03f0
comma
l_int|0x0101
)brace
comma
multiline_comment|/* 4100C */
(brace
l_int|0x03f0
comma
l_int|0x0105
)brace
comma
multiline_comment|/* 4200C */
(brace
l_int|0x03f0
comma
l_int|0x0102
)brace
comma
multiline_comment|/* PhotoSmart S20 */
(brace
l_int|0x03f0
comma
l_int|0x0401
)brace
comma
multiline_comment|/* 5200C */
(brace
l_int|0x03f0
comma
l_int|0x0201
)brace
comma
multiline_comment|/* 6200C */
(brace
l_int|0x03f0
comma
l_int|0x0601
)brace
comma
multiline_comment|/* 6300C */
multiline_comment|/* iVina */
(brace
l_int|0x0638
comma
l_int|0x0268
)brace
comma
multiline_comment|/* 1200U */
multiline_comment|/* Microtek */
(brace
l_int|0x05da
comma
l_int|0x0099
)brace
comma
multiline_comment|/* ScanMaker X6 - X6U */
(brace
l_int|0x05da
comma
l_int|0x0094
)brace
comma
multiline_comment|/* Phantom 336CX - C3 */
(brace
l_int|0x05da
comma
l_int|0x00a0
)brace
comma
multiline_comment|/* Phantom 336CX - C3 #2 */
(brace
l_int|0x05da
comma
l_int|0x009a
)brace
comma
multiline_comment|/* Phantom C6 */
(brace
l_int|0x05da
comma
l_int|0x00a3
)brace
comma
multiline_comment|/* ScanMaker V6USL */
(brace
l_int|0x05da
comma
l_int|0x80a3
)brace
comma
multiline_comment|/* ScanMaker V6USL #2 */
(brace
l_int|0x05da
comma
l_int|0x80ac
)brace
comma
multiline_comment|/* ScanMaker V6UL - SpicyU */
multiline_comment|/* Mustek */
(brace
l_int|0x055f
comma
l_int|0x0001
)brace
comma
multiline_comment|/* 1200 CU */
multiline_comment|/* Primax/Colorado */
(brace
l_int|0x0461
comma
l_int|0x0300
)brace
comma
multiline_comment|/* G2-300 #1 */
(brace
l_int|0x0461
comma
l_int|0x0380
)brace
comma
multiline_comment|/* G2-600 #1 */
(brace
l_int|0x0461
comma
l_int|0x0301
)brace
comma
multiline_comment|/* G2E-300 #1 */
(brace
l_int|0x0461
comma
l_int|0x0381
)brace
comma
multiline_comment|/* ReadyScan 636i */
(brace
l_int|0x0461
comma
l_int|0x0302
)brace
comma
multiline_comment|/* G2-300 #2 */
(brace
l_int|0x0461
comma
l_int|0x0382
)brace
comma
multiline_comment|/* G2-600 #2 */
(brace
l_int|0x0461
comma
l_int|0x0303
)brace
comma
multiline_comment|/* G2E-300 #2 */
(brace
l_int|0x0461
comma
l_int|0x0383
)brace
comma
multiline_comment|/* G2E-600 */
(brace
l_int|0x0461
comma
l_int|0x0340
)brace
comma
multiline_comment|/* Colorado USB 9600 */
(brace
l_int|0x0461
comma
l_int|0x0360
)brace
comma
multiline_comment|/* Colorado USB 19200 */
(brace
l_int|0x0461
comma
l_int|0x0341
)brace
comma
multiline_comment|/* Colorado 600u */
(brace
l_int|0x0461
comma
l_int|0x0361
)brace
comma
multiline_comment|/* Colorado 1200u */
multiline_comment|/* Seiko/Epson Corp. */
(brace
l_int|0x04b8
comma
l_int|0x0101
)brace
comma
multiline_comment|/* Perfection 636U and 636Photo */
(brace
l_int|0x04b8
comma
l_int|0x0103
)brace
comma
multiline_comment|/* Perfection 610 */
(brace
l_int|0x04b8
comma
l_int|0x0104
)brace
comma
multiline_comment|/* Perfection 1200U and 1200Photo */
multiline_comment|/* Umax */
(brace
l_int|0x1606
comma
l_int|0x0010
)brace
comma
multiline_comment|/* Astra 1220U */
(brace
l_int|0x1606
comma
l_int|0x0002
)brace
comma
multiline_comment|/* Astra 1236U */
(brace
l_int|0x1606
comma
l_int|0x0030
)brace
comma
multiline_comment|/* Astra 2000U */
(brace
l_int|0x1606
comma
l_int|0x0230
)brace
comma
multiline_comment|/* Astra 2200U */
multiline_comment|/* Visioneer */
(brace
l_int|0x04a7
comma
l_int|0x0221
)brace
comma
multiline_comment|/* OneTouch 5300 */
(brace
l_int|0x04a7
comma
l_int|0x0221
)brace
comma
multiline_comment|/* OneTouch 7600 duplicate ID (!) */
(brace
l_int|0x04a7
comma
l_int|0x0231
)brace
comma
multiline_comment|/* 6100 */
)brace
suffix:semicolon
multiline_comment|/* Forward declarations */
DECL|variable|scanner_driver
r_static
r_struct
id|usb_driver
id|scanner_driver
suffix:semicolon
eof
