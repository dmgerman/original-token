multiline_comment|/*****************************************************************************&n;* wanmain.c&t;WAN Multiprotocol Router Module. Main code.&n;*&n;*&t;&t;This module is completely hardware-independent and provides&n;*&t;&t;the following common services for the WAN Link Drivers:&n;*&t;&t; o WAN device managenment (registering, unregistering)&n;*&t;&t; o Network interface management&n;*&t;&t; o Physical connection management (dial-up, incomming calls)&n;*&t;&t; o Logical connection management (switched virtual circuits)&n;*&t;&t; o Protocol encapsulation/decapsulation&n;*&n;* Author:&t;Gene Kozin&t;&lt;genek@compuserve.com&gt;&n;*&n;* Copyright:&t;(c) 1995-1997 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Dec 27, 1996&t;Gene Kozin&t;Initial version (based on Sangoma&squot;s WANPIPE)&n;* Jan 16, 1997&t;Gene Kozin&t;router_devlist made public&n;* Jan 31, 1997  Alan Cox&t;Hacked it about a bit for 2.1&n;* Jun 27, 1997  Alan Cox&t;realigned with vendor code&n;* Oct 15, 1997  Farhan Thawar   changed wan_encapsulate to add a pad byte of 0&n;* Apr 20, 1998&t;Alan Cox&t;Fixed 2.1 symbols&n;* May 17, 1998  K. Baranowski&t;Fixed SNAP encapsulation in wan_encapsulate&n;*****************************************************************************/
macro_line|#include &lt;linux/stddef.h&gt;&t;/* offsetof(), etc. */
macro_line|#include &lt;linux/errno.h&gt;&t;/* return codes */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;&t;/* support for loadable modules */
macro_line|#include &lt;linux/malloc.h&gt;&t;/* kmalloc(), kfree() */
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* verify_area(), etc. */
macro_line|#include &lt;linux/string.h&gt;&t;/* inline mem*, str* functions */
macro_line|#include &lt;asm/segment.h&gt;&t;/* kernel &lt;-&gt; user copy */
macro_line|#include &lt;asm/byteorder.h&gt;&t;/* htons(), etc. */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy_to/from_user */
macro_line|#include &lt;linux/wanrouter.h&gt;&t;/* WAN router API definitions */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* __initfunc et al. */
multiline_comment|/****** Defines and Macros **************************************************/
macro_line|#ifndef&t;min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef&t;max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
multiline_comment|/****** Function Prototypes *************************************************/
multiline_comment|/*&n; *&t;Kernel loadable module interface.&n; */
macro_line|#ifdef MODULE
r_int
id|init_module
(paren
r_void
)paren
suffix:semicolon
r_void
id|cleanup_module
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;WAN device IOCTL handlers &n; */
r_static
r_int
id|device_setup
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_conf_t
op_star
id|u_conf
)paren
suffix:semicolon
r_static
r_int
id|device_stat
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_stat_t
op_star
id|u_stat
)paren
suffix:semicolon
r_static
r_int
id|device_shutdown
(paren
id|wan_device_t
op_star
id|wandev
)paren
suffix:semicolon
r_static
r_int
id|device_new_if
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wanif_conf_t
op_star
id|u_conf
)paren
suffix:semicolon
r_static
r_int
id|device_del_if
(paren
id|wan_device_t
op_star
id|wandev
comma
r_char
op_star
id|u_name
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Miscellaneous &n; */
r_static
id|wan_device_t
op_star
id|find_device
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_static
r_int
id|delete_interface
(paren
id|wan_device_t
op_star
id|wandev
comma
r_char
op_star
id|name
comma
r_int
id|forse
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Global Data&n; */
macro_line|#ifdef MODULE
DECL|variable|fullname
r_static
r_char
id|fullname
(braket
)braket
op_assign
l_string|&quot;WAN Router&quot;
suffix:semicolon
DECL|variable|copyright
r_static
r_char
id|copyright
(braket
)braket
op_assign
l_string|&quot;(c) 1995-1997 Sangoma Technologies Inc.&quot;
suffix:semicolon
macro_line|#endif
DECL|variable|modname
r_static
r_char
id|modname
(braket
)braket
op_assign
id|ROUTER_NAME
suffix:semicolon
multiline_comment|/* short module name */
DECL|variable|router_devlist
id|wan_device_t
op_star
id|router_devlist
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* list of registered devices */
DECL|variable|devcnt
r_static
r_int
id|devcnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;Organizationally Unique Identifiers for encapsulation/decapsulation&n; */
DECL|variable|oui_ether
r_static
r_int
r_char
id|oui_ether
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
macro_line|#if 0
r_static
r_int
r_char
id|oui_802_2
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x80
comma
l_int|0xC2
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
multiline_comment|/*&n; *&t;Kernel Loadable Module Entry Points&n; */
multiline_comment|/*&n; *&t;Module &squot;insert&squot; entry point.&n; *&t;o print announcement&n; *&t;o initialize static data&n; *&t;o create /proc/net/router directory and static entries&n; *&n; *&t;Return:&t;0&t;Ok&n; *&t;&t;&lt; 0&t;error.&n; *&t;Context:&t;process&n; */
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s v%u.%u %s&bslash;n&quot;
comma
id|fullname
comma
id|ROUTER_VERSION
comma
id|ROUTER_RELEASE
comma
id|copyright
)paren
suffix:semicolon
id|err
op_assign
id|wanrouter_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t create entry in proc filesystem!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Module &squot;remove&squot; entry point.&n; *&t;o delete /proc/net/router directory and static entries.&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
id|wanrouter_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|wanrouter_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|err
op_assign
id|wanrouter_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t create entry in proc filesystem!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Kernel APIs&n; */
multiline_comment|/*&n; *&t;Register WAN device.&n; *&t;o verify device credentials&n; *&t;o create an entry for the device in the /proc/net/router directory&n; *&t;o initialize internally maintained fields of the wan_device structure&n; *&t;o link device data space to a singly-linked list&n; *&t;o if it&squot;s the first device, then start kernel &squot;thread&squot;&n; *&t;o increment module use count&n; *&n; *&t; Return:&n; *&t;&t;0&t;Ok&n; *&t;&t;&lt; 0&t;error.&n; *&n; *&t;Context:&t;process&n; */
DECL|function|register_wan_device
r_int
id|register_wan_device
c_func
(paren
id|wan_device_t
op_star
id|wandev
)paren
(brace
r_int
id|err
comma
id|namelen
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wandev
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|wandev-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
op_logical_or
(paren
id|wandev-&gt;name
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|wandev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
op_logical_or
(paren
id|namelen
OG
id|WAN_DRVNAME_SZ
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|find_device
c_func
(paren
id|wandev-&gt;name
)paren
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
macro_line|#ifdef WANDEBUG&t;&t;
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: registering WAN device %s&bslash;n&quot;
comma
id|modname
comma
id|wandev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Register /proc directory entry &n;&t; */
id|err
op_assign
id|wanrouter_proc_add
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
l_string|&quot;%s: can&squot;t create /proc/net/router/%s entry!&bslash;n&quot;
comma
id|modname
comma
id|wandev-&gt;name
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Initialize fields of the wan_device structure maintained by the&n;&t; *&t;router and update local data.&n;&t; */
id|wandev-&gt;ndev
op_assign
l_int|0
suffix:semicolon
id|wandev-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|wandev-&gt;next
op_assign
id|router_devlist
suffix:semicolon
id|router_devlist
op_assign
id|wandev
suffix:semicolon
op_increment
id|devcnt
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* prevent module from unloading */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Unregister WAN device.&n; *&t;o shut down device&n; *&t;o unlink device data space from the linked list&n; *&t;o delete device entry in the /proc/net/router directory&n; *&t;o decrement module use count&n; *&n; *&t;Return:&t;&t;0&t;Ok&n; *&t;&t;&t;&lt;0&t;error.&n; *&t;Context:&t;process&n; */
DECL|function|unregister_wan_device
r_int
id|unregister_wan_device
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|wan_device_t
op_star
id|wandev
comma
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|wandev
op_assign
id|router_devlist
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|wandev
op_logical_and
id|strcmp
c_func
(paren
id|wandev-&gt;name
comma
id|name
)paren
suffix:semicolon
id|prev
op_assign
id|wandev
comma
id|wandev
op_assign
id|wandev-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wandev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef WANDEBUG&t;&t;
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unregistering WAN device %s&bslash;n&quot;
comma
id|modname
comma
id|name
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|wandev-&gt;state
op_ne
id|WAN_UNCONFIGURED
)paren
(brace
r_while
c_loop
(paren
id|wandev-&gt;dev
)paren
(brace
id|delete_interface
c_func
(paren
id|wandev
comma
id|wandev-&gt;dev-&gt;name
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wandev-&gt;shutdown
)paren
id|wandev
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|wandev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|wandev-&gt;next
suffix:semicolon
r_else
id|router_devlist
op_assign
id|wandev-&gt;next
suffix:semicolon
op_decrement
id|devcnt
suffix:semicolon
id|wanrouter_proc_delete
c_func
(paren
id|wandev
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Encapsulate packet.&n; *&n; *&t;Return:&t;encapsulation header size&n; *&t;&t;&lt; 0&t;- unsupported Ethertype&n; *&n; *&t;Notes:&n; *&t;1. This function may be called on interrupt context.&n; */
DECL|function|wanrouter_encapsulate
r_int
id|wanrouter_encapsulate
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|hdr_len
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;protocol
)paren
(brace
r_case
id|ETH_P_IP
suffix:colon
multiline_comment|/* IP datagram encapsulation */
id|hdr_len
op_add_assign
l_int|1
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|NLPID_IP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETH_P_IPX
suffix:colon
multiline_comment|/* SNAP encapsulation */
r_case
id|ETH_P_ARP
suffix:colon
id|hdr_len
op_add_assign
l_int|7
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
l_int|7
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
id|NLPID_SNAP
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|skb-&gt;data
(braket
l_int|2
)braket
comma
id|oui_ether
comma
r_sizeof
(paren
id|oui_ether
)paren
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|skb-&gt;data
(braket
l_int|5
)braket
)paren
op_assign
id|htons
c_func
(paren
id|skb-&gt;protocol
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown packet type */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unsupported Ethertype 0x%04X on interface %s!&bslash;n&quot;
comma
id|modname
comma
id|skb-&gt;protocol
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|hdr_len
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|hdr_len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Decapsulate packet.&n; *&n; *&t;Return:&t;Ethertype (in network order)&n; *&t;&t;&t;0&t;unknown encapsulation&n; *&n; *&t;Notes:&n; *&t;1. This function may be called on interrupt context.&n; */
DECL|function|wanrouter_type_trans
r_int
r_int
id|wanrouter_type_trans
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|cnt
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* there may be a pad present */
r_int
r_int
id|ethertype
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
id|cnt
)braket
)paren
(brace
r_case
id|NLPID_IP
suffix:colon
multiline_comment|/* IP datagramm */
id|ethertype
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|cnt
op_add_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NLPID_SNAP
suffix:colon
multiline_comment|/* SNAP encapsulation */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|skb-&gt;data
(braket
id|cnt
op_plus
l_int|1
)braket
comma
id|oui_ether
comma
r_sizeof
(paren
id|oui_ether
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unsupported SNAP OUI %02X-%02X-%02X &quot;
l_string|&quot;on interface %s!&bslash;n&quot;
comma
id|modname
comma
id|skb-&gt;data
(braket
id|cnt
op_plus
l_int|1
)braket
comma
id|skb-&gt;data
(braket
id|cnt
op_plus
l_int|2
)braket
comma
id|skb-&gt;data
(braket
id|cnt
op_plus
l_int|3
)braket
comma
id|dev-&gt;name
)paren
suffix:semicolon
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ethertype
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|skb-&gt;data
(braket
id|cnt
op_plus
l_int|4
)braket
)paren
suffix:semicolon
id|cnt
op_add_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* add other protocols, e.g. CLNP, ESIS, ISIS, if needed */
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unsupported NLPID 0x%02X on interface %s!&bslash;n&quot;
comma
id|modname
comma
id|skb-&gt;data
(braket
id|cnt
)braket
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|ethertype
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
multiline_comment|/*&t;Physically point to point */
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|cnt
)paren
suffix:semicolon
r_return
id|ethertype
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;WAN device IOCTL.&n; *&t;o find WAN device associated with this node&n; *&t;o execute requested action or pass command to the device driver&n; */
DECL|function|wanrouter_ioctl
r_int
id|wanrouter_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dent
suffix:semicolon
id|wan_device_t
op_star
id|wandev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_rshift
l_int|8
)paren
op_ne
id|ROUTER_IOCTL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dent
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dent
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|dent-&gt;data
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|wandev
op_assign
id|dent-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|wandev-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ROUTER_SETUP
suffix:colon
id|err
op_assign
id|device_setup
c_func
(paren
id|wandev
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUTER_DOWN
suffix:colon
id|err
op_assign
id|device_shutdown
c_func
(paren
id|wandev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUTER_STAT
suffix:colon
id|err
op_assign
id|device_stat
c_func
(paren
id|wandev
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUTER_IFNEW
suffix:colon
id|err
op_assign
id|device_new_if
c_func
(paren
id|wandev
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUTER_IFDEL
suffix:colon
id|err
op_assign
id|device_del_if
c_func
(paren
id|wandev
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUTER_IFSTAT
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
(paren
id|cmd
op_ge
id|ROUTER_USER
)paren
op_logical_and
(paren
id|cmd
op_le
id|ROUTER_USER_MAX
)paren
op_logical_and
id|wandev-&gt;ioctl
)paren
id|err
op_assign
id|wandev
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|wandev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_else
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;WAN Driver IOCTL Handlers&n; */
multiline_comment|/*&n; *&t;Setup WAN link device.&n; *&t;o verify user address space&n; *&t;o allocate kernel memory and copy configuration data to kernel space&n; *&t;o if configuration data includes extension, copy it to kernel space too&n; *&t;o call driver&squot;s setup() entry point&n; */
DECL|function|device_setup
r_static
r_int
id|device_setup
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_conf_t
op_star
id|u_conf
)paren
(brace
r_void
op_star
id|data
suffix:semicolon
id|wandev_conf_t
op_star
id|conf
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|wandev-&gt;setup
op_eq
l_int|NULL
)paren
multiline_comment|/* Nothing to do ? */
r_return
l_int|0
suffix:semicolon
id|conf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|wandev_conf_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|conf
comma
id|u_conf
comma
r_sizeof
(paren
id|wandev_conf_t
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|conf-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
r_goto
id|bail
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;data_size
op_logical_and
id|conf-&gt;data
)paren
(brace
r_if
c_cond
(paren
id|conf-&gt;data_size
OG
l_int|1024
op_logical_or
id|conf-&gt;data_size
OL
l_int|0
)paren
(brace
r_goto
id|bail
suffix:semicolon
)brace
id|data
op_assign
id|kmalloc
c_func
(paren
id|conf-&gt;data_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|copy_from_user
c_func
(paren
id|data
comma
id|conf-&gt;data
comma
id|conf-&gt;data_size
)paren
)paren
(brace
id|conf-&gt;data
op_assign
id|data
suffix:semicolon
id|wandev
op_member_access_from_pointer
id|setup
c_func
(paren
id|wandev
comma
id|conf
)paren
suffix:semicolon
)brace
r_else
id|err
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
)paren
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
id|bail
suffix:colon
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Shutdown WAN device.&n; *&t;o delete all not opened logical channels for this device&n; *&t;o call driver&squot;s shutdown() entry point&n; */
DECL|function|device_shutdown
r_static
r_int
id|device_shutdown
(paren
id|wan_device_t
op_star
id|wandev
)paren
(brace
r_struct
id|device
op_star
id|dev
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
r_for
c_loop
(paren
id|dev
op_assign
id|wandev-&gt;dev
suffix:semicolon
id|dev
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|delete_interface
c_func
(paren
id|wandev
comma
id|dev-&gt;name
comma
l_int|0
)paren
)paren
id|dev
op_assign
id|dev-&gt;slave
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wandev-&gt;ndev
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* there are opened interfaces  */
r_if
c_cond
(paren
id|wandev-&gt;shutdown
)paren
r_return
id|wandev
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|wandev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Get WAN device status &amp; statistics.&n; */
DECL|function|device_stat
r_static
r_int
id|device_stat
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wandev_stat_t
op_star
id|u_stat
)paren
(brace
id|wandev_stat_t
id|stat
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|stat
comma
l_int|0
comma
r_sizeof
(paren
id|stat
)paren
)paren
suffix:semicolon
multiline_comment|/* Ask device driver to update device statistics */
r_if
c_cond
(paren
(paren
id|wandev-&gt;state
op_ne
id|WAN_UNCONFIGURED
)paren
op_logical_and
id|wandev-&gt;update
)paren
id|wandev
op_member_access_from_pointer
id|update
c_func
(paren
id|wandev
)paren
suffix:semicolon
multiline_comment|/* Fill out structure */
id|stat.ndev
op_assign
id|wandev-&gt;ndev
suffix:semicolon
id|stat.state
op_assign
id|wandev-&gt;state
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|u_stat
comma
op_amp
id|stat
comma
r_sizeof
(paren
id|stat
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Create new WAN interface.&n; *&t;o verify user address space&n; *&t;o copy configuration data to kernel address space&n; *&t;o allocate network interface data space&n; *&t;o call driver&squot;s new_if() entry point&n; *&t;o make sure there is no interface name conflict&n; *&t;o register network interface&n; */
DECL|function|device_new_if
r_static
r_int
id|device_new_if
(paren
id|wan_device_t
op_star
id|wandev
comma
id|wanif_conf_t
op_star
id|u_conf
)paren
(brace
id|wanif_conf_t
id|conf
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wandev-&gt;state
op_eq
id|WAN_UNCONFIGURED
)paren
op_logical_or
(paren
id|wandev-&gt;new_if
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|conf
comma
id|u_conf
comma
r_sizeof
(paren
id|wanif_conf_t
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|conf.magic
op_ne
id|ROUTER_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|device
)paren
)paren
suffix:semicolon
id|err
op_assign
id|wandev
op_member_access_from_pointer
id|new_if
c_func
(paren
id|wandev
comma
id|dev
comma
op_amp
id|conf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
multiline_comment|/* Register network interface. This will invoke init()&n;&t;&t; * function supplied by the driver.  If device registered&n;&t;&t; * successfully, add it to the interface list.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;name
op_eq
l_int|NULL
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev_get
c_func
(paren
id|dev-&gt;name
)paren
)paren
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
multiline_comment|/* name already exists */
r_else
(brace
macro_line|#ifdef WANDEBUG&t;&t;
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: registering interface %s...&bslash;n&quot;
comma
id|modname
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/***** critical section start *****/
id|dev-&gt;slave
op_assign
id|wandev-&gt;dev
suffix:semicolon
id|wandev-&gt;dev
op_assign
id|dev
suffix:semicolon
op_increment
id|wandev-&gt;ndev
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/****** critical section end ******/
r_return
l_int|0
suffix:semicolon
multiline_comment|/* done !!! */
)brace
)brace
r_if
c_cond
(paren
id|wandev-&gt;del_if
)paren
id|wandev
op_member_access_from_pointer
id|del_if
c_func
(paren
id|wandev
comma
id|dev
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Delete WAN logical channel.&n; *&t; o verify user address space&n; *&t; o copy configuration data to kernel address space&n; */
DECL|function|device_del_if
r_static
r_int
id|device_del_if
(paren
id|wan_device_t
op_star
id|wandev
comma
r_char
op_star
id|u_name
)paren
(brace
r_char
id|name
(braket
id|WAN_IFNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|wandev-&gt;state
op_eq
id|WAN_UNCONFIGURED
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
r_sizeof
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|name
comma
id|u_name
comma
id|WAN_IFNAME_SZ
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|delete_interface
c_func
(paren
id|wandev
comma
id|name
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Miscellaneous Functions&n; */
multiline_comment|/*&n; *&t;Find WAN device by name.&n; *&t;Return pointer to the WAN device data space or NULL if device not found.&n; */
DECL|function|find_device
r_static
id|wan_device_t
op_star
id|find_device
(paren
r_char
op_star
id|name
)paren
(brace
id|wan_device_t
op_star
id|wandev
suffix:semicolon
r_for
c_loop
(paren
id|wandev
op_assign
id|router_devlist
suffix:semicolon
id|wandev
op_logical_and
id|strcmp
c_func
(paren
id|wandev-&gt;name
comma
id|name
)paren
suffix:semicolon
id|wandev
op_assign
id|wandev-&gt;next
)paren
suffix:semicolon
r_return
id|wandev
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Delete WAN logical channel identified by its name.&n; *&t;o find logical channel by its name&n; *&t;o call driver&squot;s del_if() entry point&n; *&t;o unregister network interface&n; *&t;o unlink channel data space from linked list of channels&n; *&t;o release channel data space&n; *&n; *&t;Return:&t;0&t;&t;success&n; *&t;&t;-ENODEV&t;&t;channel not found.&n; *&t;&t;-EBUSY&t;&t;interface is open&n; *&n; *&t;Note: If (force != 0), then device will be destroyed even if interface&n; *&t;associated with it is open. It&squot;s caller&squot;s responsibility to make&n; *&t;sure that opened interfaces are not removed!&n; */
DECL|function|delete_interface
r_static
r_int
id|delete_interface
(paren
id|wan_device_t
op_star
id|wandev
comma
r_char
op_star
id|name
comma
r_int
id|force
)paren
(brace
r_struct
id|device
op_star
id|dev
comma
op_star
id|prev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|wandev-&gt;dev
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|dev
op_logical_and
id|strcmp
c_func
(paren
id|name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|prev
op_assign
id|dev
comma
id|dev
op_assign
id|dev-&gt;slave
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* interface not found */
r_if
c_cond
(paren
id|dev-&gt;start
)paren
(brace
r_if
c_cond
(paren
id|force
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: deleting opened interface %s!&bslash;n&quot;
comma
id|modname
comma
id|name
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* interface in use */
)brace
r_if
c_cond
(paren
id|wandev-&gt;del_if
)paren
id|wandev
op_member_access_from_pointer
id|del_if
c_func
(paren
id|wandev
comma
id|dev
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/***** critical section start *****/
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;slave
op_assign
id|dev-&gt;slave
suffix:semicolon
r_else
id|wandev-&gt;dev
op_assign
id|dev-&gt;slave
suffix:semicolon
op_decrement
id|wandev-&gt;ndev
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/****** critical section end ******/
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|register_wan_device
id|EXPORT_SYMBOL
c_func
(paren
id|register_wan_device
)paren
suffix:semicolon
DECL|variable|unregister_wan_device
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_wan_device
)paren
suffix:semicolon
DECL|variable|wanrouter_encapsulate
id|EXPORT_SYMBOL
c_func
(paren
id|wanrouter_encapsulate
)paren
suffix:semicolon
DECL|variable|wanrouter_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|wanrouter_type_trans
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;End&n; */
eof
