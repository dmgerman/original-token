macro_line|#ifndef __ALPHA_PCI_H
DECL|macro|__ALPHA_PCI_H
mdefine_line|#define __ALPHA_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * The following structure is used to manage multiple PCI busses.&n; *&n; * XXX: We should solve thos problem in an architecture independant&n; * way, rather than hacking something up here.&n; */
DECL|struct|linux_hose_info
r_struct
id|linux_hose_info
(brace
DECL|member|pci_bus
r_struct
id|pci_bus
id|pci_bus
suffix:semicolon
DECL|member|next
r_struct
id|linux_hose_info
op_star
id|next
suffix:semicolon
DECL|member|pci_io_space
r_int
r_int
id|pci_io_space
suffix:semicolon
DECL|member|pci_mem_space
r_int
r_int
id|pci_mem_space
suffix:semicolon
DECL|member|pci_config_space
r_int
r_int
id|pci_config_space
suffix:semicolon
DECL|member|pci_sparse_space
r_int
r_int
id|pci_sparse_space
suffix:semicolon
DECL|member|pci_first_busno
r_int
r_int
id|pci_first_busno
suffix:semicolon
DECL|member|pci_last_busno
r_int
r_int
id|pci_last_busno
suffix:semicolon
DECL|member|pci_hose_index
r_int
r_int
id|pci_hose_index
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is indexed by a pseudo- PCI bus number to obtain the real deal.  */
r_extern
r_struct
id|linux_hose_info
op_star
id|bus2hose
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Create a handle that is OR-ed into the reported I/O space address&n;   for a device.  We use this later to find the bus a device lives on.  */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) &bslash;&n;    || defined(CONFIG_ALPHA_MCPCIA) &bslash;&n;    /* || defined(CONFIG_ALPHA_TSUNAMI) */
DECL|macro|PCI_HANDLE
mdefine_line|#define PCI_HANDLE(bus)   ((bus2hose[bus]-&gt;pci_hose_index &amp; 3UL) &lt;&lt; 32)
DECL|macro|DEV_IS_ON_PRIMARY
mdefine_line|#define DEV_IS_ON_PRIMARY(dev) &bslash;&n;  (bus2hose[(dev)-&gt;bus-&gt;number]-&gt;pci_first_busno == (dev)-&gt;bus-&gt;number)
macro_line|#else
DECL|macro|PCI_HANDLE
mdefine_line|#define PCI_HANDLE(bus)         0
DECL|macro|DEV_IS_ON_PRIMARY
mdefine_line|#define DEV_IS_ON_PRIMARY(dev)  ((dev)-&gt;bus-&gt;number == 0)
macro_line|#endif /* Multiple busses */
macro_line|#endif /* __ALPHA_PCI_H */
eof
