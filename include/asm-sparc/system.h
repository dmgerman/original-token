multiline_comment|/* $Id: system.h,v 1.24 1996/02/11 00:42:39 davem Exp $ */
macro_line|#ifndef __SPARC_SYSTEM_H
DECL|macro|__SPARC_SYSTEM_H
mdefine_line|#define __SPARC_SYSTEM_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT       (&amp;empty_bad_page)
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;(&amp;empty_bad_page_table)
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
multiline_comment|/* V8 ploos ploos */
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
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|macro|halt
mdefine_line|#define halt() romvec-&gt;pv_halt()
multiline_comment|/* When a context switch happens we must flush all user windows so that&n; * the windows of the current process are flushed onto it&squot;s stack. This&n; * way the windows are all clean for the next process and the stack&n; * frames are up to date.&n; */
r_extern
r_void
id|flush_user_windows
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|synchronize_user_stack
c_func
(paren
r_void
)paren
suffix:semicolon
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
mdefine_line|#define switch_to(p) do { &bslash;&n;&t;&t;&t;  flush_user_windows(); &bslash;&n;&t;&t;          switch_to_context(p); &bslash;&n;&t;&t;&t;  current-&gt;tss.current_ds = active_ds; &bslash;&n;                          active_ds = p-&gt;tss.current_ds; &bslash;&n;                          sparc_switch_to(p); &bslash;&n;                     } while(0)
multiline_comment|/* Changing the IRQ level on the Sparc. */
DECL|function|setipl
r_extern
r_inline
r_void
id|setipl
c_func
(paren
r_int
id|__new_ipl
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;andn %%g1, %1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;sll %0, 8, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;and %%g2, %1, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g1, %%g2, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g1, 0x0, %%psr&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|__new_ipl
)paren
comma
l_string|&quot;i&quot;
(paren
id|PSR_PIL
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
)paren
suffix:semicolon
)brace
DECL|function|getipl
r_extern
r_inline
r_int
id|getipl
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %0&bslash;n&bslash;t&quot;
l_string|&quot;and %0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;srl %0, 8, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|PSR_PIL
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|swpipl
r_extern
r_inline
r_int
id|swpipl
c_func
(paren
r_int
id|__new_ipl
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;srl %%g1, 8, %0&bslash;n&bslash;t&quot;
l_string|&quot;and %0, 15, %0&bslash;n&bslash;t&quot;
l_string|&quot;andn %%g1, %2, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;and %1, 15, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;sll %%g2, 8, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g1, %%g2, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g1, 0x0, %%psr&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__new_ipl
)paren
comma
l_string|&quot;i&quot;
(paren
id|PSR_PIL
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
r_char
id|spdeb_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;setipl(15)  /* 15 = no int&squot;s except nmi&squot;s */
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;setipl(0)   /* I&squot;m scared */
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { flags = getipl(); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;setipl(flags)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;);
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
id|flags
comma
id|retval
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|val
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
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
)brace
suffix:semicolon
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
macro_line|#endif /* !(__SPARC_SYSTEM_H) */
eof
