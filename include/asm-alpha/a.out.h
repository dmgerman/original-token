macro_line|#ifndef __ALPHA_A_OUT_H__
DECL|macro|__ALPHA_A_OUT_H__
mdefine_line|#define __ALPHA_A_OUT_H__
multiline_comment|/* OSF/1 pseudo-a.out header */
DECL|struct|exec
r_struct
id|exec
(brace
multiline_comment|/* OSF/1 &quot;file&quot; header */
DECL|member|f_magic
DECL|member|f_nscns
r_int
r_int
id|f_magic
comma
id|f_nscns
suffix:semicolon
DECL|member|f_timdat
r_int
r_int
id|f_timdat
suffix:semicolon
DECL|member|f_symptr
r_int
r_int
id|f_symptr
suffix:semicolon
DECL|member|f_nsyms
r_int
r_int
id|f_nsyms
suffix:semicolon
DECL|member|f_opthdr
DECL|member|f_flags
r_int
r_int
id|f_opthdr
comma
id|f_flags
suffix:semicolon
multiline_comment|/* followed by a more normal &quot;a.out&quot; header */
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
multiline_comment|/* after that it looks quite normal.. */
DECL|member|a_text
r_int
r_int
id|a_text
suffix:semicolon
DECL|member|a_data
r_int
r_int
id|a_data
suffix:semicolon
DECL|member|a_bss
r_int
r_int
id|a_bss
suffix:semicolon
DECL|member|a_entry
r_int
r_int
id|a_entry
suffix:semicolon
DECL|member|a_textstart
r_int
r_int
id|a_textstart
suffix:semicolon
multiline_comment|/* with a few additions that actually make sense */
DECL|member|a_datastart
r_int
r_int
id|a_datastart
suffix:semicolon
DECL|member|a_bssstart
r_int
r_int
id|a_bssstart
suffix:semicolon
DECL|member|a_gprmask
DECL|member|a_fprmask
r_int
r_int
id|a_gprmask
comma
id|a_fprmask
suffix:semicolon
multiline_comment|/* but what are these? */
DECL|member|a_gpvalue
r_int
r_int
id|a_gpvalue
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x) ((x).a_textstart)
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x) ((x).a_datastart)
DECL|macro|N_BSSADDR
mdefine_line|#define N_BSSADDR(x) ((x).a_bssstart)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(x) 0
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(x) 0
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(x) 0
DECL|macro|SCNHSZ
mdefine_line|#define SCNHSZ&t;&t;64&t;&t;/* XXX should be sizeof(scnhdr) */
DECL|macro|SCNROUND
mdefine_line|#define SCNROUND&t;16
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x) &bslash;&n;  ((long) N_MAGIC(x) == ZMAGIC ? 0 : &bslash;&n;   (sizeof(struct exec) + (x).f_nscns*SCNHSZ + SCNROUND - 1) &amp; ~(SCNROUND - 1))
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP (0x00120000000UL)
macro_line|#endif
macro_line|#endif /* __A_OUT_GNU_H__ */
eof
