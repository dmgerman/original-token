multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Holds initial configuration information for devices.&n; *&n; * NOTE:&t;This file is a nice idea, but its current format does not work&n; *&t;&t;well for drivers that support multiple units, like the SLIP&n; *&t;&t;driver.  We should actually have only one pointer to a driver&n; *&t;&t;here, with the driver knowing how many units it supports.&n; *&t;&t;Currently, the SLIP driver abuses the &quot;base_addr&quot; integer&n; *&t;&t;field of the &squot;device&squot; structure to store the unit number...&n; *&t;&t;-FvK&n; *&n; * Version:&t;@(#)Space.c&t;1.0.7&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@super.org&gt;&n; *&n; *&t;FIXME:&n; *&t;&t;Sort the device chain fastest first.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|NEXT_DEV
mdefine_line|#define&t;NEXT_DEV&t;NULL
multiline_comment|/* A unified ethernet device probe.  This is the easiest way to have every&n;   ethernet adaptor have the name &quot;eth[0123...]&quot;.&n;   */
r_extern
r_int
id|hp100_probe
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
id|ultra_probe
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
id|hp_plus_probe
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
id|eepro_probe
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
id|at1700_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fmv18x_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eth16i_probe
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
id|apricot_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ewrk3_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|de4x5_probe
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
macro_line|#if&t;defined(CONFIG_WAVELAN)
r_extern
r_int
id|wavelan_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* defined(CONFIG_WAVELAN) */
r_extern
r_int
id|el16_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|elplus_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ac3200_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|e2100_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ni52_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ni65_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SK_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|seeq8005_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tc59x_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|smc_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Detachable devices (&quot;pocket adaptors&quot;) */
r_extern
r_int
id|atp_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|de600_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|de620_probe
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
id|u_long
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|base_addr
op_eq
l_int|0xffe0
)paren
op_logical_or
(paren
id|base_addr
op_eq
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* ENXIO */
r_if
c_cond
(paren
l_int|1
macro_line|#if defined(CONFIG_VORTEX)
op_logical_and
id|tc59x_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_SEEQ8005)
op_logical_and
id|seeq8005_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_HP100)
op_logical_and
id|hp100_probe
c_func
(paren
id|dev
)paren
macro_line|#endif&t;
macro_line|#if defined(CONFIG_ULTRA)
op_logical_and
id|ultra_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_SMC9194)
op_logical_and
id|smc_init
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_WD80x3) || defined(WD80x3)
op_logical_and
id|wd_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_EL2) || defined(EL2)&t;/* 3c503 */
op_logical_and
id|el2_probe
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
macro_line|#if defined(CONFIG_HPLAN_PLUS)
op_logical_and
id|hp_plus_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_AC3200&t;&t;/* Ansel Communications EISA 3200. */
op_logical_and
id|ac3200_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_E2100&t;&t;/* Cabletron E21xx series. */
op_logical_and
id|e2100_probe
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
macro_line|#ifdef CONFIG_AT1500
op_logical_and
id|at1500_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_AT1700
op_logical_and
id|at1700_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_FMV18X&t;&t;/* Fujitsu FMV-181/182 */
op_logical_and
id|fmv18x_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ETH16I
op_logical_and
id|eth16i_probe
c_func
(paren
id|dev
)paren
multiline_comment|/* ICL EtherTeam 16i/32 */
macro_line|#endif
macro_line|#ifdef CONFIG_EL3&t;&t;/* 3c509 */
op_logical_and
id|el3_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ZNET&t;&t;/* Zenith Z-Note and some IBM Thinkpads. */
op_logical_and
id|znet_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EEXPRESS&t;&t;/* Intel EtherExpress */
op_logical_and
id|express_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EEXPRESS_PRO&t;/* Intel EtherExpress Pro/10 */
op_logical_and
id|eepro_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_DEPCA&t;&t;/* DEC DEPCA */
op_logical_and
id|depca_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EWRK3             /* DEC EtherWORKS 3 */
op_logical_and
id|ewrk3_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_DE4X5             /* DEC DE425, DE434, DE435 adapters */
op_logical_and
id|de4x5_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_APRICOT&t;&t;/* Apricot I82596 */
op_logical_and
id|apricot_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_EL1&t;&t;/* 3c501 */
op_logical_and
id|el1_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if&t;defined(CONFIG_WAVELAN)&t;/* WaveLAN */
op_logical_and
id|wavelan_probe
c_func
(paren
id|dev
)paren
macro_line|#endif&t;/* defined(CONFIG_WAVELAN) */
macro_line|#ifdef CONFIG_EL16&t;&t;/* 3c507 */
op_logical_and
id|el16_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ELPLUS&t;&t;/* 3c505 */
op_logical_and
id|elplus_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_DE600&t;&t;/* D-Link DE-600 adapter */
op_logical_and
id|de600_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_DE620&t;&t;/* D-Link DE-620 adapter */
op_logical_and
id|de620_probe
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_SK_G16)
op_logical_and
id|SK_init
c_func
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_NI52
op_logical_and
id|ni52_probe
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
macro_line|#ifdef CONFIG_SDLA
r_extern
r_int
id|sdla_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|sdla0_dev
r_static
r_struct
id|device
id|sdla0_dev
op_assign
(brace
l_string|&quot;sdla0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|sdla_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;sdla0_dev)
macro_line|#endif
multiline_comment|/* This must be AFTER the various FRADs so it initializes FIRST! */
macro_line|#ifdef CONFIG_DLCI
r_extern
r_int
id|dlci_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|dlci_dev
r_static
r_struct
id|device
id|dlci_dev
op_assign
(brace
l_string|&quot;dlci&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|dlci_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;dlci_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_NETROM
r_extern
r_int
id|nr_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|nr3_dev
r_static
r_struct
id|device
id|nr3_dev
op_assign
(brace
l_string|&quot;nr3&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|nr_init
comma
)brace
suffix:semicolon
DECL|variable|nr2_dev
r_static
r_struct
id|device
id|nr2_dev
op_assign
(brace
l_string|&quot;nr2&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|nr3_dev
comma
id|nr_init
comma
)brace
suffix:semicolon
DECL|variable|nr1_dev
r_static
r_struct
id|device
id|nr1_dev
op_assign
(brace
l_string|&quot;nr1&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|nr2_dev
comma
id|nr_init
comma
)brace
suffix:semicolon
DECL|variable|nr0_dev
r_static
r_struct
id|device
id|nr0_dev
op_assign
(brace
l_string|&quot;nr0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|nr1_dev
comma
id|nr_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;nr0_dev)
macro_line|#endif
multiline_comment|/* Run-time ATtachable (Pocket) devices have a different (not &quot;eth#&quot;) name. */
macro_line|#ifdef CONFIG_ATP&t;&t;/* AT-LAN-TEC (RealTek) pocket adaptor. */
DECL|variable|atp_dev
r_static
r_struct
id|device
id|atp_dev
op_assign
(brace
l_string|&quot;atp0&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
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
id|atp_init
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define NEXT_DEV&t;(&amp;atp_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCNET
r_extern
r_int
id|arcnet_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|arcnet_dev
r_static
r_struct
id|device
id|arcnet_dev
op_assign
(brace
l_string|&quot;arc0&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
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
id|arcnet_probe
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;arcnet_dev)
macro_line|#endif
multiline_comment|/* The first device defaults to I/O base &squot;0&squot;, which means autoprobe. */
macro_line|#ifndef ETH0_ADDR
DECL|macro|ETH0_ADDR
macro_line|# define ETH0_ADDR 0
macro_line|#endif
macro_line|#ifndef ETH0_IRQ
DECL|macro|ETH0_IRQ
macro_line|# define ETH0_IRQ 0
macro_line|#endif
multiline_comment|/* &quot;eth0&quot; defaults to autoprobe (== 0), other use a base of 0xffe0 (== -0x20),&n;   which means &quot;don&squot;t probe&quot;.  These entries exist to only to provide empty&n;   slots which may be enabled at boot-time. */
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
multiline_comment|/* To be exact, this node just hooks the initialization&n;&t;   routines to the device structures.&t;&t;&t;*/
r_extern
r_int
id|slip_init_ctrl_dev
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|slip_bootstrap
r_static
r_struct
id|device
id|slip_bootstrap
op_assign
(brace
l_string|&quot;slip_proto&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
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
id|slip_init_ctrl_dev
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV (&amp;slip_bootstrap)
macro_line|#endif&t;/* SLIP */
macro_line|#if defined(CONFIG_STRIP)
r_extern
r_int
id|strip_init_ctrl_dev
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|strip_bootstrap
r_static
r_struct
id|device
id|strip_bootstrap
op_assign
(brace
l_string|&quot;strip_proto&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
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
id|strip_init_ctrl_dev
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV (&amp;strip_bootstrap)
macro_line|#endif   /* STRIP */
macro_line|#if defined(CONFIG_PPP)
r_extern
r_int
id|ppp_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|ppp_bootstrap
r_static
r_struct
id|device
id|ppp_bootstrap
op_assign
(brace
l_string|&quot;ppp_proto&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
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
id|ppp_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#undef NEXT_DEV
DECL|macro|NEXT_DEV
mdefine_line|#define NEXT_DEV (&amp;ppp_bootstrap)
macro_line|#endif   /* PPP */
macro_line|#ifdef CONFIG_DUMMY
r_extern
r_int
id|dummy_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|dummy_dev
r_static
r_struct
id|device
id|dummy_dev
op_assign
(brace
l_string|&quot;dummy&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
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
id|dummy_init
comma
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;dummy_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_EQUALIZER
r_extern
r_int
id|eql_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|eql_dev
r_struct
id|device
id|eql_dev
op_assign
(brace
l_string|&quot;eql&quot;
comma
multiline_comment|/* Master device for IP traffic load &n;&t;&t;&t;&t;   balancing */
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
multiline_comment|/* recv end/start; mem end/start */
l_int|0
comma
multiline_comment|/* base I/O address */
l_int|0
comma
multiline_comment|/* IRQ */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags */
id|NEXT_DEV
comma
multiline_comment|/* next device */
id|eql_init
multiline_comment|/* set up the rest */
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef       NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define      NEXT_DEV        (&amp;eql_dev)
macro_line|#endif
macro_line|#ifdef CONFIG_IBMTR 
r_extern
r_int
id|tok_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|ibmtr_dev1
r_static
r_struct
id|device
id|ibmtr_dev1
op_assign
(brace
l_string|&quot;tr1&quot;
comma
multiline_comment|/* IBM Token Ring (Non-DMA) Interface */
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
l_int|0xa24
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
id|tok_probe
multiline_comment|/* ??? Token_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;ibmtr_dev1)
DECL|variable|ibmtr_dev0
r_static
r_struct
id|device
id|ibmtr_dev0
op_assign
(brace
l_string|&quot;tr0&quot;
comma
multiline_comment|/* IBM Token Ring (Non-DMA) Interface */
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
l_int|0xa20
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
id|tok_probe
multiline_comment|/* ??? Token_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;ibmtr_dev0)
macro_line|#endif 
macro_line|#ifdef CONFIG_NET_IPIP
macro_line|#ifdef CONFIG_IP_FORWARD
r_extern
r_int
id|tunnel_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|variable|tunnel_dev1
r_static
r_struct
id|device
id|tunnel_dev1
op_assign
(brace
l_string|&quot;tunl1&quot;
comma
multiline_comment|/* IPIP tunnel  &t;&t;&t;*/
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
id|NEXT_DEV
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|tunnel_init
multiline_comment|/* Fill in the details&t;&t;&t;*/
)brace
suffix:semicolon
DECL|variable|tunnel_dev0
r_static
r_struct
id|device
id|tunnel_dev0
op_assign
(brace
l_string|&quot;tunl0&quot;
comma
multiline_comment|/* IPIP tunnel  &t;&t;&t;*/
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
id|tunnel_dev1
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|tunnel_init
multiline_comment|/* Fill in the details&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|NEXT_DEV
macro_line|#   undef&t;NEXT_DEV
DECL|macro|NEXT_DEV
macro_line|#   define&t;NEXT_DEV&t;(&amp;tunnel_dev0)
macro_line|#endif 
macro_line|#endif
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
DECL|variable|dev_base
r_struct
id|device
op_star
id|dev_base
op_assign
op_amp
id|loopback_dev
suffix:semicolon
eof
