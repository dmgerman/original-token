macro_line|#ifndef _LINUX_CONFIG_H
DECL|macro|_LINUX_CONFIG_H
mdefine_line|#define _LINUX_CONFIG_H
DECL|macro|CONFIG_DISTRIBUTION
mdefine_line|#define CONFIG_DISTRIBUTION
multiline_comment|/*&n; * Defines for what uname() should return &n; */
macro_line|#ifndef UTS_SYSNAME
DECL|macro|UTS_SYSNAME
mdefine_line|#define UTS_SYSNAME &quot;Linux&quot;
macro_line|#endif
macro_line|#ifndef UTS_NODENAME
DECL|macro|UTS_NODENAME
mdefine_line|#define UTS_NODENAME &quot;(none)&quot;&t;/* set by sethostname() */
macro_line|#endif
DECL|macro|UTS_MACHINE
mdefine_line|#define UTS_MACHINE &quot;i386&quot;&t;/* hardware type */
multiline_comment|/*&n; * The definitions for UTS_RELEASE and UTS_VERSION are now defined&n; * in linux/version.h, and should only be used by linux/version.c&n; */
multiline_comment|/* Don&squot;t touch these, unless you really know what your doing. */
DECL|macro|DEF_INITSEG
mdefine_line|#define DEF_INITSEG&t;0x9000
DECL|macro|DEF_SYSSEG
mdefine_line|#define DEF_SYSSEG&t;0x1000
DECL|macro|DEF_SETUPSEG
mdefine_line|#define DEF_SETUPSEG&t;0x9020
DECL|macro|DEF_SYSSIZE
mdefine_line|#define DEF_SYSSIZE&t;0x7000
multiline_comment|/* internal svga startup constants */
DECL|macro|NORMAL_VGA
mdefine_line|#define NORMAL_VGA&t;0xffff&t;&t;/* 80x25 mode */
DECL|macro|EXTENDED_VGA
mdefine_line|#define EXTENDED_VGA&t;0xfffe&t;&t;/* 80x50 mode */
DECL|macro|ASK_VGA
mdefine_line|#define ASK_VGA&t;&t;0xfffd&t;&t;/* ask for it at bootup */
multiline_comment|/*&n; * The root-device is no longer hard-coded. You can change the default&n; * root-device by changing the line ROOT_DEV = XXX in boot/bootsect.s&n; */
multiline_comment|/*&n; * The keyboard is now defined in kernel/chr_dev/keyboard.S&n; */
multiline_comment|/*&n; * Normally, Linux can get the drive parameters from the BIOS at&n; * startup, but if this for some unfathomable reason fails, you&squot;d&n; * be left stranded. For this case, you can define HD_TYPE, which&n; * contains all necessary info on your harddisk.&n; *&n; * The HD_TYPE macro should look like this:&n; *&n; * #define HD_TYPE { head, sect, cyl, wpcom, lzone, ctl}&n; *&n; * In case of two harddisks, the info should be sepatated by&n; * commas:&n; *&n; * #define HD_TYPE { h,s,c,wpcom,lz,ctl },{ h,s,c,wpcom,lz,ctl }&n; */
multiline_comment|/*&n; This is an example, two drives, first is type 2, second is type 3:&n;&n;#define HD_TYPE { 4,17,615,300,615,8 }, { 6,17,615,300,615,0 }&n;&n; NOTE: ctl is 0 for all drives with heads&lt;=8, and ctl=8 for drives&n; with more than 8 heads.&n;&n; If you want the BIOS to tell what kind of drive you have, just&n; leave HD_TYPE undefined. This is the normal thing to do.&n;*/
DECL|macro|HD_TYPE
macro_line|#undef HD_TYPE
DECL|macro|CONFIG_BLK_DEV_HD
mdefine_line|#define CONFIG_BLK_DEV_HD
DECL|macro|CONFIG_BLK_DEV_SD
macro_line|#undef CONFIG_BLK_DEV_SD
DECL|macro|CONFIG_BLK_DEV_ST
macro_line|#undef CONFIG_BLK_DEV_ST
DECL|macro|CONFIG_BLK_DEV_SR
macro_line|#undef CONFIG_BLK_DEV_SR
multiline_comment|/*&n;&t;Choose supported SCSI adapters here.&n;*/
DECL|macro|CONFIG_SCSI_AHA1542
macro_line|#undef CONFIG_SCSI_AHA1542
DECL|macro|CONFIG_SCSI_ALWAYS
macro_line|#undef CONFIG_SCSI_ALWAYS
DECL|macro|CONFIG_SCSI_CSC
macro_line|#undef CONFIG_SCSI_CSC
DECL|macro|CONFIG_SCSI_DTC
macro_line|#undef CONFIG_SCSI_DTC
DECL|macro|CONFIG_SCSI_FUTURE_DOMAIN
macro_line|#undef CONFIG_SCSI_FUTURE_DOMAIN
DECL|macro|CONFIG_SCSI_SEAGATE
macro_line|#undef CONFIG_SCSI_SEAGATE
DECL|macro|CONFIG_SCSI_ULTRASTOR
macro_line|#undef CONFIG_SCSI_ULTRASTOR
DECL|macro|CONFIG_SCSI_7000FASST
macro_line|#undef CONFIG_SCSI_7000FASST
macro_line|#if defined(CONFIG_BLK_DEV_SD) || defined(CONFIG_BLK_DEV_SR) || &bslash;&n;defined(CONFIG_CHR_DEV_ST)
macro_line|#ifndef CONFIG_SCSI
DECL|macro|CONFIG_SCSI
mdefine_line|#define CONFIG_SCSI
macro_line|#endif
macro_line|#if !defined(CONFIG_SCSI_AHA1542) &amp;&amp; !defined(CONFIG_SCSI_CSC) &amp;&amp; !defined(CONFIG_SCSI_DTC) &amp;&amp; &bslash;&n;&t;&t;!defined(CONFIG_SCSI_FUTURE_DOMAIN) &amp;&amp;  !defined(CONFIG_SCSI_SEAGATE) &amp;&amp; !defined(CONFIG_SCSI_ULTRASTOR) &amp;&amp; &bslash;&n;&t;&t;!defined(CONFIG_SCSI_7000FASST)
macro_line|#error  Error : SCSI devices enabled, but no low level drivers have been enabled.
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *  Choose filesystems here.&n; */
DECL|macro|MINIX_FS
mdefine_line|#define MINIX_FS
DECL|macro|EXT_FS
mdefine_line|#define EXT_FS
DECL|macro|MSDOS_FS
mdefine_line|#define MSDOS_FS
DECL|macro|PROC_FS
mdefine_line|#define PROC_FS
DECL|macro|NFS_FS
macro_line|#undef  NFS_FS
macro_line|#ifdef CONFIG_DISTRIBUTION
macro_line|#include &lt;linux/config.dist.h&gt;
macro_line|#else
macro_line|#include &lt;linux/config.site.h&gt;
macro_line|#endif
multiline_comment|/*&n;&t;File type specific stuff goes into this.&n;*/
macro_line|#ifdef ASM_SRC
macro_line|#endif
macro_line|#ifdef C_SRC
macro_line|#endif
macro_line|#ifdef MAKE
macro_line|#endif
macro_line|#endif
eof
