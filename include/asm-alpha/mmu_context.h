macro_line|#ifndef __ALPHA_MMU_CONTEXT_H
DECL|macro|__ALPHA_MMU_CONTEXT_H
mdefine_line|#define __ALPHA_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context..&n; *&n; * Copyright (C) 1996, Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * The maximum ASN&squot;s the processor supports.  On the EV4 this is 63&n; * but the PAL-code doesn&squot;t actually use this information.  On the&n; * EV5 this is 127, and EV6 has 255.&n; *&n; * On the EV4, the ASNs are more-or-less useless anyway, as they are&n; * only used as an icache tag, not for TB entries.  On the EV5 and EV6,&n; * ASN&squot;s also validate the TB entries, and thus make a lot more sense.&n; *&n; * The EV4 ASN&squot;s don&squot;t even match the architecture manual, ugh.  And&n; * I quote: &quot;If a processor implements address space numbers (ASNs),&n; * and the old PTE has the Address Space Match (ASM) bit clear (ASNs&n; * in use) and the Valid bit set, then entries can also effectively be&n; * made coherent by assigning a new, unused ASN to the currently&n; * running process and not reusing the previous ASN before calling the&n; * appropriate PALcode routine to invalidate the translation buffer&n; * (TB)&quot;. &n; *&n; * In short, the EV4 has a &quot;kind of&quot; ASN capability, but it doesn&squot;t actually&n; * work correctly and can thus not be used (explaining the lack of PAL-code&n; * support).&n; */
DECL|macro|EV4_MAX_ASN
mdefine_line|#define EV4_MAX_ASN 63
DECL|macro|EV5_MAX_ASN
mdefine_line|#define EV5_MAX_ASN 127
DECL|macro|EV6_MAX_ASN
mdefine_line|#define EV6_MAX_ASN 255
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|MAX_ASN
macro_line|# define MAX_ASN&t;(alpha_mv.max_asn)
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|MAX_ASN
macro_line|#  define MAX_ASN&t;EV4_MAX_ASN
macro_line|# elif defined(CONFIG_ALPHA_EV5)
DECL|macro|MAX_ASN
macro_line|#  define MAX_ASN&t;EV5_MAX_ASN
macro_line|# else
DECL|macro|MAX_ASN
macro_line|#  define MAX_ASN&t;EV6_MAX_ASN
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * cpu_last_asn(processor):&n; * 63                                            0&n; * +-------------+----------------+--------------+&n; * | asn version | this processor | hardware asn |&n; * +-------------+----------------+--------------+&n; */
macro_line|#ifdef __SMP__
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|cpu_last_asn
mdefine_line|#define cpu_last_asn(cpuid)&t;(cpu_data[cpuid].last_asn)
macro_line|#else
r_extern
r_int
r_int
id|last_asn
suffix:semicolon
DECL|macro|cpu_last_asn
mdefine_line|#define cpu_last_asn(cpuid)&t;last_asn
macro_line|#endif /* __SMP__ */
DECL|macro|WIDTH_HARDWARE_ASN
mdefine_line|#define WIDTH_HARDWARE_ASN&t;8
DECL|macro|WIDTH_THIS_PROCESSOR
mdefine_line|#define WIDTH_THIS_PROCESSOR&t;5
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
r_static
r_inline
r_int
r_int
DECL|function|__get_new_mmu_context
id|__get_new_mmu_context
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
id|cpu_last_asn
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_int
r_int
id|next
op_assign
id|asn
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|next
op_xor
id|asn
)paren
op_amp
op_complement
id|MAX_ASN
)paren
(brace
id|tbiap
c_func
(paren
)paren
suffix:semicolon
id|next
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
id|cpu_last_asn
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_assign
id|next
suffix:semicolon
id|mm-&gt;context
op_assign
id|next
suffix:semicolon
multiline_comment|/* full version + asn */
r_return
id|next
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev4_get_mmu_context
id|ev4_get_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
multiline_comment|/* As described, ASN&squot;s are broken.  But we can optimize for&n;&t;   switching between threads -- if the mm is unchanged from&n;&t;   current we needn&squot;t flush.  */
r_if
c_cond
(paren
id|current-&gt;mm
op_ne
id|p-&gt;mm
)paren
id|tbiap
c_func
(paren
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev5_get_mmu_context
id|ev5_get_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
multiline_comment|/* Check if our ASN is of an older version, or on a different CPU,&n;&t;   and thus invalid.  */
r_int
id|asn
op_assign
id|cpu_last_asn
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|p-&gt;mm
suffix:semicolon
r_int
id|mmc
op_assign
id|mm-&gt;context
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;tss.mm_context
op_xor
id|asn
)paren
op_amp
op_complement
id|HARDWARE_ASN_MASK
)paren
(brace
r_if
c_cond
(paren
(paren
id|mmc
op_xor
id|asn
)paren
op_amp
op_complement
id|HARDWARE_ASN_MASK
)paren
id|mmc
op_assign
id|__get_new_mmu_context
c_func
(paren
id|p
comma
id|mm
)paren
suffix:semicolon
id|p-&gt;tss.mm_context
op_assign
id|mmc
suffix:semicolon
id|p-&gt;tss.asn
op_assign
id|mmc
op_amp
id|HARDWARE_ASN_MASK
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
r_extern
r_inline
r_void
DECL|function|init_new_context
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
r_extern
r_inline
r_void
DECL|function|destroy_context
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
macro_line|#ifdef __MMU_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__MMU_EXTERN_INLINE
macro_line|#undef __MMU_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * Force a context reload. This is needed when we change the page&n; * table pointer or when we update the ASN of the current process.&n; */
multiline_comment|/* Don&squot;t get into trouble with dueling __EXTERN_INLINEs.  */
macro_line|#ifndef __EXTERN_INLINE
macro_line|#include &lt;asm/io.h&gt;
macro_line|#endif
r_extern
r_inline
r_int
r_int
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
r_int
r_int
id|a0
id|__asm__
c_func
(paren
l_string|&quot;$16&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|v0
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
suffix:semicolon
id|a0
op_assign
id|virt_to_phys
c_func
(paren
id|tss
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call_pal %2 #__reload_tss&quot;
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
r_extern
r_inline
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
multiline_comment|/*&n; * After setting current-&gt;mm to a new value, activate the context for the&n; * new mm so we see the new mappings.&n; */
r_extern
r_inline
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
id|get_new_mmu_context
c_func
(paren
id|task
comma
id|task-&gt;mm
)paren
suffix:semicolon
id|reload_context
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ALPHA_MMU_CONTEXT_H */
eof
