multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the ICMP protocol.&n; *&n; * Version:&t;@(#)icmp.h&t;1.0.3&t;04/28/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ICMP_H
DECL|macro|_LINUX_ICMP_H
mdefine_line|#define&t;_LINUX_ICMP_H
DECL|macro|ICMP_ECHOREPLY
mdefine_line|#define ICMP_ECHOREPLY&t;&t;0&t;/* Echo Reply&t;&t;&t;*/
DECL|macro|ICMP_DEST_UNREACH
mdefine_line|#define ICMP_DEST_UNREACH&t;3&t;/* Destination Unreachable&t;*/
DECL|macro|ICMP_SOURCE_QUENCH
mdefine_line|#define ICMP_SOURCE_QUENCH&t;4&t;/* Source Quench&t;&t;*/
DECL|macro|ICMP_REDIRECT
mdefine_line|#define ICMP_REDIRECT&t;&t;5&t;/* Redirect (change route)&t;*/
DECL|macro|ICMP_ECHO
mdefine_line|#define ICMP_ECHO&t;&t;8&t;/* Echo Request&t;&t;&t;*/
DECL|macro|ICMP_TIME_EXCEEDED
mdefine_line|#define ICMP_TIME_EXCEEDED&t;11&t;/* Time Exceeded&t;&t;*/
DECL|macro|ICMP_PARAMETERPROB
mdefine_line|#define ICMP_PARAMETERPROB&t;12&t;/* Parameter Problem&t;&t;*/
DECL|macro|ICMP_TIMESTAMP
mdefine_line|#define ICMP_TIMESTAMP&t;&t;13&t;/* Timestamp Request&t;&t;*/
DECL|macro|ICMP_TIMESTAMPREPLY
mdefine_line|#define ICMP_TIMESTAMPREPLY&t;14&t;/* Timestamp Reply&t;&t;*/
DECL|macro|ICMP_INFO_REQUEST
mdefine_line|#define ICMP_INFO_REQUEST&t;15&t;/* Information Request&t;&t;*/
DECL|macro|ICMP_INFO_REPLY
mdefine_line|#define ICMP_INFO_REPLY&t;&t;16&t;/* Information Reply&t;&t;*/
DECL|macro|ICMP_ADDRESS
mdefine_line|#define ICMP_ADDRESS&t;&t;17&t;/* Address Mask Request&t;&t;*/
DECL|macro|ICMP_ADDRESSREPLY
mdefine_line|#define ICMP_ADDRESSREPLY&t;18&t;/* Address Mask Reply&t;&t;*/
multiline_comment|/* Codes for UNREACH. */
DECL|macro|ICMP_NET_UNREACH
mdefine_line|#define ICMP_NET_UNREACH&t;0&t;/* Network Unreachable&t;&t;*/
DECL|macro|ICMP_HOST_UNREACH
mdefine_line|#define ICMP_HOST_UNREACH&t;1&t;/* Host Unreachable&t;&t;*/
DECL|macro|ICMP_PROT_UNREACH
mdefine_line|#define ICMP_PROT_UNREACH&t;2&t;/* Protocol Unreachable&t;&t;*/
DECL|macro|ICMP_PORT_UNREACH
mdefine_line|#define ICMP_PORT_UNREACH&t;3&t;/* Port Unreachable&t;&t;*/
DECL|macro|ICMP_FRAG_NEEDED
mdefine_line|#define ICMP_FRAG_NEEDED&t;4&t;/* Fragmentation Needed/DF set&t;*/
DECL|macro|ICMP_SR_FAILED
mdefine_line|#define ICMP_SR_FAILED&t;&t;5&t;/* Source Route failed&t;&t;*/
DECL|macro|ICMP_NET_UNKNOWN
mdefine_line|#define ICMP_NET_UNKNOWN&t;6
DECL|macro|ICMP_HOST_UNKNOWN
mdefine_line|#define ICMP_HOST_UNKNOWN&t;7
DECL|macro|ICMP_HOST_ISOLATED
mdefine_line|#define ICMP_HOST_ISOLATED&t;8
DECL|macro|ICMP_NET_ANO
mdefine_line|#define ICMP_NET_ANO&t;&t;9
DECL|macro|ICMP_HOST_ANO
mdefine_line|#define ICMP_HOST_ANO&t;&t;10
DECL|macro|ICMP_NET_UNR_TOS
mdefine_line|#define ICMP_NET_UNR_TOS&t;11
DECL|macro|ICMP_HOST_UNR_TOS
mdefine_line|#define ICMP_HOST_UNR_TOS&t;12
multiline_comment|/* Codes for REDIRECT. */
DECL|macro|ICMP_REDIR_NET
mdefine_line|#define ICMP_REDIR_NET&t;&t;0&t;/* Redirect Net&t;&t;&t;*/
DECL|macro|ICMP_REDIR_HOST
mdefine_line|#define ICMP_REDIR_HOST&t;&t;1&t;/* Redirect Host&t;&t;*/
DECL|macro|ICMP_REDIR_NETTOS
mdefine_line|#define ICMP_REDIR_NETTOS&t;2&t;/* Redirect Net for TOS&t;&t;*/
DECL|macro|ICMP_REDIR_HOSTTOS
mdefine_line|#define ICMP_REDIR_HOSTTOS&t;3&t;/* Redirect Host for TOS&t;*/
multiline_comment|/* Codes for TIME_EXCEEDED. */
DECL|macro|ICMP_EXC_TTL
mdefine_line|#define ICMP_EXC_TTL&t;&t;0&t;/* TTL count exceeded&t;&t;*/
DECL|macro|ICMP_EXC_FRAGTIME
mdefine_line|#define ICMP_EXC_FRAGTIME&t;1&t;/* Fragment Reass time exceeded&t;*/
DECL|struct|icmphdr
r_struct
id|icmphdr
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
suffix:semicolon
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|sequence
r_int
r_int
id|sequence
suffix:semicolon
DECL|member|echo
)brace
id|echo
suffix:semicolon
DECL|member|gateway
r_int
r_int
id|gateway
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|icmp_err
r_struct
id|icmp_err
(brace
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|member|fatal
r_int
id|fatal
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_ICMP_H */
eof