multiline_comment|/*&n; *      Copyright (C) 1996, 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-rw.c,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:08 $&n; *&n; *      This file contains some common code for the r/w code for&n; *      zftape.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/zftape.h&gt;
macro_line|#include &quot;../zftape/zftape-init.h&quot;
macro_line|#include &quot;../zftape/zftape-eof.h&quot;
macro_line|#include &quot;../zftape/zftape-ctl.h&quot;
macro_line|#include &quot;../zftape/zftape-write.h&quot;
macro_line|#include &quot;../zftape/zftape-read.h&quot;
macro_line|#include &quot;../zftape/zftape-rw.h&quot;
macro_line|#include &quot;../zftape/zftape-vtbl.h&quot;
multiline_comment|/*      Global vars.&n; */
DECL|variable|zft_deblock_buf
id|__u8
op_star
id|zft_deblock_buf
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|zft_hseg_buf
id|__u8
op_star
id|zft_hseg_buf
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|zft_deblock_segment
r_int
id|zft_deblock_segment
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|zft_io_state
id|zft_status_enum
id|zft_io_state
op_assign
id|zft_idle
suffix:semicolon
DECL|variable|zft_header_changed
r_int
id|zft_header_changed
op_assign
l_int|0
suffix:semicolon
DECL|variable|zft_bad_sector_map_changed
r_int
id|zft_bad_sector_map_changed
op_assign
l_int|0
suffix:semicolon
DECL|variable|zft_qic113
r_int
id|zft_qic113
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* conform to old specs. and old zftape */
DECL|variable|zft_use_compression
r_int
id|zft_use_compression
op_assign
l_int|0
suffix:semicolon
DECL|variable|zft_pos
id|zft_position
id|zft_pos
op_assign
(brace
op_minus
l_int|1
comma
multiline_comment|/* seg_pos */
l_int|0
comma
multiline_comment|/* seg_byte_pos */
l_int|0
comma
multiline_comment|/* tape_pos */
l_int|0
multiline_comment|/* volume_pos */
)brace
suffix:semicolon
DECL|variable|zft_blk_sz
r_int
r_int
id|zft_blk_sz
op_assign
id|CONFIG_ZFT_DFLT_BLK_SZ
suffix:semicolon
DECL|variable|zft_capacity
id|__s64
id|zft_capacity
op_assign
l_int|0
suffix:semicolon
DECL|variable|zft_written_segments
r_int
r_int
id|zft_written_segments
op_assign
l_int|0
suffix:semicolon
DECL|variable|zft_label_changed
r_int
id|zft_label_changed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*      Local vars.&n; */
DECL|function|zft_get_seg_sz
r_int
r_int
id|zft_get_seg_sz
c_func
(paren
r_int
r_int
id|segment
)paren
(brace
r_int
id|size
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_any
)paren
suffix:semicolon
id|size
op_assign
id|FT_SEGMENT_SIZE
op_minus
id|count_ones
c_func
(paren
id|ftape_get_bad_sector_entry
c_func
(paren
id|segment
)paren
)paren
op_star
id|FT_SECTOR_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
id|TRACE_EXIT
(paren
r_int
)paren
id|size
suffix:semicolon
)brace
r_else
(brace
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* ftape_set_flags(). Claus-Justus Heine, 1994/1995&n; */
DECL|function|zft_set_flags
r_void
id|zft_set_flags
c_func
(paren
r_int
id|minor_unit
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|zft_use_compression
op_assign
id|zft_qic_mode
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|minor_unit
op_amp
id|ZFT_MINOR_OP_MASK
)paren
(brace
r_case
(paren
id|ZFT_Q80_MODE
op_or
id|ZFT_ZIP_MODE
)paren
suffix:colon
r_case
id|ZFT_ZIP_MODE
suffix:colon
id|zft_use_compression
op_assign
l_int|1
suffix:semicolon
r_case
l_int|0
suffix:colon
r_case
id|ZFT_Q80_MODE
suffix:colon
id|zft_qic_mode
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|zft_mt_compression
)paren
(brace
multiline_comment|/* override the default */
id|zft_use_compression
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ZFT_RAW_MODE
suffix:colon
id|TRACE
c_func
(paren
id|ft_t_noise
comma
l_string|&quot;switching to raw mode&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|TRACE
c_func
(paren
id|ft_t_warn
comma
l_string|&quot;Warning:&bslash;n&quot;
id|KERN_INFO
l_string|&quot;Wrong combination of minor device bits.&bslash;n&quot;
id|KERN_INFO
l_string|&quot;Switching to raw read-only mode.&quot;
)paren
suffix:semicolon
id|zft_write_protected
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
)brace
multiline_comment|/* computes the segment and byte offset inside the segment&n; * corresponding to tape_pos.&n; *&n; * tape_pos gives the offset in bytes from the beginning of the&n; * ft_first_data_segment *seg_byte_pos is the offset in the current&n; * segment in bytes&n; *&n; * Of, if this routine was called often one should cache the last data&n; * pos it was called with, but actually this is only needed in&n; * ftape_seek_block(), that is, almost never.&n; */
DECL|function|zft_calc_seg_byte_coord
r_int
id|zft_calc_seg_byte_coord
c_func
(paren
r_int
op_star
id|seg_byte_pos
comma
id|__s64
id|tape_pos
)paren
(brace
r_int
id|segment
suffix:semicolon
r_int
id|seg_sz
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tape_pos
op_eq
l_int|0
)paren
(brace
op_star
id|seg_byte_pos
op_assign
l_int|0
suffix:semicolon
id|segment
op_assign
id|ft_first_data_segment
suffix:semicolon
)brace
r_else
(brace
id|seg_sz
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|segment
op_assign
id|ft_first_data_segment
suffix:semicolon
(paren
(paren
id|tape_pos
OG
l_int|0
)paren
op_logical_and
(paren
id|segment
op_le
id|ft_last_data_segment
)paren
)paren
suffix:semicolon
id|segment
op_increment
)paren
(brace
id|seg_sz
op_assign
id|zft_get_seg_sz
c_func
(paren
id|segment
)paren
suffix:semicolon
id|tape_pos
op_sub_assign
id|seg_sz
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tape_pos
op_ge
l_int|0
)paren
(brace
multiline_comment|/* the case tape_pos &gt; != 0 means that the&n;&t;&t;&t; * argument tape_pos lies beyond the EOT.&n;&t;&t;&t; */
op_star
id|seg_byte_pos
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* tape_pos &lt; 0 */
id|segment
op_decrement
suffix:semicolon
op_star
id|seg_byte_pos
op_assign
id|tape_pos
op_plus
id|seg_sz
suffix:semicolon
)brace
)brace
id|TRACE_EXIT
c_func
(paren
id|segment
)paren
suffix:semicolon
)brace
multiline_comment|/* ftape_calc_tape_pos().&n; *&n; * computes the offset in bytes from the beginning of the&n; * ft_first_data_segment inverse to ftape_calc_seg_byte_coord&n; *&n; * We should do some caching. But how:&n; *&n; * Each time the header segments are read in, this routine is called&n; * with ft_tracks_per_tape*segments_per_track argumnet. So this should be&n; * the time to reset the cache.&n; *&n; * Also, it might be in the future that the bad sector map gets&n; * changed.  -&gt; reset the cache&n; */
DECL|variable|seg_pos
r_static
r_int
id|seg_pos
op_assign
l_int|0
suffix:semicolon
DECL|variable|tape_pos
r_static
id|__s64
id|tape_pos
op_assign
l_int|0
suffix:semicolon
DECL|function|zft_get_capacity
id|__s64
id|zft_get_capacity
c_func
(paren
r_void
)paren
(brace
id|seg_pos
op_assign
id|ft_first_data_segment
suffix:semicolon
id|tape_pos
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|seg_pos
op_le
id|ft_last_data_segment
)paren
(brace
id|tape_pos
op_add_assign
id|zft_get_seg_sz
c_func
(paren
id|seg_pos
op_increment
)paren
suffix:semicolon
)brace
r_return
id|tape_pos
suffix:semicolon
)brace
DECL|function|zft_calc_tape_pos
id|__s64
id|zft_calc_tape_pos
c_func
(paren
r_int
id|segment
)paren
(brace
r_int
id|d1
comma
id|d2
comma
id|d3
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_any
)paren
suffix:semicolon
r_if
c_cond
(paren
id|segment
OG
id|ft_last_data_segment
)paren
(brace
id|TRACE_EXIT
id|zft_capacity
suffix:semicolon
)brace
r_if
c_cond
(paren
id|segment
OL
id|ft_first_data_segment
)paren
(brace
id|TRACE_EXIT
l_int|0
suffix:semicolon
)brace
id|d2
op_assign
id|segment
op_minus
id|seg_pos
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|d2
OG
l_int|10
)paren
(brace
id|d1
op_assign
id|segment
op_minus
id|ft_first_data_segment
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|d2
OG
id|d1
)paren
(brace
id|tape_pos
op_assign
l_int|0
suffix:semicolon
id|seg_pos
op_assign
id|ft_first_data_segment
suffix:semicolon
id|d2
op_assign
id|d1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|d2
OG
l_int|10
)paren
(brace
id|d3
op_assign
id|ft_last_data_segment
op_minus
id|segment
suffix:semicolon
r_if
c_cond
(paren
id|d2
OG
id|d3
)paren
(brace
id|tape_pos
op_assign
id|zft_capacity
suffix:semicolon
id|seg_pos
op_assign
id|ft_last_data_segment
op_plus
l_int|1
suffix:semicolon
id|d2
op_assign
op_minus
id|d3
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|d2
OG
l_int|0
)paren
(brace
r_while
c_loop
(paren
id|seg_pos
OL
id|segment
)paren
(brace
id|tape_pos
op_add_assign
id|zft_get_seg_sz
c_func
(paren
id|seg_pos
op_increment
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|seg_pos
OG
id|segment
)paren
(brace
id|tape_pos
op_sub_assign
id|zft_get_seg_sz
c_func
(paren
op_decrement
id|seg_pos
)paren
suffix:semicolon
)brace
)brace
id|TRACE
c_func
(paren
id|ft_t_noise
comma
l_string|&quot;new cached pos: %d&quot;
comma
id|seg_pos
)paren
suffix:semicolon
id|TRACE_EXIT
id|tape_pos
suffix:semicolon
)brace
multiline_comment|/* copy Z-label string to buffer, keeps track of the correct offset in&n; * `buffer&squot; &n; */
DECL|function|zft_update_label
r_void
id|zft_update_label
c_func
(paren
id|__u8
op_star
id|buffer
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
op_amp
id|buffer
(braket
id|FT_LABEL
)braket
comma
id|ZFTAPE_LABEL
comma
r_sizeof
(paren
id|ZFTAPE_LABEL
)paren
op_minus
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;updating label from &bslash;&quot;%s&bslash;&quot; to &bslash;&quot;%s&bslash;&quot;&quot;
comma
op_amp
id|buffer
(braket
id|FT_LABEL
)braket
comma
id|ZFTAPE_LABEL
)paren
suffix:semicolon
id|strcpy
c_func
(paren
op_amp
id|buffer
(braket
id|FT_LABEL
)braket
comma
id|ZFTAPE_LABEL
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|buffer
(braket
id|FT_LABEL
)braket
op_plus
r_sizeof
(paren
id|ZFTAPE_LABEL
)paren
op_minus
l_int|1
comma
l_char|&squot; &squot;
comma
id|FT_LABEL_SZ
op_minus
r_sizeof
(paren
id|ZFTAPE_LABEL
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|PUT4
c_func
(paren
id|buffer
comma
id|FT_LABEL_DATE
comma
l_int|0
)paren
suffix:semicolon
id|zft_label_changed
op_assign
id|zft_header_changed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* changed */
)brace
id|TRACE_EXIT
suffix:semicolon
)brace
DECL|function|zft_verify_write_segments
r_int
id|zft_verify_write_segments
c_func
(paren
r_int
r_int
id|segment
comma
id|__u8
op_star
id|data
comma
r_int
id|size
comma
id|__u8
op_star
id|buffer
)paren
(brace
r_int
id|result
suffix:semicolon
id|__u8
op_star
id|write_buf
suffix:semicolon
id|__u8
op_star
id|src_buf
suffix:semicolon
r_int
id|single
suffix:semicolon
r_int
id|seg_pos
suffix:semicolon
r_int
id|seg_sz
suffix:semicolon
r_int
id|remaining
suffix:semicolon
id|ft_write_mode_t
id|write_mode
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
id|seg_pos
op_assign
id|segment
suffix:semicolon
id|seg_sz
op_assign
id|zft_get_seg_sz
c_func
(paren
id|seg_pos
)paren
suffix:semicolon
id|src_buf
op_assign
id|data
suffix:semicolon
id|single
op_assign
id|size
op_le
id|seg_sz
suffix:semicolon
id|remaining
op_assign
id|size
suffix:semicolon
r_do
(brace
id|TRACE
c_func
(paren
id|ft_t_noise
comma
l_string|&quot;&bslash;n&quot;
id|KERN_INFO
l_string|&quot;remaining: %d&bslash;n&quot;
id|KERN_INFO
l_string|&quot;seg_sz   : %d&bslash;n&quot;
id|KERN_INFO
l_string|&quot;segment  : %d&quot;
comma
id|remaining
comma
id|seg_sz
comma
id|seg_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remaining
op_eq
id|seg_sz
)paren
(brace
id|write_buf
op_assign
id|src_buf
suffix:semicolon
id|write_mode
op_assign
id|single
ques
c_cond
id|FT_WR_SINGLE
suffix:colon
id|FT_WR_MULTI
suffix:semicolon
id|remaining
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|remaining
OG
id|seg_sz
)paren
(brace
id|write_buf
op_assign
id|src_buf
suffix:semicolon
id|write_mode
op_assign
id|FT_WR_ASYNC
suffix:semicolon
multiline_comment|/* don&squot;t start tape */
id|remaining
op_sub_assign
id|seg_sz
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* remaining &lt; seg_sz */
id|write_buf
op_assign
id|buffer
suffix:semicolon
id|memcpy
c_func
(paren
id|write_buf
comma
id|src_buf
comma
id|remaining
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|write_buf
(braket
id|remaining
)braket
comma
l_char|&squot;&bslash;0&squot;
comma
id|seg_sz
op_minus
id|remaining
)paren
suffix:semicolon
id|write_mode
op_assign
id|single
ques
c_cond
id|FT_WR_SINGLE
suffix:colon
id|FT_WR_MULTI
suffix:semicolon
id|remaining
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ftape_write_segment
c_func
(paren
id|seg_pos
comma
id|write_buf
comma
id|write_mode
)paren
)paren
op_ne
id|seg_sz
)paren
(brace
id|TRACE
c_func
(paren
id|ft_t_err
comma
l_string|&quot;Error: &quot;
l_string|&quot;Couldn&squot;t write segment %d&quot;
comma
id|seg_pos
)paren
suffix:semicolon
id|TRACE_EXIT
id|result
OL
l_int|0
ques
c_cond
id|result
suffix:colon
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* bail out */
)brace
id|zft_written_segments
op_increment
suffix:semicolon
id|seg_sz
op_assign
id|zft_get_seg_sz
c_func
(paren
op_increment
id|seg_pos
)paren
suffix:semicolon
id|src_buf
op_add_assign
id|result
suffix:semicolon
)brace
r_while
c_loop
(paren
id|remaining
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ftape_get_status
c_func
(paren
)paren
op_member_access_from_pointer
id|fti_state
op_eq
id|writing
)paren
(brace
id|TRACE_CATCH
c_func
(paren
id|ftape_loop_until_writes_done
c_func
(paren
)paren
comma
)paren
suffix:semicolon
id|TRACE_CATCH
c_func
(paren
id|ftape_abort_operation
c_func
(paren
)paren
comma
)paren
suffix:semicolon
id|zft_prevent_flush
c_func
(paren
)paren
suffix:semicolon
)brace
id|seg_pos
op_assign
id|segment
suffix:semicolon
id|src_buf
op_assign
id|data
suffix:semicolon
id|remaining
op_assign
id|size
suffix:semicolon
r_do
(brace
id|TRACE_CATCH
c_func
(paren
id|result
op_assign
id|ftape_read_segment
c_func
(paren
id|seg_pos
comma
id|buffer
comma
id|single
ques
c_cond
id|FT_RD_SINGLE
suffix:colon
id|FT_RD_AHEAD
)paren
comma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|src_buf
comma
id|buffer
comma
id|remaining
OG
id|result
ques
c_cond
id|result
suffix:colon
id|remaining
)paren
op_ne
l_int|0
)paren
(brace
id|TRACE_ABORT
c_func
(paren
op_minus
id|EIO
comma
id|ft_t_err
comma
l_string|&quot;Failed to verify written segment %d&quot;
comma
id|seg_pos
)paren
suffix:semicolon
)brace
id|remaining
op_sub_assign
id|result
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_noise
comma
l_string|&quot;verify successful:&bslash;n&quot;
id|KERN_INFO
l_string|&quot;segment  : %d&bslash;n&quot;
id|KERN_INFO
l_string|&quot;segsize  : %d&bslash;n&quot;
id|KERN_INFO
l_string|&quot;remaining: %d&quot;
comma
id|seg_pos
comma
id|result
comma
id|remaining
)paren
suffix:semicolon
id|src_buf
op_add_assign
id|seg_sz
suffix:semicolon
id|seg_pos
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|remaining
OG
l_int|0
)paren
suffix:semicolon
id|TRACE_EXIT
id|size
suffix:semicolon
)brace
multiline_comment|/* zft_erase().  implemented compression-handling&n; *&n; * calculate the first data-segment when using/not using compression.&n; *&n; * update header-segment and compression-map-segment.&n; */
DECL|function|zft_erase
r_int
id|zft_erase
c_func
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zft_header_read
)paren
(brace
id|TRACE_CATCH
c_func
(paren
id|zft_vmalloc_once
c_func
(paren
(paren
r_void
op_star
op_star
)paren
op_amp
id|zft_hseg_buf
comma
id|FT_SEGMENT_SIZE
)paren
comma
)paren
suffix:semicolon
multiline_comment|/* no need to read the vtbl and compression map */
id|TRACE_CATCH
c_func
(paren
id|ftape_read_header_segment
c_func
(paren
id|zft_hseg_buf
)paren
comma
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|zft_old_ftape
op_assign
id|zft_ftape_validate_label
c_func
(paren
op_amp
id|zft_hseg_buf
(braket
id|FT_LABEL
)braket
)paren
)paren
)paren
(brace
id|zft_ftape_extract_file_marks
c_func
(paren
id|zft_hseg_buf
)paren
suffix:semicolon
)brace
id|TRACE
c_func
(paren
id|ft_t_noise
comma
l_string|&quot;ft_first_data_segment: %d, ft_last_data_segment: %d&quot;
comma
id|ft_first_data_segment
comma
id|ft_last_data_segment
)paren
suffix:semicolon
id|zft_qic113
op_assign
(paren
id|ft_format_code
op_ne
id|fmt_normal
op_logical_and
id|ft_format_code
op_ne
id|fmt_1100ft
op_logical_and
id|ft_format_code
op_ne
id|fmt_425ft
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|zft_old_ftape
)paren
(brace
id|zft_clear_ftape_file_marks
c_func
(paren
)paren
suffix:semicolon
id|zft_old_ftape
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no longer old ftape */
)brace
id|PUT2
c_func
(paren
id|zft_hseg_buf
comma
id|FT_CMAP_START
comma
l_int|0
)paren
suffix:semicolon
id|zft_volume_table_changed
op_assign
l_int|1
suffix:semicolon
id|zft_capacity
op_assign
id|zft_get_capacity
c_func
(paren
)paren
suffix:semicolon
id|zft_init_vtbl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* the rest must be done in ftape_update_header_segments &n;&t; */
id|zft_header_read
op_assign
l_int|1
suffix:semicolon
id|zft_header_changed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* force update of timestamp */
id|result
op_assign
id|zft_update_header_segments
c_func
(paren
)paren
suffix:semicolon
id|ftape_abort_operation
c_func
(paren
)paren
suffix:semicolon
id|zft_reset_position
c_func
(paren
op_amp
id|zft_pos
)paren
suffix:semicolon
id|zft_set_flags
(paren
id|zft_unit
)paren
suffix:semicolon
id|TRACE_EXIT
id|result
suffix:semicolon
)brace
DECL|function|zft_get_time
r_int
r_int
id|zft_get_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|date
op_assign
id|FT_TIME_STAMP
c_func
(paren
l_int|2097
comma
l_int|11
comma
l_int|30
comma
l_int|23
comma
l_int|59
comma
l_int|59
)paren
suffix:semicolon
multiline_comment|/* fun */
r_return
id|date
suffix:semicolon
)brace
eof