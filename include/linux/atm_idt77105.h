multiline_comment|/* atm_idt77105.h - Driver-specific declarations of the IDT77105 driver (for&n; * use by driver-specific utilities) */
multiline_comment|/* Written 1999 by Greg Banks &lt;gnb@linuxfan.com&gt;. Copied from atm_suni.h. */
macro_line|#ifndef LINUX_ATM_IDT77105_H
DECL|macro|LINUX_ATM_IDT77105_H
mdefine_line|#define LINUX_ATM_IDT77105_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/*&n; * Structure for IDT77105_GETSTAT and IDT77105_GETSTATZ ioctls.&n; * Pointed to by `arg&squot; in atmif_sioc.&n; */
DECL|struct|idt77105_stats
r_struct
id|idt77105_stats
(brace
DECL|member|symbol_errors
id|__u32
id|symbol_errors
suffix:semicolon
multiline_comment|/* wire symbol errors */
DECL|member|tx_cells
id|__u32
id|tx_cells
suffix:semicolon
multiline_comment|/* cells transmitted */
DECL|member|rx_cells
id|__u32
id|rx_cells
suffix:semicolon
multiline_comment|/* cells received */
DECL|member|rx_hec_errors
id|__u32
id|rx_hec_errors
suffix:semicolon
multiline_comment|/* Header Error Check errors on receive */
)brace
suffix:semicolon
DECL|macro|IDT77105_GETLOOP
mdefine_line|#define IDT77105_GETLOOP&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV,struct atmif_sioc)&t;/* get loopback mode */
DECL|macro|IDT77105_SETLOOP
mdefine_line|#define IDT77105_SETLOOP&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV+1,struct atmif_sioc)&t;/* set loopback mode */
DECL|macro|IDT77105_GETSTAT
mdefine_line|#define IDT77105_GETSTAT&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV+2,struct atmif_sioc)&t;/* get stats */
DECL|macro|IDT77105_GETSTATZ
mdefine_line|#define IDT77105_GETSTATZ&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV+3,struct atmif_sioc)&t;/* get stats and zero */
multiline_comment|/*&n; * TODO: what we need is a global loopback mode get/set ioctl for&n; * all devices, not these device-specific hacks -- Greg Banks&n; */
DECL|macro|IDT77105_LM_NONE
mdefine_line|#define IDT77105_LM_NONE&t;0&t;/* no loopback */
DECL|macro|IDT77105_LM_DIAG
mdefine_line|#define IDT77105_LM_DIAG&t;1&t;/* diagnostic (i.e. loop TX to RX)&n;&t;&t;&t;&t;&t; * (a.k.a. local loopback) */
DECL|macro|IDT77105_LM_LOOP
mdefine_line|#define IDT77105_LM_LOOP&t;2&t;/* line (i.e. loop RX to TX)&n;&t;&t;&t;&t;&t; * (a.k.a. remote loopback) */
macro_line|#endif
eof
