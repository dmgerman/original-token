multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irmod.c&n; * Version:       0.8&n; * Description:   IrDA module code and some other stuff&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Dec 15 13:55:39 1997&n; * Modified at:   Tue Dec 21 21:39:31 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
macro_line|#include &lt;net/irda/irlap_comp.h&gt;
macro_line|#endif /* CONFIG_IRDA_COMPRESSION */
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/wrapper.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/parameters.h&gt;
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
DECL|variable|irda
r_struct
id|irda_cb
id|irda
suffix:semicolon
multiline_comment|/* One global instance */
macro_line|#ifdef CONFIG_IRDA_DEBUG
DECL|variable|irda_debug
id|__u32
id|irda_debug
op_assign
id|IRDA_DEBUG_LEVEL
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|irda_proc_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_proc_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irda_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irda_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
suffix:semicolon
r_extern
r_void
id|irda_proto_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irda_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlan_server_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ircomm_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ircomm_tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_client_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_server_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
macro_line|#ifdef CONFIG_IRDA_DEFLATE
r_extern
id|irda_deflate_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_DEFLATE */
macro_line|#endif /* CONFIG_IRDA_COMPRESSION */
r_static
r_int
id|irda_open
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
)paren
suffix:semicolon
r_static
r_int
id|irda_ioctl
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|irda_close
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
)paren
suffix:semicolon
r_static
id|ssize_t
id|irda_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
suffix:semicolon
r_static
id|ssize_t
id|irda_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
suffix:semicolon
r_static
id|u_int
id|irda_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
DECL|variable|irda_fops
r_static
r_struct
id|file_operations
id|irda_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* seek */
id|irda_read
comma
multiline_comment|/* read */
id|irda_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
id|irda_poll
comma
multiline_comment|/* poll */
id|irda_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|irda_open
comma
l_int|NULL
comma
id|irda_close
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* fasync */
)brace
suffix:semicolon
multiline_comment|/* IrTTP */
DECL|variable|irttp_open_tsap
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_open_tsap
)paren
suffix:semicolon
DECL|variable|irttp_close_tsap
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_close_tsap
)paren
suffix:semicolon
DECL|variable|irttp_connect_response
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_connect_response
)paren
suffix:semicolon
DECL|variable|irttp_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_data_request
)paren
suffix:semicolon
DECL|variable|irttp_disconnect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_disconnect_request
)paren
suffix:semicolon
DECL|variable|irttp_flow_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_flow_request
)paren
suffix:semicolon
DECL|variable|irttp_connect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_connect_request
)paren
suffix:semicolon
DECL|variable|irttp_udata_request
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_udata_request
)paren
suffix:semicolon
DECL|variable|irttp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|irttp_dup
)paren
suffix:semicolon
multiline_comment|/* Main IrDA module */
macro_line|#ifdef CONFIG_IRDA_DEBUG
DECL|variable|irda_debug
id|EXPORT_SYMBOL
c_func
(paren
id|irda_debug
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|irda_notify_init
id|EXPORT_SYMBOL
c_func
(paren
id|irda_notify_init
)paren
suffix:semicolon
DECL|variable|irmanager_notify
id|EXPORT_SYMBOL
c_func
(paren
id|irmanager_notify
)paren
suffix:semicolon
DECL|variable|irda_lock
id|EXPORT_SYMBOL
c_func
(paren
id|irda_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_irda
id|EXPORT_SYMBOL
c_func
(paren
id|proc_irda
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|irda_param_insert
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_insert
)paren
suffix:semicolon
DECL|variable|irda_param_extract
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_extract
)paren
suffix:semicolon
DECL|variable|irda_param_extract_all
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_extract_all
)paren
suffix:semicolon
DECL|variable|irda_param_pack
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_pack
)paren
suffix:semicolon
DECL|variable|irda_param_unpack
id|EXPORT_SYMBOL
c_func
(paren
id|irda_param_unpack
)paren
suffix:semicolon
multiline_comment|/* IrIAP/IrIAS */
DECL|variable|iriap_open
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_open
)paren
suffix:semicolon
DECL|variable|iriap_close
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_close
)paren
suffix:semicolon
DECL|variable|iriap_getvaluebyclass_request
id|EXPORT_SYMBOL
c_func
(paren
id|iriap_getvaluebyclass_request
)paren
suffix:semicolon
DECL|variable|irias_object_change_attribute
id|EXPORT_SYMBOL
c_func
(paren
id|irias_object_change_attribute
)paren
suffix:semicolon
DECL|variable|irias_add_integer_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_integer_attrib
)paren
suffix:semicolon
DECL|variable|irias_add_octseq_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_octseq_attrib
)paren
suffix:semicolon
DECL|variable|irias_add_string_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_add_string_attrib
)paren
suffix:semicolon
DECL|variable|irias_insert_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_insert_object
)paren
suffix:semicolon
DECL|variable|irias_new_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_object
)paren
suffix:semicolon
DECL|variable|irias_delete_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_delete_object
)paren
suffix:semicolon
DECL|variable|irias_delete_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_delete_value
)paren
suffix:semicolon
DECL|variable|irias_find_object
id|EXPORT_SYMBOL
c_func
(paren
id|irias_find_object
)paren
suffix:semicolon
DECL|variable|irias_find_attrib
id|EXPORT_SYMBOL
c_func
(paren
id|irias_find_attrib
)paren
suffix:semicolon
DECL|variable|irias_new_integer_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_integer_value
)paren
suffix:semicolon
DECL|variable|irias_new_string_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_string_value
)paren
suffix:semicolon
DECL|variable|irias_new_octseq_value
id|EXPORT_SYMBOL
c_func
(paren
id|irias_new_octseq_value
)paren
suffix:semicolon
multiline_comment|/* IrLMP */
DECL|variable|irlmp_discovery_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_discovery_request
)paren
suffix:semicolon
DECL|variable|irlmp_register_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_register_client
)paren
suffix:semicolon
DECL|variable|irlmp_unregister_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_unregister_client
)paren
suffix:semicolon
DECL|variable|irlmp_update_client
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_update_client
)paren
suffix:semicolon
DECL|variable|irlmp_register_service
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_register_service
)paren
suffix:semicolon
DECL|variable|irlmp_unregister_service
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_unregister_service
)paren
suffix:semicolon
DECL|variable|irlmp_service_to_hint
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_service_to_hint
)paren
suffix:semicolon
DECL|variable|irlmp_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_data_request
)paren
suffix:semicolon
DECL|variable|irlmp_open_lsap
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_open_lsap
)paren
suffix:semicolon
DECL|variable|irlmp_close_lsap
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_close_lsap
)paren
suffix:semicolon
DECL|variable|irlmp_connect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_connect_request
)paren
suffix:semicolon
DECL|variable|irlmp_connect_response
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_connect_response
)paren
suffix:semicolon
DECL|variable|irlmp_disconnect_request
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_disconnect_request
)paren
suffix:semicolon
DECL|variable|irlmp_get_daddr
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_get_daddr
)paren
suffix:semicolon
DECL|variable|irlmp_get_saddr
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_get_saddr
)paren
suffix:semicolon
DECL|variable|irlmp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|irlmp_dup
)paren
suffix:semicolon
DECL|variable|lmp_reasons
id|EXPORT_SYMBOL
c_func
(paren
id|lmp_reasons
)paren
suffix:semicolon
multiline_comment|/* Queue */
DECL|variable|hashbin_find
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_find
)paren
suffix:semicolon
DECL|variable|hashbin_new
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_new
)paren
suffix:semicolon
DECL|variable|hashbin_insert
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_insert
)paren
suffix:semicolon
DECL|variable|hashbin_delete
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_delete
)paren
suffix:semicolon
DECL|variable|hashbin_remove
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_remove
)paren
suffix:semicolon
DECL|variable|hashbin_get_next
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_next
)paren
suffix:semicolon
DECL|variable|hashbin_get_first
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_first
)paren
suffix:semicolon
multiline_comment|/* IrLAP */
DECL|variable|irlap_open
id|EXPORT_SYMBOL
c_func
(paren
id|irlap_open
)paren
suffix:semicolon
DECL|variable|irlap_close
id|EXPORT_SYMBOL
c_func
(paren
id|irlap_close
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
DECL|variable|irda_unregister_compressor
id|EXPORT_SYMBOL
c_func
(paren
id|irda_unregister_compressor
)paren
suffix:semicolon
DECL|variable|irda_register_compressor
id|EXPORT_SYMBOL
c_func
(paren
id|irda_register_compressor
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_COMPRESSION */
DECL|variable|irda_init_max_qos_capabilies
id|EXPORT_SYMBOL
c_func
(paren
id|irda_init_max_qos_capabilies
)paren
suffix:semicolon
DECL|variable|irda_qos_bits_to_value
id|EXPORT_SYMBOL
c_func
(paren
id|irda_qos_bits_to_value
)paren
suffix:semicolon
DECL|variable|irda_device_setup
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_setup
)paren
suffix:semicolon
DECL|variable|irda_device_set_media_busy
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_set_media_busy
)paren
suffix:semicolon
DECL|variable|irda_device_txqueue_empty
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_txqueue_empty
)paren
suffix:semicolon
DECL|variable|irda_device_dongle_init
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_dongle_init
)paren
suffix:semicolon
DECL|variable|irda_device_dongle_cleanup
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_dongle_cleanup
)paren
suffix:semicolon
DECL|variable|irda_device_register_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_register_dongle
)paren
suffix:semicolon
DECL|variable|irda_device_unregister_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_device_unregister_dongle
)paren
suffix:semicolon
DECL|variable|irda_task_execute
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_execute
)paren
suffix:semicolon
DECL|variable|irda_task_kick
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_kick
)paren
suffix:semicolon
DECL|variable|irda_task_next_state
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_next_state
)paren
suffix:semicolon
DECL|variable|irda_task_delete
id|EXPORT_SYMBOL
c_func
(paren
id|irda_task_delete
)paren
suffix:semicolon
DECL|variable|async_wrap_skb
id|EXPORT_SYMBOL
c_func
(paren
id|async_wrap_skb
)paren
suffix:semicolon
DECL|variable|async_unwrap_char
id|EXPORT_SYMBOL
c_func
(paren
id|async_unwrap_char
)paren
suffix:semicolon
DECL|variable|irda_start_timer
id|EXPORT_SYMBOL
c_func
(paren
id|irda_start_timer
)paren
suffix:semicolon
DECL|variable|setup_dma
id|EXPORT_SYMBOL
c_func
(paren
id|setup_dma
)paren
suffix:semicolon
DECL|variable|infrared_mode
id|EXPORT_SYMBOL
c_func
(paren
id|infrared_mode
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRTTY
DECL|variable|irtty_set_dtr_rts
id|EXPORT_SYMBOL
c_func
(paren
id|irtty_set_dtr_rts
)paren
suffix:semicolon
DECL|variable|irtty_register_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irtty_register_dongle
)paren
suffix:semicolon
DECL|variable|irtty_unregister_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irtty_unregister_dongle
)paren
suffix:semicolon
DECL|variable|irtty_set_packet_mode
id|EXPORT_SYMBOL
c_func
(paren
id|irtty_set_packet_mode
)paren
suffix:semicolon
macro_line|#endif
DECL|function|irda_init
r_int
id|__init
id|irda_init
c_func
(paren
r_void
)paren
(brace
id|MESSAGE
c_func
(paren
l_string|&quot;IrDA (tm) Protocols for Linux-2.3 (Dag Brattli)&bslash;n&quot;
)paren
suffix:semicolon
id|irlmp_init
c_func
(paren
)paren
suffix:semicolon
id|irlap_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|irda_device_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Called by init/main.c when non-modular */
macro_line|#endif
id|iriap_init
c_func
(paren
)paren
suffix:semicolon
id|irttp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|irda_proc_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
id|irda_sysctl_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|init_waitqueue_head
c_func
(paren
op_amp
id|irda.wait_queue
)paren
suffix:semicolon
id|irda.dev.minor
op_assign
id|MISC_DYNAMIC_MINOR
suffix:semicolon
id|irda.dev.name
op_assign
l_string|&quot;irda&quot;
suffix:semicolon
id|irda.dev.fops
op_assign
op_amp
id|irda_fops
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|irda.dev
)paren
suffix:semicolon
id|irda.in_use
op_assign
id|FALSE
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|irda.wait_queue
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Initialize modules that got compiled into the kernel &n;&t; */
macro_line|#ifdef CONFIG_IRLAN
id|irlan_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IRCOMM
id|ircomm_init
c_func
(paren
)paren
suffix:semicolon
id|ircomm_tty_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
macro_line|#ifdef CONFIG_IRDA_DEFLATE
id|irda_deflate_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_DEFLATE */
macro_line|#endif /* CONFIG_IRDA_COMPRESSION */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|irda_cleanup
r_void
id|irda_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|irda.dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|irda_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef CONFIG_PROC_FS
id|irda_proc_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Remove higher layers */
id|irttp_cleanup
c_func
(paren
)paren
suffix:semicolon
id|iriap_cleanup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Remove lower layers */
id|irda_device_cleanup
c_func
(paren
)paren
suffix:semicolon
id|irlap_cleanup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Must be done before irlmp_cleanup()! DB */
multiline_comment|/* Remove middle layer */
id|irlmp_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Function irda_unlock (lock)&n; *&n; *    Unlock variable. Returns false if lock is already unlocked&n; *&n; */
DECL|function|irda_unlock
r_inline
r_int
id|irda_unlock
c_func
(paren
r_int
op_star
id|lock
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
id|lock
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to unlock already unlocked variable!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|FALSE
suffix:semicolon
)brace
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_notify_init (notify)&n; *&n; *    Used for initializing the notify structure&n; *&n; */
DECL|function|irda_notify_init
r_void
id|irda_notify_init
c_func
(paren
id|notify_t
op_star
id|notify
)paren
(brace
id|notify-&gt;data_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;udata_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;connect_confirm
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;connect_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;disconnect_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;flow_indication
op_assign
l_int|NULL
suffix:semicolon
id|notify-&gt;instance
op_assign
l_int|NULL
suffix:semicolon
id|strncpy
c_func
(paren
id|notify-&gt;name
comma
l_string|&quot;Unknown&quot;
comma
id|NOTIFY_MAX_NAME
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_execute_as_process (self, callback, param)&n; *&n; *    If a layer needs to have a function executed with a process context,&n; *    then it can register the function here, and the function will then &n; *    be executed as fast as possible.&n; *&n; */
DECL|function|irda_execute_as_process
r_void
id|irda_execute_as_process
c_func
(paren
r_void
op_star
id|self
comma
id|TODO_CALLBACK
id|callback
comma
id|__u32
id|param
)paren
(brace
r_struct
id|irda_todo
op_star
r_new
suffix:semicolon
r_struct
id|irmanager_event
id|event
suffix:semicolon
multiline_comment|/* Make sure irmanager is running */
r_if
c_cond
(paren
op_logical_neg
id|irda.in_use
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;irmanager is not running!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Make new todo event */
r_new
op_assign
(paren
r_struct
id|irda_todo
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irda_todo
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_todo
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|self
op_assign
id|self
suffix:semicolon
r_new
op_member_access_from_pointer
id|callback
op_assign
id|callback
suffix:semicolon
r_new
op_member_access_from_pointer
id|param
op_assign
id|param
suffix:semicolon
multiline_comment|/* Queue todo */
id|enqueue_last
c_func
(paren
op_amp
id|irda.todo_queue
comma
(paren
id|queue_t
op_star
)paren
r_new
)paren
suffix:semicolon
id|event.event
op_assign
id|EVENT_NEED_PROCESS_CONTEXT
suffix:semicolon
multiline_comment|/* Notify the user space manager */
id|irmanager_notify
c_func
(paren
op_amp
id|event
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irmanger_notify (event)&n; *&n; *    Send an event to the user space manager&n; *&n; */
DECL|function|irmanager_notify
r_void
id|irmanager_notify
c_func
(paren
r_struct
id|irmanager_event
op_star
id|event
)paren
(brace
r_struct
id|irda_event
op_star
r_new
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Make sure irmanager is running */
r_if
c_cond
(paren
op_logical_neg
id|irda.in_use
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;irmanager is not running!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Make new IrDA Event */
r_new
op_assign
(paren
r_struct
id|irda_event
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irda_event
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_event
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|event
op_assign
op_star
id|event
suffix:semicolon
multiline_comment|/* Queue event */
id|enqueue_last
c_func
(paren
op_amp
id|irda.event_queue
comma
(paren
id|queue_t
op_star
)paren
r_new
)paren
suffix:semicolon
multiline_comment|/* Wake up irmanager sleeping on read */
id|wake_up_interruptible
c_func
(paren
op_amp
id|irda.wait_queue
)paren
suffix:semicolon
)brace
DECL|function|irda_open
r_static
r_int
id|irda_open
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
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irda.in_use
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), irmanager is already running!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|irda.in_use
op_assign
id|TRUE
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_ioctl (inode, filp, cmd, arg)&n; *&n; *    Ioctl, used by irmanager to ...&n; *&n; */
DECL|function|irda_ioctl
r_static
r_int
id|irda_ioctl
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
id|filp
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
r_struct
id|irda_todo
op_star
id|todo
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
op_amp
id|_IOC_READ
)paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
id|size
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
op_amp
id|_IOC_WRITE
)paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|IRMGR_IOCTNPC
suffix:colon
multiline_comment|/* Got process context! */
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(), got process context!&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|todo
op_assign
(paren
r_struct
id|irda_todo
op_star
)paren
id|dequeue_first
c_func
(paren
op_amp
id|irda.todo_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|todo
op_member_access_from_pointer
id|callback
c_func
(paren
id|todo-&gt;self
comma
id|todo-&gt;param
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|todo
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_close
r_static
r_int
id|irda_close
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
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|irda.in_use
op_assign
id|FALSE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_read
r_static
id|ssize_t
id|irda_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
(brace
r_struct
id|irda_event
op_star
id|event
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|len
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* * Go to sleep and wait for event if there is no event to be read! */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irda.event_queue
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|irda.wait_queue
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Ensure proper reaction to signals, and screen out &n;&t; *  blocked signals (page 112. linux device drivers)&n;&t; */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|event
op_assign
(paren
r_struct
id|irda_event
op_star
)paren
id|dequeue_first
c_func
(paren
op_amp
id|irda.event_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|irmanager_event
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buffer
comma
op_amp
id|event-&gt;event
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Finished with event */
id|kfree
c_func
(paren
id|event
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|irda_write
r_static
id|ssize_t
id|irda_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_poll
r_static
id|u_int
id|irda_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Sorry not implemented yet!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_mod_inc_use_count
r_void
id|irda_mod_inc_use_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|irda_mod_dec_use_count
r_void
id|irda_mod_dec_use_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Function irda_proc_modcount (inode, fill)&n; *&n; *    Use by the proc file system functions to prevent the irda module&n; *    being removed while the use is standing in the net/irda directory&n; */
DECL|function|irda_proc_modcount
r_void
id|irda_proc_modcount
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|fill
)paren
(brace
macro_line|#ifdef MODULE
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
id|fill
)paren
id|MOD_INC_USE_COUNT
suffix:semicolon
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#endif /* MODULE */
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Linux IrDA Protocol Subsystem&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irda_debug
comma
l_string|&quot;1l&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize the irda module&n; *&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|irda_proto_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup the irda module&n; *&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|irda_proto_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
