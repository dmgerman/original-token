macro_line|#ifndef __ALPHA_TSUNAMI__H__
DECL|macro|__ALPHA_TSUNAMI__H__
mdefine_line|#define __ALPHA_TSUNAMI__H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * TSUNAMI/TYPHOON are the internal names for the core logic chipset which&n; * provides memory controller and PCI access for the 21264 based systems.&n; *&n; * This file is based on:&n; *&n; * Tsunami System Programmers Manual&n; * Preliminary, Chapters 2-5&n; *&n; */
DECL|macro|TSUNAMI_DMA_WIN_BASE_DEFAULT
mdefine_line|#define TSUNAMI_DMA_WIN_BASE_DEFAULT    (1024*1024*1024)
DECL|macro|TSUNAMI_DMA_WIN_SIZE_DEFAULT
mdefine_line|#define TSUNAMI_DMA_WIN_SIZE_DEFAULT    (1024*1024*1024)
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM_SETUP)
DECL|macro|TSUNAMI_DMA_WIN_BASE
mdefine_line|#define TSUNAMI_DMA_WIN_BASE&t;&t;alpha_mv.dma_win_base
DECL|macro|TSUNAMI_DMA_WIN_SIZE
mdefine_line|#define TSUNAMI_DMA_WIN_SIZE&t;&t;alpha_mv.dma_win_size
macro_line|#else
DECL|macro|TSUNAMI_DMA_WIN_BASE
mdefine_line|#define TSUNAMI_DMA_WIN_BASE&t;&t;TSUNAMI_DMA_WIN_BASE_DEFAULT
DECL|macro|TSUNAMI_DMA_WIN_SIZE
mdefine_line|#define TSUNAMI_DMA_WIN_SIZE&t;&t;TSUNAMI_DMA_WIN_SIZE_DEFAULT
macro_line|#endif
multiline_comment|/* XXX: Do we need to conditionalize on this?  */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|TS_BIAS
mdefine_line|#define TS_BIAS 0x80000000000UL
macro_line|#else
DECL|macro|TS_BIAS
mdefine_line|#define TS_BIAS 0x10000000000UL
macro_line|#endif
multiline_comment|/*&n; * CChip and DChip registers&n; */
DECL|macro|TSUNAMI_CSR_CSC
mdefine_line|#define&t;TSUNAMI_CSR_CSC&t;&t;(IDENT_ADDR + TS_BIAS + 0x1A0000000UL)
DECL|macro|TSUNAMI_CSR_MTR
mdefine_line|#define&t;TSUNAMI_CSR_MTR&t;&t;(IDENT_ADDR + TS_BIAS + 0x1A0000040UL)
DECL|macro|TSUNAMI_CSR_MISC
mdefine_line|#define&t;TSUNAMI_CSR_MISC&t;(IDENT_ADDR + TS_BIAS + 0x1A0000080UL)
DECL|macro|TSUNAMI_CSR_MPD
mdefine_line|#define&t;TSUNAMI_CSR_MPD&t;&t;(IDENT_ADDR + TS_BIAS + 0x1A00000C0UL)
DECL|macro|TSUNAMI_CSR_AAR0
mdefine_line|#define&t;TSUNAMI_CSR_AAR0&t;(IDENT_ADDR + TS_BIAS + 0x1A0000100UL)
DECL|macro|TSUNAMI_CSR_AAR1
mdefine_line|#define&t;TSUNAMI_CSR_AAR1&t;(IDENT_ADDR + TS_BIAS + 0x1A0000140UL)
DECL|macro|TSUNAMI_CSR_AAR2
mdefine_line|#define&t;TSUNAMI_CSR_AAR2&t;(IDENT_ADDR + TS_BIAS + 0x1A0000180UL)
DECL|macro|TSUNAMI_CSR_AAR3
mdefine_line|#define&t;TSUNAMI_CSR_AAR3&t;(IDENT_ADDR + TS_BIAS + 0x1A00001C0UL)
DECL|macro|TSUNAMI_CSR_DIM0
mdefine_line|#define&t;TSUNAMI_CSR_DIM0&t;(IDENT_ADDR + TS_BIAS + 0x1A0000200UL)
DECL|macro|TSUNAMI_CSR_DIM1
mdefine_line|#define&t;TSUNAMI_CSR_DIM1&t;(IDENT_ADDR + TS_BIAS + 0x1A0000240UL)
DECL|macro|TSUNAMI_CSR_DIR0
mdefine_line|#define&t;TSUNAMI_CSR_DIR0&t;(IDENT_ADDR + TS_BIAS + 0x1A0000280UL)
DECL|macro|TSUNAMI_CSR_DIR1
mdefine_line|#define&t;TSUNAMI_CSR_DIR1&t;(IDENT_ADDR + TS_BIAS + 0x1A00002C0UL)
DECL|macro|TSUNAMI_CSR_DRIR
mdefine_line|#define&t;TSUNAMI_CSR_DRIR&t;(IDENT_ADDR + TS_BIAS + 0x1A0000300UL)
DECL|macro|TSUNAMI_CSR_PRBEN
mdefine_line|#define&t;TSUNAMI_CSR_PRBEN&t;(IDENT_ADDR + TS_BIAS + 0x1A0000340UL)
DECL|macro|TSUNAMI_CSR_IIC
mdefine_line|#define&t;TSUNAMI_CSR_IIC&t;       &t;(IDENT_ADDR + TS_BIAS + 0x1A0000380UL)
DECL|macro|TSUNAMI_CSR_WDR
mdefine_line|#define&t;TSUNAMI_CSR_WDR&t;       &t;(IDENT_ADDR + TS_BIAS + 0x1A00003C0UL)
DECL|macro|TSUNAMI_CSR_MPR0
mdefine_line|#define&t;TSUNAMI_CSR_MPR0&t;(IDENT_ADDR + TS_BIAS + 0x1A0000400UL)
DECL|macro|TSUNAMI_CSR_MPR1
mdefine_line|#define&t;TSUNAMI_CSR_MPR1&t;(IDENT_ADDR + TS_BIAS + 0x1A0000440UL)
DECL|macro|TSUNAMI_CSR_MPR2
mdefine_line|#define&t;TSUNAMI_CSR_MPR2&t;(IDENT_ADDR + TS_BIAS + 0x1A0000480UL)
DECL|macro|TSUNAMI_CSR_MPR3
mdefine_line|#define&t;TSUNAMI_CSR_MPR3&t;(IDENT_ADDR + TS_BIAS + 0x1A00004C0UL)
DECL|macro|TSUNAMI_CSR_TTR
mdefine_line|#define&t;TSUNAMI_CSR_TTR&t;&t;(IDENT_ADDR + TS_BIAS + 0x1A0000580UL)
DECL|macro|TSUNAMI_CSR_TDR
mdefine_line|#define&t;TSUNAMI_CSR_TDR&t;&t;(IDENT_ADDR + TS_BIAS + 0x1A00005C0UL)
DECL|macro|TSUNAMI_CSR_DSC
mdefine_line|#define&t;TSUNAMI_CSR_DSC&t;       &t;(IDENT_ADDR + TS_BIAS + 0x1B0000800UL)
DECL|macro|TSUNAMI_CSR_STR
mdefine_line|#define&t;TSUNAMI_CSR_STR&t;&t;(IDENT_ADDR + TS_BIAS + 0x1B0000840UL)
DECL|macro|TSUNAMI_CSR_DREV
mdefine_line|#define&t;TSUNAMI_CSR_DREV&t;(IDENT_ADDR + TS_BIAS + 0x1B0000880UL)
multiline_comment|/*&n; * PChip registers&n; */
DECL|macro|TSUNAMI_PCHIP0_WSBA0
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSBA0  &t;(IDENT_ADDR + TS_BIAS + 0x180000000UL)
DECL|macro|TSUNAMI_PCHIP0_WSBA1
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSBA1  &t;(IDENT_ADDR + TS_BIAS + 0x180000040UL)
DECL|macro|TSUNAMI_PCHIP0_WSBA2
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSBA2  &t;(IDENT_ADDR + TS_BIAS + 0x180000080UL)
DECL|macro|TSUNAMI_PCHIP0_WSBA3
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSBA3  &t;(IDENT_ADDR + TS_BIAS + 0x1800000C0UL)
DECL|macro|TSUNAMI_PCHIP0_WSM0
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSM0  &t;(IDENT_ADDR + TS_BIAS + 0x180000100UL)
DECL|macro|TSUNAMI_PCHIP0_WSM1
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSM1  &t;(IDENT_ADDR + TS_BIAS + 0x180000140UL)
DECL|macro|TSUNAMI_PCHIP0_WSM2
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSM2  &t;(IDENT_ADDR + TS_BIAS + 0x180000180UL)
DECL|macro|TSUNAMI_PCHIP0_WSM3
mdefine_line|#define&t;TSUNAMI_PCHIP0_WSM3  &t;(IDENT_ADDR + TS_BIAS + 0x1800001C0UL)
DECL|macro|TSUNAMI_PCHIP0_TBA0
mdefine_line|#define&t;TSUNAMI_PCHIP0_TBA0  &t;(IDENT_ADDR + TS_BIAS + 0x180000200UL)
DECL|macro|TSUNAMI_PCHIP0_TBA1
mdefine_line|#define&t;TSUNAMI_PCHIP0_TBA1  &t;(IDENT_ADDR + TS_BIAS + 0x180000240UL)
DECL|macro|TSUNAMI_PCHIP0_TBA2
mdefine_line|#define&t;TSUNAMI_PCHIP0_TBA2  &t;(IDENT_ADDR + TS_BIAS + 0x180000280UL)
DECL|macro|TSUNAMI_PCHIP0_TBA3
mdefine_line|#define&t;TSUNAMI_PCHIP0_TBA3  &t;(IDENT_ADDR + TS_BIAS + 0x1800002C0UL)
DECL|macro|TSUNAMI_PCHIP0_PCTL
mdefine_line|#define&t;TSUNAMI_PCHIP0_PCTL  &t;(IDENT_ADDR + TS_BIAS + 0x180000300UL)
DECL|macro|TSUNAMI_PCHIP0_PLAT
mdefine_line|#define&t;TSUNAMI_PCHIP0_PLAT  &t;(IDENT_ADDR + TS_BIAS + 0x180000340UL)
DECL|macro|TSUNAMI_PCHIP0_RESERVED
mdefine_line|#define&t;TSUNAMI_PCHIP0_RESERVED&t;(IDENT_ADDR + TS_BIAS + 0x180000380UL)
DECL|macro|TSUNAMI_PCHIP0_PERROR
mdefine_line|#define&t;TSUNAMI_PCHIP0_PERROR&t;(IDENT_ADDR + TS_BIAS + 0x1800003c0UL)
DECL|macro|TSUNAMI_PCHIP0_PERRMASK
mdefine_line|#define&t;TSUNAMI_PCHIP0_PERRMASK&t;(IDENT_ADDR + TS_BIAS + 0x180000400UL)
DECL|macro|TSUNAMI_PCHIP0_PERRSET
mdefine_line|#define&t;TSUNAMI_PCHIP0_PERRSET &t;(IDENT_ADDR + TS_BIAS + 0x180000440UL)
DECL|macro|TSUNAMI_PCHIP0_TLBIV
mdefine_line|#define&t;TSUNAMI_PCHIP0_TLBIV  &t;(IDENT_ADDR + TS_BIAS + 0x180000480UL)
DECL|macro|TSUNAMI_PCHIP0_TLBIA
mdefine_line|#define&t;TSUNAMI_PCHIP0_TLBIA &t;(IDENT_ADDR + TS_BIAS + 0x1800004C0UL)
DECL|macro|TSUNAMI_PCHIP0_PMONCTL
mdefine_line|#define&t;TSUNAMI_PCHIP0_PMONCTL&t;(IDENT_ADDR + TS_BIAS + 0x180000500UL)
DECL|macro|TSUNAMI_PCHIP0_PMONCNT
mdefine_line|#define&t;TSUNAMI_PCHIP0_PMONCNT&t;(IDENT_ADDR + TS_BIAS + 0x180000540UL)
DECL|macro|TSUNAMI_PCHIP1_WSBA0
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSBA0  &t;(IDENT_ADDR + TS_BIAS + 0x380000000UL)
DECL|macro|TSUNAMI_PCHIP1_WSBA1
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSBA1  &t;(IDENT_ADDR + TS_BIAS + 0x380000040UL)
DECL|macro|TSUNAMI_PCHIP1_WSBA2
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSBA2  &t;(IDENT_ADDR + TS_BIAS + 0x380000080UL)
DECL|macro|TSUNAMI_PCHIP1_WSBA3
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSBA3  &t;(IDENT_ADDR + TS_BIAS + 0x3800000C0UL)
DECL|macro|TSUNAMI_PCHIP1_WSM0
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSM0  &t;(IDENT_ADDR + TS_BIAS + 0x380000100UL)
DECL|macro|TSUNAMI_PCHIP1_WSM1
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSM1  &t;(IDENT_ADDR + TS_BIAS + 0x380000140UL)
DECL|macro|TSUNAMI_PCHIP1_WSM2
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSM2  &t;(IDENT_ADDR + TS_BIAS + 0x380000180UL)
DECL|macro|TSUNAMI_PCHIP1_WSM3
mdefine_line|#define&t;TSUNAMI_PCHIP1_WSM3  &t;(IDENT_ADDR + TS_BIAS + 0x3800001C0UL)
DECL|macro|TSUNAMI_PCHIP1_TBA0
mdefine_line|#define&t;TSUNAMI_PCHIP1_TBA0  &t;(IDENT_ADDR + TS_BIAS + 0x380000200UL)
DECL|macro|TSUNAMI_PCHIP1_TBA1
mdefine_line|#define&t;TSUNAMI_PCHIP1_TBA1  &t;(IDENT_ADDR + TS_BIAS + 0x380000240UL)
DECL|macro|TSUNAMI_PCHIP1_TBA2
mdefine_line|#define&t;TSUNAMI_PCHIP1_TBA2  &t;(IDENT_ADDR + TS_BIAS + 0x380000280UL)
DECL|macro|TSUNAMI_PCHIP1_TBA3
mdefine_line|#define&t;TSUNAMI_PCHIP1_TBA3  &t;(IDENT_ADDR + TS_BIAS + 0x3800002C0UL)
DECL|macro|TSUNAMI_PCHIP1_PCTL
mdefine_line|#define&t;TSUNAMI_PCHIP1_PCTL  &t;(IDENT_ADDR + TS_BIAS + 0x380000300UL)
DECL|macro|TSUNAMI_PCHIP1_PLAT
mdefine_line|#define&t;TSUNAMI_PCHIP1_PLAT  &t;(IDENT_ADDR + TS_BIAS + 0x380000340UL)
DECL|macro|TSUNAMI_PCHIP1_RESERVED
mdefine_line|#define&t;TSUNAMI_PCHIP1_RESERVED&t;(IDENT_ADDR + TS_BIAS + 0x380000380UL)
DECL|macro|TSUNAMI_PCHIP1_PERROR
mdefine_line|#define&t;TSUNAMI_PCHIP1_PERROR&t;(IDENT_ADDR + TS_BIAS + 0x3800003c0UL)
DECL|macro|TSUNAMI_PCHIP1_PERRMASK
mdefine_line|#define&t;TSUNAMI_PCHIP1_PERRMASK&t;(IDENT_ADDR + TS_BIAS + 0x380000400UL)
DECL|macro|TSUNAMI_PCHIP1_PERRSET
mdefine_line|#define&t;TSUNAMI_PCHIP1_PERRSET&t;(IDENT_ADDR + TS_BIAS + 0x380000440UL)
DECL|macro|TSUNAMI_PCHIP1_TLBIV
mdefine_line|#define&t;TSUNAMI_PCHIP1_TLBIV  &t;(IDENT_ADDR + TS_BIAS + 0x380000480UL)
DECL|macro|TSUNAMI_PCHIP1_TLBIA
mdefine_line|#define&t;TSUNAMI_PCHIP1_TLBIA&t;(IDENT_ADDR + TS_BIAS + 0x3800004C0UL)
DECL|macro|TSUNAMI_PCHIP1_PMONCTL
mdefine_line|#define&t;TSUNAMI_PCHIP1_PMONCTL&t;(IDENT_ADDR + TS_BIAS + 0x380000500UL)
DECL|macro|TSUNAMI_PCHIP1_PMONCNT
mdefine_line|#define&t;TSUNAMI_PCHIP1_PMONCNT&t;(IDENT_ADDR + TS_BIAS + 0x380000540UL)
multiline_comment|/*                                                                          */
multiline_comment|/* TSUNAMI Pchip Error register.                                            */
multiline_comment|/*                                                                          */
DECL|macro|perror_m_lost
mdefine_line|#define perror_m_lost 0x1
DECL|macro|perror_m_serr
mdefine_line|#define perror_m_serr 0x2
DECL|macro|perror_m_perr
mdefine_line|#define perror_m_perr 0x4
DECL|macro|perror_m_dcrto
mdefine_line|#define perror_m_dcrto 0x8
DECL|macro|perror_m_sge
mdefine_line|#define perror_m_sge 0x10
DECL|macro|perror_m_ape
mdefine_line|#define perror_m_ape 0x20
DECL|macro|perror_m_ta
mdefine_line|#define perror_m_ta 0x40
DECL|macro|perror_m_rdpe
mdefine_line|#define perror_m_rdpe 0x80
DECL|macro|perror_m_nds
mdefine_line|#define perror_m_nds 0x100
DECL|macro|perror_m_rto
mdefine_line|#define perror_m_rto 0x200
DECL|macro|perror_m_uecc
mdefine_line|#define perror_m_uecc 0x400
DECL|macro|perror_m_cre
mdefine_line|#define perror_m_cre 0x800
DECL|macro|perror_m_addrl
mdefine_line|#define perror_m_addrl 0xFFFFFFFF0000UL
DECL|macro|perror_m_addrh
mdefine_line|#define perror_m_addrh 0x7000000000000UL
DECL|macro|perror_m_cmd
mdefine_line|#define perror_m_cmd 0xF0000000000000UL
DECL|macro|perror_m_syn
mdefine_line|#define perror_m_syn 0xFF00000000000000UL
DECL|union|TPchipPERROR
r_union
id|TPchipPERROR
(brace
r_struct
(brace
DECL|member|perror_v_lost
r_int
r_int
id|perror_v_lost
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_serr
r_int
id|perror_v_serr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_perr
r_int
id|perror_v_perr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_dcrto
r_int
id|perror_v_dcrto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_sge
r_int
id|perror_v_sge
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_ape
r_int
id|perror_v_ape
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_ta
r_int
id|perror_v_ta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rdpe
r_int
id|perror_v_rdpe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_nds
r_int
id|perror_v_nds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rto
r_int
id|perror_v_rto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_uecc
r_int
id|perror_v_uecc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_cre
r_int
id|perror_v_cre
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rsvd1
r_int
id|perror_v_rsvd1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|perror_v_addrl
r_int
id|perror_v_addrl
suffix:colon
l_int|32
suffix:semicolon
DECL|member|perror_v_addrh
r_int
id|perror_v_addrh
suffix:colon
l_int|3
suffix:semicolon
DECL|member|perror_v_rsvd2
r_int
id|perror_v_rsvd2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_cmd
r_int
id|perror_v_cmd
suffix:colon
l_int|4
suffix:semicolon
DECL|member|perror_v_syn
r_int
id|perror_v_syn
suffix:colon
l_int|8
suffix:semicolon
DECL|member|perror_r_bits
)brace
id|perror_r_bits
suffix:semicolon
DECL|member|perror_q_whole
r_int
id|perror_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*                                                                          */
multiline_comment|/* TSUNAMI Pchip Window Space Base Address register.                        */
multiline_comment|/*                                                                          */
DECL|macro|wsba_m_ena
mdefine_line|#define wsba_m_ena 0x1                
DECL|macro|wsba_m_sg
mdefine_line|#define wsba_m_sg 0x2
DECL|macro|wsba_m_ptp
mdefine_line|#define wsba_m_ptp 0x4
DECL|macro|wsba_m_addr
mdefine_line|#define wsba_m_addr 0xFFF00000  
DECL|macro|wmask_k_sz1gb
mdefine_line|#define wmask_k_sz1gb 0x3FF00000                   
DECL|union|TPchipWSBA
r_union
id|TPchipWSBA
(brace
r_struct
(brace
DECL|member|wsba_v_ena
r_int
id|wsba_v_ena
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_sg
r_int
id|wsba_v_sg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_ptp
r_int
id|wsba_v_ptp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_rsvd1
r_int
id|wsba_v_rsvd1
suffix:colon
l_int|17
suffix:semicolon
DECL|member|wsba_v_addr
r_int
id|wsba_v_addr
suffix:colon
l_int|12
suffix:semicolon
DECL|member|wsba_v_rsvd2
r_int
id|wsba_v_rsvd2
suffix:colon
l_int|32
suffix:semicolon
DECL|member|wsba_r_bits
)brace
id|wsba_r_bits
suffix:semicolon
DECL|member|wsba_q_whole
r_int
id|wsba_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;    */
multiline_comment|/* TSUNAMI Pchip Control Register&t;&t;&t;&t;&t;    */
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;    */
DECL|macro|pctl_m_fdsc
mdefine_line|#define pctl_m_fdsc 0x1
DECL|macro|pctl_m_fbtb
mdefine_line|#define pctl_m_fbtb 0x2
DECL|macro|pctl_m_thdis
mdefine_line|#define pctl_m_thdis 0x4
DECL|macro|pctl_m_chaindis
mdefine_line|#define pctl_m_chaindis 0x8
DECL|macro|pctl_m_tgtlat
mdefine_line|#define pctl_m_tgtlat 0x10
DECL|macro|pctl_m_hole
mdefine_line|#define pctl_m_hole 0x20
DECL|macro|pctl_m_mwin
mdefine_line|#define pctl_m_mwin 0x40
DECL|macro|pctl_m_arbena
mdefine_line|#define pctl_m_arbena 0x80
DECL|macro|pctl_m_prigrp
mdefine_line|#define pctl_m_prigrp 0x7F00
DECL|macro|pctl_m_ppri
mdefine_line|#define pctl_m_ppri 0x8000
DECL|macro|pctl_m_rsvd1
mdefine_line|#define pctl_m_rsvd1 0x30000
DECL|macro|pctl_m_eccen
mdefine_line|#define pctl_m_eccen 0x40000
DECL|macro|pctl_m_padm
mdefine_line|#define pctl_m_padm 0x80000
DECL|macro|pctl_m_cdqmax
mdefine_line|#define pctl_m_cdqmax 0xF00000
DECL|macro|pctl_m_rev
mdefine_line|#define pctl_m_rev 0xFF000000
DECL|macro|pctl_m_crqmax
mdefine_line|#define pctl_m_crqmax 0xF00000000UL
DECL|macro|pctl_m_ptpmax
mdefine_line|#define pctl_m_ptpmax 0xF000000000UL
DECL|macro|pctl_m_pclkx
mdefine_line|#define pctl_m_pclkx 0x30000000000UL
DECL|macro|pctl_m_fdsdis
mdefine_line|#define pctl_m_fdsdis 0x40000000000UL
DECL|macro|pctl_m_fdwdis
mdefine_line|#define pctl_m_fdwdis 0x80000000000UL
DECL|macro|pctl_m_ptevrfy
mdefine_line|#define pctl_m_ptevrfy 0x100000000000UL
DECL|macro|pctl_m_rpp
mdefine_line|#define pctl_m_rpp 0x200000000000UL
DECL|macro|pctl_m_pid
mdefine_line|#define pctl_m_pid 0xC00000000000UL
DECL|macro|pctl_m_rsvd2
mdefine_line|#define pctl_m_rsvd2 0xFFFF000000000000UL
DECL|union|TPchipPCTL
r_union
id|TPchipPCTL
(brace
r_struct
(brace
DECL|member|pctl_v_fdsc
r_int
id|pctl_v_fdsc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_fbtb
r_int
id|pctl_v_fbtb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_thdis
r_int
id|pctl_v_thdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_chaindis
r_int
id|pctl_v_chaindis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_tgtlat
r_int
id|pctl_v_tgtlat
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_hole
r_int
id|pctl_v_hole
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_mwin
r_int
id|pctl_v_mwin
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_arbena
r_int
id|pctl_v_arbena
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_prigrp
r_int
id|pctl_v_prigrp
suffix:colon
l_int|7
suffix:semicolon
DECL|member|pctl_v_ppri
r_int
id|pctl_v_ppri
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_rsvd1
r_int
id|pctl_v_rsvd1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_eccen
r_int
id|pctl_v_eccen
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_padm
r_int
id|pctl_v_padm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_cdqmax
r_int
id|pctl_v_cdqmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_rev
r_int
id|pctl_v_rev
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pctl_v_crqmax
r_int
id|pctl_v_crqmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_ptpmax
r_int
id|pctl_v_ptpmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_pclkx
r_int
id|pctl_v_pclkx
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_fdsdis
r_int
id|pctl_v_fdsdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_fdwdis
r_int
id|pctl_v_fdwdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_ptevrfy
r_int
id|pctl_v_ptevrfy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_rpp
r_int
id|pctl_v_rpp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_pid
r_int
id|pctl_v_pid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_rsvd2
r_int
id|pctl_v_rsvd2
suffix:colon
l_int|16
suffix:semicolon
DECL|member|pctl_r_bits
)brace
id|pctl_r_bits
suffix:semicolon
DECL|member|pctl_q_whole
r_int
id|pctl_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*                                                                          */
multiline_comment|/* TSUNAMI Pchip Error Mask Register.                                       */
multiline_comment|/*                                                                          */
DECL|macro|perrmask_m_lost
mdefine_line|#define perrmask_m_lost 0x1
DECL|macro|perrmask_m_serr
mdefine_line|#define perrmask_m_serr 0x2
DECL|macro|perrmask_m_perr
mdefine_line|#define perrmask_m_perr 0x4
DECL|macro|perrmask_m_dcrto
mdefine_line|#define perrmask_m_dcrto 0x8
DECL|macro|perrmask_m_sge
mdefine_line|#define perrmask_m_sge 0x10
DECL|macro|perrmask_m_ape
mdefine_line|#define perrmask_m_ape 0x20
DECL|macro|perrmask_m_ta
mdefine_line|#define perrmask_m_ta 0x40
DECL|macro|perrmask_m_rdpe
mdefine_line|#define perrmask_m_rdpe 0x80
DECL|macro|perrmask_m_nds
mdefine_line|#define perrmask_m_nds 0x100
DECL|macro|perrmask_m_rto
mdefine_line|#define perrmask_m_rto 0x200
DECL|macro|perrmask_m_uecc
mdefine_line|#define perrmask_m_uecc 0x400
DECL|macro|perrmask_m_cre
mdefine_line|#define perrmask_m_cre 0x800
DECL|macro|perrmask_m_rsvd
mdefine_line|#define perrmask_m_rsvd 0xFFFFFFFFFFFFF000UL
DECL|union|TPchipPERRMASK
r_union
id|TPchipPERRMASK
(brace
r_struct
(brace
DECL|member|perrmask_v_lost
r_int
r_int
id|perrmask_v_lost
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_serr
r_int
id|perrmask_v_serr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_perr
r_int
id|perrmask_v_perr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_dcrto
r_int
id|perrmask_v_dcrto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_sge
r_int
id|perrmask_v_sge
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_ape
r_int
id|perrmask_v_ape
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_ta
r_int
id|perrmask_v_ta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rdpe
r_int
id|perrmask_v_rdpe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_nds
r_int
id|perrmask_v_nds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rto
r_int
id|perrmask_v_rto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_uecc
r_int
id|perrmask_v_uecc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_cre
r_int
id|perrmask_v_cre
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rsvd1
r_int
id|perrmask_v_rsvd1
suffix:colon
l_int|20
suffix:semicolon
DECL|member|perrmask_v_rsvd2
r_int
id|perrmask_v_rsvd2
suffix:colon
l_int|32
suffix:semicolon
DECL|member|perrmask_r_bits
)brace
id|perrmask_r_bits
suffix:semicolon
DECL|member|perrmask_q_whole
r_int
id|perrmask_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|TSUNAMI_PCI0_MEM
mdefine_line|#define TSUNAMI_PCI0_MEM&t;&t;(IDENT_ADDR + TS_BIAS + 0x000000000UL)
DECL|macro|TSUNAMI_PCI0_IACK_SC
mdefine_line|#define TSUNAMI_PCI0_IACK_SC&t;&t;(IDENT_ADDR + TS_BIAS + 0x1F8000000UL)
DECL|macro|TSUNAMI_PCI0_IO
mdefine_line|#define TSUNAMI_PCI0_IO&t;&t;&t;(IDENT_ADDR + TS_BIAS + 0x1FC000000UL)
DECL|macro|TSUNAMI_PCI0_CONF
mdefine_line|#define TSUNAMI_PCI0_CONF&t;&t;(IDENT_ADDR + TS_BIAS + 0x1FE000000UL)
DECL|macro|TSUNAMI_PCI1_MEM
mdefine_line|#define TSUNAMI_PCI1_MEM&t;&t;(IDENT_ADDR + TS_BIAS + 0x200000000UL)
DECL|macro|TSUNAMI_PCI1_IACK_SC
mdefine_line|#define TSUNAMI_PCI1_IACK_SC&t;&t;(IDENT_ADDR + TS_BIAS + 0x3F8000000UL)
DECL|macro|TSUNAMI_PCI1_IO
mdefine_line|#define TSUNAMI_PCI1_IO&t;&t;&t;(IDENT_ADDR + TS_BIAS + 0x3FC000000UL)
DECL|macro|TSUNAMI_PCI1_CONF
mdefine_line|#define TSUNAMI_PCI1_CONF&t;&t;(IDENT_ADDR + TS_BIAS + 0x3FE000000UL)
multiline_comment|/*&n; * Data structure for handling TSUNAMI machine checks:&n; */
DECL|struct|el_TSUNAMI_sysdata_mcheck
r_struct
id|el_TSUNAMI_sysdata_mcheck
(brace
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * Translate physical memory address as seen on (PCI) bus into&n; * a kernel virtual address and vv.&n; */
DECL|function|tsunami_virt_to_bus
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_virt_to_bus
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_return
id|virt_to_phys
c_func
(paren
id|address
)paren
op_plus
id|TSUNAMI_DMA_WIN_BASE
suffix:semicolon
)brace
DECL|function|tsunami_bus_to_virt
id|__EXTERN_INLINE
r_void
op_star
id|tsunami_bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|TSUNAMI_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * TSUNAMI, the 21??? PCI/memory support chipset for the EV6 (21264)&n; * can only use linear accesses to get at PCI memory and I/O spaces.&n; */
multiline_comment|/* HACK ALERT! HACK ALERT! */
multiline_comment|/* HACK ALERT! HACK ALERT! */
multiline_comment|/* Only using PCI bus 0 for now in all routines.  */
DECL|macro|TSUNAMI_IACK_SC
mdefine_line|#define TSUNAMI_IACK_SC  TSUNAMI_PCI0_IACK_SC
multiline_comment|/* HACK ALERT! HACK ALERT! */
multiline_comment|/* HACK ALERT! HACK ALERT! */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|tsunami_inb
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_outb
id|__EXTERN_INLINE
r_void
id|tsunami_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_inw
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_outw
id|__EXTERN_INLINE
r_void
id|tsunami_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_inl
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
suffix:semicolon
)brace
DECL|function|tsunami_outl
id|__EXTERN_INLINE
r_void
id|tsunami_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_IO
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  all accesses are done through linear space.&n; */
DECL|function|tsunami_readb
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_readw
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_readl
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
suffix:semicolon
)brace
DECL|function|tsunami_readq
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
suffix:semicolon
)brace
DECL|function|tsunami_writeb
id|__EXTERN_INLINE
r_void
id|tsunami_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_writew
id|__EXTERN_INLINE
r_void
id|tsunami_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_writel
id|__EXTERN_INLINE
r_void
id|tsunami_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tsunami_writeq
id|__EXTERN_INLINE
r_void
id|tsunami_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
(paren
id|addr
op_plus
id|TSUNAMI_PCI0_MEM
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find the DENSE memory area for a given bus address.  */
DECL|function|tsunami_dense_mem
id|__EXTERN_INLINE
r_int
r_int
id|tsunami_dense_mem
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|TSUNAMI_PCI0_MEM
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus&t;tsunami_virt_to_bus
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt&t;tsunami_bus_to_virt
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;tsunami_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;tsunami_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;tsunami_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;tsunami_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;tsunami_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;tsunami_outl
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;tsunami_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;tsunami_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;tsunami_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;tsunami_writew
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;tsunami_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;tsunami_readq
DECL|macro|__writel
mdefine_line|#define __writel&t;tsunami_writel
DECL|macro|__writeq
mdefine_line|#define __writeq&t;tsunami_writeq
DECL|macro|dense_mem
mdefine_line|#define dense_mem&t;tsunami_dense_mem
DECL|macro|inb
mdefine_line|#define inb(port) __inb((port))
DECL|macro|inw
mdefine_line|#define inw(port) __inw((port))
DECL|macro|inl
mdefine_line|#define inl(port) __inl((port))
DECL|macro|outb
mdefine_line|#define outb(v, port) __outb((v),(port))
DECL|macro|outw
mdefine_line|#define outw(v, port) __outw((v),(port))
DECL|macro|outl
mdefine_line|#define outl(v, port) __outl((v),(port))
DECL|macro|readb
mdefine_line|#define readb(a)&t;__readb((unsigned long)(a))
DECL|macro|readw
mdefine_line|#define readw(a)&t;__readw((unsigned long)(a))
DECL|macro|readl
mdefine_line|#define readl(a)&t;__readl((unsigned long)(a))
DECL|macro|readq
mdefine_line|#define readq(a)&t;__readq((unsigned long)(a))
DECL|macro|writeb
mdefine_line|#define writeb(v,a)&t;__writeb((v),(unsigned long)(a))
DECL|macro|writew
mdefine_line|#define writew(v,a)&t;__writew((v),(unsigned long)(a))
DECL|macro|writel
mdefine_line|#define writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|writeq
mdefine_line|#define writeq(v,a)&t;__writeq((v),(unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_TSUNAMI__H__ */
eof
