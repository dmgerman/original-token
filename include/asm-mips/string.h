multiline_comment|/* $Id: string.h,v 1.6 1998/07/20 17:52:21 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1994, 1995, 1996, 1997, 1998 by Ralf Baechle&n; */
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
id|__dest
comma
id|__const__
r_char
op_star
id|__src
)paren
(brace
r_char
op_star
id|__xdest
op_assign
id|__dest
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
id|__dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__src
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|__src
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|__xdest
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
id|__dest
comma
id|__const__
r_char
op_star
id|__src
comma
r_int
id|__n
)paren
(brace
r_char
op_star
id|__xdest
op_assign
id|__dest
suffix:semicolon
r_if
c_cond
(paren
id|__n
op_eq
l_int|0
)paren
r_return
id|__xdest
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tlbu&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2,1&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$1,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t$1,2f&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%2,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%1,1&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|__src
)paren
comma
l_string|&quot;2&quot;
(paren
id|__n
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|__dest
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
id|__const__
r_char
op_star
id|__cs
comma
id|__const__
r_char
op_star
id|__ct
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
macro_line|#if _MIPS_ISA == _MIPS_ISA_MIPS1
l_string|&quot;nop&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;move&bslash;t%2,$1&bslash;n&quot;
l_string|&quot;2:&bslash;tsubu&bslash;t%2,$1&bslash;n&quot;
l_string|&quot;3:&bslash;t.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|__ct
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
id|__const__
r_char
op_star
id|__cs
comma
id|__const__
r_char
op_star
id|__ct
comma
r_int
id|__count
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
l_string|&quot;=r&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;2&quot;
(paren
id|__count
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
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|__s
comma
r_int
id|__c
comma
r_int
id|__count
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|__to
comma
id|__const__
r_void
op_star
id|__from
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|__dest
comma
id|__const__
r_void
op_star
id|__src
comma
r_int
id|__n
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t build bcopy at all ...  */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
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
id|__addr
comma
r_int
id|__c
comma
r_int
id|__size
)paren
(brace
r_char
op_star
id|__end
op_assign
(paren
r_char
op_star
)paren
id|__addr
op_plus
id|__size
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tbeq&bslash;t%0,%1,2f&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;lb&bslash;t$1,-1(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$1,%4,1b&bslash;n&quot;
l_string|&quot;2:&bslash;t.set&bslash;tat&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__addr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__end
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__addr
)paren
comma
l_string|&quot;1&quot;
(paren
id|__end
)paren
comma
l_string|&quot;r&quot;
(paren
id|__c
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_return
id|__addr
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MIPS_STRING_H */
eof
