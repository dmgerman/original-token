macro_line|#ifndef __ALPHA_MMU_CONTEXT_H
DECL|macro|__ALPHA_MMU_CONTEXT_H
mdefine_line|#define __ALPHA_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context..&n; *&n; * Copyright (C) 1996, Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * Force a context reload. This is needed when we change the page&n; * table pointer or when we update the ASN of the current process.&n; */
multiline_comment|/* Don&squot;t get into trouble with dueling __EXTERN_INLINEs.  */
macro_line|#ifndef __EXTERN_INLINE
macro_line|#include &lt;asm/io.h&gt;
macro_line|#endif
r_extern
r_inline
r_int
r_int
DECL|function|__reload_thread
id|__reload_thread
c_func
(paren
r_struct
id|thread_struct
op_star
id|pcb
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
id|pcb
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call_pal %2 #__reload_thread&quot;
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
multiline_comment|/*&n; * The maximum ASN&squot;s the processor supports.  On the EV4 this is 63&n; * but the PAL-code doesn&squot;t actually use this information.  On the&n; * EV5 this is 127, and EV6 has 255.&n; *&n; * On the EV4, the ASNs are more-or-less useless anyway, as they are&n; * only used as an icache tag, not for TB entries.  On the EV5 and EV6,&n; * ASN&squot;s also validate the TB entries, and thus make a lot more sense.&n; *&n; * The EV4 ASN&squot;s don&squot;t even match the architecture manual, ugh.  And&n; * I quote: &quot;If a processor implements address space numbers (ASNs),&n; * and the old PTE has the Address Space Match (ASM) bit clear (ASNs&n; * in use) and the Valid bit set, then entries can also effectively be&n; * made coherent by assigning a new, unused ASN to the currently&n; * running process and not reusing the previous ASN before calling the&n; * appropriate PALcode routine to invalidate the translation buffer (TB)&quot;. &n; *&n; * In short, the EV4 has a &quot;kind of&quot; ASN capability, but it doesn&squot;t actually&n; * work correctly and can thus not be used (explaining the lack of PAL-code&n; * support).&n; */
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
macro_line|#ifdef CONFIG_SMP
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
macro_line|#endif /* CONFIG_SMP */
DECL|macro|WIDTH_HARDWARE_ASN
mdefine_line|#define WIDTH_HARDWARE_ASN&t;8
DECL|macro|ASN_FIRST_VERSION
mdefine_line|#define ASN_FIRST_VERSION (1UL &lt;&lt; WIDTH_HARDWARE_ASN)
DECL|macro|HARDWARE_ASN_MASK
mdefine_line|#define HARDWARE_ASN_MASK ((1UL &lt;&lt; WIDTH_HARDWARE_ASN) - 1)
multiline_comment|/*&n; * NOTE! The way this is set up, the high bits of the &quot;asn_cache&quot; (and&n; * the &quot;mm-&gt;context&quot;) are the ASN _version_ code. A version of 0 is&n; * always considered invalid, so to invalidate another process you only&n; * need to do &quot;p-&gt;mm-&gt;context = 0&quot;.&n; *&n; * If we need more ASN&squot;s than the processor has, we invalidate the old&n; * user TLB&squot;s (tbiap()) and start a new ASN version. That will automatically&n; * force a new asn for any other processes the next time they want to&n; * run.&n; */
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__MMU_EXTERN_INLINE
mdefine_line|#define __MMU_EXTERN_INLINE
macro_line|#endif
r_static
r_inline
r_int
r_int
DECL|function|__get_new_mm_context
id|__get_new_mm_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
id|cpu
)paren
(brace
r_int
r_int
id|asn
op_assign
id|cpu_last_asn
c_func
(paren
id|cpu
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
id|asn
op_amp
id|HARDWARE_ASN_MASK
)paren
op_ge
id|MAX_ASN
)paren
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
id|cpu
)paren
op_assign
id|next
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev5_switch_mm
id|ev5_switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
comma
r_struct
id|task_struct
op_star
id|next
comma
r_int
id|cpu
)paren
(brace
multiline_comment|/* Check if our ASN is of an older version, and thus invalid. */
r_int
r_int
id|asn
suffix:semicolon
r_int
r_int
id|mmc
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|cpu_data
(braket
id|cpu
)braket
dot
id|asn_lock
op_assign
l_int|1
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|asn
op_assign
id|cpu_last_asn
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|mmc
op_assign
id|next_mm-&gt;context
(braket
id|cpu
)braket
suffix:semicolon
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
(brace
id|mmc
op_assign
id|__get_new_mm_context
c_func
(paren
id|next_mm
comma
id|cpu
)paren
suffix:semicolon
id|next_mm-&gt;context
(braket
id|cpu
)braket
op_assign
id|mmc
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_else
id|cpu_data
(braket
id|cpu
)braket
dot
id|need_new_asn
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Always update the PCB ASN.  Another thread may have allocated&n;&t;   a new mm-&gt;context (via flush_tlb_mm) without the ASN serial&n;&t;   number wrapping.  We have no way to detect when this is needed.  */
id|next-&gt;thread.asn
op_assign
id|mmc
op_amp
id|HARDWARE_ASN_MASK
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev4_switch_mm
id|ev4_switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
comma
r_struct
id|task_struct
op_star
id|next
comma
r_int
id|cpu
)paren
(brace
multiline_comment|/* As described, ASN&squot;s are broken for TLB usage.  But we can&n;&t;   optimize for switching between threads -- if the mm is&n;&t;   unchanged from current we needn&squot;t flush.  */
multiline_comment|/* ??? May not be needed because EV4 PALcode recognizes that&n;&t;   ASN&squot;s are broken and does a tbiap itself on swpctx, under&n;&t;   the &quot;Must set ASN or flush&quot; rule.  At least this is true&n;&t;   for a 1992 SRM, reports Joseph Martin (jmartin@hlo.dec.com).&n;&t;   I&squot;m going to leave this here anyway, just to Be Sure.  -- r~  */
r_if
c_cond
(paren
id|prev_mm
op_ne
id|next_mm
)paren
id|tbiap
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do continue to allocate ASNs, because we can still use them&n;&t;   to avoid flushing the icache.  */
id|ev5_switch_mm
c_func
(paren
id|prev_mm
comma
id|next_mm
comma
id|next
comma
id|cpu
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__load_new_mm_context
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|check_mmu_context
mdefine_line|#define check_mmu_context()&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int cpu = smp_processor_id();&t;&t;&t;&t;&bslash;&n;&t;cpu_data[cpu].asn_lock = 0;&t;&t;&t;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (cpu_data[cpu].need_new_asn) {&t;&t;&t;&bslash;&n;&t;&t;struct mm_struct * mm = current-&gt;active_mm;&t;&bslash;&n;&t;&t;cpu_data[cpu].need_new_asn = 0;&t;&t;&t;&bslash;&n;&t;&t;if (!mm-&gt;context[cpu])&t;&t;&t;&bslash;&n;&t;&t;&t;__load_new_mm_context(mm);&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|check_mmu_context
mdefine_line|#define check_mmu_context()  do { } while(0)
macro_line|#endif
id|__EXTERN_INLINE
r_void
DECL|function|ev5_activate_mm
id|ev5_activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
)paren
(brace
id|__load_new_mm_context
c_func
(paren
id|next_mm
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev4_activate_mm
id|ev4_activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
)paren
(brace
id|__load_new_mm_context
c_func
(paren
id|next_mm
)paren
suffix:semicolon
id|tbiap
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|switch_mm
macro_line|# define switch_mm(a,b,c,d)&t;alpha_mv.mv_switch_mm((a),(b),(c),(d))
DECL|macro|activate_mm
macro_line|# define activate_mm(x,y)&t;alpha_mv.mv_activate_mm((x),(y))
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|switch_mm
macro_line|#  define switch_mm(a,b,c,d)&t;ev4_switch_mm((a),(b),(c),(d))
DECL|macro|activate_mm
macro_line|#  define activate_mm(x,y)&t;ev4_activate_mm((x),(y))
macro_line|# else
DECL|macro|switch_mm
macro_line|#  define switch_mm(a,b,c,d)&t;ev5_switch_mm((a),(b),(c),(d))
DECL|macro|activate_mm
macro_line|#  define activate_mm(x,y)&t;ev5_activate_mm((x),(y))
macro_line|# endif
macro_line|#endif
r_extern
r_inline
r_int
DECL|function|init_new_context
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|mm-&gt;context
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.ptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|mm-&gt;pgd
op_minus
id|IDENT_ADDR
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
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
r_static
r_inline
r_void
DECL|function|enter_lazy_tlb
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|cpu
)paren
(brace
id|tsk-&gt;thread.ptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|mm-&gt;pgd
op_minus
id|IDENT_ADDR
)paren
op_rshift
id|PAGE_SHIFT
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
