multiline_comment|/*********************************************************************&n; *&n; * Filename:      irlpt_cli.c&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Thomas Davis, &lt;ratbert@radiks.net&gt;&n; * Created at:    Sat Feb 21 18:54:38 1998&n; * Modified at:   Sun Mar  8 23:44:19 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Sources:&t;  irlan.c&n; *&n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;,&n; *     Copyright (c) 1998, Dag Brattli,  &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     I, Thomas Davis, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irlpt_common.h&gt;
macro_line|#include &lt;net/irda/irlpt_cli.h&gt;
macro_line|#include &lt;net/irda/irlpt_cli_fsm.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
r_int
id|irlpt_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|irlpt_client_close
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
)paren
suffix:semicolon
r_static
r_void
id|irlpt_client_discovery_indication
c_func
(paren
id|discovery_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|irlpt_client_connect_confirm
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
id|__u32
id|max_seg_size
comma
id|__u8
id|max_header_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|irlpt_client_disconnect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_static
r_void
id|irlpt_client_expired
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_char
op_star
id|rcsid
op_assign
l_string|&quot;$Id: irlpt_client.c,v 1.10 1998/11/10 22:50:57 dagb Exp $&quot;
suffix:semicolon
macro_line|#endif
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;IrLPT client, v2 (Thomas Davis)&quot;
suffix:semicolon
DECL|variable|ckey
r_static
id|__u32
id|ckey
suffix:semicolon
multiline_comment|/* IrLMP client handle */
DECL|variable|client_fops
r_struct
id|file_operations
id|client_fops
op_assign
(brace
id|irlpt_seek
comma
multiline_comment|/* seek */
l_int|NULL
comma
multiline_comment|/* read_irlpt (server) */
id|irlpt_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|irlpt_open
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* flush */
id|irlpt_close
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
comma
multiline_comment|/* lock */
)brace
suffix:semicolon
DECL|variable|irlpt_client_debug
r_int
id|irlpt_client_debug
op_assign
l_int|4
suffix:semicolon
r_extern
r_char
op_star
id|irlptstate
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n; * Function client_proc_read (buf, start, offset, len, unused)&n; *&n; */
DECL|function|irlpt_client_proc_read
r_static
r_int
id|irlpt_client_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
id|unused
)paren
(brace
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
r_int
id|index
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|hashbin_get_first
c_func
(paren
id|irlpt_clients
)paren
suffix:semicolon
r_while
c_loop
(paren
id|self
)paren
(brace
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
id|len
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
id|len
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;in_use
op_eq
id|FALSE
)paren
(brace
r_break
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;ifname: %s&bslash;n&quot;
comma
id|self-&gt;ifname
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;minor: %d&bslash;n&quot;
comma
id|self-&gt;ir_dev.minor
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|self-&gt;servicetype
)paren
(brace
r_case
id|IRLPT_UNKNOWN
suffix:colon
id|index
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLPT_THREE_WIRE_RAW
suffix:colon
id|index
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLPT_THREE_WIRE
suffix:colon
id|index
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLPT_NINE_WIRE
suffix:colon
id|index
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLPT_CENTRONICS
suffix:colon
id|index
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLPT_SERVER_MODE
suffix:colon
id|index
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|index
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;service_type: %s, port type: %s&bslash;n&quot;
comma
id|irlpt_service_type
(braket
id|index
)braket
comma
id|irlpt_port_type
(braket
id|self-&gt;porttype
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;saddr: 0x%08x, daddr: 0x%08x&bslash;n&quot;
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;retries: %d, count: %d, queued packets: %d&bslash;n&quot;
comma
id|self-&gt;open_retries
comma
id|self-&gt;count
comma
id|self-&gt;pkt_count
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;slsap: %d, dlsap: %d&bslash;n&quot;
comma
id|self-&gt;slsap_sel
comma
id|self-&gt;dlsap_sel
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;fsm state: %s&bslash;n&quot;
comma
id|irlpt_client_fsm_state
(braket
id|self-&gt;state
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|hashbin_get_next
c_func
(paren
id|irlpt_clients
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/*&n; * Function irlpt_client_init (dev)&n; *&n; *   Initializes the irlpt control structure&n; *&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|irlpt_client_init
c_func
(paren
r_void
)paren
)paren
(brace
id|__u16
id|hints
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|irlpt_clients
op_assign
id|hashbin_new
c_func
(paren
id|HB_LOCAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irlpt_clients
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IrLPT client: Can&squot;t allocate hashbin!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|hints
op_assign
id|irlmp_service_to_hint
c_func
(paren
id|S_PRINTER
)paren
suffix:semicolon
id|ckey
op_assign
id|irlmp_register_client
c_func
(paren
id|hints
comma
id|irlpt_client_discovery_indication
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_entry
c_func
(paren
l_string|&quot;irlpt_client&quot;
comma
l_int|0
comma
id|proc_irda
)paren
op_member_access_from_pointer
id|get_info
op_assign
id|irlpt_client_proc_read
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/*&n; * Function irlpt_client_cleanup (void)&n; *&n; */
DECL|function|irlpt_client_cleanup
r_static
r_void
id|irlpt_client_cleanup
c_func
(paren
r_void
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|irlmp_unregister_client
c_func
(paren
id|ckey
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Delete hashbin and close all irlpt client instances in it&n;&t; */
id|hashbin_delete
c_func
(paren
id|irlpt_clients
comma
(paren
id|FREE_FUNC
)paren
id|irlpt_client_close
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;irlpt_client&quot;
comma
id|proc_irda
)paren
suffix:semicolon
macro_line|#endif
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Function irlpt_client_open (void)&n; *&n; */
DECL|function|irlpt_client_open
r_static
r_struct
id|irlpt_cb
op_star
id|irlpt_client_open
c_func
(paren
id|__u32
id|daddr
)paren
(brace
r_struct
id|irmanager_event
id|mgr_event
suffix:semicolon
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|hashbin_find
c_func
(paren
id|irlpt_clients
comma
id|daddr
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self
op_eq
l_int|NULL
)paren
(brace
id|self
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irlpt_cb
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|self
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irlpt_cb
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|self-&gt;ifname
comma
l_string|&quot;irlpt%d&quot;
comma
id|hashbin_get_size
c_func
(paren
id|irlpt_clients
)paren
)paren
suffix:semicolon
id|hashbin_insert
c_func
(paren
id|irlpt_clients
comma
(paren
id|QUEUE
op_star
)paren
id|self
comma
id|daddr
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|self-&gt;ir_dev.minor
op_assign
id|MISC_DYNAMIC_MINOR
suffix:semicolon
id|self-&gt;ir_dev.name
op_assign
id|self-&gt;ifname
suffix:semicolon
id|self-&gt;ir_dev.fops
op_assign
op_amp
id|client_fops
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|self-&gt;ir_dev
)paren
suffix:semicolon
id|self-&gt;magic
op_assign
id|IRLPT_MAGIC
suffix:semicolon
id|self-&gt;in_use
op_assign
id|TRUE
suffix:semicolon
id|self-&gt;servicetype
op_assign
id|IRLPT_THREE_WIRE_RAW
suffix:semicolon
id|self-&gt;porttype
op_assign
id|IRLPT_SERIAL
suffix:semicolon
id|self-&gt;do_event
op_assign
id|irlpt_client_do_event
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|self-&gt;rx_queue
)paren
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_IDLE
)paren
suffix:semicolon
multiline_comment|/* Tell irmanager to create /dev/irlpt&lt;X&gt; */
id|mgr_event.event
op_assign
id|EVENT_IRLPT_START
suffix:semicolon
id|sprintf
c_func
(paren
id|mgr_event.devname
comma
l_string|&quot;%s&quot;
comma
id|self-&gt;ifname
)paren
suffix:semicolon
id|irmanager_notify
c_func
(paren
op_amp
id|mgr_event
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|self
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_close (self)&n; *&n; *    This function closes and marks the IrLPT instance as not in use.&n; */
DECL|function|irlpt_client_close
r_static
r_void
id|irlpt_client_close
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
)paren
(brace
r_struct
id|irmanager_event
id|mgr_event
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Tell irmanager to remove /dev/irlpt&lt;X&gt; */
id|mgr_event.event
op_assign
id|EVENT_IRLPT_STOP
suffix:semicolon
id|sprintf
c_func
(paren
id|mgr_event.devname
comma
l_string|&quot;%s&quot;
comma
id|self-&gt;ifname
)paren
suffix:semicolon
id|irmanager_notify
c_func
(paren
op_amp
id|mgr_event
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|self-&gt;rx_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: freeing SKB&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|self-&gt;ir_dev
)paren
suffix:semicolon
id|self-&gt;in_use
op_assign
id|FALSE
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_discovery_indication (daddr)&n; *&n; *    Remote device discovered, try query the remote IAS to see which&n; *    device it is, and which services it has.&n; *&n; */
DECL|function|irlpt_client_discovery_indication
r_static
r_void
id|irlpt_client_discovery_indication
c_func
(paren
id|discovery_t
op_star
id|discovery
)paren
(brace
r_struct
id|irlpt_info
id|info
suffix:semicolon
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* address of remote printer */
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* address of local link where it was discovered */
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|irlpt_clients
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|discovery
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|daddr
op_assign
id|info.daddr
op_assign
id|discovery-&gt;daddr
suffix:semicolon
id|saddr
op_assign
id|info.saddr
op_assign
id|discovery-&gt;saddr
suffix:semicolon
multiline_comment|/*&n;&t; *  Check if an instance is already dealing with this device&n;&t; *  (daddr)&n;&t; */
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|hashbin_find
c_func
(paren
id|irlpt_clients
comma
id|daddr
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self
op_eq
l_int|NULL
op_logical_or
id|self-&gt;in_use
op_eq
id|FALSE
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: daddr 0x%08x not found or was closed&bslash;n&quot;
comma
id|daddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We have no instance for daddr, so time to start a new &n;&t;&t; * instance. First we must find a free entry in master array&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|self
op_assign
id|irlpt_client_open
c_func
(paren
id|daddr
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;daddr
op_assign
id|daddr
suffix:semicolon
id|self-&gt;saddr
op_assign
id|saddr
suffix:semicolon
id|self-&gt;timeout
op_assign
id|irlpt_client_expired
suffix:semicolon
id|irda_start_timer
c_func
(paren
op_amp
id|self-&gt;lpt_timer
comma
l_int|5000
comma
(paren
r_int
r_int
)paren
id|self
comma
id|self-&gt;timeout
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* changed to wake up when we get connected; that way,&n;&t;   if the connection drops, we can easily kill the link. */
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;write_wait
)paren
suffix:semicolon
macro_line|#endif
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_disconnect_indication (handle)&n; *&n; */
DECL|function|irlpt_client_disconnect_indication
r_static
r_void
id|irlpt_client_disconnect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|irlpt_info
id|info
suffix:semicolon
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|info.daddr
op_assign
id|self-&gt;daddr
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: reason=%d (%s), peersap=%d&bslash;n&quot;
comma
id|reason
comma
id|irlpt_reasons
(braket
id|reason
)braket
comma
id|self-&gt;dlsap_sel
)paren
suffix:semicolon
id|self-&gt;connected
op_assign
id|IRLPT_DISCONNECTED
suffix:semicolon
id|self-&gt;eof
op_assign
id|reason
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;write_wait
)paren
suffix:semicolon
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|LMP_DISCONNECT
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_connect_confirm (handle, qos, skb)&n; *&n; *    LSAP connection confirmed!&n; */
DECL|function|irlpt_client_connect_confirm
r_static
r_void
id|irlpt_client_connect_confirm
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
id|__u32
id|max_seg_size
comma
id|__u8
id|max_header_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|irlpt_info
id|info
suffix:semicolon
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|info.daddr
op_assign
id|self-&gt;daddr
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; *  Check if we have got some QoS parameters back! This should be the&n;&t; *  negotiated QoS for the link.&n;&t; */
r_if
c_cond
(paren
id|qos
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: Frame Size: %d&bslash;n&quot;
comma
id|qos-&gt;data_size.value
)paren
suffix:semicolon
)brace
macro_line|#endif
id|self-&gt;max_data_size
op_assign
id|max_seg_size
suffix:semicolon
id|self-&gt;max_header_size
op_assign
id|max_header_size
suffix:semicolon
id|self-&gt;connected
op_assign
id|TRUE
suffix:semicolon
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|LMP_CONNECT
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function client_data_indication (handle, skb)&n; *&n; *    This function gets the data that is received on the data channel&n; *&n; */
DECL|function|irlpt_client_data_indication
r_static
r_int
id|irlpt_client_data_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: len=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|skb-&gt;len
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
macro_line|#if 1
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
id|skb-&gt;len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|skb-&gt;data
(braket
id|i
)braket
OG
l_int|31
op_logical_and
id|skb-&gt;data
(braket
id|i
)braket
OL
l_int|128
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c&quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
id|i
)braket
op_eq
l_int|0x0d
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|skb_queue_tail
c_func
(paren
op_amp
id|self-&gt;rx_queue
comma
id|skb
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
)paren
suffix:semicolon
multiline_comment|/* &t;if (skb) { */
multiline_comment|/* &t;&t;dev_kfree_skb( skb); */
multiline_comment|/* &t;} */
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_get_value_confirm (obj_id, type, value_int, value_char, priv)&n; *&n; *    Fixed to match changes in iriap.h, DB.&n; *&n; */
DECL|function|irlpt_client_get_value_confirm
r_void
id|irlpt_client_get_value_confirm
c_func
(paren
r_int
id|result
comma
id|__u16
id|obj_id
comma
r_struct
id|ias_value
op_star
id|value
comma
r_void
op_star
id|priv
)paren
(brace
r_struct
id|irlpt_info
id|info
suffix:semicolon
r_struct
id|irlpt_cb
op_star
id|self
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|priv
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Check if request succeeded */
r_if
c_cond
(paren
id|result
op_ne
id|IAS_SUCCESS
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), got NULL value!&bslash;n&quot;
)paren
suffix:semicolon
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|IAS_PROVIDER_NOT_AVAIL
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value-&gt;type
op_eq
id|IAS_INTEGER
op_logical_and
id|value-&gt;t.integer
op_ne
op_minus
l_int|1
)paren
(brace
id|info.dlsap_sel
op_assign
id|value-&gt;t.integer
suffix:semicolon
id|self-&gt;dlsap_sel
op_assign
id|value-&gt;t.integer
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: obj_id = %d, value = %d&bslash;n&quot;
comma
id|obj_id
comma
id|value-&gt;t.integer
)paren
suffix:semicolon
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|IAS_PROVIDER_AVAIL
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
r_else
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|IAS_PROVIDER_NOT_AVAIL
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|irlpt_client_connect_request
r_void
id|irlpt_client_connect_request
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
)paren
(brace
r_struct
id|notify_t
id|lpt_notify
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|irda_notify_init
c_func
(paren
op_amp
id|lpt_notify
)paren
suffix:semicolon
id|lpt_notify.connect_confirm
op_assign
id|irlpt_client_connect_confirm
suffix:semicolon
id|lpt_notify.disconnect_indication
op_assign
id|irlpt_client_disconnect_indication
suffix:semicolon
id|lpt_notify.data_indication
op_assign
id|irlpt_client_data_indication
suffix:semicolon
id|strcpy
c_func
(paren
id|lpt_notify.name
comma
l_string|&quot;IrLPT client&quot;
)paren
suffix:semicolon
id|lpt_notify.instance
op_assign
id|self
suffix:semicolon
id|self-&gt;lsap
op_assign
id|irlmp_open_lsap
c_func
(paren
id|LSAP_ANY
comma
op_amp
id|lpt_notify
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: Dest LSAP sel= %d&bslash;n&quot;
comma
id|self-&gt;dlsap_sel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;servicetype
op_eq
id|IRLPT_THREE_WIRE_RAW
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: issue THREE_WIRE_RAW connect&bslash;n&quot;
)paren
suffix:semicolon
id|irlmp_connect_request
c_func
(paren
id|self-&gt;lsap
comma
id|self-&gt;dlsap_sel
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|irlpt_client_expired
r_static
r_void
id|irlpt_client_expired
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|irlpt_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlpt_cb
op_star
)paren
id|data
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: removing irlpt_cb!&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLPT_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;state
op_eq
id|IRLPT_CLIENT_CONN
)paren
(brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(: Could not allocate an &quot;
l_string|&quot;sk_buff of length %d&bslash;n&quot;
comma
l_int|64
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|LMP_MAX_HEADER
)paren
suffix:semicolon
id|irlmp_disconnect_request
c_func
(paren
id|self-&gt;lsap
comma
id|skb
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot;: irlmp_close_slap(self-&gt;lsap)&bslash;n&quot;
)paren
suffix:semicolon
id|irlmp_close_lsap
c_func
(paren
id|self-&gt;lsap
)paren
suffix:semicolon
)brace
id|irlpt_client_close
c_func
(paren
id|self
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Thomas Davis &lt;ratbert@radiks.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Linux IrDA/IrLPT client protocol&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize the IrLPT client module, this function is called by the&n; *    modprobe(1) program.&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; IrLPT client: init_module&bslash;n&quot;
)paren
suffix:semicolon
id|irlpt_client_init
c_func
(paren
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;IrLPT client: init_module --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Remove the IrLPT server module, this function is called by the rmmod(1)&n; *    program&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;--&gt; IrLPT client: cleanup_module&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* No need to check MOD_IN_USE, as sys_delete_module() checks. */
multiline_comment|/* Free some memory */
id|irlpt_client_cleanup
c_func
(paren
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_debug
comma
l_string|&quot;IrLPT client: cleanup_module --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
