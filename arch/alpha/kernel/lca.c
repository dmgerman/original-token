multiline_comment|/*&n; * Code common to all LCA chips.&n; *&n; * Written by David Mosberger (davidm@cs.arizona.edu) with some code&n; * taken from Dave Rusling&squot;s (david.rusling@reo.mts.dec.com) 32-bit&n; * bios code.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|##include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
multiline_comment|/*&n; * Machine check reasons.  Defined according to PALcode sources&n; * (osf.h and platform.h).&n; */
DECL|macro|MCHK_K_TPERR
mdefine_line|#define MCHK_K_TPERR&t;&t;0x0080
DECL|macro|MCHK_K_TCPERR
mdefine_line|#define MCHK_K_TCPERR&t;&t;0x0082
DECL|macro|MCHK_K_HERR
mdefine_line|#define MCHK_K_HERR&t;&t;0x0084
DECL|macro|MCHK_K_ECC_C
mdefine_line|#define MCHK_K_ECC_C&t;&t;0x0086
DECL|macro|MCHK_K_ECC_NC
mdefine_line|#define MCHK_K_ECC_NC&t;&t;0x0088
DECL|macro|MCHK_K_UNKNOWN
mdefine_line|#define MCHK_K_UNKNOWN&t;&t;0x008A
DECL|macro|MCHK_K_CACKSOFT
mdefine_line|#define MCHK_K_CACKSOFT&t;&t;0x008C
DECL|macro|MCHK_K_BUGCHECK
mdefine_line|#define MCHK_K_BUGCHECK&t;&t;0x008E
DECL|macro|MCHK_K_OS_BUGCHECK
mdefine_line|#define MCHK_K_OS_BUGCHECK&t;0x0090
DECL|macro|MCHK_K_DCPERR
mdefine_line|#define MCHK_K_DCPERR&t;&t;0x0092
DECL|macro|MCHK_K_ICPERR
mdefine_line|#define MCHK_K_ICPERR&t;&t;0x0094
multiline_comment|/*&n; * Platform-specific machine-check reasons:&n; */
DECL|macro|MCHK_K_SIO_SERR
mdefine_line|#define MCHK_K_SIO_SERR&t;&t;0x204&t;/* all platforms so far */
DECL|macro|MCHK_K_SIO_IOCHK
mdefine_line|#define MCHK_K_SIO_IOCHK&t;0x206&t;/* all platforms so far */
DECL|macro|MCHK_K_DCSR
mdefine_line|#define MCHK_K_DCSR&t;&t;0x208&t;/* all but Noname */
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
DECL|variable|LCA_DMA_WIN_BASE
r_int
r_int
id|LCA_DMA_WIN_BASE
op_assign
id|LCA_DMA_WIN_BASE_DEFAULT
suffix:semicolon
DECL|variable|LCA_DMA_WIN_SIZE
r_int
r_int
id|LCA_DMA_WIN_SIZE
op_assign
id|LCA_DMA_WIN_SIZE_DEFAULT
suffix:semicolon
macro_line|#endif /* SRM_SETUP */
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address and setup the LCA_IOC_CONF register&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | | | | | | | | | | | | | | |F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., SCSI and Ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
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
)paren
(brace
r_int
r_int
id|addr
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
r_int
id|func
op_assign
id|device_fn
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/* type 0 configuration cycle: */
r_if
c_cond
(paren
id|device
OG
l_int|12
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
(paren
id|vulp
)paren
id|LCA_IOC_CONF
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
(paren
l_int|1
op_lshift
(paren
l_int|11
op_plus
id|device
)paren
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|where
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* type 1 configuration cycle: */
op_star
(paren
id|vulp
)paren
id|LCA_IOC_CONF
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
id|where
suffix:semicolon
)brace
op_star
id|pci_addr
op_assign
id|addr
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
)paren
(brace
r_int
r_int
id|flags
comma
id|code
comma
id|stat0
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* reset status register to avoid loosing errors: */
id|stat0
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
op_assign
id|stat0
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
id|draina
c_func
(paren
)paren
suffix:semicolon
id|stat0
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
suffix:semicolon
r_if
c_cond
(paren
id|stat0
op_amp
id|LCA_IOC_STAT0_ERR
)paren
(brace
id|code
op_assign
(paren
(paren
id|stat0
op_rshift
id|LCA_IOC_STAT0_CODE_SHIFT
)paren
op_amp
id|LCA_IOC_STAT0_CODE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lca.c:conf_read: got stat0=%lx&bslash;n&quot;
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
id|LCA_IOC_STAT0
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
)paren
(brace
r_int
r_int
id|flags
comma
id|code
comma
id|stat0
suffix:semicolon
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
multiline_comment|/* reset status register to avoid loosing errors: */
id|stat0
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
op_assign
id|stat0
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
id|draina
c_func
(paren
)paren
suffix:semicolon
id|stat0
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_STAT0
suffix:semicolon
r_if
c_cond
(paren
id|stat0
op_amp
id|LCA_IOC_STAT0_ERR
)paren
(brace
id|code
op_assign
(paren
(paren
id|stat0
op_rshift
id|LCA_IOC_STAT0_CODE_SHIFT
)paren
op_amp
id|LCA_IOC_STAT0_CODE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lca.c:conf_write: got stat0=%lx&bslash;n&quot;
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
id|LCA_IOC_STAT0
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
)brace
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
id|LCA_CONF
suffix:semicolon
r_int
r_int
id|pci_addr
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
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|lca_init
r_int
r_int
id|lca_init
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
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
multiline_comment|/* check window 0 for enabled and mapped to 0 */
r_if
c_cond
(paren
(paren
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE0
op_amp
(paren
l_int|1UL
op_lshift
l_int|33
)paren
)paren
op_logical_and
(paren
op_star
(paren
id|vulp
)paren
id|LCA_IOC_T_BASE0
op_eq
l_int|0
)paren
)paren
(brace
id|LCA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE0
op_amp
l_int|0xffffffffUL
suffix:semicolon
id|LCA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_MASK0
op_amp
l_int|0xffffffffUL
suffix:semicolon
id|LCA_DMA_WIN_SIZE
op_add_assign
l_int|1
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;lca_init: using Window 0 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lca_init: BASE 0x%lx MASK 0x%lx TRANS 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE0
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_MASK0
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_T_BASE0
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
multiline_comment|/* check window 2 for enabled and mapped to 0 */
r_if
c_cond
(paren
(paren
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE1
op_amp
(paren
l_int|1UL
op_lshift
l_int|33
)paren
)paren
op_logical_and
(paren
op_star
(paren
id|vulp
)paren
id|LCA_IOC_T_BASE1
op_eq
l_int|0
)paren
)paren
(brace
id|LCA_DMA_WIN_BASE
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE1
op_amp
l_int|0xffffffffUL
suffix:semicolon
id|LCA_DMA_WIN_SIZE
op_assign
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_MASK1
op_amp
l_int|0xffffffffUL
suffix:semicolon
id|LCA_DMA_WIN_SIZE
op_add_assign
l_int|1
suffix:semicolon
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;lca_init: using Window 1 settings&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lca_init: BASE 0x%lx MASK 0x%lx TRANS 0x%lx&bslash;n&quot;
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE1
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_MASK1
comma
op_star
(paren
id|vulp
)paren
id|LCA_IOC_T_BASE1
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
multiline_comment|/* we must use our defaults... */
macro_line|#endif /* SRM_SETUP */
(brace
multiline_comment|/*&n;&t; * Set up the PCI-&gt;physical memory translation windows.&n;&t; * For now, window 1 is disabled.  In the future, we may&n;&t; * want to use it to do scatter/gather DMA.  Window 0&n;&t; * goes at 1 GB and is 1 GB large.&n;&t; */
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE1
op_assign
l_int|0UL
op_lshift
l_int|33
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_BASE0
op_assign
l_int|1UL
op_lshift
l_int|33
op_or
id|LCA_DMA_WIN_BASE
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|LCA_IOC_W_MASK0
op_assign
id|LCA_DMA_WIN_SIZE
op_minus
l_int|1
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|LCA_IOC_T_BASE0
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable PCI parity for now.  The NCR53c810 chip has&n;&t; * troubles meeting the PCI spec which results in&n;&t; * data parity errors.&n;&t; */
op_star
(paren
id|vulp
)paren
id|LCA_IOC_PAR_DIS
op_assign
l_int|1UL
op_lshift
l_int|5
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
multiline_comment|/*&n; * Constants used during machine-check handling.  I suppose these&n; * could be moved into lca.h but I don&squot;t see much reason why anybody&n; * else would want to use them.&n; */
DECL|macro|ESR_EAV
mdefine_line|#define ESR_EAV&t;&t;(1UL&lt;&lt; 0)&t;/* error address valid */
DECL|macro|ESR_CEE
mdefine_line|#define ESR_CEE&t;&t;(1UL&lt;&lt; 1)&t;/* correctable error */
DECL|macro|ESR_UEE
mdefine_line|#define ESR_UEE&t;&t;(1UL&lt;&lt; 2)&t;/* uncorrectable error */
DECL|macro|ESR_WRE
mdefine_line|#define ESR_WRE&t;&t;(1UL&lt;&lt; 3)&t;/* write-error */
DECL|macro|ESR_SOR
mdefine_line|#define ESR_SOR&t;&t;(1UL&lt;&lt; 4)&t;/* error source */
DECL|macro|ESR_CTE
mdefine_line|#define ESR_CTE&t;&t;(1UL&lt;&lt; 7)&t;/* cache-tag error */
DECL|macro|ESR_MSE
mdefine_line|#define ESR_MSE&t;&t;(1UL&lt;&lt; 9)&t;/* multiple soft errors */
DECL|macro|ESR_MHE
mdefine_line|#define ESR_MHE&t;&t;(1UL&lt;&lt;10)&t;/* multiple hard errors */
DECL|macro|ESR_NXM
mdefine_line|#define ESR_NXM&t;&t;(1UL&lt;&lt;12)&t;/* non-existent memory */
DECL|macro|IOC_ERR
mdefine_line|#define IOC_ERR&t;&t;(  1&lt;&lt;4)&t;/* ioc logs an error */
DECL|macro|IOC_CMD_SHIFT
mdefine_line|#define IOC_CMD_SHIFT&t;0
DECL|macro|IOC_CMD
mdefine_line|#define IOC_CMD&t;&t;(0xf&lt;&lt;IOC_CMD_SHIFT)
DECL|macro|IOC_CODE_SHIFT
mdefine_line|#define IOC_CODE_SHIFT&t;8
DECL|macro|IOC_CODE
mdefine_line|#define IOC_CODE&t;(0xf&lt;&lt;IOC_CODE_SHIFT)
DECL|macro|IOC_LOST
mdefine_line|#define IOC_LOST&t;(  1&lt;&lt;5)
DECL|macro|IOC_P_NBR
mdefine_line|#define IOC_P_NBR&t;((__u32) ~((1&lt;&lt;13) - 1))
DECL|function|mem_error
r_void
id|mem_error
(paren
r_int
r_int
id|esr
comma
r_int
r_int
id|ear
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    %s %s error to %s occurred at address %x&bslash;n&quot;
comma
op_star
(paren
(paren
id|esr
op_amp
id|ESR_CEE
)paren
ques
c_cond
l_string|&quot;Correctable&quot;
suffix:colon
(paren
id|esr
op_amp
id|ESR_UEE
)paren
ques
c_cond
l_string|&quot;Uncorrectable&quot;
suffix:colon
l_string|&quot;A&quot;
)paren
comma
(paren
id|esr
op_amp
id|ESR_WRE
)paren
ques
c_cond
l_string|&quot;write&quot;
suffix:colon
l_string|&quot;read&quot;
comma
(paren
id|esr
op_amp
id|ESR_SOR
)paren
ques
c_cond
l_string|&quot;memory&quot;
suffix:colon
l_string|&quot;b-cache&quot;
comma
(paren
r_int
)paren
(paren
id|ear
op_amp
l_int|0x1ffffff8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esr
op_amp
id|ESR_CTE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    A b-cache tag parity error was detected.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esr
op_amp
id|ESR_MSE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    Several other correctable errors occurred.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esr
op_amp
id|ESR_MHE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    Several other uncorrectable errors occurred.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esr
op_amp
id|ESR_NXM
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    Attempted to access non-existent memory.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|ioc_error
r_void
id|ioc_error
(paren
id|__u32
id|stat0
comma
id|__u32
id|stat1
)paren
(brace
r_static
r_const
r_char
op_star
r_const
id|pci_cmd
(braket
)braket
op_assign
(brace
l_string|&quot;Interrupt Acknowledge&quot;
comma
l_string|&quot;Special&quot;
comma
l_string|&quot;I/O Read&quot;
comma
l_string|&quot;I/O Write&quot;
comma
l_string|&quot;Rsvd 1&quot;
comma
l_string|&quot;Rsvd 2&quot;
comma
l_string|&quot;Memory Read&quot;
comma
l_string|&quot;Memory Write&quot;
comma
l_string|&quot;Rsvd3&quot;
comma
l_string|&quot;Rsvd4&quot;
comma
l_string|&quot;Configuration Read&quot;
comma
l_string|&quot;Configuration Write&quot;
comma
l_string|&quot;Memory Read Multiple&quot;
comma
l_string|&quot;Dual Address&quot;
comma
l_string|&quot;Memory Read Line&quot;
comma
l_string|&quot;Memory Write and Invalidate&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
r_const
id|err_name
(braket
)braket
op_assign
(brace
l_string|&quot;exceeded retry limit&quot;
comma
l_string|&quot;no device&quot;
comma
l_string|&quot;bad data parity&quot;
comma
l_string|&quot;target abort&quot;
comma
l_string|&quot;bad address parity&quot;
comma
l_string|&quot;page table read error&quot;
comma
l_string|&quot;invalid page&quot;
comma
l_string|&quot;data error&quot;
)brace
suffix:semicolon
r_int
id|code
op_assign
(paren
id|stat0
op_amp
id|IOC_CODE
)paren
op_rshift
id|IOC_CODE_SHIFT
suffix:semicolon
r_int
id|cmd
op_assign
(paren
id|stat0
op_amp
id|IOC_CMD
)paren
op_rshift
id|IOC_CMD_SHIFT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    %s initiated PCI %s cycle to address %x&quot;
l_string|&quot; failed due to %s.&bslash;n&quot;
comma
id|code
OG
l_int|3
ques
c_cond
l_string|&quot;PCI&quot;
suffix:colon
l_string|&quot;CPU&quot;
comma
id|pci_cmd
(braket
id|cmd
)braket
comma
id|stat1
comma
id|err_name
(braket
id|code
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
l_int|5
op_logical_or
id|code
op_eq
l_int|6
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    (Error occurred at PCI memory address %x.)&bslash;n&quot;
comma
(paren
id|stat0
op_amp
op_complement
id|IOC_P_NBR
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat0
op_amp
id|IOC_LOST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    Other PCI errors occurred simultaneously.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|lca_machine_check
r_void
id|lca_machine_check
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_const
r_char
op_star
id|reason
suffix:semicolon
r_union
id|el_lca
id|el
suffix:semicolon
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;lca: machine check (la=0x%lx,pc=0x%lx)&bslash;n&quot;
comma
id|la
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|el.c
op_assign
(paren
r_struct
id|el_common
op_star
)paren
id|la
suffix:semicolon
multiline_comment|/*&n;&t; * The first quadword after the common header always seems to&n;&t; * be the machine check reason---don&squot;t know why this isn&squot;t&n;&t; * part of the common header instead.  In the case of a long&n;&t; * logout frame, the upper 32 bits is the machine check&n;&t; * revision level, which we ignore for now.&n;&t; */
r_switch
c_cond
(paren
id|el.c-&gt;code
op_amp
l_int|0xffffffff
)paren
(brace
r_case
id|MCHK_K_TPERR
suffix:colon
id|reason
op_assign
l_string|&quot;tag parity error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_TCPERR
suffix:colon
id|reason
op_assign
l_string|&quot;tag control parity error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_HERR
suffix:colon
id|reason
op_assign
l_string|&quot;access to non-existent memory&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_ECC_C
suffix:colon
id|reason
op_assign
l_string|&quot;correctable ECC error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_ECC_NC
suffix:colon
id|reason
op_assign
l_string|&quot;non-correctable ECC error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_CACKSOFT
suffix:colon
id|reason
op_assign
l_string|&quot;MCHK_K_CACKSOFT&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* what&squot;s this? */
r_case
id|MCHK_K_BUGCHECK
suffix:colon
id|reason
op_assign
l_string|&quot;illegal exception in PAL mode&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_OS_BUGCHECK
suffix:colon
id|reason
op_assign
l_string|&quot;callsys in kernel mode&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_DCPERR
suffix:colon
id|reason
op_assign
l_string|&quot;d-cache parity error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_ICPERR
suffix:colon
id|reason
op_assign
l_string|&quot;i-cache parity error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_SIO_SERR
suffix:colon
id|reason
op_assign
l_string|&quot;SIO SERR occurred on on PCI bus&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_SIO_IOCHK
suffix:colon
id|reason
op_assign
l_string|&quot;SIO IOCHK occurred on ISA bus&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_DCSR
suffix:colon
id|reason
op_assign
l_string|&quot;MCHK_K_DCSR&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MCHK_K_UNKNOWN
suffix:colon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;reason for machine-check unknown (0x%lx)&quot;
comma
id|el.c-&gt;code
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|reason
op_assign
id|buf
suffix:semicolon
r_break
suffix:semicolon
)brace
id|wrmces
c_func
(paren
id|rdmces
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* reset machine check pending flag */
r_switch
c_cond
(paren
id|el.c-&gt;size
)paren
(brace
r_case
r_sizeof
(paren
r_struct
id|el_lca_mcheck_short
)paren
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;  Reason: %s (short frame%s, dc_stat=%lx):&bslash;n&quot;
comma
id|reason
comma
id|el.c-&gt;retry
ques
c_cond
l_string|&quot;, retryable&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|el.s-&gt;dc_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el.s-&gt;esr
op_amp
id|ESR_EAV
)paren
(brace
id|mem_error
c_func
(paren
id|el.s-&gt;esr
comma
id|el.s-&gt;ear
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|el.s-&gt;ioc_stat0
op_amp
id|IOC_ERR
)paren
(brace
id|ioc_error
c_func
(paren
id|el.s-&gt;ioc_stat0
comma
id|el.s-&gt;ioc_stat1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
r_sizeof
(paren
r_struct
id|el_lca_mcheck_long
)paren
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;  Reason: %s (long frame%s):&bslash;n&quot;
comma
id|reason
comma
id|el.c-&gt;retry
ques
c_cond
l_string|&quot;, retryable&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;    reason: %lx  exc_addr: %lx  dc_stat: %lx&bslash;n&quot;
comma
id|el.l-&gt;pt
(braket
l_int|0
)braket
comma
id|el.l-&gt;exc_addr
comma
id|el.l-&gt;dc_stat
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;    car: %lx&bslash;n&quot;
comma
id|el.l-&gt;car
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el.l-&gt;esr
op_amp
id|ESR_EAV
)paren
(brace
id|mem_error
c_func
(paren
id|el.l-&gt;esr
comma
id|el.l-&gt;ear
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|el.l-&gt;ioc_stat0
op_amp
id|IOC_ERR
)paren
(brace
id|ioc_error
c_func
(paren
id|el.l-&gt;ioc_stat0
comma
id|el.l-&gt;ioc_stat1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;  Unknown errorlog size %d&bslash;n&quot;
comma
id|el.c-&gt;size
)paren
suffix:semicolon
)brace
multiline_comment|/* dump the logout area to give all info: */
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|la
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
id|el.c-&gt;size
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
id|KERN_CRIT
l_string|&quot; +%8lx %016lx %016lx&bslash;n&quot;
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
multiline_comment|/*&n; * The following routines are needed to support the SPEED changing&n; * necessary to successfully manage the thermal problem on the AlphaBook1.&n; */
r_void
DECL|function|lca_clock_print
id|lca_clock_print
c_func
(paren
r_void
)paren
(brace
r_int
id|pmr_reg
suffix:semicolon
id|pmr_reg
op_assign
id|READ_PMR
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Status of clock control:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tPrimary clock divisor&bslash;t0x%x&bslash;n&quot;
comma
id|GET_PRIMARY
c_func
(paren
id|pmr_reg
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tOverride clock divisor&bslash;t0x%x&bslash;n&quot;
comma
id|GET_OVERRIDE
c_func
(paren
id|pmr_reg
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tInterrupt override is %s&bslash;n&quot;
comma
(paren
id|pmr_reg
op_amp
id|LCA_PMR_INTO
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tDMA override is %s&bslash;n&quot;
comma
(paren
id|pmr_reg
op_amp
id|LCA_PMR_DMAO
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
)brace
r_int
DECL|function|lca_get_clock
id|lca_get_clock
c_func
(paren
r_void
)paren
(brace
r_int
id|pmr_reg
suffix:semicolon
id|pmr_reg
op_assign
id|READ_PMR
suffix:semicolon
r_return
id|GET_PRIMARY
c_func
(paren
id|pmr_reg
)paren
suffix:semicolon
)brace
r_void
DECL|function|lca_clock_fiddle
id|lca_clock_fiddle
c_func
(paren
r_int
id|divisor
)paren
(brace
r_int
id|pmr_reg
suffix:semicolon
id|pmr_reg
op_assign
id|READ_PMR
suffix:semicolon
id|SET_PRIMARY_CLOCK
c_func
(paren
id|pmr_reg
comma
id|divisor
)paren
suffix:semicolon
multiline_comment|/* lca_norm_clock = divisor; */
id|WRITE_PMR
c_func
(paren
id|pmr_reg
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
eof
