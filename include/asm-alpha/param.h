macro_line|#ifndef _ASMAXP_PARAM_H
DECL|macro|_ASMAXP_PARAM_H
mdefine_line|#define _ASMAXP_PARAM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef HZ
macro_line|# if defined(CONFIG_ALPHA_EB66) || defined(CONFIG_ALPHA_EB66P) || &bslash;&n;     defined(CONFIG_ALPHA_EB64) || defined(CONFIG_ALPHA_EB64P)
DECL|macro|HZ
macro_line|#  define HZ&t; 977&t;/* Evaluation Boards seem to be a little odd */
macro_line|# else
DECL|macro|HZ
macro_line|#  define HZ&t;1024&t;/* normal value for Alpha systems */
macro_line|# endif
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;8192
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS&t;&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif
eof
