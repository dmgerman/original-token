multiline_comment|/* string.h: External definitions for optimized assembly string&n;             routines for the Linux Kernel.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
DECL|function|strlen
r_extern
id|__inline__
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
comma
id|tmp
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|str
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
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
comma
id|tmp2
suffix:semicolon
r_register
r_int
id|retval
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|str1
)paren
comma
l_string|&quot;r&quot;
(paren
id|str2
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
r_char
id|tmp1
comma
id|tmp2
suffix:semicolon
r_register
r_int
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cmp %3, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %5&bslash;n&bslash;t&quot;
l_string|&quot;1: ldub [%1], %4&bslash;n&bslash;t&quot;
l_string|&quot;sub %4, %5, %0&bslash;n&bslash;t&quot;
l_string|&quot;cmp %0, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp %4, 0x0&bslash;n&bslash;t&quot;
l_string|&quot;be 2f&bslash;n&bslash;t&quot;
l_string|&quot;add %1, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;addcc %3, -1, %3&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;ldub [%2], %5&bslash;n&bslash;t&quot;
l_string|&quot;2: &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|str1
)paren
comma
l_string|&quot;r&quot;
(paren
id|str2
)paren
comma
l_string|&quot;r&quot;
(paren
id|strlen
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|source
)paren
comma
l_string|&quot;r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;r&quot;
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;r&quot;
(paren
id|source
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;r&quot;
(paren
id|cpylen
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* extern __inline__ char *strcat(char *dest, char *src); */
multiline_comment|/* extern __inline__ char *strncat(char *dest, char *src, int len); */
multiline_comment|/* extern __inline__ char *strchr(char *src, char c); */
multiline_comment|/* extern __inline__ char *strpbrk(char *cs, char *ct); */
multiline_comment|/* extern __inline__ char *strtok(char *s, char *ct); */
multiline_comment|/* extern __inline__ int strspn(char *s, char *accept); */
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
r_char
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|src
)paren
comma
l_string|&quot;r&quot;
(paren
id|c
)paren
comma
l_string|&quot;r&quot;
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;r&quot;
(paren
id|src
)paren
comma
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;r&quot;
(paren
id|src
)paren
comma
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
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
