multiline_comment|/*&n; * linux/include/linux/sunrpc/stats.h&n; *&n; * Client statistics collection for SUN RPC&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_STATS_H
DECL|macro|_LINUX_SUNRPC_STATS_H
mdefine_line|#define _LINUX_SUNRPC_STATS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|struct|rpc_stat
r_struct
id|rpc_stat
(brace
DECL|member|program
r_struct
id|rpc_program
op_star
id|program
suffix:semicolon
DECL|member|netcnt
r_int
r_int
id|netcnt
comma
DECL|member|netudpcnt
id|netudpcnt
comma
DECL|member|nettcpcnt
id|nettcpcnt
comma
DECL|member|nettcpconn
id|nettcpconn
comma
DECL|member|netreconn
id|netreconn
suffix:semicolon
DECL|member|rpccnt
r_int
r_int
id|rpccnt
comma
DECL|member|rpcretrans
id|rpcretrans
comma
DECL|member|rpcauthrefresh
id|rpcauthrefresh
comma
DECL|member|rpcgarbage
id|rpcgarbage
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|svc_stat
r_struct
id|svc_stat
(brace
DECL|member|program
r_struct
id|svc_program
op_star
id|program
suffix:semicolon
DECL|member|netcnt
r_int
r_int
id|netcnt
comma
DECL|member|netudpcnt
id|netudpcnt
comma
DECL|member|nettcpcnt
id|nettcpcnt
comma
DECL|member|nettcpconn
id|nettcpconn
suffix:semicolon
DECL|member|rpccnt
r_int
r_int
id|rpccnt
comma
DECL|member|rpcbadfmt
id|rpcbadfmt
comma
DECL|member|rpcbadauth
id|rpcbadauth
comma
DECL|member|rpcbadclnt
id|rpcbadclnt
suffix:semicolon
)brace
suffix:semicolon
r_void
id|rpc_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpc_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_void
id|rpc_modcount
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
r_struct
id|proc_dir_entry
op_star
id|rpc_proc_register
c_func
(paren
r_struct
id|rpc_stat
op_star
)paren
suffix:semicolon
r_void
id|rpc_proc_unregister
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_int
id|rpc_proc_read
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|rpc_proc_zero
c_func
(paren
r_struct
id|rpc_program
op_star
)paren
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|svc_proc_register
c_func
(paren
r_struct
id|svc_stat
op_star
)paren
suffix:semicolon
r_void
id|svc_proc_unregister
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_int
id|svc_proc_read
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|svc_proc_zero
c_func
(paren
r_struct
id|svc_program
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|function|svc_proc_unregister
r_extern
r_inline
r_void
id|svc_proc_unregister
c_func
(paren
r_const
r_char
op_star
id|p
)paren
(brace
)brace
DECL|function|svc_proc_register
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|svc_proc_register
c_func
(paren
r_struct
id|svc_stat
op_star
id|s
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|svc_proc_read
r_extern
r_inline
r_int
id|svc_proc_read
c_func
(paren
r_char
op_star
id|a
comma
r_char
op_star
op_star
id|b
comma
id|off_t
id|c
comma
r_int
id|d
comma
r_int
op_star
id|e
comma
r_void
op_star
id|f
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_SUNRPC_STATS_H */
eof
