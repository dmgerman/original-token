macro_line|#ifndef __ALPHA_IO_H
DECL|macro|__ALPHA_IO_H
mdefine_line|#define __ALPHA_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * The hae (hardware address extension) register is used to&n; * access high IO addresses. To avoid doing an external cycle&n; * every time we need to set the hae, we have a hae cache in&n; * memory. The kernel entry code makes sure that the hae is&n; * preserved across interrupts, so it is safe to set the hae&n; * once and then depend on it staying the same in kernel code.&n; */
DECL|struct|hae
r_extern
r_struct
id|hae
(brace
DECL|member|cache
r_int
r_int
id|cache
suffix:semicolon
DECL|member|reg
r_int
r_int
op_star
id|reg
suffix:semicolon
)brace
id|hae
suffix:semicolon
multiline_comment|/*&n; * Virtual -&gt; physical identity mapping starts at this offset&n; */
DECL|macro|IDENT_ADDR
mdefine_line|#define IDENT_ADDR&t;(0xfffffc0000000000UL)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * We try to avoid hae updates (thus the cache), but when we&n; * do need to update the hae, we need to do it atomically, so&n; * that any interrupts wouldn&squot;t get confused with the hae&n; * register not being up-to-date with respect to the hardware&n; * value.&n; */
DECL|function|set_hae
r_extern
r_inline
r_void
id|set_hae
c_func
(paren
r_int
r_int
id|new_hae
)paren
(brace
r_int
r_int
id|ipl
op_assign
id|swpipl
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|hae.cache
op_assign
id|new_hae
suffix:semicolon
op_star
id|hae.reg
op_assign
id|new_hae
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|setipl
c_func
(paren
id|ipl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
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
l_int|0xffffffffUL
op_amp
(paren
r_int
r_int
)paren
id|address
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
(paren
id|address
op_plus
id|IDENT_ADDR
)paren
suffix:semicolon
)brace
macro_line|#else /* !__KERNEL__ */
multiline_comment|/*&n; * Define actual functions in private name-space so it&squot;s easier to&n; * accomodate things like XFree or svgalib that like to define their&n; * own versions of inb etc.&n; */
r_extern
r_void
id|__sethae
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* syscall */
r_extern
r_void
id|_sethae
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* cached version */
macro_line|#endif /* !__KERNEL__ */
multiline_comment|/*&n; * There are different version of the Alpha PC motherboards:&n; */
macro_line|#if defined(CONFIG_ALPHA_LCA)
macro_line|# include &lt;asm/lca.h&gt;&t;&t;/* get chip-specific definitions */
macro_line|#elif defined(CONFIG_ALPHA_APECS)
macro_line|# include &lt;asm/apecs.h&gt;&t;&t;/* get chip-specific definitions */
macro_line|#else
macro_line|# include &lt;asm/jensen.h&gt;
macro_line|#endif
multiline_comment|/*&n; * The convention used for inb/outb etc. is that names starting with&n; * two underscores are the inline versions, names starting with a&n; * single underscore are proper functions, and names starting with a&n; * letter are macros that map in some way to inline or proper function&n; * versions.  Not all that pretty, but before you change it, be sure&n; * to convince yourself that it won&squot;t break anything (in particular&n; * module support).&n; */
r_extern
r_int
r_int
id|_inb
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inw
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inl
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outb
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outw
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outl
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_readb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_readw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|_writeb
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
suffix:semicolon
r_extern
r_void
id|_writew
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
suffix:semicolon
multiline_comment|/*&n; * The platform header files may define some of these macros to use&n; * the inlined versions where appropriate.  These macros may also be&n; * redefined by userlevel programs.&n; */
macro_line|#ifndef inb
DECL|macro|inb
macro_line|# define inb(p)&t;&t;_inb((p))
macro_line|#endif
macro_line|#ifndef inw
DECL|macro|inw
macro_line|# define inw(p)&t;&t;_inw((p))
macro_line|#endif
macro_line|#ifndef inl
DECL|macro|inl
macro_line|# define inl(p)&t;&t;_inl((p))
macro_line|#endif
macro_line|#ifndef outb
DECL|macro|outb
macro_line|# define outb(b,p)&t;_outb((b),(p))
macro_line|#endif
macro_line|#ifndef outw
DECL|macro|outw
macro_line|# define outw(w,p)&t;_outw((w),(p))
macro_line|#endif
macro_line|#ifndef outl
DECL|macro|outl
macro_line|# define outl(l,p)&t;_outl((l),(p))
macro_line|#endif
macro_line|#ifndef inb_p
DECL|macro|inb_p
macro_line|# define inb_p&t;&t;inb
macro_line|#endif
macro_line|#ifndef outb_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;outb
macro_line|#endif
multiline_comment|/*&n; * The &quot;address&quot; in IO memory space is not clearly either a integer or a&n; * pointer. We will accept both, thus the casts.&n; */
macro_line|#ifndef readb
DECL|macro|readb
macro_line|# define readb(a)&t;_readb((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef readw
DECL|macro|readw
macro_line|# define readw(a)&t;_readw((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef readl
DECL|macro|readl
macro_line|# define readl(a)&t;_readl((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writeb
DECL|macro|writeb
macro_line|# define writeb(v,a)&t;_writeb((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writew
DECL|macro|writew
macro_line|# define writew(v,a)&t;_writew((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writel
DECL|macro|writel
macro_line|# define writel(v,a)&t;_writel((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|memcpy_fromio
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
id|memcpy_toio
c_func
(paren
r_int
r_int
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|memset_io
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
multiline_comment|/*&n; * String versions of in/out ops:&n; */
r_extern
r_void
id|insb
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
suffix:semicolon
r_extern
r_void
id|insw
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
suffix:semicolon
r_extern
r_void
id|insl
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
suffix:semicolon
r_extern
r_void
id|outsb
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
suffix:semicolon
r_extern
r_void
id|outsw
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
suffix:semicolon
r_extern
r_void
id|outsl
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
suffix:semicolon
multiline_comment|/*&n; * XXX - We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and &n; * just copy it. The net code will then do the checksum later. Presently &n; * only used by some shared memory 8390 ethernet cards anyway.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused)&t;memcpy_fromio((skb)-&gt;data,(src),(len))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
