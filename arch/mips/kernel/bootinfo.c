multiline_comment|/*&n; * arch/mips/kernel/bootinfo.c&n; *&n; * Copyright (C) 1995  Ralf Baechle&n; *&n; * Kernel data passed by the loader &n; */
macro_line|#include &lt;asm/bootinfo.h&gt;
multiline_comment|/*&n; * Initialise this structure so that it will be placed in the&n; * .data section of the object file&n; */
DECL|variable|boot_info
r_struct
id|bootinfo
id|boot_info
op_assign
id|BOOT_INFO
suffix:semicolon
eof
