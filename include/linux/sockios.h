multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions of the socket-level I/O control calls.&n; *&n; * Version:&t;@(#)sockios.h&t;1.0.2&t;03/09/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_SOCKIOS_H
DECL|macro|_LINUX_SOCKIOS_H
mdefine_line|#define _LINUX_SOCKIOS_H
multiline_comment|/* This section will go away soon! */
macro_line|#if 1&t;/* FIXME: */
DECL|macro|MAX_IP_NAME
mdefine_line|#define MAX_IP_NAME&t;20
DECL|macro|IP_SET_DEV
mdefine_line|#define IP_SET_DEV&t;0x2401
DECL|struct|ip_config
r_struct
id|ip_config
(brace
DECL|member|name
r_char
id|name
(braket
id|MAX_IP_NAME
)braket
suffix:semicolon
DECL|member|paddr
r_int
r_int
id|paddr
suffix:semicolon
DECL|member|router
r_int
r_int
id|router
suffix:semicolon
DECL|member|net
r_int
r_int
id|net
suffix:semicolon
DECL|member|up
DECL|member|destroy
r_int
r_int
id|up
suffix:colon
l_int|1
comma
id|destroy
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* FIXME: */
multiline_comment|/* Socket-level I/O control calls. */
DECL|macro|FIOSETOWN
mdefine_line|#define FIOSETOWN &t;0x8901
DECL|macro|SIOCSPGRP
mdefine_line|#define SIOCSPGRP&t;0x8902
DECL|macro|FIOGETOWN
mdefine_line|#define FIOGETOWN&t;0x8903
DECL|macro|SIOCGPGRP
mdefine_line|#define SIOCGPGRP&t;0x8904
DECL|macro|SIOCATMARK
mdefine_line|#define SIOCATMARK&t;0x8905
multiline_comment|/* Socket configuration controls. */
DECL|macro|SIOCGIFNAME
mdefine_line|#define SIOCGIFNAME&t;0x8910&t;&t;/* get iface name&t;&t;*/
DECL|macro|SIOCSIFLINK
mdefine_line|#define SIOCSIFLINK&t;0x8911&t;&t;/* set iface channel&t;&t;*/
DECL|macro|SIOCGIFCONF
mdefine_line|#define SIOCGIFCONF&t;0x8912&t;&t;/* get iface list&t;&t;*/
DECL|macro|SIOCGIFFLAGS
mdefine_line|#define SIOCGIFFLAGS&t;0x8913&t;&t;/* get flags&t;&t;&t;*/
DECL|macro|SIOCSIFFLAGS
mdefine_line|#define SIOCSIFFLAGS&t;0x8914&t;&t;/* set flags&t;&t;&t;*/
DECL|macro|SIOCGIFADDR
mdefine_line|#define SIOCGIFADDR&t;0x8915&t;&t;/* get PA address&t;&t;*/
DECL|macro|SIOCSIFADDR
mdefine_line|#define SIOCSIFADDR&t;0x8916&t;&t;/* set PA address&t;&t;*/
DECL|macro|SIOCGIFDSTADDR
mdefine_line|#define SIOCGIFDSTADDR&t;0x8917&t;&t;/* get remote PA address&t;*/
DECL|macro|SIOCSIFDSTADDR
mdefine_line|#define SIOCSIFDSTADDR&t;0x8918&t;&t;/* set remote PA address&t;*/
DECL|macro|SIOCGIFBRDADDR
mdefine_line|#define SIOCGIFBRDADDR&t;0x8919&t;&t;/* get broadcast PA address&t;*/
DECL|macro|SIOCSIFBRDADDR
mdefine_line|#define SIOCSIFBRDADDR&t;0x891a&t;&t;/* set broadcast PA address&t;*/
DECL|macro|SIOCGIFNETMASK
mdefine_line|#define SIOCGIFNETMASK&t;0x891b&t;&t;/* get network PA mask&t;&t;*/
DECL|macro|SIOCSIFNETMASK
mdefine_line|#define SIOCSIFNETMASK&t;0x891c&t;&t;/* set network PA mask&t;&t;*/
DECL|macro|SIOCGIFMETRIC
mdefine_line|#define SIOCGIFMETRIC&t;0x891d&t;&t;/* get metric&t;&t;&t;*/
DECL|macro|SIOCSIFMETRIC
mdefine_line|#define SIOCSIFMETRIC&t;0x891e&t;&t;/* set metric&t;&t;&t;*/
DECL|macro|SIOCGIFMEM
mdefine_line|#define SIOCGIFMEM&t;0x891f&t;&t;/* get memory address (BSD)&t;*/
DECL|macro|SIOCSIFMEM
mdefine_line|#define SIOCSIFMEM&t;0x8920&t;&t;/* set memory address (BSD)&t;*/
DECL|macro|SIOCGIFMTU
mdefine_line|#define SIOCGIFMTU&t;0x8921&t;&t;/* get MTU size&t;&t;&t;*/
DECL|macro|SIOCSIFMTU
mdefine_line|#define SIOCSIFMTU&t;0x8922&t;&t;/* set MTU size&t;&t;&t;*/
DECL|macro|SIOCGIFHWADDR
mdefine_line|#define&t;SIOCGIFHWADDR&t;0x8923&t;&t;/* get hardware address&t;&t;*/
DECL|macro|SIOCSIFHWADDR
mdefine_line|#define&t;SIOCSIFHWADDR&t;0x8924&t;&t;/* set hardware address (NI)&t;*/
multiline_comment|/* Routing table calls. */
DECL|macro|SIOCADDRT
mdefine_line|#define SIOCADDRT&t;0x8940&t;&t;/* add routing table entry&t;*/
DECL|macro|SIOCDELRT
mdefine_line|#define SIOCDELRT&t;0x8941&t;&t;/* delete routing table entry&t;*/
multiline_comment|/* ARP cache control calls. */
DECL|macro|SIOCDARP
mdefine_line|#define SIOCDARP&t;0x8950&t;&t;/* delete ARP table entry&t;*/
DECL|macro|SIOCGARP
mdefine_line|#define SIOCGARP&t;0x8951&t;&t;/* get ARP table entry&t;&t;*/
DECL|macro|SIOCSARP
mdefine_line|#define SIOCSARP&t;0x8952&t;&t;/* set ARP table entry&t;&t;*/
macro_line|#endif&t;/* _LINUX_SOCKIOS_H */
eof
