multiline_comment|/*&n; * linux/include/asm-arm/linux_logo.h&n; *&n; * Copyright (C) 1998 Russell King&n; *&n; * Linux console driver logo definitions for ARM&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;ARM Linux version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_COLORS
mdefine_line|#define LINUX_LOGO_COLORS&t;0
DECL|variable|__initdata
r_int
r_char
id|linux_logo_red
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo_green
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo_blue
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo16_red
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo16_green
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo16_blue
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo16
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|linux_logo_bw
(braket
)braket
id|__initdata
op_assign
(brace
)brace
suffix:semicolon
multiline_comment|/* Painted by Johnny Stenback &lt;jst@uwasa.fi&gt;&n; * Modified by Russell King for ARM&n; */
DECL|variable|__initdata
r_int
r_char
op_star
id|linux_serial_image
id|__initdata
op_assign
l_string|&quot;&bslash;n&quot;
l_string|&quot;         .u$e.&bslash;n&quot;
l_string|&quot;       .$$$$$:S&bslash;n&quot;
l_string|&quot;       $&bslash;&quot;*$/&bslash;&quot;*$$&bslash;n&quot;
l_string|&quot;       $.`$ . ^F&bslash;n&quot;
l_string|&quot;       4k+#+T.$F&bslash;n&quot;
l_string|&quot;       4P+++&bslash;&quot;$&bslash;&quot;$&bslash;n&quot;
l_string|&quot;       :R&bslash;&quot;+  t$$B&bslash;n&quot;
l_string|&quot;    ___#       $$$&bslash;n&quot;
l_string|&quot;    |  |       R$$k&bslash;n&quot;
l_string|&quot;   dd. | Linux  $!$&bslash;n&quot;
l_string|&quot;   ddd |   ARM  $9$F&bslash;n&quot;
l_string|&quot; &squot;!!!!!$       !!#!`&bslash;n&quot;
l_string|&quot;  !!!!!*     .!!!!!`&bslash;n&quot;
l_string|&quot;&squot;!!!!!!!W..e$$!!!!!!`    %s&bslash;n&quot;
l_string|&quot; &bslash;&quot;~^^~         ^~~^&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
suffix:semicolon
r_extern
r_int
(paren
op_star
id|console_show_logo
)paren
(paren
r_void
)paren
suffix:semicolon
eof
