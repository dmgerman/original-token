macro_line|#ifndef _NET_ALIAS_H
DECL|macro|_NET_ALIAS_H
mdefine_line|#define _NET_ALIAS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/in.h&gt;&t;&t;/* for default IP behavior */
multiline_comment|/*&n; * max. alias slot number allowed &n; */
DECL|macro|NET_ALIAS_MAX_SLOT
mdefine_line|#define NET_ALIAS_MAX_SLOT  256
r_struct
id|net_alias
suffix:semicolon
r_struct
id|net_alias_info
suffix:semicolon
r_struct
id|net_alias_type
suffix:semicolon
multiline_comment|/*&n; * main alias structure&n; * note that *defines* dev &amp; devname&n; */
DECL|struct|net_alias
r_struct
id|net_alias
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* alias device defn*/
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* device name defn */
DECL|member|hash
r_int
id|hash
suffix:semicolon
multiline_comment|/* my hash value: for quick rehash */
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* slot number */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data */
DECL|member|main_dev
r_struct
id|device
op_star
id|main_dev
suffix:semicolon
multiline_comment|/* pointer to main device */
DECL|member|nat
r_struct
id|net_alias_type
op_star
id|nat
suffix:semicolon
multiline_comment|/* alias type bound */
DECL|member|next
r_struct
id|net_alias
op_star
id|next
suffix:semicolon
multiline_comment|/* next alias (hashed linked list) */
)brace
suffix:semicolon
multiline_comment|/*&n; *  alias structure pointed by main device&n; *  it holds main device&squot;s alias hash table&n; */
DECL|struct|net_alias_info
r_struct
id|net_alias_info
(brace
DECL|member|n_aliases
r_int
id|n_aliases
suffix:semicolon
multiline_comment|/* num aliases */
DECL|member|taildev
r_struct
id|device
op_star
id|taildev
suffix:semicolon
multiline_comment|/* my last (alias) device */
DECL|member|hash_tab
r_struct
id|net_alias
op_star
id|hash_tab
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* hashed alias table */
)brace
suffix:semicolon
multiline_comment|/*&n; * net_alias_type class&n; * declares a generic (AF_ independent) structure that will&n; * manage generic to family-specific behavior.&n; */
DECL|struct|net_alias_type
r_struct
id|net_alias_type
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* aliasing type: address family */
DECL|member|n_attach
r_int
id|n_attach
suffix:semicolon
multiline_comment|/* number of aliases attached */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* af_name */
DECL|member|get_addr32
id|__u32
(paren
op_star
id|get_addr32
)paren
multiline_comment|/* get __u32 addr &squot;representation&squot;*/
(paren
r_struct
id|sockaddr
op_star
)paren
suffix:semicolon
DECL|member|addr_chk
r_int
(paren
op_star
id|addr_chk
)paren
multiline_comment|/* address checking func: */
(paren
r_struct
id|device
op_star
comma
r_struct
id|sockaddr
op_star
)paren
suffix:semicolon
DECL|member|alias_init_1
r_int
(paren
op_star
id|alias_init_1
)paren
multiline_comment|/* called after alias creation: */
(paren
r_struct
id|net_alias
op_star
id|alias
comma
r_struct
id|sockaddr
op_star
id|sa
)paren
suffix:semicolon
DECL|member|alias_done_1
r_int
(paren
op_star
id|alias_done_1
)paren
multiline_comment|/* called before alias deletion */
(paren
r_struct
id|net_alias
op_star
id|alias
)paren
suffix:semicolon
DECL|member|alias_print_1
r_int
(paren
op_star
id|alias_print_1
)paren
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|net_alias
op_star
id|alias
)paren
suffix:semicolon
DECL|member|next
r_struct
id|net_alias_type
op_star
id|next
suffix:semicolon
multiline_comment|/* link */
)brace
suffix:semicolon
multiline_comment|/*&n; * is dev an alias?&n; */
r_static
id|__inline__
r_int
DECL|function|net_alias_is
id|net_alias_is
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;my_alias
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * does dev have aliases?&n; */
r_static
id|__inline__
r_int
DECL|function|net_alias_has
id|net_alias_has
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;alias_info
op_ne
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_void
id|net_alias_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|net_alias_dev_get
c_func
(paren
r_char
op_star
id|dev_name
comma
r_int
id|aliasing_ok
comma
r_int
op_star
id|err
comma
r_struct
id|sockaddr
op_star
id|sa
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|net_alias_rehash
c_func
(paren
r_struct
id|net_alias
op_star
id|alias
comma
r_struct
id|sockaddr
op_star
id|sa
)paren
suffix:semicolon
r_extern
r_int
id|net_alias_getinfo
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|net_alias_types_getinfo
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|register_net_alias_type
c_func
(paren
r_struct
id|net_alias_type
op_star
id|nat
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|unregister_net_alias_type
c_func
(paren
r_struct
id|net_alias_type
op_star
id|nat
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|net_alias_chk
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sockaddr
op_star
id|sa
comma
r_int
id|flags_1
comma
r_int
id|flags_0
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|net_alias_chk32
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|family
comma
id|__u32
id|addr32
comma
r_int
id|flags_1
comma
r_int
id|flags_0
)paren
suffix:semicolon
multiline_comment|/*&n; * returns MY &squot;true&squot; main device&n; * intended for alias devices&n; */
DECL|function|net_alias_main_dev
r_static
id|__inline__
r_struct
id|device
op_star
id|net_alias_main_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
id|net_alias_is
c_func
(paren
id|dev
)paren
)paren
ques
c_cond
id|dev-&gt;my_alias-&gt;main_dev
suffix:colon
id|dev
suffix:semicolon
)brace
multiline_comment|/*&n; * returns NEXT &squot;true&squot; device&n; * intended for true devices&n; */
r_static
id|__inline__
r_struct
id|device
op_star
DECL|function|net_alias_nextdev
id|net_alias_nextdev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;alias_info
)paren
ques
c_cond
id|dev-&gt;alias_info-&gt;taildev-&gt;next
suffix:colon
id|dev-&gt;next
suffix:semicolon
)brace
multiline_comment|/*&n; * sets NEXT &squot;true&squot; device&n; * intended for main devices (treat main device as block: dev+aliases).&n; */
r_static
id|__inline__
r_struct
id|device
op_star
DECL|function|net_alias_nextdev_set
id|net_alias_nextdev_set
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device
op_star
id|nextdev
)paren
(brace
r_struct
id|device
op_star
id|pdev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|net_alias_has
c_func
(paren
id|dev
)paren
)paren
(brace
id|pdev
op_assign
id|dev-&gt;alias_info-&gt;taildev
suffix:semicolon
multiline_comment|/* point to last dev alias */
)brace
id|pdev-&gt;next
op_assign
id|nextdev
suffix:semicolon
r_return
id|nextdev
suffix:semicolon
)brace
multiline_comment|/*&n; * addr_chk wrapper: check given generic address with (UP) aliases&n; */
r_static
id|__inline__
r_struct
id|device
op_star
DECL|function|net_alias_addr_chk
id|net_alias_addr_chk
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sockaddr
op_star
id|sa
)paren
(brace
r_return
id|net_alias_chk
c_func
(paren
id|dev
comma
id|sa
comma
id|IFF_UP
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * addr_chk32 wrapper: check given u32 address with (UP) aliases&n; */
r_static
id|__inline__
r_struct
id|device
op_star
DECL|function|net_alias_addr_chk32
id|net_alias_addr_chk32
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|family
comma
id|__u32
id|addr32
)paren
(brace
r_return
id|net_alias_chk32
c_func
(paren
id|dev
comma
id|family
comma
id|addr32
comma
id|IFF_UP
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif  /* _NET_ALIAS_H */
eof