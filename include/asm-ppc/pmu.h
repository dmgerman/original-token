multiline_comment|/*&n; * Definitions for talking to the PMU.  The PMU is a microcontroller&n; * which controls battery charging and system power on PowerBook 3400&n; * and 2400 models as well as the RTC and various other things.&n; *&n; * Copyright (C) 1998 Paul Mackerras.&n; */
multiline_comment|/*&n; * PMU commands&n; */
DECL|macro|PMU_POWER_CTRL
mdefine_line|#define PMU_POWER_CTRL&t;&t;0x11&t;/* control power of some devices */
DECL|macro|PMU_ADB_CMD
mdefine_line|#define PMU_ADB_CMD&t;&t;0x20&t;/* send ADB packet */
DECL|macro|PMU_ADB_POLL_OFF
mdefine_line|#define PMU_ADB_POLL_OFF&t;0x21&t;/* disable ADB auto-poll */
DECL|macro|PMU_WRITE_NVRAM
mdefine_line|#define PMU_WRITE_NVRAM&t;&t;0x33&t;/* write non-volatile RAM */
DECL|macro|PMU_READ_NVRAM
mdefine_line|#define PMU_READ_NVRAM&t;&t;0x3b&t;/* read non-volatile RAM */
DECL|macro|PMU_SET_RTC
mdefine_line|#define PMU_SET_RTC&t;&t;0x30&t;/* set real-time clock */
DECL|macro|PMU_READ_RTC
mdefine_line|#define PMU_READ_RTC&t;&t;0x38&t;/* read real-time clock */
DECL|macro|PMU_SET_VOLBUTTON
mdefine_line|#define PMU_SET_VOLBUTTON&t;0x40&t;/* set volume up/down position */
DECL|macro|PMU_BACKLIGHT_BRIGHT
mdefine_line|#define PMU_BACKLIGHT_BRIGHT&t;0x41&t;/* set backlight brightness */
DECL|macro|PMU_GET_VOLBUTTON
mdefine_line|#define PMU_GET_VOLBUTTON&t;0x48&t;/* get volume up/down position */
DECL|macro|PMU_PCEJECT
mdefine_line|#define PMU_PCEJECT&t;&t;0x4c&t;/* eject PC-card from slot */
DECL|macro|PMU_BATTERY_STATE
mdefine_line|#define PMU_BATTERY_STATE&t;0x6b&t;/* report battery state etc. */
DECL|macro|PMU_SET_INTR_MASK
mdefine_line|#define PMU_SET_INTR_MASK&t;0x70&t;/* set PMU interrupt mask */
DECL|macro|PMU_INT_ACK
mdefine_line|#define PMU_INT_ACK&t;&t;0x78&t;/* read interrupt bits */
DECL|macro|PMU_SHUTDOWN
mdefine_line|#define PMU_SHUTDOWN&t;&t;0x7e&t;/* turn power off */
DECL|macro|PMU_SLEEP
mdefine_line|#define PMU_SLEEP&t;&t;0x7f&t;/* put CPU to sleep */
DECL|macro|PMU_RESET
mdefine_line|#define PMU_RESET&t;&t;0xd0&t;/* reset CPU */
DECL|macro|PMU_GET_BRIGHTBUTTON
mdefine_line|#define PMU_GET_BRIGHTBUTTON&t;0xd9&t;/* report brightness up/down pos */
DECL|macro|PMU_GET_COVER
mdefine_line|#define PMU_GET_COVER&t;&t;0xdc&t;/* report cover open/closed */
multiline_comment|/* Bits to use with the PMU_POWER_CTRL command */
DECL|macro|PMU_POW_ON
mdefine_line|#define PMU_POW_ON&t;&t;0x80&t;/* OR this to power ON the device */
DECL|macro|PMU_POW_OFF
mdefine_line|#define PMU_POW_OFF&t;&t;0x00&t;/* leave bit 7 to 0 to power it OFF */
DECL|macro|PMU_POW_BACKLIGHT
mdefine_line|#define PMU_POW_BACKLIGHT&t;0x01&t;/* backlight power */
DECL|macro|PMU_POW_IRLED
mdefine_line|#define PMU_POW_IRLED&t;&t;0x04&t;/* IR led power (on wallstreet) ??? */
multiline_comment|/* Bits in PMU interrupt and interrupt mask bytes */
DECL|macro|PMU_INT_ADB_AUTO
mdefine_line|#define PMU_INT_ADB_AUTO&t;0x04&t;/* ADB autopoll, when PMU_INT_ADB */
DECL|macro|PMU_INT_PCEJECT
mdefine_line|#define PMU_INT_PCEJECT&t;&t;0x04&t;/* PC-card eject buttons */
DECL|macro|PMU_INT_SNDBRT
mdefine_line|#define PMU_INT_SNDBRT&t;&t;0x08&t;/* sound/brightness up/down buttons */
DECL|macro|PMU_INT_ADB
mdefine_line|#define PMU_INT_ADB&t;&t;0x10&t;/* ADB autopoll or reply data */
DECL|macro|PMU_INT_TICK
mdefine_line|#define PMU_INT_TICK&t;&t;0x80&t;/* 1-second tick interrupt */
multiline_comment|/* Kind of PMU (model) */
r_enum
(brace
DECL|enumerator|PMU_UNKNOWN
id|PMU_UNKNOWN
comma
DECL|enumerator|PMU_OHARE_BASED
id|PMU_OHARE_BASED
comma
DECL|enumerator|PMU_HEATHROW_BASED
id|PMU_HEATHROW_BASED
)brace
suffix:semicolon
multiline_comment|/*&n; * Ioctl commands for the /dev/pmu device&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* no param */
DECL|macro|PMU_IOC_SLEEP
mdefine_line|#define PMU_IOC_SLEEP&t;&t;_IO(&squot;B&squot;, 0)
multiline_comment|/* out param: u32*&t;backlight value: 0 to 31 */
DECL|macro|PMU_IOC_GET_BACKLIGHT
mdefine_line|#define PMU_IOC_GET_BACKLIGHT&t;_IOR(&squot;B&squot;, 1, sizeof(__u32*))
multiline_comment|/* in param: u32&t;backlight value: 0 to 31 */
DECL|macro|PMU_IOC_SET_BACKLIGHT
mdefine_line|#define PMU_IOC_SET_BACKLIGHT&t;_IOW(&squot;B&squot;, 2, sizeof(__u32))
multiline_comment|/* out param: u32*&t;backlight value: 0 to 31 */
DECL|macro|PMU_IOC_GET_MODEL
mdefine_line|#define PMU_IOC_GET_MODEL&t;_IOR(&squot;B&squot;, 3, sizeof(__u32*))
macro_line|#ifdef __KERNEL__
r_void
id|find_via_pmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|via_pmu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pmu_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|pmu_send_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
)paren
suffix:semicolon
r_void
id|pmu_poll
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pmu_enable_backlight
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_void
id|pmu_set_brightness
c_func
(paren
r_int
id|level
)paren
suffix:semicolon
r_void
id|pmu_enable_irled
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_void
id|pmu_restart
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pmu_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pmu_get_model
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Stuff for putting the powerbook to sleep and waking it again.&n; */
macro_line|#include &lt;linux/notifier.h&gt;
r_extern
r_struct
id|notifier_block
op_star
id|sleep_notifier_list
suffix:semicolon
multiline_comment|/* code values for calling sleep/wakeup handlers */
DECL|macro|PBOOK_SLEEP
mdefine_line|#define PBOOK_SLEEP&t;1
DECL|macro|PBOOK_WAKE
mdefine_line|#define PBOOK_WAKE&t;2
macro_line|#endif&t;/* __KERNEL */
eof
