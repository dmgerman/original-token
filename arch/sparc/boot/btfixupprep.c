multiline_comment|/* $Id: btfixupprep.c,v 1.3 1998/03/09 14:03:10 jj Exp $&n;   Simple utility to prepare vmlinux image for sparc.&n;   Resolves all BTFIXUP uses and settings and creates&n;   a special .s object to link to the image.&n;   &n;   Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;   &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;malloc.h&gt;
DECL|macro|MAXSYMS
mdefine_line|#define MAXSYMS 1024
DECL|variable|relrec
r_static
r_char
op_star
id|relrec
op_assign
l_string|&quot;RELOCATION RECORDS FOR [&quot;
suffix:semicolon
DECL|variable|rellen
r_static
r_int
id|rellen
suffix:semicolon
r_struct
id|_btfixup
suffix:semicolon
DECL|struct|_btfixuprel
r_typedef
r_struct
id|_btfixuprel
(brace
DECL|member|sect
r_char
op_star
id|sect
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|f
r_struct
id|_btfixup
op_star
id|f
suffix:semicolon
DECL|member|frel
r_int
id|frel
suffix:semicolon
DECL|member|next
r_struct
id|_btfixuprel
op_star
id|next
suffix:semicolon
DECL|typedef|btfixuprel
)brace
id|btfixuprel
suffix:semicolon
DECL|struct|_btfixup
r_typedef
r_struct
id|_btfixup
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|setinitval
r_int
id|setinitval
suffix:semicolon
DECL|member|initval
r_int
r_int
id|initval
suffix:semicolon
DECL|member|initvalstr
r_char
op_star
id|initvalstr
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|rel
id|btfixuprel
op_star
id|rel
suffix:semicolon
DECL|typedef|btfixup
)brace
id|btfixup
suffix:semicolon
DECL|variable|array
id|btfixup
id|array
(braket
id|MAXSYMS
)braket
suffix:semicolon
DECL|variable|last
r_int
id|last
op_assign
l_int|0
suffix:semicolon
DECL|variable|buffer
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|lastfoffset
r_int
r_int
id|lastfoffset
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|lastfrelno
r_int
r_int
id|lastfrelno
suffix:semicolon
DECL|variable|lastf
id|btfixup
op_star
id|lastf
suffix:semicolon
r_void
id|fatal
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|fatal
r_void
id|fatal
c_func
(paren
r_void
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Malformed output from objdump&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|find
id|btfixup
op_star
id|find
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|array
(braket
id|i
)braket
dot
id|type
op_eq
id|type
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|array
(braket
id|i
)braket
dot
id|name
comma
id|name
)paren
)paren
r_return
id|array
op_plus
id|i
suffix:semicolon
)brace
id|array
(braket
id|last
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|array
(braket
id|last
)braket
dot
id|name
op_assign
id|strdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|array
(braket
id|last
)braket
dot
id|setinitval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|array
(braket
id|last
)braket
dot
id|name
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
id|array
(braket
id|last
)braket
dot
id|rel
op_assign
l_int|NULL
suffix:semicolon
id|last
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|last
op_ge
id|MAXSYMS
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ugh. Something strange. More than %d different BTFIXUP symbols&bslash;n&quot;
comma
id|MAXSYMS
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|array
op_plus
id|last
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_char
op_star
id|sect
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_int
r_int
id|initval
suffix:semicolon
r_int
id|shift
suffix:semicolon
id|btfixup
op_star
id|f
suffix:semicolon
id|btfixuprel
op_star
id|r
comma
op_star
op_star
id|rr
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_char
op_star
id|initvalstr
suffix:semicolon
id|rellen
op_assign
id|strlen
c_func
(paren
id|relrec
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
(paren
id|buffer
comma
l_int|1024
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|buffer
comma
id|relrec
comma
id|rellen
)paren
)paren
r_goto
id|main1
suffix:semicolon
id|fatal
c_func
(paren
)paren
suffix:semicolon
id|main1
suffix:colon
id|sect
op_assign
id|malloc
c_func
(paren
id|strlen
(paren
id|buffer
op_plus
id|rellen
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sect
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
id|strcpy
(paren
id|sect
comma
id|buffer
op_plus
id|rellen
)paren
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|sect
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fgets
(paren
id|buffer
comma
l_int|1024
comma
id|stdin
)paren
op_eq
l_int|NULL
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
(paren
id|buffer
comma
l_int|1024
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|buffer
comma
id|relrec
comma
id|rellen
)paren
)paren
r_goto
id|main1
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strlen
(paren
id|buffer
)paren
OL
l_int|30
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|8
comma
l_string|&quot; R_SPARC_&quot;
comma
l_int|9
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|27
)braket
op_ne
l_char|&squot;_&squot;
op_logical_or
id|buffer
(braket
l_int|28
)braket
op_ne
l_char|&squot;_&squot;
op_logical_or
id|buffer
(braket
l_int|29
)braket
op_ne
l_char|&squot;_&squot;
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|buffer
(braket
l_int|30
)braket
)paren
(brace
r_case
l_char|&squot;f&squot;
suffix:colon
multiline_comment|/* CALL */
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* BLACKBOX */
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* SIMM13 */
r_case
l_char|&squot;a&squot;
suffix:colon
multiline_comment|/* HALF */
r_case
l_char|&squot;h&squot;
suffix:colon
multiline_comment|/* SETHI */
r_case
l_char|&squot;i&squot;
suffix:colon
multiline_comment|/* INT */
r_break
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
id|p
op_assign
id|strchr
(paren
id|buffer
op_plus
l_int|32
comma
l_char|&squot;+&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|shift
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|31
)braket
op_eq
l_char|&squot;s&squot;
op_logical_and
id|buffer
(braket
l_int|32
)braket
op_eq
l_char|&squot;_&squot;
)paren
(brace
id|shift
op_assign
l_int|33
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
(paren
id|sect
comma
l_string|&quot;.text.init&quot;
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong use of &squot;%s&squot; BTFIXUPSET.&bslash;nBTFIXUPSET_CALL can be used only in __init sections&bslash;n&quot;
comma
id|buffer
op_plus
id|shift
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|buffer
(braket
l_int|31
)braket
op_ne
l_char|&squot;_&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
(paren
id|sect
comma
l_string|&quot;.text&quot;
)paren
op_logical_and
id|strcmp
(paren
id|sect
comma
l_string|&quot;.text.init&quot;
)paren
op_logical_and
(paren
id|strcmp
(paren
id|sect
comma
l_string|&quot;__ksymtab&quot;
)paren
op_logical_or
id|buffer
(braket
l_int|30
)braket
op_ne
l_char|&squot;f&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
l_int|30
)braket
op_eq
l_char|&squot;f&squot;
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong use of &squot;%s&squot; in &squot;%s&squot; section. It can be only used in .text, .text.init and __ksymtab&bslash;n&quot;
comma
id|buffer
op_plus
id|shift
comma
id|sect
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong use of &squot;%s&squot; in &squot;%s&squot; section. It can be only used in .text and .text.init&bslash;n&quot;
comma
id|buffer
op_plus
id|shift
comma
id|sect
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|p
op_assign
id|strstr
(paren
id|buffer
op_plus
id|shift
comma
l_string|&quot;__btset_&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
id|buffer
(braket
l_int|31
)braket
op_eq
l_char|&squot;s&squot;
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;__btset_ in BTFIXUP name can only be used when defining the variable, not for setting&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|initval
op_assign
l_int|0
suffix:semicolon
id|initvalstr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|8
)braket
op_ne
l_char|&squot;0&squot;
op_logical_or
id|p
(braket
l_int|9
)braket
op_ne
l_char|&squot;x&squot;
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Pre-initialized values can be only initialized with hexadecimal constants starting 0x&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|initval
op_assign
id|strtoul
c_func
(paren
id|p
op_plus
l_int|10
comma
op_amp
id|q
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|q
op_logical_or
op_logical_neg
id|initval
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Pre-initialized values can be only in the form name__btset_0xXXXXXXXX where X are hex digits.&bslash;nThey cannot be name__btset_0x00000000 though. Use BTFIXUPDEF_XX instead of BTFIXUPDEF_XX_INIT then.&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|initvalstr
op_assign
id|p
op_plus
l_int|10
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
id|f
op_assign
id|find
c_func
(paren
id|buffer
(braket
l_int|30
)braket
comma
id|buffer
op_plus
id|shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|31
)braket
op_eq
l_char|&squot;s&squot;
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|buffer
(braket
l_int|30
)braket
)paren
(brace
r_case
l_char|&squot;f&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Cannot use pre-initalized fixups for calls&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|sect
comma
l_string|&quot;__ksymtab&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;32        &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_CALL in EXPORT_SYMBOL results in relocation other than R_SPARC_32&bslash;n&bslash;%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;WDISP30   &quot;
comma
l_int|10
)paren
op_logical_and
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;HI22      &quot;
comma
l_int|10
)paren
op_logical_and
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;LO10      &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_CALL results in relocation other than R_SPARC_WDISP30, R_SPARC_HI22 or R_SPARC_LO10&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Cannot use pre-initialized fixups for blackboxes&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;HI22      &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_BLACKBOX results in relocation other than R_SPARC_HI22&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
op_plus
l_int|0x1000
op_ge
l_int|0x2000
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong initializer for SIMM13. Has to be from $fffff000 to $00000fff&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;13        &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_SIMM13 results in relocation other than R_SPARC_13&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
op_plus
l_int|0x1000
op_ge
l_int|0x2000
op_logical_and
(paren
id|initval
op_amp
l_int|0x3ff
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong initializer for HALF.&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;13        &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_HALF results in relocation other than R_SPARC_13&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
op_amp
l_int|0x3ff
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Wrong initializer for SETHI. Cannot have set low 10 bits&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;HI22      &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_SETHI results in relocation other than R_SPARC_HI22&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
r_if
c_cond
(paren
id|initval
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Cannot use pre-initalized fixups for INT&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;HI22      &quot;
comma
l_int|10
)paren
op_logical_and
id|strncmp
(paren
id|buffer
op_plus
l_int|17
comma
l_string|&quot;LO10      &quot;
comma
l_int|10
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;BTFIXUP_INT results in relocation other than R_SPARC_HI22 and R_SPARC_LO10&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;setinitval
)paren
(brace
id|f-&gt;initval
op_assign
id|initval
suffix:semicolon
r_if
c_cond
(paren
id|initvalstr
)paren
(brace
id|f-&gt;initvalstr
op_assign
id|strdup
c_func
(paren
id|initvalstr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;initvalstr
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
)brace
id|f-&gt;setinitval
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|f-&gt;initval
op_ne
id|initval
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Btfixup %s previously used with initializer %s which doesn&squot;t match with current initializer&bslash;n%s&bslash;n&quot;
comma
id|f-&gt;name
comma
id|f-&gt;initvalstr
ques
c_cond
suffix:colon
l_string|&quot;0x00000000&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|initval
op_logical_and
id|strcmp
c_func
(paren
id|f-&gt;initvalstr
comma
id|initvalstr
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Btfixup %s previously used with initializer %s which doesn&squot;t match with current initializer.&bslash;n&quot;
l_string|&quot;Initializers have to match literally as well.&bslash;n%s&bslash;n&quot;
comma
id|f-&gt;name
comma
id|f-&gt;initvalstr
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|strtoul
c_func
(paren
id|buffer
comma
op_amp
id|q
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
op_ne
id|buffer
op_plus
l_int|8
op_logical_or
(paren
op_logical_neg
id|offset
op_logical_and
id|strncmp
(paren
id|buffer
comma
l_string|&quot;00000000 &quot;
comma
l_int|9
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Malformed relocation address in&bslash;n%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
comma
id|r
op_assign
id|f-&gt;rel
comma
id|rr
op_assign
op_amp
id|f-&gt;rel
suffix:semicolon
id|r
suffix:semicolon
id|rr
op_assign
op_amp
id|r-&gt;next
comma
id|r
op_assign
id|r-&gt;next
comma
id|k
op_increment
)paren
r_if
c_cond
(paren
id|r-&gt;offset
op_eq
id|offset
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|r-&gt;sect
comma
id|sect
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ugh. One address has two relocation records&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
op_star
id|rr
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
id|btfixuprel
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|rr
)paren
id|fatal
c_func
(paren
)paren
suffix:semicolon
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|offset
op_assign
id|offset
suffix:semicolon
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|f
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|30
)braket
op_eq
l_char|&squot;f&squot;
)paren
(brace
id|lastf
op_assign
id|f
suffix:semicolon
id|lastfoffset
op_assign
id|offset
suffix:semicolon
id|lastfrelno
op_assign
id|k
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lastfoffset
op_plus
l_int|4
op_eq
id|offset
)paren
(brace
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|f
op_assign
id|lastf
suffix:semicolon
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|frel
op_assign
id|lastfrelno
suffix:semicolon
)brace
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|sect
op_assign
id|sect
suffix:semicolon
(paren
op_star
id|rr
)paren
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;! Generated by btfixupprep. Do not edit.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;t.section&bslash;t&bslash;&quot;.data.init&bslash;&quot;,#alloc,#write&bslash;n&bslash;t.align&bslash;t4&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;t.global&bslash;t___btfixup_start&bslash;n___btfixup_start:&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
op_assign
id|array
op_plus
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;t.global&bslash;t___%cs_%s&bslash;n&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;type
op_eq
l_char|&squot;f&squot;
)paren
id|printf
c_func
(paren
l_string|&quot;___%cs_%s:&bslash;n&bslash;t.word 0x%08x,0,0,&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
comma
id|f-&gt;type
op_lshift
l_int|24
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;___%cs_%s:&bslash;n&bslash;t.word 0x%08x,0,&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
comma
id|f-&gt;type
op_lshift
l_int|24
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
comma
id|r
op_assign
id|f-&gt;rel
suffix:semicolon
id|r
op_ne
l_int|NULL
suffix:semicolon
id|j
op_increment
comma
id|r
op_assign
id|r-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
)paren
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&bslash;t.word&bslash;t&quot;
comma
id|j
op_star
l_int|2
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|f-&gt;rel
comma
id|j
op_decrement
suffix:semicolon
id|r
op_ne
l_int|NULL
suffix:semicolon
id|j
op_decrement
comma
id|r
op_assign
id|r-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|r-&gt;sect
comma
l_string|&quot;.text&quot;
)paren
)paren
id|printf
(paren
l_string|&quot;_stext+0x%08x&quot;
comma
id|r-&gt;offset
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|r-&gt;sect
comma
l_string|&quot;.text.init&quot;
)paren
)paren
id|printf
(paren
l_string|&quot;__init_begin+0x%08x&quot;
comma
id|r-&gt;offset
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|r-&gt;sect
comma
l_string|&quot;__ksymtab&quot;
)paren
)paren
id|printf
(paren
l_string|&quot;__start___ksymtab+0x%08x&quot;
comma
id|r-&gt;offset
)paren
suffix:semicolon
r_else
id|fatal
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;type
op_eq
l_char|&squot;f&squot;
op_logical_or
op_logical_neg
id|r-&gt;f
)paren
id|printf
(paren
l_string|&quot;,0&quot;
)paren
suffix:semicolon
r_else
id|printf
(paren
l_string|&quot;,___fs_%s+0x%08x&quot;
comma
id|r-&gt;f-&gt;name
comma
(paren
l_int|4
op_plus
id|r-&gt;frel
op_star
l_int|2
)paren
op_star
l_int|4
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
)paren
id|printf
(paren
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_else
id|printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&bslash;t.global&bslash;t___btfixup_end&bslash;n___btfixup_end:&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&bslash;n! Define undefined references&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
op_assign
id|array
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;type
op_eq
l_char|&squot;f&squot;
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t.global&bslash;t___f_%s&bslash;n&quot;
comma
id|f-&gt;name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;___f_%s:&bslash;n&quot;
comma
id|f-&gt;name
)paren
suffix:semicolon
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;tretl&bslash;n&bslash;t nop&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
op_assign
id|array
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;type
op_ne
l_char|&squot;f&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;initval
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t.global&bslash;t___%c_%s&bslash;n&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;___%c_%s = 0&bslash;n&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t.global&bslash;t___%c_%s__btset_0x%s&bslash;n&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
comma
id|f-&gt;initvalstr
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;___%c_%s__btset_0x%s = 0x%08x&bslash;n&quot;
comma
id|f-&gt;type
comma
id|f-&gt;name
comma
id|f-&gt;initvalstr
comma
id|f-&gt;initval
)paren
suffix:semicolon
)brace
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
