multiline_comment|/*&n; *  font.h -- `Soft&squot; font definitions&n; *&n; *  Created 1995 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _FONT_H_
DECL|macro|_FONT_H_
mdefine_line|#define _FONT_H_
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n;    *    Find a font with a specific name&n;    */
r_extern
r_int
id|findsoftfont
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
op_star
id|width
comma
r_int
r_int
op_star
id|height
comma
id|u_char
op_star
id|data
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;    *    Get the default font for a specific screen size&n;    */
r_extern
r_void
id|getdefaultfont
c_func
(paren
r_int
id|xres
comma
r_int
id|yres
comma
r_char
op_star
id|name
(braket
)braket
comma
r_int
r_int
op_star
id|width
comma
r_int
r_int
op_star
id|height
comma
id|u_char
op_star
id|data
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/* Max. length for the name of a predefined font */
DECL|macro|MAX_FONT_NAME
mdefine_line|#define MAX_FONT_NAME&t;32
macro_line|#endif /* _FONT_H_ */
eof
