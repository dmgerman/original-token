multiline_comment|/*&n; *  linux/drivers/block/ide.h&n; *&n; *  Copyright (C) 1994, 1995  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; * This is the multiple IDE interface driver, as evolved from hd.c.  &n; * It supports up to four IDE interfaces, on one or more IRQs (usually 14 &amp; 15).&n; * There can be up to two drives per interface, as per the ATA-2 spec.&n; *&n; * Primary i/f:    ide0: major=3;  (hda)         minor=0; (hdb)         minor=64&n; * Secondary i/f:  ide1: major=22; (hdc or hd1a) minor=0; (hdd or hd1b) minor=64&n; * Tertiary i/f:   ide2: major=33; (hde)         minor=0; (hdf)         minor=64&n; * Quaternary i/f: ide3: major=34; (hdg)         minor=0; (hdh)         minor=64&n; */
multiline_comment|/******************************************************************************&n; * IDE driver configuration options (play with these as desired):&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|REALLY_FAST_IO
macro_line|#undef &t;REALLY_FAST_IO&t;&t;&t;/* define if ide ports are perfect */
DECL|macro|INITIAL_MULT_COUNT
mdefine_line|#define INITIAL_MULT_COUNT&t;0&t;/* off=0; on=2,4,8,16,32, etc.. */
macro_line|#ifndef DISK_RECOVERY_TIME&t;&t;/* off=0; on=access_delay_time */
DECL|macro|DISK_RECOVERY_TIME
mdefine_line|#define DISK_RECOVERY_TIME&t;0&t;/*  for hardware that needs it */
macro_line|#endif
macro_line|#ifndef OK_TO_RESET_CONTROLLER&t;&t;/* 1 needed for good error recovery */
DECL|macro|OK_TO_RESET_CONTROLLER
mdefine_line|#define OK_TO_RESET_CONTROLLER&t;1&t;/* 0 for use with AH2372A/B interface */
macro_line|#endif
macro_line|#ifndef SUPPORT_RZ1000&t;&t;&t;/* 1 to support RZ1000 chipset */
DECL|macro|SUPPORT_RZ1000
mdefine_line|#define SUPPORT_RZ1000&t;&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef SUPPORT_CMD640&t;&t;&t;/* 1 to support CMD640 chipset */
DECL|macro|SUPPORT_CMD640
mdefine_line|#define SUPPORT_CMD640&t;&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef SUPPORT_HT6560B&t;&t;&t;/* 1 to support HT6560B chipset */
DECL|macro|SUPPORT_HT6560B
mdefine_line|#define SUPPORT_HT6560B&t;&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef SUPPORT_DTC2278&t;&t;&t;/* 1 to support DTC2278 chipset */
DECL|macro|SUPPORT_DTC2278
mdefine_line|#define SUPPORT_DTC2278&t;&t;1&t;/* 0 to reduce kernel size */
macro_line|#ifndef SET_DTC2278_MODE4
DECL|macro|SET_DTC2278_MODE4
mdefine_line|#define SET_DTC2278_MODE4&t;0&t;/* 1 to init primary i/f for PIO mode4 */
macro_line|#endif
macro_line|#endif
macro_line|#ifndef FANCY_STATUS_DUMPS&t;&t;/* 1 for human-readable drive errors */
DECL|macro|FANCY_STATUS_DUMPS
mdefine_line|#define FANCY_STATUS_DUMPS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
multiline_comment|/*&n; * IDE_DRIVE_CMD is used to implement many features of the hdparm utility&n; */
DECL|macro|IDE_DRIVE_CMD
mdefine_line|#define IDE_DRIVE_CMD&t;&t;99&t;/* (magic) undef to reduce kernel size*/
multiline_comment|/*&n; *  &quot;No user-serviceable parts&quot; beyond this point  :)&n; *****************************************************************************/
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
multiline_comment|/* used everywhere */
multiline_comment|/*&n; * Probably not wise to fiddle with these&n; */
DECL|macro|ERROR_MAX
mdefine_line|#define ERROR_MAX&t;8&t;/* Max read/write errors per sector */
DECL|macro|ERROR_RESET
mdefine_line|#define ERROR_RESET&t;3&t;/* Reset controller every 4th retry */
DECL|macro|ERROR_RECAL
mdefine_line|#define ERROR_RECAL&t;1&t;/* Recalibrate every 2nd retry */
multiline_comment|/*&n; * Ensure that various configuration flags have compatible settings&n; */
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|REALLY_FAST_IO
macro_line|#undef REALLY_FAST_IO
macro_line|#endif
multiline_comment|/*&n; * Definitions for accessing IDE controller registers&n; */
DECL|macro|HWIF
mdefine_line|#define HWIF(drive)&t;&t;((ide_hwif_t *)drive-&gt;hwif)
DECL|macro|HWGROUP
mdefine_line|#define HWGROUP(drive)&t;&t;((ide_hwgroup_t *)(HWIF(drive)-&gt;hwgroup))
DECL|macro|IDE_DATA_REG
mdefine_line|#define IDE_DATA_REG&t;&t;(HWIF(drive)-&gt;io_base)
DECL|macro|IDE_ERROR_REG
mdefine_line|#define IDE_ERROR_REG&t;&t;(HWIF(drive)-&gt;io_base+1)
DECL|macro|IDE_NSECTOR_REG
mdefine_line|#define IDE_NSECTOR_REG&t;&t;(HWIF(drive)-&gt;io_base+2)
DECL|macro|IDE_SECTOR_REG
mdefine_line|#define IDE_SECTOR_REG&t;&t;(HWIF(drive)-&gt;io_base+3)
DECL|macro|IDE_LCYL_REG
mdefine_line|#define IDE_LCYL_REG&t;&t;(HWIF(drive)-&gt;io_base+4)
DECL|macro|IDE_HCYL_REG
mdefine_line|#define IDE_HCYL_REG&t;&t;(HWIF(drive)-&gt;io_base+5)
DECL|macro|IDE_SELECT_REG
mdefine_line|#define IDE_SELECT_REG&t;&t;(HWIF(drive)-&gt;io_base+6)
DECL|macro|IDE_STATUS_REG
mdefine_line|#define IDE_STATUS_REG&t;&t;(HWIF(drive)-&gt;io_base+7)
DECL|macro|IDE_CONTROL_REG
mdefine_line|#define IDE_CONTROL_REG&t;&t;(HWIF(drive)-&gt;ctl_port)
DECL|macro|IDE_FEATURE_REG
mdefine_line|#define IDE_FEATURE_REG&t;&t;IDE_ERROR_REG
DECL|macro|IDE_COMMAND_REG
mdefine_line|#define IDE_COMMAND_REG&t;&t;IDE_STATUS_REG
DECL|macro|IDE_ALTSTATUS_REG
mdefine_line|#define IDE_ALTSTATUS_REG&t;IDE_CONTROL_REG
macro_line|#ifdef REALLY_FAST_IO
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)&t;&t;outb((b),p)
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)&t;&t;(byte)inb(p)
macro_line|#else
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)&t;&t;outb_p((b),p)
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)&t;&t;(byte)inb_p(p)
macro_line|#endif /* REALLY_FAST_IO */
DECL|macro|GET_ERR
mdefine_line|#define GET_ERR()&t;&t;IN_BYTE(IDE_ERROR_REG)
DECL|macro|GET_STAT
mdefine_line|#define GET_STAT()&t;&t;IN_BYTE(IDE_STATUS_REG)
DECL|macro|OK_STAT
mdefine_line|#define OK_STAT(stat,good,bad)&t;(((stat)&amp;((good)|(bad)))==(good))
DECL|macro|BAD_R_STAT
mdefine_line|#define BAD_R_STAT&t;&t;(BUSY_STAT   | ERR_STAT)
DECL|macro|BAD_W_STAT
mdefine_line|#define BAD_W_STAT&t;&t;(BAD_R_STAT  | WRERR_STAT)
DECL|macro|BAD_STAT
mdefine_line|#define BAD_STAT&t;&t;(BAD_R_STAT  | DRQ_STAT)
DECL|macro|DRIVE_READY
mdefine_line|#define DRIVE_READY&t;&t;(READY_STAT  | SEEK_STAT)
DECL|macro|DATA_READY
mdefine_line|#define DATA_READY&t;&t;(DRIVE_READY | DRQ_STAT)
multiline_comment|/*&n; * Some more useful definitions&n; */
DECL|macro|IDE_MAJOR_NAME
mdefine_line|#define IDE_MAJOR_NAME&t;&quot;ide&quot;&t;/* the same for all i/f; see also genhd.c */
DECL|macro|MAJOR_NAME
mdefine_line|#define MAJOR_NAME&t;IDE_MAJOR_NAME
DECL|macro|PARTN_BITS
mdefine_line|#define PARTN_BITS&t;6&t;/* number of minor dev bits for partitions */
DECL|macro|PARTN_MASK
mdefine_line|#define PARTN_MASK&t;((1&lt;&lt;PARTN_BITS)-1)&t;/* a useful bit mask */
DECL|macro|MAX_DRIVES
mdefine_line|#define MAX_DRIVES&t;2&t;/* per interface; 2 assumed by lots of code */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4&t;/* an arbitrary, but realistic limit */
DECL|macro|SECTOR_WORDS
mdefine_line|#define SECTOR_WORDS&t;(512 / 4)&t;/* number of 32bit words per sector */
multiline_comment|/*&n; * Timeouts for various operations:&n; */
DECL|macro|WAIT_DRQ
mdefine_line|#define WAIT_DRQ&t;(5*HZ/100)&t;/* 50msec - spec allows up to 20ms */
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(3*HZ/100)&t;/* 30msec - should be instantaneous */
DECL|macro|WAIT_PIDENTIFY
mdefine_line|#define WAIT_PIDENTIFY&t;(1*HZ)&t;/* 1sec   - should be less than 3ms (?) */
DECL|macro|WAIT_WORSTCASE
mdefine_line|#define WAIT_WORSTCASE&t;(30*HZ)&t;/* 30sec  - worst case when spinning up */
DECL|macro|WAIT_CMD
mdefine_line|#define WAIT_CMD&t;(10*HZ)&t;/* 10sec  - maximum wait for an IRQ to happen */
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
DECL|struct|atapi_request_sense
r_struct
id|atapi_request_sense
(brace
DECL|member|error_code
r_int
r_char
id|error_code
suffix:colon
l_int|7
suffix:semicolon
DECL|member|valid
r_int
r_char
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|byte
id|reserved1
suffix:semicolon
DECL|member|sense_key
r_int
r_char
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ili
r_int
r_char
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
DECL|member|info
id|byte
id|info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|sense_len
id|byte
id|sense_len
suffix:semicolon
DECL|member|command_info
id|byte
id|command_info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|asc
id|byte
id|asc
suffix:semicolon
DECL|member|ascq
id|byte
id|ascq
suffix:semicolon
DECL|member|fru
id|byte
id|fru
suffix:semicolon
DECL|member|sense_key_specific
id|byte
id|sense_key_specific
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|packet_command
r_struct
id|packet_command
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|sense_data
r_struct
id|atapi_request_sense
op_star
id|sense_data
suffix:semicolon
DECL|member|c
r_int
r_char
id|c
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Space to hold the disk TOC. */
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS 99
DECL|struct|atapi_toc_header
r_struct
id|atapi_toc_header
(brace
DECL|member|toc_length
r_int
r_int
id|toc_length
suffix:semicolon
DECL|member|first_track
id|byte
id|first_track
suffix:semicolon
DECL|member|last_track
id|byte
id|last_track
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc_entry
r_struct
id|atapi_toc_entry
(brace
DECL|member|reserved1
id|byte
id|reserved1
suffix:semicolon
DECL|member|control
r_int
id|control
suffix:colon
l_int|4
suffix:semicolon
DECL|member|adr
r_int
id|adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|track
id|byte
id|track
suffix:semicolon
DECL|member|reserved2
id|byte
id|reserved2
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc
r_struct
id|atapi_toc
(brace
DECL|member|last_session_lba
r_int
id|last_session_lba
suffix:semicolon
DECL|member|xa_flag
r_int
id|xa_flag
suffix:semicolon
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
DECL|member|hdr
r_struct
id|atapi_toc_header
id|hdr
suffix:semicolon
DECL|member|ent
r_struct
id|atapi_toc_entry
id|ent
(braket
id|MAX_TRACKS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* One extra for the leadout. */
)brace
suffix:semicolon
multiline_comment|/* Extra per-device info for cdrom drives. */
DECL|struct|cdrom_info
r_struct
id|cdrom_info
(brace
multiline_comment|/* Buffer for table of contents.  NULL if we haven&squot;t allocated&n;     a TOC buffer for this device yet. */
DECL|member|toc
r_struct
id|atapi_toc
op_star
id|toc
suffix:semicolon
multiline_comment|/* Sector buffer.  If a read request wants only the first part of a cdrom&n;     block, we cache the rest of the block here, in the expectation that that&n;     data is going to be wanted soon.  SECTOR_BUFFERED is the number of the&n;     first buffered sector, and NSECTORS_BUFFERED is the number of sectors&n;     in the buffer.  Before the buffer is allocated, we should have&n;     SECTOR_BUFFER == NULL and NSECTORS_BUFFERED == 0. */
DECL|member|sector_buffered
r_int
r_int
id|sector_buffered
suffix:semicolon
DECL|member|nsectors_buffered
r_int
r_int
id|nsectors_buffered
suffix:semicolon
DECL|member|sector_buffer
r_char
op_star
id|sector_buffer
suffix:semicolon
multiline_comment|/* The result of the last successful request sense command&n;     on this device. */
DECL|member|sense_data
r_struct
id|atapi_request_sense
id|sense_data
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
multiline_comment|/*&n; * Now for the data we need to maintain per-drive:  ide_drive_t&n; */
DECL|enumerator|disk
DECL|enumerator|cdrom
DECL|typedef|media_t
r_typedef
r_enum
(brace
id|disk
comma
id|cdrom
)brace
id|media_t
suffix:semicolon
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|set_geometry
r_int
id|set_geometry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* respecify drive geometry */
DECL|member|recalibrate
r_int
id|recalibrate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* seek to cyl 0      */
DECL|member|set_multmode
r_int
id|set_multmode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set multmode count */
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* unused */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|special_t
)brace
id|special_t
suffix:semicolon
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|struct|ide_drive_s
r_typedef
r_struct
id|ide_drive_s
(brace
DECL|member|special
id|special_t
id|special
suffix:semicolon
multiline_comment|/* special action flags */
DECL|member|present
r_int
id|present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive is physically present */
DECL|member|noprobe
r_int
id|noprobe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* from:  hdx=noprobe */
DECL|member|keep_settings
r_int
id|keep_settings
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* restore settings after drive reset */
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* currently doing revalidate_disk() */
DECL|member|vlb_32bit
r_int
id|vlb_32bit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* use 32bit in/out for data */
DECL|member|vlb_sync
r_int
id|vlb_sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* needed for some 32bit chip sets */
DECL|member|removeable
r_int
id|removeable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 if need to do check_media_change */
DECL|member|using_dma
r_int
id|using_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disk is using dma for read/write */
DECL|member|unmask
r_int
id|unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: okay to unmask other irqs */
DECL|member|media
id|media_t
id|media
suffix:semicolon
multiline_comment|/* disk, cdrom, tape */
DECL|member|select
id|select_t
id|select
suffix:semicolon
multiline_comment|/* basic drive/head select reg value */
DECL|member|hwif
r_void
op_star
id|hwif
suffix:semicolon
multiline_comment|/* actually (ide_hwif_t *) */
DECL|member|ctl
id|byte
id|ctl
suffix:semicolon
multiline_comment|/* &quot;normal&quot; value for IDE_CONTROL_REG */
DECL|member|ready_stat
id|byte
id|ready_stat
suffix:semicolon
multiline_comment|/* min status value for drive ready */
DECL|member|mult_count
id|byte
id|mult_count
suffix:semicolon
multiline_comment|/* current multiple sector setting */
DECL|member|mult_req
id|byte
id|mult_req
suffix:semicolon
multiline_comment|/* requested multiple sector setting */
DECL|member|chipset
id|byte
id|chipset
suffix:semicolon
multiline_comment|/* interface chipset access method */
DECL|member|bad_wstat
id|byte
id|bad_wstat
suffix:semicolon
multiline_comment|/* used for ignoring WRERR_STAT */
DECL|member|sect0
id|byte
id|sect0
suffix:semicolon
multiline_comment|/* offset of first sector for DM6:DDO */
DECL|member|usage
id|byte
id|usage
suffix:semicolon
multiline_comment|/* current &quot;open()&quot; count for drive */
DECL|member|head
id|byte
id|head
suffix:semicolon
multiline_comment|/* &quot;real&quot; number of heads */
DECL|member|sect
id|byte
id|sect
suffix:semicolon
multiline_comment|/* &quot;real&quot; sectors per track */
DECL|member|bios_head
id|byte
id|bios_head
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO number of heads */
DECL|member|bios_sect
id|byte
id|bios_sect
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO sectors per track */
DECL|member|bios_cyl
r_int
r_int
id|bios_cyl
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO number of cyls */
DECL|member|cyl
r_int
r_int
id|cyl
suffix:semicolon
multiline_comment|/* &quot;real&quot; number of cyls */
DECL|member|wqueue
r_struct
id|wait_queue
op_star
id|wqueue
suffix:semicolon
multiline_comment|/* used to wait for drive in open() */
DECL|member|id
r_struct
id|hd_driveid
op_star
id|id
suffix:semicolon
multiline_comment|/* drive model identification info */
DECL|member|part
r_struct
id|hd_struct
op_star
id|part
suffix:semicolon
multiline_comment|/* drive partition table */
DECL|member|name
r_char
id|name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* drive name, such as &quot;hda&quot; */
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
DECL|member|cdrom_info
r_struct
id|cdrom_info
id|cdrom_info
suffix:semicolon
multiline_comment|/* from ide-cd.c */
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
DECL|typedef|ide_drive_t
)brace
id|ide_drive_t
suffix:semicolon
multiline_comment|/*&n; * An ide_dmaproc_t() initiates/aborts DMA read/write operations on a drive.&n; *&n; * The caller is assumed to have selected the drive and programmed the drive&squot;s&n; * sector address using CHS or LBA.  All that remains is to prepare for DMA&n; * and then issue the actual read/write DMA/PIO command to the drive.&n; *&n; * Returns 0 if all went well.&n; * Returns 1 if DMA read/write could not be started, in which case the caller&n; * should either try again later, or revert to PIO for the current request.&n; */
DECL|enumerator|ide_dma_read
DECL|enumerator|ide_dma_write
DECL|enumerator|ide_dma_abort
DECL|enumerator|ide_dma_check
DECL|typedef|ide_dma_action_t
r_typedef
r_enum
(brace
id|ide_dma_read
op_assign
l_int|0
comma
id|ide_dma_write
op_assign
l_int|1
comma
id|ide_dma_abort
op_assign
l_int|2
comma
id|ide_dma_check
op_assign
l_int|3
)brace
id|ide_dma_action_t
suffix:semicolon
DECL|typedef|ide_dmaproc_t
r_typedef
r_int
(paren
id|ide_dmaproc_t
)paren
(paren
id|ide_dma_action_t
comma
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|struct|hwif_s
r_typedef
r_struct
id|hwif_s
(brace
DECL|member|next
r_struct
id|hwif_s
op_star
id|next
suffix:semicolon
multiline_comment|/* for linked-list in ide_hwgroup_t */
DECL|member|hwgroup
r_void
op_star
id|hwgroup
suffix:semicolon
multiline_comment|/* actually (ide_hwgroup_t *) */
DECL|member|io_base
r_int
r_int
id|io_base
suffix:semicolon
multiline_comment|/* base io port addr */
DECL|member|ctl_port
r_int
r_int
id|ctl_port
suffix:semicolon
multiline_comment|/* usually io_base+0x206 */
DECL|member|drives
id|ide_drive_t
id|drives
(braket
id|MAX_DRIVES
)braket
suffix:semicolon
multiline_comment|/* drive info */
DECL|member|gd
r_struct
id|gendisk
op_star
id|gd
suffix:semicolon
multiline_comment|/* gendisk structure */
DECL|member|dmaproc
id|ide_dmaproc_t
op_star
id|dmaproc
suffix:semicolon
multiline_comment|/* dma read/write/abort routine */
DECL|member|dmatable
r_int
r_int
op_star
id|dmatable
suffix:semicolon
multiline_comment|/* dma physical region descriptor table */
DECL|member|dma_base
r_int
r_int
id|dma_base
suffix:semicolon
multiline_comment|/* base addr for dma ports (triton) */
DECL|member|irq
id|byte
id|irq
suffix:semicolon
multiline_comment|/* our irq number */
DECL|member|major
id|byte
id|major
suffix:semicolon
multiline_comment|/* our major number */
DECL|member|select
id|byte
id|select
suffix:semicolon
multiline_comment|/* pri/sec hwif select for ht6560b */
DECL|member|name
r_char
id|name
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* name of interface, eg. &quot;ide0&quot; */
DECL|member|noprobe
r_int
id|noprobe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t probe for this interface */
DECL|member|present
r_int
id|present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* this interface exists */
macro_line|#if (DISK_RECOVERY_TIME &gt; 0)
DECL|member|last_time
r_int
r_int
id|last_time
suffix:semicolon
multiline_comment|/* time when previous rq was done */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
DECL|member|request_sense_request
r_struct
id|request
id|request_sense_request
suffix:semicolon
multiline_comment|/* from ide-cd.c */
DECL|member|request_sense_pc
r_struct
id|packet_command
id|request_sense_pc
suffix:semicolon
multiline_comment|/* from ide-cd.c */
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
DECL|typedef|ide_hwif_t
)brace
id|ide_hwif_t
suffix:semicolon
multiline_comment|/*&n; *  internal ide interrupt handler type&n; */
DECL|typedef|ide_handler_t
r_typedef
r_void
(paren
id|ide_handler_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|struct|hwgroup_s
r_typedef
r_struct
id|hwgroup_s
(brace
DECL|member|handler
id|ide_handler_t
op_star
id|handler
suffix:semicolon
multiline_comment|/* irq handler, if active */
DECL|member|drive
id|ide_drive_t
op_star
id|drive
suffix:semicolon
multiline_comment|/* current drive */
DECL|member|hwif
id|ide_hwif_t
op_star
id|hwif
suffix:semicolon
multiline_comment|/* ptr to current hwif in linked-list */
DECL|member|rq
r_struct
id|request
op_star
id|rq
suffix:semicolon
multiline_comment|/* current request */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* failsafe timer */
DECL|member|wrq
r_struct
id|request
id|wrq
suffix:semicolon
multiline_comment|/* local copy of current write rq */
DECL|member|reset_timeout
r_int
r_int
id|reset_timeout
suffix:semicolon
multiline_comment|/* timeout value during ide resets */
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
DECL|member|doing_atapi_reset
r_int
id|doing_atapi_reset
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
DECL|typedef|ide_hwgroup_t
)brace
id|ide_hwgroup_t
suffix:semicolon
multiline_comment|/*&n; * One final include file, which references some of the data/defns from above&n; */
DECL|macro|IDE_DRIVER
mdefine_line|#define IDE_DRIVER&t;/* &quot;parameter&quot; for blk.h */
macro_line|#include &quot;blk.h&quot;
macro_line|#if (DISK_RECOVERY_TIME &gt; 0)
r_void
id|ide_set_recovery_timer
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|macro|SET_RECOVERY_TIMER
mdefine_line|#define SET_RECOVERY_TIMER(drive) ide_set_recovery_timer (drive)
macro_line|#else
DECL|macro|SET_RECOVERY_TIMER
mdefine_line|#define SET_RECOVERY_TIMER(drive)
macro_line|#endif
multiline_comment|/*&n; * The main (re-)entry point for handling a new request is IDE_DO_REQUEST.&n; * Note that IDE_DO_REQUEST should *only* ever be invoked from an interrupt&n; * handler.  All others, such as a timer expiry handler, should call&n; * do_hwgroup_request() instead (currently local to ide.c).&n; */
r_void
id|ide_do_request
(paren
id|ide_hwgroup_t
op_star
)paren
suffix:semicolon
DECL|macro|IDE_DO_REQUEST
mdefine_line|#define IDE_DO_REQUEST { SET_RECOVERY_TIMER(HWIF(drive)); ide_do_request(HWGROUP(drive)); }
multiline_comment|/*&n; * This is used for (nearly) all data transfers from the IDE interface&n; */
r_void
id|ide_input_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used for (nearly) all data transfers to the IDE interface&n; */
r_void
id|ide_output_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used on exit from the driver, to designate the next irq handler&n; * and also to start the safety timer.&n; */
r_void
id|ide_set_handler
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_handler_t
op_star
id|handler
)paren
suffix:semicolon
multiline_comment|/*&n; * Error reporting, in human readable form (luxurious, but a memory hog).&n; */
id|byte
id|ide_dump_status
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|msg
comma
id|byte
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_error() takes action based on the error returned by the controller.&n; *&n; * Returns 1 if an ide reset operation has been initiated, in which case&n; * the caller MUST simply return from the driver (through however many levels).&n; * Returns 0 otherwise.&n; */
r_int
id|ide_error
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|msg
comma
id|byte
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine busy-waits for the drive status to be not &quot;busy&quot;.&n; * It then checks the status for all of the &quot;good&quot; bits and none&n; * of the &quot;bad&quot; bits, and if all is okay it returns 0.  All other&n; * cases return 1 after invoking ide_error()&n; *&n; */
r_int
id|ide_wait_stat
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|good
comma
id|byte
id|bad
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/*&n; * This is called from genhd.c to correct DiskManager/EZ-Drive geometries&n; */
r_int
id|ide_xlate_1024
c_func
(paren
id|dev_t
comma
r_int
comma
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Start a reset operation for an IDE interface.&n; * Returns 0 if the reset operation is still in progress,&n; *  in which case the drive MUST return, to await completion.&n; * Returns 1 if the reset is complete (success or failure).&n; */
r_int
id|ide_do_reset
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_alloc(): memory allocation for use *only* during driver initialization.&n; * If &quot;within_area&quot; is non-zero, the memory will be allocated such that&n; * it lies entirely within a &quot;within_area&quot; sized area (eg. 4096).  This is&n; * needed for DMA stuff.  &quot;within_area&quot; must be a power of two (not validated).&n; * All allocations are longword aligned.&n; */
r_void
op_star
id|ide_alloc
(paren
r_int
r_int
id|bytecount
comma
r_int
r_int
id|within_area
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
multiline_comment|/*&n; * These are routines in ide-cd.c invoked from ide.c&n; */
r_void
id|ide_do_rw_cdrom
(paren
id|ide_drive_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|ide_cdrom_ioctl
(paren
id|ide_drive_t
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|ide_cdrom_check_media_change
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
r_int
id|ide_cdrom_open
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|ide_drive_t
op_star
)paren
suffix:semicolon
r_void
id|ide_cdrom_release
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|ide_drive_t
op_star
)paren
suffix:semicolon
r_void
id|ide_cdrom_setup
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
macro_line|#ifdef CONFIG_BLK_DEV_TRITON
r_void
id|ide_init_triton
(paren
id|byte
comma
id|byte
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_TRITON */
eof
