multiline_comment|/*&n; * fixmap.h: compile-time virtual memory allocation&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998 Ingo Molnar&n; */
macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; * Here we define all the compile-time &squot;special&squot; virtual&n; * addresses. The point is to have a constant address at&n; * compile time, but to set the physical address only&n; * in the boot process. We allocate these special  addresses&n; * from the end of virtual memory (0xfffff000) backwards.&n; * Also this lets us do fail-safe vmalloc(), we&n; * can guarantee that these special addresses and&n; * vmalloc()-ed addresses never overlap.&n; *&n; * these &squot;compile-time allocated&squot; memory buffers are&n; * fixed-size 4k pages. (or larger if used with an increment&n; * bigger than 1) use fixmap_set(idx,phys) to associate&n; * physical memory with fixmap indices.&n; *&n; * TLB entries of such buffers will not be flushed across&n; * task switches.&n; */
DECL|enum|fixed_addresses
r_enum
id|fixed_addresses
(brace
multiline_comment|/*&n; * on UP currently we will have no trace of the fixmap mechanizm,&n; * no page table allocations, etc. This might change in the&n; * future, say framebuffers for the console driver(s) could be&n; * fix-mapped?&n; */
macro_line|#if __SMP__
DECL|enumerator|FIX_APIC_BASE
id|FIX_APIC_BASE
op_assign
l_int|1
comma
multiline_comment|/* 0xfffff000 */
DECL|enumerator|FIX_IO_APIC_BASE
id|FIX_IO_APIC_BASE
op_assign
l_int|2
comma
multiline_comment|/* 0xffffe000 */
macro_line|#endif
DECL|enumerator|__end_of_fixed_addresses
id|__end_of_fixed_addresses
)brace
suffix:semicolon
r_extern
r_void
id|set_fixmap
(paren
r_enum
id|fixed_addresses
id|idx
comma
r_int
r_int
id|phys
)paren
suffix:semicolon
multiline_comment|/*&n; * used by vmalloc.c:&n; */
DECL|macro|FIXADDR_START
mdefine_line|#define FIXADDR_START (0UL-((__end_of_fixed_addresses-1)&lt;&lt;PAGE_SHIFT))
multiline_comment|/*&n; * &squot;index to address&squot; translation. If anyone tries to use the idx&n; * directly without tranlation, we catch the bug with a NULL-deference&n; * kernel oops. Illegal ranges of incoming indices are caught too.&n; */
DECL|function|fix_to_virt
r_extern
r_inline
r_int
r_int
id|fix_to_virt
c_func
(paren
r_const
r_int
r_int
id|idx
)paren
(brace
multiline_comment|/*&n;&t; * this branch gets completely eliminated after inlining,&n;&t; * except when someone tries to use fixaddr indices in an&n;&t; * illegal way. (such as mixing up address types or using&n;&t; * out-of-range indices)&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|idx
)paren
op_logical_or
(paren
id|idx
op_ge
id|__end_of_fixed_addresses
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;illegal fixaddr index!&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0UL
op_minus
(paren
r_int
r_int
)paren
(paren
id|idx
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
