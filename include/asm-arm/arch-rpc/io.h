multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/io.h&n; *&n; * Copyright (C) 1997 Russell King&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *              address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *              to an address that the kernel can use.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)&t;((unsigned long)(x))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)&t;((void *)(x))
multiline_comment|/*&n; * This architecture does not require any delayed IO, and&n; * has the constant-optimised IO&n; */
DECL|macro|ARCH_IO_DELAY
macro_line|#undef&t;ARCH_IO_DELAY
multiline_comment|/*&n; * We use two different types of addressing - PC style addresses, and ARM&n; * addresses.  PC style accesses the PC hardware with the normal PC IO&n; * addresses, eg 0x3f8 for serial#1.  ARM addresses are 0x80000000+&n; * and are translated to the start of IO.  Note that all addresses are&n; * shifted left!&n; */
DECL|macro|__PORT_PCIO
mdefine_line|#define __PORT_PCIO(x)&t;(!((x) &amp; 0x80000000))
multiline_comment|/*&n; * Dynamic IO functions - let the compiler&n; * optimize the expressions&n; */
DECL|macro|DECLARE_DYN_OUT
mdefine_line|#define DECLARE_DYN_OUT(fnsuffix,instr)&t;&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ void __out##fnsuffix (unsigned int value, unsigned int port)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long temp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str&quot; ##instr## &quot;&t;%1, [%0, %2, lsl #2]&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (temp)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE - IO_BASE), &quot;Ir&quot; (IO_BASE)&t;&bslash;&n;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|DECLARE_DYN_IN
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr)&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned sz __in##fnsuffix (unsigned int port)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long temp, value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;tst&t;%2, #0x80000000&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%0, %4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;addeq&t;%0, %0, %3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr&quot; ##instr## &quot;&t;%1, [%0, %2, lsl #2]&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (temp), &quot;=r&quot; (value)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (port), &quot;Ir&quot; (PCIO_BASE - IO_BASE), &quot;Ir&quot; (IO_BASE)&t;&t;&bslash;&n;&t;: &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (unsigned sz)value;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|function|__ioaddr
r_extern
id|__inline__
r_int
r_int
id|__ioaddr
(paren
r_int
r_int
id|port
)paren
"&bslash;"
(brace
"&bslash;"
r_if
c_cond
(paren
id|__PORT_PCIO
c_func
(paren
id|port
)paren
)paren
"&bslash;"
r_return
(paren
r_int
r_int
)paren
(paren
id|PCIO_BASE
op_plus
(paren
id|port
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
"&bslash;"
r_else
"&bslash;"
r_return
(paren
r_int
r_int
)paren
(paren
id|IO_BASE
op_plus
(paren
id|port
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
"&bslash;"
)brace
DECL|macro|DECLARE_IO
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr)&t;&bslash;&n;&t;DECLARE_DYN_OUT(fnsuffix,instr)&t;&bslash;&n;&t;DECLARE_DYN_IN(sz,fnsuffix,instr)
id|DECLARE_IO
c_func
(paren
r_char
comma
id|b
comma
l_string|&quot;b&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|w
comma
l_string|&quot;&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|l
comma
l_string|&quot;&quot;
)paren
DECL|macro|DECLARE_IO
macro_line|#undef DECLARE_IO
DECL|macro|DECLARE_DYN_OUT
macro_line|#undef DECLARE_DYN_OUT
DECL|macro|DECLARE_DYN_IN
macro_line|#undef DECLARE_DYN_IN
multiline_comment|/*&n; * Constant address IO functions&n; *&n; * These have to be macros for the &squot;J&squot; constraint to work -&n; * +/-4096 immediate operand.&n; */
DECL|macro|__outbc
mdefine_line|#define __outbc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;strb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (value), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldrb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v|v&lt;&lt;16), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result &amp; 0xffff;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long v = value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;str&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (v), &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&t;&bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ldr&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (result) : &quot;r&quot; (IO_BASE), &quot;r&quot; ((port) &lt;&lt; 2));&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long addr;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__PORT_PCIO((port)))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;addr = PCIO_BASE + ((port) &lt;&lt; 2);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;addr = IO_BASE + ((port) &lt;&lt; 2);&t;&t;&t;&t;&t;&bslash;&n;&t;addr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Translated address IO functions&n; *&n; * IO address has already been translated to a virtual address&n; */
DECL|macro|outb_t
mdefine_line|#define outb_t(v,p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p) = (v))
DECL|macro|inb_t
mdefine_line|#define inb_t(p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p))
DECL|macro|outl_t
mdefine_line|#define outl_t(v,p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p) = (v))
DECL|macro|inl_t
mdefine_line|#define inl_t(p)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p))
macro_line|#endif
eof