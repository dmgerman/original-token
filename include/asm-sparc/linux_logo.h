multiline_comment|/* $Id: linux_logo.h,v 1.2 1998/05/04 14:20:59 jj Exp $&n; * include/asm-sparc/linux_logo.h: This is a linux logo&n; *                                 to be displayed on boot.&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * image size has to be 80x80&n; * values have to start from 0x20&n; * (i.e. RGB(linux_logo_red[0],&n; *&t;     linux_logo_green[0],&n; *&t;     linux_logo_blue[0]) is color 0x20)&n; * BW image has to be 80x80 as well, with MS bit&n; * on the left&n; * Serial_console ascii image can be any size,&n; * but should contain %s to display the version&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/SPARC version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_COLORS
mdefine_line|#define LINUX_LOGO_COLORS 221
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
l_string|&quot;   ddd |  Sparc $9$F&bslash;n&quot;
l_string|&quot; &squot;!!!!!$       !!#!`&bslash;n&quot;
l_string|&quot;  !!!!!*     .!!!!!`&bslash;n&quot;
l_string|&quot;&squot;!!!!!!!W..e$$!!!!!!`    %s&bslash;n&quot;
l_string|&quot; &bslash;&quot;~^^~         ^~~^&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
suffix:semicolon
eof
