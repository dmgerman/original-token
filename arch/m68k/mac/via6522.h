multiline_comment|/*&n; *&t;6522 Versatile Interface Adapter (VIA)&n; *&n; *&t;There are two of these on the Mac II. Some IRQ&squot;s are vectored&n; *&t;via them as are assorted bits and bobs - eg rtc, adb. The picture&n; *&t;is a bit incomplete as the Mac documentation doesnt cover this well&n; */
macro_line|#ifndef _ASM_VIA6522_H_
DECL|macro|_ASM_VIA6522_H_
mdefine_line|#define _ASM_VIA6522_H_
DECL|macro|VIABASE
mdefine_line|#define VIABASE&t;&t;0x50F00000
DECL|macro|VIABASE2
mdefine_line|#define VIABASE2&t;0x50F02000
multiline_comment|/*&n; *&t;Not all of these are true post MacII I think&n; */
DECL|macro|VIA1A_vSccWrReq
mdefine_line|#define VIA1A_vSccWrReq&t;0x80&t;/* SCC write */
DECL|macro|VIA1A_vRev8
mdefine_line|#define VIA1A_vRev8&t;0x40&t;/* Revision 8 board ??? */
DECL|macro|VIA1A_vHeadSel
mdefine_line|#define VIA1A_vHeadSel&t;0x20&t;/* Head select for IWM */
DECL|macro|VIA1A_vOverlay
mdefine_line|#define VIA1A_vOverlay&t;0x10
DECL|macro|VIA1A_vSync
mdefine_line|#define VIA1A_vSync&t;0x08
DECL|macro|VIA1A_vVolume
mdefine_line|#define VIA1A_vVolume&t;0x07&t;/* Audio volume mask */
DECL|macro|VIA1B_vSound
mdefine_line|#define VIA1B_vSound&t;0x80&t;/* Audio on/off */
DECL|macro|VIA1B_vMystery
mdefine_line|#define VIA1B_vMystery&t;0x40
DECL|macro|VIA1B_vADBS2
mdefine_line|#define VIA1B_vADBS2&t;0x20&t;/* ADB state 2 */
DECL|macro|VIA1B_vADBS1
mdefine_line|#define VIA1B_vADBS1&t;0x10&t;/* ADB state 1 */
DECL|macro|VIA1B_vADBInt
mdefine_line|#define VIA1B_vADBInt&t;0x08&t;/* ADB interrupt */
DECL|macro|VIA1B_vRTCEnb
mdefine_line|#define VIA1B_vRTCEnb&t;0x04&t;/* Real time clock */
DECL|macro|VIA1B_vRTCClk
mdefine_line|#define VIA1B_vRTCClk&t;0x02
DECL|macro|VIA1B_vRTCData
mdefine_line|#define VIA1B_vRTCData&t;0x01
multiline_comment|/*&n; *&t;VIA2 A register is the interrupt lines raised off the nubus &n; *&t;slots.&n; */
DECL|macro|VIA2A_vIRQE
mdefine_line|#define VIA2A_vIRQE&t;0x20
DECL|macro|VIA2A_vIRQD
mdefine_line|#define VIA2A_vIRQD&t;0x10
DECL|macro|VIA2A_vIRQC
mdefine_line|#define VIA2A_vIRQC&t;0x08
DECL|macro|VIA2A_vIRQB
mdefine_line|#define VIA2A_vIRQB&t;0x04
DECL|macro|VIA2A_vIRQA
mdefine_line|#define VIA2A_vIRQA&t;0x02
DECL|macro|VIA2A_vIRQ9
mdefine_line|#define VIA2A_vIRQ9&t;0x01
multiline_comment|/*&n; *&t;Register B has the fun stuff in it&n; */
DECL|macro|VIA2B_vMode32
mdefine_line|#define VIA2B_vMode32&t;0x08&t;/* 24/32bit switch - doubles as cache flush */
DECL|macro|VIA2B_vPower
mdefine_line|#define VIA2B_vPower&t;0x04&t;/* Off switch */
DECL|macro|VIA2B_vBusLk
mdefine_line|#define VIA2B_vBusLk&t;0x02&t;/* Nubus in use ?? */
DECL|macro|VIA2B_vCDis
mdefine_line|#define VIA2B_vCDis&t;0x01&t;/* Cache disable */
multiline_comment|/*&n; *&t;The 6522 via is a 2MHz part, and needs a delay. MacOS seems to&n; *&t;execute MOV (Ax),(Ax) for this... Oh and we can&squot;t use udelay&n; *&t;here... see we need the via to calibrate the udelay loop ...&n; */
r_extern
r_volatile
r_int
op_star
id|via_memory_bogon
suffix:semicolon
DECL|function|via_write
r_extern
id|__inline__
r_void
id|via_write
c_func
(paren
r_volatile
r_int
r_char
op_star
id|via
comma
r_int
id|reg
comma
r_int
id|v
)paren
(brace
op_star
id|via_memory_bogon
suffix:semicolon
op_star
id|via_memory_bogon
suffix:semicolon
op_star
id|via_memory_bogon
suffix:semicolon
id|via
(braket
id|reg
)braket
op_assign
id|v
suffix:semicolon
)brace
DECL|function|via_read
r_extern
id|__inline__
r_int
id|via_read
c_func
(paren
r_volatile
r_int
r_char
op_star
id|via
comma
r_int
id|reg
)paren
(brace
op_star
id|via_memory_bogon
suffix:semicolon
op_star
id|via_memory_bogon
suffix:semicolon
op_star
id|via_memory_bogon
suffix:semicolon
r_return
(paren
r_int
)paren
id|via
(braket
id|reg
)braket
suffix:semicolon
)brace
r_extern
r_volatile
r_int
r_char
op_star
id|via1
comma
op_star
id|via2
suffix:semicolon
multiline_comment|/*&n; *&t;6522 registers - see databook&n; */
DECL|macro|vBufB
mdefine_line|#define vBufB&t;0x0000
DECL|macro|vBufA
mdefine_line|#define vBufA&t;0x0200
DECL|macro|vDirB
mdefine_line|#define vDirB&t;0x0400
DECL|macro|vDirA
mdefine_line|#define vDirA&t;0x0600
DECL|macro|vT1CL
mdefine_line|#define vT1CL&t;0x0800
DECL|macro|vT1CH
mdefine_line|#define vT1CH&t;0x0a00
DECL|macro|vT1LL
mdefine_line|#define vT1LL&t;0x0c00
DECL|macro|vT1LH
mdefine_line|#define vT1LH&t;0x0e00
DECL|macro|vT2CL
mdefine_line|#define vT2CL&t;0x1000
DECL|macro|vT2CH
mdefine_line|#define vT2CH&t;0x1200
DECL|macro|vSR
mdefine_line|#define vSR&t;0x1400
DECL|macro|vACR
mdefine_line|#define vACR&t;0x1600
DECL|macro|vPCR
mdefine_line|#define vPCR&t;0x1800
DECL|macro|vIFR
mdefine_line|#define vIFR&t;0x1a00
DECL|macro|vIER
mdefine_line|#define vIER&t;0x1c00 
DECL|macro|vANH
mdefine_line|#define vANH&t;0x1e00  /* register A (no shake) */
DECL|macro|rBufB
mdefine_line|#define rBufB&t;0x00
DECL|macro|rBufA
mdefine_line|#define rBufA&t;0x02
multiline_comment|/*#define rIFR&t;0x03*/
DECL|macro|rIFR
mdefine_line|#define rIFR&t;0x1A03
DECL|macro|rVideo
mdefine_line|#define rVideo&t;0x10
DECL|macro|rSlot
mdefine_line|#define rSlot&t;0x12
multiline_comment|/*#define rIER&t;0x13*/
DECL|macro|rIER
mdefine_line|#define rIER&t;0x1C13
multiline_comment|/*&n;#define R_rIFR&t;0x03&n;#define R_rIER&t;0x13&n;#define W_rIFR&t;0x1A03&n;#define W_rIER&t;0x1C13&n;*/
multiline_comment|/*&n; *&t;VIA interrupt&n; */
DECL|struct|via_irq_tab
r_struct
id|via_irq_tab
(brace
DECL|member|vector
r_void
(paren
op_star
id|vector
(braket
l_int|8
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|via1_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|via2_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|via_setup_keyboard
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_VIA6522_H_ */
eof
