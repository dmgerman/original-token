multiline_comment|/*&n; *  linux/include/asm-m68k/system.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * 680x0 support added by Hamish Macdonald&n; */
macro_line|#ifndef _M68K_SYSTEM_H
DECL|macro|_M68K_SYSTEM_H
mdefine_line|#define _M68K_SYSTEM_H
macro_line|#include &lt;linux/autoconf.h&gt; /* get configuration macros */
macro_line|#if defined(CONFIG_ATARI) &amp;&amp; !defined(CONFIG_AMIGA) &amp;&amp; !defined(CONFIG_MAC)
multiline_comment|/* block out HSYNC on the atari */
DECL|macro|sti
mdefine_line|#define sti() __asm__ __volatile__ (&quot;andiw #0xfbff,sr&quot;: : : &quot;memory&quot;)
macro_line|#else /* portable version */
DECL|macro|sti
mdefine_line|#define sti() __asm__ __volatile__ (&quot;andiw #0xf8ff,sr&quot;: : : &quot;memory&quot;)
macro_line|#endif /* machine compilation types */ 
DECL|macro|cli
mdefine_line|#define cli() __asm__ __volatile__ (&quot;oriw  #0x0700,sr&quot;: : : &quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;::)
DECL|macro|save_flags
mdefine_line|#define save_flags(x) &bslash;&n;__asm__ __volatile__(&quot;movew sr,%0&quot;:&quot;=d&quot; (x) : /* no input */ :&quot;memory&quot;)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) &bslash;&n;__asm__ __volatile__(&quot;movew %0,sr&quot;: /* no outputs */ :&quot;d&quot; (x) : &quot;memory&quot;)
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;rte&quot;: : :&quot;memory&quot;, &quot;sp&quot;, &quot;cc&quot;)
DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode() &bslash;&n;    __asm__ __volatile__ (&quot;movel sp,usp&bslash;n&bslash;t&quot;     /* setup user sp       */ &bslash;&n;&t;&t;&t;  &quot;movec %0,msp&bslash;n&bslash;t&quot;     /* setup kernel sp     */ &bslash;&n;&t;&t;&t;  &quot;andiw #0xdfff,sr&quot;     /* return to user mode */ &bslash;&n;&t;&t;&t;  : /* no output */                                &bslash;&n;&t;&t;&t;  : &quot;r&quot; (current-&gt;kernel_stack_page + PAGE_SIZE)   &bslash;&n;&t;&t;&t;  : &quot;memory&quot;, &quot;sp&quot;)
DECL|function|clear_fpu
r_static
r_inline
r_void
id|clear_fpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|nilstate
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;frestore %0@&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|nilstate
)paren
)paren
suffix:semicolon
)brace
DECL|macro|halt
mdefine_line|#define halt() &bslash;&n;        __asm__ __volatile__ (&quot;halt&quot;)
macro_line|#endif /* _M68K_SYSTEM_H */
eof
