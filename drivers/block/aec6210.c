multiline_comment|/*&n; * linux/drivers/block/aec6210.c&t;&t;Version 0.01&t;Nov 17, 1998&n; *&n; * Copyright (C) 1998-99&t;Andre Hedrick&n; *&n; *  pio 0 ::       40: 00 07 00 00 00 00 00 00 02 07 a6 04 00 02 00 02&n; *  pio 1 ::       40: 0a 07 00 00 00 00 00 00 02 07 a6 05 00 02 00 02&n; *  pio 2 ::       40: 08 07 00 00 00 00 00 00 02 07 a6 05 00 02 00 02&n; *  pio 3 ::       40: 03 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *  pio 4 ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *  dma 0 ::       40: 0a 07 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *  dma 1 ::       40: 02 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *  dma 2 ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *                 50: ff ff ff ff 00 06 04 00 00 00 00 00 00 00 00 00&n; *&n; * udma 0 ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *                 50: ff ff ff ff 01 06 04 00 00 00 00 00 00 00 00 00&n; *&n; * udma 1 ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *                 50: ff ff ff ff 01 06 04 00 00 00 00 00 00 00 00 00&n; *&n; * udma 2 ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *                 50: ff ff ff ff 02 06 04 00 00 00 00 00 00 00 00 00&n; *&n; * auto   ::       40: 01 04 00 00 00 00 00 00 02 05 a6 05 00 02 00 02&n; *                 50: ff ff ff ff 02 06 04 00 00 00 00 00 00 00 00 00&n; *&n; * auto   ::       40: 01 04 01 04 01 04 01 04 02 05 a6 cf 00 02 00 02&n; *                 50: ff ff ff ff aa 06 04 00 00 00 00 00 00 00 00 00&n; *&n; *                 NO-Devices&n; *                 40: 00 00 00 00 00 00 00 00 02 05 a6 00 00 02 00 02&n; *                 50: ff ff ff ff 00 06 00 00 00 00 00 00 00 00 00 00&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|pci_init_aec6210
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;rom_address
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
id|dev-&gt;rom_address
op_or
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: ROM enabled at 0x%08lx&bslash;n&quot;
comma
id|name
comma
id|dev-&gt;rom_address
)paren
suffix:semicolon
)brace
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
eof
