multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/hardware.h&n; *&n; * Copyright (C) 1996 Russell King.&n; *&n; * This file contains the hardware definitions of the&n; * Acorn Archimedes/A5000 machines.&n; *&n; * Modifications:&n; *  04-04-1998&t;PJB/RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * What hardware must be present - these can be tested by the kernel&n; * source.&n; */
DECL|macro|HAS_IOC
mdefine_line|#define HAS_IOC
macro_line|#include &lt;asm/ioc.h&gt;
DECL|macro|HAS_MEMC
mdefine_line|#define HAS_MEMC
macro_line|#include &lt;asm/memc.h&gt;
DECL|macro|HAS_MEMC1A
mdefine_line|#define HAS_MEMC1A
DECL|macro|HAS_VIDC
mdefine_line|#define HAS_VIDC
multiline_comment|/*&n; * Optional hardware&n; */
DECL|macro|HAS_EXPMASK
mdefine_line|#define HAS_EXPMASK
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x03000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0x03000000
multiline_comment|/*&n; * Screen mapping information&n; */
DECL|macro|SCREEN_START
mdefine_line|#define SCREEN_START&t;&t;0x02000000
DECL|macro|SCREEN2_END
mdefine_line|#define SCREEN2_END&t;&t;0x02078000
DECL|macro|SCREEN2_BASE
mdefine_line|#define SCREEN2_BASE&t;&t;0x02000000
DECL|macro|SCREEN1_END
mdefine_line|#define SCREEN1_END&t;&t;0x02000000
DECL|macro|SCREEN1_BASE
mdefine_line|#define SCREEN1_BASE&t;&t;0x01f88000
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * for use with inb/outb&n; */
DECL|macro|IO_VIDC_BASE
mdefine_line|#define IO_VIDC_BASE&t;&t;0x80100000
macro_line|#ifdef CONFIG_ARCH_ARC
DECL|macro|LATCHAADDR
mdefine_line|#define LATCHAADDR&t;&t;0x80094010
DECL|macro|LATCHBADDR
mdefine_line|#define LATCHBADDR&t;&t;0x80094006
macro_line|#endif
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0x80080000
DECL|macro|IO_EC_IOC4_BASE
mdefine_line|#define IO_EC_IOC4_BASE&t;&t;0x8009c000
DECL|macro|IO_EC_IOC_BASE
mdefine_line|#define IO_EC_IOC_BASE&t;&t;0x80090000
DECL|macro|IO_EC_MEMC_BASE
mdefine_line|#define IO_EC_MEMC_BASE&t;&t;0x80000000
multiline_comment|/*&n; * IO definitions&n; */
DECL|macro|EXPMASK_BASE
mdefine_line|#define EXPMASK_BASE&t;&t;((volatile unsigned char *)0x03360000)
DECL|macro|IOEB_BASE
mdefine_line|#define IOEB_BASE&t;&t;((volatile unsigned char *)0x03350050)
DECL|macro|PCIO_FLOPPYDMABASE
mdefine_line|#define PCIO_FLOPPYDMABASE&t;((volatile unsigned char *)0x0302a000)
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0x03010000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|MAPTOPHYS
mdefine_line|#define MAPTOPHYS(a)&t;&t;(((unsigned long)a &amp; 0x007fffff) + PAGE_OFFSET)
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((((unsigned long)(&amp;a)) &amp; 0x007fffff) + PAGE_OFFSET)
DECL|macro|GET_MEMORY_END
mdefine_line|#define GET_MEMORY_END(p)&t;(PAGE_OFFSET + (p-&gt;u1.s.page_size) * (p-&gt;u1.s.nr_pages))
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;(PAGE_OFFSET + 0x7c000)
DECL|macro|KERNEL_BASE
mdefine_line|#define KERNEL_BASE&t;&t;(PAGE_OFFSET + 0x80000)
macro_line|#else
DECL|macro|IOEB_BASE
mdefine_line|#define IOEB_BASE&t;&t;0x03350050
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0x03200000
DECL|macro|PCIO_FLOPPYDMABASE
mdefine_line|#define PCIO_FLOPPYDMABASE&t;0x0302a000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0x03010000
macro_line|#endif
macro_line|#endif
eof
