multiline_comment|/*&n; * Exported procedures for the chips65550 display driver on PowerBook 3400/2400&n; *&n; * Copyright (C) 1997 Fabio Riccardi.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_extern
r_void
id|map_chips_display
c_func
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
r_extern
r_void
id|chips_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|chips_setmode
c_func
(paren
r_struct
id|vc_mode
op_star
id|mode
comma
r_int
id|doit
)paren
suffix:semicolon
r_extern
r_void
id|chips_set_palette
c_func
(paren
r_int
r_char
id|red
(braket
)braket
comma
r_int
r_char
id|green
(braket
)braket
comma
r_int
r_char
id|blue
(braket
)braket
comma
r_int
id|index
comma
r_int
id|ncolors
)paren
suffix:semicolon
r_extern
r_void
id|chips_set_blanking
c_func
(paren
r_int
id|blank_mode
)paren
suffix:semicolon
eof