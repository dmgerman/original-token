multiline_comment|/* zutil.h -- internal interface and configuration of the compression library&n; * Copyright (C) 1995-1998 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h&n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
multiline_comment|/* @(#) $Id$ */
macro_line|#ifndef _Z_UTIL_H
DECL|macro|_Z_UTIL_H
mdefine_line|#define _Z_UTIL_H
macro_line|#include &quot;zlib.h&quot;
macro_line|#  include &lt;stddef.h&gt;
macro_line|#  include &lt;stdlib.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#  include &lt;linux/string.h&gt;
macro_line|#  include &lt;linux/errno.h&gt;
macro_line|#else
macro_line|#  include &lt;string.h&gt;
macro_line|#  include &lt;errno.h&gt;
macro_line|#endif
macro_line|#ifndef local
DECL|macro|local
macro_line|#  define local static
macro_line|#endif
multiline_comment|/* compile with -Dlocal if your debugger can&squot;t find static symbols */
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|uchf
r_typedef
id|uch
id|FAR
id|uchf
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ushf
r_typedef
id|ush
id|FAR
id|ushf
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
r_extern
r_const
r_char
op_star
id|z_errmsg
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* indexed by 2-zlib_error */
multiline_comment|/* (size given to avoid silly warnings with Visual C++) */
DECL|macro|ERR_MSG
mdefine_line|#define ERR_MSG(err) z_errmsg[Z_NEED_DICT-(err)]
DECL|macro|ERR_RETURN
mdefine_line|#define ERR_RETURN(strm,err) &bslash;&n;  return (strm-&gt;msg = (char*)ERR_MSG(err), (err))
multiline_comment|/* To be used only when the state is known to be valid */
multiline_comment|/* common constants */
macro_line|#ifndef DEF_WBITS
DECL|macro|DEF_WBITS
macro_line|#  define DEF_WBITS MAX_WBITS
macro_line|#endif
multiline_comment|/* default windowBits for decompression. MAX_WBITS is for compression only */
macro_line|#if MAX_MEM_LEVEL &gt;= 8
DECL|macro|DEF_MEM_LEVEL
macro_line|#  define DEF_MEM_LEVEL 8
macro_line|#else
DECL|macro|DEF_MEM_LEVEL
macro_line|#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
macro_line|#endif
multiline_comment|/* default memLevel */
DECL|macro|STORED_BLOCK
mdefine_line|#define STORED_BLOCK 0
DECL|macro|STATIC_TREES
mdefine_line|#define STATIC_TREES 1
DECL|macro|DYN_TREES
mdefine_line|#define DYN_TREES    2
multiline_comment|/* The three kinds of block type */
DECL|macro|MIN_MATCH
mdefine_line|#define MIN_MATCH  3
DECL|macro|MAX_MATCH
mdefine_line|#define MAX_MATCH  258
multiline_comment|/* The minimum and maximum match lengths */
DECL|macro|PRESET_DICT
mdefine_line|#define PRESET_DICT 0x20 /* preset dictionary flag in zlib header */
multiline_comment|/* target dependencies */
multiline_comment|/* Common defaults */
macro_line|#ifndef OS_CODE
DECL|macro|OS_CODE
macro_line|#  define OS_CODE  0x03  /* assume Unix */
macro_line|#endif
macro_line|#ifndef F_OPEN
DECL|macro|F_OPEN
macro_line|#  define F_OPEN(name, mode) fopen((name), (mode))
macro_line|#endif
multiline_comment|/* functions */
multiline_comment|/* Diagnostic functions */
macro_line|#ifdef DEBUG
macro_line|#  include &lt;stdio.h&gt;
r_extern
r_int
id|z_verbose
suffix:semicolon
r_extern
r_void
id|z_error
id|OF
c_func
(paren
(paren
r_char
op_star
id|m
)paren
)paren
suffix:semicolon
DECL|macro|Assert
macro_line|#  define Assert(cond,msg) {if(!(cond)) z_error(msg);}
DECL|macro|Trace
macro_line|#  define Trace(x) {if (z_verbose&gt;=0) fprintf x ;}
DECL|macro|Tracev
macro_line|#  define Tracev(x) {if (z_verbose&gt;0) fprintf x ;}
DECL|macro|Tracevv
macro_line|#  define Tracevv(x) {if (z_verbose&gt;1) fprintf x ;}
DECL|macro|Tracec
macro_line|#  define Tracec(c,x) {if (z_verbose&gt;0 &amp;&amp; (c)) fprintf x ;}
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x) {if (z_verbose&gt;1 &amp;&amp; (c)) fprintf x ;}
macro_line|#else
DECL|macro|Assert
macro_line|#  define Assert(cond,msg)
DECL|macro|Trace
macro_line|#  define Trace(x)
DECL|macro|Tracev
macro_line|#  define Tracev(x)
DECL|macro|Tracevv
macro_line|#  define Tracevv(x)
DECL|macro|Tracec
macro_line|#  define Tracec(c,x)
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x)
macro_line|#endif
DECL|typedef|OF
r_typedef
id|uLong
(paren
id|ZEXPORT
op_star
id|check_func
)paren
id|OF
c_func
(paren
(paren
id|uLong
id|check
comma
r_const
id|Bytef
op_star
id|buf
comma
id|uInt
id|len
)paren
)paren
suffix:semicolon
id|voidpf
id|zcalloc
id|OF
c_func
(paren
(paren
id|voidpf
id|opaque
comma
r_int
id|items
comma
r_int
id|size
)paren
)paren
suffix:semicolon
r_void
id|zcfree
id|OF
c_func
(paren
(paren
id|voidpf
id|opaque
comma
id|voidpf
id|ptr
)paren
)paren
suffix:semicolon
DECL|macro|ZALLOC
mdefine_line|#define ZALLOC(strm, items, size) ({ &bslash;&n;&t;printf(&quot;alloc %d %d at %s:%d&bslash;n&quot;, items, size, __FILE__, __LINE__); &bslash;&n;&t;calloc((items), (size)); })
DECL|macro|ZFREE
mdefine_line|#define ZFREE(strm, addr)  free(addr)
DECL|macro|TRY_FREE
mdefine_line|#define TRY_FREE(s, p) {if (p) ZFREE(s, p);}
macro_line|#endif /* _Z_UTIL_H */
eof
