macro_line|#ifndef _FTAPE_CTL_H
DECL|macro|_FTAPE_CTL_H
mdefine_line|#define _FTAPE_CTL_H
multiline_comment|/*&n; * Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-ctl.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.4 $&n; $Date: 1995/05/03 18:04:03 $&n; $State: Beta $&n; *&n; *      This file contains the non-standard IOCTL related definitions&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &quot;vendors.h&quot;
r_typedef
r_struct
(brace
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* any reading or writing done */
multiline_comment|/* isr statistics */
DECL|member|id_am_errors
r_int
r_int
id|id_am_errors
suffix:semicolon
multiline_comment|/* id address mark not found */
DECL|member|id_crc_errors
r_int
r_int
id|id_crc_errors
suffix:semicolon
multiline_comment|/* crc error in id address mark */
DECL|member|data_am_errors
r_int
r_int
id|data_am_errors
suffix:semicolon
multiline_comment|/* data address mark not found */
DECL|member|data_crc_errors
r_int
r_int
id|data_crc_errors
suffix:semicolon
multiline_comment|/* crc error in data field */
DECL|member|overrun_errors
r_int
r_int
id|overrun_errors
suffix:semicolon
multiline_comment|/* fdc access timing problem */
DECL|member|no_data_errors
r_int
r_int
id|no_data_errors
suffix:semicolon
multiline_comment|/* sector not found */
DECL|member|retries
r_int
r_int
id|retries
suffix:semicolon
multiline_comment|/* number of tape retries */
multiline_comment|/* ecc statistics */
DECL|member|crc_errors
r_int
r_int
id|crc_errors
suffix:semicolon
multiline_comment|/* crc error in data */
DECL|member|crc_failures
r_int
r_int
id|crc_failures
suffix:semicolon
multiline_comment|/* bad data without crc error */
DECL|member|ecc_failures
r_int
r_int
id|ecc_failures
suffix:semicolon
multiline_comment|/* failed to correct */
DECL|member|corrected
r_int
r_int
id|corrected
suffix:semicolon
multiline_comment|/* total sectors corrected */
multiline_comment|/* general statistics */
DECL|member|rewinds
r_int
r_int
id|rewinds
suffix:semicolon
multiline_comment|/* number of tape rewinds */
DECL|member|defects
r_int
r_int
id|defects
suffix:semicolon
multiline_comment|/* bad sectors due to media defects */
DECL|typedef|history_record
)brace
id|history_record
suffix:semicolon
multiline_comment|/*&n; *      ftape-ctl.c defined global vars.&n; */
r_extern
r_int
id|ftape_failure
suffix:semicolon
r_extern
r_int
id|write_protected
suffix:semicolon
r_extern
id|ftape_offline
suffix:semicolon
r_extern
r_int
id|formatted
suffix:semicolon
r_extern
r_int
id|no_tape
suffix:semicolon
r_extern
id|history_record
id|history
suffix:semicolon
r_extern
r_int
id|ftape_data_rate
suffix:semicolon
r_extern
r_int
id|going_offline
suffix:semicolon
r_extern
id|vendor_struct
id|drive_type
suffix:semicolon
r_extern
r_int
id|segments_per_track
suffix:semicolon
r_extern
r_int
id|segments_per_head
suffix:semicolon
r_extern
r_int
id|segments_per_cylinder
suffix:semicolon
r_extern
r_int
id|tracks_per_tape
suffix:semicolon
r_extern
r_int
id|ftape_seg_pos
suffix:semicolon
r_extern
r_int
id|first_data_segment
suffix:semicolon
r_extern
r_int
id|ftape_state
suffix:semicolon
r_extern
r_int
id|read_only
suffix:semicolon
multiline_comment|/*&n; *      ftape-ctl.c defined global functions.&n; */
r_extern
r_int
id|_ftape_open
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_ftape_close
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_ftape_ioctl
c_func
(paren
r_int
r_int
id|command
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_to_bot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_to_eot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_new_cartridge
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_abort_operation
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_reset_position
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_calc_timeouts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_init_driver
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
