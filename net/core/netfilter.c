multiline_comment|/* netfilter.c: look after the filters for various protocols. &n; * Heavily influenced by the old firewall.c by David Bonn and Alan Cox.&n; *&n; * Thanks to Rob `CmdrTaco&squot; Malda for not influencing this code in any&n; * way.&n; *&n; * Rusty Russell (C)1998 -- This code is GPL.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
multiline_comment|/* In this code, we can be waiting indefinitely for userspace to&n; * service a packet if a hook returns NF_QUEUE.  We could keep a count&n; * of skbuffs queued for userspace, and not deregister a hook unless&n; * this is zero, but that sucks.  Now, we simply check when the&n; * packets come back: if the hook is gone, the packet is discarded. */
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|NFDEBUG
mdefine_line|#define NFDEBUG(format, args...)  printk(format , ## args)
macro_line|#else
DECL|macro|NFDEBUG
mdefine_line|#define NFDEBUG(format, args...)
macro_line|#endif
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
DECL|member|mark
r_int
r_int
id|mark
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
DECL|variable|nf_lock
r_static
id|rwlock_t
id|nf_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|nf_sockopt_mutex
)paren
suffix:semicolon
DECL|variable|nf_hooks
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
r_static
id|LIST_HEAD
c_func
(paren
id|nf_sockopts
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|nf_interested
)paren
suffix:semicolon
DECL|function|nf_register_hook
r_int
id|nf_register_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|reg-&gt;pf
OL
l_int|0
op_logical_or
id|reg-&gt;pf
op_ge
id|NPROTO
op_logical_or
id|reg-&gt;hooknum
op_ge
id|NF_MAX_HOOKS
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_hook: bad vals: pf=%i, hooknum=%u.&bslash;n&quot;
comma
id|reg-&gt;pf
comma
id|reg-&gt;hooknum
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_hook: pf=%i hook=%u.&bslash;n&quot;
comma
id|reg-&gt;pf
comma
id|reg-&gt;hooknum
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_hooks
(braket
id|reg-&gt;pf
)braket
(braket
id|reg-&gt;hooknum
)braket
dot
id|next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_hooks
(braket
id|reg-&gt;pf
)braket
(braket
id|reg-&gt;hooknum
)braket
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|reg-&gt;priority
OL
(paren
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|i
)paren
op_member_access_from_pointer
id|priority
)paren
r_break
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|reg-&gt;list
comma
id|i-&gt;prev
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nf_unregister_hook
r_void
id|nf_unregister_hook
c_func
(paren
r_struct
id|nf_hook_ops
op_star
id|reg
)paren
(brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|reg-&gt;pf
OL
l_int|0
op_logical_or
id|reg-&gt;pf
op_ge
id|NPROTO
op_logical_or
id|reg-&gt;hooknum
op_ge
id|NF_MAX_HOOKS
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_unregister_hook: bad vals: pf=%i, hooknum=%u.&bslash;n&quot;
comma
id|reg-&gt;pf
comma
id|reg-&gt;hooknum
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|write_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|reg-&gt;list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Do exclusive ranges overlap? */
DECL|function|overlap
r_static
r_inline
r_int
id|overlap
c_func
(paren
r_int
id|min1
comma
r_int
id|max1
comma
r_int
id|min2
comma
r_int
id|max2
)paren
(brace
r_return
(paren
id|min1
op_ge
id|min2
op_logical_and
id|min1
OL
id|max2
)paren
op_logical_or
(paren
id|max1
OG
id|min2
op_logical_and
id|max1
op_le
id|max2
)paren
suffix:semicolon
)brace
multiline_comment|/* Functions to register sockopt ranges (exclusive). */
DECL|function|nf_register_sockopt
r_int
id|nf_register_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|reg-&gt;pf
OL
l_int|0
op_logical_or
id|reg-&gt;pf
op_ge
id|NPROTO
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_sockopt: bad val: pf=%i.&bslash;n&quot;
comma
id|reg-&gt;pf
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg-&gt;set_optmin
OG
id|reg-&gt;set_optmax
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_sockopt: bad set val: min=%i max=%i.&bslash;n&quot;
comma
id|reg-&gt;set_optmin
comma
id|reg-&gt;set_optmax
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg-&gt;get_optmin
OG
id|reg-&gt;get_optmax
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_sockopt: bad get val: min=%i max=%i.&bslash;n&quot;
comma
id|reg-&gt;get_optmin
comma
id|reg-&gt;get_optmax
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_sockopts.next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_sockopts
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_struct
id|nf_sockopt_ops
op_star
id|ops
op_assign
(paren
r_struct
id|nf_sockopt_ops
op_star
)paren
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;pf
op_eq
id|reg-&gt;pf
op_logical_and
(paren
id|overlap
c_func
(paren
id|ops-&gt;set_optmin
comma
id|ops-&gt;set_optmax
comma
id|reg-&gt;set_optmin
comma
id|reg-&gt;set_optmax
)paren
op_logical_or
id|overlap
c_func
(paren
id|ops-&gt;get_optmin
comma
id|ops-&gt;get_optmax
comma
id|reg-&gt;get_optmin
comma
id|reg-&gt;get_optmax
)paren
)paren
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_sock overlap: %u-%u/%u-%u v %u-%u/%u-%u&bslash;n&quot;
comma
id|ops-&gt;set_optmin
comma
id|ops-&gt;set_optmax
comma
id|ops-&gt;get_optmin
comma
id|ops-&gt;get_optmax
comma
id|reg-&gt;set_optmin
comma
id|reg-&gt;set_optmax
comma
id|reg-&gt;get_optmin
comma
id|reg-&gt;get_optmax
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_add
c_func
(paren
op_amp
id|reg-&gt;list
comma
op_amp
id|nf_sockopts
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nf_unregister_sockopt
r_void
id|nf_unregister_sockopt
c_func
(paren
r_struct
id|nf_sockopt_ops
op_star
id|reg
)paren
(brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|reg-&gt;pf
OL
l_int|0
op_logical_or
id|reg-&gt;pf
op_ge
id|NPROTO
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_register_sockopt: bad val: pf=%i.&bslash;n&quot;
comma
id|reg-&gt;pf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* No point being interruptible: we&squot;re probably in cleanup_module() */
id|down
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|reg-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
DECL|function|nf_dump_skb
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
(brace
id|printk
c_func
(paren
l_string|&quot;skb: pf=%i %s dev=%s len=%u&bslash;n&quot;
comma
id|pf
comma
id|skb-&gt;sk
ques
c_cond
l_string|&quot;(owned)&quot;
suffix:colon
l_string|&quot;(unowned)&quot;
comma
id|skb-&gt;dev
ques
c_cond
id|skb-&gt;dev-&gt;name
suffix:colon
l_string|&quot;(no dev)&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pf
)paren
(brace
r_case
id|PF_INET
suffix:colon
(brace
r_const
r_struct
id|iphdr
op_star
id|ip
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|__u32
op_star
id|opt
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|ip
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|opti
suffix:semicolon
id|__u16
id|src_port
op_assign
l_int|0
comma
id|dst_port
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;protocol
op_eq
id|IPPROTO_TCP
op_logical_or
id|ip-&gt;protocol
op_eq
id|IPPROTO_UDP
)paren
(brace
r_struct
id|tcphdr
op_star
id|tcp
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|__u32
op_star
)paren
id|ip
op_plus
id|ip-&gt;ihl
)paren
suffix:semicolon
id|src_port
op_assign
id|ntohs
c_func
(paren
id|tcp-&gt;source
)paren
suffix:semicolon
id|dst_port
op_assign
id|ntohs
c_func
(paren
id|tcp-&gt;dest
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PROTO=%d %ld.%ld.%ld.%ld:%hu %ld.%ld.%ld.%ld:%hu&quot;
l_string|&quot; L=%hu S=0x%2.2hX I=%hu F=0x%4.4hX T=%hu&quot;
comma
id|ip-&gt;protocol
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;saddr
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;saddr
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;saddr
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;saddr
)paren
)paren
op_amp
l_int|0xFF
comma
id|src_port
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;daddr
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;daddr
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;daddr
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
comma
(paren
id|ntohl
c_func
(paren
id|ip-&gt;daddr
)paren
)paren
op_amp
l_int|0xFF
comma
id|dst_port
comma
id|ntohs
c_func
(paren
id|ip-&gt;tot_len
)paren
comma
id|ip-&gt;tos
comma
id|ntohs
c_func
(paren
id|ip-&gt;id
)paren
comma
id|ntohs
c_func
(paren
id|ip-&gt;frag_off
)paren
comma
id|ip-&gt;ttl
)paren
suffix:semicolon
r_for
c_loop
(paren
id|opti
op_assign
l_int|0
suffix:semicolon
id|opti
OL
(paren
id|ip-&gt;ihl
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|opti
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; O=0x%8.8X&quot;
comma
op_star
id|opt
op_increment
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nf_debug_ip_local_deliver
r_void
id|nf_debug_ip_local_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/* If it&squot;s a loopback packet, it must have come through&n;&t; * NF_IP_LOCAL_OUT, NF_IP_RAW_INPUT, NF_IP_PRE_ROUTING and&n;&t; * NF_IP_LOCAL_IN.  Otherwise, must have gone through&n;&t; * NF_IP_RAW_INPUT and NF_IP_PRE_ROUTING.  */
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;dev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: skb-&gt;dev is NULL.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|skb-&gt;dev-&gt;name
comma
l_string|&quot;lo&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
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
op_or
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: bad loopback skb: &quot;
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_local_deliver: bad non-lo skb: &quot;
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nf_debug_ip_loopback_xmit
r_void
id|nf_debug_ip_loopback_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|newskb
)paren
(brace
r_if
c_cond
(paren
id|newskb-&gt;nf_debug
op_ne
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
l_string|&quot;ip_dev_loopback_xmit: bad owned skb = %p: &quot;
comma
id|newskb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|newskb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|newskb
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear to avoid confusing input check */
id|newskb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|nf_debug_ip_finish_output2
r_void
id|nf_debug_ip_finish_output2
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/* If it&squot;s owned, it must have gone through the&n;&t; * NF_IP_LOCAL_OUT and NF_IP_POST_ROUTING.&n;&t; * Otherwise, must have gone through NF_IP_RAW_INPUT,&n;&t; * NF_IP_PRE_ROUTING, NF_IP_FORWARD and NF_IP_POST_ROUTING.&n;&t; */
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
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
l_string|&quot;ip_finish_output: bad owned skb = %p: &quot;
comma
id|skb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_ne
(paren
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
macro_line|#ifdef CONFIG_IP_NETFILTER_RAW_INPUT
op_or
(paren
l_int|1
op_lshift
id|NF_IP_RAW_INPUT
)paren
macro_line|#endif
op_or
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
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
l_string|&quot;ip_finish_output: bad unowned skb = %p: &quot;
comma
id|skb
)paren
suffix:semicolon
id|debug_print_hooks_ip
c_func
(paren
id|skb-&gt;nf_debug
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|PF_INET
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
DECL|function|nf_cacheflush
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
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
dot
id|next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|i
)paren
op_member_access_from_pointer
id|flush
)paren
(paren
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|i
)paren
op_member_access_from_pointer
id|flush
c_func
(paren
id|packet
comma
id|indev
comma
id|outdev
comma
id|packetcount
comma
id|bytecount
)paren
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Call get/setsockopt() */
DECL|function|nf_sockopt
r_static
r_int
id|nf_sockopt
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
id|val
comma
r_char
op_star
id|opt
comma
r_int
op_star
id|len
comma
r_int
id|get
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_sockopts.next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_sockopts
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_struct
id|nf_sockopt_ops
op_star
id|ops
op_assign
(paren
r_struct
id|nf_sockopt_ops
op_star
)paren
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;pf
op_eq
id|pf
)paren
(brace
r_if
c_cond
(paren
id|get
)paren
(brace
r_if
c_cond
(paren
id|val
op_ge
id|ops-&gt;get_optmin
op_logical_and
id|val
OL
id|ops-&gt;get_optmax
)paren
(brace
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|get
c_func
(paren
id|sk
comma
id|val
comma
id|opt
comma
id|len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|val
op_ge
id|ops-&gt;set_optmin
op_logical_and
id|val
OL
id|ops-&gt;set_optmax
)paren
(brace
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|set
c_func
(paren
id|sk
comma
id|val
comma
id|opt
comma
op_star
id|len
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
)brace
id|ret
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nf_sockopt_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|nf_setsockopt
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
id|val
comma
r_char
op_star
id|opt
comma
r_int
id|len
)paren
(brace
r_return
id|nf_sockopt
c_func
(paren
id|sk
comma
id|pf
comma
id|val
comma
id|opt
comma
op_amp
id|len
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nf_getsockopt
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
id|val
comma
r_char
op_star
id|opt
comma
r_int
op_star
id|len
)paren
(brace
r_return
id|nf_sockopt
c_func
(paren
id|sk
comma
id|pf
comma
id|val
comma
id|opt
comma
id|len
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|nf_iterate
r_static
r_int
r_int
id|nf_iterate
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_int
id|hook
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
r_struct
id|list_head
op_star
op_star
id|i
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
(brace
r_for
c_loop
(paren
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|i
op_ne
id|head
suffix:semicolon
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_struct
id|nf_hook_ops
op_star
id|elem
op_assign
(paren
r_struct
id|nf_hook_ops
op_star
)paren
op_star
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|elem
op_member_access_from_pointer
id|hook
c_func
(paren
id|hook
comma
id|skb
comma
id|indev
comma
id|outdev
comma
id|okfn
)paren
)paren
(brace
r_case
id|NF_QUEUE
suffix:colon
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_iterate: NF_QUEUE for %p.&bslash;n&quot;
comma
op_star
id|skb
)paren
suffix:semicolon
r_return
id|NF_QUEUE
suffix:semicolon
r_case
id|NF_STOLEN
suffix:colon
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_iterate: NF_STOLEN for %p.&bslash;n&quot;
comma
op_star
id|skb
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_iterate: NF_DROP for %p.&bslash;n&quot;
comma
op_star
id|skb
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_case
id|NF_ACCEPT
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|NFDEBUG
c_func
(paren
l_string|&quot;Evil return from %p(%u).&bslash;n&quot;
comma
id|elem-&gt;hook
comma
id|hook
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
DECL|function|nf_queue
r_static
r_void
id|nf_queue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|list_head
op_star
id|elem
comma
r_int
id|pf
comma
r_int
r_int
id|hook
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
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_struct
id|nf_info
op_star
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: OOM.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Can&squot;t do struct assignments with arrays in them.  Damn. */
id|info-&gt;elem
op_assign
(paren
r_struct
id|nf_hook_ops
op_star
)paren
id|elem
suffix:semicolon
id|info-&gt;mark
op_assign
id|skb-&gt;nfmark
suffix:semicolon
id|info-&gt;pf
op_assign
id|pf
suffix:semicolon
id|info-&gt;hook
op_assign
id|hook
suffix:semicolon
id|info-&gt;okfn
op_assign
id|okfn
suffix:semicolon
id|info-&gt;indev
op_assign
id|indev
suffix:semicolon
id|info-&gt;outdev
op_assign
id|outdev
suffix:semicolon
id|skb-&gt;nfmark
op_assign
(paren
r_int
r_int
)paren
id|info
suffix:semicolon
multiline_comment|/* Bump dev refs so they don&squot;t vanish while packet is out */
r_if
c_cond
(paren
id|indev
)paren
id|dev_hold
c_func
(paren
id|indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outdev
)paren
id|dev_hold
c_func
(paren
id|outdev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_interested.next
suffix:semicolon
id|i
op_ne
op_amp
id|nf_interested
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_struct
id|nf_interest
op_star
id|recip
op_assign
(paren
r_struct
id|nf_interest
op_star
)paren
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|recip-&gt;hookmask
op_amp
(paren
l_int|1
op_lshift
id|info-&gt;hook
)paren
)paren
op_logical_and
id|info-&gt;pf
op_eq
id|recip-&gt;pf
op_logical_and
(paren
op_logical_neg
id|recip-&gt;mark
op_logical_or
id|info-&gt;mark
op_eq
id|recip-&gt;mark
)paren
op_logical_and
(paren
op_logical_neg
id|recip-&gt;reason
op_logical_or
id|skb-&gt;nfreason
op_eq
id|recip-&gt;reason
)paren
)paren
(brace
multiline_comment|/* FIXME: Andi says: use netlink.  Hmmm... --RR */
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|recip-&gt;wake-&gt;skbq
)paren
op_ge
l_int|100
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: queue to long.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|free_discard
suffix:semicolon
)brace
multiline_comment|/* Hand it to userspace for collection */
id|skb_queue_tail
c_func
(paren
op_amp
id|recip-&gt;wake-&gt;skbq
comma
id|skb
)paren
suffix:semicolon
id|NFDEBUG
c_func
(paren
l_string|&quot;Waking up pf=%i hook=%u mark=%lu reason=%u&bslash;n&quot;
comma
id|pf
comma
id|hook
comma
id|skb-&gt;nfmark
comma
id|skb-&gt;nfreason
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|recip-&gt;wake-&gt;sleep
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: noone wants the packet.&bslash;n&quot;
)paren
suffix:semicolon
id|free_discard
suffix:colon
r_if
c_cond
(paren
id|indev
)paren
id|dev_put
c_func
(paren
id|indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outdev
)paren
id|dev_put
c_func
(paren
id|outdev
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|info
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* nf_hook() doesn&squot;t have lock, so may give false positive. */
DECL|function|nf_hook_slow
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
(brace
r_struct
id|list_head
op_star
id|elem
suffix:semicolon
r_int
r_int
id|verdict
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
r_if
c_cond
(paren
id|pf
OL
l_int|0
op_logical_or
id|pf
op_ge
id|NPROTO
op_logical_or
id|hook
op_ge
id|NF_MAX_HOOKS
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: bad vals: pf=%i, hook=%u.&bslash;n&quot;
comma
id|pf
comma
id|hook
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* -ECODERFUCKEDUP ?*/
)brace
r_if
c_cond
(paren
id|skb-&gt;nf_debug
op_amp
(paren
l_int|1
op_lshift
id|hook
)paren
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: hook %i already set.&bslash;n&quot;
comma
id|hook
)paren
suffix:semicolon
id|nf_dump_skb
c_func
(paren
id|pf
comma
id|skb
)paren
suffix:semicolon
)brace
id|skb-&gt;nf_debug
op_or_assign
(paren
l_int|1
op_lshift
id|hook
)paren
suffix:semicolon
macro_line|#endif
id|read_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
id|elem
op_assign
op_amp
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
suffix:semicolon
id|verdict
op_assign
id|nf_iterate
c_func
(paren
op_amp
id|nf_hooks
(braket
id|pf
)braket
(braket
id|hook
)braket
comma
op_amp
id|skb
comma
id|hook
comma
id|indev
comma
id|outdev
comma
op_amp
id|elem
comma
id|okfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_QUEUE
)paren
(brace
id|NFDEBUG
c_func
(paren
l_string|&quot;nf_hook: Verdict = QUEUE.&bslash;n&quot;
)paren
suffix:semicolon
id|nf_queue
c_func
(paren
id|skb
comma
id|elem
comma
id|pf
comma
id|hook
comma
id|indev
comma
id|outdev
comma
id|okfn
)paren
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|verdict
)paren
(brace
r_case
id|NF_ACCEPT
suffix:colon
id|ret
op_assign
id|okfn
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|nf_waitinfo
r_struct
id|nf_waitinfo
(brace
DECL|member|verdict
r_int
r_int
id|verdict
suffix:semicolon
DECL|member|owner
r_struct
id|task_struct
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For netfilter device. */
DECL|function|nf_register_interest
r_void
id|nf_register_interest
c_func
(paren
r_struct
id|nf_interest
op_star
id|interest
)paren
(brace
multiline_comment|/* First in, best dressed. */
id|write_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|interest-&gt;list
comma
op_amp
id|nf_interested
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
)brace
DECL|function|nf_unregister_interest
r_void
id|nf_unregister_interest
c_func
(paren
r_struct
id|nf_interest
op_star
id|interest
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|interest-&gt;list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
multiline_comment|/* Blow away any queued skbs; this is overzealous. */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|interest-&gt;wake-&gt;skbq
)paren
)paren
op_ne
l_int|NULL
)paren
id|nf_reinject
c_func
(paren
id|skb
comma
l_int|0
comma
id|NF_DROP
)paren
suffix:semicolon
)brace
DECL|function|nf_getinfo
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
(brace
r_const
r_struct
id|nf_info
op_star
id|info
op_assign
(paren
r_const
r_struct
id|nf_info
op_star
)paren
id|skb-&gt;nfmark
suffix:semicolon
op_star
id|indev
op_assign
id|info-&gt;indev
suffix:semicolon
op_star
id|outdev
op_assign
id|info-&gt;outdev
suffix:semicolon
op_star
id|mark
op_assign
id|info-&gt;mark
suffix:semicolon
)brace
DECL|function|nf_reinject
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
(brace
r_struct
id|nf_info
op_star
id|info
op_assign
(paren
r_struct
id|nf_info
op_star
)paren
id|skb-&gt;nfmark
suffix:semicolon
r_struct
id|list_head
op_star
id|elem
op_assign
op_amp
id|info-&gt;elem-&gt;list
suffix:semicolon
r_struct
id|list_head
op_star
id|i
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nf_hooks
(braket
id|info-&gt;pf
)braket
(braket
id|info-&gt;hook
)braket
dot
id|next
suffix:semicolon
id|i
op_ne
id|elem
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
op_amp
id|nf_hooks
(braket
id|info-&gt;pf
)braket
(braket
id|info-&gt;hook
)braket
)paren
(brace
multiline_comment|/* The module which sent it to userspace is gone. */
id|verdict
op_assign
id|NF_DROP
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Continue traversal iff userspace said ok, and devices still&n;           exist... */
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_ACCEPT
)paren
(brace
id|skb-&gt;nfmark
op_assign
id|mark
suffix:semicolon
id|verdict
op_assign
id|nf_iterate
c_func
(paren
op_amp
id|nf_hooks
(braket
id|info-&gt;pf
)braket
(braket
id|info-&gt;hook
)braket
comma
op_amp
id|skb
comma
id|info-&gt;hook
comma
id|info-&gt;indev
comma
id|info-&gt;outdev
comma
op_amp
id|elem
comma
id|info-&gt;okfn
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verdict
op_eq
id|NF_QUEUE
)paren
(brace
id|nf_queue
c_func
(paren
id|skb
comma
id|elem
comma
id|info-&gt;pf
comma
id|info-&gt;hook
comma
id|info-&gt;indev
comma
id|info-&gt;outdev
comma
id|info-&gt;okfn
)paren
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|nf_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|verdict
)paren
(brace
r_case
id|NF_ACCEPT
suffix:colon
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|info
op_member_access_from_pointer
id|okfn
c_func
(paren
id|skb
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Release those devices we held, or Alexey will kill me. */
r_if
c_cond
(paren
id|info-&gt;indev
)paren
id|dev_put
c_func
(paren
id|info-&gt;indev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;outdev
)paren
id|dev_put
c_func
(paren
id|info-&gt;outdev
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|info
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* FIXME: Before cache is ever used, this must be implemented for real. */
DECL|function|nf_invalidate_cache
r_void
id|nf_invalidate_cache
c_func
(paren
r_int
id|pf
)paren
(brace
)brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|function|debug_print_hooks_ip
r_void
id|debug_print_hooks_ip
c_func
(paren
r_int
r_int
id|nf_debug
)paren
(brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PRE_ROUTING &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LOCAL_IN &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FORWARD &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LOCAL_OUT &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
op_amp
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;POST_ROUTING &quot;
)paren
suffix:semicolon
id|nf_debug
op_xor_assign
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nf_debug
)paren
id|printk
c_func
(paren
l_string|&quot;Crap bits: 0x%04X&quot;
comma
id|nf_debug
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NETFILTER_DEBUG */
DECL|function|netfilter_init
r_void
id|__init
id|netfilter_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|h
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
id|NPROTO
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|NF_MAX_HOOKS
suffix:semicolon
id|h
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|nf_hooks
(braket
id|i
)braket
(braket
id|h
)braket
)paren
suffix:semicolon
)brace
eof
