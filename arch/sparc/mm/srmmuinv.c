multiline_comment|/* $Id: srmmuinv.c,v 1.2 1995/11/25 00:59:36 davem Exp $&n; * srmmuinv.c:  Invalidate routines for the various different&n; *              SRMMU implementations.&n; *&n; * Copyright (C) 1995 David S. Miller&n; */
multiline_comment|/* HyperSparc */
DECL|function|hyper_invalidate
id|hyper_invalidate
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
id|sfsr_clear
suffix:semicolon
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
multiline_comment|/* Flush ICACHE */
id|flush_whole_icache
c_func
(paren
)paren
suffix:semicolon
id|sfsr_clear
op_assign
id|srmmu_get_fstatus
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|hyper_invalidate_mp
id|hyper_invalidate_mp
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
id|sfsr_clear
suffix:semicolon
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
multiline_comment|/* Flush ICACHE */
id|flush_whole_icache
c_func
(paren
)paren
suffix:semicolon
id|sfsr_clear
op_assign
id|srmmu_get_fstatus
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Tell other CPUS to each call the Uniprocessor&n;&t; * invalidate routine.&n;&t; */
r_return
suffix:semicolon
)brace
multiline_comment|/* Cypress */
r_void
DECL|function|cypress_invalidate
id|cypress_invalidate
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
r_void
DECL|function|cypress_invalidate_mp
id|cypress_invalidate_mp
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
multiline_comment|/* Tell other CPUS to call the UP version */
r_return
suffix:semicolon
)brace
r_void
DECL|function|cypress_invalidate_asibad
id|cypress_invalidate_asibad
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache w/o using ASIs */
r_return
suffix:semicolon
)brace
r_void
DECL|function|cypress_invalidate_asibad_mp
id|cypress_invalidate_asibad_mp
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache w/o using ASIs */
multiline_comment|/* Tell other CPUS to call the UP version */
r_return
suffix:semicolon
)brace
multiline_comment|/* Swift */
r_void
DECL|function|swift_invalidate
id|swift_invalidate
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
r_void
DECL|function|swift_invalidate_poke_kernel_pageperms
id|swift_invalidate_poke_kernel_pageperms
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
r_void
DECL|function|swift_invalidate_poke_kernel_pte_cbits
id|swift_invalidate_poke_kernel_pte_cbits
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
r_void
DECL|function|swift_invalidate_poke_everything
id|swift_invalidate_poke_everything
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
multiline_comment|/* Tsunami */
DECL|function|tsunami_invalidate
id|tsunami_invalidate
c_func
(paren
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush Virtual Address Cache */
r_return
suffix:semicolon
)brace
multiline_comment|/* Viking */
DECL|function|viking_invalidate
id|viking_invalidate
c_func
(paren
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|viking_invalidate_mp
id|viking_invalidate_mp
c_func
(paren
)paren
(brace
multiline_comment|/* Flush TLB */
id|srmmu_flush_whole_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Make other CPUS call UP routine. */
r_return
suffix:semicolon
)brace
multiline_comment|/* That should be it */
eof
