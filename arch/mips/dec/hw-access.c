multiline_comment|/*&n; * DECstation specific hardware access code.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Paul Antoine&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
id|asmlinkage
r_void
id|decstation_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|maxine_rtc_read_data
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|maxine_rtc_write_data
c_func
(paren
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * FIXME: Don&squot;t have any of the goo required to access fd etc.&n; */
DECL|variable|decstation_feature
r_struct
id|feature
id|decstation_feature
op_assign
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
id|maxine_rtc_read_data
comma
id|maxine_rtc_write_data
)brace
suffix:semicolon
eof