multiline_comment|/* $Id: firehose.h,v 1.3 1998/06/10 07:28:43 davem Exp $&n; * firehose.h: Defines for the Fire Hose Controller (FHC) found&n; *             on Sunfire/Starfire/Wildfire systems.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_FIREHOSE_H
DECL|macro|_SPARC64_FIREHOSE_H
mdefine_line|#define _SPARC64_FIREHOSE_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* XXX I have not fully verified the register sizes in this file yet... -DaveM */
multiline_comment|/* Fire Hose Controller Internal Registers */
DECL|struct|fhc_internal_regs
r_struct
id|fhc_internal_regs
(brace
DECL|member|fhc_id
multiline_comment|/*0x0000*/
id|u32
id|fhc_id
suffix:semicolon
multiline_comment|/* FHC ID Register&t;&t;&t;*/
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fhc_rcs
multiline_comment|/*0x0010*/
id|u32
id|fhc_rcs
suffix:semicolon
multiline_comment|/* FHC Reset Control/Status Register&t;*/
DECL|member|_unused2
id|u32
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fhc_control
multiline_comment|/*0x0020*/
id|u32
id|fhc_control
suffix:semicolon
multiline_comment|/* FHC Control Register&t;&t;&t;*/
DECL|member|_unused3
id|u32
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fhc_bsr
multiline_comment|/*0x0030*/
id|u32
id|fhc_bsr
suffix:semicolon
multiline_comment|/* FHC Board Status Register&t;&t;*/
DECL|member|_unused4
id|u32
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fhc_ecc
multiline_comment|/*0x0040*/
id|u32
id|fhc_ecc
suffix:semicolon
multiline_comment|/* FHC ECC Control Register (16 bits)&t;*/
DECL|member|_unused5
id|u32
id|_unused5
(braket
l_int|43
)braket
suffix:semicolon
DECL|member|fhc_jtag_ctrl
multiline_comment|/*0x00f0*/
id|u32
id|fhc_jtag_ctrl
suffix:semicolon
multiline_comment|/* FHC JTAG Control Register&t;&t;*/
DECL|member|_unused6
id|u32
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fhc_jtag_cmd
multiline_comment|/*0x0100*/
id|u32
id|fhc_jtag_cmd
suffix:semicolon
multiline_comment|/* FHC JTAG Command Register&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* Part of same space of regs, but mapped separately in PROM reg property&n; * for the FHC, thus we have the following few structs...&n; */
DECL|struct|fhc_ign_reg
r_struct
id|fhc_ign_reg
(brace
DECL|member|fhc_ign
multiline_comment|/*0x2000*/
id|u64
id|fhc_ign
suffix:semicolon
multiline_comment|/* FHC Interrupt Group Number&t;*/
)brace
suffix:semicolon
DECL|struct|fhc_fanfail_regs
r_struct
id|fhc_fanfail_regs
(brace
DECL|member|_pad0
DECL|member|fhc_ff_imap
multiline_comment|/*0x4000*/
id|u32
id|_pad0
comma
id|fhc_ff_imap
suffix:semicolon
multiline_comment|/* FHC FanFail Interrupt Map&t;*/
DECL|member|_pad1
id|u64
id|_pad1
suffix:semicolon
DECL|member|_pad2
DECL|member|fhc_ff_iclr
multiline_comment|/*0x4010*/
id|u32
id|_pad2
comma
id|fhc_ff_iclr
suffix:semicolon
multiline_comment|/* FHC FanFail Interrupt Clear&t;*/
)brace
suffix:semicolon
DECL|struct|fhc_system_regs
r_struct
id|fhc_system_regs
(brace
DECL|member|_pad0
DECL|member|fhc_sys_imap
multiline_comment|/*0x6000*/
id|u32
id|_pad0
comma
id|fhc_sys_imap
suffix:semicolon
multiline_comment|/* FHC System Interrupt Map&t;*/
DECL|member|_pad1
id|u64
id|_pad1
suffix:semicolon
DECL|member|_pad2
DECL|member|fhc_sys_iclr
multiline_comment|/*0x6010*/
id|u32
id|_pad2
comma
id|fhc_sys_iclr
suffix:semicolon
multiline_comment|/* FHC System Interrupt Clear&t;*/
)brace
suffix:semicolon
DECL|struct|fhc_uart_regs
r_struct
id|fhc_uart_regs
(brace
DECL|member|_pad0
DECL|member|fhc_uart_imap
multiline_comment|/*0x8000*/
id|u32
id|_pad0
comma
id|fhc_uart_imap
suffix:semicolon
multiline_comment|/* FHC UART Interrupt Map&t;*/
DECL|member|_pad1
id|u64
id|_pad1
suffix:semicolon
DECL|member|_pad2
DECL|member|fhc_uart_iclr
multiline_comment|/*0x8010*/
id|u32
id|_pad2
comma
id|fhc_uart_iclr
suffix:semicolon
multiline_comment|/* FHC UART Interrupt Clear&t;*/
)brace
suffix:semicolon
DECL|struct|fhc_tod_regs
r_struct
id|fhc_tod_regs
(brace
DECL|member|_pad0
DECL|member|fhc_tod_imap
multiline_comment|/*0xa000*/
id|u32
id|_pad0
comma
id|fhc_tod_imap
suffix:semicolon
multiline_comment|/* FHC TOD Interrupt Map&t;*/
DECL|member|_pad1
id|u64
id|_pad1
suffix:semicolon
DECL|member|_pad2
DECL|member|fhc_tod_iclr
multiline_comment|/*0xa010*/
id|u32
id|_pad2
comma
id|fhc_tod_iclr
suffix:semicolon
multiline_comment|/* FHC TOD Interrupt Clear&t;*/
)brace
suffix:semicolon
multiline_comment|/* All of the above. */
DECL|struct|fhc_regs
r_struct
id|fhc_regs
(brace
DECL|member|pregs
r_struct
id|fhc_internal_regs
op_star
id|pregs
suffix:semicolon
DECL|member|ireg
r_struct
id|fhc_ign_reg
op_star
id|ireg
suffix:semicolon
DECL|member|ffregs
r_struct
id|fhc_fanfail_regs
op_star
id|ffregs
suffix:semicolon
DECL|member|sregs
r_struct
id|fhc_system_regs
op_star
id|sregs
suffix:semicolon
DECL|member|uregs
r_struct
id|fhc_uart_regs
op_star
id|uregs
suffix:semicolon
DECL|member|tregs
r_struct
id|fhc_tod_regs
op_star
id|tregs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FHC ID Register */
DECL|macro|FHC_ID_VERS
mdefine_line|#define FHC_ID_VERS&t;&t;0xf0000000 /* Version of this FHC&t;&t;*/
DECL|macro|FHC_ID_PARTID
mdefine_line|#define FHC_ID_PARTID&t;&t;0x0ffff000 /* Part ID code (0x0f9f == FHC)&t;*/
DECL|macro|FHC_ID_MANUF
mdefine_line|#define FHC_ID_MANUF&t;&t;0x0000007e /* Manufacturer (0x3e == SUN&squot;s JEDEC)*/
DECL|macro|FHC_ID_RESV
mdefine_line|#define FHC_ID_RESV&t;&t;0x00000001 /* Read as one&t;&t;&t;*/
multiline_comment|/* FHC Control Register */
DECL|macro|FHC_CONTROL_ICS
mdefine_line|#define FHC_CONTROL_ICS&t;&t;0x00100000 /* Ignore Centerplane Signals&t;*/
DECL|macro|FHC_CONTROL_FRST
mdefine_line|#define FHC_CONTROL_FRST&t;0x00080000 /* Fatal Error Reset Enable&t;&t;*/
DECL|macro|FHC_CONTROL_LFAT
mdefine_line|#define FHC_CONTROL_LFAT&t;0x00040000 /* AC/DC signalled a local error&t;*/
DECL|macro|FHC_CONTROL_SLINE
mdefine_line|#define FHC_CONTROL_SLINE&t;0x00010000 /* Firmware Synchronization Line&t;*/
DECL|macro|FHC_CONTROL_DCD
mdefine_line|#define FHC_CONTROL_DCD&t;&t;0x00008000 /* DC--&gt;DC Converter Disable&t;&t;*/
DECL|macro|FHC_CONTROL_POFF
mdefine_line|#define FHC_CONTROL_POFF&t;0x00004000 /* AC/DC Controller PLL Disable&t;*/
DECL|macro|FHC_CONTROL_FOFF
mdefine_line|#define FHC_CONTROL_FOFF&t;0x00002000 /* FHC Controller PLL Disable&t;*/
DECL|macro|FHC_CONTROL_AOFF
mdefine_line|#define FHC_CONTROL_AOFF&t;0x00001000 /* CPU A SRAM/SBD Low Power Mode&t;*/
DECL|macro|FHC_CONTROL_BOFF
mdefine_line|#define FHC_CONTROL_BOFF&t;0x00000800 /* CPU B SRAM/SBD Low Power Mode&t;*/
DECL|macro|FHC_CONTROL_PSOFF
mdefine_line|#define FHC_CONTROL_PSOFF&t;0x00000400 /* Turns off this FHC&squot;s power supply&t;*/
DECL|macro|FHC_CONTROL_IXIST
mdefine_line|#define FHC_CONTROL_IXIST&t;0x00000200 /* 0=FHC tells clock board it exists&t;*/
DECL|macro|FHC_CONTROL_XMSTR
mdefine_line|#define FHC_CONTROL_XMSTR&t;0x00000100 /* 1=Causes this FHC to be XIR master*/
DECL|macro|FHC_CONTROL_LLED
mdefine_line|#define FHC_CONTROL_LLED&t;0x00000040 /* 0=Left LED ON&t;&t;&t;*/
DECL|macro|FHC_CONTROL_MLED
mdefine_line|#define FHC_CONTROL_MLED&t;0x00000020 /* 1=Middle LED ON&t;&t;&t;*/
DECL|macro|FHC_CONTROL_RLED
mdefine_line|#define FHC_CONTROL_RLED&t;0x00000010 /* 1=Right LED&t;&t;&t;*/
DECL|macro|FHC_CONTROL_BPINS
mdefine_line|#define FHC_CONTROL_BPINS&t;0x00000003 /* Spare Bidirectional Pins&t;&t;*/
multiline_comment|/* FHC Reset Control/Status Register */
DECL|macro|FHC_RCS_POR
mdefine_line|#define FHC_RCS_POR&t;&t;0x80000000 /* Last reset was a power cycle&t;*/
DECL|macro|FHC_RCS_SPOR
mdefine_line|#define FHC_RCS_SPOR&t;&t;0x40000000 /* Last reset was sw power on reset&t;*/
DECL|macro|FHC_RCS_SXIR
mdefine_line|#define FHC_RCS_SXIR&t;&t;0x20000000 /* Last reset was sw XIR reset&t;*/
DECL|macro|FHC_RCS_BPOR
mdefine_line|#define FHC_RCS_BPOR&t;&t;0x10000000 /* Last reset was due to POR button&t;*/
DECL|macro|FHC_RCS_BXIR
mdefine_line|#define FHC_RCS_BXIR&t;&t;0x08000000 /* Last reset was due to XIR button&t;*/
DECL|macro|FHC_RCS_WEVENT
mdefine_line|#define FHC_RCS_WEVENT&t;&t;0x04000000 /* CPU reset was due to wakeup event&t;*/
DECL|macro|FHC_RCS_CFATAL
mdefine_line|#define FHC_RCS_CFATAL&t;&t;0x02000000 /* Centerplane Fatal Error signalled&t;*/
DECL|macro|FHC_RCS_FENAB
mdefine_line|#define FHC_RCS_FENAB&t;&t;0x01000000 /* Fatal errors elicit system reset&t;*/
multiline_comment|/* FHC Board Status Register */
DECL|macro|FHC_BSD_DA64
mdefine_line|#define FHC_BSD_DA64&t;&t;0x00040000 /* Port A: 0=128bit 1=64bit data path */
DECL|macro|FHC_BSD_DB64
mdefine_line|#define FHC_BSD_DB64&t;&t;0x00020000 /* Port B: 0=128bit 1=64bit data path */
DECL|macro|FHC_BSD_BID
mdefine_line|#define FHC_BSD_BID&t;&t;0x0001e000 /* Board ID                           */
DECL|macro|FHC_BSD_SA
mdefine_line|#define FHC_BSD_SA&t;&t;0x00001c00 /* Port A UPA Speed (from the pins)   */
DECL|macro|FHC_BSD_SB
mdefine_line|#define FHC_BSD_SB&t;&t;0x00000380 /* Port B UPA Speed (from the pins)   */
DECL|macro|FHC_BSD_NDIAG
mdefine_line|#define FHC_BSD_NDIAG&t;&t;0x00000040 /* Not in Diag Mode                   */
DECL|macro|FHC_BSD_NTBED
mdefine_line|#define FHC_BSD_NTBED&t;&t;0x00000020 /* Not in TestBED Mode                */
DECL|macro|FHC_BSD_NIA
mdefine_line|#define FHC_BSD_NIA&t;&t;0x0000001c /* Jumper, bit 18 in PROM space       */
DECL|macro|FHC_BSD_SI
mdefine_line|#define FHC_BSD_SI&t;&t;0x00000001 /* Spare input pin value              */
multiline_comment|/* FHC then has an Interrupt Group Number register, essentially this is a 32-bit&n; * register with the low 5 bits specifying the IGN of this FHC for interrupt&n; * generation purposes, it is a product of the BoardID/Pins seen by the FHC&n; * at power on time.  I suspect the firmware really sets this value though&n; * during POST.  On board FHC devices generate fixed INO interrupt packet&n; * values, of course these are concatenated with the IGN before it reaches the&n; * CPU:&n; *&n; *&t;IRQ Source&t;&t;INO Value&n; *&t;----------------------------------------&n; *&t;&quot;System&quot; Interrupt&t;0x38&n; *&t;Zilogs&t;&t;&t;0x39&n; *&t;Mostek&t;&t;&t;0x3a&n; *&t;Fan Failure&t;&t;0x3b&n; *&t;Spare 1&t;&t;&t;0x3c&n; *&t;Spare 2&t;&t;&t;0x3d&n; *&n; * Consult the sysio.h header for the layout of the Interrupt Mapping and&n; * Interrupt Clear register bits as they are the same. -DaveM&n; */
macro_line|#endif /* !(_SPARC64_FIREHOSE_H) */
eof
