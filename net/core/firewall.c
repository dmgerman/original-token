multiline_comment|/*&n; *&t;Generic loadable firewalls. At the moment only IP will actually&n; *&t;use these, but people can add the others as they are needed.&n; *&n; *&t;Authors:&t;Dave Bonn (for IP)&n; *&t;much hacked by:&t;Alan Cox&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
DECL|variable|firewall_lock
r_static
r_int
id|firewall_lock
op_assign
l_int|0
suffix:semicolon
DECL|variable|firewall_policy
r_static
r_int
id|firewall_policy
(braket
id|NPROTO
)braket
suffix:semicolon
DECL|variable|firewall_chain
r_static
r_struct
id|firewall_ops
op_star
id|firewall_chain
(braket
id|NPROTO
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Register a firewall&n; */
DECL|function|register_firewall
r_int
id|register_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
(brace
r_struct
id|firewall_ops
op_star
op_star
id|p
suffix:semicolon
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
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Don&squot;t allow two people to adjust at once.&n;&t; */
multiline_comment|/*&n;&t; *&t;FIXME: Swap for a kernel semaphore object&n;&t; */
r_while
c_loop
(paren
id|firewall_lock
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|firewall_lock
op_assign
l_int|1
suffix:semicolon
id|p
op_assign
op_amp
id|firewall_chain
(braket
id|pf
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|fw-&gt;fw_priority
OG
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|fw_priority
)paren
(brace
r_break
suffix:semicolon
)brace
id|p
op_assign
op_amp
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We need to use a memory barrier to make sure that this&n;&t; * works correctly even in SMP with weakly ordered writes.&n;&t; *&n;&t; * This is atomic wrt interrupts (and generally walking the&n;&t; * chain), but not wrt itself (so you can&squot;t call this from&n;&t; * an interrupt. Not that you&squot;d want to).&n;&t; */
id|fw-&gt;next
op_assign
op_star
id|p
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|fw
suffix:semicolon
multiline_comment|/*&n;&t; *&t;And release the sleep lock&n;&t; */
id|firewall_lock
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Unregister a firewall&n; */
DECL|function|unregister_firewall
r_int
id|unregister_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
(brace
r_struct
id|firewall_ops
op_star
op_star
id|nl
suffix:semicolon
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
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Don&squot;t allow two people to adjust at once.&n;&t; */
r_while
c_loop
(paren
id|firewall_lock
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|firewall_lock
op_assign
l_int|1
suffix:semicolon
id|nl
op_assign
op_amp
id|firewall_chain
(braket
id|pf
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|nl
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|nl
op_eq
id|fw
)paren
(brace
r_struct
id|firewall_ops
op_star
id|f
op_assign
id|fw-&gt;next
suffix:semicolon
op_star
id|nl
op_assign
id|f
suffix:semicolon
id|firewall_lock
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|nl
op_assign
op_amp
(paren
(paren
op_star
id|nl
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|firewall_lock
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|call_fw_firewall
r_int
id|call_fw_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|firewall_ops
op_star
id|fw
op_assign
id|firewall_chain
(braket
id|pf
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fw
op_ne
l_int|NULL
)paren
(brace
r_int
id|rc
op_assign
id|fw
op_member_access_from_pointer
id|fw_forward
c_func
(paren
id|fw
comma
id|pf
comma
id|dev
comma
id|phdr
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|FW_SKIP
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|fw
op_assign
id|fw-&gt;next
suffix:semicolon
)brace
r_return
id|firewall_policy
(braket
id|pf
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Actual invocation of the chains&n; */
DECL|function|call_in_firewall
r_int
id|call_in_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|firewall_ops
op_star
id|fw
op_assign
id|firewall_chain
(braket
id|pf
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fw
op_ne
l_int|NULL
)paren
(brace
r_int
id|rc
op_assign
id|fw
op_member_access_from_pointer
id|fw_input
c_func
(paren
id|fw
comma
id|pf
comma
id|dev
comma
id|phdr
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|FW_SKIP
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|fw
op_assign
id|fw-&gt;next
suffix:semicolon
)brace
r_return
id|firewall_policy
(braket
id|pf
)braket
suffix:semicolon
)brace
DECL|function|call_out_firewall
r_int
id|call_out_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|phdr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|firewall_ops
op_star
id|fw
op_assign
id|firewall_chain
(braket
id|pf
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fw
op_ne
l_int|NULL
)paren
(brace
r_int
id|rc
op_assign
id|fw
op_member_access_from_pointer
id|fw_output
c_func
(paren
id|fw
comma
id|pf
comma
id|dev
comma
id|phdr
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|FW_SKIP
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|fw
op_assign
id|fw-&gt;next
suffix:semicolon
)brace
multiline_comment|/* alan, is this right? */
r_return
id|firewall_policy
(braket
id|pf
)braket
suffix:semicolon
)brace
DECL|variable|register_firewall
id|EXPORT_SYMBOL
c_func
(paren
id|register_firewall
)paren
suffix:semicolon
DECL|variable|unregister_firewall
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_firewall
)paren
suffix:semicolon
DECL|variable|call_in_firewall
id|EXPORT_SYMBOL
c_func
(paren
id|call_in_firewall
)paren
suffix:semicolon
DECL|variable|call_out_firewall
id|EXPORT_SYMBOL
c_func
(paren
id|call_out_firewall
)paren
suffix:semicolon
DECL|variable|call_fw_firewall
id|EXPORT_SYMBOL
c_func
(paren
id|call_fw_firewall
)paren
suffix:semicolon
DECL|function|fwchain_init
r_void
id|fwchain_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
(brace
id|firewall_policy
(braket
id|i
)braket
op_assign
id|FW_ACCEPT
suffix:semicolon
)brace
)brace
eof
