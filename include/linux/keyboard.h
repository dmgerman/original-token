macro_line|#ifndef __LINUX_KEYBOARD_H
DECL|macro|__LINUX_KEYBOARD_H
mdefine_line|#define __LINUX_KEYBOARD_H
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|set_leds
mdefine_line|#define set_leds() mark_bh(KEYBOARD_BH)
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
DECL|macro|KG_LALT
mdefine_line|#define KG_LALT&t;&t;4
DECL|macro|KG_RALT
mdefine_line|#define KG_RALT&t;&t;5&t;/* doesn&squot;t exist, but.. */
DECL|macro|KG_LALTGR
mdefine_line|#define KG_LALTGR&t;6&t;/* doesn&squot;t exist, but.. */
DECL|macro|KG_RALTGR
mdefine_line|#define KG_RALTGR&t;7
DECL|macro|KG_CAPSLOCK
mdefine_line|#define KG_CAPSLOCK&t;8
multiline_comment|/*&n; * &quot;dead&quot; keys - prefix key values that are valid only for the next&n; * character code (sticky shift, E0/E1 special scancodes, diacriticals)&n; */
r_extern
r_int
r_int
id|kbd_dead_keys
suffix:semicolon
r_extern
r_int
r_int
id|kbd_prev_dead_keys
suffix:semicolon
multiline_comment|/*&n; * these are the hardcoded dead key flags&n; */
DECL|macro|KGD_E0
mdefine_line|#define KGD_E0&t;&t;0
DECL|macro|KGD_E1
mdefine_line|#define KGD_E1&t;&t;1
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
DECL|macro|VC_PAUSE
mdefine_line|#define VC_PAUSE&t;10&t;/* pause key pressed */
DECL|macro|LED_MASK
mdefine_line|#define LED_MASK&t;7
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
DECL|function|kbd_dead
r_extern
r_inline
r_int
id|kbd_dead
c_func
(paren
r_int
id|flag
)paren
(brace
r_return
id|kbd_prev_dead_keys
op_amp
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|set_kbd_dead
r_extern
r_inline
r_void
id|set_kbd_dead
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_dead_keys
op_or_assign
l_int|1
op_lshift
id|flag
suffix:semicolon
)brace
DECL|function|clr_kbd_dead
r_extern
r_inline
r_void
id|clr_kbd_dead
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_dead_keys
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|flag
)paren
suffix:semicolon
)brace
DECL|function|chg_kbd_dead
r_extern
r_inline
r_void
id|chg_kbd_dead
c_func
(paren
r_int
id|flag
)paren
(brace
id|kbd_dead_keys
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
DECL|macro|NR_KEYS
mdefine_line|#define NR_KEYS 112
DECL|macro|NR_KEYMAPS
mdefine_line|#define NR_KEYMAPS 3
r_extern
r_const
r_int
id|NR_TYPES
suffix:semicolon
r_extern
r_const
r_int
id|max_vals
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|key_map
(braket
id|NR_KEYMAPS
)braket
(braket
id|NR_KEYS
)braket
suffix:semicolon
DECL|macro|KT_LATIN
mdefine_line|#define KT_LATIN&t;0&t;/* we depend on this being zero */
DECL|macro|KT_FN
mdefine_line|#define KT_FN&t;&t;1
DECL|macro|KT_SPEC
mdefine_line|#define KT_SPEC&t;&t;2
DECL|macro|KT_PAD
mdefine_line|#define KT_PAD&t;&t;3
DECL|macro|KT_DEAD
mdefine_line|#define KT_DEAD&t;&t;4
DECL|macro|KT_CONS
mdefine_line|#define KT_CONS&t;&t;5
DECL|macro|KT_CUR
mdefine_line|#define KT_CUR&t;&t;6
DECL|macro|KT_SHIFT
mdefine_line|#define KT_SHIFT&t;7
DECL|macro|K
mdefine_line|#define K(t,v)&t;&t;(((t)&lt;&lt;8)|(v))
DECL|macro|KTYP
mdefine_line|#define KTYP(x)&t;&t;((x) &gt;&gt; 8)
DECL|macro|KVAL
mdefine_line|#define KVAL(x)&t;&t;((x) &amp; 0xff)
DECL|macro|K_F1
mdefine_line|#define K_F1&t;&t;K(KT_FN,0)
DECL|macro|K_F2
mdefine_line|#define K_F2&t;&t;K(KT_FN,1)
DECL|macro|K_F3
mdefine_line|#define K_F3&t;&t;K(KT_FN,2)
DECL|macro|K_F4
mdefine_line|#define K_F4&t;&t;K(KT_FN,3)
DECL|macro|K_F5
mdefine_line|#define K_F5&t;&t;K(KT_FN,4)
DECL|macro|K_F6
mdefine_line|#define K_F6&t;&t;K(KT_FN,5)
DECL|macro|K_F7
mdefine_line|#define K_F7&t;&t;K(KT_FN,6)
DECL|macro|K_F8
mdefine_line|#define K_F8&t;&t;K(KT_FN,7)
DECL|macro|K_F9
mdefine_line|#define K_F9&t;&t;K(KT_FN,8)
DECL|macro|K_F10
mdefine_line|#define K_F10&t;&t;K(KT_FN,9)
DECL|macro|K_F11
mdefine_line|#define K_F11&t;&t;K(KT_FN,10)
DECL|macro|K_F12
mdefine_line|#define K_F12&t;&t;K(KT_FN,11)
DECL|macro|K_F13
mdefine_line|#define K_F13&t;&t;K(KT_FN,12)
DECL|macro|K_F14
mdefine_line|#define K_F14&t;&t;K(KT_FN,13)
DECL|macro|K_F15
mdefine_line|#define K_F15&t;&t;K(KT_FN,14)
DECL|macro|K_F16
mdefine_line|#define K_F16&t;&t;K(KT_FN,15)
DECL|macro|K_F17
mdefine_line|#define K_F17&t;&t;K(KT_FN,16)
DECL|macro|K_F18
mdefine_line|#define K_F18&t;&t;K(KT_FN,17)
DECL|macro|K_F19
mdefine_line|#define K_F19&t;&t;K(KT_FN,18)
DECL|macro|K_F20
mdefine_line|#define K_F20&t;&t;K(KT_FN,19)
DECL|macro|K_FIND
mdefine_line|#define K_FIND&t;&t;K(KT_FN,20)
DECL|macro|K_INSERT
mdefine_line|#define K_INSERT&t;K(KT_FN,21)
DECL|macro|K_REMOVE
mdefine_line|#define K_REMOVE&t;K(KT_FN,22)
DECL|macro|K_SELECT
mdefine_line|#define K_SELECT&t;K(KT_FN,23)
DECL|macro|K_PGUP
mdefine_line|#define K_PGUP&t;&t;K(KT_FN,24)
DECL|macro|K_PGDN
mdefine_line|#define K_PGDN&t;&t;K(KT_FN,25)
DECL|macro|K_HOLE
mdefine_line|#define K_HOLE&t;&t;K(KT_SPEC,0)
DECL|macro|K_ENTER
mdefine_line|#define K_ENTER&t;&t;K(KT_SPEC,1)
DECL|macro|K_SH_REGS
mdefine_line|#define K_SH_REGS&t;K(KT_SPEC,2)
DECL|macro|K_SH_MEM
mdefine_line|#define K_SH_MEM&t;K(KT_SPEC,3)
DECL|macro|K_SH_STAT
mdefine_line|#define K_SH_STAT&t;K(KT_SPEC,4)
DECL|macro|K_BREAK
mdefine_line|#define K_BREAK&t;&t;K(KT_SPEC,5)
DECL|macro|K_CONS
mdefine_line|#define K_CONS&t;&t;K(KT_SPEC,6)
DECL|macro|K_CAPS
mdefine_line|#define K_CAPS&t;&t;K(KT_SPEC,7)
DECL|macro|K_NUM
mdefine_line|#define K_NUM&t;&t;K(KT_SPEC,8)
DECL|macro|K_HOLD
mdefine_line|#define K_HOLD&t;&t;K(KT_SPEC,9)
DECL|macro|K_P0
mdefine_line|#define K_P0&t;&t;K(KT_PAD,0)
DECL|macro|K_P1
mdefine_line|#define K_P1&t;&t;K(KT_PAD,1)
DECL|macro|K_P2
mdefine_line|#define K_P2&t;&t;K(KT_PAD,2)
DECL|macro|K_P3
mdefine_line|#define K_P3&t;&t;K(KT_PAD,3)
DECL|macro|K_P4
mdefine_line|#define K_P4&t;&t;K(KT_PAD,4)
DECL|macro|K_P5
mdefine_line|#define K_P5&t;&t;K(KT_PAD,5)
DECL|macro|K_P6
mdefine_line|#define K_P6&t;&t;K(KT_PAD,6)
DECL|macro|K_P7
mdefine_line|#define K_P7&t;&t;K(KT_PAD,7)
DECL|macro|K_P8
mdefine_line|#define K_P8&t;&t;K(KT_PAD,8)
DECL|macro|K_P9
mdefine_line|#define K_P9&t;&t;K(KT_PAD,9)
DECL|macro|K_PPLUS
mdefine_line|#define K_PPLUS&t;&t;K(KT_PAD,10)&t;/* key-pad plus&t;&t;&t;   */
DECL|macro|K_PMINUS
mdefine_line|#define K_PMINUS&t;K(KT_PAD,11)&t;/* key-pad minus&t;&t;   */
DECL|macro|K_PSTAR
mdefine_line|#define K_PSTAR&t;&t;K(KT_PAD,12)&t;/* key-pad asterisk (star)&t;   */
DECL|macro|K_PSLASH
mdefine_line|#define K_PSLASH&t;K(KT_PAD,13)&t;/* key-pad slash&t;&t;   */
DECL|macro|K_PENTER
mdefine_line|#define K_PENTER&t;K(KT_PAD,14)&t;/* key-pad enter&t;&t;   */
DECL|macro|K_PCOMMA
mdefine_line|#define K_PCOMMA&t;K(KT_PAD,15)&t;/* key-pad comma: kludge...&t;   */
DECL|macro|K_PDOT
mdefine_line|#define K_PDOT&t;&t;K(KT_PAD,16)&t;/* key-pad dot (period): kludge... */
DECL|macro|K_DGRAVE
mdefine_line|#define K_DGRAVE&t;K(KT_DEAD,0)
DECL|macro|K_DACUTE
mdefine_line|#define K_DACUTE&t;K(KT_DEAD,1)
DECL|macro|K_DCIRCM
mdefine_line|#define K_DCIRCM&t;K(KT_DEAD,2)
DECL|macro|K_DTILDE
mdefine_line|#define K_DTILDE&t;K(KT_DEAD,3)
DECL|macro|K_DDIERE
mdefine_line|#define K_DDIERE&t;K(KT_DEAD,4)
DECL|macro|K_DOWN
mdefine_line|#define K_DOWN&t;&t;K(KT_CUR,0)
DECL|macro|K_LEFT
mdefine_line|#define K_LEFT&t;&t;K(KT_CUR,1)
DECL|macro|K_RIGHT
mdefine_line|#define K_RIGHT&t;&t;K(KT_CUR,2)
DECL|macro|K_UP
mdefine_line|#define K_UP&t;&t;K(KT_CUR,3)
DECL|macro|K_LSHIFT
mdefine_line|#define K_LSHIFT&t;K(KT_SHIFT,KG_LSHIFT)
DECL|macro|K_RSHIFT
mdefine_line|#define K_RSHIFT&t;K(KT_SHIFT,KG_RSHIFT)
DECL|macro|K_LCTRL
mdefine_line|#define K_LCTRL&t;&t;K(KT_SHIFT,KG_LCTRL)
DECL|macro|K_RCTRL
mdefine_line|#define K_RCTRL&t;&t;K(KT_SHIFT,KG_RCTRL)
DECL|macro|K_LALT
mdefine_line|#define K_LALT&t;&t;K(KT_SHIFT,KG_LALT)
DECL|macro|K_RALT
mdefine_line|#define K_RALT&t;&t;K(KT_SHIFT,KG_RALT)
DECL|macro|K_LALTGR
mdefine_line|#define K_LALTGR&t;K(KT_SHIFT,KG_LALTGR)
DECL|macro|K_RALTGR
mdefine_line|#define K_RALTGR&t;K(KT_SHIFT,KG_RALTGR)
DECL|macro|K_ALT
mdefine_line|#define K_ALT&t;&t;K_LALT
DECL|macro|K_ALTGR
mdefine_line|#define K_ALTGR&t;&t;K_RALTGR
macro_line|#endif
eof
