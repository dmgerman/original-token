macro_line|#ifndef __NET_SPX_H
DECL|macro|__NET_SPX_H
mdefine_line|#define __NET_SPX_H
multiline_comment|/*&n; *&t;Internal definitions for the SPX protocol.&n; */
multiline_comment|/*&n; *&t;The SPX header following an IPX header.&n; */
DECL|struct|spxhdr
r_struct
id|spxhdr
(brace
DECL|member|cctl
id|__u8
id|cctl
suffix:semicolon
DECL|macro|CCTL_SPXII_XHD
mdefine_line|#define CCTL_SPXII_XHD&t;0x01&t;/* SPX2 extended header */
DECL|macro|CCTL_SPX_UNKNOWN
mdefine_line|#define CCTL_SPX_UNKNOWN 0x02&t;/* Unknown (unused ??) */
DECL|macro|CCTL_SPXII_NEG
mdefine_line|#define CCTL_SPXII_NEG&t;0x04&t;/* Negotiate size */
DECL|macro|CCTL_SPXII
mdefine_line|#define CCTL_SPXII&t;0x08&t;/* Set for SPX2 */
DECL|macro|CCTL_EOM
mdefine_line|#define CCTL_EOM&t;0x10&t;/* End of message marker */
DECL|macro|CCTL_URG
mdefine_line|#define CCTL_URG&t;0x20&t;/* Urgent marker in SPP (not used in SPX?) */
DECL|macro|CCTL_ACK
mdefine_line|#define CCTL_ACK&t;0x40&t;/* Send me an ACK */
DECL|macro|CCTL_CTL
mdefine_line|#define CCTL_CTL&t;0x80&t;/* Control message */
DECL|member|dtype
id|__u8
id|dtype
suffix:semicolon
DECL|macro|SPX_DTYPE_ECONN
mdefine_line|#define SPX_DTYPE_ECONN&t;0xFE&t;/* Finished */
DECL|macro|SPX_DTYPE_ECACK
mdefine_line|#define SPX_DTYPE_ECACK&t;0xFF&t;/* Ok */
DECL|member|sconn
id|__u16
id|sconn
suffix:semicolon
multiline_comment|/* Connection ID */
DECL|member|dconn
id|__u16
id|dconn
suffix:semicolon
multiline_comment|/* Connection ID */
DECL|member|sequence
id|__u16
id|sequence
suffix:semicolon
DECL|member|ackseq
id|__u16
id|ackseq
suffix:semicolon
DECL|member|allocseq
id|__u16
id|allocseq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPXTYPE_SPX
mdefine_line|#define IPXTYPE_SPX&t;5
macro_line|#endif
eof
