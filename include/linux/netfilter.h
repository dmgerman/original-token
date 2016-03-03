macro_line|#ifndef __LINUX_NETFILTER_H
DECL|macro|__LINUX_NETFILTER_H
mdefine_line|#define __LINUX_NETFILTER_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#endif
multiline_comment|/* Responses from hook functions. */
DECL|macro|NF_DROP
mdefine_line|#define NF_DROP 0
DECL|macro|NF_ACCEPT
mdefine_line|#define NF_ACCEPT 1
DECL|macro|NF_STOLEN
mdefine_line|#define NF_STOLEN 2
DECL|macro|NF_QUEUE
mdefine_line|#define NF_QUEUE 3
DECL|macro|NF_REPEAT
mdefine_line|#define NF_REPEAT 4
DECL|macro|NF_MAX_VERDICT
mdefine_line|#define NF_MAX_VERDICT NF_REPEAT
multiline_comment|/* Generic cache responses from hook functions. */
DECL|macro|NFC_ALTERED
mdefine_line|#define NFC_ALTERED 0x8000
DECL|macro|NFC_UNKNOWN
mdefine_line|#define NFC_UNKNOWN 0x4000
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NETFILTER
r_extern
r_void
id|netfilter_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Largest hook number + 1 */
DECL|macro|NF_MAX_HOOKS
mdefine_line|#define NF_MAX_HOOKS 8
r_struct
id|sk_buff
suffix:semicolon
r_struct
id|net_device
suffix:semicolon
DECL|typedef|nf_hookfn
r_typedef
r_int
r_int
id|nf_hookfn
c_func
(paren
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
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
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
suffix:semicolon
DECL|struct|nf_hook_ops
r_struct
id|nf_hook_ops
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* User fills in from here down. */
DECL|member|hook
id|nf_hookfn
op_star
id|hook
suffix:semicolon
DECL|member|pf
r_int
id|pf
suffix:semicolon
DECL|member|hooknum
r_int
id|hooknum
suffix:semicolon
multiline_comment|/* Hooks are ordered in ascending priority. */
DECL|member|priority
r_int
id|priority
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nf_sockopt_ops
r_struct
id|nf_sockopt_ops
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|pf
r_int
id|pf
suffix:semicolon
multiline_comment|/* Non-inclusive ranges: use 0/0/NULL to never get called. */
DECL|member|set_optmin
r_int
id|set_optmin
suffix:semicolon
DECL|member|set_optmax
r_int
id|set_optmax
suffix:semicolon
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optval
comma
r_void
op_star
id|user
comma
r_int
r_int
id|len
)paren
suffix:semicolon
DECL|member|get_optmin
r_int
id|get_optmin
suffix:semicolon
DECL|member|get_optmax
r_int
id|get_optmax
suffix:semicolon
DECL|member|get
r_int
(paren
op_star
id|get
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optval
comma
r_void
op_star
id|user
comma
r_int
op_star
id|len
)paren
suffix:semicolon
multiline_comment|/* Number of users inside set() or get(). */
DECL|member|use
r_int
r_int
id|use
suffix:semicolon
DECL|member|cleanup_task
r_struct
id|task_struct
op_star
id|cleanup_task
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Each queued (to userspace) skbuff has one of these. */
DECL|struct|nf_info
r_struct
id|nf_info
(brace
multiline_comment|/* The ops struct which sent us to userspace. */
DECL|member|elem
r_struct
id|nf_hook_ops
op_star
id|elem
suffix:semicolon
multiline_comment|/* If we&squot;re sent to userspace, this keeps housekeeping info */
DECL|member|pf
r_int
id|pf
suffix:semicolon
DECL|member|hook
r_int
r_int
id|hook
suffix:semicolon
DECL|member|indev
DECL|member|outdev
r_struct
id|net_device
op_star
id|indev
comma
op_star
id|outdev
suffix:semicolon
DECL|member|okfn
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function to register/unregister hook points. */
r_int
id|nf_register_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
suffix:semicolon
r_void
id|nf_unregister_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
suffix:semicolon
multiline_comment|/* Functions to register get/setsockopt ranges (non-inclusive).  You&n;   need to check permissions yourself! */
r_int
id|nf_register_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
suffix:semicolon
r_void
id|nf_unregister_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|nf_hooks
(braket
id|NPROTO
)braket
(braket
id|NF_MAX_HOOKS
)braket
suffix:semicolon
multiline_comment|/* Activate hook; either okfn or kfree_skb called, unless a hook&n;   returns NF_STOLEN (in which case, it&squot;s up to the hook to deal with&n;   the consequences).&n;&n;   Returns -ERRNO if packet dropped.  Zero means queued, stolen or&n;   accepted.&n;*/
multiline_comment|/* RR:&n;   &gt; I don&squot;t want nf_hook to return anything because people might forget&n;   &gt; about async and trust the return value to mean &quot;packet was ok&quot;.&n;&n;   AK:&n;   Just document it clearly, then you can expect some sense from kernel&n;   coders :)&n;*/
multiline_comment|/* This is gross, but inline doesn&squot;t cut it for avoiding the function&n;   call in fast path: gcc doesn&squot;t inline (needs value tracking?). --RR */
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|NF_HOOK
mdefine_line|#define NF_HOOK nf_hook_slow
macro_line|#else
DECL|macro|NF_HOOK
mdefine_line|#define NF_HOOK(pf, hook, skb, indev, outdev, okfn)&t;&t;&t;&bslash;&n;(list_empty(&amp;nf_hooks[(pf)][(hook)])&t;&t;&t;&t;&t;&bslash;&n; ? (okfn)(skb)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; : nf_hook_slow((pf), (hook), (skb), (indev), (outdev), (okfn)))
macro_line|#endif
r_int
id|nf_hook_slow
c_func
(paren
r_int
id|pf
comma
r_int
r_int
id|hook
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|indev
comma
r_struct
id|net_device
op_star
id|outdev
comma
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* Call setsockopt() */
r_int
id|nf_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|pf
comma
r_int
id|optval
comma
r_char
op_star
id|opt
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|nf_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|pf
comma
r_int
id|optval
comma
r_char
op_star
id|opt
comma
r_int
op_star
id|len
)paren
suffix:semicolon
multiline_comment|/* Packet queuing */
DECL|typedef|nf_queue_outfn_t
r_typedef
r_int
(paren
op_star
id|nf_queue_outfn_t
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nf_info
op_star
id|info
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|nf_register_queue_handler
c_func
(paren
r_int
id|pf
comma
id|nf_queue_outfn_t
id|outfn
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|nf_unregister_queue_handler
c_func
(paren
r_int
id|pf
)paren
suffix:semicolon
r_extern
r_void
id|nf_reinject
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nf_info
op_star
id|info
comma
r_int
r_int
id|verdict
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_extern
r_void
id|nf_dump_skb
c_func
(paren
r_int
id|pf
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* FIXME: Before cache is ever used, this must be implemented for real. */
r_extern
r_void
id|nf_invalidate_cache
c_func
(paren
r_int
id|pf
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_NETFILTER */
DECL|macro|NF_HOOK
mdefine_line|#define NF_HOOK(pf, hook, skb, indev, outdev, okfn) (okfn)(skb)
macro_line|#endif /*CONFIG_NETFILTER*/
multiline_comment|/* From arch/i386/kernel/smp.c:&n; *&n; *&t;Why isn&squot;t this somewhere standard ??&n; *&n; * Maybe because this procedure is horribly buggy, and does&n; * not deserve to live.  Think about signedness issues for five&n; * seconds to see why.&t;&t;- Linus&n; */
multiline_comment|/* Two signed, return a signed. */
DECL|macro|SMAX
mdefine_line|#define SMAX(a,b) ((ssize_t)(a)&gt;(ssize_t)(b) ? (ssize_t)(a) : (ssize_t)(b))
DECL|macro|SMIN
mdefine_line|#define SMIN(a,b) ((ssize_t)(a)&lt;(ssize_t)(b) ? (ssize_t)(a) : (ssize_t)(b))
multiline_comment|/* Two unsigned, return an unsigned. */
DECL|macro|UMAX
mdefine_line|#define UMAX(a,b) ((size_t)(a)&gt;(size_t)(b) ? (size_t)(a) : (size_t)(b))
DECL|macro|UMIN
mdefine_line|#define UMIN(a,b) ((size_t)(a)&lt;(size_t)(b) ? (size_t)(a) : (size_t)(b))
multiline_comment|/* Two unsigned, return a signed. */
DECL|macro|SUMAX
mdefine_line|#define SUMAX(a,b) ((size_t)(a)&gt;(size_t)(b) ? (ssize_t)(a) : (ssize_t)(b))
DECL|macro|SUMIN
mdefine_line|#define SUMIN(a,b) ((size_t)(a)&lt;(size_t)(b) ? (ssize_t)(a) : (ssize_t)(b))
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*__LINUX_NETFILTER_H*/
eof
