macro_line|#ifndef _NET_PROFILE_H_
DECL|macro|_NET_PROFILE_H_
mdefine_line|#define _NET_PROFILE_H_ 1
macro_line|#ifdef CONFIG_NET_PROFILE
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|struct|net_profile_slot
r_struct
id|net_profile_slot
(brace
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|next
r_struct
id|net_profile_slot
op_star
id|next
suffix:semicolon
DECL|member|entered
r_struct
id|timeval
id|entered
suffix:semicolon
DECL|member|accumulator
r_struct
id|timeval
id|accumulator
suffix:semicolon
DECL|member|irq
r_struct
id|timeval
id|irq
suffix:semicolon
DECL|member|hits
r_int
id|hits
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|underflow
r_int
id|underflow
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|atomic_t
id|net_profile_active
suffix:semicolon
r_extern
r_struct
id|timeval
id|net_profile_adjust
suffix:semicolon
r_extern
r_void
id|net_profile_irq_adjust
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
suffix:semicolon
macro_line|#if CPU == 586 || CPU == 686
DECL|function|net_profile_stamp
r_extern
id|__inline__
r_void
id|net_profile_stamp
c_func
(paren
r_struct
id|timeval
op_star
id|pstamp
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.byte 0x0f,0x31&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|pstamp-&gt;tv_usec
)paren
comma
l_string|&quot;=d&quot;
(paren
id|pstamp-&gt;tv_sec
)paren
)paren
suffix:semicolon
)brace
DECL|function|net_profile_accumulate
r_extern
id|__inline__
r_void
id|net_profile_accumulate
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
comma
r_struct
id|timeval
op_star
id|acc
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;subl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;sbbl %3,%1&bslash;n&bslash;t&quot;
l_string|&quot;addl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;adcl %5,%1&bslash;n&bslash;t&quot;
l_string|&quot;subl &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|net_profile_adjust
)paren
l_string|&quot;+4,%0&bslash;n&bslash;t&quot;
l_string|&quot;sbbl $0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_sec
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|entered-&gt;tv_usec
)paren
comma
l_string|&quot;g&quot;
(paren
id|entered-&gt;tv_sec
)paren
comma
l_string|&quot;g&quot;
(paren
id|leaved-&gt;tv_usec
)paren
comma
l_string|&quot;g&quot;
(paren
id|leaved-&gt;tv_sec
)paren
comma
l_string|&quot;0&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;1&quot;
(paren
id|acc-&gt;tv_sec
)paren
)paren
suffix:semicolon
)brace
DECL|function|net_profile_sub
r_extern
id|__inline__
r_void
id|net_profile_sub
c_func
(paren
r_struct
id|timeval
op_star
id|sub
comma
r_struct
id|timeval
op_star
id|acc
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;subl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;sbbl %3,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_sec
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|sub-&gt;tv_usec
)paren
comma
l_string|&quot;g&quot;
(paren
id|sub-&gt;tv_sec
)paren
comma
l_string|&quot;0&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;1&quot;
(paren
id|acc-&gt;tv_sec
)paren
)paren
suffix:semicolon
)brace
DECL|function|net_profile_add
r_extern
id|__inline__
r_void
id|net_profile_add
c_func
(paren
r_struct
id|timeval
op_star
id|add
comma
r_struct
id|timeval
op_star
id|acc
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;addl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;adcl %3,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;=r&quot;
(paren
id|acc-&gt;tv_sec
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|add-&gt;tv_usec
)paren
comma
l_string|&quot;g&quot;
(paren
id|add-&gt;tv_sec
)paren
comma
l_string|&quot;0&quot;
(paren
id|acc-&gt;tv_usec
)paren
comma
l_string|&quot;1&quot;
(paren
id|acc-&gt;tv_sec
)paren
)paren
suffix:semicolon
)brace
macro_line|#elif defined (__alpha__)
r_extern
id|__u32
id|alpha_lo
suffix:semicolon
r_extern
r_int
id|alpha_hi
suffix:semicolon
multiline_comment|/* On alpha cycle counter has only 32 bits :-( :-( */
DECL|function|net_profile_stamp
r_extern
id|__inline__
r_void
id|net_profile_stamp
c_func
(paren
r_struct
id|timeval
op_star
id|pstamp
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;rpcc %0&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|result
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
id|alpha_lo
)paren
id|alpha_hi
op_increment
suffix:semicolon
id|alpha_lo
op_assign
id|result
suffix:semicolon
id|pstamp-&gt;tv_sec
op_assign
id|alpha_hi
suffix:semicolon
id|pstamp-&gt;tv_usec
op_assign
id|alpha_lo
suffix:semicolon
)brace
DECL|function|net_profile_accumulate
r_extern
id|__inline__
r_void
id|net_profile_accumulate
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
comma
r_struct
id|timeval
op_star
id|acc
)paren
(brace
id|time_t
id|usecs
op_assign
id|acc-&gt;tv_usec
op_plus
id|leaved-&gt;tv_usec
op_minus
id|entered-&gt;tv_usec
op_minus
id|net_profile_adjust.tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|acc-&gt;tv_sec
op_plus
id|leaved-&gt;tv_sec
op_minus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_ge
l_int|0x100000000L
)paren
(brace
id|usecs
op_sub_assign
l_int|0x100000000L
suffix:semicolon
id|secs
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|usecs
OL
op_minus
l_int|0x100000000L
)paren
(brace
id|usecs
op_add_assign
l_int|0x200000000L
suffix:semicolon
id|secs
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|usecs
OL
l_int|0
)paren
(brace
id|usecs
op_add_assign
l_int|0x100000000L
suffix:semicolon
id|secs
op_decrement
suffix:semicolon
)brace
id|acc-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|acc-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
DECL|function|net_profile_sub
r_extern
id|__inline__
r_void
id|net_profile_sub
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
(brace
id|time_t
id|usecs
op_assign
id|leaved-&gt;tv_usec
op_minus
id|entered-&gt;tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|leaved-&gt;tv_sec
op_minus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
OL
l_int|0
)paren
(brace
id|usecs
op_add_assign
l_int|0x100000000L
suffix:semicolon
id|secs
op_decrement
suffix:semicolon
)brace
id|leaved-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|leaved-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
DECL|function|net_profile_add
r_extern
id|__inline__
r_void
id|net_profile_add
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
(brace
id|time_t
id|usecs
op_assign
id|leaved-&gt;tv_usec
op_plus
id|entered-&gt;tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|leaved-&gt;tv_sec
op_plus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_ge
l_int|0x100000000L
)paren
(brace
id|usecs
op_sub_assign
l_int|0x100000000L
suffix:semicolon
id|secs
op_increment
suffix:semicolon
)brace
id|leaved-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|leaved-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
macro_line|#else
DECL|function|net_profile_stamp
r_extern
id|__inline__
r_void
id|net_profile_stamp
c_func
(paren
r_struct
id|timeval
op_star
id|pstamp
)paren
(brace
multiline_comment|/* Not &quot;fast&quot; counterpart! On architectures without&n;&t;   cpu clock &quot;fast&quot; routine is absolutely useless in this&n;&t;   situation. do_gettimeofday still says something on slow-slow-slow&n;&t;   boxes, though it eats more cpu time than the sobject of&n;&t;   investigation :-) :-)&n;&t; */
id|do_gettimeofday
c_func
(paren
id|pstamp
)paren
suffix:semicolon
)brace
DECL|function|net_profile_accumulate
r_extern
id|__inline__
r_void
id|net_profile_accumulate
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
comma
r_struct
id|timeval
op_star
id|acc
)paren
(brace
id|time_t
id|usecs
op_assign
id|acc-&gt;tv_usec
op_plus
id|leaved-&gt;tv_usec
op_minus
id|entered-&gt;tv_usec
op_minus
id|net_profile_adjust.tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|acc-&gt;tv_sec
op_plus
id|leaved-&gt;tv_sec
op_minus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_ge
l_int|1000000
)paren
(brace
id|usecs
op_sub_assign
l_int|1000000
suffix:semicolon
id|secs
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|usecs
OL
op_minus
l_int|1000000
)paren
(brace
id|usecs
op_add_assign
l_int|2000000
suffix:semicolon
id|secs
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|usecs
OL
l_int|0
)paren
(brace
id|usecs
op_add_assign
l_int|1000000
suffix:semicolon
id|secs
op_decrement
suffix:semicolon
)brace
id|acc-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|acc-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
DECL|function|net_profile_sub
r_extern
id|__inline__
r_void
id|net_profile_sub
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
(brace
id|time_t
id|usecs
op_assign
id|leaved-&gt;tv_usec
op_minus
id|entered-&gt;tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|leaved-&gt;tv_sec
op_minus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
OL
l_int|0
)paren
(brace
id|usecs
op_add_assign
l_int|1000000
suffix:semicolon
id|secs
op_decrement
suffix:semicolon
)brace
id|leaved-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|leaved-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
DECL|function|net_profile_add
r_extern
id|__inline__
r_void
id|net_profile_add
c_func
(paren
r_struct
id|timeval
op_star
id|entered
comma
r_struct
id|timeval
op_star
id|leaved
)paren
(brace
id|time_t
id|usecs
op_assign
id|leaved-&gt;tv_usec
op_plus
id|entered-&gt;tv_usec
suffix:semicolon
id|time_t
id|secs
op_assign
id|leaved-&gt;tv_sec
op_plus
id|entered-&gt;tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|usecs
op_ge
l_int|1000000
)paren
(brace
id|usecs
op_sub_assign
l_int|1000000
suffix:semicolon
id|secs
op_increment
suffix:semicolon
)brace
id|leaved-&gt;tv_sec
op_assign
id|secs
suffix:semicolon
id|leaved-&gt;tv_usec
op_assign
id|usecs
suffix:semicolon
)brace
macro_line|#endif
DECL|function|net_profile_enter
r_extern
id|__inline__
r_void
id|net_profile_enter
c_func
(paren
r_struct
id|net_profile_slot
op_star
id|s
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;active
op_increment
op_eq
l_int|0
)paren
(brace
id|net_profile_stamp
c_func
(paren
op_amp
id|s-&gt;entered
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|net_profile_active
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|net_profile_leave_irq
r_extern
id|__inline__
r_void
id|net_profile_leave_irq
c_func
(paren
r_struct
id|net_profile_slot
op_star
id|s
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|s-&gt;active
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;active
op_eq
l_int|0
)paren
(brace
r_struct
id|timeval
id|curr_pstamp
suffix:semicolon
id|net_profile_stamp
c_func
(paren
op_amp
id|curr_pstamp
)paren
suffix:semicolon
id|net_profile_accumulate
c_func
(paren
op_amp
id|s-&gt;entered
comma
op_amp
id|curr_pstamp
comma
op_amp
id|s-&gt;accumulator
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_and_test
c_func
(paren
op_amp
id|net_profile_active
)paren
)paren
id|net_profile_irq_adjust
c_func
(paren
op_amp
id|s-&gt;entered
comma
op_amp
id|curr_pstamp
)paren
suffix:semicolon
)brace
r_else
(brace
id|s-&gt;underflow
op_increment
suffix:semicolon
)brace
)brace
id|s-&gt;hits
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|net_profile_leave
r_extern
id|__inline__
r_void
id|net_profile_leave
c_func
(paren
r_struct
id|net_profile_slot
op_star
id|s
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|s-&gt;active
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;active
op_eq
l_int|0
)paren
(brace
r_struct
id|timeval
id|curr_pstamp
suffix:semicolon
id|net_profile_stamp
c_func
(paren
op_amp
id|curr_pstamp
)paren
suffix:semicolon
id|net_profile_accumulate
c_func
(paren
op_amp
id|s-&gt;entered
comma
op_amp
id|curr_pstamp
comma
op_amp
id|s-&gt;accumulator
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|net_profile_active
)paren
suffix:semicolon
)brace
r_else
(brace
id|s-&gt;underflow
op_increment
suffix:semicolon
)brace
)brace
id|s-&gt;hits
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|NET_PROFILE_ENTER
mdefine_line|#define NET_PROFILE_ENTER(slot) net_profile_enter(&amp;net_prof_##slot)
DECL|macro|NET_PROFILE_LEAVE
mdefine_line|#define NET_PROFILE_LEAVE(slot) net_profile_leave(&amp;net_prof_##slot)
DECL|macro|NET_PROFILE_LEAVE_IRQ
mdefine_line|#define NET_PROFILE_LEAVE_IRQ(slot) net_profile_leave_irq(&amp;net_prof_##slot)
DECL|macro|NET_PROFILE_SKB_CLEAR
mdefine_line|#define NET_PROFILE_SKB_CLEAR(skb) ({ &bslash;&n; skb-&gt;pstamp.tv_usec = 0; &bslash;&n;})
DECL|macro|NET_PROFILE_SKB_INIT
mdefine_line|#define NET_PROFILE_SKB_INIT(skb) ({ &bslash;&n; net_profile_stamp(&amp;skb-&gt;pstamp); &bslash;&n;})
DECL|macro|NET_PROFILE_SKB_PASSED
mdefine_line|#define NET_PROFILE_SKB_PASSED(skb, slot) ({ &bslash;&n; if (skb-&gt;pstamp.tv_usec) { &bslash;&n;   struct timeval cur_pstamp = skb-&gt;pstamp; &bslash;&n;   net_profile_stamp(&amp;skb-&gt;pstamp); &bslash;&n;   net_profile_accumulate(&amp;cur_pstamp, &amp;skb-&gt;pstamp, &amp;net_prof_##slot.accumulator); &bslash;&n;   net_prof_##slot.hits++; &bslash;&n; }})
DECL|macro|NET_PROFILE_DECL
mdefine_line|#define NET_PROFILE_DECL(slot) &bslash;&n;  extern struct net_profile_slot net_prof_##slot;
DECL|macro|NET_PROFILE_DEFINE
mdefine_line|#define NET_PROFILE_DEFINE(slot) &bslash;&n;  struct net_profile_slot net_prof_##slot = { #slot, };
DECL|macro|NET_PROFILE_REGISTER
mdefine_line|#define NET_PROFILE_REGISTER(slot) net_profile_register(&amp;net_prof_##slot)
DECL|macro|NET_PROFILE_UNREGISTER
mdefine_line|#define NET_PROFILE_UNREGISTER(slot) net_profile_unregister(&amp;net_prof_##slot)
r_extern
r_int
id|net_profile_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|net_profile_register
c_func
(paren
r_struct
id|net_profile_slot
op_star
)paren
suffix:semicolon
r_extern
r_int
id|net_profile_unregister
c_func
(paren
r_struct
id|net_profile_slot
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|NET_PROFILE_ENTER
mdefine_line|#define NET_PROFILE_ENTER(slot) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_LEAVE
mdefine_line|#define NET_PROFILE_LEAVE(slot) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_LEAVE_IRQ
mdefine_line|#define NET_PROFILE_LEAVE_IRQ(slot) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_SKB_CLEAR
mdefine_line|#define NET_PROFILE_SKB_CLEAR(skb) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_SKB_INIT
mdefine_line|#define NET_PROFILE_SKB_INIT(skb) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_SKB_PASSED
mdefine_line|#define NET_PROFILE_SKB_PASSED(skb, slot) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_DECL
mdefine_line|#define NET_PROFILE_DECL(slot)
DECL|macro|NET_PROFILE_DEFINE
mdefine_line|#define NET_PROFILE_DEFINE(slot)
DECL|macro|NET_PROFILE_REGISTER
mdefine_line|#define NET_PROFILE_REGISTER(slot) do { /* nothing */ } while(0)
DECL|macro|NET_PROFILE_UNREGISTER
mdefine_line|#define NET_PROFILE_UNREGISTER(slot) do { /* nothing */ } while(0)
macro_line|#endif
macro_line|#endif
eof