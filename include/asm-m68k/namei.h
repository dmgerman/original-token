multiline_comment|/*&n; * linux/include/asm-m68k/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __M68K_NAMEI_H
DECL|macro|__M68K_NAMEI_H
mdefine_line|#define __M68K_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_lookup_dentry
mdefine_line|#define __prefix_lookup_dentry(name, lookup_flags) &bslash;&n;        do {} while (0)
macro_line|#endif
eof
