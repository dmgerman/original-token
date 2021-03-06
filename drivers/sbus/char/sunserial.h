multiline_comment|/* $Id: sunserial.h,v 1.19 1999/12/01 10:45:59 davem Exp $&n; * sunserial.h: SUN serial driver infrastructure (including keyboards).&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC_SUNSERIAL_H
DECL|macro|_SPARC_SUNSERIAL_H
mdefine_line|#define _SPARC_SUNSERIAL_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/console.h&gt;
DECL|struct|initfunc
r_struct
id|initfunc
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|next
r_struct
id|initfunc
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sunserial_operations
r_struct
id|sunserial_operations
(brace
DECL|member|rs_init
r_struct
id|initfunc
op_star
id|rs_init
suffix:semicolon
DECL|member|rs_kgdb_hook
r_void
(paren
op_star
id|rs_kgdb_hook
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|rs_change_mouse_baud
r_void
(paren
op_star
id|rs_change_mouse_baud
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|rs_read_proc
r_int
(paren
op_star
id|rs_read_proc
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sunkbd_operations
r_struct
id|sunkbd_operations
(brace
DECL|member|kbd_init
r_struct
id|initfunc
op_star
id|kbd_init
suffix:semicolon
DECL|member|compute_shiftstate
r_void
(paren
op_star
id|compute_shiftstate
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setledstate
r_void
(paren
op_star
id|setledstate
)paren
(paren
r_struct
id|kbd_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|getledstate
r_int
r_char
(paren
op_star
id|getledstate
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setkeycode
r_int
(paren
op_star
id|setkeycode
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|getkeycode
r_int
(paren
op_star
id|getkeycode
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sunserial_operations
id|rs_ops
suffix:semicolon
r_extern
r_struct
id|sunkbd_operations
id|kbd_ops
suffix:semicolon
r_extern
r_void
id|sunserial_setinitfunc
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|sunkbd_setinitfunc
c_func
(paren
r_int
(paren
op_star
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
r_extern
r_void
id|sunserial_console_termios
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_void
id|sunkbd_install_keymaps
c_func
(paren
id|ushort
op_star
op_star
comma
r_int
r_int
comma
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
comma
r_int
comma
r_struct
id|kbdiacr
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !(_SPARC_SUNSERIAL_H) */
eof
