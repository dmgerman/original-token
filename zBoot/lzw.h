multiline_comment|/* lzw.h -- define the lzw functions.&n; * Copyright (C) 1992-1993 Jean-loup Gailly.&n; * This is free software; you can redistribute it and/or modify it under the&n; * terms of the GNU General Public License, see the file COPYING.&n; */
macro_line|#if !defined(OF) &amp;&amp; defined(lint)
macro_line|#  include &quot;gzip.h&quot;
macro_line|#endif
macro_line|#ifndef BITS
DECL|macro|BITS
macro_line|#  define BITS 16
macro_line|#endif
DECL|macro|INIT_BITS
mdefine_line|#define INIT_BITS 9              /* Initial number of bits per code */
DECL|macro|LZW_MAGIC
mdefine_line|#define&t;LZW_MAGIC  &quot;&bslash;037&bslash;235&quot;   /* Magic header for lzw files, 1F 9D */
DECL|macro|BIT_MASK
mdefine_line|#define BIT_MASK    0x1f /* Mask for &squot;number of compresssion bits&squot; */
multiline_comment|/* Mask 0x20 is reserved to mean a fourth header byte, and 0x40 is free.&n; * It&squot;s a pity that old uncompress does not check bit 0x20. That makes&n; * extension of the format actually undesirable because old compress&n; * would just crash on the new format instead of giving a meaningful&n; * error message. It does check the number of bits, but it&squot;s more&n; * helpful to say &quot;unsupported format, get a new version&quot; than&n; * &quot;can only handle 16 bits&quot;.&n; */
DECL|macro|BLOCK_MODE
mdefine_line|#define BLOCK_MODE  0x80
multiline_comment|/* Block compresssion: if table is full and compression rate is dropping,&n; * clear the dictionary.&n; */
DECL|macro|LZW_RESERVED
mdefine_line|#define LZW_RESERVED 0x60 /* reserved bits */
DECL|macro|CLEAR
mdefine_line|#define&t;CLEAR  256       /* flush the dictionary */
DECL|macro|FIRST
mdefine_line|#define FIRST  (CLEAR+1) /* first free entry */
r_extern
r_int
id|maxbits
suffix:semicolon
multiline_comment|/* max bits per code for LZW */
r_extern
r_int
id|block_mode
suffix:semicolon
multiline_comment|/* block compress mode -C compatible with 2.0 */
r_extern
r_void
id|lzw
id|OF
c_func
(paren
(paren
r_int
id|in
comma
r_int
id|out
)paren
)paren
suffix:semicolon
r_extern
r_void
id|unlzw
id|OF
c_func
(paren
(paren
r_int
id|in
comma
r_int
id|out
)paren
)paren
suffix:semicolon
eof
