multiline_comment|/*&n; *&t;Protocol intialiser table. Here seperately for convenience&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/net.h&gt;
DECL|macro|CONFIG_UNIX
mdefine_line|#define CONFIG_UNIX&t;&t;/* always present...&t;*/
macro_line|#ifdef&t;CONFIG_UNIX
macro_line|#include &quot;unix/unix.h&quot;
macro_line|#endif
macro_line|#ifdef&t;CONFIG_INET
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_IPX
macro_line|#include &quot;inet/ipxcall.h&quot;
macro_line|#include &quot;inet/p8022call.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_AX25
macro_line|#include &quot;inet/ax25call.h&quot;
macro_line|#endif
multiline_comment|/*&n; *&t;Protocol Table&n; */
DECL|variable|protocols
r_struct
id|net_proto
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
(brace
l_string|&quot;802.2&quot;
comma
id|p8022_proto_init
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
