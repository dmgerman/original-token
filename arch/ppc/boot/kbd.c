multiline_comment|/* Keyboard handler */
macro_line|#include &lt;../drivers/char/defkeymap.c&gt; /* yeah I know it&squot;s bad */
DECL|macro|L
mdefine_line|#define&t;L&t;&t;0x0001&t;/* locking function */
DECL|macro|SHF
mdefine_line|#define&t;SHF&t;&t;0x0002&t;/* keyboard shift */
DECL|macro|ALT
mdefine_line|#define&t;ALT&t;&t;0x0004&t;/* alternate shift -- alternate chars */
DECL|macro|NUM
mdefine_line|#define&t;NUM&t;&t;0x0008&t;/* numeric shift  cursors vs. numeric */
DECL|macro|CTL
mdefine_line|#define&t;CTL&t;&t;0x0010&t;/* control shift  -- allows ctl function */
DECL|macro|CPS
mdefine_line|#define&t;CPS&t;&t;0x0020&t;/* caps shift -- swaps case of letter */
DECL|macro|ASCII
mdefine_line|#define&t;ASCII&t;&t;0x0040&t;/* ascii code for this key */
DECL|macro|STP
mdefine_line|#define&t;STP&t;&t;0x0080&t;/* stop output */
DECL|macro|FUNC
mdefine_line|#define&t;FUNC&t;&t;0x0100&t;/* function key */
DECL|macro|SCROLL
mdefine_line|#define&t;SCROLL&t;&t;0x0200&t;/* scroll lock key */
DECL|variable|shfts
DECL|variable|ctls
DECL|variable|alts
DECL|variable|caps
DECL|variable|num
DECL|variable|stp
r_int
r_char
id|shfts
comma
id|ctls
comma
id|alts
comma
id|caps
comma
id|num
comma
id|stp
suffix:semicolon
DECL|macro|KBDATAP
mdefine_line|#define&t;KBDATAP&t;&t;0x60&t;/* kbd data port */
DECL|macro|KBSTATUSPORT
mdefine_line|#define&t;KBSTATUSPORT&t;0x61&t;/* kbd status */
DECL|macro|KBSTATP
mdefine_line|#define&t;KBSTATP&t;&t;0x64&t;/* kbd status port */
DECL|macro|KBINRDY
mdefine_line|#define&t;KBINRDY&t;&t;0x01
DECL|macro|KBOUTRDY
mdefine_line|#define&t;KBOUTRDY&t;0x02
DECL|macro|_x__
mdefine_line|#define _x__ 0x00  /* Unknown / unmapped */
DECL|variable|action
r_const
r_int
r_int
id|action
(braket
)braket
op_assign
(brace
l_int|0
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan  0- 7 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan  8-15 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan 16-23 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|CTL
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan 24-31 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan 32-39 */
id|ASCII
comma
id|ASCII
comma
id|SHF
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan 40-47 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|SHF
comma
id|ASCII
comma
multiline_comment|/* scan 48-55 */
id|ALT
comma
id|ASCII
comma
id|CPS
comma
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
multiline_comment|/* scan 56-63 */
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
id|FUNC
comma
id|NUM
comma
id|SCROLL
comma
id|ASCII
comma
multiline_comment|/* scan 64-71 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
multiline_comment|/* scan 72-79 */
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
id|ASCII
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 80-87 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 88-95 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 96-103 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 104-111 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 112-119 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* scan 120-127 */
)brace
suffix:semicolon
r_static
r_int
DECL|function|kbd
id|kbd
c_func
(paren
id|noblock
)paren
r_int
id|noblock
suffix:semicolon
(brace
r_int
r_char
id|dt
comma
id|brk
comma
id|act
suffix:semicolon
r_int
id|first
op_assign
l_int|1
suffix:semicolon
id|loop
suffix:colon
r_if
c_cond
(paren
id|noblock
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBINRDY
)paren
op_eq
l_int|0
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBINRDY
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|dt
op_assign
id|inb
c_func
(paren
id|KBDATAP
)paren
suffix:semicolon
id|brk
op_assign
id|dt
op_amp
l_int|0x80
suffix:semicolon
multiline_comment|/* brk == 1 on key release */
id|dt
op_assign
id|dt
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* keycode */
id|act
op_assign
id|action
(braket
id|dt
)braket
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*act&amp;SHF*/
id|dt
op_eq
l_int|54
)paren
id|shfts
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*act&amp;ALT*/
id|dt
op_eq
l_int|48
)paren
id|alts
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*act&amp;NUM*/
id|dt
op_eq
l_int|69
)paren
r_if
c_cond
(paren
id|act
op_amp
id|L
)paren
(brace
multiline_comment|/* NUM lock */
r_if
c_cond
(paren
op_logical_neg
id|brk
)paren
(brace
id|num
op_assign
op_logical_neg
id|num
suffix:semicolon
)brace
)brace
r_else
id|num
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*act&amp;CTL*/
id|dt
op_eq
l_int|29
)paren
id|ctls
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*act&amp;CPS*/
id|dt
op_eq
l_int|58
)paren
r_if
c_cond
(paren
id|act
op_amp
id|L
)paren
(brace
multiline_comment|/* CAPS lock */
r_if
c_cond
(paren
op_logical_neg
id|brk
)paren
(brace
id|caps
op_assign
op_logical_neg
id|caps
suffix:semicolon
)brace
)brace
r_else
id|caps
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|0
multiline_comment|/*act&amp;STP*/
)paren
r_if
c_cond
(paren
id|act
op_amp
id|L
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|brk
)paren
(brace
id|stp
op_assign
op_logical_neg
id|stp
suffix:semicolon
)brace
)brace
r_else
id|stp
op_assign
id|brk
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|act
op_amp
id|ASCII
)paren
op_logical_and
op_logical_neg
id|brk
)paren
(brace
r_int
r_char
id|chr
suffix:semicolon
r_if
c_cond
(paren
id|shfts
)paren
id|chr
op_assign
id|shift_map
(braket
id|dt
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ctls
)paren
id|chr
op_assign
id|ctrl_map
(braket
id|dt
)braket
suffix:semicolon
r_else
id|chr
op_assign
id|plain_map
(braket
id|dt
)braket
suffix:semicolon
r_if
c_cond
(paren
id|alts
)paren
id|chr
op_or_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|caps
op_logical_and
(paren
id|chr
op_ge
l_char|&squot;a&squot;
op_logical_and
id|chr
op_le
l_char|&squot;z&squot;
)paren
)paren
id|chr
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|chr
op_eq
l_int|0x01
)paren
id|chr
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
multiline_comment|/* hack */
DECL|macro|CTRL
mdefine_line|#define CTRL(s) (s &amp; 0x1F)&t;&t;&t;
r_if
c_cond
(paren
(paren
id|chr
op_eq
l_char|&squot;&bslash;r&squot;
)paren
op_logical_or
(paren
id|chr
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_logical_or
(paren
id|chr
op_eq
id|CTRL
c_func
(paren
l_char|&squot;A&squot;
)paren
)paren
op_logical_or
(paren
id|chr
op_eq
id|CTRL
c_func
(paren
l_char|&squot;S&squot;
)paren
)paren
)paren
(brace
multiline_comment|/* Wait for key up */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBINRDY
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|dt
op_assign
id|inb
c_func
(paren
id|KBDATAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dt
op_amp
l_int|0x80
)paren
multiline_comment|/* key up */
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|chr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first
op_logical_and
id|brk
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Ignore initial &squot;key up&squot; codes */
r_goto
id|loop
suffix:semicolon
)brace
r_static
DECL|function|scankbd
id|scankbd
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|kbd
c_func
(paren
l_int|1
)paren
op_ne
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_static
DECL|function|kbdreset
id|kbdreset
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Send self-test */
r_while
c_loop
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBOUTRDY
)paren
suffix:semicolon
id|outb
c_func
(paren
id|KBSTATP
comma
l_int|0xAA
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBINRDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* wait input ready */
r_if
c_cond
(paren
(paren
id|c
op_assign
id|inb
c_func
(paren
id|KBDATAP
)paren
)paren
op_ne
l_int|0x55
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;Keyboard self test failed - result:&quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|c
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable interrupts and keyboard controller */
r_while
c_loop
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBOUTRDY
)paren
suffix:semicolon
id|outb
c_func
(paren
id|KBSTATP
comma
l_int|0x60
)paren
suffix:semicolon
r_while
c_loop
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBOUTRDY
)paren
suffix:semicolon
id|outb
c_func
(paren
id|KBDATAP
comma
l_int|0x45
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10000
suffix:semicolon
id|i
op_increment
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBOUTRDY
)paren
suffix:semicolon
id|outb
c_func
(paren
id|KBSTATP
comma
l_int|0xAE
)paren
suffix:semicolon
)brace
DECL|variable|kbd_reset
r_static
r_int
id|kbd_reset
op_assign
l_int|0
suffix:semicolon
DECL|function|CRT_getc
id|CRT_getc
c_func
(paren
r_void
)paren
(brace
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd_reset
)paren
(brace
id|kbdreset
c_func
(paren
)paren
suffix:semicolon
id|kbd_reset
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|c
op_assign
id|kbd
c_func
(paren
l_int|0
)paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|CRT_tstc
id|CRT_tstc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kbd_reset
)paren
(brace
id|kbdreset
c_func
(paren
)paren
suffix:semicolon
id|kbd_reset
op_increment
suffix:semicolon
)brace
r_return
(paren
(paren
id|inb
c_func
(paren
id|KBSTATP
)paren
op_amp
id|KBINRDY
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
eof