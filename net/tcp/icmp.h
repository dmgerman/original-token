multiline_comment|/* Internet Control Message Protocol (ICMP) header file */
DECL|macro|ICMP_ECHOREPLY
mdefine_line|#define ICMP_ECHOREPLY&t;&t;0
DECL|macro|ICMP_DEST_UNREACH
mdefine_line|#define ICMP_DEST_UNREACH&t;3
DECL|macro|ICMP_SOURCE_QUENCH
mdefine_line|#define ICMP_SOURCE_QUENCH&t;4
DECL|macro|ICMP_REDIRECT
mdefine_line|#define ICMP_REDIRECT&t;&t;5
DECL|macro|ICMP_ECHO
mdefine_line|#define ICMP_ECHO&t;&t;8
DECL|macro|ICMP_TIME_EXCEEDED
mdefine_line|#define ICMP_TIME_EXCEEDED     11
DECL|macro|ICMP_PARAMETERPROB
mdefine_line|#define ICMP_PARAMETERPROB     12
DECL|macro|ICMP_TIMESTAMP
mdefine_line|#define ICMP_TIMESTAMP&t;       13
DECL|macro|ICMP_TIMESTAMPREPLY
mdefine_line|#define ICMP_TIMESTAMPREPLY    14
DECL|macro|ICMP_INFO_REQUEST
mdefine_line|#define ICMP_INFO_REQUEST      15
DECL|macro|ICMP_INFO_REPLY
mdefine_line|#define ICMP_INFO_REPLY&t;       16
multiline_comment|/* used by unreachable. */
DECL|macro|ICMP_NET_UNREACH
mdefine_line|#define ICMP_NET_UNREACH&t;0
DECL|macro|ICMP_HOST_UNREACH
mdefine_line|#define ICMP_HOST_UNREACH&t;1
DECL|macro|ICMP_PROT_UNREACH
mdefine_line|#define ICMP_PROT_UNREACH&t;2
DECL|macro|ICMP_PORT_UNREACH
mdefine_line|#define ICMP_PORT_UNREACH&t;3 /* lots of room for confusion. */
DECL|macro|ICMP_FRAG_NNEDED
mdefine_line|#define ICMP_FRAG_NNEDED&t;4
DECL|macro|ICMP_SR_FAILED
mdefine_line|#define ICMP_SR_FAILED&t;&t;5
DECL|macro|ICMP_NET_UNKNOWN
mdefine_line|#define ICMP_NET_UNKNOWN&t;6
DECL|macro|ICMP_HOST_UNKNOWN
mdefine_line|#define ICMP_HOST_UNKNOWN&t;7
DECL|macro|ICMP_HOST_ISOLATED
mdefine_line|#define ICMP_HOST_ISOLATED&t;8
DECL|macro|ICMP_NET_ANO
mdefine_line|#define ICMP_NET_ANO&t;&t;9
DECL|macro|ICMP_HOST_ANO
mdefine_line|#define ICMP_HOST_ANO&t;       10
DECL|macro|ICMP_NET_UNR_TOS
mdefine_line|#define ICMP_NET_UNR_TOS       11
DECL|macro|ICMP_HOST_UNR_TOS
mdefine_line|#define ICMP_HOST_UNR_TOS      12
DECL|struct|icmp_header
r_struct
id|icmp_header
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
suffix:semicolon
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|sequence
r_int
r_int
id|sequence
suffix:semicolon
DECL|member|echo
)brace
id|echo
suffix:semicolon
DECL|member|gateway
r_int
r_int
id|gateway
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|icmp_err
r_struct
id|icmp_err
(brace
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|member|fatal
r_int
id|fatal
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|icmp_err
id|icmp_err_convert
(braket
)braket
suffix:semicolon
r_int
id|icmp_rcv
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
r_struct
id|options
op_star
id|opt
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
id|redo
comma
r_struct
id|ip_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_void
id|icmp_reply
(paren
r_struct
id|sk_buff
op_star
id|skb_in
comma
r_int
id|type
comma
r_int
id|code
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
eof
