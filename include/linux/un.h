macro_line|#ifndef _LINUX_UN_H
DECL|macro|_LINUX_UN_H
mdefine_line|#define _LINUX_UN_H
DECL|macro|UNIX_PATH_MAX
mdefine_line|#define UNIX_PATH_MAX&t;108
DECL|struct|sockaddr_un
r_struct
id|sockaddr_un
(brace
DECL|member|sun_family
r_int
r_int
id|sun_family
suffix:semicolon
multiline_comment|/* AF_UNIX */
DECL|member|sun_path
r_char
id|sun_path
(braket
id|UNIX_PATH_MAX
)braket
suffix:semicolon
multiline_comment|/* pathname */
)brace
suffix:semicolon
DECL|struct|cmsghdr
r_struct
id|cmsghdr
(brace
DECL|member|cmsg_len
r_int
r_int
id|cmsg_len
suffix:semicolon
DECL|member|cmsg_level
r_int
id|cmsg_level
suffix:semicolon
DECL|member|cmsg_type
r_int
id|cmsg_type
suffix:semicolon
DECL|member|cmsg_data
r_int
r_char
id|cmsg_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UN_H */
eof
