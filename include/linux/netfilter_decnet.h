macro_line|#ifndef __LINUX_DECNET_NETFILTER_H
DECL|macro|__LINUX_DECNET_NETFILTER_H
mdefine_line|#define __LINUX_DECNET_NETFILTER_H
multiline_comment|/* DECnet-specific defines for netfilter. &n; * This file (C) Steve Whitehouse 1999 derived from the&n; * ipv4 netfilter header file which is&n; * (C)1998 Rusty Russell -- This code is GPL.&n; */
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* IP Cache bits. */
multiline_comment|/* Src IP address. */
DECL|macro|NFC_DN_SRC
mdefine_line|#define NFC_DN_SRC&t;&t;0x0001
multiline_comment|/* Dest IP address. */
DECL|macro|NFC_DN_DST
mdefine_line|#define NFC_DN_DST&t;&t;0x0002
multiline_comment|/* Input device. */
DECL|macro|NFC_DN_IF_IN
mdefine_line|#define NFC_DN_IF_IN&t;&t;0x0004
multiline_comment|/* Output device. */
DECL|macro|NFC_DN_IF_OUT
mdefine_line|#define NFC_DN_IF_OUT&t;&t;0x0008
multiline_comment|/* DECnet Hooks */
multiline_comment|/* After promisc drops, checksum checks. */
DECL|macro|NF_DN_PRE_ROUTING
mdefine_line|#define NF_DN_PRE_ROUTING&t;0
multiline_comment|/* If the packet is destined for this box. */
DECL|macro|NF_DN_LOCAL_IN
mdefine_line|#define NF_DN_LOCAL_IN&t;&t;1
multiline_comment|/* If the packet is destined for another interface. */
DECL|macro|NF_DN_FORWARD
mdefine_line|#define NF_DN_FORWARD&t;&t;2
multiline_comment|/* Packets coming from a local process. */
DECL|macro|NF_DN_LOCAL_OUT
mdefine_line|#define NF_DN_LOCAL_OUT&t;&t;3
multiline_comment|/* Packets about to hit the wire. */
DECL|macro|NF_DN_POST_ROUTING
mdefine_line|#define NF_DN_POST_ROUTING&t;4
multiline_comment|/* Input Hello Packets */
DECL|macro|NF_DN_HELLO
mdefine_line|#define NF_DN_HELLO&t;&t;5
multiline_comment|/* Input Routing Packets */
DECL|macro|NF_DN_ROUTE
mdefine_line|#define NF_DN_ROUTE&t;&t;6
DECL|macro|NF_DN_NUMHOOKS
mdefine_line|#define NF_DN_NUMHOOKS&t;&t;7
macro_line|#endif /*__LINUX_DECNET_NETFILTER_H*/
eof
