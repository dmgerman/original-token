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
macro_line|#ifndef inb
DECL|macro|inb
macro_line|# define inb(p) _inb((p))
DECL|macro|inw
macro_line|# define inw(p) _inw((p))
DECL|macro|inl
macro_line|# define inl(p) _inl((p))
DECL|macro|outb
macro_line|# define outb(b,p) _outb((b),(p))
DECL|macro|outw
macro_line|# define outw(w,p) _outw((w),(p))
DECL|macro|outl
macro_line|# define outl(l,p) _outl((l),(p))
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * There are different version of the alpha motherboards: the&n; * &quot;interesting&quot; (read: slightly braindead) Jensen type hardware&n; * and the PCI version&n; */
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/lca.h&gt;&t;&t;/* get chip-specific definitions */
macro_line|#else
macro_line|#include &lt;asm/jensen.h&gt;
macro_line|#endif
macro_line|#endif
eof
