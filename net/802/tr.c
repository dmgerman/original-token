multiline_comment|/*&n; * NET3:&t;Token ring device handling subroutines&n; * &n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Fixes:       3 Feb 97 Paul Norton &lt;pnorton@cts.com&gt; Minor routing fixes.&n; *              Added rif table to /proc/net/tr_rif and rif timeout to&n; *              /proc/sys/net/token-ring/rif_timeout.&n; *        &n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/arp.h&gt;
r_static
r_void
id|tr_source_route
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|tr_add_rif_info
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|rif_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|macro|TR_SR_DEBUG
mdefine_line|#define TR_SR_DEBUG 0
DECL|typedef|rif_cache
r_typedef
r_struct
id|rif_cache_s
op_star
id|rif_cache
suffix:semicolon
multiline_comment|/*&n; *&t;Each RIF entry we learn is kept this way&n; */
DECL|struct|rif_cache_s
r_struct
id|rif_cache_s
(brace
DECL|member|addr
r_int
r_char
id|addr
(braket
id|TR_ALEN
)braket
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|rcf
id|__u16
id|rcf
suffix:semicolon
DECL|member|rseg
id|__u8
id|rseg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|next
id|rif_cache
id|next
suffix:semicolon
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
DECL|member|local_ring
r_int
r_char
id|local_ring
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RIF_TABLE_SIZE
mdefine_line|#define RIF_TABLE_SIZE 32
multiline_comment|/*&n; *&t;We hash the RIF cache 32 ways. We do after all have to look it&n; *&t;up a lot.&n; */
DECL|variable|rif_table
id|rif_cache
id|rif_table
(braket
id|RIF_TABLE_SIZE
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|RIF_TIMEOUT
mdefine_line|#define RIF_TIMEOUT 60*10*HZ
DECL|macro|RIF_CHECK_INTERVAL
mdefine_line|#define RIF_CHECK_INTERVAL 60*HZ
multiline_comment|/*&n; *&t;Garbage disposal timer.&n; */
DECL|variable|rif_timer
r_static
r_struct
id|timer_list
id|rif_timer
suffix:semicolon
DECL|variable|sysctl_tr_rif_timeout
r_int
id|sysctl_tr_rif_timeout
op_assign
id|RIF_TIMEOUT
suffix:semicolon
multiline_comment|/*&n; *&t;Put the headers on a token ring packet. Token ring source routing&n; *&t;makes this a little more exciting than on ethernet.&n; */
DECL|function|tr_header
r_int
id|tr_header
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
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_struct
id|trh_hdr
op_star
id|trh
op_assign
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
r_struct
id|trllc
op_star
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|trh
op_plus
l_int|1
)paren
suffix:semicolon
id|trh-&gt;ac
op_assign
id|AC
suffix:semicolon
id|trh-&gt;fc
op_assign
id|LLC_FRAME
suffix:semicolon
r_if
c_cond
(paren
id|saddr
)paren
(brace
id|memcpy
c_func
(paren
id|trh-&gt;saddr
comma
id|saddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
id|trh-&gt;saddr
comma
l_int|0
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
multiline_comment|/* Adapter fills in address */
multiline_comment|/*&n;&t; *&t;This is the stuff needed for IP encoding - IP over 802.2&n;&t; *&t;with SNAP.&n;&t; */
id|trllc-&gt;dsap
op_assign
id|trllc-&gt;ssap
op_assign
id|EXTENDED_SAP
suffix:semicolon
id|trllc-&gt;llc
op_assign
id|UI_CMD
suffix:semicolon
id|trllc-&gt;protid
(braket
l_int|0
)braket
op_assign
id|trllc-&gt;protid
(braket
l_int|1
)braket
op_assign
id|trllc-&gt;protid
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|trllc-&gt;ethertype
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Build the destination and then source route the frame&n;&t; */
r_if
c_cond
(paren
id|daddr
)paren
(brace
id|memcpy
c_func
(paren
id|trh-&gt;daddr
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|tr_source_route
c_func
(paren
id|trh
comma
id|dev
)paren
suffix:semicolon
r_return
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
r_return
op_minus
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A neighbour discovery of some species (eg arp) has completed. We&n; *&t;can now send the packet.&n; */
DECL|function|tr_rebuild_header
r_int
id|tr_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|trh_hdr
op_star
id|trh
op_assign
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|trllc
op_star
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
)paren
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;FIXME: We don&squot;t yet support IPv6 over token rings&n;&t; */
r_if
c_cond
(paren
id|trllc-&gt;ethertype
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tr_rebuild_header: Don&squot;t know how to resolve type %04X addresses ?&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|htons
c_func
(paren
id|trllc-&gt;ethertype
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arp_find
c_func
(paren
id|trh-&gt;daddr
comma
id|skb
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|tr_source_route
c_func
(paren
id|trh
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Some of this is a bit hackish. We intercept RIF information&n; *&t;used for source routing. We also grab IP directly and don&squot;t feed&n; *&t;it via SNAP.&n; */
DECL|function|tr_type_trans
r_int
r_int
id|tr_type_trans
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
)paren
(brace
r_struct
id|trh_hdr
op_star
id|trh
op_assign
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|trllc
op_star
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
)paren
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|tr_add_rif_info
c_func
(paren
id|trh
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|trh-&gt;daddr
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|trh-&gt;daddr
comma
id|dev-&gt;broadcast
comma
id|TR_ALEN
)paren
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
)brace
r_else
id|skb-&gt;pkt_type
op_assign
id|PACKET_MULTICAST
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|trh-&gt;daddr
comma
id|dev-&gt;dev_addr
comma
id|TR_ALEN
)paren
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
)brace
r_return
id|trllc-&gt;ethertype
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We try to do source routing... &n; */
DECL|function|tr_source_route
r_static
r_void
id|tr_source_route
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
id|rif_cache
id|entry
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Broadcasts are single route as stated in RFC 1042 &n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|dev-&gt;broadcast
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
)paren
(brace
id|trh-&gt;rcf
op_assign
id|htons
c_func
(paren
(paren
(paren
(paren
r_sizeof
(paren
id|trh-&gt;rcf
)paren
)paren
op_lshift
l_int|8
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_or
id|TR_RCF_FRAME2K
op_or
id|TR_RCF_LIMITED_BROADCAST
)paren
suffix:semicolon
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|hash
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TR_ALEN
suffix:semicolon
id|hash
op_add_assign
id|trh-&gt;daddr
(braket
id|i
op_increment
)braket
)paren
(brace
suffix:semicolon
)brace
id|hash
op_and_assign
id|RIF_TABLE_SIZE
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Walk the hash table and look for an entry&n;&t;&t; */
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry
op_logical_and
id|memcmp
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;If we found an entry we can route the frame.&n;&t;&t; */
r_if
c_cond
(paren
id|entry
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;source routing for %02X %02X %02X %02X %02X %02X&bslash;n&quot;
comma
id|trh-&gt;daddr
(braket
l_int|0
)braket
comma
id|trh-&gt;daddr
(braket
l_int|1
)braket
comma
id|trh-&gt;daddr
(braket
l_int|2
)braket
comma
id|trh-&gt;daddr
(braket
l_int|3
)braket
comma
id|trh-&gt;daddr
(braket
l_int|4
)braket
comma
id|trh-&gt;daddr
(braket
l_int|5
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;local_ring
op_logical_and
(paren
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
(brace
id|trh-&gt;rcf
op_assign
id|entry-&gt;rcf
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|trh-&gt;rseg
(braket
l_int|0
)braket
comma
op_amp
id|entry-&gt;rseg
(braket
l_int|0
)braket
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|trh-&gt;rcf
op_xor_assign
id|htons
c_func
(paren
id|TR_RCF_DIR_BIT
)paren
suffix:semicolon
id|trh-&gt;rcf
op_and_assign
id|htons
c_func
(paren
l_int|0x1fff
)paren
suffix:semicolon
multiline_comment|/* Issam Chehab &lt;ichehab@madge1.demon.co.uk&gt; */
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;entry found with rcf %04x&bslash;n&quot;
comma
id|entry-&gt;rcf
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;entry found but without rcf length, local=%02x&bslash;n&quot;
comma
id|entry-&gt;local_ring
)paren
suffix:semicolon
macro_line|#endif
)brace
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Without the information we simply have to shout&n;&t;&t;&t; *&t;on the wire. The replies should rapidly clean this&n;&t;&t;&t; *&t;situation up.&n;&t;&t;&t; */
id|trh-&gt;rcf
op_assign
id|htons
c_func
(paren
(paren
(paren
(paren
r_sizeof
(paren
id|trh-&gt;rcf
)paren
)paren
op_lshift
l_int|8
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_or
id|TR_RCF_FRAME2K
op_or
id|TR_RCF_LIMITED_BROADCAST
)paren
suffix:semicolon
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;no entry in rif table found - broadcasting frame&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;We have learned some new RIF information for our source&n; *&t;routing.&n; */
DECL|function|tr_add_rif_info
r_static
r_void
id|tr_add_rif_info
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|hash
comma
id|rii_p
op_assign
l_int|0
suffix:semicolon
id|rif_cache
id|entry
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Firstly see if the entry exists&n;&t; */
r_if
c_cond
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_amp
id|TR_RII
)paren
(brace
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
OG
l_int|2
)paren
(brace
id|rii_p
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|hash
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TR_ALEN
suffix:semicolon
id|hash
op_add_assign
id|trh-&gt;saddr
(braket
id|i
op_increment
)braket
)paren
(brace
suffix:semicolon
)brace
id|hash
op_and_assign
id|RIF_TABLE_SIZE
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry
op_logical_and
id|memcmp
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;adding rif_entry: addr:%02X:%02X:%02X:%02X:%02X:%02X rcf:%04X&bslash;n&quot;
comma
id|trh-&gt;saddr
(braket
l_int|0
)braket
comma
id|trh-&gt;saddr
(braket
l_int|1
)braket
comma
id|trh-&gt;saddr
(braket
l_int|2
)braket
comma
id|trh-&gt;saddr
(braket
l_int|3
)braket
comma
id|trh-&gt;saddr
(braket
l_int|4
)braket
comma
id|trh-&gt;saddr
(braket
l_int|5
)braket
comma
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; *&t;Allocate our new entry. A failure to allocate loses&n;&t;&t; *&t;use the information. This is harmless.&n;&t;&t; *&n;&t;&t; *&t;FIXME: We ought to keep some kind of cache size&n;&t;&t; *&t;limiting and adjust the timers to suit.&n;&t;&t; */
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rif_cache_s
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;tr.c: Couldn&squot;t malloc rif cache entry !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rii_p
)paren
(brace
id|entry-&gt;rcf
op_assign
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|entry-&gt;local_ring
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|entry-&gt;local_ring
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;iface
(braket
l_int|0
)braket
)paren
comma
id|dev-&gt;name
comma
l_int|5
)paren
suffix:semicolon
id|entry-&gt;next
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
id|rif_table
(braket
id|hash
)braket
op_assign
id|entry
suffix:semicolon
)brace
r_else
multiline_comment|/* Y. Tahara added */
(brace
multiline_comment|/*&n;&t;&t; *&t;Update existing entries&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;local_ring
)paren
r_if
c_cond
(paren
id|entry-&gt;rcf
op_ne
(paren
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
id|TR_RCF_BROADCAST_MASK
)paren
)paren
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;updating rif_entry: addr:%02X:%02X:%02X:%02X:%02X:%02X rcf:%04X&bslash;n&quot;
comma
id|trh-&gt;saddr
(braket
l_int|0
)braket
comma
id|trh-&gt;saddr
(braket
l_int|1
)braket
comma
id|trh-&gt;saddr
(braket
l_int|2
)braket
comma
id|trh-&gt;saddr
(braket
l_int|3
)braket
comma
id|trh-&gt;saddr
(braket
l_int|4
)braket
comma
id|trh-&gt;saddr
(braket
l_int|5
)braket
comma
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
)paren
suffix:semicolon
macro_line|#endif
id|entry-&gt;rcf
op_assign
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Scan the cache with a timer and see what we need to throw out.&n; */
DECL|function|rif_check_expire
r_static
r_void
id|rif_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
comma
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|RIF_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rif_cache
id|entry
comma
op_star
id|pentry
op_assign
id|rif_table
op_plus
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
op_star
id|pentry
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Out it goes&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|now
op_minus
id|entry-&gt;last_used
)paren
OG
id|sysctl_tr_rif_timeout
)paren
(brace
op_star
id|pentry
op_assign
id|entry-&gt;next
suffix:semicolon
id|kfree_s
c_func
(paren
id|entry
comma
r_sizeof
(paren
r_struct
id|rif_cache_s
)paren
)paren
suffix:semicolon
)brace
r_else
id|pentry
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Reset the timer&n;&t; */
id|del_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
id|rif_timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_tr_rif_timeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Generate the /proc/net information for the token ring RIF&n; *&t;routing.&n; */
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|rif_get_info
r_int
id|rif_get_info
c_func
(paren
r_char
op_star
id|buffer
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
id|length
comma
r_int
id|dummy
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|size
comma
id|i
comma
id|j
comma
id|rcf_len
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
id|rif_cache
id|entry
suffix:semicolon
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;if     TR address       TTL   rcf   routing segments&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|pos
op_add_assign
id|size
suffix:semicolon
id|len
op_add_assign
id|size
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
id|RIF_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|i
)braket
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%s %02X:%02X:%02X:%02X:%02X:%02X %7li &quot;
comma
id|entry-&gt;iface
comma
id|entry-&gt;addr
(braket
l_int|0
)braket
comma
id|entry-&gt;addr
(braket
l_int|1
)braket
comma
id|entry-&gt;addr
(braket
l_int|2
)braket
comma
id|entry-&gt;addr
(braket
l_int|3
)braket
comma
id|entry-&gt;addr
(braket
l_int|4
)braket
comma
id|entry-&gt;addr
(braket
l_int|5
)braket
comma
id|sysctl_tr_rif_timeout
op_minus
(paren
id|now
op_minus
id|entry-&gt;last_used
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;local_ring
)paren
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;local&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%04X&quot;
comma
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
)paren
suffix:semicolon
id|rcf_len
op_assign
(paren
(paren
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|rcf_len
)paren
id|rcf_len
op_rshift_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rcf_len
suffix:semicolon
id|j
op_increment
)paren
(brace
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %04X&quot;
comma
id|ntohs
c_func
(paren
id|entry-&gt;rseg
(braket
id|j
)braket
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
multiline_comment|/* Ending slop */
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Called during bootup.  We don&squot;t actually have to initialise&n; *&t;too much for this.&n; */
DECL|function|rif_init
r_void
id|rif_init
c_func
(paren
r_struct
id|net_proto
op_star
id|unused
)paren
(brace
id|rif_timer.expires
op_assign
id|RIF_TIMEOUT
suffix:semicolon
id|rif_timer.data
op_assign
l_int|0L
suffix:semicolon
id|rif_timer.function
op_assign
id|rif_check_expire
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_register
c_func
(paren
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_NET_TR_RIF
comma
l_int|6
comma
l_string|&quot;tr_rif&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_net_inode_operations
comma
id|rif_get_info
)brace
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
