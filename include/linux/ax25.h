DECL|macro|PF_AX25
mdefine_line|#define PF_AX25&t;&t;AF_AX25
DECL|macro|AX25_MTU
mdefine_line|#define AX25_MTU&t;256
DECL|macro|AX25_MAX_DIGIS
mdefine_line|#define AX25_MAX_DIGIS&t;6
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
DECL|struct|ax25_bpqaddr_struct
r_struct
id|ax25_bpqaddr_struct
(brace
DECL|member|dev
r_char
id|dev
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|addr
id|ax25_address
id|addr
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
DECL|macro|AX25_EXTSEQ
mdefine_line|#define&t;AX25_EXTSEQ&t;7
DECL|macro|AX25_HDRINCL
mdefine_line|#define&t;AX25_HDRINCL&t;8
DECL|macro|AX25_IDLE
mdefine_line|#define AX25_IDLE&t;9
DECL|macro|AX25_PACLEN
mdefine_line|#define AX25_PACLEN&t;10
DECL|macro|AX25_KILL
mdefine_line|#define AX25_KILL&t;99
DECL|macro|SIOCAX25GETUID
mdefine_line|#define SIOCAX25GETUID&t;&t;(SIOCPROTOPRIVATE)
DECL|macro|SIOCAX25ADDUID
mdefine_line|#define SIOCAX25ADDUID&t;&t;(SIOCPROTOPRIVATE+1)
DECL|macro|SIOCAX25DELUID
mdefine_line|#define SIOCAX25DELUID&t;&t;(SIOCPROTOPRIVATE+2)
DECL|macro|SIOCAX25NOUID
mdefine_line|#define SIOCAX25NOUID&t;&t;(SIOCPROTOPRIVATE+3)
DECL|macro|SIOCAX25BPQADDR
mdefine_line|#define&t;SIOCAX25BPQADDR&t;&t;(SIOCPROTOPRIVATE+4)
DECL|macro|SIOCAX25GETPARMS
mdefine_line|#define&t;SIOCAX25GETPARMS&t;(SIOCPROTOPRIVATE+5)
DECL|macro|SIOCAX25SETPARMS
mdefine_line|#define&t;SIOCAX25SETPARMS&t;(SIOCPROTOPRIVATE+6)
DECL|macro|SIOCAX25OPTRT
mdefine_line|#define SIOCAX25OPTRT&t;&t;(SIOCPROTOPRIVATE+7)
DECL|macro|SIOCAX25CTLCON
mdefine_line|#define SIOCAX25CTLCON&t;&t;(SIOCPROTOPRIVATE+8)
DECL|macro|AX25_SET_RT_PERMANENT
mdefine_line|#define AX25_SET_RT_PERMANENT&t;1
DECL|macro|AX25_SET_RT_IPMODE
mdefine_line|#define AX25_SET_RT_IPMODE&t;2
DECL|macro|AX25_RT_DYNAMIC
mdefine_line|#define AX25_RT_DYNAMIC&t;&t;0
DECL|macro|AX25_RT_PERMANENT
mdefine_line|#define AX25_RT_PERMANENT&t;1
DECL|macro|AX25_RT_IPMODE_DEFAULT
mdefine_line|#define AX25_RT_IPMODE_DEFAULT&t;&squot; &squot;
DECL|macro|AX25_RT_IPMODE_DATAGRAM
mdefine_line|#define AX25_RT_IPMODE_DATAGRAM&t;&squot;D&squot;
DECL|macro|AX25_RT_IPMODE_VC
mdefine_line|#define AX25_RT_IPMODE_VC&t;&squot;V&squot;
DECL|macro|AX25_NOUID_DEFAULT
mdefine_line|#define AX25_NOUID_DEFAULT&t;0
DECL|macro|AX25_NOUID_BLOCK
mdefine_line|#define AX25_NOUID_BLOCK&t;1
DECL|macro|AX25_DIGI_INBAND
mdefine_line|#define&t;AX25_DIGI_INBAND&t;0x01&t;/* Allow digipeating within port **/
DECL|macro|AX25_DIGI_XBAND
mdefine_line|#define&t;AX25_DIGI_XBAND&t;&t;0x02&t;/* Allow digipeating across ports **/
DECL|macro|AX25_VALUES_IPDEFMODE
mdefine_line|#define&t;AX25_VALUES_IPDEFMODE&t;0&t;/* &squot;D&squot;=DG &squot;V&squot;=VC */
DECL|macro|AX25_VALUES_AXDEFMODE
mdefine_line|#define&t;AX25_VALUES_AXDEFMODE&t;1&t;/* 8=Normal 128=Extended Seq Nos */
DECL|macro|AX25_VALUES_NETROM
mdefine_line|#define&t;AX25_VALUES_NETROM&t;2&t;/* Allow NET/ROM  - 0=No 1=Yes */
DECL|macro|AX25_VALUES_TEXT
mdefine_line|#define&t;AX25_VALUES_TEXT&t;3&t;/* Allow PID=Text - 0=No 1=Yes */
DECL|macro|AX25_VALUES_BACKOFF
mdefine_line|#define&t;AX25_VALUES_BACKOFF&t;4&t;/* &squot;E&squot;=Exponential &squot;L&squot;=Linear */
DECL|macro|AX25_VALUES_CONMODE
mdefine_line|#define&t;AX25_VALUES_CONMODE&t;5&t;/* Allow connected modes - 0=No 1=Yes */
DECL|macro|AX25_VALUES_WINDOW
mdefine_line|#define&t;AX25_VALUES_WINDOW&t;6&t;/* Default window size for standard AX.25 */
DECL|macro|AX25_VALUES_EWINDOW
mdefine_line|#define&t;AX25_VALUES_EWINDOW&t;7&t;/* Default window size for extended AX.25 */
DECL|macro|AX25_VALUES_T1
mdefine_line|#define&t;AX25_VALUES_T1&t;&t;8&t;/* Default T1 timeout value */
DECL|macro|AX25_VALUES_T2
mdefine_line|#define&t;AX25_VALUES_T2&t;&t;9&t;/* Default T2 timeout value */
DECL|macro|AX25_VALUES_T3
mdefine_line|#define&t;AX25_VALUES_T3&t;&t;10&t;/* Default T3 timeout value */
DECL|macro|AX25_VALUES_N2
mdefine_line|#define&t;AX25_VALUES_N2&t;&t;11&t;/* Default N2 value */
DECL|macro|AX25_VALUES_DIGI
mdefine_line|#define&t;AX25_VALUES_DIGI&t;12&t;/* Digipeat mode */
DECL|macro|AX25_VALUES_IDLE
mdefine_line|#define AX25_VALUES_IDLE&t;13&t;/* mode vc idle timer */
DECL|macro|AX25_VALUES_PACLEN
mdefine_line|#define AX25_VALUES_PACLEN&t;14&t;/* AX.25 MTU */
DECL|macro|AX25_MAX_VALUES
mdefine_line|#define&t;AX25_MAX_VALUES&t;&t;20
DECL|struct|ax25_parms_struct
r_struct
id|ax25_parms_struct
(brace
DECL|member|port_addr
id|ax25_address
id|port_addr
suffix:semicolon
DECL|member|values
r_int
r_int
id|values
(braket
id|AX25_MAX_VALUES
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
