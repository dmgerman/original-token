multiline_comment|/* $Id: sparc-stub.c,v 1.19 1996/09/30 02:21:48 davem Exp $&n; * sparc-stub.c:  KGDB support for the Linux kernel.&n; *&n; * Modifications to run under Linux&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * This file originally came from the gdb sources, and the&n; * copyright notices have been retained below.&n; */
multiline_comment|/****************************************************************************&n;&n;&t;&t;THIS SOFTWARE IS NOT COPYRIGHTED&n;&n;   HP offers the following for use in the public domain.  HP makes no&n;   warranty with regard to the software or its performance and the&n;   user accepts the software &quot;AS IS&quot; with all faults.&n;&n;   HP DISCLAIMS ANY WARRANTIES, EXPRESS OR IMPLIED, WITH REGARD&n;   TO THIS SOFTWARE INCLUDING BUT NOT LIMITED TO THE WARRANTIES&n;   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n;&n;****************************************************************************/
multiline_comment|/****************************************************************************&n; *  Header: remcom.c,v 1.34 91/03/09 12:29:49 glenne Exp $&n; *&n; *  Module name: remcom.c $&n; *  Revision: 1.34 $&n; *  Date: 91/03/09 12:29:49 $&n; *  Contributor:     Lake Stevens Instrument Division$&n; *&n; *  Description:     low level support for gdb debugger. $&n; *&n; *  Considerations:  only works on target hardware $&n; *&n; *  Written by:      Glenn Engel $&n; *  ModuleState:     Experimental $&n; *&n; *  NOTES:           See Below $&n; *&n; *  Modified for SPARC by Stu Grossman, Cygnus Support.&n; *&n; *  This code has been extensively tested on the Fujitsu SPARClite demo board.&n; *&n; *  To enable debugger support, two things need to happen.  One, a&n; *  call to set_debug_traps() is necessary in order to allow any breakpoints&n; *  or error conditions to be properly intercepted and reported to gdb.&n; *  Two, a breakpoint needs to be generated to begin communication.  This&n; *  is most easily accomplished by a call to breakpoint().  Breakpoint()&n; *  simulates a breakpoint by executing a trap #1.&n; *&n; *************&n; *&n; *    The following gdb commands are supported:&n; *&n; * command          function                               Return value&n; *&n; *    g             return the value of the CPU registers  hex data or ENN&n; *    G             set the value of the CPU registers     OK or ENN&n; *&n; *    mAA..AA,LLLL  Read LLLL bytes at address AA..AA      hex data or ENN&n; *    MAA..AA,LLLL: Write LLLL bytes at address AA.AA      OK or ENN&n; *&n; *    c             Resume at current address              SNN   ( signal NN)&n; *    cAA..AA       Continue at address AA..AA             SNN&n; *&n; *    s             Step one instruction                   SNN&n; *    sAA..AA       Step one instruction from AA..AA       SNN&n; *&n; *    k             kill&n; *&n; *    ?             What was the last sigval ?             SNN   (signal NN)&n; *&n; *    bBB..BB&t;    Set baud rate to BB..BB&t;&t;   OK or BNN, then sets&n; *&t;&t;&t;&t;&t;&t;&t;   baud rate&n; *&n; * All commands and responses are sent with a packet which includes a&n; * checksum.  A packet consists of&n; *&n; * $&lt;packet info&gt;#&lt;checksum&gt;.&n; *&n; * where&n; * &lt;packet info&gt; :: &lt;characters representing the command or response&gt;&n; * &lt;checksum&gt;    :: &lt; two hex digits computed as modulo 256 sum of &lt;packetinfo&gt;&gt;&n; *&n; * When a packet is received, it is first acknowledged with either &squot;+&squot; or &squot;-&squot;.&n; * &squot;+&squot; indicates a successful transfer.  &squot;-&squot; indicates a failed transfer.&n; *&n; * Example:&n; *&n; * Host:                  Reply:&n; * $m0,10#2a               +$00010203040506070809101112131415#42&n; *&n; ****************************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; *&n; * external low-level support routines&n; */
r_extern
r_void
id|putDebugChar
c_func
(paren
r_char
)paren
suffix:semicolon
multiline_comment|/* write a single character      */
r_extern
r_char
id|getDebugChar
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* read and return a single char */
multiline_comment|/*&n; * BUFMAX defines the maximum number of characters in inbound/outbound buffers&n; * at least NUMREGBYTES*2 are needed for register packets&n; */
DECL|macro|BUFMAX
mdefine_line|#define BUFMAX 2048
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* !0 means we&squot;ve been initialized */
DECL|variable|hexchars
r_static
r_const
r_char
id|hexchars
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
DECL|macro|NUMREGS
mdefine_line|#define NUMREGS 72
multiline_comment|/* Number of bytes of registers.  */
DECL|macro|NUMREGBYTES
mdefine_line|#define NUMREGBYTES (NUMREGS * 4)
DECL|enum|regnames
DECL|enumerator|G0
DECL|enumerator|G1
DECL|enumerator|G2
DECL|enumerator|G3
DECL|enumerator|G4
DECL|enumerator|G5
DECL|enumerator|G6
DECL|enumerator|G7
r_enum
id|regnames
(brace
id|G0
comma
id|G1
comma
id|G2
comma
id|G3
comma
id|G4
comma
id|G5
comma
id|G6
comma
id|G7
comma
DECL|enumerator|O0
DECL|enumerator|O1
DECL|enumerator|O2
DECL|enumerator|O3
DECL|enumerator|O4
DECL|enumerator|O5
DECL|enumerator|SP
DECL|enumerator|O7
id|O0
comma
id|O1
comma
id|O2
comma
id|O3
comma
id|O4
comma
id|O5
comma
id|SP
comma
id|O7
comma
DECL|enumerator|L0
DECL|enumerator|L1
DECL|enumerator|L2
DECL|enumerator|L3
DECL|enumerator|L4
DECL|enumerator|L5
DECL|enumerator|L6
DECL|enumerator|L7
id|L0
comma
id|L1
comma
id|L2
comma
id|L3
comma
id|L4
comma
id|L5
comma
id|L6
comma
id|L7
comma
DECL|enumerator|I0
DECL|enumerator|I1
DECL|enumerator|I2
DECL|enumerator|I3
DECL|enumerator|I4
DECL|enumerator|I5
DECL|enumerator|FP
DECL|enumerator|I7
id|I0
comma
id|I1
comma
id|I2
comma
id|I3
comma
id|I4
comma
id|I5
comma
id|FP
comma
id|I7
comma
DECL|enumerator|F0
DECL|enumerator|F1
DECL|enumerator|F2
DECL|enumerator|F3
DECL|enumerator|F4
DECL|enumerator|F5
DECL|enumerator|F6
DECL|enumerator|F7
id|F0
comma
id|F1
comma
id|F2
comma
id|F3
comma
id|F4
comma
id|F5
comma
id|F6
comma
id|F7
comma
DECL|enumerator|F8
DECL|enumerator|F9
DECL|enumerator|F10
DECL|enumerator|F11
DECL|enumerator|F12
DECL|enumerator|F13
DECL|enumerator|F14
DECL|enumerator|F15
id|F8
comma
id|F9
comma
id|F10
comma
id|F11
comma
id|F12
comma
id|F13
comma
id|F14
comma
id|F15
comma
DECL|enumerator|F16
DECL|enumerator|F17
DECL|enumerator|F18
DECL|enumerator|F19
DECL|enumerator|F20
DECL|enumerator|F21
DECL|enumerator|F22
DECL|enumerator|F23
id|F16
comma
id|F17
comma
id|F18
comma
id|F19
comma
id|F20
comma
id|F21
comma
id|F22
comma
id|F23
comma
DECL|enumerator|F24
DECL|enumerator|F25
DECL|enumerator|F26
DECL|enumerator|F27
DECL|enumerator|F28
DECL|enumerator|F29
DECL|enumerator|F30
DECL|enumerator|F31
id|F24
comma
id|F25
comma
id|F26
comma
id|F27
comma
id|F28
comma
id|F29
comma
id|F30
comma
id|F31
comma
DECL|enumerator|Y
DECL|enumerator|PSR
DECL|enumerator|WIM
DECL|enumerator|TBR
DECL|enumerator|PC
DECL|enumerator|NPC
DECL|enumerator|FPSR
DECL|enumerator|CPSR
id|Y
comma
id|PSR
comma
id|WIM
comma
id|TBR
comma
id|PC
comma
id|NPC
comma
id|FPSR
comma
id|CPSR
)brace
suffix:semicolon
r_extern
r_void
id|trap_low
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* In arch/sparc/kernel/entry.S */
DECL|function|get_sun4cpte
r_int
r_int
id|get_sun4cpte
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|get_sun4csegmap
r_int
r_int
id|get_sun4csegmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlduba [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|flush_cache_all_nop
r_static
r_void
id|flush_cache_all_nop
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Place where we save old trap entries for restoration */
DECL|variable|kgdb_savettable
r_struct
id|tt_entry
id|kgdb_savettable
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|trapfunc_t
r_typedef
r_void
(paren
op_star
id|trapfunc_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Helper routine for manipulation of kgdb_savettable */
DECL|function|copy_ttentry
r_static
r_inline
r_void
id|copy_ttentry
c_func
(paren
r_struct
id|tt_entry
op_star
id|src
comma
r_struct
id|tt_entry
op_star
id|dest
)paren
(brace
id|dest-&gt;inst_one
op_assign
id|src-&gt;inst_one
suffix:semicolon
id|dest-&gt;inst_two
op_assign
id|src-&gt;inst_two
suffix:semicolon
id|dest-&gt;inst_three
op_assign
id|src-&gt;inst_three
suffix:semicolon
id|dest-&gt;inst_four
op_assign
id|src-&gt;inst_four
suffix:semicolon
)brace
multiline_comment|/* Initialize the kgdb_savettable so that debugging can commence */
DECL|function|eh_init
r_static
r_void
id|eh_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|copy_ttentry
c_func
(paren
op_amp
id|sparc_ttable
(braket
id|i
)braket
comma
op_amp
id|kgdb_savettable
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Install an exception handler for kgdb */
DECL|function|exceptionHandler
r_static
r_void
id|exceptionHandler
c_func
(paren
r_int
id|tnum
comma
id|trapfunc_t
id|trap_entry
)paren
(brace
r_int
r_int
id|te_addr
op_assign
(paren
r_int
r_int
)paren
id|trap_entry
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* We are dorking with a live trap table, all irqs off */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Make new vector */
id|sparc_ttable
(braket
id|tnum
)braket
dot
id|inst_one
op_assign
id|SPARC_BRANCH
c_func
(paren
(paren
r_int
r_int
)paren
id|te_addr
comma
(paren
r_int
r_int
)paren
op_amp
id|sparc_ttable
(braket
id|tnum
)braket
dot
id|inst_one
)paren
suffix:semicolon
id|sparc_ttable
(braket
id|tnum
)braket
dot
id|inst_two
op_assign
id|SPARC_RD_PSR_L0
suffix:semicolon
id|sparc_ttable
(braket
id|tnum
)braket
dot
id|inst_three
op_assign
id|SPARC_NOP
suffix:semicolon
id|sparc_ttable
(braket
id|tnum
)braket
dot
id|inst_four
op_assign
id|SPARC_NOP
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert ch from a hex digit to an int */
r_static
r_int
DECL|function|hex
id|hex
c_func
(paren
r_int
r_char
id|ch
)paren
(brace
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;f&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;0&squot;
op_logical_and
id|ch
op_le
l_char|&squot;9&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;A&squot;
op_logical_and
id|ch
op_le
l_char|&squot;F&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* scan for the sequence $&lt;data&gt;#&lt;checksum&gt;     */
r_static
r_void
DECL|function|getpacket
id|getpacket
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
r_char
id|checksum
suffix:semicolon
r_int
r_char
id|xmitcsum
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
r_do
(brace
multiline_comment|/* wait around for the start character, ignore all other characters */
r_while
c_loop
(paren
(paren
id|ch
op_assign
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
)paren
op_ne
l_char|&squot;$&squot;
)paren
suffix:semicolon
id|checksum
op_assign
l_int|0
suffix:semicolon
id|xmitcsum
op_assign
op_minus
l_int|1
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now, read until a # or end of buffer is found */
r_while
c_loop
(paren
id|count
OL
id|BUFMAX
)paren
(brace
id|ch
op_assign
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;#&squot;
)paren
r_break
suffix:semicolon
id|checksum
op_assign
id|checksum
op_plus
id|ch
suffix:semicolon
id|buffer
(braket
id|count
)braket
op_assign
id|ch
suffix:semicolon
id|count
op_assign
id|count
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ge
id|BUFMAX
)paren
r_continue
suffix:semicolon
id|buffer
(braket
id|count
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;#&squot;
)paren
(brace
id|xmitcsum
op_assign
id|hex
c_func
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
op_lshift
l_int|4
suffix:semicolon
id|xmitcsum
op_or_assign
id|hex
c_func
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
id|xmitcsum
)paren
id|putDebugChar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
multiline_comment|/* failed checksum */
r_else
(brace
id|putDebugChar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
multiline_comment|/* successful transfer */
multiline_comment|/* if a sequence char is present, reply the ID */
r_if
c_cond
(paren
id|buffer
(braket
l_int|2
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|putDebugChar
c_func
(paren
id|buffer
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* remove sequence chars from buffer */
id|count
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
)paren
id|buffer
(braket
id|i
op_minus
l_int|3
)braket
op_assign
id|buffer
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
)brace
)brace
r_while
c_loop
(paren
id|checksum
op_ne
id|xmitcsum
)paren
suffix:semicolon
)brace
multiline_comment|/* send the packet in buffer.  */
r_static
r_void
DECL|function|putpacket
id|putpacket
c_func
(paren
r_int
r_char
op_star
id|buffer
)paren
(brace
r_int
r_char
id|checksum
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_char
id|ch
comma
id|recv
suffix:semicolon
multiline_comment|/*  $&lt;packet info&gt;#&lt;checksum&gt;. */
r_do
(brace
id|putDebugChar
c_func
(paren
l_char|&squot;$&squot;
)paren
suffix:semicolon
id|checksum
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|buffer
(braket
id|count
)braket
)paren
)paren
(brace
id|putDebugChar
c_func
(paren
id|ch
)paren
suffix:semicolon
id|checksum
op_add_assign
id|ch
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|putDebugChar
c_func
(paren
l_char|&squot;#&squot;
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|hexchars
(braket
id|checksum
op_rshift
l_int|4
)braket
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|hexchars
(braket
id|checksum
op_amp
l_int|0xf
)braket
)paren
suffix:semicolon
id|recv
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|recv
op_amp
l_int|0x7f
)paren
op_ne
l_char|&squot;+&squot;
)paren
suffix:semicolon
)brace
DECL|variable|remcomInBuffer
r_static
r_char
id|remcomInBuffer
(braket
id|BUFMAX
)braket
suffix:semicolon
DECL|variable|remcomOutBuffer
r_static
r_char
id|remcomOutBuffer
(braket
id|BUFMAX
)braket
suffix:semicolon
multiline_comment|/* Convert the memory pointed to by mem into hex, placing result in buf.&n; * Return a pointer to the last char put in buf (null), in case of mem fault,&n; * return 0.&n; */
r_static
r_int
r_char
op_star
DECL|function|mem2hex
id|mem2hex
c_func
(paren
r_char
op_star
id|mem
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
id|ch
op_assign
op_star
id|mem
op_increment
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hexchars
(braket
id|ch
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hexchars
(braket
id|ch
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
op_star
id|buf
op_assign
l_int|0
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/* convert the hex array pointed to by buf into binary to be placed in mem&n; * return a pointer to the character AFTER the last byte written.&n;*/
r_static
r_char
op_star
DECL|function|hex2mem
id|hex2mem
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|mem
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|ch
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch
op_assign
id|hex
c_func
(paren
op_star
id|buf
op_increment
)paren
op_lshift
l_int|4
suffix:semicolon
id|ch
op_or_assign
id|hex
c_func
(paren
op_star
id|buf
op_increment
)paren
suffix:semicolon
op_star
id|mem
op_increment
op_assign
id|ch
suffix:semicolon
)brace
r_return
id|mem
suffix:semicolon
)brace
multiline_comment|/* This table contains the mapping between SPARC hardware trap types, and&n;   signals, which are primarily what GDB understands.  It also indicates&n;   which hardware traps we need to commandeer when initializing the stub. */
DECL|struct|hard_trap_info
r_static
r_struct
id|hard_trap_info
(brace
DECL|member|tt
r_int
r_char
id|tt
suffix:semicolon
multiline_comment|/* Trap type code for SPARC */
DECL|member|signo
r_int
r_char
id|signo
suffix:semicolon
multiline_comment|/* Signal that we map this trap into */
DECL|variable|hard_trap_info
)brace
id|hard_trap_info
(braket
)braket
op_assign
(brace
(brace
id|SP_TRAP_SBPT
comma
id|SIGTRAP
)brace
comma
multiline_comment|/* ta 1 - Linux/KGDB software breakpoint */
(brace
l_int|0
comma
l_int|0
)brace
multiline_comment|/* Must be last */
)brace
suffix:semicolon
multiline_comment|/* Set up exception handlers for tracing and breakpoints */
r_void
DECL|function|set_debug_traps
id|set_debug_traps
c_func
(paren
r_void
)paren
(brace
r_struct
id|hard_trap_info
op_star
id|ht
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|flush_cache_all
op_assign
id|flush_cache_all_nop
suffix:semicolon
multiline_comment|/* Initialize our copy of the Linux Sparc trap table */
id|eh_init
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ht
op_assign
id|hard_trap_info
suffix:semicolon
id|ht-&gt;tt
op_logical_and
id|ht-&gt;signo
suffix:semicolon
id|ht
op_increment
)paren
(brace
multiline_comment|/* Only if it doesn&squot;t destroy our fault handlers */
r_if
c_cond
(paren
(paren
id|ht-&gt;tt
op_ne
id|SP_TRAP_TFLT
)paren
op_logical_and
(paren
id|ht-&gt;tt
op_ne
id|SP_TRAP_DFLT
)paren
)paren
(brace
id|exceptionHandler
c_func
(paren
id|ht-&gt;tt
comma
id|trap_low
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* In case GDB is started before us, ack any packets (presumably&n;&t; * &quot;$?#xx&quot;) sitting there.&n;&t; */
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;$&squot;
)paren
(brace
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;#&squot;
)paren
(brace
suffix:semicolon
)brace
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* eat first csum byte */
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* eat second csum byte */
id|putDebugChar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
multiline_comment|/* ack it */
id|initialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* connect! */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert the SPARC hardware trap type code to a unix signal number. */
r_static
r_int
DECL|function|computeSignal
id|computeSignal
c_func
(paren
r_int
id|tt
)paren
(brace
r_struct
id|hard_trap_info
op_star
id|ht
suffix:semicolon
r_for
c_loop
(paren
id|ht
op_assign
id|hard_trap_info
suffix:semicolon
id|ht-&gt;tt
op_logical_and
id|ht-&gt;signo
suffix:semicolon
id|ht
op_increment
)paren
r_if
c_cond
(paren
id|ht-&gt;tt
op_eq
id|tt
)paren
r_return
id|ht-&gt;signo
suffix:semicolon
r_return
id|SIGHUP
suffix:semicolon
multiline_comment|/* default for things we don&squot;t know about */
)brace
multiline_comment|/*&n; * While we find nice hex chars, build an int.&n; * Return number of chars processed.&n; */
r_static
r_int
DECL|function|hexToInt
id|hexToInt
c_func
(paren
r_char
op_star
op_star
id|ptr
comma
r_int
op_star
id|intValue
)paren
(brace
r_int
id|numChars
op_assign
l_int|0
suffix:semicolon
r_int
id|hexValue
suffix:semicolon
op_star
id|intValue
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
op_star
id|ptr
)paren
(brace
id|hexValue
op_assign
id|hex
c_func
(paren
op_star
op_star
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hexValue
OL
l_int|0
)paren
r_break
suffix:semicolon
op_star
id|intValue
op_assign
(paren
op_star
id|intValue
op_lshift
l_int|4
)paren
op_or
id|hexValue
suffix:semicolon
id|numChars
op_increment
suffix:semicolon
(paren
op_star
id|ptr
)paren
op_increment
suffix:semicolon
)brace
r_return
(paren
id|numChars
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function does all command processing for interfacing to gdb.  It&n; * returns 1 if you should skip the instruction at the trap address, 0&n; * otherwise.&n; */
r_extern
r_void
id|breakinst
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|handle_exception
id|handle_exception
(paren
r_int
r_int
op_star
id|registers
)paren
(brace
r_int
id|tt
suffix:semicolon
multiline_comment|/* Trap type */
r_int
id|sigval
suffix:semicolon
r_int
id|addr
suffix:semicolon
r_int
id|length
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_int
r_int
op_star
id|sp
suffix:semicolon
multiline_comment|/* First, we must force all of the windows to be spilled out */
id|asm
c_func
(paren
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;save %sp, -64, %sp&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|registers
(braket
id|PC
)braket
op_eq
(paren
r_int
r_int
)paren
id|breakinst
)paren
(brace
multiline_comment|/* Skip over breakpoint trap insn */
id|registers
(braket
id|PC
)braket
op_assign
id|registers
(braket
id|NPC
)braket
suffix:semicolon
id|registers
(braket
id|NPC
)braket
op_add_assign
l_int|4
suffix:semicolon
)brace
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|registers
(braket
id|SP
)braket
suffix:semicolon
id|tt
op_assign
(paren
id|registers
(braket
id|TBR
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* reply to host that an exception has occurred */
id|sigval
op_assign
id|computeSignal
c_func
(paren
id|tt
)paren
suffix:semicolon
id|ptr
op_assign
id|remcomOutBuffer
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;T&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|PC
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|PC
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|registers
(braket
id|PC
)braket
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|FP
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|FP
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|sp
op_plus
l_int|8
op_plus
l_int|6
)paren
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* FP */
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|SP
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|SP
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|sp
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|NPC
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|NPC
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|registers
(braket
id|NPC
)braket
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|O7
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|O7
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|registers
(braket
id|O7
)braket
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_int|0
suffix:semicolon
id|putpacket
c_func
(paren
id|remcomOutBuffer
)paren
suffix:semicolon
multiline_comment|/* XXX We may want to add some features dealing with poking the&n;&t; * XXX page tables, the real ones on the srmmu, and what is currently&n;&t; * XXX loaded in the sun4/sun4c tlb at this point in time.  But this&n;&t; * XXX also required hacking to the gdb sources directly...&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|remcomOutBuffer
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|getpacket
c_func
(paren
id|remcomInBuffer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|remcomInBuffer
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;?&squot;
suffix:colon
id|remcomOutBuffer
(braket
l_int|0
)braket
op_assign
l_char|&squot;S&squot;
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|1
)braket
op_assign
id|hexchars
(braket
id|sigval
op_rshift
l_int|4
)braket
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|2
)braket
op_assign
id|hexchars
(braket
id|sigval
op_amp
l_int|0xf
)braket
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
multiline_comment|/* toggle debug flag */
r_break
suffix:semicolon
r_case
l_char|&squot;g&squot;
suffix:colon
multiline_comment|/* return the value of the CPU registers */
(brace
id|ptr
op_assign
id|remcomOutBuffer
suffix:semicolon
multiline_comment|/* G &amp; O regs */
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
id|registers
comma
id|ptr
comma
l_int|16
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* L &amp; I regs */
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|sp
op_plus
l_int|0
)paren
comma
id|ptr
comma
l_int|16
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Floating point */
id|memset
c_func
(paren
id|ptr
comma
l_char|&squot;0&squot;
comma
l_int|32
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Y, PSR, WIM, TBR, PC, NPC, FPSR, CPSR */
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|registers
(braket
id|Y
)braket
comma
(paren
id|ptr
op_plus
l_int|32
op_star
l_int|4
op_star
l_int|2
)paren
comma
(paren
l_int|8
op_star
l_int|4
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;G&squot;
suffix:colon
multiline_comment|/* set the value of the CPU registers - return OK */
(brace
r_int
r_int
op_star
id|newsp
comma
id|psr
suffix:semicolon
id|psr
op_assign
id|registers
(braket
id|PSR
)braket
suffix:semicolon
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* G &amp; O regs */
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
id|registers
comma
l_int|16
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* L &amp; I regs */
id|hex2mem
c_func
(paren
id|ptr
op_plus
l_int|16
op_star
l_int|4
op_star
l_int|2
comma
(paren
r_char
op_star
)paren
(paren
id|sp
op_plus
l_int|0
)paren
comma
l_int|16
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Y, PSR, WIM, TBR, PC, NPC, FPSR, CPSR */
id|hex2mem
c_func
(paren
id|ptr
op_plus
l_int|64
op_star
l_int|4
op_star
l_int|2
comma
(paren
r_char
op_star
)paren
op_amp
id|registers
(braket
id|Y
)braket
comma
l_int|8
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* See if the stack pointer has moved.  If so,&n;&t;&t;&t; * then copy the saved locals and ins to the&n;&t;&t;&t; * new location.  This keeps the window&n;&t;&t;&t; * overflow and underflow routines happy.&n;&t;&t;&t; */
id|newsp
op_assign
(paren
r_int
r_int
op_star
)paren
id|registers
(braket
id|SP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_ne
id|newsp
)paren
id|sp
op_assign
id|memcpy
c_func
(paren
id|newsp
comma
id|sp
comma
l_int|16
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t allow CWP to be modified. */
r_if
c_cond
(paren
id|psr
op_ne
id|registers
(braket
id|PSR
)braket
)paren
id|registers
(braket
id|PSR
)braket
op_assign
(paren
id|psr
op_amp
l_int|0x1f
)paren
op_or
(paren
id|registers
(braket
id|PSR
)braket
op_amp
op_complement
l_int|0x1f
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;OK&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
multiline_comment|/* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
multiline_comment|/* Try to read %x,%x.  */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;,&squot;
op_logical_and
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|length
)paren
)paren
(brace
r_if
c_cond
(paren
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
id|addr
comma
id|remcomOutBuffer
comma
id|length
)paren
)paren
r_break
suffix:semicolon
id|strcpy
(paren
id|remcomOutBuffer
comma
l_string|&quot;E03&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E01&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;M&squot;
suffix:colon
multiline_comment|/* MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK */
multiline_comment|/* Try to read &squot;%x,%x:&squot;.  */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;,&squot;
op_logical_and
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|length
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
id|addr
comma
id|length
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;OK&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E03&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E02&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* cAA..AA    Continue at address AA..AA(optional) */
multiline_comment|/* try to read optional parameter, pc unchanged if no parm */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
)paren
(brace
id|registers
(braket
id|PC
)braket
op_assign
id|addr
suffix:semicolon
id|registers
(braket
id|NPC
)braket
op_assign
id|addr
op_plus
l_int|4
suffix:semicolon
)brace
multiline_comment|/* Need to flush the instruction cache here, as we may have deposited a&n; * breakpoint, and the icache probably has no way of knowing that a data ref to&n; * some location may have changed something that is in the instruction cache.&n; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* kill the program */
r_case
l_char|&squot;k&squot;
suffix:colon
multiline_comment|/* do nothing */
r_break
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
multiline_comment|/* Reset */
id|asm
(paren
l_string|&quot;call 0&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch */
multiline_comment|/* reply to the request */
id|putpacket
c_func
(paren
id|remcomOutBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/* while(1) */
)brace
multiline_comment|/* This function will generate a breakpoint exception.  It is used at the&n;   beginning of a program to sync up with a debugger and can be used&n;   otherwise as a quick means to stop program execution and &quot;break&quot; into&n;   the debugger. */
r_void
DECL|function|breakpoint
id|breakpoint
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
r_return
suffix:semicolon
multiline_comment|/* Again, watch those c-prefixes for ELF kernels */
macro_line|#if defined(__svr4__) || defined(__ELF__)
id|asm
c_func
(paren
"&quot;"
dot
id|globl
id|breakinst
id|breakinst
suffix:colon
id|ta
l_int|1
"&quot;"
)paren
suffix:semicolon
macro_line|#else
id|asm
c_func
(paren
"&quot;"
dot
id|globl
id|_breakinst
id|_breakinst
suffix:colon
id|ta
l_int|1
"&quot;"
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
