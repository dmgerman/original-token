macro_line|#ifndef _LINUX_STRING_H_
DECL|macro|_LINUX_STRING_H_
mdefine_line|#define _LINUX_STRING_H_
macro_line|#include &lt;linux/types.h&gt;&t;/* for size_t */
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*&n; * Include machine specific inline routines&n; */
macro_line|#include &lt;asm/string.h&gt;
macro_line|#ifdef __USE_PORTABLE_STRINGS_H_
multiline_comment|/*&n; * include/generic/string.h imports all the string functions,&n; * for which no appropriate assembler replacements have been provided.&n; */
macro_line|#include &lt;asm-generic/string.h&gt;
macro_line|#endif
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_STRING_H_ */
eof
