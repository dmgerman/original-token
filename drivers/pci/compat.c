multiline_comment|/*&n; *&t;$Id: compat.c,v 1.1 1998/02/16 10:35:50 mj Exp $&n; *&n; *&t;PCI Bus Services -- Function For Backward Compatibility&n; *&n; *&t;Copyright 1998 Martin Mares&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
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
eof