macro_line|#ifndef _FTAPE_RW_H
DECL|macro|_FTAPE_RW_H
mdefine_line|#define _FTAPE_RW_H
multiline_comment|/*&n; * Copyright (C) 1993-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-rw.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:25 $&n; *&n; *      This file contains the definitions for the read and write&n; *      functions for the QIC-117 floppy-tape driver for Linux.&n; *&n; * Claus-Justus Heine (1996/09/20): Add definition of format code 6&n; * Claus-Justus Heine (1996/10/04): Changed GET/PUT macros to cast to (__u8 *)&n; *&n; */
macro_line|#include &quot;../lowlevel/fdc-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-init.h&quot;
macro_line|#include &quot;../lowlevel/ftape-bsm.h&quot;
macro_line|#include &lt;asm/unaligned.h&gt;
DECL|macro|GET2
mdefine_line|#define GET2(address, offset) get_unaligned((__u16*)((__u8 *)address + offset))
DECL|macro|GET4
mdefine_line|#define GET4(address, offset) get_unaligned((__u32*)((__u8 *)address + offset))
DECL|macro|GET8
mdefine_line|#define GET8(address, offset) get_unaligned((__u64*)((__u8 *)address + offset))
DECL|macro|PUT2
mdefine_line|#define PUT2(address, offset , value) put_unaligned((value), (__u16*)((__u8 *)address + offset))
DECL|macro|PUT4
mdefine_line|#define PUT4(address, offset , value) put_unaligned((value), (__u32*)((__u8 *)address + offset))
DECL|macro|PUT8
mdefine_line|#define PUT8(address, offset , value) put_unaligned((value), (__u64*)((__u8 *)address + offset))
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
)brace
suffix:semicolon
DECL|enum|ft_buffer_queue
r_typedef
r_enum
id|ft_buffer_queue
(brace
DECL|enumerator|ft_queue_head
id|ft_queue_head
op_assign
l_int|0
comma
DECL|enumerator|ft_queue_tail
id|ft_queue_tail
op_assign
l_int|1
DECL|typedef|ft_buffer_queue_t
)brace
id|ft_buffer_queue_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* tape head position */
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
DECL|member|bot
r_volatile
r_int
r_int
id|bot
suffix:semicolon
multiline_comment|/* logical begin of track */
DECL|member|eot
r_volatile
r_int
r_int
id|eot
suffix:semicolon
multiline_comment|/* logical end of track */
DECL|member|known
r_volatile
r_int
r_int
id|known
suffix:semicolon
multiline_comment|/* validates bot, segment, sector */
DECL|typedef|location_record
)brace
id|location_record
suffix:semicolon
multiline_comment|/*      Count nr of 1&squot;s in pattern.&n; */
DECL|function|count_ones
r_extern
r_inline
r_int
id|count_ones
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_int
id|bits
suffix:semicolon
r_for
c_loop
(paren
id|bits
op_assign
l_int|0
suffix:semicolon
id|mask
op_ne
l_int|0
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
(brace
op_increment
id|bits
suffix:semicolon
)brace
)brace
r_return
id|bits
suffix:semicolon
)brace
DECL|macro|FT_MAX_NR_BUFFERS
mdefine_line|#define FT_MAX_NR_BUFFERS 16 /* arbitrary value */
multiline_comment|/*      ftape-rw.c defined global vars.&n; */
r_extern
id|buffer_struct
op_star
id|ft_buffer
(braket
id|FT_MAX_NR_BUFFERS
)braket
suffix:semicolon
r_extern
r_int
id|ft_nr_buffers
suffix:semicolon
r_extern
id|location_record
id|ft_location
suffix:semicolon
r_extern
r_volatile
r_int
id|ftape_tape_running
suffix:semicolon
multiline_comment|/*      ftape-rw.c defined global functions.&n; */
r_extern
r_int
id|ftape_setup_new_segment
c_func
(paren
id|buffer_struct
op_star
id|buff
comma
r_int
id|segment_id
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|ftape_calc_next_cluster
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
id|ftape_next_buffer
(paren
id|ft_buffer_queue_t
id|pos
)paren
suffix:semicolon
r_extern
id|buffer_struct
op_star
id|ftape_get_buffer
(paren
id|ft_buffer_queue_t
id|pos
)paren
suffix:semicolon
r_extern
r_int
id|ftape_buffer_id
(paren
id|ft_buffer_queue_t
id|pos
)paren
suffix:semicolon
r_extern
r_void
id|ftape_reset_buffer
c_func
(paren
r_void
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
id|__u8
id|drive_configuration
)paren
suffix:semicolon
r_extern
r_int
id|ftape_wait_segment
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
r_extern
r_int
id|ftape_stop_tape
c_func
(paren
r_int
op_star
id|pstatus
)paren
suffix:semicolon
r_extern
r_int
id|ftape_handle_logical_eot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|buffer_state_enum
id|ftape_set_state
c_func
(paren
id|buffer_state_enum
id|new_state
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _FTAPE_RW_H */
eof
