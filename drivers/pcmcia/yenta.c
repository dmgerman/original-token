multiline_comment|/*&n; * Regular lowlevel cardbus driver (&quot;yenta&quot;)&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;yenta.h&quot;
macro_line|#include &quot;i82365.h&quot;
multiline_comment|/* Don&squot;t ask.. */
DECL|macro|to_cycles
mdefine_line|#define to_cycles(ns)&t;((ns)/120)
DECL|macro|to_ns
mdefine_line|#define to_ns(cycles)&t;((cycles)*120)
multiline_comment|/* Fixme! */
DECL|function|yenta_inquire
r_static
r_int
id|yenta_inquire
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
id|socket_cap_t
op_star
id|cap
)paren
(brace
id|cap-&gt;features
op_assign
id|SS_CAP_PAGE_REGS
op_or
id|SS_CAP_PCCARD
op_or
id|SS_CAP_CARDBUS
suffix:semicolon
id|cap-&gt;irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
multiline_comment|/* irq 15,14,12,11,10,9,7,5,4,3 */
id|cap-&gt;map_size
op_assign
l_int|0x1000
suffix:semicolon
id|cap-&gt;pci_irq
op_assign
id|socket-&gt;irq
suffix:semicolon
id|cap-&gt;cardbus
op_assign
l_int|0
suffix:semicolon
id|cap-&gt;cb_bus
op_assign
l_int|NULL
suffix:semicolon
id|cap-&gt;bus
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_inquire()&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Silly interface. We convert the cardbus status to a internal status,&n; * and we probably really should keep it in cardbus status form and&n; * only convert for old-style 16-bit PCMCIA cards..&n; */
DECL|function|yenta_get_status
r_static
r_int
id|yenta_get_status
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_int
r_int
op_star
id|value
)paren
(brace
id|u32
id|state
op_assign
id|cb_readl
c_func
(paren
id|socket
comma
id|CB_SOCKET_STATE
)paren
suffix:semicolon
id|u8
id|status
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/* Convert from Yenta status to old-style status */
id|val
op_assign
(paren
id|state
op_amp
id|CB_CARDSTS
)paren
ques
c_cond
id|SS_STSCHG
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|state
op_amp
(paren
id|CB_CDETECT1
op_or
id|CB_CDETECT2
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|SS_DETECT
suffix:semicolon
id|val
op_or_assign
(paren
id|state
op_amp
id|CB_PWRCYCLE
)paren
ques
c_cond
id|SS_POWERON
op_or
id|SS_READY
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|state
op_amp
id|CB_CBCARD
)paren
ques
c_cond
id|SS_CARDBUS
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|state
op_amp
id|CB_3VCARD
)paren
ques
c_cond
id|SS_3VCARD
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|state
op_amp
id|CB_XVCARD
)paren
ques
c_cond
id|SS_XVCARD
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Get the old compatibility status too.. */
id|status
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_STATUS
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|status
op_amp
id|I365_CS_WRPROT
)paren
ques
c_cond
id|SS_WRPROT
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|status
op_amp
id|I365_CS_READY
)paren
ques
c_cond
id|SS_READY
suffix:colon
l_int|0
suffix:semicolon
id|val
op_or_assign
(paren
id|status
op_amp
id|I365_CS_POWERON
)paren
ques
c_cond
id|SS_POWERON
suffix:colon
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_get_status(%p)= %x&bslash;n&quot;
comma
id|socket
comma
id|val
)paren
suffix:semicolon
op_star
id|value
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_Vcc_power
r_static
r_int
id|yenta_Vcc_power
c_func
(paren
id|u32
id|control
)paren
(brace
r_switch
c_cond
(paren
(paren
id|control
op_rshift
id|CB_VCCCTRL
)paren
op_amp
id|CB_PWRBITS
)paren
(brace
r_case
id|CB_PWR5V
suffix:colon
r_return
l_int|50
suffix:semicolon
r_case
id|CB_PWR3V
suffix:colon
r_return
l_int|33
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|yenta_Vpp_power
r_static
r_int
id|yenta_Vpp_power
c_func
(paren
id|u32
id|control
)paren
(brace
r_switch
c_cond
(paren
(paren
id|control
op_rshift
id|CB_VPPCTRL
)paren
op_amp
id|CB_PWRBITS
)paren
(brace
r_case
id|CB_PWR12V
suffix:colon
r_return
l_int|120
suffix:semicolon
r_case
id|CB_PWR5V
suffix:colon
r_return
l_int|50
suffix:semicolon
r_case
id|CB_PWR3V
suffix:colon
r_return
l_int|33
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|yenta_get_socket
r_static
r_int
id|yenta_get_socket
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
id|socket_state_t
op_star
id|state
)paren
(brace
id|u32
id|control
op_assign
id|cb_readl
c_func
(paren
id|socket
comma
id|CB_SOCKET_CONTROL
)paren
suffix:semicolon
id|u8
id|reg
suffix:semicolon
id|state-&gt;Vcc
op_assign
id|yenta_Vcc_power
c_func
(paren
id|control
)paren
suffix:semicolon
id|state-&gt;Vpp
op_assign
id|yenta_Vpp_power
c_func
(paren
id|control
)paren
suffix:semicolon
id|state-&gt;io_irq
op_assign
id|socket-&gt;irq
suffix:semicolon
id|reg
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_POWER
)paren
suffix:semicolon
id|state-&gt;flags
op_assign
(paren
id|reg
op_amp
id|I365_PWR_AUTO
)paren
ques
c_cond
id|SS_PWR_AUTO
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;flags
op_or_assign
(paren
id|reg
op_amp
id|I365_PWR_OUT
)paren
ques
c_cond
id|SS_OUTPUT_ENA
suffix:colon
l_int|0
suffix:semicolon
id|reg
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_INTCTL
)paren
suffix:semicolon
id|state-&gt;flags
op_or_assign
(paren
id|reg
op_amp
id|I365_PC_RESET
)paren
ques
c_cond
l_int|0
suffix:colon
id|SS_RESET
suffix:semicolon
id|state-&gt;flags
op_or_assign
(paren
id|reg
op_amp
id|I365_PC_IOCARD
)paren
ques
c_cond
id|SS_IOCARD
suffix:colon
l_int|0
suffix:semicolon
id|reg
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_CSCINT
)paren
suffix:semicolon
id|state-&gt;csc_mask
op_assign
(paren
id|reg
op_amp
id|I365_CSC_DETECT
)paren
ques
c_cond
id|SS_DETECT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
(brace
id|state-&gt;csc_mask
op_or_assign
(paren
id|reg
op_amp
id|I365_CSC_STSCHG
)paren
ques
c_cond
id|SS_STSCHG
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|state-&gt;csc_mask
op_or_assign
(paren
id|reg
op_amp
id|I365_CSC_BVD1
)paren
ques
c_cond
id|SS_BATDEAD
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;csc_mask
op_or_assign
(paren
id|reg
op_amp
id|I365_CSC_BVD2
)paren
ques
c_cond
id|SS_BATWARN
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;csc_mask
op_or_assign
(paren
id|reg
op_amp
id|I365_CSC_READY
)paren
ques
c_cond
id|SS_READY
suffix:colon
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;yenta_get_socket(%p) = %d, %d&bslash;n&quot;
comma
id|socket
comma
id|state-&gt;Vcc
comma
id|state-&gt;Vpp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_set_socket
r_static
r_int
id|yenta_set_socket
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
id|socket_state_t
op_star
id|state
)paren
(brace
id|u8
id|reg
suffix:semicolon
id|u16
id|bridge
suffix:semicolon
id|u32
id|control
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_set_socket(%p, %d, %d, %x)&bslash;n&quot;
comma
id|socket
comma
id|state-&gt;Vcc
comma
id|state-&gt;Vpp
comma
id|state-&gt;flags
)paren
suffix:semicolon
id|bridge
op_assign
id|config_readw
c_func
(paren
id|socket
comma
id|CB_BRIDGE_CONTROL
)paren
suffix:semicolon
id|bridge
op_and_assign
op_complement
id|CB_BRIDGE_CRST
suffix:semicolon
id|bridge
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
ques
c_cond
id|CB_BRIDGE_CRST
suffix:colon
l_int|0
suffix:semicolon
id|config_writew
c_func
(paren
id|socket
comma
id|CB_BRIDGE_CONTROL
comma
id|bridge
)paren
suffix:semicolon
id|reg
op_assign
id|socket-&gt;irq
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
ques
c_cond
l_int|0
suffix:colon
id|I365_PC_RESET
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
ques
c_cond
id|I365_PC_IOCARD
suffix:colon
l_int|0
suffix:semicolon
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_INTCTL
comma
id|reg
)paren
suffix:semicolon
id|reg
op_assign
id|I365_PWR_NORESET
suffix:semicolon
id|control
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* CB_STOPCLK ? Better power management */
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|33
suffix:colon
id|control
op_or_assign
id|CB_PWR3V
op_lshift
id|CB_VCCCTRL
suffix:semicolon
id|reg
op_or_assign
id|I365_VCC_5V
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|control
op_or_assign
id|CB_PWR5V
op_lshift
id|CB_VCCCTRL
suffix:semicolon
id|reg
op_or_assign
id|I365_VCC_5V
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|state-&gt;Vpp
)paren
(brace
r_case
l_int|33
suffix:colon
id|control
op_or_assign
id|CB_PWR3V
op_lshift
id|CB_VPPCTRL
suffix:semicolon
id|reg
op_or_assign
id|I365_VPP1_5V
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|control
op_or_assign
id|CB_PWR5V
op_lshift
id|CB_VPPCTRL
suffix:semicolon
id|reg
op_or_assign
id|I365_VPP1_5V
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|120
suffix:colon
id|control
op_or_assign
id|CB_PWR12V
op_lshift
id|CB_VPPCTRL
suffix:semicolon
id|reg
op_or_assign
id|I365_VPP1_12V
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cb_writel
c_func
(paren
id|socket
comma
id|CB_SOCKET_CONTROL
comma
id|control
)paren
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_PWR_AUTO
)paren
ques
c_cond
id|I365_PWR_AUTO
suffix:colon
l_int|0
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_OUTPUT_ENA
)paren
ques
c_cond
id|I365_PWR_OUT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_PWR_AUTO
)paren
id|reg
op_or_assign
id|I365_PWR_AUTO
suffix:semicolon
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_POWER
comma
id|reg
)paren
suffix:semicolon
id|reg
op_assign
id|socket-&gt;irq
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;csc_mask
op_amp
id|SS_DETECT
)paren
ques
c_cond
id|I365_CSC_DETECT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
(brace
id|reg
op_or_assign
(paren
id|state-&gt;csc_mask
op_amp
id|SS_STSCHG
)paren
ques
c_cond
id|I365_CSC_STSCHG
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|reg
op_or_assign
(paren
id|state-&gt;csc_mask
op_amp
id|SS_BATDEAD
)paren
ques
c_cond
id|I365_CSC_BVD1
suffix:colon
l_int|0
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;csc_mask
op_amp
id|SS_BATWARN
)paren
ques
c_cond
id|I365_CSC_BVD2
suffix:colon
l_int|0
suffix:semicolon
id|reg
op_or_assign
(paren
id|state-&gt;csc_mask
op_amp
id|SS_READY
)paren
ques
c_cond
id|I365_CSC_READY
suffix:colon
l_int|0
suffix:semicolon
)brace
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_CSCINT
comma
id|reg
)paren
suffix:semicolon
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_CSC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_get_io_map
r_static
r_int
id|yenta_get_io_map
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_char
id|ioctl
comma
id|addr
suffix:semicolon
id|map
op_assign
id|io-&gt;map
suffix:semicolon
r_if
c_cond
(paren
id|map
OG
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|io-&gt;start
op_assign
id|exca_readw
c_func
(paren
id|socket
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
)paren
suffix:semicolon
id|io-&gt;stop
op_assign
id|exca_readw
c_func
(paren
id|socket
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
)paren
suffix:semicolon
id|ioctl
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_IOCTL
)paren
suffix:semicolon
id|addr
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
id|io-&gt;speed
op_assign
id|to_ns
c_func
(paren
id|ioctl
op_amp
id|I365_IOCTL_WAIT
c_func
(paren
id|map
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|io-&gt;flags
op_assign
(paren
id|addr
op_amp
id|I365_ENA_IO
c_func
(paren
id|map
)paren
)paren
ques
c_cond
id|MAP_ACTIVE
suffix:colon
l_int|0
suffix:semicolon
id|io-&gt;flags
op_or_assign
(paren
id|ioctl
op_amp
id|I365_IOCTL_0WS
c_func
(paren
id|map
)paren
)paren
ques
c_cond
id|MAP_0WS
suffix:colon
l_int|0
suffix:semicolon
id|io-&gt;flags
op_or_assign
(paren
id|ioctl
op_amp
id|I365_IOCTL_16BIT
c_func
(paren
id|map
)paren
)paren
ques
c_cond
id|MAP_16BIT
suffix:colon
l_int|0
suffix:semicolon
id|io-&gt;flags
op_or_assign
(paren
id|ioctl
op_amp
id|I365_IOCTL_IOCS16
c_func
(paren
id|map
)paren
)paren
ques
c_cond
id|MAP_AUTOSZ
suffix:colon
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_get_io_map(%d) = %x, %x, %x&bslash;n&quot;
comma
id|map
comma
id|io-&gt;start
comma
id|io-&gt;stop
comma
id|io-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_set_io_map
r_static
r_int
id|yenta_set_io_map
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_char
id|ioctl
comma
id|addr
comma
id|enable
suffix:semicolon
id|map
op_assign
id|io-&gt;map
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_set_io_map(%d, %x, %x, %x)&bslash;n&quot;
comma
id|map
comma
id|io-&gt;start
comma
id|io-&gt;stop
comma
id|io-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
OG
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|enable
op_assign
id|I365_ENA_IO
c_func
(paren
id|map
)paren
suffix:semicolon
id|addr
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
multiline_comment|/* Disable the window before changing it.. */
r_if
c_cond
(paren
id|addr
op_amp
id|enable
)paren
(brace
id|addr
op_and_assign
op_complement
id|enable
suffix:semicolon
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
comma
id|addr
)paren
suffix:semicolon
)brace
id|exca_writew
c_func
(paren
id|socket
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
comma
id|io-&gt;start
)paren
suffix:semicolon
id|exca_writew
c_func
(paren
id|socket
comma
id|I365_IO
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
comma
id|io-&gt;stop
)paren
suffix:semicolon
id|ioctl
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_IOCTL
)paren
op_amp
op_complement
id|I365_IOCTL_MASK
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_0WS
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_0WS
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_16BIT
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_16BIT
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_AUTOSZ
)paren
id|ioctl
op_or_assign
id|I365_IOCTL_IOCS16
c_func
(paren
id|map
)paren
suffix:semicolon
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_IOCTL
comma
id|ioctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;flags
op_amp
id|MAP_ACTIVE
)paren
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
comma
id|addr
op_or
id|enable
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_get_mem_map
r_static
r_int
id|yenta_get_mem_map
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_char
id|addr
suffix:semicolon
r_int
r_int
id|start
comma
id|stop
comma
id|page
comma
id|offset
suffix:semicolon
id|map
op_assign
id|mem-&gt;map
suffix:semicolon
r_if
c_cond
(paren
id|map
OG
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
id|mem-&gt;flags
op_assign
(paren
id|addr
op_amp
id|I365_ENA_MEM
c_func
(paren
id|map
)paren
)paren
ques
c_cond
id|MAP_ACTIVE
suffix:colon
l_int|0
suffix:semicolon
id|start
op_assign
id|exca_readw
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
)paren
suffix:semicolon
id|mem-&gt;flags
op_or_assign
(paren
id|start
op_amp
id|I365_MEM_16BIT
)paren
ques
c_cond
id|MAP_16BIT
suffix:colon
l_int|0
suffix:semicolon
id|mem-&gt;flags
op_or_assign
(paren
id|start
op_amp
id|I365_MEM_0WS
)paren
ques
c_cond
id|MAP_0WS
suffix:colon
l_int|0
suffix:semicolon
id|start
op_assign
(paren
id|start
op_amp
l_int|0x0fff
)paren
op_lshift
l_int|12
suffix:semicolon
id|stop
op_assign
id|exca_readw
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
)paren
suffix:semicolon
id|mem-&gt;speed
op_assign
(paren
id|stop
op_amp
id|I365_MEM_WS0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|mem-&gt;speed
op_add_assign
(paren
id|stop
op_amp
id|I365_MEM_WS1
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
suffix:semicolon
id|mem-&gt;speed
op_assign
id|to_ns
c_func
(paren
id|mem-&gt;speed
)paren
suffix:semicolon
id|stop
op_assign
(paren
(paren
id|stop
op_amp
l_int|0x0fff
)paren
op_lshift
l_int|12
)paren
op_plus
l_int|0x0fff
suffix:semicolon
id|offset
op_assign
id|exca_readw
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_OFF
)paren
suffix:semicolon
id|mem-&gt;flags
op_or_assign
(paren
id|offset
op_amp
id|I365_MEM_WRPROT
)paren
ques
c_cond
id|MAP_WRPROT
suffix:colon
l_int|0
suffix:semicolon
id|mem-&gt;flags
op_or_assign
(paren
id|offset
op_amp
id|I365_MEM_REG
)paren
ques
c_cond
id|MAP_ATTRIB
suffix:colon
l_int|0
suffix:semicolon
id|offset
op_assign
(paren
(paren
id|offset
op_amp
l_int|0x3fff
)paren
op_lshift
l_int|12
)paren
op_plus
id|start
suffix:semicolon
id|mem-&gt;card_start
op_assign
id|offset
op_amp
l_int|0x3ffffff
suffix:semicolon
id|page
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|CB_MEM_PAGE
c_func
(paren
id|map
)paren
)paren
op_lshift
l_int|24
suffix:semicolon
id|mem-&gt;sys_start
op_assign
id|start
op_plus
id|page
suffix:semicolon
id|mem-&gt;sys_stop
op_assign
id|start
op_plus
id|page
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_get_map(%d) = %lx, %lx, %x&bslash;n&quot;
comma
id|map
comma
id|mem-&gt;sys_start
comma
id|mem-&gt;sys_stop
comma
id|mem-&gt;card_start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_set_mem_map
r_static
r_int
id|yenta_set_mem_map
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_char
id|addr
comma
id|enable
suffix:semicolon
r_int
r_int
id|start
comma
id|stop
comma
id|card_start
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
id|map
op_assign
id|mem-&gt;map
suffix:semicolon
id|start
op_assign
id|mem-&gt;sys_start
suffix:semicolon
id|stop
op_assign
id|mem-&gt;sys_stop
suffix:semicolon
id|card_start
op_assign
id|mem-&gt;card_start
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;yenta_set_map(%d, %x, %x, %x)&bslash;n&quot;
comma
id|map
comma
id|start
comma
id|stop
comma
id|card_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
OG
l_int|4
op_logical_or
id|start
OG
id|stop
op_logical_or
(paren
(paren
id|start
op_xor
id|stop
)paren
op_rshift
l_int|24
)paren
op_logical_or
(paren
id|card_start
op_rshift
l_int|26
)paren
op_logical_or
id|mem-&gt;speed
OG
l_int|1000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|enable
op_assign
id|I365_ENA_MEM
c_func
(paren
id|map
)paren
suffix:semicolon
id|addr
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
id|enable
)paren
(brace
id|addr
op_and_assign
op_complement
id|enable
suffix:semicolon
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
comma
id|addr
)paren
suffix:semicolon
)brace
id|word
op_assign
(paren
id|start
op_rshift
l_int|12
)paren
op_amp
l_int|0x0fff
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_16BIT
)paren
id|word
op_or_assign
id|I365_MEM_16BIT
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_0WS
)paren
id|word
op_or_assign
id|I365_MEM_0WS
suffix:semicolon
id|exca_writew
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_START
comma
id|word
)paren
suffix:semicolon
id|word
op_assign
(paren
id|stop
op_rshift
l_int|12
)paren
op_amp
l_int|0x0fff
suffix:semicolon
r_switch
c_cond
(paren
id|to_cycles
c_func
(paren
id|mem-&gt;speed
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|word
op_or_assign
id|I365_MEM_WS0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|word
op_or_assign
id|I365_MEM_WS1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|word
op_or_assign
id|I365_MEM_WS1
op_or
id|I365_MEM_WS0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|exca_writew
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_STOP
comma
id|word
)paren
suffix:semicolon
id|word
op_assign
(paren
(paren
id|card_start
op_minus
id|start
)paren
op_rshift
l_int|12
)paren
op_amp
l_int|0x3fff
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_WRPROT
)paren
id|word
op_or_assign
id|I365_MEM_WRPROT
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_ATTRIB
)paren
id|word
op_or_assign
id|I365_MEM_REG
suffix:semicolon
id|exca_writew
c_func
(paren
id|socket
comma
id|I365_MEM
c_func
(paren
id|map
)paren
op_plus
id|I365_W_OFF
comma
id|word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|MAP_ACTIVE
)paren
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_ADDRWIN
comma
id|addr
op_or
id|enable
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yenta_get_bridge
r_static
r_int
id|yenta_get_bridge
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|cb_bridge_map
op_star
id|m
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;yenta_get_bridge() called&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|yenta_set_bridge
r_static
r_int
id|yenta_set_bridge
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|cb_bridge_map
op_star
id|m
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;yenta_set_bridge() called&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|yenta_proc_setup
r_static
r_void
id|yenta_proc_setup
c_func
(paren
id|pci_socket_t
op_star
id|socket
comma
r_struct
id|proc_dir_entry
op_star
id|base
)paren
(brace
multiline_comment|/* Not done yet */
)brace
DECL|function|yenta_interrupt
r_static
r_void
id|yenta_interrupt
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
id|u8
id|csc
suffix:semicolon
id|u32
id|cb_event
suffix:semicolon
r_int
r_int
id|events
suffix:semicolon
id|pci_socket_t
op_star
id|socket
op_assign
(paren
id|pci_socket_t
op_star
)paren
id|dev_id
suffix:semicolon
multiline_comment|/* Clear interrupt status for the event */
id|cb_event
op_assign
id|cb_readl
c_func
(paren
id|socket
comma
id|CB_SOCKET_EVENT
)paren
suffix:semicolon
id|cb_writel
c_func
(paren
id|socket
comma
id|CB_SOCKET_EVENT
comma
id|cb_event
)paren
suffix:semicolon
id|csc
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_CSC
)paren
suffix:semicolon
id|events
op_assign
(paren
id|cb_event
op_amp
(paren
id|CB_CD1EVENT
op_or
id|CB_CD2EVENT
)paren
)paren
ques
c_cond
id|SS_DETECT
suffix:colon
l_int|0
suffix:semicolon
id|events
op_or_assign
(paren
id|csc
op_amp
id|I365_CSC_DETECT
)paren
ques
c_cond
id|SS_DETECT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_INTCTL
)paren
op_amp
id|I365_PC_IOCARD
)paren
(brace
id|events
op_or_assign
(paren
id|csc
op_amp
id|I365_CSC_STSCHG
)paren
ques
c_cond
id|SS_STSCHG
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|events
op_or_assign
(paren
id|csc
op_amp
id|I365_CSC_BVD1
)paren
ques
c_cond
id|SS_BATDEAD
suffix:colon
l_int|0
suffix:semicolon
id|events
op_or_assign
(paren
id|csc
op_amp
id|I365_CSC_BVD2
)paren
ques
c_cond
id|SS_BATWARN
suffix:colon
l_int|0
suffix:semicolon
id|events
op_or_assign
(paren
id|csc
op_amp
id|I365_CSC_READY
)paren
ques
c_cond
id|SS_READY
suffix:colon
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Socket interrupt event %08x (%08x %02x)&bslash;n&quot;
comma
id|events
comma
id|cb_event
comma
id|csc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|events
op_logical_and
id|socket-&gt;handler
)paren
id|socket
op_member_access_from_pointer
id|handler
c_func
(paren
id|socket-&gt;info
comma
id|events
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize a cardbus controller. Make sure we have a usable&n; * interrupt, and that we can map the cardbus area. Fill in the&n; * socket information structure..&n; */
DECL|function|yenta_open
r_static
r_int
id|yenta_open
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|socket-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t; * Do some basic sanity checking..&n;&t; */
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to enable device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No cardbus irq!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No cardbus resource!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ok, start setup.. Map the cardbus registers,&n;&t; * and request the IRQ.&n;&t; */
id|socket-&gt;base
op_assign
id|ioremap
c_func
(paren
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
l_int|0x1000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|socket-&gt;base
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|yenta_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|socket
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|socket-&gt;irq
op_assign
id|dev-&gt;irq
suffix:semicolon
multiline_comment|/* Enable all events */
id|writel
c_func
(paren
l_int|0x0f
comma
id|socket-&gt;base
op_plus
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Socket status: %08x&bslash;n&quot;
comma
id|readl
c_func
(paren
id|socket-&gt;base
op_plus
l_int|8
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Close it down - release our resources and go home..&n; */
DECL|function|yenta_close
r_static
r_void
id|yenta_close
c_func
(paren
id|pci_socket_t
op_star
id|sock
)paren
(brace
r_if
c_cond
(paren
id|sock-&gt;irq
)paren
id|free_irq
c_func
(paren
id|sock-&gt;irq
comma
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;base
)paren
id|iounmap
c_func
(paren
id|sock-&gt;base
)paren
suffix:semicolon
)brace
DECL|variable|yenta_operations
r_struct
id|pci_socket_ops
id|yenta_operations
op_assign
(brace
id|yenta_open
comma
id|yenta_close
comma
id|yenta_inquire
comma
id|yenta_get_status
comma
id|yenta_get_socket
comma
id|yenta_set_socket
comma
id|yenta_get_io_map
comma
id|yenta_set_io_map
comma
id|yenta_get_mem_map
comma
id|yenta_set_mem_map
comma
id|yenta_get_bridge
comma
id|yenta_set_bridge
comma
id|yenta_proc_setup
)brace
suffix:semicolon
eof
