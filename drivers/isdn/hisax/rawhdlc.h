multiline_comment|/* $Id: rawhdlc.h,v 1.3 2000/06/26 08:59:14 keil Exp $&n; *&n; * rawhdlc.h     support routines for cards that don&squot;t support HDLC&n; *&n; * Author     Brent Baccala &lt;baccala@FreeSoft.org&gt;&n; *&n; * This file is (c) under GNU PUBLIC LICENSE&n; *&n; */
macro_line|#ifndef RAWHDLC_H
DECL|struct|hdlc_state
r_struct
id|hdlc_state
(brace
DECL|member|insane_mode
r_char
id|insane_mode
suffix:semicolon
DECL|member|state
id|u_char
id|state
suffix:semicolon
DECL|member|r_one
id|u_char
id|r_one
suffix:semicolon
DECL|member|r_val
id|u_char
id|r_val
suffix:semicolon
DECL|member|o_bitcnt
id|u_int
id|o_bitcnt
suffix:semicolon
DECL|member|i_bitcnt
id|u_int
id|i_bitcnt
suffix:semicolon
DECL|member|fcs
id|u_int
id|fcs
suffix:semicolon
)brace
suffix:semicolon
r_int
id|make_raw_hdlc_data
c_func
(paren
id|u_char
op_star
id|src
comma
id|u_int
id|slen
comma
id|u_char
op_star
id|dst
comma
id|u_int
id|dsize
)paren
suffix:semicolon
r_void
id|init_hdlc_state
c_func
(paren
r_struct
id|hdlc_state
op_star
id|stateptr
comma
r_int
id|mode
)paren
suffix:semicolon
r_int
id|read_raw_hdlc_data
c_func
(paren
r_struct
id|hdlc_state
op_star
id|saved_state
comma
id|u_char
op_star
id|src
comma
id|u_int
id|slen
comma
id|u_char
op_star
id|dst
comma
id|u_int
id|dsize
)paren
suffix:semicolon
DECL|macro|RAWHDLC_H
mdefine_line|#define RAWHDLC_H
macro_line|#endif
eof
