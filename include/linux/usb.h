macro_line|#ifndef __LINUX_USB_H
DECL|macro|__LINUX_USB_H
mdefine_line|#define __LINUX_USB_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;&t;/* for in_interrupt() */
multiline_comment|/* USB constants */
multiline_comment|/*&n; * Device and/or Interface Class codes&n; */
DECL|macro|USB_CLASS_PER_INTERFACE
mdefine_line|#define USB_CLASS_PER_INTERFACE&t;&t;0&t;/* for DeviceClass */
DECL|macro|USB_CLASS_AUDIO
mdefine_line|#define USB_CLASS_AUDIO&t;&t;&t;1
DECL|macro|USB_CLASS_COMM
mdefine_line|#define USB_CLASS_COMM&t;&t;&t;2
DECL|macro|USB_CLASS_HID
mdefine_line|#define USB_CLASS_HID&t;&t;&t;3
DECL|macro|USB_CLASS_PRINTER
mdefine_line|#define USB_CLASS_PRINTER&t;&t;7
DECL|macro|USB_CLASS_MASS_STORAGE
mdefine_line|#define USB_CLASS_MASS_STORAGE&t;&t;8
DECL|macro|USB_CLASS_HUB
mdefine_line|#define USB_CLASS_HUB&t;&t;&t;9
DECL|macro|USB_CLASS_DATA
mdefine_line|#define USB_CLASS_DATA&t;&t;&t;10
DECL|macro|USB_CLASS_VENDOR_SPEC
mdefine_line|#define USB_CLASS_VENDOR_SPEC&t;&t;0xff
multiline_comment|/*&n; * USB types&n; */
DECL|macro|USB_TYPE_STANDARD
mdefine_line|#define USB_TYPE_STANDARD&t;&t;(0x00 &lt;&lt; 5)
DECL|macro|USB_TYPE_CLASS
mdefine_line|#define USB_TYPE_CLASS&t;&t;&t;(0x01 &lt;&lt; 5)
DECL|macro|USB_TYPE_VENDOR
mdefine_line|#define USB_TYPE_VENDOR&t;&t;&t;(0x02 &lt;&lt; 5)
DECL|macro|USB_TYPE_RESERVED
mdefine_line|#define USB_TYPE_RESERVED&t;&t;(0x03 &lt;&lt; 5)
multiline_comment|/*&n; * USB recipients&n; */
DECL|macro|USB_RECIP_DEVICE
mdefine_line|#define USB_RECIP_DEVICE&t;&t;0x00
DECL|macro|USB_RECIP_INTERFACE
mdefine_line|#define USB_RECIP_INTERFACE&t;&t;0x01
DECL|macro|USB_RECIP_ENDPOINT
mdefine_line|#define USB_RECIP_ENDPOINT&t;&t;0x02
DECL|macro|USB_RECIP_OTHER
mdefine_line|#define USB_RECIP_OTHER&t;&t;&t;0x03
multiline_comment|/*&n; * USB directions&n; */
DECL|macro|USB_DIR_OUT
mdefine_line|#define USB_DIR_OUT&t;&t;&t;0
DECL|macro|USB_DIR_IN
mdefine_line|#define USB_DIR_IN&t;&t;&t;0x80
multiline_comment|/*&n; * Descriptor types&n; */
DECL|macro|USB_DT_DEVICE
mdefine_line|#define USB_DT_DEVICE&t;&t;&t;0x01
DECL|macro|USB_DT_CONFIG
mdefine_line|#define USB_DT_CONFIG&t;&t;&t;0x02
DECL|macro|USB_DT_STRING
mdefine_line|#define USB_DT_STRING&t;&t;&t;0x03
DECL|macro|USB_DT_INTERFACE
mdefine_line|#define USB_DT_INTERFACE&t;&t;0x04
DECL|macro|USB_DT_ENDPOINT
mdefine_line|#define USB_DT_ENDPOINT&t;&t;&t;0x05
DECL|macro|USB_DT_HID
mdefine_line|#define USB_DT_HID&t;&t;&t;(USB_TYPE_CLASS | 0x01)
DECL|macro|USB_DT_REPORT
mdefine_line|#define USB_DT_REPORT&t;&t;&t;(USB_TYPE_CLASS | 0x02)
DECL|macro|USB_DT_PHYSICAL
mdefine_line|#define USB_DT_PHYSICAL&t;&t;&t;(USB_TYPE_CLASS | 0x03)
DECL|macro|USB_DT_HUB
mdefine_line|#define USB_DT_HUB&t;&t;&t;(USB_TYPE_CLASS | 0x09)
multiline_comment|/*&n; * Descriptor sizes per descriptor type&n; */
DECL|macro|USB_DT_DEVICE_SIZE
mdefine_line|#define USB_DT_DEVICE_SIZE&t;&t;18
DECL|macro|USB_DT_CONFIG_SIZE
mdefine_line|#define USB_DT_CONFIG_SIZE&t;&t;9
DECL|macro|USB_DT_INTERFACE_SIZE
mdefine_line|#define USB_DT_INTERFACE_SIZE&t;&t;9
DECL|macro|USB_DT_ENDPOINT_SIZE
mdefine_line|#define USB_DT_ENDPOINT_SIZE&t;&t;7
DECL|macro|USB_DT_ENDPOINT_AUDIO_SIZE
mdefine_line|#define USB_DT_ENDPOINT_AUDIO_SIZE&t;9&t;/* Audio extension */
DECL|macro|USB_DT_HUB_NONVAR_SIZE
mdefine_line|#define USB_DT_HUB_NONVAR_SIZE&t;&t;7
DECL|macro|USB_DT_HID_SIZE
mdefine_line|#define USB_DT_HID_SIZE&t;&t;&t;9
multiline_comment|/*&n; * Endpoints&n; */
DECL|macro|USB_ENDPOINT_NUMBER_MASK
mdefine_line|#define USB_ENDPOINT_NUMBER_MASK&t;0x0f&t;/* in bEndpointAddress */
DECL|macro|USB_ENDPOINT_DIR_MASK
mdefine_line|#define USB_ENDPOINT_DIR_MASK&t;&t;0x80
DECL|macro|USB_ENDPOINT_XFERTYPE_MASK
mdefine_line|#define USB_ENDPOINT_XFERTYPE_MASK&t;0x03&t;/* in bmAttributes */
DECL|macro|USB_ENDPOINT_XFER_CONTROL
mdefine_line|#define USB_ENDPOINT_XFER_CONTROL&t;0
DECL|macro|USB_ENDPOINT_XFER_ISOC
mdefine_line|#define USB_ENDPOINT_XFER_ISOC&t;&t;1
DECL|macro|USB_ENDPOINT_XFER_BULK
mdefine_line|#define USB_ENDPOINT_XFER_BULK&t;&t;2
DECL|macro|USB_ENDPOINT_XFER_INT
mdefine_line|#define USB_ENDPOINT_XFER_INT&t;&t;3
multiline_comment|/*&n; * USB Packet IDs (PIDs)&n; */
DECL|macro|USB_PID_UNDEF_0
mdefine_line|#define USB_PID_UNDEF_0                        0xf0
DECL|macro|USB_PID_OUT
mdefine_line|#define USB_PID_OUT                            0xe1
DECL|macro|USB_PID_ACK
mdefine_line|#define USB_PID_ACK                            0xd2
DECL|macro|USB_PID_DATA0
mdefine_line|#define USB_PID_DATA0                          0xc3
DECL|macro|USB_PID_UNDEF_4
mdefine_line|#define USB_PID_UNDEF_4                        0xb4
DECL|macro|USB_PID_SOF
mdefine_line|#define USB_PID_SOF                            0xa5
DECL|macro|USB_PID_UNDEF_6
mdefine_line|#define USB_PID_UNDEF_6                        0x96
DECL|macro|USB_PID_UNDEF_7
mdefine_line|#define USB_PID_UNDEF_7                        0x87
DECL|macro|USB_PID_UNDEF_8
mdefine_line|#define USB_PID_UNDEF_8                        0x78
DECL|macro|USB_PID_IN
mdefine_line|#define USB_PID_IN                             0x69
DECL|macro|USB_PID_NAK
mdefine_line|#define USB_PID_NAK                            0x5a
DECL|macro|USB_PID_DATA1
mdefine_line|#define USB_PID_DATA1                          0x4b
DECL|macro|USB_PID_PREAMBLE
mdefine_line|#define USB_PID_PREAMBLE                       0x3c
DECL|macro|USB_PID_SETUP
mdefine_line|#define USB_PID_SETUP                          0x2d
DECL|macro|USB_PID_STALL
mdefine_line|#define USB_PID_STALL                          0x1e
DECL|macro|USB_PID_UNDEF_F
mdefine_line|#define USB_PID_UNDEF_F                        0x0f
multiline_comment|/*&n; * Standard requests&n; */
DECL|macro|USB_REQ_GET_STATUS
mdefine_line|#define USB_REQ_GET_STATUS&t;&t;0x00
DECL|macro|USB_REQ_CLEAR_FEATURE
mdefine_line|#define USB_REQ_CLEAR_FEATURE&t;&t;0x01
DECL|macro|USB_REQ_SET_FEATURE
mdefine_line|#define USB_REQ_SET_FEATURE&t;&t;0x03
DECL|macro|USB_REQ_SET_ADDRESS
mdefine_line|#define USB_REQ_SET_ADDRESS&t;&t;0x05
DECL|macro|USB_REQ_GET_DESCRIPTOR
mdefine_line|#define USB_REQ_GET_DESCRIPTOR&t;&t;0x06
DECL|macro|USB_REQ_SET_DESCRIPTOR
mdefine_line|#define USB_REQ_SET_DESCRIPTOR&t;&t;0x07
DECL|macro|USB_REQ_GET_CONFIGURATION
mdefine_line|#define USB_REQ_GET_CONFIGURATION&t;0x08
DECL|macro|USB_REQ_SET_CONFIGURATION
mdefine_line|#define USB_REQ_SET_CONFIGURATION&t;0x09
DECL|macro|USB_REQ_GET_INTERFACE
mdefine_line|#define USB_REQ_GET_INTERFACE&t;&t;0x0A
DECL|macro|USB_REQ_SET_INTERFACE
mdefine_line|#define USB_REQ_SET_INTERFACE&t;&t;0x0B
DECL|macro|USB_REQ_SYNCH_FRAME
mdefine_line|#define USB_REQ_SYNCH_FRAME&t;&t;0x0C
multiline_comment|/*&n; * HID requests&n; */
DECL|macro|USB_REQ_GET_REPORT
mdefine_line|#define USB_REQ_GET_REPORT&t;&t;0x01
DECL|macro|USB_REQ_GET_IDLE
mdefine_line|#define USB_REQ_GET_IDLE&t;&t;0x02
DECL|macro|USB_REQ_GET_PROTOCOL
mdefine_line|#define USB_REQ_GET_PROTOCOL&t;&t;0x03
DECL|macro|USB_REQ_SET_REPORT
mdefine_line|#define USB_REQ_SET_REPORT&t;&t;0x09
DECL|macro|USB_REQ_SET_IDLE
mdefine_line|#define USB_REQ_SET_IDLE&t;&t;0x0A
DECL|macro|USB_REQ_SET_PROTOCOL
mdefine_line|#define USB_REQ_SET_PROTOCOL&t;&t;0x0B
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|USB_MAJOR
mdefine_line|#define USB_MAJOR 180
multiline_comment|/* for 2.2-kernels */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
DECL|function|list_add_tail
r_static
id|__inline__
r_void
id|list_add_tail
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add
c_func
(paren
r_new
comma
id|head-&gt;prev
comma
id|head
)paren
suffix:semicolon
)brace
DECL|macro|LIST_HEAD_INIT
mdefine_line|#define LIST_HEAD_INIT(name) { &amp;(name), &amp;(name) }
DECL|typedef|wait_queue_t
r_typedef
r_struct
id|wait_queue
id|wait_queue_t
suffix:semicolon
DECL|typedef|wait_queue_head_t
r_typedef
r_struct
id|wait_queue
op_star
id|wait_queue_head_t
suffix:semicolon
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(wait, current) &bslash;&n;&t;struct wait_queue wait = { current, NULL }
DECL|macro|DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define DECLARE_WAIT_QUEUE_HEAD(wait)&bslash;&n;&t;wait_queue_head_t wait
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(x) *x=NULL
DECL|macro|init_MUTEX
mdefine_line|#define init_MUTEX(x) *(x)=MUTEX
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) struct semaphore name=MUTEX
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name) struct semaphore name=MUTEX_LOCKED
DECL|macro|__set_current_state
mdefine_line|#define __set_current_state(state_value)                        &bslash;&n;&t;do { current-&gt;state = state_value; } while (0)
macro_line|#ifdef __SMP__
DECL|macro|set_current_state
mdefine_line|#define set_current_state(state_value)          &bslash;&n;&t;set_mb(current-&gt;state, state_value)
macro_line|#else
DECL|macro|set_current_state
mdefine_line|#define set_current_state(state_value)          &bslash;&n;&t;__set_current_state(state_value)
macro_line|#endif
macro_line|#endif 
singleline_comment|// 2.2.x
DECL|function|wait_ms
r_static
id|__inline__
r_void
id|wait_ms
c_func
(paren
r_int
r_int
id|ms
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
op_plus
id|ms
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
id|mdelay
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|requesttype
id|__u8
id|requesttype
suffix:semicolon
DECL|member|request
id|__u8
id|request
suffix:semicolon
DECL|member|value
id|__u16
id|value
suffix:semicolon
DECL|member|index
id|__u16
id|index
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|typedef|devrequest
)brace
id|devrequest
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * USB-status codes:&n; * USB_ST* maps to -E* and should go away in the future&n; */
DECL|macro|USB_ST_NOERROR
mdefine_line|#define USB_ST_NOERROR&t;&t;0
DECL|macro|USB_ST_CRC
mdefine_line|#define USB_ST_CRC&t;&t;(-EILSEQ)
DECL|macro|USB_ST_BITSTUFF
mdefine_line|#define USB_ST_BITSTUFF&t;&t;(-EPROTO)
DECL|macro|USB_ST_NORESPONSE
mdefine_line|#define USB_ST_NORESPONSE&t;(-ETIMEDOUT)&t;&t;&t;/* device not responding/handshaking */
DECL|macro|USB_ST_DATAOVERRUN
mdefine_line|#define USB_ST_DATAOVERRUN&t;(-EOVERFLOW)
DECL|macro|USB_ST_DATAUNDERRUN
mdefine_line|#define USB_ST_DATAUNDERRUN&t;(-EREMOTEIO)
DECL|macro|USB_ST_BUFFEROVERRUN
mdefine_line|#define USB_ST_BUFFEROVERRUN&t;(-ECOMM)
DECL|macro|USB_ST_BUFFERUNDERRUN
mdefine_line|#define USB_ST_BUFFERUNDERRUN&t;(-ENOSR)
DECL|macro|USB_ST_INTERNALERROR
mdefine_line|#define USB_ST_INTERNALERROR&t;(-EPROTO) &t;&t;&t;/* unknown error */
DECL|macro|USB_ST_SHORT_PACKET
mdefine_line|#define USB_ST_SHORT_PACKET    &t;(-EREMOTEIO)
DECL|macro|USB_ST_PARTIAL_ERROR
mdefine_line|#define USB_ST_PARTIAL_ERROR  &t;(-EXDEV)&t;&t;&t;/* ISO transfer only partially completed */
DECL|macro|USB_ST_URB_KILLED
mdefine_line|#define USB_ST_URB_KILLED     &t;(-ENOENT)&t;&t;&t;/* URB canceled by user */
DECL|macro|USB_ST_URB_PENDING
mdefine_line|#define USB_ST_URB_PENDING       (-EINPROGRESS)
DECL|macro|USB_ST_REMOVED
mdefine_line|#define USB_ST_REMOVED&t;&t;(-ENODEV) &t;&t;&t;/* device not existing or removed */
DECL|macro|USB_ST_TIMEOUT
mdefine_line|#define USB_ST_TIMEOUT&t;&t;(-ETIMEDOUT)&t;&t;&t;/* communication timed out, also in urb-&gt;status**/
DECL|macro|USB_ST_NOTSUPPORTED
mdefine_line|#define USB_ST_NOTSUPPORTED&t;(-ENOSYS)&t;&t;&t;
DECL|macro|USB_ST_BANDWIDTH_ERROR
mdefine_line|#define USB_ST_BANDWIDTH_ERROR&t;(-ENOSPC)&t;&t;&t;/* too much bandwidth used */
DECL|macro|USB_ST_URB_INVALID_ERROR
mdefine_line|#define USB_ST_URB_INVALID_ERROR  (-EINVAL)&t;&t;&t;/* invalid value/transfer type */
DECL|macro|USB_ST_URB_REQUEST_ERROR
mdefine_line|#define USB_ST_URB_REQUEST_ERROR  (-ENXIO)&t;&t;&t;/* invalid endpoint */
DECL|macro|USB_ST_STALL
mdefine_line|#define USB_ST_STALL&t;&t;(-EPIPE) &t;&t;&t;/* pipe stalled, also in urb-&gt;status*/
multiline_comment|/*&n; * USB device number allocation bitmap. There&squot;s one bitmap&n; * per USB tree.&n; */
DECL|struct|usb_devmap
r_struct
id|usb_devmap
(brace
DECL|member|devicemap
r_int
r_int
id|devicemap
(braket
l_int|128
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|USB_MAXBUS
mdefine_line|#define USB_MAXBUS&t;&t;64
DECL|struct|usb_busmap
r_struct
id|usb_busmap
(brace
DECL|member|busmap
r_int
r_int
id|busmap
(braket
id|USB_MAXBUS
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is a USB device descriptor.&n; *&n; * USB device information&n; */
multiline_comment|/* Everything but the endpoint maximums are aribtrary */
DECL|macro|USB_MAXCONFIG
mdefine_line|#define USB_MAXCONFIG&t;&t;8
DECL|macro|USB_ALTSETTINGALLOC
mdefine_line|#define USB_ALTSETTINGALLOC     4
DECL|macro|USB_MAXALTSETTING
mdefine_line|#define USB_MAXALTSETTING&t;128  /* Hard limit */
DECL|macro|USB_MAXINTERFACES
mdefine_line|#define USB_MAXINTERFACES&t;32
DECL|macro|USB_MAXENDPOINTS
mdefine_line|#define USB_MAXENDPOINTS&t;32
multiline_comment|/* All standard descriptors have these 2 fields in common */
DECL|struct|usb_descriptor_header
r_struct
id|usb_descriptor_header
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Device descriptor */
DECL|struct|usb_device_descriptor
r_struct
id|usb_device_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdUSB
id|__u16
id|bcdUSB
suffix:semicolon
DECL|member|bDeviceClass
id|__u8
id|bDeviceClass
suffix:semicolon
DECL|member|bDeviceSubClass
id|__u8
id|bDeviceSubClass
suffix:semicolon
DECL|member|bDeviceProtocol
id|__u8
id|bDeviceProtocol
suffix:semicolon
DECL|member|bMaxPacketSize0
id|__u8
id|bMaxPacketSize0
suffix:semicolon
DECL|member|idVendor
id|__u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__u16
id|idProduct
suffix:semicolon
DECL|member|bcdDevice
id|__u16
id|bcdDevice
suffix:semicolon
DECL|member|iManufacturer
id|__u8
id|iManufacturer
suffix:semicolon
DECL|member|iProduct
id|__u8
id|iProduct
suffix:semicolon
DECL|member|iSerialNumber
id|__u8
id|iSerialNumber
suffix:semicolon
DECL|member|bNumConfigurations
id|__u8
id|bNumConfigurations
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Endpoint descriptor */
DECL|struct|usb_endpoint_descriptor
r_struct
id|usb_endpoint_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bEndpointAddress
id|__u8
id|bEndpointAddress
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
suffix:semicolon
DECL|member|wMaxPacketSize
id|__u16
id|wMaxPacketSize
suffix:semicolon
DECL|member|bInterval
id|__u8
id|bInterval
suffix:semicolon
DECL|member|bRefresh
id|__u8
id|bRefresh
suffix:semicolon
DECL|member|bSynchAddress
id|__u8
id|bSynchAddress
suffix:semicolon
DECL|member|extra
r_int
r_char
op_star
id|extra
suffix:semicolon
multiline_comment|/* Extra descriptors */
DECL|member|extralen
r_int
id|extralen
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Interface descriptor */
DECL|struct|usb_interface_descriptor
r_struct
id|usb_interface_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bInterfaceNumber
id|__u8
id|bInterfaceNumber
suffix:semicolon
DECL|member|bAlternateSetting
id|__u8
id|bAlternateSetting
suffix:semicolon
DECL|member|bNumEndpoints
id|__u8
id|bNumEndpoints
suffix:semicolon
DECL|member|bInterfaceClass
id|__u8
id|bInterfaceClass
suffix:semicolon
DECL|member|bInterfaceSubClass
id|__u8
id|bInterfaceSubClass
suffix:semicolon
DECL|member|bInterfaceProtocol
id|__u8
id|bInterfaceProtocol
suffix:semicolon
DECL|member|iInterface
id|__u8
id|iInterface
suffix:semicolon
DECL|member|endpoint
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
DECL|member|extra
r_int
r_char
op_star
id|extra
suffix:semicolon
DECL|member|extralen
r_int
id|extralen
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|usb_interface
r_struct
id|usb_interface
(brace
DECL|member|altsetting
r_struct
id|usb_interface_descriptor
op_star
id|altsetting
suffix:semicolon
DECL|member|act_altsetting
r_int
id|act_altsetting
suffix:semicolon
multiline_comment|/* active alternate setting */
DECL|member|num_altsetting
r_int
id|num_altsetting
suffix:semicolon
multiline_comment|/* number of alternate settings */
DECL|member|max_altsetting
r_int
id|max_altsetting
suffix:semicolon
multiline_comment|/* total memory allocated */
DECL|member|driver
r_struct
id|usb_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* driver */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Configuration descriptor information.. */
DECL|struct|usb_config_descriptor
r_struct
id|usb_config_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|wTotalLength
id|__u16
id|wTotalLength
suffix:semicolon
DECL|member|bNumInterfaces
id|__u8
id|bNumInterfaces
suffix:semicolon
DECL|member|bConfigurationValue
id|__u8
id|bConfigurationValue
suffix:semicolon
DECL|member|iConfiguration
id|__u8
id|iConfiguration
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
suffix:semicolon
DECL|member|MaxPower
id|__u8
id|MaxPower
suffix:semicolon
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* String descriptor */
DECL|struct|usb_string_descriptor
r_struct
id|usb_string_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|wData
id|__u16
id|wData
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|usb_device
suffix:semicolon
DECL|struct|usb_driver
r_struct
id|usb_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe
r_void
op_star
(paren
op_star
id|probe
)paren
(paren
r_struct
id|usb_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|usb_device
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|driver_list
r_struct
id|list_head
id|driver_list
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Pointer to a device endpoint interrupt function -greg&n; *   Parameters:&n; *     int status - This needs to be defined.  Right now each HCD&n; *         passes different transfer status bits back.  Don&squot;t use it&n; *         until we come up with a common meaning.&n; *     void *buffer - This is a pointer to the data used in this&n; *         USB transfer.&n; *     int length - This is the number of bytes transferred in or out&n; *         of the buffer by this transfer.  (-1 = unknown/unsupported)&n; *     void *dev_id - This is a user defined pointer set when the IRQ&n; *         is requested that is passed back.&n; *&n; *   Special Cases:&n; *     if (status == USB_ST_REMOVED), don&squot;t trust buffer or len.&n; */
DECL|typedef|usb_device_irq
r_typedef
r_int
(paren
op_star
id|usb_device_irq
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------------------* &n; * New USB Structures                                                                   *&n; * -------------------------------------------------------------------------------------*/
DECL|macro|USB_DISABLE_SPD
mdefine_line|#define USB_DISABLE_SPD         0x0001
DECL|macro|USB_ISO_ASAP
mdefine_line|#define USB_ISO_ASAP            0x0002
DECL|macro|USB_URB_EARLY_COMPLETE
mdefine_line|#define USB_URB_EARLY_COMPLETE  0x0004
DECL|macro|USB_ASYNC_UNLINK
mdefine_line|#define USB_ASYNC_UNLINK        0x0008
DECL|macro|USB_QUEUE_BULK
mdefine_line|#define USB_QUEUE_BULK          0x0010
DECL|macro|USB_TIMEOUT_KILLED
mdefine_line|#define USB_TIMEOUT_KILLED&t;0x1000&t;
singleline_comment|// only set by HCD!
r_typedef
r_struct
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
singleline_comment|// expected length
DECL|member|actual_length
r_int
r_int
id|actual_length
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|typedef|iso_packet_descriptor_t
DECL|typedef|piso_packet_descriptor_t
)brace
id|iso_packet_descriptor_t
comma
op_star
id|piso_packet_descriptor_t
suffix:semicolon
r_struct
id|urb
suffix:semicolon
DECL|typedef|usb_complete_t
r_typedef
r_void
(paren
op_star
id|usb_complete_t
)paren
(paren
r_struct
id|urb
op_star
)paren
suffix:semicolon
DECL|struct|urb
r_typedef
r_struct
id|urb
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
singleline_comment|// lock for the URB
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
singleline_comment|// private data for host controller
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
singleline_comment|// list pointer to all active urbs 
DECL|member|next
r_struct
id|urb
op_star
id|next
suffix:semicolon
singleline_comment|// pointer to next URB&t;
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
singleline_comment|// pointer to associated USB device
DECL|member|pipe
r_int
r_int
id|pipe
suffix:semicolon
singleline_comment|// pipe information
DECL|member|status
r_int
id|status
suffix:semicolon
singleline_comment|// returned status
DECL|member|transfer_flags
r_int
r_int
id|transfer_flags
suffix:semicolon
singleline_comment|// USB_DISABLE_SPD | USB_ISO_ASAP | USB_URB_EARLY_COMPLETE
DECL|member|transfer_buffer
r_void
op_star
id|transfer_buffer
suffix:semicolon
singleline_comment|// associated data buffer
DECL|member|transfer_buffer_length
r_int
id|transfer_buffer_length
suffix:semicolon
singleline_comment|// data buffer length
DECL|member|actual_length
r_int
id|actual_length
suffix:semicolon
singleline_comment|// actual data buffer length&t;
DECL|member|setup_packet
r_int
r_char
op_star
id|setup_packet
suffix:semicolon
singleline_comment|// setup packet (control only)
singleline_comment|//
DECL|member|start_frame
r_int
id|start_frame
suffix:semicolon
singleline_comment|// start frame (iso/irq only)
DECL|member|number_of_packets
r_int
id|number_of_packets
suffix:semicolon
singleline_comment|// number of packets in this request (iso/irq only)
DECL|member|interval
r_int
id|interval
suffix:semicolon
singleline_comment|// polling interval (irq only)
DECL|member|error_count
r_int
id|error_count
suffix:semicolon
singleline_comment|// number of errors in this transfer (iso only)
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
singleline_comment|// timeout (in jiffies)
singleline_comment|//
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
singleline_comment|// context for completion routine
DECL|member|complete
id|usb_complete_t
id|complete
suffix:semicolon
singleline_comment|// pointer to completion routine
singleline_comment|//
DECL|member|iso_frame_desc
id|iso_packet_descriptor_t
id|iso_frame_desc
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|urb_t
DECL|typedef|purb_t
)brace
id|urb_t
comma
op_star
id|purb_t
suffix:semicolon
DECL|macro|FILL_CONTROL_URB
mdefine_line|#define FILL_CONTROL_URB(a,aa,b,c,d,e,f,g) &bslash;&n;    do {&bslash;&n;&t;spin_lock_init(&amp;(a)-&gt;lock);&bslash;&n;&t;(a)-&gt;dev=aa;&bslash;&n;&t;(a)-&gt;pipe=b;&bslash;&n;&t;(a)-&gt;setup_packet=c;&bslash;&n;&t;(a)-&gt;transfer_buffer=d;&bslash;&n;&t;(a)-&gt;transfer_buffer_length=e;&bslash;&n;&t;(a)-&gt;complete=f;&bslash;&n;&t;(a)-&gt;context=g;&bslash;&n;    } while (0)
DECL|macro|FILL_BULK_URB
mdefine_line|#define FILL_BULK_URB(a,aa,b,c,d,e,f) &bslash;&n;    do {&bslash;&n;&t;spin_lock_init(&amp;(a)-&gt;lock);&bslash;&n;&t;(a)-&gt;dev=aa;&bslash;&n;&t;(a)-&gt;pipe=b;&bslash;&n;&t;(a)-&gt;transfer_buffer=c;&bslash;&n;&t;(a)-&gt;transfer_buffer_length=d;&bslash;&n;&t;(a)-&gt;complete=e;&bslash;&n;&t;(a)-&gt;context=f;&bslash;&n;    } while (0)
DECL|macro|FILL_INT_URB
mdefine_line|#define FILL_INT_URB(a,aa,b,c,d,e,f,g) &bslash;&n;    do {&bslash;&n;&t;spin_lock_init(&amp;(a)-&gt;lock);&bslash;&n;&t;(a)-&gt;dev=aa;&bslash;&n;&t;(a)-&gt;pipe=b;&bslash;&n;&t;(a)-&gt;transfer_buffer=c;&bslash;&n;&t;(a)-&gt;transfer_buffer_length=d;&bslash;&n;&t;(a)-&gt;complete=e;&bslash;&n;&t;(a)-&gt;context=f;&bslash;&n;&t;(a)-&gt;interval=g;&bslash;&n;&t;(a)-&gt;start_frame=-1;&bslash;&n;    } while (0)
DECL|macro|FILL_CONTROL_URB_TO
mdefine_line|#define FILL_CONTROL_URB_TO(a,aa,b,c,d,e,f,g,h) &bslash;&n;    do {&bslash;&n;&t;spin_lock_init(&amp;(a)-&gt;lock);&bslash;&n;&t;(a)-&gt;dev=aa;&bslash;&n;&t;(a)-&gt;pipe=b;&bslash;&n;&t;(a)-&gt;setup_packet=c;&bslash;&n;&t;(a)-&gt;transfer_buffer=d;&bslash;&n;&t;(a)-&gt;transfer_buffer_length=e;&bslash;&n;&t;(a)-&gt;complete=f;&bslash;&n;&t;(a)-&gt;context=g;&bslash;&n;&t;(a)-&gt;timeout=h;&bslash;&n;    } while (0)
DECL|macro|FILL_BULK_URB_TO
mdefine_line|#define FILL_BULK_URB_TO(a,aa,b,c,d,e,f,g) &bslash;&n;    do {&bslash;&n;&t;spin_lock_init(&amp;(a)-&gt;lock);&bslash;&n;&t;(a)-&gt;dev=aa;&bslash;&n;&t;(a)-&gt;pipe=b;&bslash;&n;&t;(a)-&gt;transfer_buffer=c;&bslash;&n;&t;(a)-&gt;transfer_buffer_length=d;&bslash;&n;&t;(a)-&gt;complete=e;&bslash;&n;&t;(a)-&gt;context=f;&bslash;&n;&t;(a)-&gt;timeout=g;&bslash;&n;    } while (0)
id|purb_t
id|usb_alloc_urb
c_func
(paren
r_int
id|iso_packets
)paren
suffix:semicolon
r_void
id|usb_free_urb
(paren
id|purb_t
id|purb
)paren
suffix:semicolon
r_int
id|usb_submit_urb
c_func
(paren
id|purb_t
id|purb
)paren
suffix:semicolon
r_int
id|usb_unlink_urb
c_func
(paren
id|purb_t
id|purb
)paren
suffix:semicolon
r_int
id|usb_internal_control_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
id|devrequest
op_star
id|cmd
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_int
id|timeout
)paren
suffix:semicolon
r_int
id|usb_bulk_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_int
op_star
id|actual_length
comma
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------*&n; *                         COMPATIBILITY STUFF                       *&n; *-------------------------------------------------------------------*/
r_typedef
r_struct
(brace
DECL|member|wakeup
id|wait_queue_head_t
op_star
id|wakeup
suffix:semicolon
DECL|member|handler
id|usb_device_irq
id|handler
suffix:semicolon
DECL|member|stuff
r_void
op_star
id|stuff
suffix:semicolon
multiline_comment|/* more to follow */
DECL|typedef|api_wrapper_data
)brace
id|api_wrapper_data
suffix:semicolon
DECL|struct|irq_wrapper_data
r_struct
id|irq_wrapper_data
(brace
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|handler
id|usb_device_irq
id|handler
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------------------- */
DECL|struct|usb_operations
r_struct
id|usb_operations
(brace
DECL|member|allocate
r_int
(paren
op_star
id|allocate
)paren
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
DECL|member|deallocate
r_int
(paren
op_star
id|deallocate
)paren
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
DECL|member|get_frame_number
r_int
(paren
op_star
id|get_frame_number
)paren
(paren
r_struct
id|usb_device
op_star
id|usb_dev
)paren
suffix:semicolon
DECL|member|submit_urb
r_int
(paren
op_star
id|submit_urb
)paren
(paren
r_struct
id|urb
op_star
id|purb
)paren
suffix:semicolon
DECL|member|unlink_urb
r_int
(paren
op_star
id|unlink_urb
)paren
(paren
r_struct
id|urb
op_star
id|purb
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocated per bus we have&n; */
DECL|struct|usb_bus
r_struct
id|usb_bus
(brace
DECL|member|busnum
r_int
id|busnum
suffix:semicolon
multiline_comment|/* Bus number (in order of reg) */
DECL|member|devmap
r_struct
id|usb_devmap
id|devmap
suffix:semicolon
multiline_comment|/* Device map */
DECL|member|op
r_struct
id|usb_operations
op_star
id|op
suffix:semicolon
multiline_comment|/* Operations (specific to the HC) */
DECL|member|root_hub
r_struct
id|usb_device
op_star
id|root_hub
suffix:semicolon
multiline_comment|/* Root hub */
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
multiline_comment|/* Host Controller private data */
DECL|member|bandwidth_allocated
r_int
r_int
id|bandwidth_allocated
suffix:semicolon
multiline_comment|/* on this Host Controller; */
multiline_comment|/* applies to Int. and Isoc. pipes; */
multiline_comment|/* measured in microseconds/frame; */
multiline_comment|/* range is 0..900, where 900 = */
multiline_comment|/* 90% of a 1-millisecond frame */
DECL|member|bandwidth_int_reqs
r_int
id|bandwidth_int_reqs
suffix:semicolon
multiline_comment|/* number of Interrupt requesters */
DECL|member|bandwidth_isoc_reqs
r_int
id|bandwidth_isoc_reqs
suffix:semicolon
multiline_comment|/* number of Isoc. requesters */
multiline_comment|/* usbdevfs inode list */
DECL|member|inodes
r_struct
id|list_head
id|inodes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|USB_MAXCHILDREN
mdefine_line|#define USB_MAXCHILDREN (8)&t;/* This is arbitrary */
DECL|struct|usb_device
r_struct
id|usb_device
(brace
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
multiline_comment|/* Device number on USB bus */
DECL|member|slow
r_int
id|slow
suffix:semicolon
multiline_comment|/* Slow device? */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* Reference count */
DECL|member|maxpacketsize
r_int
id|maxpacketsize
suffix:semicolon
multiline_comment|/* Maximum packet size; encoded as 0,1,2,3 = 8,16,32,64 */
DECL|member|toggle
r_int
r_int
id|toggle
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* one bit for each endpoint ([0] = IN, [1] = OUT) */
DECL|member|halted
r_int
r_int
id|halted
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* endpoint halts; one bit per endpoint # &amp; direction; */
multiline_comment|/* [0] = IN, [1] = OUT */
DECL|member|actconfig
r_struct
id|usb_config_descriptor
op_star
id|actconfig
suffix:semicolon
multiline_comment|/* the active configuration */
DECL|member|epmaxpacketin
r_int
id|epmaxpacketin
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* INput endpoint specific maximums */
DECL|member|epmaxpacketout
r_int
id|epmaxpacketout
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OUTput endpoint specific maximums */
DECL|member|parent
r_struct
id|usb_device
op_star
id|parent
suffix:semicolon
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* Bus we&squot;re part of */
DECL|member|descriptor
r_struct
id|usb_device_descriptor
id|descriptor
suffix:semicolon
multiline_comment|/* Descriptor */
DECL|member|config
r_struct
id|usb_config_descriptor
op_star
id|config
suffix:semicolon
multiline_comment|/* All of the configs */
DECL|member|have_langid
r_int
id|have_langid
suffix:semicolon
multiline_comment|/* whether string_langid is valid yet */
DECL|member|string_langid
r_int
id|string_langid
suffix:semicolon
multiline_comment|/* language ID for strings */
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
multiline_comment|/* Host Controller private data */
multiline_comment|/* usbdevfs inode list */
DECL|member|inodes
r_struct
id|list_head
id|inodes
suffix:semicolon
DECL|member|filelist
r_struct
id|list_head
id|filelist
suffix:semicolon
multiline_comment|/*&n;&t; * Child devices - these can be either new devices&n;&t; * (if this is a hub device), or different instances&n;&t; * of this same device.&n;&t; *&n;&t; * Each instance needs its own set of data structures.&n;&t; */
DECL|member|maxchild
r_int
id|maxchild
suffix:semicolon
multiline_comment|/* Number of ports if hub */
DECL|member|children
r_struct
id|usb_device
op_star
id|children
(braket
id|USB_MAXCHILDREN
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|usb_register
c_func
(paren
r_struct
id|usb_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_deregister
c_func
(paren
r_struct
id|usb_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* used these for multi-interface device registration */
r_extern
r_void
id|usb_driver_claim_interface
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_struct
id|usb_interface
op_star
id|iface
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|usb_interface_claimed
c_func
(paren
r_struct
id|usb_interface
op_star
id|iface
)paren
suffix:semicolon
r_extern
r_void
id|usb_driver_release_interface
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_struct
id|usb_interface
op_star
id|iface
)paren
suffix:semicolon
r_extern
r_struct
id|usb_bus
op_star
id|usb_alloc_bus
c_func
(paren
r_struct
id|usb_operations
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_free_bus
c_func
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_register_bus
c_func
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_deregister_bus
c_func
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|usb_device
op_star
id|usb_alloc_dev
c_func
(paren
r_struct
id|usb_device
op_star
id|parent
comma
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_free_dev
c_func
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_inc_dev_use
c_func
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
DECL|macro|usb_dec_dev_use
mdefine_line|#define usb_dec_dev_use usb_free_dev
r_extern
r_void
id|usb_release_bandwidth
c_func
(paren
r_struct
id|usb_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|usb_control_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
id|__u8
id|request
comma
id|__u8
id|requesttype
comma
id|__u16
id|value
comma
id|__u16
id|index
comma
r_void
op_star
id|data
comma
id|__u16
id|size
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|usb_request_irq
c_func
(paren
r_struct
id|usb_device
op_star
comma
r_int
r_int
comma
id|usb_device_irq
comma
r_int
comma
r_void
op_star
comma
r_void
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_release_irq
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|handle
comma
r_int
r_int
id|pipe
)paren
suffix:semicolon
r_extern
r_void
op_star
id|usb_request_bulk
c_func
(paren
r_struct
id|usb_device
op_star
comma
r_int
r_int
comma
id|usb_device_irq
comma
r_void
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_terminate_bulk
c_func
(paren
r_struct
id|usb_device
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_init_root_hub
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|usb_root_hub_string
c_func
(paren
r_int
id|id
comma
r_int
id|serial
comma
r_char
op_star
id|type
comma
id|__u8
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|usb_connect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_destroy_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|usb_get_current_frame_number
(paren
r_struct
id|usb_device
op_star
id|usb_dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Calling this entity a &quot;pipe&quot; is glorifying it. A USB pipe&n; * is something embarrassingly simple: it basically consists&n; * of the following information:&n; *  - device number (7 bits)&n; *  - endpoint number (4 bits)&n; *  - current Data0/1 state (1 bit)&n; *  - direction (1 bit)&n; *  - speed (1 bit)&n; *  - max packet size (2 bits: 8, 16, 32 or 64)&n; *  - pipe type (2 bits: control, interrupt, bulk, isochronous)&n; *&n; * That&squot;s 18 bits. Really. Nothing more. And the USB people have&n; * documented these eighteen bits as some kind of glorious&n; * virtual data structure.&n; *&n; * Let&squot;s not fall in that trap. We&squot;ll just encode it as a simple&n; * unsigned int. The encoding is:&n; *&n; *  - max size:&t;&t;bits 0-1&t;(00 = 8, 01 = 16, 10 = 32, 11 = 64)&n; *  - direction:&t;bit 7&t;&t;(0 = Host-to-Device [Out], 1 = Device-to-Host [In])&n; *  - device:&t;&t;bits 8-14&n; *  - endpoint:&t;&t;bits 15-18&n; *  - Data0/1:&t;&t;bit 19&n; *  - speed:&t;&t;bit 26&t;&t;(0 = Full, 1 = Low Speed)&n; *  - pipe type:&t;bits 30-31&t;(00 = isochronous, 01 = interrupt, 10 = control, 11 = bulk)&n; *&n; * Why? Because it&squot;s arbitrary, and whatever encoding we select is really&n; * up to us. This one happens to share a lot of bit positions with the UHCI&n; * specification, so that much of the uhci driver can just mask the bits&n; * appropriately.&n; */
DECL|macro|PIPE_ISOCHRONOUS
mdefine_line|#define PIPE_ISOCHRONOUS&t;&t;0
DECL|macro|PIPE_INTERRUPT
mdefine_line|#define PIPE_INTERRUPT&t;&t;&t;1
DECL|macro|PIPE_CONTROL
mdefine_line|#define PIPE_CONTROL&t;&t;&t;2
DECL|macro|PIPE_BULK
mdefine_line|#define PIPE_BULK&t;&t;&t;3
DECL|macro|USB_ISOCHRONOUS
mdefine_line|#define USB_ISOCHRONOUS&t;&t;0
DECL|macro|USB_INTERRUPT
mdefine_line|#define USB_INTERRUPT&t;&t;1
DECL|macro|USB_CONTROL
mdefine_line|#define USB_CONTROL&t;&t;2
DECL|macro|USB_BULK
mdefine_line|#define USB_BULK&t;&t;3
DECL|macro|usb_maxpacket
mdefine_line|#define usb_maxpacket(dev, pipe, out)&t;(out &bslash;&n;&t;&t;&t;&t;? (dev)-&gt;epmaxpacketout[usb_pipeendpoint(pipe)] &bslash;&n;&t;&t;&t;&t;: (dev)-&gt;epmaxpacketin [usb_pipeendpoint(pipe)] )
DECL|macro|usb_packetid
mdefine_line|#define usb_packetid(pipe)&t;(((pipe) &amp; USB_DIR_IN) ? USB_PID_IN : USB_PID_OUT)
DECL|macro|usb_pipeout
mdefine_line|#define usb_pipeout(pipe)&t;((((pipe) &gt;&gt; 7) &amp; 1) ^ 1)
DECL|macro|usb_pipein
mdefine_line|#define usb_pipein(pipe)&t;(((pipe) &gt;&gt; 7) &amp; 1)
DECL|macro|usb_pipedevice
mdefine_line|#define usb_pipedevice(pipe)&t;(((pipe) &gt;&gt; 8) &amp; 0x7f)
DECL|macro|usb_pipe_endpdev
mdefine_line|#define usb_pipe_endpdev(pipe)&t;(((pipe) &gt;&gt; 8) &amp; 0x7ff)
DECL|macro|usb_pipeendpoint
mdefine_line|#define usb_pipeendpoint(pipe)&t;(((pipe) &gt;&gt; 15) &amp; 0xf)
DECL|macro|usb_pipedata
mdefine_line|#define usb_pipedata(pipe)&t;(((pipe) &gt;&gt; 19) &amp; 1)
DECL|macro|usb_pipeslow
mdefine_line|#define usb_pipeslow(pipe)&t;(((pipe) &gt;&gt; 26) &amp; 1)
DECL|macro|usb_pipetype
mdefine_line|#define usb_pipetype(pipe)&t;(((pipe) &gt;&gt; 30) &amp; 3)
DECL|macro|usb_pipeisoc
mdefine_line|#define usb_pipeisoc(pipe)&t;(usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
DECL|macro|usb_pipeint
mdefine_line|#define usb_pipeint(pipe)&t;(usb_pipetype((pipe)) == PIPE_INTERRUPT)
DECL|macro|usb_pipecontrol
mdefine_line|#define usb_pipecontrol(pipe)&t;(usb_pipetype((pipe)) == PIPE_CONTROL)
DECL|macro|usb_pipebulk
mdefine_line|#define usb_pipebulk(pipe)&t;(usb_pipetype((pipe)) == PIPE_BULK)
DECL|macro|PIPE_DEVEP_MASK
mdefine_line|#define PIPE_DEVEP_MASK&t;&t;0x0007ff00
multiline_comment|/* The D0/D1 toggle bits */
DECL|macro|usb_gettoggle
mdefine_line|#define usb_gettoggle(dev, ep, out) (((dev)-&gt;toggle[out] &gt;&gt; ep) &amp; 1)
DECL|macro|usb_dotoggle
mdefine_line|#define&t;usb_dotoggle(dev, ep, out)  ((dev)-&gt;toggle[out] ^= (1 &lt;&lt; ep))
DECL|macro|usb_settoggle
mdefine_line|#define usb_settoggle(dev, ep, out, bit) ((dev)-&gt;toggle[out] = ((dev)-&gt;toggle[out] &amp; ~(1 &lt;&lt; ep)) | ((bit) &lt;&lt; ep))
multiline_comment|/* Endpoint halt control/status */
DECL|macro|usb_endpoint_out
mdefine_line|#define usb_endpoint_out(ep_dir)&t;(((ep_dir &gt;&gt; 7) &amp; 1) ^ 1)
DECL|macro|usb_endpoint_halt
mdefine_line|#define usb_endpoint_halt(dev, ep, out) ((dev)-&gt;halted[out] |= (1 &lt;&lt; (ep)))
DECL|macro|usb_endpoint_running
mdefine_line|#define usb_endpoint_running(dev, ep, out) ((dev)-&gt;halted[out] &amp;= ~(1 &lt;&lt; (ep)))
DECL|macro|usb_endpoint_halted
mdefine_line|#define usb_endpoint_halted(dev, ep, out) ((dev)-&gt;halted[out] &amp; (1 &lt;&lt; (ep)))
DECL|function|__create_pipe
r_static
r_inline
r_int
r_int
id|__create_pipe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|endpoint
)paren
(brace
r_return
(paren
id|dev-&gt;devnum
op_lshift
l_int|8
)paren
op_or
(paren
id|endpoint
op_lshift
l_int|15
)paren
op_or
(paren
id|dev-&gt;slow
op_lshift
l_int|26
)paren
op_or
id|dev-&gt;maxpacketsize
suffix:semicolon
)brace
DECL|function|__default_pipe
r_static
r_inline
r_int
r_int
id|__default_pipe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;slow
op_lshift
l_int|26
)paren
suffix:semicolon
)brace
multiline_comment|/* Create various pipes... */
DECL|macro|usb_sndctrlpipe
mdefine_line|#define usb_sndctrlpipe(dev,endpoint)&t;((PIPE_CONTROL &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvctrlpipe
mdefine_line|#define usb_rcvctrlpipe(dev,endpoint)&t;((PIPE_CONTROL &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndisocpipe
mdefine_line|#define usb_sndisocpipe(dev,endpoint)&t;((PIPE_ISOCHRONOUS &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvisocpipe
mdefine_line|#define usb_rcvisocpipe(dev,endpoint)&t;((PIPE_ISOCHRONOUS &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndbulkpipe
mdefine_line|#define usb_sndbulkpipe(dev,endpoint)&t;((PIPE_BULK &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvbulkpipe
mdefine_line|#define usb_rcvbulkpipe(dev,endpoint)&t;((PIPE_BULK &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndintpipe
mdefine_line|#define usb_sndintpipe(dev,endpoint)&t;((PIPE_INTERRUPT &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvintpipe
mdefine_line|#define usb_rcvintpipe(dev,endpoint)&t;((PIPE_INTERRUPT &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_snddefctrl
mdefine_line|#define usb_snddefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30) | __default_pipe(dev))
DECL|macro|usb_rcvdefctrl
mdefine_line|#define usb_rcvdefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30) | __default_pipe(dev) | USB_DIR_IN)
multiline_comment|/*&n; * Send and receive control messages..&n; */
r_int
id|usb_new_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|usb_set_address
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|usb_get_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_char
id|desctype
comma
r_int
r_char
id|descindex
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|usb_get_class_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
r_char
id|desctype
comma
r_int
r_char
id|descindex
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|usb_get_device_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|__usb_get_extra_descriptor
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|size
comma
r_int
r_char
id|type
comma
r_void
op_star
op_star
id|ptr
)paren
suffix:semicolon
r_int
id|usb_get_status
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|type
comma
r_int
id|target
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_int
id|usb_get_protocol
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
)paren
suffix:semicolon
r_int
id|usb_set_protocol
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
id|protocol
)paren
suffix:semicolon
r_int
id|usb_set_interface
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
id|alternate
)paren
suffix:semicolon
r_int
id|usb_set_idle
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
id|duration
comma
r_int
id|report_id
)paren
suffix:semicolon
r_int
id|usb_set_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|configuration
)paren
suffix:semicolon
r_int
id|usb_get_report
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
r_char
id|type
comma
r_int
r_char
id|id
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|usb_set_report
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
r_char
id|type
comma
r_int
r_char
id|id
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|usb_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|usb_clear_halt
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|pipe
)paren
suffix:semicolon
DECL|macro|usb_get_extra_descriptor
mdefine_line|#define usb_get_extra_descriptor(ifpoint,type,ptr)&bslash;&n;&t;__usb_get_extra_descriptor((ifpoint)-&gt;extra,(ifpoint)-&gt;extralen,type,(void**)ptr)
multiline_comment|/*&n; * Some USB bandwidth allocation constants.&n; */
DECL|macro|BW_HOST_DELAY
mdefine_line|#define BW_HOST_DELAY&t;1000L&t;&t;/* nanoseconds */
DECL|macro|BW_HUB_LS_SETUP
mdefine_line|#define BW_HUB_LS_SETUP&t;333L&t;&t;/* nanoseconds */
multiline_comment|/* 4 full-speed bit times (est.) */
DECL|macro|FRAME_TIME_BITS
mdefine_line|#define FRAME_TIME_BITS         12000L&t;&t;/* frame = 1 millisecond */
DECL|macro|FRAME_TIME_MAX_BITS_ALLOC
mdefine_line|#define FRAME_TIME_MAX_BITS_ALLOC&t;(90L * FRAME_TIME_BITS / 100L)
DECL|macro|FRAME_TIME_USECS
mdefine_line|#define FRAME_TIME_USECS&t;1000L
DECL|macro|FRAME_TIME_MAX_USECS_ALLOC
mdefine_line|#define FRAME_TIME_MAX_USECS_ALLOC&t;(90L * FRAME_TIME_USECS / 100L)
DECL|macro|BitTime
mdefine_line|#define BitTime(bytecount)  (7 * 8 * bytecount / 6)  /* with integer truncation */
multiline_comment|/* Trying not to use worst-case bit-stuffing&n;                   of (7/6 * 8 * bytecount) = 9.33 * bytecount */
multiline_comment|/* bytecount = data payload byte count */
DECL|macro|NS_TO_US
mdefine_line|#define NS_TO_US(ns)&t;((ns + 500L) / 1000L)
multiline_comment|/* convert &amp; round nanoseconds to microseconds */
multiline_comment|/*&n; * Debugging helpers..&n; */
r_void
id|usb_show_device_descriptor
c_func
(paren
r_struct
id|usb_device_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_config_descriptor
c_func
(paren
r_struct
id|usb_config_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_interface_descriptor
c_func
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_endpoint_descriptor
c_func
(paren
r_struct
id|usb_endpoint_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_device
c_func
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
r_void
id|usb_show_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_char
op_star
id|id
comma
r_int
id|index
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
macro_line|#else
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do {} while (0)
macro_line|#endif
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
multiline_comment|/*&n; * bus and driver list&n; */
r_extern
r_struct
id|list_head
id|usb_driver_list
suffix:semicolon
r_extern
r_struct
id|list_head
id|usb_bus_list
suffix:semicolon
multiline_comment|/*&n; * USB device fs stuff&n; */
macro_line|#ifdef CONFIG_USB_DEVICEFS
multiline_comment|/*&n; * these are expected to be called from the USB core/hub thread&n; * with the kernel lock held&n; */
r_extern
r_void
id|usbdevfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbdevfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbdevfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usbdevfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|usbdevfs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usbdevfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_USB_DEVICEFS */
DECL|function|usbdevfs_add_bus
r_extern
r_inline
r_void
id|usbdevfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbdevfs_remove_bus
r_extern
r_inline
r_void
id|usbdevfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbdevfs_add_device
r_extern
r_inline
r_void
id|usbdevfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbdevfs_remove_device
r_extern
r_inline
r_void
id|usbdevfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbdevfs_init
r_extern
r_inline
r_int
id|usbdevfs_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usbdevfs_cleanup
r_extern
r_inline
r_void
id|usbdevfs_cleanup
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_USB_DEVICEFS */
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif
eof
