multiline_comment|/*&n; * Switch a MMU context.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MMU_CONTEXT_H
DECL|macro|__ASM_MIPS_MMU_CONTEXT_H
mdefine_line|#define __ASM_MIPS_MMU_CONTEXT_H
DECL|macro|MAX_ASID
mdefine_line|#define MAX_ASID 255
r_extern
r_int
r_int
id|asid_cache
suffix:semicolon
DECL|macro|ASID_VERSION_SHIFT
mdefine_line|#define ASID_VERSION_SHIFT 16
DECL|macro|ASID_VERSION_MASK
mdefine_line|#define ASID_VERSION_MASK  ((~0UL) &lt;&lt; ASID_VERSION_SHIFT)
DECL|macro|ASID_FIRST_VERSION
mdefine_line|#define ASID_FIRST_VERSION (1UL &lt;&lt; ASID_VERSION_SHIFT)
DECL|function|get_new_mmu_context
r_extern
r_inline
r_void
id|get_new_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|asid
)paren
(brace
multiline_comment|/* check if it&squot;s legal.. */
r_if
c_cond
(paren
(paren
id|asid
op_amp
op_complement
id|ASID_VERSION_MASK
)paren
OG
id|MAX_ASID
)paren
(brace
multiline_comment|/* start a new version, invalidate all old asid&squot;s */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|asid
op_assign
(paren
id|asid
op_amp
id|ASID_VERSION_MASK
)paren
op_plus
id|ASID_FIRST_VERSION
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asid
)paren
id|asid
op_assign
id|ASID_FIRST_VERSION
suffix:semicolon
)brace
id|asid_cache
op_assign
id|asid
op_plus
l_int|1
suffix:semicolon
id|mm-&gt;context
op_assign
id|asid
suffix:semicolon
multiline_comment|/* full version + asid */
)brace
DECL|function|get_mmu_context
r_extern
r_inline
r_void
id|get_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|p-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
r_int
r_int
id|asid
op_assign
id|asid_cache
suffix:semicolon
multiline_comment|/* Check if our ASID is of an older version and thus invalid */
r_if
c_cond
(paren
(paren
id|mm-&gt;context
op_xor
id|asid
)paren
op_amp
id|ASID_VERSION_MASK
)paren
id|get_new_mmu_context
c_func
(paren
id|mm
comma
id|asid
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|function|init_new_context
r_extern
r_inline
r_void
id|init_new_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
DECL|function|destroy_context
r_extern
r_inline
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MIPS_MMU_CONTEXT_H */
eof