macro_line|#ifndef __SPARC_IO_H
DECL|macro|__SPARC_IO_H
mdefine_line|#define __SPARC_IO_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/page.h&gt;      /* IO address mapping routines need this */
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Defines for io operations on the Sparc. Whether a memory access is going&n; * to i/o sparc is encoded in the pte. The type bits determine whether this&n; * is i/o sparc, on board memory, or VME space for VME cards. I think VME&n; * space only works on sun4&squot;s&n; */
DECL|function|inb_local
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|outb_local
r_extern
r_inline
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
suffix:semicolon
)brace
DECL|function|inb
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|inw
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|inl
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|outb
r_extern
r_inline
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
suffix:semicolon
)brace
DECL|function|outw
r_extern
r_inline
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
suffix:semicolon
)brace
DECL|function|outl
r_extern
r_inline
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
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions&n; */
DECL|function|readb
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|readw
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|readl
r_extern
r_inline
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
l_int|0
suffix:semicolon
)brace
DECL|function|writeb
r_extern
r_inline
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
r_return
suffix:semicolon
)brace
DECL|function|writew
r_extern
r_inline
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
r_return
suffix:semicolon
)brace
DECL|function|writel
r_extern
r_inline
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
r_return
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|outb_p
mdefine_line|#define outb_p outb
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
r_inline
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
op_star
id|sparc_alloc_io
(paren
r_void
op_star
comma
r_void
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|sparc_dvma_malloc
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(__SPARC_IO_H) */
eof