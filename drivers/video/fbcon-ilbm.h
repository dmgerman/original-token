multiline_comment|/*&n;     *  Amiga interleaved bitplanes (ilbm)&n;     */
macro_line|#ifdef MODULE
macro_line|#if defined(CONFIG_FBCON_ILBM) || defined(CONFIG_FBCON_ILBM_MODULE)  
DECL|macro|FBCON_HAS_ILBM
mdefine_line|#define FBCON_HAS_ILBM 
macro_line|#endif
macro_line|#else
macro_line|#if defined(CONFIG_FBCON_ILBM) 
DECL|macro|FBCON_HAS_ILBM
mdefine_line|#define FBCON_HAS_ILBM 
macro_line|#endif
macro_line|#endif
r_extern
r_struct
id|display_switch
id|fbcon_ilbm
suffix:semicolon
r_extern
r_void
id|fbcon_ilbm_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|fbcon_ilbm_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
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
r_extern
r_void
id|fbcon_ilbm_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
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
r_extern
r_void
id|fbcon_ilbm_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
r_extern
r_void
id|fbcon_ilbm_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
r_extern
r_void
id|fbcon_ilbm_revc
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
suffix:semicolon
eof
