macro_line|#ifndef _IDE_H
DECL|macro|_IDE_H
mdefine_line|#define _IDE_H
multiline_comment|/*&n; *  linux/drivers/block/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ide.h&gt;
multiline_comment|/*&n; * This is the multiple IDE interface driver, as evolved from hd.c.  &n; * It supports up to four IDE interfaces, on one or more IRQs (usually 14 &amp; 15).&n; * There can be up to two drives per interface, as per the ATA-2 spec.&n; *&n; * Primary i/f:    ide0: major=3;  (hda)         minor=0; (hdb)         minor=64&n; * Secondary i/f:  ide1: major=22; (hdc or hd1a) minor=0; (hdd or hd1b) minor=64&n; * Tertiary i/f:   ide2: major=33; (hde)         minor=0; (hdf)         minor=64&n; * Quaternary i/f: ide3: major=34; (hdg)         minor=0; (hdh)         minor=64&n; */
multiline_comment|/******************************************************************************&n; * IDE driver configuration options (play with these as desired):&n; * &n; * REALLY_SLOW_IO can be defined in ide.c and ide-cd.c, if necessary&n; */
DECL|macro|REALLY_FAST_IO
macro_line|#undef REALLY_FAST_IO&t;&t;&t;/* define if ide ports are perfect */
DECL|macro|INITIAL_MULT_COUNT
mdefine_line|#define INITIAL_MULT_COUNT&t;0&t;/* off=0; on=2,4,8,16,32, etc.. */
macro_line|#ifndef SUPPORT_SLOW_DATA_PORTS&t;&t;/* 1 to support slow data ports */
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef SUPPORT_VLB_SYNC&t;&t;/* 1 to support weird 32-bit chips */
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef DISK_RECOVERY_TIME&t;&t;/* off=0; on=access_delay_time */
DECL|macro|DISK_RECOVERY_TIME
mdefine_line|#define DISK_RECOVERY_TIME&t;0&t;/*  for hardware that needs it */
macro_line|#endif
macro_line|#ifndef OK_TO_RESET_CONTROLLER&t;&t;/* 1 needed for good error recovery */
DECL|macro|OK_TO_RESET_CONTROLLER
mdefine_line|#define OK_TO_RESET_CONTROLLER&t;1&t;/* 0 for use with AH2372A/B interface */
macro_line|#endif
macro_line|#ifndef FAKE_FDISK_FOR_EZDRIVE&t;&t;/* 1 to help linux fdisk with EZDRIVE */
DECL|macro|FAKE_FDISK_FOR_EZDRIVE
mdefine_line|#define FAKE_FDISK_FOR_EZDRIVE &t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef FANCY_STATUS_DUMPS&t;&t;/* 1 for human-readable drive errors */
DECL|macro|FANCY_STATUS_DUMPS
mdefine_line|#define FANCY_STATUS_DUMPS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_CMD640
macro_line|#if 0&t;/* change to 1 when debugging cmd640 problems */
r_void
id|cmd640_dump_regs
(paren
r_void
)paren
suffix:semicolon
mdefine_line|#define CMD640_DUMP_REGS cmd640_dump_regs() /* for debugging cmd640 chipset */
macro_line|#endif
macro_line|#endif  /* CONFIG_BLK_DEV_CMD640 */
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
DECL|macro|HWIF
mdefine_line|#define HWIF(drive)&t;&t;((ide_hwif_t *)((drive)-&gt;hwif))
DECL|macro|HWGROUP
mdefine_line|#define HWGROUP(drive)&t;&t;((ide_hwgroup_t *)(HWIF(drive)-&gt;hwgroup))
multiline_comment|/*&n; * Definitions for accessing IDE controller registers&n; */
DECL|macro|IDE_NR_PORTS
mdefine_line|#define IDE_NR_PORTS&t;&t;(10)
DECL|macro|IDE_DATA_OFFSET
mdefine_line|#define IDE_DATA_OFFSET&t;&t;(0)
DECL|macro|IDE_ERROR_OFFSET
mdefine_line|#define IDE_ERROR_OFFSET&t;(1)
DECL|macro|IDE_NSECTOR_OFFSET
mdefine_line|#define IDE_NSECTOR_OFFSET&t;(2)
DECL|macro|IDE_SECTOR_OFFSET
mdefine_line|#define IDE_SECTOR_OFFSET&t;(3)
DECL|macro|IDE_LCYL_OFFSET
mdefine_line|#define IDE_LCYL_OFFSET&t;&t;(4)
DECL|macro|IDE_HCYL_OFFSET
mdefine_line|#define IDE_HCYL_OFFSET&t;&t;(5)
DECL|macro|IDE_SELECT_OFFSET
mdefine_line|#define IDE_SELECT_OFFSET&t;(6)
DECL|macro|IDE_STATUS_OFFSET
mdefine_line|#define IDE_STATUS_OFFSET&t;(7)
DECL|macro|IDE_CONTROL_OFFSET
mdefine_line|#define IDE_CONTROL_OFFSET&t;(8)
DECL|macro|IDE_IRQ_OFFSET
mdefine_line|#define IDE_IRQ_OFFSET&t;&t;(9)
DECL|macro|IDE_FEATURE_OFFSET
mdefine_line|#define IDE_FEATURE_OFFSET&t;IDE_ERROR_OFFSET
DECL|macro|IDE_COMMAND_OFFSET
mdefine_line|#define IDE_COMMAND_OFFSET&t;IDE_STATUS_OFFSET
DECL|macro|IDE_DATA_REG
mdefine_line|#define IDE_DATA_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_DATA_OFFSET])
DECL|macro|IDE_ERROR_REG
mdefine_line|#define IDE_ERROR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_ERROR_OFFSET])
DECL|macro|IDE_NSECTOR_REG
mdefine_line|#define IDE_NSECTOR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_NSECTOR_OFFSET])
DECL|macro|IDE_SECTOR_REG
mdefine_line|#define IDE_SECTOR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_SECTOR_OFFSET])
DECL|macro|IDE_LCYL_REG
mdefine_line|#define IDE_LCYL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_LCYL_OFFSET])
DECL|macro|IDE_HCYL_REG
mdefine_line|#define IDE_HCYL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_HCYL_OFFSET])
DECL|macro|IDE_SELECT_REG
mdefine_line|#define IDE_SELECT_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_SELECT_OFFSET])
DECL|macro|IDE_STATUS_REG
mdefine_line|#define IDE_STATUS_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_STATUS_OFFSET])
DECL|macro|IDE_CONTROL_REG
mdefine_line|#define IDE_CONTROL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_CONTROL_OFFSET])
DECL|macro|IDE_IRQ_REG
mdefine_line|#define IDE_IRQ_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_IRQ_OFFSET])
DECL|macro|IDE_FEATURE_REG
mdefine_line|#define IDE_FEATURE_REG&t;&t;IDE_ERROR_REG
DECL|macro|IDE_COMMAND_REG
mdefine_line|#define IDE_COMMAND_REG&t;&t;IDE_STATUS_REG
DECL|macro|IDE_ALTSTATUS_REG
mdefine_line|#define IDE_ALTSTATUS_REG&t;IDE_CONTROL_REG
DECL|macro|IDE_IREASON_REG
mdefine_line|#define IDE_IREASON_REG&t;&t;IDE_NSECTOR_REG
DECL|macro|IDE_BCOUNTL_REG
mdefine_line|#define IDE_BCOUNTL_REG&t;&t;IDE_LCYL_REG
DECL|macro|IDE_BCOUNTH_REG
mdefine_line|#define IDE_BCOUNTH_REG&t;&t;IDE_HCYL_REG
macro_line|#ifdef REALLY_FAST_IO
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)&t;&t;outb((b),(p))
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)&t;&t;(byte)inb(p)
macro_line|#else
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)&t;&t;outb_p((b),(p))
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
DECL|macro|SECTOR_WORDS
mdefine_line|#define SECTOR_WORDS&t;(512 / 4)&t;/* number of 32bit words per sector */
DECL|macro|IDE_LARGE_SEEK
mdefine_line|#define IDE_LARGE_SEEK(b1,b2,t)&t;(((b1) &gt; (b2) + (t)) || ((b2) &gt; (b1) + (t)))
DECL|macro|IDE_MIN
mdefine_line|#define IDE_MIN(a,b)&t;((a)&lt;(b) ? (a):(b))
DECL|macro|IDE_MAX
mdefine_line|#define IDE_MAX(a,b)&t;((a)&gt;(b) ? (a):(b))
multiline_comment|/*&n; * Timeouts for various operations:&n; */
DECL|macro|WAIT_DRQ
mdefine_line|#define WAIT_DRQ&t;(5*HZ/100)&t;/* 50msec - spec allows up to 20ms */
macro_line|#ifdef CONFIG_APM
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(5*HZ)&t;&t;/* 5sec - some laptops are very slow */
macro_line|#else
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(3*HZ/100)&t;/* 30msec - should be instantaneous */
macro_line|#endif /* CONFIG_APM */
DECL|macro|WAIT_PIDENTIFY
mdefine_line|#define WAIT_PIDENTIFY&t;(1*HZ)&t;/* 1sec   - should be less than 3ms (?) */
DECL|macro|WAIT_WORSTCASE
mdefine_line|#define WAIT_WORSTCASE&t;(30*HZ)&t;/* 30sec  - worst case when spinning up */
DECL|macro|WAIT_CMD
mdefine_line|#define WAIT_CMD&t;(10*HZ)&t;/* 10sec  - maximum wait for an IRQ to happen */
DECL|macro|WAIT_MIN_SLEEP
mdefine_line|#define WAIT_MIN_SLEEP&t;(2*HZ/100)&t;/* 20msec - minimum sleep time */
macro_line|#if defined(CONFIG_BLK_DEV_HT6560B) || defined(CONFIG_BLK_DEV_PROMISE)
DECL|macro|SELECT_DRIVE
mdefine_line|#define SELECT_DRIVE(hwif,drive)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;selectproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;selectproc(drive);&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;OUT_BYTE((drive)-&gt;select.all, hwif-&gt;io_ports[IDE_SELECT_OFFSET]); &bslash;&n;}
macro_line|#else
DECL|macro|SELECT_DRIVE
mdefine_line|#define SELECT_DRIVE(hwif,drive)  OUT_BYTE((drive)-&gt;select.all, hwif-&gt;io_ports[IDE_SELECT_OFFSET]);
macro_line|#endif&t;/* CONFIG_BLK_DEV_HT6560B || CONFIG_BLK_DEV_PROMISE */
multiline_comment|/*&n; * Now for the data we need to maintain per-drive:  ide_drive_t&n; */
DECL|macro|ide_scsi
mdefine_line|#define ide_scsi&t;0x21
DECL|macro|ide_disk
mdefine_line|#define ide_disk&t;0x20
DECL|macro|ide_cdrom
mdefine_line|#define ide_cdrom&t;0x5
DECL|macro|ide_tape
mdefine_line|#define ide_tape&t;0x1
DECL|macro|ide_floppy
mdefine_line|#define ide_floppy&t;0x0
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
DECL|member|set_tune
r_int
id|set_tune
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tune interface for drive */
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|4
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
DECL|struct|ide_drive_s
r_typedef
r_struct
id|ide_drive_s
(brace
DECL|member|queue
r_struct
id|request
op_star
id|queue
suffix:semicolon
multiline_comment|/* request queue */
DECL|member|next
r_struct
id|ide_drive_s
op_star
id|next
suffix:semicolon
multiline_comment|/* circular list of hwgroup drives */
DECL|member|sleep
r_int
r_int
id|sleep
suffix:semicolon
multiline_comment|/* sleep until this time */
DECL|member|service_start
r_int
r_int
id|service_start
suffix:semicolon
multiline_comment|/* time we started last request */
DECL|member|service_time
r_int
r_int
id|service_time
suffix:semicolon
multiline_comment|/* service time of last request */
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
DECL|member|removable
r_int
id|removable
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
DECL|member|forced_geom
r_int
id|forced_geom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 if hdx=c,h,s was given at boot */
DECL|member|unmask
r_int
id|unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: okay to unmask other irqs */
DECL|member|no_unmask
r_int
id|no_unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow setting unmask bit */
DECL|member|no_io_32bit
r_int
id|no_io_32bit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow enabling 32bit I/O */
DECL|member|nobios
r_int
id|nobios
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: do not probe bios for drive */
DECL|member|slow
r_int
id|slow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: slow data port */
DECL|member|autotune
r_int
id|autotune
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 1=autotune, 2=noautotune, 0=default */
DECL|member|revalidate
r_int
id|revalidate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* request revalidation */
DECL|member|bswap
r_int
id|bswap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: byte swap data */
DECL|member|dsc_overlap
r_int
id|dsc_overlap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: DSC overlap */
DECL|member|atapi_overlap
r_int
id|atapi_overlap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: ATAPI overlap (not supported) */
DECL|member|nice0
r_int
id|nice0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: give obvious excess bandwidth */
DECL|member|nice1
r_int
id|nice1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: give potential excess bandwidth */
DECL|member|nice2
r_int
id|nice2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: give a share in our own bandwidth */
macro_line|#if FAKE_FDISK_FOR_EZDRIVE
DECL|member|remap_0_to_1
r_int
id|remap_0_to_1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: partitioned with ezdrive */
macro_line|#endif /* FAKE_FDISK_FOR_EZDRIVE */
DECL|member|media
id|byte
id|media
suffix:semicolon
multiline_comment|/* disk, cdrom, tape, floppy, ... */
DECL|member|select
id|select_t
id|select
suffix:semicolon
multiline_comment|/* basic drive/head select reg value */
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
DECL|member|tune_req
id|byte
id|tune_req
suffix:semicolon
multiline_comment|/* requested drive tuning setting */
DECL|member|io_32bit
id|byte
id|io_32bit
suffix:semicolon
multiline_comment|/* 0=16-bit, 1=32-bit, 2/3=32bit+sync */
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
DECL|member|hwif
r_void
op_star
id|hwif
suffix:semicolon
multiline_comment|/* actually (ide_hwif_t *) */
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
DECL|member|driver
r_void
op_star
id|driver
suffix:semicolon
multiline_comment|/* (ide_driver_t *) */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* extra driver data */
DECL|typedef|ide_drive_t
)brace
id|ide_drive_t
suffix:semicolon
multiline_comment|/*&n; * An ide_dmaproc_t() initiates/aborts DMA read/write operations on a drive.&n; *&n; * The caller is assumed to have selected the drive and programmed the drive&squot;s&n; * sector address using CHS or LBA.  All that remains is to prepare for DMA&n; * and then issue the actual read/write DMA/PIO command to the drive.&n; *&n; * Returns 0 if all went well.&n; * Returns 1 if DMA read/write could not be started, in which case the caller&n; * should either try again later, or revert to PIO for the current request.&n; */
DECL|enumerator|ide_dma_read
DECL|enumerator|ide_dma_write
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
DECL|enumerator|ide_dma_abort
DECL|enumerator|ide_dma_check
id|ide_dma_abort
op_assign
l_int|2
comma
id|ide_dma_check
op_assign
l_int|3
comma
DECL|enumerator|ide_dma_status_bad
DECL|enumerator|ide_dma_transferred
id|ide_dma_status_bad
op_assign
l_int|4
comma
id|ide_dma_transferred
op_assign
l_int|5
comma
DECL|enumerator|ide_dma_begin
DECL|enumerator|ide_dma_on
id|ide_dma_begin
op_assign
l_int|6
comma
id|ide_dma_on
op_assign
l_int|7
comma
DECL|enumerator|ide_dma_off
id|ide_dma_off
op_assign
l_int|8
)brace
DECL|typedef|ide_dma_action_t
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
multiline_comment|/*&n; * An ide_tuneproc_t() is used to set the speed of an IDE interface&n; * to a particular PIO mode.  The &quot;byte&quot; parameter is used&n; * to select the PIO mode by number (0,1,2,3,4,5), and a value of 255&n; * indicates that the interface driver should &quot;auto-tune&quot; the PIO mode&n; * according to the drive capabilities in drive-&gt;id;&n; *&n; * Not all interface types support tuning, and not all of those&n; * support all possible PIO settings.  They may silently ignore&n; * or round values as they see fit.&n; */
DECL|typedef|ide_tuneproc_t
r_typedef
r_void
(paren
id|ide_tuneproc_t
)paren
(paren
id|ide_drive_t
op_star
comma
id|byte
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used to provide HT6560B &amp; PROMISE interface support.&n; */
DECL|typedef|ide_selectproc_t
r_typedef
r_void
(paren
id|ide_selectproc_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * hwif_chipset_t is used to keep track of the specific hardware&n; * chipset used by each IDE interface, if known.&n; */
DECL|enumerator|ide_unknown
DECL|enumerator|ide_generic
DECL|enumerator|ide_triton
r_typedef
r_enum
(brace
id|ide_unknown
comma
id|ide_generic
comma
id|ide_triton
comma
DECL|enumerator|ide_cmd640
DECL|enumerator|ide_dtc2278
DECL|enumerator|ide_ali14xx
id|ide_cmd640
comma
id|ide_dtc2278
comma
id|ide_ali14xx
comma
DECL|enumerator|ide_qd6580
DECL|enumerator|ide_umc8672
DECL|enumerator|ide_ht6560b
id|ide_qd6580
comma
id|ide_umc8672
comma
id|ide_ht6560b
comma
DECL|enumerator|ide_promise
id|ide_promise
)brace
DECL|typedef|hwif_chipset_t
id|hwif_chipset_t
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
DECL|member|io_ports
id|ide_ioreg_t
id|io_ports
(braket
id|IDE_NR_PORTS
)braket
suffix:semicolon
multiline_comment|/* task file registers */
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
DECL|member|tuneproc
id|ide_tuneproc_t
op_star
id|tuneproc
suffix:semicolon
multiline_comment|/* routine to tune PIO mode for drives */
macro_line|#if defined(CONFIG_BLK_DEV_HT6560B) || defined(CONFIG_BLK_DEV_PROMISE)
DECL|member|selectproc
id|ide_selectproc_t
op_star
id|selectproc
suffix:semicolon
multiline_comment|/* tweaks hardware to select drive */
macro_line|#endif
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
r_int
id|irq
suffix:semicolon
multiline_comment|/* our irq number */
DECL|member|major
id|byte
id|major
suffix:semicolon
multiline_comment|/* our major number */
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* name of interface, eg. &quot;ide0&quot; */
DECL|member|index
id|byte
id|index
suffix:semicolon
multiline_comment|/* 0 for ide0; 1 for ide1; ... */
DECL|member|chipset
id|hwif_chipset_t
id|chipset
suffix:semicolon
multiline_comment|/* sub-module for tuning.. */
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
DECL|member|serialized
r_int
id|serialized
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* serialized operation with mate hwif */
DECL|member|sharing_irq
r_int
id|sharing_irq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 = sharing irq with another hwif */
macro_line|#ifdef CONFIG_BLK_DEV_PROMISE
DECL|member|is_promise2
r_int
id|is_promise2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2nd i/f on promise DC4030 */
macro_line|#endif /* CONFIG_BLK_DEV_PROMISE */
DECL|member|reset
r_int
id|reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reset after probe */
macro_line|#if (DISK_RECOVERY_TIME &gt; 0)
DECL|member|last_time
r_int
r_int
id|last_time
suffix:semicolon
multiline_comment|/* time when previous rq was done */
macro_line|#endif
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
DECL|member|poll_timeout
r_int
r_int
id|poll_timeout
suffix:semicolon
multiline_comment|/* timeout value during long polls */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* set when servicing requests */
DECL|typedef|ide_hwgroup_t
)brace
id|ide_hwgroup_t
suffix:semicolon
multiline_comment|/*&n; * Subdrivers support.&n; */
DECL|macro|IDE_SUBDRIVER_VERSION
mdefine_line|#define IDE_SUBDRIVER_VERSION&t;1
DECL|typedef|ide_cleanup_proc
r_typedef
r_int
(paren
id|ide_cleanup_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_do_request_proc
r_typedef
r_void
(paren
id|ide_do_request_proc
)paren
(paren
id|ide_drive_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ide_end_request_proc
r_typedef
r_void
(paren
id|ide_end_request_proc
)paren
(paren
id|byte
comma
id|ide_hwgroup_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_ioctl_proc
r_typedef
r_int
(paren
id|ide_ioctl_proc
)paren
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
DECL|typedef|ide_open_proc
r_typedef
r_int
(paren
id|ide_open_proc
)paren
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
DECL|typedef|ide_release_proc
r_typedef
r_void
(paren
id|ide_release_proc
)paren
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
DECL|typedef|ide_check_media_change_proc
r_typedef
r_int
(paren
id|ide_check_media_change_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_pre_reset_proc
r_typedef
r_void
(paren
id|ide_pre_reset_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_capacity_proc
r_typedef
r_int
r_int
(paren
id|ide_capacity_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_special_proc
r_typedef
r_void
(paren
id|ide_special_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|struct|ide_driver_s
r_typedef
r_struct
id|ide_driver_s
(brace
DECL|member|media
id|byte
id|media
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|supports_dma
r_int
id|supports_dma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|supports_dsc_overlap
r_int
id|supports_dsc_overlap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cleanup
id|ide_cleanup_proc
op_star
id|cleanup
suffix:semicolon
DECL|member|do_request
id|ide_do_request_proc
op_star
id|do_request
suffix:semicolon
DECL|member|end_request
id|ide_end_request_proc
op_star
id|end_request
suffix:semicolon
DECL|member|ioctl
id|ide_ioctl_proc
op_star
id|ioctl
suffix:semicolon
DECL|member|open
id|ide_open_proc
op_star
id|open
suffix:semicolon
DECL|member|release
id|ide_release_proc
op_star
id|release
suffix:semicolon
DECL|member|media_change
id|ide_check_media_change_proc
op_star
id|media_change
suffix:semicolon
DECL|member|pre_reset
id|ide_pre_reset_proc
op_star
id|pre_reset
suffix:semicolon
DECL|member|capacity
id|ide_capacity_proc
op_star
id|capacity
suffix:semicolon
DECL|member|special
id|ide_special_proc
op_star
id|special
suffix:semicolon
DECL|typedef|ide_driver_t
)brace
id|ide_driver_t
suffix:semicolon
DECL|macro|DRIVER
mdefine_line|#define DRIVER(drive)&t;&t;((ide_driver_t *)((drive)-&gt;driver))
multiline_comment|/*&n; * IDE modules.&n; */
DECL|macro|IDE_CHIPSET_MODULE
mdefine_line|#define IDE_CHIPSET_MODULE&t;&t;0&t;/* not supported yet */
DECL|macro|IDE_PROBE_MODULE
mdefine_line|#define IDE_PROBE_MODULE&t;&t;1
DECL|macro|IDE_DRIVER_MODULE
mdefine_line|#define IDE_DRIVER_MODULE&t;&t;2
DECL|typedef|ide_module_init_proc
r_typedef
r_int
(paren
id|ide_module_init_proc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|struct|ide_module_s
r_typedef
r_struct
id|ide_module_s
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|init
id|ide_module_init_proc
op_star
id|init
suffix:semicolon
DECL|member|next
r_struct
id|ide_module_s
op_star
id|next
suffix:semicolon
DECL|typedef|ide_module_t
)brace
id|ide_module_t
suffix:semicolon
multiline_comment|/*&n; * ide_hwifs[] is the master data structure used to keep track&n; * of just about everything in ide.c.  Whenever possible, routines&n; * should be using pointers to a drive (ide_drive_t *) or &n; * pointers to a hwif (ide_hwif_t *), rather than indexing this&n; * structure directly (the allocation/layout may change!).&n; *&n; */
macro_line|#ifndef _IDE_C
r_extern
id|ide_hwif_t
id|ide_hwifs
(braket
)braket
suffix:semicolon
multiline_comment|/* master data repository */
macro_line|#endif
multiline_comment|/*&n; * One final include file, which references some of the data/defns from above&n; */
DECL|macro|IDE_DRIVER
mdefine_line|#define IDE_DRIVER&t;/* &quot;parameter&quot; for blk.h */
macro_line|#include &lt;linux/blk.h&gt;
multiline_comment|/*&n; * This is used for (nearly) all data transfers from/to the IDE interface&n; */
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
multiline_comment|/*&n; * This is used for (nearly) all ATAPI data transfers from/to the IDE interface&n; */
r_void
id|atapi_input_bytes
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
id|bytecount
)paren
suffix:semicolon
r_void
id|atapi_output_bytes
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
id|bytecount
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
comma
r_int
r_int
id|timeout
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
multiline_comment|/*&n; * ide_error() takes action based on the error returned by the controller.&n; * The calling function must return afterwards, to restart the request.&n; */
r_void
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
multiline_comment|/*&n; * Issue a simple drive command&n; * The drive must be selected beforehand.&n; */
r_void
id|ide_cmd
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|cmd
comma
id|byte
id|nsect
comma
id|ide_handler_t
op_star
id|handler
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_fixstring() cleans up and (optionally) byte-swaps a text string,&n; * removing leading/trailing blanks and compressing internal blanks.&n; * It is primarily used to tidy up the model name/number fields as&n; * returned by the WIN_[P]IDENTIFY commands.&n; */
r_void
id|ide_fixstring
(paren
id|byte
op_star
id|s
comma
r_const
r_int
id|bytecount
comma
r_const
r_int
id|byteswap
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine busy-waits for the drive status to be not &quot;busy&quot;.&n; * It then checks the status for all of the &quot;good&quot; bits and none&n; * of the &quot;bad&quot; bits, and if all is okay it returns 0.  All other&n; * cases return 1 after invoking ide_error() -- caller should return.&n; *&n; */
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
multiline_comment|/*&n; * This routine is called from the partition-table code in genhd.c&n; * to &quot;convert&quot; a drive to a logical geometry with fewer than 1024 cyls.&n; *&n; * The second parameter, &quot;xparm&quot;, determines exactly how the translation&n; * will be handled:&n; *&t;&t; 0 = convert to CHS with fewer than 1024 cyls&n; *&t;&t;&t;using the same method as Ontrack DiskManager.&n; *&t;&t; 1 = same as &quot;0&quot;, plus offset everything by 63 sectors.&n; *&t;&t;-1 = similar to &quot;0&quot;, plus redirect sector 0 to sector 1.&n; *&t;&t;&gt;1 = convert to a CHS geometry with &quot;xparm&quot; heads.&n; *&n; * Returns 0 if the translation was not possible, if the device was not&n; * an IDE disk drive, or if a geometry was &quot;forced&quot; on the commandline.&n; * Returns 1 if the geometry translation was successful.&n; */
r_int
id|ide_xlate_1024
(paren
id|kdev_t
comma
r_int
comma
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Start a reset operation for an IDE interface.&n; * The caller should return immediately after invoking this.&n; */
r_void
id|ide_do_reset
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This function is intended to be used prior to invoking ide_do_drive_cmd().&n; */
r_void
id|ide_init_drive_cmd
(paren
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n; * &quot;action&quot; parameter type for ide_do_drive_cmd() below.&n; */
r_typedef
r_enum
DECL|enumerator|ide_wait
(brace
id|ide_wait
comma
multiline_comment|/* insert rq at end of list, and wait for it */
DECL|enumerator|ide_next
id|ide_next
comma
multiline_comment|/* insert rq immediately after current request */
DECL|enumerator|ide_preempt
id|ide_preempt
comma
multiline_comment|/* insert rq in front of current request */
DECL|enumerator|ide_end
id|ide_end
)brace
multiline_comment|/* insert rq at end of list, but don&squot;t wait for it */
DECL|typedef|ide_action_t
id|ide_action_t
suffix:semicolon
multiline_comment|/*&n; * This function issues a special IDE device request&n; * onto the request queue.&n; *&n; * If action is ide_wait, then then rq is queued at the end of&n; * the request queue, and the function sleeps until it has been&n; * processed.  This is for use when invoked from an ioctl handler.&n; *&n; * If action is ide_preempt, then the rq is queued at the head of&n; * the request queue, displacing the currently-being-processed&n; * request and this function returns immediately without waiting&n; * for the new rq to be completed.  This is VERY DANGEROUS, and is&n; * intended for careful use by the ATAPI tape/cdrom driver code.&n; *&n; * If action is ide_next, then the rq is queued immediately after&n; * the currently-being-processed-request (if any), and the function&n; * returns without waiting for the new rq to be completed.  As above,&n; * This is VERY DANGEROUS, and is intended for careful use by the &n; * ATAPI tape/cdrom driver code.&n; *&n; * If action is ide_end, then the rq is queued at the end of the&n; * request queue, and the function returns immediately without waiting&n; * for the new rq to be completed. This is again intended for careful&n; * use by the ATAPI tape/cdrom driver code.&n; */
r_int
id|ide_do_drive_cmd
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
comma
id|ide_action_t
id|action
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up after success/failure of an explicit drive cmd.&n; * stat/err are used only when (HWGROUP(drive)-&gt;rq-&gt;cmd == IDE_DRIVE_CMD).&n; */
r_void
id|ide_end_drive_cmd
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|stat
comma
id|byte
id|err
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_system_bus_speed() returns what we think is the system VESA/PCI&n; * bus speed (in MHz).  This is used for calculating interface PIO timings.&n; * The default is 40 for known PCI systems, 50 otherwise.&n; * The &quot;idebus=xx&quot; parameter can be used to override this value.&n; */
r_int
id|ide_system_bus_speed
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_multwrite() transfers a block of up to mcount sectors of data&n; * to a drive as part of a disk multwrite operation.&n; */
r_void
id|ide_multwrite
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|mcount
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_stall_queue() can be used by a drive to give excess bandwidth back&n; * to the hwgroup by sleeping for timeout jiffies.&n; */
r_void
id|ide_stall_queue
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_get_queue() returns the queue which corresponds to a given device.&n; */
r_struct
id|request
op_star
op_star
id|ide_get_queue
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_void
id|ide_timer_expiry
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_void
id|ide_intr
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|ide_geninit
(paren
r_struct
id|gendisk
op_star
id|gd
)paren
suffix:semicolon
r_void
id|do_ide0_request
(paren
r_void
)paren
suffix:semicolon
macro_line|#if MAX_HWIFS &gt; 1
r_void
id|do_ide1_request
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if MAX_HWIFS &gt; 2
r_void
id|do_ide2_request
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if MAX_HWIFS &gt; 3
r_void
id|do_ide3_request
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_void
id|ide_init_subdrivers
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef _IDE_C
r_extern
r_struct
id|file_operations
id|ide_fops
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef _IDE_C
macro_line|#ifdef CONFIG_BLK_DEV_IDEDISK
r_int
id|idedisk_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDISK */
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
r_int
id|ide_cdrom_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
macro_line|#ifdef CONFIG_BLK_DEV_IDETAPE
r_int
id|idetape_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDETAPE */
macro_line|#ifdef CONFIG_BLK_DEV_IDEFLOPPY
r_int
id|idefloppy_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEFLOPPY */
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
r_int
id|idescsi_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDESCSI */
macro_line|#endif /* _IDE_C */
r_int
id|ide_register_module
(paren
id|ide_module_t
op_star
id|module
)paren
suffix:semicolon
r_void
id|ide_unregister_module
(paren
id|ide_module_t
op_star
id|module
)paren
suffix:semicolon
id|ide_drive_t
op_star
id|ide_scan_devices
(paren
id|byte
id|media
comma
id|ide_driver_t
op_star
id|driver
comma
r_int
id|n
)paren
suffix:semicolon
r_int
id|ide_register_subdriver
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_driver_t
op_star
id|driver
comma
r_int
id|version
)paren
suffix:semicolon
r_int
id|ide_unregister_subdriver
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_BLK_DEV_OPTI621
r_void
id|ide_init_opti621
(paren
id|byte
comma
id|byte
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_OPTI621 */
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_int
id|ideprobe_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
macro_line|#ifdef CONFIG_BLK_DEV_PROMISE
macro_line|#include &quot;promise.h&quot;
DECL|macro|IS_PROMISE_DRIVE
mdefine_line|#define IS_PROMISE_DRIVE (HWIF(drive)-&gt;chipset == ide_promise)
macro_line|#else
DECL|macro|IS_PROMISE_DRIVE
mdefine_line|#define IS_PROMISE_DRIVE (0)&t;/* auto-NULLs out Promise code */
macro_line|#endif /* CONFIG_BLK_DEV_PROMISE */
macro_line|#endif /* _IDE_H */
eof
