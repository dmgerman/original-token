macro_line|#ifndef _FTAPE_BSM_H
DECL|macro|_FTAPE_BSM_H
mdefine_line|#define _FTAPE_BSM_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-bsm.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.5 $&n; $Date: 1995/04/22 07:30:15 $&n; $State: Beta $&n; *&n; *      This file contains definitions for the bad sector map handling&n; *      routines for the QIC-117 floppy-tape driver for Linux.&n; */
DECL|macro|EMPTY_SEGMENT
mdefine_line|#define EMPTY_SEGMENT           (0xffffffff)
DECL|macro|FAKE_SEGMENT
mdefine_line|#define FAKE_SEGMENT            (0xfffffffe)
multiline_comment|/*  failed sector log size (only used if format code != 4).&n; */
DECL|macro|FAILED_SECTOR_LOG_SIZE
mdefine_line|#define FAILED_SECTOR_LOG_SIZE  (2 * SECTOR_SIZE - 256)
multiline_comment|/*  maximum (format code 4) bad sector map size (bytes).&n; */
DECL|macro|BAD_SECTOR_MAP_SIZE
mdefine_line|#define BAD_SECTOR_MAP_SIZE     (29 * SECTOR_SIZE - 256)
multiline_comment|/*&n; *      ftape-io.c defined global vars.&n; */
r_extern
id|bad_sector_map_changed
suffix:semicolon
multiline_comment|/*&n; *      ftape-io.c defined global functions.&n; */
r_extern
r_void
id|update_bad_sector_map
c_func
(paren
id|byte
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|store_bad_sector_map
c_func
(paren
id|byte
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|extract_bad_sector_map
c_func
(paren
id|byte
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_bad_sector_entry
c_func
(paren
r_int
id|segment_id
)paren
suffix:semicolon
r_extern
r_void
id|put_bad_sector_entry
c_func
(paren
r_int
id|segment_id
comma
r_int
r_int
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|add_segment_to_bad_sector_map
c_func
(paren
r_int
id|segment
)paren
suffix:semicolon
r_extern
r_void
id|clear_bad_sector_map
c_func
(paren
r_int
id|count
)paren
suffix:semicolon
r_extern
id|byte
op_star
id|find_end_of_bsm_list
c_func
(paren
id|byte
op_star
id|ptr
comma
id|byte
op_star
id|limit
)paren
suffix:semicolon
r_extern
r_void
id|ftape_init_bsm
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
