multiline_comment|/*&n; * Definitions for talking to the PMU.  The PMU is a microcontroller&n; * which controls battery charging and system power on PowerBook 3400&n; * and 2400 models as well as the RTC and various other things.&n; *&n; * Copyright (C) 1998 Paul Mackerras.&n; */
multiline_comment|/*&n; * PMU commands&n; */
DECL|macro|PMU_BACKLIGHT_CTRL
mdefine_line|#define PMU_BACKLIGHT_CTRL&t;0x11&t;/* control backlight */
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
DECL|macro|PMU_BACKLIGHT_BRIGHT
mdefine_line|#define PMU_BACKLIGHT_BRIGHT&t;0x41&t;/* set backlight brightness */
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
macro_line|#ifdef __KERNEL__
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
macro_line|#endif&t;/* __KERNEL */
eof
