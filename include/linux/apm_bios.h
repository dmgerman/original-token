macro_line|#ifndef _LINUX_APM_H
DECL|macro|_LINUX_APM_H
mdefine_line|#define _LINUX_APM_H
multiline_comment|/*&n; * Include file for the interface to an APM BIOS&n; * Copyright 1994, 1995 Stephen Rothwell (Stephen.Rothwell@pd.necisa.oz.au)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * $Id: apm_bios.h,v 0.9 1995/03/09 13:50:05 sfr Exp $&n; */
DECL|typedef|apm_event_t
r_typedef
r_int
r_int
id|apm_event_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/tasks.h&gt;&t;/* for NR_TASKS */
macro_line|#include &lt;linux/sched.h&gt;&t;/* for _TSS */
DECL|macro|APM_CS
mdefine_line|#define APM_CS&t;&t;_TSS(NR_TASKS)
DECL|macro|APM_CS_16
mdefine_line|#define APM_CS_16&t;(APM_CS + 8)
DECL|macro|APM_DS
mdefine_line|#define APM_DS&t;&t;(APM_CS_16 + 8)
DECL|struct|apm_bios_info
r_struct
id|apm_bios_info
(brace
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|cseg
r_int
r_int
id|cseg
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|cseg_16
r_int
r_int
id|cseg_16
suffix:semicolon
DECL|member|dseg
r_int
r_int
id|dseg
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|cseg_len
r_int
r_int
id|cseg_len
suffix:semicolon
DECL|member|dseg_len
r_int
r_int
id|dseg_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Results of APM Installation Check */
DECL|macro|APM_16_BIT_SUPPORT
mdefine_line|#define APM_16_BIT_SUPPORT&t;0x0001
DECL|macro|APM_32_BIT_SUPPORT
mdefine_line|#define APM_32_BIT_SUPPORT&t;0x0002
DECL|macro|APM_IDLE_SLOWS_CLOCK
mdefine_line|#define APM_IDLE_SLOWS_CLOCK&t;0x0004
DECL|macro|APM_BIOS_DISABLED
mdefine_line|#define APM_BIOS_DISABLED      &t;0x0008
DECL|macro|APM_BIOS_DISENGAGED
mdefine_line|#define APM_BIOS_DISENGAGED     0x0010
multiline_comment|/*&n; * Maximum number of events stored&n; */
DECL|macro|APM_MAX_EVENTS
mdefine_line|#define APM_MAX_EVENTS&t;&t;20
multiline_comment|/*&n; * The per-file APM data&n; */
DECL|struct|apm_bios_struct
r_struct
id|apm_bios_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|next
r_struct
id|apm_bios_struct
op_star
id|next
suffix:semicolon
DECL|member|suser
r_int
id|suser
suffix:semicolon
DECL|member|suspends_pending
r_int
id|suspends_pending
suffix:semicolon
DECL|member|standbys_pending
r_int
id|standbys_pending
suffix:semicolon
DECL|member|event_head
r_int
id|event_head
suffix:semicolon
DECL|member|event_tail
r_int
id|event_tail
suffix:semicolon
DECL|member|events
id|apm_event_t
id|events
(braket
id|APM_MAX_EVENTS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The magic number in apm_bios_struct&n; */
DECL|macro|APM_BIOS_MAGIC
mdefine_line|#define APM_BIOS_MAGIC&t;&t;0x4101
multiline_comment|/*&n; * in init/main.c&n; */
r_extern
r_struct
id|apm_bios_info
id|apm_bios_info
suffix:semicolon
r_extern
r_void
id|apm_bios_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|apm_register_callback
c_func
(paren
r_int
(paren
op_star
id|callback
)paren
(paren
id|apm_event_t
)paren
)paren
suffix:semicolon
r_extern
r_void
id|apm_unregister_callback
c_func
(paren
r_int
(paren
op_star
id|callback
)paren
(paren
id|apm_event_t
)paren
)paren
suffix:semicolon
r_extern
r_int
id|apm_display_blank
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|apm_display_unblank
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Power states&n; */
DECL|macro|APM_STATE_READY
mdefine_line|#define APM_STATE_READY&t;&t;0x0000
DECL|macro|APM_STATE_STANDBY
mdefine_line|#define APM_STATE_STANDBY&t;0x0001
DECL|macro|APM_STATE_SUSPEND
mdefine_line|#define APM_STATE_SUSPEND&t;0x0002
DECL|macro|APM_STATE_OFF
mdefine_line|#define APM_STATE_OFF&t;&t;0x0003
DECL|macro|APM_STATE_BUSY
mdefine_line|#define APM_STATE_BUSY&t;&t;0x0004
DECL|macro|APM_STATE_REJECT
mdefine_line|#define APM_STATE_REJECT&t;0x0005
multiline_comment|/*&n; * Events (results of Get PM Event)&n; */
DECL|macro|APM_SYS_STANDBY
mdefine_line|#define APM_SYS_STANDBY&t;&t;0x0001
DECL|macro|APM_SYS_SUSPEND
mdefine_line|#define APM_SYS_SUSPEND&t;&t;0x0002
DECL|macro|APM_NORMAL_RESUME
mdefine_line|#define APM_NORMAL_RESUME&t;0x0003
DECL|macro|APM_CRITICAL_RESUME
mdefine_line|#define APM_CRITICAL_RESUME&t;0x0004
DECL|macro|APM_LOW_BATTERY
mdefine_line|#define APM_LOW_BATTERY&t;&t;0x0005
DECL|macro|APM_POWER_STATUS_CHANGE
mdefine_line|#define APM_POWER_STATUS_CHANGE&t;0x0006
DECL|macro|APM_UPDATE_TIME
mdefine_line|#define APM_UPDATE_TIME&t;&t;0x0007
DECL|macro|APM_CRITICAL_SUSPEND
mdefine_line|#define APM_CRITICAL_SUSPEND&t;0x0008
DECL|macro|APM_USER_STANDBY
mdefine_line|#define APM_USER_STANDBY&t;0x0009
DECL|macro|APM_USER_SUSPEND
mdefine_line|#define APM_USER_SUSPEND&t;0x000a
DECL|macro|APM_STANDBY_RESUME
mdefine_line|#define APM_STANDBY_RESUME&t;0x000b
multiline_comment|/*&n; * Error codes&n; */
DECL|macro|APM_SUCCESS
mdefine_line|#define APM_SUCCESS&t;&t;0x00
DECL|macro|APM_DISABLED
mdefine_line|#define APM_DISABLED&t;&t;0x01
DECL|macro|APM_CONNECTED
mdefine_line|#define APM_CONNECTED&t;&t;0x02
DECL|macro|APM_NOT_CONNECTED
mdefine_line|#define APM_NOT_CONNECTED&t;0x03
DECL|macro|APM_16_CONNECTED
mdefine_line|#define APM_16_CONNECTED&t;0x05
DECL|macro|APM_16_UNSUPPORTED
mdefine_line|#define APM_16_UNSUPPORTED&t;0x06
DECL|macro|APM_32_CONNECTED
mdefine_line|#define APM_32_CONNECTED&t;0x07
DECL|macro|APM_32_UNSUPPORTED
mdefine_line|#define APM_32_UNSUPPORTED&t;0x08
DECL|macro|APM_BAD_DEVICE
mdefine_line|#define APM_BAD_DEVICE&t;&t;0x09
DECL|macro|APM_BAD_PARAM
mdefine_line|#define APM_BAD_PARAM&t;&t;0x0a
DECL|macro|APM_NOT_ENGAGED
mdefine_line|#define APM_NOT_ENGAGED&t;&t;0x0b
DECL|macro|APM_BAD_STATE
mdefine_line|#define APM_BAD_STATE&t;&t;0x60
DECL|macro|APM_NO_EVENTS
mdefine_line|#define APM_NO_EVENTS&t;&t;0x80
DECL|macro|APM_NOT_PRESENT
mdefine_line|#define APM_NOT_PRESENT&t;&t;0x86
multiline_comment|/* ioctl operations */
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|APM_IOC_STANDBY
mdefine_line|#define APM_IOC_STANDBY&t;&t;_IO(&squot;A&squot;, 1)
DECL|macro|APM_IOC_SUSPEND
mdefine_line|#define APM_IOC_SUSPEND&t;&t;_IO(&squot;A&squot;, 2)
macro_line|#endif&t;/* LINUX_APM_H */
eof
