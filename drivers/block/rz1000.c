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
DECL|function|ide_pci_access_error
r_static
r_void
id|ide_pci_access_error
(paren
r_int
id|rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide: pcibios access failed - %s&bslash;n&quot;
comma
id|pcibios_strerror
c_func
(paren
id|rc
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_rz1000
r_void
id|init_rz1000
(paren
id|byte
id|bus
comma
id|byte
id|fn
)paren
(brace
r_int
id|rc
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ide0: buggy RZ1000 interface: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
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
)paren
)paren
(brace
id|ide_pci_access_error
(paren
id|rc
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
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
l_string|&quot;not enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|pcibios_read_config_word
c_func
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
)paren
op_logical_or
(paren
id|rc
op_assign
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
)paren
(brace
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
id|ide_pci_access_error
(paren
id|rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;serialized, disabled unmasking&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;disabled read-ahead&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof