multiline_comment|/*&n; *&n; * Kernel support for NCP&n; *&n; * Mark Evans 1994&n; *&n; */
macro_line|#ifndef _NCP_H
DECL|macro|_NCP_H
mdefine_line|#define _NCP_H
macro_line|#include &lt;linux/ncp.h&gt;
DECL|struct|ncp_info
r_struct
id|ncp_info
(brace
DECL|member|conn
r_int
r_int
id|conn
suffix:semicolon
multiline_comment|/* connection number */
DECL|member|seq
r_int
r_char
id|seq
suffix:semicolon
multiline_comment|/* sequence number */
DECL|member|ncp
id|ipx_socket
op_star
id|ncp
suffix:semicolon
multiline_comment|/* ncp socket */
DECL|member|watchdog
id|ipx_socket
op_star
id|watchdog
suffix:semicolon
multiline_comment|/* watchdog socket */
DECL|member|mail
id|ipx_socket
op_star
id|mail
suffix:semicolon
multiline_comment|/* mail socket */
)brace
suffix:semicolon
DECL|macro|NCP_TIMEOUT
mdefine_line|#define NCP_TIMEOUT (3*HZ)
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT 15
macro_line|#endif&t;/* _NCP_H */
eof
