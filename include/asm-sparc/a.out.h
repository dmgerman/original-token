multiline_comment|/* $Id: a.out.h,v 1.8 1995/11/25 02:31:09 davem Exp $ */
macro_line|#ifndef __SPARC_A_OUT_H__
DECL|macro|__SPARC_A_OUT_H__
mdefine_line|#define __SPARC_A_OUT_H__
DECL|macro|SPARC_PGSIZE
mdefine_line|#define SPARC_PGSIZE    0x2000        /* Thanks to the sun4 architecture... */
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE    SPARC_PGSIZE  /* whee... */
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_dynamic
r_int
r_char
id|a_dynamic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A __DYNAMIC is in this image */
DECL|member|a_toolversion
r_int
r_char
id|a_toolversion
suffix:colon
l_int|7
suffix:semicolon
DECL|member|a_machtype
r_int
r_char
id|a_machtype
suffix:semicolon
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
DECL|member|a_text
r_int
r_int
id|a_text
suffix:semicolon
multiline_comment|/* length of text, in bytes */
DECL|member|a_data
r_int
r_int
id|a_data
suffix:semicolon
multiline_comment|/* length of data, in bytes */
DECL|member|a_bss
r_int
r_int
id|a_bss
suffix:semicolon
multiline_comment|/* length of bss, in bytes */
DECL|member|a_syms
r_int
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table, in bytes */
DECL|member|a_entry
r_int
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* where program begins */
DECL|member|a_trsize
r_int
r_int
id|a_trsize
suffix:semicolon
DECL|member|a_drsize
r_int
r_int
id|a_drsize
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Where in the file does the text information begin? */
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x)     (N_MAGIC(x) == ZMAGIC ? 0 : sizeof (struct exec))
multiline_comment|/* Where do the Symbols start? */
DECL|macro|N_SYMOFF
mdefine_line|#define N_SYMOFF(x)     (N_TXTOFF(x) + (x).a_text +   &bslash;&n;                         (x).a_data + (x).a_trsize +  &bslash;&n;                         (x).a_drsize)
multiline_comment|/* Where does text segment go in memory after being loaded? */
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x)    (((N_MAGIC(x) == ZMAGIC) &amp;&amp;        &bslash;&n;&t;                 ((x).a_entry &lt; SPARC_PGSIZE)) ?   &bslash;&n;                          0 : SPARC_PGSIZE)
multiline_comment|/* And same for the data segment.. */
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x) (N_MAGIC(x)==OMAGIC ?         &bslash;&n;                      (N_TXTADDR(x) + (x).a_text)  &bslash;&n;                       : (_N_SEGMENT_ROUND (_N_TXTENDADDR(x))))
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(a)&t;((a).a_trsize)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(a)&t;((a).a_drsize)
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(a)&t;((a).a_syms)
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;TASK_SIZE
macro_line|#endif
macro_line|#endif /* __SPARC_A_OUT_H__ */
eof
