multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SNI specific PCI support for RM200/RM300.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|function|mkaddr
r_extern
r_inline
id|u32
id|mkaddr
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
id|where
)paren
(brace
r_return
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|0x10
)paren
op_or
(paren
(paren
id|dev_fn
op_amp
l_int|0xff
)paren
op_lshift
l_int|0x08
)paren
op_or
(paren
id|where
op_amp
l_int|0xfc
)paren
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_fixup
r_static
r_int
r_int
id|sni_rm200_pcibios_fixup
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
multiline_comment|/*&n;&t; * TODO: Fix PCI_INTERRUPT_LINE register for onboard cards.&n;&t; * Take care of RM300 revision D boards for where the network&n;&t; * slot became an ordinary PCI slot.&n;&t; */
r_return
id|memory_start
suffix:semicolon
)brace
multiline_comment|/*&n; * We can&squot;t address 8 and 16 bit words directly.  Instead we have to&n; * read/write a 32bit word and mask/modify the data we actually want.&n; */
DECL|function|sni_rm200_pcibios_read_config_byte
r_static
r_int
id|sni_rm200_pcibios_read_config_byte
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
id|where
comma
r_int
r_char
op_star
id|val
)paren
(brace
id|u32
id|res
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_ADDRESS
op_assign
id|mkaddr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|res
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|val
op_assign
id|res
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_read_config_word
r_static
r_int
id|sni_rm200_pcibios_read_config_word
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
id|where
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|u32
id|res
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_ADDRESS
op_assign
id|mkaddr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|res
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
op_star
id|val
op_assign
id|res
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_read_config_dword
r_static
r_int
id|sni_rm200_pcibios_read_config_dword
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
id|where
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|u32
id|res
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_ADDRESS
op_assign
id|mkaddr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
id|le32_to_cpu
c_func
(paren
id|res
)paren
suffix:semicolon
op_star
id|val
op_assign
id|res
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_write_config_byte
r_static
r_int
id|sni_rm200_pcibios_write_config_byte
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
id|where
comma
r_int
r_char
id|val
)paren
(brace
multiline_comment|/* To do */
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_write_config_word
r_static
r_int
id|sni_rm200_pcibios_write_config_word
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
id|where
comma
r_int
r_int
id|val
)paren
(brace
multiline_comment|/* To do */
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sni_rm200_pcibios_write_config_dword
r_static
r_int
id|sni_rm200_pcibios_write_config_dword
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
id|where
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_ADDRESS
op_assign
id|mkaddr
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
op_assign
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|sni_rm200_pcibios_init
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
)paren
(brace
id|_pcibios_fixup
op_assign
id|sni_rm200_pcibios_fixup
suffix:semicolon
id|_pcibios_read_config_byte
op_assign
id|sni_rm200_pcibios_read_config_byte
suffix:semicolon
id|_pcibios_read_config_word
op_assign
id|sni_rm200_pcibios_read_config_word
suffix:semicolon
id|_pcibios_read_config_dword
op_assign
id|sni_rm200_pcibios_read_config_dword
suffix:semicolon
id|_pcibios_write_config_byte
op_assign
id|sni_rm200_pcibios_write_config_byte
suffix:semicolon
id|_pcibios_write_config_word
op_assign
id|sni_rm200_pcibios_write_config_word
suffix:semicolon
id|_pcibios_write_config_dword
op_assign
id|sni_rm200_pcibios_write_config_dword
suffix:semicolon
r_return
id|memory_start
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
eof
