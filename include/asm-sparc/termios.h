multiline_comment|/* $Id: termios.h,v 1.13 1996/04/04 12:51:30 davem Exp $ */
macro_line|#ifndef _SPARC_TERMIOS_H
DECL|macro|_SPARC_TERMIOS_H
mdefine_line|#define _SPARC_TERMIOS_H
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/termbits.h&gt;
DECL|struct|sgttyb
r_struct
id|sgttyb
(brace
DECL|member|sg_ispeed
r_char
id|sg_ispeed
suffix:semicolon
DECL|member|sg_ospeed
r_char
id|sg_ospeed
suffix:semicolon
DECL|member|sg_erase
r_char
id|sg_erase
suffix:semicolon
DECL|member|sg_kill
r_char
id|sg_kill
suffix:semicolon
DECL|member|sg_flags
r_int
id|sg_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tchars
r_struct
id|tchars
(brace
DECL|member|t_intrc
r_char
id|t_intrc
suffix:semicolon
DECL|member|t_quitc
r_char
id|t_quitc
suffix:semicolon
DECL|member|t_startc
r_char
id|t_startc
suffix:semicolon
DECL|member|t_stopc
r_char
id|t_stopc
suffix:semicolon
DECL|member|t_eofc
r_char
id|t_eofc
suffix:semicolon
DECL|member|t_brkc
r_char
id|t_brkc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ltchars
r_struct
id|ltchars
(brace
DECL|member|t_suspc
r_char
id|t_suspc
suffix:semicolon
DECL|member|t_dsuspc
r_char
id|t_dsuspc
suffix:semicolon
DECL|member|t_rprntc
r_char
id|t_rprntc
suffix:semicolon
DECL|member|t_flushc
r_char
id|t_flushc
suffix:semicolon
DECL|member|t_werasc
r_char
id|t_werasc
suffix:semicolon
DECL|member|t_lnextc
r_char
id|t_lnextc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sunos_ttysize
r_struct
id|sunos_ttysize
(brace
DECL|member|st_lines
r_int
id|st_lines
suffix:semicolon
multiline_comment|/* Lines on the terminal */
DECL|member|st_columns
r_int
id|st_columns
suffix:semicolon
multiline_comment|/* Columns on the terminal */
)brace
suffix:semicolon
multiline_comment|/* Used for packet mode */
DECL|macro|TIOCPKT_DATA
mdefine_line|#define TIOCPKT_DATA&t;&t; 0
DECL|macro|TIOCPKT_FLUSHREAD
mdefine_line|#define TIOCPKT_FLUSHREAD&t; 1
DECL|macro|TIOCPKT_FLUSHWRITE
mdefine_line|#define TIOCPKT_FLUSHWRITE&t; 2
DECL|macro|TIOCPKT_STOP
mdefine_line|#define TIOCPKT_STOP&t;&t; 4
DECL|macro|TIOCPKT_START
mdefine_line|#define TIOCPKT_START&t;&t; 8
DECL|macro|TIOCPKT_NOSTOP
mdefine_line|#define TIOCPKT_NOSTOP&t;&t;16
DECL|macro|TIOCPKT_DOSTOP
mdefine_line|#define TIOCPKT_DOSTOP&t;&t;32
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
multiline_comment|/*&t;intr=^C&t;&t;quit=^&bslash;&t;&t;erase=del&t;kill=^U&n;&t;eof/vmin=&bslash;1&t;eol/vtime=&bslash;0&t;eol2=&bslash;0&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;dsusp=^Y&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;001&bslash;000&bslash;000&bslash;000&bslash;021&bslash;023&bslash;032&bslash;031&bslash;022&bslash;025&bslash;027&bslash;026&quot;
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
mdefine_line|#define SET_LOW_BITS(x,y)&t;((x) = (0xffff0000 &amp; (x)) | (y))
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
macro_line|#endif /* _SPARC_TERMIOS_H */
eof
