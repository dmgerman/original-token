multiline_comment|/* $Id: arcofi.h,v 1.5 1999/12/23 15:09:32 keil Exp $&n;&n; * arcofi.h   Ansteuerung ARCOFI 2165&n; *&n; * Author     Karsten Keil (keil@isdn4linux.de)&n; *&n; *&n; *&n; * $Log: arcofi.h,v $&n; * Revision 1.5  1999/12/23 15:09:32  keil&n; * change email&n; *&n; * Revision 1.4  1999/07/01 08:11:18  keil&n; * Common HiSax version for 2.0, 2.1, 2.2 and 2.3 kernel&n; *&n; * Revision 1.3  1998/05/25 12:57:39  keil&n; * HiSax golden code from certification, Don&squot;t use !!!&n; * No leased lines, no X75, but many changes.&n; *&n; * Revision 1.2  1998/04/15 16:47:17  keil&n; * new interface&n; *&n; * Revision 1.1  1997/10/29 18:51:20  keil&n; * New files&n; *&n; */
DECL|macro|ARCOFI_USE
mdefine_line|#define ARCOFI_USE&t;1
multiline_comment|/* states */
DECL|macro|ARCOFI_NOP
mdefine_line|#define ARCOFI_NOP&t;0
DECL|macro|ARCOFI_TRANSMIT
mdefine_line|#define ARCOFI_TRANSMIT&t;1
DECL|macro|ARCOFI_RECEIVE
mdefine_line|#define ARCOFI_RECEIVE&t;2
multiline_comment|/* events */
DECL|macro|ARCOFI_START
mdefine_line|#define ARCOFI_START&t;1
DECL|macro|ARCOFI_TX_END
mdefine_line|#define ARCOFI_TX_END&t;2
DECL|macro|ARCOFI_RX_END
mdefine_line|#define ARCOFI_RX_END&t;3
DECL|macro|ARCOFI_TIMEOUT
mdefine_line|#define ARCOFI_TIMEOUT&t;4
r_extern
r_int
id|arcofi_fsm
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|event
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|init_arcofi
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|clear_arcofi
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
