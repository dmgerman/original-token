multiline_comment|/*&n; * These are the public elements of the Linux kernel AX.25 code. A similar&n; * file netrom.h exists for the NET/ROM protocol.&n; */
macro_line|#ifndef&t;AX25_KERNEL_H
DECL|macro|AX25_KERNEL_H
mdefine_line|#define&t;AX25_KERNEL_H
DECL|macro|AX25_MTU
mdefine_line|#define AX25_MTU&t;256
DECL|macro|AX25_MAX_DIGIS
mdefine_line|#define AX25_MAX_DIGIS&t;6&t;/* This is wrong, should be 8 */
DECL|macro|AX25_WINDOW
mdefine_line|#define AX25_WINDOW&t;1
DECL|macro|AX25_T1
mdefine_line|#define AX25_T1&t;&t;2
DECL|macro|AX25_N2
mdefine_line|#define AX25_N2&t;&t;3
DECL|macro|AX25_T3
mdefine_line|#define AX25_T3&t;&t;4
DECL|macro|AX25_T2
mdefine_line|#define AX25_T2&t;&t;5
DECL|macro|AX25_BACKOFF
mdefine_line|#define&t;AX25_BACKOFF&t;6
DECL|macro|AX25_EXTSEQ
mdefine_line|#define&t;AX25_EXTSEQ&t;7
DECL|macro|AX25_HDRINCL
mdefine_line|#define&t;AX25_HDRINCL&t;8
DECL|macro|AX25_IDLE
mdefine_line|#define AX25_IDLE&t;9
DECL|macro|AX25_PACLEN
mdefine_line|#define AX25_PACLEN&t;10
DECL|macro|AX25_MAXQUEUE
mdefine_line|#define AX25_MAXQUEUE&t;11
DECL|macro|AX25_IAMDIGI
mdefine_line|#define AX25_IAMDIGI&t;12
DECL|macro|AX25_KILL
mdefine_line|#define AX25_KILL&t;99
DECL|macro|SIOCAX25GETUID
mdefine_line|#define SIOCAX25GETUID&t;&t;(SIOCPROTOPRIVATE+0)
DECL|macro|SIOCAX25ADDUID
mdefine_line|#define SIOCAX25ADDUID&t;&t;(SIOCPROTOPRIVATE+1)
DECL|macro|SIOCAX25DELUID
mdefine_line|#define SIOCAX25DELUID&t;&t;(SIOCPROTOPRIVATE+2)
DECL|macro|SIOCAX25NOUID
mdefine_line|#define SIOCAX25NOUID&t;&t;(SIOCPROTOPRIVATE+3)
DECL|macro|SIOCAX25OPTRT
mdefine_line|#define SIOCAX25OPTRT&t;&t;(SIOCPROTOPRIVATE+7)
DECL|macro|SIOCAX25CTLCON
mdefine_line|#define SIOCAX25CTLCON&t;&t;(SIOCPROTOPRIVATE+8)
DECL|macro|SIOCAX25GETINFO
mdefine_line|#define SIOCAX25GETINFO&t;&t;(SIOCPROTOPRIVATE+9)
DECL|macro|SIOCAX25ADDFWD
mdefine_line|#define SIOCAX25ADDFWD&t;&t;(SIOCPROTOPRIVATE+10)
DECL|macro|SIOCAX25DELFWD
mdefine_line|#define SIOCAX25DELFWD&t;&t;(SIOCPROTOPRIVATE+11)
DECL|macro|AX25_SET_RT_IPMODE
mdefine_line|#define AX25_SET_RT_IPMODE&t;2
DECL|macro|AX25_NOUID_DEFAULT
mdefine_line|#define AX25_NOUID_DEFAULT&t;0
DECL|macro|AX25_NOUID_BLOCK
mdefine_line|#define AX25_NOUID_BLOCK&t;1
r_typedef
r_struct
(brace
DECL|member|ax25_call
r_char
id|ax25_call
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 6 call + SSID (shifted ascii!) */
DECL|typedef|ax25_address
)brace
id|ax25_address
suffix:semicolon
DECL|struct|sockaddr_ax25
r_struct
id|sockaddr_ax25
(brace
DECL|member|sax25_family
id|sa_family_t
id|sax25_family
suffix:semicolon
DECL|member|sax25_call
id|ax25_address
id|sax25_call
suffix:semicolon
DECL|member|sax25_ndigis
r_int
id|sax25_ndigis
suffix:semicolon
multiline_comment|/* Digipeater ax25_address sets follow */
)brace
suffix:semicolon
DECL|macro|sax25_uid
mdefine_line|#define sax25_uid&t;sax25_ndigis
DECL|struct|full_sockaddr_ax25
r_struct
id|full_sockaddr_ax25
(brace
DECL|member|fsa_ax25
r_struct
id|sockaddr_ax25
id|fsa_ax25
suffix:semicolon
DECL|member|fsa_digipeater
id|ax25_address
id|fsa_digipeater
(braket
id|AX25_MAX_DIGIS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax25_routes_struct
r_struct
id|ax25_routes_struct
(brace
DECL|member|port_addr
id|ax25_address
id|port_addr
suffix:semicolon
DECL|member|dest_addr
id|ax25_address
id|dest_addr
suffix:semicolon
DECL|member|digi_count
r_int
r_char
id|digi_count
suffix:semicolon
DECL|member|digi_addr
id|ax25_address
id|digi_addr
(braket
id|AX25_MAX_DIGIS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax25_route_opt_struct
r_struct
id|ax25_route_opt_struct
(brace
DECL|member|port_addr
id|ax25_address
id|port_addr
suffix:semicolon
DECL|member|dest_addr
id|ax25_address
id|dest_addr
suffix:semicolon
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|arg
r_int
id|arg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax25_ctl_struct
r_struct
id|ax25_ctl_struct
(brace
DECL|member|port_addr
id|ax25_address
id|port_addr
suffix:semicolon
DECL|member|source_addr
id|ax25_address
id|source_addr
suffix:semicolon
DECL|member|dest_addr
id|ax25_address
id|dest_addr
suffix:semicolon
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|arg
r_int
r_int
id|arg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax25_info_struct
r_struct
id|ax25_info_struct
(brace
DECL|member|n2
DECL|member|n2count
r_int
r_int
id|n2
comma
id|n2count
suffix:semicolon
DECL|member|t1
DECL|member|t1timer
r_int
r_int
id|t1
comma
id|t1timer
suffix:semicolon
DECL|member|t2
DECL|member|t2timer
r_int
r_int
id|t2
comma
id|t2timer
suffix:semicolon
DECL|member|t3
DECL|member|t3timer
r_int
r_int
id|t3
comma
id|t3timer
suffix:semicolon
DECL|member|idle
DECL|member|idletimer
r_int
r_int
id|idle
comma
id|idletimer
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|rcv_q
DECL|member|snd_q
r_int
r_int
id|rcv_q
comma
id|snd_q
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax25_fwd_struct
r_struct
id|ax25_fwd_struct
(brace
DECL|member|port_from
id|ax25_address
id|port_from
suffix:semicolon
DECL|member|port_to
id|ax25_address
id|port_to
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
