macro_line|#ifndef _bootp_h
DECL|macro|_bootp_h
mdefine_line|#define _bootp_h
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t; Ethernet Definitions&t;&t;&t;&t;&t;&t; */
DECL|macro|PKTLEN
mdefine_line|#define&t;PKTLEN&t;&t;&t;1544
DECL|typedef|Packet
r_typedef
r_int
r_char
id|Packet
(braket
id|PKTLEN
)braket
suffix:semicolon
DECL|macro|ETHADDRLEN
mdefine_line|#define&t;ETHADDRLEN&t;&t;6
DECL|typedef|HWADDR
r_typedef
r_int
r_char
id|HWADDR
(braket
id|ETHADDRLEN
)braket
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|get_hwaddr
r_void
(paren
op_star
id|get_hwaddr
)paren
(paren
id|HWADDR
op_star
id|addr
)paren
suffix:semicolon
DECL|member|snd
r_int
(paren
op_star
id|snd
)paren
(paren
id|Packet
op_star
id|pkt
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|rcv
r_int
(paren
op_star
id|rcv
)paren
(paren
id|Packet
op_star
id|pkt
comma
r_int
op_star
id|len
)paren
suffix:semicolon
DECL|typedef|ETHIF_SWITCH
)brace
id|ETHIF_SWITCH
suffix:semicolon
multiline_comment|/* error codes */
DECL|macro|ETIMEO
mdefine_line|#define&t;ETIMEO&t;-1&t;&t;/* Timeout */
DECL|macro|ESEND
mdefine_line|#define&t;ESEND&t;-2&t;&t;/* General send error (carrier, abort, ...) */
DECL|macro|ERCV
mdefine_line|#define&t;ERCV&t;-3&t;&t;/* General receive error */
DECL|macro|EFRAM
mdefine_line|#define&t;EFRAM&t;-4&t;&t;/* Framing error */
DECL|macro|EOVERFL
mdefine_line|#define&t;EOVERFL&t;-5&t;&t;/* Overflow (too long packet) */
DECL|macro|ECRC
mdefine_line|#define&t;ECRC&t;-6&t;&t;/* CRC error */
DECL|typedef|IPADDR
r_typedef
r_int
r_int
id|IPADDR
suffix:semicolon
multiline_comment|/***************************** Prototypes *****************************/
r_int
id|get_remote_kernel
c_func
(paren
r_const
r_char
op_star
id|kname
)paren
suffix:semicolon
r_int
id|kread
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|cnt
)paren
suffix:semicolon
r_int
id|klseek
c_func
(paren
r_int
id|fd
comma
r_int
id|where
comma
r_int
id|whence
)paren
suffix:semicolon
r_int
id|kclose
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
multiline_comment|/************************* End of Prototypes **************************/
macro_line|#endif  /* _bootp_h */
eof