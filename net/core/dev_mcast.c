multiline_comment|/*&n; *&t;Linux NET3:&t;Multicast List maintenance. &n; *&n; *&t;Authors:&n; *&t;&t;Tim Kordas &lt;tjk@nostromo.eeap.cwru.edu&gt; &n; *&t;&t;Richard Underwood &lt;richard@wuzz.demon.co.uk&gt;&n; *&n; *&t;Stir fried together from the IP multicast and CAP patches above&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&t;&n; *&n; *&t;Fixes:&n; *&t;&t;Alan Cox&t;:&t;Update the device on a real delete&n; *&t;&t;&t;&t;&t;rather than any time but...&n; *&t;&t;Alan Cox&t;:&t;IFF_ALLMULTI support.&n; *&t;&t;Alan Cox&t;: &t;New format set_multicast_list() calls.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;linux/net_alias.h&gt;
multiline_comment|/*&n; *&t;Device multicast list maintenance. &n; *&n; *&t;This is used both by IP and by the user level maintenance functions. &n; *&t;Unlike BSD we maintain a usage count on a given multicast address so &n; *&t;that a casual user application can add/delete multicasts used by &n; *&t;protocols without doing damage to the protocols when it deletes the&n; *&t;entries. It also helps IP as it tracks overlapping maps.&n; */
multiline_comment|/*&n; *&t;Update the multicast list into the physical NIC controller.&n; */
DECL|function|dev_mc_upload
r_void
id|dev_mc_upload
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* Don&squot;t do anything till we up the interface&n;&t;   [dev_open will call this function so the list will&n;&t;    stay sane] */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;An aliased device should end up with the combined&n;&t; *&t;multicast list of all its aliases. &n;&t; *&t;[Check this is still ok -AC]&n;&t; */
id|dev
op_assign
id|net_alias_main_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Devices with no set multicast don&squot;t get set &n;&t; */
r_if
c_cond
(paren
id|dev-&gt;set_multicast_list
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|dev
op_member_access_from_pointer
id|set_multicast_list
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Delete a device level multicast&n; */
DECL|function|dev_mc_delete
r_void
id|dev_mc_delete
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|alen
comma
r_int
id|all
)paren
(brace
r_struct
id|dev_mc_list
op_star
op_star
id|dmi
suffix:semicolon
id|dev
op_assign
id|net_alias_main_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dmi
op_assign
op_amp
id|dev-&gt;mc_list
suffix:semicolon
op_star
id|dmi
op_ne
l_int|NULL
suffix:semicolon
id|dmi
op_assign
op_amp
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|next
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Find the entry we want to delete. The device could&n;&t;&t; *&t;have variable length entries so check these too.&n;&t;&t; */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|dmi_addr
comma
id|addr
comma
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|dmi_addrlen
)paren
op_eq
l_int|0
op_logical_and
id|alen
op_eq
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|dmi_addrlen
)paren
(brace
r_struct
id|dev_mc_list
op_star
id|tmp
op_assign
op_star
id|dmi
suffix:semicolon
r_if
c_cond
(paren
op_decrement
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|dmi_users
op_logical_and
op_logical_neg
id|all
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *&t;Last user. So delete the entry.&n;&t;&t;&t; */
op_star
id|dmi
op_assign
(paren
op_star
id|dmi
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|dev-&gt;mc_count
op_decrement
suffix:semicolon
id|kfree_s
c_func
(paren
id|tmp
comma
r_sizeof
(paren
op_star
id|tmp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;We have altered the list, so the card&n;&t;&t;&t; *&t;loaded filter is now wrong. Fix it&n;&t;&t;&t; */
id|dev_mc_upload
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;Add a device level multicast&n; */
DECL|function|dev_mc_add
r_void
id|dev_mc_add
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|alen
comma
r_int
id|newonly
)paren
(brace
r_struct
id|dev_mc_list
op_star
id|dmi
suffix:semicolon
id|dev
op_assign
id|net_alias_main_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dmi
op_assign
id|dev-&gt;mc_list
suffix:semicolon
id|dmi
op_ne
l_int|NULL
suffix:semicolon
id|dmi
op_assign
id|dmi-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|dmi-&gt;dmi_addr
comma
id|addr
comma
id|dmi-&gt;dmi_addrlen
)paren
op_eq
l_int|0
op_logical_and
id|dmi-&gt;dmi_addrlen
op_eq
id|alen
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newonly
)paren
(brace
id|dmi-&gt;dmi_users
op_increment
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
id|dmi
op_assign
(paren
r_struct
id|dev_mc_list
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dmi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmi
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* GFP_KERNEL so can&squot;t happen anyway */
id|memcpy
c_func
(paren
id|dmi-&gt;dmi_addr
comma
id|addr
comma
id|alen
)paren
suffix:semicolon
id|dmi-&gt;dmi_addrlen
op_assign
id|alen
suffix:semicolon
id|dmi-&gt;next
op_assign
id|dev-&gt;mc_list
suffix:semicolon
id|dmi-&gt;dmi_users
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;mc_list
op_assign
id|dmi
suffix:semicolon
id|dev-&gt;mc_count
op_increment
suffix:semicolon
id|dev_mc_upload
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Discard multicast list when a device is downed&n; */
DECL|function|dev_mc_discard
r_void
id|dev_mc_discard
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|net_alias_is
c_func
(paren
id|dev
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;mc_list
op_ne
l_int|NULL
)paren
(brace
r_struct
id|dev_mc_list
op_star
id|tmp
op_assign
id|dev-&gt;mc_list
suffix:semicolon
id|dev-&gt;mc_list
op_assign
id|dev-&gt;mc_list-&gt;next
suffix:semicolon
id|kfree_s
c_func
(paren
id|tmp
comma
r_sizeof
(paren
op_star
id|tmp
)paren
)paren
suffix:semicolon
)brace
id|dev-&gt;mc_count
op_assign
l_int|0
suffix:semicolon
)brace
eof
