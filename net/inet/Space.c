multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Holds initial configuration information for devices.&n; *&n; * NOTE:&t;This file is a nice idea, but its current format does not work&n; *&t;&t;well for drivers that support multiple units, like the SLIP&n; *&t;&t;driver.  We should actually have only one pointer to a driver&n; *&t;&t;here, with the driver knowing how many units it supports.&n; *&t;&t;Currently, the SLIP driver abuses the &quot;base_addr&quot; integer&n; *&t;&t;field of the &squot;device&squot; structure to store the unit number...&n; *&t;&t;-FvK&n; *&n; * Version:&t;@(#)Space.c&t;1.0.7&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@super.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ddi.h&gt;
macro_line|#include &quot;dev.h&quot;
DECL|macro|LOOPBACK
mdefine_line|#define LOOPBACK&t;&t;&t;/* always present, right?&t;*/
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;NULL
multiline_comment|/* A unifed ethernet device probe.  This is the easiest way to have every&n;   ethernet adaptor have the name &quot;eth[0123...]&quot;.&n;   */
r_extern
r_int
id|wd_probe
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
id|el2_probe
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
id|ne_probe
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
id|hp_probe
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
id|znet_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|express_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|el3_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atp_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|at1500_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|depca_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|el1_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_static
r_int
DECL|function|ethif_probe
id|ethif_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
OL
l_int|0
op_logical_or
id|base_addr
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* ENXIO */
r_if
c_cond
(paren
l_int|1
macro_line|#if defined(CONFIG_WD80x3) || defined(WD80x3)
op_logical_and
id|wd_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_EL2) || defined(EL2)
op_logical_and
id|el2_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_NE2000) || defined(NE2000)
op_logical_and
id|ne_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_HPLAN) || defined(HPLAN)
op_logical_and
id|hp_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_AT1500
op_logical_and
id|at1500_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EL3
op_logical_and
id|el3_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ZNET
op_logical_and
id|znet_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EEXPRESS
op_logical_and
id|express_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ATP&t;&t;/* AT-LAN-TEC (RealTek) pocket adaptor. */
op_logical_and
id|atp_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_DEPCA
op_logical_and
id|depca_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EL1
op_logical_and
id|el1_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
op_logical_and
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* -ENODEV or -EAGAIN would be more accurate. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This remains seperate because it requires the addr and IRQ to be&n;   set. */
macro_line|#if defined(D_LINK) || defined(CONFIG_DE600)
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
multiline_comment|/* The first device defaults to I/O base &squot;0&squot;, which means autoprobe. */
macro_line|#ifdef EI8390
DECL|macro|ETH0_ADDR
macro_line|# define ETH0_ADDR EI8390
macro_line|#else
DECL|macro|ETH0_ADDR
macro_line|# define ETH0_ADDR 0
macro_line|#endif
macro_line|#ifdef EI8390_IRQ
DECL|macro|ETH0_IRQ
macro_line|# define ETH0_IRQ EI8390_IRQ
macro_line|#else
DECL|macro|ETH0_IRQ
macro_line|# define ETH0_IRQ 0
macro_line|#endif
multiline_comment|/* &quot;eth0&quot; defaults to autoprobe, other use a base of &quot;-0x20&quot;, &quot;don&squot;t probe&quot;.&n;   Enable these with boot-time setup. 0.99pl13+ can optionally autoprobe. */
DECL|variable|eth3_dev
r_static
r_struct
id|device
id|eth3_dev
op_assign
(brace
l_string|&quot;eth3&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffe0
multiline_comment|/* I/O base*/
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NEXT_DEV
comma
id|ethif_probe
)brace
suffix:semicolon
DECL|variable|eth2_dev
r_static
r_struct
id|device
id|eth2_dev
op_assign
(brace
l_string|&quot;eth2&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffe0
multiline_comment|/* I/O base*/
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|eth3_dev
comma
id|ethif_probe
)brace
suffix:semicolon
DECL|variable|eth1_dev
r_static
r_struct
id|device
id|eth1_dev
op_assign
(brace
l_string|&quot;eth1&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffe0
multiline_comment|/* I/O base*/
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|eth2_dev
comma
id|ethif_probe
)brace
suffix:semicolon
DECL|variable|eth0_dev
r_static
r_struct
id|device
id|eth0_dev
op_assign
(brace
l_string|&quot;eth0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|ETH0_ADDR
comma
id|ETH0_IRQ
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|eth1_dev
comma
id|ethif_probe
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;eth0_dev)
macro_line|#if defined(PLIP) || defined(CONFIG_PLIP)
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
comma
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
comma
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
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;plip0_dev)
macro_line|#endif  /* PLIP */
macro_line|#if defined(SLIP) || defined(CONFIG_SLIP)
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
