multiline_comment|/*&n; *&t;ipddp.h: Header for IP-over-DDP driver for Linux.&n; */
macro_line|#ifndef __LINUX_IPDDP_H
DECL|macro|__LINUX_IPDDP_H
mdefine_line|#define __LINUX_IPDDP_H
macro_line|#ifdef __KERNEL__
DECL|macro|SIOCADDIPDDPRT
mdefine_line|#define SIOCADDIPDDPRT SIOCDEVPRIVATE
DECL|macro|SIOCDELIPDDPRT
mdefine_line|#define SIOCDELIPDDPRT SIOCDEVPRIVATE+1
DECL|macro|SIOCFINDIPDDPRT
mdefine_line|#define SIOCFINDIPDDPRT SIOCDEVPRIVATE+2
DECL|struct|ipddp_route
r_struct
id|ipddp_route
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Carrier device */
DECL|member|ip
id|__u32
id|ip
suffix:semicolon
multiline_comment|/* IP address */
DECL|member|at
r_struct
id|at_addr
id|at
suffix:semicolon
multiline_comment|/* Gateway appletalk address */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|next
r_struct
id|ipddp_route
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|ipddp_route_head
r_static
r_struct
id|ipddp_route
op_star
id|ipddp_route_head
suffix:semicolon
DECL|variable|ipddp_route_test
r_static
r_struct
id|ipddp_route
id|ipddp_route_test
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_IPDDP_H */
eof
