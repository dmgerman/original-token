multiline_comment|/* $Id: namei.h,v 1.3 1997/08/29 15:52:22 jj Exp $&n; * linux/include/asm-ppc/namei.h&n; * Adapted from linux/include/asm-alpha/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __PPC_NAMEI_H
DECL|macro|__PPC_NAMEI_H
mdefine_line|#define __PPC_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_lookup_dentry
mdefine_line|#define __prefix_lookup_dentry(name, follow_link) &bslash;&n;&t;do {} while (0)
macro_line|#endif /* __PPC_NAMEI_H */
eof
