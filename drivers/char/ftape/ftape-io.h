macro_line|#ifndef _FTAPE_IO_H
DECL|macro|_FTAPE_IO_H
mdefine_line|#define _FTAPE_IO_H
multiline_comment|/*&n; * Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-io.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.36 $&n; $Date: 1995/05/06 16:11:53 $&n; $State: Beta $&n; *&n; *      This file contains definitions for the glue part&n; *      of the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &quot;vendors.h&quot;
r_typedef
r_struct
(brace
DECL|member|seek
r_int
id|seek
suffix:semicolon
DECL|member|reset
r_int
id|reset
suffix:semicolon
DECL|member|rewind
r_int
id|rewind
suffix:semicolon
DECL|member|head_seek
r_int
id|head_seek
suffix:semicolon
DECL|member|stop
r_int
id|stop
suffix:semicolon
DECL|member|pause
r_int
id|pause
suffix:semicolon
DECL|typedef|timeout_table
)brace
id|timeout_table
suffix:semicolon
multiline_comment|/*&n; *      ftape-io.c defined global vars.&n; */
r_extern
id|timeout_table
id|timeout
suffix:semicolon
r_extern
r_int
id|qic_std
suffix:semicolon
r_extern
r_int
id|tape_len
suffix:semicolon
r_extern
r_volatile
r_int
id|current_command
suffix:semicolon
r_extern
r_const
r_struct
id|qic117_command_table
id|qic117_cmds
(braket
)braket
suffix:semicolon
r_extern
r_int
id|might_be_off_track
suffix:semicolon
multiline_comment|/*&n; *      ftape-io.c defined global functions.&n; */
r_extern
r_void
id|udelay
c_func
(paren
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_int
id|udelay_calibrate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_sleep
c_func
(paren
r_int
r_int
id|time
)paren
suffix:semicolon
r_extern
r_void
id|ftape_report_vendor_id
c_func
(paren
r_int
r_int
op_star
id|id
)paren
suffix:semicolon
r_extern
r_int
id|ftape_command
c_func
(paren
r_int
id|command
)paren
suffix:semicolon
r_extern
r_int
id|ftape_command_wait
c_func
(paren
r_int
id|command
comma
r_int
id|timeout
comma
r_int
op_star
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_report_drive_status
c_func
(paren
r_int
op_star
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_report_raw_drive_status
c_func
(paren
r_int
op_star
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_report_status
c_func
(paren
r_int
op_star
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_interrupt_wait
c_func
(paren
r_int
id|time
)paren
suffix:semicolon
r_extern
r_int
id|ftape_ready_wait
c_func
(paren
r_int
id|timeout
comma
r_int
op_star
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_head_to_track
c_func
(paren
r_int
id|track
)paren
suffix:semicolon
r_extern
r_int
id|ftape_parameter
c_func
(paren
r_int
id|command
)paren
suffix:semicolon
r_extern
r_int
id|ftape_in_error_state
c_func
(paren
r_int
id|status
)paren
suffix:semicolon
r_extern
r_int
id|ftape_set_data_rate
c_func
(paren
r_int
id|rate
)paren
suffix:semicolon
r_extern
r_int
id|ftape_report_error
c_func
(paren
r_int
op_star
id|error
comma
r_int
op_star
id|command
comma
r_int
id|report
)paren
suffix:semicolon
r_extern
r_int
id|ftape_reset_drive
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_put_drive_to_sleep
c_func
(paren
id|vendor_struct
id|drive_type
)paren
suffix:semicolon
r_extern
r_int
id|ftape_wakeup_drive
c_func
(paren
id|wake_up_types
id|method
)paren
suffix:semicolon
macro_line|#endif
eof