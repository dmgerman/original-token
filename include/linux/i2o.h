macro_line|#ifndef _I2O_H
DECL|macro|_I2O_H
mdefine_line|#define _I2O_H
multiline_comment|/*&n; *&t;Tunable parameters first&n; */
multiline_comment|/* How many different OSM&squot;s are we allowing */
DECL|macro|MAX_I2O_MODULES
mdefine_line|#define MAX_I2O_MODULES&t;&t;64
multiline_comment|/* How many controllers are we allowing */
DECL|macro|MAX_I2O_CONTROLLERS
mdefine_line|#define MAX_I2O_CONTROLLERS&t;32
macro_line|#ifdef __KERNEL__   /* ioctl stuff only thing exported to users */
DECL|macro|I2O_MAX_MANAGERS
mdefine_line|#define I2O_MAX_MANAGERS&t;4
multiline_comment|/*&n; *&t;I2O Interface Objects&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * message structures&n; */
DECL|struct|i2o_message
r_struct
id|i2o_message
(brace
DECL|member|version_size
id|u32
id|version_size
suffix:semicolon
DECL|member|function_addr
id|u32
id|function_addr
suffix:semicolon
DECL|member|initiator_context
id|u32
id|initiator_context
suffix:semicolon
multiline_comment|/* List follows */
)brace
suffix:semicolon
multiline_comment|/**************************************************************************&n; * HRT related constants and structures&n; **************************************************************************/
DECL|macro|I2O_BUS_LOCAL
mdefine_line|#define I2O_BUS_LOCAL&t;0
DECL|macro|I2O_BUS_ISA
mdefine_line|#define I2O_BUS_ISA&t;1
DECL|macro|I2O_BUS_EISA
mdefine_line|#define I2O_BUS_EISA&t;2
DECL|macro|I2O_BUS_MCA
mdefine_line|#define I2O_BUS_MCA&t;3
DECL|macro|I2O_BUS_PCI
mdefine_line|#define I2O_BUS_PCI&t;4
DECL|macro|I2O_BUS_PCMCIA
mdefine_line|#define I2O_BUS_PCMCIA&t;5
DECL|macro|I2O_BUS_NUBUS
mdefine_line|#define I2O_BUS_NUBUS&t;6
DECL|macro|I2O_BUS_CARDBUS
mdefine_line|#define I2O_BUS_CARDBUS&t;7
DECL|macro|I2O_BUS_UNKNOWN
mdefine_line|#define I2O_BUS_UNKNOWN&t;0x80
DECL|struct|_i2o_pci_bus
r_typedef
r_struct
id|_i2o_pci_bus
(brace
DECL|member|PciFunctionNumber
id|u8
id|PciFunctionNumber
suffix:semicolon
DECL|member|PciDeviceNumber
id|u8
id|PciDeviceNumber
suffix:semicolon
DECL|member|PciBusNumber
id|u8
id|PciBusNumber
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|PciVendorID
id|u16
id|PciVendorID
suffix:semicolon
DECL|member|PciDeviceID
id|u16
id|PciDeviceID
suffix:semicolon
DECL|typedef|i2o_pci_bus
DECL|typedef|pi2o_pci_bus
)brace
id|i2o_pci_bus
comma
op_star
id|pi2o_pci_bus
suffix:semicolon
DECL|struct|_i2o_local_bus
r_typedef
r_struct
id|_i2o_local_bus
(brace
DECL|member|LbBaseIOPort
id|u16
id|LbBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|LbBaseMemoryAddress
id|u32
id|LbBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_local_bus
DECL|typedef|pi2o_local_bus
)brace
id|i2o_local_bus
comma
op_star
id|pi2o_local_bus
suffix:semicolon
DECL|struct|_i2o_isa_bus
r_typedef
r_struct
id|_i2o_isa_bus
(brace
DECL|member|IsaBaseIOPort
id|u16
id|IsaBaseIOPort
suffix:semicolon
DECL|member|CSN
id|u8
id|CSN
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|IsaBaseMemoryAddress
id|u32
id|IsaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_isa_bus
DECL|typedef|pi2o_isa_bus
)brace
id|i2o_isa_bus
comma
op_star
id|pi2o_isa_bus
suffix:semicolon
DECL|struct|_i2o_eisa_bus_info
r_typedef
r_struct
id|_i2o_eisa_bus_info
(brace
DECL|member|EisaBaseIOPort
id|u16
id|EisaBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|EisaSlotNumber
id|u8
id|EisaSlotNumber
suffix:semicolon
DECL|member|EisaBaseMemoryAddress
id|u32
id|EisaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_eisa_bus
DECL|typedef|pi2o_eisa_bus
)brace
id|i2o_eisa_bus
comma
op_star
id|pi2o_eisa_bus
suffix:semicolon
DECL|struct|_i2o_mca_bus
r_typedef
r_struct
id|_i2o_mca_bus
(brace
DECL|member|McaBaseIOPort
id|u16
id|McaBaseIOPort
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|McaSlotNumber
id|u8
id|McaSlotNumber
suffix:semicolon
DECL|member|McaBaseMemoryAddress
id|u32
id|McaBaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_mca_bus
DECL|typedef|pi2o_mca_bus
)brace
id|i2o_mca_bus
comma
op_star
id|pi2o_mca_bus
suffix:semicolon
DECL|struct|_i2o_other_bus
r_typedef
r_struct
id|_i2o_other_bus
(brace
DECL|member|BaseIOPort
id|u16
id|BaseIOPort
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|BaseMemoryAddress
id|u32
id|BaseMemoryAddress
suffix:semicolon
DECL|typedef|i2o_other_bus
DECL|typedef|pi2o_other_bus
)brace
id|i2o_other_bus
comma
op_star
id|pi2o_other_bus
suffix:semicolon
DECL|struct|_i2o_hrt_entry
r_typedef
r_struct
id|_i2o_hrt_entry
(brace
DECL|member|adapter_id
id|u32
id|adapter_id
suffix:semicolon
DECL|member|parent_tid
id|u32
id|parent_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:colon
l_int|4
suffix:semicolon
DECL|member|bus_num
id|u32
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bus_type
id|u32
id|bus_type
suffix:colon
l_int|8
suffix:semicolon
r_union
(brace
DECL|member|pci_bus
id|i2o_pci_bus
id|pci_bus
suffix:semicolon
DECL|member|local_bus
id|i2o_local_bus
id|local_bus
suffix:semicolon
DECL|member|isa_bus
id|i2o_isa_bus
id|isa_bus
suffix:semicolon
DECL|member|eisa_bus
id|i2o_eisa_bus
id|eisa_bus
suffix:semicolon
DECL|member|mca_bus
id|i2o_mca_bus
id|mca_bus
suffix:semicolon
DECL|member|other_bus
id|i2o_other_bus
id|other_bus
suffix:semicolon
DECL|member|bus
)brace
id|bus
suffix:semicolon
DECL|typedef|i2o_hrt_entry
DECL|typedef|pi2o_hrt_entry
)brace
id|i2o_hrt_entry
comma
op_star
id|pi2o_hrt_entry
suffix:semicolon
DECL|struct|_i2o_hrt
r_typedef
r_struct
id|_i2o_hrt
(brace
DECL|member|num_entries
id|u16
id|num_entries
suffix:semicolon
DECL|member|entry_len
id|u8
id|entry_len
suffix:semicolon
DECL|member|hrt_version
id|u8
id|hrt_version
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|hrt_entry
id|i2o_hrt_entry
id|hrt_entry
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|i2o_hrt
DECL|typedef|pi2o_hrt
)brace
id|i2o_hrt
comma
op_star
id|pi2o_hrt
suffix:semicolon
DECL|struct|_i2o_lct_entry
r_typedef
r_struct
id|_i2o_lct_entry
(brace
DECL|member|entry_size
id|u32
id|entry_size
suffix:colon
l_int|16
suffix:semicolon
DECL|member|tid
id|u32
id|tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|4
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|device_flags
id|u32
id|device_flags
suffix:semicolon
DECL|member|class_id
id|u32
id|class_id
suffix:semicolon
DECL|member|sub_class
id|u32
id|sub_class
suffix:semicolon
DECL|member|user_tid
id|u32
id|user_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|parent_tid
id|u32
id|parent_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|bios_info
id|u32
id|bios_info
suffix:colon
l_int|8
suffix:semicolon
DECL|member|identity_tag
id|u8
id|identity_tag
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|event_capabilities
id|u32
id|event_capabilities
suffix:semicolon
DECL|typedef|i2o_lct_entry
DECL|typedef|pi2o_lct_entry
)brace
id|i2o_lct_entry
comma
op_star
id|pi2o_lct_entry
suffix:semicolon
DECL|struct|_i2o_lct
r_typedef
r_struct
id|_i2o_lct
(brace
DECL|member|table_size
id|u32
id|table_size
suffix:colon
l_int|16
suffix:semicolon
DECL|member|boot_tid
id|u32
id|boot_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|lct_ver
id|u32
id|lct_ver
suffix:colon
l_int|4
suffix:semicolon
DECL|member|iop_flags
id|u32
id|iop_flags
suffix:semicolon
DECL|member|current_change_ind
id|u32
id|current_change_ind
suffix:semicolon
DECL|member|lct_entry
id|i2o_lct_entry
id|lct_entry
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|i2o_lct
DECL|typedef|pi2o_lct
)brace
id|i2o_lct
comma
op_star
id|pi2o_lct
suffix:semicolon
multiline_comment|/*&n; *&t;Each I2O device entity has one or more of these. There is one&n; *&t;per device. *FIXME* how to handle multiple types on one unit.&n; */
DECL|struct|i2o_device
r_struct
id|i2o_device
(brace
DECL|member|class
r_int
r_class
suffix:semicolon
multiline_comment|/* Block, Net, SCSI etc (from spec) */
DECL|member|subclass
r_int
id|subclass
suffix:semicolon
multiline_comment|/* eth, fddi, tr etc (from spec)   */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* I2O ID assigned by the controller */
DECL|member|parent
r_int
id|parent
suffix:semicolon
multiline_comment|/* Parent device */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Control flags */
DECL|member|i2oversion
r_int
id|i2oversion
suffix:semicolon
multiline_comment|/* I2O version supported. Actually there&n;&t;&t;&t;&t; * should be high and low version */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
multiline_comment|/* Primary user */
DECL|member|owner
r_struct
id|i2o_handler
op_star
id|owner
suffix:semicolon
multiline_comment|/* Management users */
DECL|member|managers
r_struct
id|i2o_handler
op_star
id|managers
(braket
id|I2O_MAX_MANAGERS
)braket
suffix:semicolon
DECL|member|num_managers
r_int
id|num_managers
suffix:semicolon
DECL|member|controller
r_struct
id|i2o_controller
op_star
id|controller
suffix:semicolon
multiline_comment|/* Controlling IOP */
DECL|member|next
r_struct
id|i2o_device
op_star
id|next
suffix:semicolon
multiline_comment|/* Chain */
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* linux /dev name if available */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_I2O_PCI_MODULE
multiline_comment|/*&n; *&t;Resource data for each PCI I2O controller&n; */
DECL|struct|i2o_pci
r_struct
id|i2o_pci
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Each I2O controller has one of these objects&n; */
DECL|struct|i2o_controller
r_struct
id|i2o_controller
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* I2O status */
DECL|member|i2oversion
r_int
id|i2oversion
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|macro|I2O_TYPE_PCI
mdefine_line|#define I2O_TYPE_PCI&t;&t;0x01&t;&t;/* PCI I2O controller */&t;
DECL|member|event_notifer
r_struct
id|notifier_block
op_star
id|event_notifer
suffix:semicolon
multiline_comment|/* Events */
DECL|member|users
id|atomic_t
id|users
suffix:semicolon
DECL|member|devices
r_struct
id|i2o_device
op_star
id|devices
suffix:semicolon
multiline_comment|/* I2O device chain */
DECL|member|next
r_struct
id|i2o_controller
op_star
id|next
suffix:semicolon
multiline_comment|/* Controller chain */
DECL|member|post_port
r_volatile
id|u32
op_star
id|post_port
suffix:semicolon
multiline_comment|/* Messaging ports */
DECL|member|reply_port
r_volatile
id|u32
op_star
id|reply_port
suffix:semicolon
DECL|member|irq_mask
r_volatile
id|u32
op_star
id|irq_mask
suffix:semicolon
multiline_comment|/* Interrupt port */
DECL|member|lct
id|u32
op_star
id|lct
suffix:semicolon
DECL|member|hrt
id|u32
op_star
id|hrt
suffix:semicolon
DECL|member|mem_offset
id|u32
id|mem_offset
suffix:semicolon
multiline_comment|/* MFA offset */
DECL|member|mem_phys
id|u32
id|mem_phys
suffix:semicolon
multiline_comment|/* MFA physical */
DECL|member|priv_mem
id|u32
id|priv_mem
suffix:semicolon
DECL|member|priv_mem_size
id|u32
id|priv_mem_size
suffix:semicolon
DECL|member|priv_io
id|u32
id|priv_io
suffix:semicolon
DECL|member|priv_io_size
id|u32
id|priv_io_size
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
r_union
(brace
multiline_comment|/* Bus information */
DECL|member|pci
r_struct
id|i2o_pci
id|pci
suffix:semicolon
DECL|member|bus
)brace
id|bus
suffix:semicolon
multiline_comment|/* Bus specific destructor */
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
multiline_comment|/* Bus specific attach/detach */
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Bus specific initiator */
DECL|member|unbind
r_int
(paren
op_star
id|unbind
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
DECL|member|page_frame
r_void
op_star
id|page_frame
suffix:semicolon
multiline_comment|/* Message buffers */
DECL|member|inbound_size
r_int
id|inbound_size
suffix:semicolon
multiline_comment|/* Inbound queue size */
)brace
suffix:semicolon
DECL|struct|i2o_handler
r_struct
id|i2o_handler
(brace
DECL|member|reply
r_void
(paren
op_star
id|reply
)paren
(paren
r_struct
id|i2o_handler
op_star
comma
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_message
op_star
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
multiline_comment|/* Low 8 bits of the transaction info */
DECL|member|class
id|u32
r_class
suffix:semicolon
multiline_comment|/* I2O classes that this driver handles */
multiline_comment|/* User data follows */
)brace
suffix:semicolon
macro_line|#ifdef MODULE
multiline_comment|/*&n; * Used by bus specific modules to communicate with the core&n; *&n; * This is needed because the bus modules cannot make direct&n; * calls to the core as this results in the i2o_bus_specific_module&n; * being dependent on the core, not the otherway around.&n; * In that case, a &squot;modprobe i2o_lan&squot; loads i2o_core &amp; i2o_lan,&n; * but _not_ i2o_pci...which makes the whole thing pretty useless :)&n; *&n; */
DECL|struct|i2o_core_func_table
r_struct
id|i2o_core_func_table
(brace
DECL|member|install
r_int
(paren
op_star
id|install
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_struct
id|i2o_controller
op_star
DECL|member|find
(paren
op_star
id|find
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|unlock
r_void
(paren
op_star
id|unlock
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|run_queue
r_void
(paren
op_star
id|run_queue
)paren
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
DECL|member|delete
r_int
(paren
op_star
r_delete
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Messenger inlines&n; */
DECL|function|I2O_POST_READ32
r_extern
r_inline
id|u32
id|I2O_POST_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;post_port
suffix:semicolon
)brace
DECL|function|I2O_POST_WRITE32
r_extern
r_inline
r_void
id|I2O_POST_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;post_port
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|I2O_REPLY_READ32
r_extern
r_inline
id|u32
id|I2O_REPLY_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;reply_port
suffix:semicolon
)brace
DECL|function|I2O_REPLY_WRITE32
r_extern
r_inline
r_void
id|I2O_REPLY_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;reply_port
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|I2O_IRQ_READ32
r_extern
r_inline
id|u32
id|I2O_IRQ_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;irq_mask
suffix:semicolon
)brace
DECL|function|I2O_IRQ_WRITE32
r_extern
r_inline
r_void
id|I2O_IRQ_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;irq_mask
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|i2o_post_message
r_extern
r_inline
r_void
id|i2o_post_message
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
)paren
(brace
multiline_comment|/* The second line isnt spurious - thats forcing PCI posting */
id|I2O_POST_WRITE32
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
(paren
r_void
)paren
id|I2O_IRQ_READ32
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|i2o_flush_reply
r_extern
r_inline
r_void
id|i2o_flush_reply
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
)paren
(brace
id|I2O_REPLY_WRITE32
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
)brace
DECL|variable|i2o_controller_chain
r_struct
id|i2o_controller
op_star
id|i2o_controller_chain
suffix:semicolon
r_extern
r_int
id|i2o_quiesce_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_clear_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_install_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_delete_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_activate_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_unlock_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|i2o_controller
op_star
id|i2o_find_controller
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_num_controllers
suffix:semicolon
r_extern
r_int
id|i2o_install_handler
c_func
(paren
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_remove_handler
c_func
(paren
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_install_device
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_delete_device
c_func
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_claim_device
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|i2o_release_device
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|i2o_post_this
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
id|u32
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_post_wait
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
id|u32
op_star
comma
r_int
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_issue_claim
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|i2o_query_scalar
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_set_scalar
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_query_table
c_func
(paren
r_int
comma
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_clear_table
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_row_add_table
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_row_delete_table
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_run_queue
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_report_status
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|i2o_get_class_name
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;I2O classes / subclasses&n; */
multiline_comment|/*  Class ID and Code Assignments&n; *  (LCT.ClassID.Version field)&n; */
DECL|macro|I2O_CLASS_VERSION_10
mdefine_line|#define    I2O_CLASS_VERSION_10                        0x00
DECL|macro|I2O_CLASS_VERSION_11
mdefine_line|#define    I2O_CLASS_VERSION_11                        0x01
multiline_comment|/*  Class code names&n; *  (from v1.5 Table 6-1 Class Code Assignments.)&n; */
DECL|macro|I2O_CLASS_EXECUTIVE
mdefine_line|#define    I2O_CLASS_EXECUTIVE                         0x000
DECL|macro|I2O_CLASS_DDM
mdefine_line|#define    I2O_CLASS_DDM                               0x001
DECL|macro|I2O_CLASS_RANDOM_BLOCK_STORAGE
mdefine_line|#define    I2O_CLASS_RANDOM_BLOCK_STORAGE              0x010
DECL|macro|I2O_CLASS_SEQUENTIAL_STORAGE
mdefine_line|#define    I2O_CLASS_SEQUENTIAL_STORAGE                0x011
DECL|macro|I2O_CLASS_LAN
mdefine_line|#define    I2O_CLASS_LAN                               0x020
DECL|macro|I2O_CLASS_WAN
mdefine_line|#define    I2O_CLASS_WAN                               0x030
DECL|macro|I2O_CLASS_FIBRE_CHANNEL_PORT
mdefine_line|#define    I2O_CLASS_FIBRE_CHANNEL_PORT                0x040
DECL|macro|I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL
mdefine_line|#define    I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL          0x041
DECL|macro|I2O_CLASS_SCSI_PERIPHERAL
mdefine_line|#define    I2O_CLASS_SCSI_PERIPHERAL                   0x051
DECL|macro|I2O_CLASS_ATE_PORT
mdefine_line|#define    I2O_CLASS_ATE_PORT                          0x060
DECL|macro|I2O_CLASS_ATE_PERIPHERAL
mdefine_line|#define    I2O_CLASS_ATE_PERIPHERAL                    0x061
DECL|macro|I2O_CLASS_FLOPPY_CONTROLLER
mdefine_line|#define    I2O_CLASS_FLOPPY_CONTROLLER                 0x070
DECL|macro|I2O_CLASS_FLOPPY_DEVICE
mdefine_line|#define    I2O_CLASS_FLOPPY_DEVICE                     0x071
DECL|macro|I2O_CLASS_BUS_ADAPTER_PORT
mdefine_line|#define    I2O_CLASS_BUS_ADAPTER_PORT                  0x080
DECL|macro|I2O_CLASS_PEER_TRANSPORT_AGENT
mdefine_line|#define    I2O_CLASS_PEER_TRANSPORT_AGENT              0x090
DECL|macro|I2O_CLASS_PEER_TRANSPORT
mdefine_line|#define    I2O_CLASS_PEER_TRANSPORT                    0x091
multiline_comment|/*  Rest of 0x092 - 0x09f reserved for peer-to-peer classes&n; */
DECL|macro|I2O_CLASS_MATCH_ANYCLASS
mdefine_line|#define    I2O_CLASS_MATCH_ANYCLASS                    0xffffffff
multiline_comment|/*  Subclasses&n; */
DECL|macro|I2O_SUBCLASS_i960
mdefine_line|#define    I2O_SUBCLASS_i960                           0x001
DECL|macro|I2O_SUBCLASS_HDM
mdefine_line|#define    I2O_SUBCLASS_HDM                            0x020
DECL|macro|I2O_SUBCLASS_ISM
mdefine_line|#define    I2O_SUBCLASS_ISM                            0x021
multiline_comment|/* Operation functions */
DECL|macro|I2O_PARAMS_FIELD_GET
mdefine_line|#define I2O_PARAMS_FIELD_GET&t;0x0001
DECL|macro|I2O_PARAMS_LIST_GET
mdefine_line|#define I2O_PARAMS_LIST_GET&t;0x0002
DECL|macro|I2O_PARAMS_MORE_GET
mdefine_line|#define I2O_PARAMS_MORE_GET&t;0x0003
DECL|macro|I2O_PARAMS_SIZE_GET
mdefine_line|#define I2O_PARAMS_SIZE_GET&t;0x0004
DECL|macro|I2O_PARAMS_TABLE_GET
mdefine_line|#define I2O_PARAMS_TABLE_GET&t;0x0005
DECL|macro|I2O_PARAMS_FIELD_SET
mdefine_line|#define I2O_PARAMS_FIELD_SET&t;0x0006
DECL|macro|I2O_PARAMS_LIST_SET
mdefine_line|#define I2O_PARAMS_LIST_SET&t;0x0007
DECL|macro|I2O_PARAMS_ROW_ADD
mdefine_line|#define I2O_PARAMS_ROW_ADD&t;0x0008
DECL|macro|I2O_PARAMS_ROW_DELETE
mdefine_line|#define I2O_PARAMS_ROW_DELETE&t;0x0009
DECL|macro|I2O_PARAMS_TABLE_CLEAR
mdefine_line|#define I2O_PARAMS_TABLE_CLEAR&t;0x000A
multiline_comment|/*&n; *&t;I2O serial number conventions / formats&n; *&t;(circa v1.5)&n; */
DECL|macro|I2O_SNFORMAT_UNKNOWN
mdefine_line|#define    I2O_SNFORMAT_UNKNOWN                        0
DECL|macro|I2O_SNFORMAT_BINARY
mdefine_line|#define    I2O_SNFORMAT_BINARY                         1
DECL|macro|I2O_SNFORMAT_ASCII
mdefine_line|#define    I2O_SNFORMAT_ASCII                          2
DECL|macro|I2O_SNFORMAT_UNICODE
mdefine_line|#define    I2O_SNFORMAT_UNICODE                        3
DECL|macro|I2O_SNFORMAT_LAN48_MAC
mdefine_line|#define    I2O_SNFORMAT_LAN48_MAC                      4
DECL|macro|I2O_SNFORMAT_WAN
mdefine_line|#define    I2O_SNFORMAT_WAN                            5
multiline_comment|/* Plus new in v2.0 (Yellowstone pdf doc)&n; */
DECL|macro|I2O_SNFORMAT_LAN64_MAC
mdefine_line|#define    I2O_SNFORMAT_LAN64_MAC                      6
DECL|macro|I2O_SNFORMAT_DDM
mdefine_line|#define    I2O_SNFORMAT_DDM                            7
DECL|macro|I2O_SNFORMAT_IEEE_REG64
mdefine_line|#define    I2O_SNFORMAT_IEEE_REG64                     8
DECL|macro|I2O_SNFORMAT_IEEE_REG128
mdefine_line|#define    I2O_SNFORMAT_IEEE_REG128                    9
DECL|macro|I2O_SNFORMAT_UNKNOWN2
mdefine_line|#define    I2O_SNFORMAT_UNKNOWN2                       0xff
multiline_comment|/* Transaction Reply Lists (TRL) Control Word structure */
DECL|macro|TRL_SINGLE_FIXED_LENGTH
mdefine_line|#define TRL_SINGLE_FIXED_LENGTH&t;&t;0x00
DECL|macro|TRL_SINGLE_VARIABLE_LENGTH
mdefine_line|#define TRL_SINGLE_VARIABLE_LENGTH&t;0x40
DECL|macro|TRL_MULTIPLE_FIXED_LENGTH
mdefine_line|#define TRL_MULTIPLE_FIXED_LENGTH&t;0x80
multiline_comment|/*&n; *&t;Messaging API values&n; */
DECL|macro|I2O_CMD_ADAPTER_ASSIGN
mdefine_line|#define&t;I2O_CMD_ADAPTER_ASSIGN&t;&t;0xB3
DECL|macro|I2O_CMD_ADAPTER_READ
mdefine_line|#define&t;I2O_CMD_ADAPTER_READ&t;&t;0xB2
DECL|macro|I2O_CMD_ADAPTER_RELEASE
mdefine_line|#define&t;I2O_CMD_ADAPTER_RELEASE&t;&t;0xB5
DECL|macro|I2O_CMD_BIOS_INFO_SET
mdefine_line|#define&t;I2O_CMD_BIOS_INFO_SET&t;&t;0xA5
DECL|macro|I2O_CMD_BOOT_DEVICE_SET
mdefine_line|#define&t;I2O_CMD_BOOT_DEVICE_SET&t;&t;0xA7
DECL|macro|I2O_CMD_CONFIG_VALIDATE
mdefine_line|#define&t;I2O_CMD_CONFIG_VALIDATE&t;&t;0xBB
DECL|macro|I2O_CMD_CONN_SETUP
mdefine_line|#define&t;I2O_CMD_CONN_SETUP&t;&t;0xCA
DECL|macro|I2O_CMD_DDM_DESTROY
mdefine_line|#define&t;I2O_CMD_DDM_DESTROY&t;&t;0xB1
DECL|macro|I2O_CMD_DDM_ENABLE
mdefine_line|#define&t;I2O_CMD_DDM_ENABLE&t;&t;0xD5
DECL|macro|I2O_CMD_DDM_QUIESCE
mdefine_line|#define&t;I2O_CMD_DDM_QUIESCE&t;&t;0xC7
DECL|macro|I2O_CMD_DDM_RESET
mdefine_line|#define&t;I2O_CMD_DDM_RESET&t;&t;0xD9
DECL|macro|I2O_CMD_DDM_SUSPEND
mdefine_line|#define&t;I2O_CMD_DDM_SUSPEND&t;&t;0xAF
DECL|macro|I2O_CMD_DEVICE_ASSIGN
mdefine_line|#define&t;I2O_CMD_DEVICE_ASSIGN&t;&t;0xB7
DECL|macro|I2O_CMD_DEVICE_RELEASE
mdefine_line|#define&t;I2O_CMD_DEVICE_RELEASE&t;&t;0xB9
DECL|macro|I2O_CMD_HRT_GET
mdefine_line|#define&t;I2O_CMD_HRT_GET&t;&t;&t;0xA8
DECL|macro|I2O_CMD_ADAPTER_CLEAR
mdefine_line|#define&t;I2O_CMD_ADAPTER_CLEAR&t;&t;0xBE
DECL|macro|I2O_CMD_ADAPTER_CONNECT
mdefine_line|#define&t;I2O_CMD_ADAPTER_CONNECT&t;&t;0xC9
DECL|macro|I2O_CMD_ADAPTER_RESET
mdefine_line|#define&t;I2O_CMD_ADAPTER_RESET&t;&t;0xBD
DECL|macro|I2O_CMD_LCT_NOTIFY
mdefine_line|#define&t;I2O_CMD_LCT_NOTIFY&t;&t;0xA2
DECL|macro|I2O_CMD_OUTBOUND_INIT
mdefine_line|#define&t;I2O_CMD_OUTBOUND_INIT&t;&t;0xA1
DECL|macro|I2O_CMD_PATH_ENABLE
mdefine_line|#define&t;I2O_CMD_PATH_ENABLE&t;&t;0xD3
DECL|macro|I2O_CMD_PATH_QUIESCE
mdefine_line|#define&t;I2O_CMD_PATH_QUIESCE&t;&t;0xC5
DECL|macro|I2O_CMD_PATH_RESET
mdefine_line|#define&t;I2O_CMD_PATH_RESET&t;&t;0xD7
DECL|macro|I2O_CMD_STATIC_MF_CREATE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_CREATE&t;0xDD
DECL|macro|I2O_CMD_STATIC_MF_RELEASE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_RELEASE&t;0xDF
DECL|macro|I2O_CMD_STATUS_GET
mdefine_line|#define&t;I2O_CMD_STATUS_GET&t;&t;0xA0
DECL|macro|I2O_CMD_SW_DOWNLOAD
mdefine_line|#define&t;I2O_CMD_SW_DOWNLOAD&t;&t;0xA9
DECL|macro|I2O_CMD_SW_UPLOAD
mdefine_line|#define&t;I2O_CMD_SW_UPLOAD&t;&t;0xAB
DECL|macro|I2O_CMD_SW_REMOVE
mdefine_line|#define&t;I2O_CMD_SW_REMOVE&t;&t;0xAD
DECL|macro|I2O_CMD_SYS_ENABLE
mdefine_line|#define&t;I2O_CMD_SYS_ENABLE&t;&t;0xD1
DECL|macro|I2O_CMD_SYS_MODIFY
mdefine_line|#define&t;I2O_CMD_SYS_MODIFY&t;&t;0xC1
DECL|macro|I2O_CMD_SYS_QUIESCE
mdefine_line|#define&t;I2O_CMD_SYS_QUIESCE&t;&t;0xC3
DECL|macro|I2O_CMD_SYS_TAB_SET
mdefine_line|#define&t;I2O_CMD_SYS_TAB_SET&t;&t;0xA3
DECL|macro|I2O_CMD_UTIL_NOP
mdefine_line|#define I2O_CMD_UTIL_NOP&t;&t;0x00
DECL|macro|I2O_CMD_UTIL_ABORT
mdefine_line|#define I2O_CMD_UTIL_ABORT&t;&t;0x01
DECL|macro|I2O_CMD_UTIL_CLAIM
mdefine_line|#define I2O_CMD_UTIL_CLAIM&t;&t;0x09
DECL|macro|I2O_CMD_UTIL_RELEASE
mdefine_line|#define I2O_CMD_UTIL_RELEASE&t;&t;0x0B
DECL|macro|I2O_CMD_UTIL_PARAMS_GET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_GET&t;&t;0x06
DECL|macro|I2O_CMD_UTIL_PARAMS_SET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_SET&t;&t;0x05
DECL|macro|I2O_CMD_UTIL_EVT_REGISTER
mdefine_line|#define I2O_CMD_UTIL_EVT_REGISTER&t;0x13
DECL|macro|I2O_CMD_UTIL_ACK
mdefine_line|#define I2O_CMD_UTIL_ACK&t;&t;0x14
DECL|macro|I2O_CMD_UTIL_CONFIG_DIALOG
mdefine_line|#define I2O_CMD_UTIL_CONFIG_DIALOG&t;0x10
DECL|macro|I2O_CMD_UTIL_DEVICE_RESERVE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RESERVE&t;0x0D
DECL|macro|I2O_CMD_UTIL_DEVICE_RELEASE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RELEASE&t;0x0F
DECL|macro|I2O_CMD_UTIL_LOCK
mdefine_line|#define I2O_CMD_UTIL_LOCK&t;&t;0x17
DECL|macro|I2O_CMD_UTIL_LOCK_RELEASE
mdefine_line|#define I2O_CMD_UTIL_LOCK_RELEASE&t;0x19
DECL|macro|I2O_CMD_UTIL_REPLY_FAULT_NOTIFY
mdefine_line|#define I2O_CMD_UTIL_REPLY_FAULT_NOTIFY&t;0x15
DECL|macro|I2O_CMD_SCSI_EXEC
mdefine_line|#define I2O_CMD_SCSI_EXEC&t;&t;0x81
DECL|macro|I2O_CMD_SCSI_ABORT
mdefine_line|#define I2O_CMD_SCSI_ABORT&t;&t;0x83
DECL|macro|I2O_CMD_SCSI_BUSRESET
mdefine_line|#define I2O_CMD_SCSI_BUSRESET&t;&t;0x27
DECL|macro|I2O_CMD_BLOCK_READ
mdefine_line|#define I2O_CMD_BLOCK_READ&t;&t;0x30
DECL|macro|I2O_CMD_BLOCK_WRITE
mdefine_line|#define I2O_CMD_BLOCK_WRITE&t;&t;0x31
DECL|macro|I2O_CMD_BLOCK_CFLUSH
mdefine_line|#define I2O_CMD_BLOCK_CFLUSH&t;&t;0x37
DECL|macro|I2O_CMD_BLOCK_MLOCK
mdefine_line|#define I2O_CMD_BLOCK_MLOCK&t;&t;0x49
DECL|macro|I2O_CMD_BLOCK_MUNLOCK
mdefine_line|#define I2O_CMD_BLOCK_MUNLOCK&t;&t;0x4B
DECL|macro|I2O_CMD_BLOCK_MMOUNT
mdefine_line|#define I2O_CMD_BLOCK_MMOUNT&t;&t;0x41
DECL|macro|I2O_CMD_BLOCK_MEJECT
mdefine_line|#define I2O_CMD_BLOCK_MEJECT&t;&t;0x43
DECL|macro|I2O_PRIVATE_MSG
mdefine_line|#define I2O_PRIVATE_MSG&t;&t;&t;0xFF
multiline_comment|/*&n; *&t;Init Outbound Q status &n; */
DECL|macro|I2O_CMD_OUTBOUND_INIT_IN_PROGRESS
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_IN_PROGRESS&t;0x01
DECL|macro|I2O_CMD_OUTBOUND_INIT_REJECTED
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_REJECTED&t;&t;0x02
DECL|macro|I2O_CMD_OUTBOUND_INIT_FAILED
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_FAILED&t;&t;0x03
DECL|macro|I2O_CMD_OUTBOUND_INIT_COMPLETE
mdefine_line|#define I2O_CMD_OUTBOUND_INIT_COMPLETE&t;&t;0x04
multiline_comment|/*&n; *&t;I2O Get Status State values &n; */
DECL|macro|ADAPTER_STATE_INITIALIZING
mdefine_line|#define&t;ADAPTER_STATE_INITIALIZING&t;&t;0x01
DECL|macro|ADAPTER_STATE_RESET
mdefine_line|#define&t;ADAPTER_STATE_RESET&t;&t;&t;0x02
DECL|macro|ADAPTER_STATE_HOLD
mdefine_line|#define&t;ADAPTER_STATE_HOLD&t;&t;&t;0x04
DECL|macro|ADAPTER_STATE_READY
mdefine_line|#define ADAPTER_STATE_READY&t;&t;&t;0x05
DECL|macro|ADAPTER_STATE_OPERATIONAL
mdefine_line|#define&t;ADAPTER_STATE_OPERATIONAL&t;&t;0x08
DECL|macro|ADAPTER_STATE_FAILED
mdefine_line|#define&t;ADAPTER_STATE_FAILED&t;&t;&t;0x10
DECL|macro|ADAPTER_STATE_FAULTED
mdefine_line|#define&t;ADAPTER_STATE_FAULTED&t;&t;&t;0x11
multiline_comment|/* I2O API function return values */
DECL|macro|I2O_RTN_NO_ERROR
mdefine_line|#define I2O_RTN_NO_ERROR&t;&t;&t;0
DECL|macro|I2O_RTN_NOT_INIT
mdefine_line|#define I2O_RTN_NOT_INIT&t;&t;&t;1
DECL|macro|I2O_RTN_FREE_Q_EMPTY
mdefine_line|#define I2O_RTN_FREE_Q_EMPTY&t;&t;&t;2
DECL|macro|I2O_RTN_TCB_ERROR
mdefine_line|#define I2O_RTN_TCB_ERROR&t;&t;&t;3
DECL|macro|I2O_RTN_TRANSACTION_ERROR
mdefine_line|#define I2O_RTN_TRANSACTION_ERROR&t;&t;4
DECL|macro|I2O_RTN_ADAPTER_ALREADY_INIT
mdefine_line|#define I2O_RTN_ADAPTER_ALREADY_INIT&t;&t;5
DECL|macro|I2O_RTN_MALLOC_ERROR
mdefine_line|#define I2O_RTN_MALLOC_ERROR&t;&t;&t;6
DECL|macro|I2O_RTN_ADPTR_NOT_REGISTERED
mdefine_line|#define I2O_RTN_ADPTR_NOT_REGISTERED&t;&t;7
DECL|macro|I2O_RTN_MSG_REPLY_TIMEOUT
mdefine_line|#define I2O_RTN_MSG_REPLY_TIMEOUT&t;&t;8
DECL|macro|I2O_RTN_NO_STATUS
mdefine_line|#define I2O_RTN_NO_STATUS&t;&t;&t;9
DECL|macro|I2O_RTN_NO_FIRM_VER
mdefine_line|#define I2O_RTN_NO_FIRM_VER&t;&t;&t;10
DECL|macro|I2O_RTN_NO_LINK_SPEED
mdefine_line|#define&t;I2O_RTN_NO_LINK_SPEED&t;&t;&t;11
multiline_comment|/* Reply message status defines for all messages */
DECL|macro|I2O_REPLY_STATUS_SUCCESS
mdefine_line|#define I2O_REPLY_STATUS_SUCCESS                    &t;0x00
DECL|macro|I2O_REPLY_STATUS_ABORT_DIRTY
mdefine_line|#define I2O_REPLY_STATUS_ABORT_DIRTY                &t;0x01
DECL|macro|I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER     &t;0x02
DECL|macro|I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER&t;&t;0x03
DECL|macro|I2O_REPLY_STATUS_ERROR_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_DIRTY&t;&t;&t;0x04
DECL|macro|I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER&t;&t;0x05
DECL|macro|I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER&t;&t;0x06
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY&t;&t;0x08
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER&t;0x09
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER&t;0x0A
DECL|macro|I2O_REPLY_STATUS_TRANSACTION_ERROR
mdefine_line|#define&t;I2O_REPLY_STATUS_TRANSACTION_ERROR&t;&t;0x0B
DECL|macro|I2O_REPLY_STATUS_PROGRESS_REPORT
mdefine_line|#define&t;I2O_REPLY_STATUS_PROGRESS_REPORT&t;&t;0x80
multiline_comment|/* Status codes and Error Information for Parameter functions */
DECL|macro|I2O_PARAMS_STATUS_SUCCESS
mdefine_line|#define I2O_PARAMS_STATUS_SUCCESS&t;&t;0x00
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_ABORT
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_ABORT&t;&t;0x01
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_CONTINUE
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_CONTINUE   &t;0x02
DECL|macro|I2O_PARAMS_STATUS_BUFFER_FULL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_FULL&t;&t;0x03
DECL|macro|I2O_PARAMS_STATUS_BUFFER_TOO_SMALL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_TOO_SMALL&t;0x04
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNREADABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNREADABLE&t;0x05
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNWRITEABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNWRITEABLE&t;0x06
DECL|macro|I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS
mdefine_line|#define I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS&t;0x07
DECL|macro|I2O_PARAMS_STATUS_INVALID_GROUP_ID
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_GROUP_ID&t;0x08
DECL|macro|I2O_PARAMS_STATUS_INVALID_OPERATION
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_OPERATION&t;0x09
DECL|macro|I2O_PARAMS_STATUS_NO_KEY_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_KEY_FIELD&t;&t;0x0A
DECL|macro|I2O_PARAMS_STATUS_NO_SUCH_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_SUCH_FIELD&t;&t;0x0B
DECL|macro|I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP
mdefine_line|#define I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP&t;0x0C
DECL|macro|I2O_PARAMS_STATUS_OPERATION_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_OPERATION_ERROR&t;0x0D
DECL|macro|I2O_PARAMS_STATUS_SCALAR_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_SCALAR_ERROR&t;&t;0x0E
DECL|macro|I2O_PARAMS_STATUS_TABLE_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_TABLE_ERROR&t;&t;0x0F
DECL|macro|I2O_PARAMS_STATUS_WRONG_GROUP_TYPE
mdefine_line|#define I2O_PARAMS_STATUS_WRONG_GROUP_TYPE&t;0x10
multiline_comment|/* DetailedStatusCode defines for Executive, DDM, Util and Transaction error&n; * messages: Table 3-2 Detailed Status Codes.*/
DECL|macro|I2O_DSC_SUCCESS
mdefine_line|#define I2O_DSC_SUCCESS                        0x0000
DECL|macro|I2O_DSC_BAD_KEY
mdefine_line|#define I2O_DSC_BAD_KEY                        0x0002
DECL|macro|I2O_DSC_TCL_ERROR
mdefine_line|#define I2O_DSC_TCL_ERROR                      0x0003
DECL|macro|I2O_DSC_REPLY_BUFFER_FULL
mdefine_line|#define I2O_DSC_REPLY_BUFFER_FULL              0x0004
DECL|macro|I2O_DSC_NO_SUCH_PAGE
mdefine_line|#define I2O_DSC_NO_SUCH_PAGE                   0x0005
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_SOFT
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_SOFT     0x0006
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_HARD
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_HARD     0x0007
DECL|macro|I2O_DSC_CHAIN_BUFFER_TOO_LARGE
mdefine_line|#define I2O_DSC_CHAIN_BUFFER_TOO_LARGE         0x0009
DECL|macro|I2O_DSC_UNSUPPORTED_FUNCTION
mdefine_line|#define I2O_DSC_UNSUPPORTED_FUNCTION           0x000A
DECL|macro|I2O_DSC_DEVICE_LOCKED
mdefine_line|#define I2O_DSC_DEVICE_LOCKED                  0x000B
DECL|macro|I2O_DSC_DEVICE_RESET
mdefine_line|#define I2O_DSC_DEVICE_RESET                   0x000C
DECL|macro|I2O_DSC_INAPPROPRIATE_FUNCTION
mdefine_line|#define I2O_DSC_INAPPROPRIATE_FUNCTION         0x000D
DECL|macro|I2O_DSC_INVALID_INITIATOR_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_INITIATOR_ADDRESS      0x000E
DECL|macro|I2O_DSC_INVALID_MESSAGE_FLAGS
mdefine_line|#define I2O_DSC_INVALID_MESSAGE_FLAGS          0x000F
DECL|macro|I2O_DSC_INVALID_OFFSET
mdefine_line|#define I2O_DSC_INVALID_OFFSET                 0x0010
DECL|macro|I2O_DSC_INVALID_PARAMETER
mdefine_line|#define I2O_DSC_INVALID_PARAMETER              0x0011
DECL|macro|I2O_DSC_INVALID_REQUEST
mdefine_line|#define I2O_DSC_INVALID_REQUEST                0x0012
DECL|macro|I2O_DSC_INVALID_TARGET_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_TARGET_ADDRESS         0x0013
DECL|macro|I2O_DSC_MESSAGE_TOO_LARGE
mdefine_line|#define I2O_DSC_MESSAGE_TOO_LARGE              0x0014
DECL|macro|I2O_DSC_MESSAGE_TOO_SMALL
mdefine_line|#define I2O_DSC_MESSAGE_TOO_SMALL              0x0015
DECL|macro|I2O_DSC_MISSING_PARAMETER
mdefine_line|#define I2O_DSC_MISSING_PARAMETER              0x0016
DECL|macro|I2O_DSC_TIMEOUT
mdefine_line|#define I2O_DSC_TIMEOUT                        0x0017
DECL|macro|I2O_DSC_UNKNOWN_ERROR
mdefine_line|#define I2O_DSC_UNKNOWN_ERROR                  0x0018
DECL|macro|I2O_DSC_UNKNOWN_FUNCTION
mdefine_line|#define I2O_DSC_UNKNOWN_FUNCTION               0x0019
DECL|macro|I2O_DSC_UNSUPPORTED_VERSION
mdefine_line|#define I2O_DSC_UNSUPPORTED_VERSION            0x001A
DECL|macro|I2O_DSC_DEVICE_BUSY
mdefine_line|#define I2O_DSC_DEVICE_BUSY                    0x001B
DECL|macro|I2O_DSC_DEVICE_NOT_AVAILABLE
mdefine_line|#define I2O_DSC_DEVICE_NOT_AVAILABLE           0x001C
multiline_comment|/* Device Claim Types */
DECL|macro|I2O_CLAIM_PRIMARY
mdefine_line|#define&t;I2O_CLAIM_PRIMARY&t;&t;&t;&t;&t;&t;0x01000000
DECL|macro|I2O_CLAIM_MANAGEMENT
mdefine_line|#define&t;I2O_CLAIM_MANAGEMENT&t;&t;&t;&t;&t;0x02000000
DECL|macro|I2O_CLAIM_AUTHORIZED
mdefine_line|#define&t;I2O_CLAIM_AUTHORIZED&t;&t;&t;&t;&t;0x03000000
DECL|macro|I2O_CLAIM_SECONDARY
mdefine_line|#define&t;I2O_CLAIM_SECONDARY&t;&t;&t;&t;&t;0x04000000
multiline_comment|/* Message header defines for VersionOffset */
DECL|macro|I2OVER15
mdefine_line|#define I2OVER15&t;0x0001
DECL|macro|I2OVER20
mdefine_line|#define I2OVER20&t;0x0002
multiline_comment|/* Default is 1.5, FIXME: Need support for both 1.5 and 2.0 */
DECL|macro|I2OVERSION
mdefine_line|#define I2OVERSION&t;I2OVER15
DECL|macro|SGL_OFFSET_0
mdefine_line|#define SGL_OFFSET_0    I2OVERSION
DECL|macro|SGL_OFFSET_4
mdefine_line|#define SGL_OFFSET_4    (0x0040 | I2OVERSION)
DECL|macro|SGL_OFFSET_5
mdefine_line|#define SGL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|SGL_OFFSET_6
mdefine_line|#define SGL_OFFSET_6    (0x0060 | I2OVERSION)
DECL|macro|SGL_OFFSET_7
mdefine_line|#define SGL_OFFSET_7    (0x0070 | I2OVERSION)
DECL|macro|SGL_OFFSET_8
mdefine_line|#define SGL_OFFSET_8    (0x0080 | I2OVERSION)
DECL|macro|SGL_OFFSET_9
mdefine_line|#define SGL_OFFSET_9    (0x0090 | I2OVERSION)
DECL|macro|SGL_OFFSET_10
mdefine_line|#define SGL_OFFSET_10   (0x00A0 | I2OVERSION)
DECL|macro|TRL_OFFSET_5
mdefine_line|#define TRL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|TRL_OFFSET_6
mdefine_line|#define TRL_OFFSET_6    (0x0060 | I2OVERSION)
multiline_comment|/* msg header defines for MsgFlags */
DECL|macro|MSG_STATIC
mdefine_line|#define MSG_STATIC&t;0x0100
DECL|macro|MSG_64BIT_CNTXT
mdefine_line|#define MSG_64BIT_CNTXT&t;0x0200
DECL|macro|MSG_MULTI_TRANS
mdefine_line|#define MSG_MULTI_TRANS&t;0x1000
DECL|macro|MSG_FAIL
mdefine_line|#define MSG_FAIL&t;0x2000
DECL|macro|MSG_LAST
mdefine_line|#define MSG_LAST&t;0x4000
DECL|macro|MSG_REPLY
mdefine_line|#define MSG_REPLY&t;0x8000
multiline_comment|/* minimum size msg */
DECL|macro|THREE_WORD_MSG_SIZE
mdefine_line|#define THREE_WORD_MSG_SIZE&t;0x00030000
DECL|macro|FOUR_WORD_MSG_SIZE
mdefine_line|#define FOUR_WORD_MSG_SIZE&t;0x00040000
DECL|macro|FIVE_WORD_MSG_SIZE
mdefine_line|#define FIVE_WORD_MSG_SIZE&t;0x00050000
DECL|macro|SIX_WORD_MSG_SIZE
mdefine_line|#define SIX_WORD_MSG_SIZE&t;0x00060000
DECL|macro|SEVEN_WORD_MSG_SIZE
mdefine_line|#define SEVEN_WORD_MSG_SIZE&t;0x00070000
DECL|macro|EIGHT_WORD_MSG_SIZE
mdefine_line|#define EIGHT_WORD_MSG_SIZE&t;0x00080000
DECL|macro|NINE_WORD_MSG_SIZE
mdefine_line|#define NINE_WORD_MSG_SIZE&t;0x00090000
DECL|macro|TEN_WORD_MSG_SIZE
mdefine_line|#define TEN_WORD_MSG_SIZE&t;0x000A0000
DECL|macro|I2O_MESSAGE_SIZE
mdefine_line|#define I2O_MESSAGE_SIZE(x)&t;((x)&lt;&lt;16)
multiline_comment|/* Special TID Assignments */
DECL|macro|ADAPTER_TID
mdefine_line|#define ADAPTER_TID&t;&t;0
DECL|macro|HOST_TID
mdefine_line|#define HOST_TID&t;&t;1
DECL|macro|MSG_FRAME_SIZE
mdefine_line|#define MSG_FRAME_SIZE&t;&t;128
DECL|macro|NMBR_MSG_FRAMES
mdefine_line|#define NMBR_MSG_FRAMES&t;&t;128
DECL|macro|MSG_POOL_SIZE
mdefine_line|#define MSG_POOL_SIZE&t;&t;16384
DECL|macro|I2O_POST_WAIT_OK
mdefine_line|#define I2O_POST_WAIT_OK&t;1
DECL|macro|I2O_POST_WAIT_TIMEOUT
mdefine_line|#define I2O_POST_WAIT_TIMEOUT&t;-ETIMEDOUT
macro_line|#endif /* __KERNEL__ */
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/*&n; * I2O Control IOCTLs and structures&n; */
DECL|macro|I2O_MAGIC_NUMBER
mdefine_line|#define I2O_MAGIC_NUMBER&t;&squot;i&squot;
DECL|macro|I2OGETIOPS
mdefine_line|#define I2OGETIOPS&t;&t;_IO(I2O_MAGIC_NUMBER,0)
DECL|macro|I2OHRTGET
mdefine_line|#define I2OHRTGET&t;&t;_IO(I2O_MAGIC_NUMBER,1)
DECL|macro|I2OLCTGET
mdefine_line|#define I2OLCTGET&t;&t;_IO(I2O_MAGIC_NUMBER,2)
DECL|macro|I2OPARMSET
mdefine_line|#define I2OPARMSET&t;&t;_IO(I2O_MAGIC_NUMBER,3)
DECL|macro|I2OPARMGET
mdefine_line|#define I2OPARMGET&t;&t;_IO(I2O_MAGIC_NUMBER,4)
DECL|macro|I2OSWDL
mdefine_line|#define I2OSWDL&t;&t;&t;_IO(I2O_MAGIC_NUMBER,5)
DECL|macro|I2OSWUL
mdefine_line|#define I2OSWUL&t;&t;&t;_IO(I2O_MAGIC_NUMBER,6)
DECL|macro|I2OSWDEL
mdefine_line|#define I2OSWDEL&t;&t;_IO(I2O_MAGIC_NUMBER,7)
DECL|macro|I2OHTML
mdefine_line|#define I2OHTML&t;&t;&t;_IO(I2O_MAGIC_NUMBER,8)
multiline_comment|/* On hold until we figure this out&n;#define I2OEVTREG&t;&t;_IO(I2O_MAGIC_NUMBER,9)&n;#define I2OEVTCLR&t;&t;_IO(I2O_MAGIC_NUMBER,10)&n;#define I2OEVTGET&t;&t;_IO(I2O_MAGIC_NUMBER,11)&n; */
DECL|struct|i2o_cmd_hrtlct
r_struct
id|i2o_cmd_hrtlct
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Buffer for result */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Buffer length in bytes */
)brace
suffix:semicolon
DECL|struct|i2o_cmd_psetget
r_struct
id|i2o_cmd_psetget
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|tid
r_int
r_int
id|tid
suffix:semicolon
multiline_comment|/* Target device TID */
DECL|member|opbuf
r_void
op_star
id|opbuf
suffix:semicolon
multiline_comment|/* Operation List buffer */
DECL|member|oplen
r_int
r_int
id|oplen
suffix:semicolon
multiline_comment|/* Operation List buffer length in bytes */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Result List buffer */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Result List buffer length in bytes */
)brace
suffix:semicolon
DECL|struct|i2o_sw_xfer
r_struct
id|i2o_sw_xfer
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|dl_flags
r_int
r_char
id|dl_flags
suffix:semicolon
multiline_comment|/* DownLoadFlags field */
DECL|member|sw_type
r_int
r_char
id|sw_type
suffix:semicolon
multiline_comment|/* Software type */
DECL|member|sw_id
r_int
r_int
id|sw_id
suffix:semicolon
multiline_comment|/* Software ID */
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
multiline_comment|/* Pointer to software buffer */
DECL|member|swlen
r_int
r_int
op_star
id|swlen
suffix:semicolon
multiline_comment|/* Length of software data */
DECL|member|maxfrag
r_int
r_int
op_star
id|maxfrag
suffix:semicolon
multiline_comment|/* Maximum fragment count */
DECL|member|curfrag
r_int
r_int
op_star
id|curfrag
suffix:semicolon
multiline_comment|/* Current fragment count */
)brace
suffix:semicolon
DECL|struct|i2o_html
r_struct
id|i2o_html
(brace
DECL|member|iop
r_int
r_int
id|iop
suffix:semicolon
multiline_comment|/* IOP unit number */
DECL|member|tid
r_int
r_int
id|tid
suffix:semicolon
multiline_comment|/* Target device ID */
DECL|member|page
r_int
r_int
id|page
suffix:semicolon
multiline_comment|/* HTML page */
DECL|member|resbuf
r_void
op_star
id|resbuf
suffix:semicolon
multiline_comment|/* Buffer for reply HTML page */
DECL|member|reslen
r_int
r_int
op_star
id|reslen
suffix:semicolon
multiline_comment|/* Length in bytes of reply buffer */
DECL|member|qbuf
r_void
op_star
id|qbuf
suffix:semicolon
multiline_comment|/* Pointer to HTTP query string */
DECL|member|qlen
r_int
r_int
id|qlen
suffix:semicolon
multiline_comment|/* Length in bytes of query string buffer */
)brace
suffix:semicolon
macro_line|#endif
eof
