multiline_comment|/*======================================================================&n;  &n;    Cardbus device configuration&n;    &n;    cardbus.c 1.63 1999/11/08 20:47:02&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;    These routines handle allocating resources for Cardbus cards, as&n;    well as setting up and shutting down Cardbus sockets.  They are&n;    called from cs.c in response to Request/ReleaseConfiguration and&n;    Request/ReleaseIO calls.&n;&n;======================================================================*/
multiline_comment|/*&n; * This file is going away.  Cardbus handling has been re-written to be&n; * more of a PCI bridge thing, and the PCI code basically does all the&n; * resource handling. This has wrappers to make the rest of the PCMCIA&n; * subsystem not notice that it&squot;s not here any more.&n; *&n; *&t;&t;Linus, Jan 2000&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|IN_CARD_SERVICES
mdefine_line|#define IN_CARD_SERVICES
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
macro_line|#include &quot;rsrc_mgr.h&quot;
macro_line|#ifdef PCMCIA_DEBUG
DECL|variable|pc_debug
r_static
r_int
id|pc_debug
op_assign
id|PCMCIA_DEBUG
suffix:semicolon
macro_line|#endif
multiline_comment|/*====================================================================*/
DECL|macro|FIND_FIRST_BIT
mdefine_line|#define FIND_FIRST_BIT(n)&t;((n) - ((n) &amp; ((n)-1)))
DECL|macro|pci_readb
mdefine_line|#define pci_readb&t;&t;pci_read_config_byte
DECL|macro|pci_writeb
mdefine_line|#define pci_writeb&t;&t;pci_write_config_byte
DECL|macro|pci_readw
mdefine_line|#define pci_readw&t;&t;pci_read_config_word
DECL|macro|pci_writew
mdefine_line|#define pci_writew&t;&t;pci_write_config_word
DECL|macro|pci_readl
mdefine_line|#define pci_readl&t;&t;pci_read_config_dword
DECL|macro|pci_writel
mdefine_line|#define pci_writel&t;&t;pci_write_config_dword
multiline_comment|/* Offsets in the Expansion ROM Image Header */
DECL|macro|ROM_SIGNATURE
mdefine_line|#define ROM_SIGNATURE&t;&t;0x0000&t;/* 2 bytes */
DECL|macro|ROM_DATA_PTR
mdefine_line|#define ROM_DATA_PTR&t;&t;0x0018&t;/* 2 bytes */
multiline_comment|/* Offsets in the CardBus PC Card Data Structure */
DECL|macro|PCDATA_SIGNATURE
mdefine_line|#define PCDATA_SIGNATURE&t;0x0000&t;/* 4 bytes */
DECL|macro|PCDATA_VPD_PTR
mdefine_line|#define PCDATA_VPD_PTR&t;&t;0x0008&t;/* 2 bytes */
DECL|macro|PCDATA_LENGTH
mdefine_line|#define PCDATA_LENGTH&t;&t;0x000a&t;/* 2 bytes */
DECL|macro|PCDATA_REVISION
mdefine_line|#define PCDATA_REVISION&t;&t;0x000c
DECL|macro|PCDATA_IMAGE_SZ
mdefine_line|#define PCDATA_IMAGE_SZ&t;&t;0x0010&t;/* 2 bytes */
DECL|macro|PCDATA_ROM_LEVEL
mdefine_line|#define PCDATA_ROM_LEVEL&t;0x0012&t;/* 2 bytes */
DECL|macro|PCDATA_CODE_TYPE
mdefine_line|#define PCDATA_CODE_TYPE&t;0x0014
DECL|macro|PCDATA_INDICATOR
mdefine_line|#define PCDATA_INDICATOR&t;0x0015
DECL|struct|cb_config_t
r_typedef
r_struct
id|cb_config_t
(brace
DECL|member|dev
r_struct
id|pci_dev
id|dev
suffix:semicolon
DECL|typedef|cb_config_t
)brace
id|cb_config_t
suffix:semicolon
multiline_comment|/*=====================================================================&n;&n;    Expansion ROM&squot;s have a special layout, and pointers specify an&n;    image number and an offset within that image.  xlate_rom_addr()&n;    converts an image/offset address to an absolute offset from the&n;    ROM&squot;s base address.&n;    &n;=====================================================================*/
DECL|function|xlate_rom_addr
r_static
id|u_int
id|xlate_rom_addr
c_func
(paren
id|u_char
op_star
id|b
comma
id|u_int
id|addr
)paren
(brace
id|u_int
id|img
op_assign
l_int|0
comma
id|ofs
op_assign
l_int|0
comma
id|sz
suffix:semicolon
id|u_short
id|data
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readb
c_func
(paren
id|b
)paren
op_eq
l_int|0x55
)paren
op_logical_and
(paren
id|readb
c_func
(paren
id|b
op_plus
l_int|1
)paren
op_eq
l_int|0xaa
)paren
)paren
(brace
r_if
c_cond
(paren
id|img
op_eq
(paren
id|addr
op_rshift
l_int|28
)paren
)paren
r_return
(paren
id|addr
op_amp
l_int|0x0fffffff
)paren
op_plus
id|ofs
suffix:semicolon
id|data
op_assign
id|readb
c_func
(paren
id|b
op_plus
id|ROM_DATA_PTR
)paren
op_plus
(paren
id|readb
c_func
(paren
id|b
op_plus
id|ROM_DATA_PTR
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|sz
op_assign
l_int|512
op_star
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_IMAGE_SZ
)paren
op_plus
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_IMAGE_SZ
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sz
op_eq
l_int|0
)paren
op_logical_or
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_INDICATOR
)paren
op_amp
l_int|0x80
)paren
)paren
r_break
suffix:semicolon
id|b
op_add_assign
id|sz
suffix:semicolon
id|ofs
op_add_assign
id|sz
suffix:semicolon
id|img
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    These are similar to setup_cis_mem and release_cis_mem for 16-bit&n;    cards.  The &quot;result&quot; that is used externally is the cb_cis_virt&n;    pointer in the socket_info_t structure.&n;    &n;=====================================================================*/
DECL|function|cb_release_cis_mem
r_void
id|cb_release_cis_mem
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;cb_cis_virt
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;cs: cb_release_cis_mem()&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|s-&gt;cb_cis_virt
)paren
suffix:semicolon
id|s-&gt;cb_cis_virt
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;cb_cis_res
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|cb_setup_cis_mem
r_static
r_int
id|cb_setup_cis_mem
c_func
(paren
id|socket_info_t
op_star
id|s
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
r_int
id|start
comma
id|size
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
id|s-&gt;cb_cis_res
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;cb_cis_res
)paren
id|cb_release_cis_mem
c_func
(paren
id|s
)paren
suffix:semicolon
id|start
op_assign
id|res-&gt;start
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|start
op_plus
l_int|1
suffix:semicolon
id|s-&gt;cb_cis_virt
op_assign
id|ioremap
c_func
(paren
id|start
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;cb_cis_virt
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|s-&gt;cb_cis_res
op_assign
id|res
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    This is used by the CIS processing code to read CIS information&n;    from a CardBus device.&n;    &n;=====================================================================*/
DECL|function|read_cb_mem
r_void
id|read_cb_mem
c_func
(paren
id|socket_info_t
op_star
id|s
comma
id|u_char
id|fn
comma
r_int
id|space
comma
id|u_int
id|addr
comma
id|u_int
id|len
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;cs: read_cb_mem(%d, %#x, %u)&bslash;n&quot;
comma
id|space
comma
id|addr
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;cb_config
)paren
r_goto
id|fail
suffix:semicolon
id|dev
op_assign
op_amp
id|s-&gt;cb_config
(braket
id|fn
)braket
dot
id|dev
suffix:semicolon
multiline_comment|/* Config space? */
r_if
c_cond
(paren
id|space
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|addr
op_plus
id|len
OG
l_int|0x100
)paren
r_goto
id|fail
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
suffix:semicolon
id|addr
op_increment
comma
id|ptr
op_increment
comma
id|len
op_decrement
)paren
id|pci_readb
c_func
(paren
id|dev
comma
id|addr
comma
(paren
id|u_char
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|res
op_assign
id|dev-&gt;resource
op_plus
id|space
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res-&gt;flags
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|cb_setup_cis_mem
c_func
(paren
id|s
comma
id|dev
comma
id|res
)paren
op_ne
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|space
op_eq
l_int|7
)paren
(brace
id|addr
op_assign
id|xlate_rom_addr
c_func
(paren
id|s-&gt;cb_cis_virt
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_plus
id|len
OG
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
r_goto
id|fail
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|ptr
comma
id|s-&gt;cb_cis_virt
op_plus
id|addr
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
id|fail
suffix:colon
id|memset
c_func
(paren
id|ptr
comma
l_int|0xff
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    cb_alloc() and cb_free() allocate and free the kernel data&n;    structures for a Cardbus device, and handle the lowest level PCI&n;    device setup issues.&n;    &n;=====================================================================*/
DECL|function|cb_alloc
r_int
id|cb_alloc
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_dev
id|tmp
suffix:semicolon
id|u_short
id|vend
comma
id|v
comma
id|dev
suffix:semicolon
id|u_char
id|i
comma
id|hdr
comma
id|fn
suffix:semicolon
id|cb_config_t
op_star
id|c
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|bus
op_assign
id|s-&gt;cap.cb_dev-&gt;subordinate
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|tmp.bus
op_assign
id|bus
suffix:semicolon
id|tmp.sysdata
op_assign
id|bus-&gt;sysdata
suffix:semicolon
id|tmp.devfn
op_assign
l_int|0
suffix:semicolon
id|pci_readw
c_func
(paren
op_amp
id|tmp
comma
id|PCI_VENDOR_ID
comma
op_amp
id|vend
)paren
suffix:semicolon
id|pci_readw
c_func
(paren
op_amp
id|tmp
comma
id|PCI_DEVICE_ID
comma
op_amp
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cs: cb_alloc(bus %d): vendor 0x%04x, &quot;
l_string|&quot;device 0x%04x&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|vend
comma
id|dev
)paren
suffix:semicolon
id|pci_readb
c_func
(paren
op_amp
id|tmp
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr
)paren
suffix:semicolon
id|fn
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x80
)paren
(brace
r_do
(brace
id|tmp.devfn
op_assign
id|fn
suffix:semicolon
r_if
c_cond
(paren
id|pci_readw
c_func
(paren
op_amp
id|tmp
comma
id|PCI_VENDOR_ID
comma
op_amp
id|v
)paren
op_logical_or
op_logical_neg
id|v
op_logical_or
id|v
op_eq
l_int|0xffff
)paren
r_break
suffix:semicolon
id|fn
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fn
OL
l_int|8
)paren
suffix:semicolon
)brace
id|s-&gt;functions
op_assign
id|fn
suffix:semicolon
id|c
op_assign
id|kmalloc
c_func
(paren
id|fn
op_star
r_sizeof
(paren
r_struct
id|cb_config_t
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
id|CS_OUT_OF_RESOURCE
suffix:semicolon
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
id|fn
op_star
r_sizeof
(paren
r_struct
id|cb_config_t
)paren
)paren
suffix:semicolon
id|irq
op_assign
id|s-&gt;cap.pci_irq
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fn
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
op_amp
id|c
(braket
id|i
)braket
dot
id|dev
suffix:semicolon
id|u8
id|irq_pin
suffix:semicolon
r_int
id|r
suffix:semicolon
id|dev-&gt;bus
op_assign
id|bus
suffix:semicolon
id|dev-&gt;sysdata
op_assign
id|bus-&gt;sysdata
suffix:semicolon
id|dev-&gt;devfn
op_assign
id|i
suffix:semicolon
id|dev-&gt;vendor
op_assign
id|vend
suffix:semicolon
id|pci_readw
c_func
(paren
id|dev
comma
id|PCI_DEVICE_ID
comma
op_amp
id|dev-&gt;device
)paren
suffix:semicolon
id|dev-&gt;hdr_type
op_assign
id|hdr
op_amp
l_int|0x7f
suffix:semicolon
id|pci_setup_device
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* FIXME: Do we need to enable the expansion ROM? */
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
l_int|7
suffix:semicolon
id|r
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|dev-&gt;resource
op_plus
id|r
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
)brace
id|pci_enable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* XXX check return */
multiline_comment|/* Does this function have an interrupt at all? */
id|pci_readb
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq_pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_pin
)paren
(brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pci_writeb
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
)brace
id|pci_insert_device
c_func
(paren
id|dev
comma
id|bus
)paren
suffix:semicolon
)brace
id|s-&gt;cb_config
op_assign
id|c
suffix:semicolon
id|s-&gt;irq.AssignedIRQ
op_assign
id|irq
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
DECL|function|cb_free
r_void
id|cb_free
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
id|cb_config_t
op_star
id|c
op_assign
id|s-&gt;cb_config
suffix:semicolon
r_if
c_cond
(paren
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
id|s-&gt;cb_config
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|s-&gt;functions
suffix:semicolon
id|i
op_increment
)paren
id|pci_remove_device
c_func
(paren
op_amp
id|c
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cs: cb_free(bus %d)&bslash;n&quot;
comma
id|s-&gt;cap.cb_dev-&gt;subordinate-&gt;number
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*=====================================================================&n;&n;    cb_config() has the job of allocating all system resources that&n;    a Cardbus card requires.  Rather than using the CIS (which seems&n;    to not always be present), it treats the card as an ordinary PCI&n;    device, and probes the base address registers to determine each&n;    function&squot;s IO and memory space needs.&n;&n;    It is called from the RequestIO card service.&n;    &n;======================================================================*/
DECL|function|cb_config
r_int
id|cb_config
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
multiline_comment|/*======================================================================&n;&n;    cb_release() releases all the system resources (IO and memory&n;    space, and interrupt) committed for a Cardbus card by a prior call&n;    to cb_config().&n;&n;    It is called from the ReleaseIO() service.&n;    &n;======================================================================*/
DECL|function|cb_release
r_void
id|cb_release
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cs: cb_release(bus %d)&bslash;n&quot;
comma
id|s-&gt;cap.cb_dev-&gt;subordinate-&gt;number
)paren
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    cb_enable() has the job of configuring a socket for a Cardbus&n;    card, and initializing the card&squot;s PCI configuration registers.&n;&n;    It first sets up the Cardbus bridge windows, for IO and memory&n;    accesses.  Then, it initializes each card function&squot;s base address&n;    registers, interrupt line register, and command register.&n;&n;    It is called as part of the RequestConfiguration card service.&n;    It should be called after a previous call to cb_config() (via the&n;    RequestIO service).&n;    &n;======================================================================*/
DECL|function|cb_enable
r_void
id|cb_enable
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|u_char
id|i
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cs: cb_enable(bus %d)&bslash;n&quot;
comma
id|s-&gt;cap.cb_dev-&gt;subordinate-&gt;number
)paren
suffix:semicolon
multiline_comment|/* Configure bridge */
id|cb_release_cis_mem
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* Set up PCI interrupt and command registers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|s-&gt;functions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|s-&gt;cb_config
(braket
id|i
)braket
dot
id|dev
suffix:semicolon
id|pci_writeb
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
id|pci_writeb
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
id|L1_CACHE_BYTES
op_div
l_int|4
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|s-&gt;irq.AssignedIRQ
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|s-&gt;functions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|s-&gt;cb_config
(braket
id|i
)braket
dot
id|dev
suffix:semicolon
id|pci_writeb
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|s-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
)brace
id|s-&gt;socket.io_irq
op_assign
id|s-&gt;irq.AssignedIRQ
suffix:semicolon
id|s-&gt;ss_entry
op_member_access_from_pointer
id|set_socket
c_func
(paren
id|s-&gt;sock
comma
op_amp
id|s-&gt;socket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*======================================================================&n;&n;    cb_disable() unconfigures a Cardbus card previously set up by&n;    cb_enable().&n;&n;    It is called from the ReleaseConfiguration service.&n;    &n;======================================================================*/
DECL|function|cb_disable
r_void
id|cb_disable
c_func
(paren
id|socket_info_t
op_star
id|s
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cs: cb_disable(bus %d)&bslash;n&quot;
comma
id|s-&gt;cap.cb_dev-&gt;subordinate-&gt;number
)paren
suffix:semicolon
multiline_comment|/* Turn off bridge windows */
id|cb_release_cis_mem
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
eof
