multiline_comment|/*&n; * $Id: b1lli.h,v 1.1 1997/03/04 21:27:32 calle Exp $&n; *&n; * ISDN lowlevel-module for AVM B1-card.&n; *&n; * Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * $Log: b1lli.h,v $&n; * Revision 1.1  1997/03/04 21:27:32  calle&n; * First version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; */
macro_line|#ifndef _B1LLI_H_
DECL|macro|_B1LLI_H_
mdefine_line|#define _B1LLI_H_
multiline_comment|/*&n; * struct for loading t4 file &n; */
DECL|struct|avmb1_t4file
r_typedef
r_struct
id|avmb1_t4file
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|typedef|avmb1_t4file
)brace
id|avmb1_t4file
suffix:semicolon
DECL|struct|avmb1_loaddef
r_typedef
r_struct
id|avmb1_loaddef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|member|t4file
id|avmb1_t4file
id|t4file
suffix:semicolon
DECL|typedef|avmb1_loaddef
)brace
id|avmb1_loaddef
suffix:semicolon
DECL|struct|avmb1_resetdef
r_typedef
r_struct
id|avmb1_resetdef
(brace
DECL|member|contr
r_int
id|contr
suffix:semicolon
DECL|typedef|avmb1_resetdef
)brace
id|avmb1_resetdef
suffix:semicolon
multiline_comment|/*&n; * struct for adding new cards &n; */
DECL|struct|avmb1_carddef
r_typedef
r_struct
id|avmb1_carddef
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|typedef|avmb1_carddef
)brace
id|avmb1_carddef
suffix:semicolon
DECL|macro|AVMB1_LOAD
mdefine_line|#define&t;AVMB1_LOAD&t;0&t;/* load image to card */
DECL|macro|AVMB1_ADDCARD
mdefine_line|#define AVMB1_ADDCARD&t;1&t;/* add a new card */
DECL|macro|AVMB1_RESETCARD
mdefine_line|#define AVMB1_RESETCARD&t;2&t;/* reset a card */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * card states for startup&n; */
DECL|macro|CARD_NONE
mdefine_line|#define CARD_NONE&t;0
DECL|macro|CARD_DETECTED
mdefine_line|#define CARD_DETECTED&t;1
DECL|macro|CARD_LOADING
mdefine_line|#define CARD_LOADING&t;2
DECL|macro|CARD_INITSTATE
mdefine_line|#define CARD_INITSTATE&t;4
DECL|macro|CARD_RUNNING
mdefine_line|#define CARD_RUNNING&t;5
DECL|macro|CARD_ACTIVE
mdefine_line|#define CARD_ACTIVE&t;6
DECL|macro|AVMB1_PORTLEN
mdefine_line|#define&t;AVMB1_PORTLEN&t;0x1f
DECL|macro|AVM_MAXVERSION
mdefine_line|#define AVM_MAXVERSION&t;8
DECL|macro|AVM_NBCHAN
mdefine_line|#define AVM_NBCHAN&t;2
DECL|macro|AVM_NAPPS
mdefine_line|#define AVM_NAPPS&t;30
DECL|macro|AVM_NPLCI
mdefine_line|#define AVM_NPLCI&t;5
DECL|macro|AVM_NNCCI
mdefine_line|#define AVM_NNCCI&t;6
multiline_comment|/*&n; * Main driver data&n; */
DECL|struct|avmb1_card
r_typedef
r_struct
id|avmb1_card
(brace
DECL|member|next
r_struct
id|avmb1_card
op_star
id|next
suffix:semicolon
DECL|member|cnr
r_int
id|cnr
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|cardstate
r_volatile
r_int
r_int
id|cardstate
suffix:semicolon
DECL|member|interrupt
r_int
id|interrupt
suffix:semicolon
DECL|member|blocked
r_int
id|blocked
suffix:semicolon
DECL|member|versionlen
r_int
id|versionlen
suffix:semicolon
DECL|member|versionbuf
r_char
id|versionbuf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|member|version
r_char
op_star
id|version
(braket
id|AVM_MAXVERSION
)braket
suffix:semicolon
DECL|member|msgbuf
r_char
id|msgbuf
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* capimsg msg part */
DECL|member|databuf
r_char
id|databuf
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/* capimsg data part */
DECL|member|cversion
id|capi_version
id|cversion
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|avmb1_card
)brace
id|avmb1_card
suffix:semicolon
multiline_comment|/*&n; * Versions&n; */
DECL|macro|VER_DRIVER
mdefine_line|#define&t;VER_DRIVER&t;0
DECL|macro|VER_CARDTYPE
mdefine_line|#define&t;VER_CARDTYPE&t;1
DECL|macro|VER_HWID
mdefine_line|#define&t;VER_HWID&t;2
DECL|macro|VER_SERIAL
mdefine_line|#define&t;VER_SERIAL&t;3
DECL|macro|VER_OPTION
mdefine_line|#define&t;VER_OPTION&t;4
DECL|macro|VER_PROTO
mdefine_line|#define&t;VER_PROTO&t;5
DECL|macro|VER_PROFILE
mdefine_line|#define&t;VER_PROFILE&t;6
DECL|macro|VER_CAPI
mdefine_line|#define&t;VER_CAPI&t;7
multiline_comment|/* b1lli.c */
r_int
id|B1_detect
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_void
id|B1_reset
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_int
id|B1_load_t4file
c_func
(paren
r_int
r_int
id|base
comma
id|avmb1_t4file
op_star
id|t4file
)paren
suffix:semicolon
r_int
id|B1_loaded
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_int
r_char
id|B1_assign_irq
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
r_char
id|B1_enable_irq
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_int
r_char
id|B1_disable_irq
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_int
id|B1_valid_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|B1_handle_interrupt
c_func
(paren
id|avmb1_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|B1_send_init
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|napps
comma
r_int
r_int
id|nncci
comma
r_int
r_int
id|cardnr
)paren
suffix:semicolon
r_void
id|B1_send_register
c_func
(paren
r_int
r_int
id|port
comma
id|__u16
id|appid
comma
id|__u32
id|nmsg
comma
id|__u32
id|nb3conn
comma
id|__u32
id|nb3blocks
comma
id|__u32
id|b3bsize
)paren
suffix:semicolon
r_void
id|B1_send_release
c_func
(paren
r_int
r_int
id|port
comma
id|__u16
id|appid
)paren
suffix:semicolon
r_void
id|B1_send_message
c_func
(paren
r_int
r_int
id|port
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* b1capi.c */
r_void
id|avmb1_handle_new_ncci
c_func
(paren
id|avmb1_card
op_star
id|card
comma
id|__u16
id|appl
comma
id|__u32
id|ncci
comma
id|__u32
id|winsize
)paren
suffix:semicolon
r_void
id|avmb1_handle_free_ncci
c_func
(paren
id|avmb1_card
op_star
id|card
comma
id|__u16
id|appl
comma
id|__u32
id|ncci
)paren
suffix:semicolon
r_void
id|avmb1_handle_capimsg
c_func
(paren
id|avmb1_card
op_star
id|card
comma
id|__u16
id|appl
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|avmb1_card_ready
c_func
(paren
id|avmb1_card
op_star
id|card
)paren
suffix:semicolon
r_int
id|avmb1_addcard
c_func
(paren
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|avmb1_probecard
c_func
(paren
r_int
id|port
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _B1LLI_H_ */
eof