macro_line|#ifndef _LINUX_FDREG_H
DECL|macro|_LINUX_FDREG_H
mdefine_line|#define _LINUX_FDREG_H
multiline_comment|/*&n; * This file contains some defines for the floppy disk controller.&n; * Various sources. Mostly &quot;IBM Microcomputers: A Programmers&n; * Handbook&quot;, Sanches and Canton.&n; */
macro_line|#ifdef FDPATCHES
DECL|macro|FD_IOPORT
mdefine_line|#define FD_IOPORT fdc_state[fdc].address
multiline_comment|/* Fd controller regs. S&amp;C, about page 340 */
DECL|macro|FD_STATUS
mdefine_line|#define FD_STATUS&t;(4 + FD_IOPORT )
DECL|macro|FD_DATA
mdefine_line|#define FD_DATA&t;&t;(5 + FD_IOPORT )
multiline_comment|/* Digital Output Register */
DECL|macro|FD_DOR
mdefine_line|#define FD_DOR&t;&t;(2 + FD_IOPORT )
multiline_comment|/* Digital Input Register (read) */
DECL|macro|FD_DIR
mdefine_line|#define FD_DIR&t;&t;(7 + FD_IOPORT )
multiline_comment|/* Diskette Control Register (write)*/
DECL|macro|FD_DCR
mdefine_line|#define FD_DCR&t;&t;(7 + FD_IOPORT )
macro_line|#else
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
macro_line|#endif
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
mdefine_line|#define ST2_MAM&t;&t;0x01&t;&t;/* Missing Address Mark (again) */
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
DECL|macro|ST3_DS
mdefine_line|#define ST3_DS&t;&t;0x08&t;&t;/* drive is double-sided */
DECL|macro|ST3_TZ
mdefine_line|#define ST3_TZ&t;&t;0x10&t;&t;/* Track Zero signal (1=track 0) */
DECL|macro|ST3_RY
mdefine_line|#define ST3_RY&t;&t;0x20&t;&t;/* drive is ready */
DECL|macro|ST3_WP
mdefine_line|#define ST3_WP&t;&t;0x40&t;&t;/* Write Protect */
DECL|macro|ST3_FT
mdefine_line|#define ST3_FT&t;&t;0x80&t;&t;/* Drive Fault */
multiline_comment|/* Values for FD_COMMAND */
DECL|macro|FD_RECALIBRATE
mdefine_line|#define FD_RECALIBRATE&t;&t;0x07&t;/* move to track 0 */
DECL|macro|FD_SEEK
mdefine_line|#define FD_SEEK&t;&t;&t;0x0F&t;/* seek track */
DECL|macro|FD_READ
mdefine_line|#define FD_READ&t;&t;&t;0xE6&t;/* read with MT, MFM, SKip deleted */
DECL|macro|FD_WRITE
mdefine_line|#define FD_WRITE&t;&t;0xC5&t;/* write with MT, MFM */
DECL|macro|FD_SENSEI
mdefine_line|#define FD_SENSEI&t;&t;0x08&t;/* Sense Interrupt Status */
DECL|macro|FD_SPECIFY
mdefine_line|#define FD_SPECIFY&t;&t;0x03&t;/* specify HUT etc */
DECL|macro|FD_FORMAT
mdefine_line|#define FD_FORMAT&t;&t;0x4D&t;/* format one track */
DECL|macro|FD_VERSION
mdefine_line|#define FD_VERSION&t;&t;0x10&t;/* get version code */
DECL|macro|FD_CONFIGURE
mdefine_line|#define FD_CONFIGURE&t;&t;0x13&t;/* configure FIFO operation */
DECL|macro|FD_PERPENDICULAR
mdefine_line|#define FD_PERPENDICULAR&t;0x12&t;/* perpendicular r/w mode */
DECL|macro|FD_GETSTATUS
mdefine_line|#define FD_GETSTATUS&t;&t;0x04&t;/* read ST3 */
DECL|macro|FD_DUMPREGS
mdefine_line|#define FD_DUMPREGS&t;&t;0x0E&t;/* dump the contents of the fdc regs */
DECL|macro|FD_READID
mdefine_line|#define FD_READID&t;&t;0xEA&t;/* prints the header of a sector */
DECL|macro|FD_UNLOCK
mdefine_line|#define FD_UNLOCK&t;&t;0x14&t;/* Fifo config unlock */
DECL|macro|FD_LOCK
mdefine_line|#define FD_LOCK&t;&t;&t;0x94&t;/* Fifo config lock */
DECL|macro|FD_RSEEK_OUT
mdefine_line|#define FD_RSEEK_OUT&t;&t;0x8f&t;/* seek out (i.e. to lower tracks) */
DECL|macro|FD_RSEEK_IN
mdefine_line|#define FD_RSEEK_IN&t;&t;0xcf&t;/* seek in (i.e. to higher tracks) */
multiline_comment|/* DMA commands */
DECL|macro|DMA_READ
mdefine_line|#define DMA_READ&t;0x46
DECL|macro|DMA_WRITE
mdefine_line|#define DMA_WRITE&t;0x4A
multiline_comment|/* FDC version return types */
DECL|macro|FDC_NONE
mdefine_line|#define FDC_NONE&t;0x00
DECL|macro|FDC_UNKNOWN
mdefine_line|#define FDC_UNKNOWN&t;0x10
DECL|macro|FDC_8272A
mdefine_line|#define FDC_8272A&t;0x20&t;/* Intel 8272a, NEC 765 */
DECL|macro|FDC_765ED
mdefine_line|#define FDC_765ED&t;0x30&t;/* Non-Intel 1MB-compatible FDC, can&squot;t detect */
DECL|macro|FDC_82072
mdefine_line|#define FDC_82072&t;0x40&t;/* Intel 82072; 8272a + FIFO + DUMPREGS */
DECL|macro|FDC_82077_ORIG
mdefine_line|#define FDC_82077_ORIG&t;0x50&t;/* Original version of 82077AA, sans LOCK */
DECL|macro|FDC_82077
mdefine_line|#define FDC_82077&t;0x52&t;/* 82077AA-1 */
DECL|macro|FD_RESET_DELAY
mdefine_line|#define FD_RESET_DELAY 20
macro_line|#endif
eof
