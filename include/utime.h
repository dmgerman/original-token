macro_line|#ifndef _UTIME_H
DECL|macro|_UTIME_H
mdefine_line|#define _UTIME_H
macro_line|#include &lt;sys/types.h&gt;&t;/* I know - shouldn&squot;t do this, but .. */
DECL|struct|utimbuf
r_struct
id|utimbuf
(brace
DECL|member|actime
id|time_t
id|actime
suffix:semicolon
DECL|member|modtime
id|time_t
id|modtime
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_extern
r_int
id|utime
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|utimbuf
op_star
id|times
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif
eof
