multiline_comment|/* $Id: sunkbd.h,v 1.1 1997/08/28 02:23:34 ecd Exp $&n; * sunkbd.h: Defines needed by SUN Keyboard drivers&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC_SUNKBD_H
DECL|macro|_SPARC_SUNKBD_H
mdefine_line|#define _SPARC_SUNKBD_H 1
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
macro_line|#endif /* !(_SPARC_SUNKBD_H) */
eof
