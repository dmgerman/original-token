multiline_comment|/*&n; * arch/arm/mm/mm-rpc.c&n; *&n; * Extra MM routines for RiscPC architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
macro_line|#include &lt;asm/arch/mm-init.h&gt;
DECL|macro|NR_DRAM_BANKS
mdefine_line|#define NR_DRAM_BANKS&t;4
DECL|macro|NR_VRAM_BANKS
mdefine_line|#define NR_VRAM_BANKS&t;1
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS&t;(NR_DRAM_BANKS + NR_VRAM_BANKS)
DECL|macro|FIRST_BANK
mdefine_line|#define FIRST_BANK&t;0
DECL|macro|FIRST_DRAM_BANK
mdefine_line|#define FIRST_DRAM_BANK&t;0
DECL|macro|FIRST_VRAM_BANK
mdefine_line|#define FIRST_VRAM_BANK&t;NR_DRAM_BANKS
DECL|macro|BANK_SHIFT
mdefine_line|#define BANK_SHIFT&t;26
DECL|macro|FIRST_DRAM_ADDR
mdefine_line|#define FIRST_DRAM_ADDR&t;0x10000000
DECL|macro|PHYS_TO_BANK
mdefine_line|#define PHYS_TO_BANK(x)&t;(((x) &gt;&gt; BANK_SHIFT) &amp; (NR_DRAM_BANKS - 1))
DECL|macro|BANK_TO_PHYS
mdefine_line|#define BANK_TO_PHYS(x)&t;((FIRST_DRAM_ADDR) + &bslash;&n;&t;&t;&t;    (((x) - FIRST_DRAM_BANK) &lt;&lt; BANK_SHIFT))
DECL|struct|ram_bank
r_struct
id|ram_bank
(brace
DECL|member|virt_addr
r_int
r_int
id|virt_addr
suffix:semicolon
multiline_comment|/* virtual address of the *end* of this bank + 1 */
DECL|member|phys_offset
r_int
r_int
id|phys_offset
suffix:semicolon
multiline_comment|/* offset to physical address of this bank */
)brace
suffix:semicolon
DECL|variable|rambank
r_static
r_struct
id|ram_bank
id|rambank
(braket
id|NR_BANKS
)braket
suffix:semicolon
multiline_comment|/*&n; * Return the physical (0x10000000 -&gt; 0x20000000) address of&n; * the virtual (0xc0000000 -&gt; 0xd0000000) address&n; */
DECL|function|__virt_to_phys
r_int
r_int
id|__virt_to_phys
c_func
(paren
r_int
r_int
id|vpage
)paren
(brace
r_int
r_int
id|bank
op_assign
id|FIRST_BANK
suffix:semicolon
r_while
c_loop
(paren
id|vpage
op_ge
id|rambank
(braket
id|bank
)braket
dot
id|virt_addr
op_logical_and
id|bank
OL
id|NR_BANKS
)paren
id|bank
op_increment
suffix:semicolon
r_return
id|vpage
op_minus
id|rambank
(braket
id|bank
)braket
dot
id|phys_offset
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the virtual (0xc0000000 -&gt; 0xd0000000) address of&n; * the physical (0x10000000 -&gt; 0x20000000) address&n; */
DECL|function|__phys_to_virt
r_int
r_int
id|__phys_to_virt
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|bank
suffix:semicolon
r_if
c_cond
(paren
id|phys
OG
id|FIRST_DRAM_ADDR
)paren
id|bank
op_assign
id|PHYS_TO_BANK
c_func
(paren
id|phys
)paren
suffix:semicolon
r_else
id|bank
op_assign
id|FIRST_VRAM_BANK
suffix:semicolon
r_return
id|phys
op_plus
id|rambank
(braket
id|bank
)braket
dot
id|phys_offset
suffix:semicolon
)brace
DECL|function|init_dram_banks
r_void
id|init_dram_banks
c_func
(paren
r_struct
id|param_struct
op_star
id|params
)paren
(brace
r_int
r_int
id|bank
suffix:semicolon
r_int
r_int
id|bytes
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bank
op_assign
id|FIRST_DRAM_BANK
suffix:semicolon
id|bank
OL
id|NR_DRAM_BANKS
suffix:semicolon
id|bank
op_increment
)paren
(brace
id|rambank
(braket
id|bank
)braket
dot
id|phys_offset
op_assign
id|PAGE_OFFSET
op_plus
id|bytes
op_minus
id|BANK_TO_PHYS
c_func
(paren
id|bank
)paren
suffix:semicolon
id|bytes
op_add_assign
id|params-&gt;u1.s.pages_in_bank
(braket
id|bank
op_minus
id|FIRST_DRAM_BANK
)braket
op_star
id|PAGE_SIZE
suffix:semicolon
id|rambank
(braket
id|bank
)braket
dot
id|virt_addr
op_assign
id|PAGE_OFFSET
op_plus
id|bytes
suffix:semicolon
)brace
id|rambank
(braket
id|FIRST_VRAM_BANK
)braket
dot
id|phys_offset
op_assign
l_int|0xd6000000
suffix:semicolon
id|rambank
(braket
id|FIRST_VRAM_BANK
)braket
dot
id|virt_addr
op_assign
l_int|0xd8000000
suffix:semicolon
id|current-&gt;tss.memmap
op_assign
id|__virt_to_phys
c_func
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
)paren
suffix:semicolon
)brace
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n;&t;{ SCREEN2_BASE,&t;SCREEN_START,&t;2*1048576, DOMAIN_IO, 0, 1 },&t;/* VRAM&t;&t;*/ &bslash;&n;&t;{ IO_BASE,&t;IO_START,&t;IO_SIZE&t; , DOMAIN_IO, 0, 1 }&t;/* IO space&t;*/
multiline_comment|/*&n; * Include common routine to set up page tables&n; */
macro_line|#include &quot;mm-armv.c&quot;
eof
