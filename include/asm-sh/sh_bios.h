macro_line|#ifndef __ASM_SH_BIOS_H
DECL|macro|__ASM_SH_BIOS_H
mdefine_line|#define __ASM_SH_BIOS_H
multiline_comment|/*&n; * Copyright (C) 2000 Greg Banks, Mitch Davis&n; * C API to interface to the standard LinuxSH BIOS&n; * usually from within the early stages of kernel boot.&n; */
r_extern
r_void
id|sh_bios_console_write
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|sh_bios_char_out
c_func
(paren
r_char
id|ch
)paren
suffix:semicolon
r_extern
r_int
id|sh_bios_in_gdb_mode
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sh_bios_gdb_detach
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_BIOS_H */
eof
