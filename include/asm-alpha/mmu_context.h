macro_line|#ifndef __ALPHA_MMU_CONTEXT_H
DECL|macro|__ALPHA_MMU_CONTEXT_H
mdefine_line|#define __ALPHA_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context..&n; *&n; * Copyright (C) 1996, Linus Torvalds&n; */
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * The maximum ASN&squot;s the processor supports. On the EV4 this doesn&squot;t&n; * matter as the pal-code doesn&squot;t use the ASNs anyway, on the EV5&n; * EV5 this is 127.&n; */
DECL|macro|MAX_ASN
mdefine_line|#define MAX_ASN 127
DECL|macro|ASN_VERSION_SHIFT
mdefine_line|#define ASN_VERSION_SHIFT 32
DECL|macro|ASN_VERSION_MASK
mdefine_line|#define ASN_VERSION_MASK ((~0UL) &lt;&lt; ASN_VERSION_SHIFT)
DECL|macro|ASN_FIRST_VERSION
mdefine_line|#define ASN_FIRST_VERSION (1UL &lt;&lt; ASN_VERSION_SHIFT)
multiline_comment|/*&n; * NOTE! The way this is set up, the high bits of the &quot;asn_cache&quot; (and&n; * the &quot;mm-&gt;context&quot;) are the ASN _version_ code. A version of 0 is&n; * always considered invalid, so to invalidate another process you only&n; * need to do &quot;p-&gt;mm-&gt;context = 0&quot;.&n; *&n; * If we need more ASN&squot;s than the processor has, we invalidate the old&n; * user TLB&squot;s (tbiap()) and start a new ASN version. That will automatically&n; * force a new asn for any other processes the next time they want to&n; * run.&n; */
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
r_static
r_int
r_int
id|asn_cache
op_assign
id|ASN_FIRST_VERSION
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|p-&gt;mm
suffix:semicolon
r_int
r_int
id|asn
op_assign
id|mm-&gt;context
suffix:semicolon
multiline_comment|/* Check if our ASN is of an older version and thus invalid */
r_if
c_cond
(paren
(paren
id|asn_cache
op_xor
id|asn
)paren
op_amp
id|ASN_VERSION_MASK
)paren
(brace
multiline_comment|/* get a new asn of the current version */
id|asn
op_assign
id|asn_cache
op_increment
suffix:semicolon
multiline_comment|/* check if it&squot;s legal.. */
r_if
c_cond
(paren
(paren
id|asn
op_amp
op_complement
id|ASN_VERSION_MASK
)paren
OG
id|MAX_ASN
)paren
(brace
multiline_comment|/* start a new version, invalidate all old asn&squot;s */
id|tbiap
c_func
(paren
)paren
suffix:semicolon
id|asn_cache
op_assign
(paren
id|asn_cache
op_amp
id|ASN_VERSION_MASK
)paren
op_plus
id|ASN_FIRST_VERSION
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|asn_cache
)paren
id|asn_cache
op_assign
id|ASN_FIRST_VERSION
suffix:semicolon
id|asn
op_assign
id|asn_cache
op_increment
suffix:semicolon
)brace
id|mm-&gt;context
op_assign
id|asn
suffix:semicolon
multiline_comment|/* full version + asn */
id|p-&gt;tss.asn
op_assign
id|asn
op_amp
op_complement
id|ASN_VERSION_MASK
suffix:semicolon
multiline_comment|/* just asn */
)brace
)brace
macro_line|#endif
eof
