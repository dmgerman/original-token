multiline_comment|/*&n; * arch/arm/mm/mm-sa1100.c&n; *&n; * Extra MM routines for the SA1100 architecture&n; *&n; * Copyright (C) 1998-1999 Russell King&n; * Copyright (C) 1999 Hugo Fiennes&n; *&n; * 1999/09/12 Nicolas Pitre &lt;nico@visuaide.com&gt;&n; *&t;Specific RAM implementation details are in&n; *&t;linux/include/asm/arch-sa1100/memory.h now.&n; *&t;Allows for better macro optimisations when possible.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|macro|SIZE
mdefine_line|#define SIZE(x) (sizeof(x) / sizeof(x[0]))
multiline_comment|/*&n; * These are the memory size mappings for the&n; * SA1100.  Note that LART is a special case -&n; * it doesn&squot;t use physical address A23 on the&n; * DRAM, so we effectively have 4 * 8MB in&n; * two banks.&n; */
DECL|variable|__initdata
r_struct
id|mem_desc
id|mem_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virt start virt end */
macro_line|#if defined(CONFIG_SA1100_BRUTUS)
(brace
l_int|0xc0000000
comma
l_int|0xc0400000
)brace
comma
multiline_comment|/* 4MB */
(brace
l_int|0xc1000000
comma
l_int|0xc1400000
)brace
comma
multiline_comment|/* 4MB */
(brace
l_int|0xc2000000
comma
l_int|0xc2400000
)brace
comma
multiline_comment|/* 4MB */
(brace
l_int|0xc3000000
comma
l_int|0xc3400000
)brace
multiline_comment|/* 4MB */
macro_line|#elif defined(CONFIG_SA1100_EMPEG)
(brace
l_int|0xc0000000
comma
l_int|0xc0400000
)brace
comma
multiline_comment|/* 4MB */
(brace
l_int|0xc1000000
comma
l_int|0xc1400000
)brace
multiline_comment|/* 4MB */
macro_line|#elif defined(CONFIG_SA1100_LART)
(brace
l_int|0xc0000000
comma
l_int|0xc0800000
)brace
comma
multiline_comment|/* 16MB */
(brace
l_int|0xc1000000
comma
l_int|0xc1800000
)brace
comma
(brace
l_int|0xc2000000
comma
l_int|0xc2800000
)brace
comma
multiline_comment|/* 16MB */
(brace
l_int|0xc3000000
comma
l_int|0xc3800000
)brace
macro_line|#elif defined(CONFIG_SA1100_VICTOR)
(brace
l_int|0xc0000000
comma
l_int|0xc0400000
)brace
multiline_comment|/* 4MB */
macro_line|#elif defined(CONFIG_SA1100_TIFON)
(brace
l_int|0xc0000000
comma
l_int|0xc1000000
)brace
comma
multiline_comment|/* 16MB */
(brace
l_int|0xc1000000
comma
l_int|0xc2000000
)brace
multiline_comment|/* 16MB */
macro_line|#else
macro_line|#error missing memory configuration
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|mem_desc_size
r_int
r_int
id|__initdata
id|mem_desc_size
op_assign
id|SIZE
c_func
(paren
id|mem_desc
)paren
suffix:semicolon
DECL|variable|__initdata
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual           physical     length     domain    r  w  c  b */
macro_line|#if defined(CONFIG_SA1100_VICTOR)
(brace
l_int|0xd0000000
comma
l_int|0x00000000
comma
l_int|0x00200000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash */
macro_line|#elif defined(CONFIG_SA1100_EMPEG)
(brace
id|EMPEG_FLASHBASE
comma
l_int|0x00000000
comma
l_int|0x00200000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash */
macro_line|#elif defined(CONFIG_SA1100_TIFON)
(brace
l_int|0xd0000000
comma
l_int|0x00000000
comma
l_int|0x00800000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash bank 1 */
(brace
l_int|0xd0800000
comma
l_int|0x08000000
comma
l_int|0x00800000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash bank 2 */
macro_line|#endif
macro_line|#ifdef CONFIG_SA1101
(brace
l_int|0xdc000000
comma
id|SA1101_BASE
comma
l_int|0x00400000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SA1101 */
macro_line|#endif
(brace
l_int|0xe0000000
comma
l_int|0x20000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA0 IO */
(brace
l_int|0xe4000000
comma
l_int|0x30000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA1 IO */
(brace
l_int|0xe8000000
comma
l_int|0x28000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA0 attr */
(brace
l_int|0xec000000
comma
l_int|0x38000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA1 attr */
(brace
l_int|0xf0000000
comma
l_int|0x2c000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA0 mem */
(brace
l_int|0xf4000000
comma
l_int|0x3c000000
comma
l_int|0x04000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCMCIA1 mem */
(brace
l_int|0xf8000000
comma
l_int|0x80000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCM */
(brace
l_int|0xfa000000
comma
l_int|0x90000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SCM */
(brace
l_int|0xfc000000
comma
l_int|0xa0000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* MER */
(brace
l_int|0xfe000000
comma
l_int|0xb0000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* LCD + DMA */
)brace
suffix:semicolon
DECL|variable|io_desc_size
r_int
r_int
id|__initdata
id|io_desc_size
op_assign
id|SIZE
c_func
(paren
id|io_desc
)paren
suffix:semicolon
eof
