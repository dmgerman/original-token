multiline_comment|/* Support for the latches on the old Archimedes which control the floppy,&n; * hard disc and printer&n; *&n; * (c) David Alan Gilbert 1995/1996&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#ifdef LATCHAADDR
multiline_comment|/*&n; * They are static so that everyone who accesses them has to go through here&n; */
DECL|variable|LatchACopy
r_static
r_int
r_char
id|LatchACopy
suffix:semicolon
multiline_comment|/* newval=(oldval &amp; ~mask)|newdata */
DECL|function|oldlatch_aupdate
r_void
id|oldlatch_aupdate
c_func
(paren
r_int
r_char
id|mask
comma
r_int
r_char
id|newdata
)paren
(brace
id|LatchACopy
op_assign
(paren
id|LatchACopy
op_amp
op_complement
id|mask
)paren
op_or
id|newdata
suffix:semicolon
id|outb
c_func
(paren
id|LatchACopy
comma
id|LATCHAADDR
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;oldlatch_A:0x%2x&bslash;n&quot;
comma
id|LatchACopy
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef LATCHBADDR
DECL|variable|LatchBCopy
r_static
r_int
r_char
id|LatchBCopy
suffix:semicolon
multiline_comment|/* newval=(oldval &amp; ~mask)|newdata */
DECL|function|oldlatch_bupdate
r_void
id|oldlatch_bupdate
c_func
(paren
r_int
r_char
id|mask
comma
r_int
r_char
id|newdata
)paren
(brace
id|LatchBCopy
op_assign
(paren
id|LatchBCopy
op_amp
op_complement
id|mask
)paren
op_or
id|newdata
suffix:semicolon
id|outb
c_func
(paren
id|LatchBCopy
comma
id|LATCHBADDR
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;oldlatch_B:0x%2x&bslash;n&quot;
comma
id|LatchBCopy
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
DECL|function|oldlatch_init
r_void
id|oldlatch_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;oldlatch: init&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef LATCHAADDR
id|oldlatch_aupdate
c_func
(paren
l_int|0xff
comma
l_int|0xff
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LATCHBADDR
id|oldlatch_bupdate
c_func
(paren
l_int|0xff
comma
l_int|0x8
)paren
suffix:semicolon
multiline_comment|/* Thats no FDC reset...*/
macro_line|#endif
r_return
suffix:semicolon
)brace
eof
