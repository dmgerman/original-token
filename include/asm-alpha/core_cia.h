macro_line|#ifndef __ALPHA_CIA__H__
DECL|macro|__ALPHA_CIA__H__
mdefine_line|#define __ALPHA_CIA__H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * CIA is the internal name for the 2117x chipset which provides&n; * memory controller and PCI access for the 21164 chip based systems.&n; *&n; * This file is based on:&n; *&n; * DECchip 21171 Core Logic Chipset &n; * Technical Reference Manual&n; *&n; * EC-QE18B-TE&n; *&n; * david.rusling@reo.mts.dec.com Initial Version.&n; *&n; */
multiline_comment|/*------------------------------------------------------------------------**&n;**                                                                        **&n;**  EB164 I/O procedures                                                  **&n;**                                                                        **&n;**      inport[b|w|t|l], outport[b|w|t|l] 8:16:24:32 IO xfers             **&n;**&t;inportbxt: 8 bits only                                            **&n;**      inport:    alias of inportw                                       **&n;**      outport:   alias of outportw                                      **&n;**                                                                        **&n;**      inmem[b|w|t|l], outmem[b|w|t|l] 8:16:24:32 ISA memory xfers       **&n;**&t;inmembxt: 8 bits only                                             **&n;**      inmem:    alias of inmemw                                         **&n;**      outmem:   alias of outmemw                                        **&n;**                                                                        **&n;**------------------------------------------------------------------------*/
multiline_comment|/* CIA ADDRESS BIT DEFINITIONS&n; *&n; *  3333 3333 3322 2222 2222 1111 1111 11 &n; *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  1                                             000&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  |                                             |&bslash;|&n; *  |                               Byte Enable --+ |&n; *  |                             Transfer Length --+&n; *  +-- IO space, not cached&n; *&n; *   Byte      Transfer&n; *   Enable    Length    Transfer  Byte    Address&n; *   adr&lt;6:5&gt;  adr&lt;4:3&gt;  Length    Enable  Adder&n; *   ---------------------------------------------&n; *      00        00      Byte      1110   0x000&n; *      01        00      Byte      1101   0x020&n; *      10        00      Byte      1011   0x040&n; *      11        00      Byte      0111   0x060&n; *&n; *      00        01      Word      1100   0x008&n; *      01        01      Word      1001   0x028 &lt;= Not supported in this code.&n; *      10        01      Word      0011   0x048&n; *&n; *      00        10      Tribyte   1000   0x010&n; *      01        10      Tribyte   0001   0x030&n; *&n; *      10        11      Longword  0000   0x058&n; *&n; *      Note that byte enables are asserted low.&n; *&n; */
DECL|macro|CIA_MEM_R1_MASK
mdefine_line|#define CIA_MEM_R1_MASK 0x1fffffff  /* SPARSE Mem region 1 mask is 29 bits */
DECL|macro|CIA_MEM_R2_MASK
mdefine_line|#define CIA_MEM_R2_MASK 0x07ffffff  /* SPARSE Mem region 2 mask is 27 bits */
DECL|macro|CIA_MEM_R3_MASK
mdefine_line|#define CIA_MEM_R3_MASK 0x03ffffff  /* SPARSE Mem region 3 mask is 26 bits */
DECL|macro|CIA_DMA_WIN_BASE_DEFAULT
mdefine_line|#define CIA_DMA_WIN_BASE_DEFAULT&t;(1UL*1024*1024*1024)
DECL|macro|CIA_DMA_WIN_SIZE_DEFAULT
mdefine_line|#define CIA_DMA_WIN_SIZE_DEFAULT&t;(2UL*1024*1024*1024)
multiline_comment|/* Window 0 at 1GB size 1GB mapping to 0.  */
DECL|macro|CIA_DMA_WIN0_BASE_DEFAULT
mdefine_line|#define CIA_DMA_WIN0_BASE_DEFAULT      (1UL*1024*1024*1024)
DECL|macro|CIA_DMA_WIN0_SIZE_DEFAULT
mdefine_line|#define CIA_DMA_WIN0_SIZE_DEFAULT      (1UL*1024*1024*1024)
DECL|macro|CIA_DMA_WIN0_TRAN_DEFAULT
mdefine_line|#define CIA_DMA_WIN0_TRAN_DEFAULT      (0UL)
multiline_comment|/* Window 1 at 2GB size 1GB mapping to 1GB.  */
DECL|macro|CIA_DMA_WIN1_BASE_DEFAULT
mdefine_line|#define CIA_DMA_WIN1_BASE_DEFAULT      (2UL*1024*1024*1024)
DECL|macro|CIA_DMA_WIN1_SIZE_DEFAULT
mdefine_line|#define CIA_DMA_WIN1_SIZE_DEFAULT      (1UL*1024*1024*1024)
DECL|macro|CIA_DMA_WIN1_TRAN_DEFAULT
mdefine_line|#define CIA_DMA_WIN1_TRAN_DEFAULT      (1UL*1024*1024*1024)
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM_SETUP)
DECL|macro|CIA_DMA_WIN_BASE
mdefine_line|#define CIA_DMA_WIN_BASE&t;&t;alpha_mv.dma_win_base
DECL|macro|CIA_DMA_WIN_SIZE
mdefine_line|#define CIA_DMA_WIN_SIZE&t;&t;alpha_mv.dma_win_size
macro_line|#else
DECL|macro|CIA_DMA_WIN_BASE
mdefine_line|#define CIA_DMA_WIN_BASE&t;&t;CIA_DMA_WIN_BASE_DEFAULT
DECL|macro|CIA_DMA_WIN_SIZE
mdefine_line|#define CIA_DMA_WIN_SIZE&t;&t;CIA_DMA_WIN_SIZE_DEFAULT
macro_line|#endif
multiline_comment|/*&n; * 21171-CA Control and Status Registers (p4-1)&n; */
DECL|macro|CIA_IOC_CIA_REV
mdefine_line|#define CIA_IOC_CIA_REV               (IDENT_ADDR + 0x8740000080UL)
DECL|macro|CIA_IOC_PCI_LAT
mdefine_line|#define CIA_IOC_PCI_LAT               (IDENT_ADDR + 0x87400000C0UL)
DECL|macro|CIA_IOC_CIA_CTRL
mdefine_line|#define CIA_IOC_CIA_CTRL              (IDENT_ADDR + 0x8740000100UL)
DECL|macro|CIA_IOC_CIA_CNFG
mdefine_line|#define CIA_IOC_CIA_CNFG              (IDENT_ADDR + 0x8740000140UL)
DECL|macro|CIA_IOC_HAE_MEM
mdefine_line|#define CIA_IOC_HAE_MEM               (IDENT_ADDR + 0x8740000400UL)
DECL|macro|CIA_IOC_HAE_IO
mdefine_line|#define CIA_IOC_HAE_IO                (IDENT_ADDR + 0x8740000440UL)
DECL|macro|CIA_IOC_CFG
mdefine_line|#define CIA_IOC_CFG                   (IDENT_ADDR + 0x8740000480UL)
DECL|macro|CIA_IOC_CACK_EN
mdefine_line|#define CIA_IOC_CACK_EN               (IDENT_ADDR + 0x8740000600UL)
multiline_comment|/*&n; * 21171-CA Diagnostic Registers (p4-2)&n; */
DECL|macro|CIA_IOC_CIA_DIAG
mdefine_line|#define CIA_IOC_CIA_DIAG              (IDENT_ADDR + 0x8740002000UL)
DECL|macro|CIA_IOC_DIAG_CHECK
mdefine_line|#define CIA_IOC_DIAG_CHECK            (IDENT_ADDR + 0x8740003000UL)
multiline_comment|/*&n; * 21171-CA Performance Monitor registers (p4-3)&n; */
DECL|macro|CIA_IOC_PERF_MONITOR
mdefine_line|#define CIA_IOC_PERF_MONITOR          (IDENT_ADDR + 0x8740004000UL)
DECL|macro|CIA_IOC_PERF_CONTROL
mdefine_line|#define CIA_IOC_PERF_CONTROL          (IDENT_ADDR + 0x8740004040UL)
multiline_comment|/*&n; * 21171-CA Error registers (p4-3)&n; */
DECL|macro|CIA_IOC_CPU_ERR0
mdefine_line|#define CIA_IOC_CPU_ERR0              (IDENT_ADDR + 0x8740008000UL)
DECL|macro|CIA_IOC_CPU_ERR1
mdefine_line|#define CIA_IOC_CPU_ERR1              (IDENT_ADDR + 0x8740008040UL)
DECL|macro|CIA_IOC_CIA_ERR
mdefine_line|#define CIA_IOC_CIA_ERR               (IDENT_ADDR + 0x8740008200UL)
DECL|macro|CIA_IOC_CIA_STAT
mdefine_line|#define CIA_IOC_CIA_STAT              (IDENT_ADDR + 0x8740008240UL)
DECL|macro|CIA_IOC_ERR_MASK
mdefine_line|#define CIA_IOC_ERR_MASK              (IDENT_ADDR + 0x8740008280UL)
DECL|macro|CIA_IOC_CIA_SYN
mdefine_line|#define CIA_IOC_CIA_SYN               (IDENT_ADDR + 0x8740008300UL)
DECL|macro|CIA_IOC_MEM_ERR0
mdefine_line|#define CIA_IOC_MEM_ERR0              (IDENT_ADDR + 0x8740008400UL)
DECL|macro|CIA_IOC_MEM_ERR1
mdefine_line|#define CIA_IOC_MEM_ERR1              (IDENT_ADDR + 0x8740008440UL)
DECL|macro|CIA_IOC_PCI_ERR0
mdefine_line|#define CIA_IOC_PCI_ERR0              (IDENT_ADDR + 0x8740008800UL)
DECL|macro|CIA_IOC_PCI_ERR1
mdefine_line|#define CIA_IOC_PCI_ERR1              (IDENT_ADDR + 0x8740008840UL)
DECL|macro|CIA_IOC_PCI_ERR3
mdefine_line|#define CIA_IOC_PCI_ERR3              (IDENT_ADDR + 0x8740008880UL)
multiline_comment|/*&n; * 2117A-CA PCI Address Translation Registers.&n; */
DECL|macro|CIA_IOC_PCI_TBIA
mdefine_line|#define CIA_IOC_PCI_TBIA              (IDENT_ADDR + 0x8760000100UL)
DECL|macro|CIA_IOC_PCI_W0_BASE
mdefine_line|#define CIA_IOC_PCI_W0_BASE           (IDENT_ADDR + 0x8760000400UL)
DECL|macro|CIA_IOC_PCI_W0_MASK
mdefine_line|#define CIA_IOC_PCI_W0_MASK           (IDENT_ADDR + 0x8760000440UL)
DECL|macro|CIA_IOC_PCI_T0_BASE
mdefine_line|#define CIA_IOC_PCI_T0_BASE           (IDENT_ADDR + 0x8760000480UL)
DECL|macro|CIA_IOC_PCI_W1_BASE
mdefine_line|#define CIA_IOC_PCI_W1_BASE           (IDENT_ADDR + 0x8760000500UL)
DECL|macro|CIA_IOC_PCI_W1_MASK
mdefine_line|#define CIA_IOC_PCI_W1_MASK           (IDENT_ADDR + 0x8760000540UL)
DECL|macro|CIA_IOC_PCI_T1_BASE
mdefine_line|#define CIA_IOC_PCI_T1_BASE           (IDENT_ADDR + 0x8760000580UL)
DECL|macro|CIA_IOC_PCI_W2_BASE
mdefine_line|#define CIA_IOC_PCI_W2_BASE           (IDENT_ADDR + 0x8760000600UL)
DECL|macro|CIA_IOC_PCI_W2_MASK
mdefine_line|#define CIA_IOC_PCI_W2_MASK           (IDENT_ADDR + 0x8760000640UL)
DECL|macro|CIA_IOC_PCI_T2_BASE
mdefine_line|#define CIA_IOC_PCI_T2_BASE           (IDENT_ADDR + 0x8760000680UL)
DECL|macro|CIA_IOC_PCI_W3_BASE
mdefine_line|#define CIA_IOC_PCI_W3_BASE           (IDENT_ADDR + 0x8760000700UL)
DECL|macro|CIA_IOC_PCI_W3_MASK
mdefine_line|#define CIA_IOC_PCI_W3_MASK           (IDENT_ADDR + 0x8760000740UL)
DECL|macro|CIA_IOC_PCI_T3_BASE
mdefine_line|#define CIA_IOC_PCI_T3_BASE           (IDENT_ADDR + 0x8760000780UL)
multiline_comment|/*&n; * 21171-CA System configuration registers (p4-3)&n; */
DECL|macro|CIA_IOC_MCR
mdefine_line|#define CIA_IOC_MCR                   (IDENT_ADDR + 0x8750000000UL)
DECL|macro|CIA_IOC_MBA0
mdefine_line|#define CIA_IOC_MBA0                  (IDENT_ADDR + 0x8750000600UL)
DECL|macro|CIA_IOC_MBA2
mdefine_line|#define CIA_IOC_MBA2                  (IDENT_ADDR + 0x8750000680UL)
DECL|macro|CIA_IOC_MBA4
mdefine_line|#define CIA_IOC_MBA4                  (IDENT_ADDR + 0x8750000700UL)
DECL|macro|CIA_IOC_MBA6
mdefine_line|#define CIA_IOC_MBA6                  (IDENT_ADDR + 0x8750000780UL)
DECL|macro|CIA_IOC_MBA8
mdefine_line|#define CIA_IOC_MBA8                  (IDENT_ADDR + 0x8750000800UL)
DECL|macro|CIA_IOC_MBAA
mdefine_line|#define CIA_IOC_MBAA                  (IDENT_ADDR + 0x8750000880UL)
DECL|macro|CIA_IOC_MBAC
mdefine_line|#define CIA_IOC_MBAC                  (IDENT_ADDR + 0x8750000900UL)
DECL|macro|CIA_IOC_MBAE
mdefine_line|#define CIA_IOC_MBAE                  (IDENT_ADDR + 0x8750000980UL)
DECL|macro|CIA_IOC_TMG0
mdefine_line|#define CIA_IOC_TMG0                  (IDENT_ADDR + 0x8750000B00UL)
DECL|macro|CIA_IOC_TMG1
mdefine_line|#define CIA_IOC_TMG1                  (IDENT_ADDR + 0x8750000B40UL)
DECL|macro|CIA_IOC_TMG2
mdefine_line|#define CIA_IOC_TMG2                  (IDENT_ADDR + 0x8750000B80UL)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|CIA_IACK_SC
mdefine_line|#define CIA_IACK_SC&t;&t;        (IDENT_ADDR + 0x8720000000UL)
DECL|macro|CIA_CONF
mdefine_line|#define CIA_CONF&t;&t;        (IDENT_ADDR + 0x8700000000UL)
DECL|macro|CIA_IO
mdefine_line|#define CIA_IO&t;&t;&t;&t;(IDENT_ADDR + 0x8580000000UL)
DECL|macro|CIA_SPARSE_MEM
mdefine_line|#define CIA_SPARSE_MEM&t;&t;&t;(IDENT_ADDR + 0x8000000000UL)
DECL|macro|CIA_SPARSE_MEM_R2
mdefine_line|#define CIA_SPARSE_MEM_R2&t;&t;(IDENT_ADDR + 0x8400000000UL)
DECL|macro|CIA_SPARSE_MEM_R3
mdefine_line|#define CIA_SPARSE_MEM_R3&t;&t;(IDENT_ADDR + 0x8500000000UL)
DECL|macro|CIA_DENSE_MEM
mdefine_line|#define CIA_DENSE_MEM&t;&t;        (IDENT_ADDR + 0x8600000000UL)
multiline_comment|/*&n; * ALCOR&squot;s GRU ASIC registers&n; */
DECL|macro|GRU_INT_REQ
mdefine_line|#define GRU_INT_REQ&t;&t;&t;(IDENT_ADDR + 0x8780000000UL)
DECL|macro|GRU_INT_MASK
mdefine_line|#define GRU_INT_MASK&t;&t;&t;(IDENT_ADDR + 0x8780000040UL)
DECL|macro|GRU_INT_EDGE
mdefine_line|#define GRU_INT_EDGE&t;&t;&t;(IDENT_ADDR + 0x8780000080UL)
DECL|macro|GRU_INT_HILO
mdefine_line|#define GRU_INT_HILO&t;&t;&t;(IDENT_ADDR + 0x87800000C0UL)
DECL|macro|GRU_INT_CLEAR
mdefine_line|#define GRU_INT_CLEAR&t;&t;&t;(IDENT_ADDR + 0x8780000100UL)
DECL|macro|GRU_CACHE_CNFG
mdefine_line|#define GRU_CACHE_CNFG&t;&t;&t;(IDENT_ADDR + 0x8780000200UL)
DECL|macro|GRU_SCR
mdefine_line|#define GRU_SCR&t;&t;&t;&t;(IDENT_ADDR + 0x8780000300UL)
DECL|macro|GRU_LED
mdefine_line|#define GRU_LED&t;&t;&t;&t;(IDENT_ADDR + 0x8780000800UL)
DECL|macro|GRU_RESET
mdefine_line|#define GRU_RESET&t;&t;&t;(IDENT_ADDR + 0x8780000900UL)
DECL|macro|ALCOR_GRU_INT_REQ_BITS
mdefine_line|#define ALCOR_GRU_INT_REQ_BITS&t;&t;0x800fffffUL
DECL|macro|XLT_GRU_INT_REQ_BITS
mdefine_line|#define XLT_GRU_INT_REQ_BITS&t;&t;0x80003fffUL
DECL|macro|GRU_INT_REQ_BITS
mdefine_line|#define GRU_INT_REQ_BITS&t;&t;(alpha_mv.sys.cia.gru_int_req_bits+0)
multiline_comment|/*&n; * Bit definitions for I/O Controller status register 0:&n; */
DECL|macro|CIA_IOC_STAT0_CMD
mdefine_line|#define CIA_IOC_STAT0_CMD&t;&t;0xf
DECL|macro|CIA_IOC_STAT0_ERR
mdefine_line|#define CIA_IOC_STAT0_ERR&t;&t;(1&lt;&lt;4)
DECL|macro|CIA_IOC_STAT0_LOST
mdefine_line|#define CIA_IOC_STAT0_LOST&t;&t;(1&lt;&lt;5)
DECL|macro|CIA_IOC_STAT0_THIT
mdefine_line|#define CIA_IOC_STAT0_THIT&t;&t;(1&lt;&lt;6)
DECL|macro|CIA_IOC_STAT0_TREF
mdefine_line|#define CIA_IOC_STAT0_TREF&t;&t;(1&lt;&lt;7)
DECL|macro|CIA_IOC_STAT0_CODE_SHIFT
mdefine_line|#define CIA_IOC_STAT0_CODE_SHIFT&t;8
DECL|macro|CIA_IOC_STAT0_CODE_MASK
mdefine_line|#define CIA_IOC_STAT0_CODE_MASK&t;&t;0x7
DECL|macro|CIA_IOC_STAT0_P_NBR_SHIFT
mdefine_line|#define CIA_IOC_STAT0_P_NBR_SHIFT&t;13
DECL|macro|CIA_IOC_STAT0_P_NBR_MASK
mdefine_line|#define CIA_IOC_STAT0_P_NBR_MASK&t;0x7ffff
DECL|macro|CIA_HAE_ADDRESS
mdefine_line|#define CIA_HAE_ADDRESS&t;                CIA_IOC_HAE_MEM
multiline_comment|/*&n; * Data structure for handling CIA machine checks.&n; */
multiline_comment|/* EV5-specific info.  */
DECL|struct|el_CIA_procdata
r_struct
id|el_CIA_procdata
(brace
DECL|member|shadow
r_int
r_int
id|shadow
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* PALmode shadow registers */
DECL|member|paltemp
r_int
r_int
id|paltemp
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* PAL temporary registers */
multiline_comment|/* EV5-specific fields */
DECL|member|exc_addr
r_int
r_int
id|exc_addr
suffix:semicolon
multiline_comment|/* Address of excepting instruction. */
DECL|member|exc_sum
r_int
r_int
id|exc_sum
suffix:semicolon
multiline_comment|/* Summary of arithmetic traps. */
DECL|member|exc_mask
r_int
r_int
id|exc_mask
suffix:semicolon
multiline_comment|/* Exception mask (from exc_sum). */
DECL|member|exc_base
r_int
r_int
id|exc_base
suffix:semicolon
multiline_comment|/* PALbase at time of exception. */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* Interrupt summary register. */
DECL|member|icsr
r_int
r_int
id|icsr
suffix:semicolon
multiline_comment|/* Ibox control register. */
DECL|member|ic_perr_stat
r_int
r_int
id|ic_perr_stat
suffix:semicolon
DECL|member|dc_perr_stat
r_int
r_int
id|dc_perr_stat
suffix:semicolon
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* Effective VA of fault or miss. */
DECL|member|mm_stat
r_int
r_int
id|mm_stat
suffix:semicolon
DECL|member|sc_addr
r_int
r_int
id|sc_addr
suffix:semicolon
DECL|member|sc_stat
r_int
r_int
id|sc_stat
suffix:semicolon
DECL|member|bc_tag_addr
r_int
r_int
id|bc_tag_addr
suffix:semicolon
DECL|member|ei_addr
r_int
r_int
id|ei_addr
suffix:semicolon
DECL|member|fill_syn
r_int
r_int
id|fill_syn
suffix:semicolon
DECL|member|ei_stat
r_int
r_int
id|ei_stat
suffix:semicolon
DECL|member|ld_lock
r_int
r_int
id|ld_lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* System-specific info.  */
DECL|struct|el_CIA_sysdata_mcheck
r_struct
id|el_CIA_sysdata_mcheck
(brace
DECL|member|coma_gcr
r_int
r_int
id|coma_gcr
suffix:semicolon
DECL|member|coma_edsr
r_int
r_int
id|coma_edsr
suffix:semicolon
DECL|member|coma_ter
r_int
r_int
id|coma_ter
suffix:semicolon
DECL|member|coma_elar
r_int
r_int
id|coma_elar
suffix:semicolon
DECL|member|coma_ehar
r_int
r_int
id|coma_ehar
suffix:semicolon
DECL|member|coma_ldlr
r_int
r_int
id|coma_ldlr
suffix:semicolon
DECL|member|coma_ldhr
r_int
r_int
id|coma_ldhr
suffix:semicolon
DECL|member|coma_base0
r_int
r_int
id|coma_base0
suffix:semicolon
DECL|member|coma_base1
r_int
r_int
id|coma_base1
suffix:semicolon
DECL|member|coma_base2
r_int
r_int
id|coma_base2
suffix:semicolon
DECL|member|coma_cnfg0
r_int
r_int
id|coma_cnfg0
suffix:semicolon
DECL|member|coma_cnfg1
r_int
r_int
id|coma_cnfg1
suffix:semicolon
DECL|member|coma_cnfg2
r_int
r_int
id|coma_cnfg2
suffix:semicolon
DECL|member|epic_dcsr
r_int
r_int
id|epic_dcsr
suffix:semicolon
DECL|member|epic_pear
r_int
r_int
id|epic_pear
suffix:semicolon
DECL|member|epic_sear
r_int
r_int
id|epic_sear
suffix:semicolon
DECL|member|epic_tbr1
r_int
r_int
id|epic_tbr1
suffix:semicolon
DECL|member|epic_tbr2
r_int
r_int
id|epic_tbr2
suffix:semicolon
DECL|member|epic_pbr1
r_int
r_int
id|epic_pbr1
suffix:semicolon
DECL|member|epic_pbr2
r_int
r_int
id|epic_pbr2
suffix:semicolon
DECL|member|epic_pmr1
r_int
r_int
id|epic_pmr1
suffix:semicolon
DECL|member|epic_pmr2
r_int
r_int
id|epic_pmr2
suffix:semicolon
DECL|member|epic_harx1
r_int
r_int
id|epic_harx1
suffix:semicolon
DECL|member|epic_harx2
r_int
r_int
id|epic_harx2
suffix:semicolon
DECL|member|epic_pmlt
r_int
r_int
id|epic_pmlt
suffix:semicolon
DECL|member|epic_tag0
r_int
r_int
id|epic_tag0
suffix:semicolon
DECL|member|epic_tag1
r_int
r_int
id|epic_tag1
suffix:semicolon
DECL|member|epic_tag2
r_int
r_int
id|epic_tag2
suffix:semicolon
DECL|member|epic_tag3
r_int
r_int
id|epic_tag3
suffix:semicolon
DECL|member|epic_tag4
r_int
r_int
id|epic_tag4
suffix:semicolon
DECL|member|epic_tag5
r_int
r_int
id|epic_tag5
suffix:semicolon
DECL|member|epic_tag6
r_int
r_int
id|epic_tag6
suffix:semicolon
DECL|member|epic_tag7
r_int
r_int
id|epic_tag7
suffix:semicolon
DECL|member|epic_data0
r_int
r_int
id|epic_data0
suffix:semicolon
DECL|member|epic_data1
r_int
r_int
id|epic_data1
suffix:semicolon
DECL|member|epic_data2
r_int
r_int
id|epic_data2
suffix:semicolon
DECL|member|epic_data3
r_int
r_int
id|epic_data3
suffix:semicolon
DECL|member|epic_data4
r_int
r_int
id|epic_data4
suffix:semicolon
DECL|member|epic_data5
r_int
r_int
id|epic_data5
suffix:semicolon
DECL|member|epic_data6
r_int
r_int
id|epic_data6
suffix:semicolon
DECL|member|epic_data7
r_int
r_int
id|epic_data7
suffix:semicolon
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
DECL|function|cia_virt_to_bus
id|__EXTERN_INLINE
r_int
r_int
id|cia_virt_to_bus
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
id|CIA_DMA_WIN_BASE
suffix:semicolon
)brace
DECL|function|cia_bus_to_virt
id|__EXTERN_INLINE
r_void
op_star
id|cia_bus_to_virt
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
id|CIA_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * CIA (the 2117x PCI/memory support chipset for the EV5 (21164)&n; * series of processors uses a sparse address mapping scheme to&n; * get at PCI memory and I/O.&n; */
DECL|macro|vip
mdefine_line|#define vip&t;volatile int *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|cia_inb
id|__EXTERN_INLINE
r_int
r_int
id|cia_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x00
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_outb
id|__EXTERN_INLINE
r_void
id|cia_outb
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
r_int
r_int
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cia_inw
id|__EXTERN_INLINE
r_int
r_int
id|cia_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x08
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_outw
id|__EXTERN_INLINE
r_void
id|cia_outw
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
r_int
r_int
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cia_inl
id|__EXTERN_INLINE
r_int
r_int
id|cia_inl
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
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|function|cia_outl
id|__EXTERN_INLINE
r_void
id|cia_outl
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
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x18
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
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; * &n; * For reading and writing 8 and 16 bit quantities we need to &n; * go through one of the three sparse address mapping regions&n; * and use the HAE_MEM CSR to provide some bits of the address.&n; * The following few routines use only sparse address region 1&n; * which gives 1Gbyte of accessible space which relates exactly&n; * to the amount of PCI memory mapping *into* system address space.&n; * See p 6-17 of the specification but it looks something like this:&n; *&n; * 21164 Address:&n; * &n; *          3         2         1                                                               &n; * 9876543210987654321098765432109876543210&n; * 1ZZZZ0.PCI.QW.Address............BBLL                 &n; *&n; * ZZ = SBZ&n; * BB = Byte offset&n; * LL = Transfer length&n; *&n; * PCI Address:&n; *&n; * 3         2         1                                                               &n; * 10987654321098765432109876543210&n; * HHH....PCI.QW.Address........ 00&n; *&n; * HHH = 31:29 HAE_MEM CSR&n; * &n; */
DECL|function|cia_srm_base
id|__EXTERN_INLINE
r_int
r_int
id|cia_srm_base
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|base
suffix:semicolon
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|CIA_DENSE_MEM
suffix:semicolon
)brace
macro_line|#endif
id|addr
op_sub_assign
id|CIA_DENSE_MEM
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|alpha_mv.sm_base_r1
op_logical_and
id|addr
op_le
id|alpha_mv.sm_base_r1
op_plus
id|CIA_MEM_R1_MASK
)paren
(brace
id|mask
op_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|base
op_assign
id|CIA_SPARSE_MEM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_ge
id|alpha_mv.sm_base_r2
op_logical_and
id|addr
op_le
id|alpha_mv.sm_base_r2
op_plus
id|CIA_MEM_R2_MASK
)paren
(brace
id|mask
op_assign
id|CIA_MEM_R2_MASK
suffix:semicolon
id|base
op_assign
id|CIA_SPARSE_MEM_R2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_ge
id|alpha_mv.sm_base_r3
op_logical_and
id|addr
op_le
id|alpha_mv.sm_base_r3
op_plus
id|CIA_MEM_R3_MASK
)paren
(brace
id|mask
op_assign
id|CIA_MEM_R3_MASK
suffix:semicolon
id|base
op_assign
id|CIA_SPARSE_MEM_R3
suffix:semicolon
)brace
r_else
(brace
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: address 0x%lx not covered by HAE&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
(paren
id|addr
op_amp
id|mask
)paren
op_lshift
l_int|5
)paren
op_plus
id|base
suffix:semicolon
)brace
DECL|function|cia_srm_readb
id|__EXTERN_INLINE
r_int
r_int
id|cia_srm_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|work
suffix:semicolon
r_if
c_cond
(paren
(paren
id|work
op_assign
id|cia_srm_base
c_func
(paren
id|addr
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|0xff
suffix:semicolon
id|work
op_add_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* add transfer length */
id|result
op_assign
op_star
(paren
id|vip
)paren
id|work
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_srm_readw
id|__EXTERN_INLINE
r_int
r_int
id|cia_srm_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|work
suffix:semicolon
r_if
c_cond
(paren
(paren
id|work
op_assign
id|cia_srm_base
c_func
(paren
id|addr
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|0xffff
suffix:semicolon
id|work
op_add_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* add transfer length */
id|result
op_assign
op_star
(paren
id|vip
)paren
id|work
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_srm_writeb
id|__EXTERN_INLINE
r_void
id|cia_srm_writeb
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
r_int
r_int
id|work
comma
id|w
suffix:semicolon
r_if
c_cond
(paren
(paren
id|work
op_assign
id|cia_srm_base
c_func
(paren
id|addr
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|work
op_add_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* add transfer length */
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|work
op_assign
id|w
suffix:semicolon
)brace
)brace
DECL|function|cia_srm_writew
id|__EXTERN_INLINE
r_void
id|cia_srm_writew
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
r_int
r_int
id|work
comma
id|w
suffix:semicolon
id|addr
op_sub_assign
id|CIA_DENSE_MEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|work
op_assign
id|cia_srm_base
c_func
(paren
id|addr
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|work
op_add_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* add transfer length */
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|work
op_assign
id|w
suffix:semicolon
)brace
)brace
DECL|function|cia_readb
id|__EXTERN_INLINE
r_int
r_int
id|cia_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|msb
suffix:semicolon
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Note that CIA_DENSE_MEM has no bits not masked in these &n;&t;   operations, so we don&squot;t have to subtract it back out.  */
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_SPARSE_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_readw
id|__EXTERN_INLINE
r_int
r_int
id|cia_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|msb
suffix:semicolon
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Note that CIA_DENSE_MEM has no bits not masked in these &n;&t;   operations, so we don&squot;t have to subtract it back out.  */
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_SPARSE_MEM
op_plus
l_int|0x08
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_writeb
id|__EXTERN_INLINE
r_void
id|cia_writeb
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
r_int
r_int
id|msb
comma
id|w
suffix:semicolon
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Note that CIA_DENSE_MEM has no bits not masked in these &n;&t;   operations, so we don&squot;t have to subtract it back out.  */
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_SPARSE_MEM
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|cia_writew
id|__EXTERN_INLINE
r_void
id|cia_writew
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
r_int
r_int
id|msb
comma
id|w
suffix:semicolon
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Note that CIA_DENSE_MEM has no bits not masked in these &n;&t;   operations, so we don&squot;t have to subtract it back out.  */
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|CIA_SPARSE_MEM
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|cia_readl
id|__EXTERN_INLINE
r_int
r_int
id|cia_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|cia_readq
id|__EXTERN_INLINE
r_int
r_int
id|cia_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
op_star
(paren
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|cia_writel
id|__EXTERN_INLINE
r_void
id|cia_writel
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
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|cia_writeq
id|__EXTERN_INLINE
r_void
id|cia_writeq
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
macro_line|#if __DEBUG_IOREMAP
r_if
c_cond
(paren
id|addr
op_le
l_int|0x100000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cia: 0x%lx not ioremapped (%p)&bslash;n&quot;
comma
id|addr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
op_star
(paren
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|cia_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|cia_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|CIA_DENSE_MEM
op_plus
id|addr
suffix:semicolon
)brace
DECL|function|cia_is_ioaddr
id|__EXTERN_INLINE
r_int
id|cia_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|IDENT_ADDR
op_plus
l_int|0x8000000000UL
suffix:semicolon
)brace
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus&t;cia_virt_to_bus
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt&t;cia_bus_to_virt
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;cia_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;cia_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;cia_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;cia_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;cia_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;cia_outl
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;cia_srm_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;cia_srm_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;cia_srm_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;cia_srm_writew
macro_line|#else
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;cia_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;cia_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;cia_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;cia_writew
macro_line|#endif
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;cia_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;cia_readq
DECL|macro|__writel
mdefine_line|#define __writel&t;cia_writel
DECL|macro|__writeq
mdefine_line|#define __writeq&t;cia_writeq
DECL|macro|__ioremap
mdefine_line|#define __ioremap&t;cia_ioremap
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr&t;cia_is_ioaddr
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;(__builtin_constant_p((port))?__inb(port):_inb(port))
DECL|macro|outb
mdefine_line|#define outb(x, port) &bslash;&n;(__builtin_constant_p((port))?__outb((x),(port)):_outb((x),(port)))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;(__builtin_constant_p((port))?__inw(port):_inw(port))
DECL|macro|outw
mdefine_line|#define outw(x, port) &bslash;&n;(__builtin_constant_p((port))?__outw((x),(port)):_outw((x),(port)))
DECL|macro|inl
mdefine_line|#define inl(port)&t;__inl(port)
DECL|macro|outl
mdefine_line|#define outl(x,port)&t;__outl((x),(port))
macro_line|#if !__DEBUG_IOREMAP
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl((unsigned long)(a))
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq((unsigned long)(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(unsigned long)(a))
macro_line|#endif
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_CIA__H__ */
eof
