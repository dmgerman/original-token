macro_line|#ifndef _IP_PORTFW_H
DECL|macro|_IP_PORTFW_H
mdefine_line|#define  _IP_PORTFW_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|IP_PORTFW_PORT_MIN
mdefine_line|#define IP_PORTFW_PORT_MIN 1
DECL|macro|IP_PORTFW_PORT_MAX
mdefine_line|#define IP_PORTFW_PORT_MAX 60999
macro_line|#ifdef __KERNEL__
DECL|struct|ip_portfw
r_struct
id|ip_portfw
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|laddr
DECL|member|raddr
id|__u32
id|laddr
comma
id|raddr
suffix:semicolon
DECL|member|lport
DECL|member|rport
id|__u16
id|lport
comma
id|rport
suffix:semicolon
DECL|member|pref_cnt
id|atomic_t
id|pref_cnt
suffix:semicolon
multiline_comment|/* pref &quot;counter&quot; down to 0 */
DECL|member|pref
r_int
id|pref
suffix:semicolon
multiline_comment|/* user set pref */
)brace
suffix:semicolon
r_extern
r_int
id|ip_portfw_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|struct|ip_portfw_edits
r_struct
id|ip_portfw_edits
(brace
DECL|member|protocol
id|__u16
id|protocol
suffix:semicolon
multiline_comment|/* Which protocol are we talking? */
DECL|member|laddr
DECL|member|raddr
id|__u32
id|laddr
comma
id|raddr
suffix:semicolon
multiline_comment|/* Remote address */
DECL|member|lport
DECL|member|rport
id|__u16
id|lport
comma
id|rport
suffix:semicolon
multiline_comment|/* Local and remote port */
DECL|member|dummy
id|__u16
id|dummy
suffix:semicolon
multiline_comment|/* Make up to multiple of 4 */
DECL|member|pref
r_int
id|pref
suffix:semicolon
multiline_comment|/* Preference value */
)brace
suffix:semicolon
macro_line|#endif
eof
