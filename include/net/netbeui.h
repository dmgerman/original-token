multiline_comment|/*&n; *&t;NetBEUI data structures&n; */
macro_line|#ifndef __NET_NETBEUI_H
DECL|macro|__NET_NETBEUI_H
mdefine_line|#define __NET_NETBEUI_H
DECL|macro|NB_NAME_LEN
mdefine_line|#define NB_NAME_LEN&t;16
multiline_comment|/*&n; *&t;Used to keep lists of netbeui sessions&n; */
DECL|struct|nb_ses
r_struct
id|nb_ses
(brace
DECL|member|next
r_struct
id|nb_ses
op_star
id|next
suffix:semicolon
DECL|member|name
r_struct
id|nb_nam
op_star
id|name
suffix:semicolon
DECL|member|parent
r_struct
id|nb_link
op_star
id|parent
suffix:semicolon
multiline_comment|/* Owner link */
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;A netbeui link&n; */
DECL|struct|nb_link
r_struct
id|nb_link
(brace
DECL|member|llc
r_struct
id|llc
id|llc
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|mac
id|u8
id|mac
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Mac address of remote */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device we heard him on */
DECL|member|sessions
r_struct
id|nb_ses
op_star
id|sessions
suffix:semicolon
multiline_comment|/* Netbeui sessions on this LLC link */
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
multiline_comment|/* Wait queue for this netbios LLC */
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/* Track the LLC busy state */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Link state */
DECL|macro|NETBEUI_OPEN
mdefine_line|#define NETBEUI_OPEN&t;&t;1&t;/* Up and going */
DECL|macro|NETBEUI_CONNWAIT
mdefine_line|#define NETBEUI_CONNWAIT&t;2&t;/* Waiting to come up */
DECL|macro|NETBEUI_DISCWAIT
mdefine_line|#define NETBEUI_DISCWAIT&t;3&t;/* Waiting to drop and recover */
DECL|macro|NETBEUI_DEADWAIT
mdefine_line|#define NETBEUI_DEADWAIT&t;4&t;/* Trying to die */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Netbios name defence list&n; */
DECL|struct|nb_name
r_struct
id|nb_name
(brace
DECL|member|next
r_struct
id|nb_name
op_star
id|next
suffix:semicolon
multiline_comment|/*&t;Chain &t;&t;*/
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/*&t;Device &t;&t;*/
DECL|member|name
r_char
id|name
(braket
id|NB_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* &t;Object Name&t;*/
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* &t;Name State&t;*/
DECL|macro|NB_NAME_ACQUIRE
mdefine_line|#define NB_NAME_ACQUIRE&t;&t;1&t;/* We are trying to get a name */
DECL|macro|NB_NAME_COLLIDE
mdefine_line|#define NB_NAME_COLLIDE&t;&t;2&t;/* Name collided - we failed */
DECL|macro|NB_OURS
mdefine_line|#define NB_OURS&t;&t;&t;3&t;/* We own the name&t;*/
DECL|macro|NB_NAME_OTHER
mdefine_line|#define NB_NAME_OTHER&t;&t;4&t;/* Name found - owned by other */
DECL|macro|NB_NAME_GET
mdefine_line|#define NB_NAME_GET&t;&t;5&t;/* Trying to allocate a name */
DECL|macro|NB_STATE
mdefine_line|#define NB_STATE&t;&t;7&t;/* State bits */
DECL|macro|NB_NAME_GROUP
mdefine_line|#define NB_NAME_GROUP&t;&t;8&t;/* Group name bit */
DECL|member|ours
r_int
id|ours
suffix:semicolon
multiline_comment|/* We own this name */
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* Number of nb_ses&squot;s to this name */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Our timer */
DECL|member|timer_mode
r_int
id|timer_mode
suffix:semicolon
multiline_comment|/* Timer mode */
DECL|macro|NB_TIMER_ACQUIRE
mdefine_line|#define NB_TIMER_ACQUIRE&t;1&t;/* Expiry means we got our name */
DECL|macro|NB_TIMER_COLLIDE
mdefine_line|#define NB_TIMER_COLLIDE&t;2&t;/* Expire a collided record */
DECL|macro|NB_TIMER_DROP
mdefine_line|#define NB_TIMER_DROP&t;&t;3&t;/* Drop a learned record */&t;
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;LLC link manager&n; */
r_extern
r_struct
id|nb_link
op_star
id|netbeui_find_link
c_func
(paren
id|u8
id|macaddr
)paren
suffix:semicolon
r_extern
r_struct
id|nb_link
op_star
id|netbeui_create_link
c_func
(paren
id|u8
id|macaddr
)paren
suffix:semicolon
r_extern
r_int
id|netbeui_destroy_link
c_func
(paren
id|u8
id|macaddr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Namespace manager&n; */
r_extern
r_struct
id|nb_name
op_star
id|netbeui_find_name
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|nb_name
op_star
id|netbeui_add_name
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|ours
)paren
suffix:semicolon
r_extern
r_struct
id|nb_name
op_star
id|netbeui_lookup_name
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|nb_delete_name
c_func
(paren
r_struct
id|nb_name
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;NetBEUI Protocol items&n; */
DECL|macro|ADD_GROUP_NAME_QUERY
mdefine_line|#define ADD_GROUP_NAME_QUERY&t;0x00
DECL|macro|ADD_NAME_QUERY
mdefine_line|#define ADD_NAME_QUERY&t;&t;0x01
DECL|macro|NAME_IN_CONFLICT
mdefine_line|#define NAME_IN_CONFLICT&t;0x02
DECL|macro|STATUS_QUERY
mdefine_line|#define STATUS_QUERY&t;&t;0x03
DECL|macro|TERMINATE_TRACE
mdefine_line|#define TERMINATE_TRACE&t;&t;0x07
DECL|macro|DATAGRAM
mdefine_line|#define DATAGRAM&t;&t;0x08
DECL|macro|DATAGRAM_BROADCAST
mdefine_line|#define DATAGRAM_BROADCAST&t;0x09
DECL|macro|NAME_QUERY
mdefine_line|#define NAME_QUERY&t;&t;0x0A
DECL|macro|ADD_NAME_RESPONSE
mdefine_line|#define ADD_NAME_RESPONSE&t;0x0D
DECL|macro|NAME_RECOGNIZED
mdefine_line|#define NAME_RECOGNIZED&t;&t;0x0E
DECL|macro|STATUS_RESPONSE
mdefine_line|#define STATUS_RESPONSE&t;&t;0x0F
DECL|macro|TERMINATE_TRACE2
mdefine_line|#define TERMINATE_TRACE2&t;0x13
DECL|macro|DATA_ACK
mdefine_line|#define DATA_ACK&t;&t;0x14
DECL|macro|DATA_FIRST_MIDDLE
mdefine_line|#define DATA_FIRST_MIDDLE&t;0x15
DECL|macro|DATA_ONLY_LAST
mdefine_line|#define DATA_ONLY_LAST&t;&t;0x16
DECL|macro|SESSION_CONFIRM
mdefine_line|#define SESSION_CONFIRM&t;&t;0x17
DECL|macro|SESSION_END
mdefine_line|#define SESSION_END&t;&t;0x18
DECL|macro|SESSION_INITIALIZE
mdefine_line|#define SESSION_INITIALIZE&t;0x19
DECL|macro|NO_RECEIVE
mdefine_line|#define NO_RECEIVE&t;&t;0x1A
DECL|macro|RECEIVE_OUTSTANDING
mdefine_line|#define RECEIVE_OUTSTANDING&t;0x1B
DECL|macro|RECEIVE_CONTINUE
mdefine_line|#define RECEIVE_CONTINUE&t;0x1C
DECL|macro|SESSION_ALIVE
mdefine_line|#define SESSION_ALIVE&t;&t;0x1F
DECL|macro|NB_TRANSMIT_COUNT
mdefine_line|#define NB_TRANSMIT_COUNT&t;6
DECL|macro|NB_TRANSMIT_TIMEOUT
mdefine_line|#define NB_TRANSMIT_TIMEOUT&t;(HZ/2)
DECL|macro|NB_DESCRIM_1
mdefine_line|#define NB_DESCRIM_1&t;&t;0xEF
DECL|macro|NB_DESCRIM_2
mdefine_line|#define NB_DESCRIM_2&t;&t;0xFF
DECL|struct|nb_dgram_pkt
r_struct
id|nb_dgram_pkt
(brace
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|descrim1
id|__u8
id|descrim1
suffix:semicolon
DECL|member|descrim2
id|__u8
id|descrim2
suffix:semicolon
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|option1
id|__u8
id|option1
suffix:semicolon
DECL|member|option2
id|__u16
id|option2
suffix:semicolon
DECL|member|tx_seq
id|__u16
id|tx_seq
suffix:semicolon
DECL|member|rx_seq
id|__u16
id|rx_seq
suffix:semicolon
DECL|member|dest
id|__u8
id|dest
(braket
id|NB_NAME_LEN
)braket
suffix:semicolon
DECL|member|src
id|__u8
id|src
(braket
id|NB_NAME_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nb_sess_pkt
r_struct
id|nb_sess_pkt
(brace
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|descrim1
id|__u8
id|descrim1
suffix:semicolon
DECL|member|descrim2
id|__u8
id|descrim2
suffix:semicolon
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|option1
id|__u8
id|option1
suffix:semicolon
DECL|member|option2
id|__u16
id|option2
suffix:semicolon
DECL|member|tx_seq
id|__u16
id|tx_seq
suffix:semicolon
DECL|member|rx_seq
id|__u16
id|rx_seq
suffix:semicolon
DECL|member|dnum
id|__u8
id|dnum
suffix:semicolon
DECL|member|snum
id|__u8
id|snum
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NO_SEQ
mdefine_line|#define NO_SEQ&t;0
macro_line|#endif
eof
