macro_line|#ifndef __ALPHA_PYXIS__H__
DECL|macro|__ALPHA_PYXIS__H__
mdefine_line|#define __ALPHA_PYXIS__H__
macro_line|#include &lt;linux/config.h&gt; /* CONFIG_ALPHA_RUFFIAN. */
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * PYXIS is the internal name for a cor logic chipset which provides&n; * memory controller and PCI access for the 21164A chip based systems.&n; *&n; * This file is based on:&n; *&n; * Pyxis Chipset Spec&n; * 14-Jun-96&n; * Rev. X2.0&n; *&n; */
multiline_comment|/*------------------------------------------------------------------------**&n;**                                                                        **&n;**  I/O procedures                                                   **&n;**                                                                        **&n;**      inport[b|w|t|l], outport[b|w|t|l] 8:16:24:32 IO xfers             **&n;**&t;inportbxt: 8 bits only                                            **&n;**      inport:    alias of inportw                                       **&n;**      outport:   alias of outportw                                      **&n;**                                                                        **&n;**      inmem[b|w|t|l], outmem[b|w|t|l] 8:16:24:32 ISA memory xfers       **&n;**&t;inmembxt: 8 bits only                                             **&n;**      inmem:    alias of inmemw                                         **&n;**      outmem:   alias of outmemw                                        **&n;**                                                                        **&n;**------------------------------------------------------------------------*/
multiline_comment|/* CIA ADDRESS BIT DEFINITIONS&n; *&n; *  3 3 3 3|3 3 3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * |1| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |0|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ &n; *  |                                                                        &bslash;_/ &bslash;_/&n; *  |                                                                         |   |&n; *  +-- IO space, not cached.                                   Byte Enable --+   |&n; *                                                              Transfer Length --+&n; *&n; *&n; *&n; *   Byte      Transfer&n; *   Enable    Length    Transfer  Byte    Address&n; *   adr&lt;6:5&gt;  adr&lt;4:3&gt;  Length    Enable  Adder&n; *   ---------------------------------------------&n; *      00        00      Byte      1110   0x000&n; *      01        00      Byte      1101   0x020&n; *      10        00      Byte      1011   0x040&n; *      11        00      Byte      0111   0x060&n; *&n; *      00        01      Word      1100   0x008&n; *      01        01      Word      1001   0x028 &lt;= Not supported in this code.&n; *      10        01      Word      0011   0x048&n; *&n; *      00        10      Tribyte   1000   0x010&n; *      01        10      Tribyte   0001   0x030&n; *&n; *      10        11      Longword  0000   0x058&n; *&n; *      Note that byte enables are asserted low.&n; *&n; */
DECL|macro|BYTE_ENABLE_SHIFT
mdefine_line|#define BYTE_ENABLE_SHIFT 5
DECL|macro|TRANSFER_LENGTH_SHIFT
mdefine_line|#define TRANSFER_LENGTH_SHIFT 3
DECL|macro|MEM_SP1_MASK
mdefine_line|#define MEM_SP1_MASK 0x1fffffff  /* Mem sparse space 1 mask is 29 bits */
DECL|macro|PYXIS_DMA_WIN_BASE
mdefine_line|#define PYXIS_DMA_WIN_BASE&t;(1024UL*1024UL*1024UL)
DECL|macro|PYXIS_DMA_WIN_SIZE
mdefine_line|#define PYXIS_DMA_WIN_SIZE&t;(1024*1024*1024)
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
multiline_comment|/*&n; * Performance Monitor registers (p4-3)&n; */
DECL|macro|PYXIS_PERF_MONITOR
mdefine_line|#define PYXIS_PERF_MONITOR&t;&t;(IDENT_ADDR + 0x8740004000UL)
DECL|macro|PYXIS_PERF_CONTROL
mdefine_line|#define PYXIS_PERF_CONTROL&t;&t;(IDENT_ADDR + 0x8740004040UL)
multiline_comment|/*&n; * 21171-CA Error registers (p4-3)&n; */
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
multiline_comment|/*&n; *  PCI Address Translation Registers.   I&squot;ve only defined&n; * the first window fully as that&squot;s the only one that we&squot;re currently using.&n; * The other window bases are needed to disable the windows.&n; */
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
DECL|macro|PYXIS_W2_BASE
mdefine_line|#define PYXIS_W2_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000600UL)
DECL|macro|PYXIS_W3_BASE
mdefine_line|#define PYXIS_W3_BASE&t;&t;&t;(IDENT_ADDR + 0x8760000700UL)
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
DECL|macro|PYXIS_DENSE_MEM
mdefine_line|#define PYXIS_DENSE_MEM&t;&t;        (IDENT_ADDR + 0x8600000000UL)
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
DECL|macro|HAE_ADDRESS
mdefine_line|#define HAE_ADDRESS&t;                PYXIS_HAE_MEM
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate physical memory address as seen on (PCI) bus into&n; * a kernel virtual address and vv.&n; */
macro_line|#if defined(CONFIG_ALPHA_RUFFIAN)
multiline_comment|/* Ruffian doesn&squot;t do 1G PCI window.  */
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
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
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
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
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
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
id|PYXIS_DMA_WIN_BASE
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
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
id|PYXIS_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
macro_line|#endif /* RUFFIAN */
multiline_comment|/*&n; * I/O functions:&n; *&n; * PYXIS (the 2117x PCI/memory support chipset for the EV5 (21164)&n; * series of processors uses a sparse address mapping scheme to&n; * get at PCI memory and I/O.&n; */
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|function|__inb
r_extern
r_inline
r_int
r_int
id|__inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
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
id|PYXIS_IO
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__outb
r_extern
r_inline
r_void
id|__outb
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
suffix:semicolon
id|asm
(paren
l_string|&quot;insbl %2,%1,%0&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|w
)paren
suffix:colon
l_string|&quot;ri&quot;
(paren
id|addr
op_amp
l_int|0x3
)paren
comma
l_string|&quot;r&quot;
(paren
id|b
)paren
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
id|PYXIS_IO
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
DECL|function|__inw
r_extern
r_inline
r_int
r_int
id|__inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
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
id|PYXIS_IO
op_plus
l_int|0x08
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__outw
r_extern
r_inline
r_void
id|__outw
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
suffix:semicolon
id|asm
(paren
l_string|&quot;inswl %2,%1,%0&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|w
)paren
suffix:colon
l_string|&quot;ri&quot;
(paren
id|addr
op_amp
l_int|0x3
)paren
comma
l_string|&quot;r&quot;
(paren
id|b
)paren
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
id|PYXIS_IO
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
DECL|function|__inl
r_extern
r_inline
r_int
r_int
id|__inl
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
id|PYXIS_IO
op_plus
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|function|__outl
r_extern
r_inline
r_void
id|__outl
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
id|PYXIS_IO
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
DECL|function|pyxis_set_hae
r_extern
r_inline
r_void
id|pyxis_set_hae
c_func
(paren
r_int
r_int
id|new_hae
)paren
(brace
r_int
r_int
id|ipl
op_assign
id|swpipl
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|hae.cache
op_assign
id|new_hae
suffix:semicolon
op_star
id|hae.reg
op_assign
id|new_hae
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|new_hae
op_assign
op_star
id|hae.reg
suffix:semicolon
multiline_comment|/* read it to be sure it got out */
id|setipl
c_func
(paren
id|ipl
)paren
suffix:semicolon
)brace
DECL|function|__readb
r_extern
r_inline
r_int
r_int
id|__readb
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
id|shift
comma
id|msb
comma
id|work
comma
id|temp
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_lshift
l_int|3
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000UL
suffix:semicolon
id|temp
op_assign
id|addr
op_amp
id|MEM_SP1_MASK
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|pyxis_set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
id|work
op_assign
(paren
(paren
id|temp
op_lshift
l_int|5
)paren
op_plus
id|PYXIS_SPARSE_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vuip
)paren
id|work
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0x0ffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__readw
r_extern
r_inline
r_int
r_int
id|__readw
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
id|shift
comma
id|msb
comma
id|work
comma
id|temp
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_lshift
l_int|3
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000UL
suffix:semicolon
id|temp
op_assign
id|addr
op_amp
id|MEM_SP1_MASK
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|pyxis_set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
id|work
op_assign
(paren
(paren
id|temp
op_lshift
l_int|5
)paren
op_plus
id|PYXIS_SPARSE_MEM
op_plus
l_int|0x08
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vuip
)paren
id|work
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0x0ffffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__readl
r_extern
r_inline
r_int
r_int
id|__readl
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
id|PYXIS_DENSE_MEM
)paren
suffix:semicolon
)brace
DECL|function|__writeb
r_extern
r_inline
r_void
id|__writeb
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
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|MEM_SP1_MASK
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|pyxis_set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
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
id|PYXIS_SPARSE_MEM
op_plus
l_int|0x00
)paren
op_assign
id|b
op_star
l_int|0x01010101
suffix:semicolon
)brace
DECL|function|__writew
r_extern
r_inline
r_void
id|__writew
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
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|MEM_SP1_MASK
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|pyxis_set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
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
id|PYXIS_SPARSE_MEM
op_plus
l_int|0x08
)paren
op_assign
id|b
op_star
l_int|0x00010001
suffix:semicolon
)brace
DECL|function|__writel
r_extern
r_inline
r_void
id|__writel
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
id|PYXIS_DENSE_MEM
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;(__builtin_constant_p((port))?__inb(port):_inb(port))
DECL|macro|outb
mdefine_line|#define outb(x, port) &bslash;&n;(__builtin_constant_p((port))?__outb((x),(port)):_outb((x),(port)))
DECL|macro|readl
mdefine_line|#define readl(a)&t;__readl((unsigned long)(a))
DECL|macro|writel
mdefine_line|#define writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|vuip
macro_line|#undef vuip
r_extern
r_int
r_int
id|pyxis_init
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Data structure for handling PYXIS machine checks:&n; */
DECL|struct|el_PYXIS_sysdata_mcheck
r_struct
id|el_PYXIS_sysdata_mcheck
(brace
DECL|member|coma_gcr
id|u_long
id|coma_gcr
suffix:semicolon
DECL|member|coma_edsr
id|u_long
id|coma_edsr
suffix:semicolon
DECL|member|coma_ter
id|u_long
id|coma_ter
suffix:semicolon
DECL|member|coma_elar
id|u_long
id|coma_elar
suffix:semicolon
DECL|member|coma_ehar
id|u_long
id|coma_ehar
suffix:semicolon
DECL|member|coma_ldlr
id|u_long
id|coma_ldlr
suffix:semicolon
DECL|member|coma_ldhr
id|u_long
id|coma_ldhr
suffix:semicolon
DECL|member|coma_base0
id|u_long
id|coma_base0
suffix:semicolon
DECL|member|coma_base1
id|u_long
id|coma_base1
suffix:semicolon
DECL|member|coma_base2
id|u_long
id|coma_base2
suffix:semicolon
DECL|member|coma_cnfg0
id|u_long
id|coma_cnfg0
suffix:semicolon
DECL|member|coma_cnfg1
id|u_long
id|coma_cnfg1
suffix:semicolon
DECL|member|coma_cnfg2
id|u_long
id|coma_cnfg2
suffix:semicolon
DECL|member|epic_dcsr
id|u_long
id|epic_dcsr
suffix:semicolon
DECL|member|epic_pear
id|u_long
id|epic_pear
suffix:semicolon
DECL|member|epic_sear
id|u_long
id|epic_sear
suffix:semicolon
DECL|member|epic_tbr1
id|u_long
id|epic_tbr1
suffix:semicolon
DECL|member|epic_tbr2
id|u_long
id|epic_tbr2
suffix:semicolon
DECL|member|epic_pbr1
id|u_long
id|epic_pbr1
suffix:semicolon
DECL|member|epic_pbr2
id|u_long
id|epic_pbr2
suffix:semicolon
DECL|member|epic_pmr1
id|u_long
id|epic_pmr1
suffix:semicolon
DECL|member|epic_pmr2
id|u_long
id|epic_pmr2
suffix:semicolon
DECL|member|epic_harx1
id|u_long
id|epic_harx1
suffix:semicolon
DECL|member|epic_harx2
id|u_long
id|epic_harx2
suffix:semicolon
DECL|member|epic_pmlt
id|u_long
id|epic_pmlt
suffix:semicolon
DECL|member|epic_tag0
id|u_long
id|epic_tag0
suffix:semicolon
DECL|member|epic_tag1
id|u_long
id|epic_tag1
suffix:semicolon
DECL|member|epic_tag2
id|u_long
id|epic_tag2
suffix:semicolon
DECL|member|epic_tag3
id|u_long
id|epic_tag3
suffix:semicolon
DECL|member|epic_tag4
id|u_long
id|epic_tag4
suffix:semicolon
DECL|member|epic_tag5
id|u_long
id|epic_tag5
suffix:semicolon
DECL|member|epic_tag6
id|u_long
id|epic_tag6
suffix:semicolon
DECL|member|epic_tag7
id|u_long
id|epic_tag7
suffix:semicolon
DECL|member|epic_data0
id|u_long
id|epic_data0
suffix:semicolon
DECL|member|epic_data1
id|u_long
id|epic_data1
suffix:semicolon
DECL|member|epic_data2
id|u_long
id|epic_data2
suffix:semicolon
DECL|member|epic_data3
id|u_long
id|epic_data3
suffix:semicolon
DECL|member|epic_data4
id|u_long
id|epic_data4
suffix:semicolon
DECL|member|epic_data5
id|u_long
id|epic_data5
suffix:semicolon
DECL|member|epic_data6
id|u_long
id|epic_data6
suffix:semicolon
DECL|member|epic_data7
id|u_long
id|epic_data7
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_ADDR
mdefine_line|#define RTC_ADDR(x)&t;(0x80 | (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif /* __ALPHA_PYXIS__H__ */
eof
