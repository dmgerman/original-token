macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &quot;fbcon.h&quot;
DECL|struct|bt_regs
r_struct
id|bt_regs
(brace
DECL|member|addr
r_volatile
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* address register */
DECL|member|color_map
r_volatile
r_int
r_int
id|color_map
suffix:semicolon
multiline_comment|/* color map */
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* control register */
DECL|member|cursor
r_volatile
r_int
r_int
id|cursor
suffix:semicolon
multiline_comment|/* cursor map register */
)brace
suffix:semicolon
DECL|struct|fb_info_creator
r_struct
id|fb_info_creator
(brace
DECL|member|fbc
r_struct
id|ffb_fbc
op_star
id|fbc
suffix:semicolon
DECL|member|dac
r_struct
id|ffb_dac
op_star
id|dac
suffix:semicolon
DECL|member|dac_rev
r_int
id|dac_rev
suffix:semicolon
DECL|member|xy_margin
r_int
id|xy_margin
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_info_cgsix
r_struct
id|fb_info_cgsix
(brace
DECL|member|bt
r_struct
id|bt_regs
op_star
id|bt
suffix:semicolon
DECL|member|fbc
r_struct
id|cg6_fbc
op_star
id|fbc
suffix:semicolon
DECL|member|thc
r_struct
id|cg6_thc
op_star
id|thc
suffix:semicolon
DECL|member|tec
r_struct
id|cg6_tec
op_star
id|tec
suffix:semicolon
DECL|member|fhc
r_volatile
id|u32
op_star
id|fhc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cg_cursor
r_struct
id|cg_cursor
(brace
DECL|member|enable
r_int
id|enable
suffix:semicolon
multiline_comment|/* cursor is enabled */
DECL|member|cpos
r_struct
id|fbcurpos
id|cpos
suffix:semicolon
multiline_comment|/* position */
DECL|member|chot
r_struct
id|fbcurpos
id|chot
suffix:semicolon
multiline_comment|/* hot-spot */
DECL|member|size
r_struct
id|fbcurpos
id|size
suffix:semicolon
multiline_comment|/* size of mask &amp; image fields */
DECL|member|hwsize
r_struct
id|fbcurpos
id|hwsize
suffix:semicolon
multiline_comment|/* hw max size */
DECL|member|bits
r_int
id|bits
(braket
l_int|2
)braket
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* space for mask &amp; image bits */
DECL|member|color
r_char
id|color
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* cursor colors */
)brace
suffix:semicolon
DECL|struct|sbus_mmap_map
r_struct
id|sbus_mmap_map
(brace
DECL|member|voff
r_int
r_int
id|voff
suffix:semicolon
DECL|member|poff
r_int
r_int
id|poff
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_info_sbusfb
r_struct
id|fb_info_sbusfb
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
DECL|member|type
r_struct
id|fbtype
id|type
suffix:semicolon
DECL|member|sbdp
r_struct
id|linux_sbus_device
op_star
id|sbdp
suffix:semicolon
DECL|member|prom_node
DECL|member|prom_parent
r_int
id|prom_node
comma
id|prom_parent
suffix:semicolon
r_union
(brace
DECL|member|ffb
r_struct
id|fb_info_creator
id|ffb
suffix:semicolon
DECL|member|cg6
r_struct
id|fb_info_cgsix
id|cg6
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|color_map
r_int
r_char
op_star
id|color_map
suffix:semicolon
DECL|member|cursor
r_struct
id|cg_cursor
id|cursor
suffix:semicolon
DECL|member|hw_cursor_shown
r_int
r_char
id|hw_cursor_shown
suffix:semicolon
DECL|member|open
r_int
r_char
id|open
suffix:semicolon
DECL|member|mmaped
r_int
r_char
id|mmaped
suffix:semicolon
DECL|member|blanked
r_int
r_char
id|blanked
suffix:semicolon
DECL|member|x_margin
r_int
id|x_margin
suffix:semicolon
DECL|member|y_margin
r_int
id|y_margin
suffix:semicolon
DECL|member|vtconsole
r_int
id|vtconsole
suffix:semicolon
DECL|member|lastconsole
r_int
id|lastconsole
suffix:semicolon
DECL|member|consolecnt
r_int
id|consolecnt
suffix:semicolon
DECL|member|emulations
r_int
id|emulations
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|mmap_map
r_struct
id|sbus_mmap_map
op_star
id|mmap_map
suffix:semicolon
DECL|member|physbase
r_int
r_int
id|physbase
suffix:semicolon
DECL|member|iospace
r_int
id|iospace
suffix:semicolon
multiline_comment|/* Methods */
DECL|member|setup
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|display
op_star
)paren
suffix:semicolon
DECL|member|setcursor
r_void
(paren
op_star
id|setcursor
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|member|setcurshape
r_void
(paren
op_star
id|setcurshape
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|member|setcursormap
r_void
(paren
op_star
id|setcursormap
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|loadcmap
r_void
(paren
op_star
id|loadcmap
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|blank
r_void
(paren
op_star
id|blank
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|member|unblank
r_void
(paren
op_star
id|unblank
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|member|margins
r_void
(paren
op_star
id|margins
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
comma
r_struct
id|display
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|member|fill
r_void
(paren
op_star
id|fill
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|member|switch_from_graph
r_void
(paren
op_star
id|switch_from_graph
)paren
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_char
op_star
id|creatorfb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|cgsixfb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|cgthreefb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|tcxfb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|leofb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|bwtwofb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|cgfourteenfb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
)paren
suffix:semicolon
DECL|macro|attr_fg_col
mdefine_line|#define attr_fg_col(s)    &bslash;&n;&t;(((s) &gt;&gt; 8) &amp; 0x0f)
DECL|macro|attr_bg_col
mdefine_line|#define attr_bg_col(s)    &bslash;&n;&t;(((s) &gt;&gt; 12) &amp; 0x0f)
DECL|macro|attr_bg_col_ec
mdefine_line|#define attr_bg_col_ec(conp) &bslash;&n;&t;(((conp)-&gt;vc_video_erase_char &gt;&gt; 12) &amp; 0x0f)
DECL|macro|sbusfbinfod
mdefine_line|#define sbusfbinfod(disp) ((struct fb_info_sbusfb *)(disp-&gt;fb_info))
DECL|macro|sbusfbinfo
mdefine_line|#define sbusfbinfo(info) ((struct fb_info_sbusfb *)(info))
DECL|macro|CM
mdefine_line|#define CM(i, j) [3*(i)+(j)]
eof
