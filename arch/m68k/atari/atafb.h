macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
DECL|struct|display
r_struct
id|display
(brace
DECL|member|bytes_per_row
r_int
id|bytes_per_row
suffix:semicolon
multiline_comment|/* offset to one line below */
DECL|member|cursor_x
r_int
id|cursor_x
suffix:semicolon
multiline_comment|/* current cursor position */
DECL|member|cursor_y
r_int
id|cursor_y
suffix:semicolon
DECL|member|fgcol
r_int
id|fgcol
suffix:semicolon
multiline_comment|/* text colors */
DECL|member|bgcol
r_int
id|bgcol
suffix:semicolon
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
multiline_comment|/* variable infos */
DECL|member|cmap
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
multiline_comment|/* colormap */
multiline_comment|/* the following three are copies from fb_fix_screeninfo */
DECL|member|visual
r_int
id|visual
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|type_aux
r_int
id|type_aux
suffix:semicolon
DECL|member|bitplane
id|u_char
op_star
id|bitplane
suffix:semicolon
multiline_comment|/* pointer to top of physical screen */
DECL|member|screen_base
id|u_char
op_star
id|screen_base
suffix:semicolon
multiline_comment|/* pointer to top of virtual screen */
DECL|member|fontdata
id|u_char
op_star
id|fontdata
suffix:semicolon
multiline_comment|/* Font associated to this display */
DECL|member|fontheight
r_int
id|fontheight
suffix:semicolon
DECL|member|fontwidth
r_int
id|fontwidth
suffix:semicolon
DECL|member|inverse
r_int
id|inverse
suffix:semicolon
multiline_comment|/* != 0 text black on white as default */
DECL|member|conp
r_struct
id|vc_data
op_star
id|conp
suffix:semicolon
multiline_comment|/* pointer to console data */
DECL|member|dispsw
r_struct
id|display_switch
op_star
id|dispsw
suffix:semicolon
multiline_comment|/* pointers to depth specific functions */
)brace
suffix:semicolon
DECL|struct|fb_info
r_struct
id|fb_info
(brace
DECL|member|modename
r_char
id|modename
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* name of the at boottime detected video mode */
DECL|member|disp
r_struct
id|display
op_star
id|disp
suffix:semicolon
multiline_comment|/* pointer to display variables */
DECL|member|changevar
r_int
(paren
op_star
id|changevar
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* tell the console var has changed */
DECL|member|switch_con
r_int
(paren
op_star
id|switch_con
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* tell the framebuffer to switch consoles */
DECL|member|updatevar
r_int
(paren
op_star
id|updatevar
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* tell the framebuffer to update the vars */
DECL|member|blank
r_void
(paren
op_star
id|blank
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* tell the framebuffer to (un)blank the screen */
)brace
suffix:semicolon
r_struct
id|fb_info
op_star
id|atafb_init
c_func
(paren
r_int
op_star
)paren
suffix:semicolon
eof
