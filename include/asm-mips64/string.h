multiline_comment|/* $Id: string.h,v 1.4 2000/01/16 01:37:19 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1994, 1995, 1996, 1997, 1998 by Ralf Baechle&n; *&n; * XXX For now I&squot;m too lazy to fix the string functions, let&squot;s rely on the&n; * generic stuff.&n; */
macro_line|#ifndef _ASM_STRING_H
DECL|macro|_ASM_STRING_H
mdefine_line|#define _ASM_STRING_H
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
macro_line|#undef __HAVE_ARCH_MEMCPY
singleline_comment|//extern void *memcpy(void *__to, __const__ void *__from, size_t __n);
DECL|macro|__HAVE_ARCH_MEMMOVE
macro_line|#undef __HAVE_ARCH_MEMMOVE
singleline_comment|//extern void *memmove(void *__dest, __const__ void *__src, size_t __n);
multiline_comment|/* Don&squot;t build bcopy at all ...  */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
macro_line|#endif /* _ASM_STRING_H */
eof
