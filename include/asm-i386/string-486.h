macro_line|#ifndef _I386_STRING_I486_H_
DECL|macro|_I386_STRING_I486_H_
mdefine_line|#define _I386_STRING_I486_H_
multiline_comment|/*&n; * This string-include defines all string functions as inline&n; * functions. Use gcc. It also assumes ds=es=data space, this should be&n; * normal. Most of the string-functions are rather heavily hand-optimized,&n; * see especially strtok,strstr,str[c]spn. They should work, but are not&n; * very easy to understand. Everything is done entirely within the register&n; * set, making the functions fast and clean. &n; *&n; *&t;&t;Copyright (C) 1991, 1992 Linus Torvalds&n; *&t;&t;Revised and optimized for i486/pentium&n; *&t;&t;1994/03/15 by Alberto Vignani/Davide Parodi @crf.it&n; *&n; *&t;Split into 2 CPU specific files by Alan Cox to keep #ifdef noise down.&n; */
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
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
r_register
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
suffix:semicolon
r_register
r_char
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;movb (%0),%2&bslash;n&bslash;t&quot;
l_string|&quot;incl %0&bslash;n&bslash;t&quot;
l_string|&quot;movb %2,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;testb %2,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=q&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|function|strncpy
r_extern
r_inline
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
r_register
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
suffix:semicolon
r_register
r_char
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;movb (%0),%2&bslash;n&bslash;t&quot;
l_string|&quot;incl %0&bslash;n&bslash;t&quot;
l_string|&quot;movb %2,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;decl %3&bslash;n&bslash;t&quot;
l_string|&quot;je 3f&bslash;n&bslash;t&quot;
l_string|&quot;testb %2,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;tmovb %2,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;decl %3&bslash;n&bslash;t&quot;
l_string|&quot;jne 2b&bslash;n&bslash;t&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|src
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=q&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* if (count) */
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT
DECL|function|strcat
r_extern
r_inline
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
id|tmp
op_assign
(paren
r_char
op_star
)paren
(paren
id|dest
op_minus
l_int|1
)paren
suffix:semicolon
r_register
r_char
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;tincl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tmovb (%2),%b0&bslash;n&bslash;t&quot;
l_string|&quot;incl %2&bslash;n&bslash;t&quot;
l_string|&quot;movb %b0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;testb %b0,%b0&bslash;n&bslash;t&quot;
l_string|&quot;jne 2b&bslash;n&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCAT
mdefine_line|#define __HAVE_ARCH_STRNCAT
DECL|function|strncat
r_extern
r_inline
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
r_register
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
(paren
id|dest
op_minus
l_int|1
)paren
suffix:semicolon
r_register
r_char
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;tincl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %3&bslash;n&bslash;t&quot;
l_string|&quot;js 3f&bslash;n&bslash;t&quot;
l_string|&quot;movb (%2),%b0&bslash;n&bslash;t&quot;
l_string|&quot;incl %2&bslash;n&bslash;t&quot;
l_string|&quot;movb %b0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;testb %b0,%b0&bslash;n&bslash;t&quot;
l_string|&quot;jne 2b&bslash;n&quot;
l_string|&quot;3:&bslash;txorl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;movb %b0,(%1)&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
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
suffix:colon
l_string|&quot;1&quot;
(paren
id|tmp
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
suffix:colon
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
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;tmovb (%1),%b0&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb %b0,(%2)&bslash;n&bslash;t&quot;
l_string|&quot;jne 2f&bslash;n&bslash;t&quot;
l_string|&quot;incl %2&bslash;n&bslash;t&quot;
l_string|&quot;testb %b0,%b0&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;jmp 3f&bslash;n&quot;
l_string|&quot;2:&bslash;tmovl $1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jb 3f&bslash;n&bslash;t&quot;
l_string|&quot;negl %0&bslash;n&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|cs
)paren
comma
l_string|&quot;2&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;memory&quot;
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
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;tdecl %3&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;movb (%1),%b0&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb %b0,(%2)&bslash;n&bslash;t&quot;
l_string|&quot;jne 3f&bslash;n&bslash;t&quot;
l_string|&quot;incl %2&bslash;n&bslash;t&quot;
l_string|&quot;testb %b0,%b0&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;txorl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;jmp 4f&bslash;n&quot;
l_string|&quot;3:&bslash;tmovl $1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jb 4f&bslash;n&bslash;t&quot;
l_string|&quot;negl %0&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ct
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|cs
)paren
comma
l_string|&quot;2&quot;
(paren
id|ct
)paren
comma
l_string|&quot;3&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR
DECL|function|strchr
r_extern
r_inline
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
r_register
r_char
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movb %%al,%%ah&bslash;n&quot;
l_string|&quot;1:&bslash;tmovb (%1),%%al&bslash;n&bslash;t&quot;
l_string|&quot;cmpb %%ah,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;xorl %1,%1&bslash;n&quot;
l_string|&quot;2:&bslash;tmovl %1,%0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR
DECL|function|strrchr
r_extern
r_inline
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
r_register
r_char
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movb %%al,%%ah&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;cmpb %%ah,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 2f&bslash;n&bslash;t&quot;
l_string|&quot;leal -1(%%esi),%0&bslash;n&quot;
l_string|&quot;2:&bslash;ttestb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;S&quot;
(paren
id|s
)paren
comma
l_string|&quot;a&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRSPN
mdefine_line|#define __HAVE_ARCH_STRSPN
DECL|function|strspn
r_extern
r_inline
r_int
id|strspn
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
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;je 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&quot;
suffix:colon
l_string|&quot;=S&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0xffffffff
)paren
comma
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_return
id|__res
op_minus
id|cs
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRCSPN
mdefine_line|#define __HAVE_ARCH_STRCSPN
DECL|function|strcspn
r_extern
r_inline
r_int
id|strcspn
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
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&quot;
suffix:colon
l_string|&quot;=S&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0xffffffff
)paren
comma
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_return
id|__res
op_minus
id|cs
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRPBRK
mdefine_line|#define __HAVE_ARCH_STRPBRK
DECL|function|strpbrk
r_extern
r_inline
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
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;decl %0&bslash;n&bslash;t&quot;
l_string|&quot;jmp 3f&bslash;n&quot;
l_string|&quot;2:&bslash;txorl %0,%0&bslash;n&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=S&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0xffffffff
)paren
comma
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRSTR
mdefine_line|#define __HAVE_ARCH_STRSTR
DECL|function|strstr
r_extern
r_inline
r_char
op_star
id|strstr
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
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
multiline_comment|/* NOTE! This also sets Z if searchstring=&squot;&squot; */
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tmovl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%esi,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repe&bslash;n&bslash;t&quot;
l_string|&quot;cmpsb&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
multiline_comment|/* also works for empty string, see above */
l_string|&quot;xchgl %%eax,%%esi&bslash;n&bslash;t&quot;
l_string|&quot;incl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,-1(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;xorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0xffffffff
)paren
comma
l_string|&quot;S&quot;
(paren
id|cs
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
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
id|s
)paren
(brace
multiline_comment|/*&n; * slightly slower on a 486, but with better chances of&n; * register allocation&n; */
r_register
r_char
id|dummy
comma
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;movb&bslash;t(%0),%1&bslash;n&bslash;t&quot;
l_string|&quot;incl&bslash;t%0&bslash;n&bslash;t&quot;
l_string|&quot;testb&bslash;t%1,%1&bslash;n&bslash;t&quot;
l_string|&quot;jne&bslash;t1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=q&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|tmp
op_minus
id|s
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Added by Gertjan van Wingerde to make minix and sysv module work */
DECL|macro|__HAVE_ARCH_STRNLEN
mdefine_line|#define __HAVE_ARCH_STRNLEN
DECL|function|strnlen
r_extern
r_inline
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
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jmp 2f&bslash;n&quot;
l_string|&quot;1:&bslash;tcmpb $0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;je 3f&bslash;n&bslash;t&quot;
l_string|&quot;incl %0&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %2&bslash;n&bslash;t&quot;
l_string|&quot;cmpl $-1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;3:&bslash;tsubl %1,%0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
id|s
)paren
comma
l_string|&quot;d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/* end of additional stuff */
DECL|macro|__HAVE_ARCH_STRTOK
mdefine_line|#define __HAVE_ARCH_STRTOK
DECL|function|strtok
r_extern
r_inline
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
r_register
r_char
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;testl %1,%1&bslash;n&bslash;t&quot;
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;testl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;je 8f&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,%1&bslash;n&quot;
l_string|&quot;1:&bslash;txorl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;movl $-1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;xorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;je 7f&bslash;n&bslash;t&quot;
multiline_comment|/* empty delimiter-string */
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;2:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 7f&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;je 2b&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;je 7f&bslash;n&bslash;t&quot;
l_string|&quot;movl %1,%0&bslash;n&quot;
l_string|&quot;3:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;je 5f&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 3b&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;je 5f&bslash;n&bslash;t&quot;
l_string|&quot;movb $0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;jmp 6f&bslash;n&quot;
l_string|&quot;5:&bslash;txorl %1,%1&bslash;n&quot;
l_string|&quot;6:&bslash;tcmpb $0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;jne 7f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;7:&bslash;ttestl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;jne 8f&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,%1&bslash;n&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=S&quot;
(paren
id|___strtok
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|___strtok
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__memcpy_c
mdefine_line|#define __memcpy_c(d,s,count) &bslash;&n;((count%4==0) ? &bslash;&n; __memcpy_by4((d),(s),(count)) : &bslash;&n; ((count%2==0) ? &bslash;&n;  __memcpy_by2((d),(s),(count)) : &bslash;&n;  __memcpy_g((d),(s),(count))))
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|macro|memcpy
mdefine_line|#define memcpy(d,s,count) &bslash;&n;(__builtin_constant_p(count) ? &bslash;&n; __memcpy_c((d),(s),(count)) : &bslash;&n; __memcpy_g((d),(s),(count)))
multiline_comment|/*&n; *&t;These ought to get tweaked to do some cache priming.&n; */
DECL|function|__memcpy_by4
r_extern
r_inline
r_void
op_star
id|__memcpy_by4
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|to
suffix:semicolon
r_register
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n1:&bslash;tmovl (%2),%0&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%2&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%1&bslash;n&bslash;t&quot;
l_string|&quot;decl %3&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;2&quot;
(paren
id|from
)paren
comma
l_string|&quot;3&quot;
(paren
id|n
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
DECL|function|__memcpy_by2
r_extern
r_inline
r_void
op_star
id|__memcpy_by2
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|to
suffix:semicolon
r_register
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;shrl $1,%3&bslash;n&bslash;t&quot;
l_string|&quot;jz 2f&bslash;n&quot;
multiline_comment|/* only a word */
l_string|&quot;1:&bslash;tmovl (%2),%0&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%2&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%1&bslash;n&bslash;t&quot;
l_string|&quot;decl %3&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tmovw (%2),%w0&bslash;n&bslash;t&quot;
l_string|&quot;movw %w0,(%1)&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;2&quot;
(paren
id|from
)paren
comma
l_string|&quot;3&quot;
(paren
id|n
op_div
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
DECL|function|__memcpy_g
r_extern
r_inline
r_void
op_star
id|__memcpy_g
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|to
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;tshrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;trep&bslash;n&bslash;t&quot;
l_string|&quot;movsl&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|n
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|tmp
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|from
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|dest
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
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;movsb&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|n
)paren
comma
l_string|&quot;S&quot;
(paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;std&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&bslash;t&quot;
l_string|&quot;cld&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|n
)paren
comma
l_string|&quot;S&quot;
(paren
id|n
op_minus
l_int|1
op_plus
(paren
r_const
r_char
op_star
)paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|n
op_minus
l_int|1
op_plus
(paren
r_char
op_star
)paren
id|tmp
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|function|memcmp
r_extern
r_inline
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
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;repe&bslash;n&bslash;t&quot;
l_string|&quot;cmpsb&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;sbbl %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;orb $1,%b0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=abd&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;S&quot;
(paren
id|cs
)paren
comma
l_string|&quot;D&quot;
(paren
id|ct
)paren
comma
l_string|&quot;c&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR
DECL|function|memchr
r_extern
r_inline
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|cs
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
id|__res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|NULL
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;movl $1,%0&bslash;n&quot;
l_string|&quot;1:&bslash;tdecl %0&quot;
suffix:colon
l_string|&quot;=D&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|c
)paren
comma
l_string|&quot;D&quot;
(paren
id|cs
)paren
comma
l_string|&quot;c&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__memset_cc
mdefine_line|#define __memset_cc(s,c,count) &bslash;&n;((count%4==0) ? &bslash;&n; __memset_cc_by4((s),(c),(count)) : &bslash;&n; ((count%2==0) ? &bslash;&n;  __memset_cc_by2((s),(c),(count)) : &bslash;&n;  __memset_cg((s),(c),(count))))
DECL|macro|__memset_gc
mdefine_line|#define __memset_gc(s,c,count) &bslash;&n;((count%4==0) ? &bslash;&n; __memset_gc_by4((s),(c),(count)) : &bslash;&n; ((count%2==0) ? &bslash;&n;  __memset_gc_by2((s),(c),(count)) : &bslash;&n;  __memset_gg((s),(c),(count))))
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|memset
mdefine_line|#define memset(s,c,count) &bslash;&n;(__builtin_constant_p(c) ? &bslash;&n; (__builtin_constant_p(count) ? &bslash;&n;  __memset_cc((s),(c),(count)) : &bslash;&n;  __memset_cg((s),(c),(count))) : &bslash;&n; (__builtin_constant_p(count) ? &bslash;&n;  __memset_gc((s),(c),(count)) : &bslash;&n;  __memset_gg((s),(c),(count))))
DECL|function|__memset_cc_by4
r_extern
r_inline
r_void
op_star
id|__memset_cc_by4
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
multiline_comment|/*&n; * register char *tmp = s;&n; */
r_register
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_register
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n1:&bslash;tmovl %2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%0&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
l_int|0x01010101UL
op_star
(paren
r_int
r_char
)paren
id|c
)paren
comma
l_string|&quot;0&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__memset_cc_by2
r_extern
r_inline
r_void
op_star
id|__memset_cc_by2
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|s
suffix:semicolon
r_register
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;shrl $1,%1&bslash;n&bslash;t&quot;
multiline_comment|/* may be divisible also by 4 */
l_string|&quot;jz 2f&bslash;n&quot;
l_string|&quot;&bslash;n1:&bslash;tmovl %2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%0&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tmovw %w2,(%0)&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;q&quot;
(paren
l_int|0x01010101UL
op_star
(paren
r_int
r_char
)paren
id|c
)paren
comma
l_string|&quot;0&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
op_div
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__memset_gc_by4
r_extern
r_inline
r_void
op_star
id|__memset_gc_by4
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|s
suffix:semicolon
r_register
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movb %b0,%h0&bslash;n&quot;
l_string|&quot;pushw %w0&bslash;n&bslash;t&quot;
l_string|&quot;shll $16,%0&bslash;n&bslash;t&quot;
l_string|&quot;popw %w0&bslash;n&quot;
l_string|&quot;1:&bslash;tmovl %0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%1&bslash;n&bslash;t&quot;
l_string|&quot;decl %2&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&bslash;n&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|c
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_int
)paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__memset_gc_by2
r_extern
r_inline
r_void
op_star
id|__memset_gc_by2
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|s
suffix:semicolon
r_register
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movb %b0,%h0&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%2&bslash;n&bslash;t&quot;
multiline_comment|/* may be divisible also by 4 */
l_string|&quot;jz 2f&bslash;n&bslash;t&quot;
l_string|&quot;pushw %w0&bslash;n&bslash;t&quot;
l_string|&quot;shll $16,%0&bslash;n&bslash;t&quot;
l_string|&quot;popw %w0&bslash;n&quot;
l_string|&quot;1:&bslash;tmovl %0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addl $4,%1&bslash;n&bslash;t&quot;
l_string|&quot;decl %2&bslash;n&bslash;t&quot;
l_string|&quot;jnz 1b&bslash;n&quot;
l_string|&quot;2:&bslash;tmovw %w0,(%1)&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_int
)paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
op_div
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__memset_cg
r_extern
r_inline
r_void
op_star
id|__memset_cg
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|s
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;stosw&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movb %%al,(%%edi)&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|count
)paren
comma
l_string|&quot;D&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;a&quot;
(paren
l_int|0x0101U
op_star
(paren
r_int
r_char
)paren
id|c
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__memset_gg
r_extern
r_inline
r_void
op_star
id|__memset_gg
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
r_register
r_void
op_star
id|tmp
op_assign
(paren
r_void
op_star
)paren
id|s
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movb %%al,%%ah&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;stosw&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movb %%al,(%%edi)&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|count
)paren
comma
l_string|&quot;D&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;a&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/*&n; * find the first occurrence of byte &squot;c&squot;, or 1 past the area if none&n; */
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN
DECL|function|memscan
r_extern
r_inline
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
"&quot;"
id|cld
id|repnz
suffix:semicolon
id|scasb
id|jnz
l_float|1f
id|dec
op_mod
op_mod
id|edi
l_int|1
suffix:colon
"&quot;"
suffix:colon
l_string|&quot;=D&quot;
(paren
id|addr
)paren
comma
l_string|&quot;=c&quot;
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
l_string|&quot;a&quot;
(paren
id|c
)paren
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
macro_line|#endif
eof
