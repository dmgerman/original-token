multiline_comment|/*&n; * include/asm-mips/string.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1994, 1995  Waldorf Electronics&n; * written by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_STRING_H
DECL|macro|__ASM_MIPS_STRING_H
mdefine_line|#define __ASM_MIPS_STRING_H
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
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
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t$1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=r&quot;
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
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
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
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,%2,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t$1,2f&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,%1,1&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
suffix:colon
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
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP
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
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;lbu&bslash;t%2,(%0)&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$1,%2,2f&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;lbu&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
macro_line|#ifndef __R4000__
l_string|&quot;nop&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;move&bslash;t%2,$1&bslash;n&quot;
l_string|&quot;2:&bslash;tsubu&bslash;t%2,$1&bslash;n&quot;
l_string|&quot;3:&bslash;t.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=d&quot;
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
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t%3,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%2,2f&bslash;n&bslash;t&quot;
l_string|&quot;lbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,1&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$1,%3,3f&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%3,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&quot;
l_string|&quot;2:&bslash;tmove&bslash;t%3,$1&bslash;n&quot;
l_string|&quot;3:&bslash;tsubu&bslash;t%3,$1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=d&quot;
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
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
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
id|s
comma
r_int
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
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;1:&bslash;tsb&bslash;t%3,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t%0,%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|s
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
op_plus
id|count
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xs
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
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
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
comma
l_string|&quot;=r&quot;
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
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xto
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
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
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
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
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,-1(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,-1(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
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
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN
DECL|function|memscan
r_extern
id|__inline__
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
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|addr
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tbeqz&bslash;t%1,2f&bslash;n&bslash;t&quot;
l_string|&quot;lbu&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|addr
)paren
comma
l_string|&quot;1&quot;
(paren
id|size
)paren
comma
l_string|&quot;r&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MIPS_STRING_H */
eof
