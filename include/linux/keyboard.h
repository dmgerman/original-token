macro_line|#ifndef __LINUX_KEYBOARD_H
DECL|macro|__LINUX_KEYBOARD_H
mdefine_line|#define __LINUX_KEYBOARD_H
multiline_comment|/*&n; * Global flags: things that don&squot;t change between virtual consoles.&n; * This includes things like &quot;key-down&quot; flags - if the shift key is&n; * down when you change a console, it&squot;s down in both.&n; *&n; * Note that the KG_CAPSLOCK flags is NOT the flag that decides if&n; * capslock is on or not: it&squot;s just a flag about the key being&n; * physically down. The actual capslock status is in the local flags.&n; */
r_extern
r_int
r_int
id|kbd_flags
suffix:semicolon
multiline_comment|/*&n; * These are the hardcoded global flags - use the numbers beyond 16&n; * for non-standard or keyboard-dependent flags&n; */
DECL|macro|KG_LSHIFT
mdefine_line|#define KG_LSHIFT&t;0
DECL|macro|KG_RSHIFT
mdefine_line|#define KG_RSHIFT&t;1
DECL|macro|KG_LCTRL
mdefine_line|#define KG_LCTRL&t;2
DECL|macro|KG_RCTRL
mdefine_line|#define KG_RCTRL&t;3
DECL|macro|KG_ALT
mdefine_line|#define KG_ALT&t;&t;4
DECL|macro|KG_ALTGR
mdefine_line|#define KG_ALTGR&t;5
DECL|macro|KG_CAPSLOCK
mdefine_line|#define KG_CAPSLOCK&t;6
DECL|macro|KG_E0
mdefine_line|#define KG_E0&t;&t;7
DECL|macro|KG_E1
mdefine_line|#define KG_E1&t;&t;8
multiline_comment|/*&n; * kbd-&gt;xxx contains the VC-local things (flag settings etc..)&n; * The low 3 local flags are hardcoded to be the led setting..&n; */
DECL|struct|kbd_struct
r_struct
id|kbd_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|default_flags
r_int
r_int
id|default_flags
suffix:semicolon
DECL|member|kbd_flags
r_int
r_char
id|kbd_flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|kbd_struct
id|kbd_table
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * These are the local &quot;softflags&quot;, giving actual keyboard modes. The&n; * three first flags are coded to the led settings.&n; */
DECL|macro|VC_SCROLLOCK
mdefine_line|#define VC_SCROLLOCK&t;0&t;/* scroll-lock mode */
DECL|macro|VC_NUMLOCK
mdefine_line|#define VC_NUMLOCK&t;1&t;/* numeric lock mode */
DECL|macro|VC_CAPSLOCK
mdefine_line|#define VC_CAPSLOCK&t;2&t;/* capslock mode */
DECL|macro|VC_APPLIC
mdefine_line|#define VC_APPLIC&t;3&t;/* application key mode */
DECL|macro|VC_CKMODE
mdefine_line|#define VC_CKMODE&t;5&t;/* cursor key mode */
DECL|macro|VC_REPEAT
mdefine_line|#define VC_REPEAT&t;6&t;/* keyboard repeat */
DECL|macro|VC_RAW
mdefine_line|#define VC_RAW&t;&t;7&t;/* raw (scancode) mode */
DECL|macro|VC_CRLF
mdefine_line|#define VC_CRLF&t;&t;8&t;/* 0 - enter sends CR, 1 - enter sends CRLF */
DECL|macro|VC_META
mdefine_line|#define VC_META&t;&t;9&t;/* 0 - meta, 1 - meta=prefix with ESC */
DECL|macro|LED_MASK
mdefine_line|#define LED_MASK&t;7
macro_line|#ifndef KBD_DEFFLAGS
DECL|macro|KBD_DEFFLAGS
mdefine_line|#define KBD_DEFFLAGS ((1 &lt;&lt; VC_NUMLOCK) | (1 &lt;&lt; VC_REPEAT))
macro_line|#endif
r_extern
r_int
r_int
id|kbd_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|kbd_flag
r_extern
r_inline
r_int
id|kbd_flag
c_func
(paren
r_int
id|flag
)paren
(brace
r_return
id|kbd_flags
op_amp
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|set_kbd_flag
r_extern
r_inline
r_void
id|set_kbd_flag
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_flags
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|clr_kbd_flag
r_extern
r_inline
r_void
id|clr_kbd_flag
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|chg_kbd_flag
r_extern
r_inline
r_void
id|chg_kbd_flag
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_flags
op_xor_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|vc_kbd_flag
r_extern
r_inline
r_int
id|vc_kbd_flag
c_func
(paren
r_struct
id|kbd_struct
op_star
id|kbd
comma
r_int
id|flag
)paren
(brace
r_return
(paren
(paren
id|kbd-&gt;flags
op_rshift
id|flag
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|set_vc_kbd_flag
r_extern
r_inline
r_void
id|set_vc_kbd_flag
c_func
(paren
r_struct
id|kbd_struct
op_star
id|kbd
comma
r_int
id|flag
)paren
(brace
id|kbd-&gt;flags
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|clr_vc_kbd_flag
r_extern
r_inline
r_void
id|clr_vc_kbd_flag
c_func
(paren
r_struct
id|kbd_struct
op_star
id|kbd
comma
r_int
id|flag
)paren
(brace
id|kbd-&gt;flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|chg_vc_kbd_flag
r_extern
r_inline
r_void
id|chg_vc_kbd_flag
c_func
(paren
r_struct
id|kbd_struct
op_star
id|kbd
comma
r_int
id|flag
)paren
(brace
id|kbd-&gt;flags
op_xor_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
macro_line|#endif
eof
