multiline_comment|/*&n; *&t;IP multicast routing support for mrouted 3.6&n; *&n; *&t;&t;(c) 1995 Alan Cox, &lt;alan@cymru.net&gt;&n; *&t;  Linux Consultancy and Custom Driver Development&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#ifdef CONFIG_IP_MROUTE
multiline_comment|/*&n; *&t;Multicast router conrol variables&n; */
DECL|variable|vif_table
r_static
r_struct
id|vif_device
id|vif_table
(braket
id|MAXVIFS
)braket
suffix:semicolon
DECL|variable|vifc_map
r_static
r_int
r_int
id|vifc_map
suffix:semicolon
DECL|variable|mroute_do_pim
r_int
id|mroute_do_pim
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;Delete a VIF entry&n; */
DECL|function|vif_delete
r_static
r_void
id|vif_delete
c_func
(paren
r_struct
id|vif_device
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|v-&gt;flags
op_amp
id|VIFF_TUNNEL
)paren
)paren
(brace
id|v-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_ALLMULTI
suffix:semicolon
id|dev_mc_upload
c_func
(paren
id|v-&gt;dev
)paren
suffix:semicolon
)brace
id|v-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Socket options and virtual interface manipulation. The whole&n; *&t;virtual interface system is a complete heap, but unfortunately&n; *&t;thats how BSD mrouted happens to think. Maybe one day with a proper&n; *&t;MOSPF/PIM router set up we can clean this up.&n; */
DECL|function|ip_mroute_setsockopt
r_int
id|ip_mroute_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|vifctl
id|vif
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_ne
id|MRT_INIT
)paren
(brace
r_if
c_cond
(paren
id|sk
op_ne
id|mroute_socket
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|MRT_INIT
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;type
op_ne
id|SOCK_RAW
op_logical_or
id|sk-&gt;num
op_ne
id|IPPROTO_IGMP
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|optval
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
(paren
r_int
op_star
)paren
id|optval
)paren
op_ne
l_int|1
)paren
(brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mroute_socket
)paren
(brace
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
id|mroute_socket
op_assign
id|sk
suffix:semicolon
multiline_comment|/* Initialise state */
r_return
l_int|0
suffix:semicolon
r_case
id|MRT_DONE
suffix:colon
id|mroute_close
c_func
(paren
id|sk
)paren
suffix:semicolon
id|mroute_socket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|MRT_ADD_VIF
suffix:colon
r_case
id|MRT_DEL_VIF
suffix:colon
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
id|vif
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|optval
comma
r_sizeof
(paren
id|vif
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
op_amp
id|vif
comma
id|optval
comma
r_sizeof
(paren
id|vif
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vif.vifc_vifi
OG
id|MAXVIFS
)paren
(brace
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optname
op_eq
id|MRT_ADD_VIF
)paren
(brace
r_struct
id|vif_device
op_star
id|v
op_assign
op_amp
id|vif_table
(braket
id|vif.vifc_vifi
)braket
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Empty vif ? */
r_if
c_cond
(paren
id|vifc_map
op_amp
(paren
l_int|1
op_lshift
id|vif.vifc_vifi
)paren
)paren
(brace
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
multiline_comment|/* Find the interface */
id|dev
op_assign
id|ip_dev_find
c_func
(paren
id|vif.vifc_lcl_addr.s_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
multiline_comment|/* Must be tunnelled or multicastable */
r_if
c_cond
(paren
id|vif.vifc_flags
op_amp
id|VIFF_TUNNEL
)paren
(brace
r_if
c_cond
(paren
id|vif.vifc_flags
op_amp
id|VIFF_SRCRT
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/* IPIP will do all the work */
)brace
r_else
(brace
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
(brace
multiline_comment|/* Most ethernet cards dont know&n;&t;&t;&t;&t;&t;&t;   how to do this yet.. */
id|dev-&gt;flags
op_or_assign
id|IFF_ALLMULTI
suffix:semicolon
id|dev_mc_upload
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We are stuck.. */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t;&t; *&t;Fill in the VIF structures&n;&t;&t;&t;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
id|v-&gt;rate_limit
op_assign
id|vif.vifc_rate_limit
suffix:semicolon
id|v-&gt;local
op_assign
id|vif.vifc_lcl_addr.s_addr
suffix:semicolon
id|v-&gt;remote
op_assign
id|vif.vifc_rmt_addr.s_addr
suffix:semicolon
id|v-&gt;flags
op_assign
id|vif.vifc_flags
suffix:semicolon
id|v-&gt;threshold
op_assign
id|vif.vifc_threshold
suffix:semicolon
id|v-&gt;dev
op_assign
id|dev
suffix:semicolon
id|v-&gt;bytes_in
op_assign
l_int|0
suffix:semicolon
id|v-&gt;bytes_out
op_assign
l_int|0
suffix:semicolon
id|v-&gt;pkt_in
op_assign
l_int|0
suffix:semicolon
id|v-&gt;pkt_out
op_assign
l_int|0
suffix:semicolon
id|vifc_map
op_or_assign
(paren
l_int|1
op_lshift
id|vif.vifc_vifi
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
multiline_comment|/*&n;&t;&t;&t; *&t;VIF deletion&n;&t;&t;&t; */
(brace
r_struct
id|vif_device
op_star
id|v
op_assign
op_amp
id|vif_table
(braket
id|vif.vifc_vifi
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vifc_map
op_amp
(paren
l_int|1
op_lshift
id|vif.vifc_vifi
)paren
)paren
(brace
id|vif_delete
c_func
(paren
id|v
)paren
suffix:semicolon
id|vifc_map
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|vif.vifc_vifi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Manipulate the forwarding caches. These live&n;&t;&t; *&t;in a sort of kernel/user symbiosis.&n;&t;&t; */
r_case
id|MRT_ADD_MFC
suffix:colon
r_case
id|MRT_DEL_MFC
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Control PIM assert.&n;&t;&t; */
r_case
id|MRT_ASSERT
suffix:colon
r_if
c_cond
(paren
id|optlen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|optval
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|mroute_do_pim
op_assign
(paren
id|optval
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Spurious command, or MRT_VERSION which you cannot&n;&t;&t; *&t;set.&n;&t;&t; */
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Getsock opt support for the multicast routing system.&n; */
DECL|function|ip_mroute_getsockopt
r_int
id|ip_mroute_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_int
id|olr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_ne
id|mroute_socket
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optname
op_ne
id|MRT_VERSION
op_logical_and
id|optname
op_ne
id|MRT_ASSERT
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
id|olr
op_assign
id|get_user
c_func
(paren
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|olr
op_ne
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|optval
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|put_user
c_func
(paren
r_sizeof
(paren
r_int
)paren
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|MRT_VERSION
)paren
(brace
id|put_user
c_func
(paren
l_int|0x0305
comma
(paren
r_int
op_star
)paren
id|optval
)paren
suffix:semicolon
)brace
r_else
id|put_user
c_func
(paren
id|mroute_do_pim
comma
(paren
r_int
op_star
)paren
id|optval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The IP multicast ioctl support routines.&n; */
DECL|function|ipmr_ioctl
r_int
id|ipmr_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
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
suffix:semicolon
r_struct
id|sioc_sg_req
id|sr
suffix:semicolon
r_struct
id|sioc_vif_req
id|vr
suffix:semicolon
r_struct
id|vif_device
op_star
id|vif
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCGETVIFCNT
suffix:colon
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
r_sizeof
(paren
id|vr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
op_amp
id|vr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|sr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vr.vifi
op_ge
id|MAXVIFS
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|vif
op_assign
op_amp
id|vif_table
(braket
id|vr.vifi
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vifc_map
op_amp
(paren
l_int|1
op_lshift
id|vr.vifi
)paren
)paren
(brace
id|vr.icount
op_assign
id|vif-&gt;pkt_in
suffix:semicolon
id|vr.ocount
op_assign
id|vif-&gt;pkt_out
suffix:semicolon
id|vr.ibytes
op_assign
id|vif-&gt;bytes_in
suffix:semicolon
id|vr.obytes
op_assign
id|vif-&gt;bytes_out
suffix:semicolon
id|memcpy_tofs
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|vr
comma
r_sizeof
(paren
id|sr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_case
id|SIOCGETSGCNT
suffix:colon
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
r_sizeof
(paren
id|sr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
op_amp
id|sr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|sr
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|sr
comma
r_sizeof
(paren
id|sr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Close the multicast socket, and clear the vif tables etc&n; */
DECL|function|mroute_close
r_void
id|mroute_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|vif_device
op_star
id|v
op_assign
op_amp
id|vif_table
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Shut down all active vif entries&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAXVIFS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|vifc_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|v-&gt;flags
op_amp
id|VIFF_TUNNEL
)paren
)paren
(brace
id|v-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_ALLMULTI
suffix:semicolon
id|dev_mc_upload
c_func
(paren
id|v-&gt;dev
)paren
suffix:semicolon
)brace
)brace
id|v
op_increment
suffix:semicolon
)brace
id|vifc_map
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|ipmr_device_event
r_static
r_int
id|ipmr_device_event
c_func
(paren
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|vif_device
op_star
id|v
suffix:semicolon
r_int
id|ct
suffix:semicolon
r_if
c_cond
(paren
id|event
op_ne
id|NETDEV_DOWN
)paren
(brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
id|v
op_assign
op_amp
id|vif_table
(braket
l_int|0
)braket
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
id|MAXVIFS
suffix:semicolon
id|ct
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|vifc_map
op_amp
(paren
l_int|1
op_lshift
id|ct
)paren
)paren
op_logical_and
id|v-&gt;dev
op_eq
id|ptr
)paren
(brace
id|vif_delete
c_func
(paren
id|v
)paren
suffix:semicolon
id|vifc_map
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|ct
)paren
suffix:semicolon
)brace
id|v
op_increment
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|ip_mr_notifier
r_static
r_struct
id|notifier_block
id|ip_mr_notifier
op_assign
initialization_block
suffix:semicolon
DECL|function|ip_mr_init
r_void
id|ip_mr_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Linux IP multicast router 0.00pre-working 8)&bslash;n&quot;
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|ip_mr_notifier
)paren
suffix:semicolon
)brace
macro_line|#endif
eof