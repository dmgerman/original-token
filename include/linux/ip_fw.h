multiline_comment|/*&n; *&t;IP firewalling code. This is taken from 4.4BSD. Please note the &n; *&t;copyright message below. As per the GPL it must be maintained&n; *&t;and the licenses thus do not conflict. While this port is subject&n; *&t;to the GPL I also place my modifications under the original &n; *&t;license in recognition of the original copyright. &n; *&n; *&t;Ported from BSD to Linux,&n; *&t;&t;Alan Cox 22/Nov/1994.&n; *&n; *&t;All the real work was done by .....&n; */
multiline_comment|/*&n; * Copyright (c) 1993 Daniel Boulet&n; * Copyright (c) 1994 Ugen J.S.Antsilevich&n; *&n; * Redistribution and use in source forms, with and without modification,&n; * are permitted provided that this entire comment appears intact.&n; *&n; * Redistribution in binary form may occur without any restrictions.&n; * Obviously, it would be nice if you gave credit where credit is due&n; * but requiring it would be too onerous.&n; *&n; * This software is provided ``AS IS&squot;&squot; without any warranties of any kind.&n; */
multiline_comment|/*&n; * &t;Format of an IP firewall descriptor&n; *&n; * &t;src, dst, src_mask, dst_mask are always stored in network byte order.&n; * &t;flags and num_*_ports are stored in host byte order (of course).&n; * &t;Port numbers are stored in HOST byte order.&n; */
macro_line|#ifndef _IP_FW_H
DECL|macro|_IP_FW_H
mdefine_line|#define _IP_FW_H
DECL|struct|ip_fw
r_struct
id|ip_fw
(brace
DECL|member|next
r_struct
id|ip_fw
op_star
id|next
suffix:semicolon
multiline_comment|/* Next firewall on chain */
DECL|member|src
DECL|member|dst
r_struct
id|in_addr
id|src
comma
id|dst
suffix:semicolon
multiline_comment|/* Source and destination IP addr */
DECL|member|src_mask
DECL|member|dst_mask
r_struct
id|in_addr
id|src_mask
comma
id|dst_mask
suffix:semicolon
multiline_comment|/* Mask for src and dest IP addr */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags word */
DECL|member|n_src_p
DECL|member|n_dst_p
r_int
r_int
id|n_src_p
comma
id|n_dst_p
suffix:semicolon
multiline_comment|/* # of src ports and # of dst ports */
multiline_comment|/* in ports array (dst ports follow */
multiline_comment|/* src ports; max of 10 ports in all; */
multiline_comment|/* count of 0 means match all ports) */
DECL|macro|IP_FW_MAX_PORTS
mdefine_line|#define IP_FW_MAX_PORTS&t;10      &t;&t;/* A reasonable maximum */
DECL|member|ports
r_int
r_int
id|ports
(braket
id|IP_FW_MAX_PORTS
)braket
suffix:semicolon
multiline_comment|/* Array of port numbers to match */
DECL|member|p_cnt
DECL|member|b_cnt
r_int
r_int
id|p_cnt
comma
id|b_cnt
suffix:semicolon
multiline_comment|/* Packet and byte counters */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Values for &quot;flags&quot; field .&n; */
DECL|macro|IP_FW_F_ALL
mdefine_line|#define IP_FW_F_ALL&t;0x00&t;/* This is a universal packet firewall*/
DECL|macro|IP_FW_F_TCP
mdefine_line|#define IP_FW_F_TCP&t;0x01&t;/* This is a TCP packet firewall      */
DECL|macro|IP_FW_F_UDP
mdefine_line|#define IP_FW_F_UDP&t;0x02&t;/* This is a UDP packet firewall      */
DECL|macro|IP_FW_F_ICMP
mdefine_line|#define IP_FW_F_ICMP&t;0x03&t;/* This is a ICMP packet firewall     */
DECL|macro|IP_FW_F_KIND
mdefine_line|#define IP_FW_F_KIND&t;0x03&t;/* Mask to isolate firewall kind      */
DECL|macro|IP_FW_F_ACCEPT
mdefine_line|#define IP_FW_F_ACCEPT&t;0x04&t;/* This is an accept firewall (as     *&n;&t;&t;&t;&t; *         opposed to a deny firewall)*&n;&t;&t;&t;&t; *                                    */
DECL|macro|IP_FW_F_SRNG
mdefine_line|#define IP_FW_F_SRNG&t;0x08&t;/* The first two src ports are a min  *&n;&t;&t;&t;&t; * and max range (stored in host byte *&n;&t;&t;&t;&t; * order).                            *&n;&t;&t;&t;&t; *                                    */
DECL|macro|IP_FW_F_DRNG
mdefine_line|#define IP_FW_F_DRNG&t;0x10&t;/* The first two dst ports are a min  *&n;&t;&t;&t;&t; * and max range (stored in host byte *&n;&t;&t;&t;&t; * order).                            *&n;&t;&t;&t;&t; * (ports[0] &lt;= port &lt;= ports[1])     *&n;&t;&t;&t;&t; *                                    */
DECL|macro|IP_FW_F_PRN
mdefine_line|#define IP_FW_F_PRN&t;0x20&t;/* In verbose mode print this firewall*/
DECL|macro|IP_FW_F_BIDIR
mdefine_line|#define IP_FW_F_BIDIR&t;0x40&t;/* For accounting-count two way       */
DECL|macro|IP_FW_F_MASK
mdefine_line|#define IP_FW_F_MASK&t;0x7F&t;/* All possible flag bits mask        */
multiline_comment|/*    &n; *&t;New IP firewall options for [gs]etsockopt at the RAW IP level.&n; *&t;Unlike BSD Linux inherits IP options so you don&squot;t have to use&n; *&t;a raw socket for this. Instead we check rights in the calls.&n; */
DECL|macro|IP_FW_BASE_CTL
mdefine_line|#define IP_FW_BASE_CTL&t;64
DECL|macro|IP_FW_ADD_BLK
mdefine_line|#define IP_FW_ADD_BLK (IP_FW_BASE_CTL)
DECL|macro|IP_FW_ADD_FWD
mdefine_line|#define IP_FW_ADD_FWD (IP_FW_BASE_CTL+1)   
DECL|macro|IP_FW_CHK_BLK
mdefine_line|#define IP_FW_CHK_BLK (IP_FW_BASE_CTL+2)
DECL|macro|IP_FW_CHK_FWD
mdefine_line|#define IP_FW_CHK_FWD (IP_FW_BASE_CTL+3)
DECL|macro|IP_FW_DEL_BLK
mdefine_line|#define IP_FW_DEL_BLK (IP_FW_BASE_CTL+4)
DECL|macro|IP_FW_DEL_FWD
mdefine_line|#define IP_FW_DEL_FWD (IP_FW_BASE_CTL+5)
DECL|macro|IP_FW_FLUSH
mdefine_line|#define IP_FW_FLUSH   (IP_FW_BASE_CTL+6)
DECL|macro|IP_FW_POLICY
mdefine_line|#define IP_FW_POLICY  (IP_FW_BASE_CTL+7) 
DECL|macro|IP_ACCT_ADD
mdefine_line|#define IP_ACCT_ADD   (IP_FW_BASE_CTL+10)
DECL|macro|IP_ACCT_DEL
mdefine_line|#define IP_ACCT_DEL   (IP_FW_BASE_CTL+11)
DECL|macro|IP_ACCT_FLUSH
mdefine_line|#define IP_ACCT_FLUSH (IP_FW_BASE_CTL+12)
DECL|macro|IP_ACCT_ZERO
mdefine_line|#define IP_ACCT_ZERO  (IP_FW_BASE_CTL+13)
multiline_comment|/*&n; *&t;Main firewall chains definitions and global var&squot;s definitions.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IP_FIREWALL
r_extern
r_struct
id|ip_fw
op_star
id|ip_fw_blk_chain
suffix:semicolon
r_extern
r_struct
id|ip_fw
op_star
id|ip_fw_fwd_chain
suffix:semicolon
r_extern
r_int
id|ip_fw_policy
suffix:semicolon
r_extern
r_int
id|ip_fw_chk
c_func
(paren
r_struct
id|iphdr
op_star
comma
r_struct
id|ip_fw
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ip_fw_ctl
c_func
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IP_ACCT
r_extern
r_struct
id|ip_fw
op_star
id|ip_acct_chain
suffix:semicolon
r_extern
r_void
id|ip_acct_cnt
c_func
(paren
r_struct
id|iphdr
op_star
comma
r_struct
id|ip_fw
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ip_acct_ctl
c_func
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* KERNEL */
macro_line|#endif /* _IP_FW_H */
eof
