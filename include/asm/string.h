macro_line|#ifndef _I386_STRING_H_
DECL|macro|_I386_STRING_H_
mdefine_line|#define _I386_STRING_H_
multiline_comment|/*&n; * This string-include defines all string functions as inline&n; * functions. Use gcc. It also assumes ds=es=data space, this should be&n; * normal. Most of the string-functions are rather heavily hand-optimized,&n; * see especially strtok,strstr,str[c]spn. They should work, but are not&n; * very easy to understand. Everything is done entirely within the register&n; * set, making the functions fast and clean. String instructions have been&n; * used through-out, making for &quot;slightly&quot; unclear code :-)&n; *&n; *&t;&t;Copyright (C) 1991, 1992 Linus Torvalds&n; */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;stosb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;S&quot;
(paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|dest
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;ax&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&quot;
l_string|&quot;1:&bslash;tdecl %2&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;lodsb&bslash;n&bslash;t&quot;
l_string|&quot;stosb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;stosb&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;S&quot;
(paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|dest
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
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;stosb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;S&quot;
(paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|dest
)paren
comma
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0xffffffff
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;movl %4,%3&bslash;n&quot;
l_string|&quot;1:&bslash;tdecl %3&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;lodsb&bslash;n&bslash;t&quot;
l_string|&quot;stosb&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;txorl %2,%2&bslash;n&bslash;t&quot;
l_string|&quot;stosb&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;S&quot;
(paren
id|src
)paren
comma
l_string|&quot;D&quot;
(paren
id|dest
)paren
comma
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
l_string|&quot;g&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
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
l_string|&quot;cld&bslash;n&quot;
l_string|&quot;1:&bslash;tlodsb&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 2f&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;xorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;jmp 3f&bslash;n&quot;
l_string|&quot;2:&bslash;tsbbl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orb $1,%%eax&bslash;n&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;S&quot;
(paren
id|cs
)paren
comma
l_string|&quot;D&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;di&quot;
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
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&quot;
l_string|&quot;1:&bslash;tdecl %3&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;lodsb&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 3f&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;txorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;jmp 4f&bslash;n&quot;
l_string|&quot;3:&bslash;tsbbl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orb $1,%%al&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
suffix:colon
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
r_char
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
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;testb %%al,%%al&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;movl $1,%1&bslash;n&quot;
l_string|&quot;2:&bslash;tmovl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;decl %0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;S&quot;
(paren
id|s
)paren
comma
l_string|&quot;0&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
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
r_char
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
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %0&bslash;n&bslash;t&quot;
l_string|&quot;decl %0&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;D&quot;
(paren
id|s
)paren
comma
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0xffffffff
)paren
suffix:colon
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
r_extern
r_char
op_star
id|___strtok
suffix:semicolon
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
multiline_comment|/* empty delimeter-string */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx, %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;shrl $2,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep ; movsl&bslash;n&bslash;t&quot;
l_string|&quot;testb $1,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;ttestb $2,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;d&quot;
(paren
id|n
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|to
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
id|dest
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
c_func
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
id|dest
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
l_string|&quot;sbbl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orb $1,%%al&bslash;n&quot;
l_string|&quot;1:&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;stosb&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;a&quot;
(paren
id|c
)paren
comma
l_string|&quot;D&quot;
(paren
id|s
)paren
comma
l_string|&quot;c&quot;
(paren
id|count
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
macro_line|#endif
eof
