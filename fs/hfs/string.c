multiline_comment|/*&n; * linux/fs/hfs/string.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file contains the string comparison function for the&n; * Macintosh character set.&n; *&n; * The code in this file is derived from code which is copyright&n; * 1986, 1989, 1990 by Abacus Research and Development, Inc. (ARDI)&n; * It is used here by the permission of ARDI&squot;s president Cliff Matthews.&n; *&n; * If you discover bugs in this code please notify both the author of the&n; * Linux HFS file system: hargrove@sccm.stanford.edu (Paul H. Hargrove)&n; * and the author of ARDI&squot;s HFS code: ctm@ardi.com (Clifford T. Matthews)&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; */
macro_line|#include &quot;hfs.h&quot;
multiline_comment|/*================ File-local variables ================*/
multiline_comment|/*&n; * unsigned char caseorder[]&n; *&n; * Defines the lexical ordering of characters on the Macintosh&n; *&n; * Composition of the &squot;casefold&squot; and &squot;order&squot; tables from ARDI&squot;s code&n; * with the entry for 0x20 changed to match that for 0xCA to remove&n; * special case for those two characters.&n; */
DECL|variable|caseorder
r_static
r_int
r_char
id|caseorder
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0A
comma
l_int|0x0B
comma
l_int|0x0C
comma
l_int|0x0D
comma
l_int|0x0E
comma
l_int|0x0F
comma
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1A
comma
l_int|0x1B
comma
l_int|0x1C
comma
l_int|0x1D
comma
l_int|0x1E
comma
l_int|0x1F
comma
l_int|0x20
comma
l_int|0x22
comma
l_int|0x23
comma
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2A
comma
l_int|0x2B
comma
l_int|0x2C
comma
l_int|0x2F
comma
l_int|0x30
comma
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3A
comma
l_int|0x3B
comma
l_int|0x3C
comma
l_int|0x3D
comma
l_int|0x3E
comma
l_int|0x3F
comma
l_int|0x40
comma
l_int|0x41
comma
l_int|0x42
comma
l_int|0x43
comma
l_int|0x44
comma
l_int|0x45
comma
l_int|0x46
comma
l_int|0x47
comma
l_int|0x48
comma
l_int|0x57
comma
l_int|0x59
comma
l_int|0x5D
comma
l_int|0x5F
comma
l_int|0x66
comma
l_int|0x68
comma
l_int|0x6A
comma
l_int|0x6C
comma
l_int|0x72
comma
l_int|0x74
comma
l_int|0x76
comma
l_int|0x78
comma
l_int|0x7A
comma
l_int|0x7E
comma
l_int|0x8C
comma
l_int|0x8E
comma
l_int|0x90
comma
l_int|0x92
comma
l_int|0x95
comma
l_int|0x97
comma
l_int|0x9E
comma
l_int|0xA0
comma
l_int|0xA2
comma
l_int|0xA4
comma
l_int|0xA7
comma
l_int|0xA9
comma
l_int|0xAA
comma
l_int|0xAB
comma
l_int|0xAC
comma
l_int|0xAD
comma
l_int|0x4E
comma
l_int|0x48
comma
l_int|0x57
comma
l_int|0x59
comma
l_int|0x5D
comma
l_int|0x5F
comma
l_int|0x66
comma
l_int|0x68
comma
l_int|0x6A
comma
l_int|0x6C
comma
l_int|0x72
comma
l_int|0x74
comma
l_int|0x76
comma
l_int|0x78
comma
l_int|0x7A
comma
l_int|0x7E
comma
l_int|0x8C
comma
l_int|0x8E
comma
l_int|0x90
comma
l_int|0x92
comma
l_int|0x95
comma
l_int|0x97
comma
l_int|0x9E
comma
l_int|0xA0
comma
l_int|0xA2
comma
l_int|0xA4
comma
l_int|0xA7
comma
l_int|0xAF
comma
l_int|0xB0
comma
l_int|0xB1
comma
l_int|0xB2
comma
l_int|0xB3
comma
l_int|0x4A
comma
l_int|0x4C
comma
l_int|0x5A
comma
l_int|0x60
comma
l_int|0x7B
comma
l_int|0x7F
comma
l_int|0x98
comma
l_int|0x4F
comma
l_int|0x49
comma
l_int|0x51
comma
l_int|0x4A
comma
l_int|0x4B
comma
l_int|0x4C
comma
l_int|0x5A
comma
l_int|0x60
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x6E
comma
l_int|0x6F
comma
l_int|0x70
comma
l_int|0x71
comma
l_int|0x7B
comma
l_int|0x84
comma
l_int|0x85
comma
l_int|0x86
comma
l_int|0x7F
comma
l_int|0x80
comma
l_int|0x9A
comma
l_int|0x9B
comma
l_int|0x9C
comma
l_int|0x98
comma
l_int|0xB4
comma
l_int|0xB5
comma
l_int|0xB6
comma
l_int|0xB7
comma
l_int|0xB8
comma
l_int|0xB9
comma
l_int|0xBA
comma
l_int|0x94
comma
l_int|0xBB
comma
l_int|0xBC
comma
l_int|0xBD
comma
l_int|0xBE
comma
l_int|0xBF
comma
l_int|0xC0
comma
l_int|0x4D
comma
l_int|0x81
comma
l_int|0xC1
comma
l_int|0xC2
comma
l_int|0xC3
comma
l_int|0xC4
comma
l_int|0xC5
comma
l_int|0xC6
comma
l_int|0xC7
comma
l_int|0xC8
comma
l_int|0xC9
comma
l_int|0xCA
comma
l_int|0xCB
comma
l_int|0x55
comma
l_int|0x8A
comma
l_int|0xCC
comma
l_int|0x4D
comma
l_int|0x81
comma
l_int|0xCD
comma
l_int|0xCE
comma
l_int|0xCF
comma
l_int|0xD0
comma
l_int|0xD1
comma
l_int|0xD2
comma
l_int|0xD3
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0xD4
comma
l_int|0x20
comma
l_int|0x49
comma
l_int|0x4B
comma
l_int|0x80
comma
l_int|0x82
comma
l_int|0x82
comma
l_int|0xD5
comma
l_int|0xD6
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x2D
comma
l_int|0x2E
comma
l_int|0xD7
comma
l_int|0xD8
comma
l_int|0xA6
comma
l_int|0xD9
comma
l_int|0xDA
comma
l_int|0xDB
comma
l_int|0xDC
comma
l_int|0xDD
comma
l_int|0xDE
comma
l_int|0xDF
comma
l_int|0xE0
comma
l_int|0xE1
comma
l_int|0xE2
comma
l_int|0xE3
comma
l_int|0xE4
comma
l_int|0xE5
comma
l_int|0xE6
comma
l_int|0xE7
comma
l_int|0xE8
comma
l_int|0xE9
comma
l_int|0xEA
comma
l_int|0xEB
comma
l_int|0xEC
comma
l_int|0xED
comma
l_int|0xEE
comma
l_int|0xEF
comma
l_int|0xF0
comma
l_int|0xF1
comma
l_int|0xF2
comma
l_int|0xF3
comma
l_int|0xF4
comma
l_int|0xF5
comma
l_int|0xF6
comma
l_int|0xF7
comma
l_int|0xF8
comma
l_int|0xF9
comma
l_int|0xFA
comma
l_int|0xFB
comma
l_int|0xFC
comma
l_int|0xFD
comma
l_int|0xFE
comma
l_int|0xFF
)brace
suffix:semicolon
multiline_comment|/*&n; * unsigned char casefold[]&n; *&n; * Defines the mapping to lowercase characters on the Macintosh&n; *&n; * &quot;Inverse&quot; of the &squot;casefold&squot; from ARDI&squot;s code.&n; */
DECL|variable|casefold
r_static
r_int
r_char
id|casefold
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0A
comma
l_int|0x0B
comma
l_int|0x0C
comma
l_int|0x0D
comma
l_int|0x0E
comma
l_int|0x0F
comma
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1A
comma
l_int|0x1B
comma
l_int|0x1C
comma
l_int|0x1D
comma
l_int|0x1E
comma
l_int|0x1F
comma
l_int|0x20
comma
l_int|0x21
comma
l_int|0x22
comma
l_int|0x23
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2A
comma
l_int|0x2B
comma
l_int|0x2C
comma
l_int|0x2D
comma
l_int|0x2E
comma
l_int|0x2F
comma
l_int|0x30
comma
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3A
comma
l_int|0x3B
comma
l_int|0x3C
comma
l_int|0x3D
comma
l_int|0x3E
comma
l_int|0x3F
comma
l_int|0x40
comma
l_int|0x61
comma
l_int|0x62
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x67
comma
l_int|0x68
comma
l_int|0x69
comma
l_int|0x6A
comma
l_int|0x6B
comma
l_int|0x6C
comma
l_int|0x6D
comma
l_int|0x6E
comma
l_int|0x6F
comma
l_int|0x70
comma
l_int|0x71
comma
l_int|0x72
comma
l_int|0x73
comma
l_int|0x74
comma
l_int|0x75
comma
l_int|0x76
comma
l_int|0x77
comma
l_int|0x78
comma
l_int|0x79
comma
l_int|0x7A
comma
l_int|0x5B
comma
l_int|0x5C
comma
l_int|0x5D
comma
l_int|0x5E
comma
l_int|0x5F
comma
l_int|0x41
comma
l_int|0x61
comma
l_int|0x62
comma
l_int|0x63
comma
l_int|0x64
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x67
comma
l_int|0x68
comma
l_int|0x69
comma
l_int|0x6A
comma
l_int|0x6B
comma
l_int|0x6C
comma
l_int|0x6D
comma
l_int|0x6E
comma
l_int|0x6F
comma
l_int|0x70
comma
l_int|0x71
comma
l_int|0x72
comma
l_int|0x73
comma
l_int|0x74
comma
l_int|0x75
comma
l_int|0x76
comma
l_int|0x77
comma
l_int|0x78
comma
l_int|0x79
comma
l_int|0x7A
comma
l_int|0x7B
comma
l_int|0x7C
comma
l_int|0x7D
comma
l_int|0x7E
comma
l_int|0x7F
comma
l_int|0x8A
comma
l_int|0x8C
comma
l_int|0x8D
comma
l_int|0x8E
comma
l_int|0x96
comma
l_int|0x9A
comma
l_int|0x9F
comma
l_int|0x87
comma
l_int|0x88
comma
l_int|0x89
comma
l_int|0x8A
comma
l_int|0x8B
comma
l_int|0x8C
comma
l_int|0x8D
comma
l_int|0x8E
comma
l_int|0x8F
comma
l_int|0x90
comma
l_int|0x91
comma
l_int|0x92
comma
l_int|0x93
comma
l_int|0x94
comma
l_int|0x95
comma
l_int|0x96
comma
l_int|0x97
comma
l_int|0x98
comma
l_int|0x99
comma
l_int|0x9A
comma
l_int|0x9B
comma
l_int|0x9C
comma
l_int|0x9D
comma
l_int|0x9E
comma
l_int|0x9F
comma
l_int|0xA0
comma
l_int|0xA1
comma
l_int|0xA2
comma
l_int|0xA3
comma
l_int|0xA4
comma
l_int|0xA5
comma
l_int|0xA6
comma
l_int|0xA7
comma
l_int|0xA8
comma
l_int|0xA9
comma
l_int|0xAA
comma
l_int|0xAB
comma
l_int|0xAC
comma
l_int|0xAD
comma
l_int|0xBE
comma
l_int|0xBF
comma
l_int|0xB0
comma
l_int|0xB1
comma
l_int|0xB2
comma
l_int|0xB3
comma
l_int|0xB4
comma
l_int|0xB5
comma
l_int|0xB6
comma
l_int|0xB7
comma
l_int|0xB8
comma
l_int|0xB9
comma
l_int|0xBA
comma
l_int|0xBB
comma
l_int|0xBC
comma
l_int|0xBD
comma
l_int|0xBE
comma
l_int|0xBF
comma
l_int|0xC0
comma
l_int|0xC1
comma
l_int|0xC2
comma
l_int|0xC3
comma
l_int|0xC4
comma
l_int|0xC5
comma
l_int|0xC6
comma
l_int|0xC7
comma
l_int|0xC8
comma
l_int|0xC9
comma
l_int|0xCA
comma
l_int|0x88
comma
l_int|0x8B
comma
l_int|0x9B
comma
l_int|0xCF
comma
l_int|0xCF
comma
l_int|0xD0
comma
l_int|0xD1
comma
l_int|0xD2
comma
l_int|0xD3
comma
l_int|0xD4
comma
l_int|0xD5
comma
l_int|0xD6
comma
l_int|0xD7
comma
l_int|0xD8
comma
l_int|0xD9
comma
l_int|0xDA
comma
l_int|0xDB
comma
l_int|0xDC
comma
l_int|0xDD
comma
l_int|0xDE
comma
l_int|0xDF
comma
l_int|0xE0
comma
l_int|0xE1
comma
l_int|0xE2
comma
l_int|0xE3
comma
l_int|0xE4
comma
l_int|0xE5
comma
l_int|0xE6
comma
l_int|0xE7
comma
l_int|0xE8
comma
l_int|0xE9
comma
l_int|0xEA
comma
l_int|0xEB
comma
l_int|0xEC
comma
l_int|0xED
comma
l_int|0xEE
comma
l_int|0xEF
comma
l_int|0xF0
comma
l_int|0xF1
comma
l_int|0xF2
comma
l_int|0xF3
comma
l_int|0xF4
comma
l_int|0xF5
comma
l_int|0xF6
comma
l_int|0xF7
comma
l_int|0xF8
comma
l_int|0xF9
comma
l_int|0xFA
comma
l_int|0xFB
comma
l_int|0xFC
comma
l_int|0xFD
comma
l_int|0xFE
comma
l_int|0xFF
)brace
suffix:semicolon
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * Hash a string to an integer in a case-independent way&n; */
DECL|function|hfs_strhash
r_int
r_int
id|hfs_strhash
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|hash
op_assign
id|init_name_hash
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|caseorder
(braket
op_star
id|name
op_increment
)braket
comma
id|hash
)paren
suffix:semicolon
r_return
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Compare two strings in the HFS filename character ordering&n; * Returns positive, negative, or zero, not just 0 or (+/-)1&n; *&n; * Equivalent to ARDI&squot;s call:&n; *&t;ROMlib_RelString(s1+1, s2+1, true, false, (s1[0]&lt;&lt;16) | s2[0])&n; */
DECL|function|hfs_strcmp
r_int
id|hfs_strcmp
c_func
(paren
r_const
r_int
r_char
op_star
id|s1
comma
r_int
r_int
id|len1
comma
r_const
r_int
r_char
op_star
id|s2
comma
r_int
r_int
id|len2
)paren
(brace
r_int
id|len
comma
id|tmp
suffix:semicolon
id|len
op_assign
(paren
id|len1
OG
id|len2
)paren
ques
c_cond
id|len2
suffix:colon
id|len1
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
(paren
r_int
)paren
id|caseorder
(braket
op_star
(paren
id|s1
op_increment
)paren
)braket
op_minus
(paren
r_int
)paren
id|caseorder
(braket
op_star
(paren
id|s2
op_increment
)paren
)braket
)paren
)paren
(brace
r_return
id|tmp
suffix:semicolon
)brace
)brace
r_return
id|len1
op_minus
id|len2
suffix:semicolon
)brace
multiline_comment|/*&n; * Test for equality of two strings in the HFS filename character ordering.&n; */
DECL|function|hfs_streq
r_int
id|hfs_streq
c_func
(paren
r_const
r_int
r_char
op_star
id|s1
comma
r_int
r_int
id|len1
comma
r_const
r_int
r_char
op_star
id|s2
comma
r_int
r_int
id|len2
)paren
(brace
r_if
c_cond
(paren
id|len1
op_ne
id|len2
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len1
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|caseorder
(braket
op_star
(paren
id|s1
op_increment
)paren
)braket
op_ne
id|caseorder
(braket
op_star
(paren
id|s2
op_increment
)paren
)braket
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert a string to the Macintosh version of lower case.&n; */
DECL|function|hfs_tolower
r_void
id|hfs_tolower
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
op_star
id|p
op_assign
id|casefold
(braket
op_star
id|p
)braket
suffix:semicolon
op_increment
id|p
suffix:semicolon
)brace
)brace
eof
