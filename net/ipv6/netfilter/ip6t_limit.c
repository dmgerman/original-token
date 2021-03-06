multiline_comment|/* Kernel module to control the rate&n; *&n; * J&#xfffd;r&#xfffd;me de Vivie   &lt;devivie@info.enserb.u-bordeaux.fr&gt;&n; * Herv&#xfffd; Eychenne   &lt;eychenne@info.enserb.u-bordeaux.fr&gt;&n; *&n; * 2 September 1999: Changed from the target RATE to the match&n; *                   `limit&squot;, removed logging.  Did I mention that&n; *                   Alexey is a fucking genius?&n; *                   Rusty Russell (rusty@rustcorp.com.au).  */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_limit.h&gt;
multiline_comment|/* The algorithm used is the Simple Token Bucket Filter (TBF)&n; * see net/sched/sch_tbf.c in the linux source tree&n; */
DECL|variable|limit_lock
r_static
id|spinlock_t
id|limit_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Rusty: This is my (non-mathematically-inclined) understanding of&n;   this algorithm.  The `average rate&squot; in jiffies becomes your initial&n;   amount of credit `credit&squot; and the most credit you can ever have&n;   `credit_cap&squot;.  The `peak rate&squot; becomes the cost of passing the&n;   test, `cost&squot;.&n;&n;   `prev&squot; tracks the last packet hit: you gain one credit per jiffy.&n;   If you get credit balance more than this, the extra credit is&n;   discarded.  Every time the match passes, you lose `cost&squot; credits;&n;   if you don&squot;t have that many, the test fails.&n;&n;   See Alexey&squot;s formal explanation in net/sched/sch_tbf.c.&n;&n;   To avoid underflow, we multiply by 128 (ie. you get 128 credits per&n;   jiffy).  Hence a cost of 2^32-1, means one pass per 32768 seconds&n;   at 1024HZ (or one every 9 hours).  A cost of 1 means 12800 passes&n;   per second at 100HZ.  */
DECL|macro|CREDITS_PER_JIFFY
mdefine_line|#define CREDITS_PER_JIFFY 128
r_static
r_int
DECL|function|ipt_limit_match
id|ipt_limit_match
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
r_struct
id|ipt_rateinfo
op_star
id|r
op_assign
(paren
(paren
r_struct
id|ipt_rateinfo
op_star
)paren
id|matchinfo
)paren
op_member_access_from_pointer
id|master
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|limit_lock
)paren
suffix:semicolon
id|r-&gt;credit
op_add_assign
(paren
id|now
op_minus
id|xchg
c_func
(paren
op_amp
id|r-&gt;prev
comma
id|now
)paren
)paren
op_star
id|CREDITS_PER_JIFFY
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;credit
OG
id|r-&gt;credit_cap
)paren
id|r-&gt;credit
op_assign
id|r-&gt;credit_cap
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;credit
op_ge
id|r-&gt;cost
)paren
(brace
multiline_comment|/* We&squot;re not limited. */
id|r-&gt;credit
op_sub_assign
id|r-&gt;cost
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|limit_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|limit_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Precision saver. */
r_static
id|u_int32_t
DECL|function|user2credits
id|user2credits
c_func
(paren
id|u_int32_t
id|user
)paren
(brace
multiline_comment|/* If multiplying would overflow... */
r_if
c_cond
(paren
id|user
OG
l_int|0xFFFFFFFF
op_div
(paren
id|HZ
op_star
id|CREDITS_PER_JIFFY
)paren
)paren
multiline_comment|/* Divide first. */
r_return
(paren
id|user
op_div
id|IPT_LIMIT_SCALE
)paren
op_star
id|HZ
op_star
id|CREDITS_PER_JIFFY
suffix:semicolon
r_return
(paren
id|user
op_star
id|HZ
op_star
id|CREDITS_PER_JIFFY
)paren
op_div
id|IPT_LIMIT_SCALE
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipt_limit_checkentry
id|ipt_limit_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_ip6
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
r_struct
id|ipt_rateinfo
op_star
id|r
op_assign
id|matchinfo
suffix:semicolon
r_if
c_cond
(paren
id|matchsize
op_ne
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_rateinfo
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check for overflow. */
r_if
c_cond
(paren
id|r-&gt;burst
op_eq
l_int|0
op_logical_or
id|user2credits
c_func
(paren
id|r-&gt;avg
op_star
id|r-&gt;burst
)paren
OL
id|user2credits
c_func
(paren
id|r-&gt;avg
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Call rusty: overflow in ipt_limit: %u/%u&bslash;n&quot;
comma
id|r-&gt;avg
comma
id|r-&gt;burst
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* User avg in seconds * IPT_LIMIT_SCALE: convert to jiffies *&n;&t;   128. */
id|r-&gt;prev
op_assign
id|jiffies
suffix:semicolon
id|r-&gt;credit
op_assign
id|user2credits
c_func
(paren
id|r-&gt;avg
op_star
id|r-&gt;burst
)paren
suffix:semicolon
multiline_comment|/* Credits full. */
id|r-&gt;credit_cap
op_assign
id|user2credits
c_func
(paren
id|r-&gt;avg
op_star
id|r-&gt;burst
)paren
suffix:semicolon
multiline_comment|/* Credits full. */
id|r-&gt;cost
op_assign
id|user2credits
c_func
(paren
id|r-&gt;avg
)paren
suffix:semicolon
multiline_comment|/* For SMP, we only want to use one set of counters. */
id|r-&gt;master
op_assign
id|r
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipt_limit_reg
r_static
r_struct
id|ip6t_match
id|ipt_limit_reg
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;limit&quot;
comma
id|ipt_limit_match
comma
id|ipt_limit_checkentry
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
r_if
c_cond
(paren
id|ip6t_register_match
c_func
(paren
op_amp
id|ipt_limit_reg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
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
id|ip6t_unregister_match
c_func
(paren
op_amp
id|ipt_limit_reg
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
