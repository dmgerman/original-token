multiline_comment|/*&n; *&t;$Id: compat.c,v 1.1 1998/02/16 10:35:50 mj Exp $&n; *&n; *&t;PCI Bus Services -- Function For Backward Compatibility&n; *&n; *&t;Copyright 1998--2000 Martin Mares &lt;mj@suse.cz&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
r_int
DECL|function|pcibios_present
id|pcibios_present
c_func
(paren
r_void
)paren
(brace
r_return
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|pci_devices
)paren
suffix:semicolon
)brace
r_int
DECL|function|pcibios_find_class
id|pcibios_find_class
c_func
(paren
r_int
r_int
r_class
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|devfn
)paren
(brace
r_const
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_class
c_func
(paren
r_class
comma
id|dev
)paren
)paren
)paren
r_if
c_cond
(paren
id|index
op_eq
id|cnt
op_increment
)paren
(brace
op_star
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
op_star
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_int
DECL|function|pcibios_find_device
id|pcibios_find_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|devfn
)paren
(brace
r_const
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|vendor
comma
id|device
comma
id|dev
)paren
)paren
)paren
r_if
c_cond
(paren
id|index
op_eq
id|cnt
op_increment
)paren
(brace
op_star
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
op_star
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|macro|PCI_OP
mdefine_line|#define PCI_OP(rw,size,type)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;int pcibios_##rw##_config_##size (unsigned char bus, unsigned char dev_fn,&t;&bslash;&n;&t;&t;&t;&t;  unsigned char where, unsigned type val)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct pci_dev *dev = pci_find_slot(bus, dev_fn);&t;&t;&t;&bslash;&n;&t;if (!dev) return PCIBIOS_DEVICE_NOT_FOUND;&t;&t;&t;&t;&bslash;&n;&t;return pci_##rw##_config_##size(dev, where, val);&t;&t;&t;&bslash;&n;}
id|PCI_OP
c_func
(paren
id|read
comma
id|byte
comma
r_char
op_star
)paren
id|PCI_OP
c_func
(paren
id|read
comma
id|word
comma
r_int
op_star
)paren
id|PCI_OP
c_func
(paren
id|read
comma
id|dword
comma
r_int
op_star
)paren
id|PCI_OP
c_func
(paren
id|write
comma
id|byte
comma
r_char
)paren
id|PCI_OP
c_func
(paren
id|write
comma
id|word
comma
r_int
)paren
id|PCI_OP
c_func
(paren
id|write
comma
id|dword
comma
r_int
)paren
eof
