multiline_comment|/*&n; * $Id: io.h,v 1.25 2000/01/22 07:35:46 zaitcev Exp $&n; */
macro_line|#ifndef __SPARC_IO_H
DECL|macro|__SPARC_IO_H
mdefine_line|#define __SPARC_IO_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;  /* struct resource */
macro_line|#include &lt;asm/page.h&gt;      /* IO address mapping routines need this */
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
DECL|function|flip_dword
r_extern
id|__inline__
r_int
id|flip_dword
(paren
r_int
id|d
)paren
(brace
r_return
(paren
(paren
id|d
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
(paren
id|d
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
(paren
id|d
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|d
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|flip_word
r_extern
id|__inline__
r_int
r_int
id|flip_word
(paren
r_int
r_int
id|d
)paren
(brace
r_return
(paren
(paren
id|d
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|d
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory mapped I/O to PCI&n; */
DECL|function|readb
r_extern
id|__inline__
r_int
r_int
id|readb
c_func
(paren
r_int
r_int
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
DECL|function|readw
r_extern
id|__inline__
r_int
r_int
id|readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|flip_word
c_func
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|readl
r_extern
id|__inline__
r_int
r_int
id|readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|flip_dword
c_func
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|writeb
r_extern
id|__inline__
r_void
id|writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
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
id|b
suffix:semicolon
)brace
DECL|function|writew
r_extern
id|__inline__
r_void
id|writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
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
id|flip_word
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
DECL|function|writel
r_extern
id|__inline__
r_void
id|writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
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
id|flip_dword
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O space operations&n; *&n; * Arrangement on a Sun is somewhat complicated.&n; *&n; * First of all, we want to use standard Linux drivers&n; * for keyboard, PC serial, etc. These drivers think&n; * they access I/O space and use inb/outb.&n; * On the other hand, EBus bridge accepts PCI *memory*&n; * cycles and converts them into ISA *I/O* cycles.&n; * Ergo, we want inb &amp; outb to generate PCI memory cycles.&n; *&n; * If we want to issue PCI *I/O* cycles, we do this&n; * with a low 64K fixed window in PCIC. This window gets&n; * mapped somewhere into virtual kernel space and we&n; * can use inb/outb again.&n; */
DECL|macro|inb_local
mdefine_line|#define inb_local(addr)&t;&t;readb(addr)
DECL|macro|inb
mdefine_line|#define inb(addr)&t;&t;readb(addr)
DECL|macro|inw
mdefine_line|#define inw(addr)&t;&t;readw(addr)
DECL|macro|inl
mdefine_line|#define inl(addr)&t;&t;readl(addr)
DECL|macro|inb_p
mdefine_line|#define inb_p(addr)&t;&t;readb(addr)
DECL|macro|outb_local
mdefine_line|#define outb_local(b, addr)&t;writeb(b, addr)
DECL|macro|outb
mdefine_line|#define outb(b, addr)&t;&t;writeb(b, addr)
DECL|macro|outw
mdefine_line|#define outw(b, addr)&t;&t;writew(b, addr)
DECL|macro|outl
mdefine_line|#define outl(b, addr)&t;&t;writel(b, addr)
DECL|macro|outb_p
mdefine_line|#define outb_p(b, addr)&t;&t;writeb(b, addr)
r_extern
r_void
id|outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_extern
r_void
id|outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_extern
r_void
id|outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_extern
r_void
id|insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * SBus accessors.&n; *&n; * SBus has only one, memory mapped, I/O space.&n; * We do not need to flip bytes for SBus of course.&n; */
DECL|function|_sbus_readb
r_extern
id|__inline__
r_int
r_int
id|_sbus_readb
c_func
(paren
r_int
r_int
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
DECL|function|_sbus_readw
r_extern
id|__inline__
r_int
r_int
id|_sbus_readw
c_func
(paren
r_int
r_int
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
DECL|function|_sbus_readl
r_extern
id|__inline__
r_int
r_int
id|_sbus_readl
c_func
(paren
r_int
r_int
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
DECL|function|_sbus_writeb
r_extern
id|__inline__
r_void
id|_sbus_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
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
id|b
suffix:semicolon
)brace
DECL|function|_sbus_writew
r_extern
id|__inline__
r_void
id|_sbus_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
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
id|b
suffix:semicolon
)brace
DECL|function|_sbus_writel
r_extern
id|__inline__
r_void
id|_sbus_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
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
id|b
suffix:semicolon
)brace
multiline_comment|/*&n; * The only reason for #define&squot;s is to hide casts to unsigned long.&n; * XXX Rewrite drivers without structures for registers.&n; */
DECL|macro|sbus_readb
mdefine_line|#define sbus_readb(a)&t;_sbus_readb((unsigned long)(a))
DECL|macro|sbus_readw
mdefine_line|#define sbus_readw(a)&t;_sbus_readw((unsigned long)(a))
DECL|macro|sbus_readl
mdefine_line|#define sbus_readl(a)&t;_sbus_readl((unsigned long)(a))
DECL|macro|sbus_writeb
mdefine_line|#define sbus_writeb(v, a)&t;_sbus_writeb(v, (unsigned long)(a))
DECL|macro|sbus_writew
mdefine_line|#define sbus_writew(v, a)&t;_sbus_writew(v, (unsigned long)(a))
DECL|macro|sbus_writel
mdefine_line|#define sbus_writel(v, a)&t;_sbus_writel(v, (unsigned long)(a))
DECL|function|sbus_memset_io
r_static
r_inline
r_void
op_star
id|sbus_memset_io
c_func
(paren
r_void
op_star
id|__dst
comma
r_int
id|c
comma
id|__kernel_size_t
id|n
)paren
(brace
r_int
r_int
id|dst
op_assign
(paren
r_int
r_int
)paren
id|__dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|sbus_writeb
c_func
(paren
id|c
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|dst
suffix:semicolon
)brace
multiline_comment|/*&n; * Bus number may be embedded in the higher bits of the physical address.&n; * This is why we have no bus number argument to ioremap().&n; */
r_extern
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
multiline_comment|/* P3: talk davem into dropping &quot;name&quot; argument in favor of res-&gt;name */
multiline_comment|/*&n; * Bus number may be in res-&gt;flags... somewhere.&n; */
r_extern
r_int
r_int
id|sbus_ioremap
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* XXX Partial deallocations? I think not! */
r_extern
r_void
id|sbus_iounmap
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(x) __pa((unsigned long)(x))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(x) __va((unsigned long)(x))
multiline_comment|/*&n; * At the moment, we do not use CMOS_READ anywhere outside of rtc.c,&n; * so rtc_port is static in it. This should not change unless a new&n; * hardware pops up.&n; */
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)   (rtc_port + (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD  0
multiline_comment|/* Nothing to do */
multiline_comment|/* P3: Only IDE DMA may need these. */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif /* !(__SPARC_IO_H) */
eof
