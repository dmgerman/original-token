macro_line|#ifndef __LINUX_HUB_H
DECL|macro|__LINUX_HUB_H
mdefine_line|#define __LINUX_HUB_H
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * Hub request types&n; */
DECL|macro|USB_RT_HUB
mdefine_line|#define USB_RT_HUB&t;(USB_TYPE_CLASS | USB_RECIP_DEVICE)
DECL|macro|USB_RT_PORT
mdefine_line|#define USB_RT_PORT&t;(USB_TYPE_CLASS | USB_RECIP_OTHER)
multiline_comment|/*&n; * Hub Class feature numbers&n; */
DECL|macro|C_HUB_LOCAL_POWER
mdefine_line|#define C_HUB_LOCAL_POWER&t;0
DECL|macro|C_HUB_OVER_CURRENT
mdefine_line|#define C_HUB_OVER_CURRENT&t;1
multiline_comment|/*&n; * Port feature numbers&n; */
DECL|macro|USB_PORT_FEAT_CONNECTION
mdefine_line|#define USB_PORT_FEAT_CONNECTION&t;0
DECL|macro|USB_PORT_FEAT_ENABLE
mdefine_line|#define USB_PORT_FEAT_ENABLE&t;&t;1
DECL|macro|USB_PORT_FEAT_SUSPEND
mdefine_line|#define USB_PORT_FEAT_SUSPEND&t;&t;2
DECL|macro|USB_PORT_FEAT_OVER_CURRENT
mdefine_line|#define USB_PORT_FEAT_OVER_CURRENT&t;3
DECL|macro|USB_PORT_FEAT_RESET
mdefine_line|#define USB_PORT_FEAT_RESET&t;&t;4
DECL|macro|USB_PORT_FEAT_POWER
mdefine_line|#define USB_PORT_FEAT_POWER&t;&t;8
DECL|macro|USB_PORT_FEAT_LOWSPEED
mdefine_line|#define USB_PORT_FEAT_LOWSPEED&t;&t;9
DECL|macro|USB_PORT_FEAT_C_CONNECTION
mdefine_line|#define USB_PORT_FEAT_C_CONNECTION&t;16
DECL|macro|USB_PORT_FEAT_C_ENABLE
mdefine_line|#define USB_PORT_FEAT_C_ENABLE&t;&t;17
DECL|macro|USB_PORT_FEAT_C_SUSPEND
mdefine_line|#define USB_PORT_FEAT_C_SUSPEND&t;&t;18
DECL|macro|USB_PORT_FEAT_C_OVER_CURRENT
mdefine_line|#define USB_PORT_FEAT_C_OVER_CURRENT&t;19
DECL|macro|USB_PORT_FEAT_C_RESET
mdefine_line|#define USB_PORT_FEAT_C_RESET&t;&t;20
DECL|struct|usb_port_status
r_struct
id|usb_port_status
(brace
DECL|member|wPortStatus
id|__u16
id|wPortStatus
suffix:semicolon
DECL|member|wPortChange
id|__u16
id|wPortChange
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* wPortStatus bits */
DECL|macro|USB_PORT_STAT_CONNECTION
mdefine_line|#define USB_PORT_STAT_CONNECTION&t;0x0001
DECL|macro|USB_PORT_STAT_ENABLE
mdefine_line|#define USB_PORT_STAT_ENABLE&t;&t;0x0002
DECL|macro|USB_PORT_STAT_SUSPEND
mdefine_line|#define USB_PORT_STAT_SUSPEND&t;&t;0x0004
DECL|macro|USB_PORT_STAT_OVERCURRENT
mdefine_line|#define USB_PORT_STAT_OVERCURRENT&t;0x0008
DECL|macro|USB_PORT_STAT_RESET
mdefine_line|#define USB_PORT_STAT_RESET&t;&t;0x0010
DECL|macro|USB_PORT_STAT_POWER
mdefine_line|#define USB_PORT_STAT_POWER&t;&t;0x0100
DECL|macro|USB_PORT_STAT_LOW_SPEED
mdefine_line|#define USB_PORT_STAT_LOW_SPEED&t;&t;0x0200
multiline_comment|/* wPortChange bits */
DECL|macro|USB_PORT_STAT_C_CONNECTION
mdefine_line|#define USB_PORT_STAT_C_CONNECTION&t;0x0001
DECL|macro|USB_PORT_STAT_C_ENABLE
mdefine_line|#define USB_PORT_STAT_C_ENABLE&t;&t;0x0002
DECL|macro|USB_PORT_STAT_C_SUSPEND
mdefine_line|#define USB_PORT_STAT_C_SUSPEND&t;&t;0x0004
DECL|macro|USB_PORT_STAT_C_OVERCURRENT
mdefine_line|#define USB_PORT_STAT_C_OVERCURRENT&t;0x0008
DECL|macro|USB_PORT_STAT_C_RESET
mdefine_line|#define USB_PORT_STAT_C_RESET&t;&t;0x0010
multiline_comment|/* wHubCharacteristics (masks) */
DECL|macro|HUB_CHAR_LPSM
mdefine_line|#define HUB_CHAR_LPSM&t;&t;0x0003
DECL|macro|HUB_CHAR_COMPOUND
mdefine_line|#define HUB_CHAR_COMPOUND&t;0x0004
DECL|macro|HUB_CHAR_OCPM
mdefine_line|#define HUB_CHAR_OCPM&t;&t;0x0018
DECL|struct|usb_hub_status
r_struct
id|usb_hub_status
(brace
DECL|member|wHubStatus
id|__u16
id|wHubStatus
suffix:semicolon
DECL|member|wHubChange
id|__u16
id|wHubChange
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *Hub Status &amp; Hub Change bit masks&n; */
DECL|macro|HUB_STATUS_LOCAL_POWER
mdefine_line|#define HUB_STATUS_LOCAL_POWER&t;0x0001
DECL|macro|HUB_STATUS_OVERCURRENT
mdefine_line|#define HUB_STATUS_OVERCURRENT&t;0x0002
DECL|macro|HUB_CHANGE_LOCAL_POWER
mdefine_line|#define HUB_CHANGE_LOCAL_POWER&t;0x0001
DECL|macro|HUB_CHANGE_OVERCURRENT
mdefine_line|#define HUB_CHANGE_OVERCURRENT&t;0x0002
DECL|macro|HUB_DESCRIPTOR_MAX_SIZE
mdefine_line|#define HUB_DESCRIPTOR_MAX_SIZE&t;39&t;/* enough for 127 ports on a hub */
multiline_comment|/* Hub descriptor */
DECL|struct|usb_hub_descriptor
r_struct
id|usb_hub_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bNbrPorts
id|__u8
id|bNbrPorts
suffix:semicolon
DECL|member|wHubCharacteristics
id|__u16
id|wHubCharacteristics
suffix:semicolon
DECL|member|bPwrOn2PwrGood
id|__u8
id|bPwrOn2PwrGood
suffix:semicolon
DECL|member|bHubContrCurrent
id|__u8
id|bHubContrCurrent
suffix:semicolon
multiline_comment|/* DeviceRemovable and PortPwrCtrlMask want to be variable-length &n;&t;   bitmaps that hold max 256 entries, but for now they&squot;re ignored */
DECL|member|bitmap
id|__u8
id|bitmap
(braket
l_int|0
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
DECL|struct|usb_hub
r_struct
id|usb_hub
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
multiline_comment|/* Interrupt polling pipe */
DECL|member|buffer
r_char
id|buffer
(braket
(paren
id|USB_MAXCHILDREN
op_plus
l_int|1
op_plus
l_int|7
)paren
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* add 1 bit for hub status change */
multiline_comment|/* and add 7 bits to round up to byte boundary */
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|nerrors
r_int
id|nerrors
suffix:semicolon
DECL|member|hub_list
r_struct
id|list_head
id|hub_list
suffix:semicolon
DECL|member|event_list
r_struct
id|list_head
id|event_list
suffix:semicolon
multiline_comment|/* Number of ports on the hub */
DECL|member|nports
r_int
id|nports
suffix:semicolon
DECL|member|descriptor
r_struct
id|usb_hub_descriptor
op_star
id|descriptor
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
