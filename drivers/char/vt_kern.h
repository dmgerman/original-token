macro_line|#ifndef _VT_KERN_H
DECL|macro|_VT_KERN_H
mdefine_line|#define _VT_KERN_H
multiline_comment|/*&n; * this really is an extension of the vc_cons structure in console.c, but&n; * with information needed by the vt package&n; */
macro_line|#include &lt;linux/vt.h&gt;
DECL|struct|vt_struct
r_extern
r_struct
id|vt_struct
(brace
DECL|member|vc_mode
r_int
r_char
id|vc_mode
suffix:semicolon
multiline_comment|/* KD_TEXT, ... */
DECL|member|vc_kbdraw
r_int
r_char
id|vc_kbdraw
suffix:semicolon
DECL|member|vc_kbde0
r_int
r_char
id|vc_kbde0
suffix:semicolon
DECL|member|vc_kbdleds
r_int
r_char
id|vc_kbdleds
suffix:semicolon
DECL|member|vt_mode
r_struct
id|vt_mode
id|vt_mode
suffix:semicolon
DECL|member|vt_pid
r_int
id|vt_pid
suffix:semicolon
DECL|member|vt_newvt
r_int
id|vt_newvt
suffix:semicolon
)brace
id|vt_cons
(braket
id|NR_CONSOLES
)braket
suffix:semicolon
r_void
id|kd_mksound
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|ticks
)paren
suffix:semicolon
macro_line|#endif /* _VT_KERN_H */
eof
