multiline_comment|/* $Id: io.h,v 1.20 1999/06/03 15:02:50 davem Exp $ */
macro_line|#ifndef __SPARC_IO_H
DECL|macro|__SPARC_IO_H
mdefine_line|#define __SPARC_IO_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;      /* IO address mapping routines need this */
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Defines for io operations on the Sparc. Whether a memory access is going&n; * to i/o sparc is encoded in the pte. The type bits determine whether this&n; * is i/o sparc, on board memory, or VME space for VME cards. I think VME&n; * space only works on sun4&squot;s&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
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
DECL|function|inb_local
r_extern
id|__inline__
r_int
r_int
id|inb_local
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|readb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|outb_local
r_extern
id|__inline__
r_void
id|outb_local
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
r_return
id|writeb
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|inb
r_extern
id|__inline__
r_int
r_int
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|readb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|inw
r_extern
id|__inline__
r_int
r_int
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|readw
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|inl
r_extern
id|__inline__
r_int
r_int
id|inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|readl
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|outb
r_extern
id|__inline__
r_void
id|outb
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
r_return
id|writeb
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|outw
r_extern
id|__inline__
r_void
id|outw
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
r_return
id|writew
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|outl
r_extern
id|__inline__
r_void
id|outl
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
r_return
id|writel
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|outb_p
mdefine_line|#define outb_p outb
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
r_extern
r_void
id|sun4c_mapioaddr
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
id|bus_type
comma
r_int
id|rdonly
)paren
suffix:semicolon
r_extern
r_void
id|srmmu_mapioaddr
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
id|bus_type
comma
r_int
id|rdonly
)paren
suffix:semicolon
DECL|function|mapioaddr
r_extern
id|__inline__
r_void
id|mapioaddr
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|virt_addr
comma
r_int
id|bus
comma
r_int
id|rdonly
)paren
(brace
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4
suffix:colon
id|sun4c_mapioaddr
c_func
(paren
id|physaddr
comma
id|virt_addr
comma
id|bus
comma
id|rdonly
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
r_case
id|sun4e
suffix:colon
id|srmmu_mapioaddr
c_func
(paren
id|physaddr
comma
id|virt_addr
comma
id|bus
comma
id|rdonly
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;mapioaddr: Trying to map IO space for unsupported machine.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mapioaddr: sparc_cpu_model = %d&bslash;n&quot;
comma
id|sparc_cpu_model
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mapioaddr: Halting...&bslash;n&quot;
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
id|srmmu_unmapioaddr
c_func
(paren
r_int
r_int
id|virt
)paren
suffix:semicolon
r_extern
r_void
id|sun4c_unmapioaddr
c_func
(paren
r_int
r_int
id|virt
)paren
suffix:semicolon
DECL|function|unmapioaddr
r_extern
id|__inline__
r_void
id|unmapioaddr
c_func
(paren
r_int
r_int
id|virt_addr
)paren
(brace
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4
suffix:colon
id|sun4c_unmapioaddr
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
r_case
id|sun4e
suffix:colon
id|srmmu_unmapioaddr
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;unmapioaddr: sparc_cpu_model = %d, halt...&bslash;n&quot;
comma
id|sparc_cpu_model
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
op_star
id|sparc_alloc_io
(paren
id|u32
id|pa
comma
r_void
op_star
id|va
comma
r_int
id|sz
comma
r_char
op_star
id|name
comma
id|u32
id|io
comma
r_int
id|rdonly
)paren
suffix:semicolon
r_extern
r_void
id|sparc_free_io
(paren
r_void
op_star
id|vaddr
comma
r_int
id|sz
)paren
suffix:semicolon
r_extern
r_void
op_star
id|_sparc_dvma_malloc
(paren
r_int
id|sz
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Returns CPU visible address, dvmaaddr_p is a pointer to where&n; * the DVMA visible (ie. SBUS/PSYCO+PCI) address should be stored.&n; */
DECL|function|sparc_dvma_malloc
r_static
id|__inline__
r_void
op_star
id|sparc_dvma_malloc
c_func
(paren
r_int
id|size
comma
r_char
op_star
id|name
comma
id|__u32
op_star
id|dvmaaddr_p
)paren
(brace
r_void
op_star
id|cpuaddr
op_assign
id|_sparc_dvma_malloc
c_func
(paren
id|size
comma
id|name
)paren
suffix:semicolon
op_star
id|dvmaaddr_p
op_assign
(paren
id|__u32
)paren
id|cpuaddr
suffix:semicolon
r_return
id|cpuaddr
suffix:semicolon
)brace
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
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif /* !(__SPARC_IO_H) */
eof
