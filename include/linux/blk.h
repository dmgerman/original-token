macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
multiline_comment|/*&n; * Spinlock for protecting the request queue which&n; * is mucked around with in interrupts on potentially&n; * multiple CPU&squot;s..&n; */
r_extern
id|spinlock_t
id|current_lock
suffix:semicolon
multiline_comment|/*&n; * NR_REQUEST is the number of entries in the request-queue.&n; * NOTE that writes may use only the low 2/3 of these: reads&n; * take precedence.&n; */
DECL|macro|NR_REQUEST
mdefine_line|#define NR_REQUEST&t;64
multiline_comment|/*&n; * This is used in the elevator algorithm.  We don&squot;t prioritise reads&n; * over writes any more --- although reads are more time-critical than&n; * writes, by treating them equally we increase filesystem throughput.&n; * This turns out to give better overall performance.  -- sct&n; */
DECL|macro|IN_ORDER
mdefine_line|#define IN_ORDER(s1,s2) &bslash;&n;((s1)-&gt;rq_dev &lt; (s2)-&gt;rq_dev || (((s1)-&gt;rq_dev == (s2)-&gt;rq_dev &amp;&amp; &bslash;&n;(s1)-&gt;sector &lt; (s2)-&gt;sector)))
multiline_comment|/*&n; * These will have to be changed to be aware of different buffer&n; * sizes etc.. It actually needs a major cleanup.&n; */
macro_line|#if defined(IDE_DRIVER) || defined(MD_DRIVER)
DECL|macro|SECTOR_MASK
mdefine_line|#define SECTOR_MASK ((BLOCK_SIZE &gt;&gt; 9) - 1)
macro_line|#else
DECL|macro|SECTOR_MASK
mdefine_line|#define SECTOR_MASK (blksize_size[MAJOR_NR] &amp;&amp;     &bslash;&n;&t;blksize_size[MAJOR_NR][MINOR(CURRENT-&gt;rq_dev)] ? &bslash;&n;&t;((blksize_size[MAJOR_NR][MINOR(CURRENT-&gt;rq_dev)] &gt;&gt; 9) - 1) :  &bslash;&n;&t;((BLOCK_SIZE &gt;&gt; 9)  -  1))
macro_line|#endif /* IDE_DRIVER */
DECL|macro|SUBSECTOR
mdefine_line|#define SUBSECTOR(block) (CURRENT-&gt;current_nr_sectors &gt; 0)
macro_line|#ifdef CONFIG_CDROM
r_extern
r_int
id|cdrom_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDROM 
macro_line|#ifdef CONFIG_ISP16_CDI
r_extern
r_int
id|isp16_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_ISP16_CDI
macro_line|#ifdef CONFIG_CDU31A
r_extern
r_int
id|cdu31a_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDU31A
macro_line|#ifdef CONFIG_ATARI_ACSI
r_extern
r_int
id|acsi_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_ATARI_ACSI
macro_line|#ifdef CONFIG_MCD
r_extern
r_int
id|mcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_MCD
macro_line|#ifdef CONFIG_MCDX
r_extern
r_int
id|mcdx_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_MCDX
macro_line|#ifdef CONFIG_SBPCD
r_extern
r_int
id|sbpcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_SBPCD
macro_line|#ifdef CONFIG_AZTCD
r_extern
r_int
id|aztcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_AZTCD
macro_line|#ifdef CONFIG_CDU535
r_extern
r_int
id|sony535_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDU535
macro_line|#ifdef CONFIG_GSCD
r_extern
r_int
id|gscd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_GSCD
macro_line|#ifdef CONFIG_CM206
r_extern
r_int
id|cm206_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_CM206
macro_line|#ifdef CONFIG_OPTCD
r_extern
r_int
id|optcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_OPTCD
macro_line|#ifdef CONFIG_SJCD
r_extern
r_int
id|sjcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_SJCD
macro_line|#ifdef CONFIG_CDI_INIT
r_extern
r_int
id|cdi_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_CDI_INIT
macro_line|#ifdef CONFIG_BLK_DEV_HD
r_extern
r_int
id|hd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_extern
r_int
id|ide_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_XD
r_extern
r_int
id|xd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_LOOP
r_extern
r_int
id|loop_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_MD
r_extern
r_int
id|md_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif CONFIG_BLK_DEV_MD
macro_line|#ifdef CONFIG_APBLOCK
r_extern
r_int
id|ap_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DDV
r_extern
r_int
id|ddv_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA_Z2RAM
r_extern
r_int
id|z2_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC_FLOPPY
r_extern
r_int
id|swim3_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|set_device_ro
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|flag
)paren
suffix:semicolon
r_void
id|add_blkdev_randomness
c_func
(paren
r_int
id|major
)paren
suffix:semicolon
r_extern
r_int
id|floppy_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rd_load
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|macro|INITRD_MINOR
mdefine_line|#define INITRD_MINOR 250 /* shouldn&squot;t collide with /dev/ram* too soon ... */
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_int
id|mount_initrd
suffix:semicolon
multiline_comment|/* zero if initrd should not be mounted */
r_extern
r_int
id|initrd_below_start_ok
suffix:semicolon
multiline_comment|/* 1 if it is not an error if initrd_start &lt; memory_start */
r_void
id|initrd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_PS2
r_extern
r_int
id|ps2esdi_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|RO_IOCTLS
mdefine_line|#define RO_IOCTLS(dev,where) &bslash;&n;  case BLKROSET: { int __val;  if (!suser()) return -EACCES; &bslash;&n;&t;&t;   if (get_user(__val, (int *)(where))) return -EFAULT; &bslash;&n;&t;&t;   set_device_ro((dev),__val); return 0; } &bslash;&n;  case BLKROGET: { int __val = (is_read_only(dev) != 0) ; &bslash;&n;&t;&t;    return put_user(__val,(int *) (where)); }
macro_line|#if defined(MAJOR_NR) || defined(IDE_DRIVER)
multiline_comment|/*&n; * Add entries as needed.&n; */
macro_line|#ifdef IDE_DRIVER
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device)&t;(MINOR(device) &gt;&gt; PARTN_BITS)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)&t;/* nothing */
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)&t;/* nothing */
macro_line|#elif (MAJOR_NR == RAMDISK_MAJOR)
multiline_comment|/* ram disk */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ramdisk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST rd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) 
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
DECL|macro|DEVICE_NO_RANDOM
mdefine_line|#define DEVICE_NO_RANDOM
macro_line|#elif (MAJOR_NR == Z2RAM_MAJOR)
multiline_comment|/* Zorro II Ram */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Z2RAM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_z2_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == FLOPPY_MAJOR)
r_static
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;floppy&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_floppy
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_fd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) ( (MINOR(device) &amp; 3) | ((MINOR(device) &amp; 0x80 ) &gt;&gt; 5 ))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device) floppy_off(DEVICE_NR(device))
macro_line|#elif (MAJOR_NR == HD_MAJOR)
multiline_comment|/* harddisk: timeout is 6 seconds.. */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;harddisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_hd
DECL|macro|DEVICE_TIMEOUT
mdefine_line|#define DEVICE_TIMEOUT HD_TIMER
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (6*HZ)
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_hd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device)&gt;&gt;6)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SCSI_DISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsidisk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_sd  
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (2*HZ)
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 4)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
multiline_comment|/* Kludge to use the same number for both char and block major numbers */
macro_line|#elif  (MAJOR_NR == MD_MAJOR) &amp;&amp; defined(MD_DRIVER)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Multiple devices driver&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_md_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SCSI_TAPE_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsitape&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_st  
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &amp; 0x7f)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SCSI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CD-ROM&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_sr
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sr_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == XT_DISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;xt disk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_xd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 6)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == PS2ESDI_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;PS/2 ESDI&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_ps2esdi_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 6)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == CDU31A_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CDU31A&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cdu31a_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == ACSI_MAJOR) &amp;&amp; (defined(CONFIG_ATARI_ACSI) || defined(CONFIG_ATARI_ACSI_MODULE))
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ACSI&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_acsi
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_acsi_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device) &gt;&gt; 4)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MITSUMI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Mitsumi CD-ROM&quot;
multiline_comment|/* #define DEVICE_INTR do_mcd */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MITSUMI_X_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Mitsumi CD-ROM&quot;
multiline_comment|/* #define DEVICE_INTR do_mcdx */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mcdx_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #1&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM2_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #2&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd2_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM3_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #3&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd3_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM4_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #4&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd4_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == AZTECH_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Aztech CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_aztcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == CDU535_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;SONY-CDU535&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_cdu535
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cdu535_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == GOLDSTAR_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Goldstar R420&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_gscd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == CM206_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Philips/LMS cd-rom cm206&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cm206_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == OPTICS_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;DOLPHIN 8000AT CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_optcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == SANYO_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Sanyo H94A CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sjcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == APBLOCK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;apblock&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST ap_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) 
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#elif (MAJOR_NR == DDV_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ddv&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST ddv_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device)&gt;&gt;PARTN_BITS)
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) 
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
macro_line|#endif /* MAJOR_NR == whatever */
macro_line|#if (MAJOR_NR != SCSI_TAPE_MAJOR)
macro_line|#if !defined(IDE_DRIVER)
macro_line|#ifndef CURRENT
DECL|macro|CURRENT
mdefine_line|#define CURRENT (blk_dev[MAJOR_NR].current_request)
macro_line|#endif
DECL|macro|CURRENT_DEV
mdefine_line|#define CURRENT_DEV DEVICE_NR(CURRENT-&gt;rq_dev)
macro_line|#ifdef DEVICE_INTR
DECL|variable|DEVICE_INTR
r_static
r_void
(paren
op_star
id|DEVICE_INTR
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEVICE_TIMEOUT
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER &bslash;&n;((timer_table[DEVICE_TIMEOUT].expires = jiffies + TIMEOUT_VALUE), &bslash;&n;(timer_active |= 1&lt;&lt;DEVICE_TIMEOUT))
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER &bslash;&n;timer_active &amp;= ~(1&lt;&lt;DEVICE_TIMEOUT)
DECL|macro|SET_INTR
mdefine_line|#define SET_INTR(x) &bslash;&n;if ((DEVICE_INTR = (x)) != NULL) &bslash;&n;&t;SET_TIMER; &bslash;&n;else &bslash;&n;&t;CLEAR_TIMER;
macro_line|#else
DECL|macro|SET_INTR
mdefine_line|#define SET_INTR(x) (DEVICE_INTR = (x))
macro_line|#endif /* DEVICE_TIMEOUT */
r_static
r_void
(paren
id|DEVICE_REQUEST
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef DEVICE_INTR
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR SET_INTR(NULL)
macro_line|#else
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR
macro_line|#endif
DECL|macro|INIT_REQUEST
mdefine_line|#define INIT_REQUEST &bslash;&n;&t;if (!CURRENT) {&bslash;&n;&t;&t;CLEAR_INTR; &bslash;&n;&t;&t;return; &bslash;&n;&t;} &bslash;&n;&t;if (MAJOR(CURRENT-&gt;rq_dev) != MAJOR_NR) &bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;); &bslash;&n;&t;if (CURRENT-&gt;bh) { &bslash;&n;&t;&t;if (!buffer_locked(CURRENT-&gt;bh)) &bslash;&n;&t;&t;&t;panic(DEVICE_NAME &quot;: block not locked&quot;); &bslash;&n;&t;}
macro_line|#endif /* !defined(IDE_DRIVER) */
multiline_comment|/* end_request() - SCSI devices have their own version */
multiline_comment|/*               - IDE drivers have their own copy too */
macro_line|#if ! SCSI_BLK_MAJOR(MAJOR_NR)
macro_line|#if defined(IDE_DRIVER) &amp;&amp; !defined(_IDE_C) /* shared copy for IDE modules */
r_void
id|ide_end_request
c_func
(paren
id|byte
id|uptodate
comma
id|ide_hwgroup_t
op_star
id|hwgroup
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef IDE_DRIVER
DECL|function|ide_end_request
r_void
id|ide_end_request
c_func
(paren
id|byte
id|uptodate
comma
id|ide_hwgroup_t
op_star
id|hwgroup
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|hwgroup-&gt;rq
suffix:semicolon
macro_line|#else
r_static
r_void
id|end_request
c_func
(paren
r_int
id|uptodate
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|CURRENT
suffix:semicolon
macro_line|#endif /* IDE_DRIVER */
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|nsect
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;end_request: I/O error, dev %s, sector %lu&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|req-&gt;rq_dev
)paren
comma
id|req-&gt;sector
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|nsect
op_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;nr_sectors
op_decrement
suffix:semicolon
id|req-&gt;nr_sectors
op_and_assign
op_complement
(paren
id|nsect
op_minus
l_int|1
)paren
suffix:semicolon
id|req-&gt;sector
op_add_assign
id|nsect
suffix:semicolon
id|req-&gt;sector
op_and_assign
op_complement
(paren
id|nsect
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|bh
op_member_access_from_pointer
id|b_end_io
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;current_nr_sectors
op_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;nr_sectors
OL
id|req-&gt;current_nr_sectors
)paren
(brace
id|req-&gt;nr_sectors
op_assign
id|req-&gt;current_nr_sectors
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;end_request: buffer-list destroyed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
macro_line|#ifndef DEVICE_NO_RANDOM
id|add_blkdev_randomness
c_func
(paren
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef IDE_DRIVER
id|hwgroup-&gt;drive-&gt;queue
op_assign
id|req-&gt;next
suffix:semicolon
id|blk_dev
(braket
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)braket
dot
id|current_request
op_assign
l_int|NULL
suffix:semicolon
id|hwgroup-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
macro_line|#else
id|DEVICE_OFF
c_func
(paren
id|req-&gt;rq_dev
)paren
suffix:semicolon
id|CURRENT
op_assign
id|req-&gt;next
suffix:semicolon
macro_line|#endif /* IDE_DRIVER */
r_if
c_cond
(paren
id|req-&gt;sem
op_ne
l_int|NULL
)paren
id|up
c_func
(paren
id|req-&gt;sem
)paren
suffix:semicolon
id|req-&gt;rq_status
op_assign
id|RQ_INACTIVE
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(IDE_DRIVER) &amp;&amp; !defined(_IDE_C) */
macro_line|#endif /* ! SCSI_BLK_MAJOR(MAJOR_NR) */
macro_line|#endif /* (MAJOR_NR != SCSI_TAPE_MAJOR) */
macro_line|#endif /* defined(MAJOR_NR) || defined(IDE_DRIVER) */
macro_line|#endif /* _BLK_H */
eof
