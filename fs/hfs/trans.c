multiline_comment|/*&n; * linux/fs/hfs/trans.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file contains routines for converting between the Macintosh&n; * character set and various other encodings.  This includes dealing&n; * with &squot;:&squot; vs. &squot;/&squot; as the path-element separator.&n; *&n; * Latin-1 translation based on code contributed by Holger Schemel&n; * (aeglos@valinor.owl.de).&n; *&n; * The &squot;8-bit&squot;, &squot;7-bit ASCII&squot; and &squot;7-bit alphanumeric&squot; encodings are&n; * implementations of the three encodings recommended by Apple in the&n; * document &quot;AppleSingle/AppleDouble Formats: Developer&squot;s Note&n; * (9/94)&quot;.  This document is available from Apple&squot;s Technical&n; * Information Library from the World Wide Web server&n; * www.info.apple.com.&n; *&n; * The &squot;CAP&squot; encoding is an implementation of the naming scheme used&n; * by the Columbia AppleTalk Package, available for anonymous FTP from&n; * ????.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
multiline_comment|/*================ File-local variables ================*/
multiline_comment|/* int-&gt;ASCII map for a single hex digit */
DECL|variable|hex
r_static
r_char
id|hex
(braket
l_int|16
)braket
op_assign
(brace
l_char|&squot;0&squot;
comma
l_char|&squot;1&squot;
comma
l_char|&squot;2&squot;
comma
l_char|&squot;3&squot;
comma
l_char|&squot;4&squot;
comma
l_char|&squot;5&squot;
comma
l_char|&squot;6&squot;
comma
l_char|&squot;7&squot;
comma
l_char|&squot;8&squot;
comma
l_char|&squot;9&squot;
comma
l_char|&squot;a&squot;
comma
l_char|&squot;b&squot;
comma
l_char|&squot;c&squot;
comma
l_char|&squot;d&squot;
comma
l_char|&squot;e&squot;
comma
l_char|&squot;f&squot;
)brace
suffix:semicolon
multiline_comment|/*&n; * Latin-1 to Mac character set map&n; *&n; * For the sake of consistency this map is generated from the Mac to&n; * Latin-1 map the first time it is needed.  This means there is just&n; * one map to maintain.&n; */
DECL|variable|latin2mac_map
r_static
r_int
r_char
id|latin2mac_map
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* initially all zero */
multiline_comment|/*&n; * Mac to Latin-1 map for the upper 128 characters (both have ASCII in&n; * the lower 128 positions)&n; */
DECL|variable|mac2latin_map
r_static
r_int
r_char
id|mac2latin_map
(braket
l_int|128
)braket
op_assign
(brace
l_int|0xC4
comma
l_int|0xC5
comma
l_int|0xC7
comma
l_int|0xC9
comma
l_int|0xD1
comma
l_int|0xD6
comma
l_int|0xDC
comma
l_int|0xE1
comma
l_int|0xE0
comma
l_int|0xE2
comma
l_int|0xE4
comma
l_int|0xE3
comma
l_int|0xE5
comma
l_int|0xE7
comma
l_int|0xE9
comma
l_int|0xE8
comma
l_int|0xEA
comma
l_int|0xEB
comma
l_int|0xED
comma
l_int|0xEC
comma
l_int|0xEE
comma
l_int|0xEF
comma
l_int|0xF1
comma
l_int|0xF3
comma
l_int|0xF2
comma
l_int|0xF4
comma
l_int|0xF6
comma
l_int|0xF5
comma
l_int|0xFA
comma
l_int|0xF9
comma
l_int|0xFB
comma
l_int|0xFC
comma
l_int|0x00
comma
l_int|0xB0
comma
l_int|0xA2
comma
l_int|0xA3
comma
l_int|0xA7
comma
l_int|0xB7
comma
l_int|0xB6
comma
l_int|0xDF
comma
l_int|0xAE
comma
l_int|0xA9
comma
l_int|0x00
comma
l_int|0xB4
comma
l_int|0xA8
comma
l_int|0x00
comma
l_int|0xC6
comma
l_int|0xD8
comma
l_int|0x00
comma
l_int|0xB1
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xA5
comma
l_int|0xB5
comma
l_int|0xF0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xAA
comma
l_int|0xBA
comma
l_int|0x00
comma
l_int|0xE6
comma
l_int|0xF8
comma
l_int|0xBF
comma
l_int|0xA1
comma
l_int|0xAC
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xAB
comma
l_int|0xBB
comma
l_int|0x00
comma
l_int|0xA0
comma
l_int|0xC0
comma
l_int|0xC3
comma
l_int|0xD5
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xAD
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xF7
comma
l_int|0x00
comma
l_int|0xFF
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xA4
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xB8
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xC2
comma
l_int|0xCA
comma
l_int|0xC1
comma
l_int|0xCB
comma
l_int|0xC8
comma
l_int|0xCD
comma
l_int|0xCE
comma
l_int|0xCF
comma
l_int|0xCC
comma
l_int|0xD3
comma
l_int|0xD4
comma
l_int|0x00
comma
l_int|0xD2
comma
l_int|0xDA
comma
l_int|0xDB
comma
l_int|0xD9
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * dehex()&n; *&n; * Given a hexadecimal digit in ASCII, return the integer representation.&n; */
DECL|function|dehex
r_static
r_inline
r_const
r_int
r_char
id|dehex
c_func
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;9&squot;
)paren
)paren
(brace
r_return
id|c
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;f&squot;
)paren
)paren
(brace
r_return
id|c
op_minus
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;F&squot;
)paren
)paren
(brace
r_return
id|c
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
)brace
r_return
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_mac2nat()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the Netatalk name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL terminated.&n; *&n; * The name-mangling works as follows:&n; * Characters 32-126 (&squot; &squot;-&squot;~&squot;) except &squot;/&squot; and any initial &squot;.&squot; are passed&n; * unchanged from input to output.  The remaining characters are replaced&n; * by three characters: &squot;:xx&squot; where xx is the hexadecimal representation&n; * of the character, using lowercase &squot;a&squot; through &squot;f&squot;.&n; */
DECL|function|hfs_mac2nat
r_int
id|hfs_mac2nat
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Special case for .AppleDesktop which in the&n;&t;   distant future may be a pseudodirectory. */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;.AppleDesktop&quot;
comma
id|p
comma
id|len
)paren
op_eq
l_int|0
)paren
(brace
id|strncpy
c_func
(paren
id|out
comma
id|p
comma
l_int|13
)paren
suffix:semicolon
r_return
l_int|13
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
OL
l_int|32
)paren
op_logical_or
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|c
OG
l_int|126
)paren
op_logical_or
(paren
op_logical_neg
id|count
op_logical_and
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2cap()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the CAP name-mangling scheme, returning the length of the mangled&n; * filename.  Note that the output string is not NULL terminated.&n; *&n; * The name-mangling works as follows:&n; * Characters 32-126 (&squot; &squot;-&squot;~&squot;) except &squot;/&squot; are passed unchanged from&n; * input to output.  The remaining characters are replaced by three&n; * characters: &squot;:xx&squot; where xx is the hexadecimal representation of the&n; * character, using lowercase &squot;a&squot; through &squot;f&squot;.&n; */
DECL|function|hfs_mac2cap
r_int
id|hfs_mac2cap
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
OL
l_int|32
)paren
op_logical_or
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|c
OG
l_int|126
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2eight()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the &squot;8-bit&squot; name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This is one of the three recommended naming conventions described&n; * in Apple&squot;s document &quot;AppleSingle/AppleDouble Formats: Developer&squot;s&n; * Note (9/94)&quot;&n; *&n; * The name-mangling works as follows:&n; * Characters 0, &squot;%&squot; and &squot;/&squot; are replaced by three characters: &squot;%xx&squot;&n; * where xx is the hexadecimal representation of the character, using&n; * lowercase &squot;a&squot; through &squot;f&squot;.  All other characters are passed&n; * unchanged from input to output.  Note that this format is mainly&n; * implemented for completeness and is rather hard to read.&n; */
DECL|function|hfs_mac2eight
r_int
id|hfs_mac2eight
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|c
op_eq
l_char|&squot;%&squot;
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2seven()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the &squot;7-bit ASCII&squot; name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This is one of the three recommended naming conventions described&n; * in Apple&squot;s document &quot;AppleSingle/AppleDouble Formats: Developer&squot;s&n; * Note (9/94)&quot;&n; *&n; * The name-mangling works as follows:&n; * Characters 0, &squot;%&squot;, &squot;/&squot; and 128-255 are replaced by three&n; * characters: &squot;%xx&squot; where xx is the hexadecimal representation of the&n; * character, using lowercase &squot;a&squot; through &squot;f&squot;.&t;All other characters&n; * are passed unchanged from input to output.  Note that control&n; * characters (including newline) and space are unchanged make reading&n; * these filenames difficult.&n; */
DECL|function|hfs_mac2seven
r_int
id|hfs_mac2seven
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|c
op_eq
l_char|&squot;%&squot;
)paren
op_logical_or
(paren
id|c
op_amp
l_int|0x80
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2alpha()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the &squot;7-bit alphanumeric&squot; name-mangling scheme, returning the length&n; * of the mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This is one of the three recommended naming conventions described&n; * in Apple&squot;s document &quot;AppleSingle/AppleDouble Formats: Developer&squot;s&n; * Note (9/94)&quot;&n; *&n; * The name-mangling works as follows:&n; * The characters &squot;a&squot;-&squot;z&squot;, &squot;A&squot;-&squot;Z&squot;, &squot;0&squot;-&squot;9&squot;, &squot;_&squot; and the last &squot;.&squot; in&n; * the filename are passed unchanged from input to output.  All&n; * remaining characters (including any &squot;.&squot;s other than the last) are&n; * replaced by three characters: &squot;%xx&squot; where xx is the hexadecimal&n; * representation of the character, using lowercase &squot;a&squot; through &squot;f&squot;.&n; */
DECL|function|hfs_mac2alpha
r_int
id|hfs_mac2alpha
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_const
r_int
r_char
op_star
id|lp
suffix:semicolon
multiline_comment|/* last period */
multiline_comment|/* strrchr() would be good here, but &squot;in&squot; is not null-terminated */
r_for
c_loop
(paren
id|lp
op_assign
id|p
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
(paren
id|lp
op_ge
id|p
)paren
op_logical_and
(paren
op_star
id|lp
op_ne
l_char|&squot;.&squot;
)paren
suffix:semicolon
op_decrement
id|lp
)paren
(brace
)brace
op_increment
id|lp
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_eq
id|lp
)paren
op_logical_or
(paren
(paren
id|c
op_ge
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;9&squot;
)paren
)paren
op_logical_or
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;Z&squot;
)paren
)paren
op_logical_or
(paren
(paren
id|c
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;z&squot;
)paren
)paren
op_logical_or
(paren
id|c
op_eq
l_char|&squot;_&squot;
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2triv()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the &squot;trivial&squot; name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * The name-mangling works as follows:&n; * The character &squot;/&squot;, which is illegal in Linux filenames is replaced&n; * by &squot;:&squot; which never appears in HFS filenames.&t; All other characters&n; * are passed unchanged from input to output.&n; */
DECL|function|hfs_mac2triv
r_int
id|hfs_mac2triv
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
)brace
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_mac2latin()&n; *&n; * Given a &squot;Pascal String&squot; (a string preceded by a length byte) in&n; * the Macintosh character set produce the corresponding filename using&n; * the &squot;Latin-1&squot; name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * The Macintosh character set and Latin-1 are both extensions of the&n; * ASCII character set.&t; Some, but certainly not all, of the characters&n; * in the Macintosh character set are also in Latin-1 but not with the&n; * same encoding.  This name-mangling scheme replaces the characters in&n; * the Macintosh character set that have Latin-1 equivalents by those&n; * equivalents; the characters 32-126, excluding &squot;/&squot; and &squot;%&squot;, are&n; * passed unchanged from input to output.  The remaining characters&n; * are replaced by three characters: &squot;%xx&squot; where xx is the hexadecimal&n; * representation of the character, using lowercase &squot;a&squot; through &squot;f&squot;.&n; *&n; * The array mac2latin_map[] indicates the correspondence between the&n; * two character sets.&t;The byte in element x-128 gives the Latin-1&n; * encoding of the character with encoding x in the Macintosh&n; * character set.  A value of zero indicates Latin-1 has no&n; * corresponding character.&n; */
DECL|function|hfs_mac2latin
r_int
id|hfs_mac2latin
c_func
(paren
r_char
op_star
id|out
comma
r_const
r_struct
id|hfs_name
op_star
id|in
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|in-&gt;Name
suffix:semicolon
r_int
id|len
op_assign
id|in-&gt;Len
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_amp
l_int|0x80
)paren
op_logical_and
id|mac2latin_map
(braket
id|c
op_amp
l_int|0x7f
)braket
)paren
(brace
op_star
id|out
op_increment
op_assign
id|mac2latin_map
(braket
id|c
op_amp
l_int|0x7f
)braket
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|c
op_ge
l_int|32
)paren
op_logical_and
(paren
id|c
op_le
l_int|126
)paren
op_logical_and
(paren
id|c
op_ne
l_char|&squot;/&squot;
)paren
op_logical_and
(paren
id|c
op_ne
l_char|&squot;%&squot;
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_else
(brace
op_star
id|out
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|hex
(braket
id|c
op_amp
l_int|0xf
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_colon2mac()&n; *&n; * Given an ASCII string (not null-terminated) and its length,&n; * generate the corresponding filename in the Macintosh character set&n; * using the &squot;CAP&squot; name-mangling scheme, returning the length of the&n; * mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This routine is a inverse to hfs_mac2cap() and hfs_mac2nat().&n; * A &squot;:&squot; not followed by a 2-digit hexadecimal number (or followed&n; * by the codes for NULL or &squot;:&squot;) is replaced by a &squot;|&squot;.&n; */
DECL|function|hfs_colon2mac
r_void
id|hfs_colon2mac
c_func
(paren
r_struct
id|hfs_name
op_star
id|out
comma
r_const
r_char
op_star
id|in
comma
r_int
id|len
)paren
(brace
r_int
id|hi
comma
id|lo
suffix:semicolon
r_int
r_char
id|code
comma
id|c
comma
op_star
id|count
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|out-&gt;Name
suffix:semicolon
id|out-&gt;Len
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
op_amp
id|out-&gt;Len
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_star
id|count
OL
id|HFS_NAMELEN
)paren
)paren
(brace
id|c
op_assign
op_star
id|in
op_increment
suffix:semicolon
(paren
op_star
id|count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;:&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|len
OL
l_int|2
)paren
op_logical_or
(paren
(paren
id|hi
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|0
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
(paren
(paren
id|lo
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|1
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
op_logical_neg
(paren
id|code
op_assign
(paren
id|hi
op_lshift
l_int|4
)paren
op_or
id|lo
)paren
op_logical_or
(paren
id|code
op_eq
l_char|&squot;:&squot;
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;|&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|code
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|in
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * hfs_prcnt2mac()&n; *&n; * Given an ASCII string (not null-terminated) and its length,&n; * generate the corresponding filename in the Macintosh character set&n; * using Apple&squot;s three recommended name-mangling schemes, returning&n; * the length of the mangled filename.&t;Note that the output string is&n; * not NULL terminated.&n; *&n; * This routine is a inverse to hfs_mac2alpha(), hfs_mac2seven() and&n; * hfs_mac2eight().&n; * A &squot;%&squot; not followed by a 2-digit hexadecimal number (or followed&n; * by the code for NULL or &squot;:&squot;) is unchanged.&n; * A &squot;:&squot; is replaced by a &squot;|&squot;.&n; */
DECL|function|hfs_prcnt2mac
r_void
id|hfs_prcnt2mac
c_func
(paren
r_struct
id|hfs_name
op_star
id|out
comma
r_const
r_char
op_star
id|in
comma
r_int
id|len
)paren
(brace
r_int
id|hi
comma
id|lo
suffix:semicolon
r_int
r_char
id|code
comma
id|c
comma
op_star
id|count
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|out-&gt;Name
suffix:semicolon
id|out-&gt;Len
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
op_amp
id|out-&gt;Len
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_star
id|count
OL
id|HFS_NAMELEN
)paren
)paren
(brace
id|c
op_assign
op_star
id|in
op_increment
suffix:semicolon
(paren
op_star
id|count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;:&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;|&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;%&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|len
OL
l_int|2
)paren
op_logical_or
(paren
(paren
id|hi
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|0
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
(paren
(paren
id|lo
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|1
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
op_logical_neg
(paren
id|code
op_assign
(paren
id|hi
op_lshift
l_int|4
)paren
op_or
id|lo
)paren
op_logical_or
(paren
id|code
op_eq
l_char|&squot;:&squot;
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|code
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|in
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * hfs_triv2mac()&n; *&n; * Given an ASCII string (not null-terminated) and its length,&n; * generate the corresponding filename in the Macintosh character set&n; * using the &squot;trivial&squot; name-mangling scheme, returning the length of&n; * the mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This routine is a inverse to hfs_mac2triv().&n; * A &squot;:&squot; is replaced by a &squot;/&squot;.&n; */
DECL|function|hfs_triv2mac
r_void
id|hfs_triv2mac
c_func
(paren
r_struct
id|hfs_name
op_star
id|out
comma
r_const
r_char
op_star
id|in
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|c
comma
op_star
id|count
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|out-&gt;Name
suffix:semicolon
id|out-&gt;Len
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
op_amp
id|out-&gt;Len
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_star
id|count
OL
id|HFS_NAMELEN
)paren
)paren
(brace
id|c
op_assign
op_star
id|in
op_increment
suffix:semicolon
(paren
op_star
id|count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;:&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * hfs_latin2mac()&n; *&n; * Given an Latin-1 string (not null-terminated) and its length,&n; * generate the corresponding filename in the Macintosh character set&n; * using the &squot;Latin-1&squot; name-mangling scheme, returning the length of&n; * the mangled filename.  Note that the output string is not NULL&n; * terminated.&n; *&n; * This routine is a inverse to hfs_latin2cap().&n; * A &squot;%&squot; not followed by a 2-digit hexadecimal number (or followed&n; * by the code for NULL or &squot;:&squot;) is unchanged.&n; * A &squot;:&squot; is replaced by a &squot;|&squot;.&n; *&n; * Note that the character map is built the first time it is needed.&n; */
DECL|function|hfs_latin2mac
r_void
id|hfs_latin2mac
c_func
(paren
r_struct
id|hfs_name
op_star
id|out
comma
r_const
r_char
op_star
id|in
comma
r_int
id|len
)paren
(brace
r_int
id|hi
comma
id|lo
suffix:semicolon
r_int
r_char
id|code
comma
id|c
comma
op_star
id|count
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|out-&gt;Name
suffix:semicolon
r_static
r_int
id|map_initialized
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_initialized
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* build the inverse mapping at run time */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|c
op_assign
id|mac2latin_map
(braket
id|i
)braket
)paren
)paren
(brace
id|latin2mac_map
(braket
(paren
r_int
)paren
id|c
op_minus
l_int|128
)braket
op_assign
id|i
op_plus
l_int|128
suffix:semicolon
)brace
)brace
id|map_initialized
op_assign
l_int|1
suffix:semicolon
)brace
id|out-&gt;Len
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
op_amp
id|out-&gt;Len
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_star
id|count
OL
id|HFS_NAMELEN
)paren
)paren
(brace
id|c
op_assign
op_star
id|in
op_increment
suffix:semicolon
(paren
op_star
id|count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;:&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;|&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
OL
l_int|128
op_logical_or
op_logical_neg
(paren
op_star
id|p
op_assign
id|latin2mac_map
(braket
id|c
op_minus
l_int|128
)braket
)paren
)paren
(brace
op_star
id|p
op_assign
id|c
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|len
OL
l_int|2
)paren
op_logical_or
(paren
(paren
id|hi
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|0
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
(paren
(paren
id|lo
op_assign
id|dehex
c_func
(paren
id|in
(braket
l_int|1
)braket
)paren
)paren
op_amp
l_int|0xf0
)paren
op_logical_or
op_logical_neg
(paren
id|code
op_assign
(paren
id|hi
op_lshift
l_int|4
)paren
op_or
id|lo
)paren
op_logical_or
(paren
id|code
op_eq
l_char|&squot;:&squot;
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|code
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|in
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
)brace
eof