macro_line|#ifndef __ASM_MIPS_TERMIOS_H
DECL|macro|__ASM_MIPS_TERMIOS_H
mdefine_line|#define __ASM_MIPS_TERMIOS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/termbits.h&gt;
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
multiline_comment|/* ----------------------------------------------------------------------- */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(termios, termio) &bslash;&n;do { &bslash;&n;&t;unsigned short tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;(termios)-&gt;c_iflag = (0xffff0000 &amp; ((termios)-&gt;c_iflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;(termios)-&gt;c_oflag = (0xffff0000 &amp; ((termios)-&gt;c_oflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;(termios)-&gt;c_cflag = (0xffff0000 &amp; ((termios)-&gt;c_cflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;(termios)-&gt;c_lflag = (0xffff0000 &amp; ((termios)-&gt;c_lflag)) | tmp; &bslash;&n;&t;get_user((termios)-&gt;c_line, &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_from_user((termios)-&gt;c_cc, (termio)-&gt;c_cc, NCC); &bslash;&n;} while(0)
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(termio, termios) &bslash;&n;do { &bslash;&n;&t;put_user((termios)-&gt;c_iflag, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;put_user((termios)-&gt;c_oflag, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;put_user((termios)-&gt;c_cflag, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;put_user((termios)-&gt;c_lflag, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;put_user((termios)-&gt;c_line, &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_to_user((termio)-&gt;c_cc, (termios)-&gt;c_cc, NCC); &bslash;&n;} while(0)
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) copy_from_user(k, u, sizeof(struct termios))
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) copy_to_user(u, k, sizeof(struct termios))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __ASM_MIPS_TERMIOS_H */
eof
