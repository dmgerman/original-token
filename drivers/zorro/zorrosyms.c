multiline_comment|/*&n; *&t;$Id: zorrosyms.c,v 1.1.2.1 1998/06/07 23:21:02 geert Exp $&n; *&n; *&t;Zorro Bus Services -- Exported Symbols&n; *&n; *&t;Copyright (C) 1998 Geert Uytterhoeven&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
multiline_comment|/* Board configuration */
DECL|variable|zorro_find
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_find
)paren
suffix:semicolon
DECL|variable|zorro_get_board
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_get_board
)paren
suffix:semicolon
DECL|variable|zorro_config_board
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_config_board
)paren
suffix:semicolon
DECL|variable|zorro_unconfig_board
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_unconfig_board
)paren
suffix:semicolon
multiline_comment|/* Z2 memory */
DECL|variable|zorro_unused_z2ram
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_unused_z2ram
)paren
suffix:semicolon
eof
