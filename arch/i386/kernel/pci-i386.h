multiline_comment|/*&n; *&t;Low-Level PCI Access for i386 machines.&n; *&n; *&t;(c) 1999 Martin Mares &lt;mj@ucw.cz&gt;&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|macro|PCI_PROBE_BIOS
mdefine_line|#define PCI_PROBE_BIOS 1
DECL|macro|PCI_PROBE_CONF1
mdefine_line|#define PCI_PROBE_CONF1 2
DECL|macro|PCI_PROBE_CONF2
mdefine_line|#define PCI_PROBE_CONF2 4
DECL|macro|PCI_NO_SORT
mdefine_line|#define PCI_NO_SORT 0x100
DECL|macro|PCI_BIOS_SORT
mdefine_line|#define PCI_BIOS_SORT 0x200
DECL|macro|PCI_NO_CHECKS
mdefine_line|#define PCI_NO_CHECKS 0x400
DECL|macro|PCI_NO_PEER_FIXUP
mdefine_line|#define PCI_NO_PEER_FIXUP 0x800
DECL|macro|PCI_ASSIGN_ROMS
mdefine_line|#define PCI_ASSIGN_ROMS 0x1000
DECL|macro|PCI_NO_IRQ_SCAN
mdefine_line|#define PCI_NO_IRQ_SCAN 0x2000
r_extern
r_int
r_int
id|pci_probe
suffix:semicolon
multiline_comment|/* pci-i386.c */
r_void
id|pcibios_resource_survey
c_func
(paren
r_void
)paren
suffix:semicolon
eof
