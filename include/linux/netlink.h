macro_line|#ifndef __LINUX_NETLINK_H
DECL|macro|__LINUX_NETLINK_H
mdefine_line|#define __LINUX_NETLINK_H
DECL|struct|nlmsghdr
r_struct
id|nlmsghdr
(brace
DECL|member|nlmsg_len
r_int
r_int
id|nlmsg_len
suffix:semicolon
multiline_comment|/* Length of message including header */
DECL|member|nlmsg_type
r_int
r_int
id|nlmsg_type
suffix:semicolon
multiline_comment|/* Message type */
DECL|member|nlmsg_seq
r_int
r_int
id|nlmsg_seq
suffix:semicolon
multiline_comment|/* Sequence number */
DECL|member|nlmsg_pid
r_int
r_int
id|nlmsg_pid
suffix:semicolon
multiline_comment|/* Sending process PID */
DECL|member|nlmsg_data
r_int
r_char
id|nlmsg_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NLMSG_ALIGN
mdefine_line|#define NLMSG_ALIGN(len) ( ((len)+sizeof(long)-1) &amp; ~(sizeof(long)-1) )
DECL|macro|NLMSG_ACK
mdefine_line|#define NLMSG_ACK&t;&t;0x01&t;/* int - error code */
DECL|macro|NLMSG_OVERRUN
mdefine_line|#define NLMSG_OVERRUN&t;&t;0x02&t;/* unsigned long[2] - start and end&n;&t;&t;&t;&t;&t; * of lost message sequence numbers.&n;&t;&t;&t;&t;&t; */
macro_line|#endif
eof
