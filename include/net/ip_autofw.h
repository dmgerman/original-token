macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifndef _IP_AUTOFW_H
DECL|macro|_IP_AUTOFW_H
mdefine_line|#define _IP_AUTOFW_H
DECL|macro|IP_AUTOFW_EXPIRE
mdefine_line|#define IP_AUTOFW_EXPIRE&t;     15*HZ
DECL|macro|IP_FWD_RANGE
mdefine_line|#define IP_FWD_RANGE &t;&t;1
DECL|macro|IP_FWD_PORT
mdefine_line|#define IP_FWD_PORT&t;&t;2
DECL|macro|IP_FWD_DIRECT
mdefine_line|#define IP_FWD_DIRECT&t;&t;3
DECL|macro|IP_AUTOFW_ACTIVE
mdefine_line|#define IP_AUTOFW_ACTIVE&t;1
DECL|macro|IP_AUTOFW_USETIME
mdefine_line|#define IP_AUTOFW_USETIME&t;2
DECL|macro|IP_AUTOFW_SECURE
mdefine_line|#define IP_AUTOFW_SECURE&t;4
DECL|struct|ip_autofw
r_struct
id|ip_autofw
(brace
DECL|member|next
r_struct
id|ip_autofw
op_star
id|next
suffix:semicolon
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|low
id|__u16
id|low
suffix:semicolon
DECL|member|hidden
id|__u16
id|hidden
suffix:semicolon
DECL|member|high
id|__u16
id|high
suffix:semicolon
DECL|member|visible
id|__u16
id|visible
suffix:semicolon
DECL|member|protocol
id|__u16
id|protocol
suffix:semicolon
DECL|member|lastcontact
id|__u32
id|lastcontact
suffix:semicolon
DECL|member|where
id|__u32
id|where
suffix:semicolon
DECL|member|ctlproto
id|__u16
id|ctlproto
suffix:semicolon
DECL|member|ctlport
id|__u16
id|ctlport
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ip_autofw_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _IP_AUTOFW_H */
eof
