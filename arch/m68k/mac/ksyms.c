macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
multiline_comment|/* Hook for mouse driver */
r_extern
r_void
(paren
op_star
id|mac_mouse_interrupt_hook
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|variable|mac_mouse_interrupt_hook
id|EXPORT_SYMBOL
c_func
(paren
id|mac_mouse_interrupt_hook
)paren
suffix:semicolon
macro_line|#if CONFIG_PCI
DECL|variable|pci_devices
id|EXPORT_SYMBOL
c_func
(paren
id|pci_devices
)paren
suffix:semicolon
macro_line|#endif
eof
