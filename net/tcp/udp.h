multiline_comment|/* udp.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: udp.h,v 0.8.4.1 1992/11/10 00:17:18 bir7 Exp $ */
multiline_comment|/* $Log: udp.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and $Log: udp.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *.&n; * */
macro_line|#ifndef _TCP_UDP_H
DECL|macro|_TCP_UDP_H
mdefine_line|#define _TCP_UDP_H
DECL|struct|udp_header
r_struct
id|udp_header
(brace
DECL|member|source
r_int
r_int
id|source
suffix:semicolon
DECL|member|dest
r_int
r_int
id|dest
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|check
r_int
r_int
id|check
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|proto
id|udp_prot
suffix:semicolon
DECL|macro|UDP_NO_CHECK
mdefine_line|#define UDP_NO_CHECK 1
macro_line|#endif
eof
