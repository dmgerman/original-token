multiline_comment|/*&n; *&t;IP_MASQ user space control interface&n; *&t;$Id: ip_masq.h,v 1.1 1998/08/29 23:50:56 davem Exp $&n; */
macro_line|#ifndef _LINUX_IP_MASQ_H
DECL|macro|_LINUX_IP_MASQ_H
mdefine_line|#define _LINUX_IP_MASQ_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#else
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#endif
DECL|struct|ip_masq_user
r_struct
id|ip_masq_user
(brace
DECL|member|protocol
r_int
id|protocol
suffix:semicolon
DECL|member|sport
DECL|member|dport
DECL|member|mport
id|u_int16_t
id|sport
comma
id|dport
comma
id|mport
suffix:semicolon
DECL|member|saddr
DECL|member|daddr
DECL|member|maddr
id|u_int32_t
id|saddr
comma
id|daddr
comma
id|maddr
suffix:semicolon
DECL|member|rt_daddr
id|u_int32_t
id|rt_daddr
suffix:semicolon
multiline_comment|/* dst address to use for rt query */
DECL|member|rt_saddr
id|u_int32_t
id|rt_saddr
suffix:semicolon
DECL|member|ip_tos
id|u_int32_t
id|ip_tos
suffix:semicolon
multiline_comment|/* TOS */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* in ticks (HZ per sec) */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
multiline_comment|/* NOT IMPL: attach tunnel to this fd */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* NOT IMPL: return conn state */
)brace
suffix:semicolon
DECL|macro|IP_MASQ_USER_F_LISTEN
mdefine_line|#define IP_MASQ_USER_F_LISTEN&t;0x01&t;/* put entry to LISTEN state */
DECL|macro|IP_MASQ_USER_F_DEAD
mdefine_line|#define IP_MASQ_USER_F_DEAD&t;0x02&t;/* mark as DEAD */
DECL|macro|IP_MASQ_USER_F_FORCE
mdefine_line|#define IP_MASQ_USER_F_FORCE&t;0x04&t;/* force operation */
DECL|struct|ip_masq_timeout
r_struct
id|ip_masq_timeout
(brace
DECL|member|protocol
r_int
id|protocol
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|established
r_int
id|established
suffix:semicolon
DECL|member|syn_sent
r_int
id|syn_sent
suffix:semicolon
DECL|member|syn_recv
r_int
id|syn_recv
suffix:semicolon
DECL|member|fin_wait
r_int
id|fin_wait
suffix:semicolon
DECL|member|time_wait
r_int
id|time_wait
suffix:semicolon
DECL|member|close
r_int
id|close
suffix:semicolon
DECL|member|close_wait
r_int
id|close_wait
suffix:semicolon
DECL|member|last_ack
r_int
id|last_ack
suffix:semicolon
DECL|member|listen
r_int
id|listen
suffix:semicolon
DECL|member|tcp
)brace
id|tcp
suffix:semicolon
DECL|member|udp
r_int
id|udp
suffix:semicolon
DECL|member|icmp
r_int
id|icmp
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; *&t;AUTOFW stuff &n; */
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
multiline_comment|/* WARNING: bitwise equal to ip_autofw  in net/ip_autofw.h */
DECL|struct|ip_autofw_user
r_struct
id|ip_autofw_user
(brace
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|member|type
id|u_int16_t
id|type
suffix:semicolon
DECL|member|low
id|u_int16_t
id|low
suffix:semicolon
DECL|member|hidden
id|u_int16_t
id|hidden
suffix:semicolon
DECL|member|high
id|u_int16_t
id|high
suffix:semicolon
DECL|member|visible
id|u_int16_t
id|visible
suffix:semicolon
DECL|member|protocol
id|u_int16_t
id|protocol
suffix:semicolon
DECL|member|lastcontact
id|u_int32_t
id|lastcontact
suffix:semicolon
DECL|member|where
id|u_int32_t
id|where
suffix:semicolon
DECL|member|ctlproto
id|u_int16_t
id|ctlproto
suffix:semicolon
DECL|member|ctlport
id|u_int16_t
id|ctlport
suffix:semicolon
DECL|member|flags
id|u_int16_t
id|flags
suffix:semicolon
multiline_comment|/* struct timer_list timer; */
)brace
suffix:semicolon
multiline_comment|/* &n; *&t;PORTFW stuff &n; */
DECL|struct|ip_portfw_user
r_struct
id|ip_portfw_user
(brace
DECL|member|protocol
id|u_int16_t
id|protocol
suffix:semicolon
multiline_comment|/* Which protocol are we talking? */
DECL|member|laddr
DECL|member|raddr
id|u_int32_t
id|laddr
comma
id|raddr
suffix:semicolon
multiline_comment|/* Remote address */
DECL|member|lport
DECL|member|rport
id|u_int16_t
id|lport
comma
id|rport
suffix:semicolon
multiline_comment|/* Local and remote port */
DECL|member|pref
r_int
id|pref
suffix:semicolon
multiline_comment|/* Preference value */
)brace
suffix:semicolon
multiline_comment|/* &n; *&t;MARKFW stuff &n; */
DECL|struct|ip_markfw_user
r_struct
id|ip_markfw_user
(brace
DECL|member|fwmark
id|u_int32_t
id|fwmark
suffix:semicolon
multiline_comment|/* Firewalling mark */
DECL|member|raddr
id|u_int32_t
id|raddr
suffix:semicolon
multiline_comment|/* remote port */
DECL|member|rport
id|u_int16_t
id|rport
suffix:semicolon
multiline_comment|/* remote port */
DECL|member|dummy
id|u_int16_t
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
DECL|macro|IP_FW_MASQCTL_MAX
mdefine_line|#define IP_FW_MASQCTL_MAX 256
DECL|macro|IP_MASQ_TNAME_MAX
mdefine_line|#define IP_MASQ_TNAME_MAX  32
DECL|struct|ip_masq_ctl
r_struct
id|ip_masq_ctl
(brace
DECL|member|m_target
r_int
id|m_target
suffix:semicolon
DECL|member|m_cmd
r_int
id|m_cmd
suffix:semicolon
DECL|member|m_tname
r_char
id|m_tname
(braket
id|IP_MASQ_TNAME_MAX
)braket
suffix:semicolon
r_union
(brace
DECL|member|portfw_user
r_struct
id|ip_portfw_user
id|portfw_user
suffix:semicolon
DECL|member|autofw_user
r_struct
id|ip_autofw_user
id|autofw_user
suffix:semicolon
DECL|member|markfw_user
r_struct
id|ip_markfw_user
id|markfw_user
suffix:semicolon
DECL|member|user
r_struct
id|ip_masq_user
id|user
suffix:semicolon
DECL|member|m_raw
r_int
r_char
id|m_raw
(braket
id|IP_FW_MASQCTL_MAX
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP_MASQ_CTL_BSIZE
mdefine_line|#define IP_MASQ_CTL_BSIZE (offsetof (struct ip_masq_ctl,u))
DECL|macro|IP_MASQ_TARGET_CORE
mdefine_line|#define IP_MASQ_TARGET_CORE&t;1
DECL|macro|IP_MASQ_TARGET_MOD
mdefine_line|#define IP_MASQ_TARGET_MOD&t;2&t;/* masq_mod is selected by &quot;name&quot; */
DECL|macro|IP_MASQ_TARGET_USER
mdefine_line|#define IP_MASQ_TARGET_USER&t;3&t;
DECL|macro|IP_MASQ_TARGET_LAST
mdefine_line|#define IP_MASQ_TARGET_LAST&t;4
DECL|macro|IP_MASQ_CMD_NONE
mdefine_line|#define IP_MASQ_CMD_NONE&t;0
DECL|macro|IP_MASQ_CMD_INSERT
mdefine_line|#define IP_MASQ_CMD_INSERT&t;1
DECL|macro|IP_MASQ_CMD_ADD
mdefine_line|#define IP_MASQ_CMD_ADD&t;&t;2
DECL|macro|IP_MASQ_CMD_SET
mdefine_line|#define IP_MASQ_CMD_SET&t;&t;3
DECL|macro|IP_MASQ_CMD_DEL
mdefine_line|#define IP_MASQ_CMD_DEL&t;&t;4
DECL|macro|IP_MASQ_CMD_GET
mdefine_line|#define IP_MASQ_CMD_GET&t;&t;5
DECL|macro|IP_MASQ_CMD_FLUSH
mdefine_line|#define IP_MASQ_CMD_FLUSH&t;6
DECL|macro|IP_MASQ_CMD_LIST
mdefine_line|#define IP_MASQ_CMD_LIST&t;7
DECL|macro|IP_MASQ_CMD_ENABLE
mdefine_line|#define IP_MASQ_CMD_ENABLE&t;8
DECL|macro|IP_MASQ_CMD_DISABLE
mdefine_line|#define IP_MASQ_CMD_DISABLE&t;9
macro_line|#endif /* _LINUX_IP_MASQ_H */
eof
