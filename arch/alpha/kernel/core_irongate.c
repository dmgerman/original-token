multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_irongate.c&n; *&n; * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).&n; *&n; *&t;Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; *&n; * Code common to all IRONGATE core logic chips.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_irongate.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/*&n; * NOTE: Herein lie back-to-back mb instructions.  They are magic.&n; * One plausible explanation is that the I/O controller does not properly&n; * handle the system transaction.  Another involves timing.  Ho hum.&n; */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)
macro_line|#endif
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address accordingly.  It is therefore not safe&n; * to have concurrent invocations to configuration space access&n; * routines, but there really shouldn&squot;t be any need for this.&n; *&n; *&t;addr[31:24]&t;&t;reserved&n; *&t;addr[23:16]&t;&t;bus number (8 bits = 128 possible buses)&n; *&t;addr[15:11]&t;&t;Device number (5 bits)&n; *&t;addr[10: 8]&t;&t;function number&n; *&t;addr[ 7: 2]&t;&t;register number&n; *&n; * For IRONGATE:&n; *    if (bus = addr[23:16]) == 0&n; *    then&n; *&t;  type 0 config cycle:&n; *&t;      addr_on_pci[31:11] = id selection for device = addr[15:11]&n; *&t;      addr_on_pci[10: 2] = addr[10: 2] ???&n; *&t;      addr_on_pci[ 1: 0] = 00&n; *    else&n; *&t;  type 1 config cycle (pass on with no decoding):&n; *&t;      addr_on_pci[31:24] = 0&n; *&t;      addr_on_pci[23: 2] = addr[23: 2]&n; *&t;      addr_on_pci[ 1: 0] = 01&n; *    fi&n; *&n; * Notes:&n; *&t;The function number selects which function of a multi-function device&n; *&t;(e.g., SCSI and Ethernet).&n; *&n; *&t;The register selects a DWORD (32 bit) register offset.&t;Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
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
r_int
r_int
id|addr
suffix:semicolon
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
id|DBG_CFG
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, &quot;
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
op_star
id|type1
op_assign
(paren
id|bus
op_ne
l_int|0
)paren
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
id|addr
op_or_assign
id|IRONGATE_CONF
suffix:semicolon
op_star
id|pci_addr
op_assign
id|addr
suffix:semicolon
id|DBG_CFG
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
DECL|function|irongate_read_config_byte
id|irongate_read_config_byte
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_read_config_word
id|irongate_read_config_word
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_read_config_dword
id|irongate_read_config_dword
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_byte
id|irongate_write_config_byte
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|__kernel_stb
c_func
(paren
id|value
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_word
id|irongate_write_config_word
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|__kernel_stw
c_func
(paren
id|value
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|irongate_write_config_dword
id|irongate_write_config_dword
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
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
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
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|irongate_pci_ops
r_struct
id|pci_ops
id|irongate_pci_ops
op_assign
(brace
id|read_byte
suffix:colon
id|irongate_read_config_byte
comma
id|read_word
suffix:colon
id|irongate_read_config_word
comma
id|read_dword
suffix:colon
id|irongate_read_config_dword
comma
id|write_byte
suffix:colon
id|irongate_write_config_byte
comma
id|write_word
suffix:colon
id|irongate_write_config_word
comma
id|write_dword
suffix:colon
id|irongate_write_config_dword
)brace
suffix:semicolon
"&f;"
macro_line|#if 0
r_static
r_void
id|irongate_register_dump
c_func
(paren
r_const
r_char
op_star
id|function_name
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Irongate registers:&bslash;n&quot;
l_string|&quot;&bslash;tdev_vendor&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tstat_cmd&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tclass&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tlatency&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar0&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar1&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbar2&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[3]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[4]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd0[5]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tcapptr&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd1[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr10&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr32&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbacsr54&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd2[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdrammap&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdramtm&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tdramms&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd3[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbiu0&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tbiusip&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd4[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd4[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tmro&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd5[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;twhami&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tpciarb&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tpcicfg&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[0]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[1]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[2]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[3]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;trsrvd6[4]&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpcap&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpstat&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpcmd&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpva&bslash;t&bslash;t0x%08x&bslash;n&quot;
l_string|&quot;&bslash;tagpmode&bslash;t&bslash;t0x%08x&bslash;n&quot;
comma
id|function_name
comma
id|IRONGATE0-&gt;dev_vendor
comma
id|IRONGATE0-&gt;stat_cmd
comma
id|IRONGATE0
op_member_access_from_pointer
r_class
comma
id|IRONGATE0-&gt;latency
comma
id|IRONGATE0-&gt;bar0
comma
id|IRONGATE0-&gt;bar1
comma
id|IRONGATE0-&gt;bar2
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|3
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|4
)braket
comma
id|IRONGATE0-&gt;rsrvd0
(braket
l_int|5
)braket
comma
id|IRONGATE0-&gt;capptr
comma
id|IRONGATE0-&gt;rsrvd1
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd1
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;bacsr10
comma
id|IRONGATE0-&gt;bacsr32
comma
id|IRONGATE0-&gt;bacsr54
comma
id|IRONGATE0-&gt;rsrvd2
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;drammap
comma
id|IRONGATE0-&gt;dramtm
comma
id|IRONGATE0-&gt;dramms
comma
id|IRONGATE0-&gt;rsrvd3
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;biu0
comma
id|IRONGATE0-&gt;biusip
comma
id|IRONGATE0-&gt;rsrvd4
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd4
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;mro
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd5
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;whami
comma
id|IRONGATE0-&gt;pciarb
comma
id|IRONGATE0-&gt;pcicfg
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|0
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|1
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|2
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|3
)braket
comma
id|IRONGATE0-&gt;rsrvd6
(braket
l_int|4
)braket
comma
id|IRONGATE0-&gt;agpcap
comma
id|IRONGATE0-&gt;agpstat
comma
id|IRONGATE0-&gt;agpcmd
comma
id|IRONGATE0-&gt;agpva
comma
id|IRONGATE0-&gt;agpmode
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irongate_register_dump
mdefine_line|#define irongate_register_dump(x)
macro_line|#endif
r_int
DECL|function|irongate_pci_clr_err
id|irongate_pci_clr_err
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|nmi_ctl
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|IRONGATE_jd
suffix:semicolon
id|again
suffix:colon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron stat_cmd %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
multiline_comment|/* re-read to force write */
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron dramms %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
id|IRONGATE0-&gt;dramms
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/* Clear ALI NMI */
id|nmi_ctl
op_assign
id|inb
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_or_assign
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
r_if
c_cond
(paren
id|IRONGATE_jd
op_amp
l_int|0x300
)paren
r_goto
id|again
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|irongate_init_arch
id|irongate_init_arch
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
id|irongate_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|irongate_register_dump
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
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
id|IRONGATE_CONF
suffix:semicolon
id|hose-&gt;index
op_assign
l_int|0
suffix:semicolon
)brace
eof
