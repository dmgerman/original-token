multiline_comment|/* $Id: tpqic02.h,v 0.16 1993/04/19 23:15:39 root Exp root $&n; *&n; * Include file for QIC-02 driver for Linux.&n; *&n; * Copyright (c) 1992 by H. H. Bergman. All rights reserved.&n; *&n; * ******* USER CONFIG SECTION BELOW *******&n; */
macro_line|#ifndef _LINUX_TPQIC02_H
DECL|macro|_LINUX_TPQIC02_H
mdefine_line|#define _LINUX_TPQIC02_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_TAPE_QIC02
multiline_comment|/* need to have TAPE_QIC02_DRIVE and TAPE_QIC02_IFC expand to something */
macro_line|#include &lt;linux/mtio.h&gt;
multiline_comment|/* make TAPE_QIC02_IFC expand to something */
DECL|macro|WANGTEK
mdefine_line|#define WANGTEK&t;&t;1&t;&t;   /* don&squot;t know about Wangtek QIC-36 */
DECL|macro|EVEREX
mdefine_line|#define EVEREX&t;&t;WANGTEK      /* I heard *some* of these are identical */
DECL|macro|EVEREX_811V
mdefine_line|#define EVEREX_811V&t;EVEREX&t;&t;&t;      /* With TEAC MT 2ST 45D */
DECL|macro|EVEREX_831V
mdefine_line|#define EVEREX_831V&t;EVEREX
DECL|macro|ARCHIVE
mdefine_line|#define ARCHIVE&t;&t;3
DECL|macro|ARCHIVE_SC400
mdefine_line|#define ARCHIVE_SC400&t;ARCHIVE&t;       /* rumoured to be from the pre-SMD-age */
DECL|macro|ARCHIVE_SC402
mdefine_line|#define ARCHIVE_SC402&t;ARCHIVE&t;&t;       /* don&squot;t know much about SC400 */
DECL|macro|ARCHIVE_SC499
mdefine_line|#define ARCHIVE_SC499&t;ARCHIVE       /* SC402 and SC499R should be identical */
multiline_comment|/*********** START OF USER CONFIGURABLE SECTION ************/
multiline_comment|/* Tape configuration: &n; *&n; * Tape drive configuration:&t;(MT_IS* constants are defined in sys/mtio.h)&n; *&n; * TAPE_QIC02_DRIVE = MT_ISWT5150&n; *&t;- Wangtek 5150, format: up to QIC-150.&n; * TAPE_QIC02_DRIVE = MT_ISQIC02_ALL_FEATURES&n; *&t;- Enables some optional QIC commands that some drives may lack.&n; *&t;  It is provided so you can check which are supported by your drive.&n; *&t;  Refer to tpqic02.h for others.&n; *&n; * Supported interface cards: TAPE_QIC02_IFC =&n; *&t;WANGTEK,&n; *&t;ARCHIVE_SC402, ARCHIVE_SC499.&t;(both same programming interface)&n; *&n; * Make sure you have the I/O ports/DMA channels &n; * and IRQ stuff configured properly!&n; * NOTE: Check for conflicts with TAPE_QIC02_TIMER in timer.h.&n; */
DECL|macro|TAPE_QIC02_DRIVE
mdefine_line|#define TAPE_QIC02_DRIVE&t;MT_ISQIC02_ALL_FEATURES&t;/* drive type */
multiline_comment|/* #define TAPE_QIC02_DRIVE&t;MT_ISWT5150 */
DECL|macro|TAPE_QIC02_IFC
mdefine_line|#define TAPE_QIC02_IFC&t;&t;WANGTEK&t;&t;/* interface card type */
multiline_comment|/* #define TAPE_QIC02_IFC&t;&t;ARCHIVE */
DECL|macro|TAPE_QIC02_PORT
mdefine_line|#define TAPE_QIC02_PORT &t;0x300&t;/* controller port adress */
DECL|macro|TAPE_QIC02_IRQ
mdefine_line|#define TAPE_QIC02_IRQ&t;&t;5&t;/* Muhammad, please don&squot;t use 2 here. -- Hennus */
DECL|macro|TAPE_QIC02_DMA
mdefine_line|#define TAPE_QIC02_DMA&t;&t;1&t;/* either 1 or 3, because 2 is used by the floppy */
multiline_comment|/************ END OF USER CONFIGURABLE SECTION *************/
multiline_comment|/* NOTE: TP_HAVE_DENS should distinguish between available densities&n; * NOTE: Drive select is not implemented -- I have only one tape streamer,&n; *&t; so I&squot;m unable and unmotivated to test and implement that. ;-) ;-)&n; */
macro_line|#if TAPE_QIC02_DRIVE == MT_ISWT5150
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;/* nope */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;/* nope */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;/* nope */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;/* most of the time */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2
macro_line|#elif TAPE_QIC02_DRIVE == MT_ISARCHIVESC499&t;/* Archive SC-499 QIC-36 controller */
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;&t;/* can do set density (QIC-11 / QIC-24) */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif (TAPE_QIC02_DRIVE == MT_ISARCHIVE_2060L) || (TAPE_QIC02_DRIVE == MT_ISARCHIVE_2150L)
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;&t;/* can do set density (QIC-24 / QIC-120 / QIC-150) */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;&t;/* can read current block address */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;&t;/* can seek to block */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#elif TAPE_QIC02_DRIVE == MT_ISQIC02_ALL_FEATURES
DECL|macro|TP_HAVE_DENS
mdefine_line|#define TP_HAVE_DENS&t;&t;/* can do set density */
DECL|macro|TP_HAVE_BSF
mdefine_line|#define TP_HAVE_BSF&t;&t;/* can search filemark backwards */
DECL|macro|TP_HAVE_FSR
mdefine_line|#define TP_HAVE_FSR&t;&t;/* can skip one block forwards */
DECL|macro|TP_HAVE_BSR
mdefine_line|#define TP_HAVE_BSR&t;&t;/* can skip one block backwards */
DECL|macro|TP_HAVE_EOD
mdefine_line|#define TP_HAVE_EOD&t;&t;/* can seek to end of recorded data */
DECL|macro|TP_HAVE_SEEK
mdefine_line|#define TP_HAVE_SEEK&t;&t;/* seek to block address */
DECL|macro|TP_HAVE_TELL
mdefine_line|#define TP_HAVE_TELL&t;&t;/* tell current block address */
DECL|macro|TP_HAVE_RAS1
mdefine_line|#define TP_HAVE_RAS1&t;&t;/* can run selftest 1 */
DECL|macro|TP_HAVE_RAS2
mdefine_line|#define TP_HAVE_RAS2&t;&t;/* can run selftest 2 */
multiline_comment|/* These last two selftests shouldn&squot;t be used yet! */
macro_line|#else
macro_line|#error No QIC-02 tape drive type defined!
multiline_comment|/* If your drive is not listed above, first try the &squot;ALL_FEATURES&squot;,&n; * to see what commands are supported, then create your own entry in&n; * the list above. You may want to mail it to me, so that I can include&n; * it in the next release.&n; */
macro_line|#endif
multiline_comment|/* NR_BLK_BUF is a `tuneable parameter&squot;. If you&squot;re really low on&n; * kernel space, you could decrease it to 1, or if you got a very&n; * slow machine, you could increase it up to 128 blocks. Less kernel&n; * buffer blocks result in more context-switching.&n; */
DECL|macro|NR_BLK_BUF
mdefine_line|#define NR_BLK_BUF&t;20&t;&t;&t;&t;    /* max 128 blocks */
DECL|macro|TAPE_BLKSIZE
mdefine_line|#define TAPE_BLKSIZE&t;512&t;&t;  /* streamer tape block size (fixed) */
DECL|macro|TPQBUF_SIZE
mdefine_line|#define TPQBUF_SIZE&t;(TAPE_BLKSIZE*NR_BLK_BUF)&t;       /* buffer size */
DECL|macro|BLOCKS_BEYOND_EW
mdefine_line|#define BLOCKS_BEYOND_EW&t;2&t;/* nr of blocks after Early Warning hole */
macro_line|#if TAPE_QIC02_IFC == WANGTEK&t;
multiline_comment|/* Wangtek interface card port locations */
DECL|macro|QIC_STAT_PORT
macro_line|# define QIC_STAT_PORT&t;TAPE_QIC02_PORT
DECL|macro|QIC_CTL_PORT
macro_line|# define QIC_CTL_PORT&t;TAPE_QIC02_PORT
DECL|macro|QIC_CMD_PORT
macro_line|# define QIC_CMD_PORT&t;(TAPE_QIC02_PORT+1)
DECL|macro|QIC_DATA_PORT
macro_line|# define QIC_DATA_PORT&t;(TAPE_QIC02_PORT+1)
multiline_comment|/* status register bits (Active LOW!) */
DECL|macro|QIC_STAT_READY
macro_line|# define QIC_STAT_READY&t;&t;0x01
DECL|macro|QIC_STAT_EXCEPTION
macro_line|# define QIC_STAT_EXCEPTION&t;0x02
DECL|macro|QIC_STAT_MASK
macro_line|# define QIC_STAT_MASK&t;&t;(QIC_STAT_READY|QIC_STAT_EXCEPTION)
DECL|macro|QIC_STAT_RESETMASK
macro_line|# define QIC_STAT_RESETMASK&t;0x07
DECL|macro|QIC_STAT_RESETVAL
macro_line|# define QIC_STAT_RESETVAL&t;(QIC_STAT_RESETMASK &amp; ~QIC_STAT_EXCEPTION)
multiline_comment|/* controller register (QIC_CTL_PORT) bits */
DECL|macro|WT_CTL_ONLINE
macro_line|# define WT_CTL_ONLINE&t;&t;0x01
DECL|macro|QIC_CTL_RESET
macro_line|# define QIC_CTL_RESET&t;&t;0x02
DECL|macro|QIC_CTL_REQUEST
macro_line|# define QIC_CTL_REQUEST&t;0x04
DECL|macro|WT_CTL_CMDOFF
macro_line|# define WT_CTL_CMDOFF&t;&t;0xC0 
macro_line|# if TAPE_QIC02_DMA == 3   /* dip-switches alone don&squot;t seem to cut it */
DECL|macro|WT_CTL_DMA
macro_line|#  define WT_CTL_DMA&t;&t;0x10&t;&t;&t;  /* enable dma chan3 */
macro_line|# elif TAPE_QIC02_DMA == 1
DECL|macro|WT_CTL_DMA
macro_line|#  define WT_CTL_DMA&t;&t;0x08&t;         /* enable dma chan1 or chan2 */
macro_line|# else
macro_line|#  error Unsupported or incorrect DMA configuration.
macro_line|# endif
macro_line|#elif TAPE_QIC02_IFC == ARCHIVE
multiline_comment|/* Archive interface card port locations */
DECL|macro|QIC_STAT_PORT
macro_line|# define QIC_STAT_PORT&t;&t;(TAPE_QIC02_PORT+1)
DECL|macro|QIC_CTL_PORT
macro_line|# define QIC_CTL_PORT&t;&t;(TAPE_QIC02_PORT+1)
DECL|macro|QIC_CMD_PORT
macro_line|# define QIC_CMD_PORT&t;&t;(TAPE_QIC02_PORT)
DECL|macro|QIC_DATA_PORT
macro_line|# define QIC_DATA_PORT&t;&t;(TAPE_QIC02_PORT)
DECL|macro|AR_START_DMA_PORT
macro_line|# define AR_START_DMA_PORT&t;(TAPE_QIC02_PORT+2)
DECL|macro|AR_RESET_DMA_PORT
macro_line|# define AR_RESET_DMA_PORT&t;(TAPE_QIC02_PORT+3)
multiline_comment|/* STAT port bits */
DECL|macro|AR_STAT_IRQF
macro_line|# define AR_STAT_IRQF&t;&t;0x80&t;/* active high, interrupt request flag */
DECL|macro|QIC_STAT_READY
macro_line|# define QIC_STAT_READY&t;&t;0x40&t;/* active low */
DECL|macro|QIC_STAT_EXCEPTION
macro_line|# define QIC_STAT_EXCEPTION&t;0x20&t;/* active low */
DECL|macro|QIC_STAT_MASK
macro_line|# define QIC_STAT_MASK&t;&t;(QIC_STAT_READY|QIC_STAT_EXCEPTION)
DECL|macro|AR_STAT_DMADONE
macro_line|# define AR_STAT_DMADONE&t;0x10&t;/* active high, DMA done */
DECL|macro|AR_STAT_DIRC
macro_line|# define AR_STAT_DIRC&t;&t;0x08&t;/* active high, direction */
DECL|macro|QIC_STAT_RESETMASK
macro_line|# define QIC_STAT_RESETMASK&t;0x70&t;/* check RDY,EXC,DMADONE */
DECL|macro|QIC_STAT_RESETVAL
macro_line|# define QIC_STAT_RESETVAL&t;((QIC_STAT_RESETMASK &amp; ~AR_STAT_IRQF &amp; ~QIC_STAT_EXCEPTION) | AR_STAT_DMADONE)
multiline_comment|/* CTL port bits */
DECL|macro|QIC_CTL_RESET
macro_line|# define QIC_CTL_RESET&t;&t;0x80&t;/* drive reset */
DECL|macro|QIC_CTL_REQUEST
macro_line|# define QIC_CTL_REQUEST&t;0x40&t;/* notify of new command */
DECL|macro|AR_CTL_IEN
macro_line|# define AR_CTL_IEN&t;&t;0x20&t;/* interrupt enable */
DECL|macro|AR_CTL_DNIEN
macro_line|# define AR_CTL_DNIEN&t;&t;0x10&t;/* done-interrupt enable */
multiline_comment|/* Note: All of these bits are cleared automatically when writing to&n;   * AR_RESET_DMA_PORT. So AR_CTL_IEN and AR_CTL_DNIEN must be&n;   * reprogrammed before the write to AR_START_DMA_PORT.&n;   */
macro_line|# if TAPE_QIC02_DMA &gt; 3&t;&t;/* channel 2 is used by the floppy driver */
macro_line|#  error DMA channels other than 1 and 3 are not supported.
macro_line|# endif
macro_line|#else
macro_line|# error No valid interface card specified!
macro_line|#endif /* TAPE_QIC02_IFC */
multiline_comment|/* Standard QIC-02 commands -- rev F.  All QIC-02 drives must support these */
DECL|macro|QCMD_SEL_1
mdefine_line|#define QCMD_SEL_1&t;0x01&t;&t;/* select drive 1 */
DECL|macro|QCMD_SEL_2
mdefine_line|#define QCMD_SEL_2&t;0x02&t;&t;/* select drive 2 */
DECL|macro|QCMD_SEL_3
mdefine_line|#define QCMD_SEL_3&t;0x04&t;&t;/* select drive 3 */
DECL|macro|QCMD_SEL_4
mdefine_line|#define QCMD_SEL_4&t;0x08&t;&t;/* select drive 4 */
DECL|macro|QCMD_REWIND
mdefine_line|#define&t;QCMD_REWIND&t;0x21&t;&t;/* rewind tape*/
DECL|macro|QCMD_ERASE
mdefine_line|#define QCMD_ERASE&t;0x22&t;&t;/* erase tape */
DECL|macro|QCMD_RETEN
mdefine_line|#define QCMD_RETEN&t;0x24&t;&t;/* retension tape */
DECL|macro|QCMD_WRT_DATA
mdefine_line|#define&t;QCMD_WRT_DATA&t;0x40&t;&t;/* write data */
DECL|macro|QCMD_WRT_FM
mdefine_line|#define&t;QCMD_WRT_FM&t;0x60&t;&t;/* write file mark */
DECL|macro|QCMD_RD_DATA
mdefine_line|#define&t;QCMD_RD_DATA&t;0x80&t;&t;/* read data */
DECL|macro|QCMD_RD_FM
mdefine_line|#define&t;QCMD_RD_FM&t;0xA0&t;&t;/* read file mark (forward direction) */
DECL|macro|QCMD_RD_STAT
mdefine_line|#define&t;QCMD_RD_STAT&t;0xC0&t;&t;/* read status */
multiline_comment|/* Other (optional/vendor unique) commands */
multiline_comment|/* Density commands are only valid when TP_BOM is set! */
DECL|macro|QCMD_DENS_11
mdefine_line|#define QCMD_DENS_11&t;0x26&t;&t;/* QIC-11 */
DECL|macro|QCMD_DENS_24
mdefine_line|#define QCMD_DENS_24&t;0x27&t;&t;/* QIC-24: 9 track 60MB */
DECL|macro|QCMD_DENS_120
mdefine_line|#define QCMD_DENS_120&t;0x28&t;&t;/* QIC-120: 15 track 120MB */
DECL|macro|QCMD_DENS_150
mdefine_line|#define QCMD_DENS_150&t;0x29&t;&t;/* QIC-150: 18 track 150MB */
DECL|macro|QCMD_DENS_300
mdefine_line|#define QCMD_DENS_300&t;0x2A&t;&t;/* QIC-300/QIC-2100 */
DECL|macro|QCMD_DENS_600
mdefine_line|#define QCMD_DENS_600&t;0x2B&t;&t;/* QIC-600/QIC-2200 */
multiline_comment|/* don&squot;t know about QIC-1000 and QIC-1350 */
DECL|macro|QCMD_WRTNU_DATA
mdefine_line|#define&t;QCMD_WRTNU_DATA&t;0x40&t;&t;/* write data, no underruns, insert filler. */
DECL|macro|QCMD_SPACE_FWD
mdefine_line|#define QCMD_SPACE_FWD&t;0x81&t;&t;/* skip next block */
DECL|macro|QCMD_SPACE_BCK
mdefine_line|#define QCMD_SPACE_BCK&t;0x89&t;&t;/* move tape head one block back -- very useful! */
DECL|macro|QCMD_RD_FM_BCK
mdefine_line|#define QCMD_RD_FM_BCK&t;0xA8&t;&t;/* read filemark (backwards) */
DECL|macro|QCMD_SEEK_EOD
mdefine_line|#define QCMD_SEEK_EOD&t;0xA3&t;&t;/* skip to EOD */
DECL|macro|QCMD_RD_STAT_X1
mdefine_line|#define&t;QCMD_RD_STAT_X1&t;0xC1&t;&t;/* read extended status 1 */
DECL|macro|QCMD_RD_STAT_X2
mdefine_line|#define&t;QCMD_RD_STAT_X2&t;0xC4&t;&t;/* read extended status 2 */
DECL|macro|QCMD_RD_STAT_X3
mdefine_line|#define&t;QCMD_RD_STAT_X3&t;0xE0&t;&t;/* read extended status 3 */
DECL|macro|QCMD_SELF_TST1
mdefine_line|#define QCMD_SELF_TST1&t;0xC2&t;&t;/* run self test 1 (nondestructive) */
DECL|macro|QCMD_SELF_TST2
mdefine_line|#define QCMD_SELF_TST2&t;0xCA&t;&t;/* run self test 2 (destructive) */
multiline_comment|/* &quot;Vendor Unique&quot; codes */
macro_line|#if defined(MT_ISARCHIVESC499) || defined(MT_ISARCHIVE_2150L)
DECL|macro|QCMDV_TELL_BLK
macro_line|# define QCMDV_TELL_BLK&t;&t;0xAE&t;&t;/* read current block address */
DECL|macro|QCMDV_SEEK_BLK
macro_line|# define QCMDV_SEEK_BLK&t;&t;0xAD&t;&t;/* seek to specific block */
DECL|macro|SEEK_BUF_SIZE
macro_line|# define SEEK_BUF_SIZE&t;&t;3&t;&t;/* address is 3 bytes */
macro_line|#endif
multiline_comment|/* Optional, QFA (Quick File Access) commands.&n; * Not all drives support this, but those that do could use these commands&n; * to implement semi-non-sequential access. `mt fsf` would benefit from this.&n; * QFA divides the tape into 2 partitions, a data and a directory partition,&n; * causing some incompatibility problems wrt std QIC-02 data exchange.&n; * It would be useful to cache the directory info, but that might be tricky&n; * to do in kernel-space. [Size constraints.]&n; * Refer to QIC-02, appendix A for more information.&n; * I have no idea how other *nix variants implement QFA.&n; * I have no idea which drives support QFA and which don&squot;t.&n; */
DECL|macro|QFA_ENABLE
mdefine_line|#define QFA_ENABLE&t;0x2D&t;&t;/* enter QFA mode, give @ BOT only */
DECL|macro|QFA_DATA
mdefine_line|#define QFA_DATA&t;0x20&t;&t;/* select data partition */
DECL|macro|QFA_DIR
mdefine_line|#define QFA_DIR&t;&t;0x23&t;&t;/* select directory partition */
DECL|macro|QFA_RD_POS
mdefine_line|#define QFA_RD_POS&t;0xCF&t;&t;/* read position+status bytes */
DECL|macro|QFA_SEEK_EOD
mdefine_line|#define QFA_SEEK_EOD&t;0xA1&t;&t;/* seek EOD within current partition */
DECL|macro|QFA_SEEK_BLK
mdefine_line|#define QFA_SEEK_BLK&t;0xAF&t;&t;/* seek to a block within current partition */
multiline_comment|/* Minor device codes for tapes:&n; * |7|6|5|4|3|2|1|0|&n; *  | &bslash; | / &bslash; | / |_____ 1=rewind on close, 0=no rewind on close&n; *  |  &bslash;|/    |_________ Density: 000=none, 001=QIC-11, 010=24, 011=120,&n; *  |   |                100=QIC-150, 101..111 reserved.&n; *  |   |_______________ Reserved for unit numbers.&n; *  |___________________ Reserved for diagnostics during debugging.&n; */
DECL|macro|TP_REWCLOSE
mdefine_line|#define&t;TP_REWCLOSE(d)&t;((MINOR(d)&amp;0x01) == 1)&t;   &t;&t;/* rewind bit */
multiline_comment|/* rewind is only done if data has been transfered */
DECL|macro|TP_DENS
mdefine_line|#define&t;TP_DENS(dev)&t;((MINOR(dev) &gt;&gt; 1) &amp; 0x07) &t;      /* tape density */
DECL|macro|TP_UNIT
mdefine_line|#define TP_UNIT(dev)&t;((MINOR(dev) &gt;&gt; 4) &amp; 0x07)&t;       /* unit number */
DECL|macro|TP_DIAGS
mdefine_line|#define TP_DIAGS(dev)&t;(MINOR(dev) &amp; 0x80)    /* print excessive diagnostics */
multiline_comment|/* status codes returned by a WTS_RDSTAT call */
DECL|struct|tpstatus
r_struct
id|tpstatus
(brace
multiline_comment|/* sizeof(short)==2), LSB first */
DECL|member|exs
r_int
r_int
id|exs
suffix:semicolon
multiline_comment|/* Drive exception flags */
DECL|member|dec
r_int
r_int
id|dec
suffix:semicolon
multiline_comment|/* data error count: nr of blocks rewritten/soft read errors */
DECL|member|urc
r_int
r_int
id|urc
suffix:semicolon
multiline_comment|/* underrun count: nr of times streaming was interrupted */
)brace
suffix:semicolon
DECL|macro|TPSTATSIZE
mdefine_line|#define TPSTATSIZE&t;sizeof(struct tpstatus)
multiline_comment|/* defines for tpstatus.exs -- taken from 386BSD wt driver */
DECL|macro|TP_POR
mdefine_line|#define&t;TP_POR&t;&t;0x100&t;/* Power on or reset occurred */
DECL|macro|TP_EOR
mdefine_line|#define&t;TP_EOR&t;&t;0x200&t;/* REServed for end of RECORDED media */
DECL|macro|TP_PAR
mdefine_line|#define&t;TP_PAR&t;&t;0x400&t;/* REServed for bus parity */
DECL|macro|TP_BOM
mdefine_line|#define&t;TP_BOM&t;&t;0x800&t;/* Beginning of media */
DECL|macro|TP_MBD
mdefine_line|#define&t;TP_MBD&t;&t;0x1000&t;/* Marginal block detected */
DECL|macro|TP_NDT
mdefine_line|#define&t;TP_NDT&t;&t;0x2000&t;/* No data detected */
DECL|macro|TP_ILL
mdefine_line|#define&t;TP_ILL&t;&t;0x4000&t;/* Illegal command */
DECL|macro|TP_ST1
mdefine_line|#define&t;TP_ST1&t;&t;0x8000&t;/* Status byte 1 flag */
DECL|macro|TP_FIL
mdefine_line|#define&t;TP_FIL&t;&t;0x01&t;/* File mark detected */
DECL|macro|TP_BNL
mdefine_line|#define&t;TP_BNL&t;&t;0x02&t;/* Bad block not located */
DECL|macro|TP_UDA
mdefine_line|#define&t;TP_UDA&t;&t;0x04&t;/* Unrecoverable data error */
DECL|macro|TP_EOM
mdefine_line|#define&t;TP_EOM&t;&t;0x08&t;/* End of media */
DECL|macro|TP_WRP
mdefine_line|#define&t;TP_WRP&t;&t;0x10&t;/* Write protected cartridge */
DECL|macro|TP_USL
mdefine_line|#define&t;TP_USL&t;&t;0x20&t;/* Unselected drive */
DECL|macro|TP_CNI
mdefine_line|#define&t;TP_CNI&t;&t;0x40&t;/* Cartridge not in place */
DECL|macro|TP_ST0
mdefine_line|#define&t;TP_ST0&t;&t;0x80&t;/* Status byte 0 flag */
DECL|macro|REPORT_ERR0
mdefine_line|#define REPORT_ERR0&t;(TP_CNI|TP_USL|TP_WRP|TP_EOM|TP_UDA|TP_BNL|TP_FIL)
DECL|macro|REPORT_ERR1
mdefine_line|#define REPORT_ERR1&t;(TP_ILL|TP_NDT|TP_MBD|TP_PAR)
DECL|macro|EXC_UNKNOWN
mdefine_line|#define EXC_UNKNOWN&t;0&t;/* (extra) Unknown exception code */
DECL|macro|EXC_NCART
mdefine_line|#define EXC_NCART&t;1&t;/* No cartridge */
DECL|macro|EXC_NDRV
mdefine_line|#define EXC_NDRV&t;2&t;/* No drive */
DECL|macro|EXC_WP
mdefine_line|#define EXC_WP&t;&t;3&t;/* Write protected */
DECL|macro|EXC_EOM
mdefine_line|#define EXC_EOM&t;&t;4&t;/* EOM */
DECL|macro|EXC_RWA
mdefine_line|#define EXC_RWA&t;&t;5&t;/* read/write abort */
DECL|macro|EXC_XBAD
mdefine_line|#define EXC_XBAD&t;6&t;/* read error, bad block transfered */
DECL|macro|EXC_XFILLER
mdefine_line|#define EXC_XFILLER&t;7&t;/* read error, filler block transfered */
DECL|macro|EXC_NDT
mdefine_line|#define EXC_NDT&t;&t;8&t;/* read error, no data */
DECL|macro|EXC_NDTEOM
mdefine_line|#define EXC_NDTEOM&t;9&t;/* read error, no data &amp; EOM */
DECL|macro|EXC_NDTBOM
mdefine_line|#define EXC_NDTBOM&t;10&t;/* read error, no data &amp; BOM */
DECL|macro|EXC_FM
mdefine_line|#define EXC_FM&t;&t;11&t;/* Read a filemark */
DECL|macro|EXC_ILL
mdefine_line|#define EXC_ILL&t;&t;12&t;/* Illegal command */
DECL|macro|EXC_POR
mdefine_line|#define EXC_POR&t;&t;13&t;/* Power on/reset */
DECL|macro|EXC_MARGINAL
mdefine_line|#define EXC_MARGINAL&t;14&t;/* Marginal block detected */
DECL|macro|EXC_EOR
mdefine_line|#define EXC_EOR&t;&t;15&t;/* (extra, for SEEKEOD) End Of Recorded data reached */
DECL|macro|EXC_BOM
mdefine_line|#define EXC_BOM&t;&t;16&t;/* (extra) BOM reached */
DECL|macro|TAPE_NOTIFY_TIMEOUT
mdefine_line|#define TAPE_NOTIFY_TIMEOUT&t;1000000
multiline_comment|/* internal function return codes */
DECL|macro|TE_OK
mdefine_line|#define TE_OK&t;0&t;&t;/* everything is fine */
DECL|macro|TE_EX
mdefine_line|#define TE_EX&t;1&t;&t;/* exception detected */
DECL|macro|TE_ERR
mdefine_line|#define TE_ERR&t;2&t;&t;/* some error */
DECL|macro|TE_NS
mdefine_line|#define TE_NS&t;3&t;&t;/* can&squot;t read status */
DECL|macro|TE_TIM
mdefine_line|#define TE_TIM&t;4&t;&t;/* timed out */
DECL|macro|TE_DEAD
mdefine_line|#define TE_DEAD&t;5&t;&t;/* tape drive doesn&squot;t respond */
DECL|macro|TE_END
mdefine_line|#define TE_END&t;6&t;&t;/******** Archive hack *****/
multiline_comment|/* timeout timer values -- check these! */
DECL|macro|TIM_S
mdefine_line|#define TIM_S&t;(4*HZ)&t;&t;/* 4 seconds (normal cmds) */
DECL|macro|TIM_M
mdefine_line|#define TIM_M&t;(30*HZ)&t;&t;/* 30 seconds (write FM) */
DECL|macro|TIM_R
mdefine_line|#define TIM_R&t;(8*60*HZ)&t;/* 8 minutes (retensioning) */
DECL|macro|TIM_F
mdefine_line|#define TIM_F&t;(2*3600*HZ)&t;/* est. 1.2hr for full tape read/write+2 retens */
DECL|macro|TIMERON
mdefine_line|#define TIMERON(t)&t;timer_table[TAPE_QIC02_TIMER].expires = jiffies + (t); &bslash;&n;&t;&t;&t;timer_active |= (1&lt;&lt;TAPE_QIC02_TIMER)
DECL|macro|TIMEROFF
mdefine_line|#define TIMEROFF&t;timer_active &amp;= ~(1&lt;&lt;TAPE_QIC02_TIMER)
DECL|macro|TIMERCONT
mdefine_line|#define TIMERCONT&t;timer_active |= (1&lt;&lt;TAPE_QIC02_TIMER)
DECL|typedef|flag
r_typedef
r_char
id|flag
suffix:semicolon
DECL|macro|NO
mdefine_line|#define NO&t;0&t;/* NO must be 0 */
DECL|macro|YES
mdefine_line|#define YES&t;1&t;/* YES must be != 0 */
macro_line|#ifdef TDEBUG
DECL|macro|TPQDEB
macro_line|# define TPQDEB(s)&t;s
DECL|macro|TPQPUTS
macro_line|# define TPQPUTS(s)&t;tpqputs(s)
macro_line|#else
DECL|macro|TPQDEB
macro_line|# define TPQDEB(s)
DECL|macro|TPQPUTS
macro_line|# define TPQPUTS(s)
macro_line|#endif
r_extern
r_int
id|tape_qic02_init
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* for kernel/mem.c */
macro_line|#endif /* CONFIG_TAPE_QIC02 */
macro_line|#endif /* _LINUX_TPQIC02_H */
eof
