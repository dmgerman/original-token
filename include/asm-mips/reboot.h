multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 by Ralf Baechle&n; *&n; * Declare variables for rebooting.&n; */
macro_line|#ifndef __ASM_MIPS_REBOOT_H
DECL|macro|__ASM_MIPS_REBOOT_H
mdefine_line|#define __ASM_MIPS_REBOOT_H
DECL|variable|_machine_restart
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
DECL|variable|_machine_halt
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|_machine_power_off
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_REBOOT_H */
eof
