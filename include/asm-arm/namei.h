multiline_comment|/* $Id: namei.h,v 1.1 1998/01/28 09:56:37 ecd Exp $&n; * linux/include/asm-i386/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __ASMARM_NAMEI_H
DECL|macro|__ASMARM_NAMEI_H
mdefine_line|#define __ASMARM_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_namei
mdefine_line|#define __prefix_namei(retrieve_mode, name, base, buf, res_dir, res_inode, &bslash;&n;&t;&t;       last_name, last_entry, last_error) 1
macro_line|#endif /* __ASMARM_NAMEI_H */
eof
