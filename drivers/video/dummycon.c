multiline_comment|/*&n; *  linux/drivers/video/dummycon.c -- A dummy console driver&n; *&n; *  To be used if there&squot;s no other console driver (e.g. for plain VGA text)&n; *  available, usually until fbcon takes console over.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; *  Dummy console driver&n; */
macro_line|#if defined(__arm__)
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;ORIG_VIDEO_COLS
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;ORIG_VIDEO_LINES
macro_line|#else
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;80
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;25
macro_line|#endif
DECL|function|dummycon_startup
r_static
r_const
r_char
op_star
id|__init
id|dummycon_startup
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;dummy device&quot;
suffix:semicolon
)brace
DECL|function|dummycon_init
r_static
r_void
id|dummycon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|init
)paren
(brace
id|conp-&gt;vc_can_do_color
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|init
)paren
(brace
id|conp-&gt;vc_cols
op_assign
id|DUMMY_COLUMNS
suffix:semicolon
id|conp-&gt;vc_rows
op_assign
id|DUMMY_ROWS
suffix:semicolon
)brace
r_else
id|vc_resize_con
c_func
(paren
id|DUMMY_ROWS
comma
id|DUMMY_COLUMNS
comma
id|conp-&gt;vc_num
)paren
suffix:semicolon
)brace
DECL|function|dummycon_dummy
r_static
r_int
id|dummycon_dummy
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  The console `switch&squot; structure for the dummy console&n; *&n; *  Most of the operations are dummies.&n; */
DECL|variable|dummy_con
r_struct
id|consw
id|dummy_con
op_assign
(brace
id|dummycon_startup
comma
id|dummycon_init
comma
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_deinit */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_clear */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_putc */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_putcs */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_cursor */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_scroll */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_bmove */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_switch */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_blank */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_font_op */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_set_palette */
(paren
r_void
op_star
)paren
id|dummycon_dummy
comma
multiline_comment|/* con_scrolldelta */
l_int|NULL
comma
multiline_comment|/* con_set_origin */
l_int|NULL
comma
multiline_comment|/* con_save_screen */
)brace
suffix:semicolon
eof
