multiline_comment|/* $Id: isar.h,v 1.2 1998/11/15 23:54:54 keil Exp $&n; * isar.h   ISAR (Siemens PSB 7110) specific defines&n; *&n; * Author Karsten Keil (keil@isdn4linux.de)&n; *&n; *&n; * $Log: isar.h,v $&n; * Revision 1.2  1998/11/15 23:54:54  keil&n; * changes from 2.0&n; *&n; * Revision 1.1  1998/08/13 23:33:48  keil&n; * First version, only init&n; *&n; *&n; */
DECL|macro|ISAR_IRQMSK
mdefine_line|#define ISAR_IRQMSK&t;0x04
DECL|macro|ISAR_IRQSTA
mdefine_line|#define ISAR_IRQSTA&t;0x04
DECL|macro|ISAR_IRQBIT
mdefine_line|#define ISAR_IRQBIT&t;0x75
DECL|macro|ISAR_CTRL_H
mdefine_line|#define ISAR_CTRL_H&t;0x61
DECL|macro|ISAR_CTRL_L
mdefine_line|#define ISAR_CTRL_L&t;0x60
DECL|macro|ISAR_IIS
mdefine_line|#define ISAR_IIS&t;0x58
DECL|macro|ISAR_IIA
mdefine_line|#define ISAR_IIA&t;0x58
DECL|macro|ISAR_HIS
mdefine_line|#define ISAR_HIS&t;0x50
DECL|macro|ISAR_HIA
mdefine_line|#define ISAR_HIA&t;0x50
DECL|macro|ISAR_MBOX
mdefine_line|#define ISAR_MBOX&t;0x4c
DECL|macro|ISAR_WADR
mdefine_line|#define ISAR_WADR&t;0x4a
DECL|macro|ISAR_RADR
mdefine_line|#define ISAR_RADR&t;0x48 
DECL|macro|ISAR_HIS_VNR
mdefine_line|#define ISAR_HIS_VNR&t;0x14
DECL|macro|ISAR_HIS_DKEY
mdefine_line|#define ISAR_HIS_DKEY&t;0x02
DECL|macro|ISAR_HIS_FIRM
mdefine_line|#define ISAR_HIS_FIRM&t;0x1e
DECL|macro|ISAR_HIS_STDSP
mdefine_line|#define ISAR_HIS_STDSP  0x08
DECL|macro|ISAR_HIS_DIAG
mdefine_line|#define ISAR_HIS_DIAG&t;0x05
DECL|macro|ISAR_HIS_P0CFG
mdefine_line|#define ISAR_HIS_P0CFG&t;0x3c
DECL|macro|ISAR_HIS_P12CFG
mdefine_line|#define ISAR_HIS_P12CFG&t;0x24
DECL|macro|ISAR_HIS_SARTCFG
mdefine_line|#define ISAR_HIS_SARTCFG&t;0x25&t;
DECL|macro|ISAR_HIS_PUMPCFG
mdefine_line|#define ISAR_HIS_PUMPCFG&t;0x26&t;
DECL|macro|ISAR_HIS_IOM2CFG
mdefine_line|#define ISAR_HIS_IOM2CFG&t;0x27
DECL|macro|ISAR_HIS_IOM2REQ
mdefine_line|#define ISAR_HIS_IOM2REQ&t;0x07
DECL|macro|ISAR_HIS_BSTREQ
mdefine_line|#define ISAR_HIS_BSTREQ&t;0x0c
DECL|macro|ISAR_HIS_PSTREQ
mdefine_line|#define ISAR_HIS_PSTREQ&t;0x0e
DECL|macro|ISAR_HIS_SDATA
mdefine_line|#define ISAR_HIS_SDATA&t;0x20
DECL|macro|ISAR_HIS_DPS1
mdefine_line|#define ISAR_HIS_DPS1&t;0x40
DECL|macro|ISAR_HIS_DPS2
mdefine_line|#define ISAR_HIS_DPS2&t;0x80
DECL|macro|SET_DPS
mdefine_line|#define SET_DPS(x)&t;((x&lt;&lt;6) &amp; 0xc0)
DECL|macro|ISAR_IIS_MSCMSD
mdefine_line|#define ISAR_IIS_MSCMSD 0x3f
DECL|macro|ISAR_IIS_VNR
mdefine_line|#define ISAR_IIS_VNR&t;0x15
DECL|macro|ISAR_IIS_DKEY
mdefine_line|#define ISAR_IIS_DKEY&t;0x03
DECL|macro|ISAR_IIS_FIRM
mdefine_line|#define ISAR_IIS_FIRM&t;0x1f
DECL|macro|ISAR_IIS_STDSP
mdefine_line|#define ISAR_IIS_STDSP  0x09
DECL|macro|ISAR_IIS_DIAG
mdefine_line|#define ISAR_IIS_DIAG&t;0x25
DECL|macro|ISAR_IIS_GSTEV
mdefine_line|#define ISAR_IIS_GSTEV&t;0x0
DECL|macro|ISAR_IIS_BSTEV
mdefine_line|#define ISAR_IIS_BSTEV&t;0x28
DECL|macro|ISAR_IIS_BSTRSP
mdefine_line|#define ISAR_IIS_BSTRSP&t;0x2c
DECL|macro|ISAR_IIS_PSTRSP
mdefine_line|#define ISAR_IIS_PSTRSP&t;0x2e
DECL|macro|ISAR_IIS_PSTEV
mdefine_line|#define ISAR_IIS_PSTEV&t;0x2a
DECL|macro|ISAR_IIS_IOM2RSP
mdefine_line|#define ISAR_IIS_IOM2RSP&t;0x27
DECL|macro|ISAR_IIS_RDATA
mdefine_line|#define ISAR_IIS_RDATA&t;0x20
DECL|macro|ISAR_CTRL_SWVER
mdefine_line|#define ISAR_CTRL_SWVER&t;0x10
DECL|macro|ISAR_CTRL_STST
mdefine_line|#define ISAR_CTRL_STST&t;0x40
DECL|macro|ISAR_MSG_HWVER
mdefine_line|#define ISAR_MSG_HWVER&t;{0x20, 0, 1}
DECL|macro|ISAR_DP1_USE
mdefine_line|#define ISAR_DP1_USE&t;1
DECL|macro|ISAR_DP2_USE
mdefine_line|#define ISAR_DP2_USE&t;2
DECL|macro|PMOD_BYPASS
mdefine_line|#define PMOD_BYPASS&t;7
DECL|macro|SMODE_DISABLE
mdefine_line|#define SMODE_DISABLE&t;0
DECL|macro|SMODE_HDLC
mdefine_line|#define SMODE_HDLC&t;3
DECL|macro|SMODE_BINARY
mdefine_line|#define SMODE_BINARY&t;4
DECL|macro|HDLC_FED
mdefine_line|#define HDLC_FED&t;0x40
DECL|macro|HDLC_FSD
mdefine_line|#define HDLC_FSD&t;0x20
DECL|macro|HDLC_FST
mdefine_line|#define HDLC_FST&t;0x20
DECL|macro|HDLC_ERROR
mdefine_line|#define HDLC_ERROR&t;0x1c
DECL|macro|BSTAT_RDM0
mdefine_line|#define BSTAT_RDM0&t;0x1
DECL|macro|BSTAT_RDM1
mdefine_line|#define BSTAT_RDM1&t;0x2
DECL|macro|BSTAT_RDM2
mdefine_line|#define BSTAT_RDM2&t;0x4
DECL|macro|BSTAT_RDM3
mdefine_line|#define BSTAT_RDM3&t;0x8
r_extern
r_int
id|ISARVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|isar_load_firmware
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|isar_int_main
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|initisar
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|isar_fill_fifo
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
suffix:semicolon
eof
