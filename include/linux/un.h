macro_line|#ifndef _LINUX_UN_H
DECL|macro|_LINUX_UN_H
mdefine_line|#define _LINUX_UN_H
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
l_int|108
)braket
suffix:semicolon
multiline_comment|/* pathname */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UN_H */
eof
