multiline_comment|/*&n; *      Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape-write.c,v $&n; $Author: bas $&n; *&n; $Revision: 1.26 $&n; $Date: 1995/05/27 08:55:27 $&n; $State: Beta $&n; *&n; *      This file contains the writing code&n; *      for the QIC-117 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;tracing.h&quot;
macro_line|#include &quot;ftape-write.h&quot;
macro_line|#include &quot;ftape-read.h&quot;
macro_line|#include &quot;qic117.h&quot;
macro_line|#include &quot;ftape-io.h&quot;
macro_line|#include &quot;ftape-ctl.h&quot;
macro_line|#include &quot;ftape-rw.h&quot;
macro_line|#include &quot;ftape-eof.h&quot;
macro_line|#include &quot;ecc.h&quot;
macro_line|#include &quot;ftape-bsm.h&quot;
multiline_comment|/*      Global vars.&n; */
multiline_comment|/*      Local vars.&n; */
DECL|variable|buf_pos_wr
r_static
r_int
id|buf_pos_wr
op_assign
l_int|0
suffix:semicolon
DECL|variable|last_write_failed
r_static
r_int
id|last_write_failed
op_assign
l_int|0
suffix:semicolon
DECL|variable|need_flush
r_static
r_int
id|need_flush
op_assign
l_int|0
suffix:semicolon
DECL|macro|WRITE_MULTI
mdefine_line|#define WRITE_MULTI  0
DECL|macro|WRITE_SINGLE
mdefine_line|#define WRITE_SINGLE 1
DECL|function|ftape_zap_write_buffers
r_void
id|ftape_zap_write_buffers
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_BUFFERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|buffer
(braket
id|i
)braket
dot
id|status
op_assign
id|done
suffix:semicolon
)brace
id|need_flush
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|copy_and_gen_ecc
r_int
id|copy_and_gen_ecc
c_func
(paren
r_char
op_star
id|destination
comma
id|byte
op_star
id|source
comma
r_int
r_int
id|bad_sector_map
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|8
comma
l_string|&quot;copy_and_gen_ecc&quot;
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
r_struct
id|memory_segment
id|mseg
suffix:semicolon
r_int
id|bads
op_assign
id|count_ones
c_func
(paren
id|bad_sector_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bads
OG
l_int|0
)paren
(brace
id|TRACEi
c_func
(paren
l_int|4
comma
l_string|&quot;bad sectors in map:&quot;
comma
id|bads
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bads
op_plus
l_int|3
op_ge
id|SECTORS_PER_SEGMENT
)paren
(brace
id|TRACE
c_func
(paren
l_int|4
comma
l_string|&quot;empty segment&quot;
)paren
suffix:semicolon
id|mseg.blocks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* skip entire segment */
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing written */
)brace
r_else
(brace
id|mseg.blocks
op_assign
id|SECTORS_PER_SEGMENT
op_minus
id|bads
suffix:semicolon
id|mseg.data
op_assign
id|destination
suffix:semicolon
id|memcpy
c_func
(paren
id|mseg.data
comma
id|source
comma
(paren
id|mseg.blocks
op_minus
l_int|3
)paren
op_star
id|SECTOR_SIZE
)paren
suffix:semicolon
id|result
op_assign
id|ecc_set_segment_parity
c_func
(paren
op_amp
id|mseg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;ecc_set_segment_parity failed&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
(paren
id|mseg.blocks
op_minus
l_int|3
)paren
op_star
id|SECTOR_SIZE
suffix:semicolon
)brace
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|prevent_flush
r_void
id|prevent_flush
c_func
(paren
r_void
)paren
(brace
id|need_flush
op_assign
l_int|0
suffix:semicolon
id|ftape_state
op_assign
id|idle
suffix:semicolon
)brace
DECL|function|start_writing
r_int
id|start_writing
c_func
(paren
r_int
id|mode
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;start_writing&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|buffer_struct
op_star
id|buff
op_assign
op_amp
id|buffer
(braket
id|head
)braket
suffix:semicolon
r_int
id|segment_id
op_assign
id|buff-&gt;segment_id
suffix:semicolon
r_if
c_cond
(paren
id|ftape_state
op_eq
id|writing
op_logical_and
id|buff-&gt;status
op_eq
id|waiting
)paren
(brace
id|setup_new_segment
c_func
(paren
id|buff
comma
id|segment_id
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|WRITE_SINGLE
)paren
(brace
id|buffer
(braket
id|head
)braket
dot
id|next_segment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop tape instead of pause */
)brace
id|calc_next_cluster
c_func
(paren
id|buff
)paren
suffix:semicolon
multiline_comment|/* prepare */
id|buff-&gt;status
op_assign
id|writing
suffix:semicolon
r_if
c_cond
(paren
id|runner_status
op_eq
id|idle
)paren
(brace
id|TRACEi
c_func
(paren
l_int|5
comma
l_string|&quot;starting runner for segment&quot;
comma
id|segment_id
)paren
suffix:semicolon
id|result
op_assign
id|ftape_start_tape
c_func
(paren
id|segment_id
comma
id|buff-&gt;sector_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|runner_status
op_assign
id|running
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|result
op_assign
id|setup_fdc_and_dma
c_func
(paren
id|buff
comma
id|FDC_WRITE
)paren
suffix:semicolon
multiline_comment|/* go */
)brace
id|ftape_state
op_assign
id|writing
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|loop_until_writes_done
r_int
id|loop_until_writes_done
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;loop_until_writes_done&quot;
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *  Wait until all data is actually written to tape.&n;&t; */
r_while
c_loop
(paren
id|ftape_state
op_eq
id|writing
op_logical_and
id|buffer
(braket
id|head
)braket
dot
id|status
op_ne
id|done
)paren
(brace
id|TRACEx2
c_func
(paren
l_int|7
comma
l_string|&quot;tail: %d, head: %d&quot;
comma
id|tail
comma
id|head
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_BUFFERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|TRACEx3
c_func
(paren
l_int|8
comma
l_string|&quot;buffer[ %d] segment_id: %d, status: %d&quot;
comma
id|i
comma
id|buffer
(braket
id|i
)braket
dot
id|segment_id
comma
id|buffer
(braket
id|i
)braket
dot
id|status
)paren
suffix:semicolon
)brace
id|result
op_assign
id|fdc_interrupt_wait
c_func
(paren
l_int|5
op_star
id|SECOND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;fdc_interrupt_wait failed&quot;
)paren
suffix:semicolon
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer
(braket
id|head
)braket
dot
id|status
op_eq
id|error
)paren
(brace
multiline_comment|/* Allow escape from loop when signaled !&n;&t;&t;&t; */
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
id|_DONT_BLOCK
)paren
(brace
id|TRACE
c_func
(paren
l_int|2
comma
l_string|&quot;interrupted by signal&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
id|result
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* is this the right return value ? */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer
(braket
id|head
)braket
dot
id|hard_error_map
op_ne
l_int|0
)paren
(brace
multiline_comment|/*  Implement hard write error recovery here&n;&t;&t;&t;&t; */
)brace
id|buffer
(braket
id|head
)braket
dot
id|status
op_assign
id|waiting
suffix:semicolon
multiline_comment|/* retry this one */
r_if
c_cond
(paren
id|runner_status
op_eq
id|aborting
)paren
(brace
id|ftape_dumb_stop
c_func
(paren
)paren
suffix:semicolon
id|runner_status
op_assign
id|idle
suffix:semicolon
)brace
r_if
c_cond
(paren
id|runner_status
op_ne
id|idle
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;unexpected state: runner_status != idle&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|start_writing
c_func
(paren
id|WRITE_MULTI
)paren
suffix:semicolon
)brace
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;looping until writes done&quot;
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* normal exit status */
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*      Write given segment from buffer at address onto tape.&n; */
DECL|function|write_segment
r_int
id|write_segment
c_func
(paren
r_int
id|segment_id
comma
id|byte
op_star
id|address
comma
r_int
id|flushing
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;write_segment&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|bytes_written
op_assign
l_int|0
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|5
comma
l_string|&quot;segment_id =&quot;
comma
id|segment_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ftape_state
op_ne
id|writing
)paren
(brace
r_if
c_cond
(paren
id|ftape_state
op_eq
id|reading
)paren
(brace
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;calling ftape_abort_operation&quot;
)paren
suffix:semicolon
id|result
op_assign
id|ftape_abort_operation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;ftape_abort_operation failed&quot;
)paren
suffix:semicolon
)brace
)brace
id|ftape_zap_read_buffers
c_func
(paren
)paren
suffix:semicolon
id|ftape_zap_write_buffers
c_func
(paren
)paren
suffix:semicolon
id|ftape_state
op_assign
id|writing
suffix:semicolon
)brace
multiline_comment|/*    if all buffers full we&squot;ll have to wait...&n;&t; */
id|wait_segment
c_func
(paren
id|writing
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
id|tail
)braket
dot
id|status
op_eq
id|error
)paren
(brace
multiline_comment|/*  setup for a retry&n;&t;&t; */
id|buffer
(braket
id|tail
)braket
dot
id|status
op_assign
id|waiting
suffix:semicolon
id|bytes_written
op_assign
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* force retry */
r_if
c_cond
(paren
id|buffer
(braket
id|tail
)braket
dot
id|hard_error_map
op_ne
l_int|0
)paren
(brace
id|TRACEx1
c_func
(paren
l_int|1
comma
l_string|&quot;warning: %d hard error(s) in written segment&quot;
comma
id|count_ones
c_func
(paren
id|buffer
(braket
id|tail
)braket
dot
id|hard_error_map
)paren
)paren
suffix:semicolon
id|TRACEx1
c_func
(paren
l_int|4
comma
l_string|&quot;hard_error_map = 0x%08lx&quot;
comma
id|buffer
(braket
id|tail
)braket
dot
id|hard_error_map
)paren
suffix:semicolon
multiline_comment|/*  Implement hard write error recovery here&n;&t;&t;&t; */
)brace
)brace
r_else
r_if
c_cond
(paren
id|buffer
(braket
id|tail
)braket
dot
id|status
op_eq
id|done
)paren
(brace
id|history.defects
op_add_assign
id|count_ones
c_func
(paren
id|buffer
(braket
id|tail
)braket
dot
id|hard_error_map
)paren
suffix:semicolon
)brace
r_else
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;wait for empty segment failed&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*    If just passed last segment on tape: wait for BOT or EOT mark.&n;&t; */
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|runner_status
op_eq
id|logical_eot
)paren
(brace
r_int
id|status
suffix:semicolon
id|result
op_assign
id|ftape_ready_wait
c_func
(paren
id|timeout.seek
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
op_logical_or
(paren
id|status
op_amp
(paren
id|QIC_STATUS_AT_BOT
op_or
id|QIC_STATUS_AT_EOT
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;eot/bot not reached&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|runner_status
op_assign
id|end_of_tape
suffix:semicolon
)brace
)brace
multiline_comment|/*    should runner stop ?&n;&t; */
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
(paren
id|runner_status
op_eq
id|aborting
op_logical_or
id|runner_status
op_eq
id|buffer_underrun
op_logical_or
id|runner_status
op_eq
id|end_of_tape
)paren
)paren
(brace
r_if
c_cond
(paren
id|runner_status
op_ne
id|end_of_tape
)paren
(brace
id|result
op_assign
id|ftape_dumb_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|runner_status
op_eq
id|aborting
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
id|head
)braket
dot
id|status
op_eq
id|writing
)paren
(brace
id|buffer
(braket
id|head
)braket
dot
id|status
op_assign
id|done
suffix:semicolon
multiline_comment|/* ????? */
)brace
)brace
id|runner_status
op_assign
id|idle
suffix:semicolon
multiline_comment|/* aborted ? */
)brace
)brace
multiline_comment|/*  Don&squot;t start tape if runner idle and segment empty.&n;&t; */
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
op_logical_neg
(paren
id|runner_status
op_eq
id|idle
op_logical_and
id|get_bad_sector_entry
c_func
(paren
id|segment_id
)paren
op_eq
id|EMPTY_SEGMENT
)paren
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
id|tail
)braket
dot
id|status
op_eq
id|done
)paren
(brace
multiline_comment|/*    now at least one buffer is empty, fill it with our data.&n;&t;&t;&t; *    skip bad sectors and generate ecc.&n;&t;&t;&t; *    copy_and_gen_ecc return nr of bytes written,&n;&t;&t;&t; *    range 0..29 Kb inclusive !&n;&t;&t;&t; */
id|result
op_assign
id|copy_and_gen_ecc
c_func
(paren
id|buffer
(braket
id|tail
)braket
dot
id|address
comma
id|address
comma
id|get_bad_sector_entry
c_func
(paren
id|segment_id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|bytes_written
op_assign
id|result
suffix:semicolon
id|buffer
(braket
id|tail
)braket
dot
id|segment_id
op_assign
id|segment_id
suffix:semicolon
id|buffer
(braket
id|tail
)braket
dot
id|status
op_assign
id|waiting
suffix:semicolon
id|next_buffer
c_func
(paren
op_amp
id|tail
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*    Start tape only if all buffers full or flush mode.&n;&t;&t; *    This will give higher probability of streaming.&n;&t;&t; */
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|runner_status
op_ne
id|running
op_logical_and
(paren
(paren
id|head
op_eq
id|tail
op_logical_and
id|buffer
(braket
id|tail
)braket
dot
id|status
op_eq
id|waiting
)paren
op_logical_or
id|flushing
)paren
)paren
(brace
id|result
op_assign
id|start_writing
c_func
(paren
id|WRITE_MULTI
)paren
suffix:semicolon
)brace
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
(paren
id|result
OL
l_int|0
)paren
ques
c_cond
id|result
suffix:colon
id|bytes_written
suffix:semicolon
)brace
multiline_comment|/*  Write as much as fits from buffer to the given segment on tape&n; *  and handle retries.&n; *  Return the number of bytes written (&gt;= 0), or:&n; *      -EIO          write failed&n; *      -EINTR        interrupted by signal&n; *      -ENOSPC       device full&n; */
DECL|function|_write_segment
r_int
id|_write_segment
c_func
(paren
r_int
r_int
id|segment_id
comma
id|byte
op_star
id|buffer
comma
r_int
id|flush
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;_write_segment&quot;
)paren
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|result
suffix:semicolon
id|history.used
op_or_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|segment_id
OG
id|ftape_last_segment.id
op_logical_and
op_logical_neg
id|flush
)paren
(brace
id|result
op_assign
op_minus
id|ENOSPC
suffix:semicolon
multiline_comment|/* tape full */
r_break
suffix:semicolon
)brace
id|result
op_assign
id|write_segment
c_func
(paren
id|segment_id
comma
id|buffer
comma
id|flush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_if
c_cond
(paren
op_increment
id|retry
OG
l_int|100
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;write failed, &gt;100 retries in segment&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* give up */
r_break
suffix:semicolon
)brace
r_else
(brace
id|TRACEx1
c_func
(paren
l_int|2
comma
l_string|&quot;write error, retry %d&quot;
comma
id|retry
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|TRACEi
c_func
(paren
l_int|1
comma
l_string|&quot;write_segment failed, error:&quot;
comma
op_minus
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* success */
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
multiline_comment|/* empty segment */
id|TRACE
c_func
(paren
l_int|4
comma
l_string|&quot;empty segment, nothing written&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Allow escape from loop when signaled !&n;&t;&t; */
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
id|_DONT_BLOCK
)paren
(brace
id|TRACE
c_func
(paren
l_int|2
comma
l_string|&quot;interrupted by signal&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
id|result
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* is this the right return value ? */
r_break
suffix:semicolon
)brace
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|update_header_segment
r_int
id|update_header_segment
c_func
(paren
r_int
id|segment
comma
id|byte
op_star
id|buffer
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;update_header_segment&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
(brace
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;no input buffer specified&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|deblock_buffer
suffix:semicolon
id|result
op_assign
id|read_segment
c_func
(paren
id|used_header_segment
comma
id|buffer
comma
op_amp
id|status
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_sector_map_changed
)paren
(brace
id|store_bad_sector_map
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|failed_sector_log_changed
)paren
(brace
id|update_failed_sector_log
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|GET4
c_func
(paren
id|buffer
comma
l_int|0
)paren
op_ne
l_int|0xaa55aa55
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;wrong header signature found, aborting&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|result
op_assign
id|_write_segment
c_func
(paren
id|segment
comma
id|buffer
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|runner_status
op_eq
id|idle
)paren
(brace
multiline_comment|/*  Force flush for single segment instead of relying on&n;&t;&t;&t; *  flush in read_segment for multiple segments.&n;&t;&t;&t; */
id|result
op_assign
id|start_writing
c_func
(paren
id|WRITE_SINGLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|ftape_state
op_eq
id|writing
)paren
(brace
id|result
op_assign
id|loop_until_writes_done
c_func
(paren
)paren
suffix:semicolon
id|prevent_flush
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef VERIFY_HEADERS
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
multiline_comment|/* read back and verify */
id|result
op_assign
id|read_segment
c_func
(paren
id|segment
comma
id|scratch_buffer
comma
op_amp
id|status
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*  Should retry if soft error during read !&n;&t;&t;&t; *  TO BE IMPLEMENTED&n;&t;&t;&t; */
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
id|scratch_buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* verified */
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;verified&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* verify failed */
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;verify failed&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ftape_write_header_segments
r_int
id|ftape_write_header_segments
c_func
(paren
id|byte
op_star
id|buffer
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;ftape_write_header_segments&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|header_1_ok
op_assign
l_int|0
suffix:semicolon
r_int
id|header_2_ok
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|header_1_ok
)paren
(brace
id|result
op_assign
id|update_header_segment
c_func
(paren
id|header_segment_1
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
id|header_1_ok
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|header_2_ok
)paren
(brace
id|result
op_assign
id|update_header_segment
c_func
(paren
id|header_segment_2
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
id|header_2_ok
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|result
OL
l_int|0
op_logical_and
id|retry
op_increment
OL
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|header_1_ok
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;update of first header segment failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|header_2_ok
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;update of second header segment failed&quot;
)paren
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ftape_update_header_segments
r_int
id|ftape_update_header_segments
c_func
(paren
id|byte
op_star
id|buffer
comma
r_int
id|update
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;ftape_update_header_segments&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|dummy
suffix:semicolon
r_int
id|header_changed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ftape_state
op_eq
id|writing
)paren
(brace
id|result
op_assign
id|loop_until_writes_done
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_only
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* exit and fake success */
id|TRACE
c_func
(paren
l_int|4
comma
l_string|&quot;Tape set read-only: no update&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|result
op_assign
id|ftape_abort_operation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|bad_sector_map_changed
op_logical_or
id|failed_sector_log_changed
)paren
(brace
id|ftape_seek_to_bot
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevents extra rewind */
id|buffer
op_assign
id|deblock_buffer
suffix:semicolon
id|result
op_assign
id|read_segment
c_func
(paren
id|used_header_segment
comma
id|buffer
comma
op_amp
id|dummy
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
)brace
id|header_changed
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|update
)paren
(brace
r_if
c_cond
(paren
id|bad_sector_map_changed
)paren
(brace
id|store_bad_sector_map
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|header_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|failed_sector_log_changed
)paren
(brace
id|update_failed_sector_log
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|header_changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|header_changed
)paren
(brace
id|ftape_seek_to_bot
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevents extra rewind */
id|result
op_assign
id|ftape_write_header_segments
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
)brace
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ftape_flush_buffers
r_int
id|ftape_flush_buffers
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;ftape_flush_buffers&quot;
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|pad_count
suffix:semicolon
r_int
id|data_remaining
suffix:semicolon
r_static
r_int
id|active
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|active
)paren
(brace
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;nested call, abort&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|active
op_assign
l_int|1
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|5
comma
l_string|&quot;entered, ftape_state =&quot;
comma
id|ftape_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ftape_state
op_ne
id|writing
op_logical_and
op_logical_neg
id|need_flush
)paren
(brace
id|active
op_assign
l_int|0
suffix:semicolon
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;no need for flush&quot;
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|data_remaining
op_assign
id|buf_pos_wr
suffix:semicolon
id|buf_pos_wr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* prevent further writes if this fails */
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;flushing write buffers&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_write_failed
)paren
(brace
id|ftape_zap_write_buffers
c_func
(paren
)paren
suffix:semicolon
id|active
op_assign
l_int|0
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|write_protected
ques
c_cond
op_minus
id|EROFS
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *    If there is any data not written to tape yet, append zero&squot;s&n;&t; *    up to the end of the sector. Then write the segment(s) to tape.&n;&t; */
r_if
c_cond
(paren
id|data_remaining
OG
l_int|0
)paren
(brace
r_int
id|written
suffix:semicolon
r_do
(brace
id|TRACEi
c_func
(paren
l_int|4
comma
l_string|&quot;remaining in buffer:&quot;
comma
id|data_remaining
)paren
suffix:semicolon
id|pad_count
op_assign
r_sizeof
(paren
id|deblock_buffer
)paren
op_minus
id|data_remaining
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;flush, padding count:&quot;
comma
id|pad_count
)paren
suffix:semicolon
id|memset
c_func
(paren
id|deblock_buffer
op_plus
id|data_remaining
comma
l_int|0
comma
id|pad_count
)paren
suffix:semicolon
multiline_comment|/* pad buffer */
id|result
op_assign
id|_write_segment
c_func
(paren
id|ftape_seg_pos
comma
id|deblock_buffer
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_ne
op_minus
id|ENOSPC
)paren
(brace
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
)brace
id|active
op_assign
l_int|0
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|written
op_assign
id|result
suffix:semicolon
id|clear_eof_mark_if_set
c_func
(paren
id|ftape_seg_pos
comma
id|written
)paren
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;flush, moved out buffer:&quot;
comma
id|written
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
OG
l_int|0
)paren
(brace
id|data_remaining
op_sub_assign
id|written
suffix:semicolon
r_if
c_cond
(paren
id|data_remaining
OG
l_int|0
)paren
(brace
multiline_comment|/*  Need another segment for remaining data, move the remainder&n;&t;&t;&t;&t;&t; *  to the beginning of the buffer&n;&t;&t;&t;&t;&t; */
id|memmove
c_func
(paren
id|deblock_buffer
comma
id|deblock_buffer
op_plus
id|written
comma
id|data_remaining
)paren
suffix:semicolon
)brace
)brace
op_increment
id|ftape_seg_pos
suffix:semicolon
)brace
r_while
c_loop
(paren
id|data_remaining
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/*  Data written to last segment == data_remaining + written&n;&t;&t; *  value is in range [1..29K].&n;&t;&t; */
id|TRACEx2
c_func
(paren
l_int|4
comma
l_string|&quot;last write: %d, netto pad-count: %d&quot;
comma
id|data_remaining
op_plus
id|written
comma
op_minus
id|data_remaining
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1024
OL
id|data_remaining
op_logical_and
id|data_remaining
op_le
l_int|0
)paren
(brace
multiline_comment|/*  Last sector of segment was used for data, so put eof mark&n;&t;&t;&t; *  in next segment and position at second file mark.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ftape_weof
c_func
(paren
l_int|2
comma
id|ftape_seg_pos
comma
l_int|1
)paren
op_ge
l_int|0
)paren
(brace
op_increment
id|ftape_seg_pos
suffix:semicolon
multiline_comment|/* position between file marks */
)brace
)brace
r_else
(brace
multiline_comment|/*  Put eof mark in previous segment after data and position&n;&t;&t;&t; *  at second file mark.&n;&t;&t;&t; */
id|ftape_weof
c_func
(paren
l_int|2
comma
id|ftape_seg_pos
op_minus
l_int|1
comma
l_int|1
op_plus
(paren
(paren
id|SECTOR_SIZE
op_minus
l_int|1
op_plus
id|result
op_plus
id|data_remaining
)paren
op_div
id|SECTOR_SIZE
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|TRACE
c_func
(paren
l_int|7
comma
l_string|&quot;deblock_buffer empty&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ftape_weof
c_func
(paren
l_int|2
comma
id|ftape_seg_pos
comma
l_int|1
)paren
op_ge
l_int|0
)paren
(brace
op_increment
id|ftape_seg_pos
suffix:semicolon
multiline_comment|/* position between file marks */
)brace
id|start_writing
c_func
(paren
id|WRITE_MULTI
)paren
suffix:semicolon
)brace
id|TRACE
c_func
(paren
l_int|7
comma
l_string|&quot;waiting&quot;
)paren
suffix:semicolon
id|result
op_assign
id|loop_until_writes_done
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;flush buffers failed&quot;
)paren
suffix:semicolon
)brace
id|ftape_state
op_assign
id|idle
suffix:semicolon
id|last_write_failed
op_assign
l_int|0
suffix:semicolon
id|need_flush
op_assign
l_int|0
suffix:semicolon
id|active
op_assign
l_int|0
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|_ftape_write
r_int
id|_ftape_write
c_func
(paren
r_const
r_char
op_star
id|buff
comma
r_int
id|req_len
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;_ftape_write&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|write_protected
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;error: cartridge write protected&quot;
)paren
suffix:semicolon
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
op_minus
id|EROFS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ftape_offline
op_logical_or
op_logical_neg
id|formatted
op_logical_or
id|no_tape
)paren
(brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|first_data_segment
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; *    If we haven&squot;t read the header segment yet, do it now.&n;&t;&t; *    This will verify the configuration, get the eof markers&n;&t;&t; *    and the bad sector table.&n;&t;&t; *    We&squot;ll use the deblock buffer for scratch.&n;&t;&t; */
id|result
op_assign
id|read_header_segment
c_func
(paren
id|deblock_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
op_logical_and
id|ftape_seg_pos
OG
id|ftape_last_segment.id
)paren
(brace
id|result
op_assign
op_minus
id|ENOSPC
suffix:semicolon
multiline_comment|/* full is full */
)brace
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *    This part writes data blocks to tape until the&n;&t; *    requested amount is written.&n;&t; *    The data will go in a buffer until it&squot;s enough&n;&t; *    for a segment without bad sectors. Then we&squot;ll write&n;&t; *    that segment to tape.&n;&t; *    The bytes written will be removed from the buffer&n;&t; *    and the process is repeated until there is less&n;&t; *    than one segment to write left in the buffer.&n;&t; */
r_while
c_loop
(paren
id|req_len
OG
l_int|0
)paren
(brace
r_int
id|space_left
op_assign
r_sizeof
(paren
id|deblock_buffer
)paren
op_minus
id|buf_pos_wr
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;remaining req_len:&quot;
comma
id|req_len
)paren
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;          buf_pos:&quot;
comma
id|buf_pos_wr
)paren
suffix:semicolon
id|cnt
op_assign
(paren
id|req_len
OL
id|space_left
)paren
ques
c_cond
id|req_len
suffix:colon
id|space_left
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OG
l_int|0
)paren
(brace
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buff
comma
id|cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|TRACE
c_func
(paren
l_int|1
comma
l_string|&quot;verify_area failed&quot;
)paren
suffix:semicolon
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
id|deblock_buffer
op_plus
id|buf_pos_wr
comma
id|buff
comma
id|cnt
)paren
suffix:semicolon
id|buff
op_add_assign
id|cnt
suffix:semicolon
id|req_len
op_sub_assign
id|cnt
suffix:semicolon
id|buf_pos_wr
op_add_assign
id|cnt
suffix:semicolon
)brace
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;moved into blocking buffer:&quot;
comma
id|cnt
)paren
suffix:semicolon
r_while
c_loop
(paren
id|buf_pos_wr
op_ge
r_sizeof
(paren
id|deblock_buffer
)paren
)paren
(brace
multiline_comment|/*  If this is the last buffer to be written, let flush handle it.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ftape_seg_pos
op_ge
id|ftape_last_segment.id
)paren
(brace
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;remaining in blocking buffer:&quot;
comma
id|buf_pos_wr
)paren
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;just written bytes:&quot;
comma
id|written
op_plus
id|cnt
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|written
op_plus
id|cnt
suffix:semicolon
)brace
multiline_comment|/* Got one full buffer, write it to disk&n;&t;&t;&t; */
id|result
op_assign
id|_write_segment
c_func
(paren
id|ftape_seg_pos
comma
id|deblock_buffer
comma
l_int|0
)paren
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|5
comma
l_string|&quot;_write_segment result =&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|TRACE
c_func
(paren
l_int|5
comma
l_string|&quot;retry...&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* failed, retry same segment */
)brace
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_else
(brace
id|clear_eof_mark_if_set
c_func
(paren
id|ftape_seg_pos
comma
id|result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OG
l_int|0
op_logical_and
id|result
OL
id|buf_pos_wr
)paren
(brace
multiline_comment|/* Partial write: move remainder in lower part of buffer&n;&t;&t;&t;&t; */
id|memmove
c_func
(paren
id|deblock_buffer
comma
id|deblock_buffer
op_plus
id|result
comma
id|buf_pos_wr
op_minus
id|result
)paren
suffix:semicolon
)brace
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;moved out of blocking buffer:&quot;
comma
id|result
)paren
suffix:semicolon
id|buf_pos_wr
op_sub_assign
id|result
suffix:semicolon
multiline_comment|/* remainder */
op_increment
id|ftape_seg_pos
suffix:semicolon
multiline_comment|/* Allow us to escape from this loop with a signal !&n;&t;&t;&t; */
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
id|_DONT_BLOCK
)paren
(brace
id|TRACE
c_func
(paren
l_int|2
comma
l_string|&quot;interrupted by signal&quot;
)paren
suffix:semicolon
id|last_write_failed
op_assign
l_int|1
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* is this the right return value ? */
)brace
)brace
id|written
op_add_assign
id|cnt
suffix:semicolon
)brace
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;remaining in blocking buffer:&quot;
comma
id|buf_pos_wr
)paren
suffix:semicolon
id|TRACEi
c_func
(paren
l_int|7
comma
l_string|&quot;just written bytes:&quot;
comma
id|written
)paren
suffix:semicolon
id|last_write_failed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_flush
op_logical_and
id|written
OG
l_int|0
)paren
(brace
id|need_flush
op_assign
l_int|1
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|written
suffix:semicolon
multiline_comment|/* bytes written */
)brace
DECL|function|ftape_fix
r_int
id|ftape_fix
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;ftape_fix&quot;
)paren
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|dummy
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|write_protected
)paren
(brace
id|result
op_assign
op_minus
id|EROFS
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*  This will copy header segment 2 to header segment 1&n;&t;&t; *  Spares us a tape format operation if header 2 is still good.&n;&t;&t; */
id|header_segment_1
op_assign
l_int|0
suffix:semicolon
id|header_segment_2
op_assign
l_int|1
suffix:semicolon
id|first_data_segment
op_assign
l_int|2
suffix:semicolon
id|result
op_assign
id|read_segment
c_func
(paren
id|header_segment_2
comma
id|scratch_buffer
comma
op_amp
id|dummy
comma
l_int|0
)paren
suffix:semicolon
id|result
op_assign
id|ftape_ready_wait
c_func
(paren
id|timeout.pause
comma
op_amp
id|status
)paren
suffix:semicolon
id|result
op_assign
id|ftape_write_header_segments
c_func
(paren
id|scratch_buffer
)paren
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
