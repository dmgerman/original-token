macro_line|#ifndef __SPARC_SYSTEM_H
DECL|macro|__SPARC_SYSTEM_H
mdefine_line|#define __SPARC_SYSTEM_H
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * I wish the boot time image was as beautiful as the Alpha&squot;s&n; * but no such luck. The icky PROM loads us at 0x0, and jumps&n; * to magic address 0x4000 to start things going.&n; *&n; * Sorry, I can&squot;t impress people with cool looking 64-bit values&n; * yet. Wait till V9 ;-)&n; */
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;(0x00004000)
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT       (&amp;empty_bad_page)
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;(&amp;empty_bad_page_table)
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;(&amp;empty_zero_page)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Sparc (general) CPU types&n; */
DECL|enum|sparc_cpu
r_enum
id|sparc_cpu
(brace
DECL|enumerator|sun4
id|sun4
op_assign
l_int|0x00
comma
DECL|enumerator|sun4c
id|sun4c
op_assign
l_int|0x01
comma
DECL|enumerator|sun4m
id|sun4m
op_assign
l_int|0x02
comma
DECL|enumerator|sun4d
id|sun4d
op_assign
l_int|0x03
comma
DECL|enumerator|sun4e
id|sun4e
op_assign
l_int|0x04
comma
DECL|enumerator|sun4u
id|sun4u
op_assign
l_int|0x05
comma
DECL|enumerator|sun_unknown
id|sun_unknown
op_assign
l_int|0x06
comma
)brace
suffix:semicolon
r_extern
r_enum
id|sparc_cpu
id|sparc_cpu_model
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_page
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_page_table
suffix:semicolon
r_extern
r_int
r_int
id|empty_zero_page
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
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|macro|halt
mdefine_line|#define halt() do { &bslash;&n;&t;&t;&t; printk(&quot;Entering monitor in file %s at line %d&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;romvec-&gt;pv_halt(); } while(0)
DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode() halt()
macro_line|#ifndef stbar  /* store barrier Sparc insn to synchronize stores in PSO */
DECL|macro|stbar
mdefine_line|#define stbar() __asm__ __volatile__(&quot;stbar&quot;: : :&quot;memory&quot;)
macro_line|#endif
multiline_comment|/* When a context switch happens we must flush all user windows so that&n; * the windows of the current process are flushed onto it&squot;s stack. This&n; * way the windows are all clean for the next process.&n; */
DECL|macro|flush_user_windows
mdefine_line|#define flush_user_windows() &bslash;&n;do { __asm__ __volatile__( &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;save %sp, -64, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;  &quot;restore&bslash;n&bslash;t&quot;); } while(0)
r_extern
r_void
id|sparc_switch_to
c_func
(paren
r_void
op_star
id|new_task
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(p) sparc_switch_to(p)
multiline_comment|/* Changing the PIL on the sparc is a bit hairy. I&squot;ll figure out some&n; * more optimized way of doing this soon. This is bletcherous code.&n; */
DECL|macro|swpipl
mdefine_line|#define swpipl(__new_ipl) &bslash;&n;({ unsigned long psr, retval; &bslash;&n;__asm__ __volatile__( &bslash;&n;        &quot;rd %%psr, %0&bslash;n&bslash;t&quot; : &quot;=&amp;r&quot; (psr)); &bslash;&n;retval = psr; &bslash;&n;psr = (psr &amp; ~(PSR_PIL)); &bslash;&n;psr |= ((__new_ipl &lt;&lt; 8) &amp; PSR_PIL); &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;wr  %0, 0x0, %%psr&bslash;n&bslash;t&quot; &bslash;&n;&t;: : &quot;r&quot; (psr)); &bslash;&n;retval = ((retval&gt;&gt;8)&amp;15); &bslash;&n;retval; })
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;swpipl(15)  /* 15 = no int&squot;s except nmi&squot;s */
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;swpipl(0)   /* I&squot;m scared */
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { flags = swpipl(15); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;swpipl(flags)
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;jmp %%l1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;rett %%l2&bslash;n&bslash;t&quot;: : :&quot;memory&quot;)
multiline_comment|/* Must this be atomic? */
DECL|function|xchg_u32
r_extern
r_inline
r_void
op_star
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld %1,%2&bslash;n&bslash;t&quot;
l_string|&quot;st %0, %1&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %2, %0&quot;
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
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|val
suffix:semicolon
)brace
multiline_comment|/* pointers are 32 bits on the sparc (at least the v8, and they&squot;ll work&n; * on the V9 none the less). I don&squot;t need the xchg_u64 routine for now.&n; */
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
id|xchg_u32
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
