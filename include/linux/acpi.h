multiline_comment|/*&n; *  acpi.h - ACPI driver interface&n; *&n; *  Copyright (C) 1999 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_ACPI_H
DECL|macro|_LINUX_ACPI_H
mdefine_line|#define _LINUX_ACPI_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* /dev/acpi minor number */
DECL|macro|ACPI_MINOR_DEV
mdefine_line|#define ACPI_MINOR_DEV 167
multiline_comment|/* RSDP location */
DECL|macro|ACPI_BIOS_ROM_BASE
mdefine_line|#define ACPI_BIOS_ROM_BASE ((__u8*) 0xe0000)
DECL|macro|ACPI_BIOS_ROM_END
mdefine_line|#define ACPI_BIOS_ROM_END  ((__u8*) 0x100000)
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
multiline_comment|/* PM1_STS flags */
DECL|macro|ACPI_TMR_STS
mdefine_line|#define ACPI_TMR_STS    0x0001
DECL|macro|ACPI_BM_STS
mdefine_line|#define ACPI_BM_STS     0x0010
DECL|macro|ACPI_GBL_STS
mdefine_line|#define ACPI_GBL_STS    0x0020
DECL|macro|ACPI_PWRBTN_STS
mdefine_line|#define ACPI_PWRBTN_STS 0x0100
DECL|macro|ACPI_SLPBTN_STS
mdefine_line|#define ACPI_SLPBTN_STS 0x0200
DECL|macro|ACPI_RTC_STS
mdefine_line|#define ACPI_RTC_STS    0x0400
DECL|macro|ACPI_WAK_STS
mdefine_line|#define ACPI_WAK_STS    0x8000
multiline_comment|/* PM1_EN flags */
DECL|macro|ACPI_TMR_EN
mdefine_line|#define ACPI_TMR_EN    0x0001
DECL|macro|ACPI_GBL_EN
mdefine_line|#define ACPI_GBL_EN    0x0020
DECL|macro|ACPI_PWRBTN_EN
mdefine_line|#define ACPI_PWRBTN_EN 0x0100
DECL|macro|ACPI_SLPBTN_EN
mdefine_line|#define ACPI_SLPBTN_EN 0x0200
DECL|macro|ACPI_RTC_EN
mdefine_line|#define ACPI_RTC_EN    0x0400
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
multiline_comment|/* PM_TMR masks */
DECL|macro|ACPI_TMR_VAL_MASK
mdefine_line|#define ACPI_TMR_VAL_MASK   0x00ffffff
DECL|macro|ACPI_E_TMR_VAL_MASK
mdefine_line|#define ACPI_E_TMR_VAL_MASK 0xff000000
multiline_comment|/* PM2_CNT flags */
DECL|macro|ACPI_ARB_DIS
mdefine_line|#define ACPI_ARB_DIS 0x01
multiline_comment|/* FACP flags */
DECL|macro|ACPI_WBINVD
mdefine_line|#define ACPI_WBINVD       0x00000001
DECL|macro|ACPI_WBINVD_FLUSH
mdefine_line|#define ACPI_WBINVD_FLUSH 0x00000002
DECL|macro|ACPI_PROC_C1
mdefine_line|#define ACPI_PROC_C1      0x00000004
DECL|macro|ACPI_P_LVL2_UP
mdefine_line|#define ACPI_P_LVL2_UP    0x00000008
DECL|macro|ACPI_PWR_BUTTON
mdefine_line|#define ACPI_PWR_BUTTON   0x00000010
DECL|macro|ACPI_SLP_BUTTON
mdefine_line|#define ACPI_SLP_BUTTON   0x00000020
DECL|macro|ACPI_FIX_RTC
mdefine_line|#define ACPI_FIX_RTC      0x00000040
DECL|macro|ACPI_RTC_64
mdefine_line|#define ACPI_RTC_64       0x00000080
DECL|macro|ACPI_TMR_VAL_EXT
mdefine_line|#define ACPI_TMR_VAL_EXT  0x00000100
DECL|macro|ACPI_DCK_CAP
mdefine_line|#define ACPI_DCK_CAP      0x00000200
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
suffix:semicolon
DECL|macro|ACPI_FIND_TABLES
mdefine_line|#define ACPI_FIND_TABLES&t;_IOR(&squot;A&squot;, 1, struct acpi_find_tables)
DECL|macro|ACPI_WAIT_EVENT
mdefine_line|#define ACPI_WAIT_EVENT&t;&t;_IO(&squot;A&squot;, 2)
DECL|struct|acpi_find_tables
r_struct
id|acpi_find_tables
(brace
DECL|member|facp
r_int
r_int
id|facp
suffix:semicolon
DECL|member|dsdt
r_int
r_int
id|dsdt
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_ACPI_H */
eof
