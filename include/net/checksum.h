multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Checksumming functions for IP, TCP, UDP and so on&n; *&n; * Authors:&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Borrows very liberally from tcp.c and ip.c, see those&n; *&t;&t;files for more names.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _CHECKSUM_H
DECL|macro|_CHECKSUM_H
mdefine_line|#define _CHECKSUM_H
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#endif
eof
