multiline_comment|/*&n; * $Id: pci.c,v 1.27 1998/04/24 02:46:47 cort Exp $&n; * Common pmac/prep/chrp pci routines. -- Cort&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if !defined(CONFIG_MACH_SPECIFIC) || defined(CONFIG_PMAC)
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
suffix:semicolon
macro_line|#endif /* CONFIG_MACH_SPECIFIC || CONFIG_PMAC */
macro_line|#if !defined(CONFIG_MACH_SPECIFIC)
DECL|variable|isa_mem_base
r_int
r_int
id|isa_mem_base
suffix:semicolon
DECL|variable|pci_dram_offset
r_int
r_int
id|pci_dram_offset
suffix:semicolon
macro_line|#endif /* CONFIG_MACH_SPECIFIC */
multiline_comment|/*&n; * It would be nice if we could create a include/asm/pci.h and have just&n; * function ptrs for all these in there, but that isn&squot;t the case.&n; * We have a function, pcibios_*() which calls the function ptr ptr_pcibios_*()&n; * which has been setup by pcibios_init().  This is all to avoid a check&n; * for pmac/prep every time we call one of these.  It should also make the move&n; * to a include/asm/pcibios.h easier, we can drop the ptr_ on these functions&n; * and create pci.h&n; *   -- Cort&n; */
DECL|variable|ptr_pcibios_read_config_byte
r_int
(paren
op_star
id|ptr_pcibios_read_config_byte
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
DECL|variable|ptr_pcibios_read_config_word
r_int
(paren
op_star
id|ptr_pcibios_read_config_word
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
DECL|variable|ptr_pcibios_read_config_dword
r_int
(paren
op_star
id|ptr_pcibios_read_config_dword
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
DECL|variable|ptr_pcibios_write_config_byte
r_int
(paren
op_star
id|ptr_pcibios_write_config_byte
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|variable|ptr_pcibios_write_config_word
r_int
(paren
op_star
id|ptr_pcibios_write_config_word
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|variable|ptr_pcibios_write_config_dword
r_int
(paren
op_star
id|ptr_pcibios_write_config_dword
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|chrp_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|prep_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|mbx_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|pcibios_read_config_byte
r_int
id|pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
(brace
r_return
id|ptr_pcibios_read_config_byte
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_read_config_word
r_int
id|pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_return
id|ptr_pcibios_read_config_word
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_read_config_dword
r_int
id|pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_return
id|ptr_pcibios_read_config_dword
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_write_config_byte
r_int
id|pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
(brace
r_return
id|ptr_pcibios_write_config_byte
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_write_config_word
r_int
id|pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_return
id|ptr_pcibios_write_config_word
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_write_config_dword
r_int
id|pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_return
id|ptr_pcibios_write_config_dword
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcibios_present
r_int
id|pcibios_present
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|pcibios_init
c_func
(paren
r_void
)paren
)paren
(brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|setup_pci_ptrs
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#ifndef CONFIG_MBX  
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_prep
suffix:colon
id|ptr_pcibios_read_config_byte
op_assign
id|prep_pcibios_read_config_byte
suffix:semicolon
id|ptr_pcibios_read_config_word
op_assign
id|prep_pcibios_read_config_word
suffix:semicolon
id|ptr_pcibios_read_config_dword
op_assign
id|prep_pcibios_read_config_dword
suffix:semicolon
id|ptr_pcibios_write_config_byte
op_assign
id|prep_pcibios_write_config_byte
suffix:semicolon
id|ptr_pcibios_write_config_word
op_assign
id|prep_pcibios_write_config_word
suffix:semicolon
id|ptr_pcibios_write_config_dword
op_assign
id|prep_pcibios_write_config_dword
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_Pmac
suffix:colon
id|ptr_pcibios_read_config_byte
op_assign
id|pmac_pcibios_read_config_byte
suffix:semicolon
id|ptr_pcibios_read_config_word
op_assign
id|pmac_pcibios_read_config_word
suffix:semicolon
id|ptr_pcibios_read_config_dword
op_assign
id|pmac_pcibios_read_config_dword
suffix:semicolon
id|ptr_pcibios_write_config_byte
op_assign
id|pmac_pcibios_write_config_byte
suffix:semicolon
id|ptr_pcibios_write_config_word
op_assign
id|pmac_pcibios_write_config_word
suffix:semicolon
id|ptr_pcibios_write_config_dword
op_assign
id|pmac_pcibios_write_config_dword
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
id|ptr_pcibios_read_config_byte
op_assign
id|chrp_pcibios_read_config_byte
suffix:semicolon
id|ptr_pcibios_read_config_word
op_assign
id|chrp_pcibios_read_config_word
suffix:semicolon
id|ptr_pcibios_read_config_dword
op_assign
id|chrp_pcibios_read_config_dword
suffix:semicolon
id|ptr_pcibios_write_config_byte
op_assign
id|chrp_pcibios_write_config_byte
suffix:semicolon
id|ptr_pcibios_write_config_word
op_assign
id|chrp_pcibios_write_config_word
suffix:semicolon
id|ptr_pcibios_write_config_dword
op_assign
id|chrp_pcibios_write_config_dword
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;setup_pci_ptrs(): unknown machine type!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else  /* CONFIG_MBX */&t;
id|ptr_pcibios_read_config_byte
op_assign
id|mbx_pcibios_read_config_byte
suffix:semicolon
id|ptr_pcibios_read_config_word
op_assign
id|mbx_pcibios_read_config_word
suffix:semicolon
id|ptr_pcibios_read_config_dword
op_assign
id|mbx_pcibios_read_config_dword
suffix:semicolon
id|ptr_pcibios_write_config_byte
op_assign
id|mbx_pcibios_write_config_byte
suffix:semicolon
id|ptr_pcibios_write_config_word
op_assign
id|mbx_pcibios_write_config_word
suffix:semicolon
id|ptr_pcibios_write_config_dword
op_assign
id|mbx_pcibios_write_config_dword
suffix:semicolon
macro_line|#endif /* CONFIG_MBX */&t;
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|pcibios_fixup
c_func
(paren
r_void
)paren
)paren
(brace
r_extern
id|route_pci_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_extern
r_struct
id|bridge_data
op_star
op_star
id|bridges
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_map
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_routes
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: This is broken: We should not assign IRQ&squot;s to IRQless&n;&t; *&t;  devices (look at PCI_INTERRUPT_PIN) and we also should&n;&t; *&t;  honor the existence of multi-function devices where&n;&t; *&t;  different functions have different interrupt pins. [mj]&n;&t; */
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_prep
suffix:colon
id|route_pci_interrupts
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_int
r_char
id|d
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|Motherboard_routes
(braket
id|Motherboard_map
(braket
id|d
)braket
)braket
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
multiline_comment|/* PCI interrupts are controlled by the OpenPIC */
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|dev-&gt;irq
op_assign
id|openpic_to_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_Pmac
suffix:colon
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Open Firmware often doesn&squot;t initialize the,&n;&t;&t;&t; * PCI_INTERRUPT_LINE config register properly, so we&n;&t;&t;&t; * should find the device node and se if it has an&n;&t;&t;&t; * AAPL,interrupts property.&n;&t;&t;&t; */
r_struct
id|bridge_data
op_star
id|bp
op_assign
id|bridges
(braket
id|dev-&gt;bus-&gt;number
)braket
suffix:semicolon
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
r_int
op_star
id|reg
suffix:semicolon
r_int
r_char
id|pin
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
op_logical_or
op_logical_neg
id|pin
)paren
r_continue
suffix:semicolon
multiline_comment|/* No interrupt generated -&gt; no fixup */
r_for
c_loop
(paren
id|node
op_assign
id|bp-&gt;node-&gt;child
suffix:semicolon
id|node
op_ne
l_int|0
suffix:semicolon
id|node
op_assign
id|node-&gt;sibling
)paren
(brace
id|reg
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|0
op_logical_or
(paren
(paren
id|reg
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_ne
id|dev-&gt;devfn
)paren
r_continue
suffix:semicolon
multiline_comment|/* this is the node, see if it has interrupts */
r_if
c_cond
(paren
id|node-&gt;n_intrs
OG
l_int|0
)paren
id|dev-&gt;irq
op_assign
id|node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
)paren
(brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_char
op_star
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
eof
