multiline_comment|/*&n; * linux/include/asm-arm/procinfo.h&n; *&n; * Copyright (C) 1996-1999 Russell King&n; */
macro_line|#ifndef __ASM_PROCINFO_H
DECL|macro|__ASM_PROCINFO_H
mdefine_line|#define __ASM_PROCINFO_H
macro_line|#ifndef __ASSEMBLER__
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|struct|proc_info_item
r_struct
id|proc_info_item
(brace
DECL|member|manufacturer
r_const
r_char
op_star
id|manufacturer
suffix:semicolon
DECL|member|cpu_name
r_const
r_char
op_star
id|cpu_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Note!  struct processor is always defined if we&squot;re&n; * using MULTI_CPU, otherwise this entry is unused,&n; * but still exists.&n; */
DECL|struct|proc_info_list
r_struct
id|proc_info_list
(brace
DECL|member|cpu_val
r_int
r_int
id|cpu_val
suffix:semicolon
DECL|member|cpu_mask
r_int
r_int
id|cpu_mask
suffix:semicolon
DECL|member|arch_name
r_const
r_char
op_star
id|arch_name
suffix:semicolon
DECL|member|elf_name
r_const
r_char
op_star
id|elf_name
suffix:semicolon
DECL|member|elf_hwcap
r_int
r_int
id|elf_hwcap
suffix:semicolon
DECL|member|info
r_struct
id|proc_info_item
op_star
id|info
suffix:semicolon
macro_line|#ifdef MULTI_CPU
DECL|member|proc
r_struct
id|processor
op_star
id|proc
suffix:semicolon
macro_line|#else
DECL|member|unused
r_void
op_star
id|unused
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|HWCAP_SWP
mdefine_line|#define HWCAP_SWP&t;1
DECL|macro|HWCAP_HALF
mdefine_line|#define HWCAP_HALF&t;2
DECL|macro|HWCAP_THUMB
mdefine_line|#define HWCAP_THUMB&t;4
DECL|macro|HWCAP_26BIT
mdefine_line|#define HWCAP_26BIT&t;8&t;/* Play it safe */
macro_line|#endif
eof
