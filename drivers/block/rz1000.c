multiline_comment|/*&n; *  linux/drivers/block/rz1000.c&t;Version 0.03  Mar 20, 1996&n; *&n; *  Copyright (C) 1995-1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author/Maintainer:  mlord@pobox.com (Mark Lord)&n; *&n; *  This file provides support for disabling the buggy read-ahead&n; *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;ide.h&quot;
DECL|function|init_rz1000
r_static
r_void
id|init_rz1000
(paren
id|byte
id|bus
comma
id|byte
id|fn
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|reg
comma
id|h
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: buggy IDE controller: &quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcibios_read_config_word
(paren
id|bus
comma
id|fn
comma
id|PCI_COMMAND
comma
op_amp
id|reg
)paren
op_logical_and
op_logical_neg
(paren
id|reg
op_amp
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;disabled (BIOS)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pcibios_read_config_word
(paren
id|bus
comma
id|fn
comma
l_int|0x40
comma
op_amp
id|reg
)paren
op_logical_and
op_logical_neg
id|pcibios_write_config_word
c_func
(paren
id|bus
comma
id|fn
comma
l_int|0x40
comma
id|reg
op_amp
l_int|0xdfff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;disabled read-ahead&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|MAX_HWIFS
suffix:semicolon
op_increment
id|h
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|h
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
l_int|0x1f0
op_logical_or
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
l_int|0x170
)paren
op_logical_and
(paren
id|hwif-&gt;chipset
op_eq
id|ide_unknown
op_logical_or
id|hwif-&gt;chipset
op_eq
id|ide_generic
)paren
)paren
(brace
id|hwif-&gt;chipset
op_assign
id|ide_rz1000
suffix:semicolon
id|hwif-&gt;serialized
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  %s: serialized, disabled unmasking&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|ide_probe_for_rz100x
r_void
id|ide_probe_for_rz100x
(paren
r_void
)paren
(brace
id|byte
id|index
comma
id|bus
comma
id|fn
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|pcibios_find_device
(paren
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1000
comma
id|index
comma
op_amp
id|bus
comma
op_amp
id|fn
)paren
suffix:semicolon
op_increment
id|index
)paren
id|init_rz1000
(paren
id|bus
comma
id|fn
comma
l_string|&quot;RZ1000&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|pcibios_find_device
(paren
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1001
comma
id|index
comma
op_amp
id|bus
comma
op_amp
id|fn
)paren
suffix:semicolon
op_increment
id|index
)paren
id|init_rz1000
(paren
id|bus
comma
id|fn
comma
l_string|&quot;RZ1001&quot;
)paren
suffix:semicolon
)brace
eof
