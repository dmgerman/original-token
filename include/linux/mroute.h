macro_line|#ifndef __LINUX_MROUTE_H
DECL|macro|__LINUX_MROUTE_H
mdefine_line|#define __LINUX_MROUTE_H
multiline_comment|/*&n; *&t;Based on the MROUTING 3.5 defines primarily to keep&n; *&t;source compatibility with BSD.&n; *&n; *&t;See the mrouted code for the original history.&n; *&n; */
DECL|macro|MRT_BASE
mdefine_line|#define MRT_BASE&t;200
DECL|macro|MRT_INIT
mdefine_line|#define MRT_INIT&t;(MRT_BASE)&t;/* Activate the kernel mroute code &t;*/
DECL|macro|MRT_DONE
mdefine_line|#define MRT_DONE&t;(MRT_BASE+1)&t;/* Shutdown the kernel mroute&t;&t;*/
DECL|macro|MRT_ADD_VIF
mdefine_line|#define MRT_ADD_VIF&t;(MRT_BASE+2)&t;/* Add a virtual interface&t;&t;*/
DECL|macro|MRT_DEL_VIF
mdefine_line|#define MRT_DEL_VIF&t;(MRT_BASE+3)&t;/* Delete a virtual interface&t;&t;*/
DECL|macro|MRT_ADD_MFC
mdefine_line|#define MRT_ADD_MFC&t;(MRT_BASE+4)&t;/* Add a multicast forwarding entry&t;*/
DECL|macro|MRT_DEL_MFC
mdefine_line|#define MRT_DEL_MFC&t;(MRT_BASE+5)&t;/* Delete a multicast forwarding entry&t;*/
DECL|macro|MRT_VERSION
mdefine_line|#define MRT_VERSION&t;(MRT_BASE+6)&t;/* Get the kernel multicast version&t;*/
DECL|macro|MRT_ASSERT
mdefine_line|#define MRT_ASSERT&t;(MRT_BASE+7)&t;/* Activate PIM assert mode&t;&t;*/
DECL|macro|SIOCGETVIFCNT
mdefine_line|#define SIOCGETVIFCNT&t;SIOCPROTOPRIVATE&t;/* IP protocol privates */
DECL|macro|SIOCGETSGCNT
mdefine_line|#define SIOCGETSGCNT&t;(SIOCPROTOPRIVATE+1)
DECL|macro|MAXVIFS
mdefine_line|#define MAXVIFS&t;&t;32&t;
DECL|typedef|vifbitmap_t
r_typedef
r_int
r_int
id|vifbitmap_t
suffix:semicolon
multiline_comment|/* User mode code depends on this lot */
DECL|typedef|vifi_t
r_typedef
r_int
r_int
id|vifi_t
suffix:semicolon
DECL|macro|ALL_VIFS
mdefine_line|#define ALL_VIFS&t;((vifi_t)(-1))
multiline_comment|/*&n; *&t;Same idea as select&n; */
DECL|macro|VIFM_SET
mdefine_line|#define VIFM_SET(n,m)&t;((m)|=(1&lt;&lt;(n)))
DECL|macro|VIFM_CLR
mdefine_line|#define VIFM_CLR(n,m)&t;((m)&amp;=~(1&lt;&lt;(n)))
DECL|macro|VIFM_ISSET
mdefine_line|#define VIFM_ISSET(n,m)&t;((m)&amp;(1&lt;&lt;(n)))
DECL|macro|VIFM_CLRALL
mdefine_line|#define VIFM_CLRALL(m)&t;((m)=0)
DECL|macro|VIFM_COPY
mdefine_line|#define VIFM_COPY(mfrom,mto)&t;((mto)=(mfrom))
DECL|macro|VIFM_SAME
mdefine_line|#define VIFM_SAME(m1,m2)&t;((m1)==(m2))
multiline_comment|/*&n; *&t;Passed by mrouted for an MRT_ADD_VIF - again we use the&n; *&t;mrouted 3.6 structures for compatibility&n; */
DECL|struct|vifctl
r_struct
id|vifctl
(brace
DECL|member|vifc_vifi
id|vifi_t
id|vifc_vifi
suffix:semicolon
multiline_comment|/* Index of VIF */
DECL|member|vifc_flags
r_int
r_char
id|vifc_flags
suffix:semicolon
multiline_comment|/* VIFF_ flags */
DECL|member|vifc_threshold
r_int
r_char
id|vifc_threshold
suffix:semicolon
multiline_comment|/* ttl limit */
DECL|member|vifc_rate_limit
r_int
r_int
id|vifc_rate_limit
suffix:semicolon
multiline_comment|/* Rate limiter values (NI) */
DECL|member|vifc_lcl_addr
r_struct
id|in_addr
id|vifc_lcl_addr
suffix:semicolon
multiline_comment|/* Our address */
DECL|member|vifc_rmt_addr
r_struct
id|in_addr
id|vifc_rmt_addr
suffix:semicolon
multiline_comment|/* IPIP tunnel addr */
)brace
suffix:semicolon
DECL|macro|VIFF_TUNNEL
mdefine_line|#define VIFF_TUNNEL&t;0x1&t;&t;/* IPIP tunnel */
DECL|macro|VIFF_SRCRT
mdefine_line|#define VIFF_SRCRT&t;0x02&t;&t;/* NI */
multiline_comment|/*&n; *&t;Cache manipulation structures for mrouted&n; */
DECL|struct|mfcctl
r_struct
id|mfcctl
(brace
DECL|member|mfcc_origin
r_struct
id|in_addr
id|mfcc_origin
suffix:semicolon
multiline_comment|/* Origin of mcast&t;*/
DECL|member|mfcc_mcastgrp
r_struct
id|in_addr
id|mfcc_mcastgrp
suffix:semicolon
multiline_comment|/* Group in question&t;*/
DECL|member|mfcc_parent
id|vifi_t
id|mfcc_parent
suffix:semicolon
multiline_comment|/* Where it arrived&t;*/
DECL|member|mfcc_ttls
r_int
r_char
id|mfcc_ttls
(braket
id|MAXVIFS
)braket
suffix:semicolon
multiline_comment|/* Where it is going&t;*/
)brace
suffix:semicolon
multiline_comment|/* &n; *&t;Group count retrieval for mrouted&n; */
DECL|struct|sioc_sg_req
r_struct
id|sioc_sg_req
(brace
DECL|member|src
r_struct
id|in_addr
id|src
suffix:semicolon
DECL|member|grp
r_struct
id|in_addr
id|grp
suffix:semicolon
DECL|member|pktcnt
r_int
r_int
id|pktcnt
suffix:semicolon
DECL|member|bytecnt
r_int
r_int
id|bytecnt
suffix:semicolon
DECL|member|wrong_if
r_int
r_int
id|wrong_if
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;To get vif packet counts&n; */
DECL|struct|sioc_vif_req
r_struct
id|sioc_vif_req
(brace
DECL|member|vifi
id|vifi_t
id|vifi
suffix:semicolon
multiline_comment|/* Which iface */
DECL|member|icount
r_int
r_int
id|icount
suffix:semicolon
multiline_comment|/* In packets */
DECL|member|ocount
r_int
r_int
id|ocount
suffix:semicolon
multiline_comment|/* Out packets */
DECL|member|ibytes
r_int
r_int
id|ibytes
suffix:semicolon
multiline_comment|/* In bytes */
DECL|member|obytes
r_int
r_int
id|obytes
suffix:semicolon
multiline_comment|/* Out bytes */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;This is the format the mroute daemon expects to see IGMP control&n; *&t;data. Magically happens to be like an IP packet as per the original&n; */
DECL|struct|igmpmsg
r_struct
id|igmpmsg
(brace
DECL|member|unused1
DECL|member|unused2
r_int
r_int
id|unused1
comma
id|unused2
suffix:semicolon
DECL|member|im_msgtype
r_int
r_char
id|im_msgtype
suffix:semicolon
multiline_comment|/* What is this */
DECL|member|im_mbz
r_int
r_char
id|im_mbz
suffix:semicolon
multiline_comment|/* Must be zero */
DECL|member|im_vif
r_int
r_char
id|im_vif
suffix:semicolon
multiline_comment|/* Interface (this ought to be a vifi_t!) */
DECL|member|unused3
r_int
r_char
id|unused3
suffix:semicolon
DECL|member|im_src
DECL|member|im_dst
r_struct
id|in_addr
id|im_src
comma
id|im_dst
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Thats all usermode folks&n; */
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|sock
op_star
id|mroute_socket
suffix:semicolon
r_extern
r_int
id|ip_mroute_setsockopt
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ip_mroute_getsockopt
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|mroute_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|struct|vif_device
r_struct
id|vif_device
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device we are using */
DECL|member|rt_cache
r_struct
id|route
op_star
id|rt_cache
suffix:semicolon
multiline_comment|/* Tunnel route cache */
DECL|member|bytes_in
DECL|member|bytes_out
r_int
r_int
id|bytes_in
comma
id|bytes_out
suffix:semicolon
DECL|member|pkt_in
DECL|member|pkt_out
r_int
r_int
id|pkt_in
comma
id|pkt_out
suffix:semicolon
multiline_comment|/* Statistics */
DECL|member|rate_limit
r_int
r_int
id|rate_limit
suffix:semicolon
multiline_comment|/* Traffic shaping (NI) */
DECL|member|threshold
r_int
r_char
id|threshold
suffix:semicolon
multiline_comment|/* TTL threshold */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Control flags */
DECL|member|local
DECL|member|remote
r_int
r_int
id|local
comma
id|remote
suffix:semicolon
multiline_comment|/* Addresses (remote for tunnels) */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
