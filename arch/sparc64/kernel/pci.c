multiline_comment|/* $Id: pci.c,v 1.17 2000/09/05 06:49:44 anton Exp $&n; * pci.c: UltraSparc PCI controller support.&n; *&n; * Copyright (C) 1997, 1998, 1999 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1998, 1999 Eddie C. Dost   (ecd@skynet.be)&n; * Copyright (C) 1999 Jakub Jelinek   (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
DECL|variable|pci_memspace_mask
r_int
r_int
id|pci_memspace_mask
op_assign
l_int|0xffffffffUL
suffix:semicolon
macro_line|#ifndef CONFIG_PCI
multiline_comment|/* A &quot;nop&quot; PCI implementation. */
DECL|function|sys_pciconfig_read
id|asmlinkage
r_int
id|sys_pciconfig_read
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_pciconfig_write
id|asmlinkage
r_int
id|sys_pciconfig_write
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* List of all PCI controllers found in the system. */
DECL|variable|pci_controller_lock
id|spinlock_t
id|pci_controller_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pci_controller_root
r_struct
id|pci_controller_info
op_star
id|pci_controller_root
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Each PCI controller found gets a unique index. */
DECL|variable|pci_num_controllers
r_int
id|pci_num_controllers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Given an 8-bit PCI bus number, this yields the&n; * controlling PBM module info.&n; *&n; * Some explanation is in order here.  The Linux APIs for&n; * the PCI subsystem require that the configuration space&n; * types are enough to signify PCI configuration space&n; * accesses correctly.  This gives us 8-bits for the bus&n; * number, however we have multiple PCI controllers on&n; * UltraSparc systems.&n; *&n; * So what we do is give the PCI busses under each controller&n; * a unique portion of the 8-bit PCI bus number space.&n; * Therefore one can obtain the controller from the bus&n; * number.  For example, say PSYCHO PBM-A a subordinate bus&n; * space of 0 to 4, and PBM-B has a space of 0 to 2.  PBM-A&n; * will use 0 to 4, and PBM-B will use 5 to 7.&n; */
DECL|variable|pci_bus2pbm
r_struct
id|pci_pbm_info
op_star
id|pci_bus2pbm
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|pci_highest_busnum
r_int
r_char
id|pci_highest_busnum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* At boot time the user can give the kernel a command&n; * line option which controls if and how PCI devices&n; * are reordered at PCI bus probing time.&n; */
DECL|variable|pci_device_reorder
r_int
id|pci_device_reorder
op_assign
l_int|0
suffix:semicolon
DECL|variable|pci_poke_lock
id|spinlock_t
id|pci_poke_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pci_poke_in_progress
r_volatile
r_int
id|pci_poke_in_progress
suffix:semicolon
DECL|variable|pci_poke_faulted
r_volatile
r_int
id|pci_poke_faulted
suffix:semicolon
multiline_comment|/* Probe for all PCI controllers in the system. */
r_extern
r_void
id|sabre_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|psycho_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_struct
(brace
DECL|member|model_name
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|pci_controller_table
)brace
id|pci_controller_table
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SUNW,sabre&quot;
comma
id|sabre_init
)brace
comma
(brace
l_string|&quot;pci108e,a000&quot;
comma
id|sabre_init
)brace
comma
(brace
l_string|&quot;SUNW,psycho&quot;
comma
id|psycho_init
)brace
comma
(brace
l_string|&quot;pci108e,8000&quot;
comma
id|psycho_init
)brace
)brace
suffix:semicolon
DECL|macro|PCI_NUM_CONTROLLER_TYPES
mdefine_line|#define PCI_NUM_CONTROLLER_TYPES (sizeof(pci_controller_table) / &bslash;&n;&t;&t;&t;&t;  sizeof(pci_controller_table[0]))
DECL|function|pci_controller_init
r_static
r_void
id|pci_controller_init
c_func
(paren
r_char
op_star
id|model_name
comma
r_int
id|namelen
comma
r_int
id|node
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
id|PCI_NUM_CONTROLLER_TYPES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model_name
comma
id|pci_controller_table
(braket
id|i
)braket
dot
id|model_name
comma
id|namelen
)paren
)paren
(brace
id|pci_controller_table
(braket
id|i
)braket
dot
id|init
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: Warning unknown controller, model name [%s]&bslash;n&quot;
comma
id|model_name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Ignoring controller...&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Find each controller in the system, attach and initialize&n; * software state structure for each and link into the&n; * pci_controller_root.  Setup the controller enough such&n; * that bus scanning can be done.&n; */
DECL|function|pci_controller_probe
r_static
r_void
id|pci_controller_probe
c_func
(paren
r_void
)paren
(brace
r_char
id|namebuf
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|node
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Probing for controllers.&bslash;n&quot;
)paren
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;pci&quot;
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;model&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|pci_controller_init
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
r_else
(brace
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;compatible&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|pci_controller_init
c_func
(paren
id|namebuf
comma
id|len
comma
id|node
)paren
suffix:semicolon
)brace
id|node
op_assign
id|prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_break
suffix:semicolon
)brace
)brace
DECL|function|pci_scan_each_controller_bus
r_static
r_void
id|pci_scan_each_controller_bus
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller_info
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|pci_controller_root
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
id|p
op_member_access_from_pointer
id|scan_bus
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Reorder the pci_dev chain, so that onboard devices come first&n; * and then come the pluggable cards.&n; */
DECL|function|pci_reorder_devs
r_static
r_void
id|__init
id|pci_reorder_devs
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pci_onboard
op_assign
op_amp
id|pci_devices
suffix:semicolon
r_struct
id|list_head
op_star
id|walk
op_assign
id|pci_onboard-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|walk
op_ne
id|pci_onboard
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_dev_g
c_func
(paren
id|walk
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|walk_next
op_assign
id|walk-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;irq
op_logical_and
(paren
id|__irq_ino
c_func
(paren
id|pdev-&gt;irq
)paren
op_amp
l_int|0x20
)paren
)paren
(brace
id|list_del
c_func
(paren
id|walk
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|walk
comma
id|pci_onboard
)paren
suffix:semicolon
)brace
id|walk
op_assign
id|walk_next
suffix:semicolon
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
id|pci_controller_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_controller_root
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|pci_scan_each_controller_bus
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_device_reorder
)paren
id|pci_reorder_devs
c_func
(paren
)paren
suffix:semicolon
id|ebus_init
c_func
(paren
)paren
suffix:semicolon
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
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|pcibios_fixup_bus
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
)paren
(brace
)brace
DECL|function|pcibios_update_resource
r_void
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|resource
op_star
id|res1
comma
r_struct
id|resource
op_star
id|res2
comma
r_int
id|index
)paren
(brace
)brace
DECL|function|pcibios_update_irq
r_void
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|irq
)paren
(brace
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
id|pdev
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
DECL|function|pcibios_fixup_pbus_ranges
r_void
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|pranges
)paren
(brace
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
)brace
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_return
l_int|0
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
l_string|&quot;onboardfirst&quot;
)paren
)paren
(brace
id|pci_device_reorder
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;noreorder&quot;
)paren
)paren
(brace
id|pci_device_reorder
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
DECL|function|sys_pciconfig_read
id|asmlinkage
r_int
id|sys_pciconfig_read
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|u8
id|byte
suffix:semicolon
id|u16
id|word
suffix:semicolon
id|u32
id|dword
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|bus
comma
id|dfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
multiline_comment|/* Xfree86 is such a turd, it does not check the&n;&t;&t; * return value and just relies on the buffer being&n;&t;&t; * set to all 1&squot;s to mean &quot;device not present&quot;.&n;&t;&t; */
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|put_user
c_func
(paren
l_int|0xff
comma
(paren
r_int
r_char
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|put_user
c_func
(paren
l_int|0xffff
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|put_user
c_func
(paren
l_int|0xffffffff
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|byte
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|byte
comma
(paren
r_int
r_char
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|word
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|word
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|dword
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|dword
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_pciconfig_write
id|asmlinkage
r_int
id|sys_pciconfig_write
c_func
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|u8
id|byte
suffix:semicolon
id|u16
id|word
suffix:semicolon
id|u32
id|dword
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|bus
comma
id|dfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
multiline_comment|/* See commentary above about Xfree86 */
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|err
op_assign
id|get_user
c_func
(paren
id|byte
comma
(paren
id|u8
op_star
)paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_break
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|byte
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|err
op_assign
id|get_user
c_func
(paren
id|word
comma
(paren
id|u16
op_star
)paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_break
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|err
op_assign
id|get_user
c_func
(paren
id|dword
comma
(paren
id|u32
op_star
)paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_break
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|dword
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif /* !(CONFIG_PCI) */
eof
