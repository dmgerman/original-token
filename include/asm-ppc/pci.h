macro_line|#ifndef __PPC_PCI_H
DECL|macro|__PPC_PCI_H
mdefine_line|#define __PPC_PCI_H
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n; * already-configured bus numbers - to be used for buggy BIOSes&n; * or architectures with incomplete PCI setup by the loader.&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x10000000
macro_line|#endif /* __PPC_PCI_H */
eof
