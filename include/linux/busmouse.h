macro_line|#ifndef _LINUX_BUSMOUSE_H
DECL|macro|_LINUX_BUSMOUSE_H
mdefine_line|#define _LINUX_BUSMOUSE_H
multiline_comment|/*&n; * linux/include/linux/mouse.h: header file for Logitech Bus Mouse driver&n; * by James Banks&n; *&n; * based on information gleamed from various mouse drivers on the net&n; *&n; * Heavily modified by David giller (rafetmad@oxy.edu)&n; *&n; * Minor modifications for Linux 0.96c-pl1 by Nathan Laredo&n; * gt7080a@prism.gatech.edu (13JUL92)&n; *&n; */
DECL|macro|MOUSE_IRQ
mdefine_line|#define MOUSE_IRQ&t;&t;5
DECL|macro|MSE_DATA_PORT
mdefine_line|#define&t;MSE_DATA_PORT&t;&t;0x23c
DECL|macro|MSE_SIGNATURE_PORT
mdefine_line|#define&t;MSE_SIGNATURE_PORT&t;0x23d
DECL|macro|MSE_CONTROL_PORT
mdefine_line|#define&t;MSE_CONTROL_PORT&t;0x23e
DECL|macro|MSE_INTERRUPT_PORT
mdefine_line|#define MSE_INTERRUPT_PORT&t;0x23e
DECL|macro|MSE_CONFIG_PORT
mdefine_line|#define&t;MSE_CONFIG_PORT&t;&t;0x23f
DECL|macro|MSE_ENABLE_INTERRUPTS
mdefine_line|#define&t;MSE_ENABLE_INTERRUPTS&t;0x00
DECL|macro|MSE_DISABLE_INTERRUPTS
mdefine_line|#define&t;MSE_DISABLE_INTERRUPTS&t;0x10
DECL|macro|MSE_READ_X_LOW
mdefine_line|#define&t;MSE_READ_X_LOW&t;&t;0x80
DECL|macro|MSE_READ_X_HIGH
mdefine_line|#define&t;MSE_READ_X_HIGH&t;&t;0xa0
DECL|macro|MSE_READ_Y_LOW
mdefine_line|#define&t;MSE_READ_Y_LOW&t;&t;0xc0
DECL|macro|MSE_READ_Y_HIGH
mdefine_line|#define&t;MSE_READ_Y_HIGH&t;&t;0xe0
multiline_comment|/* Magic number used to check if the mouse exists */
DECL|macro|MSE_CONFIG_BYTE
mdefine_line|#define MSE_CONFIG_BYTE&t;&t;0x91
DECL|macro|MSE_DEFAULT_MODE
mdefine_line|#define MSE_DEFAULT_MODE&t;0x90
DECL|macro|MSE_SIGNATURE_BYTE
mdefine_line|#define MSE_SIGNATURE_BYTE&t;0xa5
multiline_comment|/* useful macros */
DECL|macro|MSE_INT_OFF
mdefine_line|#define MSE_INT_OFF()&t;outb(MSE_DISABLE_INTERRUPTS, MSE_CONTROL_PORT)
DECL|macro|MSE_INT_ON
mdefine_line|#define MSE_INT_ON()&t;outb(MSE_ENABLE_INTERRUPTS, MSE_CONTROL_PORT)
DECL|struct|mouse_status
r_struct
id|mouse_status
(brace
DECL|member|buttons
r_char
id|buttons
suffix:semicolon
DECL|member|latch_buttons
r_char
id|latch_buttons
suffix:semicolon
DECL|member|dx
r_int
id|dx
suffix:semicolon
DECL|member|dy
r_int
id|dy
suffix:semicolon
DECL|member|present
r_int
id|present
suffix:semicolon
DECL|member|ready
r_int
id|ready
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function Prototypes */
r_extern
r_int
id|mouse_init
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
