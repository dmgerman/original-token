macro_line|#ifndef _LINUX_HDREG_H
DECL|macro|_LINUX_HDREG_H
mdefine_line|#define _LINUX_HDREG_H
multiline_comment|/*&n; * This file contains some defines for the AT-hd-controller.&n; * Various sources. Check out some definitions (see comments with&n; * a ques).&n; */
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
DECL|macro|WIN_MULTREAD
mdefine_line|#define WIN_MULTREAD&t;&t;0xC4&t;/* read multiple sectors&t;*/
DECL|macro|WIN_MULTWRITE
mdefine_line|#define WIN_MULTWRITE&t;&t;0xC5&t;/* write multiple sectors&t;*/
DECL|macro|WIN_SETMULT
mdefine_line|#define WIN_SETMULT&t;&t;0xC6&t;/* enable read multiple&t;&t;*/
DECL|macro|WIN_IDENTIFY
mdefine_line|#define WIN_IDENTIFY&t;&t;0xEC&t;/* ask drive to identify itself&t;*/
DECL|macro|WIN_SETFEATURES
mdefine_line|#define WIN_SETFEATURES&t;&t;0xEF&t;/* set special drive features   */
multiline_comment|/* Bits for HD_ERROR */
DECL|macro|MARK_ERR
mdefine_line|#define MARK_ERR&t;0x01&t;/* Bad address mark */
DECL|macro|TRK0_ERR
mdefine_line|#define TRK0_ERR&t;0x02&t;/* couldn&squot;t find track 0 */
DECL|macro|ABRT_ERR
mdefine_line|#define ABRT_ERR&t;0x04&t;/* Command aborted */
DECL|macro|ID_ERR
mdefine_line|#define ID_ERR&t;&t;0x10&t;/* ID field not found */
DECL|macro|ECC_ERR
mdefine_line|#define ECC_ERR&t;&t;0x40&t;/* Uncorrectable ECC error */
DECL|macro|BBD_ERR
mdefine_line|#define&t;BBD_ERR&t;&t;0x80&t;/* block marked bad */
multiline_comment|/* HDIO_GETGEO is the preferred choice - HDIO_REQ will be removed at some&n;   later date */
DECL|macro|HDIO_REQ
mdefine_line|#define HDIO_REQ 0x301
DECL|macro|HDIO_GETGEO
mdefine_line|#define HDIO_GETGEO 0x301
DECL|struct|hd_geometry
r_struct
id|hd_geometry
(brace
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HDIO_GETUNMASKINTR
mdefine_line|#define HDIO_GETUNMASKINTR&t;0x302
DECL|macro|HDIO_SETUNMASKINTR
mdefine_line|#define HDIO_SETUNMASKINTR&t;0x303
DECL|macro|HDIO_GETMULTCOUNT
mdefine_line|#define HDIO_GETMULTCOUNT&t;0x304
DECL|macro|HDIO_SETMULTCOUNT
mdefine_line|#define HDIO_SETMULTCOUNT&t;0x305
DECL|macro|HDIO_SETFEATURE
mdefine_line|#define HDIO_SETFEATURE  &t;0x306
macro_line|#endif
eof
