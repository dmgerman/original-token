multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_cia.c&n; *&n; * Code common to all CIA core logic chips.&n; *&n; * Written by David A Rusling (david.rusling@reo.mts.dec.com).&n; * December 1995.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &quot;proto.h&quot;
multiline_comment|/*&n; * NOTE: Herein lie back-to-back mb instructions.  They are magic. &n; * One plausible explanation is that the i/o controller does not properly&n; * handle the system transaction.  Another involves timing.  Ho hum.&n; */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
DECL|macro|DEBUG_DUMP_REGS
mdefine_line|#define DEBUG_DUMP_REGS 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBGC
macro_line|# define DBGC(args)&t;printk args
macro_line|#else
DECL|macro|DBGC
macro_line|# define DBGC(args)
macro_line|#endif
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int  *
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address and setup the CIA_HAXR2 register&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., SCSI and Ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
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
id|DBGC
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d, device_fn=0x%x, where=0x%x, &quot;
l_string|&quot;pci_addr=0x%p, type1=0x%p)&bslash;n&quot;
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
op_assign
id|device_fn
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* Type 0 configuration cycle.  */
r_if
c_cond
(paren
id|device
OG
l_int|20
)paren
(brace
id|DBGC
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: device (%d) &gt; 20, returning -1&bslash;n&quot;
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
id|DBGC
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
suffix:semicolon
r_int
r_int
id|cia_cfg
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
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* avoid getting hit by machine check */
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_read(addr=0x%lx, type1=%d)&bslash;n&quot;
comma
id|addr
comma
id|type1
)paren
)paren
suffix:semicolon
multiline_comment|/* Reset status register to avoid losing errors.  */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_read: CIA ERR was 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* If Type1 access, must set CIA CFG. */
r_if
c_cond
(paren
id|type1
)paren
(brace
id|cia_cfg
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
op_assign
id|cia_cfg
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_read: TYPE1 access&bslash;n&quot;
)paren
)paren
suffix:semicolon
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
macro_line|#if 0
multiline_comment|/* This code might be necessary if machine checks aren&squot;t taken,&n;&t;   but I can&squot;t get it to work on CIA-2, so its disabled. */
id|draina
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Now look for any errors.  */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_read: CIA ERR after read 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* Is any error bit set? */
r_if
c_cond
(paren
id|stat0
op_amp
l_int|0x8FEF0FFFU
)paren
(brace
multiline_comment|/* If not MAS_ABT, print status. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat0
op_amp
l_int|0x0080
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CIA.c:conf_read: got stat0=%x&bslash;n&quot;
comma
id|stat0
)paren
suffix:semicolon
)brace
multiline_comment|/* reset error status: */
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
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
multiline_comment|/* reset machine check */
id|value
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
macro_line|#endif
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
id|CIA_IOC_CFG
op_assign
id|cia_cfg
op_amp
op_complement
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_read(): finished&bslash;n&quot;
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
suffix:semicolon
r_int
r_int
id|cia_cfg
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
id|CIA_IOC_CIA_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_write: CIA ERR was 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* If Type1 access, must set CIA CFG.  */
r_if
c_cond
(paren
id|type1
)paren
(brace
id|cia_cfg
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
op_assign
id|cia_cfg
op_or
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_write: TYPE1 access&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
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
macro_line|#if 0
multiline_comment|/* This code might be necessary if machine checks aren&squot;t taken,&n;&t;   but I can&squot;t get it to work on CIA-2, so its disabled. */
id|draina
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Now look for any errors */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_write: CIA ERR after write 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* Is any error bit set? */
r_if
c_cond
(paren
id|stat0
op_amp
l_int|0x8FEF0FFFU
)paren
(brace
multiline_comment|/* If not MAS_ABT, print status */
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat0
op_amp
l_int|0x0080
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CIA.c:conf_read: got stat0=%x&bslash;n&quot;
comma
id|stat0
)paren
suffix:semicolon
)brace
multiline_comment|/* Reset error status.  */
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|stat0
suffix:semicolon
id|mb
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
multiline_comment|/* reset machine check */
id|value
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
macro_line|#endif
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
id|CIA_IOC_CFG
op_assign
id|cia_cfg
op_amp
op_complement
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
id|DBGC
c_func
(paren
(paren
l_string|&quot;conf_write(): finished&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|cia_hose_read_config_byte
id|cia_hose_read_config_byte
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
id|CIA_CONF
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
DECL|function|cia_hose_read_config_word
id|cia_hose_read_config_word
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
id|CIA_CONF
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
DECL|function|cia_hose_read_config_dword
id|cia_hose_read_config_dword
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
id|CIA_CONF
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
DECL|function|cia_hose_write_config_byte
id|cia_hose_write_config_byte
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
id|CIA_CONF
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
DECL|function|cia_hose_write_config_word
id|cia_hose_write_config_word
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
id|CIA_CONF
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
DECL|function|cia_hose_write_config_dword
id|cia_hose_write_config_dword
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
id|CIA_CONF
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
DECL|function|cia_init_arch
id|cia_init_arch
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
r_int
r_int
id|cia_tmp
suffix:semicolon
macro_line|#if DEBUG_DUMP_REGS
(brace
r_int
r_int
id|temp
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_REV
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_REV was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_LAT
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_PCI_LAT was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_CTRL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CTRL was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
l_int|0xfffffc8740000140UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CTRL1 was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_HAE_MEM
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_HAE_MEM was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_HAE_IO
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_HAE_IO was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CFG was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CACK_EN
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CACK_EN was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CFG
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CFG was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_DIAG
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_DIAG was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_DIAG_CHECK
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_DIAG_CHECK was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PERF_MONITOR
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_PERF_MONITOR was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PERF_CONTROL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_PERF_CONTROL was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_ERR was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_STAT
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_STAT was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_MCR
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_MCR was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_CTRL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_CTRL was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_ERR_MASK
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: CIA_ERR_MASK was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_BASE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: W0_BASE was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_BASE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: W1_BASE was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_BASE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: W2_BASE was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_BASE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: W3_BASE was 0x%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_DUMP_REGS */
multiline_comment|/* &n;&t; * Set up error reporting.&n;&t; */
id|cia_tmp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
id|cia_tmp
op_or_assign
l_int|0x180
suffix:semicolon
multiline_comment|/* master, target abort */
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|cia_tmp
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|cia_tmp
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_CTRL
suffix:semicolon
id|cia_tmp
op_or_assign
l_int|0x400
suffix:semicolon
multiline_comment|/* turn on FILL_ERR to get mchecks */
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_CTRL
op_assign
id|cia_tmp
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/* Check window 0 for enabled and mapped to 0 */
r_if
c_cond
(paren
(paren
(paren
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_BASE
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
id|CIA_IOC_PCI_T0_BASE
op_eq
l_int|0
)paren
)paren
(brace
id|CIA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;cia_init: using Window 0 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_BASE
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_MASK
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_T0_BASE
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
id|CIA_IOC_PCI_W1_BASE
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
id|CIA_IOC_PCI_T1_BASE
op_eq
l_int|0
)paren
)paren
(brace
id|CIA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;cia_init: using Window 1 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_BASE
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_MASK
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_T1_BASE
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
id|CIA_IOC_PCI_W2_BASE
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
id|CIA_IOC_PCI_T2_BASE
op_eq
l_int|0
)paren
)paren
(brace
id|CIA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;cia_init: using Window 2 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_BASE
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_MASK
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_T2_BASE
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
id|CIA_IOC_PCI_W3_BASE
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
id|CIA_IOC_PCI_T3_BASE
op_eq
l_int|0
)paren
)paren
(brace
id|CIA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_BASE
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_MASK
op_amp
l_int|0xfff00000U
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_add_assign
l_int|0x00100000U
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;cia_init: using Window 3 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cia_init: BASE 0x%x MASK 0x%x TRANS 0x%x&bslash;n&quot;
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_BASE
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_MASK
comma
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_T3_BASE
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* Otherwise, we must use our defaults.  */
id|CIA_DMA_WIN_BASE
op_assign
id|CIA_DMA_WIN_BASE_DEFAULT
suffix:semicolon
id|CIA_DMA_WIN_SIZE
op_assign
id|CIA_DMA_WIN_SIZE_DEFAULT
suffix:semicolon
macro_line|#endif
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t; * Set up the PCI-&gt;physical memory translation windows.&n;&t;&t; * For now, windows 2 and 3 are disabled.  In the future,&n;&t;&t; * we may want to use them to do scatter/gather DMA. &n;&t;&t; *&n;&t;&t; * Window 0 goes at 1 GB and is 1 GB large.&n;&t;&t; * Window 1 goes at 2 GB and is 1 GB large.&n;&t;&t; */
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_BASE
op_assign
id|CIA_DMA_WIN0_BASE_DEFAULT
op_or
l_int|1U
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W0_MASK
op_assign
(paren
id|CIA_DMA_WIN0_SIZE_DEFAULT
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
id|CIA_IOC_PCI_T0_BASE
op_assign
id|CIA_DMA_WIN0_TRAN_DEFAULT
op_rshift
l_int|2
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_BASE
op_assign
id|CIA_DMA_WIN1_BASE_DEFAULT
op_or
l_int|1U
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W1_MASK
op_assign
(paren
id|CIA_DMA_WIN1_SIZE_DEFAULT
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
id|CIA_IOC_PCI_T1_BASE
op_assign
id|CIA_DMA_WIN1_TRAN_DEFAULT
op_rshift
l_int|2
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W2_BASE
op_assign
l_int|0x0
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_PCI_W3_BASE
op_assign
l_int|0x0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;         * Next, clear the CIA_CFG register, which gets used&n;         * for PCI Config Space accesses. That is the way&n;         * we want to use it, and we do not want to depend on&n;         * what ARC or SRM might have left behind...&n;         */
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_CFG
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Sigh... For the SRM setup, unless we know apriori what the HAE&n;&t; * contents will be, we need to setup the arbitrary region bases&n;&t; * so we can test against the range of addresses and tailor the&n;&t; * region chosen for the SPARSE memory access.&n;&t; *&n;&t; * See include/asm-alpha/cia.h for the SPARSE mem read/write.&n;&t; */
r_if
c_cond
(paren
id|alpha_use_srm_setup
)paren
(brace
r_int
r_int
id|cia_hae_mem
op_assign
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_HAE_MEM
)paren
suffix:semicolon
id|alpha_mv.sm_base_r1
op_assign
(paren
id|cia_hae_mem
)paren
op_amp
l_int|0xe0000000UL
suffix:semicolon
id|alpha_mv.sm_base_r2
op_assign
(paren
id|cia_hae_mem
op_lshift
l_int|16
)paren
op_amp
l_int|0xf8000000UL
suffix:semicolon
id|alpha_mv.sm_base_r3
op_assign
(paren
id|cia_hae_mem
op_lshift
l_int|24
)paren
op_amp
l_int|0xfc000000UL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the HAE cache, so that setup_arch() code&n;&t;&t; * will use the SRM setting always. Our readb/writeb&n;&t;&t; * code in cia.h expects never to have to change&n;&t;&t; * the contents of the HAE.&n;&t;&t; */
id|alpha_mv.hae_cache
op_assign
id|cia_hae_mem
suffix:semicolon
id|alpha_mv.mv_readb
op_assign
id|cia_srm_readb
suffix:semicolon
id|alpha_mv.mv_readw
op_assign
id|cia_srm_readw
suffix:semicolon
id|alpha_mv.mv_writeb
op_assign
id|cia_srm_writeb
suffix:semicolon
id|alpha_mv.mv_writew
op_assign
id|cia_srm_writew
suffix:semicolon
)brace
r_else
(brace
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_HAE_MEM
)paren
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
(paren
id|vuip
)paren
id|CIA_IOC_HAE_MEM
)paren
suffix:semicolon
multiline_comment|/* read it back. */
op_star
(paren
(paren
id|vuip
)paren
id|CIA_IOC_HAE_IO
)paren
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
(paren
id|vuip
)paren
id|CIA_IOC_HAE_IO
)paren
suffix:semicolon
multiline_comment|/* read it back. */
)brace
)brace
r_static
r_inline
r_void
DECL|function|cia_pci_clr_err
id|cia_pci_clr_err
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|jd
suffix:semicolon
id|jd
op_assign
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|CIA_IOC_CIA_ERR
op_assign
id|jd
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
id|CIA_IOC_CIA_ERR
suffix:semicolon
multiline_comment|/* re-read to force write.  */
)brace
r_void
DECL|function|cia_machine_check
id|cia_machine_check
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
multiline_comment|/* Clear the error before any reporting.  */
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
id|cia_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
id|rdmces
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* reset machine check pending flag.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|process_mcheck_info
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
comma
l_string|&quot;CIA&quot;
comma
id|mcheck_expected
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
eof
