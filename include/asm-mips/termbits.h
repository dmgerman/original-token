macro_line|#ifndef __ASM_MIPS_TERMBITS_H
DECL|macro|__ASM_MIPS_TERMBITS_H
mdefine_line|#define __ASM_MIPS_TERMBITS_H
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
multiline_comment|/*&n; * The ABI says nothing about NCC but seems to use NCCS as&n; * replacement for it in struct termio&n; */
DECL|macro|NCC
mdefine_line|#define NCC&t;8
DECL|macro|NCCS
mdefine_line|#define NCCS&t;23
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
r_char
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
r_int
r_char
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
DECL|struct|termios
r_struct
id|termios
(brace
DECL|member|c_iflag
id|tcflag_t
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
id|tcflag_t
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
id|tcflag_t
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
id|tcflag_t
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
multiline_comment|/*&n;&t; * Seems nonexistant in the ABI, but Linux assumes existence ...&n;&t; */
DECL|member|c_line
id|cc_t
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_TERMBITS_H */
eof
