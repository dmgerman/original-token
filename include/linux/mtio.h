multiline_comment|/* $Id: mtio.h,v 1.4 1992/11/18 01:32:03 root Exp root $&n; *&n; * linux/mtio.h header file for Linux. Written by H. Bergman&n; */
macro_line|#ifndef _LINUX_MTIO_H
DECL|macro|_LINUX_MTIO_H
mdefine_line|#define _LINUX_MTIO_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * Structures and definitions for mag tape io control commands&n; */
multiline_comment|/* structure for MTIOCTOP - mag tape op command */
DECL|struct|mtop
r_struct
id|mtop
(brace
DECL|member|mt_op
r_int
id|mt_op
suffix:semicolon
multiline_comment|/* operations defined below */
DECL|member|mt_count
r_int
id|mt_count
suffix:semicolon
multiline_comment|/* how many of them */
)brace
suffix:semicolon
multiline_comment|/* Magnetic Tape operations [Not all operations supported by all drivers]: */
DECL|macro|MTRESET
mdefine_line|#define MTRESET 0&t;/* +reset drive in case of problems */
DECL|macro|MTFSF
mdefine_line|#define MTFSF&t;1&t;/* forward space over FileMark,&n;&t;&t;&t; * position at first record of next file &n;&t;&t;&t; */
DECL|macro|MTBSF
mdefine_line|#define MTBSF&t;2&t;/* backward space FileMark (position before FM) */
DECL|macro|MTFSR
mdefine_line|#define MTFSR&t;3&t;/* forward space record */
DECL|macro|MTBSR
mdefine_line|#define MTBSR&t;4&t;/* backward space record */
DECL|macro|MTWEOF
mdefine_line|#define MTWEOF&t;5&t;/* write an end-of-file record (mark) */
DECL|macro|MTREW
mdefine_line|#define MTREW&t;6&t;/* rewind */
DECL|macro|MTOFFL
mdefine_line|#define MTOFFL&t;7&t;/* rewind and put the drive offline (eject?) */
DECL|macro|MTNOP
mdefine_line|#define MTNOP&t;8&t;/* no op, set status only (read with MTIOCGET) */
DECL|macro|MTRETEN
mdefine_line|#define MTRETEN 9&t;/* retension tape */
DECL|macro|MTBSFM
mdefine_line|#define MTBSFM&t;10&t;/* +backward space FileMark, position at FM */
DECL|macro|MTFSFM
mdefine_line|#define MTFSFM  11&t;/* +forward space FileMark, position at FM */
DECL|macro|MTEOM
mdefine_line|#define MTEOM&t;12&t;/* goto end of recorded media (for appending files).&n;&t;&t;&t; * MTEOM positions after the last FM, ready for&n;&t;&t;&t; * appending another file.&n;&t;&t;&t; */
DECL|macro|MTERASE
mdefine_line|#define MTERASE 13&t;/* erase tape -- be careful! */
DECL|macro|MTRAS1
mdefine_line|#define MTRAS1  14&t;/* run self test 1 (nondestructive) */
DECL|macro|MTRAS2
mdefine_line|#define MTRAS2&t;15&t;/* run self test 2 (destructive) */
DECL|macro|MTRAS3
mdefine_line|#define MTRAS3  16&t;/* reserved for self test 3 */
DECL|macro|MTSETBLK
mdefine_line|#define MTSETBLK 20&t;/* set block length (SCSI) */
DECL|macro|MTSETDENSITY
mdefine_line|#define MTSETDENSITY 21&t;/* set tape density (SCSI) */
DECL|macro|MTSEEK
mdefine_line|#define MTSEEK&t;22&t;/* seek to block (Tandberg, etc.) */
DECL|macro|MTTELL
mdefine_line|#define MTTELL&t;23&t;/* tell block (Tandber, etc.) */
multiline_comment|/* structure for MTIOCGET - mag tape get status command */
DECL|struct|mtget
r_struct
id|mtget
(brace
DECL|member|mt_type
r_int
id|mt_type
suffix:semicolon
multiline_comment|/* type of magtape device */
DECL|member|mt_resid
r_int
id|mt_resid
suffix:semicolon
multiline_comment|/* residual count: (not sure)&n;&t;&t;&t;&t; *&t;number of bytes ignored, or&n;&t;&t;&t;&t; *&t;number of files not skipped, or&n;&t;&t;&t;&t; *&t;number of records not skipped.&n;&t;&t;&t;&t; */
multiline_comment|/* the following registers are device dependent */
DECL|member|mt_dsreg
r_int
id|mt_dsreg
suffix:semicolon
multiline_comment|/* status register */
DECL|member|mt_gstat
r_int
id|mt_gstat
suffix:semicolon
multiline_comment|/* generic (device independent) status */
DECL|member|mt_erreg
r_int
id|mt_erreg
suffix:semicolon
multiline_comment|/* error register */
multiline_comment|/* The next two fields are not always used */
DECL|member|mt_fileno
id|daddr_t
id|mt_fileno
suffix:semicolon
multiline_comment|/* number of current file on tape */
DECL|member|mt_blkno
id|daddr_t
id|mt_blkno
suffix:semicolon
multiline_comment|/* current block number */
)brace
suffix:semicolon
multiline_comment|/*&n; * Constants for mt_type. Not all of these are supported.&n; */
DECL|macro|MT_ISUNKNOWN
mdefine_line|#define MT_ISUNKNOWN&t;&t;0x01
DECL|macro|MT_ISQIC02
mdefine_line|#define MT_ISQIC02&t;&t;0x02&t;/* Generic QIC-02 tape streamer */
DECL|macro|MT_ISWT5150
mdefine_line|#define MT_ISWT5150&t;&t;0x03&t;/* Wangtek 5150EQ, QIC-150, QIC-02 */
DECL|macro|MT_ISARCHIVE_5945L2
mdefine_line|#define MT_ISARCHIVE_5945L2&t;0x04&t;/* Archive 5945L-2, QIC-24, QIC-02? */
DECL|macro|MT_ISCMSJ500
mdefine_line|#define MT_ISCMSJ500&t;&t;0x05&t;/* CMS Jumbo 500 (QIC-02?) */
DECL|macro|MT_ISTDC3610
mdefine_line|#define MT_ISTDC3610&t;&t;0x06&t;/* Tandberg 6310, QIC-24 */
DECL|macro|MT_ISARCHIVE_VP60I
mdefine_line|#define MT_ISARCHIVE_VP60I&t;0x07&t;/* Archive VP60i, QIC-02 */
DECL|macro|MT_ISARCHIVE_2150L
mdefine_line|#define MT_ISARCHIVE_2150L&t;0x08&t;/* Archive Viper 2150L */
DECL|macro|MT_ISARCHIVE_2060L
mdefine_line|#define MT_ISARCHIVE_2060L&t;0x09&t;/* Archive Viper 2060L */
DECL|macro|MT_ISQIC02_ALL_FEATURES
mdefine_line|#define MT_ISQIC02_ALL_FEATURES&t;0x0F&t;/* Generic QIC-02 with all features */
DECL|macro|MT_ISWT5099EEN24
mdefine_line|#define MT_ISWT5099EEN24&t;0x11&t;/* Wangtek 5099-een24, 60MB, QIC-24 */
DECL|macro|MT_ISEVEREX_FT40A
mdefine_line|#define MT_ISEVEREX_FT40A&t;0x32&t;/* Everex FT40A (QIC-40) */
DECL|macro|MT_ISDDS1
mdefine_line|#define MT_ISDDS1&t;&t;0x51&t;/* DDS device without partitions */
DECL|macro|MT_ISDDS2
mdefine_line|#define MT_ISDDS2&t;&t;0x52&t;/* DDS device with partitions */
DECL|macro|MT_ISSCSI1
mdefine_line|#define MT_ISSCSI1&t;&t;0x71&t;/* Generic ANSI SCSI-1 tape unit */
DECL|struct|mt_tape_info
r_struct
id|mt_tape_info
(brace
DECL|member|t_type
r_int
id|t_type
suffix:semicolon
multiline_comment|/* device type id (mt_type) */
DECL|member|t_name
r_char
op_star
id|t_name
suffix:semicolon
multiline_comment|/* descriptive name */
)brace
suffix:semicolon
DECL|macro|MT_TAPE_INFO
mdefine_line|#define MT_TAPE_INFO&t;{ &bslash;&n;&t;{MT_ISUNKNOWN,&t;&t;&quot;Unknown type of tape device&quot;}, &bslash;&n;&t;{MT_ISQIC02,&t;&t;&quot;Generic QIC-02 tape streamer&quot;}, &bslash;&n;&t;{MT_ISWT5150,&t;&t;&quot;Wangtek 5150, QIC-150&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_5945L2,&t;&quot;Archive 5945L-2&quot;}, &bslash;&n;&t;{MT_ISCMSJ500,&t;&t;&quot;CMS Jumbo 500&quot;}, &bslash;&n;&t;{MT_ISTDC3610,&t;&t;&quot;Tandberg TDC 3610, QIC-24&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_VP60I,&t;&quot;Archive VP60i, QIC-02&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_2150L,&t;&quot;Archive Viper 2150L&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_2060L,&t;&quot;Archive Viper 2060L&quot;}, &bslash;&n;&t;{MT_ISWT5099EEN24,&t;&quot;Wangtek 5099-een24, 60MB&quot;}, &bslash;&n;&t;{MT_ISEVEREX_FT40A,&t;&quot;Everex FT40A, QIC-40&quot;}, &bslash;&n;&t;{MT_ISSCSI1,&t;&t;&quot;Generic SCSI-1 tape&quot;}, &bslash;&n;&t;{0, NULL} &bslash;&n;}
multiline_comment|/* structure for MTIOCPOS - mag tape get position command */
DECL|struct|mtpos
r_struct
id|mtpos
(brace
DECL|member|mt_blkno
r_int
id|mt_blkno
suffix:semicolon
multiline_comment|/* current block number */
)brace
suffix:semicolon
multiline_comment|/* mag tape io control commands */
DECL|macro|MTIOCTOP
mdefine_line|#define&t;MTIOCTOP&t;_IOW(&squot;m&squot;, 1, struct mtop)&t;/* do a mag tape op */
DECL|macro|MTIOCGET
mdefine_line|#define&t;MTIOCGET&t;_IOR(&squot;m&squot;, 2, struct mtget)&t;/* get tape status */
DECL|macro|MTIOCPOS
mdefine_line|#define&t;MTIOCPOS&t;_IOR(&squot;m&squot;, 3, struct mtpos)&t;/* get tape position */
multiline_comment|/* Generic Mag Tape (device independent) status macros for examining&n; * mt_gstat -- HP-UX compatible.&n; * There is room for more generic status bits here, but I don&squot;t&n; * know which of them are reserved. At least three or so should&n; * be added to make this really useful.&n; */
DECL|macro|GMT_EOF
mdefine_line|#define GMT_EOF(x)              ((x) &amp; 0x80000000)
DECL|macro|GMT_BOT
mdefine_line|#define GMT_BOT(x)              ((x) &amp; 0x40000000)
DECL|macro|GMT_EOT
mdefine_line|#define GMT_EOT(x)              ((x) &amp; 0x20000000)
DECL|macro|GMT_SM
mdefine_line|#define GMT_SM(x)               ((x) &amp; 0x10000000)  /* DDS setmark */
DECL|macro|GMT_EOD
mdefine_line|#define GMT_EOD(x)              ((x) &amp; 0x08000000)  /* DDS EOD */
DECL|macro|GMT_WR_PROT
mdefine_line|#define GMT_WR_PROT(x)          ((x) &amp; 0x04000000)
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x02000000) */
DECL|macro|GMT_ONLINE
mdefine_line|#define GMT_ONLINE(x)           ((x) &amp; 0x01000000)
DECL|macro|GMT_D_6250
mdefine_line|#define GMT_D_6250(x)           ((x) &amp; 0x00800000)
DECL|macro|GMT_D_1600
mdefine_line|#define GMT_D_1600(x)           ((x) &amp; 0x00400000)
DECL|macro|GMT_D_800
mdefine_line|#define GMT_D_800(x)            ((x) &amp; 0x00200000)
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00100000) */
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00080000) */
DECL|macro|GMT_DR_OPEN
mdefine_line|#define GMT_DR_OPEN(x)          ((x) &amp; 0x00040000)  /* door open (no tape) */
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00020000) */
DECL|macro|GMT_IM_REP_EN
mdefine_line|#define GMT_IM_REP_EN(x)        ((x) &amp; 0x00010000)  /* immediate report mode */
multiline_comment|/* 16 generic status bits unused */
multiline_comment|/* DDS drives have &squot;setmarks&squot;, sort of like filemarks but used to group&n; * files, rather than blocks. Not used. Not supported.&n; * I think DDS drives are DAT drives.&n; */
macro_line|#endif /* _LINUX_MTIO_H */
eof
