multiline_comment|/*&n; *  acpi.h - ACPI driver interface&n; *&n; *  Copyright (C) 1999 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_ACPI_H
DECL|macro|_LINUX_ACPI_H
mdefine_line|#define _LINUX_ACPI_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * System sleep states&n; */
r_enum
(brace
DECL|enumerator|ACPI_S0
id|ACPI_S0
comma
multiline_comment|/* working */
DECL|enumerator|ACPI_S1
id|ACPI_S1
comma
multiline_comment|/* sleep */
DECL|enumerator|ACPI_S2
id|ACPI_S2
comma
multiline_comment|/* sleep */
DECL|enumerator|ACPI_S3
id|ACPI_S3
comma
multiline_comment|/* sleep */
DECL|enumerator|ACPI_S4
id|ACPI_S4
comma
multiline_comment|/* non-volatile sleep */
DECL|enumerator|ACPI_S5
id|ACPI_S5
comma
multiline_comment|/* soft-off */
)brace
suffix:semicolon
DECL|typedef|acpi_sstate_t
r_typedef
r_int
id|acpi_sstate_t
suffix:semicolon
multiline_comment|/*&n; * Device states&n; */
r_enum
(brace
DECL|enumerator|ACPI_D0
id|ACPI_D0
comma
multiline_comment|/* fully-on */
DECL|enumerator|ACPI_D1
id|ACPI_D1
comma
multiline_comment|/* partial-on */
DECL|enumerator|ACPI_D2
id|ACPI_D2
comma
multiline_comment|/* partial-on */
DECL|enumerator|ACPI_D3
id|ACPI_D3
comma
multiline_comment|/* fully-off */
)brace
suffix:semicolon
DECL|typedef|acpi_dstate_t
r_typedef
r_int
id|acpi_dstate_t
suffix:semicolon
multiline_comment|/*&n; * HID (PnP) values&n; */
r_enum
(brace
DECL|enumerator|ACPI_UNKNOWN_HID
id|ACPI_UNKNOWN_HID
op_assign
l_int|0x00000000
comma
multiline_comment|/* generic */
DECL|enumerator|ACPI_KBC_HID
id|ACPI_KBC_HID
op_assign
l_int|0x41d00303
comma
multiline_comment|/* keyboard controller */
DECL|enumerator|ACPI_COM_HID
id|ACPI_COM_HID
op_assign
l_int|0x41d00500
comma
multiline_comment|/* serial port */
DECL|enumerator|ACPI_FDC_HID
id|ACPI_FDC_HID
op_assign
l_int|0x41d00700
comma
multiline_comment|/* floppy controller */
DECL|enumerator|ACPI_VGA_HID
id|ACPI_VGA_HID
op_assign
l_int|0x41d00900
comma
multiline_comment|/* VGA controller */
DECL|enumerator|ACPI_ISA_HID
id|ACPI_ISA_HID
op_assign
l_int|0x41d00a00
comma
multiline_comment|/* ISA bus */
DECL|enumerator|ACPI_EISA_HID
id|ACPI_EISA_HID
op_assign
l_int|0x41d00a01
comma
multiline_comment|/* EISA bus */
DECL|enumerator|ACPI_PCI_HID
id|ACPI_PCI_HID
op_assign
l_int|0x41d00a03
comma
multiline_comment|/* PCI bus */
)brace
suffix:semicolon
DECL|typedef|acpi_hid_t
r_typedef
r_int
id|acpi_hid_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Device types&n; */
r_enum
(brace
DECL|enumerator|ACPI_SYS_DEV
id|ACPI_SYS_DEV
comma
multiline_comment|/* system device (fan, KB controller, ...) */
DECL|enumerator|ACPI_PCI_DEV
id|ACPI_PCI_DEV
comma
multiline_comment|/* generic PCI device */
DECL|enumerator|ACPI_PCI_BUS
id|ACPI_PCI_BUS
comma
multiline_comment|/* PCI bus */
DECL|enumerator|ACPI_ISA_DEV
id|ACPI_ISA_DEV
comma
multiline_comment|/* generic ISA device */
DECL|enumerator|ACPI_ISA_BUS
id|ACPI_ISA_BUS
comma
multiline_comment|/* ISA bus */
DECL|enumerator|ACPI_USB_DEV
id|ACPI_USB_DEV
comma
multiline_comment|/* generic USB device */
DECL|enumerator|ACPI_USB_HUB
id|ACPI_USB_HUB
comma
multiline_comment|/* USB hub device */
DECL|enumerator|ACPI_USB_CTRL
id|ACPI_USB_CTRL
comma
multiline_comment|/* USB controller */
DECL|enumerator|ACPI_SCSI_DEV
id|ACPI_SCSI_DEV
comma
multiline_comment|/* generic SCSI device */
DECL|enumerator|ACPI_SCSI_CTRL
id|ACPI_SCSI_CTRL
comma
multiline_comment|/* SCSI controller */
)brace
suffix:semicolon
DECL|typedef|acpi_dev_t
r_typedef
r_int
id|acpi_dev_t
suffix:semicolon
multiline_comment|/*&n; * Device addresses&n; */
DECL|macro|ACPI_PCI_ADR
mdefine_line|#define ACPI_PCI_ADR(dev) ((dev)-&gt;bus-&gt;number &lt;&lt; 16 | (dev)-&gt;devfn)
r_struct
id|acpi_dev
suffix:semicolon
multiline_comment|/*&n; * Device state transition function&n; */
DECL|typedef|acpi_transition
r_typedef
r_int
(paren
op_star
id|acpi_transition
)paren
(paren
r_struct
id|acpi_dev
op_star
id|dev
comma
id|acpi_dstate_t
id|state
)paren
suffix:semicolon
multiline_comment|/*&n; * Static device information&n; */
DECL|struct|acpi_dev_info
r_struct
id|acpi_dev_info
(brace
DECL|member|type
id|acpi_dev_t
id|type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|hid
id|acpi_hid_t
id|hid
suffix:semicolon
multiline_comment|/* PnP identifier */
DECL|member|transition
id|acpi_transition
id|transition
suffix:semicolon
multiline_comment|/* state transition callback */
multiline_comment|/* other information like D-states supported,&n;&t; * D-state latencies, and in-rush current needs&n;&t; * will go here&n;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * Dynamic device information&n; */
DECL|struct|acpi_dev
r_struct
id|acpi_dev
(brace
DECL|member|info
r_struct
id|acpi_dev_info
id|info
suffix:semicolon
multiline_comment|/* static device info */
DECL|member|adr
r_int
r_int
id|adr
suffix:semicolon
multiline_comment|/* bus address or unique id */
DECL|member|state
id|acpi_dstate_t
id|state
suffix:semicolon
multiline_comment|/* current D-state */
DECL|member|accessed
r_int
r_int
id|accessed
suffix:semicolon
multiline_comment|/* last access time */
DECL|member|idle
r_int
r_int
id|idle
suffix:semicolon
multiline_comment|/* last idle time */
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
multiline_comment|/* linked list entry */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI
r_extern
id|wait_queue_head_t
id|acpi_control_wait
suffix:semicolon
multiline_comment|/*&n; * Register a device with the ACPI subsystem&n; */
r_struct
id|acpi_dev
op_star
id|acpi_register
c_func
(paren
r_struct
id|acpi_dev_info
op_star
id|info
comma
r_int
r_int
id|adr
)paren
suffix:semicolon
multiline_comment|/*&n; * Unregister a device with ACPI&n; */
r_void
id|acpi_unregister
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Update device access time and wake up device, if necessary&n; */
DECL|function|acpi_access
r_extern
r_inline
r_void
id|acpi_access
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
(brace
r_extern
r_void
id|acpi_wakeup
c_func
(paren
r_struct
id|acpi_dev
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;state
op_ne
id|ACPI_D0
)paren
id|acpi_wakeup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;accessed
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Identify device as currently being idle&n; */
DECL|function|acpi_dev_idle
r_extern
r_inline
r_void
id|acpi_dev_idle
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
(brace
id|dev-&gt;idle
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|acpi_control_wait
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|acpi_control_wait
)paren
suffix:semicolon
)brace
)brace
macro_line|#else /* CONFIG_ACPI */
r_extern
r_inline
r_struct
id|acpi_dev
op_star
DECL|function|acpi_register
id|acpi_register
c_func
(paren
r_struct
id|acpi_dev_info
op_star
id|info
comma
r_int
r_int
id|adr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_unregister
r_extern
r_inline
r_void
id|acpi_unregister
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|acpi_access
r_extern
r_inline
r_void
id|acpi_access
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|acpi_dev_idle
r_extern
r_inline
r_void
id|acpi_dev_idle
c_func
(paren
r_struct
id|acpi_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* CONFIG_ACPI */
r_extern
r_void
(paren
op_star
id|acpi_idle
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|acpi_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* RSDP location */
DECL|macro|ACPI_BIOS_ROM_BASE
mdefine_line|#define ACPI_BIOS_ROM_BASE (0x0e0000)
DECL|macro|ACPI_BIOS_ROM_END
mdefine_line|#define ACPI_BIOS_ROM_END  (0x100000)
multiline_comment|/* Table signatures */
DECL|macro|ACPI_RSDP1_SIG
mdefine_line|#define ACPI_RSDP1_SIG 0x20445352 /* &squot;RSD &squot; */
DECL|macro|ACPI_RSDP2_SIG
mdefine_line|#define ACPI_RSDP2_SIG 0x20525450 /* &squot;PTR &squot; */
DECL|macro|ACPI_RSDT_SIG
mdefine_line|#define ACPI_RSDT_SIG  0x54445352 /* &squot;RSDT&squot; */
DECL|macro|ACPI_FACP_SIG
mdefine_line|#define ACPI_FACP_SIG  0x50434146 /* &squot;FACP&squot; */
DECL|macro|ACPI_DSDT_SIG
mdefine_line|#define ACPI_DSDT_SIG  0x54445344 /* &squot;DSDT&squot; */
DECL|macro|ACPI_FACS_SIG
mdefine_line|#define ACPI_FACS_SIG  0x53434146 /* &squot;FACS&squot; */
multiline_comment|/* PM1_STS/EN flags */
DECL|macro|ACPI_TMR
mdefine_line|#define ACPI_TMR    0x0001
DECL|macro|ACPI_BM
mdefine_line|#define ACPI_BM&t;    0x0010
DECL|macro|ACPI_GBL
mdefine_line|#define ACPI_GBL    0x0020
DECL|macro|ACPI_PWRBTN
mdefine_line|#define ACPI_PWRBTN 0x0100
DECL|macro|ACPI_SLPBTN
mdefine_line|#define ACPI_SLPBTN 0x0200
DECL|macro|ACPI_RTC
mdefine_line|#define ACPI_RTC    0x0400
DECL|macro|ACPI_WAK
mdefine_line|#define ACPI_WAK    0x8000
multiline_comment|/* PM1_CNT flags */
DECL|macro|ACPI_SCI_EN
mdefine_line|#define ACPI_SCI_EN   0x0001
DECL|macro|ACPI_BM_RLD
mdefine_line|#define ACPI_BM_RLD   0x0002
DECL|macro|ACPI_GBL_RLS
mdefine_line|#define ACPI_GBL_RLS  0x0004
DECL|macro|ACPI_SLP_TYP0
mdefine_line|#define ACPI_SLP_TYP0 0x0400
DECL|macro|ACPI_SLP_TYP1
mdefine_line|#define ACPI_SLP_TYP1 0x0800
DECL|macro|ACPI_SLP_TYP2
mdefine_line|#define ACPI_SLP_TYP2 0x1000
DECL|macro|ACPI_SLP_EN
mdefine_line|#define ACPI_SLP_EN   0x2000
DECL|macro|ACPI_SLP_TYP_MASK
mdefine_line|#define ACPI_SLP_TYP_MASK  0x1c00
DECL|macro|ACPI_SLP_TYP_SHIFT
mdefine_line|#define ACPI_SLP_TYP_SHIFT 10
multiline_comment|/* PM_TMR masks */
DECL|macro|ACPI_TMR_MASK
mdefine_line|#define ACPI_TMR_MASK&t;0x00ffffff
DECL|macro|ACPI_TMR_HZ
mdefine_line|#define ACPI_TMR_HZ&t;3580000 /* 3.58 MHz */
multiline_comment|/* strangess to avoid integer overflow */
DECL|macro|ACPI_uS_TO_TMR_TICKS
mdefine_line|#define ACPI_uS_TO_TMR_TICKS(val) &bslash;&n;  (((val) * (ACPI_TMR_HZ / 10000)) / 100)
DECL|macro|ACPI_TMR_TICKS_TO_uS
mdefine_line|#define ACPI_TMR_TICKS_TO_uS(ticks) &bslash;&n;  (((ticks) * 100) / (ACPI_TMR_HZ / 10000))
multiline_comment|/* PM2_CNT flags */
DECL|macro|ACPI_ARB_DIS
mdefine_line|#define ACPI_ARB_DIS 0x01
multiline_comment|/* FACP flags */
DECL|macro|ACPI_WBINVD
mdefine_line|#define ACPI_WBINVD&t;  0x00000001
DECL|macro|ACPI_WBINVD_FLUSH
mdefine_line|#define ACPI_WBINVD_FLUSH 0x00000002
DECL|macro|ACPI_PROC_C1
mdefine_line|#define ACPI_PROC_C1&t;  0x00000004
DECL|macro|ACPI_P_LVL2_UP
mdefine_line|#define ACPI_P_LVL2_UP&t;  0x00000008
DECL|macro|ACPI_PWR_BUTTON
mdefine_line|#define ACPI_PWR_BUTTON&t;  0x00000010
DECL|macro|ACPI_SLP_BUTTON
mdefine_line|#define ACPI_SLP_BUTTON&t;  0x00000020
DECL|macro|ACPI_FIX_RTC
mdefine_line|#define ACPI_FIX_RTC&t;  0x00000040
DECL|macro|ACPI_RTC_64
mdefine_line|#define ACPI_RTC_64&t;  0x00000080
DECL|macro|ACPI_TMR_VAL_EXT
mdefine_line|#define ACPI_TMR_VAL_EXT  0x00000100
DECL|macro|ACPI_DCK_CAP
mdefine_line|#define ACPI_DCK_CAP&t;  0x00000200
multiline_comment|/* FACS flags */
DECL|macro|ACPI_S4BIOS
mdefine_line|#define ACPI_S4BIOS&t;  0x00000001
multiline_comment|/* processor block offsets */
DECL|macro|ACPI_P_CNT
mdefine_line|#define ACPI_P_CNT&t;  0x00000000
DECL|macro|ACPI_P_LVL2
mdefine_line|#define ACPI_P_LVL2&t;  0x00000004
DECL|macro|ACPI_P_LVL3
mdefine_line|#define ACPI_P_LVL3&t;  0x00000005
multiline_comment|/* C-state latencies (microseconds) */
DECL|macro|ACPI_MAX_P_LVL2_LAT
mdefine_line|#define ACPI_MAX_P_LVL2_LAT 100
DECL|macro|ACPI_MAX_P_LVL3_LAT
mdefine_line|#define ACPI_MAX_P_LVL3_LAT 1000
DECL|macro|ACPI_INFINITE_LAT
mdefine_line|#define ACPI_INFINITE_LAT   (~0UL)
DECL|struct|acpi_rsdp
r_struct
id|acpi_rsdp
(brace
DECL|member|signature
id|__u32
id|signature
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|checksum
id|__u8
id|checksum
suffix:semicolon
DECL|member|oem
id|__u8
id|oem
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
DECL|member|rsdt
id|__u32
id|rsdt
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table
r_struct
id|acpi_table
(brace
DECL|member|signature
id|__u32
id|signature
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|rev
id|__u8
id|rev
suffix:semicolon
DECL|member|checksum
id|__u8
id|checksum
suffix:semicolon
DECL|member|oem
id|__u8
id|oem
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|oem_table
id|__u8
id|oem_table
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|oem_rev
id|__u32
id|oem_rev
suffix:semicolon
DECL|member|creator
id|__u32
id|creator
suffix:semicolon
DECL|member|creator_rev
id|__u32
id|creator_rev
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_facp
r_struct
id|acpi_facp
(brace
DECL|member|hdr
r_struct
id|acpi_table
id|hdr
suffix:semicolon
DECL|member|facs
id|__u32
id|facs
suffix:semicolon
DECL|member|dsdt
id|__u32
id|dsdt
suffix:semicolon
DECL|member|int_model
id|__u8
id|int_model
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
DECL|member|sci_int
id|__u16
id|sci_int
suffix:semicolon
DECL|member|smi_cmd
id|__u32
id|smi_cmd
suffix:semicolon
DECL|member|acpi_enable
id|__u8
id|acpi_enable
suffix:semicolon
DECL|member|acpi_disable
id|__u8
id|acpi_disable
suffix:semicolon
DECL|member|s4bios_req
id|__u8
id|s4bios_req
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
DECL|member|pm1a_evt
id|__u32
id|pm1a_evt
suffix:semicolon
DECL|member|pm1b_evt
id|__u32
id|pm1b_evt
suffix:semicolon
DECL|member|pm1a_cnt
id|__u32
id|pm1a_cnt
suffix:semicolon
DECL|member|pm1b_cnt
id|__u32
id|pm1b_cnt
suffix:semicolon
DECL|member|pm2_cnt
id|__u32
id|pm2_cnt
suffix:semicolon
DECL|member|pm_tmr
id|__u32
id|pm_tmr
suffix:semicolon
DECL|member|gpe0
id|__u32
id|gpe0
suffix:semicolon
DECL|member|gpe1
id|__u32
id|gpe1
suffix:semicolon
DECL|member|pm1_evt_len
id|__u8
id|pm1_evt_len
suffix:semicolon
DECL|member|pm1_cnt_len
id|__u8
id|pm1_cnt_len
suffix:semicolon
DECL|member|pm2_cnt_len
id|__u8
id|pm2_cnt_len
suffix:semicolon
DECL|member|pm_tm_len
id|__u8
id|pm_tm_len
suffix:semicolon
DECL|member|gpe0_len
id|__u8
id|gpe0_len
suffix:semicolon
DECL|member|gpe1_len
id|__u8
id|gpe1_len
suffix:semicolon
DECL|member|gpe1_base
id|__u8
id|gpe1_base
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|p_lvl2_lat
id|__u16
id|p_lvl2_lat
suffix:semicolon
DECL|member|p_lvl3_lat
id|__u16
id|p_lvl3_lat
suffix:semicolon
DECL|member|flush_size
id|__u16
id|flush_size
suffix:semicolon
DECL|member|flush_stride
id|__u16
id|flush_stride
suffix:semicolon
DECL|member|duty_offset
id|__u8
id|duty_offset
suffix:semicolon
DECL|member|duty_width
id|__u8
id|duty_width
suffix:semicolon
DECL|member|day_alarm
id|__u8
id|day_alarm
suffix:semicolon
DECL|member|mon_alarm
id|__u8
id|mon_alarm
suffix:semicolon
DECL|member|century
id|__u8
id|century
suffix:semicolon
DECL|member|reserved4
id|__u8
id|reserved4
suffix:semicolon
DECL|member|reserved5
id|__u8
id|reserved5
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_facs
r_struct
id|acpi_facs
(brace
DECL|member|signature
id|__u32
id|signature
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|hw_signature
id|__u32
id|hw_signature
suffix:semicolon
DECL|member|fw_wake_vector
id|__u32
id|fw_wake_vector
suffix:semicolon
DECL|member|global_lock
id|__u32
id|global_lock
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Sysctl declarations&n; */
r_enum
(brace
DECL|enumerator|CTL_ACPI
id|CTL_ACPI
op_assign
l_int|10
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|ACPI_FACP
id|ACPI_FACP
op_assign
l_int|1
comma
DECL|enumerator|ACPI_DSDT
id|ACPI_DSDT
comma
DECL|enumerator|ACPI_PM1_ENABLE
id|ACPI_PM1_ENABLE
comma
DECL|enumerator|ACPI_GPE_ENABLE
id|ACPI_GPE_ENABLE
comma
DECL|enumerator|ACPI_GPE_LEVEL
id|ACPI_GPE_LEVEL
comma
DECL|enumerator|ACPI_EVENT
id|ACPI_EVENT
comma
DECL|enumerator|ACPI_P_BLK
id|ACPI_P_BLK
comma
DECL|enumerator|ACPI_P_LVL2_LAT
id|ACPI_P_LVL2_LAT
comma
DECL|enumerator|ACPI_P_LVL3_LAT
id|ACPI_P_LVL3_LAT
comma
DECL|enumerator|ACPI_S0_SLP_TYP
id|ACPI_S0_SLP_TYP
comma
DECL|enumerator|ACPI_S1_SLP_TYP
id|ACPI_S1_SLP_TYP
comma
DECL|enumerator|ACPI_S5_SLP_TYP
id|ACPI_S5_SLP_TYP
comma
DECL|enumerator|ACPI_SLEEP
id|ACPI_SLEEP
comma
)brace
suffix:semicolon
DECL|macro|ACPI_SLP_TYP_DISABLED
mdefine_line|#define ACPI_SLP_TYP_DISABLED&t;(~0UL)
multiline_comment|/*&n; * PIIX4-specific ACPI info (for systems with PIIX4 but no ACPI tables)&n; */
DECL|macro|ACPI_PIIX4_INT_MODEL
mdefine_line|#define ACPI_PIIX4_INT_MODEL&t;0x00
DECL|macro|ACPI_PIIX4_SCI_INT
mdefine_line|#define ACPI_PIIX4_SCI_INT&t;0x0009
DECL|macro|ACPI_PIIX4_SMI_CMD
mdefine_line|#define ACPI_PIIX4_SMI_CMD&t;0x00b2
DECL|macro|ACPI_PIIX4_ACPI_ENABLE
mdefine_line|#define ACPI_PIIX4_ACPI_ENABLE&t;0xf0
DECL|macro|ACPI_PIIX4_ACPI_DISABLE
mdefine_line|#define ACPI_PIIX4_ACPI_DISABLE 0xf1
DECL|macro|ACPI_PIIX4_S4BIOS_REQ
mdefine_line|#define ACPI_PIIX4_S4BIOS_REQ&t;0xf2
DECL|macro|ACPI_PIIX4_PM1_EVT
mdefine_line|#define ACPI_PIIX4_PM1_EVT&t;0x0000
DECL|macro|ACPI_PIIX4_PM1_CNT
mdefine_line|#define ACPI_PIIX4_PM1_CNT&t;0x0004
DECL|macro|ACPI_PIIX4_S0_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S0_MASK&t;(0x0005 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_S1_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S1_MASK&t;(0x0004 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_S2_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S2_MASK&t;(0x0003 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_S3_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S3_MASK&t;(0x0002 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_S4_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S4_MASK&t;(0x0001 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_S5_MASK
mdefine_line|#define&t;  ACPI_PIIX4_S5_MASK&t;(0x0000 &lt;&lt; 10)
DECL|macro|ACPI_PIIX4_PM_TMR
mdefine_line|#define ACPI_PIIX4_PM_TMR&t;0x0008
DECL|macro|ACPI_PIIX4_GPE0
mdefine_line|#define ACPI_PIIX4_GPE0&t;&t;0x000c
DECL|macro|ACPI_PIIX4_P_BLK
mdefine_line|#define ACPI_PIIX4_P_BLK&t;0x0010
DECL|macro|ACPI_PIIX4_PM1_EVT_LEN
mdefine_line|#define ACPI_PIIX4_PM1_EVT_LEN&t;0x04
DECL|macro|ACPI_PIIX4_PM1_CNT_LEN
mdefine_line|#define ACPI_PIIX4_PM1_CNT_LEN&t;0x02
DECL|macro|ACPI_PIIX4_PM_TM_LEN
mdefine_line|#define ACPI_PIIX4_PM_TM_LEN&t;0x04
DECL|macro|ACPI_PIIX4_GPE0_LEN
mdefine_line|#define ACPI_PIIX4_GPE0_LEN&t;0x04
DECL|macro|ACPI_PIIX4_PM2_CNT
mdefine_line|#define ACPI_PIIX4_PM2_CNT&t;0x0022
DECL|macro|ACPI_PIIX4_PM2_CNT_LEN
mdefine_line|#define ACPI_PIIX4_PM2_CNT_LEN&t;0x01
DECL|macro|ACPI_PIIX4_PMREGMISC
mdefine_line|#define ACPI_PIIX4_PMREGMISC&t;0x80
DECL|macro|ACPI_PIIX4_PMIOSE
mdefine_line|#define&t;  ACPI_PIIX4_PMIOSE&t;0x01
macro_line|#endif /* _LINUX_ACPI_H */
eof
