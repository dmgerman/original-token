multiline_comment|/* string.h: External definitions for optimized assembly string&n;             routines for the Linux Kernel.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
DECL|function|strlen
r_extern
r_inline
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_register
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_register
r_char
id|tmp
op_assign
l_int|0
suffix:semicolon
r_register
r_char
op_star
id|lstr
suffix:semicolon
id|lstr
op_assign
(paren
r_char
op_star
)paren
id|str
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;ldub [%1], %2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;orcc %2, %%g0, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %2&bslash;n&bslash;t&quot;
l_string|&quot;add %0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;orcc %2, %%g0, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|lstr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|lstr
)paren
comma
l_string|&quot;2&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strcmp
r_extern
id|__inline__
r_int
id|strcmp
c_func
(paren
r_const
r_char
op_star
id|str1
comma
r_const
r_char
op_star
id|str2
)paren
(brace
r_register
r_int
r_int
id|tmp1
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %4&bslash;n&bslash;t&quot;
l_string|&quot;1: add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, %4&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 2f&bslash;n&bslash;t&quot;
l_string|&quot;sub %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %4&bslash;n&bslash;t&quot;
l_string|&quot;b 3f&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;2: ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %4&bslash;n&bslash;t&quot;
l_string|&quot;sub %3, %4, %0&bslash;n&bslash;t&quot;
l_string|&quot;3: &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|str1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|str2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|str1
)paren
comma
l_string|&quot;2&quot;
(paren
id|str2
)paren
comma
l_string|&quot;3&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;4&quot;
(paren
id|tmp2
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strncmp
r_extern
id|__inline__
r_int
id|strncmp
c_func
(paren
r_const
r_char
op_star
id|str1
comma
r_const
r_char
op_star
id|str2
comma
r_int
id|strlen
)paren
(brace
r_register
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;sub %%g2, %%g3, %0&bslash;n&bslash;t&quot;
l_string|&quot;cmp %0, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp %%g2, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;addcc %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;2: &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|str1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|str2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|strlen
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|str1
)paren
comma
l_string|&quot;2&quot;
(paren
id|str2
)paren
comma
l_string|&quot;3&quot;
(paren
id|strlen
)paren
suffix:colon
l_string|&quot;%g2&quot;
comma
l_string|&quot;%g3&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strcpy
r_extern
id|__inline__
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
id|source
)paren
(brace
r_register
r_char
id|tmp
suffix:semicolon
r_register
r_char
op_star
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %2, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;1: stb %3, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%1], %3&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|source
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|source
)paren
comma
l_string|&quot;2&quot;
(paren
id|dest
)paren
comma
l_string|&quot;3&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strncpy
r_extern
id|__inline__
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
id|source
comma
r_int
id|cpylen
)paren
(brace
r_register
r_char
id|tmp
suffix:semicolon
r_register
r_char
op_star
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;1: cmp %4, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;stb %3, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;sub %4, 0x1, %4&bslash;n&bslash;t&quot;
l_string|&quot;ba 1&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|source
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|cpylen
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|dest
)paren
comma
l_string|&quot;2&quot;
(paren
id|source
)paren
comma
l_string|&quot;3&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;4&quot;
(paren
id|cpylen
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strcat
r_extern
id|__inline__
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
r_register
r_char
op_star
id|retval
suffix:semicolon
r_register
r_char
id|temp
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2: ldub [%2], %3&bslash;n&bslash;t&quot;
l_string|&quot;stb %3, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2b&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|dest
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|temp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strncat
r_extern
id|__inline__
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
id|len
)paren
(brace
r_register
r_char
op_star
id|retval
suffix:semicolon
r_register
r_char
id|temp
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2: ldub [%2], %3&bslash;n&bslash;t&quot;
l_string|&quot;stb %3, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2b&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|len
)paren
comma
l_string|&quot;=r&quot;
(paren
id|temp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|dest
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|len
)paren
comma
l_string|&quot;4&quot;
(paren
id|temp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|strchr
r_extern
id|__inline__
r_char
op_star
id|strchr
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
id|c
)paren
(brace
r_register
r_char
id|temp
op_assign
l_int|0
suffix:semicolon
r_register
r_char
op_star
id|trick
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;1: ldub [%0], %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp %2, %1&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %0, %3&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|c
)paren
comma
l_string|&quot;=r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|trick
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
)paren
comma
l_string|&quot;1&quot;
(paren
id|c
)paren
comma
l_string|&quot;2&quot;
(paren
id|temp
)paren
comma
l_string|&quot;3&quot;
(paren
id|trick
)paren
comma
l_string|&quot;4&quot;
(paren
id|src
)paren
)paren
suffix:semicolon
r_return
id|trick
suffix:semicolon
)brace
DECL|function|strpbrk
r_extern
id|__inline__
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
r_register
r_char
id|temp1
comma
id|temp2
suffix:semicolon
r_register
r_char
op_star
id|scratch
suffix:semicolon
r_register
r_char
op_star
id|trick
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %4&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%0], %2&bslash;n&bslash;t&quot;
l_string|&quot;2: ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, %2&bslash;n&bslash;t&quot;
l_string|&quot;be 3f&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %4, %1&bslash;n&bslash;t&quot;
l_string|&quot;b 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %0, %5&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cs
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ct
)paren
comma
l_string|&quot;r&quot;
(paren
id|temp1
)paren
comma
l_string|&quot;r&quot;
(paren
id|temp2
)paren
comma
l_string|&quot;r&quot;
(paren
id|scratch
)paren
comma
l_string|&quot;r&quot;
(paren
id|trick
op_assign
l_int|0
)paren
comma
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
id|trick
suffix:semicolon
)brace
DECL|function|strspn
r_extern
id|__inline__
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
r_register
r_char
id|temp1
comma
id|temp2
suffix:semicolon
r_register
r_char
op_star
id|scratch
suffix:semicolon
r_register
r_int
id|trick
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %4&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%0], %2&bslash;n&bslash;t&quot;
l_string|&quot;2: ldub [%1], %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 3f&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, %2&quot;
l_string|&quot;bne 2b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;add %0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;b 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %5, 0x1, %5&bslash;n&bslash;t&quot;
l_string|&quot;3: or %%g0, %0, %4&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|accept
)paren
comma
l_string|&quot;r&quot;
(paren
id|temp1
)paren
comma
l_string|&quot;r&quot;
(paren
id|temp2
)paren
comma
l_string|&quot;r&quot;
(paren
id|scratch
)paren
comma
l_string|&quot;r&quot;
(paren
id|trick
op_assign
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
id|s
)paren
)paren
suffix:semicolon
r_return
id|trick
suffix:semicolon
)brace
DECL|function|strtok
r_extern
id|__inline__
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
r_static
r_char
op_star
id|old
suffix:semicolon
multiline_comment|/* frob this kludge for now */
r_register
r_char
op_star
id|tok
suffix:semicolon
r_if
c_cond
(paren
id|s
op_eq
(paren
r_char
op_star
)paren
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|old
op_eq
(paren
r_char
op_star
)paren
l_int|0
)paren
(brace
r_return
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_else
id|s
op_assign
id|old
suffix:semicolon
)brace
id|s
op_add_assign
id|strspn
c_func
(paren
id|s
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|old
op_assign
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
)brace
id|tok
op_assign
id|s
suffix:semicolon
id|s
op_assign
id|strpbrk
c_func
(paren
id|tok
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_eq
(paren
r_char
op_star
)paren
l_int|0
)paren
id|old
op_assign
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
r_else
(brace
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|old
op_assign
id|s
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|tok
suffix:semicolon
)brace
DECL|function|memset
r_extern
id|__inline__
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|src
comma
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_register
r_void
op_star
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;1: add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2: add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, -1&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;stb %2, [%1]&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|c
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|c
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|memcpy
r_extern
id|__inline__
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
r_register
r_void
op_star
id|retval
suffix:semicolon
r_register
r_char
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, -1&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%2], %4&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, -1&bslash;n&bslash;t&quot;
l_string|&quot;stb %4, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2: &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|dest
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
comma
l_string|&quot;4&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|memmove
r_extern
id|__inline__
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
r_register
r_void
op_star
id|retval
suffix:semicolon
r_register
r_char
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %1&bslash;n&bslash;t&quot;
l_string|&quot;add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, -1&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%2], %4&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, -1&bslash;n&bslash;t&quot;
l_string|&quot;stb %4, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;2: &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|retval
)paren
comma
l_string|&quot;1&quot;
(paren
id|dest
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
comma
l_string|&quot;4&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|memcmp
r_extern
id|__inline__
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
r_register
r_int
id|retval
suffix:semicolon
r_register
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;ble,a 3f&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %4&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %5&bslash;n&bslash;t&quot;
l_string|&quot;cmp %4, %5&bslash;n&bslash;t&quot;
l_string|&quot;be,a 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;bgeu 3f&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;b 3f&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, -1, %0&bslash;n&bslash;t&quot;
l_string|&quot;2: add %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bg 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;3: &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|cs
)paren
comma
l_string|&quot;r&quot;
(paren
id|ct
)paren
comma
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp1
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp2
op_assign
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
