multiline_comment|/*&n; * linux/include/asm-arm/mm-init.h&n; *&n; * Copyright (C) 1997,1998 Russell King&n; *&n; * Contained within are structures to describe how to set up the&n; * initial memory map.  It includes both a processor-specific header&n; * for parsing these structures, and an architecture-specific header&n; * to fill out the structures.&n; */
macro_line|#ifndef __ASM_MM_INIT_H
DECL|macro|__ASM_MM_INIT_H
mdefine_line|#define __ASM_MM_INIT_H
r_typedef
r_enum
(brace
singleline_comment|// physical address is absolute
DECL|enumerator|init_mem_map_absolute
id|init_mem_map_absolute
comma
multiline_comment|/* physical address is relative to start_mem&n;&t; *  as passed in paging_init&n;&t; */
DECL|enumerator|init_mem_map_relative_start_mem
id|init_mem_map_relative_start_mem
DECL|typedef|init_memmap_type_t
)brace
id|init_memmap_type_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|init_memmap_type_t
id|type
suffix:semicolon
DECL|member|physical_address
r_int
r_int
id|physical_address
suffix:semicolon
DECL|member|virtual_address
r_int
r_int
id|virtual_address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|init_memmap_t
)brace
id|init_memmap_t
suffix:semicolon
DECL|macro|INIT_MEM_MAP_SENTINEL
mdefine_line|#define INIT_MEM_MAP_SENTINEL { init_mem_map_absolute, 0, 0, 0 }
DECL|macro|INIT_MEM_MAP_ABSOLUTE
mdefine_line|#define INIT_MEM_MAP_ABSOLUTE(p,l,s) { init_mem_map_absolute,p,l,s }
DECL|macro|INIT_MEM_MAP_RELATIVE
mdefine_line|#define INIT_MEM_MAP_RELATIVE(o,l,s) { init_mem_map_relative_start_mem,o,l,s }
multiline_comment|/*&n; * Within this file, initialise an array of init_mem_map_t&squot;s&n; * to describe your initial memory mapping structure.&n; */
macro_line|#include &lt;asm/arch/mm-init.h&gt;
multiline_comment|/*&n; * Contained within this file is code to read the array&n; * of init_mem_map_t&squot;s created above.&n; */
macro_line|#include &lt;asm/proc/mm-init.h&gt;
macro_line|#endif
eof
