multiline_comment|/* $Id: isdnl1.h,v 2.8 1998/11/15 23:54:59 keil Exp $&n;&n; * $Log: isdnl1.h,v $&n; * Revision 2.8  1998/11/15 23:54:59  keil&n; * changes from 2.0&n; *&n; * Revision 2.7  1998/09/30 22:21:55  keil&n; * cosmetics&n; *&n; * Revision 2.6  1998/05/25 12:58:06  keil&n; * HiSax golden code from certification, Don&squot;t use !!!&n; * No leased lines, no X75, but many changes.&n; *&n; * Revision 2.5  1998/02/02 13:36:58  keil&n; * more debug&n; *&n; * Revision 2.4  1997/11/08 21:35:49  keil&n; * new l1 init&n; *&n; * Revision 2.3  1997/10/29 19:07:53  keil&n; * changes for 2.1&n; *&n; * Revision 2.2  1997/07/30 17:11:09  keil&n; * L1deactivated exported&n; *&n; * Revision 2.1  1997/07/27 21:43:58  keil&n; * new l1 interface&n; *&n; * Revision 2.0  1997/06/26 11:02:55  keil&n; * New Layer and card interface&n; *&n; *&n; */
DECL|macro|D_RCVBUFREADY
mdefine_line|#define D_RCVBUFREADY&t;0
DECL|macro|D_XMTBUFREADY
mdefine_line|#define D_XMTBUFREADY&t;1
DECL|macro|D_L1STATECHANGE
mdefine_line|#define D_L1STATECHANGE&t;2
DECL|macro|D_CLEARBUSY
mdefine_line|#define D_CLEARBUSY&t;3
DECL|macro|D_RX_MON0
mdefine_line|#define D_RX_MON0&t;4
DECL|macro|D_RX_MON1
mdefine_line|#define D_RX_MON1&t;5
DECL|macro|D_TX_MON0
mdefine_line|#define D_TX_MON0&t;6
DECL|macro|D_TX_MON1
mdefine_line|#define D_TX_MON1&t;7
DECL|macro|B_RCVBUFREADY
mdefine_line|#define B_RCVBUFREADY 0
DECL|macro|B_XMTBUFREADY
mdefine_line|#define B_XMTBUFREADY 1
r_extern
r_void
id|debugl1
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|DChannel_proc_xmt
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
id|DChannel_proc_rcv
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
id|l1_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|l1_msg_b
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
macro_line|#ifdef L2FRAME_DEBUG
r_extern
r_void
id|Logl2Frame
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|buf
comma
r_int
id|dir
)paren
suffix:semicolon
macro_line|#endif
eof
