multiline_comment|/*&n; *&t;$Id: oldproc.c,v 1.24 1998/10/11 15:13:04 mj Exp $&n; *&n; *&t;Backward-compatible procfs interface for PCI.&n; *&n; *&t;Copyright 1993, 1994, 1995, 1997 Drew Eckhardt, Frederic Potter,&n; *&t;David Mosberger-Tang, Martin Mares&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|struct|pci_device_info
r_struct
id|pci_device_info
(brace
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|seen
r_int
r_int
id|seen
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_vendor_info
r_struct
id|pci_vendor_info
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|devices
r_struct
id|pci_device_info
op_star
id|devices
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is ridiculous, but we want the strings in&n; * the .init section so that they don&squot;t take up&n; * real memory.. Parse the same file multiple times&n; * to get all the info.&n; */
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;static const char __vendorstr_##vendor[] __initdata = name;
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name ) &t;static const char __devicestr_##vendor##device[] __initdata = name;
macro_line|#include &quot;devlist.h&quot;
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;static struct pci_device_info __devices_##vendor[] __initdata = {
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()&t;&t;&t;};
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name )&t;{ PCI_DEVICE_ID_##device, 0, __devicestr_##vendor##device },
macro_line|#include &quot;devlist.h&quot;
DECL|variable|pci_vendor_list
r_static
r_const
r_struct
id|pci_vendor_info
id|__initdata
id|pci_vendor_list
(braket
)braket
op_assign
(brace
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;{ PCI_VENDOR_ID_##vendor, sizeof(__devices_##vendor) / sizeof(struct pci_device_info), __vendorstr_##vendor, __devices_##vendor },
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name )
macro_line|#include &quot;devlist.h&quot;
)brace
suffix:semicolon
DECL|macro|VENDORS
mdefine_line|#define VENDORS (sizeof(pci_vendor_list)/sizeof(struct pci_vendor_info))
DECL|function|pci_namedevice
r_void
id|__init
id|pci_namedevice
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_const
r_struct
id|pci_vendor_info
op_star
id|vendor_p
op_assign
id|pci_vendor_list
suffix:semicolon
r_int
id|i
op_assign
id|VENDORS
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|vendor_p-&gt;vendor
op_eq
id|dev-&gt;vendor
)paren
r_goto
id|match_vendor
suffix:semicolon
id|vendor_p
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
multiline_comment|/* Coulding find either the vendor nor the device */
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;PCI&lt;%d:%04x&gt; %04x:%04x&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
r_return
suffix:semicolon
id|match_vendor
suffix:colon
(brace
r_struct
id|pci_device_info
op_star
id|device_p
op_assign
id|vendor_p-&gt;devices
suffix:semicolon
r_int
id|i
op_assign
id|vendor_p-&gt;nr
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|device_p-&gt;device
op_eq
id|dev-&gt;device
)paren
r_goto
id|match_device
suffix:semicolon
id|device_p
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Ok, found the vendor, but unknown device */
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;PCI&lt;%d:%04x&gt; %04x:%04x (%s)&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|vendor_p-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Full match */
id|match_device
suffix:colon
(brace
r_char
op_star
id|n
op_assign
id|dev-&gt;name
op_plus
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;%s %s&quot;
comma
id|vendor_p-&gt;name
comma
id|device_p-&gt;name
)paren
suffix:semicolon
r_int
id|nr
op_assign
id|device_p-&gt;seen
op_plus
l_int|1
suffix:semicolon
id|device_p-&gt;seen
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
l_int|1
)paren
id|sprintf
c_func
(paren
id|n
comma
l_string|&quot; (#%d)&quot;
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
)brace
eof
