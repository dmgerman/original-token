multiline_comment|/* Kernel module to match various things tied to sockets associated with&n;   locally generated outgoing packets.&n;&n;   Copyright (C) 2000 Marc Boucher&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_owner.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
r_static
r_int
DECL|function|match_pid
id|match_pid
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
id|pid_t
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
suffix:semicolon
r_int
id|i
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|p
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out
suffix:semicolon
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
id|files
op_assign
id|p-&gt;files
suffix:semicolon
r_if
c_cond
(paren
id|files
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|files-&gt;max_fds
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|fcheck_files
c_func
(paren
id|files
comma
id|i
)paren
op_eq
id|skb-&gt;sk-&gt;socket-&gt;file
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|match_sid
id|match_sid
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
id|pid_t
id|sid
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|skb-&gt;sk-&gt;socket-&gt;file
suffix:semicolon
r_int
id|i
comma
id|found
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_struct
id|files_struct
op_star
id|files
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;session
op_ne
id|sid
)paren
r_continue
suffix:semicolon
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
id|files
op_assign
id|p-&gt;files
suffix:semicolon
r_if
c_cond
(paren
id|files
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|files-&gt;max_fds
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|fcheck_files
c_func
(paren
id|files
comma
id|i
)paren
op_eq
id|file
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
r_static
r_int
DECL|function|match
id|match
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|matchinfo
comma
r_int
id|offset
comma
r_const
r_void
op_star
id|hdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_const
r_struct
id|ipt_owner_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;sk
op_logical_or
op_logical_neg
id|skb-&gt;sk-&gt;socket
op_logical_or
op_logical_neg
id|skb-&gt;sk-&gt;socket-&gt;file
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;match
op_amp
id|IPT_OWNER_UID
)paren
(brace
r_if
c_cond
(paren
(paren
id|skb-&gt;sk-&gt;socket-&gt;file-&gt;f_uid
op_ne
id|info-&gt;uid
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;invert
op_amp
id|IPT_OWNER_UID
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;match
op_amp
id|IPT_OWNER_GID
)paren
(brace
r_if
c_cond
(paren
(paren
id|skb-&gt;sk-&gt;socket-&gt;file-&gt;f_gid
op_ne
id|info-&gt;gid
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;invert
op_amp
id|IPT_OWNER_GID
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;match
op_amp
id|IPT_OWNER_PID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|match_pid
c_func
(paren
id|skb
comma
id|info-&gt;pid
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;invert
op_amp
id|IPT_OWNER_PID
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;match
op_amp
id|IPT_OWNER_SID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|match_sid
c_func
(paren
id|skb
comma
id|info-&gt;sid
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|info-&gt;invert
op_amp
id|IPT_OWNER_SID
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|checkentry
id|checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_ip
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_if
c_cond
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ipt_owner: only valid for LOCAL_OUT or POST_ROUTING.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|matchsize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_owner_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|owner_match
r_static
r_struct
id|ipt_match
id|owner_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;owner&quot;
comma
op_amp
id|match
comma
op_amp
id|checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|ipt_register_match
c_func
(paren
op_amp
id|owner_match
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ipt_unregister_match
c_func
(paren
op_amp
id|owner_match
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
