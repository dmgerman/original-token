multiline_comment|/*&n; * linux/include/asm-m68k/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __M68K_NAMEI_H
DECL|macro|__M68K_NAMEI_H
mdefine_line|#define __M68K_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_namei
mdefine_line|#define __prefix_namei(retrieve_mode, name, base, buf, res_dir, res_inode, &bslash;&n;&t;&t;       last_name, last_entry, last_error) 1
macro_line|#endif
eof
