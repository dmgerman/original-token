multiline_comment|/*&n; * include/asm-ppc/linux_logo.h: A linux logo to be displayed on boot&n; * (pinched from the sparc port).&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * values have to start from 0x20&n; * (i.e. linux_logo_{red,green,blue}[0] is color 0x20)&n; */
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/PPC version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_HEIGHT
mdefine_line|#define LINUX_LOGO_HEIGHT&t;80
DECL|macro|LINUX_LOGO_WIDTH
mdefine_line|#define LINUX_LOGO_WIDTH&t;80
DECL|macro|LINUX_LOGO_COLORS
mdefine_line|#define LINUX_LOGO_COLORS&t;221
macro_line|#ifdef INCLUDE_LINUX_LOGO_DATA
DECL|macro|INCLUDE_LINUX_LOGO16
mdefine_line|#define INCLUDE_LINUX_LOGO16
macro_line|#include &lt;linux/linux_logo.h&gt;
multiline_comment|/* Painted by Johnny Stenback &lt;jst@uwasa.fi&gt; */
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
l_string|&quot;   ddd |  PPC   $9$F&bslash;n&quot;
l_string|&quot; &squot;!!!!!$       !!#!`&bslash;n&quot;
l_string|&quot;  !!!!!*     .!!!!!`&bslash;n&quot;
l_string|&quot;&squot;!!!!!!!W..e$$!!!!!!`    %s&bslash;n&quot;
l_string|&quot; &bslash;&quot;~^^~         ^~~^&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
suffix:semicolon
macro_line|#else
multiline_comment|/* prototypes only */
r_extern
r_int
r_char
id|linux_logo_red
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_green
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_blue
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_bw
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_red
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_green
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_blue
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
op_star
id|linux_serial_image
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
macro_line|#endif
eof
