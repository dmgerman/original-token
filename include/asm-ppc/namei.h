multiline_comment|/* $Id: namei.h,v 1.1 1997/07/25 09:28:40 cort Exp $&n; * linux/include/asm-i386/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __I386_NAMEI_H
DECL|macro|__I386_NAMEI_H
mdefine_line|#define __I386_NAMEI_H
multiline_comment|/* These dummy routines maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|translate_namei
mdefine_line|#define translate_namei(pathname, base, follow_links, res_inode)&t;&bslash;&n;&t;do { } while (0)
DECL|macro|translate_open_namei
mdefine_line|#define translate_open_namei(pathname, flag, mode, res_inode, base) &bslash;&n;&t;do { } while (0)
macro_line|#endif /* __I386_NAMEI_H */
eof
