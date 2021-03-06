multiline_comment|/*&n; *  linux/lib/string.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * stupid library routines.. The optimized versions should generally be found&n; * as inline code in &lt;asm-xx/string.h&gt;&n; *&n; * These are buggy as well..&n; *&n; * * Fri Jun 25 1999, Ingo Oeser &lt;ioe@informatik.tu-chemnitz.de&gt;&n; * -  Added strsep() which will replace strtok() soon (because strsep() is&n; *    reentrant and should be faster). Use only strsep() in new code, please.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#ifndef __HAVE_ARCH_STRNICMP
DECL|function|strnicmp
r_int
id|strnicmp
c_func
(paren
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
comma
r_int
id|len
)paren
(brace
multiline_comment|/* Yes, Virginia, it had better be unsigned */
r_int
r_char
id|c1
comma
id|c2
suffix:semicolon
id|c1
op_assign
l_int|0
suffix:semicolon
id|c2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_do
(brace
id|c1
op_assign
op_star
id|s1
suffix:semicolon
id|c2
op_assign
op_star
id|s2
suffix:semicolon
id|s1
op_increment
suffix:semicolon
id|s2
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c2
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_eq
id|c2
)paren
r_continue
suffix:semicolon
id|c1
op_assign
id|tolower
c_func
(paren
id|c1
)paren
suffix:semicolon
id|c2
op_assign
id|tolower
c_func
(paren
id|c2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
)paren
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|c1
op_minus
(paren
r_int
)paren
id|c2
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|___strtok
r_char
op_star
id|___strtok
suffix:semicolon
macro_line|#ifndef __HAVE_ARCH_STRCPY
DECL|function|strcpy
r_char
op_star
id|strcpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCPY
DECL|function|strncpy
r_char
op_star
id|strncpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
op_logical_and
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCAT
DECL|function|strcat
r_char
op_star
id|strcat
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
op_star
id|dest
)paren
id|dest
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCAT
DECL|function|strncat
r_char
op_star
id|strncat
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_while
c_loop
(paren
op_star
id|dest
)paren
id|dest
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
op_eq
l_int|0
)paren
(brace
op_star
id|dest
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCMP
DECL|function|strcmp
r_int
id|strcmp
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_register
r_int
r_char
id|__res
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|__res
op_assign
op_star
id|cs
op_minus
op_star
id|ct
op_increment
)paren
op_ne
l_int|0
op_logical_or
op_logical_neg
op_star
id|cs
op_increment
)paren
r_break
suffix:semicolon
)brace
r_return
id|__res
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCMP
DECL|function|strncmp
r_int
id|strncmp
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
comma
r_int
id|count
)paren
(brace
r_register
r_int
r_char
id|__res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
(paren
id|__res
op_assign
op_star
id|cs
op_minus
op_star
id|ct
op_increment
)paren
op_ne
l_int|0
op_logical_or
op_logical_neg
op_star
id|cs
op_increment
)paren
r_break
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
id|__res
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCHR
DECL|function|strchr
r_char
op_star
id|strchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|s
op_ne
(paren
r_char
)paren
id|c
suffix:semicolon
op_increment
id|s
)paren
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRRCHR
DECL|function|strrchr
r_char
op_star
id|strrchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
(paren
r_char
)paren
id|c
)paren
r_return
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|p
op_ge
id|s
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRLEN
DECL|function|strlen
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_const
r_char
op_star
id|sc
suffix:semicolon
r_for
c_loop
(paren
id|sc
op_assign
id|s
suffix:semicolon
op_star
id|sc
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|sc
op_minus
id|s
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNLEN
DECL|function|strnlen
r_int
id|strnlen
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_const
r_char
op_star
id|sc
suffix:semicolon
r_for
c_loop
(paren
id|sc
op_assign
id|s
suffix:semicolon
id|count
op_decrement
op_logical_and
op_star
id|sc
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|sc
op_minus
id|s
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSPN
DECL|function|strspn
r_int
id|strspn
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_const
r_char
op_star
id|accept
)paren
(brace
r_const
r_char
op_star
id|p
suffix:semicolon
r_const
r_char
op_star
id|a
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|s
suffix:semicolon
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|p
)paren
(brace
r_for
c_loop
(paren
id|a
op_assign
id|accept
suffix:semicolon
op_star
id|a
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|a
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
op_star
id|a
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|a
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|count
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRPBRK
DECL|function|strpbrk
r_char
op_star
id|strpbrk
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_const
r_char
op_star
id|sc1
comma
op_star
id|sc2
suffix:semicolon
r_for
c_loop
(paren
id|sc1
op_assign
id|cs
suffix:semicolon
op_star
id|sc1
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc1
)paren
(brace
r_for
c_loop
(paren
id|sc2
op_assign
id|ct
suffix:semicolon
op_star
id|sc2
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc2
)paren
(brace
r_if
c_cond
(paren
op_star
id|sc1
op_eq
op_star
id|sc2
)paren
r_return
(paren
r_char
op_star
)paren
id|sc1
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRTOK
DECL|function|strtok
r_char
op_star
id|strtok
c_func
(paren
r_char
op_star
id|s
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_char
op_star
id|sbegin
comma
op_star
id|send
suffix:semicolon
id|sbegin
op_assign
id|s
ques
c_cond
id|s
suffix:colon
id|___strtok
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbegin
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|sbegin
op_add_assign
id|strspn
c_func
(paren
id|sbegin
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sbegin
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|___strtok
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|send
op_assign
id|strpbrk
c_func
(paren
id|sbegin
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|send
op_logical_and
op_star
id|send
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_star
id|send
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|___strtok
op_assign
id|send
suffix:semicolon
r_return
(paren
id|sbegin
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSEP
DECL|function|strsep
r_char
op_star
id|strsep
c_func
(paren
r_char
op_star
op_star
id|s
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_char
op_star
id|sbegin
op_assign
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbegin
)paren
r_return
l_int|NULL
suffix:semicolon
id|sbegin
op_add_assign
id|strspn
c_func
(paren
id|sbegin
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sbegin
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|s
op_assign
id|strpbrk
c_func
(paren
id|sbegin
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_logical_and
op_star
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_star
(paren
op_star
id|s
)paren
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
(paren
id|sbegin
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMSET
DECL|function|memset
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|xs
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|xs
op_increment
op_assign
id|c
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_BCOPY
DECL|function|bcopy
r_char
op_star
id|bcopy
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dest
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCPY
DECL|function|memcpy
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
comma
op_star
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMMOVE
DECL|function|memmove
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|tmp
comma
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|dest
op_le
id|src
)paren
(brace
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
suffix:semicolon
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
op_plus
id|count
suffix:semicolon
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
op_plus
id|count
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
op_decrement
id|tmp
op_assign
op_star
op_decrement
id|s
suffix:semicolon
)brace
r_return
id|dest
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCMP
DECL|function|memcmp
r_int
id|memcmp
c_func
(paren
r_const
r_void
op_star
id|cs
comma
r_const
r_void
op_star
id|ct
comma
r_int
id|count
)paren
(brace
r_const
r_int
r_char
op_star
id|su1
comma
op_star
id|su2
suffix:semicolon
r_int
r_char
id|res
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|su1
op_assign
id|cs
comma
id|su2
op_assign
id|ct
suffix:semicolon
l_int|0
OL
id|count
suffix:semicolon
op_increment
id|su1
comma
op_increment
id|su2
comma
id|count
op_decrement
)paren
r_if
c_cond
(paren
(paren
id|res
op_assign
op_star
id|su1
op_minus
op_star
id|su2
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * find the first occurrence of byte &squot;c&squot;, or 1 past the area if none&n; */
macro_line|#ifndef __HAVE_ARCH_MEMSCAN
DECL|function|memscan
r_void
op_star
id|memscan
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|c
comma
r_int
id|size
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
id|c
)paren
r_return
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSTR
DECL|function|strstr
r_char
op_star
id|strstr
c_func
(paren
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
)paren
(brace
r_int
id|l1
comma
id|l2
suffix:semicolon
id|l2
op_assign
id|strlen
c_func
(paren
id|s2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l2
)paren
r_return
(paren
r_char
op_star
)paren
id|s1
suffix:semicolon
id|l1
op_assign
id|strlen
c_func
(paren
id|s1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|l1
op_ge
id|l2
)paren
(brace
id|l1
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|s1
comma
id|s2
comma
id|l2
)paren
)paren
r_return
(paren
r_char
op_star
)paren
id|s1
suffix:semicolon
id|s1
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCHR
DECL|function|memchr
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|s
comma
r_int
id|c
comma
r_int
id|n
)paren
(brace
r_const
r_int
r_char
op_star
id|p
op_assign
id|s
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|c
op_eq
op_star
id|p
op_increment
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|p
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
