macro_line|#ifndef __LINUX_KEYBOARD_H
DECL|macro|__LINUX_KEYBOARD_H
mdefine_line|#define __LINUX_KEYBOARD_H
DECL|macro|KG_SHIFT
mdefine_line|#define KG_SHIFT&t;0
DECL|macro|KG_CTRL
mdefine_line|#define KG_CTRL&t;&t;2
DECL|macro|KG_ALT
mdefine_line|#define KG_ALT&t;&t;3
DECL|macro|KG_ALTGR
mdefine_line|#define KG_ALTGR&t;1
DECL|macro|KG_SHIFTL
mdefine_line|#define KG_SHIFTL       4
DECL|macro|KG_SHIFTR
mdefine_line|#define KG_SHIFTR       5
DECL|macro|KG_CTRLL
mdefine_line|#define KG_CTRLL        6
DECL|macro|KG_CTRLR
mdefine_line|#define KG_CTRLR        7
DECL|macro|NR_KEYS
mdefine_line|#define NR_KEYS 128
DECL|macro|NR_KEYMAPS
mdefine_line|#define NR_KEYMAPS 16
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
DECL|macro|NR_FUNC
mdefine_line|#define NR_FUNC 36
DECL|macro|FUNC_BUFSIZE
mdefine_line|#define FUNC_BUFSIZE 512
r_extern
r_char
id|func_buf
(braket
id|FUNC_BUFSIZE
)braket
suffix:semicolon
r_extern
r_char
op_star
id|func_table
(braket
id|NR_FUNC
)braket
suffix:semicolon
DECL|macro|KT_LATIN
mdefine_line|#define KT_LATIN&t;0&t;/* we depend on this being zero */
DECL|macro|KT_LETTER
mdefine_line|#define KT_LETTER      11&t;/* symbol that can be acted upon by CapsLock */
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
DECL|macro|KT_META
mdefine_line|#define KT_META&t;&t;8
DECL|macro|KT_ASCII
mdefine_line|#define KT_ASCII&t;9
DECL|macro|KT_LOCK
mdefine_line|#define KT_LOCK&t;&t;10
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
DECL|macro|K_MACRO
mdefine_line|#define K_MACRO         K(KT_FN,26)
DECL|macro|K_HELP
mdefine_line|#define K_HELP          K(KT_FN,27)
DECL|macro|K_DO
mdefine_line|#define K_DO            K(KT_FN,28)
DECL|macro|K_PAUSE
mdefine_line|#define K_PAUSE         K(KT_FN,29)
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
DECL|macro|K_SCROLLFORW
mdefine_line|#define K_SCROLLFORW&t;K(KT_SPEC,10)
DECL|macro|K_SCROLLBACK
mdefine_line|#define K_SCROLLBACK&t;K(KT_SPEC,11)
DECL|macro|K_BOOT
mdefine_line|#define K_BOOT&t;&t;K(KT_SPEC,12)
DECL|macro|K_CAPSON
mdefine_line|#define K_CAPSON&t;K(KT_SPEC,13)
DECL|macro|K_COMPOSE
mdefine_line|#define K_COMPOSE       K(KT_SPEC,14)
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
DECL|macro|K_PPLUSMINUS
mdefine_line|#define K_PPLUSMINUS    K(KT_PAD,17)    /* key-pad plus/minus              */
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
DECL|macro|K_SHIFT
mdefine_line|#define K_SHIFT&t;&t;K(KT_SHIFT,KG_SHIFT)
DECL|macro|K_CTRL
mdefine_line|#define K_CTRL&t;&t;K(KT_SHIFT,KG_CTRL)
DECL|macro|K_ALT
mdefine_line|#define K_ALT&t;&t;K(KT_SHIFT,KG_ALT)
DECL|macro|K_ALTGR
mdefine_line|#define K_ALTGR&t;&t;K(KT_SHIFT,KG_ALTGR)
DECL|macro|K_SHIFTL
mdefine_line|#define K_SHIFTL        K(KT_SHIFT,KG_SHIFTL)
DECL|macro|K_SHIFTR
mdefine_line|#define K_SHIFTR        K(KT_SHIFT,KG_SHIFTR)
DECL|macro|K_CTRLL
mdefine_line|#define K_CTRLL         K(KT_SHIFT,KG_CTRLL)
DECL|macro|K_CTRLR
mdefine_line|#define K_CTRLR         K(KT_SHIFT,KG_CTRLR)
DECL|macro|NR_SHIFT
mdefine_line|#define NR_SHIFT&t;4
DECL|macro|K_CAPSSHIFT
mdefine_line|#define K_CAPSSHIFT&t;K(KT_SHIFT,NR_SHIFT)
DECL|macro|K_ASC0
mdefine_line|#define K_ASC0&t;&t;K(KT_ASCII,0)
DECL|macro|K_ASC1
mdefine_line|#define K_ASC1&t;&t;K(KT_ASCII,1)
DECL|macro|K_ASC2
mdefine_line|#define K_ASC2&t;&t;K(KT_ASCII,2)
DECL|macro|K_ASC3
mdefine_line|#define K_ASC3&t;&t;K(KT_ASCII,3)
DECL|macro|K_ASC4
mdefine_line|#define K_ASC4&t;&t;K(KT_ASCII,4)
DECL|macro|K_ASC5
mdefine_line|#define K_ASC5&t;&t;K(KT_ASCII,5)
DECL|macro|K_ASC6
mdefine_line|#define K_ASC6&t;&t;K(KT_ASCII,6)
DECL|macro|K_ASC7
mdefine_line|#define K_ASC7&t;&t;K(KT_ASCII,7)
DECL|macro|K_ASC8
mdefine_line|#define K_ASC8&t;&t;K(KT_ASCII,8)
DECL|macro|K_ASC9
mdefine_line|#define K_ASC9&t;&t;K(KT_ASCII,9)
DECL|macro|K_SHIFTLOCK
mdefine_line|#define K_SHIFTLOCK&t;K(KT_LOCK,KG_SHIFT)
DECL|macro|K_CTRLLOCK
mdefine_line|#define K_CTRLLOCK&t;K(KT_LOCK,KG_CTRL)
DECL|macro|K_ALTLOCK
mdefine_line|#define K_ALTLOCK&t;K(KT_LOCK,KG_ALT)
DECL|macro|K_ALTGRLOCK
mdefine_line|#define K_ALTGRLOCK&t;K(KT_LOCK,KG_ALTGR)
DECL|macro|MAX_DIACR
mdefine_line|#define MAX_DIACR       256
macro_line|#endif
eof
