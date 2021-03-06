multiline_comment|/* $Id: bkm_a4t.c,v 1.13.6.2 2000/11/29 16:00:14 kai Exp $&n; * bkm_a4t.c    low level stuff for T-Berkom A4T&n; *              derived from the original file sedlbauer.c&n; *              derived from the original file niccy.c&n; *              derived from the original file netjet.c&n; *&n; * Author       Roland Klabunde (R.Klabunde@Berkom.de)&n; *&n; * This file is (c) under GNU PUBLIC LICENSE&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;jade.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;bkm_ax.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|bkm_a4t_revision
r_const
r_char
op_star
id|bkm_a4t_revision
op_assign
l_string|&quot;$Revision: 1.13.6.2 $&quot;
suffix:semicolon
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
id|u_int
id|ret
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|po
op_assign
(paren
r_int
r_int
op_star
)paren
id|adr
suffix:semicolon
multiline_comment|/* Postoffice */
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
id|po
op_assign
(paren
id|GCS_2
op_or
id|PO_WRITE
op_or
id|off
)paren
suffix:semicolon
id|__WAITI20__
c_func
(paren
id|po
)paren
suffix:semicolon
op_star
id|po
op_assign
(paren
id|ale
op_or
id|PO_READ
)paren
suffix:semicolon
id|__WAITI20__
c_func
(paren
id|po
)paren
suffix:semicolon
id|ret
op_assign
op_star
id|po
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_char
)paren
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
op_star
id|data
op_increment
op_assign
id|readreg
c_func
(paren
id|ale
comma
id|adr
comma
id|off
)paren
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
r_int
r_int
op_star
id|po
op_assign
(paren
r_int
r_int
op_star
)paren
id|adr
suffix:semicolon
multiline_comment|/* Postoffice */
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
id|po
op_assign
(paren
id|GCS_2
op_or
id|PO_WRITE
op_or
id|off
)paren
suffix:semicolon
id|__WAITI20__
c_func
(paren
id|po
)paren
suffix:semicolon
op_star
id|po
op_assign
(paren
id|ale
op_or
id|PO_WRITE
op_or
id|data
)paren
suffix:semicolon
id|__WAITI20__
c_func
(paren
id|po
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
id|writereg
c_func
(paren
id|ale
comma
id|adr
comma
id|off
comma
op_star
id|data
op_increment
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
id|cs-&gt;hw.ax.isac_ale
comma
id|cs-&gt;hw.ax.isac_adr
comma
id|offset
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
id|cs-&gt;hw.ax.isac_ale
comma
id|cs-&gt;hw.ax.isac_adr
comma
id|offset
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
id|cs-&gt;hw.ax.isac_ale
comma
id|cs-&gt;hw.ax.isac_adr
comma
l_int|0
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
id|cs-&gt;hw.ax.isac_ale
comma
id|cs-&gt;hw.ax.isac_adr
comma
l_int|0
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
id|u_char
DECL|function|ReadJADE
id|ReadJADE
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|jade
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
id|cs-&gt;hw.ax.jade_ale
comma
id|cs-&gt;hw.ax.jade_adr
comma
id|offset
op_plus
(paren
id|jade
op_eq
op_minus
l_int|1
ques
c_cond
l_int|0
suffix:colon
(paren
id|jade
ques
c_cond
l_int|0xC0
suffix:colon
l_int|0x80
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteJADE
id|WriteJADE
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|jade
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
id|cs-&gt;hw.ax.jade_ale
comma
id|cs-&gt;hw.ax.jade_adr
comma
id|offset
op_plus
(paren
id|jade
op_eq
op_minus
l_int|1
ques
c_cond
l_int|0
suffix:colon
(paren
id|jade
ques
c_cond
l_int|0xC0
suffix:colon
l_int|0x80
)paren
)paren
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fast interrupt JADE stuff goes here&n; */
DECL|macro|READJADE
mdefine_line|#define READJADE(cs, nr, reg) readreg(cs-&gt;hw.ax.jade_ale,&bslash;&n; &t;&t;cs-&gt;hw.ax.jade_adr, reg + (nr == -1 ? 0 : (nr ? 0xC0 : 0x80)))
DECL|macro|WRITEJADE
mdefine_line|#define WRITEJADE(cs, nr, reg, data) writereg(cs-&gt;hw.ax.jade_ale,&bslash;&n; &t;&t;cs-&gt;hw.ax.jade_adr, reg + (nr == -1 ? 0 : (nr ? 0xC0 : 0x80)), data)
DECL|macro|READJADEFIFO
mdefine_line|#define READJADEFIFO(cs, nr, ptr, cnt) readfifo(cs-&gt;hw.ax.jade_ale,&bslash;&n;&t;&t;cs-&gt;hw.ax.jade_adr, (nr == -1 ? 0 : (nr ? 0xC0 : 0x80)), ptr, cnt)
DECL|macro|WRITEJADEFIFO
mdefine_line|#define WRITEJADEFIFO(cs, nr, ptr, cnt) writefifo( cs-&gt;hw.ax.jade_ale,&bslash;&n;&t;&t;cs-&gt;hw.ax.jade_adr, (nr == -1 ? 0 : (nr ? 0xC0 : 0x80)), ptr, cnt)
macro_line|#include &quot;jade_irq.c&quot;
r_static
r_void
DECL|function|bkm_interrupt
id|bkm_interrupt
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
id|val
op_assign
l_int|0
suffix:semicolon
id|I20_REGISTER_FILE
op_star
id|pI20_Regs
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
l_string|&quot;HiSax: Telekom A4T: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pI20_Regs
op_assign
(paren
id|I20_REGISTER_FILE
op_star
)paren
(paren
id|cs-&gt;hw.ax.base
)paren
suffix:semicolon
multiline_comment|/* ISDN interrupt pending? */
r_if
c_cond
(paren
id|pI20_Regs-&gt;i20IntStatus
op_amp
id|intISDN
)paren
(brace
multiline_comment|/* Reset the ISDN interrupt     */
id|pI20_Regs-&gt;i20IntStatus
op_assign
id|intISDN
suffix:semicolon
multiline_comment|/* Disable ISDN interrupt */
id|pI20_Regs-&gt;i20IntCtrl
op_and_assign
op_complement
id|intISDN
suffix:semicolon
multiline_comment|/* Channel A first */
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.jade_ale
comma
id|cs-&gt;hw.ax.jade_adr
comma
id|jade_HDLC_ISR
op_plus
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|jade_int_main
c_func
(paren
id|cs
comma
id|val
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Channel B  */
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.jade_ale
comma
id|cs-&gt;hw.ax.jade_adr
comma
id|jade_HDLC_ISR
op_plus
l_int|0xC0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|jade_int_main
c_func
(paren
id|cs
comma
id|val
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* D-Channel */
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ax.isac_ale
comma
id|cs-&gt;hw.ax.isac_adr
comma
id|ISAC_ISTA
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
multiline_comment|/* Reenable ISDN interrupt */
id|pI20_Regs-&gt;i20IntCtrl
op_or_assign
id|intISDN
suffix:semicolon
)brace
)brace
r_void
DECL|function|release_io_bkm
id|release_io_bkm
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;hw.ax.base
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|cs-&gt;hw.ax.base
)paren
suffix:semicolon
id|cs-&gt;hw.ax.base
op_assign
l_int|0
suffix:semicolon
)brace
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
id|ISDN_CTYPE_BKM_A4T
)paren
(brace
id|I20_REGISTER_FILE
op_star
id|pI20_Regs
op_assign
(paren
id|I20_REGISTER_FILE
op_star
)paren
(paren
id|cs-&gt;hw.ax.base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bEnable
)paren
id|pI20_Regs-&gt;i20IntCtrl
op_or_assign
(paren
id|intISDN
op_or
id|intPCI
)paren
suffix:semicolon
r_else
multiline_comment|/* CAUTION: This disables the video capture driver too */
id|pI20_Regs-&gt;i20IntCtrl
op_and_assign
op_complement
(paren
id|intISDN
op_or
id|intPCI
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
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_BKM_A4T
)paren
(brace
id|I20_REGISTER_FILE
op_star
id|pI20_Regs
op_assign
(paren
id|I20_REGISTER_FILE
op_star
)paren
(paren
id|cs-&gt;hw.ax.base
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
multiline_comment|/* Issue the I20 soft reset     */
id|pI20_Regs-&gt;i20SysControl
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* all in */
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
id|pI20_Regs-&gt;i20SysControl
op_assign
id|sysRESET
op_or
l_int|0xFF
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
multiline_comment|/* Set our configuration */
id|pI20_Regs-&gt;i20SysControl
op_assign
id|sysRESET
op_or
id|sysCFG
suffix:semicolon
multiline_comment|/* Issue ISDN reset     */
id|pI20_Regs-&gt;i20GuestControl
op_assign
id|guestWAIT_CFG
op_or
id|g_A4T_JADE_RES
op_or
id|g_A4T_ISAR_RES
op_or
id|g_A4T_ISAC_RES
op_or
id|g_A4T_JADE_BOOTR
op_or
id|g_A4T_ISAR_BOOTR
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
multiline_comment|/* Remove RESET state from ISDN */
id|pI20_Regs-&gt;i20GuestControl
op_and_assign
op_complement
(paren
id|g_A4T_ISAC_RES
op_or
id|g_A4T_JADE_RES
op_or
id|g_A4T_ISAR_RES
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
id|release_io_bkm
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
id|clear_pending_isac_ints
c_func
(paren
id|cs
)paren
suffix:semicolon
id|clear_pending_jade_ints
c_func
(paren
id|cs
)paren
suffix:semicolon
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|initjade
c_func
(paren
id|cs
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
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_a4t
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
r_int
id|__init
DECL|function|setup_bkm_a4t
id|setup_bkm_a4t
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
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
id|u_int
id|pci_memaddr
op_assign
l_int|0
comma
id|found
op_assign
l_int|0
suffix:semicolon
id|I20_REGISTER_FILE
op_star
id|pI20_Regs
suffix:semicolon
macro_line|#if CONFIG_PCI
macro_line|#endif
id|strcpy
c_func
(paren
id|tmp
comma
id|bkm_a4t_revision
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
id|ISDN_CTYPE_BKM_A4T
)paren
(brace
id|cs-&gt;subtyp
op_assign
id|BKM_A4T
suffix:semicolon
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#if CONFIG_PCI
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
id|dev_a4t
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_ZORAN
comma
id|PCI_DEVICE_ID_ZORAN_36120
comma
id|dev_a4t
)paren
)paren
)paren
(brace
id|u16
id|sub_sys
suffix:semicolon
id|u16
id|sub_vendor
suffix:semicolon
id|sub_vendor
op_assign
id|dev_a4t-&gt;subsystem_vendor
suffix:semicolon
id|sub_sys
op_assign
id|dev_a4t-&gt;subsystem_device
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sub_sys
op_eq
id|PCI_DEVICE_ID_BERKOM_A4T
)paren
op_logical_and
(paren
id|sub_vendor
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
id|dev_a4t
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
id|pci_memaddr
op_assign
id|pci_resource_start
c_func
(paren
id|dev_a4t
comma
l_int|0
)paren
suffix:semicolon
id|cs-&gt;irq
op_assign
id|dev_a4t-&gt;irq
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
l_string|&quot;HiSax: %s: Card not found&bslash;n&quot;
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
op_logical_neg
id|cs-&gt;irq
)paren
(brace
multiline_comment|/* IRQ range check ?? */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: No IRQ&bslash;n&quot;
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
op_logical_neg
id|pci_memaddr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: No Memory base address&bslash;n&quot;
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
id|cs-&gt;hw.ax.base
op_assign
(paren
id|u_int
)paren
id|ioremap
c_func
(paren
id|pci_memaddr
comma
l_int|4096
)paren
suffix:semicolon
multiline_comment|/* Check suspecious address */
id|pI20_Regs
op_assign
(paren
id|I20_REGISTER_FILE
op_star
)paren
(paren
id|cs-&gt;hw.ax.base
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pI20_Regs-&gt;i20IntStatus
op_amp
l_int|0x8EFFFFFF
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s address %x-%x suspecious&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.base
op_plus
l_int|4096
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|cs-&gt;hw.ax.base
)paren
suffix:semicolon
id|cs-&gt;hw.ax.base
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|cs-&gt;hw.ax.isac_adr
op_assign
id|cs-&gt;hw.ax.base
op_plus
id|PO_OFFSET
suffix:semicolon
id|cs-&gt;hw.ax.jade_adr
op_assign
id|cs-&gt;hw.ax.base
op_plus
id|PO_OFFSET
suffix:semicolon
id|cs-&gt;hw.ax.isac_ale
op_assign
id|GCS_1
suffix:semicolon
id|cs-&gt;hw.ax.jade_ale
op_assign
id|GCS_3
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: NO_PCI_BIOS&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: unable to configure&bslash;n&quot;
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
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PCI */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s: Card configured at 0x%X IRQ %d&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|reset_bkm
c_func
(paren
id|cs
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
id|ReadJADE
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteJADE
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|jade_fill_fifo
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|BKM_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|bkm_interrupt
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Telekom A4T:&quot;
)paren
suffix:semicolon
multiline_comment|/* Jade version */
id|JadeVersion
c_func
(paren
id|cs
comma
l_string|&quot;Telekom A4T:&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
