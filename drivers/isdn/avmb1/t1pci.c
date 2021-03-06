multiline_comment|/*&n; * $Id: t1pci.c,v 1.13.6.1 2000/11/28 12:02:45 kai Exp $&n; * &n; * Module for AVM T1 PCI-card.&n; * &n; * (c) Copyright 1999 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: t1pci.c,v $&n; * Revision 1.13.6.1  2000/11/28 12:02:45  kai&n; * MODULE_DEVICE_TABLE for 2.4&n; *&n; * Revision 1.13.2.2  2000/11/26 17:47:53  kai&n; * added PCI_DEV_TABLE for 2.4&n; *&n; * Revision 1.13.2.1  2000/11/26 17:14:19  kai&n; * fix device ids&n; * also needs patches to include/linux/pci_ids.h&n; *&n; * Revision 1.13  2000/11/23 20:45:14  kai&n; * fixed module_init/exit stuff&n; * Note: compiled-in kernel doesn&squot;t work pre 2.2.18 anymore.&n; *&n; * Revision 1.12  2000/11/01 14:05:02  calle&n; * - use module_init/module_exit from linux/init.h.&n; * - all static struct variables are initialized with &quot;membername:&quot; now.&n; * - avm_cs.c, let it work with newer pcmcia-cs.&n; *&n; * Revision 1.11  2000/08/08 09:24:19  calle&n; * calls to pci_enable_device surounded by #ifndef COMPAT_HAS_2_2_PCI&n; *&n; * Revision 1.10  2000/07/20 10:21:21  calle&n; * Bugfix: driver will not be unregistered, if not cards were detected.&n; *         this result in an oops in kcapi.c&n; *&n; * Revision 1.9  2000/05/19 15:43:22  calle&n; * added calls to pci_device_start().&n; *&n; * Revision 1.8  2000/05/06 00:52:36  kai&n; * merged changes from kernel tree&n; * fixed timer and net_device-&gt;name breakage&n; *&n; * Revision 1.7  2000/04/07 15:26:55  calle&n; * better error message if cabel not connected or T1 has no power.&n; *&n; * Revision 1.6  2000/04/03 13:29:25  calle&n; * make Tim Waugh happy (module unload races in 2.3.99-pre3).&n; * no real problem there, but now it is much cleaner ...&n; *&n; * Revision 1.5  2000/02/02 18:36:04  calle&n; * - Modules are now locked while init_module is running&n; * - fixed problem with memory mapping if address is not aligned&n; *&n; * Revision 1.4  2000/01/25 14:33:38  calle&n; * - Added Support AVM B1 PCI V4.0 (tested with prototype)&n; *   - splitted up t1pci.c into b1dma.c for common function with b1pciv4&n; *   - support for revision register&n; *&n; * Revision 1.3  1999/11/13 21:27:16  keil&n; * remove KERNELVERSION&n; *&n; * Revision 1.2  1999/11/05 16:38:02  calle&n; * Cleanups before kernel 2.4:&n; * - Changed all messages to use card-&gt;name or driver-&gt;name instead of&n; *   constant string.&n; * - Moved some data from struct avmcard into new struct avmctrl_info.&n; *   Changed all lowlevel capi driver to match the new structur.&n; *&n; * Revision 1.1  1999/10/26 15:31:42  calle&n; * Added driver for T1-PCI card.&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;capicmd.h&quot;
macro_line|#include &quot;capiutil.h&quot;
macro_line|#include &quot;capilli.h&quot;
macro_line|#include &quot;avmcard.h&quot;
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.13.6.1 $&quot;
suffix:semicolon
DECL|macro|CONFIG_T1PCI_DEBUG
macro_line|#undef CONFIG_T1PCI_DEBUG
DECL|macro|CONFIG_T1PCI_POLLDEBUG
macro_line|#undef CONFIG_T1PCI_POLLDEBUG
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|t1pci_pci_tbl
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AVM
comma
id|PCI_DEVICE_ID_AVM_T1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|t1pci_pci_tbl
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth &lt;calle@calle.in-berlin.de&gt;&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|di
r_static
r_struct
id|capi_driver_interface
op_star
id|di
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_remove_ctr
r_static
r_void
id|t1pci_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|di
op_member_access_from_pointer
id|detach_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|card-&gt;mbase
)paren
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|ctrl-&gt;driverdata
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_add_card
r_static
r_int
id|t1pci_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
r_struct
id|capicardparams
op_star
id|p
)paren
(brace
r_int
r_int
id|base
comma
id|page_offset
suffix:semicolon
id|avmcard
op_star
id|card
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|card
op_assign
(paren
id|avmcard
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmcard
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|avmcard
)paren
)paren
suffix:semicolon
id|card-&gt;dma
op_assign
(paren
id|avmcard_dmainfo
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmcard_dmainfo
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;dma
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card-&gt;dma
comma
l_int|0
comma
r_sizeof
(paren
id|avmcard_dmainfo
)paren
)paren
suffix:semicolon
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmctrl_info
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cinfo
comma
l_int|0
comma
r_sizeof
(paren
id|avmctrl_info
)paren
)paren
suffix:semicolon
id|card-&gt;ctrlinfo
op_assign
id|cinfo
suffix:semicolon
id|cinfo-&gt;card
op_assign
id|card
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;t1pci-%x&quot;
comma
id|p-&gt;port
)paren
suffix:semicolon
id|card-&gt;port
op_assign
id|p-&gt;port
suffix:semicolon
id|card-&gt;irq
op_assign
id|p-&gt;irq
suffix:semicolon
id|card-&gt;membase
op_assign
id|p-&gt;membase
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|avm_t1pci
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ports 0x%03x-0x%03x in use.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;port
op_plus
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|base
op_assign
id|card-&gt;membase
op_amp
id|PAGE_MASK
suffix:semicolon
id|page_offset
op_assign
id|card-&gt;membase
op_minus
id|base
suffix:semicolon
id|card-&gt;mbase
op_assign
id|ioremap_nocache
c_func
(paren
id|base
comma
id|page_offset
op_plus
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;mbase
)paren
(brace
id|card-&gt;mbase
op_add_assign
id|page_offset
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: can&squot;t remap memory at 0x%lx&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;membase
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|t1pci_detect
c_func
(paren
id|card
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
OL
l_int|6
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: card at 0x%x, but cabel not connected or T1 has no power (%d)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|card-&gt;mbase
)paren
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|p-&gt;port
comma
id|AVMB1_PORTLEN
comma
id|card-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|b1dma_interrupt
comma
id|SA_SHIRQ
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to get IRQ %d.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|card-&gt;mbase
)paren
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|cinfo-&gt;capi_ctrl
op_assign
id|di
op_member_access_from_pointer
id|attach_ctr
c_func
(paren
id|driver
comma
id|card-&gt;name
comma
id|cinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo-&gt;capi_ctrl
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: attach controller failed.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|card-&gt;mbase
)paren
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|card-&gt;cardnr
op_assign
id|cinfo-&gt;capi_ctrl-&gt;cnr
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|card-&gt;dma-&gt;send_queue
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AVM T1 PCI at i/o %#x, irq %d, mem %#lx&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;membase
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_procinfo
r_static
r_char
op_star
id|t1pci_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo-&gt;infobuf
comma
l_string|&quot;%s %s 0x%x %d 0x%lx&quot;
comma
id|cinfo-&gt;cardname
(braket
l_int|0
)braket
ques
c_cond
id|cinfo-&gt;cardname
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
ques
c_cond
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;port
suffix:colon
l_int|0x0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;irq
suffix:colon
l_int|0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;membase
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|cinfo-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|t1pci_driver
r_static
r_struct
id|capi_driver
id|t1pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;t1pci&quot;
comma
id|revision
suffix:colon
l_string|&quot;0.0&quot;
comma
id|load_firmware
suffix:colon
id|b1dma_load_firmware
comma
id|reset_ctr
suffix:colon
id|b1dma_reset_ctr
comma
id|remove_ctr
suffix:colon
id|t1pci_remove_ctr
comma
id|register_appl
suffix:colon
id|b1dma_register_appl
comma
id|release_appl
suffix:colon
id|b1dma_release_appl
comma
id|send_message
suffix:colon
id|b1dma_send_message
comma
id|procinfo
suffix:colon
id|t1pci_procinfo
comma
id|ctr_read_proc
suffix:colon
id|b1dmactl_read_proc
comma
id|driver_read_proc
suffix:colon
l_int|0
comma
multiline_comment|/* use standard driver_read_proc */
id|add_card
suffix:colon
l_int|0
comma
multiline_comment|/* no add_card function */
)brace
suffix:semicolon
DECL|variable|ncards
r_static
r_int
id|ncards
op_assign
l_int|0
suffix:semicolon
DECL|function|t1pci_init
r_static
r_int
id|__init
id|t1pci_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|t1pci_driver
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|driver-&gt;revision
comma
id|p
op_plus
l_int|1
comma
r_sizeof
(paren
id|driver-&gt;revision
)paren
)paren
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|driver-&gt;revision
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: revision %s&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|driver-&gt;revision
)paren
suffix:semicolon
id|di
op_assign
id|attach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|di
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to attach capi_driver&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
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
id|KERN_ERR
l_string|&quot;%s: no PCI bus present&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AVM
comma
id|PCI_DEVICE_ID_AVM_T1
comma
id|dev
)paren
)paren
)paren
(brace
r_struct
id|capicardparams
id|param
suffix:semicolon
id|param.port
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|param.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|param.membase
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|pci_enable_device
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to enable AVM-T1-PCI at i/o %#x, irq %d, mem %#x err=%d&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
comma
id|retval
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
op_amp
id|t1pci_driver
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PCI BIOS reports AVM-T1-PCI at i/o %#x, irq %d, mem %#x&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
id|retval
op_assign
id|t1pci_add_card
c_func
(paren
id|driver
comma
op_amp
id|param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no AVM-T1-PCI at i/o %#x, irq %d detected, mem %#x&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
op_amp
id|t1pci_driver
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|ncards
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncards
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %d T1-PCI card(s) detected&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|ncards
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: NO T1-PCI card detected&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
op_amp
id|t1pci_driver
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: kernel not compiled with PCI.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
macro_line|#endif
)brace
DECL|function|t1pci_exit
r_static
r_void
id|__exit
id|t1pci_exit
c_func
(paren
r_void
)paren
(brace
id|detach_capi_driver
c_func
(paren
op_amp
id|t1pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|t1pci_init
id|module_init
c_func
(paren
id|t1pci_init
)paren
suffix:semicolon
DECL|variable|t1pci_exit
id|module_exit
c_func
(paren
id|t1pci_exit
)paren
suffix:semicolon
eof
