multiline_comment|/*+M*************************************************************************&n; * Adaptec AIC7770/AIC7870 sequencer code assembler.&n; *&n; * Copyright (c) 1994 John Aycock&n; *   The University of Calgary Department of Computer Science.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Comments are started by `#&squot; and continue to the end of the line; lines&n; * may be of the form:&n; *      &lt;label&gt;*&n; *      &lt;label&gt;*  &lt;undef-sym&gt; = &lt;value&gt;&n; *      &lt;label&gt;*  &lt;opcode&gt; &lt;operand&gt;*&n; *&n; * A &lt;label&gt; is an &lt;undef-sym&gt; ending in a colon.  Spaces, tabs, and commas&n; * are token separators.&n; *&n; *-M*************************************************************************/
DECL|variable|id
r_static
r_char
id|id
(braket
)braket
op_assign
l_string|&quot;$Id: aic7xxx_asm.c,v 1.8 1995/05/25 06:25:36 root Exp $&quot;
suffix:semicolon
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
DECL|macro|MEMORY
mdefine_line|#define MEMORY&t;&t;448
DECL|macro|MAXLINE
mdefine_line|#define MAXLINE&t;&t;1024
DECL|macro|MAXTOKEN
mdefine_line|#define MAXTOKEN&t;32
DECL|macro|ADOTOUT
mdefine_line|#define ADOTOUT&t;&t;&quot;a.out&quot;
DECL|macro|NOVALUE
mdefine_line|#define NOVALUE&t;&t;-1
multiline_comment|/*&n; * AIC-7770/AIC-7870 register definitions&n; */
DECL|macro|R_SINDEX
mdefine_line|#define R_SINDEX&t;0x65
DECL|macro|R_ALLONES
mdefine_line|#define R_ALLONES&t;0x69
DECL|macro|R_ALLZEROS
mdefine_line|#define R_ALLZEROS&t;0x6a
DECL|macro|R_NONE
mdefine_line|#define R_NONE&t;&t;0x6a
DECL|variable|debug
r_int
id|debug
suffix:semicolon
DECL|variable|lineno
DECL|variable|LC
r_int
id|lineno
comma
id|LC
suffix:semicolon
DECL|variable|filename
r_char
op_star
id|filename
suffix:semicolon
DECL|variable|ifp
DECL|variable|ofp
id|FILE
op_star
id|ifp
comma
op_star
id|ofp
suffix:semicolon
DECL|variable|M
r_int
r_char
id|M
(braket
id|MEMORY
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_void
DECL|function|error
id|error
c_func
(paren
r_char
op_star
id|s
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s at line %d&bslash;n&quot;
comma
id|filename
comma
id|s
comma
id|lineno
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|Malloc
id|Malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|p
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|error
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_void
op_star
DECL|function|Realloc
id|Realloc
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|p
op_assign
id|realloc
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|error
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_char
op_star
DECL|function|Strdup
id|Strdup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|Malloc
c_func
(paren
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
id|s
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|struct|sym_t
r_typedef
r_struct
id|sym_t
(brace
DECL|member|next
r_struct
id|sym_t
op_star
id|next
suffix:semicolon
multiline_comment|/* MUST BE FIRST */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|member|npatch
r_int
id|npatch
suffix:semicolon
DECL|member|patch
r_int
op_star
id|patch
suffix:semicolon
DECL|typedef|sym_t
)brace
id|sym_t
suffix:semicolon
DECL|variable|head
id|sym_t
op_star
id|head
suffix:semicolon
r_void
DECL|function|define
id|define
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|value
)paren
(brace
id|sym_t
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head
comma
id|q
op_assign
(paren
id|sym_t
op_star
)paren
op_amp
id|head
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;name
comma
id|name
)paren
)paren
id|error
c_func
(paren
l_string|&quot;redefined symbol&quot;
)paren
suffix:semicolon
id|q
op_assign
id|p
suffix:semicolon
)brace
id|p
op_assign
id|q-&gt;next
op_assign
(paren
id|sym_t
op_star
)paren
id|Malloc
c_func
(paren
r_sizeof
(paren
id|sym_t
)paren
)paren
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;name
op_assign
id|Strdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|p-&gt;value
op_assign
id|value
suffix:semicolon
id|p-&gt;npatch
op_assign
l_int|0
suffix:semicolon
id|p-&gt;patch
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;&quot;%s&bslash;&quot; &quot;
comma
id|p-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;value
op_ne
id|NOVALUE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;defined as 0x%x&bslash;n&quot;
comma
id|p-&gt;value
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;undefined&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|sym_t
op_star
DECL|function|lookup
id|lookup
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|sym_t
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;name
comma
id|name
)paren
)paren
r_return
id|p
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|patch
id|patch
c_func
(paren
id|sym_t
op_star
id|p
comma
r_int
id|location
)paren
(brace
id|p-&gt;npatch
op_add_assign
l_int|1
suffix:semicolon
id|p-&gt;patch
op_assign
(paren
r_int
op_star
)paren
id|Realloc
c_func
(paren
id|p-&gt;patch
comma
id|p-&gt;npatch
op_star
r_sizeof
(paren
r_int
op_star
)paren
)paren
suffix:semicolon
id|p-&gt;patch
(braket
id|p-&gt;npatch
op_minus
l_int|1
)braket
op_assign
id|location
suffix:semicolon
)brace
DECL|function|backpatch
r_void
id|backpatch
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|sym_t
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;value
op_eq
id|NOVALUE
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: undefined symbol &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|filename
comma
id|p-&gt;name
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;npatch
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;&quot;%s&bslash;&quot; (0x%x) patched at&quot;
comma
id|p-&gt;name
comma
id|p-&gt;value
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
id|p-&gt;npatch
suffix:semicolon
id|i
op_increment
)paren
(brace
id|M
(braket
id|p-&gt;patch
(braket
id|i
)braket
)braket
(braket
l_int|0
)braket
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|M
(braket
id|p-&gt;patch
(braket
id|i
)braket
)braket
(braket
l_int|0
)braket
op_or_assign
(paren
(paren
id|p-&gt;value
op_rshift
l_int|8
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|M
(braket
id|p-&gt;patch
(braket
id|i
)braket
)braket
(braket
l_int|1
)braket
op_assign
id|p-&gt;value
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; 0x%x&quot;
comma
id|p-&gt;patch
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debug
)paren
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *  Output words in byte-reversed order (least significant first)&n; *  since the sequencer RAM is loaded that way.&n; */
r_void
DECL|function|output
id|output
c_func
(paren
id|FILE
op_star
id|fp
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
id|LC
suffix:semicolon
id|i
op_increment
)paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;&bslash;t0x%02x, 0x%02x, 0x%02x, 0x%02x,&bslash;n&quot;
comma
id|M
(braket
id|i
)braket
(braket
l_int|3
)braket
comma
id|M
(braket
id|i
)braket
(braket
l_int|2
)braket
comma
id|M
(braket
id|i
)braket
(braket
l_int|1
)braket
comma
id|M
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d out of %d instructions used.&bslash;n&quot;
comma
id|LC
comma
id|MEMORY
)paren
suffix:semicolon
)brace
r_char
op_star
op_star
DECL|function|getl
id|getl
c_func
(paren
r_int
op_star
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|quote
suffix:semicolon
r_static
r_char
id|buf
(braket
id|MAXLINE
)braket
suffix:semicolon
r_static
r_char
op_star
id|a
(braket
id|MAXTOKEN
)braket
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|ifp
)paren
)paren
(brace
id|lineno
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|strlen
c_func
(paren
id|buf
)paren
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|error
c_func
(paren
l_string|&quot;line too long&quot;
)paren
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;#&squot;
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
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
id|rescan
suffix:colon
id|quote
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;&bslash;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quote
)paren
op_star
id|quote
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|strtok
c_func
(paren
id|p
comma
l_string|&quot;, &bslash;t&bslash;n&quot;
)paren
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;, &bslash;t&bslash;n&quot;
)paren
)paren
r_if
c_cond
(paren
id|i
OL
id|MAXTOKEN
op_minus
l_int|1
)paren
id|a
(braket
id|i
op_increment
)braket
op_assign
id|p
suffix:semicolon
r_else
id|error
c_func
(paren
l_string|&quot;too many tokens&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quote
)paren
(brace
id|quote
op_increment
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|quote
comma
l_char|&squot;&bslash;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|error
c_func
(paren
l_string|&quot;unterminated string constant&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
id|MAXTOKEN
op_minus
l_int|1
)paren
(brace
id|a
(braket
id|i
op_increment
)braket
op_assign
id|quote
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
r_else
id|error
c_func
(paren
l_string|&quot;too many tokens&quot;
)paren
suffix:semicolon
r_goto
id|rescan
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
)paren
(brace
op_star
id|n
op_assign
id|i
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|A
mdefine_line|#define A&t;0x8000&t;&t;/* `A&squot;ccumulator ok */
DECL|macro|I
mdefine_line|#define I&t;0x4000&t;&t;/* use as immediate value */
DECL|macro|SL
mdefine_line|#define SL&t;0x2000&t;&t;/* shift left */
DECL|macro|SR
mdefine_line|#define SR&t;0x1000&t;&t;/* shift right */
DECL|macro|RL
mdefine_line|#define RL&t;0x0800&t;&t;/* rotate left */
DECL|macro|RR
mdefine_line|#define RR&t;0x0400&t;&t;/* rotate right */
DECL|macro|LO
mdefine_line|#define LO&t;0x8000&t;&t;/* lookup: ori-{jmp,jc,jnc,call} */
DECL|macro|LA
mdefine_line|#define LA&t;0x4000&t;&t;/* lookup: and-{jz,jnz} */
DECL|macro|LX
mdefine_line|#define LX&t;0x2000&t;&t;/* lookup: xor-{je,jne} */
DECL|macro|NA
mdefine_line|#define NA&t;-1&t;&t;/* not applicable */
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:semicolon
multiline_comment|/* number of operands, including opcode */
DECL|member|op
r_int
r_int
id|op
suffix:semicolon
multiline_comment|/* immediate or L?|pos_from_0 */
DECL|member|dest
r_int
r_int
id|dest
suffix:semicolon
multiline_comment|/* NA, pos_from_0, or I|immediate */
DECL|member|src
r_int
r_int
id|src
suffix:semicolon
multiline_comment|/* NA, pos_from_0, or I|immediate */
DECL|member|imm
r_int
r_int
id|imm
suffix:semicolon
multiline_comment|/* pos_from_0, A|pos_from_0, or I|immediate */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* NA or pos_from_0 */
DECL|member|fmt
r_int
id|fmt
suffix:semicolon
multiline_comment|/* instruction format - 1, 2, or 3 */
DECL|variable|instr
)brace
id|instr
(braket
)braket
op_assign
(brace
multiline_comment|/*&n; *&t;&t;  N  OP    DEST&t;&t;SRC&t;&t;IMM&t;ADDR&t;FMT&n; */
(brace
l_string|&quot;mov&quot;
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;mov&quot;
comma
l_int|4
comma
id|LO
op_or
l_int|2
comma
id|NA
comma
l_int|1
comma
id|I
op_or
l_int|0
comma
l_int|3
comma
l_int|3
)brace
comma
(brace
l_string|&quot;mvi&quot;
comma
l_int|3
comma
l_int|0
comma
l_int|1
comma
id|I
op_or
id|R_ALLZEROS
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;mvi&quot;
comma
l_int|4
comma
id|LO
op_or
l_int|2
comma
id|NA
comma
id|I
op_or
id|R_ALLZEROS
comma
l_int|1
comma
l_int|3
comma
l_int|3
)brace
comma
(brace
l_string|&quot;not&quot;
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;and&quot;
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;and&quot;
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
l_int|3
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;or&quot;
comma
l_int|3
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;or&quot;
comma
l_int|4
comma
l_int|0
comma
l_int|1
comma
l_int|3
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;or&quot;
comma
l_int|5
comma
id|LO
op_or
l_int|3
comma
id|NA
comma
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|3
)brace
comma
(brace
l_string|&quot;xor&quot;
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;xor&quot;
comma
l_int|4
comma
l_int|2
comma
l_int|1
comma
l_int|3
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;nop&quot;
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
id|R_NONE
comma
id|I
op_or
id|R_ALLZEROS
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;inc&quot;
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
l_int|1
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;inc&quot;
comma
l_int|3
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
id|I
op_or
l_int|1
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;dec&quot;
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;dec&quot;
comma
l_int|3
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;jmp&quot;
comma
l_int|2
comma
id|LO
op_or
l_int|0
comma
id|NA
comma
id|I
op_or
id|R_SINDEX
comma
id|I
op_or
l_int|0
comma
l_int|1
comma
l_int|3
)brace
comma
(brace
l_string|&quot;jc&quot;
comma
l_int|2
comma
id|LO
op_or
l_int|0
comma
id|NA
comma
id|I
op_or
id|R_SINDEX
comma
id|I
op_or
l_int|0
comma
l_int|1
comma
l_int|3
)brace
comma
(brace
l_string|&quot;jnc&quot;
comma
l_int|2
comma
id|LO
op_or
l_int|0
comma
id|NA
comma
id|I
op_or
id|R_SINDEX
comma
id|I
op_or
l_int|0
comma
l_int|1
comma
l_int|3
)brace
comma
(brace
l_string|&quot;call&quot;
comma
l_int|2
comma
id|LO
op_or
l_int|0
comma
id|NA
comma
id|I
op_or
id|R_SINDEX
comma
id|I
op_or
l_int|0
comma
l_int|1
comma
l_int|3
)brace
comma
(brace
l_string|&quot;test&quot;
comma
l_int|5
comma
id|LA
op_or
l_int|3
comma
id|NA
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
l_int|4
comma
l_int|3
)brace
comma
(brace
l_string|&quot;cmp&quot;
comma
l_int|5
comma
id|LX
op_or
l_int|3
comma
id|NA
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
l_int|4
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ret&quot;
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
id|R_NONE
comma
id|I
op_or
id|R_ALLZEROS
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ret&quot;
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
id|R_NONE
comma
id|I
op_or
id|R_ALLZEROS
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;clc&quot;
comma
l_int|1
comma
l_int|3
comma
id|I
op_or
id|R_NONE
comma
id|I
op_or
id|R_ALLZEROS
comma
id|I
op_or
l_int|1
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;clc&quot;
comma
l_int|4
comma
l_int|3
comma
l_int|2
comma
id|I
op_or
id|R_ALLZEROS
comma
id|A
op_or
l_int|3
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;stc&quot;
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
id|I
op_or
id|R_ALLONES
comma
id|I
op_or
l_int|1
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;add&quot;
comma
l_int|3
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;add&quot;
comma
l_int|4
comma
l_int|3
comma
l_int|1
comma
l_int|3
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;adc&quot;
comma
l_int|3
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;adc&quot;
comma
l_int|4
comma
l_int|4
comma
l_int|1
comma
l_int|3
comma
id|A
op_or
l_int|2
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_string|&quot;shl&quot;
comma
l_int|3
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
id|SL
op_or
l_int|2
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;shl&quot;
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|2
comma
id|SL
op_or
l_int|3
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;shr&quot;
comma
l_int|3
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
id|SR
op_or
l_int|2
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;shr&quot;
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|2
comma
id|SR
op_or
l_int|3
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;rol&quot;
comma
l_int|3
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
id|RL
op_or
l_int|2
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;rol&quot;
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|2
comma
id|RL
op_or
l_int|3
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;ror&quot;
comma
l_int|3
comma
l_int|5
comma
l_int|1
comma
l_int|1
comma
id|RR
op_or
l_int|2
comma
id|NA
comma
l_int|2
)brace
comma
(brace
l_string|&quot;ror&quot;
comma
l_int|4
comma
l_int|5
comma
l_int|1
comma
l_int|2
comma
id|RR
op_or
l_int|3
comma
id|NA
comma
l_int|2
)brace
comma
multiline_comment|/*&n;&t; *  Extensions (note also that mvi allows A)&n;&t; */
(brace
l_string|&quot;clr&quot;
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
id|I
op_or
id|R_ALLZEROS
comma
id|I
op_or
l_int|0xff
comma
id|NA
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
r_int
DECL|function|eval_operand
id|eval_operand
c_func
(paren
r_char
op_star
op_star
id|a
comma
r_int
id|spec
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|want
op_assign
id|spec
op_amp
(paren
id|LO
op_or
id|LA
op_or
id|LX
)paren
suffix:semicolon
r_static
r_struct
(brace
r_int
r_int
id|what
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|value
suffix:semicolon
)brace
id|jmptab
(braket
)braket
op_assign
(brace
(brace
id|LO
comma
l_string|&quot;jmp&quot;
comma
l_int|8
)brace
comma
(brace
id|LO
comma
l_string|&quot;jc&quot;
comma
l_int|9
)brace
comma
(brace
id|LO
comma
l_string|&quot;jnc&quot;
comma
l_int|10
)brace
comma
(brace
id|LO
comma
l_string|&quot;call&quot;
comma
l_int|11
)brace
comma
(brace
id|LA
comma
l_string|&quot;jz&quot;
comma
l_int|15
)brace
comma
(brace
id|LA
comma
l_string|&quot;jnz&quot;
comma
l_int|13
)brace
comma
(brace
id|LX
comma
l_string|&quot;je&quot;
comma
l_int|14
)brace
comma
(brace
id|LX
comma
l_string|&quot;jne&quot;
comma
l_int|12
)brace
comma
)brace
suffix:semicolon
id|spec
op_and_assign
op_complement
(paren
id|LO
op_or
id|LA
op_or
id|LX
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
r_sizeof
(paren
id|jmptab
)paren
op_div
r_sizeof
(paren
id|jmptab
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|jmptab
(braket
id|i
)braket
dot
id|what
op_eq
id|want
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|jmptab
(braket
id|i
)braket
dot
id|name
comma
id|a
(braket
id|spec
)braket
)paren
)paren
(brace
r_return
id|jmptab
(braket
id|i
)braket
dot
id|value
suffix:semicolon
)brace
r_if
c_cond
(paren
id|want
)paren
id|error
c_func
(paren
l_string|&quot;invalid jump&quot;
)paren
suffix:semicolon
r_return
id|spec
suffix:semicolon
multiline_comment|/* &quot;case 0&quot; - no flags set */
)brace
r_int
DECL|function|eval_sdi
id|eval_sdi
c_func
(paren
r_char
op_star
op_star
id|a
comma
r_int
id|spec
)paren
(brace
id|sym_t
op_star
id|p
suffix:semicolon
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|spec
op_eq
id|NA
)paren
r_return
id|NA
suffix:semicolon
r_switch
c_cond
(paren
id|spec
op_amp
(paren
id|A
op_or
id|I
op_or
id|SL
op_or
id|SR
op_or
id|RL
op_or
id|RR
)paren
)paren
(brace
r_case
id|SL
suffix:colon
r_case
id|SR
suffix:colon
r_case
id|RL
suffix:colon
r_case
id|RR
suffix:colon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|a
(braket
id|spec
op_amp
op_complement
(paren
id|SL
op_or
id|SR
op_or
id|RL
op_or
id|RR
)paren
)braket
)paren
)paren
id|val
op_assign
id|strtol
c_func
(paren
id|a
(braket
id|spec
op_amp
op_complement
(paren
id|SL
op_or
id|SR
op_or
id|RL
op_or
id|RR
)paren
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
(brace
id|p
op_assign
id|lookup
c_func
(paren
id|a
(braket
id|spec
op_amp
op_complement
(paren
id|SL
op_or
id|SR
op_or
id|RL
op_or
id|RR
)paren
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|error
c_func
(paren
l_string|&quot;undefined symbol used&quot;
)paren
suffix:semicolon
id|val
op_assign
id|p-&gt;value
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|spec
op_amp
(paren
id|SL
op_or
id|SR
op_or
id|RL
op_or
id|RR
)paren
)paren
(brace
multiline_comment|/* blech */
r_case
id|SL
suffix:colon
r_if
c_cond
(paren
id|val
OG
l_int|7
)paren
r_return
l_int|0xf0
suffix:semicolon
r_return
(paren
(paren
id|val
op_mod
l_int|8
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|val
op_mod
l_int|8
)paren
suffix:semicolon
r_case
id|SR
suffix:colon
r_if
c_cond
(paren
id|val
OG
l_int|7
)paren
r_return
l_int|0xf0
suffix:semicolon
r_return
(paren
(paren
id|val
op_mod
l_int|8
)paren
op_lshift
l_int|4
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
op_or
(paren
(paren
l_int|8
op_minus
(paren
id|val
op_mod
l_int|8
)paren
)paren
op_mod
l_int|8
)paren
suffix:semicolon
r_case
id|RL
suffix:colon
r_return
id|val
op_mod
l_int|8
suffix:semicolon
r_case
id|RR
suffix:colon
r_return
(paren
l_int|8
op_minus
(paren
id|val
op_mod
l_int|8
)paren
)paren
op_mod
l_int|8
suffix:semicolon
)brace
r_case
id|I
suffix:colon
r_return
id|spec
op_amp
op_complement
id|I
suffix:semicolon
r_case
id|A
suffix:colon
multiline_comment|/*&n;&t;&t; *  An immediate field of zero selects&n;&t;&t; *  the accumulator.  Vigorously object&n;&t;&t; *  if zero is given otherwise - it&squot;s&n;&t;&t; *  most likely an error.&n;&t;&t; */
id|spec
op_and_assign
op_complement
id|A
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;A&quot;
comma
id|a
(braket
id|spec
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|a
(braket
id|spec
)braket
)paren
op_logical_and
id|strtol
c_func
(paren
id|a
(braket
id|spec
)braket
comma
l_int|NULL
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;immediate value of zero selects accumulator&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* falls through */
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|a
(braket
id|spec
)braket
)paren
)paren
r_return
id|strtol
c_func
(paren
id|a
(braket
id|spec
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|p
op_assign
id|lookup
c_func
(paren
id|a
(braket
id|spec
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
r_return
id|p-&gt;value
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;undefined symbol used&quot;
)paren
suffix:semicolon
)brace
r_return
id|NA
suffix:semicolon
multiline_comment|/* shut the compiler up */
)brace
r_int
DECL|function|eval_addr
id|eval_addr
c_func
(paren
r_char
op_star
op_star
id|a
comma
r_int
id|spec
)paren
(brace
id|sym_t
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|spec
op_eq
id|NA
)paren
r_return
id|NA
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|a
(braket
id|spec
)braket
)paren
)paren
r_return
id|strtol
c_func
(paren
id|a
(braket
id|spec
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|p
op_assign
id|lookup
c_func
(paren
id|a
(braket
id|spec
)braket
)paren
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
id|p-&gt;value
op_ne
id|NOVALUE
)paren
r_return
id|p-&gt;value
suffix:semicolon
id|patch
c_func
(paren
id|p
comma
id|LC
)paren
suffix:semicolon
)brace
r_else
(brace
id|define
c_func
(paren
id|a
(braket
id|spec
)braket
comma
id|NOVALUE
)paren
suffix:semicolon
id|p
op_assign
id|lookup
c_func
(paren
id|a
(braket
id|spec
)braket
)paren
suffix:semicolon
id|patch
c_func
(paren
id|p
comma
id|LC
)paren
suffix:semicolon
)brace
r_return
id|NA
suffix:semicolon
multiline_comment|/* will be patched in later */
)brace
r_int
DECL|function|crack
id|crack
c_func
(paren
r_char
op_star
op_star
id|a
comma
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|I_imm
comma
id|I_addr
suffix:semicolon
r_int
id|I_op
comma
id|I_dest
comma
id|I_src
comma
id|I_ret
suffix:semicolon
multiline_comment|/*&n;&t; *  Check for &quot;ret&quot; at the end of the line; remove&n;&t; *  it unless it&squot;s &quot;ret&quot; alone - we still want to&n;&t; *  look it up in the table.&n;&t; */
id|I_ret
op_assign
(paren
id|strcmp
c_func
(paren
id|a
(braket
id|n
op_minus
l_int|1
)braket
comma
l_string|&quot;ret&quot;
)paren
ques
c_cond
l_int|0
suffix:colon
op_logical_neg
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|I_ret
op_logical_and
id|n
OG
l_int|1
)paren
id|n
op_sub_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|instr
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; *  Look for match in table given constraints,&n;&t;&t; *  currently just the name and the number of&n;&t;&t; *  operands.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|instr
(braket
id|i
)braket
dot
id|name
comma
op_star
id|a
)paren
op_logical_and
id|instr
(braket
id|i
)braket
dot
id|n
op_eq
id|n
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|instr
(braket
id|i
)braket
dot
id|name
)paren
id|error
c_func
(paren
l_string|&quot;unknown opcode or wrong number of operands&quot;
)paren
suffix:semicolon
id|I_op
op_assign
id|eval_operand
c_func
(paren
id|a
comma
id|instr
(braket
id|i
)braket
dot
id|op
)paren
suffix:semicolon
id|I_src
op_assign
id|eval_sdi
c_func
(paren
id|a
comma
id|instr
(braket
id|i
)braket
dot
id|src
)paren
suffix:semicolon
id|I_imm
op_assign
id|eval_sdi
c_func
(paren
id|a
comma
id|instr
(braket
id|i
)braket
dot
id|imm
)paren
suffix:semicolon
id|I_dest
op_assign
id|eval_sdi
c_func
(paren
id|a
comma
id|instr
(braket
id|i
)braket
dot
id|dest
)paren
suffix:semicolon
id|I_addr
op_assign
id|eval_addr
c_func
(paren
id|a
comma
id|instr
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LC
op_ge
id|MEMORY
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Memory exhausted!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|instr
(braket
id|i
)braket
dot
id|fmt
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|M
(braket
id|LC
)braket
(braket
l_int|0
)braket
op_assign
(paren
id|I_op
op_lshift
l_int|1
)paren
op_or
id|I_ret
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|1
)braket
op_assign
id|I_dest
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|2
)braket
op_assign
id|I_src
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|3
)braket
op_assign
id|I_imm
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|I_ret
)paren
id|error
c_func
(paren
l_string|&quot;illegal use of &bslash;&quot;ret&bslash;&quot;&quot;
)paren
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|0
)braket
op_assign
(paren
id|I_op
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|I_addr
op_rshift
l_int|8
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|1
)braket
op_assign
id|I_addr
op_amp
l_int|0xff
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|2
)braket
op_assign
id|I_src
suffix:semicolon
id|M
(braket
id|LC
)braket
(braket
l_int|3
)braket
op_assign
id|I_imm
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* no two-byte instructions yet */
)brace
DECL|macro|SL
macro_line|#undef SL
DECL|macro|SR
macro_line|#undef SR
DECL|macro|RL
macro_line|#undef RL
DECL|macro|RR
macro_line|#undef RR
DECL|macro|LX
macro_line|#undef LX
DECL|macro|LA
macro_line|#undef LA
DECL|macro|LO
macro_line|#undef LO
DECL|macro|I
macro_line|#undef I
DECL|macro|A
macro_line|#undef A
r_void
DECL|function|assemble
id|assemble
c_func
(paren
r_void
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
op_star
op_star
id|a
suffix:semicolon
id|sym_t
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
(paren
id|a
op_assign
id|getl
c_func
(paren
op_amp
id|n
)paren
)paren
)paren
(brace
r_while
c_loop
(paren
id|a
(braket
l_int|0
)braket
(braket
id|strlen
c_func
(paren
op_star
id|a
)paren
op_minus
l_int|1
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|a
(braket
l_int|0
)braket
(braket
id|strlen
c_func
(paren
op_star
id|a
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_assign
id|lookup
c_func
(paren
op_star
id|a
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;value
op_assign
id|LC
suffix:semicolon
r_else
id|define
c_func
(paren
op_star
id|a
comma
id|LC
)paren
suffix:semicolon
id|a
op_add_assign
l_int|1
suffix:semicolon
id|n
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
multiline_comment|/* line was all labels */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;VERSION&quot;
comma
op_star
id|a
)paren
)paren
id|fprintf
c_func
(paren
id|ofp
comma
l_string|&quot;#define %s &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|a
(braket
l_int|1
)braket
comma
id|a
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|n
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;=&quot;
comma
id|a
(braket
l_int|1
)braket
)paren
)paren
id|define
c_func
(paren
op_star
id|a
comma
id|strtol
c_func
(paren
id|a
(braket
l_int|2
)braket
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
r_else
id|LC
op_add_assign
id|crack
c_func
(paren
id|a
comma
id|n
)paren
suffix:semicolon
)brace
)brace
id|backpatch
c_func
(paren
)paren
suffix:semicolon
id|output
c_func
(paren
id|ofp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|output
c_func
(paren
id|stderr
)paren
suffix:semicolon
)brace
r_int
DECL|function|main
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
r_int
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getopt
c_func
(paren
id|argc
comma
id|argv
comma
l_string|&quot;dho:vD&quot;
)paren
)paren
op_ne
id|EOF
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
id|debug
op_assign
op_logical_neg
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
(brace
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|optarg
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|define
c_func
(paren
id|optarg
comma
id|strtol
c_func
(paren
id|p
op_plus
l_int|1
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
id|define
c_func
(paren
id|optarg
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_char|&squot;o&squot;
suffix:colon
id|ofp
op_assign
id|fopen
c_func
(paren
id|optarg
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ofp
)paren
(brace
id|perror
c_func
(paren
id|optarg
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
id|printf
c_func
(paren
l_string|&quot;usage: %s [-d] [-Dname] [-ooutput] input&bslash;n&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_SUCCESS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;v&squot;
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_SUCCESS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|argc
op_minus
id|optind
op_ne
l_int|1
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: must have one input file&bslash;n&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
id|filename
op_assign
id|argv
(braket
id|optind
)braket
suffix:semicolon
id|ifp
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ifp
)paren
(brace
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ofp
)paren
(brace
id|ofp
op_assign
id|fopen
c_func
(paren
id|ADOTOUT
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ofp
)paren
(brace
id|perror
c_func
(paren
id|ADOTOUT
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
)brace
id|assemble
c_func
(paren
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_SUCCESS
)paren
suffix:semicolon
)brace
eof
