macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;ide.h&quot;
macro_line|#include &quot;ide_modes.h&quot;
DECL|function|ide_init_sl82c105
r_void
id|ide_init_sl82c105
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|t16
suffix:semicolon
r_int
r_int
id|t32
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|t16
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SL82C105 command word: %x&bslash;n&quot;
comma
id|t16
)paren
suffix:semicolon
id|t16
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|t16
)paren
suffix:semicolon
multiline_comment|/* IDE timing */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|t32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IDE timing: %08x, resetting to PIO0 timing&bslash;n&quot;
comma
id|t32
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x44
comma
l_int|0x03e4
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|t32
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IDE control/status register: %08x&bslash;n&quot;
comma
id|t32
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x10ff08a1
)paren
suffix:semicolon
)brace
eof
