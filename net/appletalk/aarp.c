multiline_comment|/*&n; *&t;AARP:&t;&t;An implementation of the Appletalk aarp protocol for&n; *&t;&t;&t;ethernet &squot;ELAP&squot;.&n; *&n; *&t;&t;Alan Cox  &lt;Alan.Cox@linux.org&gt;&n; *&n; *&t;This doesn&squot;t fit cleanly with the IP arp. Potentially we can use&n; *&t;the generic neighbour discovery code to clean this up.&n; *&n; *&t;FIXME:&n; *&t;&t;We ought to handle the retransmits with a single list and a &n; *&t;separate fast timer for when it is needed.&n; *&t;&t;Use neighbour discovery code.&n; *&t;&t;Token Ring Support.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&n; *&t;References:&n; *&t;&t;Inside Appletalk (2nd Ed).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE) 
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;net/psnap.h&gt;
macro_line|#include &lt;linux/atalk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|sysctl_aarp_expiry_time
r_int
id|sysctl_aarp_expiry_time
op_assign
id|AARP_EXPIRY_TIME
suffix:semicolon
DECL|variable|sysctl_aarp_tick_time
r_int
id|sysctl_aarp_tick_time
op_assign
id|AARP_TICK_TIME
suffix:semicolon
DECL|variable|sysctl_aarp_retransmit_limit
r_int
id|sysctl_aarp_retransmit_limit
op_assign
id|AARP_RETRANSMIT_LIMIT
suffix:semicolon
DECL|variable|sysctl_aarp_resolve_time
r_int
id|sysctl_aarp_resolve_time
op_assign
id|AARP_RESOLVE_TIME
suffix:semicolon
multiline_comment|/*&n; *&t;Lists of aarp entries&n; */
DECL|struct|aarp_entry
r_struct
id|aarp_entry
(brace
multiline_comment|/* These first two are only used for unresolved entries */
DECL|member|last_sent
r_int
r_int
id|last_sent
suffix:semicolon
multiline_comment|/* Last time we xmitted the aarp request */
DECL|member|packet_queue
r_struct
id|sk_buff_head
id|packet_queue
suffix:semicolon
multiline_comment|/* Queue of frames wait for resolution */
DECL|member|expires_at
r_int
r_int
id|expires_at
suffix:semicolon
multiline_comment|/* Entry expiry time */
DECL|member|target_addr
r_struct
id|at_addr
id|target_addr
suffix:semicolon
multiline_comment|/* DDP Address */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device to use */
DECL|member|hwaddr
r_char
id|hwaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Physical i/f address of target/router */
DECL|member|xmit_count
r_int
r_int
id|xmit_count
suffix:semicolon
multiline_comment|/* When this hits 10 we give up */
DECL|member|next
r_struct
id|aarp_entry
op_star
id|next
suffix:semicolon
multiline_comment|/* Next entry in chain */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Hashed list of resolved and unresolved entries&n; */
DECL|variable|resolved
DECL|variable|unresolved
r_static
r_struct
id|aarp_entry
op_star
id|resolved
(braket
id|AARP_HASH_SIZE
)braket
comma
op_star
id|unresolved
(braket
id|AARP_HASH_SIZE
)braket
suffix:semicolon
DECL|variable|unresolved_count
r_static
r_int
id|unresolved_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;Used to walk the list and purge/kick entries.&n; */
DECL|variable|aarp_timer
r_static
r_struct
id|timer_list
id|aarp_timer
suffix:semicolon
multiline_comment|/*&n; *&t;Delete an aarp queue&n; */
DECL|function|aarp_expire
r_static
r_void
id|aarp_expire
c_func
(paren
r_struct
id|aarp_entry
op_star
id|a
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
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
id|a-&gt;packet_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
id|kfree_s
c_func
(paren
id|a
comma
r_sizeof
(paren
op_star
id|a
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send an aarp queue entry request&n; */
DECL|function|aarp_send_query
r_static
r_void
id|aarp_send_query
c_func
(paren
r_struct
id|aarp_entry
op_star
id|a
)paren
(brace
r_static
r_char
id|aarp_eth_multicast
(braket
id|ETH_ALEN
)braket
op_assign
initialization_block
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|a-&gt;dev
suffix:semicolon
r_int
id|len
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|elapaarp
)paren
op_plus
id|aarp_dl-&gt;header_length
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_struct
id|elapaarp
op_star
id|eah
suffix:semicolon
r_struct
id|at_addr
op_star
id|sat
op_assign
id|atalk_find_dev_addr
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
op_logical_or
id|sat
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Set up the buffer.&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
op_plus
id|aarp_dl-&gt;header_length
)paren
suffix:semicolon
id|eah
op_assign
(paren
r_struct
id|elapaarp
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|elapaarp
)paren
)paren
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Set up the ARP.&n;&t; */
id|eah-&gt;hw_type
op_assign
id|htons
c_func
(paren
id|AARP_HW_TYPE_ETHERNET
)paren
suffix:semicolon
id|eah-&gt;pa_type
op_assign
id|htons
c_func
(paren
id|ETH_P_ATALK
)paren
suffix:semicolon
id|eah-&gt;hw_len
op_assign
id|ETH_ALEN
suffix:semicolon
id|eah-&gt;pa_len
op_assign
id|AARP_PA_ALEN
suffix:semicolon
id|eah-&gt;function
op_assign
id|htons
c_func
(paren
id|AARP_REQUEST
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eah-&gt;hw_src
comma
id|dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_src_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_src_net
op_assign
id|sat-&gt;s_net
suffix:semicolon
id|eah-&gt;pa_src_node
op_assign
id|sat-&gt;s_node
suffix:semicolon
id|memset
c_func
(paren
id|eah-&gt;hw_dst
comma
l_char|&squot;&bslash;0&squot;
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_dst_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_dst_net
op_assign
id|a-&gt;target_addr.s_net
suffix:semicolon
id|eah-&gt;pa_dst_node
op_assign
id|a-&gt;target_addr.s_node
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add ELAP headers and set target to the AARP multicast.&n;&t; */
id|aarp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|aarp_dl
comma
id|skb
comma
id|aarp_eth_multicast
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send it.&n;&t; */
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Update the sending count&n;&t; */
id|a-&gt;xmit_count
op_increment
suffix:semicolon
)brace
DECL|function|aarp_send_reply
r_static
r_void
id|aarp_send_reply
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|at_addr
op_star
id|us
comma
r_struct
id|at_addr
op_star
id|them
comma
r_int
r_char
op_star
id|sha
)paren
(brace
r_int
id|len
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|elapaarp
)paren
op_plus
id|aarp_dl-&gt;header_length
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_struct
id|elapaarp
op_star
id|eah
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Set up the buffer.&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
op_plus
id|aarp_dl-&gt;header_length
)paren
suffix:semicolon
id|eah
op_assign
(paren
r_struct
id|elapaarp
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|elapaarp
)paren
)paren
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Set up the ARP.&n;&t; */
id|eah-&gt;hw_type
op_assign
id|htons
c_func
(paren
id|AARP_HW_TYPE_ETHERNET
)paren
suffix:semicolon
id|eah-&gt;pa_type
op_assign
id|htons
c_func
(paren
id|ETH_P_ATALK
)paren
suffix:semicolon
id|eah-&gt;hw_len
op_assign
id|ETH_ALEN
suffix:semicolon
id|eah-&gt;pa_len
op_assign
id|AARP_PA_ALEN
suffix:semicolon
id|eah-&gt;function
op_assign
id|htons
c_func
(paren
id|AARP_REPLY
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eah-&gt;hw_src
comma
id|dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_src_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_src_net
op_assign
id|us-&gt;s_net
suffix:semicolon
id|eah-&gt;pa_src_node
op_assign
id|us-&gt;s_node
suffix:semicolon
r_if
c_cond
(paren
id|sha
op_eq
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|eah-&gt;hw_dst
comma
l_char|&squot;&bslash;0&squot;
comma
id|ETH_ALEN
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|eah-&gt;hw_dst
comma
id|sha
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_dst_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_dst_net
op_assign
id|them-&gt;s_net
suffix:semicolon
id|eah-&gt;pa_dst_node
op_assign
id|them-&gt;s_node
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add ELAP headers and set target to the AARP multicast.&n;&t; */
id|aarp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|aarp_dl
comma
id|skb
comma
id|sha
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send it.&n;&t; */
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send probe frames. Called from atif_probe_device.&n; */
DECL|function|aarp_send_probe
r_void
id|aarp_send_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|at_addr
op_star
id|us
)paren
(brace
r_int
id|len
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|elapaarp
)paren
op_plus
id|aarp_dl-&gt;header_length
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_struct
id|elapaarp
op_star
id|eah
suffix:semicolon
r_static
r_char
id|aarp_eth_multicast
(braket
id|ETH_ALEN
)braket
op_assign
initialization_block
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Set up the buffer.&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
op_plus
id|aarp_dl-&gt;header_length
)paren
suffix:semicolon
id|eah
op_assign
(paren
r_struct
id|elapaarp
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|elapaarp
)paren
)paren
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Set up the ARP.&n;&t; */
id|eah-&gt;hw_type
op_assign
id|htons
c_func
(paren
id|AARP_HW_TYPE_ETHERNET
)paren
suffix:semicolon
id|eah-&gt;pa_type
op_assign
id|htons
c_func
(paren
id|ETH_P_ATALK
)paren
suffix:semicolon
id|eah-&gt;hw_len
op_assign
id|ETH_ALEN
suffix:semicolon
id|eah-&gt;pa_len
op_assign
id|AARP_PA_ALEN
suffix:semicolon
id|eah-&gt;function
op_assign
id|htons
c_func
(paren
id|AARP_PROBE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eah-&gt;hw_src
comma
id|dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_src_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_src_net
op_assign
id|us-&gt;s_net
suffix:semicolon
id|eah-&gt;pa_src_node
op_assign
id|us-&gt;s_node
suffix:semicolon
id|memset
c_func
(paren
id|eah-&gt;hw_dst
comma
l_char|&squot;&bslash;0&squot;
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|eah-&gt;pa_dst_zero
op_assign
l_int|0
suffix:semicolon
id|eah-&gt;pa_dst_net
op_assign
id|us-&gt;s_net
suffix:semicolon
id|eah-&gt;pa_dst_node
op_assign
id|us-&gt;s_node
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add ELAP headers and set target to the AARP multicast.&n;&t; */
id|aarp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|aarp_dl
comma
id|skb
comma
id|aarp_eth_multicast
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send it.&n;&t; */
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle an aarp timer expire&n; */
DECL|function|aarp_expire_timer
r_static
r_void
id|aarp_expire_timer
c_func
(paren
r_struct
id|aarp_entry
op_star
op_star
id|n
)paren
(brace
r_struct
id|aarp_entry
op_star
id|t
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|n
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Expired ? */
r_if
c_cond
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|expires_at
OL
id|jiffies
)paren
(brace
id|t
op_assign
op_star
id|n
suffix:semicolon
op_star
id|n
op_assign
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|aarp_expire
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_else
id|n
op_assign
op_amp
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Kick all pending requests 5 times a second.&n; */
DECL|function|aarp_kick
r_static
r_void
id|aarp_kick
c_func
(paren
r_struct
id|aarp_entry
op_star
op_star
id|n
)paren
(brace
r_struct
id|aarp_entry
op_star
id|t
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|n
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Expired - if this will be the 11th transmit, we delete&n;&t;&t;   instead */
r_if
c_cond
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|xmit_count
op_ge
id|sysctl_aarp_retransmit_limit
)paren
(brace
id|t
op_assign
op_star
id|n
suffix:semicolon
op_star
id|n
op_assign
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|aarp_expire
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_else
(brace
id|aarp_send_query
c_func
(paren
op_star
id|n
)paren
suffix:semicolon
id|n
op_assign
op_amp
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;A device has gone down. Take all entries referring to the device&n; *&t;and remove them.&n; */
DECL|function|aarp_expire_device
r_static
r_void
id|aarp_expire_device
c_func
(paren
r_struct
id|aarp_entry
op_star
op_star
id|n
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|aarp_entry
op_star
id|t
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|n
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|dev
op_eq
id|dev
)paren
(brace
id|t
op_assign
op_star
id|n
suffix:semicolon
op_star
id|n
op_assign
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|aarp_expire
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_else
id|n
op_assign
op_amp
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Handle the timer event &n; */
DECL|function|aarp_expire_timeout
r_static
r_void
id|aarp_expire_timeout
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ct
op_assign
l_int|0
suffix:semicolon
id|ct
OL
id|AARP_HASH_SIZE
suffix:semicolon
id|ct
op_increment
)paren
(brace
id|aarp_expire_timer
c_func
(paren
op_amp
id|resolved
(braket
id|ct
)braket
)paren
suffix:semicolon
id|aarp_kick
c_func
(paren
op_amp
id|unresolved
(braket
id|ct
)braket
)paren
suffix:semicolon
id|aarp_expire_timer
c_func
(paren
op_amp
id|unresolved
(braket
id|ct
)braket
)paren
suffix:semicolon
)brace
id|del_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unresolved_count
op_eq
l_int|0
)paren
(brace
id|aarp_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_aarp_expiry_time
suffix:semicolon
)brace
r_else
id|aarp_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_aarp_tick_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Network device notifier chain handler.&n; */
DECL|function|aarp_device_event
r_static
r_int
id|aarp_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_DOWN
)paren
(brace
r_for
c_loop
(paren
id|ct
op_assign
l_int|0
suffix:semicolon
id|ct
OL
id|AARP_HASH_SIZE
suffix:semicolon
id|ct
op_increment
)paren
(brace
id|aarp_expire_device
c_func
(paren
op_amp
id|resolved
(braket
id|ct
)braket
comma
id|ptr
)paren
suffix:semicolon
id|aarp_expire_device
c_func
(paren
op_amp
id|unresolved
(braket
id|ct
)braket
comma
id|ptr
)paren
suffix:semicolon
)brace
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Create a new aarp entry.&n; */
DECL|function|aarp_alloc
r_static
r_struct
id|aarp_entry
op_star
id|aarp_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|aarp_entry
op_star
id|a
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|aarp_entry
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|skb_queue_head_init
c_func
(paren
op_amp
id|a-&gt;packet_queue
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
multiline_comment|/*&n; * Find an entry. We might return an expired but not yet purged entry. We&n; * don&squot;t care as it will do no harm.&n; */
DECL|function|aarp_find_entry
r_static
r_struct
id|aarp_entry
op_star
id|aarp_find_entry
c_func
(paren
r_struct
id|aarp_entry
op_star
id|list
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|at_addr
op_star
id|sat
)paren
(brace
r_int
r_int
id|flags
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
r_while
c_loop
(paren
id|list
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;target_addr.s_net
op_eq
id|sat-&gt;s_net
op_logical_and
id|list-&gt;target_addr.s_node
op_eq
id|sat-&gt;s_node
op_logical_and
id|list-&gt;dev
op_eq
id|dev
)paren
(brace
r_break
suffix:semicolon
)brace
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send a DDP frame&n; */
DECL|function|aarp_send_ddp
r_int
id|aarp_send_ddp
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|at_addr
op_star
id|sa
comma
r_void
op_star
id|hwaddr
)paren
(brace
r_static
r_char
id|ddp_eth_multicast
(braket
id|ETH_ALEN
)braket
op_assign
initialization_block
suffix:semicolon
r_int
id|hash
suffix:semicolon
r_struct
id|aarp_entry
op_star
id|a
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for localtalk first&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_LOCALTLK
)paren
(brace
r_struct
id|at_addr
op_star
id|at
op_assign
id|atalk_find_dev_addr
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ddpehdr
op_star
id|ddp
op_assign
(paren
r_struct
id|ddpehdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_int
id|ft
op_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Compressible ?&n;&t;&t; * &n;&t;&t; *&t;IFF: src_net==dest_net==device_net&n;&t;&t; *&t;(zero matches anything)&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|ddp-&gt;deh_snet
op_eq
l_int|0
op_logical_or
id|at-&gt;s_net
op_eq
id|ddp-&gt;deh_snet
)paren
op_logical_and
(paren
id|ddp-&gt;deh_dnet
op_eq
l_int|0
op_logical_or
id|at-&gt;s_net
op_eq
id|ddp-&gt;deh_dnet
)paren
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ddpehdr
)paren
op_minus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;The upper two remaining bytes are the port &n;&t;&t;&t; *&t;numbers&t;we just happen to need. Now put the &n;&t;&t;&t; *&t;length in the lower two.&n;&t;&t;&t; */
op_star
(paren
(paren
id|__u16
op_star
)paren
id|skb-&gt;data
)paren
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|ft
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Nice and easy. No AARP type protocols occur here&n;&t;&t; *&t;so we can just shovel it out with a 3 byte LLAP header&n;&t;&t; */
id|skb_push
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|sa-&gt;s_node
suffix:semicolon
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
id|at-&gt;s_node
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_assign
id|ft
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
id|skb-&gt;priority
op_assign
id|skb-&gt;sk-&gt;priority
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;On a PPP link we neither compress nor aarp.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_PPP
)paren
(brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_PPPTALK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
id|skb-&gt;priority
op_assign
id|skb-&gt;sk-&gt;priority
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Non ELAP we cannot do.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_ATALK
)paren
suffix:semicolon
id|hash
op_assign
id|sa-&gt;s_node
op_mod
(paren
id|AARP_HASH_SIZE
op_minus
l_int|1
)paren
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
multiline_comment|/*&n;&t; *&t;Do we have a resolved entry ?&n;&t; */
r_if
c_cond
(paren
id|sa-&gt;s_node
op_eq
id|ATADDR_BCAST
)paren
(brace
id|ddp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|ddp_dl
comma
id|skb
comma
id|ddp_eth_multicast
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
id|skb-&gt;priority
op_assign
id|skb-&gt;sk-&gt;priority
suffix:semicolon
)brace
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|a
op_assign
id|aarp_find_entry
c_func
(paren
id|resolved
(braket
id|hash
)braket
comma
id|dev
comma
id|sa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Return 1 and fill in the address&n;&t;&t; */
id|a-&gt;expires_at
op_assign
id|jiffies
op_plus
id|sysctl_aarp_expiry_time
op_star
l_int|10
suffix:semicolon
id|ddp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|ddp_dl
comma
id|skb
comma
id|a-&gt;hwaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
id|skb-&gt;priority
op_assign
id|skb-&gt;sk-&gt;priority
suffix:semicolon
)brace
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Do we have an unresolved entry: This is the less common path&n;&t; */
id|a
op_assign
id|aarp_find_entry
c_func
(paren
id|unresolved
(braket
id|hash
)braket
comma
id|dev
comma
id|sa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Queue onto the unresolved queue&n;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|a-&gt;packet_queue
comma
id|skb
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Allocate a new entry&n;&t; */
id|a
op_assign
id|aarp_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Whoops slipped... good job it&squot;s an unreliable &n;&t;&t; *&t;protocol 8)&t;&n;&t;&t; */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Set up the queue&n;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|a-&gt;packet_queue
comma
id|skb
)paren
suffix:semicolon
id|a-&gt;expires_at
op_assign
id|jiffies
op_plus
id|sysctl_aarp_resolve_time
suffix:semicolon
id|a-&gt;dev
op_assign
id|dev
suffix:semicolon
id|a-&gt;next
op_assign
id|unresolved
(braket
id|hash
)braket
suffix:semicolon
id|a-&gt;target_addr
op_assign
op_star
id|sa
suffix:semicolon
id|a-&gt;xmit_count
op_assign
l_int|0
suffix:semicolon
id|unresolved
(braket
id|hash
)braket
op_assign
id|a
suffix:semicolon
id|unresolved_count
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send an initial request for the address&n;&t; */
id|aarp_send_query
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Switch to fast timer if needed (That is if this is the&n;&t; *&t;first unresolved entry to get added)&n;&t; */
r_if
c_cond
(paren
id|unresolved_count
op_eq
l_int|1
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
id|aarp_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_aarp_tick_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Tell the ddp layer we have taken over for this frame.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;An entry in the aarp unresolved queue has become resolved. Send&n; *&t;all the frames queued under it.&n; */
DECL|function|aarp_resolved
r_static
r_void
id|aarp_resolved
c_func
(paren
r_struct
id|aarp_entry
op_star
op_star
id|list
comma
r_struct
id|aarp_entry
op_star
id|a
comma
r_int
id|hash
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|list
op_eq
id|a
)paren
(brace
id|unresolved_count
op_decrement
suffix:semicolon
op_star
id|list
op_assign
id|a-&gt;next
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; *&t;Move into the resolved list &n;&t;&t;&t; */
id|a-&gt;next
op_assign
id|resolved
(braket
id|hash
)braket
suffix:semicolon
id|resolved
(braket
id|hash
)braket
op_assign
id|a
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Kick frames off &n;&t;&t;&t; */
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
id|a-&gt;packet_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|a-&gt;expires_at
op_assign
id|jiffies
op_plus
id|sysctl_aarp_expiry_time
op_star
l_int|10
suffix:semicolon
id|ddp_dl
op_member_access_from_pointer
id|datalink_header
c_func
(paren
id|ddp_dl
comma
id|skb
comma
id|a-&gt;hwaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
id|skb-&gt;priority
op_assign
id|skb-&gt;sk-&gt;priority
suffix:semicolon
)brace
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
id|list
op_assign
op_amp
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;This is called by the SNAP driver whenever we see an AARP SNAP&n; *&t;frame. We currently only support ethernet.&n; */
DECL|function|aarp_rcv
r_static
r_int
id|aarp_rcv
c_func
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
comma
r_struct
id|packet_type
op_star
id|pt
)paren
(brace
r_struct
id|elapaarp
op_star
id|ea
op_assign
(paren
r_struct
id|elapaarp
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_struct
id|aarp_entry
op_star
id|a
suffix:semicolon
r_struct
id|at_addr
id|sa
comma
op_star
id|ma
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|hash
suffix:semicolon
r_struct
id|atalk_iface
op_star
id|ifa
suffix:semicolon
multiline_comment|/*&n;&t; *&t;We only do ethernet SNAP AARP&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Frame size ok ?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|ea
)paren
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ea-&gt;function
op_assign
id|ntohs
c_func
(paren
id|ea-&gt;function
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Sanity check fields.&n;&t; */
r_if
c_cond
(paren
id|ea-&gt;function
id|AARP_PROBE
op_logical_or
id|ea-&gt;hw_len
op_ne
id|ETH_ALEN
op_logical_or
id|ea-&gt;pa_len
op_ne
id|AARP_PA_ALEN
op_logical_or
id|ea-&gt;pa_src_zero
op_ne
l_int|0
op_logical_or
id|ea-&gt;pa_dst_zero
op_ne
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Looks good&n;&t; */
id|hash
op_assign
id|ea-&gt;pa_src_node
op_mod
(paren
id|AARP_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Build an address&n;&t; */
id|sa.s_node
op_assign
id|ea-&gt;pa_src_node
suffix:semicolon
id|sa.s_net
op_assign
id|ea-&gt;pa_src_net
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Process the packet&n;&t; */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for replies of me&n;&t; */
id|ifa
op_assign
id|atalk_find_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifa
op_eq
l_int|NULL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifa-&gt;status
op_amp
id|ATIF_PROBE
)paren
(brace
r_if
c_cond
(paren
id|ifa-&gt;address.s_node
op_eq
id|ea-&gt;pa_dst_node
op_logical_and
id|ifa-&gt;address.s_net
op_eq
id|ea-&gt;pa_dst_net
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Fail the probe (in use)&n;&t;&t;&t; */
id|ifa-&gt;status
op_or_assign
id|ATIF_PROBE_FAIL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|ea-&gt;function
)paren
(brace
r_case
id|AARP_REPLY
suffix:colon
r_if
c_cond
(paren
id|unresolved_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Speed up */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *&t;Find the entry&t;&n;&t;&t;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_assign
id|aarp_find_entry
c_func
(paren
id|unresolved
(braket
id|hash
)braket
comma
id|dev
comma
op_amp
id|sa
)paren
)paren
op_eq
l_int|NULL
op_logical_or
id|dev
op_ne
id|a-&gt;dev
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *&t;We can fill one in - this is good&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|a-&gt;hwaddr
comma
id|ea-&gt;hw_src
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|aarp_resolved
c_func
(paren
op_amp
id|unresolved
(braket
id|hash
)braket
comma
id|a
comma
id|hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unresolved_count
op_eq
l_int|0
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
id|aarp_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_aarp_expiry_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AARP_REQUEST
suffix:colon
r_case
id|AARP_PROBE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *&t;If it is my address set ma to my address and reply. We can treat probe and&n;&t;&t;&t; *&t;request the same. Probe simply means we shouldn&squot;t cache the querying host, &n;&t;&t;&t; *&t;as in a probe they are proposing an address not using one.&n;&t;&t;&t; */
id|ma
op_assign
op_amp
id|ifa-&gt;address
suffix:semicolon
id|sa.s_node
op_assign
id|ea-&gt;pa_dst_node
suffix:semicolon
id|sa.s_net
op_assign
id|ea-&gt;pa_dst_net
suffix:semicolon
r_if
c_cond
(paren
id|sa.s_node
op_ne
id|ma-&gt;s_node
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sa.s_net
op_logical_and
id|ma-&gt;s_net
op_logical_and
id|sa.s_net
op_ne
id|ma-&gt;s_net
)paren
(brace
r_break
suffix:semicolon
)brace
id|sa.s_node
op_assign
id|ea-&gt;pa_src_node
suffix:semicolon
id|sa.s_net
op_assign
id|ea-&gt;pa_src_net
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;aarp_my_address has found the address to use for us.&n;&t;&t;&t; */
id|aarp_send_reply
c_func
(paren
id|dev
comma
id|ma
comma
op_amp
id|sa
comma
id|ea-&gt;hw_src
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|aarp_notifier
r_static
r_struct
id|notifier_block
id|aarp_notifier
op_assign
initialization_block
suffix:semicolon
DECL|variable|aarp_snap_id
r_static
r_char
id|aarp_snap_id
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|aarp_proto_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|aarp_dl
op_assign
id|register_snap_client
c_func
(paren
id|aarp_snap_id
comma
id|aarp_rcv
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unable to register AARP with SNAP.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
id|aarp_timer.function
op_assign
id|aarp_expire_timeout
suffix:semicolon
id|aarp_timer.data
op_assign
l_int|0
suffix:semicolon
id|aarp_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_aarp_expiry_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|aarp_notifier
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove the AARP entries associated with a device.&n; */
DECL|function|aarp_device_down
r_void
id|aarp_device_down
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ct
op_assign
l_int|0
suffix:semicolon
id|ct
OL
id|AARP_HASH_SIZE
suffix:semicolon
id|ct
op_increment
)paren
(brace
id|aarp_expire_device
c_func
(paren
op_amp
id|resolved
(braket
id|ct
)braket
comma
id|dev
)paren
suffix:semicolon
id|aarp_expire_device
c_func
(paren
op_amp
id|unresolved
(braket
id|ct
)braket
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/*&n; * General module cleanup. Called from cleanup_module() in ddp.c.&n; */
DECL|function|aarp_cleanup_module
r_void
id|aarp_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|aarp_timer
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|aarp_notifier
)paren
suffix:semicolon
id|unregister_snap_client
c_func
(paren
id|aarp_snap_id
)paren
suffix:semicolon
)brace
macro_line|#endif  /* MODULE */
macro_line|#endif  /* CONFIG_ATALK || CONFIG_ATALK_MODULE */
eof
