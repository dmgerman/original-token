macro_line|#ifndef _ALPHA_TERMIOS_H
DECL|macro|_ALPHA_TERMIOS_H
mdefine_line|#define _ALPHA_TERMIOS_H
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
multiline_comment|/*&n; * c_cc characters in the termio structure.  Oh, how I love being&n; * backwardly compatible.  Notice that character 4 and 5 are&n; * interpreted differently depending on whether ICANON is set in&n; * c_lflag.  If it&squot;s set, they are used as _VEOF and _VEOL, otherwise&n; * as _VMIN and V_TIME.  This is for compatibility with OSF/1 (which&n; * is compatible with sysV)...&n; */
DECL|macro|_VINTR
mdefine_line|#define _VINTR&t;0
DECL|macro|_VQUIT
mdefine_line|#define _VQUIT&t;1
DECL|macro|_VERASE
mdefine_line|#define _VERASE&t;2
DECL|macro|_VKILL
mdefine_line|#define _VKILL&t;3
DECL|macro|_VEOF
mdefine_line|#define _VEOF&t;4
DECL|macro|_VMIN
mdefine_line|#define _VMIN&t;4
DECL|macro|_VEOL
mdefine_line|#define _VEOL&t;5
DECL|macro|_VTIME
mdefine_line|#define _VTIME&t;5
DECL|macro|_VEOL2
mdefine_line|#define _VEOL2&t;6
DECL|macro|_VSWTC
mdefine_line|#define _VSWTC&t;7
multiline_comment|/* line disciplines */
DECL|macro|N_TTY
mdefine_line|#define N_TTY&t;&t;0
DECL|macro|N_SLIP
mdefine_line|#define N_SLIP&t;&t;1
DECL|macro|N_MOUSE
mdefine_line|#define N_MOUSE&t;&t;2
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;&t;3
DECL|macro|N_AX25
mdefine_line|#define N_AX25&t;&t;5
macro_line|#ifdef __KERNEL__
multiline_comment|/*&t;eof=^D&t;&t;eol=&bslash;0&t;&t;eol2=&bslash;0&t;&t;erase=del&n;&t;werase=^W&t;kill=^U&t;&t;reprint=^R&t;sxtc=&bslash;0&n;&t;intr=^C&t;&t;quit=^&bslash;&t;&t;susp=^Z&t;&t;&lt;OSF/1 VDSUSP&gt;&n;&t;start=^Q&t;stop=^S&t;&t;lnext=^V&t;discard=^U&n;&t;vmin=&bslash;1&t;&t;vtime=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;004&bslash;000&bslash;000&bslash;177&bslash;027&bslash;025&bslash;022&bslash;000&bslash;003&bslash;034&bslash;032&bslash;000&bslash;021&bslash;023&bslash;026&bslash;025&bslash;001&bslash;000&quot;
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|SET_LOW_TERMIOS_BITS
mdefine_line|#define SET_LOW_TERMIOS_BITS(termios, termio, x) { &bslash;&n;&t;unsigned short __tmp; &bslash;&n;&t;get_user(__tmp,&amp;(termio)-&gt;x); &bslash;&n;&t;*(unsigned short *) &amp;(termios)-&gt;x = __tmp; &bslash;&n;}
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(termios, termio) &bslash;&n;do { &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_iflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_oflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_cflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_lflag); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VINTR], &amp;(termio)-&gt;c_cc[_VINTR]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VQUIT], &amp;(termio)-&gt;c_cc[_VQUIT]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VERASE], &amp;(termio)-&gt;c_cc[_VERASE]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VKILL], &amp;(termio)-&gt;c_cc[_VKILL]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VEOF], &amp;(termio)-&gt;c_cc[_VEOF]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VMIN], &amp;(termio)-&gt;c_cc[_VMIN]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VEOL], &amp;(termio)-&gt;c_cc[_VEOL]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VTIME], &amp;(termio)-&gt;c_cc[_VTIME]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VEOL2], &amp;(termio)-&gt;c_cc[_VEOL2]); &bslash;&n;&t;get_user((termios)-&gt;c_cc[VSWTC], &amp;(termio)-&gt;c_cc[_VSWTC]); &bslash;&n;} while(0)
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; *&n; * Note the &quot;fun&quot; _VMIN overloading.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(termio, termios) &bslash;&n;do { &bslash;&n;&t;put_user((termios)-&gt;c_iflag, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;put_user((termios)-&gt;c_oflag, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;put_user((termios)-&gt;c_cflag, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;put_user((termios)-&gt;c_lflag, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;put_user((termios)-&gt;c_line, &amp;(termio)-&gt;c_line); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VINTR], &amp;(termio)-&gt;c_cc[_VINTR]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VQUIT], &amp;(termio)-&gt;c_cc[_VQUIT]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VERASE], &amp;(termio)-&gt;c_cc[_VERASE]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VKILL], &amp;(termio)-&gt;c_cc[_VKILL]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VEOF], &amp;(termio)-&gt;c_cc[_VEOF]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VEOL], &amp;(termio)-&gt;c_cc[_VEOL]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VEOL2], &amp;(termio)-&gt;c_cc[_VEOL2]); &bslash;&n;&t;put_user((termios)-&gt;c_cc[VSWTC], &amp;(termio)-&gt;c_cc[_VSWTC]); &bslash;&n;&t;if (!((termios)-&gt;c_lflag &amp; ICANON)) { &bslash;&n;&t;&t;put_user((termios)-&gt;c_cc[VMIN], &amp;(termio)-&gt;c_cc[_VMIN]); &bslash;&n;&t;&t;put_user((termios)-&gt;c_cc[VTIME], &amp;(termio)-&gt;c_cc[_VTIME]); &bslash;&n;&t;} &bslash;&n;} while(0)
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) copy_from_user(k, u, sizeof(struct termios))
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) copy_to_user(u, k, sizeof(struct termios))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _ALPHA_TERMIOS_H */
eof
