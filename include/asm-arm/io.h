multiline_comment|/*&n; * linux/include/asm-arm/io.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * Modifications:&n; *  16-Sep-1996&t;RMK&t;Inlined the inx/outx functions &amp; optimised for both&n; *&t;&t;&t;constant addresses and variable addresses.&n; *  04-Dec-1997&t;RMK&t;Moved a lot of this stuff to the new architecture&n; *&t;&t;&t;specific IO header files.&n; *  27-Mar-1999&t;PJB&t;Second parameter of memcpy_toio is const..&n; *  04-Apr-1999&t;PJB&t;Added check_signature.&n; */
macro_line|#ifndef __ASM_ARM_IO_H
DECL|macro|__ASM_ARM_IO_H
mdefine_line|#define __ASM_ARM_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL&t;((void *) 0)
macro_line|#endif
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|_memcpy_fromio
c_func
(paren
r_void
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memcpy_toio
c_func
(paren
r_int
r_int
comma
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memset_io
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(to,from,len)&t;_memcpy_fromio((to),(unsigned long)(from),(len))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(to,from,len)&t;_memcpy_toio((unsigned long)(to),(from),(len))
DECL|macro|memset_io
mdefine_line|#define memset_io(addr,c,len)&t;&t;_memset_io((unsigned long)(addr),(c),(len))
macro_line|#endif
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/arch/io.h&gt;
macro_line|#include &lt;asm/proc/io.h&gt;
multiline_comment|/* unsigned long virt_to_phys(void *x) */
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(x)&t;&t;(__virt_to_phys((unsigned long)(x)))
multiline_comment|/* void *phys_to_virt(unsigned long x) */
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(x)&t;&t;((void *)(__phys_to_virt((unsigned long)(x))))
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *              address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *              to an address that the kernel can use.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)&t;(__virt_to_bus((unsigned long)(x)))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)&t;((void *)(__bus_to_virt((unsigned long)(x))))
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
multiline_comment|/* Nothing to do */
macro_line|#ifndef dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
macro_line|#endif
macro_line|#ifndef dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
macro_line|#ifndef ARCH_READWRITE
macro_line|#ifndef dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ARM_IO_H */
multiline_comment|/* for panic */
macro_line|#include &lt;linux/kernel.h&gt;
mdefine_line|#define readb(p)&t;(panic(&quot;readb called, but not implemented&quot;),0)
mdefine_line|#define readw(p)&t;(panic(&quot;readw called, but not implemented&quot;),0)
mdefine_line|#define readl(p)&t;(panic(&quot;readl called, but not implemented&quot;),0)
mdefine_line|#define writeb(v,p)&t;panic(&quot;writeb called, but not implemented&quot;)
mdefine_line|#define writew(v,p)&t;panic(&quot;writew called, but not implemented&quot;)
mdefine_line|#define writel(v,p)&t;panic(&quot;writel called, but not implemented&quot;)
macro_line|#endif
multiline_comment|/*&n; * This isn&squot;t especially architecture dependent so it seems like it&n; * might as well go here as anywhere.&n; */
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
DECL|macro|ARCH_READWRITE
macro_line|#undef ARCH_READWRITE
DECL|macro|ARCH_IO_DELAY
macro_line|#undef ARCH_IO_DELAY
DECL|macro|ARCH_IO_CONSTANT
macro_line|#undef ARCH_IO_CONSTANT
macro_line|#endif
eof
