macro_line|#ifndef _UN_H
DECL|macro|_UN_H
mdefine_line|#define _UN_H
DECL|struct|sockaddr_un
r_struct
id|sockaddr_un
(brace
DECL|member|sun_family
id|u_short
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
macro_line|#endif /* _UN_H */
eof
