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
DECL|macro|HDIO_GETIDENTITY
mdefine_line|#define HDIO_GETIDENTITY &t;0x307
macro_line|#endif
multiline_comment|/* structure returned by HDIO_GETIDENTITY, as per ASC X3T9.2 rev 4a */
DECL|struct|hd_driveid
r_struct
id|hd_driveid
(brace
DECL|member|config
r_int
r_int
id|config
suffix:semicolon
multiline_comment|/* lots of obsolete bit flags */
DECL|member|cyls
r_int
r_int
id|cyls
suffix:semicolon
multiline_comment|/* &quot;physical&quot; cyls */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
multiline_comment|/* reserved (word 2) */
DECL|member|heads
r_int
r_int
id|heads
suffix:semicolon
multiline_comment|/* &quot;physical&quot; heads */
DECL|member|track_bytes
r_int
r_int
id|track_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per track */
DECL|member|sector_bytes
r_int
r_int
id|sector_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per sector */
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
multiline_comment|/* &quot;physical&quot; sectors per track */
DECL|member|vendor0
r_int
r_int
id|vendor0
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor1
r_int
r_int
id|vendor1
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor2
r_int
r_int
id|vendor2
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|serial_no
r_int
r_char
id|serial_no
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|buf_type
r_int
r_int
id|buf_type
suffix:semicolon
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* 512 byte increments; 0 = not_specified */
DECL|member|ecc_bytes
r_int
r_int
id|ecc_bytes
suffix:semicolon
multiline_comment|/* for r/w long cmds; 0 = not_specified */
DECL|member|fw_rev
r_int
r_char
id|fw_rev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|model
r_int
r_char
id|model
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|max_multsect
r_int
r_char
id|max_multsect
suffix:semicolon
multiline_comment|/* 0=not_implemented */
DECL|member|vendor3
r_int
r_char
id|vendor3
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|dword_io
r_int
r_int
id|dword_io
suffix:semicolon
multiline_comment|/* 0=not_implemented; 1=implemented */
DECL|member|vendor4
r_int
r_char
id|vendor4
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|capability
r_int
r_char
id|capability
suffix:semicolon
multiline_comment|/* bits 0:DMA 1:LBA 2:IORDYsw 3:IORDYsup*/
DECL|member|reserved50
r_int
r_int
id|reserved50
suffix:semicolon
multiline_comment|/* reserved (word 50) */
DECL|member|vendor5
r_int
r_char
id|vendor5
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|tPIO
r_int
r_char
id|tPIO
suffix:semicolon
multiline_comment|/* 0=slow, 1=medium, 2=fast */
DECL|member|vendor6
r_int
r_char
id|vendor6
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|tDMA
r_int
r_char
id|tDMA
suffix:semicolon
multiline_comment|/* 0=slow, 1=medium, 2=fast */
DECL|member|field_valid
r_int
r_int
id|field_valid
suffix:semicolon
multiline_comment|/* bits 0:cur_ok 1:eide_ok */
DECL|member|cur_cyls
r_int
r_int
id|cur_cyls
suffix:semicolon
multiline_comment|/* logical cylinders */
DECL|member|cur_heads
r_int
r_int
id|cur_heads
suffix:semicolon
multiline_comment|/* logical heads */
DECL|member|cur_sectors
r_int
r_int
id|cur_sectors
suffix:semicolon
multiline_comment|/* logical sectors per track */
DECL|member|cur_capacity0
r_int
r_int
id|cur_capacity0
suffix:semicolon
multiline_comment|/* logical total sectors on drive */
DECL|member|cur_capacity1
r_int
r_int
id|cur_capacity1
suffix:semicolon
multiline_comment|/*  (2 words, misaligned int)     */
DECL|member|multsect
r_int
r_char
id|multsect
suffix:semicolon
multiline_comment|/* current multiple sector count */
DECL|member|multsect_valid
r_int
r_char
id|multsect_valid
suffix:semicolon
multiline_comment|/* when (bit0==1) multsect is ok */
DECL|member|lba_capacity
r_int
r_int
id|lba_capacity
suffix:semicolon
multiline_comment|/* total number of sectors */
DECL|member|dma_1word
r_int
r_int
id|dma_1word
suffix:semicolon
multiline_comment|/* single-word dma info */
DECL|member|dma_mword
r_int
r_int
id|dma_mword
suffix:semicolon
multiline_comment|/* multiple-word dma info */
DECL|member|eide_pio_modes
r_int
r_int
id|eide_pio_modes
suffix:semicolon
multiline_comment|/* bits 0:mode3 1:mode4 */
DECL|member|eide_dma_min
r_int
r_int
id|eide_dma_min
suffix:semicolon
multiline_comment|/* min mword dma cycle time (ns) */
DECL|member|eide_dma_time
r_int
r_int
id|eide_dma_time
suffix:semicolon
multiline_comment|/* recommended mword dma cycle time (ns) */
DECL|member|eide_pio
r_int
r_int
id|eide_pio
suffix:semicolon
multiline_comment|/* min cycle time (ns), no IORDY  */
DECL|member|eide_pio_iordy
r_int
r_int
id|eide_pio_iordy
suffix:semicolon
multiline_comment|/* min cycle time (ns), with IORDY */
DECL|member|reserved69
r_int
r_int
id|reserved69
suffix:semicolon
multiline_comment|/* reserved (word 69) */
DECL|member|reserved70
r_int
r_int
id|reserved70
suffix:semicolon
multiline_comment|/* reserved (word 70) */
multiline_comment|/* unsigned short reservedxx[57];*/
multiline_comment|/* reserved (words 71-127) */
multiline_comment|/* unsigned short vendor7  [32];*/
multiline_comment|/* vendor unique (words 128-159) */
multiline_comment|/* unsigned short reservedyy[96];*/
multiline_comment|/* reserved (words 160-255) */
)brace
suffix:semicolon
eof
