macro_line|#ifndef __LINUX_HUB_H
DECL|macro|__LINUX_HUB_H
mdefine_line|#define __LINUX_HUB_H
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * Hub feature numbers&n; */
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
multiline_comment|/* wPortStatus */
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
multiline_comment|/* wPortChange */
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
r_struct
id|usb_device
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|USB_PORT_UNPOWERED
id|USB_PORT_UNPOWERED
op_assign
l_int|0
comma
multiline_comment|/* Default state */
DECL|enumerator|USB_PORT_POWERED
id|USB_PORT_POWERED
comma
multiline_comment|/* When we&squot;ve put power to it */
DECL|enumerator|USB_PORT_ENABLED
id|USB_PORT_ENABLED
comma
multiline_comment|/* When it&squot;s been enabled */
DECL|enumerator|USB_PORT_DISABLED
id|USB_PORT_DISABLED
comma
multiline_comment|/* If it&squot;s been disabled */
DECL|enumerator|USB_PORT_ADMINDISABLED
id|USB_PORT_ADMINDISABLED
comma
multiline_comment|/* Forced down */
DECL|typedef|usb_hub_port_state
)brace
id|usb_hub_port_state
suffix:semicolon
DECL|struct|usb_hub_port
r_struct
id|usb_hub_port
(brace
DECL|member|cstate
id|usb_hub_port_state
id|cstate
suffix:semicolon
multiline_comment|/* Configuration state */
DECL|member|child
r_struct
id|usb_device
op_star
id|child
suffix:semicolon
multiline_comment|/* Device attached to this port */
DECL|member|parent
r_struct
id|usb_hub
op_star
id|parent
suffix:semicolon
multiline_comment|/* Parent hub */
)brace
suffix:semicolon
DECL|struct|usb_hub
r_struct
id|usb_hub
(brace
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Reference to the hub&squot;s polling IRQ */
DECL|member|irq_handle
r_void
op_star
id|irq_handle
suffix:semicolon
multiline_comment|/* List of hubs */
DECL|member|hub_list
r_struct
id|list_head
id|hub_list
suffix:semicolon
multiline_comment|/* Temporary event list */
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
DECL|member|ports
r_struct
id|usb_hub_port
id|ports
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Dynamically allocated */
)brace
suffix:semicolon
macro_line|#endif
eof
