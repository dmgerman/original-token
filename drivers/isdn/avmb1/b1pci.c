multiline_comment|/*&n; * $Id: b1pci.c,v 1.5 1998/01/31 11:14:43 calle Exp $&n; * &n; * Module for AVM B1 PCI-card.&n; * &n; * (c) Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: b1pci.c,v $&n; * Revision 1.5  1998/01/31 11:14:43  calle&n; * merged changes to 2.0 tree, prepare 2.1.82 to work.&n; *&n; * Revision 1.4  1997/12/10 20:00:50  calle&n; * get changes from 2.0 version&n; *&n; * Revision 1.3  1997/10/01 09:21:14  fritz&n; * Removed old compatibility stuff for 2.0.X kernels.&n; * From now on, this code is for 2.1.X ONLY!&n; * Old stuff is still in the separate branch.&n; *&n; * Revision 1.2  1997/05/18 09:24:13  calle&n; * added verbose disconnect reason reporting to avmb1.&n; * some fixes in capi20 interface.&n; * changed info messages for B1-PCI&n; *&n; * Revision 1.1  1997/03/30 17:10:42  calle&n; * added support for AVM-B1-PCI card.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;compat.h&quot;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/b1lli.h&gt;
macro_line|#ifndef PCI_VENDOR_ID_AVM
DECL|macro|PCI_VENDOR_ID_AVM
mdefine_line|#define PCI_VENDOR_ID_AVM&t;0x1244
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AVM_B1
DECL|macro|PCI_DEVICE_ID_AVM_B1
mdefine_line|#define PCI_DEVICE_ID_AVM_B1&t;0x700
macro_line|#endif
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.5 $&quot;
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth &lt;calle@calle.in-berlin.de&gt;&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
multiline_comment|/* ------------------------------------------------------------- */
multiline_comment|/* -------- Init &amp; Cleanup ------------------------------------- */
multiline_comment|/* ------------------------------------------------------------- */
multiline_comment|/*&n; * init / exit functions&n; */
macro_line|#ifdef MODULE
DECL|macro|b1pci_init
mdefine_line|#define b1pci_init init_module
macro_line|#endif
DECL|function|b1pci_init
r_int
id|b1pci_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_char
id|rev
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|rev
comma
id|p
op_plus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|rev
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|strcpy
c_func
(paren
id|rev
comma
l_string|&quot; ??? &quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1pci: no PCI bus present&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;b1pci: revision %s&bslash;n&quot;
comma
id|rev
)paren
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
id|PCI_VENDOR_ID_AVM
comma
id|PCI_DEVICE_ID_AVM_B1
comma
id|dev
)paren
)paren
)paren
(brace
r_int
r_int
id|ioaddr
op_assign
id|dev-&gt;base_address
(braket
l_int|1
)braket
op_amp
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
r_int
r_int
id|irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;b1pci: PCI BIOS reports AVM-B1 at i/o %#x, irq %d&bslash;n&quot;
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|avmb1_probecard
c_func
(paren
id|ioaddr
comma
id|irq
comma
id|AVM_CARDTYPE_B1
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1pci: no AVM-B1 at i/o %#x, irq %d detected&bslash;n&quot;
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|avmb1_addcard
c_func
(paren
id|ioaddr
comma
id|irq
comma
id|AVM_CARDTYPE_B1
)paren
)paren
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1pci: kernel not compiled with PCI.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
