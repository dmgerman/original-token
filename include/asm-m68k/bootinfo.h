multiline_comment|/*&n;** asm/bootinfo.h -- Definition of the Linux/68K boot information structure&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created 09/29/92 by Greg Harp&n;**&n;** 5/2/94 Roman Hodek:&n;**   Added bi_atari part of the machine dependent union bi_un; for now it&n;**&t; contains just a model field to distinguish between TT and Falcon.&n;*/
macro_line|#ifndef BOOTINFO_H
DECL|macro|BOOTINFO_H
mdefine_line|#define BOOTINFO_H
macro_line|#include &lt;asm/zorro.h&gt;
multiline_comment|/*&n; * Amiga specific part of bootinfo structure.&n; */
DECL|macro|NUM_AUTO
mdefine_line|#define NUM_AUTO    16
macro_line|#ifndef __ASSEMBLY__
DECL|macro|AMIGAHW_DECLARE
mdefine_line|#define AMIGAHW_DECLARE(name)&t;unsigned name : 1
DECL|macro|AMIGAHW_SET
mdefine_line|#define AMIGAHW_SET(name)&t;(boot_info.bi_amiga.hw_present.name = 1)
DECL|macro|AMIGAHW_PRESENT
mdefine_line|#define AMIGAHW_PRESENT(name)&t;(boot_info.bi_amiga.hw_present.name)
DECL|struct|bi_Amiga
r_struct
id|bi_Amiga
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
multiline_comment|/* Amiga Model (3000?) */
DECL|member|num_autocon
r_int
id|num_autocon
suffix:semicolon
multiline_comment|/* # of autoconfig devices found */
DECL|member|autocon
r_struct
id|ConfigDev
id|autocon
(braket
id|NUM_AUTO
)braket
suffix:semicolon
multiline_comment|/* up to 16 autoconfig devices */
macro_line|#ifdef HACKER_KERNEL
DECL|member|exit_func
r_void
(paren
op_star
id|exit_func
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* addr of function to exit kernel */
DECL|member|chip_addr
r_int
r_int
id|chip_addr
suffix:semicolon
multiline_comment|/* start of chip memory (bytes) */
macro_line|#endif
DECL|member|chip_size
r_int
r_int
id|chip_size
suffix:semicolon
multiline_comment|/* size of chip memory (bytes) */
DECL|member|vblank
r_int
r_char
id|vblank
suffix:semicolon
multiline_comment|/* VBLANK frequency */
DECL|member|psfreq
r_int
r_char
id|psfreq
suffix:semicolon
multiline_comment|/* power supply frequency */
DECL|member|eclock
r_int
r_int
id|eclock
suffix:semicolon
multiline_comment|/* EClock frequency */
DECL|member|chipset
r_int
r_int
id|chipset
suffix:semicolon
multiline_comment|/* native chipset present */
r_struct
(brace
multiline_comment|/* video hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_VIDEO
)paren
suffix:semicolon
multiline_comment|/* Amiga Video */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_BLITTER
)paren
suffix:semicolon
multiline_comment|/* Amiga Blitter */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMBER_FF
)paren
suffix:semicolon
multiline_comment|/* Amber Flicker Fixer */
multiline_comment|/* sound hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_AUDIO
)paren
suffix:semicolon
multiline_comment|/* Amiga Audio */
multiline_comment|/* disk storage interfaces */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_FLOPPY
)paren
suffix:semicolon
multiline_comment|/* Amiga Floppy */
id|AMIGAHW_DECLARE
c_func
(paren
id|A3000_SCSI
)paren
suffix:semicolon
multiline_comment|/* SCSI (wd33c93, A3000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A4000_SCSI
)paren
suffix:semicolon
multiline_comment|/* SCSI (ncr53c710, A4000T alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A1200_IDE
)paren
suffix:semicolon
multiline_comment|/* IDE (A1200 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A4000_IDE
)paren
suffix:semicolon
multiline_comment|/* IDE (A4000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|CD_ROM
)paren
suffix:semicolon
multiline_comment|/* CD ROM drive */
multiline_comment|/* other I/O hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_KEYBOARD
)paren
suffix:semicolon
multiline_comment|/* Amiga Keyboard */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_MOUSE
)paren
suffix:semicolon
multiline_comment|/* Amiga Mouse */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_SERIAL
)paren
suffix:semicolon
multiline_comment|/* Amiga Serial */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_PARALLEL
)paren
suffix:semicolon
multiline_comment|/* Amiga Parallel */
multiline_comment|/* real time clocks */
id|AMIGAHW_DECLARE
c_func
(paren
id|A2000_CLK
)paren
suffix:semicolon
multiline_comment|/* Hardware Clock (A2000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A3000_CLK
)paren
suffix:semicolon
multiline_comment|/* Hardware Clock (A3000 alike) */
multiline_comment|/* supporting hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|CHIP_RAM
)paren
suffix:semicolon
multiline_comment|/* Chip RAM */
id|AMIGAHW_DECLARE
c_func
(paren
id|PAULA
)paren
suffix:semicolon
multiline_comment|/* Paula (8364) */
id|AMIGAHW_DECLARE
c_func
(paren
id|DENISE
)paren
suffix:semicolon
multiline_comment|/* Denise (8362) */
id|AMIGAHW_DECLARE
c_func
(paren
id|DENISE_HR
)paren
suffix:semicolon
multiline_comment|/* Denise (8373) */
id|AMIGAHW_DECLARE
c_func
(paren
id|LISA
)paren
suffix:semicolon
multiline_comment|/* Lisa (8375) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_PAL
)paren
suffix:semicolon
multiline_comment|/* Normal/Fat PAL Agnus (8367/8371) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_NTSC
)paren
suffix:semicolon
multiline_comment|/* Normal/Fat NTSC Agnus (8361/8370) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_HR_PAL
)paren
suffix:semicolon
multiline_comment|/* Fat Hires PAL Agnus (8372) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_HR_NTSC
)paren
suffix:semicolon
multiline_comment|/* Fat Hires NTSC Agnus (8372) */
id|AMIGAHW_DECLARE
c_func
(paren
id|ALICE_PAL
)paren
suffix:semicolon
multiline_comment|/* PAL Alice (8374) */
id|AMIGAHW_DECLARE
c_func
(paren
id|ALICE_NTSC
)paren
suffix:semicolon
multiline_comment|/* NTSC Alice (8374) */
id|AMIGAHW_DECLARE
c_func
(paren
id|MAGIC_REKICK
)paren
suffix:semicolon
multiline_comment|/* A3000 Magic Hard Rekick */
id|AMIGAHW_DECLARE
c_func
(paren
id|ZORRO
)paren
suffix:semicolon
multiline_comment|/* Zorro AutoConfig */
DECL|member|hw_present
)brace
id|hw_present
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else&t;/* __ASSEMBLY__ */
id|BI_amiga_model
op_assign
id|BI_un
id|BI_amiga_num_autcon
op_assign
id|BI_amiga_model
op_plus
l_int|4
id|BI_amiga_autocon
op_assign
id|BI_amiga_num_autcon
op_plus
l_int|4
macro_line|#ifdef HACKER_KERNEL
id|BI_amiga_exit_func
op_assign
id|BI_amiga_autocon
op_plus
(paren
id|CD_sizeof
op_star
id|NUM_AUTO
)paren
id|BI_amiga_chip_addr
op_assign
id|BI_amiga_exit_func
op_plus
l_int|4
id|BI_amiga_chip_size
op_assign
id|BI_amiga_chip_addr
op_plus
l_int|4
macro_line|#else
id|BI_amiga_chip_size
op_assign
id|BI_amiga_autocon
op_plus
(paren
id|CD_sizeof
op_star
id|NUM_AUTO
)paren
macro_line|#endif
id|BI_amiga_vblank
op_assign
id|BI_amiga_chip_size
op_plus
l_int|4
id|BI_amiga_psfreq
op_assign
id|BI_amiga_vblank
op_plus
l_int|1
id|BI_amiga_eclock
op_assign
id|BI_amiga_psfreq
op_plus
l_int|1
id|BI_amiga_chipset
op_assign
id|BI_amiga_eclock
op_plus
l_int|4
id|BI_amiga_hw_present
op_assign
id|BI_amiga_chipset
op_plus
l_int|4
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/* Atari specific part of bootinfo */
multiline_comment|/*&n; * Define several Hardware-Chips for indication so that for the ATARI we do&n; * no longer decide whether it is a Falcon or other machine . It&squot;s just&n; * important what hardware the machine uses&n; */
multiline_comment|/* ++roman 08/08/95: rewritten from ORing constants to a C bitfield */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|ATARIHW_DECLARE
mdefine_line|#define ATARIHW_DECLARE(name)&t;unsigned name : 1
DECL|macro|ATARIHW_SET
mdefine_line|#define ATARIHW_SET(name)&t;(boot_info.bi_atari.hw_present.name = 1)
DECL|macro|ATARIHW_PRESENT
mdefine_line|#define ATARIHW_PRESENT(name)&t;(boot_info.bi_atari.hw_present.name)
r_struct
id|bi_Atari
(brace
r_struct
(brace
multiline_comment|/* video hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|STND_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* ST-Shifter - no base low ! */
id|ATARIHW_DECLARE
c_func
(paren
id|EXTD_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* STe-Shifter - 24 bit address */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* TT-Shifter */
id|ATARIHW_DECLARE
c_func
(paren
id|VIDEL_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* Falcon-Shifter */
multiline_comment|/* sound hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|YM_2149
)paren
suffix:semicolon
multiline_comment|/* Yamaha YM 2149 */
id|ATARIHW_DECLARE
c_func
(paren
id|PCM_8BIT
)paren
suffix:semicolon
multiline_comment|/* PCM-Sound in STe-ATARI */
id|ATARIHW_DECLARE
c_func
(paren
id|CODEC
)paren
suffix:semicolon
multiline_comment|/* CODEC Sound (Falcon) */
multiline_comment|/* disk storage interfaces */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_SCSI
)paren
suffix:semicolon
multiline_comment|/* Directly mapped NCR5380 */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_SCSI
)paren
suffix:semicolon
multiline_comment|/* NCR5380 via ST-DMA (Falcon) */
id|ATARIHW_DECLARE
c_func
(paren
id|ACSI
)paren
suffix:semicolon
multiline_comment|/* Standard ACSI like in STs */
id|ATARIHW_DECLARE
c_func
(paren
id|IDE
)paren
suffix:semicolon
multiline_comment|/* IDE Interface */
id|ATARIHW_DECLARE
c_func
(paren
id|FDCSPEED
)paren
suffix:semicolon
multiline_comment|/* 8/16 MHz switch for FDC */
multiline_comment|/* other I/O hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_MFP
)paren
suffix:semicolon
multiline_comment|/* The ST-MFP (there should&n;&t;&t;&t;&t;&t;   be no Atari without&n;&t;&t;&t;&t;&t;   it... but who knows?) */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_MFP
)paren
suffix:semicolon
multiline_comment|/* 2nd MFP */
id|ATARIHW_DECLARE
c_func
(paren
id|SCC
)paren
suffix:semicolon
multiline_comment|/* Serial Communications Contr. */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_ESCC
)paren
suffix:semicolon
multiline_comment|/* SCC Z83230 in an ST */
id|ATARIHW_DECLARE
c_func
(paren
id|ANALOG_JOY
)paren
suffix:semicolon
multiline_comment|/* Paddle Interface for STe&n;&t;&t;&t;&t;&t;   and Falcon */
id|ATARIHW_DECLARE
c_func
(paren
id|MICROWIRE
)paren
suffix:semicolon
multiline_comment|/* Microwire Interface */
multiline_comment|/* DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|STND_DMA
)paren
suffix:semicolon
multiline_comment|/* 24 Bit limited ST-DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|EXTD_DMA
)paren
suffix:semicolon
multiline_comment|/* 32 Bit ST-DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|SCSI_DMA
)paren
suffix:semicolon
multiline_comment|/* DMA for the NCR5380 */
id|ATARIHW_DECLARE
c_func
(paren
id|SCC_DMA
)paren
suffix:semicolon
multiline_comment|/* DMA for the SCC */
multiline_comment|/* real time clocks */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_CLK
)paren
suffix:semicolon
multiline_comment|/* TT compatible clock chip */
id|ATARIHW_DECLARE
c_func
(paren
id|MSTE_CLK
)paren
suffix:semicolon
multiline_comment|/* Mega ST(E) clock chip */
multiline_comment|/* supporting hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|SCU
)paren
suffix:semicolon
multiline_comment|/* System Control Unit */
id|ATARIHW_DECLARE
c_func
(paren
id|BLITTER
)paren
suffix:semicolon
multiline_comment|/* Blitter */
id|ATARIHW_DECLARE
c_func
(paren
id|VME
)paren
suffix:semicolon
multiline_comment|/* VME Bus */
)brace
id|hw_present
suffix:semicolon
r_int
r_int
id|mch_cookie
suffix:semicolon
multiline_comment|/* _MCH cookie from TOS */
)brace
suffix:semicolon
multiline_comment|/* mch_cookie values (upper word) */
DECL|macro|ATARI_MCH_ST
mdefine_line|#define&t;ATARI_MCH_ST&t;&t;0
DECL|macro|ATARI_MCH_STE
mdefine_line|#define&t;ATARI_MCH_STE&t;&t;1
DECL|macro|ATARI_MCH_TT
mdefine_line|#define&t;ATARI_MCH_TT&t;&t;2
DECL|macro|ATARI_MCH_FALCON
mdefine_line|#define&t;ATARI_MCH_FALCON&t;3
DECL|struct|mem_info
r_struct
id|mem_info
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* physical address of memory chunk */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* length of memory chunk (in bytes) */
)brace
suffix:semicolon
macro_line|#else&t;/* __ASSEMBLY__ */
id|MI_addr
op_assign
l_int|0
id|MI_size
op_assign
id|MI_addr
op_plus
l_int|4
id|MI_sizeof
op_assign
id|MI_size
op_plus
l_int|4
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|NUM_MEMINFO
mdefine_line|#define NUM_MEMINFO  4
DECL|macro|MACH_AMIGA
mdefine_line|#define MACH_AMIGA   1
DECL|macro|MACH_ATARI
mdefine_line|#define MACH_ATARI   2
DECL|macro|MACH_MAC
mdefine_line|#define MACH_MAC     3
multiline_comment|/*&n; * CPU and FPU types&n; */
DECL|macro|CPUB_68020
mdefine_line|#define CPUB_68020 0
DECL|macro|CPUB_68030
mdefine_line|#define CPUB_68030 1
DECL|macro|CPUB_68040
mdefine_line|#define CPUB_68040 2
DECL|macro|CPUB_68060
mdefine_line|#define CPUB_68060 3
DECL|macro|FPUB_68881
mdefine_line|#define FPUB_68881 5
DECL|macro|FPUB_68882
mdefine_line|#define FPUB_68882 6
DECL|macro|FPUB_68040
mdefine_line|#define FPUB_68040 7&t;/* Internal FPU */
DECL|macro|FPUB_68060
mdefine_line|#define FPUB_68060 8&t;/* Internal FPU */
DECL|macro|CPU_68020
mdefine_line|#define CPU_68020    (1&lt;&lt;CPUB_68020)
DECL|macro|CPU_68030
mdefine_line|#define CPU_68030    (1&lt;&lt;CPUB_68030)
DECL|macro|CPU_68040
mdefine_line|#define CPU_68040    (1&lt;&lt;CPUB_68040)
DECL|macro|CPU_68060
mdefine_line|#define CPU_68060    (1&lt;&lt;CPUB_68060)
DECL|macro|CPU_MASK
mdefine_line|#define CPU_MASK     (31)
DECL|macro|FPU_68881
mdefine_line|#define FPU_68881    (1&lt;&lt;FPUB_68881)
DECL|macro|FPU_68882
mdefine_line|#define FPU_68882    (1&lt;&lt;FPUB_68882)
DECL|macro|FPU_68040
mdefine_line|#define FPU_68040    (1&lt;&lt;FPUB_68040)&t;/* Internal FPU */
DECL|macro|FPU_68060
mdefine_line|#define FPU_68060    (1&lt;&lt;FPUB_68060)&t;/* Internal FPU */
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE      (256)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|MACH_IS_AMIGA
mdefine_line|#define MACH_IS_AMIGA&t;(boot_info.machtype == MACH_AMIGA)
DECL|macro|MACH_IS_ATARI
mdefine_line|#define MACH_IS_ATARI&t;(boot_info.machtype == MACH_ATARI)
DECL|struct|bootinfo
r_struct
id|bootinfo
(brace
DECL|member|machtype
r_int
r_int
id|machtype
suffix:semicolon
multiline_comment|/* machine type */
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
multiline_comment|/* system CPU &amp; FPU */
DECL|member|memory
r_struct
id|mem_info
id|memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
multiline_comment|/* memory description */
DECL|member|num_memory
r_int
id|num_memory
suffix:semicolon
multiline_comment|/* # of memory blocks found */
DECL|member|ramdisk_size
r_int
r_int
id|ramdisk_size
suffix:semicolon
multiline_comment|/* ramdisk size in 1024 byte blocks */
DECL|member|ramdisk_addr
r_int
r_int
id|ramdisk_addr
suffix:semicolon
multiline_comment|/* address of the ram disk in mem */
DECL|member|command_line
r_char
id|command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/* kernel command line parameters */
r_union
(brace
DECL|member|bi_ami
r_struct
id|bi_Amiga
id|bi_ami
suffix:semicolon
multiline_comment|/* Amiga specific information */
DECL|member|bi_ata
r_struct
id|bi_Atari
id|bi_ata
suffix:semicolon
multiline_comment|/* Atari specific information */
DECL|member|bi_un
)brace
id|bi_un
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bi_amiga
mdefine_line|#define bi_amiga bi_un.bi_ami
DECL|macro|bi_atari
mdefine_line|#define bi_atari bi_un.bi_ata
DECL|macro|bi_mac
mdefine_line|#define bi_mac&t; bi_un.bi_mac
r_extern
r_struct
id|bootinfo
id|boot_info
suffix:semicolon
macro_line|#else&t;/* __ASSEMBLY__ */
id|BI_machtype
op_assign
l_int|0
id|BI_cputype
op_assign
id|BI_machtype
op_plus
l_int|4
id|BI_memory
op_assign
id|BI_cputype
op_plus
l_int|4
id|BI_num_memory
op_assign
id|BI_memory
op_plus
(paren
id|MI_sizeof
op_star
id|NUM_MEMINFO
)paren
id|BI_ramdisk_size
op_assign
id|BI_num_memory
op_plus
l_int|4
id|BI_ramdisk_addr
op_assign
id|BI_ramdisk_size
op_plus
l_int|4
id|BI_command_line
op_assign
id|BI_ramdisk_addr
op_plus
l_int|4
id|BI_un
op_assign
id|BI_command_line
op_plus
id|CL_SIZE
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Stuff for bootinfo interface versioning&n; *&n; * At the start of kernel code, a &squot;struct bootversion&squot; is located. bootstrap&n; * checks for a matching version of the interface before booting a kernel, to&n; * avoid user confusion if kernel and bootstrap don&squot;t work together :-)&n; *&n; * If incompatible changes are made to the bootinfo interface, the major&n; * number below should be stepped (and the minor reset to 0) for the&n; * appropriate machine. If a change is backward-compatible, the minor should&n; * be stepped. &quot;Backwards-compatible&quot; means that booting will work, but&n; * certain features may not.&n; */
DECL|macro|BOOTINFOV_MAGIC
mdefine_line|#define BOOTINFOV_MAGIC&t;&t;&t;0x4249561A&t;/* &squot;BIV^Z&squot; */
DECL|macro|MK_BI_VERSION
mdefine_line|#define MK_BI_VERSION(major,minor)&t;(((major)&lt;&lt;16)+(minor))
DECL|macro|BI_VERSION_MAJOR
mdefine_line|#define BI_VERSION_MAJOR(v)&t;&t;(((v) &gt;&gt; 16) &amp; 0xffff)
DECL|macro|BI_VERSION_MINOR
mdefine_line|#define BI_VERSION_MINOR(v)&t;&t;((v) &amp; 0xffff)
macro_line|#ifndef __ASSEMBLY__
r_struct
id|bootversion
(brace
r_int
r_int
id|branch
suffix:semicolon
r_int
r_int
id|magic
suffix:semicolon
r_struct
(brace
r_int
r_int
id|machtype
suffix:semicolon
r_int
r_int
id|version
suffix:semicolon
)brace
id|machversions
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|AMIGA_BOOTI_VERSION
mdefine_line|#define AMIGA_BOOTI_VERSION    MK_BI_VERSION( 1, 0 )
DECL|macro|ATARI_BOOTI_VERSION
mdefine_line|#define ATARI_BOOTI_VERSION    MK_BI_VERSION( 1, 0 )
macro_line|#endif /* BOOTINFO_H */
eof
