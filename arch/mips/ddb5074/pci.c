multiline_comment|/*&n; *  arch/mips/ddb5074/pci.c -- NEC DDB Vrc-5074 PCI access routines&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Albert Dorofeev &lt;albert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; *&n; *  $Id: pci.c,v 1.4 2000/02/18 00:02:17 ralf Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm-mips/nile4.h&gt;
DECL|function|nile4_pre_pci_access0
r_static
id|u32
id|nile4_pre_pci_access0
c_func
(paren
r_int
id|slot_num
)paren
(brace
id|u32
id|pci_addr
op_assign
l_int|0
suffix:semicolon
id|u32
id|virt_addr
op_assign
id|NILE4_PCI_CFG_BASE
suffix:semicolon
multiline_comment|/* Set window 1 address 8000000 - 64 bit - 2 MB (PCI config space) */
id|nile4_set_pdar
c_func
(paren
id|NILE4_PCIW1
comma
id|PHYSADDR
c_func
(paren
id|virt_addr
)paren
comma
l_int|0x00200000
comma
l_int|64
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot_num
OG
l_int|2
)paren
id|pci_addr
op_assign
l_int|0x00040000
op_lshift
id|slot_num
suffix:semicolon
r_else
id|virt_addr
op_add_assign
l_int|0x00040000
op_lshift
id|slot_num
suffix:semicolon
id|nile4_set_pmr
c_func
(paren
id|NILE4_PCIINIT1
comma
id|NILE4_PCICMD_CFG
comma
id|pci_addr
)paren
suffix:semicolon
r_return
id|virt_addr
suffix:semicolon
)brace
DECL|function|nile4_post_pci_access0
r_static
r_void
id|nile4_post_pci_access0
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Set window 1 back to address 8000000 - 64 bit - 128 MB (PCI IO space) */
id|nile4_set_pdar
c_func
(paren
id|NILE4_PCIW1
comma
id|PHYSADDR
c_func
(paren
id|NILE4_PCI_MEM_BASE
)paren
comma
l_int|0x08000000
comma
l_int|64
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|nile4_set_pmr
c_func
(paren
id|NILE4_PCIINIT1
comma
id|NILE4_PCICMD_MEM
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nile4_pci_read_config_dword
r_static
r_int
id|nile4_pci_read_config_dword
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
id|val
)paren
(brace
r_int
id|slot_num
comma
id|func_num
suffix:semicolon
id|u32
id|base
suffix:semicolon
multiline_comment|/*&n;     *  For starters let&squot;s do configuration cycle 0 only (one bus only)&n;     */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
)paren
r_return
id|PCIBIOS_FUNC_NOT_SUPPORTED
suffix:semicolon
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|func_num
op_assign
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot_num
op_eq
l_int|5
)paren
(brace
multiline_comment|/*&n;&t; *  This is Nile 4 and it will crash if we access it like other&n;&t; *   devices&n;&t; */
op_star
id|val
op_assign
id|nile4_in32
c_func
(paren
id|NILE4_PCI_BASE
op_plus
id|where
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|base
op_assign
id|nile4_pre_pci_access0
c_func
(paren
id|slot_num
)paren
suffix:semicolon
op_star
id|val
op_assign
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|base
op_plus
(paren
id|func_num
op_lshift
l_int|8
)paren
op_plus
(paren
id|where
op_amp
l_int|0xfc
)paren
)paren
)paren
suffix:semicolon
id|nile4_post_pci_access0
c_func
(paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|nile4_pci_write_config_dword
r_static
r_int
id|nile4_pci_write_config_dword
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
id|val
)paren
(brace
r_int
id|slot_num
comma
id|func_num
suffix:semicolon
id|u32
id|base
suffix:semicolon
multiline_comment|/*&n;     *  For starters let&squot;s do configuration cycle 0 only (one bus only)&n;     */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
)paren
r_return
id|PCIBIOS_FUNC_NOT_SUPPORTED
suffix:semicolon
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|func_num
op_assign
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot_num
op_eq
l_int|5
)paren
(brace
multiline_comment|/*&n;&t; *  This is Nile 4 and it will crash if we access it like other&n;&t; *   devices&n;&t; */
id|nile4_out32
c_func
(paren
id|NILE4_PCI_BASE
op_plus
id|where
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|base
op_assign
id|nile4_pre_pci_access0
c_func
(paren
id|slot_num
)paren
suffix:semicolon
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|base
op_plus
(paren
id|func_num
op_lshift
l_int|8
)paren
op_plus
(paren
id|where
op_amp
l_int|0xfc
)paren
)paren
)paren
op_assign
id|val
suffix:semicolon
id|nile4_post_pci_access0
c_func
(paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|nile4_pci_read_config_word
r_static
r_int
id|nile4_pci_read_config_word
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
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
id|u32
id|result
suffix:semicolon
id|status
op_assign
id|nile4_pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|result
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
id|result
op_amp
l_int|0xffff
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|nile4_pci_read_config_byte
r_static
r_int
id|nile4_pci_read_config_byte
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
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
id|u32
id|result
suffix:semicolon
id|status
op_assign
id|nile4_pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
id|result
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|result
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
id|result
op_amp
l_int|0xff
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|nile4_pci_write_config_word
r_static
r_int
id|nile4_pci_write_config_word
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
id|val
)paren
(brace
r_int
id|status
comma
id|shift
op_assign
l_int|0
suffix:semicolon
id|u32
id|result
suffix:semicolon
id|status
op_assign
id|nile4_pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|shift
op_add_assign
l_int|16
suffix:semicolon
id|result
op_and_assign
op_complement
(paren
l_int|0xffff
op_lshift
id|shift
)paren
suffix:semicolon
id|result
op_or_assign
id|val
op_lshift
id|shift
suffix:semicolon
r_return
id|nile4_pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|nile4_pci_write_config_byte
r_static
r_int
id|nile4_pci_write_config_byte
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
id|val
)paren
(brace
r_int
id|status
comma
id|shift
op_assign
l_int|0
suffix:semicolon
id|u32
id|result
suffix:semicolon
id|status
op_assign
id|nile4_pci_read_config_dword
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|shift
op_add_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
id|shift
op_add_assign
l_int|8
suffix:semicolon
id|result
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|shift
)paren
suffix:semicolon
id|result
op_or_assign
id|val
op_lshift
id|shift
suffix:semicolon
r_return
id|nile4_pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|result
)paren
suffix:semicolon
)brace
DECL|variable|nile4_pci_ops
r_struct
id|pci_ops
id|nile4_pci_ops
op_assign
(brace
id|nile4_pci_read_config_byte
comma
id|nile4_pci_read_config_word
comma
id|nile4_pci_read_config_dword
comma
id|nile4_pci_write_config_byte
comma
id|nile4_pci_write_config_word
comma
id|nile4_pci_write_config_dword
)brace
suffix:semicolon
r_struct
(brace
DECL|member|ram
r_struct
id|resource
id|ram
suffix:semicolon
DECL|member|flash
r_struct
id|resource
id|flash
suffix:semicolon
DECL|member|isa_io
r_struct
id|resource
id|isa_io
suffix:semicolon
DECL|member|pci_io
r_struct
id|resource
id|pci_io
suffix:semicolon
DECL|member|isa_mem
r_struct
id|resource
id|isa_mem
suffix:semicolon
DECL|member|pci_mem
r_struct
id|resource
id|pci_mem
suffix:semicolon
DECL|member|nile4
r_struct
id|resource
id|nile4
suffix:semicolon
DECL|member|boot
r_struct
id|resource
id|boot
suffix:semicolon
DECL|variable|ddb5074_resources
)brace
id|ddb5074_resources
op_assign
(brace
(brace
l_string|&quot;RAM&quot;
comma
l_int|0x00000000
comma
l_int|0x03ffffff
comma
id|IORESOURCE_MEM
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)brace
comma
(brace
l_string|&quot;Flash ROM&quot;
comma
l_int|0x04000000
comma
l_int|0x043fffff
)brace
comma
(brace
l_string|&quot;Nile4 ISA I/O&quot;
comma
l_int|0x06000000
comma
l_int|0x060fffff
)brace
comma
(brace
l_string|&quot;Nile4 PCI I/O&quot;
comma
l_int|0x06100000
comma
l_int|0x07ffffff
)brace
comma
(brace
l_string|&quot;Nile4 ISA mem&quot;
comma
l_int|0x08000000
comma
l_int|0x08ffffff
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Nile4 PCI mem&quot;
comma
l_int|0x09000000
comma
l_int|0x0fffffff
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Nile4 ctrl&quot;
comma
l_int|0x1fa00000
comma
l_int|0x1fbfffff
comma
id|IORESOURCE_MEM
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)brace
comma
(brace
l_string|&quot;Boot ROM&quot;
comma
l_int|0x1fc00000
comma
l_int|0x1fffffff
)brace
)brace
suffix:semicolon
DECL|function|ddb5074_pci_fixup
r_static
r_void
id|__init
id|ddb5074_pci_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NEC
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_NEC_NILE4
)paren
(brace
multiline_comment|/*&n;&t;     *  The first 64-bit PCI base register should point to the Nile4&n;&t;     *  control registers. Unfortunately this isn&squot;t the case, so we fix&n;&t;     *  it ourselves. This allows the serial driver to find the UART.&n;&t;     */
id|dev-&gt;resource
(braket
l_int|0
)braket
op_assign
id|ddb5074_resources.nile4
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|dev-&gt;resource
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;     *  The second 64-bit PCI base register points to the first memory&n;&t;     *  bank. Unfortunately the address is wrong, so we fix it (again).&n;&t;     */
id|dev-&gt;resource
(braket
l_int|2
)braket
op_assign
id|ddb5074_resources.ram
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|dev-&gt;resource
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AL
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M7101
)paren
(brace
multiline_comment|/*&n;&t;     *  It&squot;s nice to have the LEDs on the GPIO pins available for&n;&t;     *  debugging&n;&t;     */
r_extern
r_struct
id|pci_dev
op_star
id|pci_pmu
suffix:semicolon
id|u8
id|t8
suffix:semicolon
id|pci_pmu
op_assign
id|dev
suffix:semicolon
multiline_comment|/* for LEDs D2 and D3 */
multiline_comment|/* Program the lines for LEDs D2 and D3 to output */
id|nile4_pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x7d
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|nile4_pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x7d
comma
id|t8
)paren
suffix:semicolon
multiline_comment|/* Turn LEDs D2 and D3 off */
id|nile4_pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x7e
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|nile4_pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x7e
comma
id|t8
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|pcibios_fixup_irqs
r_static
r_void
id|__init
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|slot_num
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot_num
)paren
(brace
r_case
l_int|0
suffix:colon
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* slot 1 */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* slot 2 */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTB
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* slot 3 */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTC
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/*&n;&t;&t; * Fixup so the serial driver can use the UART&n;&t;&t; */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_UART
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0x1ffffff
suffix:semicolon
multiline_comment|/*  32 MB */
id|iomem_resource.end
op_assign
l_int|0x1fffffff
suffix:semicolon
multiline_comment|/* 512 MB */
multiline_comment|/* `ram&squot; and `nile4&squot; are requested through the Nile4 pci_dev */
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.flash
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.isa_io
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.pci_io
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.isa_mem
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.pci_mem
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5074_resources.boot
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|nile4_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
id|ddb5074_pci_fixup
c_func
(paren
)paren
suffix:semicolon
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
id|bus-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|ddb5074_resources.pci_mem
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|pcibios_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
DECL|function|pcibios_update_irq
r_void
id|__init
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
DECL|function|pcibios_fixup_pbus_ranges
r_void
id|__init
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
DECL|function|pcibios_enable_resources
r_int
id|pcibios_enable_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|cmd
comma
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
multiline_comment|/*&n;&t; *  Don&squot;t touch the Nile 4&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NEC
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_NEC_NILE4
)paren
r_return
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|old_cmd
op_assign
id|cmd
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because of resource collisions&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
id|pcibios_enable_resources
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|pcibios_update_resource
r_void
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
id|u32
r_new
comma
id|check
suffix:semicolon
r_int
id|reg
suffix:semicolon
r_new
op_assign
id|res-&gt;start
op_or
(paren
id|res-&gt;flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource
OL
l_int|6
)paren
(brace
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
l_int|4
op_star
id|resource
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resource
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|res-&gt;flags
op_or_assign
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Somebody might have asked allocation of a non-standard resource */
r_return
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
r_new
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_new
op_xor
id|check
)paren
op_amp
(paren
(paren
r_new
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
ques
c_cond
id|PCI_BASE_ADDRESS_IO_MASK
suffix:colon
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error while updating region &quot;
l_string|&quot;%s/%d (%08x != %08x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|resource
comma
r_new
comma
id|check
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_align_resource
r_void
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
multiline_comment|/* We need to avoid collisions with `mirrored&squot; VGA ports&n;&t;&t;   and other strange ISA hardware, so we always want the&n;&t;&t;   addresses kilobyte aligned.  */
r_if
c_cond
(paren
id|size
OG
l_int|0x100
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: I/O Region %s/%d too large&quot;
l_string|&quot; (%ld bytes)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;resource
op_minus
id|res
comma
id|size
)paren
suffix:semicolon
)brace
id|start
op_assign
(paren
id|start
op_plus
l_int|1024
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
l_int|1024
op_minus
l_int|1
)paren
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
eof
