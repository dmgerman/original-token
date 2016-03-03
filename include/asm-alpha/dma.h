multiline_comment|/*&n; * include/asm-alpha/dma.h&n; *&n; * This is essentially the same as the i386 DMA stuff, as the AlphaPCs&n; * use ISA-compatible dma.  The only extension is support for high-page&n; * registers that allow to set the top 8 bits of a 32-bit DMA address.&n; * This register should be written last when setting up a DMA address&n; * as this will also enable DMA across 64 KB boundaries.&n; */
multiline_comment|/* $Id: dma.h,v 1.7 1992/12/14 00:29:34 root Exp root $&n; * linux/include/asm/dma.h: Defines for using and allocating dma channels.&n; * Written by Hennus Bergman, 1992.&n; * High DMA channel support &amp; info by Hannu Savolainen&n; * and John Boyd, Nov. 1992.&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|dma_outb
mdefine_line|#define dma_outb&t;outb
DECL|macro|dma_inb
mdefine_line|#define dma_inb&t;&t;inb
multiline_comment|/*&n; * NOTES about DMA transfers:&n; *&n; *  controller 1: channels 0-3, byte operations, ports 00-1F&n; *  controller 2: channels 4-7, word operations, ports C0-DF&n; *&n; *  - ALL registers are 8 bits only, regardless of transfer size&n; *  - channel 4 is not used - cascades 1 into 2.&n; *  - channels 0-3 are byte - addresses/counts are for physical bytes&n; *  - channels 5-7 are word - addresses/counts are for physical words&n; *  - transfers must not cross physical 64K (0-3) or 128K (5-7) boundaries&n; *  - transfer count loaded to registers is 1 less than actual count&n; *  - controller 2 offsets are all even (2x offsets for controller 1)&n; *  - page registers for 5-7 don&squot;t use data bit 0, represent 128K pages&n; *  - page registers for 0-3 use bit 0, represent 64K pages&n; *&n; * DMA transfers are limited to the lower 16MB of _physical_ memory.  &n; * Note that addresses loaded into registers must be _physical_ addresses,&n; * not logical addresses (which may differ if paging is active).&n; *&n; *  Address mapping for channels 0-3:&n; *&n; *   A23 ... A16 A15 ... A8  A7 ... A0    (Physical addresses)&n; *    |  ...  |   |  ... |   |  ... |&n; *    |  ...  |   |  ... |   |  ... |&n; *    |  ...  |   |  ... |   |  ... |&n; *   P7  ...  P0  A7 ... A0  A7 ... A0   &n; * |    Page    | Addr MSB | Addr LSB |   (DMA registers)&n; *&n; *  Address mapping for channels 5-7:&n; *&n; *   A23 ... A17 A16 A15 ... A9 A8 A7 ... A1 A0    (Physical addresses)&n; *    |  ...  |   &bslash;   &bslash;   ... &bslash;  &bslash;  &bslash;  ... &bslash;  &bslash;&n; *    |  ...  |    &bslash;   &bslash;   ... &bslash;  &bslash;  &bslash;  ... &bslash;  (not used)&n; *    |  ...  |     &bslash;   &bslash;   ... &bslash;  &bslash;  &bslash;  ... &bslash;&n; *   P7  ...  P1 (0) A7 A6  ... A0 A7 A6 ... A0   &n; * |      Page      |  Addr MSB   |  Addr LSB  |   (DMA registers)&n; *&n; * Again, channels 5-7 transfer _physical_ words (16 bits), so addresses&n; * and counts _must_ be word-aligned (the lowest address bit is _ignored_ at&n; * the hardware level, so odd-byte transfers aren&squot;t possible).&n; *&n; * Transfer count (_not # bytes_) is limited to 64K, represented as actual&n; * count - 1 : 64K =&gt; 0xFFFF, 1 =&gt; 0x0000.  Thus, count is always 1 or more,&n; * and up to 128K bytes may be transferred on channels 5-7 in one operation. &n; *&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
multiline_comment|/* The maximum address that we can perform a DMA transfer to on Alpha XL,&n;   due to a hardware SIO (PCI&lt;-&gt;ISA bus bridge) chip limitation, is 64MB.&n;   See &lt;asm/apecs.h&gt; for more info.&n;*/
multiline_comment|/* The maximum address that we can perform a DMA transfer to on RUFFIAN,&n;   due to a hardware SIO (PCI&lt;-&gt;ISA bus bridge) chip limitation, is 16MB.&n;   See &lt;asm/pyxis.h&gt; for more info.&n;*/
multiline_comment|/* NOTE: we must define the maximum as something less than 64Mb, to prevent &n;   virt_to_bus() from returning an address in the first window, for a&n;   data area that goes beyond the 64Mb first DMA window. Sigh...&n;   We MUST coordinate the maximum with &lt;asm/apecs.h&gt; for consistency.&n;   For now, this limit is set to 48Mb...&n;*/
DECL|macro|ALPHA_XL_MAX_DMA_ADDRESS
mdefine_line|#define ALPHA_XL_MAX_DMA_ADDRESS&t;(IDENT_ADDR+0x3000000UL)
DECL|macro|ALPHA_RUFFIAN_MAX_DMA_ADDRESS
mdefine_line|#define ALPHA_RUFFIAN_MAX_DMA_ADDRESS&t;(IDENT_ADDR+0x1000000UL)
DECL|macro|ALPHA_NAUTILUS_MAX_DMA_ADDRESS
mdefine_line|#define ALPHA_NAUTILUS_MAX_DMA_ADDRESS&t;(IDENT_ADDR+0x1000000UL)
DECL|macro|ALPHA_MAX_DMA_ADDRESS
mdefine_line|#define ALPHA_MAX_DMA_ADDRESS&t;&t;(~0UL)
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|MAX_DMA_ADDRESS
macro_line|# define MAX_DMA_ADDRESS&t;&t;(alpha_mv.max_dma_address)
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_XL
DECL|macro|MAX_DMA_ADDRESS
macro_line|#  define MAX_DMA_ADDRESS&t;&t;ALPHA_XL_MAX_DMA_ADDRESS
macro_line|# elif defined(CONFIG_ALPHA_RUFFIAN)
DECL|macro|MAX_DMA_ADDRESS
macro_line|#  define MAX_DMA_ADDRESS&t;&t;ALPHA_RUFFIAN_MAX_DMA_ADDRESS
macro_line|# elif defined(CONFIG_ALPHA_NAUTILUS)
DECL|macro|MAX_DMA_ADDRESS
macro_line|#  define MAX_DMA_ADDRESS&t;&t;ALPHA_NAUTILUS_MAX_DMA_ADDRESS
macro_line|# else
DECL|macro|MAX_DMA_ADDRESS
macro_line|#  define MAX_DMA_ADDRESS&t;&t;ALPHA_MAX_DMA_ADDRESS
macro_line|# endif
macro_line|#endif
multiline_comment|/* 8237 DMA controllers */
DECL|macro|IO_DMA1_BASE
mdefine_line|#define IO_DMA1_BASE&t;0x00&t;/* 8 bit slave DMA, channels 0..3 */
DECL|macro|IO_DMA2_BASE
mdefine_line|#define IO_DMA2_BASE&t;0xC0&t;/* 16 bit master DMA, ch 4(=slave input)..7 */
multiline_comment|/* DMA controller registers */
DECL|macro|DMA1_CMD_REG
mdefine_line|#define DMA1_CMD_REG&t;&t;0x08&t;/* command register (w) */
DECL|macro|DMA1_STAT_REG
mdefine_line|#define DMA1_STAT_REG&t;&t;0x08&t;/* status register (r) */
DECL|macro|DMA1_REQ_REG
mdefine_line|#define DMA1_REQ_REG            0x09    /* request register (w) */
DECL|macro|DMA1_MASK_REG
mdefine_line|#define DMA1_MASK_REG&t;&t;0x0A&t;/* single-channel mask (w) */
DECL|macro|DMA1_MODE_REG
mdefine_line|#define DMA1_MODE_REG&t;&t;0x0B&t;/* mode register (w) */
DECL|macro|DMA1_CLEAR_FF_REG
mdefine_line|#define DMA1_CLEAR_FF_REG&t;0x0C&t;/* clear pointer flip-flop (w) */
DECL|macro|DMA1_TEMP_REG
mdefine_line|#define DMA1_TEMP_REG           0x0D    /* Temporary Register (r) */
DECL|macro|DMA1_RESET_REG
mdefine_line|#define DMA1_RESET_REG&t;&t;0x0D&t;/* Master Clear (w) */
DECL|macro|DMA1_CLR_MASK_REG
mdefine_line|#define DMA1_CLR_MASK_REG       0x0E    /* Clear Mask */
DECL|macro|DMA1_MASK_ALL_REG
mdefine_line|#define DMA1_MASK_ALL_REG       0x0F    /* all-channels mask (w) */
DECL|macro|DMA1_EXT_MODE_REG
mdefine_line|#define DMA1_EXT_MODE_REG&t;(0x400 | DMA1_MODE_REG)
DECL|macro|DMA2_CMD_REG
mdefine_line|#define DMA2_CMD_REG&t;&t;0xD0&t;/* command register (w) */
DECL|macro|DMA2_STAT_REG
mdefine_line|#define DMA2_STAT_REG&t;&t;0xD0&t;/* status register (r) */
DECL|macro|DMA2_REQ_REG
mdefine_line|#define DMA2_REQ_REG            0xD2    /* request register (w) */
DECL|macro|DMA2_MASK_REG
mdefine_line|#define DMA2_MASK_REG&t;&t;0xD4&t;/* single-channel mask (w) */
DECL|macro|DMA2_MODE_REG
mdefine_line|#define DMA2_MODE_REG&t;&t;0xD6&t;/* mode register (w) */
DECL|macro|DMA2_CLEAR_FF_REG
mdefine_line|#define DMA2_CLEAR_FF_REG&t;0xD8&t;/* clear pointer flip-flop (w) */
DECL|macro|DMA2_TEMP_REG
mdefine_line|#define DMA2_TEMP_REG           0xDA    /* Temporary Register (r) */
DECL|macro|DMA2_RESET_REG
mdefine_line|#define DMA2_RESET_REG&t;&t;0xDA&t;/* Master Clear (w) */
DECL|macro|DMA2_CLR_MASK_REG
mdefine_line|#define DMA2_CLR_MASK_REG       0xDC    /* Clear Mask */
DECL|macro|DMA2_MASK_ALL_REG
mdefine_line|#define DMA2_MASK_ALL_REG       0xDE    /* all-channels mask (w) */
DECL|macro|DMA2_EXT_MODE_REG
mdefine_line|#define DMA2_EXT_MODE_REG&t;(0x400 | DMA2_MODE_REG)
DECL|macro|DMA_ADDR_0
mdefine_line|#define DMA_ADDR_0              0x00    /* DMA address registers */
DECL|macro|DMA_ADDR_1
mdefine_line|#define DMA_ADDR_1              0x02
DECL|macro|DMA_ADDR_2
mdefine_line|#define DMA_ADDR_2              0x04
DECL|macro|DMA_ADDR_3
mdefine_line|#define DMA_ADDR_3              0x06
DECL|macro|DMA_ADDR_4
mdefine_line|#define DMA_ADDR_4              0xC0
DECL|macro|DMA_ADDR_5
mdefine_line|#define DMA_ADDR_5              0xC4
DECL|macro|DMA_ADDR_6
mdefine_line|#define DMA_ADDR_6              0xC8
DECL|macro|DMA_ADDR_7
mdefine_line|#define DMA_ADDR_7              0xCC
DECL|macro|DMA_CNT_0
mdefine_line|#define DMA_CNT_0               0x01    /* DMA count registers */
DECL|macro|DMA_CNT_1
mdefine_line|#define DMA_CNT_1               0x03
DECL|macro|DMA_CNT_2
mdefine_line|#define DMA_CNT_2               0x05
DECL|macro|DMA_CNT_3
mdefine_line|#define DMA_CNT_3               0x07
DECL|macro|DMA_CNT_4
mdefine_line|#define DMA_CNT_4               0xC2
DECL|macro|DMA_CNT_5
mdefine_line|#define DMA_CNT_5               0xC6
DECL|macro|DMA_CNT_6
mdefine_line|#define DMA_CNT_6               0xCA
DECL|macro|DMA_CNT_7
mdefine_line|#define DMA_CNT_7               0xCE
DECL|macro|DMA_PAGE_0
mdefine_line|#define DMA_PAGE_0              0x87    /* DMA page registers */
DECL|macro|DMA_PAGE_1
mdefine_line|#define DMA_PAGE_1              0x83
DECL|macro|DMA_PAGE_2
mdefine_line|#define DMA_PAGE_2              0x81
DECL|macro|DMA_PAGE_3
mdefine_line|#define DMA_PAGE_3              0x82
DECL|macro|DMA_PAGE_5
mdefine_line|#define DMA_PAGE_5              0x8B
DECL|macro|DMA_PAGE_6
mdefine_line|#define DMA_PAGE_6              0x89
DECL|macro|DMA_PAGE_7
mdefine_line|#define DMA_PAGE_7              0x8A
DECL|macro|DMA_HIPAGE_0
mdefine_line|#define DMA_HIPAGE_0&t;&t;(0x400 | DMA_PAGE_0)
DECL|macro|DMA_HIPAGE_1
mdefine_line|#define DMA_HIPAGE_1&t;&t;(0x400 | DMA_PAGE_1)
DECL|macro|DMA_HIPAGE_2
mdefine_line|#define DMA_HIPAGE_2&t;&t;(0x400 | DMA_PAGE_2)
DECL|macro|DMA_HIPAGE_3
mdefine_line|#define DMA_HIPAGE_3&t;&t;(0x400 | DMA_PAGE_3)
DECL|macro|DMA_HIPAGE_4
mdefine_line|#define DMA_HIPAGE_4&t;&t;(0x400 | DMA_PAGE_4)
DECL|macro|DMA_HIPAGE_5
mdefine_line|#define DMA_HIPAGE_5&t;&t;(0x400 | DMA_PAGE_5)
DECL|macro|DMA_HIPAGE_6
mdefine_line|#define DMA_HIPAGE_6&t;&t;(0x400 | DMA_PAGE_6)
DECL|macro|DMA_HIPAGE_7
mdefine_line|#define DMA_HIPAGE_7&t;&t;(0x400 | DMA_PAGE_7)
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;0x44&t;/* I/O to memory, no autoinit, increment, single mode */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;0x48&t;/* memory to I/O, no autoinit, increment, single mode */
DECL|macro|DMA_MODE_CASCADE
mdefine_line|#define DMA_MODE_CASCADE 0xC0   /* pass thru DREQ-&gt;HRQ, DACK&lt;-HLDA only */
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT&t;0x10
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
DECL|function|claim_dma_lock
r_static
id|__inline__
r_int
r_int
id|claim_dma_lock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|function|release_dma_lock
r_static
id|__inline__
r_void
id|release_dma_lock
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* enable/disable a specific DMA channel */
DECL|function|enable_dma
r_static
id|__inline__
r_void
id|enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|dmanr
comma
id|DMA1_MASK_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
id|dmanr
op_amp
l_int|3
comma
id|DMA2_MASK_REG
)paren
suffix:semicolon
)brace
DECL|function|disable_dma
r_static
id|__inline__
r_void
id|disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|dmanr
op_or
l_int|4
comma
id|DMA1_MASK_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_or
l_int|4
comma
id|DMA2_MASK_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; * Use this once to initialize the FF to a known state.&n; * After that, keep track of it. :-)&n; * --- In order to do that, the DMA routines below should ---&n; * --- only be used while interrupts are disabled! ---&n; */
DECL|function|clear_dma_ff
r_static
id|__inline__
r_void
id|clear_dma_ff
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA1_CLEAR_FF_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
l_int|0
comma
id|DMA2_CLEAR_FF_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* set mode (above) for a specific DMA channel */
DECL|function|set_dma_mode
r_static
id|__inline__
r_void
id|set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|mode
op_or
id|dmanr
comma
id|DMA1_MODE_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
id|mode
op_or
(paren
id|dmanr
op_amp
l_int|3
)paren
comma
id|DMA2_MODE_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* set extended mode for a specific DMA channel */
DECL|function|set_dma_ext_mode
r_static
id|__inline__
r_void
id|set_dma_ext_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|ext_mode
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
id|dma_outb
c_func
(paren
id|ext_mode
op_or
id|dmanr
comma
id|DMA1_EXT_MODE_REG
)paren
suffix:semicolon
r_else
id|dma_outb
c_func
(paren
id|ext_mode
op_or
(paren
id|dmanr
op_amp
l_int|3
)paren
comma
id|DMA2_EXT_MODE_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* Set only the page register bits of the transfer address.&n; * This is used for successive transfers when we know the contents of&n; * the lower 16 bits of the DMA current address register.&n; */
DECL|function|set_dma_page
r_static
id|__inline__
r_void
id|set_dma_page
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|pagenr
)paren
(brace
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
comma
id|DMA_PAGE_0
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
comma
id|DMA_PAGE_1
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
comma
id|DMA_PAGE_2
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
comma
id|DMA_PAGE_3
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
op_amp
l_int|0xfe
comma
id|DMA_PAGE_5
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_5
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
op_amp
l_int|0xfe
comma
id|DMA_PAGE_6
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|dma_outb
c_func
(paren
id|pagenr
op_amp
l_int|0xfe
comma
id|DMA_PAGE_7
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|pagenr
op_rshift
l_int|8
)paren
comma
id|DMA_HIPAGE_7
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Set transfer address &amp; page bits for specific DMA channel.&n; * Assumes dma flipflop is clear.&n; */
DECL|function|set_dma_addr
r_static
id|__inline__
r_void
id|set_dma_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
(brace
id|dma_outb
c_func
(paren
id|a
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
id|IO_DMA1_BASE
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|a
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
id|IO_DMA1_BASE
)paren
suffix:semicolon
)brace
r_else
(brace
id|dma_outb
c_func
(paren
(paren
id|a
op_rshift
l_int|1
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
id|IO_DMA2_BASE
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|a
op_rshift
l_int|9
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
id|IO_DMA2_BASE
)paren
suffix:semicolon
)brace
id|set_dma_page
c_func
(paren
id|dmanr
comma
id|a
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* set hipage last to enable 32-bit mode */
)brace
multiline_comment|/* Set transfer size (max 64k for DMA1..3, 128k for DMA5..7) for&n; * a specific DMA channel.&n; * You must ensure the parameters are valid.&n; * NOTE: from a manual: &quot;the number of transfers is one more&n; * than the initial word count&quot;! This is taken into account.&n; * Assumes dma flip-flop is clear.&n; * NOTE 2: &quot;count&quot; represents _bytes_ and must be even for channels 5-7.&n; */
DECL|function|set_dma_count
r_static
id|__inline__
r_void
id|set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|dmanr
op_le
l_int|3
)paren
(brace
id|dma_outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|1
op_plus
id|IO_DMA1_BASE
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|1
op_plus
id|IO_DMA1_BASE
)paren
suffix:semicolon
)brace
r_else
(brace
id|dma_outb
c_func
(paren
(paren
id|count
op_rshift
l_int|1
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
l_int|2
op_plus
id|IO_DMA2_BASE
)paren
suffix:semicolon
id|dma_outb
c_func
(paren
(paren
id|count
op_rshift
l_int|9
)paren
op_amp
l_int|0xff
comma
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
l_int|2
op_plus
id|IO_DMA2_BASE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * If called before the channel has been used, it may return 1.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; *&n; * Assumes DMA flip-flop is clear.&n; */
DECL|function|get_dma_residue
r_static
id|__inline__
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_int
r_int
id|io_port
op_assign
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|1
op_plus
id|IO_DMA1_BASE
suffix:colon
(paren
(paren
id|dmanr
op_amp
l_int|3
)paren
op_lshift
l_int|2
)paren
op_plus
l_int|2
op_plus
id|IO_DMA2_BASE
suffix:semicolon
multiline_comment|/* using short to get 16-bit wrap around */
r_int
r_int
id|count
suffix:semicolon
id|count
op_assign
l_int|1
op_plus
id|dma_inb
c_func
(paren
id|io_port
)paren
suffix:semicolon
id|count
op_add_assign
id|dma_inb
c_func
(paren
id|io_port
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
id|count
suffix:colon
(paren
id|count
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* These are in kernel/dma.c: */
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* reserve a DMA channel */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
multiline_comment|/* release it again */
DECL|macro|KERNEL_HAVE_CHECK_DMA
mdefine_line|#define KERNEL_HAVE_CHECK_DMA
r_extern
r_int
id|check_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
multiline_comment|/* From PCI */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* _ASM_DMA_H */
eof
