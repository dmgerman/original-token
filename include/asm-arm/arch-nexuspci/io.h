multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/io.h&n; *&n; * Copyright (C) 1997,1998 Russell King&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * Dynamic IO functions - let the compiler&n; * optimize the expressions&n; */
DECL|macro|DECLARE_DYN_OUT
mdefine_line|#define DECLARE_DYN_OUT(fnsuffix,instr,typ)&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ void __out##fnsuffix (unsigned int value, unsigned int port)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str&quot; ##instr## &quot;&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), typ (port));&t;&t;&t;&t;&bslash;&n;}
DECL|macro|DECLARE_DYN_IN
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr,typ)&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned sz __in##fnsuffix (unsigned int port)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long value;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr&quot; ##instr## &quot;&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (value)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), typ (port));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (unsigned sz)value;&t;&t;&t;&t;&t;&t;&bslash;&n;}
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
r_return
(paren
r_int
r_int
)paren
(paren
id|PCIO_BASE
op_plus
id|port
)paren
suffix:semicolon
"&bslash;"
)brace
DECL|macro|DECLARE_IO
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr,typ)&t;&bslash;&n;&t;DECLARE_DYN_OUT(fnsuffix,instr,typ)&t;&bslash;&n;&t;DECLARE_DYN_IN(sz,fnsuffix,instr,typ)
id|DECLARE_IO
c_func
(paren
r_char
comma
id|b
comma
l_string|&quot;b&quot;
comma
l_string|&quot;Jr&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|w
comma
l_string|&quot;h&quot;
comma
l_string|&quot;r&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|l
comma
l_string|&quot;&quot;
comma
l_string|&quot;Jr&quot;
)paren
DECL|macro|DECLARE_IO
macro_line|#undef DECLARE_IO
DECL|macro|DECLARE_DYN_OUT
macro_line|#undef DECLARE_DYN_OUT
DECL|macro|DECLARE_DYN_IN
macro_line|#undef DECLARE_DYN_IN
multiline_comment|/*&n; * Constant address IO functions&n; *&n; * These have to be macros for the &squot;J&squot; constraint to work -&n; * +/-4096 immediate operand.&n; */
DECL|macro|__outbc
mdefine_line|#define __outbc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;strb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldrb&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;strh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port));&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldrh&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;result &amp; 0xffff;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr&t;%0, [%1, %2]&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long addr;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;addr = PCIO_BASE + port;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;addr;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|inb
mdefine_line|#define inb(p)&t; &t;(__builtin_constant_p((p)) ? __inbc(p)    : __inb(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t; &t;(__builtin_constant_p((p)) ? __inwc(p)    : __inw(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t; &t;(__builtin_constant_p((p)) ? __inlc(p)    : __inl(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;(__builtin_constant_p((p)) ? __outbc(v,p) : __outb(v,p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;(__builtin_constant_p((p)) ? __outwc(v,p) : __outw(v,p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;(__builtin_constant_p((p)) ? __outlc(v,p) : __outl(v,p))
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;(__builtin_constant_p((p)) ? __ioaddr(p)  : __ioaddrc(p))
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
