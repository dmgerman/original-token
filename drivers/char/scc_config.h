macro_line|#include &lt;linux/scc.h&gt;
multiline_comment|/********* CONFIGURATION PARAMATERES; PLEASE CHANGE THIS TO YOUR OWN SITUATION **********/
multiline_comment|/* SCC hardware parameters */
multiline_comment|/* use the following board types: &n; *&n; *&t;PA0HZP&t;&t;OptoSCC (PA0HZP)&n; *&t;EAGLE         &t;EAGLE&n; *&t;PC100         &t;PC100 &n; *&t;PRIMUS        &t;PRIMUS-PC (DG9BL)&n; *&t;DRSI          &t;DRSI PC*Packet&n; *&t;BAYCOM        &t;BayCom (U)SCC&n; *&t;&n; */
DECL|variable|Nchips
r_int
id|Nchips
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* number of chips */
DECL|variable|Vector_Latch
id|io_port
id|Vector_Latch
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* addr. of INTACK-Latch (0 for poll mode) */
DECL|variable|Ivec
r_int
id|Ivec
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* interrupt vector */
DECL|variable|Clock
r_int
id|Clock
op_assign
l_int|4915200
suffix:semicolon
multiline_comment|/* frequency of the scc clock */
DECL|variable|Board
r_char
id|Board
op_assign
id|BAYCOM
suffix:semicolon
multiline_comment|/* what type of SCC card do you use? */
DECL|variable|Option
r_int
id|Option
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* command for extra hardware */
DECL|variable|Special_Port
id|io_port
id|Special_Port
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* port address for special hardware */
multiline_comment|/* (for EAGLE, PC100, PRIMUS, DRSI) */
multiline_comment|/*      ^  never remove the semicolon !! */
multiline_comment|/* &t;&t;&t;Channel    A      B&t;    Chip&t;*/
multiline_comment|/*&t;&t;&t;         ============&t;  ========&t;*/
multiline_comment|/* Control ports:&t;&t;&t;&t;&t;&t;*/
DECL|variable|SCC_ctrl
id|io_port
id|SCC_ctrl
(braket
id|MAXSCC
op_star
l_int|2
)braket
op_assign
(brace
l_int|0x304
comma
l_int|0x305
comma
multiline_comment|/* ...one... &t;*/
l_int|0x306
comma
l_int|0x307
comma
multiline_comment|/* ...two...&t;*/
l_int|0
comma
l_int|0
comma
multiline_comment|/* ...three...&t;*/
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* ...four...&t;*/
multiline_comment|/* Data ports:&t;&t;&t;&t;&t;&t;&t;*/
DECL|variable|SCC_data
id|io_port
id|SCC_data
(braket
id|MAXSCC
op_star
l_int|2
)braket
op_assign
(brace
l_int|0x300
comma
l_int|0x301
comma
multiline_comment|/* ...one...&t;*/
l_int|0x302
comma
l_int|0x303
comma
multiline_comment|/* ...two...&t;*/
l_int|0
comma
l_int|0
comma
multiline_comment|/* ...three...&t;*/
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* ...four...&t;*/
multiline_comment|/* set to &squot;1&squot; if you have and want ESCC chip (8580/85180/85280) support */
multiline_comment|/*&t;&t;&t;&t;&t;      Chip&t;*/
multiline_comment|/*&t;&t;&t;&t;            ========   &t;*/
DECL|variable|SCC_Enhanced
r_int
id|SCC_Enhanced
(braket
id|MAXSCC
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* ...one...&t;*/
l_int|0
comma
multiline_comment|/* ...two...&t;*/
l_int|0
comma
multiline_comment|/* ...three...&t;*/
l_int|0
)brace
suffix:semicolon
multiline_comment|/* ...four...&t;*/
multiline_comment|/* some useful #defines. You might need them or not */
DECL|macro|VERBOSE_BOOTMSG
mdefine_line|#define VERBOSE_BOOTMSG 1
DECL|macro|SCC_DELAY
macro_line|#undef  SCC_DELAY&t;&t;/* perhaps a 486DX2 is a *bit* too fast */
DECL|macro|SCC_LDELAY
macro_line|#undef  SCC_LDELAY&t;&t;/* slow it even a bit more down */
DECL|macro|DONT_CHECK
macro_line|#undef  DONT_CHECK&t;&t;/* don&squot;t look if the SCCs you specified are available */
multiline_comment|/* The external clocking, nrz and fullduplex divider configuration is gone */
multiline_comment|/* you can set these parameters in /etc/z8530drv.rc and initialize the  */
multiline_comment|/* driver with sccinit */
eof
