macro_line|#ifndef __LINUX_RTNETLINK_H
DECL|macro|__LINUX_RTNETLINK_H
mdefine_line|#define __LINUX_RTNETLINK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
DECL|macro|RTNL_DEBUG
mdefine_line|#define RTNL_DEBUG 1
multiline_comment|/****&n; *&t;&t;Routing/neighbour discovery messages.&n; ****/
multiline_comment|/* Types of messages */
DECL|macro|RTM_BASE
mdefine_line|#define RTM_BASE&t;0x10
DECL|macro|RTM_NEWLINK
mdefine_line|#define&t;RTM_NEWLINK&t;(RTM_BASE+0)
DECL|macro|RTM_DELLINK
mdefine_line|#define&t;RTM_DELLINK&t;(RTM_BASE+1)
DECL|macro|RTM_GETLINK
mdefine_line|#define&t;RTM_GETLINK&t;(RTM_BASE+2)
DECL|macro|RTM_NEWADDR
mdefine_line|#define&t;RTM_NEWADDR&t;(RTM_BASE+4)
DECL|macro|RTM_DELADDR
mdefine_line|#define&t;RTM_DELADDR&t;(RTM_BASE+5)
DECL|macro|RTM_GETADDR
mdefine_line|#define&t;RTM_GETADDR&t;(RTM_BASE+6)
DECL|macro|RTM_NEWROUTE
mdefine_line|#define&t;RTM_NEWROUTE&t;(RTM_BASE+8)
DECL|macro|RTM_DELROUTE
mdefine_line|#define&t;RTM_DELROUTE&t;(RTM_BASE+9)
DECL|macro|RTM_GETROUTE
mdefine_line|#define&t;RTM_GETROUTE&t;(RTM_BASE+10)
DECL|macro|RTM_NEWNEIGH
mdefine_line|#define&t;RTM_NEWNEIGH&t;(RTM_BASE+12)
DECL|macro|RTM_DELNEIGH
mdefine_line|#define&t;RTM_DELNEIGH&t;(RTM_BASE+13)
DECL|macro|RTM_GETNEIGH
mdefine_line|#define&t;RTM_GETNEIGH&t;(RTM_BASE+14)
DECL|macro|RTM_NEWRULE
mdefine_line|#define&t;RTM_NEWRULE&t;(RTM_BASE+16)
DECL|macro|RTM_DELRULE
mdefine_line|#define&t;RTM_DELRULE&t;(RTM_BASE+17)
DECL|macro|RTM_GETRULE
mdefine_line|#define&t;RTM_GETRULE&t;(RTM_BASE+18)
DECL|macro|RTM_MAX
mdefine_line|#define&t;RTM_MAX&t;&t;(RTM_BASE+19)
multiline_comment|/* Generic structure for encapsulation optional route&n;   information. It is reminiscent of sockaddr, but with sa_family&n;   replaced with attribute type.&n;   It would be good, if constructions of sort:&n;   struct something {&n;     struct rtattr rta;&n;     struct a_content a;&n;   }&n;   had correct alignment. It is true for x86, but I have no idea&n;   how to make it on 64bit architectures. Please, teach me. --ANK&n; */
DECL|struct|rtattr
r_struct
id|rtattr
(brace
DECL|member|rta_len
r_int
r_int
id|rta_len
suffix:semicolon
DECL|member|rta_type
r_int
r_int
id|rta_type
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|rtattr_type_t
r_enum
id|rtattr_type_t
(brace
DECL|enumerator|RTA_UNSPEC
id|RTA_UNSPEC
comma
DECL|enumerator|RTA_DST
id|RTA_DST
comma
DECL|enumerator|RTA_SRC
id|RTA_SRC
comma
DECL|enumerator|RTA_IIF
id|RTA_IIF
comma
DECL|enumerator|RTA_OIF
id|RTA_OIF
comma
DECL|enumerator|RTA_GATEWAY
id|RTA_GATEWAY
comma
DECL|enumerator|RTA_PRIORITY
id|RTA_PRIORITY
comma
DECL|enumerator|RTA_PREFSRC
id|RTA_PREFSRC
comma
DECL|enumerator|RTA_WINDOW
id|RTA_WINDOW
comma
DECL|enumerator|RTA_RTT
id|RTA_RTT
comma
DECL|enumerator|RTA_MTU
id|RTA_MTU
comma
DECL|enumerator|RTA_IFNAME
id|RTA_IFNAME
comma
DECL|enumerator|RTA_CACHEINFO
id|RTA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|RTA_MAX
mdefine_line|#define RTA_MAX RTA_CACHEINFO
multiline_comment|/* Macros to handle rtattributes */
DECL|macro|RTA_ALIGNTO
mdefine_line|#define RTA_ALIGNTO&t;4
DECL|macro|RTA_ALIGN
mdefine_line|#define RTA_ALIGN(len) ( ((len)+RTA_ALIGNTO-1) &amp; ~(RTA_ALIGNTO-1) )
DECL|macro|RTA_OK
mdefine_line|#define RTA_OK(rta,len) ((rta)-&gt;rta_len &gt; sizeof(struct rtattr) &amp;&amp; &bslash;&n;&t;&t;&t; (rta)-&gt;rta_len &lt;= (len))
DECL|macro|RTA_NEXT
mdefine_line|#define RTA_NEXT(rta,attrlen)&t;((attrlen) -= RTA_ALIGN((rta)-&gt;rta_len), &bslash;&n;&t;&t;&t;&t; (struct rtattr*)(((char*)(rta)) + RTA_ALIGN((rta)-&gt;rta_len)))
DECL|macro|RTA_LENGTH
mdefine_line|#define RTA_LENGTH(len)&t;(RTA_ALIGN(sizeof(struct rtattr)) + (len))
DECL|macro|RTA_SPACE
mdefine_line|#define RTA_SPACE(len)&t;RTA_ALIGN(RTA_LENGTH(len))
DECL|macro|RTA_DATA
mdefine_line|#define RTA_DATA(rta)   ((void*)(((char*)(rta)) + RTA_LENGTH(0)))
DECL|struct|rta_cacheinfo
r_struct
id|rta_cacheinfo
(brace
DECL|member|rta_clntref
id|__u32
id|rta_clntref
suffix:semicolon
DECL|member|rta_lastuse
id|__u32
id|rta_lastuse
suffix:semicolon
DECL|member|rta_expires
id|__s32
id|rta_expires
suffix:semicolon
DECL|member|rta_error
id|__u32
id|rta_error
suffix:semicolon
DECL|member|rta_used
id|__u32
id|rta_used
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * &quot;struct rtnexthop&quot; describres all necessary nexthop information,&n; * i.e. parameters of path to a destination via this nextop.&n; *&n; * At the moment it is impossible to set different prefsrc, mtu, window&n; * and rtt for different paths from multipath.&n; */
DECL|struct|rtnexthop
r_struct
id|rtnexthop
(brace
DECL|member|rtnh_len
r_int
r_int
id|rtnh_len
suffix:semicolon
DECL|member|rtnh_flags
r_int
r_char
id|rtnh_flags
suffix:semicolon
DECL|member|rtnh_hops
r_int
r_char
id|rtnh_hops
suffix:semicolon
DECL|member|rtnh_ifindex
r_int
id|rtnh_ifindex
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* rtnh_flags */
DECL|macro|RTNH_F_DEAD
mdefine_line|#define RTNH_F_DEAD&t;&t;1&t;/* Nexthop is dead (used by multipath)&t;*/
DECL|macro|RTNH_F_PERVASIVE
mdefine_line|#define RTNH_F_PERVASIVE&t;2&t;/* Do recursive gateway lookup&t;*/
DECL|macro|RTNH_F_ONLINK
mdefine_line|#define RTNH_F_ONLINK&t;&t;4&t;/* Gateway is forced on link&t;*/
multiline_comment|/* Macros to handle hexthops */
DECL|macro|RTNH_ALIGNTO
mdefine_line|#define RTNH_ALIGNTO&t;4
DECL|macro|RTNH_ALIGN
mdefine_line|#define RTNH_ALIGN(len) ( ((len)+RTNH_ALIGNTO-1) &amp; ~(RTNH_ALIGNTO-1) )
DECL|macro|RTNH_OK
mdefine_line|#define RTNH_OK(rtnh,len) ((rtnh)-&gt;rtnh_len &gt;= sizeof(struct rtnexthop) &amp;&amp; &bslash;&n;&t;&t;&t;   (rtnh)-&gt;rtnh_len &lt;= (len))
DECL|macro|RTNH_NEXT
mdefine_line|#define RTNH_NEXT(rtnh)&t;((struct rtnexthop*)(((char*)(rtnh)) + RTNH_ALIGN((rtnh)-&gt;rtnh_len)))
DECL|macro|RTNH_LENGTH
mdefine_line|#define RTNH_LENGTH(len) (RTNH_ALIGN(sizeof(struct rtnexthop)) + (len))
DECL|macro|RTNH_SPACE
mdefine_line|#define RTNH_SPACE(len)&t;RTNH_ALIGN(RTNH_LENGTH(len))
DECL|macro|RTNH_DATA
mdefine_line|#define RTNH_DATA(rtnh)   ((struct rtattr*)(((char*)(rtnh)) + RTNH_LENGTH(0)))
DECL|struct|rtmsg
r_struct
id|rtmsg
(brace
DECL|member|rtm_family
r_int
r_char
id|rtm_family
suffix:semicolon
DECL|member|rtm_dst_len
r_int
r_char
id|rtm_dst_len
suffix:semicolon
DECL|member|rtm_src_len
r_int
r_char
id|rtm_src_len
suffix:semicolon
DECL|member|rtm_tos
r_int
r_char
id|rtm_tos
suffix:semicolon
DECL|member|rtm_table
r_int
r_char
id|rtm_table
suffix:semicolon
multiline_comment|/* Routing table id */
DECL|member|rtm_protocol
r_int
r_char
id|rtm_protocol
suffix:semicolon
multiline_comment|/* Routing protocol; see below&t;*/
DECL|member|rtm_nhs
r_int
r_char
id|rtm_nhs
suffix:semicolon
multiline_comment|/* Number of nexthops */
DECL|member|rtm_type
r_int
r_char
id|rtm_type
suffix:semicolon
multiline_comment|/* See below&t;*/
DECL|member|rtm_optlen
r_int
r_int
id|rtm_optlen
suffix:semicolon
multiline_comment|/* Byte length of rtm_opt */
DECL|member|rtm_scope
r_int
r_char
id|rtm_scope
suffix:semicolon
multiline_comment|/* See below */
DECL|member|rtm_whatsit
r_int
r_char
id|rtm_whatsit
suffix:semicolon
multiline_comment|/* Unused byte */
DECL|member|rtm_flags
r_int
id|rtm_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTM_RTA
mdefine_line|#define RTM_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct rtmsg))))
DECL|macro|RTM_RTNH
mdefine_line|#define RTM_RTNH(r) ((struct rtnexthop*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct rtmsg)) &bslash;&n;&t;&t;&t;&t;&t;   + NLMSG_ALIGN((r)-&gt;rtm_optlen)))
DECL|macro|RTM_NHLEN
mdefine_line|#define RTM_NHLEN(nlh,r) ((nlh)-&gt;nlmsg_len - NLMSG_SPACE(sizeof(struct rtmsg)) - NLMSG_ALIGN((r)-&gt;rtm_optlen))
multiline_comment|/* rtm_type */
r_enum
(brace
DECL|enumerator|RTN_UNSPEC
id|RTN_UNSPEC
comma
DECL|enumerator|RTN_UNICAST
id|RTN_UNICAST
comma
multiline_comment|/* Gateway or direct route&t;*/
DECL|enumerator|RTN_LOCAL
id|RTN_LOCAL
comma
multiline_comment|/* Accept locally&t;&t;*/
DECL|enumerator|RTN_BROADCAST
id|RTN_BROADCAST
comma
multiline_comment|/* Accept locally as broadcast,&n;&t;&t;&t;&t;   send as broadcast */
DECL|enumerator|RTN_ANYCAST
id|RTN_ANYCAST
comma
multiline_comment|/* Accept locally as broadcast,&n;&t;&t;&t;&t;   but send as unicast */
DECL|enumerator|RTN_MULTICAST
id|RTN_MULTICAST
comma
multiline_comment|/* Multicast route&t;&t;*/
DECL|enumerator|RTN_BLACKHOLE
id|RTN_BLACKHOLE
comma
multiline_comment|/* Drop&t;&t;&t;&t;*/
DECL|enumerator|RTN_UNREACHABLE
id|RTN_UNREACHABLE
comma
multiline_comment|/* Destination is unreachable   */
DECL|enumerator|RTN_PROHIBIT
id|RTN_PROHIBIT
comma
multiline_comment|/* Administratively prohibited&t;*/
DECL|enumerator|RTN_THROW
id|RTN_THROW
comma
multiline_comment|/* Not in this table&t;&t;*/
DECL|enumerator|RTN_NAT
id|RTN_NAT
comma
multiline_comment|/* Translate this address&t;*/
DECL|enumerator|RTN_XRESOLVE
id|RTN_XRESOLVE
comma
multiline_comment|/* Use external resolver&t;*/
)brace
suffix:semicolon
DECL|macro|RTN_MAX
mdefine_line|#define RTN_MAX RTN_XRESOLVE
multiline_comment|/* rtm_protocol */
DECL|macro|RTPROT_UNSPEC
mdefine_line|#define RTPROT_UNSPEC&t;0
DECL|macro|RTPROT_REDIRECT
mdefine_line|#define RTPROT_REDIRECT&t;1&t;/* Route installed by ICMP redirects;&n;&t;&t;&t;&t;   not used by current IPv4 */
DECL|macro|RTPROT_KERNEL
mdefine_line|#define RTPROT_KERNEL&t;2&t;/* Route installed by kernel&t;&t;*/
DECL|macro|RTPROT_BOOT
mdefine_line|#define RTPROT_BOOT&t;3&t;/* Route installed during boot&t;&t;*/
DECL|macro|RTPROT_STATIC
mdefine_line|#define RTPROT_STATIC&t;4&t;/* Route installed by administrator&t;*/
multiline_comment|/* Values of protocol &gt;= RTPROT_STATIC are not interpreted by kernel;&n;   they just passed from user and back as is.&n;   It will be used by hypothetical multiple routing daemons.&n;   Note that protocol values should be standardized in order to&n;   avoid conflicts.&n; */
DECL|macro|RTPROT_GATED
mdefine_line|#define RTPROT_GATED&t;8&t;/* Apparently, GateD */
DECL|macro|RTPROT_RA
mdefine_line|#define RTPROT_RA&t;9&t;/* RDISC/ND router advertisments */
DECL|macro|RTPROT_MRT
mdefine_line|#define RTPROT_MRT&t;10&t;/* Merit MRT */
DECL|macro|RTPROT_ZEBRA
mdefine_line|#define RTPROT_ZEBRA&t;11&t;/* Zebra */
multiline_comment|/* rtm_scope&n;&n;   Really it is not scope, but sort of distance to the destination.&n;   NOWHERE are reserved for not existing destinations, HOST is our&n;   local addresses, LINK are destinations, locate on directly attached&n;   link and UNIVERSE is everywhere in the Universe :-)&n;&n;   Intermediate values are also possible f.e. interior routes&n;   could be assigned a value between UNIVERSE and LINK.&n;*/
DECL|enum|rt_scope_t
r_enum
id|rt_scope_t
(brace
DECL|enumerator|RT_SCOPE_UNIVERSE
id|RT_SCOPE_UNIVERSE
op_assign
l_int|0
comma
multiline_comment|/* User defined values f.e. &quot;site&quot; */
DECL|enumerator|RT_SCOPE_SITE
id|RT_SCOPE_SITE
op_assign
l_int|200
comma
DECL|enumerator|RT_SCOPE_LINK
id|RT_SCOPE_LINK
op_assign
l_int|253
comma
DECL|enumerator|RT_SCOPE_HOST
id|RT_SCOPE_HOST
op_assign
l_int|254
comma
DECL|enumerator|RT_SCOPE_NOWHERE
id|RT_SCOPE_NOWHERE
op_assign
l_int|255
)brace
suffix:semicolon
multiline_comment|/* rtm_flags */
DECL|macro|RTM_F_NOTIFY
mdefine_line|#define RTM_F_NOTIFY&t;&t;0x100&t;/* Notify user of route change&t;*/
DECL|macro|RTM_F_CLONED
mdefine_line|#define RTM_F_CLONED&t;&t;0x200&t;/* This route is cloned&t;&t;*/
DECL|macro|RTM_F_NOPMTUDISC
mdefine_line|#define RTM_F_NOPMTUDISC&t;0x400&t;/* Do not make PMTU discovery&t;*/
DECL|macro|RTM_F_EQUALIZE
mdefine_line|#define RTM_F_EQUALIZE&t;&t;0x800&t;/* Multipath equalizer: NI&t;*/
multiline_comment|/* Reserved table identifiers */
DECL|enum|rt_class_t
r_enum
id|rt_class_t
(brace
DECL|enumerator|RT_TABLE_UNSPEC
id|RT_TABLE_UNSPEC
op_assign
l_int|0
comma
multiline_comment|/* User defined values */
DECL|enumerator|RT_TABLE_DEFAULT
id|RT_TABLE_DEFAULT
op_assign
l_int|253
comma
DECL|enumerator|RT_TABLE_MAIN
id|RT_TABLE_MAIN
op_assign
l_int|254
comma
DECL|enumerator|RT_TABLE_LOCAL
id|RT_TABLE_LOCAL
op_assign
l_int|255
)brace
suffix:semicolon
DECL|macro|RT_TABLE_MAX
mdefine_line|#define RT_TABLE_MAX RT_TABLE_LOCAL
multiline_comment|/*********************************************************&n; *&t;&t;Interface address.&n; ****/
DECL|struct|ifaddrmsg
r_struct
id|ifaddrmsg
(brace
DECL|member|ifa_family
r_int
r_char
id|ifa_family
suffix:semicolon
DECL|member|ifa_prefixlen
r_int
r_char
id|ifa_prefixlen
suffix:semicolon
multiline_comment|/* The prefix length&t;&t;*/
DECL|member|ifa_flags
r_int
r_char
id|ifa_flags
suffix:semicolon
multiline_comment|/* Flags&t;&t;&t;*/
DECL|member|ifa_scope
r_int
r_char
id|ifa_scope
suffix:semicolon
multiline_comment|/* See above&t;&t;&t;*/
DECL|member|ifa_index
r_int
id|ifa_index
suffix:semicolon
multiline_comment|/* Link index&t;&t;&t;*/
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IFA_UNSPEC
id|IFA_UNSPEC
comma
DECL|enumerator|IFA_ADDRESS
id|IFA_ADDRESS
comma
DECL|enumerator|IFA_LOCAL
id|IFA_LOCAL
comma
DECL|enumerator|IFA_LABEL
id|IFA_LABEL
comma
DECL|enumerator|IFA_BROADCAST
id|IFA_BROADCAST
comma
DECL|enumerator|IFA_ANYCAST
id|IFA_ANYCAST
comma
DECL|enumerator|IFA_CACHEINFO
id|IFA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|IFA_MAX
mdefine_line|#define IFA_MAX IFA_CACHEINFO
multiline_comment|/* ifa_flags */
DECL|macro|IFA_F_SECONDARY
mdefine_line|#define IFA_F_SECONDARY&t;&t;0x01
DECL|macro|IFA_F_DEPRECATED
mdefine_line|#define IFA_F_DEPRECATED&t;0x20
DECL|macro|IFA_F_TENTATIVE
mdefine_line|#define IFA_F_TENTATIVE&t;&t;0x40
DECL|macro|IFA_F_PERMANENT
mdefine_line|#define IFA_F_PERMANENT&t;&t;0x80
DECL|struct|ifa_cacheinfo
r_struct
id|ifa_cacheinfo
(brace
DECL|member|ifa_prefered
id|__s32
id|ifa_prefered
suffix:semicolon
DECL|member|ifa_valid
id|__s32
id|ifa_valid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IFA_RTA
mdefine_line|#define IFA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))))
multiline_comment|/*&n;   Important comment:&n;   IFA_ADDRESS is prefix address, rather than local interface address.&n;   It makes no difference for normally configured broadcast interfaces,&n;   but for point-to-point IFA_ADDRESS is DESTINATION address,&n;   local address is supplied in IFA_LOCAL attribute.&n; */
multiline_comment|/**************************************************************&n; *&t;&t;Neighbour discovery.&n; ****/
DECL|struct|ndmsg
r_struct
id|ndmsg
(brace
DECL|member|ndm_family
r_int
r_char
id|ndm_family
suffix:semicolon
DECL|member|ndm_ifindex
r_int
id|ndm_ifindex
suffix:semicolon
multiline_comment|/* Link index&t;&t;&t;*/
DECL|member|ndm_state
id|__u16
id|ndm_state
suffix:semicolon
DECL|member|ndm_flags
id|__u8
id|ndm_flags
suffix:semicolon
DECL|member|ndm_type
id|__u8
id|ndm_type
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|NDA_UNSPEC
id|NDA_UNSPEC
comma
DECL|enumerator|NDA_DST
id|NDA_DST
comma
DECL|enumerator|NDA_LLADDR
id|NDA_LLADDR
comma
DECL|enumerator|NDA_CACHEINFO
id|NDA_CACHEINFO
)brace
suffix:semicolon
DECL|macro|NDA_MAX
mdefine_line|#define NDA_MAX NDA_CACHEINFO
DECL|macro|NDA_RTA
mdefine_line|#define NDA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ndmsg))))
DECL|struct|nda_cacheinfo
r_struct
id|nda_cacheinfo
(brace
DECL|member|ndm_confirmed
id|__u32
id|ndm_confirmed
suffix:semicolon
DECL|member|ndm_used
id|__u32
id|ndm_used
suffix:semicolon
DECL|member|ndm_updated
id|__u32
id|ndm_updated
suffix:semicolon
DECL|member|ndm_refcnt
id|__u32
id|ndm_refcnt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****&n; *&t;&t;General form of address family dependent message.&n; ****/
DECL|struct|rtgenmsg
r_struct
id|rtgenmsg
(brace
DECL|member|rtgen_family
r_int
r_char
id|rtgen_family
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n; *&t;&t;Link layer specific messages.&n; ****/
multiline_comment|/* struct ifinfomsg&n; * passes link level specific information, not dependent&n; * on network protocol.&n; */
DECL|struct|ifinfomsg
r_struct
id|ifinfomsg
(brace
DECL|member|ifi_family
r_int
r_char
id|ifi_family
suffix:semicolon
multiline_comment|/* Dummy&t;*/
DECL|member|ifi_addrlen
r_int
r_char
id|ifi_addrlen
suffix:semicolon
multiline_comment|/* Length of HW address */
DECL|member|ifi_pad__
r_int
r_int
id|ifi_pad__
suffix:semicolon
DECL|member|ifi_index
r_int
id|ifi_index
suffix:semicolon
multiline_comment|/* Link index&t;*/
DECL|member|ifi_link
r_int
id|ifi_link
suffix:semicolon
multiline_comment|/* Physical device */
DECL|member|ifi_name
r_char
id|ifi_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|ifi_address
r_struct
id|sockaddr
id|ifi_address
suffix:semicolon
multiline_comment|/* HW address&t;*/
DECL|member|ifi_broadcast
r_struct
id|sockaddr
id|ifi_broadcast
suffix:semicolon
multiline_comment|/* HW broadcast&t;*/
DECL|member|ifi_flags
r_int
id|ifi_flags
suffix:semicolon
multiline_comment|/* IFF_* flags&t;*/
DECL|member|ifi_mtu
r_int
id|ifi_mtu
suffix:semicolon
multiline_comment|/* Link mtu&t;*/
DECL|member|ifi_qdiscname
r_char
id|ifi_qdiscname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Id of packet scheduler */
DECL|member|ifi_qdisc
r_int
id|ifi_qdisc
suffix:semicolon
multiline_comment|/* Packet scheduler handle */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IFLA_UNSPEC
id|IFLA_UNSPEC
comma
DECL|enumerator|IFLA_ADDRESS
id|IFLA_ADDRESS
comma
DECL|enumerator|IFLA_BROADCAST
id|IFLA_BROADCAST
comma
DECL|enumerator|IFLA_IFNAME
id|IFLA_IFNAME
comma
DECL|enumerator|IFLA_QDISC
id|IFLA_QDISC
comma
DECL|enumerator|IFLA_STATS
id|IFLA_STATS
)brace
suffix:semicolon
DECL|macro|IFLA_MAX
mdefine_line|#define IFLA_MAX IFLA_STATS
DECL|macro|IFLA_RTA
mdefine_line|#define IFLA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifinfomsg))))
multiline_comment|/* ifi_flags.&n;&n;   IFF_* flags.&n;&n;   The only change is:&n;   IFF_LOOPBACK, IFF_BROADCAST and IFF_POINTOPOINT are&n;   more not changeable by user. They describe link media&n;   characteristics and set by device driver.&n;&n;   Comments:&n;   - Combination IFF_BROADCAST|IFF_POINTOPOINT is invalid&n;   - If neiher of these three flags are set;&n;     the interface is NBMA.&n;&n;   - IFF_MULTICAST does not mean anything special:&n;   multicasts can be used on all not-NBMA links.&n;   IFF_MULTICAST means that this media uses special encapsulation&n;   for multicast frames. Apparently, all IFF_POINTOPOINT and&n;   IFF_BROADCAST devices are able to use multicasts too.&n; */
multiline_comment|/* ifi_link.&n;   For usual devices it is equal ifi_index.&n;   If it is a &quot;virtual interface&quot; (f.e. tunnel), ifi_link&n;   can point to real physical interface (f.e. for bandwidth calculations),&n;   or maybe 0, what means, that real media is unknown (usual&n;   for IPIP tunnels, when route to endpoint is allowed to change)&n; */
DECL|macro|RTMGRP_LINK
mdefine_line|#define RTMGRP_LINK&t;&t;1
DECL|macro|RTMGRP_NOTIFY
mdefine_line|#define RTMGRP_NOTIFY&t;&t;2
DECL|macro|RTMGRP_NEIGH
mdefine_line|#define RTMGRP_NEIGH&t;&t;4
DECL|macro|RTMGRP_IPV4_IFADDR
mdefine_line|#define RTMGRP_IPV4_IFADDR&t;0x10
DECL|macro|RTMGRP_IPV4_MROUTE
mdefine_line|#define RTMGRP_IPV4_MROUTE&t;0x20
DECL|macro|RTMGRP_IPV4_ROUTE
mdefine_line|#define RTMGRP_IPV4_ROUTE&t;0x40
DECL|macro|RTMGRP_IPV6_IFADDR
mdefine_line|#define RTMGRP_IPV6_IFADDR&t;0x100
DECL|macro|RTMGRP_IPV6_MROUTE
mdefine_line|#define RTMGRP_IPV6_MROUTE&t;0x200
DECL|macro|RTMGRP_IPV6_ROUTE
mdefine_line|#define RTMGRP_IPV6_ROUTE&t;0x400
macro_line|#ifdef __KERNEL__
DECL|struct|kern_rta
r_struct
id|kern_rta
(brace
DECL|member|rta_dst
r_void
op_star
id|rta_dst
suffix:semicolon
DECL|member|rta_src
r_void
op_star
id|rta_src
suffix:semicolon
DECL|member|rta_iif
r_int
op_star
id|rta_iif
suffix:semicolon
DECL|member|rta_oif
r_int
op_star
id|rta_oif
suffix:semicolon
DECL|member|rta_gw
r_void
op_star
id|rta_gw
suffix:semicolon
DECL|member|rta_priority
id|u32
op_star
id|rta_priority
suffix:semicolon
DECL|member|rta_prefsrc
r_void
op_star
id|rta_prefsrc
suffix:semicolon
DECL|member|rta_window
r_int
op_star
id|rta_window
suffix:semicolon
DECL|member|rta_rtt
r_int
op_star
id|rta_rtt
suffix:semicolon
DECL|member|rta_mtu
r_int
op_star
id|rta_mtu
suffix:semicolon
DECL|member|rta_ifname
r_int
r_char
op_star
id|rta_ifname
suffix:semicolon
DECL|member|rta_ci
r_struct
id|rta_cacheinfo
op_star
id|rta_ci
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kern_ifa
r_struct
id|kern_ifa
(brace
DECL|member|ifa_address
r_void
op_star
id|ifa_address
suffix:semicolon
DECL|member|ifa_local
r_void
op_star
id|ifa_local
suffix:semicolon
DECL|member|ifa_label
r_int
r_char
op_star
id|ifa_label
suffix:semicolon
DECL|member|ifa_broadcast
r_void
op_star
id|ifa_broadcast
suffix:semicolon
DECL|member|ifa_anycast
r_void
op_star
id|ifa_anycast
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|atomic_t
id|rtnl_rlockct
suffix:semicolon
r_extern
r_struct
id|wait_queue
op_star
id|rtnl_wait
suffix:semicolon
macro_line|#ifdef CONFIG_RTNETLINK
r_extern
r_struct
id|sock
op_star
id|rtnl
suffix:semicolon
DECL|struct|rtnetlink_link
r_struct
id|rtnetlink_link
(brace
DECL|member|doit
r_int
(paren
op_star
id|doit
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|nlmsghdr
op_star
comma
r_void
op_star
id|attr
)paren
suffix:semicolon
DECL|member|dumpit
r_int
(paren
op_star
id|dumpit
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rtnetlink_link
op_star
id|rtnetlink_links
(braket
id|NPROTO
)braket
suffix:semicolon
r_extern
r_int
id|rtnetlink_dump_ifinfo
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_void
id|__rta_fill
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|attrtype
comma
r_int
id|attrlen
comma
r_const
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|macro|RTA_PUT
mdefine_line|#define RTA_PUT(skb, attrtype, attrlen, data) &bslash;&n;({ if (skb_tailroom(skb) &lt; RTA_SPACE(attrlen)) goto rtattr_failure; &bslash;&n;   __rta_fill(skb, attrtype, attrlen, data); })
r_extern
r_int
r_int
id|rtnl_wlockct
suffix:semicolon
multiline_comment|/* NOTE: these locks are not interrupt safe, are not SMP safe,&n; * they are even not atomic. 8)8)8) ... and it is not a bug.&n; * Really, if these locks will be programmed correctly,&n; * all the addressing/routing machine would become SMP safe,&n; * but is absolutely useless at the moment, because all the kernel&n; * is not reenterable in any case. --ANK&n; *&n; * Well, atomic_* and set_bit provide the only thing here:&n; * gcc is confused not to overoptimize them, that&squot;s all.&n; * I remember as gcc splitted ++ operation, but cannot reproduce&n; * it with gcc-2.7.*. --ANK&n; *&n; * One more note: rwlock facility should be written and put&n; * to a kernel wide location: f.e. current implementation of semaphores&n; * (especially, for x86) looks like a wonder. It would be good&n; * to have something similar for rwlock. Recursive lock could be also&n; * useful thing. --ANK&n; */
DECL|function|rtnl_shlock_nowait
r_extern
id|__inline__
r_int
id|rtnl_shlock_nowait
c_func
(paren
r_void
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|rtnl_wlockct
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtnl_shlock
r_extern
id|__inline__
r_void
id|rtnl_shlock
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|rtnl_shlock_nowait
c_func
(paren
)paren
)paren
id|sleep_on
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for possibility to PROMOTE shared lock to exclusive.&n;   Shared lock must be already grabbed with rtnl_shlock*().&n; */
DECL|function|rtnl_exlock_nowait
r_extern
id|__inline__
r_int
id|rtnl_exlock_nowait
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
OG
l_int|1
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|rtnl_wlockct
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtnl_exlock
r_extern
id|__inline__
r_void
id|rtnl_exlock
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|rtnl_exlock_nowait
c_func
(paren
)paren
)paren
id|sleep_on
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_extern
id|__inline__
r_void
id|rtnl_shunlock
c_func
(paren
r_void
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
op_le
l_int|1
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtnl-&gt;receive_queue.qlen
)paren
id|rtnl
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|rtnl
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
multiline_comment|/* The problem: inline requires to include &lt;net/sock.h&gt; and, hence,&n;   almost all of net includes :-(&n; */
DECL|macro|rtnl_shunlock
mdefine_line|#define rtnl_shunlock() ({ &bslash;&n;&t;atomic_dec(&amp;rtnl_rlockct); &bslash;&n;&t;if (atomic_read(&amp;rtnl_rlockct) &lt;= 1) { &bslash;&n;&t;&t;wake_up(&amp;rtnl_wait); &bslash;&n;&t;&t;if (rtnl-&gt;receive_queue.qlen) &bslash;&n;&t;&t;&t;rtnl-&gt;data_ready(rtnl, 0); &bslash;&n;&t;} &bslash;&n;})
macro_line|#endif
multiline_comment|/* Release exclusive lock. Note, that we do not wake up rtnetlink socket,&n; * it will be done later after releasing shared lock.&n; */
DECL|function|rtnl_exunlock
r_extern
id|__inline__
r_void
id|rtnl_exunlock
c_func
(paren
r_void
)paren
(brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|rtnl_wlockct
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|rtnl_shlock
r_extern
id|__inline__
r_void
id|rtnl_shlock
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
)paren
id|sleep_on
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
suffix:semicolon
)brace
DECL|function|rtnl_shunlock
r_extern
id|__inline__
r_void
id|rtnl_shunlock
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|rtnl_rlockct
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|rtnl_wait
)paren
suffix:semicolon
)brace
DECL|function|rtnl_exlock
r_extern
id|__inline__
r_void
id|rtnl_exlock
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|rtnl_exunlock
r_extern
id|__inline__
r_void
id|rtnl_exunlock
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
r_extern
r_void
id|rtnl_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtnl_unlock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtnetlink_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_RTNETLINK_H */
eof
