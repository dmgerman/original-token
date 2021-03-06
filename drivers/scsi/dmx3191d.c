multiline_comment|/*&n;    dmx3191d.c - midlevel driver for the Domex DMX3191D SCSI card.&n;    Copyright (C) 2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    Based on the generic NCR5380 driver by Drew Eckhardt et al.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;constants.h&quot;
macro_line|#include &quot;sd.h&quot;
macro_line|#include &quot;dmx3191d.h&quot;
multiline_comment|/* play with these values to tune up your system performances */
multiline_comment|/* default setting from g_NCR5380.c */
multiline_comment|/*&n;#define USLEEP&n;#define USLEEP_POLL&t;&t;1&n;#define USLEEP_SLEEP&t;&t;20&n;#define USLEEP_WAITLONG&t;&t;500&n;*/
DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
macro_line|#include &quot;NCR5380.h&quot;
macro_line|#include &quot;NCR5380.c&quot;
DECL|function|dmx3191d_detect
r_int
id|__init
id|dmx3191d_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tmpl
)paren
(brace
r_int
id|boards
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
id|dmx3191d_printk
c_func
(paren
l_string|&quot;PCI support not enabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmpl-&gt;proc_name
op_assign
id|DMX3191D_DRIVER_NAME
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_DOMEX
comma
id|PCI_DEVICE_ID_DOMEX_DMX3191D
comma
id|pdev
)paren
)paren
)paren
(brace
r_int
r_int
id|port
op_assign
id|pci_resource_start
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|port
comma
id|DMX3191D_REGION
)paren
)paren
(brace
id|dmx3191d_printk
c_func
(paren
l_string|&quot;region 0x%lx-0x%lx already reserved&bslash;n&quot;
comma
id|port
comma
id|port
op_plus
id|DMX3191D_REGION
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|port
comma
id|DMX3191D_REGION
comma
id|DMX3191D_DRIVER_NAME
)paren
suffix:semicolon
id|instance
op_assign
id|scsi_register
c_func
(paren
id|tmpl
comma
r_sizeof
(paren
r_struct
id|NCR5380_hostdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance
op_eq
l_int|NULL
)paren
(brace
id|release_region
c_func
(paren
id|port
comma
id|DMX3191D_REGION
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|instance-&gt;io_port
op_assign
id|port
suffix:semicolon
id|instance-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
id|FLAG_NO_PSEUDO_DMA
op_or
id|FLAG_DTC3181E
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|dmx3191d_do_intr
comma
id|SA_SHIRQ
comma
id|DMX3191D_DRIVER_NAME
comma
id|instance
)paren
)paren
(brace
id|dmx3191d_printk
c_func
(paren
l_string|&quot;irq %d not available&bslash;n&quot;
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Steam powered scsi controllers run without an IRQ&n;&t;&t;&t;   anyway */
id|instance-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
)brace
id|boards
op_increment
suffix:semicolon
)brace
r_return
id|boards
suffix:semicolon
)brace
DECL|function|dmx3191d_info
r_const
r_char
op_star
id|dmx3191d_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_static
r_const
r_char
op_star
id|info
op_assign
l_string|&quot;Domex DMX3191D&quot;
suffix:semicolon
r_return
id|info
suffix:semicolon
)brace
DECL|function|dmx3191d_release_resources
r_int
id|dmx3191d_release_resources
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
id|release_region
c_func
(paren
id|instance-&gt;io_port
comma
id|DMX3191D_REGION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
(brace
id|free_irq
c_func
(paren
id|instance-&gt;irq
comma
id|instance
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|DMX3191D
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
