multiline_comment|/* $Id: proto.h,v 1.1 1996/09/23 01:53:52 fritz Exp $&n; *&n; * not much now - just the l3 proto discriminator&n; *&n; * $Log: proto.h,v $&n; * Revision 1.1  1996/09/23 01:53:52  fritz&n; * Bugfix: discard unknown frames (non-EDSS1 and non-1TR6).&n; *&n; */
macro_line|#ifndef&t;PROTO_H
DECL|macro|PROTO_H
mdefine_line|#define&t;PROTO_H
DECL|macro|PROTO_EURO
mdefine_line|#define&t;PROTO_EURO&t;&t;0x08
DECL|macro|PROTO_DIS_N0
mdefine_line|#define&t;PROTO_DIS_N0&t;0x40
DECL|macro|PROTO_DIS_N1
mdefine_line|#define&t;PROTO_DIS_N1&t;0x41
macro_line|#endif
eof
