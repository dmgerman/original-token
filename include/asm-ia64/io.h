macro_line|#ifndef _ASM_IA64_IO_H
DECL|macro|_ASM_IA64_IO_H
mdefine_line|#define _ASM_IA64_IO_H
multiline_comment|/*&n; * This file contains the definitions for the emulated IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated to&n; * (a) handle it all in a way that makes gcc able to optimize it as&n; * well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
multiline_comment|/* We don&squot;t use IO slowdowns on the ia64, but.. */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|__IA64_UNCACHED_OFFSET
mdefine_line|#define __IA64_UNCACHED_OFFSET&t;0xc000000000000000&t;/* region 6 */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
macro_line|# ifdef __KERNEL__
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
r_static
r_inline
r_int
r_int
DECL|function|virt_to_phys
id|virt_to_phys
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|phys_to_virt
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
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt&t;phys_to_virt
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus&t;virt_to_phys
macro_line|# else /* !KERNEL */
macro_line|# endif /* !KERNEL */
multiline_comment|/*&n; * Memory fence w/accept.  This should never be used in code that is&n; * not IA-64 specific.&n; */
DECL|macro|__ia64_mf_a
mdefine_line|#define __ia64_mf_a()&t;__asm__ __volatile__ (&quot;mf.a&quot; ::: &quot;memory&quot;)
r_extern
r_inline
r_const
r_int
r_int
DECL|function|__ia64_get_io_port_base
id|__ia64_get_io_port_base
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=ar.k0;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|__IA64_UNCACHED_OFFSET
op_or
id|addr
suffix:semicolon
)brace
r_extern
r_inline
r_void
op_star
DECL|function|__ia64_mk_io_addr
id|__ia64_mk_io_addr
(paren
r_int
r_int
id|port
)paren
(brace
r_const
r_int
r_int
id|io_base
op_assign
id|__ia64_get_io_port_base
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
id|io_base
op_or
(paren
(paren
id|port
op_rshift
l_int|2
)paren
op_lshift
l_int|12
)paren
op_or
(paren
id|port
op_amp
l_int|0xfff
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * For the in/out instructions, we need to do:&n; *&n; *&t;o &quot;mf&quot; _before_ doing the I/O access to ensure that all prior&n; *&t;  accesses to memory occur before the I/O access&n; *&t;o &quot;mf.a&quot; _after_ doing the I/O access to ensure that the access&n; *&t;  has completed before we&squot;re doing any other I/O accesses&n; *&n; * The former is necessary because we might be doing normal (cached) memory&n; * accesses, e.g., to set up a DMA descriptor table and then do an &quot;outX()&quot;&n; * to tell the DMA controller to start the DMA operation.  The &quot;mf&quot; ahead&n; * of the I/O operation ensures that the DMA table is correct when the I/O&n; * access occurs.&n; *&n; * The mf.a is necessary to ensure that all I/O access occur in program&n; * order. --davidm 99/12/07 &n; */
r_extern
r_inline
r_int
r_int
DECL|function|__inb
id|__inb
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_char
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|__inw
id|__inw
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|__inl
id|__inl
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__insb
id|__insb
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_char
op_star
id|dp
op_assign
id|dst
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|dp
op_increment
op_assign
op_star
id|addr
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__insw
id|__insw
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
op_star
id|dp
op_assign
id|dst
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|dp
op_increment
op_assign
op_star
id|addr
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__insl
id|__insl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
op_star
id|dp
op_assign
id|dst
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|dp
op_increment
op_assign
op_star
id|addr
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outb
id|__outb
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outw
id|__outw
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outl
id|__outl
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outsb
id|__outsb
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_const
r_int
r_char
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|addr
op_assign
op_star
id|sp
op_increment
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outsw
id|__outsw
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_const
r_int
r_int
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|addr
op_assign
op_star
id|sp
op_increment
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__outsl
id|__outsl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_const
r_int
r_int
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|addr
op_assign
op_star
id|sp
op_increment
suffix:semicolon
)brace
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|inb
mdefine_line|#define inb&t;&t;__inb
DECL|macro|inw
mdefine_line|#define inw&t;&t;__inw
DECL|macro|inl
mdefine_line|#define inl&t;&t;__inl
DECL|macro|insb
mdefine_line|#define insb&t;&t;__insb
DECL|macro|insw
mdefine_line|#define insw&t;&t;__insw
DECL|macro|insl
mdefine_line|#define insl&t;&t;__insl
DECL|macro|outb
mdefine_line|#define outb&t;&t;__outb
DECL|macro|outw
mdefine_line|#define outw&t;&t;__outw
DECL|macro|outl
mdefine_line|#define outl&t;&t;__outl
DECL|macro|outsb
mdefine_line|#define outsb&t;&t;__outsb
DECL|macro|outsw
mdefine_line|#define outsw&t;&t;__outsw
DECL|macro|outsl
mdefine_line|#define outsl&t;&t;__outsl
multiline_comment|/*&n; * The address passed to these functions are ioremap()ped already.&n; */
r_extern
r_inline
r_int
r_char
DECL|function|__readb
id|__readb
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|__readw
id|__readw
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|__readl
id|__readl
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|__readq
id|__readq
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__writeb
id|__writeb
(paren
r_int
r_char
id|val
comma
r_void
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__writew
id|__writew
(paren
r_int
r_int
id|val
comma
r_void
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__writel
id|__writel
(paren
r_int
r_int
id|val
comma
r_void
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|__writeq
id|__writeq
(paren
r_int
r_int
id|val
comma
r_void
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|readb
mdefine_line|#define readb(a)&t;__readb((void *)(a))
DECL|macro|readw
mdefine_line|#define readw(a)&t;__readw((void *)(a))
DECL|macro|readl
mdefine_line|#define readl(a)&t;__readl((void *)(a))
DECL|macro|readq
mdefine_line|#define readq(a)&t;__readqq((void *)(a))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb&t;readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw&t;readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl&t;readl
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq&t;readq
DECL|macro|writeb
mdefine_line|#define writeb(v,a)&t;__writeb((v), (void *) (a))
DECL|macro|writew
mdefine_line|#define writew(v,a)&t;__writew((v), (void *) (a))
DECL|macro|writel
mdefine_line|#define writel(v,a)&t;__writel((v), (void *) (a))
DECL|macro|writeq
mdefine_line|#define writeq(v,a)&t;__writeq((v), (void *) (a))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb&t;writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew&t;writew
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq&t;writeq
macro_line|#ifndef inb_p
DECL|macro|inb_p
macro_line|# define inb_p&t;&t;inb
macro_line|#endif
macro_line|#ifndef inw_p
DECL|macro|inw_p
macro_line|# define inw_p&t;&t;inw
macro_line|#endif
macro_line|#ifndef inl_p
DECL|macro|inl_p
macro_line|# define inl_p&t;&t;inl
macro_line|#endif
macro_line|#ifndef outb_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;outb
macro_line|#endif
macro_line|#ifndef outw_p
DECL|macro|outw_p
macro_line|# define outw_p&t;&t;outw
macro_line|#endif
macro_line|#ifndef outl_p
DECL|macro|outl_p
macro_line|# define outl_p&t;&t;outl
macro_line|#endif
multiline_comment|/*&n; * An &quot;address&quot; in IO memory space is not clearly either an integer&n; * or a pointer. We will accept both, thus the casts.&n; *&n; * On ia-64, we access the physical I/O memory space through the&n; * uncached kernel region.&n; */
r_static
r_inline
r_void
op_star
DECL|function|ioremap
id|ioremap
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
(paren
id|__IA64_UNCACHED_OFFSET
op_or
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|iounmap
id|iounmap
(paren
r_void
op_star
id|addr
)paren
(brace
)brace
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(o,s)&t;ioremap(o,s)
macro_line|# ifdef __KERNEL__
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|__ia64_memcpy_fromio
(paren
r_void
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_memcpy_toio
(paren
r_int
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_memset_c_io
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(to,from,len) &bslash;&n;  __ia64_memcpy_fromio((to),(unsigned long)(from),(len))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(to,from,len) &bslash;&n;  __ia64_memcpy_toio((unsigned long)(to),(from),(len))
DECL|macro|memset_io
mdefine_line|#define memset_io(addr,c,len) &bslash;&n;  __ia64_memset_c_io((unsigned long)(addr),0x0101010101010101UL*(u8)(c),(len))
DECL|macro|__HAVE_ARCH_MEMSETW_IO
mdefine_line|#define __HAVE_ARCH_MEMSETW_IO
DECL|macro|memsetw_io
mdefine_line|#define memsetw_io(addr,c,len) &bslash;&n;  _memset_c_io((unsigned long)(addr),0x0001000100010001UL*(u16)(c),(len))
multiline_comment|/*&n; * XXX - We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and &n; * just copy it. The net code will then do the checksum later. Presently &n; * only used by some shared memory 8390 Ethernet cards anyway.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused)&t;&t;memcpy_fromio((skb)-&gt;data,(src),(len))
macro_line|#if 0
multiline_comment|/*&n; * XXX this is the kind of legacy stuff we want to get rid of with IA-64... --davidm 99/12/02&n; */
multiline_comment|/*&n; * This is used for checking BIOS signatures.  It&squot;s not clear at all&n; * why this is here.  This implementation seems to be the same on&n; * all architectures.  Strange.&n; */
r_static
r_inline
r_int
id|check_signature
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
mdefine_line|#define RTC_PORT(x)&t;&t;(0x70 + (x))
mdefine_line|#define RTC_ALWAYS_BCD&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * The caches on some architectures aren&squot;t DMA-coherent and have need&n; * to handle this in software.  There are two types of operations that&n; * can be applied to dma buffers.&n; *&n; * - dma_cache_inv(start, size) invalidates the affected parts of the&n; *   caches.  Dirty lines of the caches may be written back or simply&n; *   be discarded.  This operation is necessary before dma operations&n; *   to the memory.&n; *&n; * - dma_cache_wback(start, size) makes caches and memory coherent&n; *   by writing the content of the caches back to memory, if necessary&n; *   (cache flush).&n; *&n; * - dma_cache_wback_inv(start, size) Like dma_cache_wback() but the&n; *   function also invalidates the affected part of the caches as&n; *   necessary before DMA transfers from outside to memory.&n; *&n; * Fortunately, the IA-64 architecture mandates cache-coherent DMA, so&n; * these functions can be implemented as no-ops.&n; */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|# endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_IO_H */
eof
