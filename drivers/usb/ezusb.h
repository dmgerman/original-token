multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;ezusb.h  --  Firmware download miscdevice for Anchorchips EZUSB microcontrollers.&n; *&n; *&t;Copyright (C) 1999&n; *          Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _LINUX_EZUSB_H
DECL|macro|_LINUX_EZUSB_H
mdefine_line|#define _LINUX_EZUSB_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|ezusb_ctrltransfer
r_struct
id|ezusb_ctrltransfer
(brace
multiline_comment|/* keep in sync with usb.h:devrequest */
DECL|member|requesttype
r_int
r_char
id|requesttype
suffix:semicolon
DECL|member|request
r_int
r_char
id|request
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* pointer to data */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EZUSB_CONTROL
mdefine_line|#define EZUSB_CONTROL        _IOWR(&squot;E&squot;, 0, struct ezusb_ctrltransfer)
DECL|struct|ezusb_bulktransfer
r_struct
id|ezusb_bulktransfer
(brace
DECL|member|ep
r_int
r_int
id|ep
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EZUSB_BULK
mdefine_line|#define EZUSB_BULK           _IOWR(&squot;E&squot;, 2, struct ezusb_bulktransfer)
DECL|macro|EZUSB_RESETEP
mdefine_line|#define EZUSB_RESETEP        _IOR(&squot;E&squot;, 3, unsigned int)
DECL|struct|ezusb_setinterface
r_struct
id|ezusb_setinterface
(brace
DECL|member|interface
r_int
r_int
id|interface
suffix:semicolon
DECL|member|altsetting
r_int
r_int
id|altsetting
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EZUSB_SETINTERFACE
mdefine_line|#define EZUSB_SETINTERFACE   _IOR(&squot;E&squot;, 4, struct ezusb_setinterface)
DECL|struct|ezusb_isotransfer
r_struct
id|ezusb_isotransfer
(brace
DECL|member|ep
r_int
r_int
id|ep
suffix:semicolon
DECL|member|pktsz
r_int
r_int
id|pktsz
suffix:semicolon
DECL|member|framesperint
r_int
r_int
id|framesperint
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ezusb_isodata
r_struct
id|ezusb_isodata
(brace
DECL|member|ep
r_int
r_int
id|ep
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|bufqueued
r_int
r_int
id|bufqueued
suffix:semicolon
DECL|member|buffree
r_int
r_int
id|buffree
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EZUSB_STARTISO
mdefine_line|#define EZUSB_STARTISO       _IOR(&squot;E&squot;, 8, struct ezusb_isotransfer)
DECL|macro|EZUSB_STOPISO
mdefine_line|#define EZUSB_STOPISO        _IOR(&squot;E&squot;, 9, unsigned int)
DECL|macro|EZUSB_ISODATA
mdefine_line|#define EZUSB_ISODATA        _IOWR(&squot;E&squot;, 10, struct ezusb_isodata)
DECL|macro|EZUSB_PAUSEISO
mdefine_line|#define EZUSB_PAUSEISO       _IOR(&squot;E&squot;, 11, unsigned int)
DECL|macro|EZUSB_RESUMEISO
mdefine_line|#define EZUSB_RESUMEISO      _IOR(&squot;E&squot;, 12, unsigned int)
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* _LINUX_EZUSB_H */
eof
