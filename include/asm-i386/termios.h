macro_line|#ifndef _I386_TERMIOS_H
DECL|macro|_I386_TERMIOS_H
mdefine_line|#define _I386_TERMIOS_H
macro_line|#include &lt;asm/termbits.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
DECL|struct|winsize
r_struct
id|winsize
(brace
DECL|member|ws_row
r_int
r_int
id|ws_row
suffix:semicolon
DECL|member|ws_col
r_int
r_int
id|ws_col
suffix:semicolon
DECL|member|ws_xpixel
r_int
r_int
id|ws_xpixel
suffix:semicolon
DECL|member|ws_ypixel
r_int
r_int
id|ws_ypixel
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCC
mdefine_line|#define NCC 8
DECL|struct|termio
r_struct
id|termio
(brace
DECL|member|c_iflag
r_int
r_int
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
r_int
r_int
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
r_int
r_int
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
r_int
r_int
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
DECL|member|c_line
r_int
r_char
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
r_int
r_char
id|c_cc
(braket
id|NCC
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&t;intr=^C&t;&t;quit=^&bslash;&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;vtime=&bslash;0&t;vmin=&bslash;1&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;eol=&bslash;0&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;eol2=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;1&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;0&quot;
macro_line|#endif
multiline_comment|/* modem lines */
DECL|macro|TIOCM_LE
mdefine_line|#define TIOCM_LE&t;0x001
DECL|macro|TIOCM_DTR
mdefine_line|#define TIOCM_DTR&t;0x002
DECL|macro|TIOCM_RTS
mdefine_line|#define TIOCM_RTS&t;0x004
DECL|macro|TIOCM_ST
mdefine_line|#define TIOCM_ST&t;0x008
DECL|macro|TIOCM_SR
mdefine_line|#define TIOCM_SR&t;0x010
DECL|macro|TIOCM_CTS
mdefine_line|#define TIOCM_CTS&t;0x020
DECL|macro|TIOCM_CAR
mdefine_line|#define TIOCM_CAR&t;0x040
DECL|macro|TIOCM_RNG
mdefine_line|#define TIOCM_RNG&t;0x080
DECL|macro|TIOCM_DSR
mdefine_line|#define TIOCM_DSR&t;0x100
DECL|macro|TIOCM_CD
mdefine_line|#define TIOCM_CD&t;TIOCM_CAR
DECL|macro|TIOCM_RI
mdefine_line|#define TIOCM_RI&t;TIOCM_RNG
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
multiline_comment|/* line disciplines */
DECL|macro|N_TTY
mdefine_line|#define N_TTY&t;&t;0
DECL|macro|N_SLIP
mdefine_line|#define N_SLIP&t;&t;1
DECL|macro|N_MOUSE
mdefine_line|#define N_MOUSE&t;&t;2
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;&t;3
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|function|trans_from_termio
r_extern
r_inline
r_void
id|trans_from_termio
c_func
(paren
r_struct
id|termio
op_star
id|termio
comma
r_struct
id|termios
op_star
id|termios
)paren
(brace
DECL|macro|SET_LOW_BITS
mdefine_line|#define SET_LOW_BITS(x,y)&t;(*(unsigned short *)(&amp;x) = (y))
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_iflag
comma
id|termio-&gt;c_iflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_oflag
comma
id|termio-&gt;c_oflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_cflag
comma
id|termio-&gt;c_cflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_lflag
comma
id|termio-&gt;c_lflag
)paren
suffix:semicolon
DECL|macro|SET_LOW_BITS
macro_line|#undef SET_LOW_BITS
id|memcpy
c_func
(paren
id|termios-&gt;c_cc
comma
id|termio-&gt;c_cc
comma
id|NCC
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; */
DECL|function|trans_to_termio
r_extern
r_inline
r_void
id|trans_to_termio
c_func
(paren
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termio
op_star
id|termio
)paren
(brace
id|termio-&gt;c_iflag
op_assign
id|termios-&gt;c_iflag
suffix:semicolon
id|termio-&gt;c_oflag
op_assign
id|termios-&gt;c_oflag
suffix:semicolon
id|termio-&gt;c_cflag
op_assign
id|termios-&gt;c_cflag
suffix:semicolon
id|termio-&gt;c_lflag
op_assign
id|termios-&gt;c_lflag
suffix:semicolon
id|termio-&gt;c_line
op_assign
id|termios-&gt;c_line
suffix:semicolon
id|memcpy
c_func
(paren
id|termio-&gt;c_cc
comma
id|termios-&gt;c_cc
comma
id|NCC
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _I386_TERMIOS_H */
eof
