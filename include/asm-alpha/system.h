macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
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
DECL|macro|invalidate_all
mdefine_line|#define invalidate_all() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-2($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-1($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
DECL|macro|swpipl
mdefine_line|#define swpipl(__new_ipl) &bslash;&n;({ unsigned long __old_ipl; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;bis %1,%1,$16&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 53&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bis $0,$0,%0&quot; &bslash;&n;&t;: &quot;=r&quot; (__old_ipl) &bslash;&n;&t;: &quot;r&quot; (__new_ipl) &bslash;&n;&t;: &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;); &bslash;&n;__old_ipl; })
macro_line|#endif
eof
