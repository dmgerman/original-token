macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
macro_line|#include &lt;asm/pal.h&gt;&t;/* for backwards compatibility... */
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
mdefine_line|#define START_SIZE&t;(2*1024*1024)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * This is the logout header that should be common to all platforms&n; * (assuming they are running OSF/1 PALcode, I guess).&n; */
DECL|struct|el_common
r_struct
id|el_common
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size in bytes of logout area */
DECL|member|sbz1
r_int
id|sbz1
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* should be zero */
DECL|member|retry
r_char
id|retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* retry flag */
DECL|member|proc_offset
r_int
r_int
id|proc_offset
suffix:semicolon
multiline_comment|/* processor-specific offset */
DECL|member|sys_offset
r_int
r_int
id|sys_offset
suffix:semicolon
multiline_comment|/* system-specific offset */
)brace
suffix:semicolon
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
r_extern
r_int
r_int
id|rdmces
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wrmces
(paren
r_int
r_int
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
mdefine_line|#define switch_to(p) do { &bslash;&n;&t;current_set[0] = p; &bslash;&n;&t;alpha_switch_to((unsigned long) &amp;(p)-&gt;tss - 0xfffffc0000000000); &bslash;&n;} while (0)
DECL|macro|mb
mdefine_line|#define mb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|draina
mdefine_line|#define draina() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0&quot; : : &quot;i&quot; (PAL_draina) : &quot;memory&quot;)
DECL|macro|getipl
mdefine_line|#define getipl() &bslash;&n;({ unsigned long __old_ipl; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;call_pal 54&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bis $0,$0,%0&quot; &bslash;&n;&t;: &quot;=r&quot; (__old_ipl) &bslash;&n;&t;: : &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;); &bslash;&n;__old_ipl; })
DECL|macro|setipl
mdefine_line|#define setipl(__new_ipl) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;bis %0,%0,$16&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call_pal 53&quot; &bslash;&n;&t;: : &quot;r&quot; (__new_ipl) &bslash;&n;&t;: &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;)
DECL|macro|swpipl
mdefine_line|#define swpipl(__new_ipl) &bslash;&n;({ unsigned long __old_ipl; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;bis %1,%1,$16&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call_pal 53&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bis $0,$0,%0&quot; &bslash;&n;&t;: &quot;=r&quot; (__old_ipl) &bslash;&n;&t;: &quot;r&quot; (__new_ipl) &bslash;&n;&t;: &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;__old_ipl; })
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;setipl(7)
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;setipl(0)
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { flags = getipl(); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;setipl(flags)
multiline_comment|/*&n; * Give prototypes to shut up gcc.&n; */
r_extern
r_inline
r_int
r_int
id|xchg_u32
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_inline
r_int
r_int
id|xchg_u64
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|xchg_u32
r_extern
r_inline
r_int
r_int
id|xchg_u32
c_func
(paren
r_volatile
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
l_string|&quot;ldl_l %0,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;bis %2,%2,%3&bslash;n&bslash;t&quot;
l_string|&quot;stl_c %3,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;beq %3,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
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
id|m
)paren
comma
l_string|&quot;2&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
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
r_volatile
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
l_string|&quot;ldq_l %0,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;bis %2,%2,%3&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %3,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;beq %3,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
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
id|m
)paren
comma
l_string|&quot;2&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; *&n; * This only works if the compiler isn&squot;t horribly bad at optimizing.&n; * gcc-2.5.8 reportedly can&squot;t handle this, but as that doesn&squot;t work&n; * too well on the alpha anyway..&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__xchg
r_static
r_inline
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
id|xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
