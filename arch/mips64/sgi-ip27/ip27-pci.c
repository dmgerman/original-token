multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/pci/bridge.h&gt;
macro_line|#include &lt;asm/paccess.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
macro_line|#include &lt;asm/sn/sn0/hub.h&gt;
multiline_comment|/*&n; * Max #PCI busses we can handle; ie, max #PCI bridges.&n; */
DECL|macro|MAX_PCI_BUSSES
mdefine_line|#define MAX_PCI_BUSSES&t;&t;20
multiline_comment|/*&n; * Max #PCI devices (like scsi controllers) we handle on a bus.&n; */
DECL|macro|MAX_DEVICES_PER_PCIBUS
mdefine_line|#define MAX_DEVICES_PER_PCIBUS&t;8
multiline_comment|/*&n; * No locking needed until PCI initialization is done parallely.&n; */
DECL|variable|irqstore
r_int
id|irqstore
(braket
id|MAX_PCI_BUSSES
)braket
(braket
id|MAX_DEVICES_PER_PCIBUS
)braket
suffix:semicolon
DECL|variable|lastirq
r_int
id|lastirq
op_assign
id|BASE_PCI_IRQ
suffix:semicolon
multiline_comment|/*&n; * Translate from irq to software PCI bus number and PCI slot.&n; */
DECL|variable|irq_to_bus
r_int
id|irq_to_bus
(braket
id|MAX_PCI_BUSSES
op_star
id|MAX_DEVICES_PER_PCIBUS
)braket
suffix:semicolon
DECL|variable|irq_to_slot
r_int
id|irq_to_slot
(braket
id|MAX_PCI_BUSSES
op_star
id|MAX_DEVICES_PER_PCIBUS
)braket
suffix:semicolon
multiline_comment|/*&n; * The Bridge ASIC supports both type 0 and type 1 access.  Type 1 is&n; * not really documented, so right now I can&squot;t write code which uses it.&n; * Therefore we use type 0 accesses for now even though they won&squot;t work&n; * correcly for PCI-to-PCI bridges.&n; */
DECL|macro|CF0_READ_PCI_CFG
mdefine_line|#define CF0_READ_PCI_CFG(dev,where,value,bm,mask)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bridge_t *bridge;                                               &bslash;&n;&t;int slot = PCI_SLOT(dev-&gt;devfn);&t;&t;&t;&t;&bslash;&n;&t;int fn = PCI_FUNC(dev-&gt;devfn);&t;&t;&t;&t;&t;&bslash;&n;&t;volatile u32 *addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32 cf, __bit;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int bus_id = (unsigned) dev-&gt;bus-&gt;number;              &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bridge = (bridge_t *) NODE_SWIN_BASE(bus_to_nid[bus_id],        &bslash;&n;                                             bus_to_wid[bus_id]);       &bslash;&n;                                                                        &bslash;&n;&t;/*if (dev-&gt;bus-&gt;number)&t;&t;&t; */&t;&t;&t;&bslash;&n;&t;/*&t;return PCIBIOS_DEVICE_NOT_FOUND; */&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__bit = (((where) &amp; (bm)) &lt;&lt; 3);&t;&t;&t;&t;&bslash;&n;&t;addr = &amp;bridge-&gt;b_type0_cfg_dev[slot].f[fn].l[where &gt;&gt; 2];&t;&bslash;&n;&t;if (get_dbe(cf, addr))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_DEVICE_NOT_FOUND;&t;&t;&t;&bslash;&n;&t;*value = (cf &gt;&gt; __bit) &amp; (mask);&t;&t;&t;&t;&bslash;&n;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
r_static
r_int
DECL|function|pci_conf0_read_config_byte
id|pci_conf0_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|value
)paren
(brace
id|CF0_READ_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|3
comma
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf0_read_config_word
id|pci_conf0_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|value
)paren
(brace
id|CF0_READ_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|2
comma
l_int|0xffff
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf0_read_config_dword
id|pci_conf0_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|value
)paren
(brace
id|CF0_READ_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|0
comma
l_int|0xffffffff
)paren
suffix:semicolon
)brace
DECL|macro|CF0_WRITE_PCI_CFG
mdefine_line|#define CF0_WRITE_PCI_CFG(dev,where,value,bm,mask)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bridge_t *bridge;                                               &bslash;&n;&t;int slot = PCI_SLOT(dev-&gt;devfn);&t;&t;&t;&t;&bslash;&n;&t;int fn = PCI_FUNC(dev-&gt;devfn);&t;&t;&t;&t;&t;&bslash;&n;&t;volatile u32 *addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32 cf, __bit;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int bus_id = (unsigned) dev-&gt;bus-&gt;number;              &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bridge = (bridge_t *) NODE_SWIN_BASE(bus_to_nid[bus_id],        &bslash;&n;                                             bus_to_wid[bus_id]);       &bslash;&n;                                                                        &bslash;&n;&t;/* if (dev-&gt;bus-&gt;number)&t;&t; */&t;&t;&t;&bslash;&n;&t;/* &t;return PCIBIOS_DEVICE_NOT_FOUND; */&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (dev-&gt;vendor == PCI_VENDOR_ID_SGI&t;&t;&t;&t;&bslash;&n;&t;    &amp;&amp; dev-&gt;device == PCI_DEVICE_ID_SGI_IOC3)&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__bit = (((where) &amp; (bm)) &lt;&lt; 3);&t;&t;&t;&t;&bslash;&n;&t;addr = &amp;bridge-&gt;b_type0_cfg_dev[slot].f[fn].l[where &gt;&gt; 2];&t;&bslash;&n;&t;if (get_dbe(cf, addr))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_DEVICE_NOT_FOUND;&t;&t;&t;&bslash;&n;&t;cf &amp;= (~mask);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cf |= (value);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;put_dbe(cf, addr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
r_static
r_int
DECL|function|pci_conf0_write_config_byte
id|pci_conf0_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
id|CF0_WRITE_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|3
comma
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf0_write_config_word
id|pci_conf0_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
id|CF0_WRITE_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|2
comma
l_int|0xffff
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_conf0_write_config_dword
id|pci_conf0_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|value
)paren
(brace
id|CF0_WRITE_PCI_CFG
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|0
comma
l_int|0xffffffff
)paren
suffix:semicolon
)brace
DECL|variable|bridge_pci_ops
r_static
r_struct
id|pci_ops
id|bridge_pci_ops
op_assign
(brace
id|pci_conf0_read_config_byte
comma
id|pci_conf0_read_config_word
comma
id|pci_conf0_read_config_dword
comma
id|pci_conf0_write_config_byte
comma
id|pci_conf0_write_config_word
comma
id|pci_conf0_write_config_dword
)brace
suffix:semicolon
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_ops
op_star
id|ops
op_assign
op_amp
id|bridge_pci_ops
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ioport_resource.end
op_assign
op_complement
l_int|0UL
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
id|num_bridges
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware on host bus %2d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|i
comma
id|ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
id|u8
DECL|function|bridge_swizzle
id|bridge_swizzle
c_func
(paren
id|u8
id|pin
comma
id|u8
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_plus
id|slot
)paren
op_mod
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_static
id|u8
id|__init
DECL|function|pci_swizzle
id|pci_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
id|u8
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
multiline_comment|/* Move up the chain of bridges. */
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * All observed requests have pin == 1. We could have a global here, that&n; * gets incremented and returned every time - unfortunately, pci_map_irq&n; * may be called on the same device over and over, and need to return the&n; * same value. On o2000, pin can be 0 or 1, and PCI slots can be [0..7]. &n; *&n; * A given PCI device, in general, should be able to intr any of the cpus&n; * on any one of the hubs connected to its xbow.&n; */
r_static
r_int
id|__init
DECL|function|pci_map_irq
id|pci_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev-&gt;bus-&gt;number
op_ge
id|MAX_PCI_BUSSES
)paren
op_logical_or
(paren
id|pin
op_ne
l_int|1
)paren
op_logical_or
"&bslash;"
(paren
id|slot
op_ge
id|MAX_DEVICES_PER_PCIBUS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Increase supported PCI busses %d,%d,%d&bslash;n&quot;
comma
"&bslash;"
id|dev-&gt;bus-&gt;number
comma
id|slot
comma
id|pin
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Already assigned? Then return previously assigned value ...&n;&t; */
r_if
c_cond
(paren
id|irqstore
(braket
id|dev-&gt;bus-&gt;number
)braket
(braket
id|slot
)braket
)paren
r_return
id|irqstore
(braket
id|dev-&gt;bus-&gt;number
)braket
(braket
id|slot
)braket
suffix:semicolon
r_else
(brace
id|lastirq
op_increment
suffix:semicolon
multiline_comment|/* IOC3_ETH_INT hack */
id|irq_to_bus
(braket
id|lastirq
)braket
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|irq_to_slot
(braket
id|lastirq
)braket
op_assign
id|slot
suffix:semicolon
r_return
id|irqstore
(braket
id|dev-&gt;bus-&gt;number
)braket
(braket
id|slot
)braket
op_assign
id|lastirq
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|pcibios_update_irq
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
id|pci_write_config_byte
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
r_void
id|__init
DECL|function|pcibios_update_resource
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resource
)paren
(brace
r_int
r_int
id|where
comma
id|size
suffix:semicolon
id|u32
id|reg
suffix:semicolon
id|where
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|resource
op_star
l_int|4
)paren
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|reg
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|reg
op_amp
id|size
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
(paren
id|res-&gt;start
op_minus
id|root-&gt;start
)paren
)paren
op_amp
op_complement
id|size
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|reg
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
id|pci_fixup_irqs
c_func
(paren
id|pci_swizzle
comma
id|pci_map_irq
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_pbus_ranges
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|ranges
)paren
(brace
id|ranges-&gt;io_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;io_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
)brace
r_int
id|__init
DECL|function|pcibios_enable_device
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Not needed, since we enable all devices at startup.  */
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_align_resource
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
)paren
(brace
)brace
r_char
op_star
id|__init
DECL|function|pcibios_setup
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* Nothing to do for now.  */
r_return
id|str
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pci_disable_swapping
id|pci_disable_swapping
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|bus_id
op_assign
(paren
r_int
)paren
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|bridge_t
op_star
id|bridge
op_assign
(paren
id|bridge_t
op_star
)paren
id|NODE_SWIN_BASE
c_func
(paren
id|bus_to_nid
(braket
id|bus_id
)braket
comma
id|bus_to_wid
(braket
id|bus_id
)braket
)paren
suffix:semicolon
r_int
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|bridgereg_t
id|devreg
suffix:semicolon
id|devreg
op_assign
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
suffix:semicolon
id|devreg
op_and_assign
op_complement
id|BRIDGE_DEV_SWAP_DIR
suffix:semicolon
multiline_comment|/* turn off byte swapping */
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
op_assign
id|devreg
suffix:semicolon
id|bridge-&gt;b_widget.w_tflush
suffix:semicolon
multiline_comment|/* Flush */
)brace
r_static
r_void
id|__init
DECL|function|pci_enable_swapping
id|pci_enable_swapping
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|bus_id
op_assign
(paren
r_int
)paren
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|bridge_t
op_star
id|bridge
op_assign
(paren
id|bridge_t
op_star
)paren
id|NODE_SWIN_BASE
c_func
(paren
id|bus_to_nid
(braket
id|bus_id
)braket
comma
id|bus_to_wid
(braket
id|bus_id
)braket
)paren
suffix:semicolon
r_int
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|bridgereg_t
id|devreg
suffix:semicolon
id|devreg
op_assign
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
suffix:semicolon
id|devreg
op_or_assign
id|BRIDGE_DEV_SWAP_DIR
suffix:semicolon
multiline_comment|/* turn on byte swapping */
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
op_assign
id|devreg
suffix:semicolon
id|bridge-&gt;b_widget.w_tflush
suffix:semicolon
multiline_comment|/* Flush */
)brace
r_static
r_void
id|__init
DECL|function|pci_fixup_ioc3
id|pci_fixup_ioc3
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
r_int
id|bus_id
op_assign
(paren
r_int
)paren
id|d-&gt;bus-&gt;number
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* IOC3 only decodes 0x20 bytes of the config space, so we end up&n;&t;   with tons of bogus information in the pci_dev.  On Origins the&n;&t;   INTA, INTB and INTC pins are all wired together as if it&squot;d only&n;&t;   use INTA.  */
id|printk
c_func
(paren
l_string|&quot;PCI: Fixing base addresses for IOC3 device %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_or_assign
id|NODE_OFFSET
c_func
(paren
id|bus_to_nid
(braket
id|bus_id
)braket
)paren
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_or_assign
id|NODE_OFFSET
c_func
(paren
id|bus_to_nid
(braket
id|bus_id
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
l_int|0UL
suffix:semicolon
id|d-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0UL
suffix:semicolon
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0UL
suffix:semicolon
)brace
id|d-&gt;subsystem_vendor
op_assign
l_int|0
suffix:semicolon
id|d-&gt;subsystem_device
op_assign
l_int|0
suffix:semicolon
id|d-&gt;irq
op_assign
l_int|1
suffix:semicolon
id|pci_disable_swapping
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pci_fixup_isp1020
id|pci_fixup_isp1020
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
r_int
id|command
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_or_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|bus_to_nid
(braket
id|d-&gt;bus-&gt;number
)braket
)paren
op_lshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Fixing isp1020 in [bus:slot.fn] %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* Configure device to allow bus mastering, i/o and memory mapping. &n;&t; * Older qlogicisp driver expects to have the IO space enable &n;&t; * bit set. Things stop working if we program the controllers as not &n;&t; * having PCI_COMMAND_MEMORY, so we have to fudge the mem_flags.&n;&t; */
id|pci_set_master
c_func
(paren
id|d
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|d
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
id|command
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
id|command
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|d
comma
id|PCI_COMMAND
comma
id|command
)paren
suffix:semicolon
id|d-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_or_assign
l_int|1
suffix:semicolon
id|pci_enable_swapping
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pci_fixup_isp2x00
id|pci_fixup_isp2x00
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
r_int
id|bus_id
op_assign
(paren
r_int
)paren
id|d-&gt;bus-&gt;number
suffix:semicolon
id|bridge_t
op_star
id|bridge
op_assign
(paren
id|bridge_t
op_star
)paren
id|NODE_SWIN_BASE
c_func
(paren
id|bus_to_nid
(braket
id|bus_id
)braket
comma
id|bus_to_wid
(braket
id|bus_id
)braket
)paren
suffix:semicolon
id|bridgereg_t
id|devreg
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|d-&gt;devfn
)paren
suffix:semicolon
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|command
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Fixing isp2x00 in [bus:slot.fn] %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* set the resource struct for this device */
id|start
op_assign
(paren
id|u32
)paren
(paren
id|u64
)paren
id|bridge
suffix:semicolon
multiline_comment|/* yes, we want to lose the upper 32 bits here */
id|start
op_or_assign
id|BRIDGE_DEVIO
c_func
(paren
id|slot
)paren
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
id|start
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
l_int|0xff
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|d-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
id|start
suffix:semicolon
id|d-&gt;resource
(braket
l_int|1
)braket
dot
id|end
op_assign
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
l_int|0xfff
suffix:semicolon
id|d-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
multiline_comment|/*&n;&t; * set the bridge device(x) reg for this device&n;&t; */
id|devreg
op_assign
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
suffix:semicolon
multiline_comment|/* point device(x) to it appropriate small window */
id|devreg
op_and_assign
op_complement
id|BRIDGE_DEV_OFF_MASK
suffix:semicolon
id|devreg
op_or_assign
(paren
id|start
op_rshift
l_int|20
)paren
op_amp
id|BRIDGE_DEV_OFF_MASK
suffix:semicolon
id|bridge-&gt;b_device
(braket
id|slot
)braket
dot
id|reg
op_assign
id|devreg
suffix:semicolon
id|pci_enable_swapping
c_func
(paren
id|d
)paren
suffix:semicolon
multiline_comment|/* set card&squot;s base addr reg */
singleline_comment|//pci_conf0_write_config_dword(d, PCI_BASE_ADDRESS_0, 0x500001);
singleline_comment|//pci_conf0_write_config_dword(d, PCI_BASE_ADDRESS_1, 0x8b00000);
singleline_comment|//pci_conf0_write_config_dword(d, PCI_ROM_ADDRESS, 0x8b20000);
multiline_comment|/* I got these from booting irix on system...*/
id|pci_conf0_write_config_dword
c_func
(paren
id|d
comma
id|PCI_BASE_ADDRESS_0
comma
l_int|0x200001
)paren
suffix:semicolon
singleline_comment|//pci_conf0_write_config_dword(d, PCI_BASE_ADDRESS_1, 0xf800000);
id|pci_conf0_write_config_dword
c_func
(paren
id|d
comma
id|PCI_ROM_ADDRESS
comma
l_int|0x10200000
)paren
suffix:semicolon
id|pci_conf0_write_config_dword
c_func
(paren
id|d
comma
id|PCI_BASE_ADDRESS_1
comma
id|start
)paren
suffix:semicolon
singleline_comment|//pci_conf0_write_config_dword(d, PCI_ROM_ADDRESS, (start | 0x20000));
multiline_comment|/* set cache line size */
id|pci_conf0_write_config_dword
c_func
(paren
id|d
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0xf080
)paren
suffix:semicolon
multiline_comment|/* set pci bus timeout */
id|bridge-&gt;b_bus_timeout
op_or_assign
id|BRIDGE_BUS_PCI_RETRY_HLD
c_func
(paren
l_int|0x3
)paren
suffix:semicolon
id|bridge-&gt;b_wid_tflush
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: bridge bus timeout= 0x%x &bslash;n&quot;
comma
id|bridge-&gt;b_bus_timeout
)paren
suffix:semicolon
multiline_comment|/* set host error field */
id|bridge-&gt;b_int_host_err
op_assign
l_int|0x44
suffix:semicolon
id|bridge-&gt;b_wid_tflush
suffix:semicolon
id|bridge-&gt;b_wid_tflush
suffix:semicolon
multiline_comment|/* wait until Bridge PIO complete */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: device(%d)= 0x%x&bslash;n&quot;
comma
id|i
comma
id|bridge-&gt;b_device
(braket
id|i
)braket
dot
id|reg
)paren
suffix:semicolon
multiline_comment|/* configure device to allow bus mastering, i/o and memory mapping */
id|pci_set_master
c_func
(paren
id|d
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|d
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
id|command
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
id|command
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|d
comma
id|PCI_COMMAND
comma
id|command
)paren
suffix:semicolon
multiline_comment|/*d-&gt;resource[1].flags |= 1;*/
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_SGI
comma
id|PCI_DEVICE_ID_SGI_IOC3
comma
id|pci_fixup_ioc3
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_QLOGIC
comma
id|PCI_DEVICE_ID_QLOGIC_ISP1020
comma
id|pci_fixup_isp1020
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_QLOGIC
comma
id|PCI_DEVICE_ID_QLOGIC_ISP2100
comma
id|pci_fixup_isp2x00
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_QLOGIC
comma
id|PCI_DEVICE_ID_QLOGIC_ISP2200
comma
id|pci_fixup_isp2x00
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
