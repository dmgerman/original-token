multiline_comment|/* $Id: namei.h,v 1.1 1999/08/20 21:59:08 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_NAMEI_H
DECL|macro|_ASM_NAMEI_H
mdefine_line|#define _ASM_NAMEI_H
multiline_comment|/*&n; * This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_lookup_dentry
mdefine_line|#define __prefix_lookup_dentry(name, lookup_flags) &bslash;&n;&t;do {} while (0)
macro_line|#endif /* _ASM_NAMEI_H */
eof
