multiline_comment|/* $Id: arcofi.h,v 1.3 1998/05/25 12:57:39 keil Exp $&n;&n; * arcofi.h   Ansteuerung ARCOFI 2165&n; *&n; * Author     Karsten Keil (keil@temic-ech.spacenet.de)&n; *&n; *&n; *&n; * $Log: arcofi.h,v $&n; * Revision 1.3  1998/05/25 12:57:39  keil&n; * HiSax golden code from certification, Don&squot;t use !!!&n; * No leased lines, no X75, but many changes.&n; *&n; * Revision 1.2  1998/04/15 16:47:17  keil&n; * new interface&n; *&n; * Revision 1.1  1997/10/29 18:51:20  keil&n; * New files&n; *&n; */
DECL|macro|ARCOFI_USE
mdefine_line|#define ARCOFI_USE&t;1
r_extern
r_int
id|send_arcofi
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_const
id|u_char
op_star
id|msg
comma
r_int
id|bc
comma
r_int
id|receive
)paren
suffix:semicolon
eof
