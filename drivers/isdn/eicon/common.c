multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * This source file is supplied for the exclusive use with Eicon&n; * Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n; * Eicon File Revision :    1.15  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &quot;sys.h&quot;
macro_line|#include &quot;idi.h&quot;
macro_line|#include &quot;constant.h&quot;
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;pc.h&quot;
macro_line|#include &quot;pr_pc.h&quot;
macro_line|#include &quot;uxio.h&quot;
macro_line|#include &lt;sys/types.h&gt;
DECL|macro|MAX_ADDR_LEN
mdefine_line|#define MAX_ADDR_LEN
DECL|macro|DIVAS_LOAD_CMD
mdefine_line|#define DIVAS_LOAD_CMD&t;&t;0x02
DECL|macro|DIVAS_START_CMD
mdefine_line|#define DIVAS_START_CMD&t;&t;0x03
DECL|macro|DIVAS_IRQ_RESET
mdefine_line|#define DIVAS_IRQ_RESET&t;&t;0xC18
DECL|macro|DIVAS_IRQ_RESET_VAL
mdefine_line|#define DIVAS_IRQ_RESET_VAL&t;0xFE
DECL|macro|PCI_COMMAND
mdefine_line|#define&t;PCI_COMMAND&t;0x04
DECL|macro|PCI_STATUS
mdefine_line|#define&t;PCI_STATUS&t;0x06
DECL|macro|PCI_LATENCY
mdefine_line|#define&t;PCI_LATENCY&t;0x0D
DECL|macro|PCI_INTERRUPT
mdefine_line|#define PCI_INTERRUPT&t;0x3C
DECL|macro|TEST_INT_DIVAS
mdefine_line|#define TEST_INT_DIVAS&t;&t;0x11
DECL|macro|TEST_INT_DIVAS_BRI
mdefine_line|#define TEST_INT_DIVAS_BRI&t;0x12
DECL|macro|TEST_INT_DIVAS_Q
mdefine_line|#define TEST_INT_DIVAS_Q&t;0x13
DECL|macro|DIVAS_RESET
mdefine_line|#define DIVAS_RESET&t;0x81
DECL|macro|DIVAS_LED1
mdefine_line|#define DIVAS_LED1&t;0x04
DECL|macro|DIVAS_LED2
mdefine_line|#define DIVAS_LED2&t;0x08
DECL|macro|DIVAS_LED3
mdefine_line|#define DIVAS_LED3&t;0x20
DECL|macro|DIVAS_LED4
mdefine_line|#define DIVAS_LED4&t;0x40
DECL|macro|DIVAS_SIGNATURE
mdefine_line|#define DIVAS_SIGNATURE 0x4447
DECL|macro|MP_PROTOCOL_ADDR
mdefine_line|#define MP_PROTOCOL_ADDR 0xA0011000
DECL|macro|PLX_IOBASE
mdefine_line|#define PLX_IOBASE&t;0
DECL|macro|DIVAS_IOBASE
mdefine_line|#define&t;DIVAS_IOBASE&t;1
r_typedef
r_struct
(brace
DECL|member|cmd
id|dword
id|cmd
suffix:semicolon
DECL|member|addr
id|dword
id|addr
suffix:semicolon
DECL|member|len
id|dword
id|len
suffix:semicolon
DECL|member|err
id|dword
id|err
suffix:semicolon
DECL|member|live
id|dword
id|live
suffix:semicolon
DECL|member|reserved
id|dword
id|reserved
(braket
(paren
l_int|0x1020
op_rshift
l_int|2
)paren
op_minus
l_int|6
)braket
suffix:semicolon
DECL|member|signature
id|dword
id|signature
suffix:semicolon
DECL|member|data
id|byte
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|diva_server_boot_t
)brace
id|diva_server_boot_t
suffix:semicolon
DECL|variable|DivasCardNext
r_int
id|DivasCardNext
suffix:semicolon
DECL|variable|DivasCards
id|card_t
id|DivasCards
(braket
id|MAX_CARDS
)braket
suffix:semicolon
id|dia_config_t
op_star
id|DivasConfig
c_func
(paren
id|card_t
op_star
comma
id|dia_config_t
op_star
)paren
suffix:semicolon
r_static
DECL|variable|DIDD_Table
id|DESCRIPTOR
id|DIDD_Table
(braket
l_int|32
)braket
suffix:semicolon
DECL|function|DIVA_DIDD_Read
r_void
id|DIVA_DIDD_Read
c_func
(paren
id|DESCRIPTOR
op_star
id|table
comma
r_int
id|tablelength
)paren
(brace
id|bzero
c_func
(paren
id|table
comma
id|tablelength
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tablelength
OG
r_sizeof
(paren
id|DIDD_Table
)paren
)paren
id|tablelength
op_assign
r_sizeof
(paren
id|DIDD_Table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tablelength
op_mod
r_sizeof
(paren
id|DESCRIPTOR
)paren
)paren
(brace
id|tablelength
op_div_assign
r_sizeof
(paren
id|DESCRIPTOR
)paren
suffix:semicolon
id|tablelength
op_mul_assign
r_sizeof
(paren
id|DESCRIPTOR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tablelength
OG
l_int|0
)paren
id|bcopy
c_func
(paren
(paren
id|caddr_t
)paren
id|DIDD_Table
comma
(paren
id|caddr_t
)paren
id|table
comma
id|tablelength
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
DECL|function|DIVA_DIDD_Write
r_void
id|DIVA_DIDD_Write
c_func
(paren
id|DESCRIPTOR
op_star
id|table
comma
r_int
id|tablelength
)paren
(brace
r_if
c_cond
(paren
id|tablelength
OG
r_sizeof
(paren
id|DIDD_Table
)paren
)paren
id|tablelength
op_assign
r_sizeof
(paren
id|DIDD_Table
)paren
suffix:semicolon
id|bcopy
c_func
(paren
(paren
id|caddr_t
)paren
id|table
comma
(paren
id|caddr_t
)paren
id|DIDD_Table
comma
id|tablelength
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
DECL|function|init_idi_tab
r_void
id|init_idi_tab
c_func
(paren
r_void
)paren
(brace
id|DESCRIPTOR
id|d
(braket
l_int|32
)braket
suffix:semicolon
id|bzero
c_func
(paren
id|d
comma
r_sizeof
(paren
id|d
)paren
)paren
suffix:semicolon
id|d
(braket
l_int|0
)braket
dot
id|type
op_assign
id|IDI_DIMAINT
suffix:semicolon
multiline_comment|/* identify the DIMAINT entry */
id|d
(braket
l_int|0
)braket
dot
id|channels
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* zero channels associated with dimaint*/
id|d
(braket
l_int|0
)braket
dot
id|features
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no features associated with dimaint */
id|d
(braket
l_int|0
)braket
dot
id|request
op_assign
(paren
id|IDI_CALL
)paren
id|DivasPrintf
suffix:semicolon
id|DIVA_DIDD_Write
c_func
(paren
id|d
comma
r_sizeof
(paren
id|d
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O routines for memory mapped cards&n; */
DECL|function|mem_in
id|byte
id|mem_in
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|byte
id|value
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|value
op_assign
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
id|m
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|mem_inw
id|word
id|mem_inw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|word
id|value
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|value
op_assign
id|UxCardMemInW
c_func
(paren
id|card-&gt;hw
comma
id|m
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|mem_in_buffer
r_void
id|mem_in_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|UxCardMemInBuffer
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|P
comma
id|length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mem_look_ahead
r_void
id|mem_look_ahead
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|PBUFFER
op_star
id|RBuffer
comma
id|ENTITY
op_star
id|e
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
id|dword
)paren
op_amp
id|RBuffer-&gt;length
suffix:semicolon
id|card-&gt;RBuffer.length
op_assign
id|UxCardMemInW
c_func
(paren
id|card-&gt;hw
comma
id|m
)paren
suffix:semicolon
id|m
op_assign
id|b
suffix:semicolon
id|m
op_add_assign
(paren
id|dword
)paren
op_amp
id|RBuffer-&gt;P
suffix:semicolon
id|UxCardMemInBuffer
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|card-&gt;RBuffer.P
comma
id|card-&gt;RBuffer.length
)paren
suffix:semicolon
id|e-&gt;RBuffer
op_assign
(paren
id|DBUFFER
op_star
)paren
op_amp
id|card-&gt;RBuffer
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mem_out
r_void
id|mem_out
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|byte
id|data
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|data
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mem_outw
r_void
id|mem_outw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|word
id|data
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|UxCardMemOutW
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|data
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mem_out_buffer
r_void
id|mem_out_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|UxCardMemOutBuffer
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|P
comma
id|length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mem_inc
r_void
id|mem_inc
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|word
id|value
suffix:semicolon
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
r_int
r_char
op_star
id|b
comma
op_star
id|m
suffix:semicolon
id|m
op_assign
id|b
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|m
op_add_assign
(paren
r_int
r_int
)paren
id|adr
suffix:semicolon
id|value
op_assign
id|UxCardMemInW
c_func
(paren
id|card-&gt;hw
comma
id|m
)paren
suffix:semicolon
id|value
op_increment
suffix:semicolon
id|UxCardMemOutW
c_func
(paren
id|card-&gt;hw
comma
id|m
comma
id|value
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|b
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O routines for I/O mapped cards&n; */
DECL|function|io_in
id|byte
id|io_in
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
id|value
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|value
op_assign
id|UxCardIoIn
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|io_inw
id|word
id|io_inw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|word
id|value
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|value
op_assign
id|UxCardIoInW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|io_in_buffer
r_void
id|io_in_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|UxCardIoInBuffer
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
comma
id|P
comma
id|length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|io_look_ahead
r_void
id|io_look_ahead
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|PBUFFER
op_star
id|RBuffer
comma
id|ENTITY
op_star
id|e
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|card-&gt;RBuffer.length
op_assign
id|UxCardIoInW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
(paren
id|byte
op_star
)paren
id|RBuffer
)paren
suffix:semicolon
id|UxCardIoInBuffer
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
op_amp
id|RBuffer-&gt;P
comma
id|card-&gt;RBuffer.P
comma
id|card-&gt;RBuffer.length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
id|e-&gt;RBuffer
op_assign
(paren
id|DBUFFER
op_star
)paren
op_amp
id|card-&gt;RBuffer
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|io_out
r_void
id|io_out
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|byte
id|data
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|UxCardIoOut
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
comma
id|data
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|io_outw
r_void
id|io_outw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|word
id|data
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|UxCardIoOutW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
comma
id|data
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|io_out_buffer
r_void
id|io_out_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
op_assign
l_int|NULL
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|UxCardIoOutBuffer
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
comma
id|P
comma
id|length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|io_inc
r_void
id|io_inc
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
(brace
id|word
id|value
suffix:semicolon
id|card_t
op_star
id|card
op_assign
id|a-&gt;io
suffix:semicolon
id|byte
op_star
id|DivasIOBase
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|value
op_assign
id|UxCardIoInW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
)paren
suffix:semicolon
id|value
op_increment
suffix:semicolon
id|UxCardIoOutW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
id|adr
comma
id|value
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
DECL|function|test_int
r_void
id|test_int
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
id|byte
op_star
id|shared
comma
op_star
id|DivasIOBase
suffix:semicolon
r_switch
c_cond
(paren
id|card-&gt;test_int_pend
)paren
(brace
r_case
id|TEST_INT_DIVAS
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: test interrupt pending&quot;
)paren
)paren
suffix:semicolon
id|shared
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|0x3FE
)braket
)paren
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
(paren
(paren
(paren
r_struct
id|pr_ram
op_star
)paren
id|shared
)paren
op_member_access_from_pointer
id|RcOutput
)paren
comma
l_int|0
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|shared
)paren
suffix:semicolon
(paren
op_star
id|card-&gt;reset_int
)paren
(paren
id|card
)paren
suffix:semicolon
id|shared
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|0x3FE
)braket
comma
l_int|0
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: test interrupt cleared&quot;
)paren
)paren
suffix:semicolon
)brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|shared
)paren
suffix:semicolon
id|card-&gt;test_int_pend
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TEST_INT_DIVAS_BRI
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: BRI test interrupt pending&quot;
)paren
)paren
suffix:semicolon
(paren
op_star
id|card-&gt;reset_int
)paren
(paren
id|card
)paren
suffix:semicolon
id|DivasIOBase
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_IOBASE
)paren
suffix:semicolon
id|UxCardIoOutW
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
comma
(paren
r_void
op_star
)paren
l_int|0x3FE
comma
l_int|0
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|DivasIOBase
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: test interrupt cleared&quot;
)paren
)paren
suffix:semicolon
id|card-&gt;test_int_pend
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TEST_INT_DIVAS_Q
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: 4BRI test interrupt pending&quot;
)paren
)paren
suffix:semicolon
(paren
op_star
id|card-&gt;reset_int
)paren
(paren
id|card
)paren
suffix:semicolon
id|card-&gt;test_int_pend
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: unknown test interrupt pending&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|card_isr
r_void
id|card_isr
(paren
r_void
op_star
id|dev_id
)paren
(brace
id|card_t
op_star
id|card
op_assign
(paren
id|card_t
op_star
)paren
id|dev_id
suffix:semicolon
id|ADAPTER
op_star
id|a
op_assign
op_amp
id|card-&gt;a
suffix:semicolon
r_int
id|ipl
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;test_int_pend
)paren
(brace
id|ipl
op_assign
id|UxCardLock
c_func
(paren
id|card-&gt;hw
)paren
suffix:semicolon
id|card-&gt;int_pend
op_assign
l_int|0
suffix:semicolon
id|test_int
c_func
(paren
id|card
)paren
suffix:semicolon
id|UxCardUnlock
c_func
(paren
id|card-&gt;hw
comma
id|ipl
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;card_isr
)paren
(brace
(paren
op_star
(paren
id|card-&gt;card_isr
)paren
)paren
(paren
id|card
)paren
suffix:semicolon
)brace
r_else
(brace
id|ipl
op_assign
id|UxCardLock
c_func
(paren
id|card-&gt;hw
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|card-&gt;test_int
)paren
(paren
id|a
)paren
)paren
(brace
(paren
id|card-&gt;reset_int
)paren
(paren
id|card
)paren
suffix:semicolon
)brace
id|UxCardUnlock
c_func
(paren
id|card-&gt;hw
comma
id|ipl
)paren
suffix:semicolon
)brace
)brace
DECL|function|DivasCardNew
r_int
id|DivasCardNew
c_func
(paren
id|dia_card_t
op_star
id|card_info
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
id|byte
id|b
suffix:semicolon
r_static
id|boolean_t
id|first_call
op_assign
id|TRUE
suffix:semicolon
id|boolean_t
id|NeedISRandReset
op_assign
id|FALSE
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: new card &quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_call
)paren
(brace
id|first_call
op_assign
id|FALSE
suffix:semicolon
id|init_idi_tab
c_func
(paren
)paren
suffix:semicolon
)brace
id|DivasConfigGet
c_func
(paren
id|card_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DivasCardNext
op_eq
id|DIM
c_func
(paren
id|DivasCards
)paren
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: no space available for new card&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|card
op_assign
op_amp
id|DivasCards
(braket
id|DivasCardNext
)braket
suffix:semicolon
id|card-&gt;state
op_assign
id|DIA_UNKNOWN
suffix:semicolon
id|card-&gt;cfg
op_assign
op_star
id|card_info
suffix:semicolon
id|card-&gt;a.io
op_assign
id|card
suffix:semicolon
r_if
c_cond
(paren
id|UxCardHandleGet
c_func
(paren
op_amp
id|card-&gt;hw
comma
id|card_info
)paren
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: cannot get OS specific handle for card&quot;
)paren
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
id|card_info-&gt;card_type
op_eq
id|DIA_CARD_TYPE_DIVA_SERVER_B
)paren
(brace
id|DivasBriPatch
c_func
(paren
id|card
)paren
suffix:semicolon
id|card_info-&gt;io_base
op_assign
id|card-&gt;cfg.io_base
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|card_info-&gt;card_type
)paren
(brace
r_case
id|DIA_CARD_TYPE_DIVA_SERVER
suffix:colon
r_if
c_cond
(paren
id|DivasPriInit
c_func
(paren
id|card
comma
id|card_info
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|NeedISRandReset
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_B
suffix:colon
r_if
c_cond
(paren
id|DivasBriInit
c_func
(paren
id|card
comma
id|card_info
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|NeedISRandReset
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_Q
suffix:colon
r_if
c_cond
(paren
id|Divas4BriInit
c_func
(paren
id|card
comma
id|card_info
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card_info-&gt;name
(braket
l_int|6
)braket
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|NeedISRandReset
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
singleline_comment|// Need to set paramater for ISR anyway
(brace
id|card-&gt;hw-&gt;user_isr_arg
op_assign
id|card
suffix:semicolon
id|card-&gt;hw-&gt;user_isr
op_assign
id|card_isr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: unsupported card type (%d)&quot;
comma
id|card_info-&gt;card_type
)paren
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
id|NeedISRandReset
)paren
(brace
r_if
c_cond
(paren
id|UxIsrInstall
c_func
(paren
id|card-&gt;hw
comma
id|card_isr
comma
id|card
)paren
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: Install ISR failed (IRQ %d)&quot;
comma
id|card-&gt;cfg.irq
)paren
)paren
suffix:semicolon
id|UxCardHandleFree
c_func
(paren
id|card-&gt;hw
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|b
op_assign
id|card-&gt;cfg.irq
suffix:semicolon
id|UxPciConfigWrite
c_func
(paren
id|card-&gt;hw
comma
r_sizeof
(paren
id|b
)paren
comma
id|PCI_INTERRUPT
comma
op_amp
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_info-&gt;card_type
op_ne
id|DIA_CARD_TYPE_DIVA_SERVER_Q
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|card-&gt;card_reset
)paren
(paren
id|card
)paren
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: Adapter reset failed&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|card-&gt;state
op_assign
id|DIA_RESET
suffix:semicolon
)brace
id|NeedISRandReset
op_assign
id|FALSE
suffix:semicolon
)brace
id|DivasCardNext
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_card
r_void
op_star
id|get_card
c_func
(paren
r_int
id|card_id
)paren
(brace
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
id|DivasCardNext
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|DivasCards
(braket
id|i
)braket
dot
id|cfg.card_id
op_eq
id|card_id
)paren
(brace
r_return
op_amp
id|DivasCards
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: get_card() : no such card id (%d)&quot;
comma
id|card_id
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|DivasCardConfig
r_int
id|DivasCardConfig
c_func
(paren
id|dia_config_t
op_star
id|config
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
r_int
id|status
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: configuring card&quot;
)paren
)paren
suffix:semicolon
id|card
op_assign
id|get_card
c_func
(paren
id|config-&gt;card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|config
op_assign
id|DivasConfig
c_func
(paren
id|card
comma
id|config
)paren
suffix:semicolon
id|status
op_assign
(paren
op_star
id|card-&gt;card_config
)paren
(paren
id|card
comma
id|config
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|card-&gt;state
op_assign
id|DIA_CONFIGURED
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|DivasCardLoad
r_int
id|DivasCardLoad
c_func
(paren
id|dia_load_t
op_star
id|load
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
r_int
id|status
suffix:semicolon
id|card
op_assign
id|get_card
c_func
(paren
id|load-&gt;card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;state
op_eq
id|DIA_RUNNING
)paren
(brace
(paren
op_star
id|card-&gt;card_reset
)paren
(paren
id|card
)paren
suffix:semicolon
)brace
id|status
op_assign
(paren
op_star
id|card-&gt;card_load
)paren
(paren
id|card
comma
id|load
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|card-&gt;state
op_assign
id|DIA_LOADED
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|idi_register
r_static
r_int
id|idi_register
c_func
(paren
id|card_t
op_star
id|card
comma
id|byte
id|channels
)paren
(brace
id|DESCRIPTOR
id|d
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|length
comma
id|num_entities
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: registering card with IDI&quot;
)paren
)paren
suffix:semicolon
id|num_entities
op_assign
(paren
id|channels
OG
l_int|2
)paren
ques
c_cond
id|MAX_PENTITIES
suffix:colon
id|MAX_ENTITIES
suffix:semicolon
id|card-&gt;e_tbl
op_assign
id|UxAlloc
c_func
(paren
r_sizeof
(paren
id|E_INFO
)paren
op_star
id|num_entities
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;e_tbl
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: IDI register failed - no memory available&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|bzero
c_func
(paren
id|card-&gt;e_tbl
comma
r_sizeof
(paren
id|E_INFO
)paren
op_star
id|num_entities
)paren
suffix:semicolon
id|card-&gt;e_max
op_assign
id|num_entities
suffix:semicolon
id|DIVA_DIDD_Read
c_func
(paren
id|d
comma
r_sizeof
(paren
id|d
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|length
op_assign
l_int|0
suffix:semicolon
id|length
OL
id|DIM
c_func
(paren
id|d
)paren
suffix:semicolon
id|length
op_increment
)paren
r_if
c_cond
(paren
id|d
(braket
id|length
)braket
dot
id|type
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
id|DIM
c_func
(paren
id|d
)paren
)paren
(brace
id|KDPRINTF
c_func
(paren
(paren
id|KERN_WARNING
l_string|&quot;Divas: IDI register failed - table full&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|card-&gt;cfg.card_type
)paren
(brace
r_case
id|DIA_CARD_TYPE_DIVA_SERVER
suffix:colon
id|d
(braket
id|length
)braket
dot
id|type
op_assign
id|IDI_ADAPTER_PR
suffix:semicolon
multiline_comment|/* d[length].serial = card-&gt;serial_no; */
r_break
suffix:semicolon
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_B
suffix:colon
id|d
(braket
id|length
)braket
dot
id|type
op_assign
id|IDI_ADAPTER_MAESTRA
suffix:semicolon
multiline_comment|/* d[length].serial = card-&gt;serial_no; */
r_break
suffix:semicolon
singleline_comment|// 4BRI is treated as 4 BRI adapters
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_Q
suffix:colon
id|d
(braket
id|length
)braket
dot
id|type
op_assign
id|IDI_ADAPTER_MAESTRA
suffix:semicolon
multiline_comment|/* d[length].serial = card-&gt;cfg.serial; */
)brace
id|d
(braket
id|length
)braket
dot
id|features
op_assign
l_int|0
suffix:semicolon
id|d
(braket
id|length
)braket
dot
id|features
op_or_assign
id|DI_FAX3
op_or
id|DI_MODEM
op_or
id|DI_POST
op_or
id|DI_V110
op_or
id|DI_V120
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;hw-&gt;features
op_amp
id|PROTCAP_MANIF
)paren
(brace
id|d
(braket
id|length
)braket
dot
id|features
op_or_assign
id|DI_MANAGE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;hw-&gt;features
op_amp
id|PROTCAP_V_42
)paren
(brace
id|d
(braket
id|length
)braket
dot
id|features
op_or_assign
id|DI_V_42
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;hw-&gt;features
op_amp
id|PROTCAP_EXTD_FAX
)paren
(brace
id|d
(braket
id|length
)braket
dot
id|features
op_or_assign
id|DI_EXTD_FAX
suffix:semicolon
)brace
id|d
(braket
id|length
)braket
dot
id|channels
op_assign
id|channels
suffix:semicolon
id|d
(braket
id|length
)braket
dot
id|request
op_assign
id|DivasIdiRequest
(braket
id|card
op_minus
id|DivasCards
)braket
suffix:semicolon
id|length
op_increment
suffix:semicolon
id|DIVA_DIDD_Write
c_func
(paren
id|d
comma
r_sizeof
(paren
id|d
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DivasCardStart
r_int
id|DivasCardStart
c_func
(paren
r_int
id|card_id
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
id|byte
id|channels
suffix:semicolon
r_int
id|status
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: starting card&quot;
)paren
)paren
suffix:semicolon
id|card
op_assign
id|get_card
c_func
(paren
id|card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|status
op_assign
(paren
op_star
id|card-&gt;card_start
)paren
(paren
id|card
comma
op_amp
id|channels
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/* 4BRI == 4 x BRI so call idi_register 4 times each with 2 channels */
r_if
c_cond
(paren
id|card-&gt;cfg.card_type
op_eq
id|DIA_CARD_TYPE_DIVA_SERVER_Q
)paren
(brace
r_int
id|i
suffix:semicolon
id|card_t
op_star
id|FourBRISlave
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|FourBRISlave
op_assign
id|get_card
c_func
(paren
id|card_id
op_minus
id|i
)paren
suffix:semicolon
multiline_comment|/* 0, 1, 2, 3 */
r_if
c_cond
(paren
id|FourBRISlave
)paren
(brace
id|idi_register
c_func
(paren
id|FourBRISlave
comma
l_int|2
)paren
suffix:semicolon
id|FourBRISlave-&gt;state
op_assign
id|DIA_RUNNING
suffix:semicolon
)brace
)brace
id|card-&gt;serial_no
op_assign
id|card-&gt;cfg.serial
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: card id %d (4BRI), serial no. 0x%x ready with %d channels&quot;
comma
id|card_id
op_minus
l_int|3
comma
id|card-&gt;serial_no
comma
(paren
r_int
)paren
id|channels
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|idi_register
c_func
(paren
id|card
comma
id|channels
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|card-&gt;state
op_assign
id|DIA_RUNNING
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: card id %d, serial no. 0x%x ready with %d channels&quot;
comma
id|card_id
comma
id|card-&gt;serial_no
comma
(paren
r_int
)paren
id|channels
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|DivasGetMem
r_int
id|DivasGetMem
c_func
(paren
id|mem_block_t
op_star
id|mem_block
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
id|word
id|card_id
op_assign
id|mem_block-&gt;card_id
suffix:semicolon
id|card
op_assign
id|get_card
c_func
(paren
id|card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
op_star
id|card-&gt;card_mem_get
)paren
(paren
id|card
comma
id|mem_block
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Deleyed Procedure Call for handling interrupts from card&n; */
DECL|function|DivaDoCardDpc
r_void
id|DivaDoCardDpc
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
id|ADAPTER
op_star
id|a
suffix:semicolon
id|a
op_assign
op_amp
id|card-&gt;a
suffix:semicolon
r_if
c_cond
(paren
id|UxInterlockedIncrement
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|card-&gt;dpc_reentered
)paren
OG
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
(paren
op_star
(paren
id|card-&gt;test_int
)paren
)paren
(paren
id|a
)paren
)paren
(brace
(paren
op_star
(paren
id|card-&gt;dpc
)paren
)paren
(paren
id|a
)paren
suffix:semicolon
(paren
op_star
(paren
id|card-&gt;clear_int
)paren
)paren
(paren
id|a
)paren
suffix:semicolon
)brace
(paren
op_star
(paren
id|card-&gt;out
)paren
)paren
(paren
id|a
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|UxInterlockedDecrement
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|card-&gt;dpc_reentered
)paren
)paren
suffix:semicolon
)brace
DECL|function|DivasDoDpc
r_void
id|DivasDoDpc
c_func
(paren
r_void
op_star
id|pData
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|DivasCards
suffix:semicolon
r_int
id|i
op_assign
id|DivasCardNext
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|DivaDoCardDpc
c_func
(paren
id|card
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|DivasDoRequestDpc
r_void
id|DivasDoRequestDpc
c_func
(paren
r_void
op_star
id|pData
)paren
(brace
id|DivasDoDpc
c_func
(paren
id|pData
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * DivasGetNum&n; * Returns the number of active adapters&n; */
DECL|function|DivasGetNum
r_int
id|DivasGetNum
c_func
(paren
r_void
)paren
(brace
r_return
id|DivasCardNext
suffix:semicolon
)brace
multiline_comment|/*&n; * DivasGetList&n; * Returns a list of active adapters&n; */
DECL|function|DivasGetList
r_int
id|DivasGetList
c_func
(paren
id|dia_card_list_t
op_star
id|card_list
)paren
(brace
r_int
id|i
suffix:semicolon
id|bzero
c_func
(paren
id|card_list
comma
r_sizeof
(paren
id|dia_card_list_t
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
id|DivasCardNext
suffix:semicolon
id|i
op_increment
)paren
(brace
id|card_list-&gt;card_type
op_assign
id|DivasCards
(braket
id|i
)braket
dot
id|cfg.card_type
suffix:semicolon
id|card_list-&gt;card_slot
op_assign
id|DivasCards
(braket
id|i
)braket
dot
id|cfg.slot
suffix:semicolon
id|card_list-&gt;state
op_assign
id|DivasCards
(braket
id|i
)braket
dot
id|state
suffix:semicolon
id|card_list
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * control logging for specified card&n; */
DECL|function|DivasLog
r_void
id|DivasLog
c_func
(paren
id|dia_log_t
op_star
id|log
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
id|card
op_assign
id|get_card
c_func
(paren
id|log-&gt;card_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
r_return
suffix:semicolon
)brace
id|card-&gt;log_types
op_assign
id|log-&gt;log_types
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
