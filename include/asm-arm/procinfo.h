multiline_comment|/*&n; * linux/include/asm-arm/procinfo.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROCINFO_H
DECL|macro|__ASM_PROCINFO_H
mdefine_line|#define __ASM_PROCINFO_H
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#ifndef __ASSEMBLER__
DECL|macro|HWCAP_SWP
mdefine_line|#define HWCAP_SWP&t;(1 &lt;&lt; 0)
DECL|macro|HWCAP_HALF
mdefine_line|#define HWCAP_HALF&t;(1 &lt;&lt; 1)
DECL|struct|armversions
r_struct
id|armversions
(brace
DECL|member|id
r_const
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* Processor ID&t;&t;&t;*/
DECL|member|mask
r_const
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/* Processor ID mask&t;&t;*/
DECL|member|manu
r_const
r_char
op_star
id|manu
suffix:semicolon
multiline_comment|/* Manufacturer&t;&t;&t;*/
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Processor name&t;&t;*/
DECL|member|arch_vsn
r_const
r_char
op_star
id|arch_vsn
suffix:semicolon
multiline_comment|/* Architecture version&t;&t;*/
DECL|member|elf_vsn
r_const
r_char
op_star
id|elf_vsn
suffix:semicolon
multiline_comment|/* ELF library version&t;&t;*/
DECL|member|hwcap
r_const
r_int
id|hwcap
suffix:semicolon
multiline_comment|/* ELF HWCAP&t;&t;&t;*/
DECL|member|proc
r_const
r_struct
id|processor
op_star
id|proc
suffix:semicolon
multiline_comment|/* Processor-specific ASM&t;*/
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|armversions
id|armidlist
(braket
)braket
suffix:semicolon
r_extern
r_int
id|armidindex
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
