macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/proc/pgtable.h&gt;
DECL|macro|module_map
mdefine_line|#define module_map&t;vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap&t;vfree
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;&t;(0)
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
