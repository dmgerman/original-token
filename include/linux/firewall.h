macro_line|#ifndef __LINUX_FIREWALL_H
DECL|macro|__LINUX_FIREWALL_H
mdefine_line|#define __LINUX_FIREWALL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Definitions for loadable firewall modules&n; */
DECL|macro|FW_QUEUE
mdefine_line|#define FW_QUEUE&t;0
DECL|macro|FW_BLOCK
mdefine_line|#define FW_BLOCK&t;1
DECL|macro|FW_ACCEPT
mdefine_line|#define FW_ACCEPT&t;2
DECL|macro|FW_REJECT
mdefine_line|#define FW_REJECT&t;(-1)
DECL|macro|FW_REDIRECT
mdefine_line|#define FW_REDIRECT&t;3
DECL|macro|FW_MASQUERADE
mdefine_line|#define FW_MASQUERADE&t;4
DECL|macro|FW_SKIP
mdefine_line|#define FW_SKIP&t;&t;5
DECL|struct|firewall_ops
r_struct
id|firewall_ops
(brace
DECL|member|next
r_struct
id|firewall_ops
op_star
id|next
suffix:semicolon
DECL|member|fw_forward
r_int
(paren
op_star
id|fw_forward
)paren
(paren
r_struct
id|firewall_ops
op_star
id|this
comma
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
DECL|member|fw_input
r_int
(paren
op_star
id|fw_input
)paren
(paren
r_struct
id|firewall_ops
op_star
id|this
comma
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
DECL|member|fw_output
r_int
(paren
op_star
id|fw_output
)paren
(paren
r_struct
id|firewall_ops
op_star
id|this
comma
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
multiline_comment|/* Data falling in the second 486 cache line isn&squot;t used directly&n;&t;   during a firewall call and scan, only by insert/delete and other&n;&t;   unusual cases&n;&t; */
DECL|member|fw_pf
r_int
id|fw_pf
suffix:semicolon
multiline_comment|/* Protocol family &t;&t;&t;*/
DECL|member|fw_priority
r_int
id|fw_priority
suffix:semicolon
multiline_comment|/* Priority of chosen firewalls &t;*/
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|register_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
suffix:semicolon
r_extern
r_int
id|unregister_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
suffix:semicolon
r_extern
r_void
id|fwchain_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FIREWALL
r_extern
r_int
id|call_fw_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
id|call_in_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
id|call_out_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
macro_line|#else
DECL|function|call_fw_firewall
r_extern
id|__inline__
r_int
id|call_fw_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
)paren
(brace
r_return
id|FW_ACCEPT
suffix:semicolon
)brace
DECL|function|call_in_firewall
r_extern
id|__inline__
r_int
id|call_in_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
)paren
(brace
r_return
id|FW_ACCEPT
suffix:semicolon
)brace
DECL|function|call_out_firewall
r_extern
id|__inline__
r_int
id|call_out_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
)paren
(brace
r_return
id|FW_ACCEPT
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
