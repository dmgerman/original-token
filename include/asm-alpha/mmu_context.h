macro_line|#ifndef __ALPHA_MMU_CONTEXT_H
DECL|macro|__ALPHA_MMU_CONTEXT_H
mdefine_line|#define __ALPHA_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context..&n; *&n; * Copyright (C) 1996, Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * The maximum ASN&squot;s the processor supports.  On the EV4 this is 63&n; * but the PAL-code doesn&squot;t actually use this information.  On the&n; * EV5 this is 127.&n; *&n; * On the EV4, the ASNs are more-or-less useless anyway, as they are&n; * only used as an icache tag, not for TB entries.  On the EV5 ASN&squot;s&n; * also validate the TB entries, and thus make a lot more sense.&n; *&n; * The EV4 ASN&squot;s don&squot;t even match the architecture manual, ugh.  And&n; * I quote: &quot;If a processor implements address space numbers (ASNs),&n; * and the old PTE has the Address Space Match (ASM) bit clear (ASNs&n; * in use) and the Valid bit set, then entries can also effectively be&n; * made coherent by assigning a new, unused ASN to the currently&n; * running process and not reusing the previous ASN before calling the&n; * appropriate PALcode routine to invalidate the translation buffer&n; * (TB)&quot;. &n; *&n; * In short, the EV4 has a &quot;kind of&quot; ASN capability, but it doesn&squot;t actually&n; * work correctly and can thus not be used (explaining the lack of PAL-code&n; * support).&n; */
macro_line|#ifdef CONFIG_ALPHA_EV5
DECL|macro|MAX_ASN
mdefine_line|#define MAX_ASN 127
macro_line|#else
DECL|macro|MAX_ASN
mdefine_line|#define MAX_ASN 63
DECL|macro|BROKEN_ASN
mdefine_line|#define BROKEN_ASN 1
macro_line|#endif
macro_line|#ifdef __SMP__
DECL|macro|WIDTH_THIS_PROCESSOR
mdefine_line|#define WIDTH_THIS_PROCESSOR&t;5
multiline_comment|/*&n; * last_asn[processor]:&n; * 63                                            0&n; * +-------------+----------------+--------------+&n; * | asn version | this processor | hardware asn |&n; * +-------------+----------------+--------------+&n; */
r_extern
r_int
r_int
id|last_asn
(braket
)braket
suffix:semicolon
DECL|macro|asn_cache
mdefine_line|#define asn_cache last_asn[p-&gt;processor]
macro_line|#else
DECL|macro|WIDTH_THIS_PROCESSOR
mdefine_line|#define WIDTH_THIS_PROCESSOR&t;0
multiline_comment|/*&n; * asn_cache:&n; * 63                                            0&n; * +------------------------------+--------------+&n; * |         asn version          | hardware asn |&n; * +------------------------------+--------------+&n; */
r_extern
r_int
r_int
id|asn_cache
suffix:semicolon
macro_line|#endif /* __SMP__ */
DECL|macro|WIDTH_HARDWARE_ASN
mdefine_line|#define WIDTH_HARDWARE_ASN&t;7
DECL|macro|ASN_FIRST_VERSION
mdefine_line|#define ASN_FIRST_VERSION (1UL &lt;&lt; (WIDTH_THIS_PROCESSOR + WIDTH_HARDWARE_ASN))
DECL|macro|HARDWARE_ASN_MASK
mdefine_line|#define HARDWARE_ASN_MASK ((1UL &lt;&lt; WIDTH_HARDWARE_ASN) - 1)
multiline_comment|/*&n; * NOTE! The way this is set up, the high bits of the &quot;asn_cache&quot; (and&n; * the &quot;mm-&gt;context&quot;) are the ASN _version_ code. A version of 0 is&n; * always considered invalid, so to invalidate another process you only&n; * need to do &quot;p-&gt;mm-&gt;context = 0&quot;.&n; *&n; * If we need more ASN&squot;s than the processor has, we invalidate the old&n; * user TLB&squot;s (tbiap()) and start a new ASN version. That will automatically&n; * force a new asn for any other processes the next time they want to&n; * run.&n; */
r_extern
r_inline
r_void
DECL|function|get_new_mmu_context
id|get_new_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|asn
op_assign
id|asn_cache
suffix:semicolon
r_if
c_cond
(paren
(paren
id|asn
op_amp
id|HARDWARE_ASN_MASK
)paren
OL
id|MAX_ASN
)paren
op_increment
id|asn
suffix:semicolon
r_else
(brace
id|tbiap
c_func
(paren
)paren
suffix:semicolon
id|imb
c_func
(paren
)paren
suffix:semicolon
id|asn
op_assign
(paren
id|asn
op_amp
op_complement
id|HARDWARE_ASN_MASK
)paren
op_plus
id|ASN_FIRST_VERSION
suffix:semicolon
)brace
id|asn_cache
op_assign
id|asn
suffix:semicolon
id|mm-&gt;context
op_assign
id|asn
suffix:semicolon
multiline_comment|/* full version + asn */
id|p-&gt;tss.asn
op_assign
id|asn
op_amp
id|HARDWARE_ASN_MASK
suffix:semicolon
multiline_comment|/* just asn */
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
macro_line|#ifndef BROKEN_ASN
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
id|asn
op_assign
id|asn_cache
suffix:semicolon
multiline_comment|/* Check if our ASN is of an older version and thus invalid */
r_if
c_cond
(paren
(paren
id|mm-&gt;context
op_xor
id|asn
)paren
op_amp
op_complement
id|HARDWARE_ASN_MASK
)paren
id|get_new_mmu_context
c_func
(paren
id|p
comma
id|mm
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
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
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while(0)
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; * Ideally this would be an extern inline function, but reload_context&n; * is declared in pgtable.h, which includes this file. :-(&n; */
DECL|macro|activate_context
mdefine_line|#define activate_context(tsk)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;get_mmu_context(tsk);&t;&bslash;&n;&t;&t;reload_context(tsk);&t;&bslash;&n;&t;} while (0)
macro_line|#endif
eof
