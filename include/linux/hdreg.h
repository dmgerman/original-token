multiline_comment|/*&n; * This file contains some defines for the AT-hd-controller.&n; * Various sources. Check out some definitions (see comments with&n; * a ques).&n; */
macro_line|#ifndef _HDREG_H
DECL|macro|_HDREG_H
mdefine_line|#define _HDREG_H
multiline_comment|/* Hd controller regs. Ref: IBM AT Bios-listing */
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA&t;&t;0x1f0&t;/* _CTL when writing */
DECL|macro|HD_ERROR
mdefine_line|#define HD_ERROR&t;0x1f1&t;/* see err-bits */
DECL|macro|HD_NSECTOR
mdefine_line|#define HD_NSECTOR&t;0x1f2&t;/* nr of sectors to read/write */
DECL|macro|HD_SECTOR
mdefine_line|#define HD_SECTOR&t;0x1f3&t;/* starting sector */
DECL|macro|HD_LCYL
mdefine_line|#define HD_LCYL&t;&t;0x1f4&t;/* starting cylinder */
DECL|macro|HD_HCYL
mdefine_line|#define HD_HCYL&t;&t;0x1f5&t;/* high byte of starting cyl */
DECL|macro|HD_CURRENT
mdefine_line|#define HD_CURRENT&t;0x1f6&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|HD_STATUS
mdefine_line|#define HD_STATUS&t;0x1f7&t;/* see status-bits */
DECL|macro|HD_PRECOMP
mdefine_line|#define HD_PRECOMP HD_ERROR&t;/* same io address, read=error, write=precomp */
DECL|macro|HD_COMMAND
mdefine_line|#define HD_COMMAND HD_STATUS&t;/* same io address, read=status, write=cmd */
DECL|macro|HD_CMD
mdefine_line|#define HD_CMD&t;&t;0x3f6
multiline_comment|/* Bits of HD_STATUS */
DECL|macro|ERR_STAT
mdefine_line|#define ERR_STAT&t;0x01
DECL|macro|INDEX_STAT
mdefine_line|#define INDEX_STAT&t;0x02
DECL|macro|ECC_STAT
mdefine_line|#define ECC_STAT&t;0x04&t;/* Corrected error */
DECL|macro|DRQ_STAT
mdefine_line|#define DRQ_STAT&t;0x08
DECL|macro|SEEK_STAT
mdefine_line|#define SEEK_STAT&t;0x10
DECL|macro|WRERR_STAT
mdefine_line|#define WRERR_STAT&t;0x20
DECL|macro|READY_STAT
mdefine_line|#define READY_STAT&t;0x40
DECL|macro|BUSY_STAT
mdefine_line|#define BUSY_STAT&t;0x80
multiline_comment|/* Values for HD_COMMAND */
DECL|macro|WIN_RESTORE
mdefine_line|#define WIN_RESTORE&t;&t;0x10
DECL|macro|WIN_READ
mdefine_line|#define WIN_READ&t;&t;0x20
DECL|macro|WIN_WRITE
mdefine_line|#define WIN_WRITE&t;&t;0x30
DECL|macro|WIN_VERIFY
mdefine_line|#define WIN_VERIFY&t;&t;0x40
DECL|macro|WIN_FORMAT
mdefine_line|#define WIN_FORMAT&t;&t;0x50
DECL|macro|WIN_INIT
mdefine_line|#define WIN_INIT&t;&t;0x60
DECL|macro|WIN_SEEK
mdefine_line|#define WIN_SEEK &t;&t;0x70
DECL|macro|WIN_DIAGNOSE
mdefine_line|#define WIN_DIAGNOSE&t;&t;0x90
DECL|macro|WIN_SPECIFY
mdefine_line|#define WIN_SPECIFY&t;&t;0x91
multiline_comment|/* Bits for HD_ERROR */
DECL|macro|MARK_ERR
mdefine_line|#define MARK_ERR&t;0x01&t;/* Bad address mark ? */
DECL|macro|TRK0_ERR
mdefine_line|#define TRK0_ERR&t;0x02&t;/* couldn&squot;t find track 0 */
DECL|macro|ABRT_ERR
mdefine_line|#define ABRT_ERR&t;0x04&t;/* ? */
DECL|macro|ID_ERR
mdefine_line|#define ID_ERR&t;&t;0x10&t;/* ? */
DECL|macro|ECC_ERR
mdefine_line|#define ECC_ERR&t;&t;0x40&t;/* ? */
DECL|macro|BBD_ERR
mdefine_line|#define&t;BBD_ERR&t;&t;0x80&t;/* ? */
DECL|struct|partition
r_struct
id|partition
(brace
DECL|member|boot_ind
r_int
r_char
id|boot_ind
suffix:semicolon
multiline_comment|/* 0x80 - active (unused) */
DECL|member|head
r_int
r_char
id|head
suffix:semicolon
multiline_comment|/* ? */
DECL|member|sector
r_int
r_char
id|sector
suffix:semicolon
multiline_comment|/* ? */
DECL|member|cyl
r_int
r_char
id|cyl
suffix:semicolon
multiline_comment|/* ? */
DECL|member|sys_ind
r_int
r_char
id|sys_ind
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_head
r_int
r_char
id|end_head
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_sector
r_int
r_char
id|end_sector
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_cyl
r_int
r_char
id|end_cyl
suffix:semicolon
multiline_comment|/* ? */
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector counting from 0 */
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
multiline_comment|/* nr of sectors in partition */
)brace
suffix:semicolon
macro_line|#endif
eof
