macro_line|#ifndef __ALPHA_LCA__H
DECL|macro|__ALPHA_LCA__H
mdefine_line|#define __ALPHA_LCA__H
multiline_comment|/*&n; * Low Cost Alpha (LCA) definitions (these apply to 21066 and 21068,&n; * for example).&n; *&n; * This file is based on:&n; *&n; *&t;DECchip 21066 and DECchip 21068 Alpha AXP Microprocessors&n; *&t;Hardware Reference Manual; Digital Equipment Corp.; May 1994;&n; *&t;Maynard, MA; Order Number: EC-N2681-71.&n; */
multiline_comment|/*&n; * NOTE: The LCA uses a Host Address Extension (HAE) register to access&n; *&t; PCI addresses that are beyond the first 27 bits of address&n; *&t; space.  Updating the HAE requires an external cycle (and&n; *&t; a memory barrier), which tends to be slow.  Instead of updating&n; *&t; it on each sparse memory access, we keep the current HAE value&n; *&t; cached in variable cache_hae.  Only if the cached HAE differs&n; *&t; from the desired HAE value do we actually updated HAE register.&n; *&t; The HAE register is preserved by the interrupt handler entry/exit&n; *&t; code, so this scheme works even in the presence of interrupts.&n; *&n; * Dense memory space doesn&squot;t require the HAE, but is restricted to&n; * aligned 32 and 64 bit accesses.  Special Cycle and Interrupt&n; * Acknowledge cycles may also require the use of the HAE.  The LCA&n; * limits I/O address space to the bottom 24 bits of address space,&n; * but this easily covers the 16 bit ISA I/O address space.&n; */
multiline_comment|/*&n; * NOTE 2! The memory operations do not set any memory barriers, as&n; * it&squot;s not needed for cases like a frame buffer that is essentially&n; * memory-like.  You need to do them by hand if the operations depend&n; * on ordering.&n; *&n; * Similarly, the port I/O operations do a &quot;mb&quot; only after a write&n; * operation: if an mb is needed before (as in the case of doing&n; * memory mapped I/O first, and then a port I/O operation to the same&n; * device), it needs to be done by hand.&n; *&n; * After the above has bitten me 100 times, I&squot;ll give up and just do&n; * the mb all the time, but right now I&squot;m hoping this will work out.&n; * Avoiding mb&squot;s may potentially be a noticeable speed improvement,&n; * but I can&squot;t honestly say I&squot;ve tested it.&n; *&n; * Handling interrupts that need to do mb&squot;s to synchronize to&n; * non-interrupts is another fun race area.  Don&squot;t do it (because if&n; * you do, I&squot;ll have to do *everything* with interrupts disabled,&n; * ugh).&n; */
DECL|macro|LCA_DMA_WIN_BASE
mdefine_line|#define LCA_DMA_WIN_BASE&t;(1024*1024*1024)
DECL|macro|LCA_DMA_WIN_SIZE
mdefine_line|#define LCA_DMA_WIN_SIZE&t;(1024*1024*1024)
multiline_comment|/*&n; * Memory Controller registers:&n; */
DECL|macro|LCA_MEM_BCR0
mdefine_line|#define LCA_MEM_BCR0&t;&t;(IDENT_ADDR + 0x120000000UL)
DECL|macro|LCA_MEM_BCR1
mdefine_line|#define LCA_MEM_BCR1&t;&t;(IDENT_ADDR + 0x120000008UL)
DECL|macro|LCA_MEM_BCR2
mdefine_line|#define LCA_MEM_BCR2&t;&t;(IDENT_ADDR + 0x120000010UL)
DECL|macro|LCA_MEM_BCR3
mdefine_line|#define LCA_MEM_BCR3&t;&t;(IDENT_ADDR + 0x120000018UL)
DECL|macro|LCA_MEM_BMR0
mdefine_line|#define LCA_MEM_BMR0&t;&t;(IDENT_ADDR + 0x120000020UL)
DECL|macro|LCA_MEM_BMR1
mdefine_line|#define LCA_MEM_BMR1&t;&t;(IDENT_ADDR + 0x120000028UL)
DECL|macro|LCA_MEM_BMR2
mdefine_line|#define LCA_MEM_BMR2&t;&t;(IDENT_ADDR + 0x120000030UL)
DECL|macro|LCA_MEM_BMR3
mdefine_line|#define LCA_MEM_BMR3&t;&t;(IDENT_ADDR + 0x120000038UL)
DECL|macro|LCA_MEM_BTR0
mdefine_line|#define LCA_MEM_BTR0&t;&t;(IDENT_ADDR + 0x120000040UL)
DECL|macro|LCA_MEM_BTR1
mdefine_line|#define LCA_MEM_BTR1&t;&t;(IDENT_ADDR + 0x120000048UL)
DECL|macro|LCA_MEM_BTR2
mdefine_line|#define LCA_MEM_BTR2&t;&t;(IDENT_ADDR + 0x120000050UL)
DECL|macro|LCA_MEM_BTR3
mdefine_line|#define LCA_MEM_BTR3&t;&t;(IDENT_ADDR + 0x120000058UL)
DECL|macro|LCA_MEM_GTR
mdefine_line|#define LCA_MEM_GTR&t;&t;(IDENT_ADDR + 0x120000060UL)
DECL|macro|LCA_MEM_ESR
mdefine_line|#define LCA_MEM_ESR&t;&t;(IDENT_ADDR + 0x120000068UL)
DECL|macro|LCA_MEM_EAR
mdefine_line|#define LCA_MEM_EAR&t;&t;(IDENT_ADDR + 0x120000070UL)
DECL|macro|LCA_MEM_CAR
mdefine_line|#define LCA_MEM_CAR&t;&t;(IDENT_ADDR + 0x120000078UL)
DECL|macro|LCA_MEM_VGR
mdefine_line|#define LCA_MEM_VGR&t;&t;(IDENT_ADDR + 0x120000080UL)
DECL|macro|LCA_MEM_PLM
mdefine_line|#define LCA_MEM_PLM&t;&t;(IDENT_ADDR + 0x120000088UL)
DECL|macro|LCA_MEM_FOR
mdefine_line|#define LCA_MEM_FOR&t;&t;(IDENT_ADDR + 0x120000090UL)
multiline_comment|/*&n; * I/O Controller registers:&n; */
DECL|macro|LCA_IOC_HAE
mdefine_line|#define LCA_IOC_HAE&t;&t;(IDENT_ADDR + 0x180000000UL)
DECL|macro|LCA_IOC_CONF
mdefine_line|#define LCA_IOC_CONF&t;&t;(IDENT_ADDR + 0x180000020UL)
DECL|macro|LCA_IOC_STAT0
mdefine_line|#define LCA_IOC_STAT0&t;&t;(IDENT_ADDR + 0x180000040UL)
DECL|macro|LCA_IOC_STAT1
mdefine_line|#define LCA_IOC_STAT1&t;&t;(IDENT_ADDR + 0x180000060UL)
DECL|macro|LCA_IOC_TBIA
mdefine_line|#define LCA_IOC_TBIA&t;&t;(IDENT_ADDR + 0x180000080UL)
DECL|macro|LCA_IOC_TB_ENA
mdefine_line|#define LCA_IOC_TB_ENA&t;&t;(IDENT_ADDR + 0x1800000a0UL)
DECL|macro|LCA_IOC_SFT_RST
mdefine_line|#define LCA_IOC_SFT_RST&t;&t;(IDENT_ADDR + 0x1800000c0UL)
DECL|macro|LCA_IOC_PAR_DIS
mdefine_line|#define LCA_IOC_PAR_DIS&t;&t;(IDENT_ADDR + 0x1800000e0UL)
DECL|macro|LCA_IOC_W_BASE0
mdefine_line|#define LCA_IOC_W_BASE0&t;&t;(IDENT_ADDR + 0x180000100UL)
DECL|macro|LCA_IOC_W_BASE1
mdefine_line|#define LCA_IOC_W_BASE1&t;&t;(IDENT_ADDR + 0x180000120UL)
DECL|macro|LCA_IOC_W_MASK0
mdefine_line|#define LCA_IOC_W_MASK0&t;&t;(IDENT_ADDR + 0x180000140UL)
DECL|macro|LCA_IOC_W_MASK1
mdefine_line|#define LCA_IOC_W_MASK1&t;&t;(IDENT_ADDR + 0x180000160UL)
DECL|macro|LCA_IOC_T_BASE0
mdefine_line|#define LCA_IOC_T_BASE0&t;&t;(IDENT_ADDR + 0x180000180UL)
DECL|macro|LCA_IOC_T_BASE1
mdefine_line|#define LCA_IOC_T_BASE1&t;&t;(IDENT_ADDR + 0x1800001a0UL)
DECL|macro|LCA_IOC_TB_TAG0
mdefine_line|#define LCA_IOC_TB_TAG0&t;&t;(IDENT_ADDR + 0x188000000UL)
DECL|macro|LCA_IOC_TB_TAG1
mdefine_line|#define LCA_IOC_TB_TAG1&t;&t;(IDENT_ADDR + 0x188000020UL)
DECL|macro|LCA_IOC_TB_TAG2
mdefine_line|#define LCA_IOC_TB_TAG2&t;&t;(IDENT_ADDR + 0x188000040UL)
DECL|macro|LCA_IOC_TB_TAG3
mdefine_line|#define LCA_IOC_TB_TAG3&t;&t;(IDENT_ADDR + 0x188000060UL)
DECL|macro|LCA_IOC_TB_TAG4
mdefine_line|#define LCA_IOC_TB_TAG4&t;&t;(IDENT_ADDR + 0x188000070UL)
DECL|macro|LCA_IOC_TB_TAG5
mdefine_line|#define LCA_IOC_TB_TAG5&t;&t;(IDENT_ADDR + 0x1880000a0UL)
DECL|macro|LCA_IOC_TB_TAG6
mdefine_line|#define LCA_IOC_TB_TAG6&t;&t;(IDENT_ADDR + 0x1880000c0UL)
DECL|macro|LCA_IOC_TB_TAG7
mdefine_line|#define LCA_IOC_TB_TAG7&t;&t;(IDENT_ADDR + 0x1880000e0UL)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|LCA_IACK_SC
mdefine_line|#define LCA_IACK_SC&t;&t;(IDENT_ADDR + 0x1a0000000UL)
DECL|macro|LCA_CONF
mdefine_line|#define LCA_CONF&t;&t;(IDENT_ADDR + 0x1e0000000UL)
DECL|macro|LCA_IO
mdefine_line|#define LCA_IO&t;&t;&t;(IDENT_ADDR + 0x1c0000000UL)
DECL|macro|LCA_SPARSE_MEM
mdefine_line|#define LCA_SPARSE_MEM&t;&t;(IDENT_ADDR + 0x200000000UL)
DECL|macro|LCA_DENSE_MEM
mdefine_line|#define LCA_DENSE_MEM&t;&t;(IDENT_ADDR + 0x300000000UL)
multiline_comment|/*&n; * Bit definitions for I/O Controller status register 0:&n; */
DECL|macro|LCA_IOC_STAT0_CMD
mdefine_line|#define LCA_IOC_STAT0_CMD&t;&t;0xf
DECL|macro|LCA_IOC_STAT0_ERR
mdefine_line|#define LCA_IOC_STAT0_ERR&t;&t;(1&lt;&lt;4)
DECL|macro|LCA_IOC_STAT0_LOST
mdefine_line|#define LCA_IOC_STAT0_LOST&t;&t;(1&lt;&lt;5)
DECL|macro|LCA_IOC_STAT0_THIT
mdefine_line|#define LCA_IOC_STAT0_THIT&t;&t;(1&lt;&lt;6)
DECL|macro|LCA_IOC_STAT0_TREF
mdefine_line|#define LCA_IOC_STAT0_TREF&t;&t;(1&lt;&lt;7)
DECL|macro|LCA_IOC_STAT0_CODE_SHIFT
mdefine_line|#define LCA_IOC_STAT0_CODE_SHIFT&t;8
DECL|macro|LCA_IOC_STAT0_CODE_MASK
mdefine_line|#define LCA_IOC_STAT0_CODE_MASK&t;&t;0x7
DECL|macro|LCA_IOC_STAT0_P_NBR_SHIFT
mdefine_line|#define LCA_IOC_STAT0_P_NBR_SHIFT&t;13
DECL|macro|LCA_IOC_STAT0_P_NBR_MASK
mdefine_line|#define LCA_IOC_STAT0_P_NBR_MASK&t;0x7ffff
DECL|macro|HAE_ADDRESS
mdefine_line|#define HAE_ADDRESS&t;LCA_IOC_HAE
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate physical memory address as seen on (PCI) bus into&n; * a kernel virtual address and vv.&n; */
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
id|LCA_DMA_WIN_BASE
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
id|LCA_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * Unlike Jensen, the Noname machines have no concept of local&n; * I/O---everything goes over the PCI bus.&n; *&n; * There is plenty room for optimization here.  In particular,&n; * the Alpha&squot;s insb/insw/extb/extw should be useful in moving&n; * data to/from the right byte-lanes.&n; */
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
id|LCA_IO
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
id|LCA_IO
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
id|LCA_IO
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
id|LCA_IO
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
id|LCA_IO
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
id|LCA_IO
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
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; */
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
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
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
id|LCA_SPARSE_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0xffUL
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
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
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
id|LCA_SPARSE_MEM
op_plus
l_int|0x08
)paren
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0xffffUL
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
id|LCA_DENSE_MEM
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
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
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
id|LCA_SPARSE_MEM
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
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
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
id|LCA_SPARSE_MEM
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
id|LCA_DENSE_MEM
)paren
op_assign
id|b
suffix:semicolon
)brace
multiline_comment|/*&n; * Most of the above have so much overhead that it probably doesn&squot;t&n; * make sense to have them inlined (better icache behavior).&n; */
r_extern
r_int
r_int
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|inl
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|outb
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
suffix:semicolon
r_extern
r_void
id|outw
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
suffix:semicolon
r_extern
r_void
id|outl
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
suffix:semicolon
multiline_comment|/*&n; * String versions of in/out ops:&n; */
r_extern
r_void
id|insw
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsw
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_int
id|readb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|readw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|writeb
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
suffix:semicolon
r_extern
r_void
id|writew
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
suffix:semicolon
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;(__builtin_constant_p((port))?__inb(port):(inb)(port))
DECL|macro|outb
mdefine_line|#define outb(x, port) &bslash;&n;(__builtin_constant_p((port))?__outb((x),(port)):(outb)((x),(port)))
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|outb_p
mdefine_line|#define outb_p outb
DECL|macro|readl
mdefine_line|#define readl(addr)&t;__readl(addr)
DECL|macro|writel
mdefine_line|#define writel(b,addr)&t;__writel(b,addr)
DECL|macro|vuip
macro_line|#undef vuip
r_extern
r_int
r_int
id|lca_init
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
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x) (0x70 + (x))
DECL|macro|RTC_ADDR
mdefine_line|#define RTC_ADDR(x) (0x80 | (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD 0
macro_line|#endif /* __ALPHA_LCA__H */
eof
