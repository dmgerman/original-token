multiline_comment|/*&n; * arch/arm/kernel/dma.h&n; *&n; * Copyright (C) 1998 Russell King&n; *&n; * This header file describes the interface between the generic DMA handler&n; * (dma.c) and the architecture-specific DMA backends (dma-*.c)&n; */
r_typedef
r_struct
(brace
DECL|member|buf
id|dmasg_t
id|buf
suffix:semicolon
multiline_comment|/* single DMA&t;&t;&t;*/
DECL|member|sgcount
r_int
id|sgcount
suffix:semicolon
multiline_comment|/* number of DMA SG&t;&t;*/
DECL|member|sg
id|dmasg_t
op_star
id|sg
suffix:semicolon
multiline_comment|/* DMA Scatter-Gather List&t;*/
DECL|member|active
r_int
r_int
id|active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transfer active&t;&t;*/
DECL|member|invalid
r_int
r_int
id|invalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Address/Count changed&t;*/
DECL|member|dma_mode
id|dmamode_t
id|dma_mode
suffix:semicolon
multiline_comment|/* DMA mode&t;&t;&t;*/
DECL|member|lock
r_int
r_int
id|lock
suffix:semicolon
multiline_comment|/* Device is allocated&t;&t;*/
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
multiline_comment|/* Device name&t;&t;&t;*/
DECL|member|dma_base
r_int
r_int
id|dma_base
suffix:semicolon
multiline_comment|/* Controller base address&t;*/
DECL|member|dma_irq
r_int
id|dma_irq
suffix:semicolon
multiline_comment|/* Controller IRQ&t;&t;*/
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Controller state&t;&t;*/
DECL|member|cur_sg
id|dmasg_t
id|cur_sg
suffix:semicolon
multiline_comment|/* Current controller buffer&t;*/
DECL|typedef|dma_t
)brace
id|dma_t
suffix:semicolon
multiline_comment|/* Prototype: int arch_request_dma(channel, dma, dev_id)&n; * Purpose  : Perform architecture specific claiming of a DMA channel&n; * Params   : channel - DMA channel number&n; *          : dma     - DMA structure (above) for channel&n; *          : dev_id  - device ID string passed with request&n; * Returns  : 0 on success, E????? number on error&n; */
r_int
id|arch_request_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
comma
r_const
r_char
op_star
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* Prototype: int arch_free_dma(channel, dma)&n; * Purpose  : Perform architecture specific freeing of a DMA channel&n; * Params   : channel - DMA channel number&n; *          : dma     - DMA structure for channel&n; */
r_void
id|arch_free_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* Prototype: void arch_enable_dma(channel, dma)&n; * Purpose  : Enable a claimed DMA channel&n; * Params   : channel - DMA channel number&n; *          : dma     - DMA structure for channel&n; */
r_void
id|arch_enable_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* Prototype: void arch_disable_dma(channel, dma)&n; * Purpose  : Disable a claimed DMA channel&n; * Params   : channel - DMA channel number&n; *          : dma     - DMA structure for channel&n; */
r_void
id|arch_disable_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* Prototype: int arch_get_dma_residue(channel, dma)&n; * Purpose  : Return number of bytes left to DMA&n; * Params   : channel - DMA channel number&n; *          : dma     - DMA structure for channel&n; * Returns  : Number of bytes left to DMA&n; */
r_int
id|arch_get_dma_residue
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* Prototype: void arch_dma_init(dma)&n; * Purpose  : Initialise architecture specific DMA&n; * Params   : dma - pointer to array of DMA structures&n; */
r_void
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
eof
