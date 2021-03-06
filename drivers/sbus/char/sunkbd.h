multiline_comment|/* $Id: sunkbd.h,v 1.4 2000/02/09 11:15:54 davem Exp $&n; * sunkbd.h: Defines needed by SUN Keyboard drivers&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC_SUNKBD_H
DECL|macro|_SPARC_SUNKBD_H
mdefine_line|#define _SPARC_SUNKBD_H 1
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Keyboard defines for L1-A processing... */
DECL|macro|SUNKBD_RESET
mdefine_line|#define SUNKBD_RESET&t;&t;0xff
DECL|macro|SUNKBD_L1
mdefine_line|#define SUNKBD_L1&t;&t;0x01
DECL|macro|SUNKBD_UP
mdefine_line|#define SUNKBD_UP&t;&t;0x80
DECL|macro|SUNKBD_A
mdefine_line|#define SUNKBD_A&t;&t;0x4d
DECL|struct|l1a_kbd_state
r_struct
id|l1a_kbd_state
(brace
DECL|member|kbd_id
r_int
id|kbd_id
suffix:semicolon
DECL|member|l1_down
r_int
id|l1_down
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|l1a_kbd_state
id|l1a_state
suffix:semicolon
r_extern
r_void
id|keyboard_zsinit
c_func
(paren
r_void
(paren
op_star
id|kbd_put_char
)paren
(paren
r_int
r_char
)paren
)paren
suffix:semicolon
r_extern
r_void
id|sunkbd_inchar
c_func
(paren
r_int
r_char
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|batten_down_hatches
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun_kbd_bh
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sun_kbd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun_compute_shiftstate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun_setledstate
c_func
(paren
r_struct
id|kbd_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_char
id|sun_getledstate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sun_setkeycode
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sun_getkeycode
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
id|ushort
op_star
id|sun_key_maps
(braket
id|MAX_NR_KEYMAPS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|sun_keymap_count
suffix:semicolon
r_extern
r_char
id|sun_func_buf
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|sun_func_table
(braket
id|MAX_NR_FUNC
)braket
suffix:semicolon
r_extern
r_int
id|sun_funcbufsize
suffix:semicolon
r_extern
r_int
id|sun_funcbufleft
suffix:semicolon
r_extern
r_struct
id|kbdiacr
id|sun_accent_table
(braket
id|MAX_DIACR
)braket
suffix:semicolon
r_extern
r_int
r_int
id|sun_accent_table_size
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
macro_line|#endif /* !(_SPARC_SUNKBD_H) */
eof
