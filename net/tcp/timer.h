multiline_comment|/* timer.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 1, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
macro_line|#ifndef _TCP_TIMER_H
DECL|macro|_TCP_TIMER_H
mdefine_line|#define _TCP_TIMER_H
DECL|struct|timer
r_struct
id|timer
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|sk
r_volatile
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|when
r_int
r_int
id|when
suffix:semicolon
DECL|member|next
r_struct
id|timer
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_void
id|delete_timer
(paren
r_struct
id|timer
op_star
)paren
suffix:semicolon
r_void
id|reset_timer
(paren
r_struct
id|timer
op_star
)paren
suffix:semicolon
r_void
id|net_timer
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SEQ_TICK
mdefine_line|#define SEQ_TICK 3
DECL|macro|timer_seq
mdefine_line|#define timer_seq jiffies
r_extern
r_int
r_int
id|seq_offset
suffix:semicolon
macro_line|#endif
eof
