macro_line|#ifndef __ALPHA_PCI_H
DECL|macro|__ALPHA_PCI_H
mdefine_line|#define __ALPHA_PCI_H
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * The following structure is used to manage multiple PCI busses.&n; */
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|resource
suffix:semicolon
DECL|struct|pci_controler
r_struct
id|pci_controler
(brace
multiline_comment|/* Mandated.  */
DECL|member|next
r_struct
id|pci_controler
op_star
id|next
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|io_space
r_struct
id|resource
op_star
id|io_space
suffix:semicolon
DECL|member|mem_space
r_struct
id|resource
op_star
id|mem_space
suffix:semicolon
multiline_comment|/* Alpha specific.  */
DECL|member|config_space
r_int
r_int
id|config_space
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|first_busno
r_int
r_int
id|first_busno
suffix:semicolon
DECL|member|last_busno
r_int
r_int
id|last_busno
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Override the logic in pci_scan_bus for skipping already-configured&n;   bus numbers.  */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;alpha_mv.min_io_address
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;alpha_mv.min_mem_address
macro_line|#endif /* __ALPHA_PCI_H */
eof
