multiline_comment|/*&n; * This file contains some defines for the floppy disk controller.&n; * Various sources. Mostly &quot;IBM Microcomputers: A Programmers&n; * Handbook&quot;, Sanches and Canton.&n; */
macro_line|#ifndef _FDREG_H
DECL|macro|_FDREG_H
mdefine_line|#define _FDREG_H
r_extern
r_int
id|ticks_to_floppy_on
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|floppy_on
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|floppy_select
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|floppy_deselect
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
multiline_comment|/* Fd controller regs. S&amp;C, about page 340 */
DECL|macro|FD_STATUS
mdefine_line|#define FD_STATUS&t;0x3f4
DECL|macro|FD_DATA
mdefine_line|#define FD_DATA&t;&t;0x3f5
DECL|macro|FD_DOR
mdefine_line|#define FD_DOR&t;&t;0x3f2&t;&t;/* Digital Output Register */
DECL|macro|FD_DIR
mdefine_line|#define FD_DIR&t;&t;0x3f7&t;&t;/* Digital Input Register (read) */
DECL|macro|FD_DCR
mdefine_line|#define FD_DCR&t;&t;0x3f7&t;&t;/* Diskette Control Register (write)*/
multiline_comment|/* Bits of main status register */
DECL|macro|STATUS_BUSYMASK
mdefine_line|#define STATUS_BUSYMASK&t;0x0F&t;&t;/* drive busy mask */
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY&t;0x10&t;&t;/* FDC busy */
DECL|macro|STATUS_DMA
mdefine_line|#define STATUS_DMA&t;0x20&t;&t;/* 0- DMA mode */
DECL|macro|STATUS_DIR
mdefine_line|#define STATUS_DIR&t;0x40&t;&t;/* 0- cpu-&gt;fdc */
DECL|macro|STATUS_READY
mdefine_line|#define STATUS_READY&t;0x80&t;&t;/* Data reg ready */
multiline_comment|/* Bits of FD_ST0 */
DECL|macro|ST0_DS
mdefine_line|#define ST0_DS&t;&t;0x03&t;&t;/* drive select mask */
DECL|macro|ST0_HA
mdefine_line|#define ST0_HA&t;&t;0x04&t;&t;/* Head (Address) */
DECL|macro|ST0_NR
mdefine_line|#define ST0_NR&t;&t;0x08&t;&t;/* Not Ready */
DECL|macro|ST0_ECE
mdefine_line|#define ST0_ECE&t;&t;0x10&t;&t;/* Equipment chech error */
DECL|macro|ST0_SE
mdefine_line|#define ST0_SE&t;&t;0x20&t;&t;/* Seek end */
DECL|macro|ST0_INTR
mdefine_line|#define ST0_INTR&t;0xC0&t;&t;/* Interrupt code mask */
multiline_comment|/* Bits of FD_ST1 */
DECL|macro|ST1_MAM
mdefine_line|#define ST1_MAM&t;&t;0x01&t;&t;/* Missing Address Mark */
DECL|macro|ST1_WP
mdefine_line|#define ST1_WP&t;&t;0x02&t;&t;/* Write Protect */
DECL|macro|ST1_ND
mdefine_line|#define ST1_ND&t;&t;0x04&t;&t;/* No Data - unreadable */
DECL|macro|ST1_OR
mdefine_line|#define ST1_OR&t;&t;0x10&t;&t;/* OverRun */
DECL|macro|ST1_CRC
mdefine_line|#define ST1_CRC&t;&t;0x20&t;&t;/* CRC error in data or addr */
DECL|macro|ST1_EOC
mdefine_line|#define ST1_EOC&t;&t;0x80&t;&t;/* End Of Cylinder */
multiline_comment|/* Bits of FD_ST2 */
DECL|macro|ST2_MAM
mdefine_line|#define ST2_MAM&t;&t;0x01&t;&t;/* Missing Addess Mark (again) */
DECL|macro|ST2_BC
mdefine_line|#define ST2_BC&t;&t;0x02&t;&t;/* Bad Cylinder */
DECL|macro|ST2_SNS
mdefine_line|#define ST2_SNS&t;&t;0x04&t;&t;/* Scan Not Satisfied */
DECL|macro|ST2_SEH
mdefine_line|#define ST2_SEH&t;&t;0x08&t;&t;/* Scan Equal Hit */
DECL|macro|ST2_WC
mdefine_line|#define ST2_WC&t;&t;0x10&t;&t;/* Wrong Cylinder */
DECL|macro|ST2_CRC
mdefine_line|#define ST2_CRC&t;&t;0x20&t;&t;/* CRC error in data field */
DECL|macro|ST2_CM
mdefine_line|#define ST2_CM&t;&t;0x40&t;&t;/* Control Mark = deleted */
multiline_comment|/* Bits of FD_ST3 */
DECL|macro|ST3_HA
mdefine_line|#define ST3_HA&t;&t;0x04&t;&t;/* Head (Address) */
DECL|macro|ST3_TZ
mdefine_line|#define ST3_TZ&t;&t;0x10&t;&t;/* Track Zero signal (1=track 0) */
DECL|macro|ST3_WP
mdefine_line|#define ST3_WP&t;&t;0x40&t;&t;/* Write Protect */
multiline_comment|/* Values for FD_COMMAND */
DECL|macro|FD_RECALIBRATE
mdefine_line|#define FD_RECALIBRATE&t;0x07&t;&t;/* move to track 0 */
DECL|macro|FD_SEEK
mdefine_line|#define FD_SEEK&t;&t;0x0F&t;&t;/* seek track */
DECL|macro|FD_READ
mdefine_line|#define FD_READ&t;&t;0xE6&t;&t;/* read with MT, MFM, SKip deleted */
DECL|macro|FD_WRITE
mdefine_line|#define FD_WRITE&t;0xC5&t;&t;/* write with MT, MFM */
DECL|macro|FD_SENSEI
mdefine_line|#define FD_SENSEI&t;0x08&t;&t;/* Sense Interrupt Status */
DECL|macro|FD_SPECIFY
mdefine_line|#define FD_SPECIFY&t;0x03&t;&t;/* specify HUT etc */
multiline_comment|/* DMA commands */
DECL|macro|DMA_READ
mdefine_line|#define DMA_READ&t;0x46
DECL|macro|DMA_WRITE
mdefine_line|#define DMA_WRITE&t;0x4A
macro_line|#endif
eof
