macro_line|#ifndef __ARM_A_OUT_H__
DECL|macro|__ARM_A_OUT_H__
mdefine_line|#define __ARM_A_OUT_H__
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
multiline_comment|/* Use macros N_MAGIC, etc for access */
DECL|member|a_text
r_int
id|a_text
suffix:semicolon
multiline_comment|/* length of text, in bytes */
DECL|member|a_data
r_int
id|a_data
suffix:semicolon
multiline_comment|/* length of data, in bytes */
DECL|member|a_bss
r_int
id|a_bss
suffix:semicolon
multiline_comment|/* length of uninitialized data area for file, in bytes */
DECL|member|a_syms
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table data in file, in bytes */
DECL|member|a_entry
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* start address */
DECL|member|a_trsize
r_int
id|a_trsize
suffix:semicolon
multiline_comment|/* length of relocation info for text, in bytes */
DECL|member|a_drsize
r_int
id|a_drsize
suffix:semicolon
multiline_comment|/* length of relocation info for data, in bytes */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is always the same&n; */
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(a)&t;(0x00008000)
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(a)&t;((a).a_trsize)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(a)&t;((a).a_drsize)
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(a)&t;((a).a_syms)
DECL|macro|M_ARM
mdefine_line|#define M_ARM 103
macro_line|#include &lt;asm/arch/a.out.h&gt;
macro_line|#endif /* __A_OUT_GNU_H__ */
eof
