macro_line|#ifndef __I386_LITHIUM_H
DECL|macro|__I386_LITHIUM_H
mdefine_line|#define __I386_LITHIUM_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Lithium is the I/O ASIC on the SGI 320 and 540 Visual Workstations&n; */
DECL|macro|LI_PCI_A_PHYS
mdefine_line|#define&t;LI_PCI_A_PHYS&t;&t;0xfc000000&t;/* Enet is dev 3 */
DECL|macro|LI_PCI_B_PHYS
mdefine_line|#define&t;LI_PCI_B_PHYS&t;&t;0xfd000000&t;/* PIIX4 is here */
multiline_comment|/* see set_fixmap() and asm/fixmap.h */
DECL|macro|LI_PCIA_VADDR
mdefine_line|#define LI_PCIA_VADDR   (fix_to_virt(FIX_LI_PCIA))
DECL|macro|LI_PCIB_VADDR
mdefine_line|#define LI_PCIB_VADDR   (fix_to_virt(FIX_LI_PCIB))
multiline_comment|/* Not a standard PCI? (not in linux/pci.h) */
DECL|macro|LI_PCI_BUSNUM
mdefine_line|#define&t;LI_PCI_BUSNUM&t;0x44&t;&t;&t;/* lo8: primary, hi8: sub */
DECL|macro|LI_PCI_INTEN
mdefine_line|#define LI_PCI_INTEN    0x46
macro_line|#ifdef CONFIG_X86_VISWS_APIC
multiline_comment|/* More special purpose macros... */
DECL|function|li_pcia_write16
r_extern
id|__inline
r_void
id|li_pcia_write16
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|v
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|LI_PCIA_VADDR
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|li_pcia_read16
r_extern
id|__inline
r_int
r_int
id|li_pcia_read16
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|LI_PCIA_VADDR
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
DECL|function|li_pcib_write16
r_extern
id|__inline
r_void
id|li_pcib_write16
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|v
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|LI_PCIB_VADDR
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|li_pcib_read16
r_extern
id|__inline
r_int
r_int
id|li_pcib_read16
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|LI_PCIB_VADDR
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
