multiline_comment|/*&n; *  linux/include/linux/console.h&n; *&n; *  Copyright (C) 1993        Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * Changed:&n; * 10-Mar-94: Arno Griffioen: Conversion for vt100 emulator port from PC LINUX&n; */
macro_line|#ifndef _LINUX_CONSOLE_H_
DECL|macro|_LINUX_CONSOLE_H_
mdefine_line|#define _LINUX_CONSOLE_H_ 1
r_struct
id|vc_data
suffix:semicolon
multiline_comment|/*&n; * this is what the terminal answers to a ESC-Z or csi0c query.&n; */
DECL|macro|VT100ID
mdefine_line|#define VT100ID &quot;&bslash;033[?1;2c&quot;
DECL|macro|VT102ID
mdefine_line|#define VT102ID &quot;&bslash;033[?6c&quot;
multiline_comment|/* DPC: 1994-04-13 !!! con_putcs is new entry !!! */
DECL|struct|consw
r_struct
id|consw
(brace
DECL|member|con_startup
r_const
r_char
op_star
(paren
op_star
id|con_startup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|con_init
r_void
(paren
op_star
id|con_init
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_deinit
r_void
(paren
op_star
id|con_deinit
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_clear
r_void
(paren
op_star
id|con_clear
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_putc
r_void
(paren
op_star
id|con_putc
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_putcs
r_void
(paren
op_star
id|con_putcs
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_const
r_int
r_int
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_cursor
r_void
(paren
op_star
id|con_cursor
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_scroll
r_int
(paren
op_star
id|con_scroll
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_bmove
r_void
(paren
op_star
id|con_bmove
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_switch
r_int
(paren
op_star
id|con_switch
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_blank
r_int
(paren
op_star
id|con_blank
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_get_font
r_int
(paren
op_star
id|con_get_font
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|con_set_font
r_int
(paren
op_star
id|con_set_font
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|con_set_palette
r_int
(paren
op_star
id|con_set_palette
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|con_scrolldelta
r_int
(paren
op_star
id|con_scrolldelta
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_set_origin
r_int
(paren
op_star
id|con_set_origin
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_save_screen
r_void
(paren
op_star
id|con_save_screen
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|consw
op_star
id|conswitchp
suffix:semicolon
r_extern
r_struct
id|consw
id|dummy_con
suffix:semicolon
multiline_comment|/* dummy console buffer */
r_extern
r_struct
id|consw
id|fb_con
suffix:semicolon
multiline_comment|/* frame buffer based console */
r_extern
r_struct
id|consw
id|vga_con
suffix:semicolon
multiline_comment|/* VGA text console */
r_extern
r_struct
id|consw
id|compat_con
suffix:semicolon
multiline_comment|/* console wrapper */
r_extern
r_struct
id|consw
id|prom_con
suffix:semicolon
multiline_comment|/* SPARC PROM console */
r_void
id|take_over_console
c_func
(paren
r_struct
id|consw
op_star
id|sw
comma
r_int
id|first
comma
r_int
id|last
comma
r_int
id|deflt
)paren
suffix:semicolon
multiline_comment|/* flag bits */
DECL|macro|CON_INITED
mdefine_line|#define CON_INITED  (1)
multiline_comment|/* scroll */
DECL|macro|SM_UP
mdefine_line|#define SM_UP       (1)
DECL|macro|SM_DOWN
mdefine_line|#define SM_DOWN     (2)
DECL|macro|SM_LEFT
mdefine_line|#define SM_LEFT     (3)
DECL|macro|SM_RIGHT
mdefine_line|#define SM_RIGHT    (4)
multiline_comment|/* cursor */
DECL|macro|CM_DRAW
mdefine_line|#define CM_DRAW     (1)
DECL|macro|CM_ERASE
mdefine_line|#define CM_ERASE    (2)
DECL|macro|CM_MOVE
mdefine_line|#define CM_MOVE     (3)
multiline_comment|/*&n; *&t;Array of consoles built from command line options (console=)&n; */
DECL|struct|console_cmdline
r_struct
id|console_cmdline
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Name of the driver&t;    */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* Minor dev. to use&t;    */
DECL|member|options
r_char
op_star
id|options
suffix:semicolon
multiline_comment|/* Options for the driver   */
)brace
suffix:semicolon
DECL|macro|MAX_CMDLINECONSOLES
mdefine_line|#define MAX_CMDLINECONSOLES 8
r_extern
r_struct
id|console_cmdline
id|console_list
(braket
id|MAX_CMDLINECONSOLES
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;The interface for a console, or any other device that&n; *&t;wants to capture console messages (printer driver?)&n; */
DECL|macro|CON_PRINTBUFFER
mdefine_line|#define CON_PRINTBUFFER&t;(1)
DECL|macro|CON_CONSDEV
mdefine_line|#define CON_CONSDEV&t;(2) /* Last on the command line */
DECL|macro|CON_ENABLED
mdefine_line|#define CON_ENABLED&t;(4)
DECL|struct|console
r_struct
id|console
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|device
id|kdev_t
(paren
op_star
id|device
)paren
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
DECL|member|wait_key
r_int
(paren
op_star
id|wait_key
)paren
(paren
r_struct
id|console
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
r_void
)paren
suffix:semicolon
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|console
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|cflag
r_int
id|cflag
suffix:semicolon
DECL|member|next
r_struct
id|console
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|register_console
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_console
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|console
op_star
id|console_drivers
suffix:semicolon
multiline_comment|/* VEA Blanking Levels */
DECL|macro|VESA_NO_BLANKING
mdefine_line|#define VESA_NO_BLANKING        0
DECL|macro|VESA_VSYNC_SUSPEND
mdefine_line|#define VESA_VSYNC_SUSPEND      1
DECL|macro|VESA_HSYNC_SUSPEND
mdefine_line|#define VESA_HSYNC_SUSPEND      2
DECL|macro|VESA_POWERDOWN
mdefine_line|#define VESA_POWERDOWN          3
macro_line|#endif /* linux/console.h */
eof
