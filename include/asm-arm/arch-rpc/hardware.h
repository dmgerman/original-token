multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/hardware.h&n; *&n; * Copyright (C) 1996 Russell King.&n; *&n; * This file contains the hardware definitions of the RiscPC series machines.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * What hardware must be present&n; */
DECL|macro|HAS_IOMD
mdefine_line|#define HAS_IOMD
DECL|macro|HAS_VIDC20
mdefine_line|#define HAS_VIDC20
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE&t;&t;0x10000000
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;&t;0x10000000
DECL|macro|EASI_SIZE
mdefine_line|#define EASI_SIZE&t;&t;0x08000000&t;/* EASI I/O */
DECL|macro|EASI_START
mdefine_line|#define EASI_START&t;&t;0x08000000
DECL|macro|EASI_BASE
mdefine_line|#define EASI_BASE&t;&t;0xe8000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x03000000&t;/* I/O */
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|SCREEN_START
mdefine_line|#define SCREEN_START&t;&t;0x02000000&t;/* VRAM */
DECL|macro|SCREEN2_END
mdefine_line|#define SCREEN2_END&t;&t;0xe0000000
DECL|macro|SCREEN2_BASE
mdefine_line|#define SCREEN2_BASE&t;&t;0xd8000000
DECL|macro|SCREEN1_END
mdefine_line|#define SCREEN1_END&t;&t;0xd8000000
DECL|macro|SCREEN1_BASE
mdefine_line|#define SCREEN1_BASE&t;&t;0xd0000000
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * for use with inb/outb&n; */
DECL|macro|IO_VIDC_AUDIO_BASE
mdefine_line|#define IO_VIDC_AUDIO_BASE&t;0x80140000
DECL|macro|IO_VIDC_BASE
mdefine_line|#define IO_VIDC_BASE&t;&t;0x80100000
DECL|macro|IO_IOMD_BASE
mdefine_line|#define IO_IOMD_BASE&t;&t;0x80080000
DECL|macro|IO_EC_EASI_BASE
mdefine_line|#define IO_EC_EASI_BASE&t;&t;0x82000000
DECL|macro|IO_EC_IOC4_BASE
mdefine_line|#define IO_EC_IOC4_BASE&t;&t;0x8009c000
DECL|macro|IO_EC_IOC_BASE
mdefine_line|#define IO_EC_IOC_BASE&t;&t;0x80090000
DECL|macro|IO_EC_MEMC8_BASE
mdefine_line|#define IO_EC_MEMC8_BASE&t;0x8000ac00
DECL|macro|IO_EC_MEMC_BASE
mdefine_line|#define IO_EC_MEMC_BASE&t;&t;0x80000000
multiline_comment|/*&n; * IO definitions&n; */
DECL|macro|EXPMASK_BASE
mdefine_line|#define EXPMASK_BASE&t;&t;((volatile unsigned char *)0xe0360000)
DECL|macro|IOEB_BASE
mdefine_line|#define IOEB_BASE&t;&t;((volatile unsigned char *)0xe0350050)
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;((volatile unsigned char *)0xe0200000)
DECL|macro|PCIO_FLOPPYDMABASE
mdefine_line|#define PCIO_FLOPPYDMABASE&t;((volatile unsigned char *)0xe002a000)
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0010000
multiline_comment|/*&n; * Offsets from RAM base&n; */
DECL|macro|PARAMS_OFFSET
mdefine_line|#define PARAMS_OFFSET&t;&t;0x0100
DECL|macro|KERNEL_OFFSET
mdefine_line|#define KERNEL_OFFSET&t;&t;0x8000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|MAPTOPHYS
mdefine_line|#define MAPTOPHYS(x)&t;&t;(x)
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(x)&t;&t;((unsigned long)(&amp;x))
DECL|macro|GET_MEMORY_END
mdefine_line|#define GET_MEMORY_END(p)&t;(PAGE_OFFSET + p-&gt;u1.s.page_size * &bslash;&n;&t;&t;&t;&t;&t;&t;(p-&gt;u1.s.pages_in_bank[0] + &bslash;&n;&t;&t;&t;&t;&t;&t; p-&gt;u1.s.pages_in_bank[1] + &bslash;&n;&t;&t;&t;&t;&t;&t; p-&gt;u1.s.pages_in_bank[2] + &bslash;&n;&t;&t;&t;&t;&t;&t; p-&gt;u1.s.pages_in_bank[3]))
DECL|macro|KERNEL_BASE
mdefine_line|#define KERNEL_BASE&t;&t;(PAGE_OFFSET + KERNEL_OFFSET)
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;(PAGE_OFFSET + PARAMS_OFFSET)
DECL|macro|Z_PARAMS_BASE
mdefine_line|#define Z_PARAMS_BASE&t;&t;(RAM_START + PARAMS_OFFSET)
DECL|macro|SAFE_ADDR
mdefine_line|#define SAFE_ADDR&t;&t;0x00000000&t;/* ROM */
macro_line|#else
DECL|macro|VIDC_SND_BASE
mdefine_line|#define VIDC_SND_BASE&t;&t;0xe0500000
DECL|macro|VIDC_BASE
mdefine_line|#define VIDC_BASE&t;&t;0xe0400000
DECL|macro|IOMD_BASE
mdefine_line|#define IOMD_BASE&t;&t;0xe0200000
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0xe0200000
DECL|macro|PCIO_FLOPPYDMABASE
mdefine_line|#define PCIO_FLOPPYDMABASE&t;0xe002a000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0010000
macro_line|#endif
macro_line|#endif
eof
