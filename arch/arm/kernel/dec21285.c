multiline_comment|/*&n; * arch/arm/kernel/dec21285.c: PCI functions for DC21285&n; *&n; * Copyright (C) 1998-1999 Russell King, Phil Blundell&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/dec21285.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;bios32.h&quot;
DECL|macro|MAX_SLOTS
mdefine_line|#define MAX_SLOTS&t;&t;21
r_extern
r_int
id|setup_arm_irq
c_func
(paren
r_int
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_report_device_errors
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
r_int
DECL|function|dc21285_base_address
id|dc21285_base_address
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
)paren
(brace
r_int
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|devfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
l_int|0
)paren
id|addr
op_assign
id|PCICFG1_BASE
op_or
(paren
id|dev-&gt;bus-&gt;number
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|devfn
OL
id|PCI_DEVFN
c_func
(paren
id|MAX_SLOTS
comma
l_int|0
)paren
)paren
id|addr
op_assign
id|PCICFG0_BASE
op_or
l_int|0xc00000
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_read_config_byte
id|dc21285_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|u8
id|v
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;ldr%?b&t;%0, [%1, %2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_else
id|v
op_assign
l_int|0xff
suffix:semicolon
op_star
id|value
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_read_config_word
id|dc21285_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|u16
id|v
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;ldr%?h&t;%0, [%1, %2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_else
id|v
op_assign
l_int|0xffff
suffix:semicolon
op_star
id|value
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_read_config_dword
id|dc21285_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|u32
id|v
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;ldr%?&t;%0, [%1, %2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_else
id|v
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
id|value
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_write_config_byte
id|dc21285_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;str%?b&t;%0, [%1, %2]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_write_config_word
id|dc21285_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;str%?h&t;%0, [%1, %2]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|dc21285_write_config_dword
id|dc21285_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|dc21285_base_address
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|asm
c_func
(paren
l_string|&quot;str%?&t;%0, [%1, %2]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|dc21285_ops
r_static
r_struct
id|pci_ops
id|dc21285_ops
op_assign
(brace
id|dc21285_read_config_byte
comma
id|dc21285_read_config_word
comma
id|dc21285_read_config_dword
comma
id|dc21285_write_config_byte
comma
id|dc21285_write_config_word
comma
id|dc21285_write_config_dword
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Warn on PCI errors.&n; */
r_static
r_void
DECL|function|dc21285_error
id|dc21285_error
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
r_int
id|next_warn
suffix:semicolon
r_int
r_int
id|cmd
op_assign
op_star
id|CSR_PCICMD
op_amp
l_int|0x0000ffff
suffix:semicolon
r_int
r_int
id|ctrl
op_assign
(paren
op_star
id|CSR_SA110_CNTL
)paren
op_amp
l_int|0xffffde07
suffix:semicolon
r_int
r_int
id|irqstatus
op_assign
op_star
id|CSR_IRQ_RAWSTATUS
suffix:semicolon
r_int
id|warn
op_assign
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|next_warn
)paren
suffix:semicolon
id|ctrl
op_or_assign
id|SA110_CNTL_DISCARDTIMER
suffix:semicolon
r_if
c_cond
(paren
id|warn
)paren
(brace
id|next_warn
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: &quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;parity error &quot;
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|1
op_lshift
l_int|31
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|30
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;target abort &quot;
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|1
op_lshift
l_int|28
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;master abort &quot;
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|1
op_lshift
l_int|29
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|28
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;data parity error &quot;
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|1
op_lshift
l_int|24
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;discard timer expired &quot;
)paren
suffix:semicolon
id|ctrl
op_and_assign
op_complement
id|SA110_CNTL_DISCARDTIMER
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqstatus
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;system error &quot;
)paren
suffix:semicolon
id|ctrl
op_or_assign
id|SA110_CNTL_RXSERR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;pc=[&lt;%08lX&gt;]&bslash;n&quot;
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|pcibios_report_device_errors
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_PCICMD
op_assign
id|cmd
suffix:semicolon
op_star
id|CSR_SA110_CNTL
op_assign
id|ctrl
suffix:semicolon
)brace
DECL|variable|dc21285_error_action
r_static
r_struct
id|irqaction
id|dc21285_error_action
op_assign
(brace
id|dc21285_error
comma
id|SA_INTERRUPT
comma
l_int|0
comma
l_string|&quot;PCI error&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|dc21285_init
r_void
id|__init
id|dc21285_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mem_size
suffix:semicolon
r_int
r_int
id|cntl
suffix:semicolon
id|mem_size
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|PAGE_OFFSET
suffix:semicolon
op_star
id|CSR_SDRAMBASEMASK
op_assign
(paren
id|mem_size
op_minus
l_int|1
)paren
op_amp
l_int|0x0ffc0000
suffix:semicolon
op_star
id|CSR_SDRAMBASEOFFSET
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_ROMBASEMASK
op_assign
l_int|0x80000000
suffix:semicolon
op_star
id|CSR_CSRBASEMASK
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_CSRBASEOFFSET
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_PCIADDR_EXTN
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_HOST_FOOTBRIDGE
multiline_comment|/*&n;&t; * Map our SDRAM at a known address in PCI space, just in case&n;&t; * the firmware had other ideas.  Using a nonzero base is&n;&t; * necessary, since some VGA cards forcefully use PCI addresses&n;&t; * in the range 0x000a0000 to 0x000c0000. (eg, S3 cards).&n;&t; */
op_star
id|CSR_PCICACHELINESIZE
op_assign
l_int|0x00002008
suffix:semicolon
op_star
id|CSR_PCICSRBASE
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_PCICSRIOBASE
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_PCISDRAMBASE
op_assign
id|virt_to_bus
c_func
(paren
(paren
r_void
op_star
)paren
id|PAGE_OFFSET
)paren
suffix:semicolon
op_star
id|CSR_PCIROMBASE
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_PCICMD
op_assign
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_FAST_BACK
op_or
id|PCI_COMMAND_INVALIDATE
op_or
id|PCI_COMMAND_PARITY
op_or
(paren
l_int|1
op_lshift
l_int|31
)paren
op_or
(paren
l_int|1
op_lshift
l_int|29
)paren
op_or
(paren
l_int|1
op_lshift
l_int|28
)paren
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: DC21285 footbridge, revision %02lX&bslash;n&quot;
comma
op_star
id|CSR_CLASSREV
op_amp
l_int|0xff
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|dc21285_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear any existing errors - we aren&squot;t&n;&t; * interested in historical data...&n;&t; */
id|cntl
op_assign
op_star
id|CSR_SA110_CNTL
op_amp
l_int|0xffffde07
suffix:semicolon
op_star
id|CSR_SA110_CNTL
op_assign
id|cntl
op_or
id|SA110_CNTL_RXSERR
suffix:semicolon
id|cntl
op_assign
op_star
id|CSR_PCICMD
op_amp
l_int|0x0000ffff
suffix:semicolon
op_star
id|CSR_PCICMD
op_assign
id|cntl
op_or
l_int|1
op_lshift
l_int|31
op_or
l_int|1
op_lshift
l_int|29
op_or
l_int|1
op_lshift
l_int|28
op_or
l_int|1
op_lshift
l_int|24
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise PCI error IRQ after we&squot;ve finished probing&n;&t; */
id|setup_arm_irq
c_func
(paren
id|IRQ_PCI_ERR
comma
op_amp
id|dc21285_error_action
)paren
suffix:semicolon
)brace
eof
