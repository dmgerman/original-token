multiline_comment|/*&n; *&t;Find I2O capable controllers on the PCI bus, and register/install&n; *&t;them with the I2O layer&n; *&n; *&t;(C) Copyright 1999   Red Hat Software&n; *&t;&n; *&t;Written by Alan Cox, Building Number Three Ltd&n; * &t;Modified by Deepak Saxena &lt;deepak@plexity.net&gt;&n; * &t;Modified by Boji T Kannanthanam &lt;boji.t.kannanthanam@intel.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; * &t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;TODO:&n; *&t;&t;Support polled I2O PCI controllers. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2o.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_MTRR
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#endif 
singleline_comment|// CONFIG_MTRR
macro_line|#ifdef MODULE
multiline_comment|/*&n; * Core function table&n; * See &lt;include/linux/i2o.h&gt; for an explanation&n; */
DECL|variable|core
r_static
r_struct
id|i2o_core_func_table
op_star
id|core
suffix:semicolon
multiline_comment|/* Core attach function */
r_extern
r_int
id|i2o_pci_core_attach
c_func
(paren
r_struct
id|i2o_core_func_table
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_pci_core_detach
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
multiline_comment|/*&n; *&t;Free bus specific resources&n; */
DECL|function|i2o_pci_dispose
r_static
r_void
id|i2o_pci_dispose
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;bus.pci.irq
OG
l_int|0
)paren
(brace
id|free_irq
c_func
(paren
id|c-&gt;bus.pci.irq
comma
id|c
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
(paren
id|u8
op_star
)paren
id|c-&gt;post_port
)paren
op_minus
l_int|0x40
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
r_if
c_cond
(paren
id|c-&gt;bus.pci.mtrr_reg0
OG
l_int|0
)paren
(brace
id|mtrr_del
c_func
(paren
id|c-&gt;bus.pci.mtrr_reg0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;bus.pci.mtrr_reg1
OG
l_int|0
)paren
(brace
id|mtrr_del
c_func
(paren
id|c-&gt;bus.pci.mtrr_reg1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;No real bus specific handling yet (note that later we will&n; *&t;need to &squot;steal&squot; PCI devices on i960 mainboards)&n; */
DECL|function|i2o_pci_bind
r_static
r_int
id|i2o_pci_bind
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_struct
id|i2o_device
op_star
id|dev
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2o_pci_unbind
r_static
r_int
id|i2o_pci_unbind
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_struct
id|i2o_device
op_star
id|dev
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Bus specific enable/disable functions&n; */
DECL|function|i2o_pci_enable
r_static
r_void
id|i2o_pci_enable
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0
)paren
suffix:semicolon
id|c-&gt;enabled
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|i2o_pci_disable
r_static
r_void
id|i2o_pci_disable
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|c-&gt;enabled
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Bus specific interrupt handler&n; */
DECL|function|i2o_pci_interrupt
r_static
r_void
id|i2o_pci_interrupt
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
id|r
)paren
(brace
r_struct
id|i2o_controller
op_star
id|c
op_assign
id|dev_id
suffix:semicolon
macro_line|#ifdef MODULE
id|core
op_member_access_from_pointer
id|run_queue
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#else
id|i2o_run_queue
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
)brace
multiline_comment|/*&n; *&t;Install a PCI (or in theory AGP) i2o controller&n; *&n; * TODO: Add support for polled controllers&n; */
DECL|function|i2o_pci_install
r_int
id|__init
id|i2o_pci_install
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|i2o_controller
op_star
id|c
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2o_controller
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|u8
op_star
id|mem
suffix:semicolon
id|u32
id|memptr
op_assign
l_int|0
suffix:semicolon
id|u32
id|size
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: Insufficient memory to add controller.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|c
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Skip I/O spaces */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|i
)paren
op_amp
id|IORESOURCE_IO
)paren
)paren
(brace
id|memptr
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|6
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: I2O controller has no memory regions defined.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|size
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_minus
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Map the I2O controller */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o: PCI I2O controller at 0x%08X size=%d&bslash;n&quot;
comma
id|memptr
comma
id|size
)paren
suffix:semicolon
id|mem
op_assign
id|ioremap
c_func
(paren
id|memptr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: Unable to map controller.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|c-&gt;bus.pci.irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|c-&gt;irq_mask
op_assign
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|mem
op_plus
l_int|0x34
)paren
suffix:semicolon
id|c-&gt;post_port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|mem
op_plus
l_int|0x40
)paren
suffix:semicolon
id|c-&gt;reply_port
op_assign
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|mem
op_plus
l_int|0x44
)paren
suffix:semicolon
id|c-&gt;mem_phys
op_assign
id|memptr
suffix:semicolon
id|c-&gt;mem_offset
op_assign
(paren
id|u32
)paren
id|mem
suffix:semicolon
id|c-&gt;destructor
op_assign
id|i2o_pci_dispose
suffix:semicolon
id|c-&gt;bind
op_assign
id|i2o_pci_bind
suffix:semicolon
id|c-&gt;unbind
op_assign
id|i2o_pci_unbind
suffix:semicolon
id|c-&gt;bus_enable
op_assign
id|i2o_pci_enable
suffix:semicolon
id|c-&gt;bus_disable
op_assign
id|i2o_pci_disable
suffix:semicolon
id|c-&gt;type
op_assign
id|I2O_TYPE_PCI
suffix:semicolon
multiline_comment|/* &n;&t; * Enable Write Combining MTRR for IOP&squot;s memory region&n;&t; */
macro_line|#ifdef CONFIG_MTRR
id|c-&gt;bus.pci.mtrr_reg0
op_assign
id|mtrr_add
c_func
(paren
id|c-&gt;mem_phys
comma
id|size
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;* If it is an INTEL i960 I/O processor then set the first 64K to Uncacheable&n;* since the region contains the Messaging unit which shouldn&squot;t be cached.&n;*/
id|c-&gt;bus.pci.mtrr_reg1
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_INTEL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;I2O: MTRR workaround for Intel i960 processor&bslash;n&quot;
)paren
suffix:semicolon
id|c-&gt;bus.pci.mtrr_reg1
op_assign
id|mtrr_add
c_func
(paren
id|c-&gt;mem_phys
comma
l_int|65536
comma
id|MTRR_TYPE_UNCACHABLE
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;bus.pci.mtrr_reg1
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o_pci: Error in setting MTRR_TYPE_UNCACHABLE&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|i
op_assign
id|core
op_member_access_from_pointer
id|install
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#else
id|i
op_assign
id|i2o_install_controller
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: Unable to install controller.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|c-&gt;bus.pci.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;bus.pci.irq
)paren
(brace
id|i
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|i2o_pci_interrupt
comma
id|SA_SHIRQ
comma
id|c-&gt;name
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to allocate interrupt %d.&bslash;n&quot;
comma
id|c-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|c-&gt;bus.pci.irq
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef MODULE
id|core
op_member_access_from_pointer
r_delete
(paren
id|c
)paren
suffix:semicolon
macro_line|#else
id|i2o_delete_controller
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#endif /* MODULE */&t;
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Installed at IRQ%d&bslash;n&quot;
comma
id|c-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0x0
)paren
suffix:semicolon
id|c-&gt;enabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2o_pci_scan
r_int
id|__init
id|i2o_pci_scan
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
id|count
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o: Checking for PCI I2O controllers...&bslash;n&quot;
)paren
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
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_INTELLIGENT_I2O
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_amp
l_int|0xFF
)paren
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o: I2O Controller found but does not support I2O 1.5 (skipping).&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev
)paren
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o: I2O controller on bus %d at %d.&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|pci_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2o_pci_install
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2o: %d I2O controller%s found and installed.&bslash;n&quot;
comma
id|count
comma
id|count
op_eq
l_int|1
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
)brace
r_return
id|count
ques
c_cond
id|count
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef I2O_HOTPLUG_SUPPORT
multiline_comment|/*&n; * Activate a newly found PCI I2O controller&n; * Not used now, but will be needed in future for&n; * hot plug PCI support&n; */
DECL|function|i2o_pci_activate
r_static
r_void
id|i2o_pci_activate
c_func
(paren
id|i2o_controller
op_star
id|c
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|i2o_controller
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;type
op_eq
id|I2O_TYPE_PCI
)paren
(brace
id|I2O_IRQ_WRITE32
c_func
(paren
id|c
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|core
op_member_access_from_pointer
id|activate
c_func
(paren
id|c
)paren
)paren
macro_line|#else
r_if
c_cond
(paren
id|i2o_activate_controller
c_func
(paren
id|c
)paren
)paren
macro_line|#endif /* MODULE */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Failed to initialize.&bslash;n&quot;
comma
id|c-&gt;name
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|core
op_member_access_from_pointer
id|unlock
c_func
(paren
id|c
)paren
suffix:semicolon
id|core
op_member_access_from_pointer
r_delete
(paren
id|c
)paren
suffix:semicolon
macro_line|#else
id|i2o_unlock_controller
c_func
(paren
id|c
)paren
suffix:semicolon
id|i2o_delete_controller
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#endif
r_continue
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif 
singleline_comment|// I2O_HOTPLUG_SUPPORT
macro_line|#ifdef MODULE
DECL|function|i2o_pci_core_attach
r_int
id|i2o_pci_core_attach
c_func
(paren
r_struct
id|i2o_core_func_table
op_star
id|table
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|core
op_assign
id|table
suffix:semicolon
r_return
id|i2o_pci_scan
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|i2o_pci_core_detach
r_void
id|i2o_pci_core_detach
c_func
(paren
r_void
)paren
(brace
id|core
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux I2O PCI support (c) 1999 Red Hat Software.&bslash;n&quot;
)paren
suffix:semicolon
id|core
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|i2o_pci_core_attach
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_pci_core_attach
)paren
suffix:semicolon
DECL|variable|i2o_pci_core_detach
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_pci_core_detach
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat Software&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2O PCI Interface&quot;
)paren
suffix:semicolon
macro_line|#else
DECL|function|i2o_pci_init
r_void
id|__init
id|i2o_pci_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux I2O PCI support (c) 1999 Red Hat Software.&bslash;n&quot;
)paren
suffix:semicolon
id|i2o_pci_scan
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
