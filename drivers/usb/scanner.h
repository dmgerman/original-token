macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
singleline_comment|// #define DEBUG
multiline_comment|/* Enable to activate the ioctl interface.  This is mainly meant for */
multiline_comment|/* development purposes until an ioctl number is officially registered */
singleline_comment|// #define SCN_IOCTL
macro_line|#include &lt;linux/usb.h&gt;
singleline_comment|// #include &quot;usb.h&quot;
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
multiline_comment|/* Forward declarations */
DECL|variable|scanner_driver
r_static
r_struct
id|usb_driver
id|scanner_driver
suffix:semicolon
eof
