macro_line|#ifndef __PARISC_A_OUT_H__
DECL|macro|__PARISC_A_OUT_H__
mdefine_line|#define __PARISC_A_OUT_H__
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
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(a)&t;((a).a_trsize)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(a)&t;((a).a_drsize)
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(a)&t;((a).a_syms)
macro_line|#ifdef __KERNEL__
multiline_comment|/* XXX: STACK_TOP actually should be STACK_BOTTOM for parisc.&n; * prumpf */
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;TASK_SIZE
macro_line|#endif
macro_line|#endif /* __A_OUT_GNU_H__ */
eof
