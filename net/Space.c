multiline_comment|/*&n; * Space.c&t;Defines which protocol modules and I/O device drivers get&n; *&t;&t;linked into the LINUX kernel.  Currently, this is only used&n; *&t;&t;by the NET layer of LINUX, but it eventually might move to&n; *&t;&t;an upper directory of the system.&n; *&n; * Version:&t;@(#)Space.c&t;1.0.2&t;04/22/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ddi.h&gt;
DECL|macro|CONFIG_UNIX
mdefine_line|#define CONFIG_UNIX&t;&t;YES&t;&t;/* always present...&t;*/
multiline_comment|/*&n; * Section A:&t;Networking Protocol Handlers.&n; *&t;&t;This section defines which networking protocols get&n; *&t;&t;linked into the SOCKET layer of the Linux kernel.&n; *&t;&t;Currently, these are AF_UNIX (always) and AF_INET.&n; */
macro_line|#ifdef&t;CONFIG_UNIX
macro_line|#  include &quot;unix/unix.h&quot;
macro_line|#endif
macro_line|#ifdef&t;CONFIG_INET
macro_line|#  include &quot;inet/inet.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_IPX
macro_line|#include &quot;ipx/ipxcall.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_AX25
macro_line|#include &quot;ax25/ax25call.h&quot;
macro_line|#endif
DECL|variable|protocols
r_struct
id|ddi_proto
id|protocols
(braket
)braket
op_assign
(brace
macro_line|#ifdef&t;CONFIG_UNIX
(brace
l_string|&quot;UNIX&quot;
comma
id|unix_proto_init
)brace
comma
macro_line|#endif
macro_line|#ifdef  CONFIG_IPX
(brace
l_string|&quot;IPX&quot;
comma
id|ipx_proto_init
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AX25  
(brace
l_string|&quot;AX.25&quot;
comma
id|ax25_proto_init
)brace
comma
macro_line|#endif  
macro_line|#ifdef&t;CONFIG_INET
(brace
l_string|&quot;INET&quot;
comma
id|inet_proto_init
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
eof
