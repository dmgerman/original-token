macro_line|#ifndef _LINUX_CTYPE_H
DECL|macro|_LINUX_CTYPE_H
mdefine_line|#define _LINUX_CTYPE_H
DECL|macro|_U
mdefine_line|#define _U&t;0x01&t;/* upper */
DECL|macro|_L
mdefine_line|#define _L&t;0x02&t;/* lower */
DECL|macro|_D
mdefine_line|#define _D&t;0x04&t;/* digit */
DECL|macro|_C
mdefine_line|#define _C&t;0x08&t;/* cntrl */
DECL|macro|_P
mdefine_line|#define _P&t;0x10&t;/* punct */
DECL|macro|_S
mdefine_line|#define _S&t;0x20&t;/* white space (space/lf/tab) */
DECL|macro|_X
mdefine_line|#define _X&t;0x40&t;/* hex digit */
DECL|macro|_SP
mdefine_line|#define _SP&t;0x80&t;/* hard space (0x20) */
r_extern
r_int
r_char
id|_ctype
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_ctmp
suffix:semicolon
DECL|macro|isalnum
mdefine_line|#define isalnum(c) ((_ctype+1)[c]&amp;(_U|_L|_D))
DECL|macro|isalpha
mdefine_line|#define isalpha(c) ((_ctype+1)[c]&amp;(_U|_L))
DECL|macro|iscntrl
mdefine_line|#define iscntrl(c) ((_ctype+1)[c]&amp;(_C))
DECL|macro|isdigit
mdefine_line|#define isdigit(c) ((_ctype+1)[c]&amp;(_D))
DECL|macro|isgraph
mdefine_line|#define isgraph(c) ((_ctype+1)[c]&amp;(_P|_U|_L|_D))
DECL|macro|islower
mdefine_line|#define islower(c) ((_ctype+1)[c]&amp;(_L))
DECL|macro|isprint
mdefine_line|#define isprint(c) ((_ctype+1)[c]&amp;(_P|_U|_L|_D|_SP))
DECL|macro|ispunct
mdefine_line|#define ispunct(c) ((_ctype+1)[c]&amp;(_P))
DECL|macro|isspace
mdefine_line|#define isspace(c) ((_ctype+1)[c]&amp;(_S))
DECL|macro|isupper
mdefine_line|#define isupper(c) ((_ctype+1)[c]&amp;(_U))
DECL|macro|isxdigit
mdefine_line|#define isxdigit(c) ((_ctype+1)[c]&amp;(_D|_X))
DECL|macro|isascii
mdefine_line|#define isascii(c) (((unsigned) c)&lt;=0x7f)
DECL|macro|toascii
mdefine_line|#define toascii(c) (((unsigned) c)&amp;0x7f)
DECL|macro|tolower
mdefine_line|#define tolower(c) (_ctmp=c,isupper(_ctmp)?_ctmp-(&squot;A&squot;-&squot;a&squot;):_ctmp)
DECL|macro|toupper
mdefine_line|#define toupper(c) (_ctmp=c,islower(_ctmp)?_ctmp-(&squot;a&squot;-&squot;A&squot;):_ctmp)
macro_line|#endif
eof
