multiline_comment|/*&n; * include/asm-sparc/dma.h&n; *&n; * Don&squot;t even ask, I am figuring out how this crap works&n; * on the Sparc. It may end up being real hairy to plug&n; * into this code, maybe not, we&squot;ll see.&n; *&n; * Copyright 1995 (C) David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _ASM_SPARC_DMA_H
DECL|macro|_ASM_SPARC_DMA_H
mdefine_line|#define _ASM_SPARC_DMA_H
macro_line|#include &lt;asm/vac-ops.h&gt;  /* for invalidate&squot;s, etc. */
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* DMA probing routine */
r_extern
r_int
r_int
id|probe_dma
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* These are irrelevant for Sparc DMA, but we leave it in so that&n; * things can compile.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS  0x0
multiline_comment|/* Structure to describe the current status of DMA registers on the Sparc */
DECL|struct|sparc_dma_registers
r_struct
id|sparc_dma_registers
(brace
DECL|member|cond_reg
r_volatile
r_int
r_int
id|cond_reg
suffix:semicolon
multiline_comment|/* DMA condition register */
DECL|member|st_addr
r_volatile
r_char
op_star
id|st_addr
suffix:semicolon
multiline_comment|/* Start address of this transfer */
DECL|member|cnt
r_volatile
r_int
r_int
id|cnt
suffix:semicolon
multiline_comment|/* How many bytes to transfer */
DECL|member|dma_test
r_volatile
r_int
r_int
id|dma_test
suffix:semicolon
multiline_comment|/* DMA test register */
)brace
suffix:semicolon
multiline_comment|/* Linux DMA information structure, filled during probe. */
DECL|struct|Linux_SBus_DMA
r_struct
id|Linux_SBus_DMA
(brace
DECL|member|SBus_dev
r_struct
id|linux_sbus_device
op_star
id|SBus_dev
suffix:semicolon
multiline_comment|/* pointer to sbus device struct */
DECL|member|DMA_regs
r_struct
id|sparc_dma_registers
op_star
id|DMA_regs
suffix:semicolon
multiline_comment|/* Pointer to DMA regs in IO space */
multiline_comment|/* Status, misc info */
DECL|member|node
r_int
id|node
suffix:semicolon
multiline_comment|/* Prom node for this DMA device */
DECL|member|dma_running
r_int
id|dma_running
suffix:semicolon
multiline_comment|/* Are we using the DMA now? */
multiline_comment|/* DMA revision: 0=REV0 1=REV1 2=REV2 3=DMA_PLUS */
DECL|member|dma_rev
r_int
id|dma_rev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|Linux_SBus_DMA
id|Sparc_DMA
suffix:semicolon
multiline_comment|/* Main routines in dma.c */
r_extern
r_void
id|dump_dma_regs
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|probe_dma
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sparc_dma_init_transfer
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sparc_dma_interrupt
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
suffix:semicolon
multiline_comment|/* Fields in the cond_reg register */
multiline_comment|/* First, the version identification bits */
DECL|macro|DMA_DEVICE_ID
mdefine_line|#define DMA_DEVICE_ID    0xf0000000        /* Device identification bits */
DECL|macro|DMA_VERS0
mdefine_line|#define DMA_VERS0        0x00000000        /* Sunray DMA version */
DECL|macro|DMA_VERS1
mdefine_line|#define DMA_VERS1        0x80000000        /* DMA rev 1 */
DECL|macro|DMA_VERS2
mdefine_line|#define DMA_VERS2        0xa0000000        /* DMA rev 2 */
DECL|macro|DMA_VERSPLUS
mdefine_line|#define DMA_VERSPLUS     0x90000000        /* DMA rev 1 PLUS */
DECL|macro|DMA_HNDL_INTR
mdefine_line|#define DMA_HNDL_INTR    0x00000001        /* An interrupt needs to be handled */
DECL|macro|DMA_HNDL_ERROR
mdefine_line|#define DMA_HNDL_ERROR   0x00000002        /* We need to take care of an error */
DECL|macro|DMA_FIFO_ISDRAIN
mdefine_line|#define DMA_FIFO_ISDRAIN 0x0000000c        /* The DMA FIFO is draining */
DECL|macro|DMA_INT_ENAB
mdefine_line|#define DMA_INT_ENAB     0x00000010        /* Turn on interrupts */
DECL|macro|DMA_FIFO_INV
mdefine_line|#define DMA_FIFO_INV     0x00000020        /* Invalidate the FIFO */
DECL|macro|DMA_ACC_SZ_ERR
mdefine_line|#define DMA_ACC_SZ_ERR   0x00000040        /* The access size was bad */
DECL|macro|DMA_FIFO_STDRAIN
mdefine_line|#define DMA_FIFO_STDRAIN 0x00000040        /* DMA_VERS1 Drain the FIFO */
DECL|macro|DMA_RST_SCSI
mdefine_line|#define DMA_RST_SCSI     0x00000080        /* Reset the SCSI controller */
DECL|macro|DMA_ST_WRITE
mdefine_line|#define DMA_ST_WRITE     0x00000100        /* If set, write from device to memory */
DECL|macro|DMA_ENABLE
mdefine_line|#define DMA_ENABLE       0x00000200        /* Fire up DMA, handle requests */
DECL|macro|DMA_PEND_READ
mdefine_line|#define DMA_PEND_READ    0x00000400        /* DMA_VERS1/0/PLUS Read is pending */
DECL|macro|DMA_BCNT_ENAB
mdefine_line|#define DMA_BCNT_ENAB    0x00002000        /* If on, use the byte counter */
DECL|macro|DMA_TERM_CNTR
mdefine_line|#define DMA_TERM_CNTR    0x00004000        /* Terminal counter */
DECL|macro|DMA_CSR_DISAB
mdefine_line|#define DMA_CSR_DISAB    0x00010000        /* No FIFO drains during csr */
DECL|macro|DMA_SCSI_DISAB
mdefine_line|#define DMA_SCSI_DISAB   0x00020000        /* No FIFO drains during reg */
DECL|macro|DMA_BRST_SZ
mdefine_line|#define DMA_BRST_SZ      0x000c0000        /* SBUS transfer r/w burst size */
DECL|macro|DMA_ADDR_DISAB
mdefine_line|#define DMA_ADDR_DISAB   0x00100000        /* No FIFO drains during addr */
DECL|macro|DMA_2CLKS
mdefine_line|#define DMA_2CLKS        0x00200000        /* Each transfer equals 2 clock ticks */
DECL|macro|DMA_3CLKS
mdefine_line|#define DMA_3CLKS        0x00400000        /* Each transfer equals 3 clock ticks */
DECL|macro|DMA_CNTR_DISAB
mdefine_line|#define DMA_CNTR_DISAB   0x00800000        /* No intr&squot;s when DMA_TERM_CNTR is set */
DECL|macro|DMA_AUTO_NADDR
mdefine_line|#define DMA_AUTO_NADDR   0x01000000        /* Use &quot;auto next address&quot; feature */
DECL|macro|DMA_SCSI_ON
mdefine_line|#define DMA_SCSI_ON      0x02000000        /* Enable SCSI dma */
DECL|macro|DMA_LOADED_ADDR
mdefine_line|#define DMA_LOADED_ADDR  0x04000000        /* Address has been loaded */
DECL|macro|DMA_LOADED_NADDR
mdefine_line|#define DMA_LOADED_NADDR 0x08000000        /* Next address has been loaded */
multiline_comment|/* Only 24-bits of the byte count are significant */
DECL|macro|DMA_BYTE_CNT_MASK
mdefine_line|#define DMA_BYTE_CNT_MASK  0x00ffffff
multiline_comment|/* Pause until counter runs out or BIT isn&squot;t set in the DMA condition&n; * register.&n; */
DECL|function|sparc_dma_pause
r_extern
r_inline
r_void
id|sparc_dma_pause
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
id|dma_regs
comma
r_int
r_int
id|bit
)paren
(brace
r_int
id|ctr
op_assign
l_int|50000
suffix:semicolon
multiline_comment|/* Let&squot;s find some bugs ;) */
multiline_comment|/* Busy wait until the bit is not set any more */
r_while
c_loop
(paren
(paren
id|dma_regs-&gt;cond_reg
op_amp
id|bit
)paren
op_logical_and
(paren
id|ctr
OG
l_int|0
)paren
)paren
(brace
id|ctr
op_decrement
suffix:semicolon
id|__delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for bogus outcome. */
r_if
c_cond
(paren
id|ctr
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA Grrr:  I tried for wait for the assertion of bit %08xl to clear&quot;
comma
(paren
r_int
r_int
)paren
id|bit
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           in the DMA condition register and it did not!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Cannot continue, halting...&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Enable DMA interrupts */
DECL|function|sparc_dma_enable_interrupts
r_extern
r_inline
r_void
id|sparc_dma_enable_interrupts
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
id|dma_regs
)paren
(brace
id|dma_regs-&gt;cond_reg
op_or_assign
id|DMA_INT_ENAB
suffix:semicolon
)brace
multiline_comment|/* Disable DMA interrupts from coming in */
DECL|function|sparc_dma_disable_interrupts
r_extern
r_inline
r_void
id|sparc_dma_disable_interrupts
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
id|dma_regs
)paren
(brace
id|dma_regs-&gt;cond_reg
op_and_assign
op_complement
(paren
id|DMA_INT_ENAB
)paren
suffix:semicolon
)brace
multiline_comment|/* Reset the DMA module. */
DECL|function|sparc_dma_reset
r_extern
r_inline
r_void
id|sparc_dma_reset
c_func
(paren
r_struct
id|sparc_dma_registers
op_star
id|dma_regs
)paren
(brace
multiline_comment|/* Let the current FIFO drain itself */
id|sparc_dma_pause
c_func
(paren
id|dma_regs
comma
(paren
id|DMA_FIFO_ISDRAIN
)paren
)paren
suffix:semicolon
multiline_comment|/* Reset the logic */
id|dma_regs-&gt;cond_reg
op_or_assign
(paren
id|DMA_RST_SCSI
)paren
suffix:semicolon
multiline_comment|/* assert */
id|__delay
c_func
(paren
l_int|400
)paren
suffix:semicolon
multiline_comment|/* let the bits set ;) */
id|dma_regs-&gt;cond_reg
op_and_assign
op_complement
(paren
id|DMA_RST_SCSI
)paren
suffix:semicolon
multiline_comment|/* de-assert */
id|sparc_dma_enable_interrupts
c_func
(paren
id|dma_regs
)paren
suffix:semicolon
multiline_comment|/* Re-enable interrupts */
multiline_comment|/* Enable FAST transfers if available */
r_if
c_cond
(paren
id|Sparc_DMA.dma_rev
OG
l_int|1
)paren
(brace
id|dma_regs-&gt;cond_reg
op_or_assign
id|DMA_3CLKS
suffix:semicolon
)brace
id|Sparc_DMA.dma_running
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* !(_ASM_SPARC_DMA_H) */
eof
