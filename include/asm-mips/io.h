macro_line|#ifndef __ASM_MIPS_IO_H
DECL|macro|__ASM_MIPS_IO_H
mdefine_line|#define __ASM_MIPS_IO_H
multiline_comment|/*&n; * Slowdown I/O port space accesses for antique hardware.&n; */
DECL|macro|CONF_SLOWDOWN_IO
macro_line|#undef CONF_SLOWDOWN_IO
macro_line|#include &lt;asm/mipsconfig.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * This file contains the definitions for the MIPS counterpart of the&n; * x86 in/out instructions. This heap of macros and C results in much&n; * better code than the approach of doing it in plain C.  The macros&n; * result in code that is to fast for certain hardware.  On the other&n; * side the performance of the string functions should be improved for&n; * sake of certain devices like EIDE disks that do highspeed polled I/O.&n; *&n; *   Ralf&n; *&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; *&n; */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;sb&bslash;t$0,0x80(%0)&quot; &bslash;&n;&t;&t;: : &quot;r&quot; (PORT_BASE));
macro_line|#ifdef CONF_SLOWDOWN_IO
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are trivial on the 1:1 Linux/MIPS mapping&n; */
DECL|function|virt_to_phys
r_extern
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_extern
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG0ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
r_extern
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG0ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is is mapped&n; * for the processor.&n; */
r_extern
r_int
r_int
id|isa_slot_offset
suffix:semicolon
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the x86 architecture, we just read/write the&n; * memory location directly.&n; *&n; * On MIPS, we have the whole physical address space mapped at all&n; * times, so &quot;ioremap()&quot; and &quot;iounmap()&quot; do not need to do anything.&n; * (This isn&squot;t true for all machines but we still handle these cases&n; * with wired TLB entries anyway ...)&n; *&n; * We cheat a bit and always return uncachable areas until we&squot;ve fixed&n; * the drivers to handle caching properly.&n; */
DECL|function|ioremap
r_extern
r_inline
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This one maps high address device memory and turns off caching for that area.&n; * it&squot;s useful if some control registers are in such an area and write combining&n; * or read caching is not desirable:&n; */
DECL|function|ioremap_nocache
r_extern
r_inline
r_void
op_star
id|ioremap_nocache
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|offset
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_extern
r_inline
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
)brace
multiline_comment|/*&n; * XXX We need system specific versions of these to handle EISA address bits&n; * 24-31 on SNI.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (isa_slot_offset + (unsigned long)(addr)))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) (isa_slot_offset + (unsigned long)(addr)))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) (isa_slot_offset + (unsigned long)(addr)))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (*(volatile unsigned char *) (isa_slot_offset + (unsigned long)(addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) (*(volatile unsigned short *) (isa_slot_offset + (unsigned long)(addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (*(volatile unsigned int *) (isa_slot_offset + (unsigned long)(addr)) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(isa_slot_offset + (unsigned long)a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(isa_slot_offset + (unsigned long)(b)),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(isa_slot_offset + (unsigned long)(a)),(b),(c))
multiline_comment|/*&n; * We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and&n; * just copy it. The net code will then do the checksum later.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused)&t;memcpy_fromio((skb)-&gt;data,(src),(len))
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_int
r_int
id|io_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|io_addr
op_increment
suffix:semicolon
id|signature
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s) &bslash;&n;extern inline void __out##s(unsigned int value, unsigned int port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(m) &bslash;&n;__asm__ __volatile__ (&quot;s&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(m,s) &bslash;&n;__OUT1(s) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); } &bslash;&n;__OUT1(s##c) __OUT2(m) : : &quot;r&quot; (value), &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE)); } &bslash;&n;__OUT1(s##_p) __OUT2(m) : : &quot;r&quot; (value), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); &bslash;&n;&t;SLOW_DOWN_IO; } &bslash;&n;__OUT1(s##c_p) __OUT2(m) : : &quot;r&quot; (value), &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE)); &bslash;&n;&t;SLOW_DOWN_IO; }
DECL|macro|__IN1
mdefine_line|#define __IN1(t,s) &bslash;&n;extern __inline__ t __in##s(unsigned int port) { t _v;
multiline_comment|/*&n; * Required nops will be inserted by the assembler&n; */
DECL|macro|__IN2
mdefine_line|#define __IN2(m) &bslash;&n;__asm__ __volatile__ (&quot;l&quot; #m &quot;&bslash;t%0,%1(%2)&quot;
DECL|macro|__IN
mdefine_line|#define __IN(t,m,s) &bslash;&n;__IN1(t,s) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); return _v; } &bslash;&n;__IN1(t,s##c) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE)); return _v; } &bslash;&n;__IN1(t,s##_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port)); SLOW_DOWN_IO; return _v; } &bslash;&n;__IN1(t,s##c_p) __IN2(m) : &quot;=r&quot; (_v) : &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE)); SLOW_DOWN_IO; return _v; }
DECL|macro|__INS1
mdefine_line|#define __INS1(s) &bslash;&n;extern inline void __ins##s(unsigned int port, void * addr, unsigned long count) {
DECL|macro|__INS2
mdefine_line|#define __INS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;s&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addiu&bslash;t%0,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot;
DECL|macro|__INS
mdefine_line|#define __INS(m,s,i) &bslash;&n;__INS1(s) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__INS1(s##c) __INS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
DECL|macro|__OUTS1
mdefine_line|#define __OUTS1(s) &bslash;&n;extern inline void __outs##s(unsigned int port, const void * addr, unsigned long count) {
DECL|macro|__OUTS2
mdefine_line|#define __OUTS2(m) &bslash;&n;if (count) &bslash;&n;__asm__ __volatile__ ( &bslash;&n;        &quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tnoat&bslash;n&quot; &bslash;&n;        &quot;1:&bslash;tl&quot; #m &quot;&bslash;t$1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot; &bslash;&n;        &quot;s&quot; #m &quot;&bslash;t$1,%4(%5)&bslash;n&bslash;t&quot; &bslash;&n;        &quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;        &quot;addiu&bslash;t%0,%6&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;        &quot;.set&bslash;treorder&quot;
DECL|macro|__OUTS
mdefine_line|#define __OUTS(m,s,i) &bslash;&n;__OUTS1(s) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;i&quot; (0), &quot;r&quot; (PORT_BASE+port), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);} &bslash;&n;__OUTS1(s##c) __OUTS2(m) &bslash;&n;&t;: &quot;=r&quot; (addr), &quot;=r&quot; (count) &bslash;&n;&t;: &quot;0&quot; (addr), &quot;1&quot; (count), &quot;ir&quot; (port), &quot;r&quot; (PORT_BASE), &quot;I&quot; (i) &bslash;&n;&t;: &quot;$1&quot;);}
id|__IN
c_func
(paren
r_int
r_char
comma
id|b
comma
id|b
)paren
id|__IN
c_func
(paren
r_int
r_int
comma
id|h
comma
id|w
)paren
id|__IN
c_func
(paren
r_int
r_int
comma
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
multiline_comment|/*&n; * Note that due to the way __builtin_constant_p() works, you&n; *  - can&squot;t use it inside an inline function (it will never be true)&n; *  - you don&squot;t have to worry about side effects within the __builtin..&n; */
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
