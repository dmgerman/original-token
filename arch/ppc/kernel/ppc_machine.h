multiline_comment|/*&n; * PowerPC machine specifics&n; */
macro_line|#ifndef _PPC_MACHINE_H_
DECL|macro|_PPC_MACHINE_H_
mdefine_line|#define _PPC_MACHINE_H_ 
multiline_comment|/* Bit encodings for Machine State Register (MSR) */
DECL|macro|MSR_POW
mdefine_line|#define MSR_POW&t;&t;(1&lt;&lt;18)&t;&t;/* Enable Power Management */
DECL|macro|MSR_TGPR
mdefine_line|#define MSR_TGPR&t;(1&lt;&lt;17)&t;&t;/* TLB Update registers in use */
DECL|macro|MSR_ILE
mdefine_line|#define MSR_ILE&t;&t;(1&lt;&lt;16)&t;&t;/* Interrupt Little-Endian enable */
DECL|macro|MSR_EE
mdefine_line|#define MSR_EE&t;&t;(1&lt;&lt;15)&t;&t;/* External Interrupt enable */
DECL|macro|MSR_PR
mdefine_line|#define MSR_PR&t;&t;(1&lt;&lt;14)&t;&t;/* Supervisor/User privelege */
DECL|macro|MSR_FP
mdefine_line|#define MSR_FP&t;&t;(1&lt;&lt;13)&t;&t;/* Floating Point enable */
DECL|macro|MSR_ME
mdefine_line|#define MSR_ME&t;&t;(1&lt;&lt;12)&t;&t;/* Machine Check enable */
DECL|macro|MSR_FE0
mdefine_line|#define MSR_FE0&t;&t;(1&lt;&lt;11)&t;&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE
mdefine_line|#define MSR_SE&t;&t;(1&lt;&lt;10)&t;&t;/* Single Step */
DECL|macro|MSR_BE
mdefine_line|#define MSR_BE&t;&t;(1&lt;&lt;9)&t;&t;/* Branch Trace */
DECL|macro|MSR_FE1
mdefine_line|#define MSR_FE1&t;&t;(1&lt;&lt;8)&t;&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP
mdefine_line|#define MSR_IP&t;&t;(1&lt;&lt;6)&t;&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR
mdefine_line|#define MSR_IR&t;&t;(1&lt;&lt;5)&t;&t;/* Instruction MMU enable */
DECL|macro|MSR_DR
mdefine_line|#define MSR_DR&t;&t;(1&lt;&lt;4)&t;&t;/* Data MMU enable */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;(1&lt;&lt;1)&t;&t;/* Recoverable Exception */
DECL|macro|MSR_LE
mdefine_line|#define MSR_LE&t;&t;(1&lt;&lt;0)&t;&t;/* Little-Endian enable */
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;MSR_FP|MSR_FE0|MSR_FE1|MSR_ME
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;MSR_|MSR_PR|MSR_EE|MSR_IR|MSR_DR
multiline_comment|/* Bit encodings for Hardware Implementation Register (HID0) */
DECL|macro|HID0_EMCP
mdefine_line|#define HID0_EMCP&t;(1&lt;&lt;31)&t;&t;/* Enable Machine Check pin */
DECL|macro|HID0_EBA
mdefine_line|#define HID0_EBA&t;(1&lt;&lt;29)&t;&t;/* Enable Bus Address Parity */
DECL|macro|HID0_EBD
mdefine_line|#define HID0_EBD&t;(1&lt;&lt;28)&t;&t;/* Enable Bus Data Parity */
DECL|macro|HID0_SBCLK
mdefine_line|#define HID0_SBCLK&t;(1&lt;&lt;27)
DECL|macro|HID0_EICE
mdefine_line|#define HID0_EICE&t;(1&lt;&lt;26)
DECL|macro|HID0_ECLK
mdefine_line|#define HID0_ECLK&t;(1&lt;&lt;25)
DECL|macro|HID0_PAR
mdefine_line|#define HID0_PAR&t;(1&lt;&lt;24)
DECL|macro|HID0_DOZE
mdefine_line|#define HID0_DOZE&t;(1&lt;&lt;23)
DECL|macro|HID0_NAP
mdefine_line|#define HID0_NAP&t;(1&lt;&lt;22)
DECL|macro|HID0_SLEEP
mdefine_line|#define HID0_SLEEP&t;(1&lt;&lt;21)
DECL|macro|HID0_DPM
mdefine_line|#define HID0_DPM&t;(1&lt;&lt;20)
DECL|macro|HID0_ICE
mdefine_line|#define HID0_ICE&t;(1&lt;&lt;15)&t;&t;/* Instruction Cache Enable */
DECL|macro|HID0_DCE
mdefine_line|#define HID0_DCE&t;(1&lt;&lt;14)&t;&t;/* Data Cache Enable */
DECL|macro|HID0_ILOCK
mdefine_line|#define HID0_ILOCK&t;(1&lt;&lt;13)&t;&t;/* Instruction Cache Lock */
DECL|macro|HID0_DLOCK
mdefine_line|#define HID0_DLOCK&t;(1&lt;&lt;12)&t;&t;/* Data Cache Lock */
DECL|macro|HID0_ICFI
mdefine_line|#define HID0_ICFI&t;(1&lt;&lt;11)&t;&t;/* Instruction Cache Flash Invalidate */
DECL|macro|HID0_DCI
mdefine_line|#define HID0_DCI&t;(1&lt;&lt;10)&t;&t;/* Data Cache Invalidate */
DECL|macro|HID0_SIED
mdefine_line|#define HID0_SIED&t;(1&lt;&lt;7)&t;&t;/* Serial Instruction Execution [Disable] */
DECL|macro|HID0_BHTE
mdefine_line|#define HID0_BHTE&t;(1&lt;&lt;2)&t;&t;/* Branch History Table Enable */
macro_line|#endif
eof
