multiline_comment|/*&n; *&t;Protocol initializer table. Here separately for convenience&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
DECL|macro|CONFIG_UNIX
mdefine_line|#define CONFIG_UNIX&t;&t;/* always present...&t;*/
macro_line|#ifdef&t;CONFIG_UNIX
macro_line|#include &lt;net/af_unix.h&gt;
macro_line|#endif
macro_line|#ifdef&t;CONFIG_INET
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#ifdef&t;CONFIG_IPV6
r_extern
r_void
id|inet6_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* INET */
macro_line|#if defined(CONFIG_IPX) || defined(CONFIG_IPX_MODULE)
macro_line|#include &lt;net/ipxcall.h&gt;
macro_line|#include &lt;net/p8022call.h&gt;
macro_line|#include &lt;net/p8022trcall.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X25
macro_line|#include &lt;net/x25call.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_AX25
macro_line|#include &lt;net/ax25call.h&gt;
macro_line|#ifdef CONFIG_NETROM
macro_line|#include &lt;net/nrcall.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ROSE
macro_line|#include &lt;net/rosecall.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE)
macro_line|#if ! ( defined(CONFIG_IPX) || defined(CONFIG_IPX_MODULE) )
macro_line|#include &lt;net/p8022call.h&gt;
macro_line|#include &lt;net/p8022trcall.h&gt;
macro_line|#endif
macro_line|#include &lt;net/atalkcall.h&gt;
macro_line|#endif
macro_line|#include &lt;net/psnapcall.h&gt;
macro_line|#ifdef CONFIG_TR
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
r_extern
r_void
id|rif_init
c_func
(paren
r_struct
id|net_proto
op_star
)paren
suffix:semicolon
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
multiline_comment|/* Unix domain socket family &t;*/
macro_line|#endif
macro_line|#if defined(CONFIG_IPX)   || defined(CONFIG_IPX_MODULE) || &bslash;&n;    defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE)
(brace
l_string|&quot;802.2&quot;
comma
id|p8022_proto_init
)brace
comma
multiline_comment|/* 802.2 demultiplexor&t;&t;*/
(brace
l_string|&quot;802.2TR&quot;
comma
id|p8022tr_proto_init
)brace
comma
multiline_comment|/* 802.2 demultiplexor&t;&t;*/
(brace
l_string|&quot;SNAP&quot;
comma
id|snap_proto_init
)brace
comma
multiline_comment|/* SNAP demultiplexor&t;&t;*/
macro_line|#endif
macro_line|#ifdef CONFIG_TR
(brace
l_string|&quot;RIF&quot;
comma
id|rif_init
)brace
comma
multiline_comment|/* RIF for Token ring&t;&t;*/
macro_line|#endif  
macro_line|#ifdef CONFIG_AX25  
(brace
l_string|&quot;AX.25&quot;
comma
id|ax25_proto_init
)brace
comma
multiline_comment|/* Amateur Radio AX.25 */
macro_line|#ifdef CONFIG_NETROM
(brace
l_string|&quot;NET/ROM&quot;
comma
id|nr_proto_init
)brace
comma
multiline_comment|/* Amateur Radio NET/ROM */
macro_line|#endif
macro_line|#ifdef CONFIG_ROSE
(brace
l_string|&quot;Rose&quot;
comma
id|rose_proto_init
)brace
comma
multiline_comment|/* Amateur Radio X.25 PLP */
macro_line|#endif
macro_line|#endif  
macro_line|#ifdef&t;CONFIG_INET
(brace
l_string|&quot;INET&quot;
comma
id|inet_proto_init
)brace
comma
multiline_comment|/* TCP/IP&t;&t;&t;*/
macro_line|#ifdef&t;CONFIG_IPV6
(brace
l_string|&quot;INET6&quot;
comma
id|inet6_proto_init
)brace
comma
multiline_comment|/* IPv6&t;*/
macro_line|#endif
macro_line|#endif
macro_line|#ifdef  CONFIG_IPX
(brace
l_string|&quot;IPX&quot;
comma
id|ipx_proto_init
)brace
comma
multiline_comment|/* IPX&t;&t;&t;&t;*/
macro_line|#endif
macro_line|#ifdef CONFIG_ATALK
(brace
l_string|&quot;DDP&quot;
comma
id|atalk_proto_init
)brace
comma
multiline_comment|/* Netatalk Appletalk driver&t;*/
macro_line|#endif
macro_line|#ifdef CONFIG_X25
(brace
l_string|&quot;X.25&quot;
comma
id|x25_proto_init
)brace
comma
multiline_comment|/* CCITT X.25 Packet Layer */
macro_line|#endif
(brace
l_int|NULL
comma
l_int|NULL
)brace
multiline_comment|/* End marker&t;&t;&t;*/
)brace
suffix:semicolon
eof
