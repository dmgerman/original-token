multiline_comment|/*&n; *&t;&t;&t;Simple traffic shaper for Linux NET3.&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@cymru.net&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.cymru.net&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;&n; *&t;Algorithm:&n; *&n; *&t;Queue Frame:&n; *&t;&t;Compute time length of frame at regulated speed&n; *&t;&t;Add frame to queue at appropriate point&n; *&t;&t;Adjust time length computation for followup frames&n; *&t;&t;Any frame that falls outside of its boundaries is freed&n; *&n; *&t;We work to the following constants&n; *&n; *&t;&t;SHAPER_QLEN&t;Maximum queued frames&n; *&t;&t;SHAPER_LATENCY&t;Bounding latency on a frame. Leaving this latency&n; *&t;&t;&t;&t;window drops the frame. This stops us queueing &n; *&t;&t;&t;&t;frames for a long time and confusing a remote&n; *&t;&t;&t;&t;host.&n; *&t;&t;SHAPER_MAXSLIP&t;Maximum time a priority frame may jump forward.&n; *&t;&t;&t;&t;That bounds the penalty we will inflict on low&n; *&t;&t;&t;&t;priority traffic.&n; *&t;&t;SHAPER_BURST&t;Time range we call &quot;now&quot; in order to reduce&n; *&t;&t;&t;&t;system load. The more we make this the burstier&n; *&t;&t;&t;&t;the behaviour, the better local performance you&n; *&t;&t;&t;&t;get through packet clustering on routers and the&n; *&t;&t;&t;&t;worse the remote end gets to judge rtts.&n; *&n; *&t;This is designed to handle lower speed links ( &lt; 200K/second or so). We&n; *&t;run off a 100-150Hz base clock typically. This gives us a resolution at&n; *&t;200Kbit/second of about 2Kbit or 256 bytes. Above that our timer&n; *&t;resolution may start to cause much more burstiness in the traffic. We&n; *&t;could avoid a lot of that by calling kick_shaper() at the end of the &n; *&t;tied device transmissions. If you run above about 100K second you &n; *&t;may need to tune the supposed speed rate for the right values.&n; *&n; *&t;BUGS:&n; *&t;&t;Downing the interface under the shaper before the shaper&n; *&t;&t;will render your machine defunct. Don&squot;t for now shape over&n; *&t;&t;PPP or SLIP therefore!&n; *&t;&t;This will be fixed in BETA4&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;linux/if_shaper.h&gt;
DECL|variable|sh_debug
r_int
id|sh_debug
suffix:semicolon
multiline_comment|/* Debug flag */
DECL|macro|SHAPER_BANNER
mdefine_line|#define SHAPER_BANNER&t;&quot;CymruNet Traffic Shaper BETA 0.04 for Linux 2.1&bslash;n&quot;
multiline_comment|/*&n; *&t;Locking&n; */
DECL|function|shaper_lock
r_static
r_int
id|shaper_lock
c_func
(paren
r_struct
id|shaper
op_star
id|sh
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
multiline_comment|/*&n;&t; *&t;Lock in an interrupt may fail&n;&t; */
r_if
c_cond
(paren
id|sh-&gt;locked
op_logical_and
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sh-&gt;locked
)paren
(brace
id|sleep_on
c_func
(paren
op_amp
id|sh-&gt;wait_queue
)paren
suffix:semicolon
)brace
id|sh-&gt;locked
op_assign
l_int|1
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
id|shaper_kick
c_func
(paren
r_struct
id|shaper
op_star
id|sh
)paren
suffix:semicolon
DECL|function|shaper_unlock
r_static
r_void
id|shaper_unlock
c_func
(paren
r_struct
id|shaper
op_star
id|sh
)paren
(brace
id|sh-&gt;locked
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sh-&gt;wait_queue
)paren
suffix:semicolon
id|shaper_kick
c_func
(paren
id|sh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Compute clocks on a buffer&n; */
DECL|function|shaper_clocks
r_static
r_int
id|shaper_clocks
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|t
op_assign
id|skb-&gt;len
op_div
id|shaper-&gt;bytespertick
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set the speed of a shaper. We compute this in bytes per tick since&n; *&t;thats how the machine wants to run. Quoted input is in bits per second&n; *&t;as is traditional (note not BAUD). We assume 8 bit bytes. &n; */
DECL|function|shaper_setspeed
r_static
r_void
id|shaper_setspeed
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
comma
r_int
id|bitspersec
)paren
(brace
id|shaper-&gt;bytespertick
op_assign
(paren
id|bitspersec
op_div
id|HZ
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shaper-&gt;bytespertick
)paren
(brace
id|shaper-&gt;bytespertick
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Throw a frame at a shaper.&n; */
DECL|function|shaper_qframe
r_static
r_int
id|shaper_qframe
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|ptr
suffix:semicolon
multiline_comment|/*&n; &t; *&t;Get ready to work on this shaper. Lock may fail if its&n; &t; *&t;an interrupt and locked.&n; &t; */
r_if
c_cond
(paren
op_logical_neg
id|shaper_lock
c_func
(paren
id|shaper
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ptr
op_assign
id|shaper-&gt;sendq.prev
suffix:semicolon
multiline_comment|/*&n; &t; *&t;Set up our packet details&n; &t; */
id|skb-&gt;shapelatency
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;shapeclock
op_assign
id|shaper-&gt;recovery
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;shapeclock
OL
id|jiffies
)paren
(brace
id|skb-&gt;shapeclock
op_assign
id|jiffies
suffix:semicolon
)brace
id|skb-&gt;priority
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* short term bug fix */
id|skb-&gt;shapestamp
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n; &t; *&t;Time slots for this packet.&n; &t; */
id|skb-&gt;shapelen
op_assign
id|shaper_clocks
c_func
(paren
id|shaper
comma
id|skb
)paren
suffix:semicolon
macro_line|#ifdef SHAPER_COMPLEX /* and broken.. */
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr
op_ne
(paren
r_struct
id|sk_buff
op_star
)paren
op_amp
id|shaper-&gt;sendq
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;pri
OL
id|skb-&gt;pri
op_logical_and
id|jiffies
op_minus
id|ptr-&gt;shapeclock
OL
id|SHAPER_MAXSLIP
)paren
(brace
r_struct
id|sk_buff
op_star
id|tmp
op_assign
id|ptr-&gt;prev
suffix:semicolon
multiline_comment|/*&n; &t;&t;&t; *&t;It goes before us therefore we slip the length&n; &t;&t;&t; *&t;of the new frame.&n; &t;&t;&t; */
id|ptr-&gt;shapeclock
op_add_assign
id|skb-&gt;shapelen
suffix:semicolon
id|ptr-&gt;shapelatency
op_add_assign
id|skb-&gt;shapelen
suffix:semicolon
multiline_comment|/*&n; &t;&t;&t; *&t;The packet may have slipped so far back it&n; &t;&t;&t; *&t;fell off.&n; &t;&t;&t; */
r_if
c_cond
(paren
id|ptr-&gt;shapelatency
OG
id|SHAPER_LATENCY
)paren
(brace
id|skb_unlink
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|ptr
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
id|ptr
op_assign
id|tmp
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
op_logical_or
id|ptr
op_eq
(paren
r_struct
id|sk_buff
op_star
)paren
op_amp
id|shaper-&gt;sendq
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|shaper-&gt;sendq
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|sk_buff
op_star
id|tmp
suffix:semicolon
multiline_comment|/*&n; &t;&t; *&t;Set the packet clock out time according to the&n; &t;&t; *&t;frames ahead. Im sure a bit of thought could drop&n; &t;&t; *&t;this loop.&n; &t;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
id|skb_peek
c_func
(paren
op_amp
id|shaper-&gt;sendq
)paren
suffix:semicolon
id|tmp
op_ne
l_int|NULL
op_logical_and
id|tmp
op_ne
id|ptr
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|skb-&gt;shapeclock
op_add_assign
id|tmp-&gt;shapelen
suffix:semicolon
)brace
id|skb_append
c_func
(paren
id|ptr
comma
id|skb
)paren
suffix:semicolon
)brace
macro_line|#else
(brace
r_struct
id|sk_buff
op_star
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Up our shape clock by the time pending on the queue&n;&t;&t; *&t;(Should keep this in the shaper as a variable..)&n;&t;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
id|skb_peek
c_func
(paren
op_amp
id|shaper-&gt;sendq
)paren
suffix:semicolon
id|tmp
op_ne
l_int|NULL
op_logical_and
id|tmp
op_ne
(paren
r_struct
id|sk_buff
op_star
)paren
op_amp
id|shaper-&gt;sendq
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|skb-&gt;shapeclock
op_add_assign
id|tmp-&gt;shapelen
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Queue over time. Spill packet.&n;&t;&t; */
r_if
c_cond
(paren
id|skb-&gt;shapeclock
op_minus
id|jiffies
OG
id|SHAPER_LATENCY
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_else
id|skb_queue_tail
c_func
(paren
op_amp
id|shaper-&gt;sendq
comma
id|skb
)paren
suffix:semicolon
)brace
macro_line|#endif &t;
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Frame queued.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|shaper-&gt;sendq
)paren
OG
id|SHAPER_QLEN
)paren
(brace
id|ptr
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|shaper-&gt;sendq
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|ptr
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
id|shaper_unlock
c_func
(paren
id|shaper
)paren
suffix:semicolon
id|shaper_kick
c_func
(paren
id|shaper
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Transmit from a shaper&n; */
DECL|function|shaper_queue_xmit
r_static
r_void
id|shaper_queue_xmit
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|newskb
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Kick frame on %p&bslash;n&quot;
comma
id|newskb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newskb
)paren
(brace
id|newskb-&gt;dev
op_assign
id|shaper-&gt;dev
suffix:semicolon
id|newskb-&gt;priority
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Kick new frame to %s, %d&bslash;n&quot;
comma
id|shaper-&gt;dev-&gt;name
comma
id|newskb-&gt;priority
)paren
suffix:semicolon
)brace
id|dev_queue_xmit
c_func
(paren
id|newskb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Kicked new frame out.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Timer handler for shaping clock&n; */
DECL|function|shaper_timer
r_static
r_void
id|shaper_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
(paren
r_struct
id|shaper
op_star
)paren
id|data
suffix:semicolon
id|shaper_kick
c_func
(paren
id|sh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kick a shaper queue and try and do something sensible with the &n; *&t;queue. &n; */
DECL|function|shaper_kick
r_static
r_void
id|shaper_kick
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
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
id|del_timer
c_func
(paren
op_amp
id|shaper-&gt;timer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Shaper unlock will kick&n;&t; */
r_if
c_cond
(paren
id|shaper-&gt;locked
)paren
(brace
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Shaper locked.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|shaper-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|shaper-&gt;timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Walk the list (may be empty)&n;&t; */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|shaper-&gt;sendq
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Each packet due to go out by now (within an error&n;&t;&t; *&t;of SHAPER_BURST) gets kicked onto the link &n;&t;&t; */
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Clock = %d, jiffies = %ld&bslash;n&quot;
comma
id|skb-&gt;shapeclock
comma
id|jiffies
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;shapeclock
op_le
id|jiffies
op_plus
id|SHAPER_BURST
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Pull the frame and get interrupts back on.&n;&t;&t;&t; */
id|skb_unlink
c_func
(paren
id|skb
)paren
suffix:semicolon
id|shaper-&gt;recovery
op_assign
id|jiffies
op_plus
id|skb-&gt;shapelen
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Pass on to the physical target device via&n;&t;&t;&t; *&t;our low level packet thrower.&n;&t;&t;&t; */
id|skb-&gt;shapepend
op_assign
l_int|0
suffix:semicolon
id|shaper_queue_xmit
c_func
(paren
id|shaper
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Fire */
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Next kick.&n;&t; */
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|shaper-&gt;timer
)paren
suffix:semicolon
id|shaper-&gt;timer.expires
op_assign
id|skb-&gt;shapeclock
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|shaper-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Interrupts on, mission complete&n;&t; */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Flush the shaper queues on a closedown&n; */
DECL|function|shaper_flush
r_static
r_void
id|shaper_flush
c_func
(paren
r_struct
id|shaper
op_star
id|shaper
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
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
id|shaper-&gt;sendq
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Bring the interface up. We just disallow this until a &n; *&t;bind.&n; */
DECL|function|shaper_open
r_static
r_int
id|shaper_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|shaper
op_star
id|shaper
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Can&squot;t open until attached.&n;&t; */
r_if
c_cond
(paren
id|shaper-&gt;dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Closing a shaper flushes the queues.&n; */
DECL|function|shaper_close
r_static
r_int
id|shaper_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|shaper
op_star
id|shaper
op_assign
id|dev-&gt;priv
suffix:semicolon
id|shaper_flush
c_func
(paren
id|shaper
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|shaper-&gt;timer
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Revectored calls. We alter the parameters and call the functions&n; *&t;for our attached device. This enables us to bandwidth allocate after&n; *&t;ARP and other resolutions and not before.&n; */
DECL|function|shaper_start_xmit
r_static
r_int
id|shaper_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|dev-&gt;priv
suffix:semicolon
r_return
id|shaper_qframe
c_func
(paren
id|sh
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|shaper_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|shaper_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|shaper_header
r_static
r_int
id|shaper_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Shaper header&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|sh-&gt;dev
suffix:semicolon
id|v
op_assign
id|sh
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|sh-&gt;dev
comma
id|type
comma
id|daddr
comma
id|saddr
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|shaper_rebuild_header
r_static
r_int
id|shaper_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|skb-&gt;dev-&gt;priv
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Shaper rebuild header&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|sh-&gt;dev
suffix:semicolon
id|v
op_assign
id|sh
op_member_access_from_pointer
id|rebuild_header
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|shaper_cache
r_static
r_int
id|shaper_cache
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|hh_cache
op_star
id|hh
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|neigh-&gt;dev-&gt;priv
suffix:semicolon
r_struct
id|device
op_star
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Shaper header cache bind&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|neigh-&gt;dev
suffix:semicolon
id|neigh-&gt;dev
op_assign
id|sh-&gt;dev
suffix:semicolon
id|ret
op_assign
id|sh
op_member_access_from_pointer
id|hard_header_cache
c_func
(paren
id|neigh
comma
id|hh
)paren
suffix:semicolon
id|neigh-&gt;dev
op_assign
id|tmp
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|shaper_cache_update
r_static
r_void
id|shaper_cache_update
c_func
(paren
r_struct
id|hh_cache
op_star
id|hh
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_char
op_star
id|haddr
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|sh_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Shaper cache update&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|sh
op_member_access_from_pointer
id|header_cache_update
c_func
(paren
id|hh
comma
id|sh-&gt;dev
comma
id|haddr
)paren
suffix:semicolon
)brace
DECL|function|shaper_attach
r_static
r_int
id|shaper_attach
c_func
(paren
r_struct
id|device
op_star
id|shdev
comma
r_struct
id|shaper
op_star
id|sh
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
id|sh-&gt;dev
op_assign
id|dev
suffix:semicolon
id|sh-&gt;hard_start_xmit
op_assign
id|dev-&gt;hard_start_xmit
suffix:semicolon
id|sh-&gt;get_stats
op_assign
id|dev-&gt;get_stats
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hard_header
)paren
(brace
id|sh-&gt;hard_header
op_assign
id|dev-&gt;hard_header
suffix:semicolon
id|shdev-&gt;hard_header
op_assign
id|shaper_header
suffix:semicolon
)brace
r_else
id|shdev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;rebuild_header
)paren
(brace
id|sh-&gt;rebuild_header
op_assign
id|dev-&gt;rebuild_header
suffix:semicolon
id|shdev-&gt;rebuild_header
op_assign
id|shaper_rebuild_header
suffix:semicolon
)brace
r_else
id|shdev-&gt;rebuild_header
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|dev-&gt;hard_header_cache
)paren
(brace
id|sh-&gt;hard_header_cache
op_assign
id|dev-&gt;hard_header_cache
suffix:semicolon
id|shdev-&gt;hard_header_cache
op_assign
id|shaper_cache
suffix:semicolon
)brace
r_else
(brace
id|shdev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;header_cache_update
)paren
(brace
id|sh-&gt;header_cache_update
op_assign
id|dev-&gt;header_cache_update
suffix:semicolon
id|shdev-&gt;header_cache_update
op_assign
id|shaper_cache_update
suffix:semicolon
)brace
r_else
id|shdev-&gt;header_cache_update
op_assign
l_int|NULL
suffix:semicolon
macro_line|#else
id|shdev-&gt;header_cache_update
op_assign
l_int|NULL
suffix:semicolon
id|shdev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;&t;
id|shdev-&gt;hard_header_len
op_assign
id|dev-&gt;hard_header_len
suffix:semicolon
id|shdev-&gt;type
op_assign
id|dev-&gt;type
suffix:semicolon
id|shdev-&gt;addr_len
op_assign
id|dev-&gt;addr_len
suffix:semicolon
id|shdev-&gt;mtu
op_assign
id|dev-&gt;mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shaper_ioctl
r_static
r_int
id|shaper_ioctl
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
(brace
r_struct
id|shaperconf
op_star
id|ss
op_assign
(paren
r_struct
id|shaperconf
op_star
)paren
op_amp
id|ifr-&gt;ifr_data
suffix:semicolon
r_struct
id|shaper
op_star
id|sh
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|device
op_star
id|them
op_assign
id|dev_get
c_func
(paren
id|ss-&gt;ss_name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ss-&gt;ss_cmd
)paren
(brace
r_case
id|SHAPER_SET_DEV
suffix:colon
r_if
c_cond
(paren
id|them
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sh-&gt;dev
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
id|shaper_attach
c_func
(paren
id|dev
comma
id|dev-&gt;priv
comma
id|them
)paren
suffix:semicolon
r_case
id|SHAPER_SET_SPEED
suffix:colon
id|shaper_setspeed
c_func
(paren
id|sh
comma
id|ss-&gt;ss_speed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|shaper_alloc
r_static
r_struct
id|shaper
op_star
id|shaper_alloc
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|shaper
op_star
id|sh
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|shaper
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sh
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sh
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sh
)paren
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|sh-&gt;sendq
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|sh-&gt;timer
)paren
suffix:semicolon
id|sh-&gt;timer.function
op_assign
id|shaper_timer
suffix:semicolon
id|sh-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sh
suffix:semicolon
r_return
id|sh
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Add a shaper device to the system&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|shaper_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
)paren
(brace
multiline_comment|/*&n;&t; *&t;Set up the shaper.&n;&t; */
id|dev-&gt;priv
op_assign
id|shaper_alloc
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dev-&gt;open
op_assign
id|shaper_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|shaper_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|shaper_start_xmit
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|shaper_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Intialise the packet queues&n;&t; */
id|dev_init_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Handlers for when we attach to a device.&n;&t; */
id|dev-&gt;hard_header
op_assign
id|shaper_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|shaper_rebuild_header
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
id|shaper_cache
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
id|shaper_cache_update
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|shaper_ioctl
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_ETHER
suffix:semicolon
multiline_comment|/* initially */
id|dev-&gt;set_mac_address
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|10
suffix:semicolon
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Shaper is ok&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|devicename
r_static
r_char
id|devicename
(braket
l_int|9
)braket
suffix:semicolon
DECL|variable|dev_shape
r_static
r_struct
id|device
id|dev_shape
op_assign
(brace
id|devicename
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|shaper_probe
)brace
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|dev_alloc_name
c_func
(paren
op_amp
id|dev_shape
comma
l_string|&quot;shaper%d&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|SHAPER_BANNER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_shape
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Traffic shaper initialised.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;No need to check MOD_IN_USE, as sys_delete_module() checks.&n;&t; *&t;To be unloadable we must be closed and detached so we don&squot;t&n;&t; *&t;need to flush things.&n;&t; */
id|unregister_netdev
c_func
(paren
op_amp
id|dev_shape
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Free up the private structure, or leak memory :-) &n;&t; */
id|kfree
c_func
(paren
id|dev_shape.priv
)paren
suffix:semicolon
id|dev_shape.priv
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#else
DECL|variable|dev_sh0
r_static
r_struct
id|device
id|dev_sh0
op_assign
(brace
l_string|&quot;shaper0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|shaper_probe
)brace
suffix:semicolon
DECL|variable|dev_sh1
r_static
r_struct
id|device
id|dev_sh1
op_assign
(brace
l_string|&quot;shaper1&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|shaper_probe
)brace
suffix:semicolon
DECL|variable|dev_sh2
r_static
r_struct
id|device
id|dev_sh2
op_assign
(brace
l_string|&quot;shaper2&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|shaper_probe
)brace
suffix:semicolon
DECL|variable|dev_sh3
r_static
r_struct
id|device
id|dev_sh3
op_assign
(brace
l_string|&quot;shaper3&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|shaper_probe
)brace
suffix:semicolon
DECL|function|shaper_init
r_void
id|shaper_init
c_func
(paren
r_void
)paren
(brace
id|register_netdev
c_func
(paren
op_amp
id|dev_sh0
)paren
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|dev_sh1
)paren
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|dev_sh2
)paren
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|dev_sh3
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
