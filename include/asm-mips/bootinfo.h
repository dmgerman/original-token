multiline_comment|/*&n; * bootinfo.h -- Definition of the Linux/MIPS boot information structure&n; *&n; * Copyright (C) 1994 by Waldorf Electronics&n; * Written by Ralf Baechle and Andreas Busse&n; *&n; * Based on Linux/68k linux/include/linux/bootstrap.h&n; * Copyright (C) 1992 by Greg Harp&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_MIPS_BOOTINFO_H
DECL|macro|__ASM_MIPS_BOOTINFO_H
mdefine_line|#define __ASM_MIPS_BOOTINFO_H
multiline_comment|/*&n; * Valid machtype values&n; */
DECL|macro|MACH_UNKNOWN
mdefine_line|#define MACH_UNKNOWN&t;&t;0&t;&t;/* whatever...               */
DECL|macro|MACH_DESKSTATION_RPC44
mdefine_line|#define MACH_DESKSTATION_RPC44  1               /* Deskstation rPC44         */
DECL|macro|MACH_DESKSTATION_TYNE
mdefine_line|#define MACH_DESKSTATION_TYNE&t;2&t;&t;/* Deskstation Tyne          */
DECL|macro|MACH_ACER_PICA_61
mdefine_line|#define MACH_ACER_PICA_61&t;3&t;&t;/* Acer PICA-61 (PICA1)      */
DECL|macro|MACH_MIPS_MAGNUM_4000
mdefine_line|#define MACH_MIPS_MAGNUM_4000&t;4&t;&t;/* Mips Magnum 4000 &quot;RC4030&quot; */
DECL|macro|MACH_OLIVETTI_M700
mdefine_line|#define MACH_OLIVETTI_M700      5               /* Olivetti M700 */
DECL|macro|MACH_LAST
mdefine_line|#define MACH_LAST               5
DECL|macro|MACH_NAMES
mdefine_line|#define MACH_NAMES { &quot;unknown&quot;, &quot;Deskstation rPC44&quot;, &quot;Deskstation Tyne&quot;, &bslash;&n;&t;&quot;Acer PICA 61&quot;, &quot;Mips Magnum 4000&quot;, &quot;Olivetti M700&quot; }
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
DECL|macro|CPU_LAST
mdefine_line|#define CPU_LAST                20
DECL|macro|CPU_NAMES
mdefine_line|#define CPU_NAMES { &quot;unknown&quot;, &quot;R2000&quot;, &quot;R3000&quot;, &quot;R3000A&quot;, &quot;R3041&quot;, &quot;R3051&quot;, &bslash;&n;        &quot;R3052&quot;, &quot;R3081&quot;, &quot;R3081E&quot;, &quot;R4000PC&quot;, &quot;R4000SC&quot;, &quot;R4000MC&quot;,         &bslash;&n;        &quot;R4200&quot;, &quot;R4400PC&quot;, &quot;R4400SC&quot;, &quot;R4400MC&quot;, &quot;R4600&quot;, &quot;R6000&quot;,          &bslash;&n;        &quot;R6000A&quot;, &quot;R8000&quot;, &quot;R10000&quot; }
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE      (80)
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
multiline_comment|/*&n; * Some machine parameters passed by MILO. Note that bootinfo&n; * *must* be in the data segment since the kernel clears the&n; * bss segment directly after startup.&n; */
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
DECL|struct|bootinfo
r_struct
id|bootinfo
(brace
multiline_comment|/*&n;&t; * machine type&n;&t; */
DECL|member|machtype
r_int
r_int
id|machtype
suffix:semicolon
multiline_comment|/*&n;&t; * system CPU &amp; FPU&n;&t; */
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
multiline_comment|/*&n;&t; * Installed RAM&n;&t; */
DECL|member|memlower
r_int
r_int
id|memlower
suffix:semicolon
DECL|member|memupper
r_int
r_int
id|memupper
suffix:semicolon
multiline_comment|/*&n;&t; * Cache Sizes (0xffffffff = unknown)&n;&t; */
DECL|member|icache_size
r_int
r_int
id|icache_size
suffix:semicolon
DECL|member|icache_linesize
r_int
r_int
id|icache_linesize
suffix:semicolon
DECL|member|dcache_size
r_int
r_int
id|dcache_size
suffix:semicolon
DECL|member|dcache_linesize
r_int
r_int
id|dcache_linesize
suffix:semicolon
DECL|member|scache_size
r_int
r_int
id|scache_size
suffix:semicolon
DECL|member|scache_linesize
r_int
r_int
id|scache_linesize
suffix:semicolon
multiline_comment|/*&n;&t; * TLB Info&n;&t; */
DECL|member|tlb_entries
r_int
r_int
id|tlb_entries
suffix:semicolon
multiline_comment|/*&n;&t; * DMA buffer size (Deskstation only)&n;&t; */
DECL|member|dma_cache_size
r_int
r_int
id|dma_cache_size
suffix:semicolon
DECL|member|dma_cache_base
r_int
r_int
id|dma_cache_base
suffix:semicolon
multiline_comment|/*&n;&t; * Ramdisk Info&n;&t; */
DECL|member|ramdisk_flags
r_int
r_int
id|ramdisk_flags
suffix:semicolon
multiline_comment|/* ramdisk flags */
DECL|member|ramdisk_base
r_int
r_int
id|ramdisk_base
suffix:semicolon
multiline_comment|/* address of the ram disk in mem */
multiline_comment|/*&n;&t; * Boot flags for the kernel&n;&t; */
DECL|member|mount_root_rdonly
r_int
r_int
id|mount_root_rdonly
suffix:semicolon
DECL|member|drive_info
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
multiline_comment|/*&n;&t; * Video ram info (not in tty.h)&n;&t; */
DECL|member|vram_base
r_int
r_int
id|vram_base
suffix:semicolon
multiline_comment|/* video ram base address */
DECL|member|command_line
r_char
id|command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/* kernel command line parameters */
)brace
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n; * New style bootinfo&n; *&n; * Add new tags only at the end of the enum; *never* remove any tags&n; * or you&squot;ll break compatibility!&n; */
r_enum
id|bi_tag
(brace
multiline_comment|/*&n;&t; * not a real tag&n;&t; */
id|dummy
comma
multiline_comment|/*&n;&t; * machine type&n;&t; */
id|machtype
comma
multiline_comment|/*&n;&t; * system CPU &amp; FPU&n;&t; */
id|cputype
comma
multiline_comment|/*&n;&t; * Installed RAM&n;&t; */
id|memlower
comma
id|memupper
comma
multiline_comment|/*&n;&t; * Cache Sizes (0xffffffff = unknown)&n;&t; */
id|icache_size
comma
id|icache_linesize
comma
id|dcache_size
comma
id|dcache_linesize
comma
id|scache_size
comma
id|scache_linesize
comma
multiline_comment|/*&n;&t; * TLB Info&n;&t; */
id|tlb_entries
comma
multiline_comment|/*&n;&t; * DMA buffer size (Deskstation only)&n;&t; */
id|dma_cache_size
comma
id|dma_cache_base
comma
multiline_comment|/*&n;&t; * Ramdisk Info&n;&t; */
id|ramdisk_size
comma
multiline_comment|/* ramdisk size in 1024 byte blocks */
id|ramdisk_base
comma
multiline_comment|/* address of the ram disk in mem */
multiline_comment|/*&n;&t; * Boot flags for the kernel&n;&t; */
id|mount_root_rdonly
comma
id|drive_info
comma
multiline_comment|/*&n;&t; * Video ram info (not in tty.h)&n;&t; */
id|vram_base
comma
multiline_comment|/* video ram base address */
id|command_line
multiline_comment|/* kernel command line parameters */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
id|bi_tag
id|tag
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
)brace
id|tag
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|bootinfo
id|boot_info
suffix:semicolon
multiline_comment|/*&n; * Defaults, may be overwritten by milo. We initialize&n; * them to make sure that both boot_info and screen_info&n; * are in the .data segment since the .bss segment is&n; * cleared during startup.&n; */
DECL|macro|BOOT_INFO
mdefine_line|#define BOOT_INFO { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, {{0,}}, 0, &quot;&quot; }
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO {0, 0, {0, }, 52, 3, 80, 4626, 3, 9, 50}
macro_line|#else /* !__LANGUAGE_ASSEMBLY__ */
multiline_comment|/*&n; * Same structure, but as offsets for usage within assembler source.&n; * Don&squot;t mess with struct bootinfo without changing offsets too!&n; */
DECL|macro|OFFSET_BOOTINFO_MACHTYPE
mdefine_line|#define OFFSET_BOOTINFO_MACHTYPE           0
DECL|macro|OFFSET_BOOTINFO_CPUTYPE
mdefine_line|#define OFFSET_BOOTINFO_CPUTYPE            4
DECL|macro|OFFSET_BOOTINFO_MEMLOWER
mdefine_line|#define OFFSET_BOOTINFO_MEMLOWER           8
DECL|macro|OFFSET_BOOTINFO_MEMUPPER
mdefine_line|#define OFFSET_BOOTINFO_MEMUPPER          12
DECL|macro|OFFSET_BOOTINFO_ICACHE_SIZE
mdefine_line|#define OFFSET_BOOTINFO_ICACHE_SIZE       16
DECL|macro|OFFSET_BOOTINFO_ICACHE_LINESIZE
mdefine_line|#define OFFSET_BOOTINFO_ICACHE_LINESIZE   20
DECL|macro|OFFSET_BOOTINFO_DCACHE_SIZE
mdefine_line|#define OFFSET_BOOTINFO_DCACHE_SIZE       24
DECL|macro|OFFSET_BOOTINFO_DCACHE_LINESIZE
mdefine_line|#define OFFSET_BOOTINFO_DCACHE_LINESIZE   28
DECL|macro|OFFSET_BOOTINFO_SCACHE_SIZE
mdefine_line|#define OFFSET_BOOTINFO_SCACHE_SIZE       32
DECL|macro|OFFSET_BOOTINFO_SCACHE_LINESIZE
mdefine_line|#define OFFSET_BOOTINFO_SCACHE_LINESIZE   36
DECL|macro|OFFSET_BOOTINFO_TLB_ENTRIES
mdefine_line|#define OFFSET_BOOTINFO_TLB_ENTRIES       40
DECL|macro|OFFSET_BOOTINFO_DMA_CACHE_SIZE
mdefine_line|#define OFFSET_BOOTINFO_DMA_CACHE_SIZE    44
DECL|macro|OFFSET_BOOTINFO_DMA_CACHE_BASE
mdefine_line|#define OFFSET_BOOTINFO_DMA_CACHE_BASE    48
DECL|macro|OFFSET_BOOTINFO_RAMDISK_SIZE
mdefine_line|#define OFFSET_BOOTINFO_RAMDISK_SIZE      52
DECL|macro|OFFSET_BOOTINFO_RAMDISK_BASE
mdefine_line|#define OFFSET_BOOTINFO_RAMDISK_BASE      56
DECL|macro|OFFSET_BOOTINFO_MOUNT_RD_ONLY
mdefine_line|#define OFFSET_BOOTINFO_MOUNT_RD_ONLY     60
DECL|macro|OFFSET_BOOTINFO_DRIVE_INFO
mdefine_line|#define OFFSET_BOOTINFO_DRIVE_INFO        64
DECL|macro|OFFSET_BOOTINFO_VRAM_BASE
mdefine_line|#define OFFSET_BOOTINFO_VRAM_BASE         96
DECL|macro|OFFSET_BOOTINFO_COMMAND_LINE
mdefine_line|#define OFFSET_BOOTINFO_COMMAND_LINE      100
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
macro_line|#endif /* __ASM_MIPS_BOOTINFO_H */
eof
