macro_line|#ifndef _M68K_STRING_H_
DECL|macro|_M68K_STRING_H_
mdefine_line|#define _M68K_STRING_H_
DECL|macro|__USE_PORTABLE_STRINGS_H_
mdefine_line|#define __USE_PORTABLE_STRINGS_H_
DECL|function|strcpy
r_extern
r_inline
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
id|xdest
op_assign
id|dest
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
DECL|function|strncpy
r_extern
r_inline
r_void
op_star
id|strncpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|n
)paren
(brace
r_char
op_star
id|xdest
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_return
id|xdest
suffix:semicolon
id|__asm__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;beq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%3&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|__USE_PORTABLE_strcat
mdefine_line|#define __USE_PORTABLE_strcat
DECL|macro|__USE_PORTABLE_strncat
mdefine_line|#define __USE_PORTABLE_strncat
DECL|function|strcmp
r_extern
r_inline
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
r_char
id|__res
suffix:semicolon
id|__asm__
(paren
l_string|&quot;1:&bslash;tmoveb %0@+,%2&bslash;n&bslash;t&quot;
multiline_comment|/* get *cs */
l_string|&quot;cmpb %1@+,%2&bslash;n&bslash;t&quot;
multiline_comment|/* compare a byte */
l_string|&quot;bne  2f&bslash;n&bslash;t&quot;
multiline_comment|/* not equal, break out */
l_string|&quot;tstb %2&bslash;n&bslash;t&quot;
multiline_comment|/* at end of cs? */
l_string|&quot;bne  1b&bslash;n&bslash;t&quot;
multiline_comment|/* no, keep going */
l_string|&quot;bra  3f&bslash;n&bslash;t&quot;
multiline_comment|/* strings are equal */
l_string|&quot;2:&bslash;tsubb %1@-,%2&bslash;n&bslash;t&quot;
multiline_comment|/* *cs - *ct */
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ct
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|ct
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|function|strncmp
r_extern
r_inline
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
r_char
id|__res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
(paren
l_string|&quot;1:&bslash;tmovb %0@+,%3&bslash;n&bslash;t&quot;
multiline_comment|/* get *cs */
l_string|&quot;cmpb   %1@+,%3&bslash;n&bslash;t&quot;
multiline_comment|/* compare a byte */
l_string|&quot;bne    3f&bslash;n&bslash;t&quot;
multiline_comment|/* not equal, break out */
l_string|&quot;tstb   %3&bslash;n&bslash;t&quot;
multiline_comment|/* at end of cs? */
l_string|&quot;beq    4f&bslash;n&bslash;t&quot;
multiline_comment|/* yes, all done */
l_string|&quot;subql  #1,%2&bslash;n&bslash;t&quot;
multiline_comment|/* no, adjust count */
l_string|&quot;bne    1b&bslash;n&bslash;t&quot;
multiline_comment|/* more to do, keep going */
l_string|&quot;2:&bslash;tmoveq #0,%3&bslash;n&bslash;t&quot;
multiline_comment|/* strings are equal */
l_string|&quot;bra    4f&bslash;n&bslash;t&quot;
l_string|&quot;3:&bslash;tsubb %1@-,%3&bslash;n&bslash;t&quot;
multiline_comment|/* *cs - *ct */
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ct
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|ct
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__USE_PORTABLE_strchr
mdefine_line|#define __USE_PORTABLE_strchr
DECL|macro|__USE_PORTABLE_strlen
mdefine_line|#define __USE_PORTABLE_strlen
DECL|macro|__USE_PORTABLE_strspn
mdefine_line|#define __USE_PORTABLE_strspn
DECL|macro|__USE_PORTABLE_strpbrk
mdefine_line|#define __USE_PORTABLE_strpbrk
DECL|macro|__USE_PORTABLE_strtok
mdefine_line|#define __USE_PORTABLE_strtok
DECL|function|memset
r_extern
r_inline
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|c
comma
r_int
id|count
)paren
(brace
r_void
op_star
id|xs
op_assign
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
id|xs
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %3,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
comma
l_string|&quot;d&quot;
(paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xs
suffix:semicolon
)brace
DECL|function|memcpy
r_extern
r_inline
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_void
op_star
id|xto
op_assign
id|to
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
id|xto
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xto
suffix:semicolon
)brace
DECL|function|memmove
r_extern
r_inline
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
id|n
)paren
(brace
r_void
op_star
id|xdest
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
id|xdest
suffix:semicolon
r_if
c_cond
(paren
id|dest
OL
id|src
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
op_plus
id|n
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
op_plus
id|n
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
DECL|macro|__USE_PORTABLE_memcmp
mdefine_line|#define __USE_PORTABLE_memcmp
DECL|macro|__USE_PORTABLE_memscan
mdefine_line|#define __USE_PORTABLE_memscan
macro_line|#endif /* _M68K_STRING_H_ */
eof
