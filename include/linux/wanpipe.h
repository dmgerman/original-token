multiline_comment|/*****************************************************************************&n;* wanpipe.h&t;WANPIPE(tm) Multiprotocol WAN Link Driver.&n;*&t;&t;User-level API definitions.&n;*&n;* Author:&t;Gene Kozin&t;&lt;genek@compuserve.com&gt;&n;*&n;* Copyright:&t;(c) 1995-1997 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jan 15, 1997&t;Gene Kozin&t;Version 3.1.0&n;*&t;&t;&t;&t; o added UDP management stuff&n;* Jan 02, 1997&t;Gene Kozin&t;Version 3.0.0&n;*****************************************************************************/
macro_line|#ifndef&t;_WANPIPE_H
DECL|macro|_WANPIPE_H
mdefine_line|#define&t;_WANPIPE_H
macro_line|#include &lt;linux/wanrouter.h&gt;
multiline_comment|/* Defines */
macro_line|#ifndef&t;PACKED
DECL|macro|PACKED
mdefine_line|#define&t;PACKED&t;__attribute__((packed))
macro_line|#endif
DECL|macro|WANPIPE_MAGIC
mdefine_line|#define&t;WANPIPE_MAGIC&t;0x414C4453L&t;/* signatire: &squot;SDLA&squot; reversed */
multiline_comment|/* IOCTL numbers (up to 16) */
DECL|macro|WANPIPE_DUMP
mdefine_line|#define&t;WANPIPE_DUMP&t;(ROUTER_USER+0)&t;/* dump adapter&squot;s memory */
DECL|macro|WANPIPE_EXEC
mdefine_line|#define&t;WANPIPE_EXEC&t;(ROUTER_USER+1)&t;/* execute firmware command */
multiline_comment|/*&n; * Data structures for IOCTL calls.&n; */
DECL|struct|sdla_dump
r_typedef
r_struct
id|sdla_dump
multiline_comment|/* WANPIPE_DUMP */
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* for verification */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* absolute adapter memory address */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* block length */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
multiline_comment|/* -&gt; buffer */
DECL|typedef|sdla_dump_t
)brace
id|sdla_dump_t
suffix:semicolon
DECL|struct|sdla_exec
r_typedef
r_struct
id|sdla_exec
multiline_comment|/* WANPIPE_EXEC */
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* for verification */
DECL|member|cmd
r_void
op_star
id|cmd
suffix:semicolon
multiline_comment|/* -&gt; command structure */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* -&gt; data buffer */
DECL|typedef|sdla_exec_t
)brace
id|sdla_exec_t
suffix:semicolon
multiline_comment|/* UDP management stuff */
DECL|struct|wum_header
r_typedef
r_struct
id|wum_header
(brace
DECL|member|signature
r_int
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 00h: signature */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* 08h: request/reply */
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
multiline_comment|/* 09h: commnand */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0Ah: reserved */
DECL|typedef|wum_header_t
)brace
id|wum_header_t
suffix:semicolon
DECL|macro|WUM_SIGNATURE_L
mdefine_line|#define&t;WUM_SIGNATURE_L&t;0x50495046
DECL|macro|WUM_SIGNATURE_H
mdefine_line|#define&t;WUM_SIGNATURE_H&t;0x444E3845
DECL|macro|WUM_KILL
mdefine_line|#define&t;WUM_KILL&t;0x50
DECL|macro|WUM_EXEC
mdefine_line|#define&t;WUM_EXEC&t;0x51
macro_line|#ifdef&t;__KERNEL__
multiline_comment|/****** Kernel Interface ****************************************************/
macro_line|#include &lt;linux/sdladrv.h&gt;&t;/* SDLA support module API definitions */
macro_line|#include &lt;linux/sdlasfm.h&gt;&t;/* SDLA firmware module definitions */
macro_line|#ifndef&t;min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef&t;max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
DECL|macro|is_digit
mdefine_line|#define&t;is_digit(ch) (((ch)&gt;=(unsigned)&squot;0&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;9&squot;)?1:0)
DECL|macro|is_alpha
mdefine_line|#define&t;is_alpha(ch) ((((ch)&gt;=(unsigned)&squot;a&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;z&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;A&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;Z&squot;))?1:0)
DECL|macro|is_hex_digit
mdefine_line|#define&t;is_hex_digit(ch) ((((ch)&gt;=(unsigned)&squot;0&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;9&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;a&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;f&squot;)||&bslash;&n;&t; &t;  ((ch)&gt;=(unsigned)&squot;A&squot;&amp;&amp;(ch)&lt;=(unsigned)&squot;F&squot;))?1:0)
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/* Adapter Data Space.&n; * This structure is needed because we handle multiple cards, otherwise&n; * static data would do it.&n; */
DECL|struct|sdla
r_typedef
r_struct
id|sdla
(brace
DECL|member|devname
r_char
id|devname
(braket
id|WAN_DRVNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* card name */
DECL|member|hw
id|sdlahw_t
id|hw
suffix:semicolon
multiline_comment|/* hardware configuration */
DECL|member|wandev
id|wan_device_t
id|wandev
suffix:semicolon
multiline_comment|/* WAN device data space */
DECL|member|open_cnt
r_int
id|open_cnt
suffix:semicolon
multiline_comment|/* number of open interfaces */
DECL|member|state_tick
r_int
r_int
id|state_tick
suffix:semicolon
multiline_comment|/* link state timestamp */
multiline_comment|/*&t;unsigned tx_int_enabled; */
multiline_comment|/* tranmit interrupt enabled or not */
DECL|member|in_isr
r_char
id|in_isr
suffix:semicolon
multiline_comment|/* interrupt-in-service flag */
DECL|member|mbox
r_void
op_star
id|mbox
suffix:semicolon
multiline_comment|/* -&gt; mailbox */
DECL|member|rxmb
r_void
op_star
id|rxmb
suffix:semicolon
multiline_comment|/* -&gt; receive mailbox */
DECL|member|flags
r_void
op_star
id|flags
suffix:semicolon
multiline_comment|/* -&gt; adapter status flags */
DECL|member|isr
r_void
(paren
op_star
id|isr
)paren
(paren
r_struct
id|sdla
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* interrupt service routine */
DECL|member|poll
r_void
(paren
op_star
id|poll
)paren
(paren
r_struct
id|sdla
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* polling routine */
DECL|member|exec
r_int
(paren
op_star
id|exec
)paren
(paren
r_struct
id|sdla
op_star
id|card
comma
r_void
op_star
id|u_cmd
comma
r_void
op_star
id|u_data
)paren
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/****** X.25 specific data **********/
DECL|member|lo_pvc
r_int
id|lo_pvc
suffix:semicolon
DECL|member|hi_pvc
r_int
id|hi_pvc
suffix:semicolon
DECL|member|lo_svc
r_int
id|lo_svc
suffix:semicolon
DECL|member|hi_svc
r_int
id|hi_svc
suffix:semicolon
DECL|member|x
)brace
id|x
suffix:semicolon
r_struct
(brace
multiline_comment|/****** frame relay specific data ***/
DECL|member|rxmb_base
r_void
op_star
id|rxmb_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxmb_last
r_void
op_star
id|rxmb_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* S508 receive buffer base */
DECL|member|rx_top
r_int
id|rx_top
suffix:semicolon
multiline_comment|/* S508 receive buffer end */
DECL|member|node_dlci
r_int
r_int
id|node_dlci
suffix:semicolon
DECL|member|dlci_num
r_int
r_int
id|dlci_num
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
r_struct
multiline_comment|/****** PPP-specific data ***********/
(brace
DECL|member|if_name
r_char
id|if_name
(braket
id|WAN_IFNAME_SZ
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* interface name */
DECL|member|txbuf
r_void
op_star
id|txbuf
suffix:semicolon
multiline_comment|/* -&gt; current Tx buffer */
DECL|member|txbuf_base
r_void
op_star
id|txbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Tx buffer */
DECL|member|txbuf_last
r_void
op_star
id|txbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Tx buffer */
DECL|member|rxbuf_base
r_void
op_star
id|rxbuf_base
suffix:semicolon
multiline_comment|/* -&gt; first Rx buffer */
DECL|member|rxbuf_last
r_void
op_star
id|rxbuf_last
suffix:semicolon
multiline_comment|/* -&gt; last Rx buffer */
DECL|member|rx_base
r_int
id|rx_base
suffix:semicolon
multiline_comment|/* S508 receive buffer base */
DECL|member|rx_top
r_int
id|rx_top
suffix:semicolon
multiline_comment|/* S508 receive buffer end */
DECL|member|p
)brace
id|p
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|sdla_t
)brace
id|sdla_t
suffix:semicolon
multiline_comment|/****** Public Functions ****************************************************/
r_void
id|wanpipe_open
(paren
id|sdla_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_void
id|wanpipe_close
(paren
id|sdla_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_void
id|wanpipe_set_state
(paren
id|sdla_t
op_star
id|card
comma
r_int
id|state
)paren
suffix:semicolon
multiline_comment|/* wpmain.c */
r_int
id|wpx_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpx.c */
r_int
id|wpf_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpf.c */
r_int
id|wpp_init
(paren
id|sdla_t
op_star
id|card
comma
id|wandev_conf_t
op_star
id|conf
)paren
suffix:semicolon
multiline_comment|/* wpp.c */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _WANPIPE_H */
eof
