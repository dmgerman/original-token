DECL|macro|PF_AX25
mdefine_line|#define PF_AX25&t;&t;AF_AX25
DECL|macro|AX25_MTU
mdefine_line|#define AX25_MTU&t;256
DECL|macro|AX25_MAX_DIGIS
mdefine_line|#define AX25_MAX_DIGIS&t;8
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
)brace
DECL|typedef|ax25_address
id|ax25_address
suffix:semicolon
DECL|struct|sockaddr_ax25
r_struct
id|sockaddr_ax25
(brace
DECL|member|sax25_family
r_int
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
DECL|macro|SIOCAX25GETUID
mdefine_line|#define SIOCAX25GETUID&t;&t;(SIOCPROTOPRIVATE)
DECL|macro|SIOCAX25ADDUID
mdefine_line|#define SIOCAX25ADDUID&t;&t;(SIOCPROTOPRIVATE+1)
DECL|macro|SIOCAX25DELUID
mdefine_line|#define SIOCAX25DELUID&t;&t;(SIOCPROTOPRIVATE+2)
DECL|macro|SIOCAX25NOUID
mdefine_line|#define SIOCAX25NOUID&t;&t;(SIOCPROTOPRIVATE+3)
DECL|macro|AX25_NOUID_DEFAULT
mdefine_line|#define AX25_NOUID_DEFAULT&t;0
DECL|macro|AX25_NOUID_BLOCK
mdefine_line|#define AX25_NOUID_BLOCK&t;1
eof
