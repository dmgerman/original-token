macro_line|#ifndef __ALPHA_MMU_CONTEXT_H
DECL|macro|__ALPHA_MMU_CONTEXT_H
mdefine_line|#define __ALPHA_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context..&n; *&n; * Copyright (C) 1996, Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * The maximum ASN&squot;s the processor supports.  On the EV4 this is 63&n; * but the PAL-code doesn&squot;t actually use this information.  On the&n; * EV5 this is 127.&n; *&n; * On the EV4, the ASNs are more-or-less useless anyway, as they are&n; * only used as an icache tag, not for TB entries.  On the EV5 ASN&squot;s&n; * also validate the TB entries, and thus make a lot more sense.&n; *&n; * The EV4 ASN&squot;s don&squot;t even match the architecture manual, ugh.  And&n; * I quote: &quot;If a processor implements address space numbers (ASNs),&n; * and the old PTE has the Address Space Match (ASM) bit clear (ASNs&n; * in use) and the Valid bit set, then entries can also effectively be&n; * made coherent by assigning a new, unused ASN to the currently&n; * running process and not reusing the previous ASN before calling the&n; * appropriate PALcode routine to invalidate the translation buffer&n; * (TB)&quot;. &n; *&n; * In short, the EV4 has a &quot;kind of&quot; ASN capability, but it doesn&squot;t actually&n; * work correctly and can thus not be used (explaining the lack of PAL-code&n; * support).&n; */
DECL|macro|EV4_MAX_ASN
mdefine_line|#define EV4_MAX_ASN 63
DECL|macro|EV5_MAX_ASN
mdefine_line|#define EV5_MAX_ASN 127
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|MAX_ASN
macro_line|# define MAX_ASN&t;(alpha_mv.max_asn)
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|MAX_ASN
macro_line|#  define MAX_ASN&t;EV4_MAX_ASN
macro_line|# else
DECL|macro|MAX_ASN
macro_line|#  define MAX_ASN&t;EV5_MAX_ASN
macro_line|# endif
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
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__MMU_EXTERN_INLINE
mdefine_line|#define __MMU_EXTERN_INLINE
macro_line|#endif
r_extern
r_void
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
suffix:semicolon
DECL|function|ev4_get_mmu_context
id|__EXTERN_INLINE
r_void
id|ev4_get_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
multiline_comment|/* As described, ASN&squot;s are broken.  */
)brace
DECL|function|ev5_get_mmu_context
id|__EXTERN_INLINE
r_void
id|ev5_get_mmu_context
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
)brace
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|get_mmu_context
macro_line|# define get_mmu_context&t;&t;(alpha_mv.mv_get_mmu_context)
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|get_mmu_context
macro_line|#  define get_mmu_context&t;&t;ev4_get_mmu_context
macro_line|# else
DECL|macro|get_mmu_context
macro_line|#  define get_mmu_context&t;&t;ev5_get_mmu_context
macro_line|# endif
macro_line|#endif
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
multiline_comment|/* Nothing to do.  */
)brace
multiline_comment|/*&n; * Force a context reload. This is needed when we change the page&n; * table pointer or when we update the ASN of the current process.&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC)
DECL|macro|MASK_CONTEXT
mdefine_line|#define MASK_CONTEXT(tss) &bslash;&n; ((struct thread_struct *)((unsigned long)(tss) &amp; alpha_mv.mmu_context_mask))
macro_line|#elif defined(CONFIG_ALPHA_DP264)
DECL|macro|MASK_CONTEXT
mdefine_line|#define MASK_CONTEXT(tss) &bslash;&n; ((struct thread_struct *)((unsigned long)(tss) &amp; 0xfffffffffful))
macro_line|#else
DECL|macro|MASK_CONTEXT
mdefine_line|#define MASK_CONTEXT(tss)  (tss)
macro_line|#endif
id|__EXTERN_INLINE
r_struct
id|thread_struct
op_star
DECL|function|__reload_tss
id|__reload_tss
c_func
(paren
r_struct
id|thread_struct
op_star
id|tss
)paren
(brace
r_register
r_struct
id|thread_struct
op_star
id|a0
id|__asm__
c_func
(paren
l_string|&quot;$16&quot;
)paren
suffix:semicolon
r_register
r_struct
id|thread_struct
op_star
id|v0
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
suffix:semicolon
id|a0
op_assign
id|MASK_CONTEXT
c_func
(paren
id|tss
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call_pal %2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v0
)paren
comma
l_string|&quot;=r&quot;
(paren
id|a0
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|PAL_swpctx
)paren
comma
l_string|&quot;r&quot;
(paren
id|a0
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$16&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
r_return
id|v0
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|reload_context
id|reload_context
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
id|__reload_tss
c_func
(paren
op_amp
id|task-&gt;tss
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates the&n; * context for the new mm so we see the new mappings.&n; */
id|__EXTERN_INLINE
r_void
DECL|function|activate_context
id|activate_context
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
id|get_mmu_context
c_func
(paren
id|task
)paren
suffix:semicolon
id|reload_context
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
macro_line|#ifdef __MMU_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__MMU_EXTERN_INLINE
macro_line|#undef __MMU_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __ALPHA_MMU_CONTEXT_H */
eof
