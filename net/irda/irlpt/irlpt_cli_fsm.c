multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlpt_cli_fsm.c&n; * Version:       0.1&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Jan 12 11:06:00 1999&n; * Modified at:   Sun May  9 13:36:13 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999, Thomas Davis, &lt;ratbert@radiks.net&gt;&n; *     Copyright (c) 1998, Dag Brattli, &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     I, Thomas Davis, provide no warranty for any of this software. This &n; *     material is provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irlpt_common.h&gt;
macro_line|#include &lt;net/irda/irlpt_cli.h&gt;
macro_line|#include &lt;net/irda/irlpt_cli_fsm.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#if 0
r_static
r_char
op_star
id|rcsid
op_assign
l_string|&quot;$Id: irlpt_client_fsm.c,v 1.3 1998/10/05 05:46:44 ratbert Exp $&quot;
suffix:semicolon
macro_line|#endif
r_static
r_int
id|irlpt_client_state_idle
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|irlpt_client_state_query
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|irlpt_client_state_ready
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|irlpt_client_state_waiti
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|irlpt_client_state_conn
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
DECL|variable|irlpt_client_fsm_debug
r_int
id|irlpt_client_fsm_debug
op_assign
l_int|4
suffix:semicolon
DECL|variable|irlpt_client_state
r_int
(paren
op_star
id|irlpt_client_state
(braket
)braket
)paren
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
op_assign
(brace
id|irlpt_client_state_idle
comma
id|irlpt_client_state_query
comma
id|irlpt_client_state_ready
comma
id|irlpt_client_state_waiti
comma
id|irlpt_client_state_conn
comma
)brace
suffix:semicolon
DECL|function|irlpt_client_do_event
r_void
id|irlpt_client_do_event
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
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
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: STATE = %s, EVENT = %s&bslash;n&quot;
comma
id|irlpt_server_fsm_state
(braket
id|self-&gt;state
)braket
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
(paren
op_star
id|irlpt_client_state
(braket
id|self-&gt;state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
comma
id|info
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|irlpt_client_next_state
r_void
id|irlpt_client_next_state
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_CLIENT_STATE
id|state
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: NEXT STATE = %s&bslash;n&quot;
comma
id|irlpt_client_fsm_state
(braket
id|state
)braket
)paren
suffix:semicolon
id|self-&gt;state
op_assign
id|state
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_state_idle (self, event, skb, info)&n; *&n; *    IDLE, We are waiting for an indication that there is a provider&n; *    available.&n; */
DECL|function|irlpt_client_state_idle
r_static
r_int
id|irlpt_client_state_idle
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLPT_DISCOVERY_INDICATION
suffix:colon
multiline_comment|/* Get some values from peer IAS */
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: IRLPT_DISCOVERY_INDICATION, &quot;
l_string|&quot;sending getvaluebyclass command..&bslash;n&quot;
)paren
suffix:semicolon
id|iriap_getvaluebyclass_request
c_func
(paren
l_string|&quot;IrLPT&quot;
comma
l_string|&quot;IrDA:IrLMP:LsapSel&quot;
comma
id|info-&gt;saddr
comma
id|info-&gt;daddr
comma
id|irlpt_client_get_value_confirm
comma
(paren
r_void
op_star
)paren
id|self
)paren
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_QUERY
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: Unknown event %d (%s)&bslash;n&quot;
comma
id|event
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_state_query&n; *&n; *    QUERY, We have queryed the remote IAS and is ready to connect&n; *    to provider, just waiting for the confirm.&n; *&n; */
DECL|function|irlpt_client_state_query
r_static
r_int
id|irlpt_client_state_query
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAS_PROVIDER_AVAIL
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: IAS_PROVIDER_AVAIL&bslash;n&quot;
)paren
suffix:semicolon
id|self-&gt;open_retries
op_assign
l_int|0
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_READY
)paren
suffix:semicolon
id|irlpt_client_do_event
c_func
(paren
id|self
comma
id|IRLPT_CONNECT_REQUEST
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IAS_PROVIDER_NOT_AVAIL
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: IAS_PROVIDER_NOT_AVAIL&bslash;n&quot;
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
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMP_DISCONNECT
suffix:colon
r_case
id|LAP_DISCONNECT
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: LMP_DISCONNECT or LAP_DISCONNECT&bslash;n&quot;
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
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: Unknown event %d (%s)&bslash;n&quot;
comma
id|event
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_state_info &n; *&n; *    INFO, We have issued a GetInfo command and is awaiting a reply.&n; */
DECL|function|irlpt_client_state_ready
r_static
r_int
id|irlpt_client_state_ready
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLPT_CONNECT_REQUEST
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: IRLPT_CONNECT_REQUEST&bslash;n&quot;
)paren
suffix:semicolon
id|irlpt_client_connect_request
c_func
(paren
id|self
)paren
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_WAITI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMP_DISCONNECT
suffix:colon
r_case
id|LAP_DISCONNECT
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: LMP_DISCONNECT or LAP_DISCONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
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
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: Unknown event %d (%s)&bslash;n&quot;
comma
id|event
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_state_waiti &n; *&n; *&n; */
DECL|function|irlpt_client_state_waiti
r_static
r_int
id|irlpt_client_state_waiti
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|LMP_CONNECT
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: LMP_CONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_CONN
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAP_DISCONNECT
suffix:colon
r_case
id|LMP_DISCONNECT
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: LMP_DISCONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
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
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: Unknown event %d (%s)&bslash;n&quot;
comma
id|event
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlpt_client_state_conn (self, event, skb, info)&n; *&n; *    CONN, We have connected to a provider but has not issued any&n; *    commands yet.&n; *&n; */
DECL|function|irlpt_client_state_conn
r_static
r_int
id|irlpt_client_state_conn
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
l_string|&quot;--&gt; &quot;
id|__FUNCTION__
l_string|&quot;:&bslash;n&quot;
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
id|IRLPT_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CLIENT_DATA_INDICATION
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: CLIENT_DATA_INDICATION&bslash;n&quot;
)paren
suffix:semicolon
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_CONN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMP_DISCONNECT
suffix:colon
r_case
id|LAP_DISCONNECT
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: LMP_DISCONNECT/LAP_DISCONNECT&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: waking any sleepers..&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|self-&gt;read_wait
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
id|irlpt_client_next_state
c_func
(paren
id|self
comma
id|IRLPT_CLIENT_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: Unknown event %d (%s)&bslash;n&quot;
comma
id|event
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot; --&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irlpt_client_print_event
r_void
id|irlpt_client_print_event
c_func
(paren
id|IRLPT_EVENT
id|event
)paren
(brace
id|DEBUG
c_func
(paren
id|irlpt_client_fsm_debug
comma
id|__FUNCTION__
l_string|&quot;: IRLPT_EVENT = %s&bslash;n&quot;
comma
id|irlpt_fsm_event
(braket
id|event
)braket
)paren
suffix:semicolon
)brace
eof
