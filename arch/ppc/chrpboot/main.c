multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;../coffboot/nonstdio.h&quot;
macro_line|#include &quot;../coffboot/zlib.h&quot;
r_extern
r_void
op_star
id|finddevice
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|getprop
c_func
(paren
r_void
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|get_16be
mdefine_line|#define get_16be(x)&t;(*(unsigned short *)(x))
DECL|macro|get_32be
mdefine_line|#define get_32be(x)&t;(*(unsigned *)(x))
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;0x00000000
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;0x00800000&t;/* only 8M mapped with BATs */
DECL|macro|RAM_FREE
mdefine_line|#define RAM_FREE&t;0x00540000&t;/* after image of chrpboot */
DECL|macro|PROG_START
mdefine_line|#define PROG_START&t;0x00010000
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|end_avail
r_char
op_star
id|end_avail
suffix:semicolon
r_extern
r_char
id|image_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|image_len
suffix:semicolon
r_extern
r_char
id|initrd_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|initrd_len
suffix:semicolon
DECL|function|chrpboot
id|chrpboot
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_void
op_star
id|prom
)paren
(brace
r_int
id|ns
comma
id|oh
comma
id|i
suffix:semicolon
r_int
id|sa
comma
id|len
suffix:semicolon
r_void
op_star
id|dst
suffix:semicolon
r_int
r_char
op_star
id|im
suffix:semicolon
r_int
id|initrd_start
comma
id|initrd_size
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;chrpboot starting&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
multiline_comment|/* setup_bats(); */
r_if
c_cond
(paren
id|initrd_len
)paren
(brace
id|initrd_size
op_assign
id|initrd_len
suffix:semicolon
id|initrd_start
op_assign
(paren
id|RAM_END
op_minus
id|initrd_size
)paren
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|a1
op_assign
id|initrd_start
suffix:semicolon
id|a2
op_assign
id|initrd_size
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial ramdisk at %x (%u bytes)&bslash;n&bslash;r&quot;
comma
id|initrd_start
comma
id|initrd_size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|initrd_start
comma
id|initrd_data
comma
id|initrd_size
)paren
suffix:semicolon
id|end_avail
op_assign
(paren
r_char
op_star
)paren
id|initrd_start
suffix:semicolon
)brace
r_else
id|end_avail
op_assign
(paren
r_char
op_star
)paren
id|RAM_END
suffix:semicolon
id|im
op_assign
id|image_data
suffix:semicolon
id|len
op_assign
id|image_len
suffix:semicolon
id|dst
op_assign
(paren
r_void
op_star
)paren
id|PROG_START
suffix:semicolon
r_if
c_cond
(paren
id|im
(braket
l_int|0
)braket
op_eq
l_int|0x1f
op_logical_and
id|im
(braket
l_int|1
)braket
op_eq
l_int|0x8b
)paren
(brace
r_void
op_star
id|cp
op_assign
(paren
r_void
op_star
)paren
id|RAM_FREE
suffix:semicolon
id|avail_ram
op_assign
(paren
r_void
op_star
)paren
(paren
id|RAM_FREE
op_plus
(paren
(paren
id|len
op_plus
l_int|7
)paren
op_amp
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cp
comma
id|im
comma
id|len
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;gunzipping... &quot;
)paren
suffix:semicolon
id|gunzip
c_func
(paren
id|dst
comma
l_int|0x400000
comma
id|cp
comma
op_amp
id|len
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;done&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|memmove
c_func
(paren
id|dst
comma
id|im
comma
id|len
)paren
suffix:semicolon
)brace
id|flush_cache
c_func
(paren
id|dst
comma
id|len
)paren
suffix:semicolon
id|sa
op_assign
id|PROG_START
op_plus
l_int|12
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;start address = 0x%x&bslash;n&bslash;r&quot;
comma
id|sa
)paren
suffix:semicolon
macro_line|#if 0
id|pause
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
(paren
op_star
(paren
r_void
(paren
op_star
)paren
(paren
)paren
)paren
id|sa
)paren
(paren
id|a1
comma
id|a2
comma
id|prom
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;returned?&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|zalloc
r_void
op_star
id|zalloc
c_func
(paren
r_void
op_star
id|x
comma
r_int
id|items
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|p
op_assign
id|avail_ram
suffix:semicolon
id|size
op_mul_assign
id|items
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|7
)paren
op_amp
op_minus
l_int|8
suffix:semicolon
id|avail_ram
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
OG
id|end_avail
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;oops... out of memory&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|zfree
r_void
id|zfree
c_func
(paren
r_void
op_star
id|x
comma
r_void
op_star
id|addr
comma
r_int
id|nb
)paren
(brace
)brace
DECL|macro|HEAD_CRC
mdefine_line|#define HEAD_CRC&t;2
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD&t;4
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME&t;8
DECL|macro|COMMENT
mdefine_line|#define COMMENT&t;&t;0x10
DECL|macro|RESERVED
mdefine_line|#define RESERVED&t;0xe0
DECL|macro|DEFLATED
mdefine_line|#define DEFLATED&t;8
DECL|function|gunzip
r_void
id|gunzip
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_int
r_char
op_star
id|src
comma
r_int
op_star
id|lenp
)paren
(brace
id|z_stream
id|s
suffix:semicolon
r_int
id|r
comma
id|i
comma
id|flags
suffix:semicolon
multiline_comment|/* skip header */
id|i
op_assign
l_int|10
suffix:semicolon
id|flags
op_assign
id|src
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_ne
id|DEFLATED
op_logical_or
(paren
id|flags
op_amp
id|RESERVED
)paren
op_ne
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;bad gzipped data&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|EXTRA_FIELD
)paren
op_ne
l_int|0
)paren
id|i
op_assign
l_int|12
op_plus
id|src
(braket
l_int|10
)braket
op_plus
(paren
id|src
(braket
l_int|11
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ORIG_NAME
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|COMMENT
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|HEAD_CRC
)paren
op_ne
l_int|0
)paren
id|i
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
op_star
id|lenp
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;gunzip: ran out of data in header&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.zalloc
op_assign
id|zalloc
suffix:semicolon
id|s.zfree
op_assign
id|zfree
suffix:semicolon
id|r
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|s
comma
op_minus
id|MAX_WBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;inflateInit2 returned %d&bslash;n&bslash;r&quot;
comma
id|r
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.next_in
op_assign
id|src
op_plus
id|i
suffix:semicolon
id|s.avail_in
op_assign
op_star
id|lenp
op_minus
id|i
suffix:semicolon
id|s.next_out
op_assign
id|dst
suffix:semicolon
id|s.avail_out
op_assign
id|dstlen
suffix:semicolon
id|r
op_assign
id|inflate
c_func
(paren
op_amp
id|s
comma
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_and
id|r
op_ne
id|Z_STREAM_END
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;inflate returned %d&bslash;n&bslash;r&quot;
comma
id|r
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
id|s.next_out
op_minus
(paren
r_int
r_char
op_star
)paren
id|dst
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
)brace
eof
