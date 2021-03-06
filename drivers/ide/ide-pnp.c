multiline_comment|/*&n; * linux/drivers/ide/ide-pnp.c&n; *&n; * This file provides autodetection for ISA PnP IDE interfaces.&n; * It was tested with &quot;ESS ES1868 Plug and Play AudioDrive&quot; IDE interface.&n; *&n; * Copyright (C) 2000 Andrey Panin &lt;pazke@orbita.don.sitek.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n; */
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#ifndef PREPARE_FUNC
DECL|macro|PREPARE_FUNC
mdefine_line|#define PREPARE_FUNC(dev)  (dev-&gt;prepare)
DECL|macro|ACTIVATE_FUNC
mdefine_line|#define ACTIVATE_FUNC(dev)  (dev-&gt;activate)
DECL|macro|DEACTIVATE_FUNC
mdefine_line|#define DEACTIVATE_FUNC(dev)  (dev-&gt;deactivate)
macro_line|#endif
DECL|macro|DEV_IO
mdefine_line|#define DEV_IO(dev, index) (dev-&gt;resource[index].start)
DECL|macro|DEV_IRQ
mdefine_line|#define DEV_IRQ(dev, index) (dev-&gt;irq_resource[index].start)
DECL|macro|DEV_NAME
mdefine_line|#define DEV_NAME(dev) (dev-&gt;bus-&gt;name ? dev-&gt;bus-&gt;name : &quot;ISA PnP&quot;)
DECL|macro|GENERIC_HD_DATA
mdefine_line|#define GENERIC_HD_DATA&t;&t;0
DECL|macro|GENERIC_HD_ERROR
mdefine_line|#define GENERIC_HD_ERROR&t;1
DECL|macro|GENERIC_HD_NSECTOR
mdefine_line|#define GENERIC_HD_NSECTOR&t;2
DECL|macro|GENERIC_HD_SECTOR
mdefine_line|#define GENERIC_HD_SECTOR&t;3
DECL|macro|GENERIC_HD_LCYL
mdefine_line|#define GENERIC_HD_LCYL&t;&t;4
DECL|macro|GENERIC_HD_HCYL
mdefine_line|#define GENERIC_HD_HCYL&t;&t;5
DECL|macro|GENERIC_HD_SELECT
mdefine_line|#define GENERIC_HD_SELECT&t;6
DECL|macro|GENERIC_HD_STATUS
mdefine_line|#define GENERIC_HD_STATUS&t;7
DECL|variable|__initdata
r_static
r_int
id|generic_ide_offsets
(braket
id|IDE_NR_PORTS
)braket
id|__initdata
op_assign
(brace
id|GENERIC_HD_DATA
comma
id|GENERIC_HD_ERROR
comma
id|GENERIC_HD_NSECTOR
comma
id|GENERIC_HD_SECTOR
comma
id|GENERIC_HD_LCYL
comma
id|GENERIC_HD_HCYL
comma
id|GENERIC_HD_SELECT
comma
id|GENERIC_HD_STATUS
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* ISA PnP device table entry */
DECL|struct|pnp_dev_t
r_struct
id|pnp_dev_t
(brace
DECL|member|vendor
DECL|member|device
r_int
r_int
id|vendor
comma
id|device
suffix:semicolon
DECL|member|init_fn
r_int
(paren
op_star
id|init_fn
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|enable
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Generic initialisation function for ISA PnP IDE interface */
DECL|function|pnpide_generic_init
r_static
r_int
id|__init
id|pnpide_generic_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|enable
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|DEV_IO
c_func
(paren
id|dev
comma
l_int|0
)paren
op_logical_and
id|DEV_IO
c_func
(paren
id|dev
comma
l_int|1
)paren
op_logical_and
id|DEV_IRQ
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
id|DEV_IO
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|generic_ide_offsets
comma
(paren
id|ide_ioreg_t
)paren
id|DEV_IO
c_func
(paren
id|dev
comma
l_int|1
)paren
comma
l_int|0
comma
l_int|NULL
comma
id|DEV_IRQ
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
suffix:semicolon
id|index
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide%d: %s IDE interface&bslash;n&quot;
comma
id|index
comma
id|DEV_NAME
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Add your devices here :)) */
DECL|variable|__initdata
r_struct
id|pnp_dev_t
id|idepnp_devices
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* Generic ESDI/IDE/ATA compatible hard disk controller&r; */
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;P&squot;
comma
l_char|&squot;N&squot;
comma
l_char|&squot;P&squot;
)paren
comma
id|ISAPNP_DEVICE
c_func
(paren
l_int|0x0600
)paren
comma
id|pnpide_generic_init
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NR_PNP_DEVICES
macro_line|#ifdef MODULE
DECL|struct|pnp_dev_inst
mdefine_line|#define NR_PNP_DEVICES 8
DECL|member|dev
r_struct
id|pnp_dev_inst
(brace
DECL|member|dev_type
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pnp_dev_t
op_star
id|dev_type
suffix:semicolon
DECL|variable|devices
)brace
suffix:semicolon
DECL|variable|pnp_ide_dev_idx
r_static
r_struct
id|pnp_dev_inst
id|devices
(braket
id|NR_PNP_DEVICES
)braket
suffix:semicolon
r_static
r_int
id|pnp_ide_dev_idx
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Probe for ISA PnP IDE interfaces.&n; */
r_void
id|__init
id|pnpide_init
c_func
(paren
r_int
id|enable
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pnp_dev_t
op_star
id|dev_type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isapnp_present
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
macro_line|#ifdef MODULE
multiline_comment|/* Module unload, deactivate all registered devices. */
r_if
c_cond
(paren
op_logical_neg
id|enable
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pnp_ide_dev_idx
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devices
(braket
id|i
)braket
dot
id|dev_type
op_member_access_from_pointer
id|init_fn
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DEACTIVATE_FUNC
c_func
(paren
id|devices
(braket
id|i
)braket
dot
id|dev
)paren
)paren
id|DEACTIVATE_FUNC
c_func
(paren
id|devices
(braket
id|i
)braket
dot
id|dev
)paren
(paren
id|devices
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#endif
r_for
c_loop
(paren
id|dev_type
op_assign
id|idepnp_devices
suffix:semicolon
id|dev_type-&gt;vendor
suffix:semicolon
id|dev_type
op_increment
)paren
(brace
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|isapnp_find_dev
c_func
(paren
l_int|NULL
comma
id|dev_type-&gt;vendor
comma
id|dev_type-&gt;device
comma
id|dev
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;active
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|PREPARE_FUNC
c_func
(paren
id|dev
)paren
op_logical_and
(paren
id|PREPARE_FUNC
c_func
(paren
id|dev
)paren
)paren
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide: %s prepare failed&bslash;n&quot;
comma
id|DEV_NAME
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACTIVATE_FUNC
c_func
(paren
id|dev
)paren
op_logical_and
(paren
id|ACTIVATE_FUNC
c_func
(paren
id|dev
)paren
)paren
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide: %s activate failed&bslash;n&quot;
comma
id|DEV_NAME
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Call device initialization function */
r_if
c_cond
(paren
id|dev_type
op_member_access_from_pointer
id|init_fn
c_func
(paren
id|dev
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|DEACTIVATE_FUNC
c_func
(paren
id|dev
)paren
)paren
id|DEACTIVATE_FUNC
c_func
(paren
id|dev
)paren
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef MODULE
multiline_comment|/*&n;&t;&t;&t;&t; * Register device in the array to&n;&t;&t;&t;&t; * deactivate it on a module unload.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|pnp_ide_dev_idx
op_ge
id|NR_PNP_DEVICES
)paren
r_return
suffix:semicolon
id|devices
(braket
id|pnp_ide_dev_idx
)braket
dot
id|dev
op_assign
id|dev
suffix:semicolon
id|devices
(braket
id|pnp_ide_dev_idx
)braket
dot
id|dev_type
op_assign
id|dev_type
suffix:semicolon
id|pnp_ide_dev_idx
op_increment
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
)brace
eof
