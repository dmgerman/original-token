multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/machvec.h&n; *&n; *&t;Copyright (C) 1997, 1998  Richard Henderson&n; *&n; * This file has goodies to help simplify instantiation of machine vectors.&n; */
multiline_comment|/* Whee.  TSUNAMI doesn&squot;t have an HAE.  Fix things up for the GENERIC&n;   kernel by defining the HAE address to be that of the cache.  Now&n;   we can read and write it as we like.  ;-)  */
DECL|macro|TSUNAMI_HAE_ADDRESS
mdefine_line|#define TSUNAMI_HAE_ADDRESS&t;(&amp;alpha_mv.hae_cache)
multiline_comment|/* Only a few systems don&squot;t define IACK_SC, handling all interrupts through&n;   the SRM console.  But splitting out that one case from IO() below&n;   seems like such a pain.  Define this to get things to compile.  */
DECL|macro|JENSEN_IACK_SC
mdefine_line|#define JENSEN_IACK_SC&t;&t;1
DECL|macro|T2_IACK_SC
mdefine_line|#define T2_IACK_SC&t;&t;1
multiline_comment|/*&n; * Some helpful macros for filling in the blanks.&n; */
DECL|macro|CAT1
mdefine_line|#define CAT1(x,y)  x##y
DECL|macro|CAT
mdefine_line|#define CAT(x,y)   CAT1(x,y)
DECL|macro|DO_DEFAULT_RTC
mdefine_line|#define DO_DEFAULT_RTC&t;&t;&t;&t;&bslash;&n;&t;rtc_port: 0x70, rtc_addr: 0x80
DECL|macro|DO_EV4_MMU
mdefine_line|#define DO_EV4_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;max_asn:&t;&t;&t;EV4_MAX_ASN,&t;&t;&t;&bslash;&n;&t;mmu_context_mask:&t;&t;~0UL,&t;&t;&t;&t;&bslash;&n;&t;mv_get_mmu_context:&t;&t;ev4_get_mmu_context,&t;&t;&bslash;&n;&t;mv_flush_tlb_current:&t;&t;ev4_flush_tlb_current,&t;&t;&bslash;&n;&t;mv_flush_tlb_other:&t;&t;ev4_flush_tlb_other,&t;&t;&bslash;&n;&t;mv_flush_tlb_current_page:&t;ev4_flush_tlb_current_page
DECL|macro|DO_EV5_MMU
mdefine_line|#define DO_EV5_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;max_asn:&t;&t;&t;EV5_MAX_ASN,&t;&t;&t;&bslash;&n;&t;mmu_context_mask:&t;&t;~0UL,&t;&t;&t;&t;&bslash;&n;&t;mv_get_mmu_context:&t;&t;ev5_get_mmu_context,&t;&t;&bslash;&n;&t;mv_flush_tlb_current:&t;&t;ev5_flush_tlb_current,&t;&t;&bslash;&n;&t;mv_flush_tlb_other:&t;&t;ev5_flush_tlb_other,&t;&t;&bslash;&n;&t;mv_flush_tlb_current_page:&t;ev5_flush_tlb_current_page
DECL|macro|DO_EV6_MMU
mdefine_line|#define DO_EV6_MMU&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;max_asn:&t;&t;&t;EV5_MAX_ASN,&t;&t;&t;&bslash;&n;&t;mmu_context_mask:&t;&t;0xfffffffffful,&t;&t;&t;&bslash;&n;&t;mv_get_mmu_context:&t;&t;ev5_get_mmu_context,&t;&t;&bslash;&n;&t;mv_flush_tlb_current:&t;&t;ev5_flush_tlb_current,&t;&t;&bslash;&n;&t;mv_flush_tlb_other:&t;&t;ev5_flush_tlb_other,&t;&t;&bslash;&n;&t;mv_flush_tlb_current_page:&t;ev5_flush_tlb_current_page
DECL|macro|IO_LITE
mdefine_line|#define IO_LITE(UP,low1,low2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;hae_register:&t;&t;(unsigned long *) CAT(UP,_HAE_ADDRESS),&t;&bslash;&n;&t;iack_sc:&t;&t;CAT(UP,_IACK_SC),&t;&t;&t;&bslash;&n;&t;mv_inb:&t;&t;&t;CAT(low1,_inb),&t;&t;&t;&t;&bslash;&n;&t;mv_inw:&t;&t;&t;CAT(low1,_inw),&t;&t;&t;&t;&bslash;&n;&t;mv_inl:&t;&t;&t;CAT(low1,_inl),&t;&t;&t;&t;&bslash;&n;&t;mv_outb:&t;&t;CAT(low1,_outb),&t;&t;&t;&bslash;&n;&t;mv_outw:&t;&t;CAT(low1,_outw),&t;&t;&t;&bslash;&n;&t;mv_outl:&t;&t;CAT(low1,_outl),&t;&t;&t;&bslash;&n;&t;mv_readb:&t;&t;CAT(low1,_readb),&t;&t;&t;&bslash;&n;&t;mv_readw:&t;&t;CAT(low1,_readw),&t;&t;&t;&bslash;&n;&t;mv_readl:&t;&t;CAT(low1,_readl),&t;&t;&t;&bslash;&n;&t;mv_readq:&t;&t;CAT(low1,_readq),&t;&t;&t;&bslash;&n;&t;mv_writeb:&t;&t;CAT(low1,_writeb),&t;&t;&t;&bslash;&n;&t;mv_writew:&t;&t;CAT(low1,_writew),&t;&t;&t;&bslash;&n;&t;mv_writel:&t;&t;CAT(low1,_writel),&t;&t;&t;&bslash;&n;&t;mv_writeq:&t;&t;CAT(low1,_writeq),&t;&t;&t;&bslash;&n;&t;mv_dense_mem:&t;&t;CAT(low2,_dense_mem)
DECL|macro|IO
mdefine_line|#define IO(UP,low1,low2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;IO_LITE(UP,low1,low2),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pci_read_config_byte:&t;CAT(low2,_pcibios_read_config_byte),&t;&bslash;&n;&t;pci_read_config_word:&t;CAT(low2,_pcibios_read_config_word),&t;&bslash;&n;&t;pci_read_config_dword:&t;CAT(low2,_pcibios_read_config_dword),&t;&bslash;&n;&t;pci_write_config_byte:&t;CAT(low2,_pcibios_write_config_byte),&t;&bslash;&n;&t;pci_write_config_word:&t;CAT(low2,_pcibios_write_config_word),&t;&bslash;&n;&t;pci_write_config_dword:&t;CAT(low2,_pcibios_write_config_dword),&t;&bslash;&n;&t;dma_win_base:&t;&t;CAT(UP,_DMA_WIN_BASE_DEFAULT),&t;&t;&bslash;&n;        dma_win_size:&t;&t;CAT(UP,_DMA_WIN_SIZE_DEFAULT)
multiline_comment|/* Any assembler that can generate a GENERIC kernel can generate BWX&n;   instructions.  So always use them for PYXIS I/O.  */
DECL|macro|DO_APECS_IO
mdefine_line|#define DO_APECS_IO&t;IO(APECS,apecs,apecs)
DECL|macro|DO_CIA_IO
mdefine_line|#define DO_CIA_IO&t;IO(CIA,cia,cia)
DECL|macro|DO_LCA_IO
mdefine_line|#define DO_LCA_IO&t;IO(LCA,lca,lca)
DECL|macro|DO_MCPCIA_IO
mdefine_line|#define DO_MCPCIA_IO&t;IO(MCPCIA,mcpcia,mcpcia)
DECL|macro|DO_PYXIS_IO
mdefine_line|#define DO_PYXIS_IO&t;IO(PYXIS,pyxis_bw,pyxis)
DECL|macro|DO_T2_IO
mdefine_line|#define DO_T2_IO&t;IO(T2,t2,t2)
DECL|macro|DO_TSUNAMI_IO
mdefine_line|#define DO_TSUNAMI_IO&t;IO(TSUNAMI,tsunami,tsunami)
DECL|macro|BUS
mdefine_line|#define BUS(which)&t;&t;&t;&t;&t;&bslash;&n;&t;mv_virt_to_bus:&t;CAT(which,_virt_to_bus),&t;&bslash;&n;&t;mv_bus_to_virt:&t;CAT(which,_bus_to_virt)
DECL|macro|DO_APECS_BUS
mdefine_line|#define DO_APECS_BUS&t;BUS(apecs)
DECL|macro|DO_CIA_BUS
mdefine_line|#define DO_CIA_BUS&t;BUS(cia)
DECL|macro|DO_LCA_BUS
mdefine_line|#define DO_LCA_BUS&t;BUS(lca)
DECL|macro|DO_MCPCIA_BUS
mdefine_line|#define DO_MCPCIA_BUS&t;BUS(mcpcia)
DECL|macro|DO_PYXIS_BUS
mdefine_line|#define DO_PYXIS_BUS&t;BUS(pyxis)
DECL|macro|DO_T2_BUS
mdefine_line|#define DO_T2_BUS&t;BUS(t2)
DECL|macro|DO_TSUNAMI_BUS
mdefine_line|#define DO_TSUNAMI_BUS&t;BUS(tsunami)
multiline_comment|/*&n; * In a GENERIC kernel, we have lots of these vectors floating about,&n; * all but one of which we want to go away.  In a non-GENERIC kernel,&n; * we want only one, ever.&n; *&n; * Accomplish this in the GENERIC kernel by puting all of the vectors&n; * in the .init.data section where they&squot;ll go away.  We&squot;ll copy the&n; * one we want to the real alpha_mv vector in setup_arch.&n; *&n; * Accomplish this in a non-GENERIC kernel by ifdef&squot;ing out all but&n; * one of the vectors, which will not reside in .init.data.  We then&n; * alias this one vector to alpha_mv, so no copy is needed.&n; *&n; * Upshot: set __initdata to nothing for non-GENERIC kernels.&n; */
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|__initmv
mdefine_line|#define __initmv __initdata
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(x)
macro_line|#else
DECL|macro|__initmv
mdefine_line|#define __initmv
multiline_comment|/* GCC actually has a syntax for defining aliases, but is under some&n;   delusion that you shouldn&squot;t be able to declare it extern somewhere&n;   else beforehand.  Fine.  We&squot;ll do it ourselves.  */
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(system) asm(&quot;.global alpha_mv&bslash;nalpha_mv = &quot; #system &quot;_mv&quot;);
macro_line|#endif
eof
