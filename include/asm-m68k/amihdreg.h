macro_line|#ifndef _LINUX_AMIHDREG_H
DECL|macro|_LINUX_AMIHDREG_H
mdefine_line|#define _LINUX_AMIHDREG_H
multiline_comment|/*&n; * This file contains some defines for the Amiga IDE hd controller.&n; * Various sources. Check out some definitions (see comments with&n; * a ques).&n; */
DECL|macro|IDE_DISABLE_IRQ
mdefine_line|#define IDE_DISABLE_IRQ  0x02
DECL|macro|IDE_ENABLE_IRQ
mdefine_line|#define IDE_ENABLE_IRQ   0x00
multiline_comment|/* Bases of the hard drive controller */
DECL|macro|HD_BASE_A4000
mdefine_line|#define HD_BASE_A4000   0xdd2020
DECL|macro|HD_BASE_A1200
mdefine_line|#define HD_BASE_A1200   0xda0000
multiline_comment|/* Offsets from one of the above bases */
DECL|macro|AMI_HD_ERROR
mdefine_line|#define AMI_HD_ERROR&t;(0x06)&t;&t;/* see err-bits */
DECL|macro|AMI_HD_NSECTOR
mdefine_line|#define AMI_HD_NSECTOR&t;(0x0a)&t;&t;/* nr of sectors to read/write */
DECL|macro|AMI_HD_SECTOR
mdefine_line|#define AMI_HD_SECTOR&t;(0x0e)&t;&t;/* starting sector */
DECL|macro|AMI_HD_LCYL
mdefine_line|#define AMI_HD_LCYL&t;(0x12)&t;&t;/* starting cylinder */
DECL|macro|AMI_HD_HCYL
mdefine_line|#define AMI_HD_HCYL&t;(0x16)&t;&t;/* high byte of starting cyl */
DECL|macro|AMI_HD_SELECT
mdefine_line|#define AMI_HD_SELECT&t;(0x1a)&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|AMI_HD_STATUS
mdefine_line|#define AMI_HD_STATUS&t;(0x1e)&t;&t;/* see status-bits */
DECL|macro|AMI_HD_CMD
mdefine_line|#define AMI_HD_CMD&t;(0x101a)
multiline_comment|/* These are at different offsets from the base */
DECL|macro|HD_A4000_IRQ
mdefine_line|#define HD_A4000_IRQ&t;(0xdd3020)&t;/* MSB = 1, Harddisk is source of interrupt */
DECL|macro|HD_A1200_IRQ
mdefine_line|#define HD_A1200_IRQ&t;(0xda9000)&t;/* MSB = 1, Harddisk is source of interrupt */
macro_line|#endif
eof
