macro_line|#ifndef __ASM_MIPS_IO_H
DECL|macro|__ASM_MIPS_IO_H
mdefine_line|#define __ASM_MIPS_IO_H
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/mipsconfig.h&gt;
multiline_comment|/*&n; * This file contains the definitions for the MIPS counterpart of the&n; * x86 in/out instructions. This heap of macros and C results in much&n; * better code than the approach of doing it in plain C, though that&squot;s&n; * probably not needed.&n; *&n; *   Ralf&n; *&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;sb&bslash;t$0,0x80(%0)&quot; &bslash;&n;&t;&t;: : &quot;r&quot; (PORT_BASE));
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s) &bslash;&n;extern inline void __out##s(unsigned int value, unsigned int port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(m) &bslash;&n;__asm__ __volatile__ (&quot;s&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(m,s) &bslash;&n;__OUT1(s) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); } &bslash;&n;__OUT1(s##c) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (port), &quot;r&quot; (PORT_BASE)); } &bslash;&n;__OUT1(s##_p) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); &bslash;&n;&t;SLOW_DOWN_IO; } &bslash;&n;__OUT1(s##c_p) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (port), &quot;r&quot; (PORT_BASE)); &bslash;&n;&t;SLOW_DOWN_IO; }
DECL|macro|__IN1
mdefine_line|#define __IN1(s) &bslash;&n;extern inline unsigned int __in##s(unsigned int port) { unsigned int _v;
DECL|macro|__IN2
mdefine_line|#define __IN2(m) &bslash;&n;__asm__ __volatile__ (&quot;l&quot; #m &quot;u&bslash;t%0,%1(%2)&bslash;n&bslash;t&quot;
DECL|macro|__IN
mdefine_line|#define __IN(m,s) &bslash;&n;__IN1(s) __IN2(m) STR(FILL_LDS) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); return _v; } &bslash;&n;__IN1(s##c) __IN2(m) STR(FILL_LDS) : &quot;=r&quot; (_v) : &quot;i&quot; (port), &quot;r&quot; (PORT_BASE)); return _v; } &bslash;&n;__IN1(s##_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); SLOW_DOWN_IO; return _v; } &bslash;&n;__IN1(s##c_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (port), &quot;r&quot; (PORT_BASE)); SLOW_DOWN_IO; return _v; }
DECL|macro|__INS1
mdefine_line|#define __INS1(s) &bslash;&n;extern inline void __ins##s(unsigned int port, void * addr, unsigned long count) {
DECL|macro|__INS2
mdefine_line|#define __INS2(m) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tl&quot; #m &quot;u&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t%1,%1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;s&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t%0,%0,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot;
DECL|macro|__INS
mdefine_line|#define __INS(m,s,i) &bslash;&n;__INS1(s) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__INS1(s##c) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (port), &quot;r&quot; (PORT_BASE), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
DECL|macro|__OUTS1
mdefine_line|#define __OUTS1(s) &bslash;&n;extern inline void __outs##s(unsigned int port, const void * addr, unsigned long count) {
DECL|macro|__OUTS2
mdefine_line|#define __OUTS2(m) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;        &quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;        &quot;1:&bslash;tl&quot; #m &quot;u&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;subu&bslash;t%1,%1,1&bslash;n&bslash;t&quot; &bslash;&n;        &quot;s&quot; #m &quot;&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;        &quot;addiu&bslash;t%0,%0,%6&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;treorder&quot;
DECL|macro|__OUTS
mdefine_line|#define __OUTS(m,s,i) &bslash;&n;__OUTS1(s) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__OUTS1(s##c) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (port), &quot;r&quot; (PORT_BASE), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
id|__IN
c_func
(paren
id|b
comma
id|b
)paren
id|__IN
c_func
(paren
id|h
comma
id|w
)paren
id|__IN
c_func
(paren
id|w
comma
id|l
)paren
id|__OUT
c_func
(paren
id|b
comma
id|b
)paren
id|__OUT
c_func
(paren
id|h
comma
id|w
)paren
id|__OUT
c_func
(paren
id|w
comma
id|l
)paren
id|__INS
c_func
(paren
id|b
comma
id|b
comma
l_int|1
)paren
id|__INS
c_func
(paren
id|h
comma
id|w
comma
l_int|2
)paren
id|__INS
c_func
(paren
id|w
comma
id|l
comma
l_int|4
)paren
id|__OUTS
c_func
(paren
id|b
comma
id|b
comma
l_int|1
)paren
id|__OUTS
c_func
(paren
id|h
comma
id|w
comma
l_int|2
)paren
id|__OUTS
c_func
(paren
id|w
comma
id|l
comma
l_int|4
)paren
multiline_comment|/*&n; * Note that due to the way __builtin_constant_p() works, you&n; *  - can&squot;t use it inside a inline function (it will never be true)&n; *  - you don&squot;t have to worry about side effects within the __builtin..&n; */
DECL|macro|outb
mdefine_line|#define outb(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outbc((val),(port)) : &bslash;&n;&t;__outb((val),(port)))
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inbc(port) : &bslash;&n;&t;__inb(port))
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outbc_p((val),(port)) : &bslash;&n;&t;__outb_p((val),(port)))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inbc_p(port) : &bslash;&n;&t;__inb_p(port))
DECL|macro|outw
mdefine_line|#define outw(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outwc((val),(port)) : &bslash;&n;&t;__outw((val),(port)))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inwc(port) : &bslash;&n;&t;__inw(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outwc_p((val),(port)) : &bslash;&n;&t;__outw_p((val),(port)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inwc_p(port) : &bslash;&n;&t;__inw_p(port))
DECL|macro|outl
mdefine_line|#define outl(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outlc((val),(port)) : &bslash;&n;&t;__outl((val),(port)))
DECL|macro|inl
mdefine_line|#define inl(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inlc(port) : &bslash;&n;&t;__inl(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outlc_p((val),(port)) : &bslash;&n;&t;__outl_p((val),(port)))
DECL|macro|inl_p
mdefine_line|#define inl_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inlc_p(port) : &bslash;&n;&t;__inl_p(port))
DECL|macro|outsb
mdefine_line|#define outsb(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outsbc((port),(addr),(count)) : &bslash;&n;&t;__outsb ((port),(addr),(count)))
DECL|macro|insb
mdefine_line|#define insb(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__insbc((port),(addr),(count)) : &bslash;&n;&t;__insb((port),(addr),(count)))
DECL|macro|outsw
mdefine_line|#define outsw(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outswc((port),(addr),(count)) : &bslash;&n;&t;__outsw ((port),(addr),(count)))
DECL|macro|insw
mdefine_line|#define insw(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inswc((port),(addr),(count)) : &bslash;&n;&t;__insw((port),(addr),(count)))
DECL|macro|outsl
mdefine_line|#define outsl(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__outslc((port),(addr),(count)) : &bslash;&n;&t;__outsl ((port),(addr),(count)))
DECL|macro|insl
mdefine_line|#define insl(port,addr,count) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 32768) ? &bslash;&n;&t;__inslc((port),(addr),(count)) : &bslash;&n;&t;__insl((port),(addr),(count)))
macro_line|#endif /* __ASM_MIPS_IO_H */
eof
