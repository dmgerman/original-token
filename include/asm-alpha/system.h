macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
multiline_comment|/*&n; * System defines.. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.&n; */
multiline_comment|/*&n; * We leave one page for the initial stack page, and one page for&n; * the initial process structure. Also, the console eats 3 MB for&n; * the initial bootloader (one of which we can reclaim later).&n; * With a few other pages for various reasons, we&squot;ll use an initial&n; * load address of 0xfffffc0000310000UL&n; */
DECL|macro|BOOT_PCB
mdefine_line|#define BOOT_PCB&t;0x20000000
DECL|macro|BOOT_ADDR
mdefine_line|#define BOOT_ADDR&t;0x20000000
DECL|macro|BOOT_SIZE
mdefine_line|#define BOOT_SIZE&t;(16*1024)
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;0xfffffc0000300000
DECL|macro|SWAPPER_PGD
mdefine_line|#define SWAPPER_PGD&t;0xfffffc0000300000
DECL|macro|INIT_STACK
mdefine_line|#define INIT_STACK&t;0xfffffc0000302000
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT&t;0xfffffc0000304000
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;0xfffffc0000308000
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;0xfffffc000030A000
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;0xfffffc0000310000
DECL|macro|START_SIZE
mdefine_line|#define START_SIZE&t;(1024*1024)
multiline_comment|/*&n; * Common PAL-code&n; */
DECL|macro|PAL_halt
mdefine_line|#define PAL_halt&t;  0
DECL|macro|PAL_cflush
mdefine_line|#define PAL_cflush&t;  1
DECL|macro|PAL_draina
mdefine_line|#define PAL_draina&t;  2
DECL|macro|PAL_cobratt
mdefine_line|#define PAL_cobratt&t;  9
DECL|macro|PAL_bpt
mdefine_line|#define PAL_bpt&t;&t;128
DECL|macro|PAL_bugchk
mdefine_line|#define PAL_bugchk&t;129
DECL|macro|PAL_chmk
mdefine_line|#define PAL_chmk&t;131
DECL|macro|PAL_callsys
mdefine_line|#define PAL_callsys&t;131
DECL|macro|PAL_imb
mdefine_line|#define PAL_imb&t;&t;134
DECL|macro|PAL_rduniq
mdefine_line|#define PAL_rduniq&t;158
DECL|macro|PAL_wruniq
mdefine_line|#define PAL_wruniq&t;159
DECL|macro|PAL_gentrap
mdefine_line|#define PAL_gentrap&t;170
DECL|macro|PAL_nphalt
mdefine_line|#define PAL_nphalt&t;190
multiline_comment|/*&n; * VMS specific PAL-code&n; */
DECL|macro|PAL_swppal
mdefine_line|#define PAL_swppal&t;10
DECL|macro|PAL_mfpr_vptb
mdefine_line|#define PAL_mfpr_vptb&t;41
multiline_comment|/*&n; * OSF specific PAL-code&n; */
DECL|macro|PAL_mtpr_mces
mdefine_line|#define PAL_mtpr_mces&t;17
DECL|macro|PAL_wrfen
mdefine_line|#define PAL_wrfen&t;43
DECL|macro|PAL_wrvptptr
mdefine_line|#define PAL_wrvptptr&t;45
DECL|macro|PAL_jtopal
mdefine_line|#define PAL_jtopal&t;46
DECL|macro|PAL_swpctx
mdefine_line|#define PAL_swpctx&t;48
DECL|macro|PAL_wrval
mdefine_line|#define PAL_wrval&t;49
DECL|macro|PAL_rdval
mdefine_line|#define PAL_rdval&t;50
DECL|macro|PAL_tbi
mdefine_line|#define PAL_tbi&t;&t;51
DECL|macro|PAL_wrent
mdefine_line|#define PAL_wrent&t;52
DECL|macro|PAL_swpipl
mdefine_line|#define PAL_swpipl&t;53
DECL|macro|PAL_rdps
mdefine_line|#define PAL_rdps&t;54
DECL|macro|PAL_wrkgp
mdefine_line|#define PAL_wrkgp&t;55
DECL|macro|PAL_wrusp
mdefine_line|#define PAL_wrusp&t;56
DECL|macro|PAL_wrperfmon
mdefine_line|#define PAL_wrperfmon&t;57
DECL|macro|PAL_rdusp
mdefine_line|#define PAL_rdusp&t;58
DECL|macro|PAL_whami
mdefine_line|#define PAL_whami&t;60
DECL|macro|PAL_rtsys
mdefine_line|#define PAL_rtsys&t;61
DECL|macro|PAL_rti
mdefine_line|#define PAL_rti&t;&t;63
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|wrent
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wrkgp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wrusp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|rdusp
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|halt
mdefine_line|#define halt() __asm__ __volatile__(&quot;.long 0&quot;);
r_extern
r_void
id|alpha_switch_to
c_func
(paren
r_int
r_int
id|pctxp
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(p) do { &bslash;&n;&t;current = p; &bslash;&n;&t;alpha_switch_to((unsigned long) &amp;(p)-&gt;tss - 0xfffffc0000000000); &bslash;&n;} while (0)
macro_line|#ifndef mb
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
macro_line|#endif
DECL|macro|swpipl
mdefine_line|#define swpipl(__new_ipl) &bslash;&n;({ unsigned long __old_ipl; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;bis %1,%1,$16&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 53&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bis $0,$0,%0&quot; &bslash;&n;&t;: &quot;=r&quot; (__old_ipl) &bslash;&n;&t;: &quot;r&quot; (__new_ipl) &bslash;&n;&t;: &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;); &bslash;&n;__old_ipl; })
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;swpipl(7)
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;swpipl(0)
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { flags = swpipl(7); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;swpipl(flags)
DECL|function|xchg_u32
r_extern
r_inline
r_int
r_int
id|xchg_u32
c_func
(paren
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
comma
id|dummy2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldl_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;bis %2,%2,%3&bslash;n&bslash;t&quot;
l_string|&quot;stl_c %3,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %3,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;2&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg_u64
r_extern
r_inline
r_int
r_int
id|xchg_u64
c_func
(paren
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
comma
id|dummy2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;bis %2,%2,%3&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %3,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %3,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;2&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg_ptr
r_extern
r_inline
r_void
op_star
id|xchg_ptr
c_func
(paren
r_void
op_star
id|m
comma
r_void
op_star
id|val
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|xchg_u64
c_func
(paren
(paren
r_int
op_star
)paren
id|m
comma
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
