multiline_comment|/*&n; * bios32.c - PCI BIOS functions for Alpha systems not using BIOS&n; *&t;      emulation code.&n; *&n; * Written by Dave Rusling (david.rusling@reo.mts.dec.com)&n; *&n; * Adapted to 64-bit kernel and then rewritten by David Mosberger&n; * (davidm@cs.arizona.edu)&n; *&n; * For more information, please consult&n; *&n; * PCI BIOS Specification Revision&n; * PCI Local Bus Specification&n; * PCI System Design Guide&n; *&n; * PCI Special Interest Group&n; * M/S HF3-15A&n; * 5200 N.E. Elam Young Parkway&n; * Hillsboro, Oregon 97124-6497&n; * +1 (503) 696-2000&n; * +1 (800) 433-5177&n; *&n; * Manuals are $25 each or $50 for all three, plus $7 shipping&n; * within the United States, $35 abroad.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_PCI
DECL|function|pcibios_present
r_int
id|pcibios_present
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PCI */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|KB
mdefine_line|#define KB&t;&t;1024
DECL|macro|MB
mdefine_line|#define MB&t;&t;(1024*KB)
DECL|macro|GB
mdefine_line|#define GB&t;&t;(1024*MB)
DECL|macro|MAJOR_REV
mdefine_line|#define MAJOR_REV&t;0
DECL|macro|MINOR_REV
mdefine_line|#define MINOR_REV&t;3
multiline_comment|/*&n; * Align VAL to ALIGN, which must be a power of two.&n; */
DECL|macro|ALIGN
mdefine_line|#define ALIGN(val,align)&t;(((val) + ((align) - 1)) &amp; ~((align) - 1))
multiline_comment|/*&n; * Temporary internal macro.  If this 0, then do not write to any of&n; * the PCI registers, merely read them (i.e., use configuration as&n; * determined by SRM).  The SRM seem do be doing a less than perfect&n; * job in configuring PCI devices, so for now we do it ourselves.&n; * Reconfiguring PCI devices breaks console (RPB) callbacks, but&n; * those don&squot;t work properly with 64 bit addresses anyways.&n; *&n; * The accepted convention seems to be that the console (POST&n; * software) should fully configure boot devices and configure the&n; * interrupt routing of *all* devices.  In particular, the base&n; * addresses of non-boot devices need not be initialized.  For&n; * example, on the AXPpci33 board, the base address a #9 GXE PCI&n; * graphics card reads as zero (this may, however, be due to a bug in&n; * the graphics card---there have been some rumor that the #9 BIOS&n; * incorrectly resets that address to 0...).&n; */
DECL|macro|PCI_MODIFY
mdefine_line|#define PCI_MODIFY&t;&t;1
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
macro_line|#if PCI_MODIFY
DECL|variable|io_base
r_static
r_int
r_int
id|io_base
op_assign
l_int|64
op_star
id|KB
suffix:semicolon
multiline_comment|/* &lt;64KB are (E)ISA ports */
DECL|variable|mem_base
r_static
r_int
r_int
id|mem_base
op_assign
l_int|16
op_star
id|MB
suffix:semicolon
multiline_comment|/* &lt;16MB is ISA memory */
multiline_comment|/*&n; * Layout memory and I/O for a device:&n; */
DECL|function|layout_dev
r_static
r_void
id|layout_dev
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_int
r_int
id|base
comma
id|mask
comma
id|size
comma
id|reg
suffix:semicolon
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
id|pcibios_read_config_word
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
suffix:semicolon
id|reg
op_le
id|PCI_BASE_ADDRESS_5
suffix:semicolon
id|reg
op_add_assign
l_int|4
)paren
(brace
multiline_comment|/*&n;&t;&t; * Figure out how much space and of what type this&n;&t;&t; * device wants.&n;&t;&t; */
id|pcibios_write_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|reg
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|reg
comma
op_amp
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
multiline_comment|/* this base-address register is unused */
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We&squot;ve read the base address register back after&n;&t;&t; * writing all ones and so now we must decode it.&n;&t;&t; */
r_if
c_cond
(paren
id|base
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * I/O space base address register.&n;&t;&t;&t; */
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
id|base
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|mask
op_assign
(paren
op_complement
id|base
op_lshift
l_int|1
)paren
op_or
l_int|0x1
suffix:semicolon
id|size
op_assign
(paren
id|mask
op_amp
id|base
)paren
op_amp
l_int|0xffffffff
suffix:semicolon
id|base
op_assign
id|ALIGN
c_func
(paren
id|io_base
comma
id|size
)paren
suffix:semicolon
id|io_base
op_assign
id|base
op_plus
id|size
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|reg
comma
id|base
op_or
l_int|0x1
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Memory space base address register.&n;&t;&t;&t; */
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
id|type
op_assign
id|base
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
suffix:semicolon
id|base
op_and_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|mask
op_assign
(paren
op_complement
id|base
op_lshift
l_int|1
)paren
op_or
l_int|0x1
suffix:semicolon
id|size
op_assign
(paren
id|mask
op_amp
id|base
)paren
op_amp
l_int|0xffffffff
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_32
suffix:colon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_64
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bios32 WARNING: &quot;
l_string|&quot;ignoring 64-bit device in &quot;
l_string|&quot;slot %d, function %d: &bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|reg
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* skip extra 4 bytes */
r_continue
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_1M
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * Allocating memory below 1MB is *very*&n;&t;&t;&t;&t; * tricky, as there may be all kinds of&n;&t;&t;&t;&t; * ISA devices lurking that we don&squot;t know&n;&t;&t;&t;&t; * about.  For now, we just cross fingers&n;&t;&t;&t;&t; * and hope nobody tries to do this on an&n;&t;&t;&t;&t; * Alpha (or that the console has set it&n;&t;&t;&t;&t; * up properly).&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;bios32 WARNING: slot %d, function %d &quot;
l_string|&quot;requests memory below 1MB---don&squot;t &quot;
l_string|&quot;know how to do that.&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * The following holds at least for the Low Cost&n;&t;&t;&t; * Alpha implementation of the PCI interface:&n;&t;&t;&t; *&n;&t;&t;&t; * In sparse memory address space, the first&n;&t;&t;&t; * octant (16MB) of every 128MB segment is&n;&t;&t;&t; * aliased to the the very first 16MB of the&n;&t;&t;&t; * address space (i.e., it aliases the ISA&n;&t;&t;&t; * memory address space).  Thus, we try to&n;&t;&t;&t; * avoid allocating PCI devices in that range.&n;&t;&t;&t; * Can be allocated in 2nd-7th octant only.&n;&t;&t;&t; * Devices that need more than 112MB of&n;&t;&t;&t; * address space must be accessed through&n;&t;&t;&t; * dense memory space only!&n;&t;&t;&t; */
id|base
op_assign
id|ALIGN
c_func
(paren
id|mem_base
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|7
op_star
l_int|16
op_star
id|MB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bios32 WARNING: slot %d, function %d &quot;
l_string|&quot;requests  %dB of contiguous address &quot;
l_string|&quot; space---don&squot;t use sparse memory &quot;
l_string|&quot; accesses on this device!!&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
(paren
id|base
op_div
l_int|16
op_star
id|MB
)paren
op_amp
l_int|0x7
)paren
op_eq
l_int|0
)paren
(brace
id|base
op_and_assign
op_complement
(paren
l_int|128
op_star
id|MB
op_minus
l_int|1
)paren
suffix:semicolon
id|base
op_add_assign
l_int|16
op_star
id|MB
suffix:semicolon
id|base
op_assign
id|ALIGN
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_div
l_int|128
op_star
id|MB
op_ne
(paren
id|base
op_plus
id|size
)paren
op_div
l_int|128
op_star
id|MB
)paren
(brace
id|base
op_and_assign
op_complement
(paren
l_int|128
op_star
id|MB
op_minus
l_int|1
)paren
suffix:semicolon
id|base
op_add_assign
(paren
l_int|128
op_plus
l_int|16
)paren
op_star
id|MB
suffix:semicolon
id|base
op_assign
id|ALIGN
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
)brace
)brace
id|mem_base
op_assign
id|base
op_plus
id|size
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|reg
comma
id|base
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* enable device: */
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_NOT_DEFINED
op_logical_or
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_NOT_DEFINED_VGA
op_logical_or
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_DISPLAY_VGA
op_logical_or
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_DISPLAY_XGA
)paren
(brace
multiline_comment|/*&n;&t;&t; * All of these (may) have I/O scattered all around&n;&t;&t; * and may not use i/o-base address registers at all.&n;&t;&t; * So we just have to always enable I/O to these&n;&t;&t; * devices.&n;&t;&t; */
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
)brace
id|pcibios_write_config_word
c_func
(paren
id|bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_COMMAND
comma
id|cmd
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
)brace
DECL|function|layout_bus
r_static
r_void
id|layout_bus
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
id|l
comma
id|tio
comma
id|bio
comma
id|tmem
comma
id|bmem
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;devices
op_logical_and
op_logical_neg
id|bus-&gt;children
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Align the current bases on appropriate boundaries (4K for&n;&t; * IO and 1MB for memory).&n;&t; */
id|bio
op_assign
id|io_base
op_assign
id|ALIGN
c_func
(paren
id|io_base
comma
l_int|4
op_star
id|KB
)paren
suffix:semicolon
id|bmem
op_assign
id|mem_base
op_assign
id|ALIGN
c_func
(paren
id|mem_base
comma
l_int|1
op_star
id|MB
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate space to each device:&n;&t; */
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
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|16
op_ne
id|PCI_BASE_CLASS_BRIDGE
)paren
(brace
id|layout_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Recursively allocate space for all of the sub-buses:&n;&t; */
r_for
c_loop
(paren
id|child
op_assign
id|bus-&gt;children
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|child-&gt;next
)paren
(brace
id|layout_bus
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Align the current bases on 4K and 1MB boundaries:&n;&t; */
id|tio
op_assign
id|io_base
op_assign
id|ALIGN
c_func
(paren
id|io_base
comma
l_int|4
op_star
id|KB
)paren
suffix:semicolon
id|tmem
op_assign
id|mem_base
op_assign
id|ALIGN
c_func
(paren
id|mem_base
comma
l_int|1
op_star
id|MB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;self
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|bus-&gt;self
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up the top and bottom of the I/O memory segment&n;&t;&t; * for this bus.&n;&t;&t; */
id|pcibios_read_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x1c
comma
op_amp
id|l
)paren
suffix:semicolon
id|l
op_assign
id|l
op_or
(paren
id|bio
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|tio
op_minus
l_int|1
)paren
op_amp
l_int|0xf000
)paren
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x1c
comma
id|l
)paren
suffix:semicolon
id|l
op_assign
(paren
(paren
id|bmem
op_amp
l_int|0xfff00000
)paren
op_rshift
l_int|16
)paren
op_or
(paren
(paren
id|tmem
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
)paren
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x20
comma
id|l
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Turn off downstream PF memory address range:&n;&t;&t; */
id|pcibios_write_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x24
comma
l_int|0x0000ffff
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Tell bridge that there is an ISA bus in the system:&n;&t;&t; */
id|pcibios_write_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x3c
comma
l_int|0x00040000
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Clear status bits, enable I/O (for downstream I/O),&n;&t;&t; * turn on master enable (for upstream I/O), turn on&n;&t;&t; * memory enable (for downstream memory), turn on&n;&t;&t; * master enable (for upstream memory and I/O).&n;&t;&t; */
id|pcibios_write_config_dword
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|bridge-&gt;devfn
comma
l_int|0x4
comma
l_int|0xffff0007
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* !PCI_MODIFY */
multiline_comment|/*&n; * Given the vendor and device ids, find the n&squot;th instance of that device&n; * in the system.  &n; */
DECL|function|pcibios_find_device
r_int
id|pcibios_find_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device_id
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|devfn
)paren
(brace
r_int
r_int
id|current
op_assign
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|vendor
op_logical_and
id|dev-&gt;device
op_eq
id|device_id
)paren
(brace
r_if
c_cond
(paren
id|current
op_eq
id|index
)paren
(brace
op_star
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
op_star
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
op_increment
id|current
suffix:semicolon
)brace
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
multiline_comment|/*&n; * Given the class, find the n&squot;th instance of that device&n; * in the system.&n; */
DECL|function|pcibios_find_class
r_int
id|pcibios_find_class
(paren
r_int
r_int
id|class_code
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|devfn
)paren
(brace
r_int
r_int
id|current
op_assign
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_eq
id|class_code
)paren
(brace
r_if
c_cond
(paren
id|current
op_eq
id|index
)paren
(brace
op_star
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
op_star
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
op_increment
id|current
suffix:semicolon
)brace
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
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
DECL|function|pcibios_init
r_int
r_int
id|pcibios_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Alpha PCI BIOS32 revision %x.%02x&bslash;n&quot;
comma
id|MAJOR_REV
comma
id|MINOR_REV
)paren
suffix:semicolon
macro_line|#if !PCI_MODIFY
id|printk
c_func
(paren
l_string|&quot;...NOT modifying existing (SRM) PCI configuration&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|mem_start
suffix:semicolon
)brace
multiline_comment|/*&n; * The SRM console *disables* the IDE interface, this code ensures its&n; * enabled.&n; *&n; * This code bangs on a control register of the 87312 Super I/O chip&n; * that implements parallel port/serial ports/IDE/FDI.  Depending on&n; * the motherboard, the Super I/O chip can be configured through a&n; * pair of registers that are located either at I/O ports 0x26e/0x26f&n; * or 0x398/0x399.  Unfortunately, autodetecting which base address is&n; * in use works only once (right after a reset).  The Super I/O chip&n; * has the additional quirk that configuration register data must be&n; * written twice (I believe this is a saftey feature to prevent&n; * accidental modification---fun, isn&squot;t it?).&n; */
DECL|function|enable_ide
r_static
r_inline
r_void
id|enable_ide
c_func
(paren
r_int
id|ide_base
)paren
(brace
r_int
id|data
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ide_base
)paren
suffix:semicolon
multiline_comment|/* set the index register for reg #0 */
id|data
op_assign
id|inb
c_func
(paren
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* read the current contents */
id|outb
c_func
(paren
l_int|0
comma
id|ide_base
)paren
suffix:semicolon
multiline_comment|/* set the index register for reg #0 */
id|outb
c_func
(paren
id|data
op_or
l_int|0x40
comma
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* turn on IDE */
id|outb
c_func
(paren
id|data
op_or
l_int|0x40
comma
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* turn on IDE, really! */
)brace
multiline_comment|/*&n; * Most evaluation boards share most of the fixup code, which is isolated here.&n; * This function is declared &quot;inline&quot; as only one platform will ever be selected&n; * in any given kernel.  If that platform doesn&squot;t need this code, we don&squot;t want&n; * it around as dead code.&n; */
DECL|function|common_fixup
r_static
r_inline
r_void
id|common_fixup
c_func
(paren
r_int
id|min_idsel
comma
r_int
id|max_idsel
comma
r_int
id|irqs_per_slot
comma
r_char
id|irq_tab
(braket
id|max_idsel
op_minus
id|min_idsel
op_plus
l_int|1
)braket
(braket
id|irqs_per_slot
)braket
comma
r_int
id|ide_base
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_char
id|pin
suffix:semicolon
multiline_comment|/*&n;&t; * Go through all devices, fixing up irqs as we see fit:&n;&t; */
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
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ignore things not on the primary bus - I&squot;ll figure&n;&t;&t; * this out one day - Dave Rusling&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* read the pin */
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
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
id|irq_tab
(braket
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_minus
id|min_idsel
)braket
(braket
id|pin
)braket
op_ne
op_minus
l_int|1
)paren
id|dev-&gt;irq
op_assign
id|irq_tab
(braket
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_minus
id|min_idsel
)braket
(braket
id|pin
)braket
suffix:semicolon
macro_line|#if PCI_MODIFY
multiline_comment|/* tell the device: */
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|ide_base
)paren
(brace
id|enable_ide
c_func
(paren
id|ide_base
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The EB66+ is very similar to the EB66 except that it does not have&n; * the on-board NCR and Tulip chips.  In the code below, I have used&n; * slot number to refer to the id select line and *not* the slot&n; * number used in the EB66+ documentation.  However, in the table,&n; * I&squot;ve given the slot number, the id select line and the Jxx number&n; * that&squot;s printed on the board.  The interrupt pins from the PCI slots&n; * are wired into 3 interrupt summary registers at 0x804, 0x805 and&n; * 0x806 ISA.&n; *&n; * In the table, -1 means don&squot;t assign an IRQ number.  This is usually&n; * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.&n; */
DECL|function|eb66p_fixup
r_static
r_inline
r_void
id|eb66p_fixup
c_func
(paren
r_void
)paren
(brace
r_char
id|irq_tab
(braket
l_int|5
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 6,  slot 0, J25 */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|14
)brace
comma
multiline_comment|/* IdSel 7,  slot 1, J26 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 8,  SIO         */
(brace
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 9,  slot 2, J27 */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|6
)brace
multiline_comment|/* IdSel 10, slot 3, J28 */
)brace
suffix:semicolon
id|common_fixup
c_func
(paren
l_int|6
comma
l_int|10
comma
l_int|5
comma
id|irq_tab
comma
l_int|0x398
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The AlphaPC64 is very similar to the EB66+ except that its slots&n; * are numbered differently.  In the code below, I have used slot&n; * number to refer to the id select line and *not* the slot number&n; * used in the AlphaPC64 documentation.  However, in the table, I&squot;ve&n; * given the slot number, the id select line and the Jxx number that&squot;s&n; * printed on the board.  The interrupt pins from the PCI slots are&n; * wired into 3 interrupt summary registers at 0x804, 0x805 and 0x806&n; * ISA.&n; *&n; * In the table, -1 means don&squot;t assign an IRQ number.  This is usually&n; * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.&n; */
DECL|function|cabriolet_fixup
r_static
r_inline
r_void
id|cabriolet_fixup
c_func
(paren
r_void
)paren
(brace
r_char
id|irq_tab
(braket
l_int|5
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 5,  slot 2, J21 */
(brace
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 6,  slot 0, J19 */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|14
)brace
comma
multiline_comment|/* IdSel 7,  slot 1, J20 */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 8,  SIO         */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|16
)brace
multiline_comment|/* IdSel 9,  slot 3, J22 */
)brace
suffix:semicolon
id|common_fixup
c_func
(paren
l_int|5
comma
l_int|9
comma
l_int|5
comma
id|irq_tab
comma
l_int|0x398
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Fixup configuration for EB66/EB64+ boards.&n; *&n; * Both these boards use the same interrupt summary scheme.  There are&n; * two 8 bit external summary registers as follows:&n; *&n; * Summary @ 0x26:&n; * Bit      Meaning&n; * 0        Interrupt Line A from slot 0&n; * 1        Interrupt Line A from slot 1&n; * 2        Interrupt Line B from slot 0&n; * 3        Interrupt Line B from slot 1&n; * 4        Interrupt Line C from slot 0&n; * 5        Interrupt line from the two ISA PICs&n; * 6        Tulip (slot &n; * 7        NCR SCSI&n; *&n; * Summary @ 0x27&n; * Bit      Meaning&n; * 0        Interrupt Line C from slot 1&n; * 1        Interrupt Line D from slot 0&n; * 2        Interrupt Line D from slot 1&n; * 3        RAZ&n; * 4        RAZ&n; * 5        RAZ&n; * 6        RAZ&n; * 7        RAZ&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  5       NCR SCSI controller&n; *  6       PCI on board slot 0&n; *  7       PCI on board slot 1&n; *  8       Intel SIO PCI-ISA bridge chip&n; *  9       Tulip - DECchip 21040 ethernet controller&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
DECL|function|eb66_and_eb64p_fixup
r_static
r_inline
r_void
id|eb66_and_eb64p_fixup
c_func
(paren
r_void
)paren
(brace
r_char
id|irq_tab
(braket
l_int|5
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
)brace
comma
multiline_comment|/* IdSel 5,  slot ?, ?? */
(brace
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|9
)brace
comma
multiline_comment|/* IdSel 6,  slot ?, ?? */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|10
)brace
comma
multiline_comment|/* IdSel 7,  slot ?, ?? */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* IdSel 8,  SIO */
(brace
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
)brace
comma
multiline_comment|/* IdSel 9,  TULIP */
)brace
suffix:semicolon
id|common_fixup
c_func
(paren
l_int|5
comma
l_int|9
comma
l_int|5
comma
id|irq_tab
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Fixup configuration for Noname boards (AXPpci33).&n; */
DECL|function|noname_fixup
r_static
r_inline
r_void
id|noname_fixup
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
multiline_comment|/*&n;&t; * The Noname board has 5 PCI slots with each of the 4&n;&t; * interrupt pins routed to different pins on the PCI/ISA&n;&t; * bridge (PIRQ0-PIRQ3).  I don&squot;t have any information yet as&n;&t; * to how INTB, INTC, and INTD get routed (4/12/95,&n;&t; * davidm@cs.arizona.edu).  pirq_tab[0] is a fake entry to&n;&t; * deal with old PCI boards that have the interrupt pin number&n;&t; * hardwired to 0 (meaning that they use the default INTA&n;&t; * line, if they are interrupt driven at all).&n;&t; */
r_static
r_const
r_char
id|pirq_tab
(braket
l_int|7
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|3
comma
l_int|3
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel  6 (53c810) */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel  7 (PCI/ISA bridge) */
(brace
l_int|2
comma
l_int|2
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel  8 (slot closest to ISA) */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel  9 (unused) */
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel 10 (unused) */
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel 11 (slot furthest from ISA) */
(brace
l_int|1
comma
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
comma
multiline_comment|/* idsel 12 (middle slot) */
)brace
suffix:semicolon
multiline_comment|/*&n;&t; * route_tab selects irq routing in PCI/ISA bridge so that:&n;&t; *&t;&t;PIRQ0 -&gt; irq 15&n;&t; *&t;&t;PIRQ1 -&gt; irq  9&n;&t; *&t;&t;PIRQ2 -&gt; irq 10&n;&t; *&t;&t;PIRQ3 -&gt; irq 11&n;&t; */
r_const
r_int
r_int
id|route_tab
op_assign
l_int|0x0b0a090f
suffix:semicolon
r_int
r_char
id|pin
suffix:semicolon
r_int
id|pirq
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|7
comma
l_int|0
)paren
comma
l_int|0x60
comma
id|route_tab
)paren
suffix:semicolon
multiline_comment|/* ensure irq 9, 10, 11, and 15 are level sensitive: */
id|outb
c_func
(paren
(paren
l_int|1
op_lshift
(paren
l_int|9
op_minus
l_int|8
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
l_int|10
op_minus
l_int|8
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
l_int|11
op_minus
l_int|8
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
l_int|15
op_minus
l_int|8
)paren
)paren
comma
l_int|0x4d1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Go through all devices, fixing up irqs as we see fit:&n;&t; */
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
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
l_int|0
op_logical_or
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
template_param
l_int|12
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;noname_set_irq: no dev on bus %d, slot %d!!&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
id|pirq
op_assign
id|pirq_tab
(braket
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_minus
l_int|6
)braket
(braket
id|pin
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pirq
OL
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
(paren
id|route_tab
op_rshift
(paren
l_int|8
op_star
id|pirq
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
macro_line|#if PCI_MODIFY
multiline_comment|/* tell the device: */
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if PCI_MODIFY
(brace
r_int
r_char
id|hostid
suffix:semicolon
multiline_comment|/*&n;&t;&t; * SRM console version X3.9 seems to reset the SCSI&n;&t;&t; * host-id to 0 no matter what console environment&n;&t;&t; * variable pka0_host_id is set to.  Thus, if the&n;&t;&t; * host-id reads out as a zero, we set it to 7.  The&n;&t;&t; * SCSI controller is on the motherboard on bus 0,&n;&t;&t; * slot 6&n;&t;&t; */
r_if
c_cond
(paren
id|pcibios_read_config_byte
c_func
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|6
comma
l_int|0
)paren
comma
l_int|0x84
comma
op_amp
id|hostid
)paren
op_eq
id|PCIBIOS_SUCCESSFUL
op_logical_and
(paren
id|hostid
op_eq
l_int|0
)paren
)paren
(brace
id|pcibios_write_config_byte
c_func
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|6
comma
l_int|0
)paren
comma
l_int|0x84
comma
l_int|7
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* !PCI_MODIFY */
id|enable_ide
c_func
(paren
l_int|0x26e
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup
r_int
r_int
id|pcibios_fixup
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
macro_line|#if PCI_MODIFY
multiline_comment|/*&n;&t; * Scan the tree, allocating PCI memory and I/O space.&n;&t; */
id|layout_bus
c_func
(paren
op_amp
id|pci_root
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Now is the time to do all those dirty little deeds...&n;&t; */
macro_line|#if defined(CONFIG_ALPHA_NONAME)
id|noname_fixup
c_func
(paren
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_CABRIOLET)
id|cabriolet_fixup
c_func
(paren
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_EB66)
id|eb66_and_eb64p_fixup
c_func
(paren
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_EB64P)
id|eb66_and_eb64p_fixup
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#&t;error You must tell me what kind of platform you want.
macro_line|#endif
r_return
id|mem_start
suffix:semicolon
)brace
DECL|function|pcibios_strerror
r_const
r_char
op_star
id|pcibios_strerror
(paren
r_int
id|error
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|error
)paren
(brace
r_case
id|PCIBIOS_SUCCESSFUL
suffix:colon
r_return
l_string|&quot;SUCCESSFUL&quot;
suffix:semicolon
r_case
id|PCIBIOS_FUNC_NOT_SUPPORTED
suffix:colon
r_return
l_string|&quot;FUNC_NOT_SUPPORTED&quot;
suffix:semicolon
r_case
id|PCIBIOS_BAD_VENDOR_ID
suffix:colon
r_return
l_string|&quot;SUCCESSFUL&quot;
suffix:semicolon
r_case
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:colon
r_return
l_string|&quot;DEVICE_NOT_FOUND&quot;
suffix:semicolon
r_case
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:colon
r_return
l_string|&quot;BAD_REGISTER_NUMBER&quot;
suffix:semicolon
r_default
suffix:colon
id|sprintf
(paren
id|buf
comma
l_string|&quot;UNKNOWN RETURN 0x%x&quot;
comma
id|error
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PCI */
eof
