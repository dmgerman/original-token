multiline_comment|/* $Id: tc.c,v 1.3 1999/10/09 00:01:32 ralf Exp $&n; * tc-init: We assume the TURBOchannel to be up and running so&n; * just probe for Modules and fill in the global data structure&n; * tc_bus.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) Harald Koerfgen, 1998&n; *&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/dec/machtype.h&gt;
macro_line|#include &lt;asm/dec/tcinfo.h&gt;
macro_line|#include &lt;asm/dec/tcmodule.h&gt;
macro_line|#include &lt;asm/dec/interrupts.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|TC_DEBUG
mdefine_line|#define TC_DEBUG
DECL|variable|tc_bus
id|slot_info
id|tc_bus
(braket
id|MAX_SLOT
)braket
suffix:semicolon
DECL|variable|max_tcslot
r_static
r_int
id|max_tcslot
op_assign
l_int|0
suffix:semicolon
DECL|variable|info
r_static
id|tcinfo
op_star
id|info
op_assign
(paren
id|tcinfo
op_star
)paren
l_int|0
suffix:semicolon
DECL|variable|system_base
r_int
r_int
id|system_base
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
(paren
op_star
id|dbe_board_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
(paren
op_star
id|rex_slot_address
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
(paren
op_star
id|rex_gettcinfo
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Interface to the world. Read comment in include/asm-mips/tc.h.&n; */
DECL|function|search_tc_card
r_int
id|search_tc_card
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|slot
suffix:semicolon
id|slot_info
op_star
id|sip
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
op_le
id|max_tcslot
suffix:semicolon
id|slot
op_increment
)paren
(brace
id|sip
op_assign
op_amp
id|tc_bus
(braket
id|slot
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sip-&gt;flags
op_amp
id|FREE
)paren
op_logical_and
(paren
id|strncmp
c_func
(paren
id|sip-&gt;name
comma
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|0
)paren
)paren
(brace
r_return
id|slot
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|claim_tc_card
r_void
id|claim_tc_card
c_func
(paren
r_int
id|slot
)paren
(brace
r_if
c_cond
(paren
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_amp
id|IN_USE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;claim_tc_card: attempting to claim a card already in use&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_and_assign
op_complement
id|FREE
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_or_assign
id|IN_USE
suffix:semicolon
)brace
DECL|function|release_tc_card
r_void
id|release_tc_card
c_func
(paren
r_int
id|slot
)paren
(brace
r_if
c_cond
(paren
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_amp
id|FREE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;release_tc_card: attempting to release a card already free&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_and_assign
op_complement
id|IN_USE
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|flags
op_or_assign
id|FREE
suffix:semicolon
)brace
DECL|function|get_tc_base_addr
r_int
r_int
id|get_tc_base_addr
c_func
(paren
r_int
id|slot
)paren
(brace
r_return
id|tc_bus
(braket
id|slot
)braket
dot
id|base_addr
suffix:semicolon
)brace
DECL|function|get_tc_irq_nr
r_int
r_int
id|get_tc_irq_nr
c_func
(paren
r_int
id|slot
)paren
(brace
r_return
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
suffix:semicolon
)brace
DECL|function|get_tc_speed
r_int
r_int
id|get_tc_speed
c_func
(paren
r_void
)paren
(brace
r_return
l_int|100000
op_star
(paren
l_int|10000
op_div
(paren
r_int
r_int
)paren
id|info-&gt;clk_period
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Probing for TURBOchannel modules&n; */
DECL|function|my_dbe_handler
r_static
r_void
id|__init
id|my_dbe_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;cp0_epc
op_add_assign
l_int|4
suffix:semicolon
)brace
DECL|function|tc_probe
r_static
r_void
id|__init
id|tc_probe
c_func
(paren
r_int
r_int
id|startaddr
comma
r_int
r_int
id|size
comma
r_int
id|max_slot
)paren
(brace
r_int
id|i
comma
id|slot
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_int
r_char
op_star
id|module
suffix:semicolon
r_void
(paren
op_star
id|old_be_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/* Install our exception handler temporarily */
id|old_be_handler
op_assign
id|dbe_board_handler
suffix:semicolon
id|dbe_board_handler
op_assign
id|my_dbe_handler
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
op_le
id|max_slot
suffix:semicolon
id|slot
op_increment
)paren
(brace
id|module
op_assign
(paren
r_char
op_star
)paren
(paren
id|startaddr
op_plus
id|slot
op_star
id|size
)paren
suffix:semicolon
id|offset
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|module
(braket
id|OLDCARD
op_plus
id|PATTERN0
)braket
op_eq
l_int|0x55
op_logical_and
id|module
(braket
id|OLDCARD
op_plus
id|PATTERN1
)braket
op_eq
l_int|0x00
op_logical_and
id|module
(braket
id|OLDCARD
op_plus
id|PATTERN2
)braket
op_eq
l_int|0xaa
op_logical_and
id|module
(braket
id|OLDCARD
op_plus
id|PATTERN3
)braket
op_eq
l_int|0xff
)paren
id|offset
op_assign
id|OLDCARD
suffix:semicolon
r_if
c_cond
(paren
id|module
(braket
id|PATTERN0
)braket
op_eq
l_int|0x55
op_logical_and
id|module
(braket
id|PATTERN1
)braket
op_eq
l_int|0x00
op_logical_and
id|module
(braket
id|PATTERN2
)braket
op_eq
l_int|0xaa
op_logical_and
id|module
(braket
id|PATTERN3
)braket
op_eq
l_int|0xff
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ne
op_minus
l_int|1
)paren
(brace
id|tc_bus
(braket
id|slot
)braket
dot
id|base_addr
op_assign
(paren
r_int
r_int
)paren
id|module
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tc_bus
(braket
id|slot
)braket
dot
id|firmware
(braket
id|i
)braket
op_assign
id|module
(braket
id|FIRM_VER
op_plus
id|offset
op_plus
l_int|4
op_star
id|i
)braket
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|vendor
(braket
id|i
)braket
op_assign
id|module
(braket
id|VENDOR
op_plus
id|offset
op_plus
l_int|4
op_star
id|i
)braket
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|name
(braket
id|i
)braket
op_assign
id|module
(braket
id|MODULE
op_plus
id|offset
op_plus
l_int|4
op_star
id|i
)braket
suffix:semicolon
)brace
id|tc_bus
(braket
id|slot
)braket
dot
id|firmware
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|vendor
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|slot
)braket
dot
id|name
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Looks unneccesary, but we may change&n;&t;&t;&t; * TC? in the future&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|0
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
id|TC0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
id|TC1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
id|TC2
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Yuck! DS5000/200 onboard devices&n;&t;&t;&t; */
r_case
l_int|5
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
id|SCSI_INT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
id|ETHER
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tc_bus
(braket
id|slot
)braket
dot
id|interrupt
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|dbe_board_handler
op_assign
id|old_be_handler
suffix:semicolon
)brace
multiline_comment|/*&n; * the main entry&n; */
DECL|function|tc_init
r_void
id|__init
id|tc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|tc_clock
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|slot0addr
suffix:semicolon
r_int
r_int
id|slot_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TURBOCHANNEL
)paren
r_return
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
id|MAX_SLOT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tc_bus
(braket
id|i
)braket
dot
id|base_addr
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|i
)braket
dot
id|name
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|i
)braket
dot
id|vendor
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|i
)braket
dot
id|firmware
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|tc_bus
(braket
id|i
)braket
dot
id|interrupt
op_assign
op_minus
l_int|1
suffix:semicolon
id|tc_bus
(braket
id|i
)braket
dot
id|flags
op_assign
id|FREE
suffix:semicolon
)brace
id|info
op_assign
(paren
id|tcinfo
op_star
)paren
id|rex_gettcinfo
c_func
(paren
)paren
suffix:semicolon
id|slot0addr
op_assign
(paren
r_int
r_int
)paren
id|KSEG1ADDR
c_func
(paren
id|rex_slot_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_DS5000_200
suffix:colon
id|max_tcslot
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_DS5000_1XX
suffix:colon
r_case
id|MACH_DS5000_2X0
suffix:colon
id|max_tcslot
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_DS5000_XX
suffix:colon
r_default
suffix:colon
id|max_tcslot
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tc_clock
op_assign
l_int|10000
op_div
id|info-&gt;clk_period
suffix:semicolon
r_if
c_cond
(paren
id|TURBOCHANNEL
op_logical_and
id|info-&gt;slot_size
op_logical_and
id|slot0addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TURBOchannel rev. %1d at %2d.%1d MHz &quot;
comma
id|info-&gt;revision
comma
id|tc_clock
op_div
l_int|10
comma
id|tc_clock
op_mod
l_int|10
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(%sparity)&bslash;n&quot;
comma
id|info-&gt;parity
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
id|slot_size
op_assign
id|info-&gt;slot_size
op_lshift
l_int|20
suffix:semicolon
id|tc_probe
c_func
(paren
id|slot0addr
comma
id|slot_size
comma
id|max_tcslot
)paren
suffix:semicolon
multiline_comment|/*&n;  &t;&t; * All TURBOchannel DECstations have the onboard devices&n; &t;&t; * where the (max_tcslot + 1 or 2 on DS5k/xx) Option Module&n; &t;&t; * would be.&n; &t;&t; */
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_DS5000_XX
)paren
(brace
id|i
op_assign
l_int|2
suffix:semicolon
)brace
r_else
id|i
op_assign
l_int|1
suffix:semicolon
id|system_base
op_assign
id|slot0addr
op_plus
id|slot_size
op_star
(paren
id|max_tcslot
op_plus
id|i
)paren
suffix:semicolon
macro_line|#ifdef TC_DEBUG
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|max_tcslot
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|tc_bus
(braket
id|i
)braket
dot
id|base_addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    slot %d: &quot;
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s %s %s&bslash;n&quot;
comma
id|tc_bus
(braket
id|i
)braket
dot
id|vendor
comma
id|tc_bus
(braket
id|i
)braket
dot
id|name
comma
id|tc_bus
(braket
id|i
)braket
dot
id|firmware
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ioport_resource.end
op_assign
id|KSEG2
op_minus
l_int|1
suffix:semicolon
)brace
)brace
eof
