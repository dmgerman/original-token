macro_line|#ifndef _LINUX_ATAHDREG_H
DECL|macro|_LINUX_ATAHDREG_H
mdefine_line|#define _LINUX_ATAHDREG_H
multiline_comment|/*&n; * This file contains some defines for the Falcon IDE hd controller.&n; * Various sources. Check out some definitions (see comments with&n; * a ques).&n; */
DECL|macro|ATA_HD_BASE
mdefine_line|#define ATA_HD_BASE&t;0xfff00000
DECL|macro|ATA_HD_DATA
mdefine_line|#define ATA_HD_DATA&t;0x00&t;/* _CTL when writing */
DECL|macro|ATA_HD_ERROR
mdefine_line|#define ATA_HD_ERROR&t;0x05&t;/* see err-bits */
DECL|macro|ATA_HD_NSECTOR
mdefine_line|#define ATA_HD_NSECTOR&t;0x09&t;/* nr of sectors to read/write */
DECL|macro|ATA_HD_SECTOR
mdefine_line|#define ATA_HD_SECTOR&t;0x0d&t;/* starting sector */
DECL|macro|ATA_HD_LCYL
mdefine_line|#define ATA_HD_LCYL&t;0x11&t;/* starting cylinder */
DECL|macro|ATA_HD_HCYL
mdefine_line|#define ATA_HD_HCYL&t;0x15&t;/* high byte of starting cyl */
DECL|macro|ATA_HD_CURRENT
mdefine_line|#define ATA_HD_CURRENT&t;0x19&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|ATA_HD_STATUS
mdefine_line|#define ATA_HD_STATUS&t;0x1d&t;/* see status-bits */
DECL|macro|ATA_HD_CMD
mdefine_line|#define ATA_HD_CMD&t;0x39
DECL|macro|ATA_HD_ALTSTATUS
mdefine_line|#define ATA_HD_ALTSTATUS 0x39&t;/* same as HD_STATUS but doesn&squot;t clear irq */
macro_line|#endif&t;/* _LINUX_ATAHDREG_H */
eof
