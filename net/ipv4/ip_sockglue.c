multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The IP to API glue.&n; *&t;&t;&n; * Version:&t;$Id: ip_sockglue.c,v 1.49 2000/07/08 00:20:43 davem Exp $&n; *&n; * Authors:&t;see ip.c&n; *&n; * Fixes:&n; *&t;&t;Many&t;&t;:&t;Split from ip.c , see ip.c for history.&n; *&t;&t;Martin Mares&t;:&t;TOS setting fixed.&n; *&t;&t;Alan Cox&t;:&t;Fixed a couple of oopses in Martin&squot;s &n; *&t;&t;&t;&t;&t;TOS tweaks.&n; *&t;&t;Mike McLagan&t;:&t;Routing by source&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/errqueue.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a)&gt;(b)?(a):(b))
DECL|macro|IP_CMSG_PKTINFO
mdefine_line|#define IP_CMSG_PKTINFO&t;&t;1
DECL|macro|IP_CMSG_TTL
mdefine_line|#define IP_CMSG_TTL&t;&t;2
DECL|macro|IP_CMSG_TOS
mdefine_line|#define IP_CMSG_TOS&t;&t;4
DECL|macro|IP_CMSG_RECVOPTS
mdefine_line|#define IP_CMSG_RECVOPTS&t;8
DECL|macro|IP_CMSG_RETOPTS
mdefine_line|#define IP_CMSG_RETOPTS&t;&t;16
multiline_comment|/*&n; *&t;SOL_IP control messages.&n; */
DECL|function|ip_cmsg_recv_pktinfo
r_static
r_void
id|ip_cmsg_recv_pktinfo
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|in_pktinfo
id|info
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
id|info.ipi_addr.s_addr
op_assign
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|rt
)paren
(brace
id|info.ipi_ifindex
op_assign
id|rt-&gt;rt_iif
suffix:semicolon
id|info.ipi_spec_dst.s_addr
op_assign
id|rt-&gt;rt_spec_dst
suffix:semicolon
)brace
r_else
(brace
id|info.ipi_ifindex
op_assign
l_int|0
suffix:semicolon
id|info.ipi_spec_dst.s_addr
op_assign
l_int|0
suffix:semicolon
)brace
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_PKTINFO
comma
r_sizeof
(paren
id|info
)paren
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_recv_ttl
r_static
r_void
id|ip_cmsg_recv_ttl
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ttl
op_assign
id|skb-&gt;nh.iph-&gt;ttl
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_TTL
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|ttl
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_recv_tos
r_static
r_void
id|ip_cmsg_recv_tos
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_TOS
comma
l_int|1
comma
op_amp
id|skb-&gt;nh.iph-&gt;tos
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_recv_opts
r_static
r_void
id|ip_cmsg_recv_opts
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt.optlen
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_RECVOPTS
comma
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt.optlen
comma
id|skb-&gt;nh.iph
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_recv_retopts
r_void
id|ip_cmsg_recv_retopts
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
id|optbuf
(braket
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
l_int|40
)braket
suffix:semicolon
r_struct
id|ip_options
op_star
id|opt
op_assign
(paren
r_struct
id|ip_options
op_star
)paren
id|optbuf
suffix:semicolon
r_if
c_cond
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt.optlen
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
id|opt
comma
id|skb
)paren
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ip_options_undo
c_func
(paren
id|opt
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_RETOPTS
comma
id|opt-&gt;optlen
comma
id|opt-&gt;__data
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_recv
r_void
id|ip_cmsg_recv
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|flags
op_assign
id|skb-&gt;sk-&gt;protinfo.af_inet.cmsg_flags
suffix:semicolon
multiline_comment|/* Ordered by supposed usage frequency */
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|ip_cmsg_recv_pktinfo
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_rshift_assign
l_int|1
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|ip_cmsg_recv_ttl
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_rshift_assign
l_int|1
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|ip_cmsg_recv_tos
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_rshift_assign
l_int|1
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|ip_cmsg_recv_opts
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_rshift_assign
l_int|1
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|ip_cmsg_recv_retopts
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ip_cmsg_send
r_int
id|ip_cmsg_send
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|ipcm_cookie
op_star
id|ipc
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|cmsghdr
op_star
id|cmsg
suffix:semicolon
r_for
c_loop
(paren
id|cmsg
op_assign
id|CMSG_FIRSTHDR
c_func
(paren
id|msg
)paren
suffix:semicolon
id|cmsg
suffix:semicolon
id|cmsg
op_assign
id|CMSG_NXTHDR
c_func
(paren
id|msg
comma
id|cmsg
)paren
)paren
(brace
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
template_param
id|msg-&gt;msg_controllen
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
id|cmsg-&gt;cmsg_level
op_ne
id|SOL_IP
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|cmsg-&gt;cmsg_type
)paren
(brace
r_case
id|IP_RETOPTS
suffix:colon
id|err
op_assign
id|cmsg-&gt;cmsg_len
op_minus
id|CMSG_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
suffix:semicolon
id|err
op_assign
id|ip_options_get
c_func
(paren
op_amp
id|ipc-&gt;opt
comma
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
comma
id|err
OL
l_int|40
ques
c_cond
id|err
suffix:colon
l_int|40
comma
l_int|0
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
r_break
suffix:semicolon
r_case
id|IP_PKTINFO
suffix:colon
(brace
r_struct
id|in_pktinfo
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
op_ne
id|CMSG_LEN
c_func
(paren
r_sizeof
(paren
r_struct
id|in_pktinfo
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|in_pktinfo
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
suffix:semicolon
id|ipc-&gt;oif
op_assign
id|info-&gt;ipi_ifindex
suffix:semicolon
id|ipc-&gt;addr
op_assign
id|info-&gt;ipi_spec_dst.s_addr
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Special input handler for packets catched by router alert option.&n;   They are selected only by protocol field, and then processed likely&n;   local ones; but only if someone wants them! Otherwise, router&n;   not running rsvpd will kill RSVP.&n;&n;   It is user level problem, what it will make with them.&n;   I have no idea, how it will masquearde or NAT them (it is joke, joke :-)),&n;   but receiver should be enough clever f.e. to forward mtrace requests,&n;   sent to multicast group to reach destination designated router.&n; */
DECL|variable|ip_ra_chain
r_struct
id|ip_ra_chain
op_star
id|ip_ra_chain
suffix:semicolon
DECL|variable|ip_ra_lock
id|rwlock_t
id|ip_ra_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ip_ra_control
r_int
id|ip_ra_control
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
id|on
comma
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|sock
op_star
)paren
)paren
(brace
r_struct
id|ip_ra_chain
op_star
id|ra
comma
op_star
id|new_ra
comma
op_star
op_star
id|rap
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;type
op_ne
id|SOCK_RAW
op_logical_or
id|sk-&gt;num
op_eq
id|IPPROTO_RAW
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|new_ra
op_assign
id|on
ques
c_cond
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_ra
)paren
comma
id|GFP_KERNEL
)paren
suffix:colon
l_int|NULL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rap
op_assign
op_amp
id|ip_ra_chain
suffix:semicolon
(paren
id|ra
op_assign
op_star
id|rap
)paren
op_ne
l_int|NULL
suffix:semicolon
id|rap
op_assign
op_amp
id|ra-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ra-&gt;sk
op_eq
id|sk
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_ra
)paren
id|kfree
c_func
(paren
id|new_ra
)paren
suffix:semicolon
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
op_star
id|rap
op_assign
id|ra-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;destructor
)paren
id|ra
op_member_access_from_pointer
id|destructor
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ra
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|new_ra
op_eq
l_int|NULL
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|new_ra-&gt;sk
op_assign
id|sk
suffix:semicolon
id|new_ra-&gt;destructor
op_assign
id|destructor
suffix:semicolon
id|new_ra-&gt;next
op_assign
id|ra
suffix:semicolon
op_star
id|rap
op_assign
id|new_ra
suffix:semicolon
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_icmp_error
r_void
id|ip_icmp_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|err
comma
id|u16
id|port
comma
id|u32
id|info
comma
id|u8
op_star
id|payload
)paren
(brace
r_struct
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;protinfo.af_inet.recverr
)paren
r_return
suffix:semicolon
id|skb
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
id|skb
)paren
r_return
suffix:semicolon
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|serr-&gt;ee.ee_errno
op_assign
id|err
suffix:semicolon
id|serr-&gt;ee.ee_origin
op_assign
id|SO_EE_ORIGIN_ICMP
suffix:semicolon
id|serr-&gt;ee.ee_type
op_assign
id|skb-&gt;h.icmph-&gt;type
suffix:semicolon
id|serr-&gt;ee.ee_code
op_assign
id|skb-&gt;h.icmph-&gt;code
suffix:semicolon
id|serr-&gt;ee.ee_pad
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_info
op_assign
id|info
suffix:semicolon
id|serr-&gt;ee.ee_data
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;addr_offset
op_assign
(paren
id|u8
op_star
)paren
op_amp
(paren
(paren
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|skb-&gt;h.icmph
op_plus
l_int|1
)paren
)paren
op_member_access_from_pointer
id|daddr
)paren
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|serr-&gt;port
op_assign
id|port
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|payload
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|payload
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_err_skb
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ip_local_error
r_void
id|ip_local_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|err
comma
id|u32
id|daddr
comma
id|u16
id|port
comma
id|u32
id|info
)paren
(brace
r_struct
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;protinfo.af_inet.recverr
)paren
r_return
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
r_sizeof
(paren
r_struct
id|iphdr
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|iphdr
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
id|iphdr
)paren
)paren
suffix:semicolon
id|skb-&gt;nh.iph
op_assign
id|iph
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|daddr
suffix:semicolon
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|serr-&gt;ee.ee_errno
op_assign
id|err
suffix:semicolon
id|serr-&gt;ee.ee_origin
op_assign
id|SO_EE_ORIGIN_LOCAL
suffix:semicolon
id|serr-&gt;ee.ee_type
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_code
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_pad
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;ee.ee_info
op_assign
id|info
suffix:semicolon
id|serr-&gt;ee.ee_data
op_assign
l_int|0
suffix:semicolon
id|serr-&gt;addr_offset
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|iph-&gt;daddr
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
id|serr-&gt;port
op_assign
id|port
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;tail
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;tail
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_queue_err_skb
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Handle MSG_ERRQUEUE&n; */
DECL|function|ip_recv_error
r_int
id|ip_recv_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
)paren
(brace
r_struct
id|sock_exterr_skb
op_star
id|serr
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skb2
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
r_struct
(brace
r_struct
id|sock_extended_err
id|ee
suffix:semicolon
r_struct
id|sockaddr_in
id|offender
suffix:semicolon
)brace
id|errhdr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;error_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|copied
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|copied
OG
id|len
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
id|copied
op_assign
id|len
suffix:semicolon
)brace
id|err
op_assign
id|memcpy_toiovec
c_func
(paren
id|msg-&gt;msg_iov
comma
id|skb-&gt;data
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_free_skb
suffix:semicolon
id|sock_recv_timestamp
c_func
(paren
id|msg
comma
id|sk
comma
id|skb
)paren
suffix:semicolon
id|serr
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_if
c_cond
(paren
id|sin
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
id|serr-&gt;addr_offset
)paren
suffix:semicolon
id|sin-&gt;sin_port
op_assign
id|serr-&gt;port
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|errhdr.ee
comma
op_amp
id|serr-&gt;ee
comma
r_sizeof
(paren
r_struct
id|sock_extended_err
)paren
)paren
suffix:semicolon
id|sin
op_assign
op_amp
id|errhdr.offender
suffix:semicolon
id|sin-&gt;sin_family
op_assign
id|AF_UNSPEC
suffix:semicolon
r_if
c_cond
(paren
id|serr-&gt;ee.ee_origin
op_eq
id|SO_EE_ORIGIN_ICMP
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
)paren
id|ip_cmsg_recv
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
)brace
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IP
comma
id|IP_RECVERR
comma
r_sizeof
(paren
id|errhdr
)paren
comma
op_amp
id|errhdr
)paren
suffix:semicolon
multiline_comment|/* Now we could try to dump offended packet options */
id|msg-&gt;msg_flags
op_or_assign
id|MSG_ERRQUEUE
suffix:semicolon
id|err
op_assign
id|copied
suffix:semicolon
multiline_comment|/* Reset and regenerate socket error */
id|sk-&gt;err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;error_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|sk-&gt;err
op_assign
id|SKB_EXT_ERR
c_func
(paren
id|skb2
)paren
op_member_access_from_pointer
id|ee.ee_errno
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|out_free_skb
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Socket option code for IP. This is the end of the line after any TCP,UDP etc options on&n; *&t;an IP socket.&n; *&n; *&t;We implement IP_TOS (type of service), IP_TTL (time to live).&n; */
DECL|function|ip_setsockopt
r_int
id|ip_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
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
id|val
op_assign
l_int|0
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ge
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|optval
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|optlen
op_ge
r_sizeof
(paren
r_char
)paren
)paren
(brace
r_int
r_char
id|ucval
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ucval
comma
(paren
r_int
r_char
op_star
)paren
id|optval
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|val
op_assign
(paren
r_int
)paren
id|ucval
suffix:semicolon
)brace
multiline_comment|/* If optlen==0, it is equivalent to val == 0 */
r_if
c_cond
(paren
id|level
op_ne
id|SOL_IP
)paren
(brace
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
id|optname
op_ge
id|MRT_BASE
op_logical_and
id|optname
op_le
id|MRT_BASE
op_plus
l_int|10
)paren
(brace
r_return
id|ip_mroute_setsockopt
c_func
(paren
id|sk
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
macro_line|#endif
id|err
op_assign
l_int|0
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IP_OPTIONS
suffix:colon
(brace
r_struct
id|ip_options
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OG
l_int|40
op_logical_or
id|optlen
OL
l_int|0
)paren
r_goto
id|e_inval
suffix:semicolon
id|err
op_assign
id|ip_options_get
c_func
(paren
op_amp
id|opt
comma
id|optval
comma
id|optlen
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;type
op_eq
id|SOCK_STREAM
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
r_if
c_cond
(paren
id|sk-&gt;family
op_eq
id|PF_INET
op_logical_or
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;state
)paren
op_amp
(paren
id|TCPF_LISTEN
op_or
id|TCPF_CLOSE
)paren
)paren
op_logical_and
id|sk-&gt;daddr
op_ne
id|LOOPBACK4_IPV6
)paren
)paren
(brace
macro_line|#endif
r_if
c_cond
(paren
id|opt
)paren
id|tp-&gt;ext_header_len
op_assign
id|opt-&gt;optlen
suffix:semicolon
id|tcp_sync_mss
c_func
(paren
id|sk
comma
id|tp-&gt;pmtu_cookie
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
)brace
macro_line|#endif
)brace
id|opt
op_assign
id|xchg
c_func
(paren
op_amp
id|sk-&gt;protinfo.af_inet.opt
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
)paren
id|kfree_s
c_func
(paren
id|opt
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
id|opt-&gt;optlen
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IP_PKTINFO
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_or_assign
id|IP_CMSG_PKTINFO
suffix:semicolon
r_else
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_and_assign
op_complement
id|IP_CMSG_PKTINFO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVTTL
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_or_assign
id|IP_CMSG_TTL
suffix:semicolon
r_else
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_and_assign
op_complement
id|IP_CMSG_TTL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVTOS
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_or_assign
id|IP_CMSG_TOS
suffix:semicolon
r_else
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_and_assign
op_complement
id|IP_CMSG_TOS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVOPTS
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_or_assign
id|IP_CMSG_RECVOPTS
suffix:semicolon
r_else
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_and_assign
op_complement
id|IP_CMSG_RECVOPTS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RETOPTS
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_or_assign
id|IP_CMSG_RETOPTS
suffix:semicolon
r_else
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_and_assign
op_complement
id|IP_CMSG_RETOPTS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_TOS
suffix:colon
multiline_comment|/* This sets both TOS and Precedence */
multiline_comment|/* Reject setting of unused bits */
macro_line|#ifndef CONFIG_INET_ECN
r_if
c_cond
(paren
id|val
op_amp
op_complement
(paren
id|IPTOS_TOS_MASK
op_or
id|IPTOS_PREC_MASK
)paren
)paren
r_goto
id|e_inval
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|sk-&gt;type
op_eq
id|SOCK_STREAM
)paren
(brace
id|val
op_and_assign
op_complement
l_int|3
suffix:semicolon
id|val
op_or_assign
id|sk-&gt;protinfo.af_inet.tos
op_amp
l_int|3
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|IPTOS_PREC
c_func
(paren
id|val
)paren
op_ge
id|IPTOS_PREC_CRITIC_ECP
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.tos
op_ne
id|val
)paren
(brace
id|sk-&gt;protinfo.af_inet.tos
op_assign
id|val
suffix:semicolon
id|sk-&gt;priority
op_assign
id|rt_tos2priority
c_func
(paren
id|val
)paren
suffix:semicolon
id|sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IP_TTL
suffix:colon
r_if
c_cond
(paren
id|optlen
OL
l_int|1
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
op_minus
l_int|1
)paren
(brace
id|val
op_assign
id|sysctl_ip_default_ttl
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
l_int|255
)paren
(brace
r_goto
id|e_inval
suffix:semicolon
)brace
id|sk-&gt;protinfo.af_inet.ttl
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_HDRINCL
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;type
op_ne
id|SOCK_RAW
)paren
(brace
id|err
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sk-&gt;protinfo.af_inet.hdrincl
op_assign
id|val
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MTU_DISCOVER
suffix:colon
r_if
c_cond
(paren
id|val
l_int|2
)paren
r_goto
id|e_inval
suffix:semicolon
id|sk-&gt;protinfo.af_inet.pmtudisc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVERR
suffix:colon
id|sk-&gt;protinfo.af_inet.recverr
op_assign
op_logical_neg
op_logical_neg
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;error_queue
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_TTL
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;type
op_eq
id|SOCK_STREAM
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OL
l_int|1
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
op_minus
l_int|1
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|255
)paren
r_goto
id|e_inval
suffix:semicolon
id|sk-&gt;protinfo.af_inet.mc_ttl
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_LOOP
suffix:colon
r_if
c_cond
(paren
id|optlen
OL
l_int|1
)paren
r_goto
id|e_inval
suffix:semicolon
id|sk-&gt;protinfo.af_inet.mc_loop
op_assign
id|val
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_IF
suffix:colon
(brace
r_struct
id|ip_mreqn
id|mreq
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;type
op_eq
id|SOCK_STREAM
)paren
r_goto
id|e_inval
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Check the arguments are allowable&n;&t;&t;&t; */
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ge
r_sizeof
(paren
r_struct
id|ip_mreqn
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
id|mreq
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|mreq
comma
l_int|0
comma
r_sizeof
(paren
id|mreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ge
r_sizeof
(paren
r_struct
id|in_addr
)paren
op_logical_and
id|copy_from_user
c_func
(paren
op_amp
id|mreq.imr_address
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|in_addr
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mreq.imr_ifindex
)paren
(brace
r_if
c_cond
(paren
id|mreq.imr_address.s_addr
op_eq
id|INADDR_ANY
)paren
(brace
id|sk-&gt;protinfo.af_inet.mc_index
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.af_inet.mc_addr
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dev
op_assign
id|ip_dev_find
c_func
(paren
id|mreq.imr_address.s_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|mreq.imr_ifindex
op_assign
id|dev-&gt;ifindex
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_else
id|dev
op_assign
id|__dev_get_by_index
c_func
(paren
id|mreq.imr_ifindex
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;bound_dev_if
op_logical_and
id|mreq.imr_ifindex
op_ne
id|sk-&gt;bound_dev_if
)paren
r_break
suffix:semicolon
id|sk-&gt;protinfo.af_inet.mc_index
op_assign
id|mreq.imr_ifindex
suffix:semicolon
id|sk-&gt;protinfo.af_inet.mc_addr
op_assign
id|mreq.imr_address.s_addr
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IP_ADD_MEMBERSHIP
suffix:colon
r_case
id|IP_DROP_MEMBERSHIP
suffix:colon
(brace
r_struct
id|ip_mreqn
id|mreq
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OL
r_sizeof
(paren
r_struct
id|ip_mreq
)paren
)paren
r_goto
id|e_inval
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_ge
r_sizeof
(paren
r_struct
id|ip_mreqn
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
id|mreq
)paren
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|mreq
comma
l_int|0
comma
r_sizeof
(paren
id|mreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|ip_mreq
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optname
op_eq
id|IP_ADD_MEMBERSHIP
)paren
id|err
op_assign
id|ip_mc_join_group
c_func
(paren
id|sk
comma
op_amp
id|mreq
)paren
suffix:semicolon
r_else
id|err
op_assign
id|ip_mc_leave_group
c_func
(paren
id|sk
comma
op_amp
id|mreq
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IP_ROUTER_ALERT
suffix:colon
id|err
op_assign
id|ip_ra_control
c_func
(paren
id|sk
comma
id|val
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef CONFIG_NETFILTER
id|err
op_assign
id|nf_setsockopt
c_func
(paren
id|sk
comma
id|PF_INET
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
macro_line|#else
id|err
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|e_inval
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Get the options. Note for future reference. The GET of IP options gets the&n; *&t;_received_ ones. The set sets the _sent_ ones.&n; */
DECL|function|ip_getsockopt
r_int
id|ip_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
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
id|val
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ne
id|SOL_IP
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
id|optname
op_ge
id|MRT_BASE
op_logical_and
id|optname
op_le
id|MRT_BASE
op_plus
l_int|10
)paren
(brace
r_return
id|ip_mroute_getsockopt
c_func
(paren
id|sk
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IP_OPTIONS
suffix:colon
(brace
r_int
r_char
id|optbuf
(braket
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
l_int|40
)braket
suffix:semicolon
r_struct
id|ip_options
op_star
id|opt
op_assign
(paren
r_struct
id|ip_options
op_star
)paren
id|optbuf
suffix:semicolon
id|opt-&gt;optlen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.opt
)paren
id|memcpy
c_func
(paren
id|optbuf
comma
id|sk-&gt;protinfo.af_inet.opt
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
id|sk-&gt;protinfo.af_inet.opt-&gt;optlen
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;optlen
op_eq
l_int|0
)paren
r_return
id|put_user
c_func
(paren
l_int|0
comma
id|optlen
)paren
suffix:semicolon
id|ip_options_undo
c_func
(paren
id|opt
)paren
suffix:semicolon
id|len
op_assign
id|min
c_func
(paren
id|len
comma
id|opt-&gt;optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
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
id|copy_to_user
c_func
(paren
id|optval
comma
id|opt-&gt;__data
comma
id|len
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
r_case
id|IP_PKTINFO
suffix:colon
id|val
op_assign
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_PKTINFO
)paren
op_ne
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVTTL
suffix:colon
id|val
op_assign
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_TTL
)paren
op_ne
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVTOS
suffix:colon
id|val
op_assign
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_TOS
)paren
op_ne
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RECVOPTS
suffix:colon
id|val
op_assign
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_RECVOPTS
)paren
op_ne
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_RETOPTS
suffix:colon
id|val
op_assign
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_RETOPTS
)paren
op_ne
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_TOS
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.tos
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_TTL
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.ttl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_HDRINCL
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.hdrincl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MTU_DISCOVER
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.pmtudisc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MTU
suffix:colon
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
id|dst
op_assign
id|sk_dst_get
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
id|val
op_assign
id|dst-&gt;pmtu
suffix:semicolon
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|ENOTCONN
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|IP_RECVERR
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.recverr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_TTL
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.mc_ttl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_LOOP
suffix:colon
id|val
op_assign
id|sk-&gt;protinfo.af_inet.mc_loop
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IP_MULTICAST_IF
suffix:colon
(brace
r_struct
id|ip_mreqn
id|mreq
suffix:semicolon
id|len
op_assign
id|min
c_func
(paren
id|len
comma
r_sizeof
(paren
r_struct
id|ip_mreqn
)paren
)paren
suffix:semicolon
id|mreq.imr_ifindex
op_assign
id|sk-&gt;protinfo.af_inet.mc_index
suffix:semicolon
id|mreq.imr_address.s_addr
op_assign
id|sk-&gt;protinfo.af_inet.mc_addr
suffix:semicolon
id|mreq.imr_multiaddr.s_addr
op_assign
l_int|0
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
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
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|optval
comma
op_amp
id|mreq
comma
id|len
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
r_case
id|IP_PKTOPTIONS
suffix:colon
(brace
r_struct
id|msghdr
id|msg
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;type
op_ne
id|SOCK_STREAM
)paren
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
id|msg.msg_control
op_assign
id|optval
suffix:semicolon
id|msg.msg_controllen
op_assign
id|len
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_PKTINFO
)paren
(brace
r_struct
id|in_pktinfo
id|info
suffix:semicolon
id|info.ipi_addr.s_addr
op_assign
id|sk-&gt;rcv_saddr
suffix:semicolon
id|info.ipi_spec_dst.s_addr
op_assign
id|sk-&gt;rcv_saddr
suffix:semicolon
id|info.ipi_ifindex
op_assign
id|sk-&gt;protinfo.af_inet.mc_index
suffix:semicolon
id|put_cmsg
c_func
(paren
op_amp
id|msg
comma
id|SOL_IP
comma
id|IP_PKTINFO
comma
r_sizeof
(paren
id|info
)paren
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.af_inet.cmsg_flags
op_amp
id|IP_CMSG_TTL
)paren
(brace
r_int
id|hlim
op_assign
id|sk-&gt;protinfo.af_inet.mc_ttl
suffix:semicolon
id|put_cmsg
c_func
(paren
op_amp
id|msg
comma
id|SOL_IP
comma
id|IP_TTL
comma
r_sizeof
(paren
id|hlim
)paren
comma
op_amp
id|hlim
)paren
suffix:semicolon
)brace
id|len
op_sub_assign
id|msg.msg_controllen
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
suffix:semicolon
)brace
r_default
suffix:colon
macro_line|#ifdef CONFIG_NETFILTER
id|val
op_assign
id|nf_getsockopt
c_func
(paren
id|sk
comma
id|PF_INET
comma
id|optname
comma
id|optval
comma
op_amp
id|len
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ge
l_int|0
)paren
id|val
op_assign
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
macro_line|#else
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
macro_line|#endif
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
template_param
l_int|0
op_logical_and
id|val
op_ge
l_int|0
op_logical_and
id|val
OL
l_int|255
)paren
(brace
r_int
r_char
id|ucval
op_assign
(paren
r_int
r_char
)paren
id|val
suffix:semicolon
id|len
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
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
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|ucval
comma
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
id|len
op_assign
id|min
c_func
(paren
r_sizeof
(paren
r_int
)paren
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
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
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|val
comma
id|len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
