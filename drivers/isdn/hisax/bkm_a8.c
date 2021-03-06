multiline_comment|/* $Id: bkm_a8.c,v 1.14.6.2 2000/11/29 16:00:14 kai Exp $&n; * bkm_a8.c     low level stuff for Scitel Quadro (4*S0, passive)&n; *              derived from the original file sedlbauer.c&n; *              derived from the original file niccy.c&n; *              derived from the original file netjet.c&n; *&n; * Author       Roland Klabunde (R.Klabunde@Berkom.de)&n; *&n; * This file is (c) under GNU PUBLIC LICENSE&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;ipac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;bkm_ax.h&quot;
macro_line|#if CONFIG_PCI
DECL|macro|ATTEMPT_PCI_REMAPPING
mdefine_line|#define&t;ATTEMPT_PCI_REMAPPING&t;/* Required for PLX rev 1 */
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|sct_quadro_revision
r_const
r_char
id|sct_quadro_revision
(braket
)braket
op_assign
l_string|&quot;$Revision: 1.14.6.2 $&quot;
suffix:semicolon
DECL|variable|sct_quadro_subtypes
r_static
r_const
r_char
op_star
id|sct_quadro_subtypes
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;#1&quot;
comma
l_string|&quot;#2&quot;
comma
l_string|&quot;#3&quot;
comma
l_string|&quot;#4&quot;
)brace
suffix:semicolon
DECL|macro|wordout
mdefine_line|#define wordout(addr,val) outw(val,addr)
DECL|macro|wordin
mdefine_line|#define wordin(addr) inw(addr)
r_static
r_inline
id|u_char
DECL|function|readreg
id|readreg
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
)paren
(brace
r_register
id|u_char
id|ret
suffix:semicolon
r_int
id|flags
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
id|wordout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|wordin
c_func
(paren
id|adr
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|readfifo
id|readfifo
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
multiline_comment|/* fifo read without cli because it&squot;s allready done  */
r_int
id|i
suffix:semicolon
id|wordout
c_func
(paren
id|ale
comma
id|off
)paren
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|wordin
c_func
(paren
id|adr
)paren
op_amp
l_int|0xFF
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writereg
id|writereg
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
id|data
)paren
(brace
r_int
id|flags
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
id|wordout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|wordout
c_func
(paren
id|adr
comma
id|data
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writefifo
id|writefifo
c_func
(paren
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
multiline_comment|/* fifo write without cli because it&squot;s allready done  */
r_int
id|i
suffix:semicolon
id|wordout
c_func
(paren
id|ale
comma
id|off
)paren
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|wordout
c_func
(paren
id|adr
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Interface functions */
r_static
id|u_char
DECL|function|ReadISAC
id|ReadISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
)paren
(brace
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|offset
op_or
l_int|0x80
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAC
id|WriteISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|offset
op_or
l_int|0x80
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ReadISACfifo
id|ReadISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|readfifo
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISACfifo
id|WriteISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|writefifo
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
id|u_char
DECL|function|ReadHSCX
id|ReadHSCX
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u_char
id|offset
)paren
(brace
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteHSCX
id|WriteHSCX
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the specific ipac to active */
r_static
r_void
DECL|function|set_ipac_active
id|set_ipac_active
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_int
id|active
)paren
(brace
multiline_comment|/* set irq mask */
id|writereg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_MASK
comma
id|active
ques
c_cond
l_int|0xc0
suffix:colon
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readreg(cs-&gt;hw.ax.base, &bslash;&n;&t;cs-&gt;hw.ax.data_adr, reg + (nr ? 0x40 : 0))
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writereg(cs-&gt;hw.ax.base, &bslash;&n;&t;cs-&gt;hw.ax.data_adr, reg + (nr ? 0x40 : 0), data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs-&gt;hw.ax.base, &bslash;&n;&t;cs-&gt;hw.ax.data_adr, (nr ? 0x40 : 0), ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs-&gt;hw.ax.base, &bslash;&n;&t;cs-&gt;hw.ax.data_adr, (nr ? 0x40 : 0), ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|bkm_interrupt_ipac
id|bkm_interrupt_ipac
c_func
(paren
r_int
id|intno
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
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|u_char
id|ista
comma
id|val
comma
id|icnt
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: Scitel Quadro: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ista
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ista
op_amp
l_int|0x3f
)paren
)paren
multiline_comment|/* not this IPAC */
r_return
suffix:semicolon
id|Start_IPAC
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_IPAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;IPAC ISTA %02X&quot;
comma
id|ista
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x0f
)paren
(brace
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|HSCX_ISTA
op_plus
l_int|0x40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x01
)paren
id|val
op_or_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x04
)paren
id|val
op_or_assign
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x08
)paren
id|val
op_or_assign
l_int|0x04
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x20
)paren
(brace
id|val
op_assign
l_int|0xfe
op_amp
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|ISAC_ISTA
op_or
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x10
)paren
(brace
id|val
op_assign
l_int|0x01
suffix:semicolon
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
id|ista
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ista
op_amp
l_int|0x3f
)paren
op_logical_and
id|icnt
)paren
(brace
id|icnt
op_decrement
suffix:semicolon
r_goto
id|Start_IPAC
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|icnt
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s) IRQ LOOP&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_MASK
comma
l_int|0xC0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_sct_quadro
id|release_io_sct_quadro
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|release_region
c_func
(paren
id|cs-&gt;hw.ax.base
op_amp
l_int|0xffffffc0
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|SCT_1
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
comma
l_int|256
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|enable_bkm_int
id|enable_bkm_int
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|bEnable
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_SCT_QUADRO
)paren
(brace
r_if
c_cond
(paren
id|bEnable
)paren
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
)paren
op_or
l_int|0x41
)paren
)paren
suffix:semicolon
r_else
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
)paren
op_amp
op_complement
l_int|0x41
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|reset_bkm
id|reset_bkm
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|SCT_1
)paren
(brace
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
)paren
op_amp
op_complement
l_int|4
)paren
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Remove the soft reset */
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
)paren
op_or
l_int|4
)paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|BKM_card_msg
id|BKM_card_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mt
comma
r_void
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|mt
)paren
(brace
r_case
id|CARD_RESET
suffix:colon
multiline_comment|/* Disable ints */
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|reset_bkm
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
multiline_comment|/* Sanity */
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|release_io_sct_quadro
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|cs-&gt;debug
op_or_assign
id|L1_DEB_IPAC
suffix:semicolon
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|1
)paren
suffix:semicolon
id|inithscxisac
c_func
(paren
id|cs
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Enable ints */
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|sct_alloc_io
id|sct_alloc_io
c_func
(paren
id|u_int
id|adr
comma
id|u_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
comma
id|len
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: Scitel port %#x-%#x already in use&bslash;n&quot;
comma
id|adr
comma
id|adr
op_plus
id|len
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|adr
comma
id|len
comma
l_string|&quot;scitel&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_a8
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
r_static
id|u16
id|sub_vendor_id
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u16
id|sub_sys_id
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|pci_bus
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|pci_device_fn
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|pci_irq
id|__initdata
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
r_int
id|__init
DECL|function|setup_sct_quadro
id|setup_sct_quadro
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
macro_line|#if CONFIG_PCI
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|u_char
id|pci_rev_id
suffix:semicolon
id|u_int
id|found
op_assign
l_int|0
suffix:semicolon
id|u_int
id|pci_ioaddr1
comma
id|pci_ioaddr2
comma
id|pci_ioaddr3
comma
id|pci_ioaddr4
comma
id|pci_ioaddr5
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|sct_quadro_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: T-Berkom driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_SCT_QUADRO
)paren
(brace
id|cs-&gt;subtyp
op_assign
id|SCT_1
suffix:semicolon
multiline_comment|/* Preset */
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Identify subtype by para[0] */
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|0
)braket
op_ge
id|SCT_1
op_logical_and
id|card-&gt;para
(braket
l_int|0
)braket
op_le
id|SCT_4
)paren
id|cs-&gt;subtyp
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: Invalid subcontroller in configuration, default to 1&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cs-&gt;subtyp
op_ne
id|SCT_1
)paren
op_logical_and
(paren
(paren
id|sub_sys_id
op_ne
id|PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO
)paren
op_logical_or
(paren
id|sub_vendor_id
op_ne
id|PCI_VENDOR_ID_BERKOM
)paren
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|SCT_1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bkm_a4t: no PCI bus present&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|dev_a8
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_PLX
comma
id|PCI_DEVICE_ID_PLX_9050
comma
id|dev_a8
)paren
)paren
)paren
(brace
id|sub_vendor_id
op_assign
id|dev_a8-&gt;subsystem_vendor
suffix:semicolon
id|sub_sys_id
op_assign
id|dev_a8-&gt;subsystem_device
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sub_sys_id
op_eq
id|PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO
)paren
op_logical_and
(paren
id|sub_vendor_id
op_eq
id|PCI_VENDOR_ID_BERKOM
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev_a8
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pci_ioaddr1
op_assign
id|pci_resource_start
c_func
(paren
id|dev_a8
comma
l_int|1
)paren
suffix:semicolon
id|pci_irq
op_assign
id|dev_a8-&gt;irq
suffix:semicolon
id|pci_bus
op_assign
id|dev_a8-&gt;bus-&gt;number
suffix:semicolon
id|pci_device_fn
op_assign
id|dev_a8-&gt;devfn
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): Card not found&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef ATTEMPT_PCI_REMAPPING
multiline_comment|/* HACK: PLX revision 1 bug: PLX address bit 7 must not be set */
id|pcibios_read_config_byte
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_REVISION_ID
comma
op_amp
id|pci_rev_id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_ioaddr1
op_amp
l_int|0x80
)paren
op_logical_and
(paren
id|pci_rev_id
op_eq
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): PLX rev 1, remapping required!&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
multiline_comment|/* Restart PCI negotiation */
id|pcibios_write_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_1
comma
(paren
id|u_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Move up by 0x80 byte */
id|pci_ioaddr1
op_add_assign
l_int|0x80
suffix:semicolon
id|pci_ioaddr1
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_1
comma
id|pci_ioaddr1
)paren
suffix:semicolon
id|dev_a8-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
id|pci_ioaddr1
suffix:semicolon
)brace
macro_line|#endif /* End HACK */
)brace
r_if
c_cond
(paren
op_logical_neg
id|pci_irq
)paren
(brace
multiline_comment|/* IRQ range check ?? */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): No IRQ&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pcibios_read_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_1
comma
op_amp
id|pci_ioaddr1
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_2
comma
op_amp
id|pci_ioaddr2
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_3
comma
op_amp
id|pci_ioaddr3
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_4
comma
op_amp
id|pci_ioaddr4
)paren
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_5
comma
op_amp
id|pci_ioaddr5
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_ioaddr1
op_logical_or
op_logical_neg
id|pci_ioaddr2
op_logical_or
op_logical_neg
id|pci_ioaddr3
op_logical_or
op_logical_neg
id|pci_ioaddr4
op_logical_or
op_logical_neg
id|pci_ioaddr5
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): No IO base address(es)&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pci_ioaddr1
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr2
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr3
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr4
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr5
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
multiline_comment|/* Take over */
id|cs-&gt;irq
op_assign
id|pci_irq
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
multiline_comment|/* pci_ioaddr1 is unique to all subdevices */
multiline_comment|/* pci_ioaddr2 is for the fourth subdevice only */
multiline_comment|/* pci_ioaddr3 is for the third subdevice only */
multiline_comment|/* pci_ioaddr4 is for the second subdevice only */
multiline_comment|/* pci_ioaddr5 is for the first subdevice only */
id|cs-&gt;hw.ax.plx_adr
op_assign
id|pci_ioaddr1
suffix:semicolon
multiline_comment|/* Enter all ipac_base addresses */
r_switch
c_cond
(paren
id|cs-&gt;subtyp
)paren
(brace
r_case
l_int|1
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr5
op_plus
l_int|0x00
suffix:semicolon
r_if
c_cond
(paren
id|sct_alloc_io
c_func
(paren
id|pci_ioaddr1
comma
l_int|256
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sct_alloc_io
c_func
(paren
id|pci_ioaddr5
comma
l_int|256
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* disable all IPAC */
id|writereg
c_func
(paren
id|pci_ioaddr5
comma
id|pci_ioaddr5
op_plus
l_int|4
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|pci_ioaddr4
op_plus
l_int|0x08
comma
id|pci_ioaddr4
op_plus
l_int|0x0c
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|pci_ioaddr3
op_plus
l_int|0x10
comma
id|pci_ioaddr3
op_plus
l_int|0x14
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|pci_ioaddr2
op_plus
l_int|0x20
comma
id|pci_ioaddr2
op_plus
l_int|0x24
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr4
op_plus
l_int|0x08
suffix:semicolon
r_if
c_cond
(paren
id|sct_alloc_io
c_func
(paren
id|pci_ioaddr4
comma
l_int|256
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr3
op_plus
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|sct_alloc_io
c_func
(paren
id|pci_ioaddr3
comma
l_int|256
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr2
op_plus
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|sct_alloc_io
c_func
(paren
id|pci_ioaddr2
comma
l_int|256
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* For isac and hscx data path */
id|cs-&gt;hw.ax.data_adr
op_assign
id|cs-&gt;hw.ax.base
op_plus
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s (%s) configured at 0x%.4X, 0x%.4X, 0x%.4X and IRQ %d&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
comma
id|cs-&gt;hw.ax.plx_adr
comma
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|test_and_set_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
id|cs-&gt;readisac
op_assign
op_amp
id|ReadISAC
suffix:semicolon
id|cs-&gt;writeisac
op_assign
op_amp
id|WriteISAC
suffix:semicolon
id|cs-&gt;readisacfifo
op_assign
op_amp
id|ReadISACfifo
suffix:semicolon
id|cs-&gt;writeisacfifo
op_assign
op_amp
id|WriteISACfifo
suffix:semicolon
id|cs-&gt;BC_Read_Reg
op_assign
op_amp
id|ReadHSCX
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteHSCX
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|hscx_fill_fifo
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|BKM_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|bkm_interrupt_ipac
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s (%s): IPAC Version %d&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
comma
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|IPAC_ID
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HiSax: bkm_a8 only supported on PCI Systems&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
)brace
eof
