multiline_comment|/*&n;* cycx_main.c&t;Cyclades Cyclom 2X WAN Link Driver. Main module.&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2000 Arnaldo Carvalho de Melo&n;*&n;* Based on sdlamain.c by Gene Kozin &lt;genek@compuserve.com&gt; &amp;&n;*&t;&t;&t; Jaspreet Singh&t;&lt;jaspreet@sangoma.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 2000/04/02&t;acme&t;&t;dprintk and cycx_debug&n;* &t;&t;&t;&t;module_init/module_exit&n;* 2000/01/21&t;acme&t;&t;rename cyclomx_open to cyclomx_mod_inc_use_count&n;*&t;&t;&t;&t;and cyclomx_close to cyclomx_mod_dec_use_count&n;* 2000/01/08&t;acme&t;&t;cleanup&n;* 1999/11/06&t;acme&t;&t;cycx_down back to life (it needs to be&n;*&t;&t;&t;&t;called to iounmap the dpmbase)&n;* 1999/08/09&t;acme&t;&t;removed references to enable_tx_int&n;*&t;&t;&t;&t;use spinlocks instead of cli/sti in&n;*&t;&t;&t;&t;cyclomx_set_state&n;* 1999/05/19&t;acme&t;&t;works directly linked into the kernel&n;*&t;&t;&t;&t;init_waitqueue_head for 2.3.* kernel&n;* 1999/05/18&t;acme&t;&t;major cleanup (polling not needed), etc&n;* 1998/08/28&t;acme&t;&t;minor cleanup (ioctls for firmware deleted)&n;*&t;&t;&t;&t;queue_task activated&n;* 1998/08/08&t;acme&t;&t;Initial version.&n;*/
macro_line|#include &lt;linux/config.h&gt;&t;/* OS configuration options */
macro_line|#include &lt;linux/stddef.h&gt;&t;/* offsetof(), etc. */
macro_line|#include &lt;linux/errno.h&gt;&t;/* return codes */
macro_line|#include &lt;linux/string.h&gt;&t;/* inline memset(), etc. */
macro_line|#include &lt;linux/malloc.h&gt;&t;/* kmalloc(), kfree() */
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk(), and other useful stuff */
macro_line|#include &lt;linux/module.h&gt;&t;/* support for loadable modules */
macro_line|#include &lt;linux/ioport.h&gt;&t;/* request_region(), release_region() */
macro_line|#include &lt;linux/tqueue.h&gt;&t;/* for kernel task queues */
macro_line|#include &lt;linux/wanrouter.h&gt;&t;/* WAN router definitions */
macro_line|#include &lt;linux/cyclomx.h&gt;&t;/* cyclomx common user API definitions */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* kernel &lt;-&gt; user copy */
macro_line|#include &lt;linux/init.h&gt;         /* __init (when not using as a module) */
multiline_comment|/* Debug */
DECL|variable|cycx_debug
r_int
r_int
id|cycx_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Arnaldo Carvalho de Melo&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Cyclom 2X Sync Card Driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;cyclomx debug level&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Defines &amp; Macros */
DECL|macro|DRV_VERSION
mdefine_line|#define&t;DRV_VERSION&t;0&t;&t;/* version number */
DECL|macro|DRV_RELEASE
mdefine_line|#define&t;DRV_RELEASE&t;7&t;&t;/* release (minor version) number */
DECL|macro|MAX_CARDS
mdefine_line|#define&t;MAX_CARDS&t;1&t;&t;/* max number of adapters */
macro_line|#ifndef&t;CONFIG_CYCLOMX_CARDS&t;&t;/* configurable option */
DECL|macro|CONFIG_CYCLOMX_CARDS
mdefine_line|#define&t;CONFIG_CYCLOMX_CARDS 1
macro_line|#endif
multiline_comment|/* Function Prototypes */
multiline_comment|/* WAN link driver entry points */
r_static
r_int
id|setup
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
r_static
r_int
id|shutdown
(paren
id|wan_device_t
op_star
id|wandev
)paren
suffix:semicolon
r_static
r_int
id|ioctl
(paren
id|wan_device_t
op_star
id|wandev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* Miscellaneous functions */
r_static
r_void
id|cycx_isr
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
suffix:semicolon
multiline_comment|/* Global Data&n; * Note: All data must be explicitly initialized!!!&n; */
multiline_comment|/* private data */
DECL|variable|drvname
r_static
r_char
id|drvname
(braket
)braket
op_assign
l_string|&quot;cyclomx&quot;
suffix:semicolon
DECL|variable|fullname
r_static
r_char
id|fullname
(braket
)braket
op_assign
l_string|&quot;CYCLOM 2X(tm) Sync Card Driver&quot;
suffix:semicolon
DECL|variable|copyright
r_static
r_char
id|copyright
(braket
)braket
op_assign
l_string|&quot;(c) 1998-2000 Arnaldo Carvalho de Melo &quot;
l_string|&quot;&lt;acme@conectiva.com.br&gt;&quot;
suffix:semicolon
DECL|variable|ncards
r_static
r_int
id|ncards
op_assign
id|CONFIG_CYCLOMX_CARDS
suffix:semicolon
DECL|variable|card_array
r_static
id|cycx_t
op_star
id|card_array
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* adapter data space */
multiline_comment|/* Kernel Loadable Module Entry Points */
multiline_comment|/*&n; * Module &squot;insert&squot; entry point.&n; * o print announcement&n; * o allocate adapter data space&n; * o initialize static data&n; * o register all cards with WAN router&n; * o calibrate Cyclom 2X shared memory access delay.&n; *&n; * Return:&t;0&t;Ok&n; *&t;&t;&lt; 0&t;error.&n; * Context:&t;process&n; */
DECL|function|cyclomx_init
r_int
id|__init
id|cyclomx_init
(paren
r_void
)paren
(brace
r_int
id|cnt
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s v%u.%u %s&bslash;n&quot;
comma
id|fullname
comma
id|DRV_VERSION
comma
id|DRV_RELEASE
comma
id|copyright
)paren
suffix:semicolon
multiline_comment|/* Verify number of cards and allocate adapter data space */
id|ncards
op_assign
id|min
c_func
(paren
id|ncards
comma
id|MAX_CARDS
)paren
suffix:semicolon
id|ncards
op_assign
id|max
c_func
(paren
id|ncards
comma
l_int|1
)paren
suffix:semicolon
id|card_array
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|cycx_t
)paren
op_star
id|ncards
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card_array
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|card_array
comma
l_int|0
comma
r_sizeof
(paren
id|cycx_t
)paren
op_star
id|ncards
)paren
suffix:semicolon
multiline_comment|/* Register adapters with WAN router */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|ncards
suffix:semicolon
op_increment
id|cnt
)paren
(brace
id|cycx_t
op_star
id|card
op_assign
op_amp
id|card_array
(braket
id|cnt
)braket
suffix:semicolon
id|wan_device_t
op_star
id|wandev
op_assign
op_amp
id|card-&gt;wandev
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;devname
comma
l_string|&quot;%s%d&quot;
comma
id|drvname
comma
id|cnt
op_plus
l_int|1
)paren
suffix:semicolon
id|wandev-&gt;magic
op_assign
id|ROUTER_MAGIC
suffix:semicolon
id|wandev-&gt;name
op_assign
id|card-&gt;devname
suffix:semicolon
id|wandev
op_member_access_from_pointer
r_private
op_assign
id|card
suffix:semicolon
id|wandev-&gt;setup
op_assign
op_amp
id|setup
suffix:semicolon
id|wandev-&gt;shutdown
op_assign
op_amp
id|shutdown
suffix:semicolon
id|wandev-&gt;ioctl
op_assign
op_amp
id|ioctl
suffix:semicolon
id|err
op_assign
id|register_wan_device
c_func
(paren
id|wandev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: %s registration failed with &quot;
l_string|&quot;error %d!&bslash;n&quot;
comma
id|drvname
comma
id|card-&gt;devname
comma
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cnt
)paren
id|ncards
op_assign
id|cnt
suffix:semicolon
multiline_comment|/* adjust actual number of cards */
r_else
(brace
id|kfree
c_func
(paren
id|card_array
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Module &squot;remove&squot; entry point.&n; * o unregister all adapters from the WAN router&n; * o release all remaining system resources&n; */
DECL|function|cyclomx_cleanup
r_void
id|cyclomx_cleanup
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|ncards
suffix:semicolon
op_increment
id|i
)paren
(brace
id|cycx_t
op_star
id|card
op_assign
op_amp
id|card_array
(braket
id|i
)braket
suffix:semicolon
id|unregister_wan_device
c_func
(paren
id|card-&gt;devname
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|card_array
)paren
suffix:semicolon
)brace
multiline_comment|/* WAN Device Driver Entry Points */
multiline_comment|/*&n; * Setup/configure WAN link driver.&n; * o check adapter state&n; * o make sure firmware is present in configuration&n; * o allocate interrupt vector&n; * o setup Cyclom 2X hardware&n; * o call appropriate routine to perform protocol-specific initialization&n; *&n; * This function is called when router handles ROUTER_SETUP IOCTL. The&n; * configuration structure is in kernel memory (including extended data, if&n; * any).&n; */
DECL|function|setup
r_static
r_int
id|setup
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_conf_t
op_star
id|conf
)paren
(brace
id|cycx_t
op_star
id|card
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|irq
suffix:semicolon
multiline_comment|/* Sanity checks */
r_if
c_cond
(paren
op_logical_neg
id|wandev
op_logical_or
op_logical_neg
id|wandev
op_member_access_from_pointer
r_private
op_logical_or
op_logical_neg
id|conf
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|card
op_assign
id|wandev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|wandev-&gt;state
op_ne
id|WAN_UNCONFIGURED
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;data_size
op_logical_or
op_logical_neg
id|conf-&gt;data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: firmware not found in configuration &quot;
l_string|&quot;data!&bslash;n&quot;
comma
id|wandev-&gt;name
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
id|conf-&gt;irq
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t configure without IRQ!&bslash;n&quot;
comma
id|wandev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Allocate IRQ */
id|irq
op_assign
id|conf-&gt;irq
op_eq
l_int|2
ques
c_cond
l_int|9
suffix:colon
id|conf-&gt;irq
suffix:semicolon
multiline_comment|/* IRQ2 -&gt; IRQ9 */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|cycx_isr
comma
l_int|0
comma
id|wandev-&gt;name
comma
id|card
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t reserve IRQ %d!&bslash;n&quot;
comma
id|wandev-&gt;name
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Configure hardware, load firmware, etc. */
id|memset
c_func
(paren
op_amp
id|card-&gt;hw
comma
l_int|0
comma
r_sizeof
(paren
id|cycxhw_t
)paren
)paren
suffix:semicolon
id|card-&gt;hw.irq
op_assign
id|irq
suffix:semicolon
id|card-&gt;hw.dpmbase
op_assign
id|conf-&gt;maddr
suffix:semicolon
id|card-&gt;hw.dpmsize
op_assign
id|CYCX_WINDOWSIZE
suffix:semicolon
id|card-&gt;hw.fwid
op_assign
id|CFID_X25_2X
suffix:semicolon
id|card-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|init_waitqueue_head
c_func
(paren
op_amp
id|card-&gt;wait_stats
)paren
suffix:semicolon
macro_line|#else
id|card-&gt;wait_stats
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|cycx_setup
c_func
(paren
op_amp
id|card-&gt;hw
comma
id|conf-&gt;data
comma
id|conf-&gt;data_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|free_irq
c_func
(paren
id|irq
comma
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Initialize WAN device data space */
id|wandev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|wandev-&gt;dma
op_assign
id|wandev-&gt;ioport
op_assign
l_int|0
suffix:semicolon
id|wandev-&gt;maddr
op_assign
id|card-&gt;hw.dpmbase
suffix:semicolon
id|wandev-&gt;msize
op_assign
id|card-&gt;hw.dpmsize
suffix:semicolon
id|wandev-&gt;hw_opt
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|wandev-&gt;hw_opt
(braket
l_int|3
)braket
op_assign
id|card-&gt;hw.fwid
suffix:semicolon
multiline_comment|/* Protocol-specific initialization */
r_switch
c_cond
(paren
id|card-&gt;hw.fwid
)paren
(brace
macro_line|#ifdef CONFIG_CYCLOMX_X25
r_case
id|CFID_X25_2X
suffix:colon
id|err
op_assign
id|cyx_init
c_func
(paren
id|card
comma
id|conf
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: this firmware is not supported!&bslash;n&quot;
comma
id|wandev-&gt;name
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|cycx_down
c_func
(paren
op_amp
id|card-&gt;hw
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Shut down WAN link driver. &n; * o shut down adapter hardware&n; * o release system resources.&n; *&n; * This function is called by the router when device is being unregistered or&n; * when it handles ROUTER_DOWN IOCTL.&n; */
DECL|function|shutdown
r_static
r_int
id|shutdown
(paren
id|wan_device_t
op_star
id|wandev
)paren
(brace
id|cycx_t
op_star
id|card
suffix:semicolon
multiline_comment|/* sanity checks */
r_if
c_cond
(paren
op_logical_neg
id|wandev
op_logical_or
op_logical_neg
id|wandev
op_member_access_from_pointer
r_private
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|wandev-&gt;state
op_eq
id|WAN_UNCONFIGURED
)paren
r_return
l_int|0
suffix:semicolon
id|card
op_assign
id|wandev
op_member_access_from_pointer
r_private
suffix:semicolon
id|wandev-&gt;state
op_assign
id|WAN_UNCONFIGURED
suffix:semicolon
id|cycx_down
c_func
(paren
op_amp
id|card-&gt;hw
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: irq %d being freed!&bslash;n&quot;
comma
id|wandev-&gt;name
comma
id|wandev-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|wandev-&gt;irq
comma
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Driver I/O control. &n; * o verify arguments&n; * o perform requested action&n; *&n; * This function is called when router handles one of the reserved user&n; * IOCTLs.  Note that &squot;arg&squot; still points to user address space.&n; *&n; * no reserved ioctls for the cyclom 2x up to now&n; */
DECL|function|ioctl
r_static
r_int
id|ioctl
(paren
id|wan_device_t
op_star
id|wandev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Miscellaneous */
multiline_comment|/*&n; * Cyclom 2X Interrupt Service Routine.&n; * o acknowledge Cyclom 2X hardware interrupt.&n; * o call protocol-specific interrupt service routine, if any.&n; */
DECL|function|cycx_isr
r_static
r_void
id|cycx_isr
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
DECL|macro|card
mdefine_line|#define&t;card&t;((cycx_t*)dev_id)
r_if
c_cond
(paren
op_logical_neg
id|card
op_logical_or
id|card-&gt;wandev.state
op_eq
id|WAN_UNCONFIGURED
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;in_isr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: interrupt re-entrancy on IRQ %d!&bslash;n&quot;
comma
id|card-&gt;devname
comma
id|card-&gt;wandev.irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;isr
)paren
id|card
op_member_access_from_pointer
id|isr
c_func
(paren
id|card
)paren
suffix:semicolon
DECL|macro|card
macro_line|#undef&t;card
)brace
multiline_comment|/*&n; * This routine is called by the protocol-specific modules when network&n; * interface is being open.  The only reason we need this, is because we&n; * have to call MOD_INC_USE_COUNT, but cannot include &squot;module.h&squot; where it&squot;s&n; * defined more than once into the same kernel module.&n; */
DECL|function|cyclomx_mod_inc_use_count
r_void
id|cyclomx_mod_inc_use_count
(paren
id|cycx_t
op_star
id|card
)paren
(brace
op_increment
id|card-&gt;open_cnt
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called by the protocol-specific modules when network&n; * interface is being closed.  The only reason we need this, is because we&n; * have to call MOD_DEC_USE_COUNT, but cannot include &squot;module.h&squot; where it&squot;s&n; * defined more than once into the same kernel module.&n; */
DECL|function|cyclomx_mod_dec_use_count
r_void
id|cyclomx_mod_dec_use_count
(paren
id|cycx_t
op_star
id|card
)paren
(brace
op_decrement
id|card-&gt;open_cnt
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* Set WAN device state.  */
DECL|function|cyclomx_set_state
r_void
id|cyclomx_set_state
(paren
id|cycx_t
op_star
id|card
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|host_cpu_flags
suffix:semicolon
r_char
op_star
id|string_state
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|host_cpu_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;wandev.state
op_ne
id|state
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|WAN_CONNECTED
suffix:colon
id|string_state
op_assign
l_string|&quot;connected!&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAN_DISCONNECTED
suffix:colon
id|string_state
op_assign
l_string|&quot;disconnected!&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: link %s&bslash;n&quot;
comma
id|card-&gt;devname
comma
id|string_state
)paren
suffix:semicolon
id|card-&gt;wandev.state
op_assign
id|state
suffix:semicolon
)brace
id|card-&gt;state_tick
op_assign
id|jiffies
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|host_cpu_flags
)paren
suffix:semicolon
)brace
DECL|variable|cyclomx_init
id|module_init
c_func
(paren
id|cyclomx_init
)paren
suffix:semicolon
DECL|variable|cyclomx_cleanup
id|module_exit
c_func
(paren
id|cyclomx_cleanup
)paren
suffix:semicolon
multiline_comment|/* End */
eof
