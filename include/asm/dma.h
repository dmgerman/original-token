multiline_comment|/* $Header: /sys/linux-0.97/include/asm/RCS/dma.h,v 1.4 1992/09/21 03:15:46 root Exp root $&n; * linux/include/asm/dma.h: Defines for using and allocating dma channels.&n; * Written by Hennus Bergman, 1992.&n; *&n; * High DMA channel support by Hannu Savolainen&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
macro_line|#ifdef HAVE_REALLY_SLOW_DMA_CONTROLLER
DECL|macro|outb
mdefine_line|#define outb&t;outb_p
macro_line|#endif
multiline_comment|/*&n; * The routines below should in most cases (with optimizing on) result&n; * in equal or better code than similar code using macros.&n; *&n; * NOTE about DMA transfers: The DMA controller cannot handle transfers&n; * that cross a 64k boundary. When the address reaches 0xNffff, it will wrap&n; * around to 0xN0000, rather than increment to 0x(N+1)0000 !&n; * Make sure you align your buffers properly! Runtime check recommended.&n;&n; ****** Correction!!!!!&n; * &t;Channels 4-7 16 bit channels and capable to cross 64k boundaries&n; *&t;but not 128k boundaries. Transfer count must be given as words.&n; *&t;Maximum transfer size is 65k words = 128kb.&n; *&n; * NOTE2: DMA1..3 can only use the lower 1MB of physical memory. DMA4..7&n; * can access the lower 16MB. There are people with &gt;16MB, so beware!&n; &n; * **** Not correct!!! All channels are able to access the first 16MB *******&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
multiline_comment|/* SOMEBODY should check the following:&n; * Channels 0..3 are on the first DMA controller, channels 4..7 are&n; * on the second. Channel 0 is for refresh, 4 is for cascading.&n; * The first DMA controller uses bytes, the second words.&n; *&n; * Where are the page regs for the second DMA controller?????&n; * (ch 5=0x8b, 6=0x89, 7=0x8a)&n; */
multiline_comment|/* 8237 DMA controllers */
DECL|macro|IO_DMA1_BASE
mdefine_line|#define IO_DMA1_BASE&t;0x00&t;/* 8 bit slave DMA, channels 0..3 */
DECL|macro|IO_DMA2_BASE
mdefine_line|#define IO_DMA2_BASE&t;0xC0&t;/* 16 bit master DMA, ch 4(=slave input)..7 */
multiline_comment|/* DMA controller registers */
DECL|macro|DMA1_CMD_REG
mdefine_line|#define DMA1_CMD_REG&t;&t;0x08&t;/* DMA command register */
DECL|macro|DMA1_STAT_REG
mdefine_line|#define DMA1_STAT_REG&t;&t;0x08&t;/* DMA status register */
DECL|macro|DMA1_MASK_REG
mdefine_line|#define DMA1_MASK_REG&t;&t;0x0A&t;/* mask individual channels */
DECL|macro|DMA1_MODE_REG
mdefine_line|#define DMA1_MODE_REG&t;&t;0x0B&t;/* set modes for individual channels */
DECL|macro|DMA1_CLEAR_FF_REG
mdefine_line|#define DMA1_CLEAR_FF_REG&t;0x0C&t;/* Write 0 for LSB, 1 for MSB */
DECL|macro|DMA1_RESET_REG
mdefine_line|#define DMA1_RESET_REG&t;&t;0x0D&t;/* Write here to reset DMA controller */
DECL|macro|DMA2_CMD_REG
mdefine_line|#define DMA2_CMD_REG&t;&t;0xD0&t;/* DMA command register */
DECL|macro|DMA2_STAT_REG
mdefine_line|#define DMA2_STAT_REG&t;&t;0xD0&t;/* DMA status register */
DECL|macro|DMA2_MASK_REG
mdefine_line|#define DMA2_MASK_REG&t;&t;0xD4
DECL|macro|DMA2_MODE_REG
mdefine_line|#define DMA2_MODE_REG&t;&t;0xD6
DECL|macro|DMA2_CLEAR_FF_REG
mdefine_line|#define DMA2_CLEAR_FF_REG &t;0xD8
DECL|macro|DMA2_RESET_REG
mdefine_line|#define DMA2_RESET_REG&t;&t;0xDA&t;/* Write here to reset DMA controller */
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;0x44&t;/* I/O to memory, no autoinit, increment, single mode */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;0x48&t;/* memory to I/O, no autoinit, increment, single mode */
multiline_comment|/* cascade mode (for DMA2 controller only) */
DECL|macro|DMA_MODE_CASCADE
mdefine_line|#define DMA_MODE_CASCADE&t;0x40&t;/* 0xC0 */
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
id|outb
c_func
(paren
id|dmanr
comma
id|DMA1_MASK_REG
)paren
suffix:semicolon
r_else
id|outb
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
id|outb
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
id|outb
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
multiline_comment|/* Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; * Use this once to initialize the FF to a know state.&n; * After that, keep track of it. :-) In order to do that,&n; * dma_set_addr() and dma_set_count() should only be used wile&n; * interrupts are disbled.&n; */
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
id|outb
c_func
(paren
l_int|0
comma
id|DMA1_CLEAR_FF_REG
)paren
suffix:semicolon
r_else
id|outb
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
id|outb
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
id|outb
c_func
(paren
id|DMA_MODE_CASCADE
op_or
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
multiline_comment|/* Set only the page register bits of the transfer address.&n; * This is used for successive transfers when we know the contents of&n; * the lower 16 bits of the DMA current address register, but a 64k boundary&n; * may have been crossed.&n; */
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
r_char
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
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x83
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x81
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x82
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x8f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x8b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x89
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|outb
c_func
(paren
id|pagenr
comma
l_int|0x8a
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Set transfer address &amp; page bits for specific DMA channel.&n; * Assumes dma flipflop is clear.&n; *&n; * NOTE! A word address is assumed for the channels 4 to 7.&n; */
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
r_int
r_int
id|io_base
op_assign
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
id|IO_DMA1_BASE
suffix:colon
id|IO_DMA2_BASE
suffix:semicolon
r_int
r_int
id|page
op_assign
id|a
op_rshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|dmanr
OG
l_int|3
)paren
id|page
op_and_assign
l_int|0xfe
suffix:semicolon
multiline_comment|/* The last bit is never used */
id|set_dma_page
c_func
(paren
id|dmanr
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmanr
OG
l_int|3
)paren
id|a
op_rshift_assign
l_int|1
suffix:semicolon
id|outb
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
id|io_base
)paren
suffix:semicolon
id|outb
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
id|io_base
)paren
suffix:semicolon
)brace
multiline_comment|/* Set transfer size (max 64k) for a specific DMA channel.&n; * You must ensure the parameters are valid.&n; * NOTE: from a manual: &quot;the number of transfers is one more &n; * than the initial word count&quot;! This is taken into account.&n; * Assumes dma flip-flop is clear.&n; */
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
r_int
r_int
id|dc
suffix:semicolon
r_int
r_int
id|io_base
op_assign
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
id|IO_DMA1_BASE
suffix:colon
id|IO_DMA2_BASE
suffix:semicolon
r_if
c_cond
(paren
id|dmanr
OG
l_int|3
)paren
id|count
op_rshift_assign
l_int|1
suffix:semicolon
id|dc
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|dc
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
id|io_base
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|dc
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
id|io_base
)paren
suffix:semicolon
)brace
multiline_comment|/* Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * If called before the channel has been used, it may return 1.&n; * Otherwise, it returns the number of bytes left to transfer,&n; * minus 1, modulo 64k.&n; * Assumes DMA flip-flop is clear.&n; */
DECL|function|get_dma_residue
r_static
id|__inline__
r_int
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
id|io_base
op_assign
(paren
id|dmanr
op_le
l_int|3
)paren
ques
c_cond
id|IO_DMA1_BASE
suffix:colon
id|IO_DMA2_BASE
suffix:semicolon
r_return
l_int|1
op_plus
id|inb
c_func
(paren
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
id|io_base
)paren
op_plus
(paren
id|inb
c_func
(paren
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
id|io_base
)paren
op_lshift
l_int|8
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
macro_line|#endif /* _ASM_DMA_H */
eof
