multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SNI specific PCI support for RM200/RM300.&n; *&n; * Copyright (C) 1997 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|macro|mkaddr
mdefine_line|#define mkaddr(dev, where)                                                   &bslash;&n;do {                                                                         &bslash;&n;&t;if ((dev)-&gt;bus-&gt;number == 0)                                         &bslash;&n;&t;&t;return -1;                                                   &bslash;&n;&t;*(volatile u32 *)PCIMT_CONFIG_ADDRESS =                              &bslash;&n;&t;&t; ((dev-&gt;bus-&gt;number    &amp; 0xff) &lt;&lt; 0x10) |                    &bslash;&n;&t;         ((dev-&gt;devfn &amp; 0xff) &lt;&lt; 0x08) |                             &bslash;&n;&t;         (where  &amp; 0xfc);                                            &bslash;&n;} while(0);
macro_line|#if 0
multiline_comment|/* To do:  Bring this uptodate ...  */
r_static
r_void
id|pcimt_pcibios_fixup
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * TODO: Take care of RM300 revision D boards for where the&n;&t;&t; * network slot became an ordinary PCI slot.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|PCI_DEVFN
c_func
(paren
l_int|1
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/* Evil hack ...  */
id|set_cp0_config
c_func
(paren
id|CONF_CM_CMASK
comma
id|CONF_CM_CACHABLE_NO_WA
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|PCIMT_IRQ_SCSI
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|PCI_DEVFN
c_func
(paren
l_int|2
comma
l_int|0
)paren
)paren
(brace
id|dev-&gt;irq
op_assign
id|PCIMT_IRQ_ETHERNET
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev-&gt;irq
)paren
(brace
r_case
l_int|1
dot
dot
dot
l_int|4
suffix:colon
id|dev-&gt;irq
op_add_assign
id|PCIMT_IRQ_INTA
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PCI device on bus %d, dev %d, function %d &quot;
l_string|&quot;impossible interrupt configured.&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * We can&squot;t address 8 and 16 bit words directly.  Instead we have to&n; * read/write a 32bit word and mask/modify the data we actually want.&n; */
DECL|function|pcimt_read_config_byte
r_static
r_int
id|pcimt_read_config_byte
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
r_char
op_star
id|val
)paren
(brace
id|u32
id|res
suffix:semicolon
id|mkaddr
c_func
(paren
id|dev
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
DECL|function|pcimt_read_config_word
r_static
r_int
id|pcimt_read_config_word
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
id|mkaddr
c_func
(paren
id|dev
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
DECL|function|pcimt_read_config_dword
r_static
r_int
id|pcimt_read_config_dword
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
id|mkaddr
c_func
(paren
id|dev
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
DECL|function|pcimt_write_config_byte
r_static
r_int
id|pcimt_write_config_byte
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
r_char
id|val
)paren
(brace
id|mkaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|PCIMT_CONFIG_DATA
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
op_assign
id|val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write_config_word
r_static
r_int
id|pcimt_write_config_word
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
id|val
)paren
(brace
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
id|mkaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|PCIMT_CONFIG_DATA
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
op_assign
id|le16_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write_config_dword
r_static
r_int
id|pcimt_write_config_dword
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
id|mkaddr
c_func
(paren
id|dev
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
DECL|variable|sni_pci_ops
r_struct
id|pci_ops
id|sni_pci_ops
op_assign
(brace
id|pcimt_read_config_byte
comma
id|pcimt_read_config_word
comma
id|pcimt_read_config_dword
comma
id|pcimt_write_config_byte
comma
id|pcimt_write_config_word
comma
id|pcimt_write_config_dword
)brace
suffix:semicolon
r_void
id|__init
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
)brace
r_void
DECL|function|pcibios_update_resource
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resource
)paren
(brace
id|u32
r_new
comma
id|check
suffix:semicolon
r_int
id|reg
suffix:semicolon
r_new
op_assign
id|res-&gt;start
op_or
(paren
id|res-&gt;flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource
OL
l_int|6
)paren
(brace
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
l_int|4
op_star
id|resource
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resource
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|res-&gt;flags
op_or_assign
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
r_new
op_or_assign
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Somebody might have asked allocation of a non-standard resource */
r_return
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
r_new
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_new
op_xor
id|check
)paren
op_amp
(paren
(paren
r_new
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
ques
c_cond
id|PCI_BASE_ADDRESS_IO_MASK
suffix:colon
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error while updating region &quot;
l_string|&quot;%s/%d (%08x != %08x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|resource
comma
r_new
comma
id|check
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_ops
op_star
id|ops
op_assign
op_amp
id|sni_pci_ops
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
id|ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pcibios_enable_device
r_int
id|__init
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Not needed, since we enable all devices at startup.  */
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_align_resource
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
)paren
(brace
)brace
r_char
op_star
id|__init
DECL|function|pcibios_setup
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* Nothing to do for now.  */
r_return
id|str
suffix:semicolon
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
eof
