multiline_comment|/* $Id: nosun4c.c,v 1.3 2000/02/14 04:52:36 jj Exp $&n; * nosun4c.c: This file is a bunch of dummies for SMP compiles, &n; *         so that it does not need sun4c and avoid ifdefs.&n; *&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|__initdata
r_static
r_char
id|shouldnothappen
(braket
)braket
id|__initdata
op_assign
l_string|&quot;32bit SMP kernel only supports sun4m and sun4d&bslash;n&quot;
suffix:semicolon
multiline_comment|/* Dummies */
DECL|struct|sun4c_mmu_ring
r_struct
id|sun4c_mmu_ring
(brace
DECL|member|xxx1
r_int
r_int
id|xxx1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|xxx2
r_int
r_char
id|xxx2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|xxx3
r_int
id|xxx3
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sun4c_kernel_ring
r_struct
id|sun4c_mmu_ring
id|sun4c_kernel_ring
suffix:semicolon
DECL|variable|sun4c_kfree_ring
r_struct
id|sun4c_mmu_ring
id|sun4c_kfree_ring
suffix:semicolon
DECL|variable|sun4c_kernel_faults
r_int
r_int
id|sun4c_kernel_faults
suffix:semicolon
DECL|variable|sun4c_memerr_reg
r_int
r_int
op_star
id|sun4c_memerr_reg
suffix:semicolon
DECL|function|should_not_happen
r_static
r_void
id|__init
id|should_not_happen
c_func
(paren
r_void
)paren
(brace
id|prom_printf
c_func
(paren
id|shouldnothappen
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sun4c_paging_init
r_int
r_int
id|__init
id|sun4c_paging_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
(brace
id|should_not_happen
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ld_mmu_sun4c
r_void
id|__init
id|ld_mmu_sun4c
c_func
(paren
r_void
)paren
(brace
id|should_not_happen
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sun4c_mapioaddr
r_void
id|sun4c_mapioaddr
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|virt_addr
comma
r_int
id|bus_type
comma
r_int
id|rdonly
)paren
(brace
)brace
DECL|function|sun4c_unmapioaddr
r_void
id|sun4c_unmapioaddr
c_func
(paren
r_int
r_int
id|virt_addr
)paren
(brace
)brace
DECL|function|sun4c_complete_all_stores
r_void
id|sun4c_complete_all_stores
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|sun4c_pte_offset
id|pte_t
op_star
id|sun4c_pte_offset
c_func
(paren
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sun4c_update_mmu_cache
r_void
id|sun4c_update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
)brace
DECL|function|sun4c_probe_vac
r_void
id|__init
id|sun4c_probe_vac
c_func
(paren
r_void
)paren
(brace
id|should_not_happen
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sun4c_probe_memerr_reg
r_void
id|__init
id|sun4c_probe_memerr_reg
c_func
(paren
r_void
)paren
(brace
id|should_not_happen
c_func
(paren
)paren
suffix:semicolon
)brace
eof
