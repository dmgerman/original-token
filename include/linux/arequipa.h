multiline_comment|/* arequipa.h - Arequipa interface definitions */
multiline_comment|/* Written 1996-1998 by Jean-Michel Pittet and Werner Almesberger, EPFL ICA */
macro_line|#ifndef _LINUX_AREQUIPA_H
DECL|macro|_LINUX_AREQUIPA_H
mdefine_line|#define _LINUX_AREQUIPA_H
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|enum|arequipa_msg_type
DECL|enumerator|amt_invalid
DECL|enumerator|amt_close
DECL|enumerator|amt_sync
r_enum
id|arequipa_msg_type
(brace
id|amt_invalid
comma
id|amt_close
comma
id|amt_sync
)brace
suffix:semicolon
DECL|struct|arequipa_msg
r_struct
id|arequipa_msg
(brace
DECL|member|type
r_enum
id|arequipa_msg_type
id|type
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AREQUIPA_PRESET
mdefine_line|#define AREQUIPA_PRESET&t;&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA)
DECL|macro|AREQUIPA_INCOMING
mdefine_line|#define AREQUIPA_INCOMING&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+1)
DECL|macro|AREQUIPA_EXPECT
mdefine_line|#define AREQUIPA_EXPECT&t;&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+2)
DECL|macro|AREQUIPA_CLOSE
mdefine_line|#define AREQUIPA_CLOSE&t;&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+3)
DECL|macro|AREQUIPA_CTRL
mdefine_line|#define AREQUIPA_CTRL&t;&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+4)
multiline_comment|/* #define AREQUIPA_CLS3RD&t;removed */
DECL|macro|AREQUIPA_SYNCREQ
mdefine_line|#define AREQUIPA_SYNCREQ&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+6)
multiline_comment|/* #define AREQUIPA_SYNCACK&t;removed */
DECL|macro|AREQUIPA_WORK
mdefine_line|#define AREQUIPA_WORK&t;&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+8)
DECL|macro|AREQUIPA_RENEGOTIATE
mdefine_line|#define AREQUIPA_RENEGOTIATE&t;_IO(&squot;a&squot;,ATMIOC_AREQUIPA+9)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;net/sock.h&gt;
r_extern
r_struct
id|atm_vcc
op_star
id|aqd
suffix:semicolon
multiline_comment|/* for net/atm/proc.c */
multiline_comment|/* extern struct rtable *arequipa_rt; - not needed; we use a local dcl instead*/
r_extern
r_struct
id|net_device
op_star
id|arequipa_dev
suffix:semicolon
r_int
id|atm_init_arequipa
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|arequipa_attach
c_func
(paren
r_struct
id|socket
op_star
id|lower
comma
r_struct
id|sock
op_star
id|upper
comma
r_int
r_int
id|generation
)paren
suffix:semicolon
r_int
id|arequipa_preset
c_func
(paren
r_struct
id|socket
op_star
id|lower
comma
r_struct
id|sock
op_star
id|upper
)paren
suffix:semicolon
r_int
id|arequipa_expect
c_func
(paren
r_struct
id|sock
op_star
id|upper
comma
r_int
id|on
comma
r_int
id|kmalloc_flags
)paren
suffix:semicolon
r_int
id|arequipa_incoming
c_func
(paren
r_struct
id|socket
op_star
id|lower
)paren
suffix:semicolon
r_int
id|arequipa_close
c_func
(paren
r_struct
id|sock
op_star
id|upper
)paren
suffix:semicolon
r_int
id|arequipa_renegotiate
c_func
(paren
r_struct
id|sock
op_star
id|upper
comma
r_struct
id|atm_qos
op_star
id|u_qos
)paren
suffix:semicolon
r_void
id|arequipa_synchronize
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|arequipa_work
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|arequipad_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
