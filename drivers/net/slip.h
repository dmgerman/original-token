multiline_comment|/*&n; * slip.h&t;Define the SLIP device driver interface and constants.&n; *&n; * NOTE:&t;THIS FILE WILL BE MOVED TO THE LINUX INCLUDE DIRECTORY&n; *&t;&t;AS SOON AS POSSIBLE!&n; *&n; * Version:&t;@(#)slip.h&t;1.2.0&t;03/28/93&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;: &t;Added slip mtu field.&n; *&t;&t;Matt Dillon&t;:&t;Printable slip (borrowed from net2e)&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_SLIP_H
DECL|macro|_LINUX_SLIP_H
mdefine_line|#define _LINUX_SLIP_H
multiline_comment|/* SLIP configuration. */
DECL|macro|SL_NRUNIT
mdefine_line|#define SL_NRUNIT&t;4&t;&t;/* number of SLIP channels&t;*/
DECL|macro|SL_MTU
mdefine_line|#define SL_MTU&t;&t;296&t;&t;/* 296; I am used to 600- FvK&t;*/
multiline_comment|/* SLIP protocol characters. */
DECL|macro|END
mdefine_line|#define END             0300&t;&t;/* indicates end of frame&t;*/
DECL|macro|ESC
mdefine_line|#define ESC             0333&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|ESC_END
mdefine_line|#define ESC_END         0334&t;&t;/* ESC ESC_END means END &squot;data&squot;&t;*/
DECL|macro|ESC_ESC
mdefine_line|#define ESC_ESC         0335&t;&t;/* ESC ESC_ESC means ESC &squot;data&squot;&t;*/
DECL|struct|slip
r_struct
id|slip
(brace
multiline_comment|/* Bitmapped flag fields. */
DECL|member|inuse
r_char
id|inuse
suffix:semicolon
multiline_comment|/* are we allocated?&t;&t;*/
DECL|member|sending
r_char
id|sending
suffix:semicolon
multiline_comment|/* &quot;channel busy&quot; indicator&t;*/
DECL|member|escape
r_char
id|escape
suffix:semicolon
multiline_comment|/* SLIP state machine&t;&t;*/
DECL|member|unused
r_char
id|unused
suffix:semicolon
multiline_comment|/* fillers&t;&t;&t;*/
multiline_comment|/* Various fields. */
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* SLIP channel number&t;&t;*/
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;&t;*/
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
multiline_comment|/* for header compression &t;*/
multiline_comment|/* These are pointers to the malloc()ed frame buffers. */
DECL|member|rbuff
r_int
r_char
op_star
id|rbuff
suffix:semicolon
multiline_comment|/* receiver buffer&t;&t;*/
DECL|member|xbuff
r_int
r_char
op_star
id|xbuff
suffix:semicolon
multiline_comment|/* transmitter buffer&t;&t;*/
DECL|member|cbuff
r_int
r_char
op_star
id|cbuff
suffix:semicolon
multiline_comment|/* compression buffer&t;&t;*/
multiline_comment|/* These are the various pointers into the buffers. */
DECL|member|rhead
r_int
r_char
op_star
id|rhead
suffix:semicolon
multiline_comment|/* RECV buffer pointer (head)&t;*/
DECL|member|rend
r_int
r_char
op_star
id|rend
suffix:semicolon
multiline_comment|/* RECV buffer pointer (end)&t;*/
DECL|member|rcount
r_int
id|rcount
suffix:semicolon
multiline_comment|/* SLIP receive counter&t;&t;*/
multiline_comment|/* SLIP interface statistics. */
DECL|member|rpacket
r_int
r_int
id|rpacket
suffix:semicolon
multiline_comment|/* inbound frame counter&t;*/
DECL|member|roverrun
r_int
r_int
id|roverrun
suffix:semicolon
multiline_comment|/* &quot;buffer overrun&quot; counter&t;*/
DECL|member|spacket
r_int
r_int
id|spacket
suffix:semicolon
multiline_comment|/* outbound frames counter&t;*/
DECL|member|sbusy
r_int
r_int
id|sbusy
suffix:semicolon
multiline_comment|/* &quot;transmitter busy&quot; counter&t;*/
DECL|member|errors
r_int
r_int
id|errors
suffix:semicolon
multiline_comment|/* error count&t;&t;&t;*/
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* Our mtu (to spot changes!)   */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* Flag values/ mode etc&t;*/
DECL|macro|SLF_ESCAPE
mdefine_line|#define SLF_ESCAPE&t;2
DECL|macro|SLF_ERROR
mdefine_line|#define SLF_ERROR&t;4
DECL|macro|SLF_COMP
mdefine_line|#define SLF_COMP&t;16
DECL|macro|SLF_EXPN
mdefine_line|#define SLF_EXPN&t;32
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* SLIP mode&t;&t;&t;*/
DECL|macro|SL_MODE_SLIP
mdefine_line|#define SL_MODE_SLIP&t;0
DECL|macro|SL_MODE_CSLIP
mdefine_line|#define SL_MODE_CSLIP&t;1
DECL|macro|SL_MODE_SLIP6
mdefine_line|#define SL_MODE_SLIP6&t;2&t;&t;/* Matt Dillon&squot;s printable slip */
DECL|macro|SL_MODE_CSLIP6
mdefine_line|#define SL_MODE_CSLIP6&t;(SL_MODE_SLIP|SL_MODE_CSLIP)
DECL|macro|SL_MODE_AX25
mdefine_line|#define SL_MODE_AX25&t;4
DECL|member|xdata
DECL|member|xbits
r_int
id|xdata
comma
id|xbits
suffix:semicolon
multiline_comment|/* 6 bit slip controls &t;&t;*/
)brace
suffix:semicolon
r_extern
r_int
id|slip_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|slip_esc
c_func
(paren
r_int
r_char
op_star
id|s
comma
r_int
r_char
op_star
id|d
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|slip_esc6
c_func
(paren
r_int
r_char
op_star
id|s
comma
r_int
r_char
op_star
id|d
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|slip_unesc
c_func
(paren
r_struct
id|slip
op_star
id|sl
comma
r_int
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|error
)paren
suffix:semicolon
r_extern
r_void
id|slip_unesc6
c_func
(paren
r_struct
id|slip
op_star
id|sl
comma
r_int
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|error
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_SLIP.H */
eof
