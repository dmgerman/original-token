macro_line|#ifndef _LINUX_KERNELD_H
DECL|macro|_LINUX_KERNELD_H
mdefine_line|#define _LINUX_KERNELD_H
DECL|macro|KERNELD_SYSTEM
mdefine_line|#define KERNELD_SYSTEM 1
DECL|macro|KERNELD_REQUEST_MODULE
mdefine_line|#define KERNELD_REQUEST_MODULE 2 /* &quot;insmod&quot; */
DECL|macro|KERNELD_RELEASE_MODULE
mdefine_line|#define KERNELD_RELEASE_MODULE 3 /* &quot;rmmod&quot; */
DECL|macro|KERNELD_DELAYED_RELEASE_MODULE
mdefine_line|#define KERNELD_DELAYED_RELEASE_MODULE 4 /* &quot;rmmod&quot; */
DECL|macro|KERNELD_CANCEL_RELEASE_MODULE
mdefine_line|#define KERNELD_CANCEL_RELEASE_MODULE 5 /* &quot;rmmod&quot; */
DECL|macro|KERNELD_REQUEST_ROUTE
mdefine_line|#define KERNELD_REQUEST_ROUTE 6 /* from net/ipv4/route.c */
DECL|macro|KERNELD_BLANKER
mdefine_line|#define KERNELD_BLANKER 7 /* from drivers/char/console.c */
DECL|macro|KERNELD_PNP
mdefine_line|#define KERNELD_PNP 8 /* from drivers/pnp/kerneld.c */
DECL|macro|KERNELD_ARP
mdefine_line|#define KERNELD_ARP 256 /* from net/ipv4/arp.c */
multiline_comment|/*&n; * Uncomment the following line for the new kerneld protocol&n; * This includes the pid of the kernel level requester into the kerneld header&n; */
multiline_comment|/*&n;#define NEW_KERNELD_PROTOCOL&n; */
macro_line|#ifdef NEW_KERNELD_PROTOCOL
DECL|macro|OLDIPC_KERNELD
mdefine_line|#define OLDIPC_KERNELD 00040000   /* use the kerneld message channel */
DECL|macro|IPC_KERNELD
mdefine_line|#define IPC_KERNELD 00140000   /* use the kerneld message channel, new protocol */
DECL|macro|KDHDR
mdefine_line|#define KDHDR (sizeof(long) + sizeof(short) + sizeof(short))
DECL|macro|NULL_KDHDR
mdefine_line|#define NULL_KDHDR 0, 2, 0
macro_line|#else
DECL|macro|IPC_KERNELD
mdefine_line|#define IPC_KERNELD 00040000   /* use the kerneld message channel */
DECL|macro|KDHDR
mdefine_line|#define KDHDR (sizeof(long))
DECL|macro|NULL_KDHDR
mdefine_line|#define NULL_KDHDR 0
macro_line|#endif
DECL|macro|KERNELD_MAXCMD
mdefine_line|#define KERNELD_MAXCMD 0x7ffeffff
DECL|macro|KERNELD_MINSEQ
mdefine_line|#define KERNELD_MINSEQ 0x7fff0000 /* &quot;commands&quot; legal up to 0x7ffeffff */
DECL|macro|KERNELD_WAIT
mdefine_line|#define KERNELD_WAIT 0x80000000
DECL|macro|KERNELD_NOWAIT
mdefine_line|#define KERNELD_NOWAIT 0
DECL|struct|kerneld_msg
r_struct
id|kerneld_msg
(brace
DECL|member|mtype
r_int
id|mtype
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
macro_line|#ifdef NEW_KERNELD_PROTOCOL
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|member|text
r_char
op_star
id|text
suffix:semicolon
macro_line|#else
DECL|member|text
r_char
id|text
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|kerneld_send
c_func
(paren
r_int
id|msgtype
comma
r_int
id|ret_size
comma
r_int
id|msgsz
comma
r_const
r_char
op_star
id|text
comma
r_const
r_char
op_star
id|ret_val
)paren
suffix:semicolon
multiline_comment|/*&n; * Request that a module should be loaded.&n; * Wait for the exit status from insmod/modprobe.&n; * If it fails, it fails... at least we tried...&n; */
DECL|function|request_module
r_static
r_inline
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_REQUEST_MODULE
comma
l_int|0
op_or
id|KERNELD_WAIT
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Request the removal of a module, maybe don&squot;t wait for it.&n; * It doesn&squot;t matter if the removal fails, now does it?&n; */
DECL|function|release_module
r_static
r_inline
r_int
id|release_module
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|waitflag
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_RELEASE_MODULE
comma
l_int|0
op_or
(paren
id|waitflag
ques
c_cond
id|KERNELD_WAIT
suffix:colon
id|KERNELD_NOWAIT
)paren
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Request a delayed removal of a module, but don&squot;t wait for it.&n; * The delay is done by kerneld (default: 60 seconds)&n; */
DECL|function|delayed_release_module
r_static
r_inline
r_int
id|delayed_release_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_DELAYED_RELEASE_MODULE
comma
l_int|0
op_or
id|KERNELD_NOWAIT
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to cancel a previous request for removal of a module,&n; * but don&squot;t wait for it.&n; * This call can be made if the kernel wants to prevent a delayed&n; * unloading of a module.&n; */
DECL|function|cancel_release_module
r_static
r_inline
r_int
id|cancel_release_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_CANCEL_RELEASE_MODULE
comma
l_int|0
op_or
id|KERNELD_NOWAIT
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform an &quot;inverted&quot; system call, maybe return the exit status&n; */
DECL|function|ksystem
r_static
r_inline
r_int
id|ksystem
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_int
id|waitflag
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_SYSTEM
comma
l_int|0
op_or
(paren
id|waitflag
ques
c_cond
id|KERNELD_WAIT
suffix:colon
id|KERNELD_NOWAIT
)paren
comma
id|strlen
c_func
(paren
id|cmd
)paren
comma
id|cmd
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to create a route, possibly by opening a ppp-connection&n; */
DECL|function|kerneld_route
r_static
r_inline
r_int
id|kerneld_route
c_func
(paren
r_const
r_char
op_star
id|ip_route
)paren
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_REQUEST_ROUTE
comma
l_int|0
op_or
id|KERNELD_WAIT
comma
id|strlen
c_func
(paren
id|ip_route
)paren
comma
id|ip_route
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle an external screen blanker&n; */
DECL|function|kerneld_blanker
r_static
r_inline
r_int
id|kerneld_blanker
c_func
(paren
r_int
id|on_off
)paren
multiline_comment|/* 0 =&gt; &quot;off&quot;, else &quot;on&quot; */
(brace
r_return
id|kerneld_send
c_func
(paren
id|KERNELD_BLANKER
comma
l_int|0
op_or
(paren
id|on_off
ques
c_cond
id|KERNELD_NOWAIT
suffix:colon
id|KERNELD_WAIT
)paren
comma
id|strlen
c_func
(paren
id|on_off
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
comma
id|on_off
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
