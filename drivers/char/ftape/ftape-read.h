macro_line|#ifndef _FTAPE_READ_H
DECL|macro|_FTAPE_READ_H
mdefine_line|#define _FTAPE_READ_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-read.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.13 $&n; $Date: 1995/05/10 16:09:36 $&n; $State: Beta $&n; *&n; *      This file contains the definitions for the read functions&n; *      for the QIC-117 floppy-tape driver for Linux.&n; *&n; */
multiline_comment|/*      ftape-read.c defined global vars.&n; */
multiline_comment|/*      ftape-read.c defined global functions.&n; */
r_extern
r_int
id|_ftape_read
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|req_len
)paren
suffix:semicolon
r_extern
r_int
id|read_header_segment
c_func
(paren
id|byte
op_star
id|address
)paren
suffix:semicolon
r_extern
r_int
id|read_segment
c_func
(paren
r_int
id|segment
comma
id|byte
op_star
id|address
comma
r_int
op_star
id|eof_mark
comma
r_int
id|read_ahead
)paren
suffix:semicolon
r_extern
r_void
id|ftape_zap_read_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _FTAPE_READ_H */
eof
