multiline_comment|/*&n; *&t;$Id: pci.c,v 1.91 1999/01/21 13:34:01 davem Exp $&n; *&n; *&t;PCI Bus Services, see include/linux/pci.h for further explanation.&n; *&n; *&t;Copyright 1993 -- 1997 Drew Eckhardt, Frederic Potter,&n; *&t;David Mosberger-Tang&n; *&n; *&t;Copyright 1997 -- 1999 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
r_extern
r_void
id|pci_namedevice
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
DECL|variable|pci_root
r_struct
id|pci_bus
id|pci_root
suffix:semicolon
DECL|variable|pci_devices
r_struct
id|pci_dev
op_star
id|pci_devices
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
r_int
id|pci_reverse
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|pci_last_dev_p
r_static
r_struct
id|pci_dev
op_star
op_star
id|pci_last_dev_p
op_assign
op_amp
id|pci_devices
suffix:semicolon
r_struct
id|pci_dev
op_star
DECL|function|pci_find_slot
id|pci_find_slot
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
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
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
id|bus
op_logical_and
id|dev-&gt;devfn
op_eq
id|devfn
)paren
r_break
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
r_struct
id|pci_dev
op_star
DECL|function|pci_find_device
id|pci_find_device
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
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_struct
id|pci_dev
op_star
id|next
suffix:semicolon
id|next
op_assign
id|pci_devices
suffix:semicolon
r_if
c_cond
(paren
id|from
)paren
id|next
op_assign
id|from-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|next
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_ne
id|PCI_ANY_ID
op_logical_and
id|dev-&gt;vendor
op_ne
id|vendor
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|device
op_ne
id|PCI_ANY_ID
op_logical_and
id|dev-&gt;device
op_ne
id|device
)paren
r_continue
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_struct
id|pci_dev
op_star
DECL|function|pci_find_class
id|pci_find_class
c_func
(paren
r_int
r_int
r_class
comma
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|from
)paren
id|from
op_assign
id|pci_devices
suffix:semicolon
r_else
id|from
op_assign
id|from-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|from
op_logical_and
id|from
op_member_access_from_pointer
r_class
op_ne
r_class
)paren
id|from
op_assign
id|from-&gt;next
suffix:semicolon
r_return
id|from
suffix:semicolon
)brace
r_int
DECL|function|pci_read_config_byte
id|pci_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u8
op_star
id|val
)paren
(brace
r_return
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_int
DECL|function|pci_read_config_word
id|pci_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u16
op_star
id|val
)paren
(brace
r_return
id|pcibios_read_config_word
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_int
DECL|function|pci_read_config_dword
id|pci_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_return
id|pcibios_read_config_dword
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_int
DECL|function|pci_write_config_byte
id|pci_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u8
id|val
)paren
(brace
r_return
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_int
DECL|function|pci_write_config_word
id|pci_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u16
id|val
)paren
(brace
r_return
id|pcibios_write_config_word
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_int
DECL|function|pci_write_config_dword
id|pci_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|where
comma
id|u32
id|val
)paren
(brace
r_return
id|pcibios_write_config_dword
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
r_void
DECL|function|pci_set_master
id|pci_set_master
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
suffix:semicolon
id|u8
id|lat
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmd
op_amp
id|PCI_COMMAND_MASTER
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling bus mastering for device %02x:%02x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|cmd
op_or_assign
id|PCI_COMMAND_MASTER
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
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lat
OL
l_int|16
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Increasing latency timer of device %02x:%02x to 64&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|64
)paren
suffix:semicolon
)brace
)brace
DECL|function|pci_read_bases
r_void
id|__init
id|pci_read_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_int
id|howmany
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
id|u32
id|l
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
OL
id|howmany
suffix:semicolon
id|reg
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
id|reg
suffix:semicolon
r_int
r_int
id|mask
comma
id|newval
comma
id|size
suffix:semicolon
id|res-&gt;name
op_assign
id|dev-&gt;name
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|reg
op_lshift
l_int|2
)paren
comma
op_amp
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
l_int|0xffffffff
)paren
r_continue
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|reg
op_lshift
l_int|2
)paren
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|reg
op_lshift
l_int|2
)paren
comma
op_amp
id|newval
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|reg
op_lshift
l_int|2
)paren
comma
id|l
)paren
suffix:semicolon
id|mask
op_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
r_if
c_cond
(paren
id|l
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
id|mask
op_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|newval
op_and_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newval
)paren
r_continue
suffix:semicolon
id|res-&gt;start
op_assign
id|l
op_amp
id|mask
suffix:semicolon
id|res-&gt;flags
op_assign
id|l
op_amp
op_complement
id|mask
suffix:semicolon
id|size
op_assign
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|size
op_amp
id|newval
)paren
)paren
suffix:semicolon
multiline_comment|/* 64-bit memory? */
r_if
c_cond
(paren
(paren
id|l
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
(brace
r_int
r_int
id|high
suffix:semicolon
id|reg
op_increment
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|reg
op_lshift
l_int|2
)paren
comma
op_amp
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
)paren
(brace
macro_line|#if BITS_PER_LONG == 64
id|res-&gt;start
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|high
)paren
op_lshift
l_int|32
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;PCI: Unable to handle 64-bit address for device %02x:%02x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|res-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|res-&gt;start
op_assign
l_int|0
suffix:semicolon
id|res-&gt;end
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
macro_line|#endif
)brace
)brace
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
id|request_resource
c_func
(paren
(paren
id|l
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
ques
c_cond
op_amp
id|ioport_resource
suffix:colon
op_amp
id|iomem_resource
comma
id|res
)paren
suffix:semicolon
)brace
)brace
DECL|function|pci_scan_bus
r_int
r_int
id|__init
id|pci_scan_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_int
r_int
id|devfn
comma
id|l
comma
id|max
comma
r_class
suffix:semicolon
r_int
r_char
id|cmd
comma
id|irq
comma
id|tmp
comma
id|hdr_type
comma
id|is_multi
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
comma
op_star
op_star
id|bus_last
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;pci_scan_bus for bus %d&bslash;n&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
id|bus_last
op_assign
op_amp
id|bus-&gt;devices
suffix:semicolon
id|max
op_assign
id|bus-&gt;secondary
suffix:semicolon
r_for
c_loop
(paren
id|devfn
op_assign
l_int|0
suffix:semicolon
id|devfn
OL
l_int|0xff
suffix:semicolon
op_increment
id|devfn
)paren
(brace
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
op_logical_and
op_logical_neg
id|is_multi
)paren
(brace
multiline_comment|/* not a multi-function device */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr_type
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
)paren
id|is_multi
op_assign
id|hdr_type
op_amp
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|l
)paren
op_logical_or
multiline_comment|/* some broken boards return 0 if a slot is empty: */
id|l
op_eq
l_int|0xffffffff
op_logical_or
id|l
op_eq
l_int|0x00000000
op_logical_or
id|l
op_eq
l_int|0x0000ffff
op_logical_or
id|l
op_eq
l_int|0xffff0000
)paren
r_continue
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pci: out of memory.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;bus
op_assign
id|bus
suffix:semicolon
id|dev-&gt;devfn
op_assign
id|devfn
suffix:semicolon
id|dev-&gt;vendor
op_assign
id|l
op_amp
l_int|0xffff
suffix:semicolon
id|dev-&gt;device
op_assign
(paren
id|l
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|pci_namedevice
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* non-destructively determine if device can be a master: */
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|cmd
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|dev-&gt;master
op_assign
(paren
(paren
id|tmp
op_amp
id|PCI_COMMAND_MASTER
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_CLASS_REVISION
comma
op_amp
r_class
)paren
suffix:semicolon
r_class
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* upper 3 bytes */
id|dev
op_member_access_from_pointer
r_class
op_assign
r_class
suffix:semicolon
r_class
op_rshift_assign
l_int|8
suffix:semicolon
id|dev-&gt;hdr_type
op_assign
id|hdr_type
suffix:semicolon
r_switch
c_cond
(paren
id|hdr_type
op_amp
l_int|0x7f
)paren
(brace
multiline_comment|/* header type */
r_case
id|PCI_HEADER_TYPE_NORMAL
suffix:colon
multiline_comment|/* standard header */
r_if
c_cond
(paren
r_class
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the card generates interrupts, read IRQ number&n;&t;&t;&t; * (some architectures change it during pcibios_fixup())&n;&t;&t;&t; */
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * read base address registers, again pcibios_fixup() can&n;&t;&t;&t; * tweak these&n;&t;&t;&t; */
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|6
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_ROM_ADDRESS
comma
op_amp
id|l
)paren
suffix:semicolon
id|dev-&gt;rom_address
op_assign
(paren
id|l
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
id|l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_BRIDGE
suffix:colon
multiline_comment|/* bridge header */
r_if
c_cond
(paren
r_class
op_ne
id|PCI_CLASS_BRIDGE_PCI
)paren
r_goto
id|bad
suffix:semicolon
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|2
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_ROM_ADDRESS1
comma
op_amp
id|l
)paren
suffix:semicolon
id|dev-&gt;rom_address
op_assign
(paren
id|l
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
id|l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_CARDBUS
suffix:colon
multiline_comment|/* CardBus bridge header */
r_if
c_cond
(paren
r_class
op_ne
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
r_goto
id|bad
suffix:semicolon
id|pci_read_bases
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* unknown header */
id|bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: %02x:%02x [%04x/%04x/%06x] has unknown header type %02x, ignoring.&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
r_class
comma
id|hdr_type
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;PCI: %02x:%02x [%04x/%04x]&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Put it into the global PCI device chain. It&squot;s used to&n;&t;&t; * find devices once everything is set up.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pci_reverse
)paren
(brace
op_star
id|pci_last_dev_p
op_assign
id|dev
suffix:semicolon
id|pci_last_dev_p
op_assign
op_amp
id|dev-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;next
op_assign
id|pci_devices
suffix:semicolon
id|pci_devices
op_assign
id|dev
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Now insert it into the list of devices held&n;&t;&t; * by the parent bus.&n;&t;&t; */
op_star
id|bus_last
op_assign
id|dev
suffix:semicolon
id|bus_last
op_assign
op_amp
id|dev-&gt;sibling
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t;&t; * Setting of latency timer in case it was less than 32 was&n;&t;&t; * a great idea, but it confused several broken devices. Grrr.&n;&t;&t; */
id|pcibios_read_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|32
)paren
id|pcibios_write_config_byte
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_LATENCY_TIMER
comma
l_int|32
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t; * After performing arch-dependent fixup of the bus, look behind&n;&t; * all PCI-to-PCI bridges on this bus.&n;&t; */
id|pcibios_fixup_bus
c_func
(paren
id|bus
)paren
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
multiline_comment|/*&n;&t;&t; * If it&squot;s a bridge, scan the bus behind it.&n;&t;&t; */
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
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
(brace
r_int
r_int
id|buses
suffix:semicolon
r_int
r_int
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_int
r_int
id|cr
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Insert it into the tree of buses.&n;&t;&t;&t; */
id|child
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|child
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pci: out of memory for bridge.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|child
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|child
)paren
)paren
suffix:semicolon
id|child-&gt;next
op_assign
id|bus-&gt;children
suffix:semicolon
id|bus-&gt;children
op_assign
id|child
suffix:semicolon
id|child-&gt;self
op_assign
id|dev
suffix:semicolon
id|child-&gt;parent
op_assign
id|bus
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Set up the primary, secondary and subordinate&n;&t;&t;&t; * bus numbers.&n;&t;&t;&t; */
id|child-&gt;number
op_assign
id|child-&gt;secondary
op_assign
op_increment
id|max
suffix:semicolon
id|child-&gt;primary
op_assign
id|bus-&gt;secondary
suffix:semicolon
id|child-&gt;subordinate
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Clear all status bits and turn off memory,&n;&t;&t;&t; * I/O and master enables.&n;&t;&t;&t; */
id|pcibios_read_config_word
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cr
)paren
suffix:semicolon
id|pcibios_write_config_word
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
l_int|0x0000
)paren
suffix:semicolon
id|pcibios_write_config_word
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_STATUS
comma
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Read the existing primary/secondary/subordinate bus&n;&t;&t;&t; * number configuration to determine if the PCI bridge&n;&t;&t;&t; * has already been configured by the system.  If so,&n;&t;&t;&t; * do not modify the configuration, merely note it.&n;&t;&t;&t; */
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_PRIMARY_BUS
comma
op_amp
id|buses
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buses
op_amp
l_int|0xFFFFFF
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|cmax
suffix:semicolon
id|child-&gt;primary
op_assign
id|buses
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;secondary
op_assign
(paren
id|buses
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;subordinate
op_assign
(paren
id|buses
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|child-&gt;number
op_assign
id|child-&gt;secondary
suffix:semicolon
id|cmax
op_assign
id|pci_scan_bus
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmax
OG
id|max
)paren
id|max
op_assign
id|cmax
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;     * Configure the bus numbers for this bridge:&n;&t;&t;&t;     */
id|buses
op_and_assign
l_int|0xff000000
suffix:semicolon
id|buses
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;primary
)paren
op_lshift
l_int|0
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;secondary
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;subordinate
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_PRIMARY_BUS
comma
id|buses
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;     * Now we can scan all subordinate buses:&n;&t;&t;&t;     */
id|max
op_assign
id|pci_scan_bus
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;     * Set the subordinate bus number to its real&n;&t;&t;&t;     * value:&n;&t;&t;&t;     */
id|child-&gt;subordinate
op_assign
id|max
suffix:semicolon
id|buses
op_assign
(paren
id|buses
op_amp
l_int|0xff00ffff
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|child-&gt;subordinate
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_PRIMARY_BUS
comma
id|buses
)paren
suffix:semicolon
)brace
id|pcibios_write_config_word
c_func
(paren
id|bus-&gt;number
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|cr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We&squot;ve scanned the bus and so we know all about what&squot;s on&n;&t; * the other side of any bridges that may be on this bus plus&n;&t; * any devices.&n;&t; *&n;&t; * Return how far we&squot;ve got finding sub-buses.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;PCI: pci_scan_bus returning with max=%02x&bslash;n&quot;
comma
id|max
)paren
suffix:semicolon
r_return
id|max
suffix:semicolon
)brace
DECL|function|pci_scan_peer_bridge
r_struct
id|pci_bus
op_star
id|__init
id|pci_scan_peer_bridge
c_func
(paren
r_int
id|bus
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
suffix:semicolon
id|b
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|b
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|b
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|b
)paren
)paren
suffix:semicolon
id|b-&gt;next
op_assign
id|pci_root.next
suffix:semicolon
id|pci_root.next
op_assign
id|b
suffix:semicolon
id|b-&gt;number
op_assign
id|b-&gt;secondary
op_assign
id|bus
suffix:semicolon
id|b-&gt;subordinate
op_assign
id|pci_scan_bus
c_func
(paren
id|b
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
DECL|function|pci_init
r_void
id|__init
id|pci_init
c_func
(paren
r_void
)paren
(brace
id|pcibios_init
c_func
(paren
)paren
suffix:semicolon
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
l_string|&quot;PCI: No PCI bus detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pci_root
comma
l_int|0
comma
r_sizeof
(paren
id|pci_root
)paren
)paren
suffix:semicolon
id|pci_root.subordinate
op_assign
id|pci_scan_bus
c_func
(paren
op_amp
id|pci_root
)paren
suffix:semicolon
multiline_comment|/* give BIOS a chance to apply platform specific fixes: */
id|pcibios_fixup
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_QUIRKS
id|pci_quirks_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|pci_setup
r_static
r_int
id|__init
id|pci_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
id|str
)paren
(brace
r_char
op_star
id|k
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|k
)paren
op_star
id|k
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_logical_and
(paren
id|str
op_assign
id|pcibios_setup
c_func
(paren
id|str
)paren
)paren
op_logical_and
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
l_string|&quot;reverse&quot;
)paren
)paren
id|pci_reverse
op_assign
l_int|1
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Unknown option `%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
id|str
op_assign
id|k
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pci=&quot;
comma
id|pci_setup
)paren
suffix:semicolon
eof
