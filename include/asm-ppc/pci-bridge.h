macro_line|#ifndef _ASM_PCI_BRIDGE_H
DECL|macro|_ASM_PCI_BRIDGE_H
mdefine_line|#define _ASM_PCI_BRIDGE_H
r_int
r_int
id|pmac_find_bridges
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * pci_io_base returns the memory address at which you can access&n; * the I/O space for PCI bus number `bus&squot; (or NULL on error).&n; */
r_void
op_star
id|pci_io_base
c_func
(paren
r_int
r_int
id|bus
)paren
suffix:semicolon
multiline_comment|/*&n; * pci_device_loc returns the bus number and device/function number&n; * for a device on a PCI bus, given its device_node struct.&n; * It returns 0 if OK, -1 on error.&n; */
r_int
id|pci_device_loc
c_func
(paren
r_struct
id|device_node
op_star
id|dev
comma
r_int
r_char
op_star
id|bus_ptr
comma
r_int
r_char
op_star
id|devfn_ptr
)paren
suffix:semicolon
macro_line|#endif
eof