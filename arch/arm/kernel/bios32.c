multiline_comment|/*&n; * arch/arm/kernel/bios32.c&n; *&n; * PCI bios-type initialisation for PCI machines&n; *&n; * Bits taken from various places.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;bios32.h&quot;
DECL|variable|debug_pci
r_static
r_int
id|debug_pci
suffix:semicolon
DECL|variable|have_isa_bridge
r_int
id|have_isa_bridge
suffix:semicolon
r_extern
r_void
id|hw_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|pcibios_report_device_errors
r_void
id|pcibios_report_device_errors
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
id|u16
id|status
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0xf900
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
id|status
op_amp
l_int|0xf900
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: status %04X on %s&bslash;n&quot;
comma
id|status
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We don&squot;t use this to fix the device, but initialisation of it.&n; * It&squot;s not the correct use for this, but it works.  The actions we&n; * take are:&n; * - enable only IO&n; * - set memory region to start at zero&n; * - (0x48) enable all memory requests from ISA to be channeled to PCI&n; * - (0x42) disable ping-pong (as per errata)&n; * - (0x40) enable PCI packet retry&n; * - (0x83) don&squot;t use CPU park enable, park on last master, disable GAT bit&n; * - (0x80) default rotating priorities&n; * - (0x81) rotate bank 4&n; */
DECL|function|pci_fixup_83c553
r_static
r_void
id|__init
id|pci_fixup_83c553
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
comma
id|PCI_BASE_ADDRESS_SPACE_MEMORY
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|PCI_COMMAND_IO
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_sub_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
l_int|0xff
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x42
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x22
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x83
comma
l_int|0x02
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x80
comma
l_int|0xe0
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x81
comma
l_int|0x01
)paren
suffix:semicolon
)brace
DECL|function|pci_fixup_unassign
r_static
r_void
id|__init
id|pci_fixup_unassign
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_sub_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI IDE controllers use non-standard I/O port&n; * decoding, respect it.&n; */
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__init
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r
op_assign
id|dev-&gt;resource
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
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
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_83C553
comma
id|pci_fixup_83c553
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_WINBOND2
comma
id|PCI_DEVICE_ID_WINBOND2_89C940F
comma
id|pci_fixup_unassign
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocate resources for all PCI devices that have been enabled.&n; * We need to do that before we try to fix up anything.&n; */
DECL|function|pcibios_claim_resources
r_static
r_void
id|__init
id|pcibios_claim_resources
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
id|idx
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
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PCI_NUM_RESOURCES
suffix:semicolon
id|idx
op_increment
)paren
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|idx
)braket
dot
id|flags
op_logical_and
id|dev-&gt;resource
(braket
id|idx
)braket
dot
id|start
)paren
id|pci_claim_resource
c_func
(paren
id|dev
comma
id|idx
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
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: Assigning %3s %08lx to %s&bslash;n&quot;
comma
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
ques
c_cond
l_string|&quot;IO&quot;
suffix:colon
l_string|&quot;MEM&quot;
comma
id|res-&gt;start
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|where
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
id|resource
op_star
l_int|4
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
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: Assigning IRQ %02d to %s&bslash;n&quot;
comma
id|irq
comma
id|dev-&gt;name
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Called after each bus is probed, but before its children&n; * are examined.&n; */
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
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|bus-&gt;devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;sibling
)paren
(brace
id|u16
id|cmd
suffix:semicolon
multiline_comment|/*&n;&t;&t; * architecture specific hacks. I don&squot;t really want&n;&t;&t; * this here, but I don&squot;t see any other place for it&n;&t;&t; * to live.  Shame the device doesn&squot;t support&n;&t;&t; * capabilities&n;&t;&t; */
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
op_logical_and
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_DEC
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_DEC_21142
)paren
multiline_comment|/* Put the chip to sleep in case the driver isn&squot;t loaded */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x80000000
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this device is an ISA bridge, set the have_isa_bridge&n;&t;&t; * flag.  We will then go looking for things like keyboard,&n;&t;&t; * etc&n;&t;&t; */
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_BRIDGE_ISA
op_logical_or
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_BRIDGE_EISA
)paren
id|have_isa_bridge
op_assign
op_logical_neg
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set latency timer to 32, and a cache line size to 32 bytes.&n;&t;&t; * Also, set system error enable, parity error enable, and&n;&t;&t; * fast back to back transaction enable.  Disable ROM.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|32
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|8
)paren
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
id|cmd
op_or_assign
id|PCI_COMMAND_FAST_BACK
op_or
id|PCI_COMMAND_SERR
op_or
id|PCI_COMMAND_PARITY
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
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|no_swizzle
r_static
id|u8
id|__init
id|no_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ebsa285 host-specific stuff */
DECL|variable|__initdata
r_static
r_int
id|irqmap_ebsa285
(braket
)braket
id|__initdata
op_assign
(brace
id|IRQ_IN1
comma
id|IRQ_IN0
comma
id|IRQ_PCI
comma
id|IRQ_IN3
)brace
suffix:semicolon
DECL|function|ebsa285_swizzle
r_static
id|u8
id|__init
id|ebsa285_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
(brace
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
DECL|function|ebsa285_map_irq
r_static
r_int
id|__init
id|ebsa285_map_irq
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
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_CONTAQ
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_CONTAQ_82C693
)paren
r_switch
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
l_int|14
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_int|15
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_int|12
suffix:semicolon
)brace
r_return
id|irqmap_ebsa285
(braket
(paren
id|slot
op_plus
id|pin
)paren
op_amp
l_int|3
)braket
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|ebsa285_pci
id|__initdata
op_assign
(brace
id|dc21285_init
comma
l_int|0x9000
comma
l_int|0x00100000
comma
id|ebsa285_swizzle
comma
id|ebsa285_map_irq
)brace
suffix:semicolon
multiline_comment|/* cats host-specific stuff */
DECL|variable|__initdata
r_static
r_int
id|irqmap_cats
(braket
)braket
id|__initdata
op_assign
(brace
id|IRQ_PCI
comma
id|IRQ_IN0
comma
id|IRQ_IN1
comma
id|IRQ_IN3
)brace
suffix:semicolon
DECL|function|cats_map_irq
r_static
r_int
id|__init
id|cats_map_irq
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
id|dev-&gt;irq
op_ge
l_int|128
)paren
r_return
l_int|16
op_plus
(paren
id|dev-&gt;irq
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|1
op_logical_and
id|dev-&gt;irq
op_le
l_int|4
)paren
r_return
id|irqmap_cats
(braket
id|dev-&gt;irq
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: device %02x:%02x has unknown irq line %x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|cats_pci
id|__initdata
op_assign
(brace
id|dc21285_init
comma
l_int|0x9000
comma
l_int|0x00100000
comma
id|no_swizzle
comma
id|cats_map_irq
)brace
suffix:semicolon
multiline_comment|/* netwinder host-specific stuff */
DECL|function|netwinder_map_irq
r_static
r_int
id|__init
id|netwinder_map_irq
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
DECL|macro|DEV
mdefine_line|#define DEV(v,d) ((v)&lt;&lt;16|(d))
r_switch
c_cond
(paren
id|DEV
c_func
(paren
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
)paren
(brace
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_DEC
comma
id|PCI_DEVICE_ID_DEC_21142
)paren
suffix:colon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_NCR
comma
id|PCI_DEVICE_ID_NCR_53C885
)paren
suffix:colon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_NCR
comma
id|PCI_DEVICE_ID_NCR_YELLOWFIN
)paren
suffix:colon
r_return
id|IRQ_NETWINDER_ETHER100
suffix:semicolon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_WINBOND2
comma
l_int|0x5a5a
)paren
suffix:colon
r_return
id|IRQ_NETWINDER_ETHER10
suffix:semicolon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_83C553
)paren
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
)paren
suffix:colon
r_return
id|IRQ_ISA_HARDDISK1
suffix:semicolon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_INTERG
comma
id|PCI_DEVICE_ID_INTERG_2000
)paren
suffix:colon
r_case
id|DEV
c_func
(paren
id|PCI_VENDOR_ID_INTERG
comma
id|PCI_DEVICE_ID_INTERG_2010
)paren
suffix:colon
r_return
id|IRQ_NETWINDER_VGA
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: %02X:%02X [%04X:%04X] unknown device&bslash;n&quot;
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
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|netwinder_pci
id|__initdata
op_assign
(brace
id|dc21285_init
comma
l_int|0x9000
comma
l_int|0x00100000
comma
id|no_swizzle
comma
id|netwinder_map_irq
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
id|hw_pci
op_star
id|hw_pci
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_ebsa285
c_func
(paren
)paren
)paren
id|hw_pci
op_assign
op_amp
id|ebsa285_pci
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|hw_pci
op_assign
op_amp
id|cats_pci
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|hw_pci
op_assign
op_amp
id|netwinder_pci
suffix:semicolon
r_if
c_cond
(paren
id|hw_pci
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the host bridge, and scan the bus.&n;&t; */
id|hw_pci
op_member_access_from_pointer
id|init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Other architectures don&squot;t seem to do this... should we?&n;&t; */
id|pcibios_claim_resources
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Assign any unassigned resources.  Note that we really ought to&n;&t; * have min/max stuff here - max mem address is 0x0fffffff&n;&t; */
id|pci_assign_unassigned_resources
c_func
(paren
id|hw_pci-&gt;io_start
comma
id|hw_pci-&gt;mem_start
)paren
suffix:semicolon
id|pci_fixup_irqs
c_func
(paren
id|hw_pci-&gt;swizzle
comma
id|hw_pci-&gt;map_irq
)paren
suffix:semicolon
id|pci_set_bus_ranges
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise any other hardware after we&squot;ve got the PCI bus&n;&t; * initialised.  We may need the PCI bus to talk to this other&n;&t; * hardware.&n;&t; */
id|hw_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;debug&quot;
)paren
)paren
(brace
id|debug_pci
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
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
eof
