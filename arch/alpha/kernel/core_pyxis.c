multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_pyxis.c&n; *&n; * Code common to all PYXIS core logic chips.&n; *&n; * Based on code written by David A Rusling (david.rusling@reo.mts.dec.com).&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_pyxis.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &quot;proto.h&quot;
multiline_comment|/* NOTE: Herein are back-to-back mb instructions.  They are magic.&n;   One plausible explanation is that the I/O controller does not properly&n;   handle the system transaction.  Another involves timing.  Ho hum.  */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
DECL|macro|DEBUG_MCHECK
mdefine_line|#define DEBUG_MCHECK 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CNF
macro_line|# define DBG_CNF(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CNF
macro_line|# define DBG_CNF(args)
macro_line|#endif
macro_line|#if DEBUG_MCHECK
DECL|macro|DBG_MCK
macro_line|# define DBG_MCK(args)&t;printk args
DECL|macro|DEBUG_MCHECK_DUMP
macro_line|# define DEBUG_MCHECK_DUMP
macro_line|#else
DECL|macro|DBG_MCK
macro_line|# define DBG_MCK(args)
macro_line|#endif
DECL|variable|PYXIS_mcheck_expected
r_static
r_volatile
r_int
r_int
id|PYXIS_mcheck_expected
op_assign
l_int|0
suffix:semicolon
DECL|variable|PYXIS_mcheck_taken
r_static
r_volatile
r_int
r_int
id|PYXIS_mcheck_taken
op_assign
l_int|0
suffix:semicolon
DECL|variable|PYXIS_jd
r_static
r_int
r_int
id|PYXIS_jd
suffix:semicolon
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address and setup the PYXIS_HAXR2 register&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., SCSI and Ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
r_static
r_int
DECL|function|mk_conf_addr
id|mk_conf_addr
c_func
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
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
r_int
r_int
id|addr
suffix:semicolon
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x,&quot;
l_string|&quot; pci_addr=0x%p, type1=0x%p)&bslash;n&quot;
comma
id|bus
comma
id|device_fn
comma
id|where
comma
id|pci_addr
comma
id|type1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
(brace
r_int
id|device
suffix:semicolon
id|device
op_assign
id|device_fn
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* Type 0 configuration cycle. */
macro_line|#if NOT_NOW
r_if
c_cond
(paren
id|device
OG
l_int|20
)paren
(brace
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: device (%d) &gt; 20, return -1&bslash;n&quot;
comma
id|device
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
op_star
id|type1
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
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
)brace
r_else
(brace
multiline_comment|/* Type 1 configuration cycle.  */
op_star
id|type1
op_assign
l_int|1
suffix:semicolon
id|addr
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
)brace
op_star
id|pci_addr
op_assign
id|addr
suffix:semicolon
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: returning pci_addr 0x%lx&bslash;n&quot;
comma
id|addr
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
id|DBG_CNF
c_func
(paren
(paren
l_string|&quot;conf_read: PYXIS ERR was 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
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
id|pyxis_cfg
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
id|PYXIS_mcheck_expected
op_assign
l_int|1
suffix:semicolon
id|PYXIS_mcheck_taken
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
id|PYXIS_mcheck_taken
)paren
(brace
id|PYXIS_mcheck_taken
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
id|PYXIS_mcheck_expected
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
id|__restore_flags
c_func
(paren
id|flags
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
id|pyxis_cfg
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
id|PYXIS_mcheck_expected
op_assign
l_int|1
suffix:semicolon
id|PYXIS_mcheck_taken
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
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* magic */
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* do a PYXIS read to force the write */
id|PYXIS_mcheck_expected
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
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|pyxis_hose_read_config_byte
id|pyxis_hose_read_config_byte
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u8
op_star
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x00
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
r_int
DECL|function|pyxis_hose_read_config_word
id|pyxis_hose_read_config_word
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u16
op_star
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x08
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
r_int
DECL|function|pyxis_hose_read_config_dword
id|pyxis_hose_read_config_dword
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u32
op_star
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x18
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
r_int
DECL|function|pyxis_hose_write_config_byte
id|pyxis_hose_write_config_byte
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u8
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x00
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
r_int
DECL|function|pyxis_hose_write_config_word
id|pyxis_hose_write_config_word
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u16
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x08
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
r_int
DECL|function|pyxis_hose_write_config_dword
id|pyxis_hose_write_config_dword
(paren
id|u8
id|bus
comma
id|u8
id|device_fn
comma
id|u8
id|where
comma
id|u32
id|value
comma
r_struct
id|linux_hose_info
op_star
id|hose
)paren
(brace
r_int
r_int
id|addr
op_assign
id|PYXIS_CONF
suffix:semicolon
r_int
r_int
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
id|bus
comma
id|device_fn
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
op_or_assign
(paren
id|pci_addr
op_lshift
l_int|5
)paren
op_plus
l_int|0x18
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
r_void
id|__init
DECL|function|pyxis_enable_errors
id|pyxis_enable_errors
(paren
r_void
)paren
(brace
r_int
r_int
id|pyxis_err
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
id|pyxis_err
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
suffix:semicolon
id|pyxis_err
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
id|pyxis_err
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|pyxis_err
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR_MASK
suffix:semicolon
multiline_comment|/* re-read to force write */
id|pyxis_err
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
id|pyxis_err
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
id|pyxis_err
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|pyxis_err
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
)brace
r_int
id|__init
DECL|function|pyxis_srm_window_setup
id|pyxis_srm_window_setup
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|alpha_use_srm_setup
)paren
(brace
r_default
suffix:colon
(brace
)brace
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM_SETUP)
multiline_comment|/* Check window 0 for enabled and mapped to 0.  */
r_if
c_cond
(paren
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
op_amp
l_int|3
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_T0_BASE
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_MASK
op_amp
l_int|0xfff00000U
)paren
OG
l_int|0x0ff00000U
)paren
)paren
(brace
id|PYXIS_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;pyxis_init: using Window 0 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_MASK
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_T0_BASE
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* Check window 1 for enabled and mapped to 0.  */
r_if
c_cond
(paren
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_BASE
op_amp
l_int|3
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_T1_BASE
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_MASK
op_amp
l_int|0xfff00000U
)paren
OG
l_int|0x0ff00000U
)paren
)paren
(brace
id|PYXIS_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;pyxis_init: using Window 1 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_BASE
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_MASK
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_T1_BASE
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* Check window 2 for enabled and mapped to 0.  */
r_if
c_cond
(paren
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_BASE
op_amp
l_int|3
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_T2_BASE
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_MASK
op_amp
l_int|0xfff00000U
)paren
OG
l_int|0x0ff00000U
)paren
)paren
(brace
id|PYXIS_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;pyxis_init: using Window 2 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_BASE
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_MASK
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_T2_BASE
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* Check window 3 for enabled and mapped to 0.  */
r_if
c_cond
(paren
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_BASE
op_amp
l_int|3
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_T3_BASE
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_MASK
op_amp
l_int|0xfff00000U
)paren
OG
l_int|0x0ff00000U
)paren
)paren
(brace
id|PYXIS_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;pyxis_init: using Window 3 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pyxis_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_BASE
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_MASK
comma
op_star
(paren
id|vuip
)paren
id|PYXIS_T3_BASE
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* Otherwise, we must use our defaults.  */
id|PYXIS_DMA_WIN_BASE
op_assign
id|PYXIS_DMA_WIN_BASE_DEFAULT
suffix:semicolon
id|PYXIS_DMA_WIN_SIZE
op_assign
id|PYXIS_DMA_WIN_SIZE_DEFAULT
suffix:semicolon
macro_line|#endif
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pyxis_native_window_setup
id|pyxis_native_window_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Set up the PCI-&gt;physical memory translation windows.&n;&t; * For now, windows 1,2 and 3 are disabled.  In the future, we may&n;&t; * want to use them to do scatter/gather DMA. &n;&t; *&n;&t; * Window 0 goes at 1 GB and is 1 GB large.&n;&t; */
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
op_assign
l_int|1U
op_or
(paren
id|PYXIS_DMA_WIN_BASE_DEFAULT
op_amp
l_int|0xfff00000U
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_MASK
op_assign
(paren
id|PYXIS_DMA_WIN_SIZE_DEFAULT
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000U
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_T0_BASE
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W1_BASE
op_assign
l_int|0x0
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W2_BASE
op_assign
l_int|0x0
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_W3_BASE
op_assign
l_int|0x0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pyxis_finish_init_arch
id|pyxis_finish_init_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;         * Next, clear the PYXIS_CFG register, which gets used&n;&t; *  for PCI Config Space accesses. That is the way&n;&t; *  we want to use it, and we do not want to depend on&n;&t; *  what ARC or SRM might have left behind...&n;&t; */
(brace
r_int
r_int
id|pyxis_cfg
comma
id|temp
suffix:semicolon
id|pyxis_cfg
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CFG
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pyxis_cfg
op_ne
l_int|0
)paren
(brace
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;PYXIS_init: CFG was 0x%x&bslash;n&quot;
comma
id|pyxis_cfg
)paren
suffix:semicolon
macro_line|#endif
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
)brace
multiline_comment|/*&n;&t; * Sigh... For the SRM setup, unless we know apriori what the HAE&n;&t; * contents will be, we need to setup the arbitrary region bases&n;&t; * so we can test against the range of addresses and tailor the&n;&t; * region chosen for the SPARSE memory access.&n;&t; *&n;&t; * See include/asm-alpha/pyxis.h for the SPARSE mem read/write.&n;&t; */
r_if
c_cond
(paren
id|alpha_use_srm_setup
)paren
(brace
r_int
r_int
id|pyxis_hae_mem
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_MEM
suffix:semicolon
id|alpha_mv.sm_base_r1
op_assign
(paren
id|pyxis_hae_mem
)paren
op_amp
l_int|0xe0000000UL
suffix:semicolon
id|alpha_mv.sm_base_r2
op_assign
(paren
id|pyxis_hae_mem
op_lshift
l_int|16
)paren
op_amp
l_int|0xf8000000UL
suffix:semicolon
id|alpha_mv.sm_base_r3
op_assign
(paren
id|pyxis_hae_mem
op_lshift
l_int|24
)paren
op_amp
l_int|0xfc000000UL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the HAE cache, so that setup_arch() code&n;&t;&t; * will use the SRM setting always. Our readb/writeb&n;&t;&t; * code in pyxis.h expects never to have to change&n;&t;&t; * the contents of the HAE.&n;&t;&t; */
id|alpha_mv.hae_cache
op_assign
id|pyxis_hae_mem
suffix:semicolon
macro_line|#ifndef CONFIG_ALPHA_GENERIC
multiline_comment|/* In a generic kernel, we can always use BWIO.  */
id|alpha_mv.mv_readb
op_assign
id|pyxis_srm_readb
suffix:semicolon
id|alpha_mv.mv_readw
op_assign
id|pyxis_srm_readw
suffix:semicolon
id|alpha_mv.mv_writeb
op_assign
id|pyxis_srm_writeb
suffix:semicolon
id|alpha_mv.mv_writew
op_assign
id|pyxis_srm_writew
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
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
)brace
multiline_comment|/*&n;&t; * Finally, check that the PYXIS_CTRL1 has IOA_BEN set for&n;&t; * enabling byte/word PCI bus space(s) access.&n;&t; */
(brace
r_int
r_int
id|ctrl1
suffix:semicolon
id|ctrl1
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
id|ctrl1
op_amp
l_int|1
)paren
)paren
(brace
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;PYXIS_init: enabling byte/word PCI space&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL1
op_assign
id|ctrl1
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|ctrl1
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_CTRL1
suffix:semicolon
multiline_comment|/* re-read */
)brace
)brace
)brace
r_void
id|__init
DECL|function|pyxis_init_arch
id|pyxis_init_arch
c_func
(paren
r_int
r_int
op_star
id|mem_start
comma
r_int
r_int
op_star
id|mem_end
)paren
(brace
id|pyxis_enable_errors
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pyxis_srm_window_setup
c_func
(paren
)paren
)paren
id|pyxis_native_window_setup
c_func
(paren
)paren
suffix:semicolon
id|pyxis_finish_init_arch
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pyxis_pci_clr_err
id|pyxis_pci_clr_err
c_func
(paren
r_void
)paren
(brace
id|PYXIS_jd
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;PYXIS_pci_clr_err: PYXIS ERR after read 0x%x&bslash;n&quot;
comma
id|PYXIS_jd
)paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
op_assign
l_int|0x0180
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|PYXIS_jd
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_ERR
suffix:semicolon
multiline_comment|/* re-read to force write */
r_return
l_int|0
suffix:semicolon
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
r_struct
id|el_common
op_star
id|mchk_header
suffix:semicolon
r_struct
id|el_PYXIS_sysdata_mcheck
op_star
id|mchk_sysdata
suffix:semicolon
id|mchk_header
op_assign
(paren
r_struct
id|el_common
op_star
)paren
id|la_ptr
suffix:semicolon
id|mchk_sysdata
op_assign
(paren
r_struct
id|el_PYXIS_sysdata_mcheck
op_star
)paren
(paren
id|la_ptr
op_plus
id|mchk_header-&gt;sys_offset
)paren
suffix:semicolon
macro_line|#if 0
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;pyxis_machine_check: vector=0x%lx la_ptr=0x%lx&bslash;n&quot;
comma
id|vector
comma
id|la_ptr
)paren
)paren
suffix:semicolon
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;&bslash;t&bslash;t pc=0x%lx size=0x%x procoffset=0x%x sysoffset 0x%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|mchk_header-&gt;size
comma
id|mchk_header-&gt;proc_offset
comma
id|mchk_header-&gt;sys_offset
)paren
)paren
suffix:semicolon
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;pyxis_machine_check: expected %d DCSR 0x%lx PEAR 0x%lx&bslash;n&quot;
comma
id|PYXIS_mcheck_expected
comma
id|mchk_sysdata-&gt;epic_dcsr
comma
id|mchk_sysdata-&gt;epic_pear
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Check if machine check is due to a badaddr() and if so,&n;&t; * ignore the machine check.&n;&t; */
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
id|PYXIS_mcheck_expected
)paren
(brace
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;PYXIS machine check expected&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|PYXIS_mcheck_expected
op_assign
l_int|0
suffix:semicolon
id|PYXIS_mcheck_taken
op_assign
l_int|1
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
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PYXIS machine check NOT expected&bslash;n&quot;
)paren
suffix:semicolon
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;pyxis_machine_check: vector=0x%lx la_ptr=0x%lx&bslash;n&quot;
comma
id|vector
comma
id|la_ptr
)paren
)paren
suffix:semicolon
id|DBG_MCK
c_func
(paren
(paren
l_string|&quot;&bslash;t&bslash;t pc=0x%lx size=0x%x procoffset=0x%x&quot;
l_string|&quot; sysoffset 0x%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|mchk_header-&gt;size
comma
id|mchk_header-&gt;proc_offset
comma
id|mchk_header-&gt;sys_offset
)paren
)paren
suffix:semicolon
id|PYXIS_mcheck_expected
op_assign
l_int|0
suffix:semicolon
id|PYXIS_mcheck_taken
op_assign
l_int|1
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
macro_line|#ifdef DEBUG_MCHECK_DUMP
(brace
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|la_ptr
suffix:semicolon
suffix:semicolon
r_int
id|n
op_assign
id|mchk_header-&gt;size
op_div
(paren
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_do
id|printk
c_func
(paren
l_string|&quot; +%lx %lx %lx&bslash;n&quot;
comma
id|i
op_star
r_sizeof
(paren
r_int
)paren
comma
id|ptr
(braket
id|i
)braket
comma
id|ptr
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
eof