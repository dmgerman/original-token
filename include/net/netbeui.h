multiline_comment|/*&n; *&t;NetBEUI data structures&n; */
macro_line|#ifndef __NET_NETBEUI_H
DECL|macro|__NET_NETBEUI_H
mdefine_line|#define __NET_NETBEUI_H
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
DECL|member|llc
r_struct
id|llc
op_star
id|llc
suffix:semicolon
multiline_comment|/* 802.2 link layer */
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
mdefine_line|#define NB_TIMER_COLLIDE&t;2&t;/* Expire a collded record */
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
macro_line|#endif
eof
