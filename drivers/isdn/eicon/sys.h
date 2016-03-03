multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * This source file is supplied for the exclusive use with Eicon&n; * Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n; * Eicon File Revision :    1.2  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* Environment provided by system and miscellaneous definitions */
macro_line|#if !defined(SYS_H)
DECL|macro|SYS_H
mdefine_line|#define SYS_H
multiline_comment|/* abreviations for unsigned types */
DECL|typedef|boolean_t
r_typedef
r_int
id|boolean_t
suffix:semicolon
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
DECL|typedef|dword
r_typedef
r_int
r_int
id|dword
suffix:semicolon
DECL|typedef|word
r_typedef
r_int
r_int
id|word
suffix:semicolon
multiline_comment|/* abreviations for volatile types */
DECL|typedef|vbyte
r_typedef
r_volatile
id|byte
id|vbyte
suffix:semicolon
DECL|typedef|vword
r_typedef
r_volatile
id|word
id|vword
suffix:semicolon
DECL|typedef|vdword
r_typedef
r_volatile
id|dword
id|vdword
suffix:semicolon
multiline_comment|/* Booleans */
macro_line|#if !defined(TRUE)
DECL|macro|TRUE
mdefine_line|#define TRUE    (1)
DECL|macro|FALSE
mdefine_line|#define FALSE   (0)
macro_line|#endif
multiline_comment|/* NULL pointer */
macro_line|#if !defined(NULL)
DECL|macro|NULL
mdefine_line|#define NULL    ((void *) 0)
macro_line|#endif
multiline_comment|/* MIN and MAX */
macro_line|#if !defined(MIN)
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a)&gt;(b) ? (b) : (a))
macro_line|#endif
macro_line|#if !defined(MAX)
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a)&gt;(b) ? (a) : (b))
macro_line|#endif
multiline_comment|/* Return the dimension of an array */
macro_line|#if !defined(DIM)
DECL|macro|DIM
mdefine_line|#define DIM(array)  (sizeof (array)/sizeof ((array)[0]))
macro_line|#endif
multiline_comment|/*&n; * Return the number of milliseconds since last boot&n; */
r_extern
id|dword
id|UxTimeGet
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|DivasSprintf
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|DivasPrintf
c_func
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* fatal errors, asserts and tracing */
r_void
id|HwFatalErrorFrom
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
r_void
id|HwFatalError
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* void HwAssert(char *file, int line, char *condition); */
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|_PRINTK
mdefine_line|#define _PRINTK printk
DECL|macro|_PRINTF
mdefine_line|#define _PRINTF&t;DivasPrintf
r_void
id|_PRINTF
c_func
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|PRINTF
mdefine_line|#define PRINTF(arg_list)&t;_PRINTF arg_list
macro_line|#if defined DTRACE
DECL|macro|DPRINTF
macro_line|# define DPRINTF(arg_list)&t;_PRINTF arg_list
DECL|macro|KDPRINTF
macro_line|# define KDPRINTF(arg_list)&t;_PRINTF arg_list ; _PRINTK arg_list ; _PRINTK(&quot;&bslash;n&quot;);
macro_line|#else
DECL|macro|DPRINTF
macro_line|# define DPRINTF(arg_list)&t;(void)0
DECL|macro|KDPRINTF
macro_line|# define KDPRINTF(arg_list)&t;_PRINTK arg_list ; _PRINTK(&quot;&bslash;n&quot;);
macro_line|#endif
macro_line|#if !defined(ASSERT)
macro_line|#if defined DEBUG || defined DBG
DECL|macro|HwFatalError
macro_line|# define HwFatalError()&t;HwFatalErrorFrom(__FILE__, __LINE__)
DECL|macro|ASSERT
macro_line|# define ASSERT(cond)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!(cond)) &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/*&t;&t;&t;HwAssert(__FILE__, __LINE__, #cond);*/&t;&bslash;&n;&t;&t;}
macro_line|#else
DECL|macro|ASSERT
macro_line|# define ASSERT(cond)&t;((void)0)
macro_line|#endif
macro_line|#endif /* !defined(ASSERT) */
DECL|macro|TRACE
mdefine_line|#define TRACE&t;(_PRINTF(__FILE__&quot;@%d&bslash;n&quot;, __LINE__))
macro_line|#endif /* SYS_H */
eof
