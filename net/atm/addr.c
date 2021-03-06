multiline_comment|/* net/atm/addr.c - Local ATM address registry */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;signaling.h&quot;
macro_line|#include &quot;addr.h&quot;
DECL|function|check_addr
r_static
r_int
id|check_addr
c_func
(paren
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sas_family
op_ne
id|AF_ATMSVC
)paren
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|addr-&gt;sas_addr.pub
)paren
r_return
op_star
id|addr-&gt;sas_addr.prv
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ATM_E164_LEN
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* make sure it&squot;s &bslash;0-terminated */
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;sas_addr.pub
(braket
id|i
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|identical
r_static
r_int
id|identical
c_func
(paren
r_struct
id|sockaddr_atmsvc
op_star
id|a
comma
r_struct
id|sockaddr_atmsvc
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
op_star
id|a-&gt;sas_addr.prv
)paren
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|a-&gt;sas_addr.prv
comma
id|b-&gt;sas_addr.prv
comma
id|ATM_ESA_LEN
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|a-&gt;sas_addr.pub
)paren
r_return
op_logical_neg
op_star
id|b-&gt;sas_addr.pub
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|b-&gt;sas_addr.pub
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|a-&gt;sas_addr.pub
comma
id|b-&gt;sas_addr.pub
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Avoid modification of any list of local interfaces while reading it&n; * (which may involve page faults and therefore rescheduling)&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|local_lock
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|atm_dev_lock
suffix:semicolon
DECL|function|notify_sigd
r_static
r_void
id|notify_sigd
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_struct
id|sockaddr_atmpvc
id|pvc
suffix:semicolon
id|pvc.sap_addr.itf
op_assign
id|dev-&gt;number
suffix:semicolon
id|sigd_enq
c_func
(paren
l_int|NULL
comma
id|as_itf_notify
comma
l_int|NULL
comma
op_amp
id|pvc
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|reset_addr
r_void
id|reset_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_struct
id|atm_dev_addr
op_star
id|this
suffix:semicolon
id|down
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|atm_dev_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;local
)paren
(brace
id|this
op_assign
id|dev-&gt;local
suffix:semicolon
id|dev-&gt;local
op_assign
id|this-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|this
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|atm_dev_lock
)paren
suffix:semicolon
id|notify_sigd
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|add_addr
r_int
id|add_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
(brace
r_struct
id|atm_dev_addr
op_star
op_star
id|walk
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|check_addr
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|down
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
op_amp
id|dev-&gt;local
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_assign
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
id|identical
c_func
(paren
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|addr
comma
id|addr
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
op_star
id|walk
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|atm_dev_addr
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|walk
)paren
(brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|addr
op_assign
op_star
id|addr
suffix:semicolon
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
id|notify_sigd
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|del_addr
r_int
id|del_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
(brace
r_struct
id|atm_dev_addr
op_star
op_star
id|walk
comma
op_star
id|this
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|check_addr
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|down
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
op_amp
id|dev-&gt;local
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_assign
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
id|identical
c_func
(paren
op_amp
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|addr
comma
id|addr
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|walk
)paren
(brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|this
op_assign
op_star
id|walk
suffix:semicolon
op_star
id|walk
op_assign
id|this-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|this
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
id|notify_sigd
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_addr
r_int
id|get_addr
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|sockaddr_atmsvc
op_star
id|u_buf
comma
r_int
id|size
)paren
(brace
r_struct
id|atm_dev_addr
op_star
id|walk
suffix:semicolon
r_int
id|total
suffix:semicolon
id|down
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
id|total
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|dev-&gt;local
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
id|total
op_add_assign
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|total
OG
id|size
)paren
(brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
op_minus
id|E2BIG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|u_buf
comma
op_amp
id|walk-&gt;addr
comma
r_sizeof
(paren
r_struct
id|sockaddr_atmsvc
)paren
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|u_buf
op_increment
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|local_lock
)paren
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
eof
