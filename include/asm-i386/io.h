macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
multiline_comment|/*&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; */
macro_line|#ifdef SLOW_IO_BY_JUMPING
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO __asm__ __volatile__(&quot;jmp 1f&bslash;n1:&bslash;tjmp 1f&bslash;n1:&quot;)
macro_line|#else
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO __asm__ __volatile__(&quot;outb %al,$0x80&quot;)
macro_line|#endif
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s,x) &bslash;&n;extern inline void __out##s(unsigned x value, unsigned short port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(s,s1,s2) &bslash;&n;__asm__ __volatile__ (&quot;out&quot; #s &quot; %&quot; s1 &quot;0,%&quot; s2 &quot;1&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(s,s1,x) &bslash;&n;__OUT1(s,x) __OUT2(s,s1,&quot;w&quot;) : : &quot;a&quot; (value), &quot;d&quot; (port)); } &bslash;&n;__OUT1(s##c,x) __OUT2(s,s1,&quot;&quot;) : : &quot;a&quot; (value), &quot;i&quot; (port)); } &bslash;&n;__OUT1(s##_p,x) __OUT2(s,s1,&quot;w&quot;) : : &quot;a&quot; (value), &quot;d&quot; (port)); SLOW_DOWN_IO; } &bslash;&n;__OUT1(s##c_p,x) __OUT2(s,s1,&quot;&quot;) : : &quot;a&quot; (value), &quot;i&quot; (port)); SLOW_DOWN_IO; }
DECL|macro|__IN1
mdefine_line|#define __IN1(s) &bslash;&n;extern inline unsigned int __in##s(unsigned short port) { unsigned int _v;
DECL|macro|__IN2
mdefine_line|#define __IN2(s,s1,s2) &bslash;&n;__asm__ __volatile__ (&quot;in&quot; #s &quot; %&quot; s2 &quot;1,%&quot; s1 &quot;0&quot;
DECL|macro|__IN
mdefine_line|#define __IN(s,s1,i...) &bslash;&n;__IN1(s) __IN2(s,s1,&quot;w&quot;) : &quot;=a&quot; (_v) : &quot;d&quot; (port) ,##i ); return _v; } &bslash;&n;__IN1(s##c) __IN2(s,s1,&quot;&quot;) : &quot;=a&quot; (_v) : &quot;i&quot; (port) ,##i ); return _v; } &bslash;&n;__IN1(s##_p) __IN2(s,s1,&quot;w&quot;) : &quot;=a&quot; (_v) : &quot;d&quot; (port) ,##i ); SLOW_DOWN_IO; return _v; } &bslash;&n;__IN1(s##c_p) __IN2(s,s1,&quot;&quot;) : &quot;=a&quot; (_v) : &quot;i&quot; (port) ,##i ); SLOW_DOWN_IO; return _v; }
DECL|macro|__INS
mdefine_line|#define __INS(s) &bslash;&n;extern inline void ins##s(unsigned short port, void * addr, unsigned long count) &bslash;&n;{ __asm__ __volatile__ (&quot;cld ; rep ; ins&quot; #s &bslash;&n;: &quot;=D&quot; (addr), &quot;=c&quot; (count) : &quot;d&quot; (port),&quot;0&quot; (addr),&quot;1&quot; (count)); }
DECL|macro|__OUTS
mdefine_line|#define __OUTS(s) &bslash;&n;extern inline void outs##s(unsigned short port, const void * addr, unsigned long count) &bslash;&n;{ __asm__ __volatile__ (&quot;cld ; rep ; outs&quot; #s &bslash;&n;: &quot;=S&quot; (addr), &quot;=c&quot; (count) : &quot;d&quot; (port),&quot;0&quot; (addr),&quot;1&quot; (count)); }
id|__IN
c_func
(paren
id|b
comma
l_string|&quot;b&quot;
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
id|__IN
c_func
(paren
id|w
comma
l_string|&quot;w&quot;
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
id|__IN
c_func
(paren
id|l
comma
l_string|&quot;&quot;
)paren
id|__OUT
c_func
(paren
id|b
comma
l_string|&quot;b&quot;
comma
r_char
)paren
id|__OUT
c_func
(paren
id|w
comma
l_string|&quot;w&quot;
comma
r_int
)paren
id|__OUT
c_func
(paren
id|l
comma
comma
r_int
)paren
id|__INS
c_func
(paren
id|b
)paren
id|__INS
c_func
(paren
id|w
)paren
id|__INS
c_func
(paren
id|l
)paren
id|__OUTS
c_func
(paren
id|b
)paren
id|__OUTS
c_func
(paren
id|w
)paren
id|__OUTS
c_func
(paren
id|l
)paren
multiline_comment|/*&n; * Note that due to the way __builtin_constant_p() works, you&n; *  - can&squot;t use it inside a inline function (it will never be true)&n; *  - you don&squot;t have to worry about side effects within the __builtin..&n; */
DECL|macro|outb
mdefine_line|#define outb(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outbc((val),(port)) : &bslash;&n;&t;__outb((val),(port)))
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inbc(port) : &bslash;&n;&t;__inb(port))
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outbc_p((val),(port)) : &bslash;&n;&t;__outb_p((val),(port)))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inbc_p(port) : &bslash;&n;&t;__inb_p(port))
DECL|macro|outw
mdefine_line|#define outw(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outwc((val),(port)) : &bslash;&n;&t;__outw((val),(port)))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inwc(port) : &bslash;&n;&t;__inw(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outwc_p((val),(port)) : &bslash;&n;&t;__outw_p((val),(port)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inwc_p(port) : &bslash;&n;&t;__inw_p(port))
DECL|macro|outl
mdefine_line|#define outl(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outlc((val),(port)) : &bslash;&n;&t;__outl((val),(port)))
DECL|macro|inl
mdefine_line|#define inl(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inlc(port) : &bslash;&n;&t;__inl(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outlc_p((val),(port)) : &bslash;&n;&t;__outl_p((val),(port)))
DECL|macro|inl_p
mdefine_line|#define inl_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inlc_p(port) : &bslash;&n;&t;__inl_p(port))
macro_line|#endif
eof
