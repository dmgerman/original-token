multiline_comment|/*&n; *&t;Spanning tree protocol; timer-related code&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_stp_timer.c,v 1.3 2000/05/05 02:17:17 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
macro_line|#include &quot;br_private_stp.h&quot;
DECL|function|dump_bridge_id
r_static
r_void
id|dump_bridge_id
c_func
(paren
id|bridge_id
op_star
id|id
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%.2x%.2x.%.2x:%.2x:%.2x:%.2x:%.2x:%.2x&quot;
comma
id|id-&gt;prio
(braket
l_int|0
)braket
comma
id|id-&gt;prio
(braket
l_int|1
)braket
comma
id|id-&gt;addr
(braket
l_int|0
)braket
comma
id|id-&gt;addr
(braket
l_int|1
)braket
comma
id|id-&gt;addr
(braket
l_int|2
)braket
comma
id|id-&gt;addr
(braket
l_int|3
)braket
comma
id|id-&gt;addr
(braket
l_int|4
)braket
comma
id|id-&gt;addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_is_designated_for_some_port
r_static
r_int
id|br_is_designated_for_some_port
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|p
op_assign
id|br-&gt;port_list
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|BR_STATE_DISABLED
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_bridge
comma
op_amp
id|br-&gt;bridge_id
comma
l_int|8
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_hello_timer_expired
r_static
r_void
id|br_hello_timer_expired
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br_config_bpdu_generation
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_timer_set
c_func
(paren
op_amp
id|br-&gt;hello_timer
comma
id|jiffies
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_message_age_timer_expired
r_static
r_void
id|br_message_age_timer_expired
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
id|was_root
suffix:semicolon
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: &quot;
comma
id|br-&gt;dev.name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;neighbour &quot;
)paren
suffix:semicolon
id|dump_bridge_id
c_func
(paren
op_amp
id|p-&gt;designated_bridge
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; lost on port %i(%s)&bslash;n&quot;
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * According to the spec, the message age timer cannot be&n;&t; * running when we are the root bridge. So..  this was_root&n;&t; * check is redundant. I&squot;m leaving it in for now, though.&n;&t; */
id|was_root
op_assign
id|br_is_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_become_designated_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|br_configuration_update
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_port_state_selection
c_func
(paren
id|br
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br_is_root_bridge
c_func
(paren
id|br
)paren
op_logical_and
op_logical_neg
id|was_root
)paren
id|br_become_root_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_forward_delay_timer_expired
r_static
r_void
id|br_forward_delay_timer_expired
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_LISTENING
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: port %i(%s) entering %s state&bslash;n&quot;
comma
id|p-&gt;br-&gt;dev.name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
comma
l_string|&quot;learning&quot;
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_LEARNING
suffix:semicolon
id|br_timer_set
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
comma
id|jiffies
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_LEARNING
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: port %i(%s) entering %s state&bslash;n&quot;
comma
id|p-&gt;br-&gt;dev.name
comma
id|p-&gt;port_no
comma
id|p-&gt;dev-&gt;name
comma
l_string|&quot;forwarding&quot;
)paren
suffix:semicolon
id|p-&gt;state
op_assign
id|BR_STATE_FORWARDING
suffix:semicolon
r_if
c_cond
(paren
id|br_is_designated_for_some_port
c_func
(paren
id|p-&gt;br
)paren
)paren
id|br_topology_change_detection
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_tcn_timer_expired
r_static
r_void
id|br_tcn_timer_expired
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: retransmitting tcn bpdu&bslash;n&quot;
comma
id|br-&gt;dev.name
)paren
suffix:semicolon
id|br_transmit_tcn
c_func
(paren
id|br
)paren
suffix:semicolon
id|br_timer_set
c_func
(paren
op_amp
id|br-&gt;tcn_timer
comma
id|jiffies
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_topology_change_timer_expired
r_static
r_void
id|br_topology_change_timer_expired
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
id|br-&gt;topology_change_detected
op_assign
l_int|0
suffix:semicolon
id|br-&gt;topology_change
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_hold_timer_expired
r_static
r_void
id|br_hold_timer_expired
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;config_pending
)paren
id|br_transmit_config
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_check_port_timers
r_static
r_void
id|br_check_port_timers
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|p-&gt;message_age_timer
comma
id|p-&gt;br-&gt;max_age
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;message_age_timer
)paren
suffix:semicolon
id|br_message_age_timer_expired
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
comma
id|p-&gt;br-&gt;forward_delay
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;forward_delay_timer
)paren
suffix:semicolon
id|br_forward_delay_timer_expired
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|p-&gt;hold_timer
comma
id|BR_HOLD_TIME
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|p-&gt;hold_timer
)paren
suffix:semicolon
id|br_hold_timer_expired
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_check_timers
r_static
r_void
id|br_check_timers
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|br-&gt;gc_timer
comma
id|br-&gt;gc_interval
)paren
)paren
(brace
id|br_timer_set
c_func
(paren
op_amp
id|br-&gt;gc_timer
comma
id|jiffies
)paren
suffix:semicolon
id|br_fdb_cleanup
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|br-&gt;hello_timer
comma
id|br-&gt;hello_time
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;hello_timer
)paren
suffix:semicolon
id|br_hello_timer_expired
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|br-&gt;tcn_timer
comma
id|br-&gt;bridge_hello_time
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;tcn_timer
)paren
suffix:semicolon
id|br_tcn_timer_expired
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|br_timer_has_expired
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
comma
id|br-&gt;bridge_forward_delay
op_plus
id|br-&gt;bridge_max_age
)paren
)paren
(brace
id|br_timer_clear
c_func
(paren
op_amp
id|br-&gt;topology_change_timer
)paren
suffix:semicolon
id|br_topology_change_timer_expired
c_func
(paren
id|br
)paren
suffix:semicolon
)brace
id|p
op_assign
id|br-&gt;port_list
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|BR_STATE_DISABLED
)paren
id|br_check_port_timers
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|br_tick
r_void
id|br_tick
c_func
(paren
r_int
r_int
id|__data
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
op_assign
(paren
r_struct
id|net_bridge
op_star
)paren
id|__data
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_check_timers
c_func
(paren
id|br
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br-&gt;tick.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|br-&gt;tick
)paren
suffix:semicolon
)brace
eof
