macro_line|#ifndef NAMETRANS_H
DECL|macro|NAMETRANS_H
mdefine_line|#define NAMETRANS_H
multiline_comment|/*&n; * $Id: nametrans.h,v 1.1 1997/06/04 08:26:57 davem Exp $&n; *&n; * include/linux/nametrans.h - context-dependend filename suffixes.&n; * Copyright (C) 1997, Thomas Schoebel-Theuer,&n; * &lt;schoebel@informatik.uni-stuttgart.de&gt;.&n; */
macro_line|#include &lt;linux/dalloc.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|macro|MAX_DEFAULT_TRANSLEN
mdefine_line|#define MAX_DEFAULT_TRANSLEN 128
multiline_comment|/* only filenames matching the following length restrictions can be&n; * translated. I introduced these restrictions because they *greatly*&n; * simplify buffer management (no need to allocate kernel pages and free them).&n; * The maximal total length of a context-dependend filename is the&n; * sum of both constants. */
DECL|macro|MAX_TRANS_FILELEN
mdefine_line|#define MAX_TRANS_FILELEN 128 /* max len of a name that could be translated */
DECL|macro|MAX_TRANS_SUFFIX
mdefine_line|#define MAX_TRANS_SUFFIX   64 /* max len of a #keyword=value# suffix */
multiline_comment|/* max number of translations */
DECL|macro|MAX_TRANSLATIONS
mdefine_line|#define MAX_TRANSLATIONS 16
DECL|struct|translations
r_struct
id|translations
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|name
r_struct
id|qstr
id|name
(braket
id|MAX_TRANSLATIONS
)braket
suffix:semicolon
DECL|member|c_name
r_struct
id|qstr
id|c_name
(braket
id|MAX_TRANSLATIONS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* global/default translations */
r_extern
r_char
id|nametrans_txt
(braket
id|MAX_DEFAULT_TRANSLEN
)braket
suffix:semicolon
multiline_comment|/* Any changer of a built-in translation must set this flag */
r_extern
r_int
id|translations_dirty
suffix:semicolon
multiline_comment|/* called once at boot time */
r_extern
r_void
id|init_nametrans
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* set global translations */
r_extern
r_void
id|nametrans_setup
c_func
(paren
r_char
op_star
id|line
)paren
suffix:semicolon
multiline_comment|/* return reusable global buffer. needed by VFS. */
r_struct
id|translations
op_star
id|get_translations
c_func
(paren
r_char
op_star
id|env
)paren
suffix:semicolon
multiline_comment|/* if the _first_ environment variable is &quot;NAMETRANS&quot;, return&n; * a pointer to the list of appendices.&n; * You can set the first environment variable using&n; * &squot;env - NAMETRANS=... &quot;`env`&quot; command ...&squot;&n; */
r_extern
r_char
op_star
id|env_transl
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* if name has the correct suffix &quot;#keyword=correct_context#&quot;,&n; * return position of the suffix, else 0.&n; */
r_extern
r_char
op_star
id|testname
c_func
(paren
r_int
id|restricted
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* for use in kernel/sysctrl.h */
r_extern
r_int
id|nametrans_dostring
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
r_extern
r_int
id|nametrans_string
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
macro_line|#endif
eof
