macro_line|#ifndef _IP_CONNTRACK_TUPLE_H
DECL|macro|_IP_CONNTRACK_TUPLE_H
mdefine_line|#define _IP_CONNTRACK_TUPLE_H
multiline_comment|/* A `tuple&squot; is a structure containing the information to uniquely&n;  identify a connection.  ie. if two packets have the same tuple, they&n;  are in the same connection; if not, they are not.&n;&n;  We divide the structure along &quot;manipulatable&quot; and&n;  &quot;non-manipulatable&quot; lines, for the benefit of the NAT code.&n;*/
multiline_comment|/* The protocol-specific manipulable parts of the tuple. */
DECL|union|ip_conntrack_manip_proto
r_union
id|ip_conntrack_manip_proto
(brace
multiline_comment|/* Add other protocols here. */
DECL|member|all
id|u_int16_t
id|all
suffix:semicolon
r_struct
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
DECL|member|tcp
)brace
id|tcp
suffix:semicolon
r_struct
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
DECL|member|udp
)brace
id|udp
suffix:semicolon
r_struct
(brace
DECL|member|id
id|u_int16_t
id|id
suffix:semicolon
DECL|member|icmp
)brace
id|icmp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The manipulable part of the tuple. */
DECL|struct|ip_conntrack_manip
r_struct
id|ip_conntrack_manip
(brace
DECL|member|ip
id|u_int32_t
id|ip
suffix:semicolon
DECL|member|u
r_union
id|ip_conntrack_manip_proto
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This contains the information to distinguish a connection. */
DECL|struct|ip_conntrack_tuple
r_struct
id|ip_conntrack_tuple
(brace
DECL|member|src
r_struct
id|ip_conntrack_manip
id|src
suffix:semicolon
multiline_comment|/* These are the parts of the tuple which are fixed. */
r_struct
(brace
DECL|member|ip
id|u_int32_t
id|ip
suffix:semicolon
r_union
(brace
multiline_comment|/* Add other protocols here. */
DECL|member|all
id|u_int16_t
id|all
suffix:semicolon
r_struct
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
DECL|member|tcp
)brace
id|tcp
suffix:semicolon
r_struct
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
DECL|member|udp
)brace
id|udp
suffix:semicolon
r_struct
(brace
DECL|member|type
DECL|member|code
id|u_int8_t
id|type
comma
id|code
suffix:semicolon
DECL|member|icmp
)brace
id|icmp
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* The protocol. */
DECL|member|protonum
id|u_int16_t
id|protonum
suffix:semicolon
DECL|member|dst
)brace
id|dst
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP_PARTS_NATIVE
mdefine_line|#define IP_PARTS_NATIVE(n)&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;24)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;16)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;8)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&amp;0xFF)
DECL|macro|IP_PARTS
mdefine_line|#define IP_PARTS(n) IP_PARTS_NATIVE(ntohl(n))
macro_line|#ifdef __KERNEL__
DECL|macro|DUMP_TUPLE
mdefine_line|#define DUMP_TUPLE(tp)&t;&t;&t;&t;&t;&t;&bslash;&n;DEBUGP(&quot;tuple %p: %u %u.%u.%u.%u:%u -&gt; %u.%u.%u.%u:%u&bslash;n&quot;,&t;&bslash;&n;       (tp), (tp)-&gt;dst.protonum,&t;&t;&t;&t;&bslash;&n;       IP_PARTS((tp)-&gt;src.ip), ntohs((tp)-&gt;src.u.all),&t;&t;&bslash;&n;       IP_PARTS((tp)-&gt;dst.ip), ntohs((tp)-&gt;dst.u.all))
DECL|macro|CTINFO2DIR
mdefine_line|#define CTINFO2DIR(ctinfo) ((ctinfo) &gt;= IP_CT_IS_REPLY ? IP_CT_DIR_REPLY : IP_CT_DIR_ORIGINAL)
multiline_comment|/* If we&squot;re the first tuple, it&squot;s the original dir. */
DECL|macro|DIRECTION
mdefine_line|#define DIRECTION(h) ((enum ip_conntrack_dir)(&amp;(h)-&gt;ctrack-&gt;tuplehash[1] == (h)))
DECL|enum|ip_conntrack_dir
r_enum
id|ip_conntrack_dir
(brace
DECL|enumerator|IP_CT_DIR_ORIGINAL
id|IP_CT_DIR_ORIGINAL
comma
DECL|enumerator|IP_CT_DIR_REPLY
id|IP_CT_DIR_REPLY
comma
DECL|enumerator|IP_CT_DIR_MAX
id|IP_CT_DIR_MAX
)brace
suffix:semicolon
DECL|function|ip_ct_tuple_src_equal
r_extern
r_inline
r_int
id|ip_ct_tuple_src_equal
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t1
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t2
)paren
(brace
r_return
id|t1-&gt;src.ip
op_eq
id|t2-&gt;src.ip
op_logical_and
id|t1-&gt;src.u.all
op_eq
id|t2-&gt;src.u.all
suffix:semicolon
)brace
DECL|function|ip_ct_tuple_dst_equal
r_extern
r_inline
r_int
id|ip_ct_tuple_dst_equal
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t1
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t2
)paren
(brace
r_return
id|t1-&gt;dst.ip
op_eq
id|t2-&gt;dst.ip
op_logical_and
id|t1-&gt;dst.u.all
op_eq
id|t2-&gt;dst.u.all
op_logical_and
id|t1-&gt;dst.protonum
op_eq
id|t2-&gt;dst.protonum
suffix:semicolon
)brace
DECL|function|ip_ct_tuple_equal
r_extern
r_inline
r_int
id|ip_ct_tuple_equal
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t1
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|t2
)paren
(brace
r_return
id|ip_ct_tuple_src_equal
c_func
(paren
id|t1
comma
id|t2
)paren
op_logical_and
id|ip_ct_tuple_dst_equal
c_func
(paren
id|t1
comma
id|t2
)paren
suffix:semicolon
)brace
multiline_comment|/* Connections have two entries in the hash table: one for each way */
DECL|struct|ip_conntrack_tuple_hash
r_struct
id|ip_conntrack_tuple_hash
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|tuple
r_struct
id|ip_conntrack_tuple
id|tuple
suffix:semicolon
multiline_comment|/* this == &amp;ctrack-&gt;tuplehash[DIRECTION(this)]. */
DECL|member|ctrack
r_struct
id|ip_conntrack
op_star
id|ctrack
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _IP_CONNTRACK_TUPLE_H */
eof
