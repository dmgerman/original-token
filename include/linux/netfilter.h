macro_line|#ifndef __LINUX_NETFILTER_H
DECL|macro|__LINUX_NETFILTER_H
mdefine_line|#define __LINUX_NETFILTER_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/net.h&gt;
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
DECL|macro|NF_MAX_VERDICT
mdefine_line|#define NF_MAX_VERDICT NF_QUEUE
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
mdefine_line|#define NF_MAX_HOOKS 5
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
)paren
suffix:semicolon
DECL|typedef|nf_cacheflushfn
r_typedef
r_int
r_int
id|nf_cacheflushfn
c_func
(paren
r_const
r_void
op_star
id|packet
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
id|u_int32_t
id|packetcount
comma
id|u_int32_t
id|bytecount
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
DECL|member|flush
id|nf_cacheflushfn
op_star
id|flush
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
DECL|struct|nf_setsockopt_ops
r_struct
id|nf_setsockopt_ops
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
DECL|member|optmin
r_int
id|optmin
suffix:semicolon
DECL|member|optmax
r_int
id|optmax
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
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
multiline_comment|/* Functions to register setsockopt ranges (inclusive). */
r_int
id|nf_register_sockopt
c_func
(paren
r_struct
id|nf_setsockopt_ops
op_star
id|reg
)paren
suffix:semicolon
r_void
id|nf_unregister_sockopt
c_func
(paren
r_struct
id|nf_setsockopt_ops
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
multiline_comment|/* Activate hook/flush; either okfn or kfree_skb called, unless a hook&n;   returns NF_STOLEN (in which case, it&squot;s up to the hook to deal with&n;   the consequences).&n;&n;   Returns -ERRNO if packet dropped.  Zero means queued, stolen or&n;   accepted.&n;*/
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
r_void
id|nf_cacheflush
c_func
(paren
r_int
id|pf
comma
r_int
r_int
id|hook
comma
r_const
r_void
op_star
id|packet
comma
r_const
r_struct
id|net_device
op_star
id|indev
comma
r_const
r_struct
id|net_device
op_star
id|outdev
comma
id|__u32
id|packetcount
comma
id|__u32
id|bytecount
)paren
suffix:semicolon
multiline_comment|/* Call setsockopt() */
r_int
id|nf_setsockopt
c_func
(paren
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
r_int
id|len
)paren
suffix:semicolon
DECL|struct|nf_wakeme
r_struct
id|nf_wakeme
(brace
DECL|member|sleep
id|wait_queue_head_t
id|sleep
suffix:semicolon
DECL|member|skbq
r_struct
id|sk_buff_head
id|skbq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For netfilter device. */
DECL|struct|nf_interest
r_struct
id|nf_interest
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
multiline_comment|/* Bitmask of hook numbers to match (1 &lt;&lt; hooknum). */
DECL|member|hookmask
r_int
r_int
id|hookmask
suffix:semicolon
multiline_comment|/* If non-zero, only catch packets with this mark. */
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
multiline_comment|/* If non-zero, only catch packets of this reason. */
DECL|member|reason
r_int
r_int
id|reason
suffix:semicolon
DECL|member|wake
r_struct
id|nf_wakeme
op_star
id|wake
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For asynchronous packet handling. */
r_extern
r_void
id|nf_register_interest
c_func
(paren
r_struct
id|nf_interest
op_star
id|interest
)paren
suffix:semicolon
r_extern
r_void
id|nf_unregister_interest
c_func
(paren
r_struct
id|nf_interest
op_star
id|interest
)paren
suffix:semicolon
r_extern
r_void
id|nf_getinfo
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
op_star
id|indev
comma
r_struct
id|net_device
op_star
op_star
id|outdev
comma
r_int
r_int
op_star
id|mark
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
r_int
r_int
id|mark
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
multiline_comment|/* Use which one you mean explicitly.  You have been warned. */
macro_line|#include &lt;linux/types.h&gt;
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
DECL|enum|nf_reason
r_enum
id|nf_reason
(brace
multiline_comment|/* Do not, NOT, reorder these.  Add at end. */
DECL|enumerator|NF_REASON_NONE
id|NF_REASON_NONE
comma
DECL|enumerator|NF_REASON_SET_BY_IPCHAINS
id|NF_REASON_SET_BY_IPCHAINS
comma
DECL|enumerator|NF_REASON_FOR_ROUTING
id|NF_REASON_FOR_ROUTING
comma
DECL|enumerator|NF_REASON_FOR_CLS_FW
id|NF_REASON_FOR_CLS_FW
comma
DECL|enumerator|NF_REASON_MIN_RESERVED_FOR_CONNTRACK
id|NF_REASON_MIN_RESERVED_FOR_CONNTRACK
op_assign
l_int|1024
comma
)brace
suffix:semicolon
macro_line|#endif /*__LINUX_NETFILTER_H*/
eof
