multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the RAW-IP module.&n; *&n; * Version:&t;@(#)raw.h&t;1.0.2&t;05/07/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _RAW_H
DECL|macro|_RAW_H
mdefine_line|#define _RAW_H
r_extern
r_struct
id|proto
id|raw_prot
suffix:semicolon
r_extern
r_int
id|raw_err
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|raw_rcv
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* _RAW_H */
eof
