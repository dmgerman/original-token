multiline_comment|/*&n; * QSpan pci routines.&n; * Most 8xx boards use the QSpan PCI bridge.  The config address register&n; * is located 0x500 from the base of the bridge control/status registers.&n; * The data register is located at 0x504.&n; * This is a two step operation.  First, the address register is written,&n; * then the data register is read/written as required.&n; * I don&squot;t know what to do about interrupts (yet).&n; *&n; * The RPX Classic implementation shares a chip select for normal&n; * PCI access and QSpan control register addresses.  The selection is&n; * further selected by a bit setting in a board control register.&n; * Although it should happen, we disable interrupts during this operation&n; * to make sure some driver doesn&squot;t accidently access the PCI while&n; * we have switched the chip select.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * This blows......&n; * When reading the configuration space, if something does not respond&n; * the bus times out and we get a machine check interrupt.  So, the&n; * good ol&squot; exception tables come to mind to trap it and return some&n; * value.&n; *&n; * On an error we just return a -1, since that is what the caller wants&n; * returned if nothing is present.  I copied this from __get_user_asm,&n; * with the only difference of returning -1 instead of EFAULT.&n; * There is an associated hack in the machine check trap code.&n; *&n; * The QSPAN is also a big endian device, that is it makes the PCI&n; * look big endian to us.  This presents a problem for the Linux PCI&n; * functions, which assume little endian.  For example, we see the&n; * first 32-bit word like this:&n; *&t;------------------------&n; *&t;| Device ID | Vendor ID |&n; *&t;------------------------&n; * If we read/write as a double word, that&squot;s OK.  But in our world,&n; * when read as a word, device ID is at location 0, not location 2 as&n; * the little endian PCI would believe.  We have to switch bits in&n; * the PCI addresses given to us to get the data to/from the correct&n; * byte lanes.&n; *&n; * The QSPAN only supports 4 bits of &quot;slot&quot; in the dev_fn instead of 5.&n; * It always forces the MS bit to zero.  Therefore, dev_fn values&n; * greater than 128 are returned as &quot;no device found&quot; errors.&n; *&n; * The QSPAN can only perform long word (32-bit) configuration cycles.&n; * The &quot;offset&quot; must have the two LS bits set to zero.  Read operations&n; * require we read the entire word and then sort out what should be&n; * returned.  Write operations other than long word require that we&n; * read the long word, update the proper word or byte, then write the&n; * entire long word back.&n; *&n; * PCI Bridge hack.  We assume (correctly) that bus 0 is the primary&n; * PCI bus from the QSPAN.  If we are called with a bus number other&n; * than zero, we create a Type 1 configuration access that a downstream&n; * PCI bridge will interpret.&n; */
DECL|macro|__get_qspan_pci_config
mdefine_line|#define __get_qspan_pci_config(x, addr, op)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;op&quot; %0,0(%1)&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;eieio&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li %0,-1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(x) : &quot;r&quot;(addr) : &quot; %0&quot;)
DECL|macro|QS_CONFIG_ADDR
mdefine_line|#define QS_CONFIG_ADDR&t;((volatile uint *)(PCI_CSR_ADDR + 0x500))
DECL|macro|QS_CONFIG_DATA
mdefine_line|#define QS_CONFIG_DATA&t;((volatile uint *)(PCI_CSR_ADDR + 0x504))
DECL|macro|mk_config_addr
mdefine_line|#define mk_config_addr(bus, dev, offset) &bslash;&n;&t;(((bus)&lt;&lt;16) | ((dev)&lt;&lt;8) | (offset &amp; 0xfc))
DECL|macro|mk_config_type1
mdefine_line|#define mk_config_type1(bus, dev, offset) &bslash;&n;&t;mk_config_addr(bus, dev, offset) | 1;
DECL|function|qspan_pcibios_read_config_byte
r_int
id|qspan_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
(brace
id|uint
id|temp
suffix:semicolon
id|u_char
op_star
id|cp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xff
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
id|__get_qspan_pci_config
c_func
(paren
id|temp
comma
id|QS_CONFIG_DATA
comma
l_string|&quot;lwz&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
id|offset
op_xor_assign
l_int|0x03
suffix:semicolon
id|cp
op_assign
(paren
(paren
id|u_char
op_star
)paren
op_amp
id|temp
)paren
op_plus
(paren
id|offset
op_amp
l_int|0x03
)paren
suffix:semicolon
op_star
id|val
op_assign
op_star
id|cp
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_read_config_word
r_int
id|qspan_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|uint
id|temp
suffix:semicolon
id|ushort
op_star
id|sp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xffff
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
id|__get_qspan_pci_config
c_func
(paren
id|temp
comma
id|QS_CONFIG_DATA
comma
l_string|&quot;lwz&quot;
)paren
suffix:semicolon
id|offset
op_xor_assign
l_int|0x02
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
id|sp
op_assign
(paren
(paren
id|ushort
op_star
)paren
op_amp
id|temp
)paren
op_plus
(paren
(paren
id|offset
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
op_star
id|val
op_assign
op_star
id|sp
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_read_config_dword
r_int
id|qspan_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xffffffff
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
id|__get_qspan_pci_config
c_func
(paren
op_star
id|val
comma
id|QS_CONFIG_DATA
comma
l_string|&quot;lwz&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_write_config_byte
r_int
id|qspan_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
(brace
id|uint
id|temp
suffix:semicolon
id|u_char
op_star
id|cp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|qspan_pcibios_read_config_dword
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
op_amp
id|temp
)paren
suffix:semicolon
id|offset
op_xor_assign
l_int|0x03
suffix:semicolon
id|cp
op_assign
(paren
(paren
id|u_char
op_star
)paren
op_amp
id|temp
)paren
op_plus
(paren
id|offset
op_amp
l_int|0x03
)paren
suffix:semicolon
op_star
id|cp
op_assign
id|val
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
op_star
id|QS_CONFIG_DATA
op_assign
id|temp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_write_config_word
r_int
id|qspan_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
id|uint
id|temp
suffix:semicolon
id|ushort
op_star
id|sp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|qspan_pcibios_read_config_dword
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
comma
op_amp
id|temp
)paren
suffix:semicolon
id|offset
op_xor_assign
l_int|0x02
suffix:semicolon
id|sp
op_assign
(paren
(paren
id|ushort
op_star
)paren
op_amp
id|temp
)paren
op_plus
(paren
(paren
id|offset
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
op_star
id|sp
op_assign
id|val
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
op_star
id|QS_CONFIG_DATA
op_assign
id|temp
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_write_config_dword
r_int
id|qspan_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
macro_line|#ifdef CONFIG_RPXCLASSIC
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|7
)paren
op_logical_or
(paren
id|dev_fn
OG
l_int|127
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
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
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_and_assign
op_complement
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_addr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
r_else
op_star
id|QS_CONFIG_ADDR
op_assign
id|mk_config_type1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|QS_CONFIG_DATA
op_assign
id|val
suffix:semicolon
macro_line|#ifdef CONFIG_RPXCLASSIC
op_star
(paren
(paren
id|uint
op_star
)paren
id|RPX_CSR_ADDR
)paren
op_or_assign
id|BCSR2_QSPACESEL
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|qspan_pcibios_find_device
r_int
id|qspan_pcibios_find_device
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|dev_id
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus_ptr
comma
r_int
r_char
op_star
id|dev_fn_ptr
)paren
(brace
r_int
id|num
comma
id|devfn
suffix:semicolon
r_int
r_int
id|x
comma
id|vendev
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_eq
l_int|0xffff
)paren
r_return
id|PCIBIOS_BAD_VENDOR_ID
suffix:semicolon
id|vendev
op_assign
(paren
id|dev_id
op_lshift
l_int|16
)paren
op_plus
id|vendor
suffix:semicolon
id|num
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|devfn
op_assign
l_int|0
suffix:semicolon
id|devfn
OL
l_int|32
suffix:semicolon
id|devfn
op_increment
)paren
(brace
id|qspan_pcibios_read_config_dword
c_func
(paren
l_int|0
comma
id|devfn
op_lshift
l_int|3
comma
id|PCI_VENDOR_ID
comma
op_amp
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
id|vendev
)paren
(brace
r_if
c_cond
(paren
id|index
op_eq
id|num
)paren
(brace
op_star
id|bus_ptr
op_assign
l_int|0
suffix:semicolon
op_star
id|dev_fn_ptr
op_assign
id|devfn
op_lshift
l_int|3
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
op_increment
id|num
suffix:semicolon
)brace
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|function|qspan_pcibios_find_class
r_int
id|qspan_pcibios_find_class
c_func
(paren
r_int
r_int
id|class_code
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus_ptr
comma
r_int
r_char
op_star
id|dev_fn_ptr
)paren
(brace
r_int
id|devnr
comma
id|x
comma
id|num
suffix:semicolon
id|num
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|devnr
op_assign
l_int|0
suffix:semicolon
id|devnr
OL
l_int|32
suffix:semicolon
id|devnr
op_increment
)paren
(brace
id|qspan_pcibios_read_config_dword
c_func
(paren
l_int|0
comma
id|devnr
op_lshift
l_int|3
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_rshift
l_int|8
)paren
op_eq
id|class_code
)paren
(brace
r_if
c_cond
(paren
id|index
op_eq
id|num
)paren
(brace
op_star
id|bus_ptr
op_assign
l_int|0
suffix:semicolon
op_star
id|dev_fn_ptr
op_assign
id|devnr
op_lshift
l_int|3
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
op_increment
id|num
suffix:semicolon
)brace
)brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_void
id|__init
DECL|function|m8xx_pcibios_fixup
id|m8xx_pcibios_fixup
c_func
(paren
r_void
)paren
)paren
(brace
multiline_comment|/* Lots to do here, all board and configuration specific. */
)brace
r_void
id|__init
DECL|function|m8xx_setup_pci_ptrs
id|m8xx_setup_pci_ptrs
c_func
(paren
r_void
)paren
)paren
(brace
id|set_config_access_method
c_func
(paren
id|qspan
)paren
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
id|m8xx_pcibios_fixup
suffix:semicolon
)brace
eof
