multiline_comment|/*&n; * $Id: compat.h,v 1.1 1997/03/04 21:50:36 calle Exp $&n; * &n; * Headerfile for Compartibility between different kernel versions&n; * &n; * (c) Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: compat.h,v $&n; * Revision 1.1  1997/03/04 21:50:36  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; * &n; */
macro_line|#ifndef __COMPAT_H__
DECL|macro|__COMPAT_H__
mdefine_line|#define __COMPAT_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020112&t;/* 2.1.18 */
DECL|macro|HAS_NEW_SYMTAB
mdefine_line|#define HAS_NEW_SYMTAB
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* __COMPAT_H__ */
eof
