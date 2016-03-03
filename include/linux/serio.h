macro_line|#ifndef _SERIO_H
DECL|macro|_SERIO_H
mdefine_line|#define _SERIO_H
multiline_comment|/*&n; * $Id: serio.h,v 1.7 2000/06/01 11:39:46 vojtech Exp $&n; *&n; * Copyright (C) 1999 Vojtech Pavlik&n; *&n; * Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
multiline_comment|/*&n; * The serial port set type ioctl.&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|SPIOCSTYPE
mdefine_line|#define SPIOCSTYPE&t;_IOW(&squot;q&squot;, 0x01, unsigned long)
r_struct
id|serio
suffix:semicolon
DECL|struct|serio
r_struct
id|serio
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|driver
r_void
op_star
id|driver
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|serio
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|dev
r_struct
id|serio_dev
op_star
id|dev
suffix:semicolon
DECL|member|next
r_struct
id|serio
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|serio_dev
r_struct
id|serio_dev
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
r_struct
id|serio
op_star
comma
r_int
r_char
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|connect
r_void
(paren
op_star
id|connect
)paren
(paren
r_struct
id|serio
op_star
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|next
r_struct
id|serio_dev
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_int
id|serio_open
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|serio_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_rescan
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_register_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_unregister_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_register_device
c_func
(paren
r_struct
id|serio_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|serio_unregister_device
c_func
(paren
r_struct
id|serio_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|function|serio_write
r_static
id|__inline__
r_int
id|serio_write
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
)paren
(brace
r_return
id|serio
op_member_access_from_pointer
id|write
c_func
(paren
id|serio
comma
id|data
)paren
suffix:semicolon
)brace
DECL|macro|SERIO_TIMEOUT
mdefine_line|#define SERIO_TIMEOUT&t;1
DECL|macro|SERIO_PARITY
mdefine_line|#define SERIO_PARITY&t;2
DECL|macro|SERIO_TYPE
mdefine_line|#define SERIO_TYPE&t;0xff000000UL
DECL|macro|SERIO_XT
mdefine_line|#define SERIO_XT&t;0x00000000UL
DECL|macro|SERIO_8042
mdefine_line|#define SERIO_8042&t;0x01000000UL
DECL|macro|SERIO_RS232
mdefine_line|#define SERIO_RS232&t;0x02000000UL
DECL|macro|SERIO_PROTO
mdefine_line|#define SERIO_PROTO&t;0xFFUL
DECL|macro|SERIO_MSC
mdefine_line|#define SERIO_MSC&t;0x01
DECL|macro|SERIO_SUN
mdefine_line|#define SERIO_SUN&t;0x02
DECL|macro|SERIO_MS
mdefine_line|#define SERIO_MS&t;0x03
DECL|macro|SERIO_MP
mdefine_line|#define SERIO_MP&t;0x04
DECL|macro|SERIO_MZ
mdefine_line|#define SERIO_MZ&t;0x05
DECL|macro|SERIO_MZP
mdefine_line|#define SERIO_MZP&t;0x06
DECL|macro|SERIO_MZPP
mdefine_line|#define SERIO_MZPP&t;0x07
DECL|macro|SERIO_SUNKBD
mdefine_line|#define SERIO_SUNKBD&t;0x10
DECL|macro|SERIO_WARRIOR
mdefine_line|#define SERIO_WARRIOR&t;0x18
DECL|macro|SERIO_SPACEORB
mdefine_line|#define SERIO_SPACEORB&t;0x19
DECL|macro|SERIO_MAGELLAN
mdefine_line|#define SERIO_MAGELLAN&t;0x1a
DECL|macro|SERIO_SPACEBALL
mdefine_line|#define SERIO_SPACEBALL&t;0x1b
DECL|macro|SERIO_GUNZE
mdefine_line|#define SERIO_GUNZE&t;0x1c
DECL|macro|SERIO_IFORCE
mdefine_line|#define SERIO_IFORCE&t;0x1d
DECL|macro|SERIO_ID
mdefine_line|#define SERIO_ID&t;0xff00UL
DECL|macro|SERIO_EXTRA
mdefine_line|#define SERIO_EXTRA&t;0xff0000UL
macro_line|#endif
eof
