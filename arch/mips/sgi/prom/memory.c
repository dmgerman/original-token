multiline_comment|/* $Id: memory.c,v 1.1 1997/06/06 09:37:10 ralf Exp $&n; * memory.c: PROM library functions for acquiring/using memory descriptors&n; *           given to us from the ARCS firmware.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
multiline_comment|/* #define DEBUG */
DECL|function|prom_getmdesc
r_struct
id|linux_mdesc
op_star
id|prom_getmdesc
c_func
(paren
r_struct
id|linux_mdesc
op_star
id|curr
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|get_mdesc
c_func
(paren
id|curr
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG /* convenient for debugging */
DECL|variable|mtypes
r_static
r_char
op_star
id|mtypes
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;Exception Block&quot;
comma
l_string|&quot;ARCS Romvec Page&quot;
comma
l_string|&quot;Free/Contig RAM&quot;
comma
l_string|&quot;Generic Free RAM&quot;
comma
l_string|&quot;Bad Memory&quot;
comma
l_string|&quot;Standlong Program Pages&quot;
comma
l_string|&quot;ARCS Temp Storage Area&quot;
comma
l_string|&quot;ARCS Permanent Storage Area&quot;
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|prom_pblocks
r_static
r_struct
id|prom_pmemblock
id|prom_pblocks
(braket
id|PROM_MAX_PMEMBLOCKS
)braket
suffix:semicolon
DECL|function|prom_getpblock_array
r_struct
id|prom_pmemblock
op_star
id|prom_getpblock_array
c_func
(paren
r_void
)paren
(brace
r_return
op_amp
id|prom_pblocks
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|prom_setup_memupper
r_static
r_void
id|prom_setup_memupper
c_func
(paren
r_void
)paren
(brace
r_struct
id|prom_pmemblock
op_star
id|p
comma
op_star
id|highest
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|prom_getpblock_array
c_func
(paren
)paren
comma
id|highest
op_assign
l_int|0
suffix:semicolon
id|p-&gt;size
op_ne
l_int|0
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;base
op_eq
l_int|0xdeadbeef
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WHEEE, bogus pmemblock&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|highest
op_logical_or
id|p-&gt;base
OG
id|highest-&gt;base
)paren
(brace
id|highest
op_assign
id|p
suffix:semicolon
)brace
)brace
id|mips_memory_upper
op_assign
id|highest-&gt;base
op_plus
id|highest-&gt;size
suffix:semicolon
macro_line|#ifdef DEBUG
id|prom_printf
c_func
(paren
l_string|&quot;prom_setup_memupper: mips_memory_upper = %08lx&bslash;n&quot;
comma
id|mips_memory_upper
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|prom_meminit
r_void
id|prom_meminit
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_mdesc
op_star
id|p
suffix:semicolon
r_int
id|totram
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|prom_getmdesc
c_func
(paren
id|PROM_NULL_MDESC
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|prom_printf
c_func
(paren
l_string|&quot;ARCS MEMORY DESCRIPTOR dump:&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;[%d,%p]: base&lt;%08lx&gt; pages&lt;%08lx&gt; type&lt;%s&gt;&bslash;n&quot;
comma
id|i
comma
id|p
comma
id|p-&gt;base
comma
id|p-&gt;pages
comma
id|mtypes
(braket
id|p-&gt;type
)braket
)paren
suffix:semicolon
id|p
op_assign
id|prom_getmdesc
c_func
(paren
id|p
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
macro_line|#endif
id|p
op_assign
id|prom_getmdesc
c_func
(paren
id|PROM_NULL_MDESC
)paren
suffix:semicolon
id|totram
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;type
op_eq
id|free
op_logical_or
id|p-&gt;type
op_eq
id|fcontig
)paren
(brace
id|prom_pblocks
(braket
id|i
)braket
dot
id|base
op_assign
(paren
(paren
id|p-&gt;base
op_lshift
id|PAGE_SHIFT
)paren
op_plus
l_int|0x80000000
)paren
suffix:semicolon
id|prom_pblocks
(braket
id|i
)braket
dot
id|size
op_assign
id|p-&gt;pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|totram
op_add_assign
id|prom_pblocks
(braket
id|i
)braket
dot
id|size
suffix:semicolon
macro_line|#ifdef DEBUG
id|prom_printf
c_func
(paren
l_string|&quot;free_chunk[%d]: base=%08lx size=%d&bslash;n&quot;
comma
id|i
comma
id|prom_pblocks
(braket
id|i
)braket
dot
id|base
comma
id|prom_pblocks
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
macro_line|#endif
id|i
op_increment
suffix:semicolon
)brace
id|p
op_assign
id|prom_getmdesc
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|prom_pblocks
(braket
id|i
)braket
dot
id|base
op_assign
l_int|0xdeadbeef
suffix:semicolon
id|prom_pblocks
(braket
id|i
)braket
dot
id|size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* indicates last elem. of array */
id|printk
c_func
(paren
l_string|&quot;PROMLIB: Total free ram %d bytes (%dK,%dMB)&bslash;n&quot;
comma
id|totram
comma
(paren
id|totram
op_div
l_int|1024
)paren
comma
(paren
id|totram
op_div
l_int|1024
op_div
l_int|1024
)paren
)paren
suffix:semicolon
multiline_comment|/* Setup upper physical memory bound. */
id|prom_setup_memupper
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Called from mem_init() to fixup the mem_map page settings. */
DECL|function|prom_fixup_mem_map
r_void
id|prom_fixup_mem_map
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|prom_pmemblock
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|nents
suffix:semicolon
multiline_comment|/* Determine number of pblockarray entries. */
id|p
op_assign
id|prom_getpblock_array
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|p
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
id|nents
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|start
op_ge
(paren
id|p
(braket
id|i
)braket
dot
id|base
)paren
)paren
op_logical_and
(paren
id|start
OL
(paren
id|p
(braket
id|i
)braket
dot
id|base
op_plus
id|p
(braket
id|i
)braket
dot
id|size
)paren
)paren
)paren
(brace
id|start
op_assign
id|p
(braket
id|i
)braket
dot
id|base
op_plus
id|p
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|start
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
eof
