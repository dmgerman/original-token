multiline_comment|/*&n; * Code common to all PYXIS chips.&n; *&n; * Based on code written by David A Rusling (david.rusling@reo.mts.dec.com).&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* NOTE: Herein are back-to-back mb insns.  They are magic.&n;   A plausible explanation is that the i/o controler does not properly&n;   handle the system transaction.  Another involves timing.  Ho hum.  */
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|wrmces
c_func
(paren
r_int
r_int
id|mces
)paren
suffix:semicolon
r_extern
r_int
id|alpha_sys_type
suffix:semicolon
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
macro_line|#ifdef DEBUG 
DECL|macro|DBG
macro_line|# define DBG(args)&t;printk args
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG(args)
macro_line|#endif
DECL|macro|DEBUG_MCHECK
mdefine_line|#define DEBUG_MCHECK
macro_line|#ifdef DEBUG_MCHECK
DECL|macro|DBG_MCK
macro_line|# define DBG_MCK(args)&t;printk args
macro_line|#else
DECL|macro|DBG_MCK
macro_line|# define DBG_MCK(args)
macro_line|#endif
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int  *
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
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address and setup the PYXIS_HAXR2 register&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., scsi and ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
DECL|function|mk_conf_addr
r_static
r_int
id|mk_conf_addr
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
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
id|DBG
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
multiline_comment|/* type 0 configuration cycle: */
macro_line|#if NOT_NOW
r_if
c_cond
(paren
id|device
OG
l_int|20
)paren
(brace
id|DBG
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
multiline_comment|/* type 1 configuration cycle: */
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
id|DBG
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
DECL|function|conf_read
r_static
r_int
r_int
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
id|pyxis_cfg
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to keep gcc quiet */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* avoid getting hit by machine check */
id|cli
c_func
(paren
)paren
suffix:semicolon
id|DBG
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
multiline_comment|/* reset status register to avoid losing errors: */
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
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_read: PYXIS ERR was 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* if Type1 access, must set PYXIS CFG */
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
id|DBG
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
multiline_comment|/* access configuration space: */
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
multiline_comment|/*&n;&t; * david.rusling@reo.mts.dec.com.  This code is needed for the&n;&t; * EB64+ as it does not generate a machine check (why I don&squot;t&n;&t; * know).  When we build kernels for one particular platform&n;&t; * then we can make this conditional on the type.&n;&t; */
macro_line|#if 0
id|draina
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* now look for any errors */
id|stat0
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_IOC_PYXIS_ERR
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_read: PYXIS ERR after read 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat0
op_amp
l_int|0x8280U
)paren
(brace
multiline_comment|/* is any error bit set? */
multiline_comment|/* if not NDEV, print status */
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
l_string|&quot;PYXIS.c:conf_read: got stat0=%x&bslash;n&quot;
comma
id|stat0
)paren
suffix:semicolon
)brace
multiline_comment|/* reset error status: */
op_star
(paren
id|vulp
)paren
id|PYXIS_IOC_PYXIS_ERR
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
multiline_comment|/* if Type1 access, must reset IOC CFG so normal IO space ops work */
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
)brace
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_read(): finished&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|conf_write
r_static
r_void
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
id|pyxis_cfg
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to keep gcc quiet */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* avoid getting hit by machine check */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* reset status register to avoid losing errors: */
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
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_write: PYXIS ERR was 0x%x&bslash;n&quot;
comma
id|stat0
)paren
)paren
suffix:semicolon
multiline_comment|/* if Type1 access, must set PYXIS CFG */
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
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_read: TYPE1 access&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|draina
c_func
(paren
)paren
suffix:semicolon
id|PYXIS_mcheck_expected
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* access configuration space: */
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
id|PYXIS_mcheck_expected
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if Type1 access, must reset IOC CFG so normal IO space ops work */
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
)brace
id|DBG
c_func
(paren
(paren
l_string|&quot;conf_write(): finished&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pcibios_read_config_byte
r_int
id|pcibios_read_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
op_star
id|value
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
op_star
id|value
op_assign
l_int|0xff
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
OL
l_int|0
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pcibios_read_config_word
r_int
id|pcibios_read_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|value
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
op_star
id|value
op_assign
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|0x1
)paren
(brace
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
)brace
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
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pcibios_read_config_dword
r_int
id|pcibios_read_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|value
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
op_star
id|value
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|0x3
)paren
(brace
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
)brace
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
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pcibios_write_config_byte
r_int
id|pcibios_write_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
id|value
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
OL
l_int|0
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pcibios_write_config_word
r_int
id|pcibios_write_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|value
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
OL
l_int|0
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pcibios_write_config_dword
r_int
id|pcibios_write_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|value
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
OL
l_int|0
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
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
DECL|function|pyxis_init
r_int
r_int
id|pyxis_init
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
r_int
r_int
id|pyxis_err
suffix:semicolon
multiline_comment|/* &n;&t; * Set up error reporting.&n;&t; */
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
multiline_comment|/*&n;&t; * Set up the PCI-&gt;physical memory translation windows.&n;&t; * For now, windows 1,2 and 3 are disabled.  In the future, we may&n;&t; * want to use them to do scatter/gather DMA.  Window 0&n;&t; * goes at 1 GB and is 1 GB large.&n;&t; */
op_star
(paren
id|vuip
)paren
id|PYXIS_W0_BASE
op_assign
l_int|1U
op_or
(paren
id|PYXIS_DMA_WIN_BASE
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
id|PYXIS_DMA_WIN_SIZE
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
multiline_comment|/*&n;&t; * check ASN in HWRPB for validity, report if bad&n;&t; */
r_if
c_cond
(paren
id|hwrpb-&gt;max_asn
op_ne
id|MAX_ASN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PYXIS_init: max ASN from HWRPB is bad (0x%lx)&bslash;n&quot;
comma
id|hwrpb-&gt;max_asn
)paren
suffix:semicolon
id|hwrpb-&gt;max_asn
op_assign
id|MAX_ASN
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Finally, clear the PYXIS_CFG register, which gets used&n;&t; *  for PCI Config Space accesses. That is the way&n;&t; *  we want to use it, and we do not want to depend on&n;&t; *  what ARC or SRM might have left behind...&n;&t; */
(brace
r_int
r_int
id|pyxis_cfg
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
macro_line|#if 0
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
)brace
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
r_int
r_int
id|pyxis_hae_io
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_IO
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;PYXIS_init: HAE_MEM was 0x%x&bslash;n&quot;
comma
id|pyxis_hae_mem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PYXIS_init: HAE_IO was 0x%x&bslash;n&quot;
comma
id|pyxis_hae_io
)paren
suffix:semicolon
macro_line|#endif
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_MEM
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|pyxis_hae_mem
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_MEM
suffix:semicolon
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
id|pyxis_hae_io
op_assign
op_star
(paren
id|vuip
)paren
id|PYXIS_HAE_IO
suffix:semicolon
)brace
r_return
id|mem_start
suffix:semicolon
)brace
DECL|function|pyxis_pci_clr_err
r_int
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
id|DBG
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pyxis_machine_check
r_void
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
macro_line|#ifdef DEBUG_MCHECK_DUMP
(brace
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|la_ptr
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
id|mchk_header-&gt;size
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
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
)brace
)brace
macro_line|#endif /* DEBUG_MCHECK_DUMP */
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
multiline_comment|/* &amp;&amp; (mchk_sysdata-&gt;epic_dcsr &amp;&amp; 0x0c00UL)*/
)paren
(brace
id|DBG
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
macro_line|#if 1
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
macro_line|#endif
)brace
eof