multiline_comment|/*&n; *&t;Low-Level PCI Support for PC -- Routing of Interrupts&n; *&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@suse.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#include &quot;pci-i386.h&quot;
DECL|macro|PIRQ_SIGNATURE
mdefine_line|#define PIRQ_SIGNATURE&t;((&squot;$&squot; &lt;&lt; 0) + (&squot;P&squot; &lt;&lt; 8) + (&squot;I&squot; &lt;&lt; 16) + (&squot;R&squot; &lt;&lt; 24))
DECL|macro|PIRQ_VERSION
mdefine_line|#define PIRQ_VERSION 0x0100
DECL|variable|pirq_table
r_static
r_struct
id|irq_routing_table
op_star
id|pirq_table
suffix:semicolon
multiline_comment|/*&n; * Never use: 0, 1, 2 (timer, keyboard, and cascade)&n; * Avoid using: 13, 14 and 15 (FP error and IDE).&n; * Penalize: 3, 4, 6, 7, 12 (known ISA uses: serial, floppy, parallel and mouse)&n; */
DECL|variable|pcibios_irq_mask
r_int
r_int
id|pcibios_irq_mask
op_assign
l_int|0xfff8
suffix:semicolon
DECL|variable|pirq_penalty
r_static
r_int
id|pirq_penalty
(braket
l_int|16
)braket
op_assign
(brace
l_int|1000000
comma
l_int|1000000
comma
l_int|1000000
comma
l_int|1000
comma
l_int|1000
comma
l_int|0
comma
l_int|1000
comma
l_int|1000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1000
comma
l_int|100000
comma
l_int|100000
comma
l_int|100000
)brace
suffix:semicolon
DECL|struct|irq_router
r_struct
id|irq_router
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|vendor
DECL|member|device
id|u16
id|vendor
comma
id|device
suffix:semicolon
DECL|member|get
r_int
(paren
op_star
id|get
)paren
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
suffix:semicolon
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
r_new
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Search 0xf0000 -- 0xfffff for the PCI IRQ Routing Table.&n; */
DECL|function|pirq_find_routing_table
r_static
r_struct
id|irq_routing_table
op_star
id|__init
id|pirq_find_routing_table
c_func
(paren
r_void
)paren
(brace
id|u8
op_star
id|addr
suffix:semicolon
r_struct
id|irq_routing_table
op_star
id|rt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|sum
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
(paren
id|u8
op_star
)paren
id|__va
c_func
(paren
l_int|0xf0000
)paren
suffix:semicolon
id|addr
OL
(paren
id|u8
op_star
)paren
id|__va
c_func
(paren
l_int|0x100000
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|16
)paren
(brace
id|rt
op_assign
(paren
r_struct
id|irq_routing_table
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;signature
op_ne
id|PIRQ_SIGNATURE
op_logical_or
id|rt-&gt;version
op_ne
id|PIRQ_VERSION
op_logical_or
id|rt-&gt;size
op_mod
l_int|16
op_logical_or
id|rt-&gt;size
OL
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
r_continue
suffix:semicolon
id|sum
op_assign
l_int|0
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
id|rt-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sum
op_add_assign
id|addr
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sum
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Interrupt Routing Table found at 0x%p&bslash;n&quot;
comma
id|rt
)paren
suffix:semicolon
r_return
id|rt
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *  If we have a IRQ routing table, use it to search for peer host&n; *  bridges.  It&squot;s a gross hack, but since there are no other known&n; *  ways how to get a list of buses, we have to go this way.&n; */
DECL|function|pirq_peer_trick
r_static
r_void
id|__init
id|pirq_peer_trick
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
id|u8
id|busmap
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|irq_info
op_star
id|e
suffix:semicolon
id|memset
c_func
(paren
id|busmap
comma
l_int|0
comma
r_sizeof
(paren
id|busmap
)paren
)paren
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
(paren
id|rt-&gt;size
op_minus
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
op_div
r_sizeof
(paren
r_struct
id|irq_info
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e
op_assign
op_amp
id|rt-&gt;slots
(braket
id|i
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_int
id|j
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%02x:%02x slot=%02x&quot;
comma
id|e-&gt;bus
comma
id|e-&gt;devfn
op_div
l_int|8
comma
id|e-&gt;slot
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; %d:%02x/%04x&quot;
comma
id|j
comma
id|e-&gt;irq
(braket
id|j
)braket
dot
id|link
comma
id|e-&gt;irq
(braket
id|j
)braket
dot
id|bitmap
)paren
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|busmap
(braket
id|e-&gt;bus
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/*&n;&t;&t; *  It might be a secondary bus, but in this case its parent is already&n;&t;&t; *  known (ascending bus order) and therefore pci_scan_bus returns immediately.&n;&t;&t; */
r_if
c_cond
(paren
id|busmap
(braket
id|i
)braket
op_logical_and
id|pci_scan_bus
c_func
(paren
id|i
comma
id|pci_root_bus-&gt;ops
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: Discovered primary peer bus %02x [IRQ]&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  Code for querying and setting of IRQ routes on various interrupt routers.&n; */
DECL|function|eisa_set_level_irq
r_static
r_void
id|eisa_set_level_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_char
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|port
op_assign
l_int|0x4d0
op_plus
(paren
id|irq
op_rshift
l_int|3
)paren
suffix:semicolon
r_int
r_char
id|val
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|val
op_amp
id|mask
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; edge&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Common IRQ routing practice: nybbles in config space,&n; * offset by some magic constant.&n; */
DECL|function|read_config_nybble
r_static
r_int
r_int
id|read_config_nybble
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_int
id|offset
comma
r_int
id|nr
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|offset
op_plus
(paren
id|nr
op_rshift
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
r_return
(paren
id|nr
op_amp
l_int|1
)paren
ques
c_cond
(paren
id|x
op_rshift
l_int|4
)paren
suffix:colon
(paren
id|x
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
DECL|function|write_config_nybble
r_static
r_void
id|write_config_nybble
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_int
id|offset
comma
r_int
id|nr
comma
r_int
r_int
id|val
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|offset
op_plus
(paren
id|nr
op_rshift
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
id|x
op_assign
(paren
id|nr
op_amp
l_int|1
)paren
ques
c_cond
(paren
(paren
id|x
op_amp
l_int|0x0f
)paren
op_or
(paren
id|val
op_lshift
l_int|4
)paren
)paren
suffix:colon
(paren
(paren
id|x
op_amp
l_int|0xf0
)paren
op_or
id|val
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|router
comma
id|reg
comma
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ALI pirq entries are damn ugly, and completely undocumented.&n; * This has been figured out from pirq tables, and it&squot;s not a pretty&n; * picture.&n; */
DECL|function|pirq_ali_get
r_static
r_int
id|pirq_ali_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
r_static
r_int
r_char
id|irqmap
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|9
comma
l_int|3
comma
l_int|10
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|6
comma
l_int|1
comma
l_int|11
comma
l_int|0
comma
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|15
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_case
l_int|0x00
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
id|irqmap
(braket
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x48
comma
id|pirq
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_case
l_int|0xfe
suffix:colon
r_return
id|irqmap
(braket
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x44
comma
l_int|0
)paren
)braket
suffix:semicolon
r_case
l_int|0xff
suffix:colon
r_return
id|irqmap
(braket
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x75
comma
l_int|0
)paren
)braket
suffix:semicolon
)brace
)brace
DECL|function|pirq_ali_ide_interrupt
r_static
r_void
id|pirq_ali_ide_interrupt
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_int
id|reg
comma
r_int
id|val
comma
r_int
id|irq
)paren
(brace
id|u8
id|x
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
id|x
op_assign
(paren
id|x
op_amp
l_int|0xe0
)paren
op_or
id|val
suffix:semicolon
multiline_comment|/* clear the level-&gt;edge transform */
id|pci_write_config_byte
c_func
(paren
id|router
comma
id|reg
comma
id|x
)paren
suffix:semicolon
id|eisa_set_level_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|pirq_ali_set
r_static
r_int
id|pirq_ali_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
r_static
r_int
r_char
id|irqmap
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
comma
l_int|2
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|3
comma
l_int|9
comma
l_int|11
comma
l_int|0
comma
l_int|13
comma
l_int|15
)brace
suffix:semicolon
r_int
r_int
id|val
op_assign
id|irqmap
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_default
suffix:colon
id|write_config_nybble
c_func
(paren
id|router
comma
l_int|0x48
comma
id|pirq
op_minus
l_int|1
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xfe
suffix:colon
id|pirq_ali_ide_interrupt
c_func
(paren
id|router
comma
l_int|0x44
comma
id|val
comma
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
id|pirq_ali_ide_interrupt
c_func
(paren
id|router
comma
l_int|0x75
comma
id|val
comma
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|eisa_set_level_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The Intel PIIX4 pirq rules are fairly simple: &quot;pirq&quot; is&n; * just a pointer to the config space. However, something&n; * funny is going on with 0xfe/0xff, and apparently they&n; * should handle IDE irq routing. Ignore them for now.&n; */
DECL|function|pirq_piix_get
r_static
r_int
id|pirq_piix_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
id|u8
id|x
suffix:semicolon
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_case
l_int|0xfe
suffix:colon
r_case
l_int|0xff
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|pirq
comma
op_amp
id|x
)paren
suffix:semicolon
r_return
(paren
id|x
OL
l_int|16
)paren
ques
c_cond
id|x
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|pirq_piix_set
r_static
r_int
id|pirq_piix_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_case
l_int|0xfe
suffix:colon
r_case
l_int|0xff
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|pci_write_config_byte
c_func
(paren
id|router
comma
id|pirq
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The VIA pirq rules are nibble-based, like ALI,&n; * but without the ugly irq number munging or the&n; * strange special cases..&n; */
DECL|function|pirq_via_get
r_static
r_int
id|pirq_via_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
r_return
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x55
comma
id|pirq
)paren
suffix:semicolon
)brace
DECL|function|pirq_via_set
r_static
r_int
id|pirq_via_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
id|write_config_nybble
c_func
(paren
id|router
comma
l_int|0x55
comma
id|pirq
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * OPTI: high four bits are nibble pointer..&n; * I wonder what the low bits do?&n; */
DECL|function|pirq_opti_get
r_static
r_int
id|pirq_opti_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
r_return
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0xb8
comma
id|pirq
op_rshift
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|pirq_opti_set
r_static
r_int
id|pirq_opti_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
id|write_config_nybble
c_func
(paren
id|router
comma
l_int|0xb8
comma
id|pirq
op_rshift
l_int|4
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI_BIOS
DECL|function|pirq_bios_set
r_static
r_int
id|pirq_bios_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
suffix:semicolon
r_int
id|pin
op_assign
id|pci_get_interrupt_pin
c_func
(paren
id|dev
comma
op_amp
id|bridge
)paren
suffix:semicolon
r_return
id|pcibios_set_irq_routing
c_func
(paren
id|bridge
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|pirq_bios_router
r_static
r_struct
id|irq_router
id|pirq_bios_router
op_assign
(brace
l_string|&quot;BIOS&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|pirq_bios_set
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|pirq_routers
r_static
r_struct
id|irq_router
id|pirq_routers
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;PIIX&quot;
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371FB_0
comma
id|pirq_piix_get
comma
id|pirq_piix_set
)brace
comma
(brace
l_string|&quot;PIIX&quot;
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371SB_0
comma
id|pirq_piix_get
comma
id|pirq_piix_set
)brace
comma
(brace
l_string|&quot;PIIX&quot;
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_0
comma
id|pirq_piix_get
comma
id|pirq_piix_set
)brace
comma
(brace
l_string|&quot;PIIX&quot;
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443MX_0
comma
id|pirq_piix_get
comma
id|pirq_piix_set
)brace
comma
(brace
l_string|&quot;ALI&quot;
comma
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M1533
comma
id|pirq_ali_get
comma
id|pirq_ali_set
)brace
comma
(brace
l_string|&quot;VIA&quot;
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
id|pirq_via_get
comma
id|pirq_via_set
)brace
comma
(brace
l_string|&quot;VIA&quot;
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C596
comma
id|pirq_via_get
comma
id|pirq_via_set
)brace
comma
(brace
l_string|&quot;VIA&quot;
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
id|pirq_via_get
comma
id|pirq_via_set
)brace
comma
(brace
l_string|&quot;OPTI&quot;
comma
id|PCI_VENDOR_ID_OPTI
comma
id|PCI_DEVICE_ID_OPTI_82C700
comma
id|pirq_opti_get
comma
id|pirq_opti_set
)brace
comma
(brace
l_string|&quot;default&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|pirq_router
r_static
r_struct
id|irq_router
op_star
id|pirq_router
suffix:semicolon
DECL|variable|pirq_router_dev
r_static
r_struct
id|pci_dev
op_star
id|pirq_router_dev
suffix:semicolon
DECL|function|pirq_find_router
r_static
r_void
id|__init
id|pirq_find_router
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
id|u16
id|rvendor
comma
id|rdevice
suffix:semicolon
r_struct
id|irq_router
op_star
id|r
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_BIOS
r_if
c_cond
(paren
op_logical_neg
id|rt-&gt;signature
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Using BIOS for IRQ routing&bslash;n&quot;
)paren
suffix:semicolon
id|pirq_router
op_assign
op_amp
id|pirq_bios_router
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|pirq_router_dev
op_assign
id|pci_find_slot
c_func
(paren
id|rt-&gt;rtr_bus
comma
id|rt-&gt;rtr_devfn
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Interrupt router not found at %02x:%02x&bslash;n&quot;
comma
id|rt-&gt;rtr_bus
comma
id|rt-&gt;rtr_devfn
)paren
suffix:semicolon
multiline_comment|/* fall back to default router */
id|pirq_router
op_assign
id|pirq_routers
op_plus
r_sizeof
(paren
id|pirq_routers
)paren
op_div
r_sizeof
(paren
id|pirq_routers
(braket
l_int|0
)braket
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rt-&gt;rtr_vendor
)paren
(brace
id|rvendor
op_assign
id|rt-&gt;rtr_vendor
suffix:semicolon
id|rdevice
op_assign
id|rt-&gt;rtr_device
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Several BIOSes forget to set the router type. In such cases, we&n;&t;&t; * use chip vendor/device. This doesn&squot;t guarantee us semantics of&n;&t;&t; * PIRQ values, but was found to work in practice and it&squot;s still&n;&t;&t; * better than not trying.&n;&t;&t; */
id|DBG
c_func
(paren
l_string|&quot;PCI: Guessed interrupt router ID from %s&bslash;n&quot;
comma
id|pirq_router_dev-&gt;slot_name
)paren
suffix:semicolon
id|rvendor
op_assign
id|pirq_router_dev-&gt;vendor
suffix:semicolon
id|rdevice
op_assign
id|pirq_router_dev-&gt;device
suffix:semicolon
)brace
r_for
c_loop
(paren
id|r
op_assign
id|pirq_routers
suffix:semicolon
id|r-&gt;vendor
suffix:semicolon
id|r
op_increment
)paren
r_if
c_cond
(paren
id|r-&gt;vendor
op_eq
id|rvendor
op_logical_and
id|r-&gt;device
op_eq
id|rdevice
)paren
r_break
suffix:semicolon
id|pirq_router
op_assign
id|r
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Using IRQ router %s [%04x/%04x] at %s&bslash;n&quot;
comma
id|r-&gt;name
comma
id|rvendor
comma
id|rdevice
comma
id|pirq_router_dev-&gt;slot_name
)paren
suffix:semicolon
)brace
DECL|function|pirq_get_info
r_static
r_struct
id|irq_info
op_star
id|pirq_get_info
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pin
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
r_int
id|entries
op_assign
(paren
id|rt-&gt;size
op_minus
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
op_div
r_sizeof
(paren
r_struct
id|irq_info
)paren
suffix:semicolon
r_struct
id|irq_info
op_star
id|info
suffix:semicolon
r_for
c_loop
(paren
id|info
op_assign
id|rt-&gt;slots
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
id|info
op_increment
)paren
r_if
c_cond
(paren
id|info-&gt;bus
op_eq
id|dev-&gt;bus-&gt;number
op_logical_and
id|PCI_SLOT
c_func
(paren
id|info-&gt;devfn
)paren
op_eq
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
r_return
id|info
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pcibios_test_irq_handler
r_static
r_void
id|pcibios_test_irq_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
DECL|function|pcibios_lookup_irq
r_static
r_int
id|pcibios_lookup_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|assign
)paren
(brace
r_struct
id|irq_info
op_star
id|info
suffix:semicolon
r_int
id|i
comma
id|pirq
comma
id|pin
comma
id|newirq
suffix:semicolon
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
id|u32
id|mask
suffix:semicolon
r_struct
id|irq_router
op_star
id|r
op_assign
id|pirq_router
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev2
comma
op_star
id|d
suffix:semicolon
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pirq_table
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Find IRQ routing entry */
id|pin
op_assign
id|pci_get_interrupt_pin
c_func
(paren
id|dev
comma
op_amp
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
l_int|0
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; no interrupt pin&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;IRQ for %s(%d) via %s&quot;
comma
id|dev-&gt;slot_name
comma
id|pin
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|info
op_assign
id|pirq_get_info
c_func
(paren
id|d
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; not found in routing table&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pirq
op_assign
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|link
suffix:semicolon
id|mask
op_assign
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|bitmap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pirq
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; not routed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; PIRQ %02x, mask %04x, excl %04x&quot;
comma
id|pirq
comma
id|mask
comma
id|pirq_table-&gt;exclusive_irqs
)paren
suffix:semicolon
id|mask
op_and_assign
id|pcibios_irq_mask
suffix:semicolon
multiline_comment|/* Find the best IRQ to assign */
id|newirq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|assign
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pirq_penalty
(braket
id|i
)braket
OL
id|pirq_penalty
(braket
id|newirq
)braket
op_logical_and
op_logical_neg
id|request_irq
c_func
(paren
id|i
comma
id|pcibios_test_irq_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;pci-test&quot;
comma
id|dev
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|i
comma
id|dev
)paren
suffix:semicolon
id|newirq
op_assign
id|i
suffix:semicolon
)brace
)brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; newirq=%d&quot;
comma
id|newirq
)paren
suffix:semicolon
)brace
multiline_comment|/* Try to get current IRQ */
r_if
c_cond
(paren
id|r-&gt;get
op_logical_and
(paren
id|irq
op_assign
id|r
op_member_access_from_pointer
id|get
c_func
(paren
id|pirq_router_dev
comma
id|d
comma
id|pirq
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; got IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|msg
op_assign
l_string|&quot;Found&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|newirq
op_logical_and
id|r-&gt;set
op_logical_and
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_DISPLAY_VGA
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; assigning IRQ %d&quot;
comma
id|newirq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_member_access_from_pointer
id|set
c_func
(paren
id|pirq_router_dev
comma
id|d
comma
id|pirq
comma
id|newirq
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; ... OK&bslash;n&quot;
)paren
suffix:semicolon
id|msg
op_assign
l_string|&quot;Assigned&quot;
suffix:semicolon
id|irq
op_assign
id|newirq
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; ... failed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newirq
op_logical_and
id|mask
op_eq
(paren
l_int|1
op_lshift
id|newirq
)paren
)paren
(brace
id|msg
op_assign
l_string|&quot;Guessed&quot;
suffix:semicolon
id|irq
op_assign
id|newirq
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: %s IRQ %d for device %s&bslash;n&quot;
comma
id|msg
comma
id|irq
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* Update IRQ for all devices with the same pirq value */
id|pci_for_each_dev
c_func
(paren
id|dev2
)paren
(brace
r_if
c_cond
(paren
(paren
id|pin
op_assign
id|pci_get_interrupt_pin
c_func
(paren
id|dev2
comma
op_amp
id|d
)paren
)paren
op_ge
l_int|0
op_logical_and
(paren
id|info
op_assign
id|pirq_get_info
c_func
(paren
id|d
comma
id|pin
)paren
)paren
op_logical_and
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|link
op_eq
id|pirq
)paren
(brace
id|dev2-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pirq_penalty
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ne
id|dev2
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: The same IRQ used for device %s&bslash;n&quot;
comma
id|dev2-&gt;slot_name
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_irq_init
r_void
id|__init
id|pcibios_irq_init
c_func
(paren
r_void
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: IRQ init&bslash;n&quot;
)paren
suffix:semicolon
id|pirq_table
op_assign
id|pirq_find_routing_table
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_BIOS
r_if
c_cond
(paren
op_logical_neg
id|pirq_table
op_logical_and
(paren
id|pci_probe
op_amp
id|PCI_BIOS_IRQ_SCAN
)paren
)paren
id|pirq_table
op_assign
id|pcibios_get_irq_routing_table
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pirq_table
)paren
(brace
id|pirq_peer_trick
c_func
(paren
)paren
suffix:semicolon
id|pirq_find_router
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pirq_table-&gt;exclusive_irqs
)paren
(brace
r_int
id|i
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|pirq_table-&gt;exclusive_irqs
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|pirq_penalty
(braket
id|i
)braket
op_add_assign
l_int|100
suffix:semicolon
)brace
multiline_comment|/* If we&squot;re using the I/O APIC, avoid using the PCI IRQ routing table */
r_if
c_cond
(paren
id|io_apic_assign_pci_irqs
)paren
id|pirq_table
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|pcibios_fixup_irqs
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
id|u8
id|pin
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: IRQ fixup&bslash;n&quot;
)paren
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the BIOS has set an out of range IRQ number, just ignore it.&n;&t;&t; * Also keep track of which IRQ&squot;s are already in use.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|16
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%s: ignoring bogus IRQ %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If the IRQ is already assigned to a PCI device, ignore its ISA use penalty */
r_if
c_cond
(paren
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_ge
l_int|100
op_logical_and
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
OL
l_int|100000
)paren
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_increment
suffix:semicolon
)brace
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
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
suffix:semicolon
macro_line|#ifdef CONFIG_X86_IO_APIC
multiline_comment|/*&n;&t;&t; * Recalculate IRQ numbers if we use the I/O APIC.&n;&t;&t; */
r_if
c_cond
(paren
id|io_apic_assign_pci_irqs
)paren
(brace
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|pin
)paren
(brace
id|pin
op_decrement
suffix:semicolon
multiline_comment|/* interrupt pins are numbered starting from 1 */
id|irq
op_assign
id|IO_APIC_get_PCI_irq_vector
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|pin
)paren
suffix:semicolon
multiline_comment|/*&n; * Will be removed completely if things work out well with fuzzy parsing&n; */
macro_line|#if 0
r_if
c_cond
(paren
id|irq
OL
l_int|0
op_logical_and
id|dev-&gt;bus-&gt;parent
)paren
(brace
multiline_comment|/* go back to the bridge */
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
id|pin
op_assign
(paren
id|pin
op_plus
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
id|irq
op_assign
id|IO_APIC_get_PCI_irq_vector
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|bridge-&gt;devfn
)paren
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: using PPB(B%d,I%d,P%d) to get irq %d&bslash;n&quot;
comma
id|bridge-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|bridge-&gt;devfn
)paren
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI-&gt;APIC IRQ transform: (B%d,I%d,P%d) -&gt; %d&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Still no IRQ? Try to lookup one...&n;&t;&t; */
r_if
c_cond
(paren
id|pin
op_logical_and
op_logical_neg
id|dev-&gt;irq
)paren
id|pcibios_lookup_irq
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_penalize_isa_irq
r_void
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; *  If any ISAPnP device reports an IRQ in its list of possible&n;&t; *  IRQ&squot;s, we try to avoid assigning it to PCI devices.&n;&t; */
id|pirq_penalty
(braket
id|irq
)braket
op_add_assign
l_int|100
suffix:semicolon
)brace
DECL|function|pcibios_enable_irq
r_void
id|pcibios_enable_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|u8
id|pin
suffix:semicolon
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
suffix:semicolon
r_if
c_cond
(paren
id|pin
op_logical_and
op_logical_neg
id|pcibios_lookup_irq
c_func
(paren
id|dev
comma
l_int|1
)paren
)paren
(brace
r_char
op_star
id|msg
suffix:semicolon
r_if
c_cond
(paren
id|io_apic_assign_pci_irqs
)paren
id|msg
op_assign
l_string|&quot; Probably buggy MP table.&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_BIOS_IRQ_SCAN
)paren
id|msg
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_else
id|msg
op_assign
l_string|&quot; Please try using pci=biosirq.&quot;
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: No IRQ known for interrupt pin %c of device %s.%s&bslash;n&quot;
comma
l_char|&squot;A&squot;
op_plus
id|pin
op_minus
l_int|1
comma
id|dev-&gt;slot_name
comma
id|msg
)paren
suffix:semicolon
)brace
)brace
)brace
eof
