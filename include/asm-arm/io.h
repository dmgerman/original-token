multiline_comment|/*&n; * linux/include/asm-arm/io.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * Modifications:&n; *  16-Sep-1996&t;RMK&t;Inlined the inx/outx functions &amp; optimised for both&n; *&t;&t;&t;constant addresses and variable addresses.&n; *  04-Dec-1997&t;RMK&t;Moved a lot of this stuff to the new architecture&n; *&t;&t;&t;specific IO header files.&n; */
macro_line|#ifndef __ASM_ARM_IO_H
DECL|macro|__ASM_ARM_IO_H
mdefine_line|#define __ASM_ARM_IO_H
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/mmu.h&gt;
macro_line|#include &lt;asm/arch/io.h&gt;
multiline_comment|/* unsigned long virt_to_phys(void *x) */
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(x)&t;&t;__virt_to_phys((unsigned long)(x))
multiline_comment|/* void *phys_to_virt(unsigned long x) */
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(x)&t;&t;((void *)(__phys_to_virt((unsigned long)(x))))
multiline_comment|/*&n; * These macros actually build the multi-value IO function prototypes&n; */
DECL|macro|__OUTS
mdefine_line|#define __OUTS(s,i,x)&t;extern void outs##s(unsigned int port, const void *from, int len);
DECL|macro|__INS
mdefine_line|#define __INS(s,i,x)&t;extern void ins##s(unsigned int port, void *to, int len);
DECL|macro|__IO
mdefine_line|#define __IO(s,i,x) &bslash;&n;  __OUTS(s,i,x) &bslash;&n;  __INS(s,i,x)
id|__IO
c_func
(paren
id|b
comma
l_string|&quot;b&quot;
comma
r_char
)paren
id|__IO
c_func
(paren
id|w
comma
l_string|&quot;h&quot;
comma
r_int
)paren
id|__IO
c_func
(paren
id|l
comma
l_string|&quot;&quot;
comma
r_int
)paren
multiline_comment|/*&n; * Note that due to the way __builtin_constant_t() works, you&n; *  - can&squot;t use it inside an inline function (it will never be true)&n; *  - you don&squot;t have to worry about side effects withing the __builtin..&n; */
macro_line|#ifdef __outbc
DECL|macro|outb
mdefine_line|#define outb(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outbc((val),(port)) : __outb((val),(port)))
macro_line|#else
mdefine_line|#define outb(val,port) __outb((val),(port))
macro_line|#endif
macro_line|#ifdef __outwc
DECL|macro|outw
mdefine_line|#define outw(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outwc((val),(port)) : __outw((val),(port)))
macro_line|#else
mdefine_line|#define outw(val,port) __outw((val),(port))
macro_line|#endif
macro_line|#ifdef __outlc
DECL|macro|outl
mdefine_line|#define outl(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outlc((val),(port)) : __outl((val),(port)))
macro_line|#else
mdefine_line|#define outl(val,port) __outl((val),(port))
macro_line|#endif
macro_line|#ifdef __inbc
DECL|macro|inb
mdefine_line|#define inb(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inbc((port)) : __inb((port)))
macro_line|#else
mdefine_line|#define inb(port) __inb((port))
macro_line|#endif
macro_line|#ifdef __inwc
DECL|macro|inw
mdefine_line|#define inw(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inwc((port)) : __inw((port)))
macro_line|#else
mdefine_line|#define inw(port) __inw((port))
macro_line|#endif
macro_line|#ifdef __inlc
DECL|macro|inl
mdefine_line|#define inl(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inlc((port)) : __inl((port)))
macro_line|#else
mdefine_line|#define inl(port) __inl((port))
macro_line|#endif
multiline_comment|/*&n; * This macro will give you the translated IO address for this particular&n; * architecture, which can be used with the out_t... functions.&n; */
DECL|macro|ioaddr
mdefine_line|#define ioaddr(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __ioaddrc((port)) : __ioaddr((port)))
macro_line|#ifndef ARCH_IO_DELAY
multiline_comment|/*&n; * This architecture does not require any delayed IO.&n; * It is handled in the hardware.&n; */
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port)&t;outb((val),(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port)&t;outw((val),(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port)&t;outl((val),(port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;inb((port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;inw((port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;inl((port))
DECL|macro|outsb_p
mdefine_line|#define outsb_p(port,from,len)&t;outsb(port,from,len)
DECL|macro|outsw_p
mdefine_line|#define outsw_p(port,from,len)&t;outsw(port,from,len)
DECL|macro|outsl_p
mdefine_line|#define outsl_p(port,from,len)&t;outsl(port,from,len)
DECL|macro|insb_p
mdefine_line|#define insb_p(port,to,len)&t;insb(port,to,len)
DECL|macro|insw_p
mdefine_line|#define insw_p(port,to,len)&t;insw(port,to,len)
DECL|macro|insl_p
mdefine_line|#define insl_p(port,to,len)&t;insl(port,to,len)
macro_line|#else
multiline_comment|/*&n; * We have to delay the IO...&n; */
macro_line|#ifdef __outbc_p
mdefine_line|#define outb_p(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outbc_p((val),(port)) : __outb_p((val),(port)))
macro_line|#else
mdefine_line|#define outb_p(val,port) __outb_p((val),(port))
macro_line|#endif
macro_line|#ifdef __outwc_p
mdefine_line|#define outw_p(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outwc_p((val),(port)) : __outw_p((val),(port)))
macro_line|#else
mdefine_line|#define outw_p(val,port) __outw_p((val),(port))
macro_line|#endif
macro_line|#ifdef __outlc_p
mdefine_line|#define outl_p(val,port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __outlc_p((val),(port)) : __outl_p((val),(port)))
macro_line|#else
mdefine_line|#define outl_p(val,port) __outl_p((val),(port))
macro_line|#endif
macro_line|#ifdef __inbc_p
mdefine_line|#define inb_p(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inbc_p((port)) : __inb_p((port)))
macro_line|#else
mdefine_line|#define inb_p(port) __inb_p((port))
macro_line|#endif
macro_line|#ifdef __inwc_p
mdefine_line|#define inw_p(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inwc_p((port)) : __inw_p((port)))
macro_line|#else
mdefine_line|#define inw_p(port) __inw_p((port))
macro_line|#endif
macro_line|#ifdef __inlc_p
mdefine_line|#define inl_p(port)&t;&bslash;&n;  (__builtin_constant_p((port)) ? __inlc_p((port)) : __inl_p((port)))
macro_line|#else
mdefine_line|#define inl_p(port) __inl_p((port))
macro_line|#endif
macro_line|#endif
DECL|macro|ARCH_IO_DELAY
macro_line|#undef ARCH_IO_DELAY
DECL|macro|ARCH_IO_CONSTANT
macro_line|#undef ARCH_IO_CONSTANT
multiline_comment|/*&n; * Leftovers...&n; */
macro_line|#if 0
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (port &lt; 256)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;J&quot; (port &lt;&lt; 2));&t;&bslash;&n;&t;else if (__PORT_PCIO(port))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port &lt;&lt; 2));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (IO_BASE), &quot;r&quot; (port &lt;&lt; 2));&t;&bslash;&n;})
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (port &lt; 256)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;J&quot; (port &lt;&lt; 2));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO(port))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port &lt;&lt; 2));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; (port &lt;&lt; 2));&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#endif
eof