multiline_comment|/* $Id: promfb.h,v 1.1 1998/07/05 22:50:43 ecd Exp $&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _PROMFB_H
DECL|macro|_PROMFB_H
mdefine_line|#define _PROMFB_H 1
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &quot;fbcon.h&quot;
DECL|struct|fb_info_promfb
r_struct
id|fb_info_promfb
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|fix
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
DECL|member|disp
r_struct
id|display
id|disp
suffix:semicolon
DECL|member|dispsw
r_struct
id|display_switch
id|dispsw
suffix:semicolon
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|data
r_int
r_int
op_star
id|data
suffix:semicolon
DECL|member|curx
DECL|member|cury
r_int
id|curx
comma
id|cury
suffix:semicolon
DECL|member|maxx
DECL|member|maxy
r_int
id|maxx
comma
id|maxy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|promfbinfo
mdefine_line|#define promfbinfo(info)&t;((struct fb_info_promfb *)(info))
DECL|macro|promfbinfod
mdefine_line|#define promfbinfod(disp)&t;((struct fb_info_promfb *)(disp-&gt;fb_info))
macro_line|#endif /* !(_PROM_FB_H) */
eof
