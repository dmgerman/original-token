multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Holds initial configuration information for devices.&n; *&n; * NOTE:&t;This file is a nice idea, but its current format does not work&n; *&t;&t;well for drivers that support multiple units, like the SLIP&n; *&t;&t;driver.  We should actually have only one pointer to a driver&n; *&t;&t;here, with the driver knowing how many units it supports.&n; *&t;&t;Currently, the SLIP driver abuses the &quot;base_addr&quot; integer&n; *&t;&t;field of the &squot;device&squot; structure to store the unit number...&n; *&t;&t;-FvK&n; *&n; * Version:&t;@(#)Space.c&t;1.0.7&t;05/28/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@super.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ddi.h&gt;
macro_line|#include &quot;dev.h&quot;
DECL|macro|LOOPBACK
mdefine_line|#define LOOPBACK&t;&t;&t;/* always present, right?&t;*/
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;NULL
macro_line|#ifdef D_LINK
r_extern
r_int
id|d_link_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|d_link_dev
r_static
r_struct
id|device
id|d_link_dev
op_assign
(brace
l_string|&quot;dl0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|D_LINK_IO
comma
id|D_LINK_IRQ
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NEXT_DEV
comma
id|d_link_init
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;d_link_dev)
macro_line|#endif
macro_line|#ifdef EL1
macro_line|#   ifndef EL1_IRQ
DECL|macro|EL1_IRQ
macro_line|#&t;define EL1_IRQ 9
macro_line|#   endif
r_extern
r_int
id|el1_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|el1_dev
r_static
r_struct
id|device
id|el1_dev
op_assign
(brace
l_string|&quot;el0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|EL1
comma
id|EL1_IRQ
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NEXT_DEV
comma
id|el1_init
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;el1_dev)
macro_line|#endif  /* EL1 */
macro_line|#if defined(EI8390) || defined(EL2) || defined(NE2000) &bslash;&n;    || defined(WD80x3) || defined(HPLAN)
macro_line|#   ifndef EI8390
DECL|macro|EI8390
macro_line|#&t;define EI8390 0
macro_line|#   endif
macro_line|#   ifndef EI8390_IRQ
DECL|macro|EI8390_IRQ
macro_line|#&t;define EI8390_IRQ 0
macro_line|#   endif
r_extern
r_int
id|ethif_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|ei8390_dev
r_static
r_struct
id|device
id|ei8390_dev
op_assign
(brace
l_string|&quot;eth0&quot;
comma
l_int|0
comma
multiline_comment|/* auto-config&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|EI8390
comma
id|EI8390_IRQ
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NEXT_DEV
comma
id|ethif_init
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;ei8390_dev)
macro_line|#endif  /* The EI8390 drivers. */
macro_line|#ifdef&t;PLIP
r_extern
r_int
id|plip_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|plip2_dev
r_static
r_struct
id|device
id|plip2_dev
op_assign
(brace
l_string|&quot;plip2&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x278
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NEXT_DEV
comma
id|plip_init
)brace
suffix:semicolon
DECL|variable|plip1_dev
r_static
r_struct
id|device
id|plip1_dev
op_assign
(brace
l_string|&quot;plip1&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x378
comma
l_int|7
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|plip2_dev
comma
id|plip_init
)brace
suffix:semicolon
DECL|variable|plip0_dev
r_static
r_struct
id|device
id|plip0_dev
op_assign
(brace
l_string|&quot;plip0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x3BC
comma
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|plip1_dev
comma
id|plip_init
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;plip0_dev)
macro_line|#endif  /* PLIP */
macro_line|#ifdef&t;SLIP
r_extern
r_int
id|slip_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|slip3_dev
r_static
r_struct
id|device
id|slip3_dev
op_assign
(brace
l_string|&quot;sl3&quot;
comma
multiline_comment|/* Internal SLIP driver, channel 3&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0x3
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
id|NEXT_DEV
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|slip_init
multiline_comment|/* slip_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|variable|slip2_dev
r_static
r_struct
id|device
id|slip2_dev
op_assign
(brace
l_string|&quot;sl2&quot;
comma
multiline_comment|/* Internal SLIP driver, channel 2&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0x2
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
op_amp
id|slip3_dev
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|slip_init
multiline_comment|/* slip_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|variable|slip1_dev
r_static
r_struct
id|device
id|slip1_dev
op_assign
(brace
l_string|&quot;sl1&quot;
comma
multiline_comment|/* Internal SLIP driver, channel 1&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0x1
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
op_amp
id|slip2_dev
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|slip_init
multiline_comment|/* slip_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|variable|slip0_dev
r_static
r_struct
id|device
id|slip0_dev
op_assign
(brace
l_string|&quot;sl0&quot;
comma
multiline_comment|/* Internal SLIP driver, channel 0&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
op_amp
id|slip1_dev
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|slip_init
multiline_comment|/* slip_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;slip0_dev)
macro_line|#endif&t;/* SLIP */
macro_line|#ifdef LOOPBACK
r_extern
r_int
id|loopback_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|loopback_dev
r_static
r_struct
id|device
id|loopback_dev
op_assign
(brace
l_string|&quot;lo&quot;
comma
multiline_comment|/* Software Loopback interface&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
id|NEXT_DEV
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|loopback_init
multiline_comment|/* loopback_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;loopback_dev)
macro_line|#endif
DECL|variable|dev_base
r_struct
id|device
op_star
id|dev_base
op_assign
id|NEXT_DEV
suffix:semicolon
eof
