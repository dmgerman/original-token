multiline_comment|/* $Id: namei.h,v 1.2 1997/03/19 17:28:27 jj Exp $&n; * linux/include/asm-sparc64/namei.h&n; *&n; * Routines to handle famous /usr/gnemul/s*.&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __SPARC64_NAMEI_H
DECL|macro|__SPARC64_NAMEI_H
mdefine_line|#define __SPARC64_NAMEI_H
DECL|macro|SPARC_BSD_EMUL
mdefine_line|#define SPARC_BSD_EMUL &quot;usr/gnemul/sunos/&quot;
DECL|macro|SPARC_SOL_EMUL
mdefine_line|#define SPARC_SOL_EMUL &quot;usr/gnemul/solaris/&quot;
DECL|macro|translate_namei
mdefine_line|#define translate_namei(pathname, base, follow_links, res_inode) ({&t;&t;&t;&t;&t;&bslash;&n;&t;if ((current-&gt;personality &amp; (PER_BSD|PER_SVR4)) &amp;&amp; !base &amp;&amp; *pathname == &squot;/&squot;) {&t;&t;&t;&bslash;&n;&t;&t;struct inode *emul_ino;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int namelen;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const char *name;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (*pathname == &squot;/&squot;)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;pathname++;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;fs-&gt;root-&gt;i_count++;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (dir_namei (current-&gt;personality &amp; PER_BSD ? SPARC_BSD_EMUL : SPARC_SOL_EMUL, &t;&bslash;&n;&t;&t;&t;&t;&amp;namelen, &amp;name, current-&gt;fs-&gt;root, &amp;emul_ino) &gt;= 0 &amp;&amp; emul_ino) {&t;&bslash;&n;&t;&t;&t;*res_inode = NULL;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (_namei (pathname, emul_ino, follow_links, res_inode) &gt;= 0 &amp;&amp; *res_inode) &t;&bslash;&n;&t;&t;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;base = current-&gt;fs-&gt;root;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;base-&gt;i_count++;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|translate_open_namei
mdefine_line|#define translate_open_namei(pathname, flag, mode, res_inode, base) ({&t;&t;&t;&t;&t;&bslash;&n;&t;if ((current-&gt;personality &amp; (PER_BSD|PER_SVR4)) &amp;&amp; !base &amp;&amp; *pathname == &squot;/&squot;) {&t;&t;&t;&bslash;&n;&t;&t;struct inode *emul_ino;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int namelen;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;const char *name;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (*pathname == &squot;/&squot;)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;pathname++;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;fs-&gt;root-&gt;i_count++;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (dir_namei (current-&gt;personality &amp; PER_BSD ? SPARC_BSD_EMUL : SPARC_SOL_EMUL, &t;&bslash;&n;&t;&t;&t;&t;&amp;namelen, &amp;name, current-&gt;fs-&gt;root, &amp;emul_ino) &gt;= 0 &amp;&amp; emul_ino) {&t;&bslash;&n;&t;&t;&t;*res_inode = NULL;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (open_namei (pathname, flag, mode, res_inode, emul_ino) &gt;= 0 &amp;&amp; *res_inode)&t;&bslash;&n;&t;&t;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;base = current-&gt;fs-&gt;root;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;base-&gt;i_count++;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* __SPARC64_NAMEI_H */
eof
