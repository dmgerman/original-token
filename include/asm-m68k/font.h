multiline_comment|/*&n; *  asm-m68k/font.h -- `Soft&squot; font definitions&n; *&n; *  Created 1995 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file README.legal in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _ASM_M68K_FONT_H_
DECL|macro|_ASM_M68K_FONT_H_
mdefine_line|#define _ASM_M68K_FONT_H_
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
op_star
id|width
comma
r_int
op_star
id|heigth
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
op_star
id|width
comma
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
macro_line|#endif /* _ASM_M68K_FONT_H_ */
eof
