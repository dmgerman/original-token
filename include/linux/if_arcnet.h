multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the ARCnet interface.&n; *&n; * Version:&t;$Id: if_arcnet.h,v 1.2 1997/09/05 08:57:54 mj Exp $&n; *&n; * Author:&t;David Woodhouse &lt;dwmw2@cam.ac.uk&gt;&n; *&t;&t;Avery Pennarun &lt;apenwarr@bond.net&gt;&t;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ARCNET_H
DECL|macro|_LINUX_IF_ARCNET_H
mdefine_line|#define _LINUX_IF_ARCNET_H
multiline_comment|/*&n; *&t;These are the defined ARCnet Protocol ID&squot;s.&n; */
multiline_comment|/* RFC1201 Protocol ID&squot;s */
DECL|macro|ARC_P_IP
mdefine_line|#define ARC_P_IP&t;212&t;&t;/* 0xD4 */
DECL|macro|ARC_P_ARP
mdefine_line|#define ARC_P_ARP&t;213&t;&t;/* 0xD5 */
DECL|macro|ARC_P_RARP
mdefine_line|#define ARC_P_RARP&t;214&t;&t;/* 0xD6 */
DECL|macro|ARC_P_IPX
mdefine_line|#define ARC_P_IPX&t;250&t;&t;/* 0xFA */
DECL|macro|ARC_P_NOVELL_EC
mdefine_line|#define ARC_P_NOVELL_EC&t;236&t;&t;/* 0xEC */
multiline_comment|/* Old RFC1051 Protocol ID&squot;s */
DECL|macro|ARC_P_IP_RFC1051
mdefine_line|#define ARC_P_IP_RFC1051 240&t;&t;/* 0xF0 */
DECL|macro|ARC_P_ARP_RFC1051
mdefine_line|#define ARC_P_ARP_RFC1051 241&t;&t;/* 0xF1 */
multiline_comment|/* MS LanMan/WfWg protocol */
DECL|macro|ARC_P_ETHER
mdefine_line|#define ARC_P_ETHER&t;0xE8
multiline_comment|/* Unsupported/indirectly supported protocols */
DECL|macro|ARC_P_DATAPOINT_BOOT
mdefine_line|#define ARC_P_DATAPOINT_BOOT&t;0&t;/* very old Datapoint equipment */
DECL|macro|ARC_P_DATAPOINT_MOUNT
mdefine_line|#define ARC_P_DATAPOINT_MOUNT&t;1
DECL|macro|ARC_P_POWERLAN_BEACON
mdefine_line|#define ARC_P_POWERLAN_BEACON&t;8&t;/* Probably ATA-Netbios related */
DECL|macro|ARC_P_POWERLAN_BEACON2
mdefine_line|#define ARC_P_POWERLAN_BEACON2&t;243
DECL|macro|ARC_P_LANSOFT
mdefine_line|#define ARC_P_LANSOFT&t;251&t;&t;/* 0xFB - what is this? */
DECL|macro|ARC_P_ATALK
mdefine_line|#define ARC_P_ATALK&t;0xDD
multiline_comment|/*&n; *&t;This is an ARCnet frame header.&n; */
DECL|struct|archdr
r_struct
id|archdr
multiline_comment|/* was struct HardHeader */
(brace
DECL|member|source
id|u_char
id|source
comma
multiline_comment|/* source ARCnet - filled in automagically */
DECL|member|destination
id|destination
comma
multiline_comment|/* destination ARCnet - 0 for broadcast    */
DECL|member|offset1
id|offset1
comma
multiline_comment|/* offset of ClientData (256-byte packets) */
DECL|member|offset2
id|offset2
suffix:semicolon
multiline_comment|/* offset of ClientData (512-byte packets) */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IF_ARCNET_H */
eof
