macro_line|#ifndef _VT_KERN_H
DECL|macro|_VT_KERN_H
mdefine_line|#define _VT_KERN_H
multiline_comment|/*&n; * this really is an extension of the vc_cons structure in console.c, but&n; * with information needed by the vt package&n; */
DECL|struct|vt_cons
r_extern
r_struct
id|vt_cons
(brace
DECL|member|vt_mode
r_int
id|vt_mode
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
)brace
id|vt_cons
(braket
id|MAX_CONSOLES
)braket
suffix:semicolon
macro_line|#endif /* _VT_KERN_H */
eof
