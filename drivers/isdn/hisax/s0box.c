multiline_comment|/* $Id: s0box.c,v 2.2 1999/07/12 21:05:25 keil Exp $&n;&n; * s0box.c      low level stuff for Creatix S0BOX&n; *&n; * Author       S0BOX specific stuff: Enrik Berkhan (enrik@starfleet.inka.de)&n; *&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
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
DECL|variable|s0box_revision
r_const
r_char
op_star
id|s0box_revision
op_assign
l_string|&quot;$Revision: 2.2 $&quot;
suffix:semicolon
r_static
r_inline
r_void
DECL|function|writereg
id|writereg
c_func
(paren
r_int
r_int
id|padr
comma
r_int
r_int
id|addr
comma
id|u_char
id|off
comma
id|u_char
id|val
)paren
(brace
r_int
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
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|addr
op_plus
id|off
)paren
op_amp
l_int|0x7f
comma
id|padr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|padr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x17
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|nibtab
r_static
id|u_char
id|nibtab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|9
comma
l_int|5
comma
l_int|0xd
comma
l_int|3
comma
l_int|0xb
comma
l_int|7
comma
l_int|0xf
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|8
comma
l_int|4
comma
l_int|0xc
comma
l_int|2
comma
l_int|0xa
comma
l_int|6
comma
l_int|0xe
)brace
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
id|padr
comma
r_int
r_int
id|addr
comma
id|u_char
id|off
)paren
(brace
r_register
id|u_char
id|n1
comma
id|n2
suffix:semicolon
r_int
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
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|addr
op_plus
id|off
)paren
op_or
l_int|0x80
comma
id|padr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x17
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|n1
op_assign
(paren
id|inb_p
c_func
(paren
id|padr
op_plus
l_int|1
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x17
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|n2
op_assign
(paren
id|inb_p
c_func
(paren
id|padr
op_plus
l_int|1
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x17
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|nibtab
(braket
id|n1
)braket
op_or
(paren
id|nibtab
(braket
id|n2
)braket
op_lshift
l_int|4
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|read_fifo
id|read_fifo
c_func
(paren
r_int
r_int
id|padr
comma
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
r_int
id|i
suffix:semicolon
r_register
id|u_char
id|n1
comma
id|n2
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|adr
op_or
l_int|0x80
comma
id|padr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
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
id|outb_p
c_func
(paren
l_int|0x17
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|n1
op_assign
(paren
id|inb_p
c_func
(paren
id|padr
op_plus
l_int|1
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x17
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|n2
op_assign
(paren
id|inb_p
c_func
(paren
id|padr
op_plus
l_int|1
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x17
suffix:semicolon
op_star
(paren
id|data
op_increment
)paren
op_assign
id|nibtab
(braket
id|n1
)braket
op_or
(paren
id|nibtab
(braket
id|n2
)braket
op_lshift
l_int|4
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|write_fifo
id|write_fifo
c_func
(paren
r_int
r_int
id|padr
comma
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
r_int
id|i
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|adr
op_amp
l_int|0x7f
comma
id|padr
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
id|outb_p
c_func
(paren
l_int|0x16
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
comma
id|padr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x17
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0x14
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x1c
comma
id|padr
op_plus
l_int|2
)paren
suffix:semicolon
r_return
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
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
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
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
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
id|read_fifo
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isacfifo
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
id|write_fifo
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isacfifo
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
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
id|hscx
)braket
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
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
id|hscx
)braket
comma
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readreg(cs-&gt;hw.teles3.cfg_reg, cs-&gt;hw.teles3.hscx[nr], reg)
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writereg(cs-&gt;hw.teles3.cfg_reg, cs-&gt;hw.teles3.hscx[nr], reg, data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) read_fifo(cs-&gt;hw.teles3.cfg_reg, cs-&gt;hw.teles3.hscxfifo[nr], ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) write_fifo(cs-&gt;hw.teles3.cfg_reg, cs-&gt;hw.teles3.hscxfifo[nr], ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|s0box_interrupt
id|s0box_interrupt
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
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 5
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
l_string|&quot;Teles: Spurious interrupt!&bslash;n&quot;
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
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
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
id|readreg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
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
id|readreg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
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
id|MAXCOUNT
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
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
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
id|MAXCOUNT
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
r_if
c_cond
(paren
id|count
op_ge
id|MAXCOUNT
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;S0Box: more than %d loops in s0box_interrupt&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.isac
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_s0box
id|release_io_s0box
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
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|S0Box_card_msg
id|S0Box_card_msg
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
r_break
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_s0box
c_func
(paren
id|cs
)paren
suffix:semicolon
r_break
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
r_break
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_break
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
id|setup_s0box
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
id|strcpy
c_func
(paren
id|tmp
comma
id|s0box_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: S0Box IO driver Rev. %s&bslash;n&quot;
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
id|ISDN_CTYPE_S0BOX
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|cs-&gt;hw.teles3.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_assign
op_minus
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_assign
l_int|0x0
suffix:semicolon
id|cs-&gt;hw.teles3.isac
op_assign
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.teles3.isacfifo
op_assign
id|cs-&gt;hw.teles3.isac
op_plus
l_int|0x3e
suffix:semicolon
id|cs-&gt;hw.teles3.hscxfifo
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
op_plus
l_int|0x3e
suffix:semicolon
id|cs-&gt;hw.teles3.hscxfifo
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
op_plus
l_int|0x3e
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
id|check_region
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|8
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s ports %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.teles3.cfg_reg
comma
id|cs-&gt;hw.teles3.cfg_reg
op_plus
l_int|7
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|request_region
c_func
(paren
id|cs-&gt;hw.teles3.cfg_reg
comma
l_int|8
comma
l_string|&quot;S0Box parallel I/O&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d isac:0x%x  cfg:0x%x&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.teles3.isac
comma
id|cs-&gt;hw.teles3.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: hscx A:0x%x  hscx B:0x%x&bslash;n&quot;
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|0
)braket
comma
id|cs-&gt;hw.teles3.hscx
(braket
l_int|1
)braket
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
id|S0Box_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|s0box_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;S0Box:&quot;
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
l_string|&quot;S0Box:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;S0Box: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_s0box
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
