multiline_comment|/* $Id: teles0.c,v 2.9 1999/07/12 21:05:31 keil Exp $&n;&n; * teles0.c     low level stuff for Teles Memory IO isdn cards&n; *              based on the teles driver from Jan den Ouden&n; *&n; * Author       Karsten Keil (keil@temic-ech.spacenet.de)&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *              Beat Doebeli&n; *&n; * $Log: teles0.c,v $&n; * Revision 2.9  1999/07/12 21:05:31  keil&n; * fix race in IRQ handling&n; * added watchdog for lost IRQs&n; *&n; * Revision 2.8  1998/04/15 16:44:28  keil&n; * new init code&n; *&n; * Revision 2.7  1998/03/07 22:57:08  tsbogend&n; * made HiSax working on Linux/Alpha&n; *&n; * Revision 2.6  1998/02/03 23:27:47  keil&n; * IRQ 9&n; *&n; * Revision 2.5  1998/02/02 13:29:47  keil&n; * fast io&n; *&n; * Revision 2.4  1997/11/08 21:35:54  keil&n; * new l1 init&n; *&n; * Revision 2.3  1997/11/06 17:09:31  keil&n; * New 2.1 init code&n; *&n; * Revision 2.2  1997/10/29 18:55:57  keil&n; * changes for 2.1.60 (irq2dev_map)&n; *&n; * Revision 2.1  1997/07/27 21:47:10  keil&n; * new interface structures&n; *&n; * Revision 2.0  1997/06/26 11:02:43  keil&n; * New Layer and card interface&n; *&n; * Revision 1.8  1997/04/13 19:54:04  keil&n; * Change in IRQ check delay for SMP&n; *&n; * Revision 1.7  1997/04/06 22:54:04  keil&n; * Using SKB&squot;s&n; *&n; * removed old log info /KKe&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|teles0_revision
r_const
r_char
op_star
id|teles0_revision
op_assign
l_string|&quot;$Revision: 2.9 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
r_static
r_inline
id|u_char
DECL|function|readisac
id|readisac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_char
id|off
)paren
(brace
r_return
id|readb
c_func
(paren
id|adr
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x2ff
suffix:colon
l_int|0x100
)paren
op_plus
id|off
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writeisac
id|writeisac
c_func
(paren
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
id|writeb
c_func
(paren
id|data
comma
id|adr
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x2ff
suffix:colon
l_int|0x100
)paren
op_plus
id|off
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u_char
DECL|function|readhscx
id|readhscx
c_func
(paren
r_int
r_int
id|adr
comma
r_int
id|hscx
comma
id|u_char
id|off
)paren
(brace
r_return
id|readb
c_func
(paren
id|adr
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0
)paren
op_plus
id|off
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writehscx
id|writehscx
c_func
(paren
r_int
r_int
id|adr
comma
r_int
id|hscx
comma
id|u_char
id|off
comma
id|u_char
id|data
)paren
(brace
id|writeb
c_func
(paren
id|data
comma
id|adr
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0
)paren
op_plus
id|off
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|read_fifo_isac
id|read_fifo_isac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
id|u_char
op_star
id|ad
op_assign
(paren
id|u_char
op_star
)paren
(paren
(paren
r_int
)paren
id|adr
op_plus
l_int|0x100
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
id|readb
c_func
(paren
id|ad
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|write_fifo_isac
id|write_fifo_isac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
id|u_char
op_star
id|ad
op_assign
(paren
id|u_char
op_star
)paren
(paren
(paren
r_int
)paren
id|adr
op_plus
l_int|0x100
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
(brace
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|ad
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|read_fifo_hscx
id|read_fifo_hscx
c_func
(paren
r_int
r_int
id|adr
comma
r_int
id|hscx
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
id|u_char
op_star
id|ad
op_assign
(paren
id|u_char
op_star
)paren
(paren
(paren
r_int
)paren
id|adr
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
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
id|readb
c_func
(paren
id|ad
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|write_fifo_hscx
id|write_fifo_hscx
c_func
(paren
r_int
r_int
id|adr
comma
r_int
id|hscx
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_int
id|i
suffix:semicolon
r_register
id|u_char
op_star
id|ad
op_assign
(paren
id|u_char
op_star
)paren
(paren
(paren
r_int
)paren
id|adr
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
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
(brace
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|ad
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|readisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
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
id|writeisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
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
id|read_fifo_isac
c_func
(paren
id|cs-&gt;hw.teles0.membase
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
id|write_fifo_isac
c_func
(paren
id|cs-&gt;hw.teles0.membase
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
id|readhscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|hscx
comma
id|offset
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
id|writehscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|hscx
comma
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readhscx(cs-&gt;hw.teles0.membase, nr, reg)
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writehscx(cs-&gt;hw.teles0.membase, nr, reg, data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) read_fifo_hscx(cs-&gt;hw.teles0.membase, nr, ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) write_fifo_hscx(cs-&gt;hw.teles0.membase, nr, ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|teles0_interrupt
id|teles0_interrupt
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
suffix:semicolon
r_int
id|count
op_assign
l_int|0
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
l_string|&quot;Teles0: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|val
op_assign
id|readhscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
id|Start_HSCX
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|readisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|ISAC_ISTA
)paren
suffix:semicolon
id|Start_ISAC
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|val
op_assign
id|readhscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
id|count
OL
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_HSCX
suffix:semicolon
)brace
id|val
op_assign
id|readisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|ISAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
id|count
OL
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_ISAC
suffix:semicolon
)brace
id|writehscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writehscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writeisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writeisac
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writehscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writehscx
c_func
(paren
id|cs-&gt;hw.teles0.membase
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_teles0
id|release_io_teles0
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
id|cs-&gt;hw.teles0.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|reset_teles0
id|reset_teles0
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|u_char
id|cfval
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
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_switch
c_cond
(paren
id|cs-&gt;irq
)paren
(brace
r_case
l_int|2
suffix:colon
r_case
l_int|9
suffix:colon
id|cfval
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|cfval
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|cfval
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|cfval
op_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|cfval
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|cfval
op_assign
l_int|0x0A
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|cfval
op_assign
l_int|0x0C
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|cfval
op_assign
l_int|0x0E
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
id|cfval
op_or_assign
(paren
(paren
id|cs-&gt;hw.teles0.membase
op_rshift
l_int|9
)paren
op_amp
l_int|0xF0
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|4
comma
id|cfval
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|4
comma
id|cfval
op_or
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|writeb
c_func
(paren
l_int|0
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x80
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|5
op_plus
l_int|1
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|1
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x80
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|5
op_plus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|Teles_card_msg
id|Teles_card_msg
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
id|reset_teles0
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_teles0
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|inithscxisac
c_func
(paren
id|cs
comma
l_int|3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|setup_teles0
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
)paren
(brace
id|u_char
id|val
suffix:semicolon
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
id|strcpy
c_func
(paren
id|tmp
comma
id|teles0_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Teles 8.0/16.0 driver Rev. %s&bslash;n&quot;
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
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_16_0
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_8_0
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
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_16_0
)paren
id|cs-&gt;hw.teles0.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
suffix:semicolon
r_else
multiline_comment|/* 8.0 */
id|cs-&gt;hw.teles0.cfg_reg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|1
)braket
OL
l_int|0x10000
)paren
(brace
id|card-&gt;para
(braket
l_int|1
)braket
op_lshift_assign
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Teles0: membase configured DOSish, assuming 0x%lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|card-&gt;para
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|cs-&gt;hw.teles0.membase
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
comma
l_int|8
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s config port %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.teles0.cfg_reg
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
comma
l_string|&quot;teles cfg&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|0
)paren
)paren
op_ne
l_int|0x51
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|0
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
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
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|1
)paren
)paren
op_ne
l_int|0x93
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|1
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 0x1e=without AB&n;&t;&t;&t;&t;&t;&t;&t;&t;   * 0x1f=with AB&n;&t;&t;&t;&t;&t;&t;&t;&t;   * 0x1c 16.3 ???&n;&t;&t;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|val
op_ne
l_int|0x1e
op_logical_and
id|val
op_ne
l_int|0x1f
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|2
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* 16.0 and 8.0 designed for IOM1 */
id|test_and_set_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d mem:0x%X cfg:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.teles0.membase
comma
id|cs-&gt;hw.teles0.cfg_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_teles0
c_func
(paren
id|cs
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_teles0
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
)brace
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
id|Teles_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|teles0_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Teles0:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HscxVersion
c_func
(paren
id|cs
comma
l_string|&quot;Teles0:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: wrong HSCX versions check IO/MEM addresses&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_teles0
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
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
