macro_line|#ifndef _LINUX_CONFIG_H
DECL|macro|_LINUX_CONFIG_H
mdefine_line|#define _LINUX_CONFIG_H
macro_line|#include &lt;linux/autoconf.h&gt;
multiline_comment|/*&n; * Defines for what uname() should return &n; */
macro_line|#ifndef UTS_SYSNAME
DECL|macro|UTS_SYSNAME
mdefine_line|#define UTS_SYSNAME &quot;Linux&quot;
macro_line|#endif
macro_line|#ifndef UTS_MACHINE
DECL|macro|UTS_MACHINE
mdefine_line|#define UTS_MACHINE &quot;unknown&quot;
macro_line|#endif
macro_line|#ifndef UTS_NODENAME
DECL|macro|UTS_NODENAME
mdefine_line|#define UTS_NODENAME &quot;(none)&quot;&t;/* set by sethostname() */
macro_line|#endif
macro_line|#ifndef UTS_DOMAINNAME
DECL|macro|UTS_DOMAINNAME
mdefine_line|#define UTS_DOMAINNAME &quot;(none)&quot;&t;/* set by setdomainname() */
macro_line|#endif
multiline_comment|/*&n; * The definitions for UTS_RELEASE and UTS_VERSION are now defined&n; * in linux/version.h, and should only be used by linux/version.c&n; */
macro_line|#endif
eof
