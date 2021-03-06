multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_core.c&n; * Version:       1.0&n; * Description:   IrCOMM service interface&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Jun  6 20:37:34 1999&n; * Modified at:   Tue Dec 21 13:26:41 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/ircomm_event.h&gt;
macro_line|#include &lt;net/irda/ircomm_lmp.h&gt;
macro_line|#include &lt;net/irda/ircomm_ttp.h&gt;
macro_line|#include &lt;net/irda/ircomm_param.h&gt;
macro_line|#include &lt;net/irda/ircomm_core.h&gt;
r_static
r_int
id|__ircomm_close
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
r_static
r_void
id|ircomm_control_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|clen
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|ircomm_proc_read
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
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
DECL|variable|ircomm
id|hashbin_t
op_star
id|ircomm
op_assign
l_int|NULL
suffix:semicolon
DECL|function|ircomm_init
r_int
id|__init
id|ircomm_init
c_func
(paren
r_void
)paren
(brace
id|ircomm
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
id|ircomm
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), can&squot;t allocate hashbin!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_info_entry
c_func
(paren
l_string|&quot;ircomm&quot;
comma
l_int|0
comma
id|proc_irda
comma
id|ircomm_proc_read
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
id|MESSAGE
c_func
(paren
l_string|&quot;IrCOMM protocol (Dag Brattli)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|ircomm_cleanup
r_void
id|ircomm_cleanup
c_func
(paren
r_void
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|hashbin_delete
c_func
(paren
id|ircomm
comma
(paren
id|FREE_FUNC
)paren
id|__ircomm_close
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;ircomm&quot;
comma
id|proc_irda
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Function ircomm_open (client_notify)&n; *&n; *    Start a new IrCOMM instance&n; *&n; */
DECL|function|ircomm_open
r_struct
id|ircomm_cb
op_star
id|ircomm_open
c_func
(paren
id|notify_t
op_star
id|notify
comma
id|__u8
id|service_type
comma
r_int
id|line
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), service_type=0x%02x&bslash;n&quot;
comma
id|service_type
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ircomm
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ircomm_cb
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
id|ircomm_cb
)paren
)paren
suffix:semicolon
id|self-&gt;notify
op_assign
op_star
id|notify
suffix:semicolon
id|self-&gt;magic
op_assign
id|IRCOMM_MAGIC
suffix:semicolon
multiline_comment|/* Check if we should use IrLMP or IrTTP */
r_if
c_cond
(paren
id|service_type
op_amp
id|IRCOMM_3_WIRE_RAW
)paren
(brace
id|self-&gt;flow_status
op_assign
id|FLOW_START
suffix:semicolon
id|ret
op_assign
id|ircomm_open_lsap
c_func
(paren
id|self
)paren
suffix:semicolon
)brace
r_else
id|ret
op_assign
id|ircomm_open_tsap
c_func
(paren
id|self
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|self-&gt;service_type
op_assign
id|service_type
suffix:semicolon
id|self-&gt;line
op_assign
id|line
suffix:semicolon
id|hashbin_insert
c_func
(paren
id|ircomm
comma
(paren
id|irda_queue_t
op_star
)paren
id|self
comma
id|line
comma
l_int|NULL
)paren
suffix:semicolon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
r_return
id|self
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_close_instance (self)&n; *&n; *    Remove IrCOMM instance&n; *&n; */
DECL|function|__ircomm_close
r_static
r_int
id|__ircomm_close
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Disconnect link if any */
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_DISCONNECT_REQUEST
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Remove TSAP */
r_if
c_cond
(paren
id|self-&gt;tsap
)paren
(brace
id|irttp_close_tsap
c_func
(paren
id|self-&gt;tsap
)paren
suffix:semicolon
id|self-&gt;tsap
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Remove LSAP */
r_if
c_cond
(paren
id|self-&gt;lsap
)paren
(brace
id|irlmp_close_lsap
c_func
(paren
id|self-&gt;lsap
)paren
suffix:semicolon
id|self-&gt;lsap
op_assign
l_int|NULL
suffix:semicolon
)brace
id|self-&gt;magic
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|self
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_close (self)&n; *&n; *    Closes and removes the specified IrCOMM instance&n; *&n; */
DECL|function|ircomm_close
r_int
id|ircomm_close
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|entry
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
id|EIO
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
op_minus
id|EIO
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|entry
op_assign
id|hashbin_remove
c_func
(paren
id|ircomm
comma
id|self-&gt;line
comma
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|entry
op_eq
id|self
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_return
id|__ircomm_close
c_func
(paren
id|self
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_connect_request (self, service_type)&n; *&n; *    Impl. of this function is differ from one of the reference. This&n; *    function does discovery as well as sending connect request&n; * &n; */
DECL|function|ircomm_connect_request
r_int
id|ircomm_connect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|__u8
id|dlsap_sel
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u8
id|service_type
)paren
(brace
r_struct
id|ircomm_info
id|info
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
id|IRCOMM_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;service_type
op_assign
id|service_type
suffix:semicolon
id|info.dlsap_sel
op_assign
id|dlsap_sel
suffix:semicolon
id|info.saddr
op_assign
id|saddr
suffix:semicolon
id|info.daddr
op_assign
id|daddr
suffix:semicolon
id|ret
op_assign
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_CONNECT_REQUEST
comma
id|skb
comma
op_amp
id|info
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_connect_indication (self, qos, skb)&n; *&n; *    Notify user layer about the incomming connection&n; *&n; */
DECL|function|ircomm_connect_indication
r_void
id|ircomm_connect_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
(brace
r_int
id|clen
op_assign
l_int|0
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if the packet contains data on the control channel */
r_if
c_cond
(paren
id|skb-&gt;len
OG
l_int|0
)paren
id|clen
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* &n;&t; * If there are any data hiding in the control channel, we must &n;&t; * deliver it first. The side effect is that the control channel &n;&t; * will be removed from the skb&n;&t; */
r_if
c_cond
(paren
id|self-&gt;notify.connect_indication
)paren
id|self-&gt;notify
dot
id|connect_indication
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|info-&gt;qos
comma
id|info-&gt;max_data_size
comma
id|info-&gt;max_header_size
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), missing handler&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_connect_response (self, userdata, max_sdu_size)&n; *&n; *    User accepts connection&n; *&n; */
DECL|function|ircomm_connect_response
r_int
id|ircomm_connect_response
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
(brace
r_int
id|ret
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
id|IRCOMM_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
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
id|ret
op_assign
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_CONNECT_RESPONSE
comma
id|userdata
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function connect_confirm (self, skb)&n; *&n; *    Notify user layer that the link is now connected&n; *&n; */
DECL|function|ircomm_connect_confirm
r_void
id|ircomm_connect_confirm
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
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
id|self-&gt;notify.connect_confirm
)paren
id|self-&gt;notify
dot
id|connect_confirm
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|info-&gt;qos
comma
id|info-&gt;max_data_size
comma
id|info-&gt;max_header_size
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), missing handler&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_data_request (self, userdata)&n; *&n; *    Send IrCOMM data to peer device&n; *&n; */
DECL|function|ircomm_data_request
r_int
id|ircomm_data_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ret
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
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
id|EFAULT
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
op_minus
id|EFAULT
suffix:semicolon
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
id|EFAULT
suffix:semicolon
)paren
suffix:semicolon
id|ret
op_assign
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_DATA_REQUEST
comma
id|skb
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_data_indication (self, skb)&n; *&n; *    Data arrived, so deliver it to user&n; *&n; */
DECL|function|ircomm_data_indication
r_void
id|ircomm_data_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
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
id|ASSERT
c_func
(paren
id|skb-&gt;len
OG
l_int|0
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;notify.data_indication
)paren
id|self-&gt;notify
dot
id|data_indication
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), missing handler&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_process_data (self, skb)&n; *&n; *    Data arrived which may contain control channel data&n; *&n; */
DECL|function|ircomm_process_data
r_void
id|ircomm_process_data
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|clen
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb-&gt;len
OG
l_int|0
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|clen
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* &n;&t; * If there are any data hiding in the control channel, we must &n;&t; * deliver it first. The side effect is that the control channel &n;&t; * will be removed from the skb&n;&t; */
r_if
c_cond
(paren
id|clen
OG
l_int|0
)paren
id|ircomm_control_indication
c_func
(paren
id|self
comma
id|skb
comma
id|clen
)paren
suffix:semicolon
multiline_comment|/* Remove control channel from data channel */
id|skb_pull
c_func
(paren
id|skb
comma
id|clen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
)paren
id|ircomm_data_indication
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(), data was control info only!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_control_request (self, params)&n; *&n; *    Send control data to peer device&n; *&n; */
DECL|function|ircomm_control_request
r_int
id|ircomm_control_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
op_minus
id|EFAULT
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
op_minus
id|EFAULT
suffix:semicolon
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
id|EFAULT
suffix:semicolon
)paren
suffix:semicolon
id|ret
op_assign
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_CONTROL_REQUEST
comma
id|skb
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_control_indication (self, skb)&n; *&n; *    Data has arrived on the control channel&n; *&n; */
DECL|function|ircomm_control_indication
r_static
r_void
id|ircomm_control_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|clen
)paren
(brace
r_struct
id|sk_buff
op_star
id|ctrl_skb
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl_skb
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctrl_skb
)paren
r_return
suffix:semicolon
multiline_comment|/* Remove data channel from control channel */
id|skb_trim
c_func
(paren
id|ctrl_skb
comma
id|clen
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Use udata for delivering data on the control channel */
r_if
c_cond
(paren
id|self-&gt;notify.udata_indication
)paren
id|self-&gt;notify
dot
id|udata_indication
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|ctrl_skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), missing handler&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_disconnect_request (self, userdata, priority)&n; *&n; *    User layer wants to disconnect the IrCOMM connection&n; *&n; */
DECL|function|ircomm_disconnect_request
r_int
id|ircomm_disconnect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
(brace
r_struct
id|ircomm_info
id|info
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
id|IRCOMM_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ret
op_assign
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_DISCONNECT_REQUEST
comma
id|userdata
comma
op_amp
id|info
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function disconnect_indication (self, skb)&n; *&n; *    Tell user that the link has been disconnected&n; *&n; */
DECL|function|ircomm_disconnect_indication
r_void
id|ircomm_disconnect_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|info
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;notify.disconnect_indication
)paren
(brace
id|self-&gt;notify
dot
id|disconnect_indication
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|info-&gt;reason
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), missing handler&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_flow_request (self, flow)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_flow_request
r_void
id|ircomm_flow_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|LOCAL_FLOW
id|flow
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
id|IRCOMM_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;service_type
op_eq
id|IRCOMM_3_WIRE_RAW
)paren
r_return
suffix:semicolon
id|irttp_flow_request
c_func
(paren
id|self-&gt;tsap
comma
id|flow
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n; * Function ircomm_proc_read (buf, start, offset, len, unused)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_proc_read
r_int
id|ircomm_proc_read
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
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
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
id|len
op_assign
l_int|0
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
l_string|&quot;Instance %d:&bslash;n&quot;
comma
id|i
op_increment
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|hashbin_get_first
c_func
(paren
id|ircomm
)paren
suffix:semicolon
r_while
c_loop
(paren
id|self
op_ne
l_int|NULL
)paren
(brace
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
id|len
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|hashbin_get_next
c_func
(paren
id|ircomm
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dag@brattli.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IrCOMM protocol&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|ircomm_init
c_func
(paren
)paren
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
id|ircomm_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
