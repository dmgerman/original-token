macro_line|#ifndef _FTAPE_EOF_H
DECL|macro|_FTAPE_EOF_H
mdefine_line|#define _FTAPE_EOF_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-eof.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.12 $&n; $Date: 1995/04/22 07:30:15 $&n; $State: Beta $&n; *&n; *      Definitions and declarations for the end of file markers&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
multiline_comment|/*      ftape-eof.c defined global vars.&n; */
r_extern
r_int
id|failed_sector_log_changed
suffix:semicolon
r_extern
r_int
id|eof_mark
suffix:semicolon
multiline_comment|/*      ftape-eof.c defined global functions.&n; */
r_extern
r_void
id|clear_eof_mark_if_set
c_func
(paren
r_int
id|segment
comma
r_int
id|byte_count
)paren
suffix:semicolon
r_extern
r_void
id|reset_eof_list
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|check_for_eof
c_func
(paren
r_int
id|segment
)paren
suffix:semicolon
r_extern
r_int
id|ftape_weof
c_func
(paren
r_int
id|count
comma
r_int
id|segment
comma
r_int
id|sector
)paren
suffix:semicolon
r_extern
r_int
id|ftape_erase
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|put_file_mark_in_map
c_func
(paren
r_int
id|segment
comma
r_int
id|sector
)paren
suffix:semicolon
r_extern
r_void
id|extract_file_marks
c_func
(paren
id|byte
op_star
id|address
)paren
suffix:semicolon
r_extern
r_int
id|update_failed_sector_log
c_func
(paren
id|byte
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_eom
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_eof
c_func
(paren
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|ftape_file_no
c_func
(paren
id|daddr_t
op_star
id|file
comma
id|daddr_t
op_star
id|block
)paren
suffix:semicolon
r_extern
r_int
id|ftape_validate_label
c_func
(paren
r_char
op_star
id|label
)paren
suffix:semicolon
macro_line|#endif
eof
