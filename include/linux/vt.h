macro_line|#ifndef _LINUX_VT_H
DECL|macro|_LINUX_VT_H
mdefine_line|#define _LINUX_VT_H
multiline_comment|/* 0x56 is &squot;V&squot;, to avoid collision with termios and kd */
DECL|macro|VT_OPENQRY
mdefine_line|#define VT_OPENQRY&t;0x5600&t;/* find available vt */
DECL|struct|vt_mode
r_struct
id|vt_mode
(brace
DECL|member|mode
r_char
id|mode
suffix:semicolon
multiline_comment|/* vt mode */
DECL|member|waitv
r_char
id|waitv
suffix:semicolon
multiline_comment|/* if set, hang on writes if not active */
DECL|member|relsig
r_int
id|relsig
suffix:semicolon
multiline_comment|/* signal to raise on release req */
DECL|member|acqsig
r_int
id|acqsig
suffix:semicolon
multiline_comment|/* signal to raise on acquisition */
DECL|member|frsig
r_int
id|frsig
suffix:semicolon
multiline_comment|/* unused (set to 0) */
)brace
suffix:semicolon
DECL|macro|VT_GETMODE
mdefine_line|#define VT_GETMODE&t;0x5601&t;/* get mode of active vt */
DECL|macro|VT_SETMODE
mdefine_line|#define VT_SETMODE&t;0x5602&t;/* set mode of active vt */
DECL|macro|VT_AUTO
mdefine_line|#define&t;&t;VT_AUTO&t;&t;0x00&t;/* auto vt switching */
DECL|macro|VT_PROCESS
mdefine_line|#define&t;&t;VT_PROCESS&t;0x01&t;/* process controls switching */
DECL|struct|vt_stat
r_struct
id|vt_stat
(brace
DECL|member|v_active
id|ushort
id|v_active
suffix:semicolon
multiline_comment|/* active vt */
DECL|member|v_signal
id|ushort
id|v_signal
suffix:semicolon
multiline_comment|/* signal to send */
DECL|member|v_state
id|ushort
id|v_state
suffix:semicolon
multiline_comment|/* vt bitmask */
)brace
suffix:semicolon
DECL|macro|VT_GETSTATE
mdefine_line|#define VT_GETSTATE&t;0x5603&t;/* get global vt state info */
DECL|macro|VT_SENDSIG
mdefine_line|#define VT_SENDSIG&t;0x5604&t;/* signal to send to bitmask of vts */
DECL|macro|VT_RELDISP
mdefine_line|#define VT_RELDISP&t;0x5605&t;/* release display */
DECL|macro|VT_ACTIVATE
mdefine_line|#define VT_ACTIVATE&t;0x5606&t;/* make vt active */
macro_line|#endif /* _LINUX_VT_H */
eof
