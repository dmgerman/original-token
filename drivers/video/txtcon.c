multiline_comment|/*&n; * linux/drivers/video/txtcon.c -- Low level text mode based console driver&n; *&n; *    Copyright (C) 1995 Geert Uytterhoeven&n; *&n; *&n; * This file is currently only a skeleton, since all Amigas and Ataris have&n; * bitmapped graphics.&n; *&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_static
r_int
r_int
id|txtcon_startup
c_func
(paren
r_int
r_int
id|kmem_start
comma
r_const
r_char
op_star
op_star
id|display_desc
)paren
suffix:semicolon
r_static
r_void
id|txtcon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
suffix:semicolon
r_static
r_void
id|txtcon_deinit
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
suffix:semicolon
r_static
r_void
id|txtcon_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_static
r_void
id|txtcon_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|c
comma
r_int
id|y
comma
r_int
id|x
)paren
suffix:semicolon
r_static
r_void
id|txtcon_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|y
comma
r_int
id|x
)paren
suffix:semicolon
r_static
r_void
id|txtcon_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_void
id|txtcon_scroll
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|t
comma
r_int
id|b
comma
r_int
id|dir
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|txtcon_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_static
r_int
id|txtcon_switch
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
suffix:semicolon
r_static
r_int
id|txtcon_blank
c_func
(paren
r_int
id|blank
)paren
suffix:semicolon
r_static
r_int
id|txtcon_get_font
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
op_star
id|w
comma
r_int
op_star
id|h
comma
r_char
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|txtcon_set_font
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|w
comma
r_int
id|h
comma
r_char
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|txtcon_set_palette
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
r_char
op_star
id|table
)paren
suffix:semicolon
r_static
r_int
id|txtcon_scrolldelta
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|lines
)paren
suffix:semicolon
DECL|function|txtcon_startup
r_static
r_int
r_int
id|txtcon_startup
c_func
(paren
r_int
r_int
id|kmem_start
comma
r_const
r_char
op_star
op_star
id|display_desc
)paren
(brace
r_return
id|kmem_start
suffix:semicolon
)brace
DECL|function|txtcon_init
r_static
r_void
id|txtcon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_deinit
r_static
r_void
id|txtcon_deinit
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
(brace
multiline_comment|/* ... */
)brace
multiline_comment|/* ====================================================================== */
multiline_comment|/* txtcon_XXX routines - interface used by the world */
DECL|function|txtcon_clear
r_static
r_void
id|txtcon_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_putc
r_static
r_void
id|txtcon_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|c
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_putcs
r_static
r_void
id|txtcon_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_cursor
r_static
r_void
id|txtcon_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|mode
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_scroll
r_static
r_void
id|txtcon_scroll
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|t
comma
r_int
id|b
comma
r_int
id|dir
comma
r_int
id|count
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_bmove
r_static
r_void
id|txtcon_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
multiline_comment|/* ... */
)brace
DECL|function|txtcon_switch
r_static
r_int
id|txtcon_switch
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|txtcon_blank
r_static
r_int
id|txtcon_blank
c_func
(paren
r_int
id|blank
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|txtcon_get_font
r_static
r_int
id|txtcon_get_font
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
op_star
id|w
comma
r_int
op_star
id|h
comma
r_char
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|txtcon_set_font
r_static
r_int
id|txtcon_set_font
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|w
comma
r_int
id|h
comma
r_char
op_star
id|data
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|txtcon_set_palette
r_static
r_int
id|txtcon_set_palette
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
r_char
op_star
id|table
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|txtcon_scrolldelta
r_static
r_int
id|txtcon_scrolldelta
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|lines
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/* ====================================================================== */
multiline_comment|/*&n;     *  The console `switch&squot; structure for the text mode based console&n;     */
DECL|variable|txt_con
r_struct
id|consw
id|txt_con
op_assign
(brace
id|txtcon_startup
comma
id|txtcon_init
comma
id|txtcon_deinit
comma
id|txtcon_clear
comma
id|txtcon_putc
comma
id|txtcon_putcs
comma
id|txtcon_cursor
comma
id|txtcon_scroll
comma
id|txtcon_bmove
comma
id|txtcon_switch
comma
id|txtcon_blank
comma
id|txtcon_get_font
comma
id|txtcon_set_font
comma
id|txtcon_set_palette
comma
id|txtcon_scrolldelta
)brace
suffix:semicolon
eof
