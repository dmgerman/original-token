multiline_comment|/* $Id: param.h,v 1.1 1996/12/02 00:08:24 davem Exp $ */
macro_line|#ifndef _ASMSPARC64_PARAM_H
DECL|macro|_ASMSPARC64_PARAM_H
mdefine_line|#define _ASMSPARC64_PARAM_H
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;8192    /* Thanks for sun4&squot;s we carry baggage... */
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS&t;&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif /* _ASMSPARC64_PARAM_H */
eof