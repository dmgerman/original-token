macro_line|#ifndef _KBD_KERN_H
DECL|macro|_KBD_KERN_H
mdefine_line|#define _KBD_KERN_H
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|set_leds
mdefine_line|#define set_leds() mark_bh(KEYBOARD_BH)
macro_line|#include &lt;linux/keyboard.h&gt;
multiline_comment|/*&n; * kbd-&gt;xxx contains the VC-local things (flag settings etc..)&n; *&n; * Note: externally visible are LED_SCR, LED_NUM, LED_CAP defined in kd.h&n; *       The code in KDGETLED / KDSETLED depends on the internal and&n; *       external order being the same.&n; *&n; * Note: lockstate is used as index in the array key_map.&n; */
DECL|struct|kbd_struct
r_struct
id|kbd_struct
(brace
DECL|member|ledstate
r_int
r_char
id|ledstate
suffix:semicolon
multiline_comment|/* 3 bits */
DECL|member|default_ledstate
r_int
r_char
id|default_ledstate
suffix:semicolon
DECL|macro|VC_SCROLLOCK
mdefine_line|#define VC_SCROLLOCK&t;0&t;/* scroll-lock mode */
DECL|macro|VC_NUMLOCK
mdefine_line|#define VC_NUMLOCK&t;1&t;/* numeric lock mode */
DECL|macro|VC_CAPSLOCK
mdefine_line|#define VC_CAPSLOCK&t;2&t;/* capslock mode */
DECL|member|lockstate
r_int
r_char
id|lockstate
suffix:semicolon
multiline_comment|/* 4 bits - must be in 0..15 */
DECL|macro|VC_SHIFTLOCK
mdefine_line|#define VC_SHIFTLOCK&t;KG_SHIFT&t;/* shift lock mode */
DECL|macro|VC_ALTGRLOCK
mdefine_line|#define VC_ALTGRLOCK&t;KG_ALTGR&t;/* altgr lock mode */
DECL|macro|VC_CTRLLOCK
mdefine_line|#define VC_CTRLLOCK&t;KG_CTRL &t;/* control lock mode */
DECL|macro|VC_ALTLOCK
mdefine_line|#define VC_ALTLOCK&t;KG_ALT  &t;/* alt lock mode */
DECL|member|modeflags
r_int
r_char
id|modeflags
suffix:semicolon
DECL|macro|VC_APPLIC
mdefine_line|#define VC_APPLIC&t;0&t;/* application key mode */
DECL|macro|VC_CKMODE
mdefine_line|#define VC_CKMODE&t;1&t;/* cursor key mode */
DECL|macro|VC_REPEAT
mdefine_line|#define VC_REPEAT&t;2&t;/* keyboard repeat */
DECL|macro|VC_CRLF
mdefine_line|#define VC_CRLF&t;&t;3&t;/* 0 - enter sends CR, 1 - enter sends CRLF */
DECL|macro|VC_META
mdefine_line|#define VC_META&t;&t;4&t;/* 0 - meta, 1 - meta=prefix with ESC */
DECL|macro|VC_PAUSE
mdefine_line|#define VC_PAUSE&t;5&t;/* pause key pressed - unused */
DECL|macro|VC_RAW
mdefine_line|#define VC_RAW&t;&t;6&t;/* raw (scancode) mode */
DECL|macro|VC_MEDIUMRAW
mdefine_line|#define VC_MEDIUMRAW&t;7&t;/* medium raw (keycode) mode */
)brace
suffix:semicolon
r_extern
r_struct
id|kbd_struct
id|kbd_table
(braket
)braket
suffix:semicolon
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
DECL|function|vc_kbd_led
r_extern
r_inline
r_int
id|vc_kbd_led
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
id|kbd-&gt;ledstate
op_rshift
id|flag
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|vc_kbd_lock
r_extern
r_inline
r_int
id|vc_kbd_lock
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
id|kbd-&gt;lockstate
op_rshift
id|flag
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|vc_kbd_mode
r_extern
r_inline
r_int
id|vc_kbd_mode
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
id|kbd-&gt;modeflags
op_rshift
id|flag
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|set_vc_kbd_led
r_extern
r_inline
r_void
id|set_vc_kbd_led
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
id|kbd-&gt;ledstate
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|set_vc_kbd_lock
r_extern
r_inline
r_void
id|set_vc_kbd_lock
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
id|kbd-&gt;lockstate
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|set_vc_kbd_mode
r_extern
r_inline
r_void
id|set_vc_kbd_mode
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
id|kbd-&gt;modeflags
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|clr_vc_kbd_led
r_extern
r_inline
r_void
id|clr_vc_kbd_led
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
id|kbd-&gt;ledstate
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|clr_vc_kbd_lock
r_extern
r_inline
r_void
id|clr_vc_kbd_lock
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
id|kbd-&gt;lockstate
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|clr_vc_kbd_mode
r_extern
r_inline
r_void
id|clr_vc_kbd_mode
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
id|kbd-&gt;modeflags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|chg_vc_kbd_led
r_extern
r_inline
r_void
id|chg_vc_kbd_led
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
id|kbd-&gt;ledstate
op_xor_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|chg_vc_kbd_lock
r_extern
r_inline
r_void
id|chg_vc_kbd_lock
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
id|kbd-&gt;lockstate
op_xor_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|chg_vc_kbd_mode
r_extern
r_inline
r_void
id|chg_vc_kbd_mode
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
id|kbd-&gt;modeflags
op_xor_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
macro_line|#endif
eof