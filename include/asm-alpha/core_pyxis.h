macro_line|#ifndef __ALPHA_PYXIS__H__
DECL|macro|__ALPHA_PYXIS__H__
mdefine_line|#define __ALPHA_PYXIS__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * PYXIS is the internal name for a core logic chipset which provides&n; * memory controller and PCI access for the 21164A chip based systems.&n; *&n; * This file is based on:&n; *&n; * Pyxis Chipset Spec&n; * 14-Jun-96&n; * Rev. X2.0&n; *&n; */
multiline_comment|/*------------------------------------------------------------------------**&n;**                                                                        **&n;**  I/O procedures                                                        **&n;**                                                                        **&n;**      inport[b|w|t|l], outport[b|w|t|l] 8:16:24:32 IO xfers             **&n;**&t;inportbxt: 8 bits only                                            **&n;**      inport:    alias of inportw                                       **&n;**      outport:   alias of outportw                                      **&n;**                                                                        **&n;**      inmem[b|w|t|l], outmem[b|w|t|l] 8:16:24:32 ISA memory xfers       **&n;**&t;inmembxt: 8 bits only                                             **&n;**      inmem:    alias of inmemw                                         **&n;**      outmem:   alias of outmemw                                        **&n;**                                                                        **&n;**------------------------------------------------------------------------*/
multiline_comment|/* PYXIS ADDRESS BIT DEFINITIONS&n; *&n; *  3333 3333 3322 2222 2222 1111 1111 11&n; *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  1                                             000&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  |&t;&t;&t;&t;&t;&t;  |&bslash;|&n; *  |                               Byte Enable --+ |&n; *  |                             Transfer Length --+&n; *  +-- IO space, not cached&n; *&n; *   Byte      Transfer&n; *   Enable    Length    Transfer  Byte    Address&n; *   adr&lt;6:5&gt;  adr&lt;4:3&gt;  Length    Enable  Adder&n; *   ---------------------------------------------&n; *      00        00      Byte      1110   0x000&n; *      01        00      Byte      1101   0x020&n; *      10        00      Byte      1011   0x040&n; *      11        00      Byte      0111   0x060&n; *&n; *      00        01      Word      1100   0x008&n; *      01        01      Word      1001   0x028 &lt;= Not supported in this code.&n; *      10        01      Word      0011   0x048&n; *&n; *      00        10      Tribyte   1000   0x010&n; *      01        10      Tribyte   0001   0x030&n; *&n; *      10        11      Longword  0000   0x058&n; *&n; *      Note that byte enables are asserted low.&n; *&n; */
DECL|macro|PYXIS_MEM_R1_MASK
mdefine_line|#define PYXIS_MEM_R1_MASK 0x1fffffff  /* SPARSE Mem region 1 mask is 29 bits */
DECL|macro|PYXIS_MEM_R2_MASK
mdefine_line|#define PYXIS_MEM_R2_MASK 0x07ffffff  /* SPARSE Mem region 2 mask is 27 bits */
DECL|macro|PYXIS_MEM_R3_MASK
mdefine_line|#define PYXIS_MEM_R3_MASK 0x03ffffff  /* SPARSE Mem region 3 mask is 26 bits */
multiline_comment|/*&n; *  General Registers&n; */
DECL|macro|PYXIS_REV
mdefine_line|#define PYXIS_REV&t;&t;&t;(IDENT_ADDR + 0x8740000080UL)
DECL|macro|PYXIS_PCI_LAT
mdefine_line|#define PYXIS_PCI_LAT&t;&t;&t;(IDENT_ADDR + 0x87400000C0UL)
DECL|macro|PYXIS_CTRL
mdefine_line|#define PYXIS_CTRL&t;&t;&t;(IDENT_ADDR + 0x8740000100UL)
DECL|macro|PYXIS_CTRL1
mdefine_line|#define PYXIS_CTRL1&t;&t;&t;(IDENT_ADDR + 0x8740000140UL)
DECL|macro|PYXIS_FLASH_CTRL
mdefine_line|#define PYXIS_FLASH_CTRL&t;&t;(IDENT_ADDR + 0x8740000200UL)
DECL|macro|PYXIS_HAE_MEM
mdefine_line|#define PYXIS_HAE_MEM&t;&t;&t;(IDENT_ADDR + 0x8740000400UL)
DECL|macro|PYXIS_HAE_IO
mdefine_line|#define PYXIS_HAE_IO&t;&t;&t;(IDENT_ADDR + 0x8740000440UL)
DECL|macro|PYXIS_CFG
mdefine_line|#define PYXIS_CFG&t;&t;&t;(IDENT_ADDR + 0x8740000480UL)
multiline_comment|/*&n; * Diagnostic Registers&n; */
DECL|macro|PYXIS_DIAG
mdefine_line|#define PYXIS_DIAG&t;&t;&t;(IDENT_ADDR + 0x8740002000UL)
DECL|macro|PYXIS_DIAG_CHECK
mdefine_line|#define PYXIS_DIAG_CHECK&t;&t;(IDENT_ADDR + 0x8740003000UL)
multiline_comment|/*&n; * Performance Monitor registers&n; */
DECL|macro|PYXIS_PERF_MONITOR
mdefine_line|#define PYXIS_PERF_MONITOR&t;&t;(IDENT_ADDR + 0x8740004000UL)
DECL|macro|PYXIS_PERF_CONTROL
mdefine_line|#define PYXIS_PERF_CONTROL&t;&t;(IDENT_ADDR + 0x8740004040UL)
multiline_comment|/*&n; * Error registers&n; */
DECL|macro|PYXIS_ERR
mdefine_line|#define PYXIS_ERR&t;&t;&t;(IDENT_ADDR + 0x8740008200UL)
DECL|macro|PYXIS_STAT
mdefine_line|#define PYXIS_STAT&t;&t;&t;(IDENT_ADDR + 0x8740008240UL)
DECL|macro|PYXIS_ERR_MASK
mdefine_line|#define PYXIS_ERR_MASK&t;&t;&t;(IDENT_ADDR + 0x8740008280UL)
DECL|macro|PYXIS_SYN
mdefine_line|#define PYXIS_SYN&t;&t;&t;(IDENT_ADDR + 0x8740008300UL)
DECL|macro|PYXIS_ERR_DATA
mdefine_line|#define PYXIS_ERR_DATA&t;&t;&t;(IDENT_ADDR + 0x8740008308UL)
DECL|macro|PYXIS_MEAR
mdefine_line|#define PYXIS_MEAR&t;&t;&t;(IDENT_ADDR + 0x8740008400UL)
DECL|macro|PYXIS_MESR
mdefine_line|#define PYXIS_MESR&t;&t;&t;(IDENT_ADDR + 0x8740008440UL)
DECL|macro|PYXIS_PCI_ERR0
mdefine_line|#define PYXIS_PCI_ERR0&t;&t;&t;(IDENT_ADDR + 0x8740008800UL)
DECL|macro|PYXIS_PCI_ERR1
mdefine_line|#define PYXIS_PCI_ERR1&t;&t;&t;(IDENT_ADDR + 0x8740008840UL)
DECL|macro|PYXIS_PCI_ERR2
mdefine_line|#define PYXIS_PCI_ERR2&t;&t;&t;(IDENT_ADDR + 0x8740008880UL)
multiline_comment|/*&n; * PCI Address Translation Registers.&n; */
DECL|macro|PYXIS_TBIA
mdefine_line|#define PYXIS_TBIA&t;&t;&t;(IDENT_ADDR + 0x8760000100UL)
DECL|macro|PYXIS_W0_BASE
mdefine_line|#define PYXIS_W0_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000400UL)
DECL|macro|PYXIS_W0_MASK
mdefine_line|#define PYXIS_W0_MASK&t;&t;&t;(IDENT_ADDR + 0x8760000440UL)
DECL|macro|PYXIS_T0_BASE
mdefine_line|#define PYXIS_T0_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000480UL)
DECL|macro|PYXIS_W1_BASE
mdefine_line|#define PYXIS_W1_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000500UL)
DECL|macro|PYXIS_W1_MASK
mdefine_line|#define PYXIS_W1_MASK&t;&t;&t;(IDENT_ADDR + 0x8760000540UL)
DECL|macro|PYXIS_T1_BASE
mdefine_line|#define PYXIS_T1_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000580UL)
DECL|macro|PYXIS_W2_BASE
mdefine_line|#define PYXIS_W2_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000600UL)
DECL|macro|PYXIS_W2_MASK
mdefine_line|#define PYXIS_W2_MASK&t;&t;&t;(IDENT_ADDR + 0x8760000640UL)
DECL|macro|PYXIS_T2_BASE
mdefine_line|#define PYXIS_T2_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000680UL)
DECL|macro|PYXIS_W3_BASE
mdefine_line|#define PYXIS_W3_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000700UL)
DECL|macro|PYXIS_W3_MASK
mdefine_line|#define PYXIS_W3_MASK&t;&t;&t;(IDENT_ADDR + 0x8760000740UL)
DECL|macro|PYXIS_T3_BASE
mdefine_line|#define PYXIS_T3_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000780UL)
multiline_comment|/*&n; * Memory Control registers&n; */
DECL|macro|PYXIS_MCR
mdefine_line|#define PYXIS_MCR&t;&t;&t;(IDENT_ADDR + 0x8750000000UL)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|PYXIS_IACK_SC
mdefine_line|#define PYXIS_IACK_SC&t;&t;        (IDENT_ADDR + 0x8720000000UL)
DECL|macro|PYXIS_CONF
mdefine_line|#define PYXIS_CONF&t;&t;        (IDENT_ADDR + 0x8700000000UL)
DECL|macro|PYXIS_IO
mdefine_line|#define PYXIS_IO&t;&t;&t;(IDENT_ADDR + 0x8580000000UL)
DECL|macro|PYXIS_SPARSE_MEM
mdefine_line|#define PYXIS_SPARSE_MEM&t;&t;(IDENT_ADDR + 0x8000000000UL)
DECL|macro|PYXIS_SPARSE_MEM_R2
mdefine_line|#define PYXIS_SPARSE_MEM_R2&t;&t;(IDENT_ADDR + 0x8400000000UL)
DECL|macro|PYXIS_SPARSE_MEM_R3
mdefine_line|#define PYXIS_SPARSE_MEM_R3&t;&t;(IDENT_ADDR + 0x8500000000UL)
DECL|macro|PYXIS_DENSE_MEM
mdefine_line|#define PYXIS_DENSE_MEM&t;&t;        (IDENT_ADDR + 0x8600000000UL)
multiline_comment|/*&n; * Byte/Word PCI Memory Spaces:&n; */
DECL|macro|PYXIS_BW_MEM
mdefine_line|#define PYXIS_BW_MEM&t;&t;&t;(IDENT_ADDR + 0x8800000000UL)
DECL|macro|PYXIS_BW_IO
mdefine_line|#define PYXIS_BW_IO&t;&t;&t;(IDENT_ADDR + 0x8900000000UL)
DECL|macro|PYXIS_BW_CFG_0
mdefine_line|#define PYXIS_BW_CFG_0&t;&t;&t;(IDENT_ADDR + 0x8a00000000UL)
DECL|macro|PYXIS_BW_CFG_1
mdefine_line|#define PYXIS_BW_CFG_1&t;&t;&t;(IDENT_ADDR + 0x8b00000000UL)
multiline_comment|/*&n; * Interrupt Control registers&n; */
DECL|macro|PYXIS_INT_REQ
mdefine_line|#define PYXIS_INT_REQ&t;&t;&t;(IDENT_ADDR + 0x87A0000000UL)
DECL|macro|PYXIS_INT_MASK
mdefine_line|#define PYXIS_INT_MASK&t;&t;&t;(IDENT_ADDR + 0x87A0000040UL)
DECL|macro|PYXIS_INT_HILO
mdefine_line|#define PYXIS_INT_HILO&t;&t;&t;(IDENT_ADDR + 0x87A00000C0UL)
DECL|macro|PYXIS_INT_ROUTE
mdefine_line|#define PYXIS_INT_ROUTE&t;&t;&t;(IDENT_ADDR + 0x87A0000140UL)
DECL|macro|PYXIS_GPO
mdefine_line|#define PYXIS_GPO&t;&t;&t;(IDENT_ADDR + 0x87A0000180UL)
DECL|macro|PYXIS_INT_CNFG
mdefine_line|#define PYXIS_INT_CNFG&t;&t;&t;(IDENT_ADDR + 0x87A00001C0UL)
DECL|macro|PYXIS_RT_COUNT
mdefine_line|#define PYXIS_RT_COUNT&t;&t;&t;(IDENT_ADDR + 0x87A0000200UL)
DECL|macro|PYXIS_INT_TIME
mdefine_line|#define PYXIS_INT_TIME&t;&t;&t;(IDENT_ADDR + 0x87A0000240UL)
DECL|macro|PYXIS_IIC_CTRL
mdefine_line|#define PYXIS_IIC_CTRL&t;&t;&t;(IDENT_ADDR + 0x87A00002C0UL)
DECL|macro|PYXIS_RESET
mdefine_line|#define PYXIS_RESET&t;&t;&t;(IDENT_ADDR + 0x8780000900UL)
multiline_comment|/*&n; * Bit definitions for I/O Controller status register 0:&n; */
DECL|macro|PYXIS_STAT0_CMD
mdefine_line|#define PYXIS_STAT0_CMD&t;&t;&t;0xf
DECL|macro|PYXIS_STAT0_ERR
mdefine_line|#define PYXIS_STAT0_ERR&t;&t;&t;(1&lt;&lt;4)
DECL|macro|PYXIS_STAT0_LOST
mdefine_line|#define PYXIS_STAT0_LOST&t;&t;(1&lt;&lt;5)
DECL|macro|PYXIS_STAT0_THIT
mdefine_line|#define PYXIS_STAT0_THIT&t;&t;(1&lt;&lt;6)
DECL|macro|PYXIS_STAT0_TREF
mdefine_line|#define PYXIS_STAT0_TREF&t;&t;(1&lt;&lt;7)
DECL|macro|PYXIS_STAT0_CODE_SHIFT
mdefine_line|#define PYXIS_STAT0_CODE_SHIFT&t;&t;8
DECL|macro|PYXIS_STAT0_CODE_MASK
mdefine_line|#define PYXIS_STAT0_CODE_MASK&t;&t;0x7
DECL|macro|PYXIS_STAT0_P_NBR_SHIFT
mdefine_line|#define PYXIS_STAT0_P_NBR_SHIFT&t;&t;13
DECL|macro|PYXIS_STAT0_P_NBR_MASK
mdefine_line|#define PYXIS_STAT0_P_NBR_MASK&t;&t;0x7ffff
DECL|macro|PYXIS_HAE_ADDRESS
mdefine_line|#define PYXIS_HAE_ADDRESS                PYXIS_HAE_MEM
multiline_comment|/*&n; * Data structure for handling PYXIS machine checks:&n; */
DECL|struct|el_PYXIS_sysdata_mcheck
r_struct
id|el_PYXIS_sysdata_mcheck
(brace
macro_line|#if 0
multiline_comment|/* ??? Where did this come from.  It appears to bear no&n;&t;   relation to the pyxis logout written in the milo sources.&n;&t;   Who knows what happens in the srm console... */
id|u_long
id|coma_gcr
suffix:semicolon
id|u_long
id|coma_edsr
suffix:semicolon
id|u_long
id|coma_ter
suffix:semicolon
id|u_long
id|coma_elar
suffix:semicolon
id|u_long
id|coma_ehar
suffix:semicolon
id|u_long
id|coma_ldlr
suffix:semicolon
id|u_long
id|coma_ldhr
suffix:semicolon
id|u_long
id|coma_base0
suffix:semicolon
id|u_long
id|coma_base1
suffix:semicolon
id|u_long
id|coma_base2
suffix:semicolon
id|u_long
id|coma_cnfg0
suffix:semicolon
id|u_long
id|coma_cnfg1
suffix:semicolon
id|u_long
id|coma_cnfg2
suffix:semicolon
id|u_long
id|epic_dcsr
suffix:semicolon
id|u_long
id|epic_pear
suffix:semicolon
id|u_long
id|epic_sear
suffix:semicolon
id|u_long
id|epic_tbr1
suffix:semicolon
id|u_long
id|epic_tbr2
suffix:semicolon
id|u_long
id|epic_pbr1
suffix:semicolon
id|u_long
id|epic_pbr2
suffix:semicolon
id|u_long
id|epic_pmr1
suffix:semicolon
id|u_long
id|epic_pmr2
suffix:semicolon
id|u_long
id|epic_harx1
suffix:semicolon
id|u_long
id|epic_harx2
suffix:semicolon
id|u_long
id|epic_pmlt
suffix:semicolon
id|u_long
id|epic_tag0
suffix:semicolon
id|u_long
id|epic_tag1
suffix:semicolon
id|u_long
id|epic_tag2
suffix:semicolon
id|u_long
id|epic_tag3
suffix:semicolon
id|u_long
id|epic_tag4
suffix:semicolon
id|u_long
id|epic_tag5
suffix:semicolon
id|u_long
id|epic_tag6
suffix:semicolon
id|u_long
id|epic_tag7
suffix:semicolon
id|u_long
id|epic_data0
suffix:semicolon
id|u_long
id|epic_data1
suffix:semicolon
id|u_long
id|epic_data2
suffix:semicolon
id|u_long
id|epic_data3
suffix:semicolon
id|u_long
id|epic_data4
suffix:semicolon
id|u_long
id|epic_data5
suffix:semicolon
id|u_long
id|epic_data6
suffix:semicolon
id|u_long
id|epic_data7
suffix:semicolon
macro_line|#else
DECL|member|cpu_err0
r_int
r_int
id|cpu_err0
suffix:semicolon
DECL|member|cpu_err1
r_int
r_int
id|cpu_err1
suffix:semicolon
DECL|member|cia_err
r_int
r_int
id|cia_err
suffix:semicolon
DECL|member|cia_stat
r_int
r_int
id|cia_stat
suffix:semicolon
DECL|member|err_mask
r_int
r_int
id|err_mask
suffix:semicolon
DECL|member|cia_syn
r_int
r_int
id|cia_syn
suffix:semicolon
DECL|member|mem_err0
r_int
r_int
id|mem_err0
suffix:semicolon
DECL|member|mem_err1
r_int
r_int
id|mem_err1
suffix:semicolon
DECL|member|pci_err0
r_int
r_int
id|pci_err0
suffix:semicolon
DECL|member|pci_err1
r_int
r_int
id|pci_err1
suffix:semicolon
DECL|member|pci_err2
r_int
r_int
id|pci_err2
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * PYXIS, the 21174 PCI/memory support chipset for the EV56 (21164A)&n; * and PCA56 (21164PC) processors, can use either a sparse address&n; * mapping scheme, or the so-called byte-word PCI address space, to&n; * get at PCI memory and I/O.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vip
mdefine_line|#define vip&t;volatile int *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|pyxis_inb
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* ??? I wish I could get rid of this.  But there&squot;s no ioremap&n;&t;   equivalent for I/O space.  PCI I/O can be forced into the&n;&t;   PYXIS I/O region, but that doesn&squot;t take care of legacy ISA crap.  */
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
id|PYXIS_BW_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|pyxis_outb
id|__EXTERN_INLINE
r_void
id|pyxis_outb
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
id|PYXIS_BW_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pyxis_inw
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_inw
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
id|PYXIS_BW_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|pyxis_outw
id|__EXTERN_INLINE
r_void
id|pyxis_outw
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
id|PYXIS_BW_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pyxis_inl
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_inl
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
id|PYXIS_BW_IO
)paren
suffix:semicolon
)brace
DECL|function|pyxis_outl
id|__EXTERN_INLINE
r_void
id|pyxis_outl
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
id|PYXIS_BW_IO
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
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; *&n; * For reading and writing 8 and 16 bit quantities we need to&n; * go through one of the three sparse address mapping regions&n; * and use the HAE_MEM CSR to provide some bits of the address.&n; * The following few routines use only sparse address region 1&n; * which gives 1Gbyte of accessible space which relates exactly&n; * to the amount of PCI memory mapping *into* system address space.&n; * See p 6-17 of the specification but it looks something like this:&n; *&n; * 21164 Address:&n; *&n; *          3         2         1&n; * 9876543210987654321098765432109876543210&n; * 1ZZZZ0.PCI.QW.Address............BBLL&n; *&n; * ZZ = SBZ&n; * BB = Byte offset&n; * LL = Transfer length&n; *&n; * PCI Address:&n; *&n; * 3         2         1&n; * 10987654321098765432109876543210&n; * HHH....PCI.QW.Address........ 00&n; *&n; * HHH = 31:29 HAE_MEM CSR&n; *&n; */
DECL|function|pyxis_readb
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_readb
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
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pyxis_readw
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_readw
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
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pyxis_readl
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_readl
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
id|addr
suffix:semicolon
)brace
DECL|function|pyxis_readq
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_readq
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
id|addr
suffix:semicolon
)brace
DECL|function|pyxis_writeb
id|__EXTERN_INLINE
r_void
id|pyxis_writeb
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
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pyxis_writew
id|__EXTERN_INLINE
r_void
id|pyxis_writew
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
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pyxis_writel
id|__EXTERN_INLINE
r_void
id|pyxis_writel
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
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|pyxis_writeq
id|__EXTERN_INLINE
r_void
id|pyxis_writeq
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
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|pyxis_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|pyxis_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_plus
id|PYXIS_BW_MEM
suffix:semicolon
)brace
DECL|function|pyxis_is_ioaddr
id|__EXTERN_INLINE
r_int
id|pyxis_is_ioaddr
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
l_int|0x8740000000UL
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;pyxis_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;pyxis_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;pyxis_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;pyxis_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;pyxis_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;pyxis_outl
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;pyxis_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;pyxis_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;pyxis_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;pyxis_writew
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;pyxis_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;pyxis_readq
DECL|macro|__writel
mdefine_line|#define __writel&t;pyxis_writel
DECL|macro|__writeq
mdefine_line|#define __writeq&t;pyxis_writeq
DECL|macro|__ioremap
mdefine_line|#define __ioremap&t;pyxis_ioremap
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr&t;pyxis_is_ioaddr
DECL|macro|inb
mdefine_line|#define inb(port)&t;&t;__inb((port))
DECL|macro|inw
mdefine_line|#define inw(port)&t;&t;__inw((port))
DECL|macro|inl
mdefine_line|#define inl(port)&t;&t;__inl((port))
DECL|macro|outb
mdefine_line|#define outb(x, port)&t;&t;__outb((x),(port))
DECL|macro|outw
mdefine_line|#define outw(x, port)&t;&t;__outw((x),(port))
DECL|macro|outl
mdefine_line|#define outl(x, port)&t;&t;__outl((x),(port))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(addr)&t;__readb((addr))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(addr)&t;__readw((addr))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(b, addr)&t;__writeb((b),(addr))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(b, addr)&t;__writew((b),(addr))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl((unsigned long)(a))
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq((unsigned long)(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_PYXIS__H__ */
eof
