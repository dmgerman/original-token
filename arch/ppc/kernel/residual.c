multiline_comment|/*&n; * $Id: residual.c,v 1.2 1997/08/25 06:54:56 cort Exp $&n; *&n; * Code to deal with the PReP residual data.&n; *&n; * Written by: Cort Dougan (cort@cs.nmt.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ide.h&gt;
macro_line|#include &lt;asm/pnp.h&gt;
multiline_comment|/*&n; * Spit out some info about residual data&n; */
DECL|function|print_residual_device_info
r_void
id|print_residual_device_info
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_union
id|_PnP_TAG_PACKET
op_star
id|pkt
suffix:semicolon
id|PPC_DEVICE
op_star
id|dev
suffix:semicolon
DECL|macro|did
mdefine_line|#define did dev-&gt;DeviceId
multiline_comment|/* make sure we have residual data first */
r_if
c_cond
(paren
id|res.ResidualLength
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Residual: %ld devices&bslash;n&quot;
comma
id|res.ActualNumDevices
)paren
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
id|res.ActualNumDevices
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|res.Devices
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * pci devices&n;&t;&t; */
r_if
c_cond
(paren
id|did.BusId
op_amp
id|PCIDEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI Device:&quot;
)paren
suffix:semicolon
multiline_comment|/* unknown vendor */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;Unknown&quot;
comma
id|pci_strvendor
c_func
(paren
id|did.DevId
op_rshift
l_int|16
)paren
comma
l_int|7
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; id %08lx types %d/%d&quot;
comma
id|did.DevId
comma
id|did.BaseType
comma
id|did.SubType
)paren
suffix:semicolon
multiline_comment|/* known vendor */
r_else
id|printk
c_func
(paren
l_string|&quot; %s %s&quot;
comma
id|pci_strvendor
c_func
(paren
id|did.DevId
op_rshift
l_int|16
)paren
comma
id|pci_strdev
c_func
(paren
id|did.DevId
op_rshift
l_int|16
comma
id|did.DevId
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|did.BusId
op_amp
id|PNPISADEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; pnp:&quot;
)paren
suffix:semicolon
multiline_comment|/* get pnp info on the device */
id|pkt
op_assign
(paren
r_union
id|_PnP_TAG_PACKET
op_star
)paren
op_amp
id|res.DevicePnPHeap
(braket
id|dev-&gt;AllocatedOffset
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|pkt-&gt;S1_Pack.Tag
op_ne
id|DF_END_TAG
suffix:semicolon
id|pkt
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|pkt-&gt;S1_Pack.Tag
op_eq
id|S4_Packet
)paren
op_logical_or
(paren
id|pkt-&gt;S1_Pack.Tag
op_eq
id|S4_Packet_flags
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; irq %02x%02x&quot;
comma
id|pkt-&gt;S4_Pack.IRQMask
(braket
l_int|0
)braket
comma
id|pkt-&gt;S4_Pack.IRQMask
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * isa devices&n;&t;&t; */
r_if
c_cond
(paren
id|did.BusId
op_amp
id|ISADEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISA Device: basetype: %d subtype: %d&quot;
comma
id|did.BaseType
comma
id|did.SubType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * eisa devices&n;&t;&t; */
r_if
c_cond
(paren
id|did.BusId
op_amp
id|EISADEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;EISA Device: basetype: %d subtype: %d&quot;
comma
id|did.BaseType
comma
id|did.SubType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * proc bus devices&n;&t;&t; */
r_if
c_cond
(paren
id|did.BusId
op_amp
id|PROCESSORDEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ProcBus Device: basetype: %d subtype: %d&quot;
comma
id|did.BaseType
comma
id|did.SubType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * pcmcia devices&n;&t;&t; */
r_if
c_cond
(paren
id|did.BusId
op_amp
id|PCMCIADEVICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCMCIA Device: basetype: %d subtype: %d&quot;
comma
id|did.BaseType
comma
id|did.SubType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Unknown bus access device: busid %lx&bslash;n&quot;
comma
id|did.BusId
)paren
suffix:semicolon
)brace
)brace
eof
