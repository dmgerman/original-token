multiline_comment|/*&n; * net/sched/cls_fw.c&t;Routing table based packet classifier.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
DECL|function|fw_classify
r_static
r_int
id|fw_classify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_result
op_star
id|res
)paren
(brace
id|u32
id|clid
op_assign
id|skb-&gt;fwmark
suffix:semicolon
r_if
c_cond
(paren
id|clid
op_logical_and
(paren
id|TC_H_MAJ
c_func
(paren
id|clid
)paren
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
id|TC_H_MAJ
c_func
(paren
id|clid
op_xor
id|tp-&gt;q-&gt;handle
)paren
)paren
)paren
)paren
(brace
id|res-&gt;classid
op_assign
id|clid
suffix:semicolon
id|res
op_member_access_from_pointer
r_class
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|fw_get
r_static
r_int
r_int
id|fw_get
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
id|u32
id|handle
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fw_put
r_static
r_void
id|fw_put
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|f
)paren
(brace
)brace
DECL|function|fw_init
r_static
r_int
id|fw_init
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fw_destroy
r_static
r_void
id|fw_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
)brace
DECL|function|fw_delete
r_static
r_int
id|fw_delete
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|arg
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|fw_change
r_static
r_int
id|fw_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
id|u32
id|handle
comma
r_struct
id|rtattr
op_star
op_star
id|tca
comma
r_int
r_int
op_star
id|arg
)paren
(brace
r_return
id|handle
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|cls_fw_ops
r_struct
id|tcf_proto_ops
id|cls_fw_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;fw&quot;
comma
id|fw_classify
comma
id|fw_init
comma
id|fw_destroy
comma
id|fw_get
comma
id|fw_put
comma
id|fw_change
comma
id|fw_delete
comma
l_int|NULL
comma
)brace
suffix:semicolon
eof
