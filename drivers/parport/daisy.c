multiline_comment|/*&n; * IEEE 1284.3 Parallel port daisy chain and multiplexor code&n; * &n; * Copyright (C) 1999, 2000  Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * ??-12-1998: Initial implementation.&n; * 31-01-1999: Make port-cloning transparent.&n; * 13-02-1999: Move DeviceID technique from parport_probe.&n; * 13-03-1999: Get DeviceID from non-IEEE 1284.3 devices too.&n; * 22-02-2000: Count devices that are actually detected.&n; *&n; */
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG /* undef me for production */
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(stuff...) printk (stuff)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(stuff...)
macro_line|#endif
DECL|struct|daisydev
r_static
r_struct
id|daisydev
(brace
DECL|member|next
r_struct
id|daisydev
op_star
id|next
suffix:semicolon
DECL|member|port
r_struct
id|parport
op_star
id|port
suffix:semicolon
DECL|member|daisy
r_int
id|daisy
suffix:semicolon
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
DECL|variable|topology
)brace
op_star
id|topology
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|numdevs
r_static
r_int
id|numdevs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Forward-declaration of lower-level functions. */
r_static
r_int
id|mux_present
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|num_mux_ports
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|select_port
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|assign_addrs
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
multiline_comment|/* Add a device to the discovered topology. */
DECL|function|add_dev
r_static
r_void
id|add_dev
(paren
r_int
id|devnum
comma
r_struct
id|parport
op_star
id|port
comma
r_int
id|daisy
)paren
(brace
r_struct
id|daisydev
op_star
id|newdev
suffix:semicolon
id|newdev
op_assign
id|kmalloc
(paren
id|GFP_KERNEL
comma
r_sizeof
(paren
r_struct
id|daisydev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newdev
)paren
(brace
id|newdev-&gt;port
op_assign
id|port
suffix:semicolon
id|newdev-&gt;daisy
op_assign
id|daisy
suffix:semicolon
id|newdev-&gt;devnum
op_assign
id|devnum
suffix:semicolon
id|newdev-&gt;next
op_assign
id|topology
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|topology
op_logical_or
id|topology-&gt;devnum
op_ge
id|devnum
)paren
id|topology
op_assign
id|newdev
suffix:semicolon
r_else
(brace
r_struct
id|daisydev
op_star
id|prev
op_assign
id|topology
suffix:semicolon
r_while
c_loop
(paren
id|prev-&gt;next
op_logical_and
id|prev-&gt;next-&gt;devnum
OL
id|devnum
)paren
id|prev
op_assign
id|prev-&gt;next
suffix:semicolon
id|newdev-&gt;next
op_assign
id|prev-&gt;next
suffix:semicolon
id|prev-&gt;next
op_assign
id|newdev
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Clone a parport (actually, make an alias). */
DECL|function|clone_parport
r_static
r_struct
id|parport
op_star
id|clone_parport
(paren
r_struct
id|parport
op_star
id|real
comma
r_int
id|muxport
)paren
(brace
r_struct
id|parport
op_star
id|extra
op_assign
id|parport_register_port
(paren
id|real-&gt;base
comma
id|real-&gt;irq
comma
id|real-&gt;dma
comma
id|real-&gt;ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extra
)paren
(brace
id|extra-&gt;portnum
op_assign
id|real-&gt;portnum
suffix:semicolon
id|extra-&gt;physport
op_assign
id|real
suffix:semicolon
id|extra-&gt;muxport
op_assign
id|muxport
suffix:semicolon
)brace
r_return
id|extra
suffix:semicolon
)brace
multiline_comment|/* Discover the IEEE1284.3 topology on a port -- muxes and daisy chains.&n; * Return value is number of devices actually detected. */
DECL|function|parport_daisy_init
r_int
id|parport_daisy_init
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_int
id|detected
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|deviceid
suffix:semicolon
r_static
r_const
r_char
op_star
id|th
(braket
)braket
op_assign
(brace
multiline_comment|/*0*/
l_string|&quot;th&quot;
comma
l_string|&quot;st&quot;
comma
l_string|&quot;nd&quot;
comma
l_string|&quot;rd&quot;
comma
l_string|&quot;th&quot;
)brace
suffix:semicolon
r_int
id|num_ports
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Because this is called before any other devices exist,&n;&t; * we don&squot;t have to claim exclusive access.  */
multiline_comment|/* If mux present on normal port, need to create new&n;&t; * parports for each extra port. */
r_if
c_cond
(paren
id|port-&gt;muxport
OL
l_int|0
op_logical_and
id|mux_present
(paren
id|port
)paren
op_logical_and
multiline_comment|/* don&squot;t be fooled: a mux must have 2 or 4 ports. */
(paren
(paren
id|num_ports
op_assign
id|num_mux_ports
(paren
id|port
)paren
)paren
op_eq
l_int|2
op_logical_or
id|num_ports
op_eq
l_int|4
)paren
)paren
(brace
multiline_comment|/* Leave original as port zero. */
id|port-&gt;muxport
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: 1st (default) port of %d-way multiplexor&bslash;n&quot;
comma
id|port-&gt;name
comma
id|num_ports
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|num_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Clone the port. */
r_struct
id|parport
op_star
id|extra
op_assign
id|clone_parport
(paren
id|port
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|extra
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
id|schedule
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: %d%s port of %d-way multiplexor on %s&bslash;n&quot;
comma
id|extra-&gt;name
comma
id|i
op_plus
l_int|1
comma
id|th
(braket
id|i
op_plus
l_int|1
)braket
comma
id|num_ports
comma
id|port-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Analyse that port too.  We won&squot;t recurse&n;&t;&t;&t;   forever because of the &squot;port-&gt;muxport &lt; 0&squot;&n;&t;&t;&t;   test above. */
id|parport_announce_port
(paren
id|extra
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|port-&gt;muxport
op_ge
l_int|0
)paren
id|select_port
(paren
id|port
)paren
suffix:semicolon
id|parport_daisy_deselect_all
(paren
id|port
)paren
suffix:semicolon
id|detected
op_add_assign
id|assign_addrs
(paren
id|port
)paren
suffix:semicolon
multiline_comment|/* Count the potential legacy device at the end. */
id|add_dev
(paren
id|numdevs
op_increment
comma
id|port
comma
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Find out the legacy device&squot;s IEEE 1284 device ID. */
id|deviceid
op_assign
id|kmalloc
(paren
l_int|1000
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deviceid
)paren
(brace
r_if
c_cond
(paren
id|parport_device_id
(paren
id|numdevs
op_minus
l_int|1
comma
id|deviceid
comma
l_int|1000
)paren
OG
l_int|2
)paren
id|detected
op_increment
suffix:semicolon
id|kfree
(paren
id|deviceid
)paren
suffix:semicolon
)brace
r_return
id|detected
suffix:semicolon
)brace
multiline_comment|/* Forget about devices on a physical port. */
DECL|function|parport_daisy_fini
r_void
id|parport_daisy_fini
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|daisydev
op_star
id|dev
comma
op_star
id|prev
op_assign
id|topology
suffix:semicolon
r_while
c_loop
(paren
id|prev
op_logical_and
id|prev-&gt;port
op_eq
id|port
)paren
(brace
id|topology
op_assign
id|topology-&gt;next
suffix:semicolon
id|kfree
(paren
id|prev
)paren
suffix:semicolon
id|prev
op_assign
id|topology
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev
)paren
(brace
id|dev
op_assign
id|prev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_logical_and
id|dev-&gt;port
op_eq
id|port
)paren
(brace
id|prev-&gt;next
op_assign
id|dev-&gt;next
suffix:semicolon
id|kfree
(paren
id|dev
)paren
suffix:semicolon
)brace
id|prev
op_assign
id|prev-&gt;next
suffix:semicolon
)brace
multiline_comment|/* Gaps in the numbering could be handled better.  How should&n;           someone enumerate through all IEEE1284.3 devices in the&n;           topology?. */
r_if
c_cond
(paren
op_logical_neg
id|topology
)paren
id|numdevs
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Find a device by canonical device number. */
DECL|function|parport_open
r_struct
id|pardevice
op_star
id|parport_open
(paren
r_int
id|devnum
comma
r_const
r_char
op_star
id|name
comma
r_int
(paren
op_star
id|pf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|kf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|irqf
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|flags
comma
r_void
op_star
id|handle
)paren
(brace
r_struct
id|parport
op_star
id|port
op_assign
id|parport_enumerate
(paren
)paren
suffix:semicolon
r_struct
id|pardevice
op_star
id|dev
suffix:semicolon
r_int
id|portnum
suffix:semicolon
r_int
id|muxnum
suffix:semicolon
r_int
id|daisynum
suffix:semicolon
r_if
c_cond
(paren
id|parport_device_coords
(paren
id|devnum
comma
op_amp
id|portnum
comma
op_amp
id|muxnum
comma
op_amp
id|daisynum
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|port
op_logical_and
(paren
(paren
id|port-&gt;portnum
op_ne
id|portnum
)paren
op_logical_or
(paren
id|port-&gt;muxport
op_ne
id|muxnum
)paren
)paren
)paren
id|port
op_assign
id|port-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
multiline_comment|/* No corresponding parport. */
r_return
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|parport_register_device
(paren
id|port
comma
id|name
comma
id|pf
comma
id|kf
comma
id|irqf
comma
id|flags
comma
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|dev-&gt;daisy
op_assign
id|daisynum
suffix:semicolon
multiline_comment|/* Check that there really is a device to select. */
r_if
c_cond
(paren
id|daisynum
op_ge
l_int|0
)paren
(brace
r_int
id|selected
suffix:semicolon
id|parport_claim_or_block
(paren
id|dev
)paren
suffix:semicolon
id|selected
op_assign
id|port-&gt;daisy
suffix:semicolon
id|parport_release
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|selected
op_ne
id|port-&gt;daisy
)paren
(brace
multiline_comment|/* No corresponding device. */
id|parport_unregister_device
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/* The converse of parport_open. */
DECL|function|parport_close
r_void
id|parport_close
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
(brace
id|parport_unregister_device
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert device coordinates into a canonical device number. */
DECL|function|parport_device_num
r_int
id|parport_device_num
(paren
r_int
id|parport
comma
r_int
id|mux
comma
r_int
id|daisy
)paren
(brace
r_struct
id|daisydev
op_star
id|dev
op_assign
id|topology
suffix:semicolon
r_while
c_loop
(paren
id|dev
op_logical_and
id|dev-&gt;port-&gt;portnum
op_ne
id|parport
op_logical_and
id|dev-&gt;port-&gt;muxport
op_ne
id|mux
op_logical_and
id|dev-&gt;daisy
op_ne
id|daisy
)paren
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|dev-&gt;devnum
suffix:semicolon
)brace
multiline_comment|/* Convert a canonical device number into device coordinates. */
DECL|function|parport_device_coords
r_int
id|parport_device_coords
(paren
r_int
id|devnum
comma
r_int
op_star
id|parport
comma
r_int
op_star
id|mux
comma
r_int
op_star
id|daisy
)paren
(brace
r_struct
id|daisydev
op_star
id|dev
op_assign
id|topology
suffix:semicolon
r_while
c_loop
(paren
id|dev
op_logical_and
id|dev-&gt;devnum
op_ne
id|devnum
)paren
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|parport
)paren
op_star
id|parport
op_assign
id|dev-&gt;port-&gt;portnum
suffix:semicolon
r_if
c_cond
(paren
id|mux
)paren
op_star
id|mux
op_assign
id|dev-&gt;port-&gt;muxport
suffix:semicolon
r_if
c_cond
(paren
id|daisy
)paren
op_star
id|daisy
op_assign
id|dev-&gt;daisy
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Send a daisy-chain-style CPP command packet. */
DECL|function|cpp_daisy
r_static
r_int
id|cpp_daisy
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
id|cmd
)paren
(brace
r_int
r_char
id|s
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xaa
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x55
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x00
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xff
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
op_amp
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
)paren
(brace
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: cpp_daisy: aa5500ff(%02x)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|s
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|parport_write_data
(paren
id|port
comma
l_int|0x87
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
op_amp
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
(paren
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
)paren
(brace
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: cpp_daisy: aa5500ff87(%02x)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|s
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|parport_write_data
(paren
id|port
comma
l_int|0x78
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
id|cmd
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_frob_control
(paren
id|port
comma
id|PARPORT_CONTROL_STROBE
comma
id|PARPORT_CONTROL_STROBE
)paren
suffix:semicolon
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
id|parport_frob_control
(paren
id|port
comma
id|PARPORT_CONTROL_STROBE
comma
l_int|0
)paren
suffix:semicolon
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xff
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* Send a mux-style CPP command packet. */
DECL|function|cpp_mux
r_static
r_int
id|cpp_mux
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
id|cmd
)paren
(brace
r_int
r_char
id|s
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xaa
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x55
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xf0
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x0f
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x52
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xad
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
id|cmd
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s
op_amp
id|PARPORT_STATUS_ACK
)paren
)paren
(brace
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: cpp_mux: aa55f00f52ad%02x(%02x)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|cmd
comma
id|s
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|rc
op_assign
(paren
(paren
(paren
id|s
op_amp
id|PARPORT_STATUS_SELECT
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_lshift
l_int|0
)paren
op_or
(paren
(paren
id|s
op_amp
id|PARPORT_STATUS_PAPEROUT
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|s
op_amp
id|PARPORT_STATUS_BUSY
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|s
op_amp
id|PARPORT_STATUS_ERROR
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|parport_daisy_deselect_all
r_void
id|parport_daisy_deselect_all
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
id|cpp_daisy
(paren
id|port
comma
l_int|0x30
)paren
suffix:semicolon
)brace
DECL|function|parport_daisy_select
r_int
id|parport_daisy_select
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
id|daisy
comma
r_int
id|mode
)paren
(brace
multiline_comment|/* mode is currently ignored. FIXME? */
r_return
id|cpp_daisy
(paren
id|port
comma
l_int|0xe0
op_plus
id|daisy
)paren
op_amp
id|PARPORT_STATUS_ERROR
suffix:semicolon
)brace
DECL|function|mux_present
r_static
r_int
id|mux_present
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_return
id|cpp_mux
(paren
id|port
comma
l_int|0x51
)paren
op_eq
l_int|3
suffix:semicolon
)brace
DECL|function|num_mux_ports
r_static
r_int
id|num_mux_ports
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_return
id|cpp_mux
(paren
id|port
comma
l_int|0x58
)paren
suffix:semicolon
)brace
DECL|function|select_port
r_static
r_int
id|select_port
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_int
id|muxport
op_assign
id|port-&gt;muxport
suffix:semicolon
r_return
id|cpp_mux
(paren
id|port
comma
l_int|0x60
op_plus
id|muxport
)paren
op_eq
id|muxport
suffix:semicolon
)brace
DECL|function|assign_addrs
r_static
r_int
id|assign_addrs
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_int
r_char
id|s
comma
id|last_dev
suffix:semicolon
r_int
r_char
id|daisy
suffix:semicolon
r_int
id|thisdev
op_assign
id|numdevs
suffix:semicolon
r_char
op_star
id|deviceid
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xaa
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x55
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0x00
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
l_int|0xff
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
op_amp
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
)paren
(brace
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: assign_addrs: aa5500ff(%02x)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|parport_write_data
(paren
id|port
comma
l_int|0x87
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|s
op_assign
id|parport_read_status
(paren
id|port
)paren
op_amp
(paren
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_PAPEROUT
op_or
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
(paren
id|PARPORT_STATUS_SELECT
op_or
id|PARPORT_STATUS_ERROR
)paren
)paren
(brace
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: assign_addrs: aa5500ff87(%02x)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|parport_write_data
(paren
id|port
comma
l_int|0x78
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|last_dev
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We&squot;ve just been speaking to a device, so we&n;&t;&t;&t; know there must be at least _one_ out there. */
r_for
c_loop
(paren
id|daisy
op_assign
l_int|0
suffix:semicolon
id|daisy
OL
l_int|4
suffix:semicolon
id|daisy
op_increment
)paren
(brace
id|parport_write_data
(paren
id|port
comma
id|daisy
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|parport_frob_control
(paren
id|port
comma
id|PARPORT_CONTROL_STROBE
comma
id|PARPORT_CONTROL_STROBE
)paren
suffix:semicolon
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
id|parport_frob_control
(paren
id|port
comma
id|PARPORT_CONTROL_STROBE
comma
l_int|0
)paren
suffix:semicolon
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_dev
)paren
multiline_comment|/* No more devices. */
r_break
suffix:semicolon
id|last_dev
op_assign
op_logical_neg
(paren
id|parport_read_status
(paren
id|port
)paren
op_amp
id|PARPORT_STATUS_BUSY
)paren
suffix:semicolon
id|add_dev
(paren
id|numdevs
op_increment
comma
id|port
comma
id|daisy
)paren
suffix:semicolon
)brace
id|parport_write_data
(paren
id|port
comma
l_int|0xff
)paren
suffix:semicolon
id|udelay
(paren
l_int|2
)paren
suffix:semicolon
id|DPRINTK
(paren
id|KERN_DEBUG
l_string|&quot;%s: Found %d daisy-chained devices&bslash;n&quot;
comma
id|port-&gt;name
comma
id|numdevs
op_minus
id|thisdev
)paren
suffix:semicolon
multiline_comment|/* Ask the new devices to introduce themselves. */
id|deviceid
op_assign
id|kmalloc
(paren
l_int|1000
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|deviceid
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|daisy
op_assign
l_int|0
suffix:semicolon
id|thisdev
OL
id|numdevs
suffix:semicolon
id|thisdev
op_increment
comma
id|daisy
op_increment
)paren
id|parport_device_id
(paren
id|thisdev
comma
id|deviceid
comma
l_int|1000
)paren
suffix:semicolon
id|kfree
(paren
id|deviceid
)paren
suffix:semicolon
r_return
id|numdevs
op_minus
id|thisdev
suffix:semicolon
)brace
multiline_comment|/* Find a device with a particular manufacturer and model string,&n;   starting from a given device number.  Like the PCI equivalent,&n;   &squot;from&squot; itself is skipped. */
DECL|function|parport_find_device
r_int
id|parport_find_device
(paren
r_const
r_char
op_star
id|mfg
comma
r_const
r_char
op_star
id|mdl
comma
r_int
id|from
)paren
(brace
r_struct
id|daisydev
op_star
id|d
op_assign
id|topology
suffix:semicolon
multiline_comment|/* sorted by devnum */
multiline_comment|/* Find where to start. */
r_while
c_loop
(paren
id|d
op_logical_and
id|d-&gt;devnum
op_le
id|from
)paren
id|d
op_assign
id|d-&gt;next
suffix:semicolon
multiline_comment|/* Search. */
r_while
c_loop
(paren
id|d
)paren
(brace
r_struct
id|parport_device_info
op_star
id|info
suffix:semicolon
id|info
op_assign
op_amp
id|d-&gt;port-&gt;probe_info
(braket
l_int|1
op_plus
id|d-&gt;daisy
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|mfg
op_logical_or
op_logical_neg
id|strcmp
(paren
id|mfg
comma
id|info-&gt;mfr
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|mdl
op_logical_or
op_logical_neg
id|strcmp
(paren
id|mdl
comma
id|info-&gt;model
)paren
)paren
)paren
r_break
suffix:semicolon
id|d
op_assign
id|d-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
)paren
r_return
id|d-&gt;devnum
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Find a device in a particular class.  Like the PCI equivalent,&n;   &squot;from&squot; itself is skipped. */
DECL|function|parport_find_class
r_int
id|parport_find_class
(paren
id|parport_device_class
id|cls
comma
r_int
id|from
)paren
(brace
r_struct
id|daisydev
op_star
id|d
op_assign
id|topology
suffix:semicolon
multiline_comment|/* sorted by devnum */
multiline_comment|/* Find where to start. */
r_while
c_loop
(paren
id|d
op_logical_and
id|d-&gt;devnum
op_le
id|from
)paren
id|d
op_assign
id|d-&gt;next
suffix:semicolon
multiline_comment|/* Search. */
r_while
c_loop
(paren
id|d
op_logical_and
id|d-&gt;port-&gt;probe_info
(braket
l_int|1
op_plus
id|d-&gt;daisy
)braket
dot
r_class
op_ne
id|cls
)paren
id|d
op_assign
id|d-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|d
)paren
r_return
id|d-&gt;devnum
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof
