multiline_comment|/*&n; *  linux/fs/umsdos/mangle.c&n; *&n; *&t;Written 1993 by Jacques Gelinas &n; *&n; * Control the mangling of file name to fit msdos name space.&n; * Many optimisation by GLU == dglaude@is1.vub.ac.be (GLAUDE DAVID)&n;*/
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
multiline_comment|/*&n;&t;Complete the mangling of the MSDOS fake name&n;&t;based on the position of the entry in the EMD file.&n;&n;&t;Simply complete the job of umsdos_parse; fill the extension.&n;&n;&t;Beware that info-&gt;f_pos must be set.&n;*/
DECL|function|umsdos_manglename
r_void
id|umsdos_manglename
(paren
r_struct
id|umsdos_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;msdos_reject
)paren
(brace
multiline_comment|/* #Specification: file name / non MSDOS conforming / mangling&n;&t;&t;&t;Each non MSDOS conforming file has a special extension&n;&t;&t;&t;build from the entry position in the EMD file.&n;&n;&t;&t;&t;This number is then transform in a base 32 number, where&n;&t;&t;&t;each digit is expressed like hexadecimal number, using&n;&t;&t;&t;digit and letter, except it uses 22 letters from &squot;a&squot; to &squot;v&squot;.&n;&t;&t;&t;The number 32 comes from 2**5. It is faster to split a binary&n;&t;&t;&t;number using a base which is a power of two. And I was 32&n;&t;&t;&t;when I started this project. Pick your answer :-) .&n;&n;&t;&t;&t;If the result is &squot;0&squot;, it is replace with &squot;_&squot;, simply&n;&t;&t;&t;to make it odd.&n;&n;&t;&t;&t;This is true for the first two character of the extension.&n;&t;&t;&t;The last one is taken from a list of odd character, which&n;&t;&t;&t;are:&n;&n;&t;&t;&t;&t;{ } ( ) ! ` ^ &amp; @&n;&n;&t;&t;&t;With this scheme, we can produce 9216 ( 9* 32 * 32)&n;&t;&t;&t;different extensions which should not clash with any useful&n;&t;&t;&t;extension already popular or meaningful. Since most directory&n;&t;&t;&t;have much less than 32 * 32 files in it, the first character&n;&t;&t;&t;of the extension of any mangle name will be {.&n;&n;&t;&t;&t;Here are the reason to do this (this kind of mangling).&n;&n;&t;&t;&t;-The mangling is deterministic. Just by the extension, we&n;&t;&t;&t; are able to locate the entry in the EMD file.&n;&n;&t;&t;&t;-By keeping to beginning of the file name almost unchanged,&n;&t;&t;&t; we are helping the MSDOS user.&n;&n;&t;&t;&t;-The mangling produces names not too ugly, so an msdos user&n;&t;&t;&t; may live with it (remember it, type it, etc...).&n;&n;&t;&t;&t;-The mangling produces names ugly enough so no one will&n;&t;&t;&t; ever think of using such a name in real life. This is not&n;&t;&t;&t; fool proof. I don&squot;t think there is a total solution to this.&n;&t;&t;*/
r_union
(brace
r_int
id|entry_num
suffix:semicolon
r_struct
(brace
r_int
id|num1
suffix:colon
l_int|5
comma
id|num2
suffix:colon
l_int|5
comma
id|num3
suffix:colon
l_int|5
suffix:semicolon
)brace
id|num
suffix:semicolon
)brace
id|u
suffix:semicolon
r_char
op_star
id|pt
op_assign
id|info-&gt;fake.fname
op_plus
id|info-&gt;fake.len
suffix:semicolon
multiline_comment|/* lookup for encoding the last character of the extension */
multiline_comment|/* It contain valid character after the ugly one to make sure */
multiline_comment|/* even if someone overflow the 32 * 32 * 9 limit, it still do */
multiline_comment|/* something */
DECL|macro|SPECIAL_MANGLING
mdefine_line|#define SPECIAL_MANGLING &squot;{&squot;,&squot;}&squot;,&squot;(&squot;,&squot;)&squot;,&squot;!&squot;,&squot;`&squot;,&squot;^&squot;,&squot;&amp;&squot;,&squot;@&squot;
r_static
r_char
id|lookup3
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|lookup12
mdefine_line|#define lookup12 (lookup3+9)
id|u.entry_num
op_assign
id|info-&gt;f_pos
op_div
id|UMSDOS_REC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|u.entry_num
OG
(paren
l_int|9
op_star
l_int|32
op_star
l_int|32
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;UMSDOS: More than 9216 file in a directory.&bslash;n&quot;
l_string|&quot;This may break the mangling strategy.&bslash;n&quot;
l_string|&quot;Not a killer problem. See doc.&bslash;n&quot;
)paren
suffix:semicolon
)brace
op_star
id|pt
op_increment
op_assign
l_char|&squot;.&squot;
suffix:semicolon
op_star
id|pt
op_increment
op_assign
id|lookup3
(braket
id|u.num.num3
)braket
suffix:semicolon
op_star
id|pt
op_increment
op_assign
id|lookup12
(braket
id|u.num.num2
)braket
suffix:semicolon
op_star
id|pt
op_increment
op_assign
id|lookup12
(braket
id|u.num.num1
)braket
suffix:semicolon
op_star
id|pt
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* help doing printk */
id|info-&gt;fake.len
op_add_assign
l_int|4
suffix:semicolon
id|info-&gt;msdos_reject
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Avoid mangling twice */
)brace
)brace
multiline_comment|/*&n;&t;Evaluate the record size needed to store of name of len character.&n;&t;The value returned is a multiple of UMSDOS_REC_SIZE.&n;*/
DECL|function|umsdos_evalrecsize
r_int
id|umsdos_evalrecsize
(paren
r_int
id|len
)paren
(brace
r_struct
id|umsdos_dirent
id|dirent
suffix:semicolon
r_int
id|nbrec
op_assign
l_int|1
op_plus
(paren
(paren
id|len
op_minus
l_int|1
op_plus
(paren
id|dirent.name
op_minus
(paren
r_char
op_star
)paren
op_amp
id|dirent
)paren
)paren
op_div
id|UMSDOS_REC_SIZE
)paren
suffix:semicolon
r_return
id|nbrec
op_star
id|UMSDOS_REC_SIZE
suffix:semicolon
multiline_comment|/*&n;&t;GLU&t;This should be inlined or something to speed it up to the max.&n;&t;GLU&t;nbrec is absolutely not needed to return the value.&n;&t;*/
)brace
macro_line|#ifdef TEST
DECL|function|umsdos_evalrecsize_old
r_int
id|umsdos_evalrecsize_old
(paren
r_int
id|len
)paren
(brace
r_struct
id|umsdos_dirent
id|dirent
suffix:semicolon
r_int
id|size
op_assign
id|len
op_plus
(paren
id|dirent.name
op_minus
(paren
r_char
op_star
)paren
op_amp
id|dirent
)paren
suffix:semicolon
r_int
id|nbrec
op_assign
id|size
op_div
id|UMSDOS_REC_SIZE
suffix:semicolon
r_int
id|extra
op_assign
id|size
op_mod
id|UMSDOS_REC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|extra
OG
l_int|0
)paren
id|nbrec
op_increment
suffix:semicolon
r_return
id|nbrec
op_star
id|UMSDOS_REC_SIZE
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t;Fill the struct info with the full and msdos name of a file&n;&t;Return 0 if all is ok, a negative error code otherwise.&n;*/
DECL|function|umsdos_parse
r_int
id|umsdos_parse
(paren
r_const
r_char
op_star
id|fname
comma
r_int
id|len
comma
r_struct
id|umsdos_info
op_star
id|info
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
multiline_comment|/* #Specification: file name / too long&n;&t;&t;If a file name exceed UMSDOS maxima, the file name is silently&n;&t;&t;truncated. This makes it conformant with the other file system&n;&t;&t;of Linux (minix and ext2 at least).&n;&t;*/
r_if
c_cond
(paren
id|len
OG
id|UMSDOS_MAXNAME
)paren
id|len
op_assign
id|UMSDOS_MAXNAME
suffix:semicolon
(brace
r_const
r_char
op_star
id|firstpt
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* First place we saw a . in fname */
multiline_comment|/* #Specification: file name / non MSDOS conforming / base length 0&n;&t;&t;&t;file name beginning with a period &squot;.&squot; are invalid for MsDOS.&n;&t;&t;&t;It needs absolutely a base name. So the file name is mangled&n;&t;&t;*/
r_int
id|ivldchar
op_assign
id|fname
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
multiline_comment|/* At least one invalid character */
r_int
id|msdos_len
op_assign
id|len
suffix:semicolon
r_int
id|base_len
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;cardinal_per_size tells if there exist at least one&n;&t;&t;&t;DOS pseudo devices on length n. See the test below.&n;&t;&t;*/
r_static
r_const
r_char
id|cardinal_per_size
(braket
l_int|9
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;lkp translate all character to acceptable character (for DOS).&n;&t;&t;&t;When lkp[n] == n, it means also it is an acceptable one.&n;&t;&t;&t;So it serve both as a flag and as a translator.&n;&t;&t;*/
r_static
r_char
id|lkp
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_char
id|is_init
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_init
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;Initialisation of the array is easier and less error prone&n;&t;&t;&t;&t;like this.&n;&t;&t;&t;*/
r_int
id|i
suffix:semicolon
r_static
r_char
op_star
id|spc
op_assign
l_string|&quot;&bslash;&quot;*+,/:;&lt;=&gt;?[&bslash;&bslash;]|~&quot;
suffix:semicolon
id|is_init
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|lkp
(braket
id|i
)braket
op_assign
l_char|&squot;#&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|33
suffix:semicolon
id|i
OL
l_char|&squot;A&squot;
suffix:semicolon
id|i
op_increment
)paren
id|lkp
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_char|&squot;A&squot;
suffix:semicolon
id|i
op_le
l_char|&squot;Z&squot;
suffix:semicolon
id|i
op_increment
)paren
id|lkp
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
(paren
id|i
op_plus
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_char|&squot;Z&squot;
op_plus
l_int|1
suffix:semicolon
id|i
OL
l_int|127
suffix:semicolon
id|i
op_increment
)paren
id|lkp
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|128
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|lkp
(braket
id|i
)braket
op_assign
l_char|&squot;#&squot;
suffix:semicolon
id|lkp
(braket
l_char|&squot;.&squot;
)braket
op_assign
l_char|&squot;_&squot;
suffix:semicolon
r_while
c_loop
(paren
op_star
id|spc
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|lkp
(braket
(paren
r_int
r_char
)paren
(paren
op_star
id|spc
op_increment
)paren
)braket
op_assign
l_char|&squot;#&squot;
suffix:semicolon
)brace
multiline_comment|/*&t;GLU&n;&t;&t;&t;file name which are longer than 8+&squot;.&squot;+3 are invalid for MsDOS.&n;&t;&t;&t;So the file name is to be mangled no more test needed.&n;&t;&t;&t;This Speed Up for long and very long name.&n;&t;&t;&t;The position of the last point is no more necessary anyway.&n;&t;&t;*/
r_if
c_cond
(paren
id|len
op_le
(paren
l_int|8
op_plus
l_int|1
op_plus
l_int|3
)paren
)paren
(brace
r_const
r_char
op_star
id|pt
op_assign
id|fname
suffix:semicolon
r_const
r_char
op_star
id|endpt
op_assign
id|fname
op_plus
id|len
suffix:semicolon
r_while
c_loop
(paren
id|pt
OL
id|endpt
)paren
(brace
r_if
c_cond
(paren
op_star
id|pt
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|firstpt
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* 2 . in a file name. Reject */
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
r_int
id|extlen
op_assign
(paren
r_int
)paren
(paren
id|endpt
op_minus
id|pt
)paren
suffix:semicolon
id|firstpt
op_assign
id|pt
suffix:semicolon
r_if
c_cond
(paren
id|firstpt
op_minus
id|fname
OG
l_int|8
)paren
(brace
multiline_comment|/* base name longer than 8: reject */
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|extlen
OG
l_int|4
)paren
(brace
multiline_comment|/* Extension longer than 4 (including .): reject */
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|extlen
op_eq
l_int|1
)paren
(brace
multiline_comment|/* #Specification: file name / non MSDOS conforming / last char == .&n;&t;&t;&t;&t;&t;&t;&t;&t;If the last character of a file name is&n;&t;&t;&t;&t;&t;&t;&t;&t;a period, mangling is applied. MsDOS do&n;&t;&t;&t;&t;&t;&t;&t;&t;not support those file name.&n;&t;&t;&t;&t;&t;&t;&t;*/
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|extlen
op_eq
l_int|4
)paren
(brace
multiline_comment|/* #Specification: file name / non MSDOS conforming / mangling clash&n;&t;&t;&t;&t;&t;&t;&t;&t;To avoid clash with&t;the umsdos mangling, any file&n;&t;&t;&t;&t;&t;&t;&t;&t;with a special character as the first character&n;&t;&t;&t;&t;&t;&t;&t;&t;of the extension will be mangled. This solve the&n;&t;&t;&t;&t;&t;&t;&t;&t;following problem:&n;&t;&t;&t;&t;&n;&t;&t;&t;&t;&t;&t;&t;&t;touch FILE&n;&t;&t;&t;&t;&t;&t;&t;&t;# FILE is invalid for DOS, so mangling is applied&n;&t;&t;&t;&t;&t;&t;&t;&t;# file.{_1 is created in the DOS directory&n;&t;&t;&t;&t;&t;&t;&t;&t;touch file.{_1&n;&t;&t;&t;&t;&t;&t;&t;&t;# To UMSDOS file point to a single DOS entry.&n;&t;&t;&t;&t;&t;&t;&t;&t;# So file.{_1 has to be mangled.&n;&t;&t;&t;&t;&t;&t;&t;*/
r_static
r_char
id|special
(braket
)braket
op_assign
initialization_block
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|special
comma
id|firstpt
(braket
l_int|1
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|lkp
(braket
(paren
r_int
r_char
)paren
(paren
op_star
id|pt
)paren
)braket
op_ne
op_star
id|pt
)paren
(brace
id|ivldchar
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pt
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|ivldchar
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ivldchar
op_logical_or
(paren
id|firstpt
op_eq
l_int|NULL
op_logical_and
id|len
OG
l_int|8
)paren
op_logical_or
(paren
id|len
op_eq
id|UMSDOS_EMD_NAMELEN
op_logical_and
id|memcmp
c_func
(paren
id|fname
comma
id|UMSDOS_EMD_FILE
comma
id|UMSDOS_EMD_NAMELEN
)paren
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* #Specification: file name / --linux-.---&n;&t;&t;&t;&t;The name of the EMD file --linux-.--- is map to a mangled&n;&t;&t;&t;&t;name. So UMSDOS does not restrict its use.&n;&t;&t;&t;*/
multiline_comment|/* #Specification: file name / non MSDOS conforming / mangling&n;&t;&t;&t;&t;Non MSDOS conforming file name must use some alias to fit&n;&t;&t;&t;&t;in the MSDOS name space.&n;&n;&t;&t;&t;&t;The strategy is simple. The name is simply truncated to&n;&t;&t;&t;&t;8 char. points are replace with underscore and a&n;&t;&t;&t;&t;number is given as an extension. This number correspond&n;&t;&t;&t;&t;to the entry number in the EMD file. The EMD file&n;&t;&t;&t;&t;only need to carry the real name.&n;&n;&t;&t;&t;&t;Upper case is also convert to lower case.&n;&t;&t;&t;&t;Control character are converted to #.&n;&t;&t;&t;&t;Space are converted to #.&n;&t;&t;&t;&t;The following character are also converted to #.&n;&t;&t;&t;&t;&t;&quot; * + , / : ; &lt; = &gt; ? [ &bslash; ] | ~&n;&n;&t;&t;&t;&t;Sometime, the problem is not in MsDOS itself but in&n;&t;&t;&t;&t;command.com.&n;&t;&t;&t;*/
r_int
id|i
suffix:semicolon
r_char
op_star
id|pt
op_assign
id|info-&gt;fake.fname
suffix:semicolon
id|base_len
op_assign
id|msdos_len
op_assign
(paren
id|msdos_len
OG
l_int|8
)paren
ques
c_cond
l_int|8
suffix:colon
id|msdos_len
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;There is no &squot;.&squot; any more so we know for a fact that&n;&t;&t;&t;&t;the base length is the length.&n;&t;&t;&t;*/
id|memcpy
(paren
id|info-&gt;fake.fname
comma
id|fname
comma
id|msdos_len
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
id|msdos_len
suffix:semicolon
id|i
op_increment
comma
id|pt
op_increment
)paren
op_star
id|pt
op_assign
id|lkp
(braket
(paren
r_int
r_char
)paren
(paren
op_star
id|pt
)paren
)braket
suffix:semicolon
op_star
id|pt
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* GLU&t;C&squot;est sur on a un 0 a la fin */
id|info-&gt;msdos_reject
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;The numeric extension is added only when we know&n;&t;&t;&t;&t;the position in the EMD file, in umsdos_newentry(),&n;&t;&t;&t;&t;umsdos_delentry(), and umsdos_findentry().&n;&t;&t;&t;&t;See umsdos_manglename().&n;&t;&t;&t;*/
)brace
r_else
(brace
multiline_comment|/* Conforming MSDOS file name */
id|strcpy
(paren
id|info-&gt;fake.fname
comma
id|fname
)paren
suffix:semicolon
multiline_comment|/* GLU&t;C&squot;est sur on a un 0 a la fin */
id|info-&gt;msdos_reject
op_assign
l_int|0
suffix:semicolon
id|base_len
op_assign
id|firstpt
op_ne
l_int|NULL
ques
c_cond
(paren
r_int
)paren
(paren
id|firstpt
op_minus
id|fname
)paren
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cardinal_per_size
(braket
id|base_len
)braket
)paren
(brace
multiline_comment|/* #Specification: file name / MSDOS devices / mangling&n;&t;&t;&t;&t;To avoid unreachable file from MsDOS, any MsDOS conforming&n;&t;&t;&t;&t;file with a basename equal to one of the MsDOS pseudo&n;&t;&t;&t;&t;devices will be mangled.&n;&n;&t;&t;&t;&t;If a file such as &quot;prn&quot; was created, it would be unreachable&n;&t;&t;&t;&t;under MsDOS because prn is assumed to be the printer, even&n;&t;&t;&t;&t;if the file does have an extension.&n;&n;&t;&t;&t;&t;Since the extension is unimportant to MsDOS, we must patch&n;&t;&t;&t;&t;the basename also. We simply insert a minus &squot;-&squot;. To avoid&n;&t;&t;&t;&t;conflict with valid file with a minus in front (such as&n;&t;&t;&t;&t;&quot;-prn&quot;), we add an mangled extension like any other&n;&t;&t;&t;&t;mangled file name.&n;&n;&t;&t;&t;&t;Here is the list of DOS pseudo devices:&n;&n;&t;&t;&t;&t;&t;&quot;prn&quot;,&quot;con&quot;,&quot;aux&quot;,&quot;nul&quot;,&n;&t;&t;&t;&t;&t;&quot;lpt1&quot;,&quot;lpt2&quot;,&quot;lpt3&quot;,&quot;lpt4&quot;,&n;&t;&t;&t;&t;&t;&quot;com1&quot;,&quot;com2&quot;,&quot;com3&quot;,&quot;com4&quot;,&n;&t;&t;&t;&t;&t;&quot;clock$&quot;&n;&n;&t;&t;&t;&t;and some standard ones for common DOS programs&n;&n;&t;&t;&t;&t;&t;&quot;emmxxxx0&quot;,&quot;xmsxxxx0&quot;,&quot;setverxx&quot;&n;&n;&t;&t;&t;&t;(Thanks to Chris Hall &lt;CAH17@PHOENIX.CAMBRIDGE.AC.UK&gt;&n;&t;&t;&t;&t; for pointing these to me).&n;&n;&t;&t;&t;&t;Is there one missing ?&n;&t;&t;&t;*/
multiline_comment|/* This table must be ordered by length */
r_static
r_const
r_char
op_star
id|tbdev
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* Tell where to find in tbdev[], the first name of */
multiline_comment|/* a certain length */
r_static
r_const
r_char
id|start_ind_dev
(braket
l_int|9
)braket
op_assign
initialization_block
suffix:semicolon
r_char
id|basen
(braket
l_int|9
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start_ind_dev
(braket
id|base_len
op_minus
l_int|1
)braket
suffix:semicolon
id|i
OL
id|start_ind_dev
(braket
id|base_len
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|info-&gt;fake.fname
comma
id|tbdev
(braket
id|i
)braket
comma
id|base_len
)paren
op_eq
l_int|0
)paren
(brace
id|memcpy
(paren
id|basen
comma
id|info-&gt;fake.fname
comma
id|base_len
)paren
suffix:semicolon
id|basen
(braket
id|base_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* GLU&t;C&squot;est sur on a un 0 a la fin */
multiline_comment|/*&n;&t;&t;&t;&t;&t;GLU&t;On ne fait cela que si necessaire, on essaye d&squot;etre le&n;&t;&t;&t;&t;&t;GLU&t;simple dans le cas general (le plus frequent).&n;&t;&t;&t;&t;&t;*/
id|info-&gt;fake.fname
(braket
l_int|0
)braket
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|strcpy
(paren
id|info-&gt;fake.fname
op_plus
l_int|1
comma
id|basen
)paren
suffix:semicolon
multiline_comment|/* GLU&t;C&squot;est sur on a un 0 a la fin */
id|msdos_len
op_assign
(paren
id|base_len
op_eq
l_int|8
)paren
ques
c_cond
l_int|8
suffix:colon
id|base_len
op_plus
l_int|1
suffix:semicolon
id|info-&gt;msdos_reject
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|info-&gt;fake.fname
(braket
id|msdos_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Help doing printk */
multiline_comment|/* GLU&t;Ce zero devrais deja y etre ! (invariant ?) */
id|info-&gt;fake.len
op_assign
id|msdos_len
suffix:semicolon
multiline_comment|/* Pourquoi ne pas utiliser info-&gt;fake.len partout ??? plus long ?*/
id|memcpy
(paren
id|info-&gt;entry.name
comma
id|fname
comma
id|len
)paren
suffix:semicolon
id|info-&gt;entry.name_len
op_assign
id|len
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;Evaluate how many record are needed to store this entry.&n;&t;*/
id|info-&gt;recsize
op_assign
id|umsdos_evalrecsize
(paren
id|len
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef TEST
DECL|struct|MANG_TEST
r_struct
id|MANG_TEST
(brace
DECL|member|fname
r_char
op_star
id|fname
suffix:semicolon
multiline_comment|/* Name to validate */
DECL|member|msdos_reject
r_int
id|msdos_reject
suffix:semicolon
multiline_comment|/* Expected msdos_reject flag */
DECL|member|msname
r_char
op_star
id|msname
suffix:semicolon
multiline_comment|/* Expected msdos name */
)brace
suffix:semicolon
DECL|variable|tb
r_struct
id|MANG_TEST
id|tb
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|main
r_int
id|main
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int
id|i
comma
id|rold
comma
id|rnew
suffix:semicolon
id|printf
(paren
l_string|&quot;Testing the umsdos_parse.&bslash;n&quot;
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
id|tb
)paren
op_div
r_sizeof
(paren
id|tb
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|MANG_TEST
op_star
id|pttb
op_assign
id|tb
op_plus
id|i
suffix:semicolon
r_struct
id|umsdos_info
id|info
suffix:semicolon
r_int
id|ok
op_assign
id|umsdos_parse
(paren
id|pttb-&gt;fname
comma
id|strlen
c_func
(paren
id|pttb-&gt;fname
)paren
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|info.fake.fname
comma
id|pttb-&gt;msname
)paren
op_ne
l_int|0
)paren
(brace
id|printf
(paren
l_string|&quot;**** %s -&gt; &quot;
comma
id|pttb-&gt;fname
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;%s &lt;&gt; %s&bslash;n&quot;
comma
id|info.fake.fname
comma
id|pttb-&gt;msname
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|info.msdos_reject
op_ne
id|pttb-&gt;msdos_reject
)paren
(brace
id|printf
(paren
l_string|&quot;**** %s -&gt; %s &quot;
comma
id|pttb-&gt;fname
comma
id|pttb-&gt;msname
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;%d &lt;&gt; %d&bslash;n&quot;
comma
id|info.msdos_reject
comma
id|pttb-&gt;msdos_reject
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
(paren
l_string|&quot;     %s -&gt; %s %d&bslash;n&quot;
comma
id|pttb-&gt;fname
comma
id|pttb-&gt;msname
comma
id|pttb-&gt;msdos_reject
)paren
suffix:semicolon
)brace
)brace
id|printf
(paren
l_string|&quot;Testing the new umsdos_evalrecsize.&quot;
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
id|UMSDOS_MAXNAME
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rnew
op_assign
id|umsdos_evalrecsize
(paren
id|i
)paren
suffix:semicolon
id|rold
op_assign
id|umsdos_evalrecsize_old
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
id|UMSDOS_REC_SIZE
)paren
)paren
(brace
id|printf
(paren
l_string|&quot;&bslash;n%d:&bslash;t&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rnew
op_ne
id|rold
)paren
(brace
id|printf
(paren
l_string|&quot;**** %d newres: %d != %d &bslash;n&quot;
comma
id|i
comma
id|rnew
comma
id|rold
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
)brace
id|printf
(paren
l_string|&quot;&bslash;nEnd of Testing.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof