multiline_comment|/* atm_tcp.h - Driver-specific declarations of the ATMTCP driver (for use by&n;&t;       driver-specific utilities) */
multiline_comment|/* Written 1997,1998 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATM_TCP_H
DECL|macro|LINUX_ATM_TCP_H
mdefine_line|#define LINUX_ATM_TCP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/*&n; * All values are in network byte order&n; */
DECL|struct|atmtcp_hdr
r_struct
id|atmtcp_hdr
(brace
DECL|member|vpi
r_uint16
id|vpi
suffix:semicolon
DECL|member|vci
r_uint16
id|vci
suffix:semicolon
DECL|member|length
r_uint32
id|length
suffix:semicolon
multiline_comment|/* ... of data part */
)brace
suffix:semicolon
DECL|macro|SIOCSIFATMTCP
mdefine_line|#define SIOCSIFATMTCP&t;_IO(&squot;a&squot;,ATMIOC_ITF)&t;/* set ATMTCP mode */
DECL|macro|ATMTCP_CREATE
mdefine_line|#define ATMTCP_CREATE&t;_IO(&squot;a&squot;,ATMIOC_ITF+14)&t;/* create persistent ATMTCP&n;&t;&t;&t;&t;&t;&t;   interface */
DECL|macro|ATMTCP_REMOVE
mdefine_line|#define ATMTCP_REMOVE&t;_IO(&squot;a&squot;,ATMIOC_ITF+15)&t;/* destroy persistent ATMTCP&n;&t;&t;&t;&t;&t;&t;   interface*/
macro_line|#ifdef __KERNEL__
DECL|struct|atm_tcp_ops
r_struct
id|atm_tcp_ops
(brace
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|itf
)paren
suffix:semicolon
DECL|member|create_persistent
r_int
(paren
op_star
id|create_persistent
)paren
(paren
r_int
id|itf
)paren
suffix:semicolon
DECL|member|remove_persistent
r_int
(paren
op_star
id|remove_persistent
)paren
(paren
r_int
id|itf
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|atm_tcp_ops
id|atm_tcp_ops
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
