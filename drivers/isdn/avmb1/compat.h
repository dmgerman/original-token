multiline_comment|/*&n; * $Id: compat.h,v 1.4 1998/10/25 14:39:02 fritz Exp $&n; * &n; * Headerfile for Compartibility between different kernel versions&n; * &n; * (c) Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: compat.h,v $&n; * Revision 1.4  1998/10/25 14:39:02  fritz&n; * Backported from MIPS (Cobalt).&n; *&n; * Revision 1.3  1997/11/04 06:12:15  calle&n; * capi.c: new read/write in file_ops since 2.1.60&n; * capidrv.c: prepared isdnlog interface for d2-trace in newer firmware.&n; * capiutil.c: needs config.h (CONFIG_ISDN_DRV_AVMB1_VERBOSE_REASON)&n; * compat.h: added #define LinuxVersionCode&n; *&n; * Revision 1.2  1997/10/01 09:21:22  fritz&n; * Removed old compatibility stuff for 2.0.X kernels.&n; * From now on, this code is for 2.1.X ONLY!&n; * Old stuff is still in the separate branch.&n; *&n; * Revision 1.1  1997/03/04 21:50:36  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; * &n; */
macro_line|#ifndef __COMPAT_H__
DECL|macro|__COMPAT_H__
mdefine_line|#define __COMPAT_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#ifndef LinuxVersionCode
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* __COMPAT_H__ */
eof
