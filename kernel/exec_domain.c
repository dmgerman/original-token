macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
r_static
id|asmlinkage
r_void
id|no_lcall7
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|ident_map
r_static
r_int
r_int
id|ident_map
(braket
l_int|32
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|variable|default_exec_domain
r_struct
id|exec_domain
id|default_exec_domain
op_assign
(brace
l_string|&quot;Linux&quot;
comma
multiline_comment|/* name */
id|no_lcall7
comma
multiline_comment|/* lcall7 causes a seg fault. */
l_int|0
comma
l_int|0xff
comma
multiline_comment|/* All personalities. */
id|ident_map
comma
multiline_comment|/* Identiy map signals. */
id|ident_map
comma
multiline_comment|/*  - both ways. */
l_int|NULL
comma
multiline_comment|/* No usage counter. */
l_int|NULL
multiline_comment|/* Nothing after this in the list. */
)brace
suffix:semicolon
DECL|variable|exec_domains
r_static
r_struct
id|exec_domain
op_star
id|exec_domains
op_assign
op_amp
id|default_exec_domain
suffix:semicolon
DECL|function|no_lcall7
r_static
id|asmlinkage
r_void
id|no_lcall7
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|lookup_exec_domain
r_struct
id|exec_domain
op_star
id|lookup_exec_domain
c_func
(paren
r_int
r_int
id|personality
)paren
(brace
r_int
r_int
id|pers
op_assign
id|personality
op_amp
id|PER_MASK
suffix:semicolon
r_struct
id|exec_domain
op_star
id|it
suffix:semicolon
r_for
c_loop
(paren
id|it
op_assign
id|exec_domains
suffix:semicolon
id|it
suffix:semicolon
id|it
op_assign
id|it-&gt;next
)paren
r_if
c_cond
(paren
id|pers
op_ge
id|it-&gt;pers_low
op_logical_and
id|pers
op_le
id|it-&gt;pers_high
)paren
r_return
id|it
suffix:semicolon
multiline_comment|/* Should never get this far. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No execution domain for personality 0x%02lx&bslash;n&quot;
comma
id|pers
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|register_exec_domain
r_int
id|register_exec_domain
c_func
(paren
r_struct
id|exec_domain
op_star
id|it
)paren
(brace
r_struct
id|exec_domain
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|it-&gt;next
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|exec_domains
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
r_if
c_cond
(paren
id|tmp
op_eq
id|it
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|it-&gt;next
op_assign
id|exec_domains
suffix:semicolon
id|exec_domains
op_assign
id|it
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_exec_domain
r_int
id|unregister_exec_domain
c_func
(paren
r_struct
id|exec_domain
op_star
id|it
)paren
(brace
r_struct
id|exec_domain
op_star
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
op_amp
id|exec_domains
suffix:semicolon
r_while
c_loop
(paren
op_star
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|it
op_eq
op_star
id|tmp
)paren
(brace
op_star
id|tmp
op_assign
id|it-&gt;next
suffix:semicolon
id|it-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
op_amp
(paren
op_star
id|tmp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|sys_personality
id|asmlinkage
r_int
id|sys_personality
c_func
(paren
r_int
r_int
id|personality
)paren
(brace
r_struct
id|exec_domain
op_star
id|it
suffix:semicolon
r_int
r_int
id|old_personality
suffix:semicolon
r_if
c_cond
(paren
id|personality
op_eq
l_int|0xffffffff
)paren
r_return
id|current-&gt;personality
suffix:semicolon
id|it
op_assign
id|lookup_exec_domain
c_func
(paren
id|personality
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|old_personality
op_assign
id|current-&gt;personality
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;use_count
)paren
(paren
op_star
id|current-&gt;exec_domain-&gt;use_count
)paren
op_decrement
suffix:semicolon
id|current-&gt;personality
op_assign
id|personality
suffix:semicolon
id|current-&gt;exec_domain
op_assign
id|it
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain-&gt;use_count
)paren
(paren
op_star
id|current-&gt;exec_domain-&gt;use_count
)paren
op_increment
suffix:semicolon
r_return
id|old_personality
suffix:semicolon
)brace
eof