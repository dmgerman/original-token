multiline_comment|/* $Id: bkm_a8.c,v 1.8 1999/09/04 06:20:05 keil Exp $&n; * bkm_a8.c     low level stuff for Scitel Quadro (4*S0, passive)&n; *              derived from the original file sedlbauer.c&n; *              derived from the original file niccy.c&n; *              derived from the original file netjet.c&n; *&n; * Author       Roland Klabunde (R.Klabunde@Berkom.de)&n; *&n; * $Log: bkm_a8.c,v $&n; * Revision 1.8  1999/09/04 06:20:05  keil&n; * Changes from kernel set_current_state()&n; *&n; * Revision 1.7  1999/08/22 20:26:58  calle&n; * backported changes from kernel 2.3.14:&n; * - several #include &quot;config.h&quot; gone, others come.&n; * - &quot;struct device&quot; changed to &quot;struct net_device&quot; in 2.3.14, added a&n; *   define in isdn_compat.h for older kernel versions.&n; *&n; * Revision 1.6  1999/08/11 21:01:24  keil&n; * new PCI codefix&n; *&n; * Revision 1.5  1999/08/10 16:01:48  calle&n; * struct pci_dev changed in 2.3.13. Made the necessary changes.&n; *&n; * Revision 1.4  1999/07/14 11:43:15  keil&n; * correct PCI_SUBSYSTEM_VENDOR_ID&n; *&n; * Revision 1.3  1999/07/12 21:04:59  keil&n; * fix race in IRQ handling&n; * added watchdog for lost IRQs&n; *&n; * Revision 1.2  1999/07/01 08:07:54  keil&n; * Initial version&n; *&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;ipac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &quot;bkm_ax.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
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
l_string|&quot;$Revision: 1.8 $&quot;
suffix:semicolon
multiline_comment|/* To survive the startup phase */
r_typedef
r_struct
(brace
DECL|member|active
id|u_int
id|active
suffix:semicolon
multiline_comment|/* true/false */
DECL|member|base
id|u_int
id|base
suffix:semicolon
multiline_comment|/* ipac base address */
DECL|typedef|IPAC_STATE
)brace
id|IPAC_STATE
suffix:semicolon
DECL|variable|__initdata
r_static
id|IPAC_STATE
id|ipac_state
(braket
l_int|4
op_plus
l_int|1
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* dummy */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SCT_1 */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SCT_2 */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SCT_3 */
(brace
l_int|0
comma
l_int|0
)brace
multiline_comment|/* SCT_4 */
)brace
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
multiline_comment|/* Check whether the specified ipac is already active or not */
r_static
r_int
DECL|function|is_ipac_active
id|is_ipac_active
c_func
(paren
id|u_int
id|ipac_nr
)paren
(brace
r_return
(paren
id|ipac_state
(braket
id|ipac_nr
)braket
dot
id|active
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
id|u_int
id|ipac_nr
comma
id|u_int
id|active
)paren
(brace
multiline_comment|/* set activation state */
id|ipac_state
(braket
id|ipac_nr
)braket
dot
id|active
op_assign
id|active
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
r_int
id|i
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
multiline_comment|/* Read out all interrupt sources from currently not active ipacs */
multiline_comment|/* &quot;Handle&quot; all interrupts from currently not active ipac by reading the regs */
r_for
c_loop
(paren
id|i
op_assign
id|SCT_1
suffix:semicolon
id|i
op_le
id|SCT_4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|i
)paren
)paren
(brace
id|u_int
id|base
op_assign
id|ipac_state
(braket
id|i
)braket
dot
id|base
suffix:semicolon
r_if
c_cond
(paren
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0xC1
)paren
)paren
(brace
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0xA0
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0xA4
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0x20
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0x24
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0x60
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0x64
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
l_int|0xC1
)paren
suffix:semicolon
id|readreg
c_func
(paren
id|base
comma
id|base
op_plus
l_int|4
comma
id|ISAC_CIR0
op_plus
l_int|0x80
)paren
suffix:semicolon
)brace
)brace
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
multiline_comment|/* ?? */
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
multiline_comment|/* Issue general di only if no ipac is active */
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_1
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_2
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_3
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_4
)paren
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
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_SCT_QUADRO
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_1
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_2
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_3
)paren
op_logical_and
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_4
)paren
)paren
(brace
multiline_comment|/* Issue total reset only if no ipac is active */
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
id|TASK_INTERRUPTIBLE
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
id|TASK_INTERRUPTIBLE
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
id|cs-&gt;subtyp
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
id|cs-&gt;subtyp
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
id|cs-&gt;subtyp
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
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|setup_sct_quadro
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
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
macro_line|#if CONFIG_PCI
id|u_char
id|pci_bus
op_assign
l_int|0
comma
id|pci_device_fn
op_assign
l_int|0
comma
id|pci_irq
op_assign
l_int|0
comma
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
macro_line|#endif
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
r_if
c_cond
(paren
(paren
id|dev_a8
op_assign
id|pci_find_device
c_func
(paren
id|PLX_VENDOR_ID
comma
id|PLX_DEVICE_ID
comma
id|dev_a8
)paren
)paren
)paren
(brace
id|u_int
id|sub_sys_id
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_SUBSYSTEM_VENDOR_ID
comma
op_amp
id|sub_sys_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sub_sys_id
op_eq
(paren
(paren
id|SCT_SUBSYS_ID
op_lshift
l_int|16
)paren
op_or
id|SCT_SUBVEN_ID
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|pci_ioaddr1
op_assign
id|dev_a8-&gt;resource
(braket
l_int|1
)braket
dot
id|start
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
multiline_comment|/* End HACK */
macro_line|#endif
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
id|ipac_state
(braket
id|SCT_1
)braket
dot
id|base
op_assign
id|pci_ioaddr5
op_plus
l_int|0x00
suffix:semicolon
id|ipac_state
(braket
id|SCT_2
)braket
dot
id|base
op_assign
id|pci_ioaddr4
op_plus
l_int|0x08
suffix:semicolon
id|ipac_state
(braket
id|SCT_3
)braket
dot
id|base
op_assign
id|pci_ioaddr3
op_plus
l_int|0x10
suffix:semicolon
id|ipac_state
(braket
id|SCT_4
)braket
dot
id|base
op_assign
id|pci_ioaddr2
op_plus
l_int|0x20
suffix:semicolon
multiline_comment|/* For isac and hscx control path */
id|cs-&gt;hw.ax.base
op_assign
id|ipac_state
(braket
id|cs-&gt;subtyp
)braket
dot
id|base
suffix:semicolon
multiline_comment|/* For isac and hscx data path */
id|cs-&gt;hw.ax.data_adr
op_assign
id|cs-&gt;hw.ax.base
op_plus
l_int|4
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): NO_PCI_BIOS&bslash;n&quot;
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): Unable to configure&bslash;n&quot;
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
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PCI */
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
multiline_comment|/* Disable all currently not active ipacs */
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_1
)paren
)paren
id|set_ipac_active
c_func
(paren
id|SCT_1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_2
)paren
)paren
id|set_ipac_active
c_func
(paren
id|SCT_2
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_3
)paren
)paren
id|set_ipac_active
c_func
(paren
id|SCT_3
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_ipac_active
c_func
(paren
id|SCT_4
)paren
)paren
id|set_ipac_active
c_func
(paren
id|SCT_4
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Perfom general reset (if possible) */
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
)brace
eof
