macro_line|#ifndef _LINUX_ERRNO_H
DECL|macro|_LINUX_ERRNO_H
mdefine_line|#define _LINUX_ERRNO_H
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* Should never be seen by user programs */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
DECL|macro|ERESTARTNOHAND
mdefine_line|#define ERESTARTNOHAND&t;514&t;/* restart if no handler.. */
DECL|macro|ENOIOCTLCMD
mdefine_line|#define ENOIOCTLCMD&t;515&t;/* No ioctl command */
macro_line|#endif
macro_line|#endif
eof
