multiline_comment|/* uncompr.c -- decompress a memory buffer&n; * Copyright (C) 1995-1998 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* @(#) $Id$ */
macro_line|#include &quot;zlib.h&quot;
multiline_comment|/* ===========================================================================&n;     Decompresses the source buffer into the destination buffer.  sourceLen is&n;   the byte length of the source buffer. Upon entry, destLen is the total&n;   size of the destination buffer, which must be large enough to hold the&n;   entire uncompressed data. (The size of the uncompressed data must have&n;   been saved previously by the compressor and transmitted to the decompressor&n;   by some mechanism outside the scope of this compression library.)&n;   Upon exit, destLen is the actual size of the compressed buffer.&n;     This function can be used to decompress a whole file at once if the&n;   input file is mmap&squot;ed.&n;&n;     uncompress returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_BUF_ERROR if there was not enough room in the output&n;   buffer, or Z_DATA_ERROR if the input data was corrupted.&n;*/
DECL|function|uncompress
r_int
id|ZEXPORT
id|uncompress
(paren
id|dest
comma
id|destLen
comma
id|source
comma
id|sourceLen
)paren
id|Bytef
op_star
id|dest
suffix:semicolon
id|uLongf
op_star
id|destLen
suffix:semicolon
r_const
id|Bytef
op_star
id|source
suffix:semicolon
id|uLong
id|sourceLen
suffix:semicolon
(brace
id|z_stream
id|stream
suffix:semicolon
r_int
id|err
suffix:semicolon
id|stream.next_in
op_assign
(paren
id|Bytef
op_star
)paren
id|source
suffix:semicolon
id|stream.avail_in
op_assign
(paren
id|uInt
)paren
id|sourceLen
suffix:semicolon
multiline_comment|/* Check for source &gt; 64K on 16-bit machine: */
r_if
c_cond
(paren
(paren
id|uLong
)paren
id|stream.avail_in
op_ne
id|sourceLen
)paren
r_return
id|Z_BUF_ERROR
suffix:semicolon
id|stream.next_out
op_assign
id|dest
suffix:semicolon
id|stream.avail_out
op_assign
(paren
id|uInt
)paren
op_star
id|destLen
suffix:semicolon
r_if
c_cond
(paren
(paren
id|uLong
)paren
id|stream.avail_out
op_ne
op_star
id|destLen
)paren
r_return
id|Z_BUF_ERROR
suffix:semicolon
id|err
op_assign
id|cramfs_inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|Z_OK
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
id|cramfs_inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|Z_STREAM_END
)paren
(brace
id|cramfs_inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_return
id|err
op_eq
id|Z_OK
ques
c_cond
id|Z_BUF_ERROR
suffix:colon
id|err
suffix:semicolon
)brace
op_star
id|destLen
op_assign
id|stream.total_out
suffix:semicolon
id|err
op_assign
id|cramfs_inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
