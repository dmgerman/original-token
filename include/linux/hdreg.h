macro_line|#ifndef _LINUX_HDREG_H
DECL|macro|_LINUX_HDREG_H
mdefine_line|#define _LINUX_HDREG_H
multiline_comment|/*&n; * This file contains some defines for the AT-hd-controller.&n; * Various sources.  &n; */
DECL|macro|HD_IRQ
mdefine_line|#define HD_IRQ 14&t;&t;/* the standard disk interrupt */
multiline_comment|/* ide.c has its own port definitions in &quot;ide.h&quot; */
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
DECL|macro|HD_FEATURE
mdefine_line|#define HD_FEATURE HD_ERROR&t;/* same io address, read=error, write=feature */
DECL|macro|HD_PRECOMP
mdefine_line|#define HD_PRECOMP HD_FEATURE&t;/* obsolete use of this port - predates IDE */
DECL|macro|HD_COMMAND
mdefine_line|#define HD_COMMAND HD_STATUS&t;/* same io address, read=status, write=cmd */
DECL|macro|HD_CMD
mdefine_line|#define HD_CMD&t;&t;0x3f6&t;/* used for resets */
DECL|macro|HD_ALTSTATUS
mdefine_line|#define HD_ALTSTATUS&t;0x3f6&t;/* same as HD_STATUS but doesn&squot;t clear irq */
multiline_comment|/* remainder is shared between hd.c, ide.c, ide-cd.c, and the hdparm utility */
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
DECL|macro|WIN_WRITE_VERIFY
mdefine_line|#define WIN_WRITE_VERIFY&t;0x3C
DECL|macro|WIN_VERIFY
mdefine_line|#define WIN_VERIFY&t;&t;0x40
DECL|macro|WIN_FORMAT
mdefine_line|#define WIN_FORMAT&t;&t;0x50
DECL|macro|WIN_INIT
mdefine_line|#define WIN_INIT&t;&t;0x60
DECL|macro|WIN_SEEK
mdefine_line|#define WIN_SEEK&t;&t;0x70
DECL|macro|WIN_DIAGNOSE
mdefine_line|#define WIN_DIAGNOSE&t;&t;0x90
DECL|macro|WIN_SPECIFY
mdefine_line|#define WIN_SPECIFY&t;&t;0x91&t;/* set drive geometry translation */
DECL|macro|WIN_SETIDLE1
mdefine_line|#define WIN_SETIDLE1&t;&t;0xE3
DECL|macro|WIN_SETIDLE2
mdefine_line|#define WIN_SETIDLE2&t;&t;0x97
DECL|macro|WIN_STANDBYNOW1
mdefine_line|#define WIN_STANDBYNOW1&t;&t;0xE0
DECL|macro|WIN_STANDBYNOW2
mdefine_line|#define WIN_STANDBYNOW2&t;&t;0x94
DECL|macro|WIN_SLEEPNOW1
mdefine_line|#define WIN_SLEEPNOW1&t;&t;0xE6
DECL|macro|WIN_SLEEPNOW2
mdefine_line|#define WIN_SLEEPNOW2&t;&t;0x99
DECL|macro|WIN_CHECKPOWERMODE1
mdefine_line|#define WIN_CHECKPOWERMODE1&t;0xE5
DECL|macro|WIN_CHECKPOWERMODE2
mdefine_line|#define WIN_CHECKPOWERMODE2&t;0x98
DECL|macro|WIN_DOORLOCK
mdefine_line|#define WIN_DOORLOCK&t;&t;0xde&t;/* lock door on removable drives */
DECL|macro|WIN_DOORUNLOCK
mdefine_line|#define WIN_DOORUNLOCK&t;&t;0xdf&t;/* unlock door on removable drives */
DECL|macro|WIN_MULTREAD
mdefine_line|#define WIN_MULTREAD&t;&t;0xC4&t;/* read sectors using multiple mode */
DECL|macro|WIN_MULTWRITE
mdefine_line|#define WIN_MULTWRITE&t;&t;0xC5&t;/* write sectors using multiple mode */
DECL|macro|WIN_SETMULT
mdefine_line|#define WIN_SETMULT&t;&t;0xC6&t;/* enable/disable multiple mode */
DECL|macro|WIN_IDENTIFY
mdefine_line|#define WIN_IDENTIFY&t;&t;0xEC&t;/* ask drive to identify itself&t;*/
DECL|macro|WIN_IDENTIFY_DMA
mdefine_line|#define WIN_IDENTIFY_DMA&t;0xEE&t;/* same as WIN_IDENTIFY, but DMA */
DECL|macro|WIN_SETFEATURES
mdefine_line|#define WIN_SETFEATURES&t;&t;0xEF&t;/* set special drive features */
DECL|macro|WIN_READDMA
mdefine_line|#define WIN_READDMA&t;&t;0xc8&t;/* read sectors using DMA transfers */
DECL|macro|WIN_WRITEDMA
mdefine_line|#define WIN_WRITEDMA&t;&t;0xca&t;/* write sectors using DMA transfers */
DECL|macro|WIN_READ_BUFFER
mdefine_line|#define WIN_READ_BUFFER&t;&t;0xE4&t;/* force read only 1 sector */
DECL|macro|WIN_WRITE_BUFFER
mdefine_line|#define WIN_WRITE_BUFFER&t;0xE8&t;/* force write only 1 sector */
DECL|macro|WIN_SMART
mdefine_line|#define WIN_SMART&t;&t;0xb0&t;/* self-monitoring and reporting */
multiline_comment|/* Additional drive command codes used by ATAPI devices. */
DECL|macro|WIN_PIDENTIFY
mdefine_line|#define WIN_PIDENTIFY&t;&t;0xA1&t;/* identify ATAPI device&t;*/
DECL|macro|WIN_SRST
mdefine_line|#define WIN_SRST&t;&t;0x08&t;/* ATAPI soft reset command */
DECL|macro|WIN_PACKETCMD
mdefine_line|#define WIN_PACKETCMD&t;&t;0xa0&t;/* Send a packet command. */
DECL|macro|EXABYTE_ENABLE_NEST
mdefine_line|#define EXABYTE_ENABLE_NEST&t;0xf0
multiline_comment|/* WIN_SMART sub-commands */
DECL|macro|SMART_READ_VALUES
mdefine_line|#define SMART_READ_VALUES&t;0xd0
DECL|macro|SMART_READ_THRESHOLDS
mdefine_line|#define SMART_READ_THRESHOLDS&t;0xd1
DECL|macro|SMART_AUTOSAVE
mdefine_line|#define SMART_AUTOSAVE&t;&t;0xd2
DECL|macro|SMART_SAVE
mdefine_line|#define SMART_SAVE&t;&t;0xd3
DECL|macro|SMART_IMMEDIATE_OFFLINE
mdefine_line|#define SMART_IMMEDIATE_OFFLINE&t;0xd4
DECL|macro|SMART_ENABLE
mdefine_line|#define SMART_ENABLE&t;&t;0xd8
DECL|macro|SMART_DISABLE
mdefine_line|#define SMART_DISABLE&t;&t;0xd9
DECL|macro|SMART_STATUS
mdefine_line|#define SMART_STATUS&t;&t;0xda
DECL|macro|SMART_AUTO_OFFLINE
mdefine_line|#define SMART_AUTO_OFFLINE&t;0xdb
multiline_comment|/* WIN_SETFEATURES sub-commands */
DECL|macro|SETFEATURES_EN_WCACHE
mdefine_line|#define SETFEATURES_EN_WCACHE&t;0x02&t;/* Enable write cache */
DECL|macro|SETFEATURES_XFER
mdefine_line|#define SETFEATURES_XFER&t;0x03&t;/* Set transfer mode */
DECL|macro|XFER_UDMA_6
macro_line|#&t;define XFER_UDMA_6&t;0x46&t;/* 0100|0110 */
DECL|macro|XFER_UDMA_5
macro_line|#&t;define XFER_UDMA_5&t;0x45&t;/* 0100|0101 */
DECL|macro|XFER_UDMA_4
macro_line|#&t;define XFER_UDMA_4&t;0x44&t;/* 0100|0100 */
DECL|macro|XFER_UDMA_3
macro_line|#&t;define XFER_UDMA_3&t;0x43&t;/* 0100|0011 */
DECL|macro|XFER_UDMA_2
macro_line|#&t;define XFER_UDMA_2&t;0x42&t;/* 0100|0010 */
DECL|macro|XFER_UDMA_1
macro_line|#&t;define XFER_UDMA_1&t;0x41&t;/* 0100|0001 */
DECL|macro|XFER_UDMA_0
macro_line|#&t;define XFER_UDMA_0&t;0x40&t;/* 0100|0000 */
DECL|macro|XFER_MW_DMA_2
macro_line|#&t;define XFER_MW_DMA_2&t;0x22&t;/* 0010|0010 */
DECL|macro|XFER_MW_DMA_1
macro_line|#&t;define XFER_MW_DMA_1&t;0x21&t;/* 0010|0001 */
DECL|macro|XFER_MW_DMA_0
macro_line|#&t;define XFER_MW_DMA_0&t;0x20&t;/* 0010|0000 */
DECL|macro|XFER_SW_DMA_2
macro_line|#&t;define XFER_SW_DMA_2&t;0x12&t;/* 0001|0010 */
DECL|macro|XFER_SW_DMA_1
macro_line|#&t;define XFER_SW_DMA_1&t;0x11&t;/* 0001|0001 */
DECL|macro|XFER_SW_DMA_0
macro_line|#&t;define XFER_SW_DMA_0&t;0x10&t;/* 0001|0000 */
DECL|macro|XFER_PIO_4
macro_line|#&t;define XFER_PIO_4&t;0x0C&t;/* 0000|1100 */
DECL|macro|XFER_PIO_3
macro_line|#&t;define XFER_PIO_3&t;0x0B&t;/* 0000|1011 */
DECL|macro|XFER_PIO_2
macro_line|#&t;define XFER_PIO_2&t;0x0A&t;/* 0000|1010 */
DECL|macro|XFER_PIO_1
macro_line|#&t;define XFER_PIO_1&t;0x09&t;/* 0000|1001 */
DECL|macro|XFER_PIO_0
macro_line|#&t;define XFER_PIO_0&t;0x08&t;/* 0000|1000 */
DECL|macro|XFER_PIO_SLOW
macro_line|#&t;define XFER_PIO_SLOW&t;0x00&t;/* 0000|0000 */
DECL|macro|SETFEATURES_EN_APM
mdefine_line|#define SETFEATURES_EN_APM&t;0x05&t;/* Enable advanced power management */
DECL|macro|SETFEATURES_DIS_MSN
mdefine_line|#define SETFEATURES_DIS_MSN&t;0x31&t;/* Disable Media Status Notification */
DECL|macro|SETFEATURES_DIS_RLA
mdefine_line|#define SETFEATURES_DIS_RLA&t;0x55&t;/* Disable read look-ahead feature */
DECL|macro|SETFEATURES_EN_RI
mdefine_line|#define SETFEATURES_EN_RI&t;0x5D&t;/* Enable release interrupt */
DECL|macro|SETFEATURES_EN_SI
mdefine_line|#define SETFEATURES_EN_SI&t;0x5E&t;/* Enable SERVICE interrupt */
DECL|macro|SETFEATURES_DIS_RPOD
mdefine_line|#define SETFEATURES_DIS_RPOD&t;0x66&t;/* Disable reverting to power on defaults */
DECL|macro|SETFEATURES_DIS_WCACHE
mdefine_line|#define SETFEATURES_DIS_WCACHE&t;0x82&t;/* Disable write cache */
DECL|macro|SETFEATURES_DIS_APM
mdefine_line|#define SETFEATURES_DIS_APM&t;0x85&t;/* Disable advanced power management */
DECL|macro|SETFEATURES_EN_MSN
mdefine_line|#define SETFEATURES_EN_MSN&t;0x95&t;/* Enable Media Status Notification */
DECL|macro|SETFEATURES_EN_RLA
mdefine_line|#define SETFEATURES_EN_RLA&t;0xAA&t;/* Enable read look-ahead feature */
DECL|macro|SETFEATURES_EN_RPOD
mdefine_line|#define SETFEATURES_EN_RPOD&t;0xCC&t;/* Enable reverting to power on defaults */
DECL|macro|SETFEATURES_DIS_RI
mdefine_line|#define SETFEATURES_DIS_RI&t;0xDD&t;/* Disable release interrupt */
DECL|macro|SETFEATURES_DIS_SI
mdefine_line|#define SETFEATURES_DIS_SI&t;0xDE&t;/* Disable SERVICE interrupt */
multiline_comment|/* WIN_SECURITY sub-commands */
DECL|macro|SECURITY_SET_PASSWORD
mdefine_line|#define SECURITY_SET_PASSWORD&t;&t;0xBA&t;/* 0xF1 */
DECL|macro|SECURITY_UNLOCK
mdefine_line|#define SECURITY_UNLOCK&t;&t;&t;0xBB&t;/* 0xF2 */
DECL|macro|SECURITY_ERASE_PREPARE
mdefine_line|#define SECURITY_ERASE_PREPARE&t;&t;0xBC&t;/* 0xF3 */
DECL|macro|SECURITY_ERASE_UNIT
mdefine_line|#define SECURITY_ERASE_UNIT&t;&t;0xBD&t;/* 0xF4 */
DECL|macro|SECURITY_FREEZE_LOCK
mdefine_line|#define SECURITY_FREEZE_LOCK&t;&t;0xBE&t;/* 0xF5 */
DECL|macro|SECURITY_DISABLE_PASSWORD
mdefine_line|#define SECURITY_DISABLE_PASSWORD&t;0xBF&t;/* 0xF6 */
multiline_comment|/* Bits for HD_ERROR */
DECL|macro|MARK_ERR
mdefine_line|#define MARK_ERR&t;0x01&t;/* Bad address mark */
DECL|macro|TRK0_ERR
mdefine_line|#define TRK0_ERR&t;0x02&t;/* couldn&squot;t find track 0 */
DECL|macro|ABRT_ERR
mdefine_line|#define ABRT_ERR&t;0x04&t;/* Command aborted */
DECL|macro|MCR_ERR
mdefine_line|#define MCR_ERR&t;&t;0x08&t;/* media change request */
DECL|macro|ID_ERR
mdefine_line|#define ID_ERR&t;&t;0x10&t;/* ID field not found */
DECL|macro|ECC_ERR
mdefine_line|#define ECC_ERR&t;&t;0x40&t;/* Uncorrectable ECC error */
DECL|macro|BBD_ERR
mdefine_line|#define&t;BBD_ERR&t;&t;0x80&t;/* pre-EIDE meaning:  block marked bad */
DECL|macro|ICRC_ERR
mdefine_line|#define&t;ICRC_ERR&t;0x80&t;/* new meaning:  CRC error during transfer */
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
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) ptrs to user space are numbered 0x030n/0x031n */
DECL|macro|HDIO_GETGEO
mdefine_line|#define HDIO_GETGEO&t;&t;0x0301&t;/* get device geometry */
DECL|macro|HDIO_GET_UNMASKINTR
mdefine_line|#define HDIO_GET_UNMASKINTR&t;0x0302&t;/* get current unmask setting */
DECL|macro|HDIO_GET_MULTCOUNT
mdefine_line|#define HDIO_GET_MULTCOUNT&t;0x0304&t;/* get current IDE blockmode setting */
DECL|macro|HDIO_OBSOLETE_IDENTITY
mdefine_line|#define HDIO_OBSOLETE_IDENTITY&t;0x0307&t;/* OBSOLETE, DO NOT USE: returns 142 bytes */
DECL|macro|HDIO_GET_KEEPSETTINGS
mdefine_line|#define HDIO_GET_KEEPSETTINGS&t;0x0308&t;/* get keep-settings-on-reset flag */
DECL|macro|HDIO_GET_32BIT
mdefine_line|#define HDIO_GET_32BIT&t;&t;0x0309&t;/* get current io_32bit setting */
DECL|macro|HDIO_GET_NOWERR
mdefine_line|#define HDIO_GET_NOWERR&t;&t;0x030a&t;/* get ignore-write-error flag */
DECL|macro|HDIO_GET_DMA
mdefine_line|#define HDIO_GET_DMA&t;&t;0x030b&t;/* get use-dma flag */
DECL|macro|HDIO_GET_NICE
mdefine_line|#define HDIO_GET_NICE&t;&t;0x030c&t;/* get nice flags */
DECL|macro|HDIO_GET_IDENTITY
mdefine_line|#define HDIO_GET_IDENTITY&t;0x030d&t;/* get IDE identification info */
DECL|macro|HDIO_DRIVE_CMD
mdefine_line|#define HDIO_DRIVE_CMD&t;&t;0x031f&t;/* execute a special drive command */
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) non-ptr values are numbered 0x032n/0x033n */
DECL|macro|HDIO_SET_MULTCOUNT
mdefine_line|#define HDIO_SET_MULTCOUNT&t;0x0321&t;/* change IDE blockmode */
DECL|macro|HDIO_SET_UNMASKINTR
mdefine_line|#define HDIO_SET_UNMASKINTR&t;0x0322&t;/* permit other irqs during I/O */
DECL|macro|HDIO_SET_KEEPSETTINGS
mdefine_line|#define HDIO_SET_KEEPSETTINGS&t;0x0323&t;/* keep ioctl settings on reset */
DECL|macro|HDIO_SET_32BIT
mdefine_line|#define HDIO_SET_32BIT&t;&t;0x0324&t;/* change io_32bit flags */
DECL|macro|HDIO_SET_NOWERR
mdefine_line|#define HDIO_SET_NOWERR&t;&t;0x0325&t;/* change ignore-write-error flag */
DECL|macro|HDIO_SET_DMA
mdefine_line|#define HDIO_SET_DMA&t;&t;0x0326&t;/* change use-dma flag */
DECL|macro|HDIO_SET_PIO_MODE
mdefine_line|#define HDIO_SET_PIO_MODE&t;0x0327&t;/* reconfig interface to new speed */
DECL|macro|HDIO_SCAN_HWIF
mdefine_line|#define HDIO_SCAN_HWIF&t;&t;0x0328&t;/* register and (re)scan interface */
DECL|macro|HDIO_SET_NICE
mdefine_line|#define HDIO_SET_NICE&t;&t;0x0329&t;/* set nice flags */
DECL|macro|HDIO_UNREGISTER_HWIF
mdefine_line|#define HDIO_UNREGISTER_HWIF&t;0x032a  /* unregister interface */
multiline_comment|/* structure returned by HDIO_GET_IDENTITY, as per ANSI ATA2 rev.2f spec */
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
DECL|member|word69
r_int
r_int
id|word69
suffix:semicolon
DECL|member|word70
r_int
r_int
id|word70
suffix:semicolon
multiline_comment|/* HDIO_GET_IDENTITY currently returns only words 0 through 70 */
DECL|member|word71
r_int
r_int
id|word71
suffix:semicolon
DECL|member|word72
r_int
r_int
id|word72
suffix:semicolon
DECL|member|word73
r_int
r_int
id|word73
suffix:semicolon
DECL|member|word74
r_int
r_int
id|word74
suffix:semicolon
DECL|member|word75
r_int
r_int
id|word75
suffix:semicolon
DECL|member|word76
r_int
r_int
id|word76
suffix:semicolon
DECL|member|word77
r_int
r_int
id|word77
suffix:semicolon
DECL|member|word78
r_int
r_int
id|word78
suffix:semicolon
DECL|member|word79
r_int
r_int
id|word79
suffix:semicolon
DECL|member|word80
r_int
r_int
id|word80
suffix:semicolon
DECL|member|word81
r_int
r_int
id|word81
suffix:semicolon
DECL|member|command_sets
r_int
r_int
id|command_sets
suffix:semicolon
multiline_comment|/* bits 0:Smart 1:Security 2:Removable 3:PM */
DECL|member|word83
r_int
r_int
id|word83
suffix:semicolon
multiline_comment|/* bits 14:Smart Enabled 13:0 zero */
DECL|member|word84
r_int
r_int
id|word84
suffix:semicolon
DECL|member|word85
r_int
r_int
id|word85
suffix:semicolon
DECL|member|word86
r_int
r_int
id|word86
suffix:semicolon
DECL|member|word87
r_int
r_int
id|word87
suffix:semicolon
DECL|member|dma_ultra
r_int
r_int
id|dma_ultra
suffix:semicolon
DECL|member|word89
r_int
r_int
id|word89
suffix:semicolon
multiline_comment|/* reserved (word 89) */
DECL|member|word90
r_int
r_int
id|word90
suffix:semicolon
multiline_comment|/* reserved (word 90) */
DECL|member|word91
r_int
r_int
id|word91
suffix:semicolon
multiline_comment|/* reserved (word 91) */
DECL|member|word92
r_int
r_int
id|word92
suffix:semicolon
multiline_comment|/* reserved (word 92) */
DECL|member|word93
r_int
r_int
id|word93
suffix:semicolon
multiline_comment|/* reserved (word 93) */
DECL|member|word94
r_int
r_int
id|word94
suffix:semicolon
multiline_comment|/* reserved (word 94) */
DECL|member|word95
r_int
r_int
id|word95
suffix:semicolon
multiline_comment|/* reserved (word 95) */
DECL|member|word96
r_int
r_int
id|word96
suffix:semicolon
multiline_comment|/* reserved (word 96) */
DECL|member|word97
r_int
r_int
id|word97
suffix:semicolon
multiline_comment|/* reserved (word 97) */
DECL|member|word98
r_int
r_int
id|word98
suffix:semicolon
multiline_comment|/* reserved (word 98) */
DECL|member|word99
r_int
r_int
id|word99
suffix:semicolon
multiline_comment|/* reserved (word 99) */
DECL|member|word100
r_int
r_int
id|word100
suffix:semicolon
multiline_comment|/* reserved (word 100) */
DECL|member|word101
r_int
r_int
id|word101
suffix:semicolon
multiline_comment|/* reserved (word 101) */
DECL|member|word102
r_int
r_int
id|word102
suffix:semicolon
multiline_comment|/* reserved (word 102) */
DECL|member|word103
r_int
r_int
id|word103
suffix:semicolon
multiline_comment|/* reserved (word 103) */
DECL|member|word104
r_int
r_int
id|word104
suffix:semicolon
multiline_comment|/* reserved (word 104) */
DECL|member|word105
r_int
r_int
id|word105
suffix:semicolon
multiline_comment|/* reserved (word 105) */
DECL|member|word106
r_int
r_int
id|word106
suffix:semicolon
multiline_comment|/* reserved (word 106) */
DECL|member|word107
r_int
r_int
id|word107
suffix:semicolon
multiline_comment|/* reserved (word 107) */
DECL|member|word108
r_int
r_int
id|word108
suffix:semicolon
multiline_comment|/* reserved (word 108) */
DECL|member|word109
r_int
r_int
id|word109
suffix:semicolon
multiline_comment|/* reserved (word 109) */
DECL|member|word110
r_int
r_int
id|word110
suffix:semicolon
multiline_comment|/* reserved (word 110) */
DECL|member|word111
r_int
r_int
id|word111
suffix:semicolon
multiline_comment|/* reserved (word 111) */
DECL|member|word112
r_int
r_int
id|word112
suffix:semicolon
multiline_comment|/* reserved (word 112) */
DECL|member|word113
r_int
r_int
id|word113
suffix:semicolon
multiline_comment|/* reserved (word 113) */
DECL|member|word114
r_int
r_int
id|word114
suffix:semicolon
multiline_comment|/* reserved (word 114) */
DECL|member|word115
r_int
r_int
id|word115
suffix:semicolon
multiline_comment|/* reserved (word 115) */
DECL|member|word116
r_int
r_int
id|word116
suffix:semicolon
multiline_comment|/* reserved (word 116) */
DECL|member|word117
r_int
r_int
id|word117
suffix:semicolon
multiline_comment|/* reserved (word 117) */
DECL|member|word118
r_int
r_int
id|word118
suffix:semicolon
multiline_comment|/* reserved (word 118) */
DECL|member|word119
r_int
r_int
id|word119
suffix:semicolon
multiline_comment|/* reserved (word 119) */
DECL|member|word120
r_int
r_int
id|word120
suffix:semicolon
multiline_comment|/* reserved (word 120) */
DECL|member|word121
r_int
r_int
id|word121
suffix:semicolon
multiline_comment|/* reserved (word 121) */
DECL|member|word122
r_int
r_int
id|word122
suffix:semicolon
multiline_comment|/* reserved (word 122) */
DECL|member|word123
r_int
r_int
id|word123
suffix:semicolon
multiline_comment|/* reserved (word 123) */
DECL|member|word124
r_int
r_int
id|word124
suffix:semicolon
multiline_comment|/* reserved (word 124) */
DECL|member|word125
r_int
r_int
id|word125
suffix:semicolon
multiline_comment|/* reserved (word 125) */
DECL|member|word126
r_int
r_int
id|word126
suffix:semicolon
multiline_comment|/* reserved (word 126) */
DECL|member|word127
r_int
r_int
id|word127
suffix:semicolon
multiline_comment|/* reserved (word 127) */
DECL|member|security
r_int
r_int
id|security
suffix:semicolon
multiline_comment|/* bits 0:support 1:enabled 2:locked 3:frozen */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|127
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IDE &quot;nice&quot; flags. These are used on a per drive basis to determine&n; * when to be nice and give more bandwidth to the other devices which&n; * share the same IDE bus.&n; */
DECL|macro|IDE_NICE_DSC_OVERLAP
mdefine_line|#define IDE_NICE_DSC_OVERLAP&t;(0)&t;/* per the DSC overlap protocol */
DECL|macro|IDE_NICE_ATAPI_OVERLAP
mdefine_line|#define IDE_NICE_ATAPI_OVERLAP&t;(1)&t;/* not supported yet */
DECL|macro|IDE_NICE_0
mdefine_line|#define IDE_NICE_0&t;&t;(2)&t;/* when sure that it won&squot;t affect us */
DECL|macro|IDE_NICE_1
mdefine_line|#define IDE_NICE_1&t;&t;(3)&t;/* when probably won&squot;t affect us much */
DECL|macro|IDE_NICE_2
mdefine_line|#define IDE_NICE_2&t;&t;(4)&t;/* when we know it&squot;s on our expense */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These routines are used for kernel command line parameters from main.c:&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_HD
r_void
id|hd_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_BLK_DEV_HD */
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
r_int
id|ide_register
c_func
(paren
r_int
id|io_port
comma
r_int
id|ctl_port
comma
r_int
id|irq
)paren
suffix:semicolon
r_void
id|ide_unregister
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDE || CONFIG_BLK_DEV_IDE_MODULE */
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_HDREG_H */
eof
