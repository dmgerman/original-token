multiline_comment|/*&n; * $Id: pci.c,v 1.64 1999/09/17 18:01:53 cort Exp $&n; * Common pmac/prep/chrp pci routines. -- Cort&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/gg2.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|isa_mem_base
r_int
r_int
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|pci_dram_offset
r_int
r_int
id|pci_dram_offset
op_assign
l_int|0
suffix:semicolon
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|generic_pcibios_read_byte
r_int
id|generic_pcibios_read_byte
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
r_return
id|ppc_md
dot
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
DECL|function|generic_pcibios_read_word
r_int
id|generic_pcibios_read_word
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
r_return
id|ppc_md
dot
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
DECL|function|generic_pcibios_read_dword
r_int
id|generic_pcibios_read_dword
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
r_return
id|ppc_md
dot
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
DECL|function|generic_pcibios_write_byte
r_int
id|generic_pcibios_write_byte
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
r_return
id|ppc_md
dot
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
DECL|function|generic_pcibios_write_word
r_int
id|generic_pcibios_write_word
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
r_return
id|ppc_md
dot
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
DECL|function|generic_pcibios_write_dword
r_int
id|generic_pcibios_write_dword
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
r_return
id|ppc_md
dot
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
DECL|variable|generic_pci_ops
r_struct
id|pci_ops
id|generic_pci_ops
op_assign
(brace
id|generic_pcibios_read_byte
comma
id|generic_pcibios_read_word
comma
id|generic_pcibios_read_dword
comma
id|generic_pcibios_write_byte
comma
id|generic_pcibios_write_word
comma
id|generic_pcibios_write_dword
)brace
suffix:semicolon
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
multiline_comment|/*&n; * We need to avoid collisions with `mirrored&squot; VGA ports&n; * and other strange ISA hardware, so we always want the&n; * addresses to be allocated in the 0x000-0x0ff region&n; * modulo 0x400.&n; *&n; * Why? Because some silly external IO cards only decode&n; * the low 10 bits of the IO address. The 0x00-0xff region&n; * is reserved for motherboard devices that decode all 16&n; * bits, so it&squot;s ok to allocate at, say, 0x2800-0x28ff,&n; * but we want to try to avoid allocating at 0x2900-0x2bff&n; * which might have be mirrored at 0x0100-0x03ff..&n; */
r_void
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
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
(brace
id|start
op_assign
(paren
id|start
op_plus
l_int|0x3ff
)paren
op_amp
op_complement
l_int|0x3ff
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *  Handle resources of PCI devices.  If the world were perfect, we could&n; *  just allocate all the resource regions and do nothing more.  It isn&squot;t.&n; *  On the other hand, we cannot just re-allocate all devices, as it would&n; *  require us to know lots of host bridge internals.  So we attempt to&n; *  keep as much of the original configuration as possible, but tweak it&n; *  when it&squot;s found to be wrong.&n; *&n; *  Known BIOS problems we have to work around:&n; *&t;- I/O or memory regions not configured&n; *&t;- regions configured, but not enabled in the command register&n; *&t;- bogus I/O addresses above 64K used&n; *&t;- expansion ROMs left enabled (this may sound harmless, but given&n; *&t;  the fact the PCI specs explicitly allow address decoders to be&n; *&t;  shared between expansion ROMs and other resource regions, it&squot;s&n; *&t;  at least dangerous)&n; *&n; *  Our solution:&n; *&t;(1) Allocate resources for all buses behind PCI-to-PCI bridges.&n; *&t;    This gives us fixed barriers on where we can allocate.&n; *&t;(2) Allocate resources for all enabled devices.  If there is&n; *&t;    a collision, just mark the resource as unallocated. Also&n; *&t;    disable expansion ROMs during this step.&n; *&t;(3) Try to allocate resources for disabled devices.  If the&n; *&t;    resources were assigned correctly, everything goes well,&n; *&t;    if they weren&squot;t, they won&squot;t disturb allocation of other&n; *&t;    resources.&n; *&t;(4) Assign new addresses to resources which were either&n; *&t;    not configured at all or misconfigured.  If explicitly&n; *&t;    requested by the user, configure expansion ROM address&n; *&t;    as well.&n; */
DECL|function|pcibios_allocate_bus_resources
r_static
r_void
id|__init
id|pcibios_allocate_bus_resources
c_func
(paren
r_struct
id|list_head
op_star
id|bus_list
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
multiline_comment|/* Depth-First Search on bus tree */
r_for
c_loop
(paren
id|ln
op_assign
id|bus_list-&gt;next
suffix:semicolon
id|ln
op_ne
id|bus_list
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bus-&gt;self
)paren
)paren
(brace
r_for
c_loop
(paren
id|idx
op_assign
id|PCI_BRIDGE_RESOURCES
suffix:semicolon
id|idx
OL
id|PCI_NUM_RESOURCES
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
)paren
r_continue
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of bridge %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
)brace
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|bus-&gt;children
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_allocate_resources
r_static
r_void
id|__init
id|pcibios_allocate_resources
c_func
(paren
r_int
id|pass
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
comma
id|disabled
suffix:semicolon
id|u16
id|command
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
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
id|r-&gt;parent
)paren
multiline_comment|/* Already allocated */
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
)paren
multiline_comment|/* Address not assigned at all */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;end
op_eq
l_int|0xffffffff
)paren
(brace
multiline_comment|/* LongTrail OF quirk: unassigned */
id|DBG
c_func
(paren
l_string|&quot;PCI: Resource %08lx-%08lx was unassigned&bslash;n&quot;
comma
id|r-&gt;start
comma
id|r-&gt;end
)paren
suffix:semicolon
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_IO
)paren
suffix:semicolon
r_else
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
id|disabled
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Resource %08lx-%08lx (f=%lx, d=%d, p=%d)&bslash;n&quot;
comma
id|r-&gt;start
comma
id|r-&gt;end
comma
id|r-&gt;flags
comma
id|disabled
comma
id|pass
)paren
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of device %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll assign a new address later */
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|PCI_ROM_ADDRESS_ENABLE
)paren
(brace
multiline_comment|/* Turn the ROM off, leave the resource region, but keep it unregistered. */
id|u32
id|reg
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Switching off ROM of %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|r-&gt;flags
op_and_assign
op_complement
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
op_amp
id|reg
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
id|reg
op_amp
op_complement
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pcibios_assign_resources
r_static
r_void
id|__init
id|pcibios_assign_resources
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
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_int
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
multiline_comment|/* Don&squot;t touch classless devices and host bridges */
r_if
c_cond
(paren
op_logical_neg
r_class
op_logical_or
r_class
op_eq
id|PCI_CLASS_BRIDGE_HOST
)paren
r_continue
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
multiline_comment|/*&n;&t;&t;&t; *  Don&squot;t touch IDE controllers and I/O ports of video cards!&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
r_class
op_eq
id|PCI_CLASS_STORAGE_IDE
op_logical_and
id|idx
OL
l_int|4
)paren
op_logical_or
(paren
r_class
op_eq
id|PCI_CLASS_DISPLAY_VGA
op_logical_and
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  We shall assign a new address to this resource, either because&n;&t;&t;&t; *  the BIOS forgot to do so or because we have decided the old&n;&t;&t;&t; *  address was unusable for some reason.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|idx
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
)paren
(brace
multiline_comment|/* don&squot;t assign ROMs */
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|PCI_ROM_RESOURCE
)paren
suffix:semicolon
)brace
)brace
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
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
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
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|generic_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.pcibios_fixup
)paren
id|ppc_md
dot
id|pcibios_fixup
c_func
(paren
)paren
suffix:semicolon
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|pci_root_buses
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|pcibios_assign_resources
c_func
(paren
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
DECL|function|resource_fixup
r_int
r_int
id|resource_fixup
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
id|res
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|start
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
r_if
c_cond
(paren
id|ppc_md.pcibios_fixup_bus
)paren
id|ppc_md
dot
id|pcibios_fixup_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
id|__init
op_star
id|pcibios_setup
c_func
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
multiline_comment|/* the next one is stolen from the alpha port... */
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
multiline_comment|/* XXX FIXME - update OF device tree node interrupt property */
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
r_void
op_star
DECL|function|pci_dev_io_base
id|pci_dev_io_base
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
comma
r_int
id|physical
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.pci_dev_io_base
)paren
(brace
multiline_comment|/* Please, someone fix this for non-pmac machines, we&n;&t;&t; * need either the virtual or physical PCI IO base&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ppc_md
dot
id|pci_dev_io_base
c_func
(paren
id|bus
comma
id|devfn
comma
id|physical
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|pci_dev_mem_base
id|pci_dev_mem_base
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
(brace
multiline_comment|/* Default memory base is 0 (1:1 mapping) */
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.pci_dev_mem_base
)paren
(brace
multiline_comment|/* Please, someone fix this for non-pmac machines.*/
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ppc_md
dot
id|pci_dev_mem_base
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the root-bridge number (Uni-N number) of a device */
r_int
DECL|function|pci_dev_root_bridge
id|pci_dev_root_bridge
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
(brace
multiline_comment|/* Defaults to 0 */
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.pci_dev_root_bridge
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ppc_md
dot
id|pci_dev_root_bridge
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
)brace
multiline_comment|/* Provide information on locations of various I/O regions in physical&n; * memory.  Do this on a per-card basis so that we choose the right&n; * root bridge.&n; * Note that the returned IO or memory base is a physical address&n; */
id|asmlinkage
r_int
DECL|function|sys_pciconfig_iobase
id|sys_pciconfig_iobase
c_func
(paren
r_int
id|which
comma
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|IOBASE_BRIDGE_NUMBER
suffix:colon
r_return
(paren
r_int
)paren
id|pci_dev_root_bridge
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
r_case
id|IOBASE_MEMORY
suffix:colon
r_return
(paren
r_int
)paren
id|pci_dev_mem_base
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
r_case
id|IOBASE_IO
suffix:colon
id|result
op_assign
(paren
r_int
)paren
id|pci_dev_io_base
c_func
(paren
id|bus
comma
id|devfn
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
id|result
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
eof
