multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_filter.c&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Jan 29 11:16:38 1999&n; * Modified at:   Sat May  8 15:25:23 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/irda/irlan_common.h&gt;
multiline_comment|/*&n; * Function handle_filter_request (self, skb)&n; *&n; *    Handle filter request from client peer device&n; *&n; */
DECL|function|handle_filter_request
r_void
id|handle_filter_request
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
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
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_DIRECTED
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_operation
op_eq
id|DYNAMIC
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Giving peer a dynamic Ethernet address&bslash;n&quot;
)paren
suffix:semicolon
id|self-&gt;provider.mac_address
(braket
l_int|0
)braket
op_assign
l_int|0x40
suffix:semicolon
id|self-&gt;provider.mac_address
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|self-&gt;provider.mac_address
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|self-&gt;provider.mac_address
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Use arbitration value to generate MAC address */
r_if
c_cond
(paren
id|self-&gt;provider.access_type
op_eq
id|ACCESS_PEER
)paren
(brace
id|self-&gt;provider.mac_address
(braket
l_int|4
)braket
op_assign
id|self-&gt;provider.send_arb_val
op_amp
l_int|0xff
suffix:semicolon
id|self-&gt;provider.mac_address
(braket
l_int|5
)braket
op_assign
(paren
id|self-&gt;provider.send_arb_val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Just generate something for now */
id|get_random_bytes
c_func
(paren
id|self-&gt;provider.mac_address
op_plus
l_int|4
comma
l_int|1
)paren
suffix:semicolon
id|get_random_bytes
c_func
(paren
id|self-&gt;provider.mac_address
op_plus
l_int|5
comma
l_int|1
)paren
suffix:semicolon
)brace
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x03
suffix:semicolon
id|irlan_insert_string_param
c_func
(paren
id|skb
comma
l_string|&quot;FILTER_MODE&quot;
comma
l_string|&quot;NONE&quot;
)paren
suffix:semicolon
id|irlan_insert_short_param
c_func
(paren
id|skb
comma
l_string|&quot;MAX_ENTRY&quot;
comma
l_int|0x0001
)paren
suffix:semicolon
id|irlan_insert_array_param
c_func
(paren
id|skb
comma
l_string|&quot;FILTER_ENTRY&quot;
comma
id|self-&gt;provider.mac_address
comma
l_int|6
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_DIRECTED
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|FILTER
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Directed filter on&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_DIRECTED
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|NONE
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Directed filter off&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_BROADCAST
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|FILTER
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Broadcast filter on&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_BROADCAST
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|NONE
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Broadcast filter off&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_MULTICAST
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|FILTER
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Multicast filter on&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_MULTICAST
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_mode
op_eq
id|NONE
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Multicast filter off&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;provider.filter_type
op_eq
id|IRLAN_MULTICAST
)paren
op_logical_and
(paren
id|self-&gt;provider.filter_operation
op_eq
id|GET
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Multicast filter get&bslash;n&quot;
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Success? */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x02
suffix:semicolon
id|irlan_insert_string_param
c_func
(paren
id|skb
comma
l_string|&quot;FILTER_MODE&quot;
comma
l_string|&quot;NONE&quot;
)paren
suffix:semicolon
id|irlan_insert_short_param
c_func
(paren
id|skb
comma
l_string|&quot;MAX_ENTRY&quot;
comma
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Command not supported */
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Not implemented!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function check_request_param (self, param, value)&n; *&n; *    Check parameters in request from peer device&n; *&n; */
DECL|function|irlan_check_command_param
r_void
id|irlan_check_command_param
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
)paren
(brace
id|__u8
op_star
id|bytes
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|bytes
op_assign
id|value
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s, %s&bslash;n&quot;
comma
id|param
comma
id|value
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  This is experimental!! DB.&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;MODE&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|self-&gt;use_udata
op_assign
id|TRUE
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  FILTER_TYPE&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;FILTER_TYPE&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;DIRECTED&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_type
op_assign
id|IRLAN_DIRECTED
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;MULTICAST&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_type
op_assign
id|IRLAN_MULTICAST
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;BROADCAST&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_type
op_assign
id|IRLAN_BROADCAST
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  FILTER_MODE&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;FILTER_MODE&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;ALL&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_mode
op_assign
id|ALL
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;FILTER&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_mode
op_assign
id|FILTER
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;NONE&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_mode
op_assign
id|FILTER
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  FILTER_OPERATION&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;FILTER_OPERATION&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;DYNAMIC&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_operation
op_assign
id|DYNAMIC
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;GET&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;provider.filter_operation
op_assign
id|GET
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Function irlan_print_filter (filter_type, buf)&n; *&n; *    Print status of filter. Used by /proc file system&n; *&n; */
DECL|function|irlan_print_filter
r_int
id|irlan_print_filter
c_func
(paren
r_int
id|filter_type
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_DIRECTED
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;DIRECTED &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_FUNCTIONAL
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;FUNCTIONAL &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_GROUP
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;GROUP &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_MAC_FRAME
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;MAC_FRAME &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_MULTICAST
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;MULTICAST &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_BROADCAST
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;BROADCAST &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter_type
op_amp
id|IRLAN_IPX_SOCKET
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;IPX_SOCKET&quot;
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
