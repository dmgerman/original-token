macro_line|#ifndef __ASM_ARM_DMA_H
DECL|macro|__ASM_ARM_DMA_H
mdefine_line|#define __ASM_ARM_DMA_H
DECL|typedef|dmach_t
r_typedef
r_int
r_int
id|dmach_t
suffix:semicolon
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/dma.h&gt;
r_typedef
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|typedef|dmasg_t
)brace
id|dmasg_t
suffix:semicolon
r_extern
r_const
r_char
id|dma_str
(braket
)braket
suffix:semicolon
multiline_comment|/* Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; *&n; * NOTE: This is an architecture specific function, and should&n; *       be hidden from the drivers.&n; */
DECL|macro|clear_dma_ff
mdefine_line|#define clear_dma_ff(channel)
multiline_comment|/* Set only the page register bits of the transfer address.&n; *&n; * NOTE: This is an architecture specific function, and should&n; *       be hidden from the drivers&n; */
DECL|function|set_dma_page
r_static
id|__inline__
r_void
id|set_dma_page
c_func
(paren
id|dmach_t
id|channel
comma
r_char
id|pagenr
)paren
(brace
id|printk
c_func
(paren
id|dma_str
comma
l_string|&quot;set_dma_page&quot;
comma
id|channel
)paren
suffix:semicolon
)brace
multiline_comment|/* Request a DMA channel&n; *&n; * Some architectures may need to do allocate an interrupt&n; */
r_extern
r_int
id|request_dma
c_func
(paren
id|dmach_t
id|channel
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* Free a DMA channel&n; *&n; * Some architectures may need to do free an interrupt&n; */
r_extern
r_void
id|free_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Enable DMA for this channel&n; *&n; * On some architectures, this may have other side effects like&n; * enabling an interrupt and setting the DMA registers.&n; */
r_extern
r_void
id|enable_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Disable DMA for this channel&n; *&n; * On some architectures, this may have other side effects like&n; * disabling an interrupt or whatever.&n; */
r_extern
r_void
id|disable_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Set the DMA scatter gather list for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA address immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_sg
c_func
(paren
id|dmach_t
id|channel
comma
id|dmasg_t
op_star
id|sg
comma
r_int
id|nr_sg
)paren
suffix:semicolon
multiline_comment|/* Set the DMA address for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA address immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_addr
c_func
(paren
id|dmach_t
id|channel
comma
r_int
r_int
id|physaddr
)paren
suffix:semicolon
multiline_comment|/* Set the DMA byte count for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA count immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_count
c_func
(paren
id|dmach_t
id|channel
comma
r_int
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Set the transfer direction for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA transfer direction immediately, but defer it to the&n; * enable_dma().&n; */
r_extern
r_void
id|set_dma_mode
c_func
(paren
id|dmach_t
id|channel
comma
id|dmamode_t
id|mode
)paren
suffix:semicolon
multiline_comment|/* Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * If called before the channel has been used, it may return 1.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; */
r_extern
r_int
id|get_dma_residue
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
macro_line|#ifndef NO_DMA
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA&t;255
macro_line|#endif
macro_line|#endif /* _ARM_DMA_H */
eof
