multiline_comment|/*&n; * include/asm-mips/string.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1994, 1995, 1996 by Ralf Baechle&n; *&n; * For now io.c contains only the definition of isa_slot_offset.  The&n; * real io.S doesn&squot;t assemble due to a GAS bug.&n; */
multiline_comment|/*&n; * port_base is the begin of the address space to which x86 style&n; * I/O ports are mapped.&n; */
DECL|variable|port_base
r_int
r_int
id|port_base
suffix:semicolon
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is is mapped&n; * for the processor.&n; */
DECL|variable|isa_slot_offset
r_int
r_int
id|isa_slot_offset
suffix:semicolon
eof
