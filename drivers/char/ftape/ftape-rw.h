macro_line|#ifndef _FTAPE_RW_H
DECL|macro|_FTAPE_RW_H
mdefine_line|#define _FTAPE_RW_H
multiline_comment|/*&n; * Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-rw.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.33 $&n; $Date: 1995/04/22 07:30:15 $&n; $State: Beta $&n; *&n; *      This file contains the definitions for the read and write&n; *      functions for the QIC-117 floppy-tape driver for Linux.&n; *&n; */
macro_line|#include &quot;fdc-io.h&quot;
macro_line|#include &quot;kernel-interface.h&quot;
DECL|macro|GET2
mdefine_line|#define GET2( address, offset) *(short*)(address + offset)
DECL|macro|GET4
mdefine_line|#define GET4( address, offset) *(long*)(address + offset)
DECL|macro|PUT2
mdefine_line|#define PUT2( address, offset, value) *(short*)(address + offset) = value
DECL|macro|PUT4
mdefine_line|#define PUT4( address, offset, value) *(long*)(address + offset) = value
DECL|enum|runner_status_enum
r_enum
id|runner_status_enum
(brace
DECL|enumerator|idle
id|idle
op_assign
l_int|0
comma
DECL|enumerator|running
id|running
comma
DECL|enumerator|do_abort
id|do_abort
comma
DECL|enumerator|aborting
id|aborting
comma
DECL|enumerator|logical_eot
id|logical_eot
comma
DECL|enumerator|end_of_tape
id|end_of_tape
comma
DECL|enumerator|buffer_overrun
id|buffer_overrun
comma
DECL|enumerator|buffer_underrun
id|buffer_underrun
comma
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|address
id|byte
op_star
id|address
suffix:semicolon
DECL|member|status
r_volatile
id|buffer_state_enum
id|status
suffix:semicolon
DECL|member|ptr
r_volatile
id|byte
op_star
id|ptr
suffix:semicolon
DECL|member|bytes
r_volatile
r_int
id|bytes
suffix:semicolon
DECL|member|segment_id
r_volatile
r_int
id|segment_id
suffix:semicolon
multiline_comment|/* bitmap for remainder of segment not yet handled.&n;&t; * one bit set for each bad sector that must be skipped.&n;&t; */
DECL|member|bad_sector_map
r_volatile
r_int
r_int
id|bad_sector_map
suffix:semicolon
multiline_comment|/* bitmap with bad data blocks in data buffer.&n;&t; * the errors in this map may be retried.&n;&t; */
DECL|member|soft_error_map
r_volatile
r_int
r_int
id|soft_error_map
suffix:semicolon
multiline_comment|/* bitmap with bad data blocks in data buffer&n;&t; * the errors in this map may not be retried.&n;&t; */
DECL|member|hard_error_map
r_volatile
r_int
r_int
id|hard_error_map
suffix:semicolon
multiline_comment|/* retry counter for soft errors.&n;&t; */
DECL|member|retry
r_volatile
r_int
id|retry
suffix:semicolon
multiline_comment|/* sectors to skip on retry ???&n;&t; */
DECL|member|skip
r_volatile
r_int
r_int
id|skip
suffix:semicolon
multiline_comment|/* nr of data blocks in data buffer&n;&t; */
DECL|member|data_offset
r_volatile
r_int
id|data_offset
suffix:semicolon
multiline_comment|/* offset in segment for first sector to be handled.&n;&t; */
DECL|member|sector_offset
r_volatile
r_int
id|sector_offset
suffix:semicolon
multiline_comment|/* size of cluster of good sectors to be handled.&n;&t; */
DECL|member|sector_count
r_volatile
r_int
id|sector_count
suffix:semicolon
multiline_comment|/* size of remaining part of segment to be handled.&n;&t; */
DECL|member|remaining
r_volatile
r_int
id|remaining
suffix:semicolon
multiline_comment|/* points to next segment (contigious) to be handled,&n;&t; * or is zero if no read-ahead is allowed.&n;&t; */
DECL|member|next_segment
r_volatile
r_int
id|next_segment
suffix:semicolon
multiline_comment|/* flag being set if deleted data was read.&n;&t; */
DECL|member|deleted
r_volatile
r_int
id|deleted
suffix:semicolon
DECL|member|head
r_volatile
id|byte
id|head
suffix:semicolon
DECL|member|cyl
r_volatile
id|byte
id|cyl
suffix:semicolon
DECL|member|sect
r_volatile
id|byte
id|sect
suffix:semicolon
DECL|typedef|buffer_struct
)brace
id|buffer_struct
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|typedef|ftape_fast_start_struct
)brace
id|ftape_fast_start_struct
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|free
r_int
id|free
suffix:semicolon
DECL|typedef|ftape_last_segment_struct
)brace
id|ftape_last_segment_struct
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* tape head position */
DECL|member|known
r_volatile
r_int
id|known
suffix:semicolon
multiline_comment|/* validates bot, segment, sector */
DECL|member|bot
r_volatile
r_int
id|bot
suffix:semicolon
multiline_comment|/* logical begin of track */
DECL|member|eot
r_volatile
r_int
id|eot
suffix:semicolon
multiline_comment|/* logical end of track */
DECL|member|segment
r_volatile
r_int
id|segment
suffix:semicolon
multiline_comment|/* current segment */
DECL|member|sector
r_volatile
r_int
id|sector
suffix:semicolon
multiline_comment|/* sector offset within current segment */
DECL|typedef|location_record
)brace
id|location_record
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|fmt_normal
DECL|enumerator|fmt_1100ft
DECL|enumerator|fmt_wide
DECL|enumerator|fmt_425ft
id|fmt_normal
op_assign
l_int|2
comma
id|fmt_1100ft
op_assign
l_int|3
comma
id|fmt_wide
op_assign
l_int|4
comma
id|fmt_425ft
op_assign
l_int|5
DECL|typedef|format_type
)brace
id|format_type
suffix:semicolon
multiline_comment|/*      ftape-rw.c defined global vars.&n; */
r_extern
r_int
id|tracing
suffix:semicolon
r_extern
id|byte
id|trace_id
suffix:semicolon
r_extern
id|buffer_struct
id|buffer
(braket
)braket
suffix:semicolon
r_extern
id|location_record
id|location
suffix:semicolon
r_extern
r_volatile
id|ftape_fast_start_struct
id|ftape_fast_start
suffix:semicolon
r_extern
id|byte
id|deblock_buffer
(braket
(paren
id|SECTORS_PER_SEGMENT
op_minus
l_int|3
)paren
op_star
id|SECTOR_SIZE
)braket
suffix:semicolon
r_extern
id|byte
id|scratch_buffer
(braket
(paren
id|SECTORS_PER_SEGMENT
op_minus
l_int|3
)paren
op_star
id|SECTOR_SIZE
)braket
suffix:semicolon
r_extern
id|ftape_last_segment_struct
id|ftape_last_segment
suffix:semicolon
r_extern
r_int
id|header_segment_1
suffix:semicolon
r_extern
r_int
id|header_segment_2
suffix:semicolon
r_extern
r_int
id|used_header_segment
suffix:semicolon
r_extern
r_int
r_int
id|fast_seek_segment_time
suffix:semicolon
r_extern
r_volatile
r_int
id|tape_running
suffix:semicolon
r_extern
id|format_type
id|format_code
suffix:semicolon
multiline_comment|/*      ftape-rw.c defined global functions.&n; */
r_extern
r_int
id|count_ones
c_func
(paren
r_int
r_int
id|mask
)paren
suffix:semicolon
r_extern
r_int
id|valid_segment_no
c_func
(paren
r_int
id|segment
)paren
suffix:semicolon
r_extern
r_int
id|setup_new_segment
c_func
(paren
id|buffer_struct
op_star
id|buff
comma
r_int
r_int
id|segment_id
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|calc_next_cluster
c_func
(paren
id|buffer_struct
op_star
id|buff
)paren
suffix:semicolon
r_extern
id|buffer_struct
op_star
id|next_buffer
c_func
(paren
r_volatile
r_int
op_star
id|x
)paren
suffix:semicolon
r_extern
r_int
id|ftape_read_id
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_tape_parameters
c_func
(paren
id|byte
id|drive_configuration
)paren
suffix:semicolon
r_extern
r_int
id|wait_segment
c_func
(paren
id|buffer_state_enum
id|state
)paren
suffix:semicolon
r_extern
r_int
id|ftape_dumb_stop
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_start_tape
c_func
(paren
r_int
id|segment_id
comma
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/*      fdc-io.c defined global functions.&n; */
r_extern
r_int
id|setup_fdc_and_dma
c_func
(paren
id|buffer_struct
op_star
id|buff
comma
id|byte
id|operation
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _FTAPE_RW_H */
eof
