multiline_comment|/*&n; *  linux/lib/string.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef __GNUC__
macro_line|#error I want gcc!
macro_line|#endif
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef __cplusplus
DECL|macro|C_BEGIN
mdefine_line|#define C_BEGIN extern &quot;C&quot; {
DECL|macro|C_END
mdefine_line|#define C_END }
macro_line|#else
DECL|macro|C_BEGIN
mdefine_line|#define C_BEGIN
DECL|macro|C_END
mdefine_line|#define C_END
macro_line|#endif
DECL|macro|__cplusplus
macro_line|#undef __cplusplus
DECL|macro|extern
mdefine_line|#define extern
DECL|macro|inline
mdefine_line|#define inline
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
id|C_BEGIN
macro_line|#include &lt;linux/string.h&gt;
id|C_END
eof
