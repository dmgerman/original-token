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
multiline_comment|/* Don&squot;t touch these, unless you really know what you&squot;re doing. */
DECL|macro|DEF_INITSEG
mdefine_line|#define DEF_INITSEG&t;0x9000
DECL|macro|DEF_SYSSEG
mdefine_line|#define DEF_SYSSEG&t;0x1000
DECL|macro|DEF_SETUPSEG
mdefine_line|#define DEF_SETUPSEG&t;0x9020
DECL|macro|DEF_SYSSIZE
mdefine_line|#define DEF_SYSSIZE&t;0x7F00
multiline_comment|/* internal svga startup constants */
DECL|macro|NORMAL_VGA
mdefine_line|#define NORMAL_VGA&t;0xffff&t;&t;/* 80x25 mode */
DECL|macro|EXTENDED_VGA
mdefine_line|#define EXTENDED_VGA&t;0xfffe&t;&t;/* 80x50 mode */
DECL|macro|ASK_VGA
mdefine_line|#define ASK_VGA&t;&t;0xfffd&t;&t;/* ask for it at bootup */
macro_line|#endif
eof
