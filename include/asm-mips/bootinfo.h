multiline_comment|/*&n; * bootinfo.h -- Definition of the Linux/MIPS boot information structure&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle, Andreas Busse,&n; *                             Stoned Elipot and Paul M. Antoine.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * $Id: bootinfo.h,v 1.3 1997/09/19 08:37:44 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_BOOTINFO_H
DECL|macro|__ASM_MIPS_BOOTINFO_H
mdefine_line|#define __ASM_MIPS_BOOTINFO_H
multiline_comment|/* XXX */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Values for machgroup&n; */
DECL|macro|MACH_GROUP_UNKNOWN
mdefine_line|#define MACH_GROUP_UNKNOWN      0 /* whatever... */
DECL|macro|MACH_GROUP_JAZZ
mdefine_line|#define MACH_GROUP_JAZZ     &t;1 /* Jazz                                     */
DECL|macro|MACH_GROUP_DEC
mdefine_line|#define MACH_GROUP_DEC          2 /* Digital Equipment                        */
DECL|macro|MACH_GROUP_ARC
mdefine_line|#define MACH_GROUP_ARC&t;&t;3 /* Wreckstation Tyne, rPC44, possibly other */
DECL|macro|MACH_GROUP_SNI_RM
mdefine_line|#define MACH_GROUP_SNI_RM&t;4 /* Siemens Nixdorf RM series                */
DECL|macro|MACH_GROUP_ACN
mdefine_line|#define MACH_GROUP_ACN&t;&t;5
DECL|macro|MACH_GROUP_SGI
mdefine_line|#define MACH_GROUP_SGI          6 /* Silicon Graphics workstations and servers */
DECL|macro|GROUP_NAMES
mdefine_line|#define GROUP_NAMES { &quot;unknown&quot;, &quot;Jazz&quot;, &quot;Digital&quot;, &quot;ARC&quot;, &bslash;&n;                      &quot;SNI&quot;, &quot;ACN&quot;, &quot;SGI&quot; }
multiline_comment|/*&n; * Valid machtype values for group unknown (low order halfword of mips_machtype)&n; */
DECL|macro|MACH_UNKNOWN
mdefine_line|#define MACH_UNKNOWN&t;&t;0&t;/* whatever...&t;&t;&t;*/
DECL|macro|GROUP_UNKNOWN_NAMES
mdefine_line|#define GROUP_UNKNOWN_NAMES { &quot;unknown&quot; }
multiline_comment|/*&n; * Valid machtype values for group JAZZ&n; */
DECL|macro|MACH_ACER_PICA_61
mdefine_line|#define MACH_ACER_PICA_61&t;0&t;/* Acer PICA-61 (PICA1)&t;&t;*/
DECL|macro|MACH_MIPS_MAGNUM_4000
mdefine_line|#define MACH_MIPS_MAGNUM_4000&t;1&t;/* Mips Magnum 4000 &quot;RC4030&quot;&t;*/
DECL|macro|MACH_OLIVETTI_M700
mdefine_line|#define MACH_OLIVETTI_M700      2&t;/* Olivetti M700-10 (-15 ??)    */
DECL|macro|GROUP_JAZZ_NAMES
mdefine_line|#define GROUP_JAZZ_NAMES { &quot;Acer PICA 61&quot;, &quot;Mips Magnum 4000&quot;, &quot;Olivetti M700&quot; }
multiline_comment|/*&n; * Valid machtype for group DEC &n; */
multiline_comment|/* FIXME: this is a very fuzzy name, and we got a big &quot;name space now&quot; */
multiline_comment|/* So otiginal DEC codes can be used -Stoned */
DECL|macro|MACH_DECSTATION
mdefine_line|#define MACH_DECSTATION&t;&t;0&t;/* DECStation 5000/2x for now */
DECL|macro|GROUP_DEC_NAMES
mdefine_line|#define GROUP_DEC_NAMES { &quot;3min&quot; }
multiline_comment|/*&n; * Valid machtype for group ARC&n; */
DECL|macro|MACH_DESKSTATION_RPC44
mdefine_line|#define MACH_DESKSTATION_RPC44  0&t;/* Deskstation rPC44 */
DECL|macro|MACH_DESKSTATION_TYNE
mdefine_line|#define MACH_DESKSTATION_TYNE&t;1&t;/* Deskstation Tyne */
DECL|macro|GROUP_ARC_NAMES
mdefine_line|#define GROUP_ARC_NAMES { &quot;Deskstation rPC44&quot;, &quot;Deskstation Tyne&quot; }
multiline_comment|/*&n; * Valid machtype for group SNI_RM&n; */
DECL|macro|MACH_SNI_RM200_PCI
mdefine_line|#define MACH_SNI_RM200_PCI&t;0&t;/* RM200/RM300/RM400 PCI series */
DECL|macro|GROUP_SNI_RM_NAMES
mdefine_line|#define GROUP_SNI_RM_NAMES { &quot;RM200 PCI&quot; }
multiline_comment|/*&n; * Valid machtype for group ACN&n; */
DECL|macro|MACH_ACN_MIPS_BOARD
mdefine_line|#define MACH_ACN_MIPS_BOARD&t;0       /* ACN MIPS single board        */
DECL|macro|GROUP_ACN_NAMES
mdefine_line|#define GROUP_ACN_NAMES { &quot;ACN&quot; }
multiline_comment|/*&n; * Valid machtype for group SGI&n; */
DECL|macro|MACH_SGI_INDY
mdefine_line|#define MACH_SGI_INDY&t;&t;0&t;/* R4?K and R5K Indy workstaions */
DECL|macro|GROUP_SGI_NAMES
mdefine_line|#define GROUP_SGI_NAMES { &quot;Indy&quot; }
DECL|macro|GROUP_SGI_NAMES
mdefine_line|#define GROUP_SGI_NAMES { &quot;Indy&quot; }
multiline_comment|/*&n; * Valid cputype values&n; */
DECL|macro|CPU_UNKNOWN
mdefine_line|#define CPU_UNKNOWN&t;&t;0
DECL|macro|CPU_R2000
mdefine_line|#define CPU_R2000&t;&t;1
DECL|macro|CPU_R3000
mdefine_line|#define CPU_R3000&t;&t;2
DECL|macro|CPU_R3000A
mdefine_line|#define CPU_R3000A&t;&t;3
DECL|macro|CPU_R3041
mdefine_line|#define CPU_R3041&t;&t;4
DECL|macro|CPU_R3051
mdefine_line|#define CPU_R3051&t;&t;5
DECL|macro|CPU_R3052
mdefine_line|#define CPU_R3052&t;&t;6
DECL|macro|CPU_R3081
mdefine_line|#define CPU_R3081&t;&t;7
DECL|macro|CPU_R3081E
mdefine_line|#define CPU_R3081E&t;&t;8
DECL|macro|CPU_R4000PC
mdefine_line|#define CPU_R4000PC&t;&t;9
DECL|macro|CPU_R4000SC
mdefine_line|#define CPU_R4000SC&t;&t;10
DECL|macro|CPU_R4000MC
mdefine_line|#define CPU_R4000MC&t;&t;11
DECL|macro|CPU_R4200
mdefine_line|#define CPU_R4200&t;&t;12
DECL|macro|CPU_R4400PC
mdefine_line|#define CPU_R4400PC&t;&t;13
DECL|macro|CPU_R4400SC
mdefine_line|#define CPU_R4400SC&t;&t;14
DECL|macro|CPU_R4400MC
mdefine_line|#define CPU_R4400MC&t;&t;15
DECL|macro|CPU_R4600
mdefine_line|#define CPU_R4600&t;&t;16
DECL|macro|CPU_R6000
mdefine_line|#define CPU_R6000&t;&t;17
DECL|macro|CPU_R6000A
mdefine_line|#define CPU_R6000A&t;&t;18
DECL|macro|CPU_R8000
mdefine_line|#define CPU_R8000&t;&t;19
DECL|macro|CPU_R10000
mdefine_line|#define CPU_R10000&t;&t;20
DECL|macro|CPU_R4300
mdefine_line|#define CPU_R4300&t;&t;21
DECL|macro|CPU_R4650
mdefine_line|#define CPU_R4650&t;&t;22
DECL|macro|CPU_R4700
mdefine_line|#define CPU_R4700&t;&t;23
DECL|macro|CPU_R5000
mdefine_line|#define CPU_R5000&t;&t;24
DECL|macro|CPU_R5000A
mdefine_line|#define CPU_R5000A&t;&t;25
DECL|macro|CPU_R4640
mdefine_line|#define CPU_R4640&t;&t;26
DECL|macro|CPU_NEVADA
mdefine_line|#define CPU_NEVADA&t;&t;27&t;/* RM5230, RM5260 */
DECL|macro|CPU_LAST
mdefine_line|#define CPU_LAST&t;&t;27
DECL|macro|CPU_NAMES
mdefine_line|#define CPU_NAMES { &quot;unknown&quot;, &quot;R2000&quot;, &quot;R3000&quot;, &quot;R3000A&quot;, &quot;R3041&quot;, &quot;R3051&quot;, &bslash;&n;        &quot;R3052&quot;, &quot;R3081&quot;, &quot;R3081E&quot;, &quot;R4000PC&quot;, &quot;R4000SC&quot;, &quot;R4000MC&quot;,         &bslash;&n;        &quot;R4200&quot;, &quot;R4400PC&quot;, &quot;R4400SC&quot;, &quot;R4400MC&quot;, &quot;R4600&quot;, &quot;R6000&quot;,          &bslash;&n;        &quot;R6000A&quot;, &quot;R8000&quot;, &quot;R10000&quot;, &quot;R4300&quot;, &quot;R4650&quot;, &quot;R4700&quot;, &quot;R5000&quot;,     &bslash;&n;        &quot;R5000A&quot;, &quot;R4640&quot;, &quot;Nevada&quot; }
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE      (80)
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
multiline_comment|/*&n; * Some machine parameters passed by the bootloaders. &n; */
DECL|struct|drive_info_struct
r_struct
id|drive_info_struct
(brace
DECL|member|dummy
r_char
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is the same as in Milo but renamed for the sake of kernel&squot;s */
multiline_comment|/* namespace */
DECL|struct|mips_arc_DisplayInfo
r_typedef
r_struct
id|mips_arc_DisplayInfo
(brace
multiline_comment|/* video adapter information */
DECL|member|cursor_x
r_int
r_int
id|cursor_x
suffix:semicolon
DECL|member|cursor_y
r_int
r_int
id|cursor_y
suffix:semicolon
DECL|member|columns
r_int
r_int
id|columns
suffix:semicolon
DECL|member|lines
r_int
r_int
id|lines
suffix:semicolon
DECL|typedef|mips_arc_DisplayInfo
)brace
id|mips_arc_DisplayInfo
suffix:semicolon
multiline_comment|/*&n; * New style bootinfo&n; *&n; * Add new tags only at the end of the enum; *never* remove any tags&n; * or you&squot;ll break compatibility!&n; */
DECL|enum|bi_tag
r_enum
id|bi_tag
(brace
multiline_comment|/*&n; &t; * not a real tag&n; &t; */
DECL|enumerator|tag_dummy
id|tag_dummy
comma
multiline_comment|/*&n; &t; * machine type&n; &t; */
DECL|enumerator|tag_machtype
id|tag_machtype
comma
multiline_comment|/*&n; &t; * system CPU &amp; FPU&n; &t; */
DECL|enumerator|tag_cputype
id|tag_cputype
comma
multiline_comment|/*&n; &t; * Installed RAM&n; &t; */
DECL|enumerator|tag_memlower
id|tag_memlower
comma
DECL|enumerator|tag_memupper
id|tag_memupper
comma
multiline_comment|/*&n; &t; * Cache Sizes (0xffffffff = unknown)&n; &t; */
DECL|enumerator|tag_icache_size
id|tag_icache_size
comma
DECL|enumerator|tag_icache_linesize
id|tag_icache_linesize
comma
DECL|enumerator|tag_dcache_size
id|tag_dcache_size
comma
DECL|enumerator|tag_dcache_linesize
id|tag_dcache_linesize
comma
DECL|enumerator|tag_scache_size
id|tag_scache_size
comma
DECL|enumerator|tag_scache_linesize
id|tag_scache_linesize
comma
multiline_comment|/*&n; &t; * TLB Info&n; &t; */
DECL|enumerator|tag_tlb_entries
id|tag_tlb_entries
comma
multiline_comment|/*&n; &t; * DMA buffer size (Deskstation only)&n; &t; */
DECL|enumerator|tag_dma_cache_size
id|tag_dma_cache_size
comma
DECL|enumerator|tag_dma_cache_base
id|tag_dma_cache_base
comma
multiline_comment|/*&n;&t; * Ramdisk Info &n; &t; */
DECL|enumerator|tag_ramdisk_size
id|tag_ramdisk_size
comma
multiline_comment|/* ramdisk size in 1024 byte blocks */
DECL|enumerator|tag_ramdisk_base
id|tag_ramdisk_base
comma
multiline_comment|/* address of the ram disk in mem */
multiline_comment|/*&n; &t; * Boot flags for the kernel&n; &t; */
DECL|enumerator|tag_mount_root_rdonly
id|tag_mount_root_rdonly
comma
DECL|enumerator|tag_drive_info
id|tag_drive_info
comma
multiline_comment|/*&n; &t; * Video ram info (not in tty.h)&n; &t; */
DECL|enumerator|tag_vram_base
id|tag_vram_base
comma
multiline_comment|/* video ram base address */
DECL|enumerator|tag_command_line
id|tag_command_line
comma
multiline_comment|/* kernel command line parameters */
multiline_comment|/*&n;         * machine group&n;         */
DECL|enumerator|tag_machgroup
id|tag_machgroup
comma
multiline_comment|/*&n;&t; * info on the display from the ARC BIOS&n;&t; */
DECL|enumerator|tag_arcdisplayinfo
id|tag_arcdisplayinfo
comma
multiline_comment|/*&n;&t; * tag to pass a complete struct screen_info&n;&t; */
DECL|enumerator|tag_screen_info
id|tag_screen_info
)brace
suffix:semicolon
multiline_comment|/* struct defining a tag */
r_typedef
r_struct
(brace
DECL|member|tag
r_enum
id|bi_tag
id|tag
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|tag
)brace
id|tag
suffix:semicolon
multiline_comment|/* struct to define a tag and it&squot;s data */
r_typedef
r_struct
(brace
DECL|member|t
id|tag
id|t
suffix:semicolon
DECL|member|d
r_void
op_star
id|d
suffix:semicolon
DECL|typedef|tag_def
)brace
id|tag_def
suffix:semicolon
multiline_comment|/* macros for parsing tag list */
DECL|macro|TAGVALPTR
mdefine_line|#define TAGVALPTR(t) ((void*)(((void*)(t)) - ((t)-&gt;size)))
DECL|macro|NEXTTAGPTR
mdefine_line|#define NEXTTAGPTR(t) ((void*)(TAGVALPTR(t) - (sizeof(tag))))
multiline_comment|/* size macros for tag size field */
DECL|macro|UCHARSIZE
mdefine_line|#define UCHARSIZE (sizeof(unsigned char))
DECL|macro|ULONGSIZE
mdefine_line|#define ULONGSIZE (sizeof(unsigned long))
DECL|macro|UINTSIZE
mdefine_line|#define UINTSIZE  (sizeof(unsigned int))
DECL|macro|DRVINFOSIZE
mdefine_line|#define DRVINFOSIZE (sizeof(struct drive_info_struct))
DECL|macro|CMDLINESIZE
mdefine_line|#define CMDLINESIZE (sizeof(char[CL_SIZE])
multiline_comment|/*&n; * For tag readers aka the kernel&n; */
id|tag
op_star
id|bi_TagFind
c_func
(paren
r_enum
id|bi_tag
id|type
)paren
suffix:semicolon
r_void
id|bi_EarlySnarf
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* For tag creators aka bootloaders */
multiline_comment|/* Now implemented in Milo 0.26 */
r_int
id|bi_TagAdd
c_func
(paren
r_enum
id|bi_tag
id|type
comma
r_int
r_int
id|size
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_int
id|bi_TagAddList
c_func
(paren
id|tag_def
op_star
id|taglist
)paren
suffix:semicolon
r_void
id|bi_TagWalk
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SGI
multiline_comment|/* screen info will dissapear... soon */
DECL|macro|DEFAULT_SCREEN_INFO
mdefine_line|#define DEFAULT_SCREEN_INFO {0, 0, {0, 0, }, 0, 0, 158, 0, 0, 0, 62, 0, 16}
DECL|macro|DEFAULT_DRIVE_INFO
mdefine_line|#define DEFAULT_DRIVE_INFO { {0,}}
macro_line|#else
multiline_comment|/* default values for screen_info variable */
DECL|macro|DEFAULT_SCREEN_INFO
mdefine_line|#define DEFAULT_SCREEN_INFO {0, 0, {0, }, 52, 3, 80, 4626, 3, 9, 50}
multiline_comment|/* default values for drive info */
DECL|macro|DEFAULT_DRIVE_INFO
mdefine_line|#define DEFAULT_DRIVE_INFO { {0,}}
macro_line|#endif
multiline_comment|/*&n; * These are the kernel variables initialized from&n; * the tag. And they have to be initialized to dummy/default&n; * values in setup.c (or whereever suitable) so they are in&n; * .data section&n; */
r_extern
r_int
r_int
id|mips_memory_upper
suffix:semicolon
r_extern
r_int
r_int
id|mips_cputype
suffix:semicolon
r_extern
r_int
r_int
id|mips_machtype
suffix:semicolon
r_extern
r_int
r_int
id|mips_machgroup
suffix:semicolon
r_extern
r_int
r_int
id|mips_tlb_entries
suffix:semicolon
r_extern
r_int
r_int
id|mips_vram_base
suffix:semicolon
r_extern
r_int
r_int
id|mips_dma_cache_size
suffix:semicolon
r_extern
r_int
r_int
id|mips_dma_cache_base
suffix:semicolon
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
macro_line|#endif /* __ASM_MIPS_BOOTINFO_H */
eof
