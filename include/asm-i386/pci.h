macro_line|#ifndef __i386_PCI_H
DECL|macro|__i386_PCI_H
mdefine_line|#define __i386_PCI_H
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n;   already-configured bus numbers - to be used for buggy BIOSes&n;   or architectures with incomplete PCI setup by the loader */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
macro_line|#endif /* __i386_PCI_H */
eof
