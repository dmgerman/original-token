multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;ezusb.h  --  Firmware download miscdevice for Anchorchips EZUSB microcontrollers.&n; *&n; *&t;Copyright (C) 1999&n; *          Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _LINUX_EZUSB_H
DECL|macro|_LINUX_EZUSB_H
mdefine_line|#define _LINUX_EZUSB_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|ezusb_old_ctrltransfer
r_struct
id|ezusb_old_ctrltransfer
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
DECL|member|dlen
r_int
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
DECL|struct|ezusb_old_bulktransfer
r_struct
id|ezusb_old_bulktransfer
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
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* in milliseconds */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* in milliseconds */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ezusb_interrupt
r_struct
id|ezusb_interrupt
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
DECL|member|interval
r_int
r_int
id|interval
suffix:semicolon
multiline_comment|/* in milliseconds */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
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
DECL|struct|ezusb_isoframestat
r_struct
id|ezusb_isoframestat
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ezusb_asynccompleted
r_struct
id|ezusb_asynccompleted
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|isostat
r_struct
id|ezusb_isoframestat
id|isostat
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ezusb_asyncbulk
r_struct
id|ezusb_asyncbulk
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
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ezusb_asynciso
r_struct
id|ezusb_asynciso
(brace
DECL|member|ep
r_int
r_int
id|ep
suffix:semicolon
DECL|member|framecnt
r_int
r_int
id|framecnt
suffix:semicolon
DECL|member|startframe
r_int
r_int
id|startframe
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|isostat
r_struct
id|ezusb_isoframestat
id|isostat
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EZUSB_CONTROL
mdefine_line|#define EZUSB_CONTROL           _IOWR(&squot;E&squot;, 1, struct ezusb_ctrltransfer)
DECL|macro|EZUSB_BULK
mdefine_line|#define EZUSB_BULK              _IOWR(&squot;E&squot;, 2, struct ezusb_bulktransfer)
DECL|macro|EZUSB_OLD_CONTROL
mdefine_line|#define EZUSB_OLD_CONTROL       _IOWR(&squot;E&squot;, 0, struct ezusb_old_ctrltransfer)
DECL|macro|EZUSB_OLD_BULK
mdefine_line|#define EZUSB_OLD_BULK          _IOWR(&squot;E&squot;, 2, struct ezusb_old_bulktransfer)
DECL|macro|EZUSB_RESETEP
mdefine_line|#define EZUSB_RESETEP           _IOR(&squot;E&squot;, 3, unsigned int)
DECL|macro|EZUSB_SETINTERFACE
mdefine_line|#define EZUSB_SETINTERFACE      _IOR(&squot;E&squot;, 4, struct ezusb_setinterface)
DECL|macro|EZUSB_SETCONFIGURATION
mdefine_line|#define EZUSB_SETCONFIGURATION  _IOR(&squot;E&squot;, 5, unsigned int)
DECL|macro|EZUSB_ASYNCCOMPLETED
mdefine_line|#define EZUSB_ASYNCCOMPLETED    _IOW(&squot;E&squot;, 8, struct ezusb_asynccompleted)
DECL|macro|EZUSB_ASYNCCOMPLETEDNB
mdefine_line|#define EZUSB_ASYNCCOMPLETEDNB  _IOW(&squot;E&squot;, 9, struct ezusb_asynccompleted)
DECL|macro|EZUSB_REQUESTBULK
mdefine_line|#define EZUSB_REQUESTBULK       _IOR(&squot;E&squot;, 16, struct ezusb_asyncbulk)
DECL|macro|EZUSB_REQUESTISO
mdefine_line|#define EZUSB_REQUESTISO        _IOR(&squot;E&squot;, 17, struct ezusb_asynciso)
DECL|macro|EZUSB_TERMINATEASYNC
mdefine_line|#define EZUSB_TERMINATEASYNC    _IOR(&squot;E&squot;, 18, void *)
DECL|macro|EZUSB_GETFRAMENUMBER
mdefine_line|#define EZUSB_GETFRAMENUMBER    _IOW(&squot;E&squot;, 19, unsigned int)
DECL|macro|EZUSB_INTERRUPT
mdefine_line|#define EZUSB_INTERRUPT&t;&t;_IOWR(&squot;E&squot;, 20, struct ezusb_interrupt)
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* _LINUX_EZUSB_H */
eof
