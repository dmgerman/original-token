multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_pyxis.c&n; *&n; * Based on code written by David A Rusling (david.rusling@reo.mts.dec.com).&n; *&n; * Code common to all PYXIS core logic chips.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_pyxis.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/* NOTE: Herein are back-to-back mb instructions.  They are magic.&n;   One plausible explanation is that the I/O controller does not properly&n;   handle the system transaction.  Another involves timing.  Ho hum.  */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CNF
macro_line|# define DBG_CNF(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CNF
macro_line|# define DBG_CNF(args)
macro_line|#endif
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address and setup the PYXIS_HAXR2 register&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., SCSI and Ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
r_static
r_int
DECL|function|mk_conf_addr
id|mk_conf_addr
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
r_int
r_int
op_star
id|pci_addr
comma
r_int
r_char
op_star
id|type1
)paren
(brace
id|u8
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|u8
id|device_fn
op_assign
id|dev-&gt;devfn
suffix:semicolon
op_star
id|type1
op_assign
(paren
id|bus
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
op_star
id|pci_addr
op_assign
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|device_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|where
)paren
suffix:semicolon
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x,&quot;
l_string|&quot; returning address 0x%p&bslash;n&quot;
id|bus
comma
id|device_fn
comma
id|where
comma
op_star
id|pci_addr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|conf_read
id|conf_read
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_char
id|type1
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|stat0
comma
id|value
comma
id|temp
suffix:semicolon
r_int
r_int
id|pyxis_cfg
op_assign
l_int|0
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* avoid getting hit by machine check */
multiline_comment|/* Reset status register to avoid losing errors.  */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/* If Type1 access, must set PYXIS CFG.  */
r_if
c_cond
(paren
id|type1
)paren
(brace
id|pyxis_cfg
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
op_assign
(paren
id|pyxis_cfg
op_amp
op_complement
l_int|3L
)paren
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|mcheck_expected
c_func
(paren
l_int|0
)paren
op_assign
l_int|1
suffix:semicolon
id|mcheck_taken
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Access configuration space.  */
id|value
op_assign
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* magic */
r_if
c_cond
(paren
id|mcheck_taken
c_func
(paren
l_int|0
)paren
)paren
(brace
id|mcheck_taken
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|value
op_assign
l_int|0xffffffffU
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
id|mcheck_expected
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If Type1 access, must reset IOC CFG so normal IO space ops work.  */
r_if
c_cond
(paren
id|type1
)paren
(brace
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
op_assign
id|pyxis_cfg
op_amp
op_complement
l_int|3L
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;conf_read(addr=0x%lx, type1=%d) = %#x&bslash;n&quot;
comma
id|addr
comma
id|type1
comma
id|value
)paren
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
r_static
r_void
DECL|function|conf_write
id|conf_write
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|value
comma
r_int
r_char
id|type1
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|stat0
comma
id|temp
suffix:semicolon
r_int
r_int
id|pyxis_cfg
op_assign
l_int|0
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* avoid getting hit by machine check */
multiline_comment|/* Reset status register to avoid losing errors.  */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/* If Type1 access, must set PYXIS CFG.  */
r_if
c_cond
(paren
id|type1
)paren
(brace
id|pyxis_cfg
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
op_assign
(paren
id|pyxis_cfg
op_amp
op_complement
l_int|3L
)paren
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|mcheck_expected
c_func
(paren
l_int|0
)paren
op_assign
l_int|1
suffix:semicolon
id|mcheck_taken
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Access configuration space.  */
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|value
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
multiline_comment|/* read back to force the write */
id|mcheck_expected
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If Type1 access, must reset IOC CFG so normal IO space ops work.  */
r_if
c_cond
(paren
id|type1
)paren
(brace
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
op_assign
id|pyxis_cfg
op_amp
op_complement
l_int|3L
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;conf_write(addr=%#lx, value=%#x, type1=%d)&bslash;n&quot;
comma
id|addr
comma
id|value
comma
id|type1
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_read_config_byte
id|pyxis_read_config_byte
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
comma
id|pci_addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|pci_addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x00
op_plus
id|PYXIS_CONF
suffix:semicolon
op_star
id|value
op_assign
id|conf_read
c_func
(paren
id|addr
comma
id|type1
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_read_config_word
id|pyxis_read_config_word
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
comma
id|pci_addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|pci_addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x08
op_plus
id|PYXIS_CONF
suffix:semicolon
op_star
id|value
op_assign
id|conf_read
c_func
(paren
id|addr
comma
id|type1
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_read_config_dword
id|pyxis_read_config_dword
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
comma
id|pci_addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|pci_addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x18
op_plus
id|PYXIS_CONF
suffix:semicolon
op_star
id|value
op_assign
id|conf_read
c_func
(paren
id|addr
comma
id|type1
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_write_config
id|pyxis_write_config
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
comma
r_int
id|mask
)paren
(brace
r_int
r_int
id|addr
comma
id|pci_addr
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|dev
comma
id|where
comma
op_amp
id|pci_addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
id|mask
op_plus
id|PYXIS_CONF
suffix:semicolon
id|conf_write
c_func
(paren
id|addr
comma
id|value
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
)paren
comma
id|type1
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_write_config_byte
id|pyxis_write_config_byte
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
r_return
id|pyxis_write_config
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|0x00
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_write_config_word
id|pyxis_write_config_word
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
r_return
id|pyxis_write_config
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|0x08
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_write_config_dword
id|pyxis_write_config_dword
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
r_return
id|pyxis_write_config
c_func
(paren
id|dev
comma
id|where
comma
id|value
comma
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|variable|pyxis_pci_ops
r_struct
id|pci_ops
id|pyxis_pci_ops
op_assign
(brace
id|read_byte
suffix:colon
id|pyxis_read_config_byte
comma
id|read_word
suffix:colon
id|pyxis_read_config_word
comma
id|read_dword
suffix:colon
id|pyxis_read_config_dword
comma
id|write_byte
suffix:colon
id|pyxis_write_config_byte
comma
id|write_word
suffix:colon
id|pyxis_write_config_word
comma
id|write_dword
suffix:colon
id|pyxis_write_config_dword
)brace
suffix:semicolon
"&f;"
multiline_comment|/* Note mask bit is true for ENABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
suffix:semicolon
r_static
r_inline
r_void
DECL|function|pyxis_update_irq_hw
id|pyxis_update_irq_hw
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
op_assign
id|mask
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pyxis_enable_irq
id|pyxis_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|pyxis_update_irq_hw
c_func
(paren
id|cached_irq_mask
op_or_assign
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pyxis_disable_irq
id|pyxis_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|pyxis_update_irq_hw
c_func
(paren
id|cached_irq_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|pyxis_startup_irq
id|pyxis_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|pyxis_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pyxis_mask_and_ack_irq
id|pyxis_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|bit
op_assign
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|cached_irq_mask
op_and_assign
op_complement
id|bit
suffix:semicolon
multiline_comment|/* Disable the interrupt.  */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
op_assign
id|mask
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ack PYXIS PCI interrupt.  */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_REQ
op_assign
id|bit
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Re-read to force both writes.  */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
suffix:semicolon
)brace
DECL|variable|pyxis_irq_type
r_static
r_struct
id|hw_interrupt_type
id|pyxis_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;PYXIS&quot;
comma
id|startup
suffix:colon
id|pyxis_startup_irq
comma
id|shutdown
suffix:colon
id|pyxis_disable_irq
comma
id|enable
suffix:colon
id|pyxis_enable_irq
comma
id|disable
suffix:colon
id|pyxis_disable_irq
comma
id|ack
suffix:colon
id|pyxis_mask_and_ack_irq
comma
id|end
suffix:colon
id|pyxis_enable_irq
comma
)brace
suffix:semicolon
r_void
DECL|function|pyxis_device_interrupt
id|pyxis_device_interrupt
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary register of PYXIS */
id|pld
op_assign
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_REQ
suffix:semicolon
id|pld
op_and_assign
id|cached_irq_mask
suffix:semicolon
multiline_comment|/*&n;&t; * Now for every possible bit set, work through them and call&n;&t; * the appropriate interrupt handler.&n;&t; */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|7
)paren
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
r_else
id|handle_irq
c_func
(paren
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|init_pyxis_irqs
id|init_pyxis_irqs
c_func
(paren
r_int
r_int
id|ignore_mask
)paren
(brace
r_int
id|i
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable all */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_REQ
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* flush all */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Send -INTA pulses to clear any pending interrupts ...*/
op_star
(paren
id|vuip
)paren
id|PYXIS_IACK_SC
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|48
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
(paren
id|ignore_mask
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
r_continue
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|pyxis_irq_type
suffix:semicolon
)brace
id|setup_irq
c_func
(paren
l_int|16
op_plus
l_int|7
comma
op_amp
id|isa_cascade_irqaction
)paren
suffix:semicolon
)brace
"&f;"
r_void
DECL|function|pyxis_pci_tbi
id|pyxis_pci_tbi
c_func
(paren
r_struct
id|pci_controler
op_star
id|hose
comma
id|dma_addr_t
id|start
comma
id|dma_addr_t
id|end
)paren
(brace
id|wmb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vip
)paren
id|PYXIS_TBIA
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Flush all locked and unlocked.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pass 1 and 2 have a broken scatter-gather tlb -- it cannot be invalidated.&n; * To work around this problem, we allocate mappings, and put the chip into&n; * DMA loopback mode to read a garbage page.  This works by causing TLB&n; * misses, causing old entries to be purged to make room for the new entries&n; * coming in for the garbage page.&n; * &n; * Thanks to NetBSD sources for pointing out this bug.  What a pain.&n; */
DECL|variable|broken_tbi_addr
r_static
r_int
r_int
id|broken_tbi_addr
suffix:semicolon
DECL|macro|BROKEN_TBI_READS
mdefine_line|#define BROKEN_TBI_READS 12
r_static
r_void
DECL|function|pyxis_broken_pci_tbi
id|pyxis_broken_pci_tbi
c_func
(paren
r_struct
id|pci_controler
op_star
id|hose
comma
id|dma_addr_t
id|start
comma
id|dma_addr_t
id|end
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|bus_addr
suffix:semicolon
r_int
r_int
id|ctrl
suffix:semicolon
r_int
id|i
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Put the chip into PCI loopback mode.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|ctrl
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL
op_assign
id|ctrl
op_or
l_int|4
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Read from PCI dense memory space at TBI_ADDR, skipping 64k&n;&t;   on each read.  This forces SG TLB misses.  It appears that&n;&t;   the TLB entries are &quot;not quite LRU&quot;, meaning that we need&n;&t;   to read more times than there are actual tags.  */
id|bus_addr
op_assign
id|broken_tbi_addr
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
id|BROKEN_TBI_READS
suffix:semicolon
op_increment
id|i
comma
id|bus_addr
op_add_assign
l_int|64
op_star
l_int|1024
)paren
id|pyxis_readl
c_func
(paren
id|bus_addr
)paren
suffix:semicolon
multiline_comment|/* Restore normal PCI operation.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL
op_assign
id|ctrl
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pyxis_enable_broken_tbi
id|pyxis_enable_broken_tbi
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
id|arena
)paren
(brace
r_void
op_star
id|page
suffix:semicolon
r_int
r_int
op_star
id|ppte
comma
id|ofs
comma
id|pte
suffix:semicolon
r_int
id|i
comma
id|npages
suffix:semicolon
id|page
op_assign
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|pte
op_assign
(paren
id|virt_to_phys
c_func
(paren
id|page
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
)paren
op_or
l_int|1
suffix:semicolon
id|npages
op_assign
(paren
id|BROKEN_TBI_READS
op_plus
l_int|1
)paren
op_star
l_int|64
op_star
l_int|1024
op_div
id|PAGE_SIZE
suffix:semicolon
id|ofs
op_assign
id|iommu_arena_alloc
c_func
(paren
id|arena
comma
id|npages
)paren
suffix:semicolon
id|ppte
op_assign
id|arena-&gt;ptes
op_plus
id|ofs
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
id|npages
suffix:semicolon
op_increment
id|i
)paren
id|ppte
(braket
id|i
)braket
op_assign
id|pte
suffix:semicolon
id|broken_tbi_addr
op_assign
id|pyxis_ioremap
c_func
(paren
id|arena-&gt;dma_base
op_plus
id|ofs
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|alpha_mv.mv_pci_tbi
op_assign
id|pyxis_broken_pci_tbi
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PYXIS: Enabling broken tbia workaround.&bslash;n&quot;
)paren
suffix:semicolon
)brace
"&f;"
r_void
id|__init
DECL|function|pyxis_init_arch
id|pyxis_init_arch
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controler
op_star
id|hose
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_ERR_MASK 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_ERR 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_INT_REQ 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_REQ
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_INT_MASK 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_MASK
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_INT_ROUTE 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_ROUTE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_INT_HILO 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_HILO
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_INT_CNFG 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_INT_CNFG
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: PYXIS_RT_COUNT 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|PYXIS_RT_COUNT
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* &n;&t; * Set up error reporting. Make sure CPU_PE is OFF in the mask.&n;&t; */
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
suffix:semicolon
id|temp
op_and_assign
op_complement
l_int|4
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
op_assign
id|temp
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
suffix:semicolon
multiline_comment|/* re-read to force write */
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
id|temp
op_or_assign
l_int|0x180
suffix:semicolon
multiline_comment|/* master/target abort */
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
op_assign
id|temp
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/*&n;&t; * Create our single hose.&n;&t; */
id|hose
op_assign
id|alloc_pci_controler
c_func
(paren
)paren
suffix:semicolon
id|hose-&gt;io_space
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|hose-&gt;mem_space
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|hose-&gt;config_space
op_assign
id|PYXIS_CONF
suffix:semicolon
id|hose-&gt;index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the PCI to main memory translation windows.&n;&t; *&n;&t; * Window 0 is scatter-gather 8MB at 8MB (for isa)&n;&t; * Window 1 is scatter-gather 128MB at 3GB&n;&t; * Window 2 is direct access 1GB at 1GB&n;&t; * Window 3 is direct access 1GB at 2GB&n;&t; * ??? We ought to scale window 1 with memory.&n;&t; *&n;&t; * We must actually use 2 windows to direct-map the 2GB space,&n;&t; * because of an idiot-syncrasy of the CYPRESS chip.  It may&n;&t; * respond to a PCI bus address in the last 1MB of the 4GB&n;&t; * address range.&n;&t; */
multiline_comment|/* NetBSD hints that page tables must be aligned to 32K due&n;&t;   to a hardware bug.  No description of what models affected.  */
id|hose-&gt;sg_isa
op_assign
id|iommu_arena_new
c_func
(paren
l_int|0x00800000
comma
l_int|0x00800000
comma
l_int|32768
)paren
suffix:semicolon
id|hose-&gt;sg_pci
op_assign
id|iommu_arena_new
c_func
(paren
l_int|0xc0000000
comma
l_int|0x08000000
comma
l_int|32768
)paren
suffix:semicolon
id|__direct_map_base
op_assign
l_int|0x40000000
suffix:semicolon
id|__direct_map_size
op_assign
l_int|0x80000000
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
op_assign
id|hose-&gt;sg_isa-&gt;dma_base
op_or
l_int|3
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_MASK
op_assign
(paren
id|hose-&gt;sg_isa-&gt;size
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_T0_BASE
op_assign
id|virt_to_phys
c_func
(paren
id|hose-&gt;sg_isa-&gt;ptes
)paren
op_rshift
l_int|2
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_BASE
op_assign
id|hose-&gt;sg_pci-&gt;dma_base
op_or
l_int|3
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_MASK
op_assign
(paren
id|hose-&gt;sg_pci-&gt;size
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_T1_BASE
op_assign
id|virt_to_phys
c_func
(paren
id|hose-&gt;sg_pci-&gt;ptes
)paren
op_rshift
l_int|2
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_BASE
op_assign
l_int|0x40000000
op_or
l_int|1
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_MASK
op_assign
(paren
l_int|0x40000000
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_T2_BASE
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_BASE
op_assign
l_int|0x80000000
op_or
l_int|1
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_MASK
op_assign
(paren
l_int|0x40000000
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_T3_BASE
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Pass 1 and 2 (ie revision &lt;= 1) have a broken TBIA.  See the&n;&t;   complete description next to pyxis_broken_pci_tbi for details.  */
r_if
c_cond
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_REV
op_amp
l_int|0xff
)paren
op_le
l_int|1
)paren
id|pyxis_enable_broken_tbi
c_func
(paren
id|hose-&gt;sg_pci
)paren
suffix:semicolon
id|alpha_mv
dot
id|mv_pci_tbi
c_func
(paren
id|hose
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Next, clear the PYXIS_CFG register, which gets used&n;&t; *  for PCI Config Space accesses. That is the way&n;&t; *  we want to use it, and we do not want to depend on&n;&t; *  what ARC or SRM might have left behind...&n;&t; */
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_ne
l_int|0
)paren
(brace
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
multiline_comment|/* Zero the HAE.  */
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_MEM
op_assign
l_int|0U
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_MEM
suffix:semicolon
multiline_comment|/* re-read to force write */
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_IO
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_IO
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/*&n;&t; * Finally, check that the PYXIS_CTRL1 has IOA_BEN set for&n;&t; * enabling byte/word PCI bus space(s) access.&n;&t; */
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|1
)paren
)paren
(brace
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL1
op_assign
id|temp
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL1
suffix:semicolon
multiline_comment|/* re-read */
)brace
)brace
r_static
r_inline
r_void
DECL|function|pyxis_pci_clr_err
id|pyxis_pci_clr_err
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
op_assign
id|tmp
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
r_void
DECL|function|pyxis_machine_check
id|pyxis_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|expected
suffix:semicolon
multiline_comment|/* Clear the error before reporting anything.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* magic */
id|draina
c_func
(paren
)paren
suffix:semicolon
id|pyxis_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|expected
op_assign
id|mcheck_expected
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|expected
op_logical_and
id|vector
op_eq
l_int|0x660
)paren
(brace
r_struct
id|el_common
op_star
id|com
suffix:semicolon
r_struct
id|el_common_EV5_uncorrectable_mcheck
op_star
id|ev5
suffix:semicolon
r_struct
id|el_PYXIS_sysdata_mcheck
op_star
id|pyxis
suffix:semicolon
id|com
op_assign
(paren
r_void
op_star
)paren
id|la_ptr
suffix:semicolon
id|ev5
op_assign
(paren
r_void
op_star
)paren
(paren
id|la_ptr
op_plus
id|com-&gt;proc_offset
)paren
suffix:semicolon
id|pyxis
op_assign
(paren
r_void
op_star
)paren
(paren
id|la_ptr
op_plus
id|com-&gt;sys_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|com-&gt;code
op_eq
l_int|0x202
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PYXIS PCI machine check: err0=%08x &quot;
l_string|&quot;err1=%08x err2=%08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|pyxis-&gt;pci_err0
comma
(paren
r_int
)paren
id|pyxis-&gt;pci_err1
comma
(paren
r_int
)paren
id|pyxis-&gt;pci_err2
)paren
suffix:semicolon
id|expected
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|process_mcheck_info
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
comma
l_string|&quot;PYXIS&quot;
comma
id|expected
)paren
suffix:semicolon
)brace
eof
