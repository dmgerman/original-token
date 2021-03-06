multiline_comment|/* $Id: ix1_micro.c,v 2.10 2000/11/24 17:05:38 kai Exp $&n; *&n; * ix1_micro.c  low level stuff for ITK ix1-micro Rev.2 isdn cards&n; *              derived from the original file teles3.c from Karsten Keil&n; *&n; * Copyright (C) 1997 Klaus-Peter Nischke (ITK AG) (for the modifications to&n; *                                                  the original file teles.c)&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *              Beat Doebeli&n; *&n; */
multiline_comment|/*&n;   For the modification done by the author the following terms and conditions&n;   apply (GNU PUBLIC LICENSE)&n;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;&n;   You may contact Klaus-Peter Nischke by email: klaus@nischke.do.eunet.de&n;   or by conventional mail:&n;&n;   Klaus-Peter Nischke&n;   Deusener Str. 287&n;   44369 Dortmund&n;   Germany&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|ix1_revision
r_const
r_char
op_star
id|ix1_revision
op_assign
l_string|&quot;$Revision: 2.10 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|SPECIAL_PORT_OFFSET
mdefine_line|#define SPECIAL_PORT_OFFSET 3
DECL|macro|ISAC_COMMAND_OFFSET
mdefine_line|#define ISAC_COMMAND_OFFSET 2
DECL|macro|ISAC_DATA_OFFSET
mdefine_line|#define ISAC_DATA_OFFSET 0
DECL|macro|HSCX_COMMAND_OFFSET
mdefine_line|#define HSCX_COMMAND_OFFSET 2
DECL|macro|HSCX_DATA_OFFSET
mdefine_line|#define HSCX_DATA_OFFSET 1
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT 50
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
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|adr
)paren
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
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|insb
c_func
(paren
id|adr
comma
id|data
comma
id|size
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
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|byteout
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
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|outsb
c_func
(paren
id|adr
comma
id|data
comma
id|size
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
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
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
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
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
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readreg(cs-&gt;hw.ix1.hscx_ale, &bslash;&n;&t;&t;cs-&gt;hw.ix1.hscx, reg + (nr ? 0x40 : 0))
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writereg(cs-&gt;hw.ix1.hscx_ale, &bslash;&n;&t;&t;cs-&gt;hw.ix1.hscx, reg + (nr ? 0x40 : 0), data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs-&gt;hw.ix1.hscx_ale, &bslash;&n;&t;&t;cs-&gt;hw.ix1.hscx, (nr ? 0x40 : 0), ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs-&gt;hw.ix1.hscx_ale, &bslash;&n;&t;&t;cs-&gt;hw.ix1.hscx, (nr ? 0x40 : 0), ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|ix1micro_interrupt
id|ix1micro_interrupt
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
l_string|&quot;IX1: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
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
id|readreg
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|val
op_assign
id|readreg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
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
id|readreg
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
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
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.isac_ale
comma
id|cs-&gt;hw.ix1.isac
comma
id|ISAC_MASK
comma
l_int|0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_MASK
comma
l_int|0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.ix1.hscx_ale
comma
id|cs-&gt;hw.ix1.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_ix1micro
id|release_io_ix1micro
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
id|cs-&gt;hw.ix1.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
comma
l_int|4
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ix1_reset
id|ix1_reset
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
r_int
id|cnt
suffix:semicolon
multiline_comment|/* reset isac */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cnt
op_assign
l_int|3
op_star
(paren
id|HZ
op_div
l_int|10
)paren
op_plus
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cnt
op_decrement
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
op_plus
id|SPECIAL_PORT_OFFSET
comma
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* wait &gt;=10 ms */
)brace
id|byteout
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
op_plus
id|SPECIAL_PORT_OFFSET
comma
l_int|0
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
r_int
DECL|function|ix1_card_msg
id|ix1_card_msg
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
id|ix1_reset
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
id|release_io_ix1micro
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
r_int
id|__init
DECL|function|setup_ix1micro
id|setup_ix1micro
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
id|strcpy
c_func
(paren
id|tmp
comma
id|ix1_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: ITK IX1 driver Rev. %s&bslash;n&quot;
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
op_ne
id|ISDN_CTYPE_IX1MICROR2
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* IO-Ports */
id|cs-&gt;hw.ix1.isac_ale
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_COMMAND_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.hscx_ale
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|HSCX_COMMAND_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_DATA_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.hscx
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|HSCX_DATA_OFFSET
suffix:semicolon
id|cs-&gt;hw.ix1.cfg_reg
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
id|cs-&gt;hw.ix1.cfg_reg
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.ix1.cfg_reg
)paren
comma
l_int|4
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
id|cs-&gt;hw.ix1.cfg_reg
comma
id|cs-&gt;hw.ix1.cfg_reg
op_plus
l_int|4
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|request_region
c_func
(paren
id|cs-&gt;hw.ix1.cfg_reg
comma
l_int|4
comma
l_string|&quot;ix1micro cfg&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d io:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.ix1.cfg_reg
)paren
suffix:semicolon
id|ix1_reset
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
id|ix1_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|ix1micro_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;ix1-Micro:&quot;
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
l_string|&quot;ix1-Micro:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ix1-Micro: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_ix1micro
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
