multiline_comment|/*&n; * linux/drivers/char/q40_keyb.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/q40ints.h&gt;
multiline_comment|/* Some configuration switches are present in the include file... */
DECL|macro|KBD_REPORT_ERR
mdefine_line|#define KBD_REPORT_ERR
multiline_comment|/* Simple translation table for the SysRq keys */
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|q40kbd_sysrq_xlate
r_int
r_char
id|q40kbd_sysrq_xlate
(braket
l_int|128
)braket
op_assign
l_string|&quot;&bslash;000&bslash;0331234567890-=&bslash;177&bslash;t&quot;
multiline_comment|/* 0x00 - 0x0f */
l_string|&quot;qwertyuiop[]&bslash;r&bslash;000as&quot;
multiline_comment|/* 0x10 - 0x1f */
l_string|&quot;dfghjkl;&squot;`&bslash;000&bslash;&bslash;zxcv&quot;
multiline_comment|/* 0x20 - 0x2f */
l_string|&quot;bnm,./&bslash;000*&bslash;000 &bslash;000&bslash;201&bslash;202&bslash;203&bslash;204&bslash;205&quot;
multiline_comment|/* 0x30 - 0x3f */
l_string|&quot;&bslash;206&bslash;207&bslash;210&bslash;211&bslash;212&bslash;000&bslash;000789-456+1&quot;
multiline_comment|/* 0x40 - 0x4f */
l_string|&quot;230&bslash;177&bslash;000&bslash;000&bslash;213&bslash;214&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&quot;
multiline_comment|/* 0x50 - 0x5f */
l_string|&quot;&bslash;r&bslash;000/&quot;
suffix:semicolon
multiline_comment|/* 0x60 - 0x6f */
macro_line|#endif
multiline_comment|/* Q40 uses AT scancodes - no way to change it. so we have to translate ..*/
multiline_comment|/* 0x00 means not a valid entry or no conversion known                    */
DECL|variable|q40cl
r_int
r_static
r_char
id|q40cl
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/* 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   a,   b,   c,   d,   e,   f, */
l_int|0x00
comma
l_int|0x43
comma
l_int|0x00
comma
l_int|0x3f
comma
l_int|0x3d
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x58
comma
l_int|0x00
comma
l_int|0x44
comma
l_int|0x42
comma
l_int|0x40
comma
l_int|0x3e
comma
l_int|0x0f
comma
l_int|0x29
comma
l_int|0x00
comma
multiline_comment|/* 0x00 - 0x0f */
l_int|0x00
comma
l_int|0x38
comma
l_int|0x2a
comma
l_int|0x00
comma
l_int|0x1d
comma
l_int|0x10
comma
l_int|0x02
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x2c
comma
l_int|0x1f
comma
l_int|0x1e
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x00
comma
multiline_comment|/* 0x10 - 0x1f */
l_int|0x00
comma
l_int|0x2e
comma
l_int|0x2d
comma
l_int|0x20
comma
l_int|0x12
comma
l_int|0x05
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x21
comma
l_int|0x39
comma
l_int|0x2f
comma
l_int|0x21
comma
l_int|0x14
comma
l_int|0x13
comma
l_int|0x06
comma
l_int|0x00
comma
multiline_comment|/* 0x20 - 0x2f  &squot;f&squot; is at 0x2b, what is 0x28 ???*/
l_int|0x00
comma
l_int|0x31
comma
l_int|0x30
comma
l_int|0x23
comma
l_int|0x22
comma
l_int|0x15
comma
l_int|0x07
comma
l_int|0x00
comma
l_int|0x24
comma
l_int|0x00
comma
l_int|0x32
comma
l_int|0x24
comma
l_int|0x16
comma
l_int|0x08
comma
l_int|0x09
comma
l_int|0x00
comma
multiline_comment|/* 0x30 - 0x3f */
l_int|0x00
comma
l_int|0x33
comma
l_int|0x25
comma
l_int|0x17
comma
l_int|0x18
comma
l_int|0x0b
comma
l_int|0x0a
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0x19
comma
l_int|0x0c
comma
l_int|0x00
comma
multiline_comment|/* 0x40 - 0x4f */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x28
comma
l_int|0x00
comma
l_int|0x1a
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x3a
comma
l_int|0x36
comma
l_int|0x1c
comma
l_int|0x1b
comma
l_int|0x00
comma
l_int|0x2b
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x50 - 0x5f*/
l_int|0x00
comma
l_int|0x56
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x0e
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x4f
comma
l_int|0x00
comma
l_int|0x4b
comma
l_int|0x47
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x60 - 0x6f */
l_int|0x52
comma
l_int|0x53
comma
l_int|0x50
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x48
comma
l_int|0x01
comma
l_int|0x45
comma
l_int|0x57
comma
l_int|0x4e
comma
l_int|0x51
comma
l_int|0x4a
comma
l_int|0x37
comma
l_int|0x49
comma
l_int|0x46
comma
l_int|0x00
comma
multiline_comment|/* 0x70 - 0x7f */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x41
comma
l_int|0x37
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x80 - 0x8f  0x84/0x37 is SySrq*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x90 - 0x9f */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xa0 - 0xaf */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xb0 - 0xbf */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xc0 - 0xcf */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xd0 - 0xdf */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xe0 - 0xef */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xf0 - 0xff */
)brace
suffix:semicolon
multiline_comment|/* another table, AT 0xe0 codes to PC 0xe0 codes, &n;   0xff special entry for SysRq - DROPPED right now  */
DECL|variable|q40ecl
r_static
r_int
r_char
id|q40ecl
(braket
)braket
op_assign
(brace
multiline_comment|/* 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   a,   b,   c,   d,   e,   f, */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x00 - 0x0f*/
l_int|0x00
comma
l_int|0x38
comma
l_int|0x2a
comma
l_int|0x00
comma
l_int|0x1d
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x10 - 0x1f */
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x20 - 0x2f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x30 - 0x3f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x35
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x40 - 0x4f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x36
comma
l_int|0x1c
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x50 - 0x5f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x4f
comma
l_int|0x00
comma
l_int|0x4b
comma
l_int|0x47
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x60 - 0x6f*/
l_int|0x52
comma
l_int|0x53
comma
l_int|0x50
comma
l_int|0x00
comma
l_int|0x4d
comma
l_int|0x48
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x51
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x49
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x70 - 0x7f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x80 - 0x8f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0x90 - 0x9f*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xa0 - 0xaf*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xb0 - 0xbf*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xc0 - 0xcf*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xd0 - 0xdf*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 0xe0 - 0xef*/
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
multiline_comment|/* 0xf0 - 0xff*/
)brace
suffix:semicolon
DECL|variable|kbd_controller_lock
r_static
id|spinlock_t
id|kbd_controller_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Translation of escaped scancodes to keycodes.&n; * This is now user-settable.&n; * The keycodes 1-88,96-111,119 are fairly standard, and&n; * should probably not be changed - changing might confuse X.&n; * X also interprets scancode 0x5d (KEY_Begin).&n; *&n; * For 1-88 keycode equals scancode.&n; */
DECL|macro|E0_KPENTER
mdefine_line|#define E0_KPENTER 96
DECL|macro|E0_RCTRL
mdefine_line|#define E0_RCTRL   97
DECL|macro|E0_KPSLASH
mdefine_line|#define E0_KPSLASH 98
DECL|macro|E0_PRSCR
mdefine_line|#define E0_PRSCR   99
DECL|macro|E0_RALT
mdefine_line|#define E0_RALT    100
DECL|macro|E0_BREAK
mdefine_line|#define E0_BREAK   101  /* (control-pause) */
DECL|macro|E0_HOME
mdefine_line|#define E0_HOME    102
DECL|macro|E0_UP
mdefine_line|#define E0_UP      103
DECL|macro|E0_PGUP
mdefine_line|#define E0_PGUP    104
DECL|macro|E0_LEFT
mdefine_line|#define E0_LEFT    105
DECL|macro|E0_RIGHT
mdefine_line|#define E0_RIGHT   106
DECL|macro|E0_END
mdefine_line|#define E0_END     107
DECL|macro|E0_DOWN
mdefine_line|#define E0_DOWN    108
DECL|macro|E0_PGDN
mdefine_line|#define E0_PGDN    109
DECL|macro|E0_INS
mdefine_line|#define E0_INS     110
DECL|macro|E0_DEL
mdefine_line|#define E0_DEL     111
DECL|macro|E1_PAUSE
mdefine_line|#define E1_PAUSE   119
multiline_comment|/*&n; * The keycodes below are randomly located in 89-95,112-118,120-127.&n; * They could be thrown away (and all occurrences below replaced by 0),&n; * but that would force many users to use the `setkeycodes&squot; utility, where&n; * they needed not before. It does not matter that there are duplicates, as&n; * long as no duplication occurs for any single keyboard.&n; */
DECL|macro|SC_LIM
mdefine_line|#define SC_LIM 89
DECL|macro|FOCUS_PF1
mdefine_line|#define FOCUS_PF1 85           /* actual code! */
DECL|macro|FOCUS_PF2
mdefine_line|#define FOCUS_PF2 89
DECL|macro|FOCUS_PF3
mdefine_line|#define FOCUS_PF3 90
DECL|macro|FOCUS_PF4
mdefine_line|#define FOCUS_PF4 91
DECL|macro|FOCUS_PF5
mdefine_line|#define FOCUS_PF5 92
DECL|macro|FOCUS_PF6
mdefine_line|#define FOCUS_PF6 93
DECL|macro|FOCUS_PF7
mdefine_line|#define FOCUS_PF7 94
DECL|macro|FOCUS_PF8
mdefine_line|#define FOCUS_PF8 95
DECL|macro|FOCUS_PF9
mdefine_line|#define FOCUS_PF9 120
DECL|macro|FOCUS_PF10
mdefine_line|#define FOCUS_PF10 121
DECL|macro|FOCUS_PF11
mdefine_line|#define FOCUS_PF11 122
DECL|macro|FOCUS_PF12
mdefine_line|#define FOCUS_PF12 123
DECL|macro|JAP_86
mdefine_line|#define JAP_86     124
multiline_comment|/* tfj@olivia.ping.dk:&n; * The four keys are located over the numeric keypad, and are&n; * labelled A1-A4. It&squot;s an rc930 keyboard, from&n; * Regnecentralen/RC International, Now ICL.&n; * Scancodes: 59, 5a, 5b, 5c.&n; */
DECL|macro|RGN1
mdefine_line|#define RGN1 124
DECL|macro|RGN2
mdefine_line|#define RGN2 125
DECL|macro|RGN3
mdefine_line|#define RGN3 126
DECL|macro|RGN4
mdefine_line|#define RGN4 127
DECL|variable|high_keys
r_static
r_int
r_char
id|high_keys
(braket
l_int|128
op_minus
id|SC_LIM
)braket
op_assign
(brace
id|RGN1
comma
id|RGN2
comma
id|RGN3
comma
id|RGN4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x59-0x5f */
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
multiline_comment|/* 0x60-0x67 */
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
id|FOCUS_PF11
comma
l_int|0
comma
id|FOCUS_PF12
comma
multiline_comment|/* 0x68-0x6f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|FOCUS_PF2
comma
id|FOCUS_PF9
comma
l_int|0
comma
l_int|0
comma
id|FOCUS_PF3
comma
multiline_comment|/* 0x70-0x77 */
id|FOCUS_PF4
comma
id|FOCUS_PF5
comma
id|FOCUS_PF6
comma
id|FOCUS_PF7
comma
multiline_comment|/* 0x78-0x7b */
id|FOCUS_PF8
comma
id|JAP_86
comma
id|FOCUS_PF10
comma
l_int|0
multiline_comment|/* 0x7c-0x7f */
)brace
suffix:semicolon
multiline_comment|/* BTC */
DECL|macro|E0_MACRO
mdefine_line|#define E0_MACRO   112
multiline_comment|/* LK450 */
DECL|macro|E0_F13
mdefine_line|#define E0_F13     113
DECL|macro|E0_F14
mdefine_line|#define E0_F14     114
DECL|macro|E0_HELP
mdefine_line|#define E0_HELP    115
DECL|macro|E0_DO
mdefine_line|#define E0_DO      116
DECL|macro|E0_F17
mdefine_line|#define E0_F17     117
DECL|macro|E0_KPMINPLUS
mdefine_line|#define E0_KPMINPLUS 118
multiline_comment|/*&n; * My OmniKey generates e0 4c for  the &quot;OMNI&quot; key and the&n; * right alt key does nada. [kkoller@nyx10.cs.du.edu]&n; */
DECL|macro|E0_OK
mdefine_line|#define E0_OK&t;124
multiline_comment|/*&n; * New microsoft keyboard is rumoured to have&n; * e0 5b (left window button), e0 5c (right window button),&n; * e0 5d (menu button). [or: LBANNER, RBANNER, RMENU]&n; * [or: Windows_L, Windows_R, TaskMan]&n; */
DECL|macro|E0_MSLW
mdefine_line|#define E0_MSLW&t;125
DECL|macro|E0_MSRW
mdefine_line|#define E0_MSRW&t;126
DECL|macro|E0_MSTM
mdefine_line|#define E0_MSTM&t;127
multiline_comment|/* this can be changed using setkeys : */
DECL|variable|e0_keys
r_static
r_int
r_char
id|e0_keys
(braket
l_int|128
)braket
op_assign
(brace
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
multiline_comment|/* 0x00-0x07 */
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
multiline_comment|/* 0x08-0x0f */
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
multiline_comment|/* 0x10-0x17 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_KPENTER
comma
id|E0_RCTRL
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x18-0x1f */
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
multiline_comment|/* 0x20-0x27 */
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
multiline_comment|/* 0x28-0x2f */
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
id|E0_KPSLASH
comma
l_int|0
comma
id|E0_PRSCR
comma
multiline_comment|/* 0x30-0x37 */
id|E0_RALT
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_F13
comma
id|E0_F14
comma
id|E0_HELP
comma
multiline_comment|/* 0x38-0x3f */
id|E0_DO
comma
id|E0_F17
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_BREAK
comma
id|E0_HOME
comma
multiline_comment|/* 0x40-0x47 */
id|E0_UP
comma
id|E0_PGUP
comma
l_int|0
comma
id|E0_LEFT
comma
id|E0_OK
comma
id|E0_RIGHT
comma
id|E0_KPMINPLUS
comma
id|E0_END
comma
multiline_comment|/* 0x48-0x4f */
id|E0_DOWN
comma
id|E0_PGDN
comma
id|E0_INS
comma
id|E0_DEL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x50-0x57 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_MSLW
comma
id|E0_MSRW
comma
id|E0_MSTM
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x58-0x5f */
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
multiline_comment|/* 0x60-0x67 */
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
id|E0_MACRO
comma
multiline_comment|/* 0x68-0x6f */
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
multiline_comment|/* 0x70-0x77 */
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
multiline_comment|/* 0x78-0x7f */
)brace
suffix:semicolon
DECL|variable|prev_scancode
r_static
r_int
r_int
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* remember E0, E1 */
DECL|function|q40kbd_setkeycode
r_int
id|q40kbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
(brace
r_if
c_cond
(paren
id|scancode
template_param
l_int|255
op_logical_or
id|keycode
OG
l_int|127
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|scancode
OL
l_int|128
)paren
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
op_assign
id|keycode
suffix:semicolon
r_else
id|e0_keys
(braket
id|scancode
op_minus
l_int|128
)braket
op_assign
id|keycode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|q40kbd_getkeycode
r_int
id|q40kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
r_return
(paren
id|scancode
template_param
l_int|255
)paren
ques
c_cond
op_minus
id|EINVAL
suffix:colon
(paren
id|scancode
OL
l_int|128
)paren
ques
c_cond
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
suffix:colon
id|e0_keys
(braket
id|scancode
op_minus
l_int|128
)braket
suffix:semicolon
)brace
DECL|macro|disable_keyboard
mdefine_line|#define disable_keyboard()&t;
DECL|macro|enable_keyboard
mdefine_line|#define enable_keyboard()&t;
DECL|function|q40kbd_translate
r_int
id|q40kbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
(brace
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0xe0
op_logical_or
id|scancode
op_eq
l_int|0xe1
)paren
(brace
id|prev_scancode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_scancode
)paren
(brace
multiline_comment|/*&n;&t;   * usually it will be 0xe0, but a Pause key generates&n;&t;   * e1 1d 45 e1 9d c5 when pressed, and nothing when released&n;&t;   */
r_if
c_cond
(paren
id|prev_scancode
op_ne
l_int|0xe0
)paren
(brace
r_if
c_cond
(paren
id|prev_scancode
op_eq
l_int|0xe1
op_logical_and
id|scancode
op_eq
l_int|0x1d
)paren
(brace
id|prev_scancode
op_assign
l_int|0x100
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|prev_scancode
op_eq
l_int|0x100
op_logical_and
id|scancode
op_eq
l_int|0x45
)paren
(brace
op_star
id|keycode
op_assign
id|E1_PAUSE
suffix:semicolon
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef KBD_REPORT_UNKN
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unknown e1 escape sequence&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;       *  The keyboard maintains its own internal caps lock and&n;&t;       *  num lock statuses. In caps lock mode E0 AA precedes make&n;&t;       *  code and E0 2A follows break code. In num lock mode,&n;&t;       *  E0 2A precedes make code and E0 AA follows break code.&n;&t;       *  We do our own book-keeping, so we will just ignore these.&n;&t;       */
multiline_comment|/*&n;&t;       *  For my keyboard there is no caps lock mode, but there are&n;&t;       *  both Shift-L and Shift-R modes. The former mode generates&n;&t;       *  E0 2A / E0 AA pairs, the latter E0 B6 / E0 36 pairs.&n;&t;       *  So, we should also ignore the latter. - aeb@cwi.nl&n;&t;       */
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0x2a
op_logical_or
id|scancode
op_eq
l_int|0x36
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|e0_keys
(braket
id|scancode
)braket
)paren
op_star
id|keycode
op_assign
id|e0_keys
(braket
id|scancode
)braket
suffix:semicolon
r_else
(brace
macro_line|#ifdef KBD_REPORT_UNKN
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unknown scancode e0 %02x&bslash;n&quot;
comma
id|scancode
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|scancode
op_ge
id|SC_LIM
)paren
(brace
multiline_comment|/* This happens with the FOCUS 9000 keyboard&n;&t;       Its keys PF1..PF12 are reported to generate&n;&t;       55 73 77 78 79 7a 7b 7c 74 7e 6d 6f&n;&t;       Moreover, unless repeated, they do not generate&n;&t;       key-down events, so we have to zero up_flag below */
multiline_comment|/* Also, Japanese 86/106 keyboards are reported to&n;&t;       generate 0x73 and 0x7d for &bslash; - and &bslash; | respectively. */
multiline_comment|/* Also, some Brazilian keyboard is reported to produce&n;&t;       0x73 and 0x7e for &bslash; ? and KP-dot, respectively. */
op_star
id|keycode
op_assign
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|keycode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
(brace
macro_line|#ifdef KBD_REPORT_UNKN
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unrecognized scancode (%02x)&quot;
l_string|&quot; - ignored&bslash;n&quot;
comma
id|scancode
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
op_star
id|keycode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|q40kbd_unexpected_up
r_char
id|q40kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
multiline_comment|/* unexpected, but this can happen: maybe this was a key release for a&n;&t;   FOCUS 9000 PF key; if we want to see it, we have to clear up_flag */
r_if
c_cond
(paren
id|keycode
op_ge
id|SC_LIM
op_logical_or
id|keycode
op_eq
l_int|85
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|0200
suffix:semicolon
)brace
DECL|variable|keyup
r_static
r_int
id|keyup
op_assign
l_int|0
suffix:semicolon
DECL|variable|qprev
r_static
r_int
id|qprev
op_assign
l_int|0
suffix:semicolon
DECL|function|keyboard_interrupt
r_static
r_void
id|keyboard_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
id|disable_keyboard
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kbd_controller_lock
)paren
suffix:semicolon
id|kbd_pt_regs
op_assign
id|regs
suffix:semicolon
id|status
op_assign
id|IRQ_KEYB_MASK
op_amp
id|master_inb
c_func
(paren
id|INTERRUPT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_int
r_char
id|scancode
comma
id|qcode
suffix:semicolon
id|qcode
op_assign
id|master_inb
c_func
(paren
id|KEYCODE_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qcode
op_ne
l_int|0xf0
)paren
(brace
r_if
c_cond
(paren
id|qcode
op_eq
l_int|0xe0
)paren
(brace
id|qprev
op_assign
l_int|0xe0
suffix:semicolon
id|handle_scancode
c_func
(paren
id|qprev
comma
l_int|1
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|scancode
op_assign
id|qprev
ques
c_cond
id|q40ecl
(braket
id|qcode
)braket
suffix:colon
id|q40cl
(braket
id|qcode
)braket
suffix:semicolon
macro_line|#if 0
multiline_comment|/* next line is last resort to hanlde some oddities */
r_if
c_cond
(paren
id|qprev
op_logical_and
op_logical_neg
id|scancode
)paren
id|scancode
op_assign
id|q40cl
(braket
id|qcode
)braket
suffix:semicolon
macro_line|#endif
id|qprev
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scancode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unknown scancode %x&bslash;n&quot;
comma
id|qcode
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0xff
)paren
multiline_comment|/* SySrq */
id|scancode
op_assign
id|SYSRQ_KEY
suffix:semicolon
id|handle_scancode
c_func
(paren
id|scancode
comma
op_logical_neg
id|keyup
)paren
suffix:semicolon
id|keyup
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|KEYBOARD_BH
)paren
suffix:semicolon
)brace
r_else
id|keyup
op_assign
l_int|1
suffix:semicolon
)brace
m_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|kbd_controller_lock
)paren
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|KEYBOARD_UNLOCK_REG
)paren
suffix:semicolon
multiline_comment|/* keyb ints reenabled herewith */
id|enable_keyboard
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|function|kbd_is_sysrq
r_int
id|kbd_is_sysrq
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
r_return
id|keycode
op_eq
id|SYSRQ_KEY
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MAGIC_SYSRQ */
DECL|macro|KBD_NO_DATA
mdefine_line|#define KBD_NO_DATA&t;(-1)&t;/* No data */
DECL|macro|KBD_BAD_DATA
mdefine_line|#define KBD_BAD_DATA&t;(-2)&t;/* Parity or other error */
DECL|function|kbd_read_input
r_static
r_int
id|__init
id|kbd_read_input
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
id|KBD_NO_DATA
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
id|status
op_assign
id|IRQ_KEYB_MASK
op_amp
id|master_inb
c_func
(paren
id|INTERRUPT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_int
r_char
id|data
op_assign
id|master_inb
c_func
(paren
id|KEYCODE_REG
)paren
suffix:semicolon
id|retval
op_assign
id|data
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|KEYBOARD_UNLOCK_REG
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|q40kbd_leds
r_extern
r_void
id|q40kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
multiline_comment|/* nothing can be done */
)brace
DECL|function|kbd_clear_input
r_static
r_void
id|__init
id|kbd_clear_input
c_func
(paren
r_void
)paren
(brace
r_int
id|maxread
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Random number */
r_do
(brace
r_if
c_cond
(paren
id|kbd_read_input
c_func
(paren
)paren
op_eq
id|KBD_NO_DATA
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|maxread
)paren
suffix:semicolon
)brace
DECL|function|q40kbd_init_hw
r_void
id|__init
id|q40kbd_init_hw
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
multiline_comment|/* Get the keyboard controller registers (incomplete decode) */
id|request_region
c_func
(paren
l_int|0x60
comma
l_int|16
comma
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Flush any pending input. */
id|kbd_clear_input
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ok, finally allocate the IRQ, and off we go.. */
id|request_irq
c_func
(paren
id|Q40_IRQ_KEYBOARD
comma
id|keyboard_interrupt
comma
l_int|0
comma
l_string|&quot;keyboard&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|KEYBOARD_UNLOCK_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|KEY_IRQ_ENABLE_REG
)paren
suffix:semicolon
)brace
eof
