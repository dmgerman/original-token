multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* ap1000 register definitions needed for Linux/AP+ */
macro_line|#ifndef _AP1000_APREG_H
DECL|macro|_AP1000_APREG_H
mdefine_line|#define _AP1000_APREG_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ap1000/apservice.h&gt;
macro_line|#include &lt;asm/ap1000/apbif.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * Macros for accessing I/O registers.&n; */
DECL|macro|BIF_IN
mdefine_line|#define BIF_IN(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|BIF_OUT
mdefine_line|#define BIF_OUT(reg,v)&t;(*(volatile unsigned *)(reg) = (v))
DECL|macro|DMA_IN
mdefine_line|#define DMA_IN(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|DMA_OUT
mdefine_line|#define DMA_OUT(reg,v)&t;(*(volatile unsigned *)(reg) = (v))
DECL|macro|MC_IN
mdefine_line|#define MC_IN(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|MC_OUT
mdefine_line|#define MC_OUT(reg,v)&t;(*(volatile unsigned *)(reg) = (v))
DECL|macro|MSC_IN
mdefine_line|#define MSC_IN(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|MSC_OUT
mdefine_line|#define MSC_OUT(reg,v)&t;(*(volatile unsigned *)(reg) = (v))
DECL|macro|MSC_IO
mdefine_line|#define MSC_IO(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|RTC_IO
mdefine_line|#define RTC_IO(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|MC_IO
mdefine_line|#define MC_IO(reg)&t;(*(volatile unsigned *)(reg))
DECL|macro|OPT_IO
mdefine_line|#define OPT_IO(reg)&t;(*(volatile unsigned *)(reg))
multiline_comment|/*&n; * B-net interface register definitions.&n; */
DECL|macro|BIF
mdefine_line|#define BIF &t;0xfff30000&t;
DECL|macro|BIF_CIDR1
mdefine_line|#define BIF_CIDR1 &t;(BIF+0x004c)&t;/* cell-id register 1 (for cell mode)*/
DECL|macro|BIF_SDCSR
mdefine_line|#define BIF_SDCSR &t;(BIF+0x0070)&t;/* BIF data control set register  */
DECL|macro|BIF_DATA
mdefine_line|#define BIF_DATA &t;(BIF+0x0000)&t;/* BIF send and receive data registe&t;*/
DECL|macro|BIF_EDATA
mdefine_line|#define BIF_EDATA  &t;(BIF+0x0004)&t;/* BIF end data register &t;&t;*/
DECL|macro|BIF_INTR
mdefine_line|#define BIF_INTR &t;(BIF+0x006c)&t;/* BIF interrupt control register &t;*/
DECL|macro|SSTT_SET
mdefine_line|#define SSTT_SET&t;(BIF+0xe0)&t;/* set SSTT &t;&t;&t;*/
DECL|macro|SSTT_CLR
mdefine_line|#define SSTT_CLR&t;(BIF+0xe4)&t;/* clear SSTT &t;&t;&t;*/
DECL|macro|SSTT_SMSK
mdefine_line|#define SSTT_SMSK&t;(BIF+0xe8)&t;/* set SSTT mask&t;&t;*/
DECL|macro|SSTT_CMSK
mdefine_line|#define SSTT_CMSK&t;(BIF+0xec)&t;/* clear SSTT mask&t;&t;*/
DECL|macro|SSTT_SMD
mdefine_line|#define SSTT_SMD&t;(BIF+0xf0)&t;/* set SSYN &amp; SSTT mode&t;&t;*/
DECL|macro|SSTT_CMD
mdefine_line|#define SSTT_CMD&t;(BIF+0xf4)&t;/* clear SSYN &amp; SSTT mode&t;*/
multiline_comment|/*&n;** FSTT registers&n;*/
DECL|macro|FSTT
mdefine_line|#define FSTT&t;BIF&t;/*&t;FSTT only system mode&t;*/
DECL|macro|FSTT_SET
mdefine_line|#define FSTT_SET&t;(FSTT+0xa0)&t;/* set FSTT &t;&t;&t;  */
DECL|macro|FSTT_CLR
mdefine_line|#define FSTT_CLR&t;(FSTT+0xa4)&t;/* clear FSTT &t;&t;&t;  */
DECL|macro|FSTT_SMSK
mdefine_line|#define FSTT_SMSK&t;(FSTT+0xa8)&t;/* set FSTT mask&t;&t;  */
DECL|macro|FSTT_CMSK
mdefine_line|#define FSTT_CMSK&t;(FSTT+0xac)&t;/* clear FSTT mask&t;&t;  */
DECL|macro|FSTT_SMD
mdefine_line|#define FSTT_SMD&t;(FSTT+0xb0)&t;/* set FSYN &amp; FSTT mode&t;&t;  */
DECL|macro|FSTT_CMD
mdefine_line|#define FSTT_CMD&t;(FSTT+0xb4)&t;/* clear FSYN &amp; FSTT mode&t;  */
DECL|macro|FSTT_TIM
mdefine_line|#define FSTT_TIM&t;(FSTT+0xb8)&t;/* status timer&t;&t;&t;  */
DECL|macro|BIF_SDCSR_RB
mdefine_line|#define BIF_SDCSR_RB&t;0x0000001c&t;/* data in receive FIFO&t;&t;  */
DECL|macro|BIF_SDCSR_EB
mdefine_line|#define BIF_SDCSR_EB&t;0x00000100&t;/* send data that have end bit&t;  */
DECL|macro|BIF_SDCSR_BG
mdefine_line|#define BIF_SDCSR_BG&t;0x00001000&t;/* check if command bus got&t;  */
DECL|macro|BIF_SDCSR_BR
mdefine_line|#define BIF_SDCSR_BR&t;0x00000800&t;/* request command bus&t;&t;  */
DECL|macro|BIF_SDCSR_TB
mdefine_line|#define BIF_SDCSR_TB&t;0x000000E0&t;/* data in send FIFO&t;&t;  */
DECL|macro|BIF_SDCSR_PE
mdefine_line|#define BIF_SDCSR_PE&t;0x80000000&t;/* detect parity error in sync&t;       &t;*/
DECL|macro|BIF_SDCSR_BB
mdefine_line|#define BIF_SDCSR_BB    0x00002000      /* check if some BIF use command bus    */
DECL|macro|BIF_SDCSR_RB_SHIFT
mdefine_line|#define BIF_SDCSR_RB_SHIFT 2
DECL|macro|BIF_SDCSR_TB_SHIFT
mdefine_line|#define BIF_SDCSR_TB_SHIFT 5
DECL|macro|BIF_INTR_GET_SH
mdefine_line|#define BIF_INTR_GET_SH       15         /* get bus interrupt */
DECL|macro|BIF_INTR_HEADER_SH
mdefine_line|#define BIF_INTR_HEADER_SH    12         /* header interrupt */
DECL|macro|BIF_INTR_SEND_SH
mdefine_line|#define BIF_INTR_SEND_SH      9          /* send interrupt */
DECL|macro|BIF_INTR_RECV_SH
mdefine_line|#define BIF_INTR_RECV_SH      6          /* receive interrupt */
DECL|macro|BIF_INTR_ERR_SH
mdefine_line|#define BIF_INTR_ERR_SH       3          /* error interrupt */
DECL|macro|BIF_INTR_ATTN_SH
mdefine_line|#define BIF_INTR_ATTN_SH      0          /* attention interrupt */
DECL|macro|BIF_HEADER_HS
mdefine_line|#define BIF_HEADER_HS&t;0x00000200&t;/* header strip&t;&t;*/
DECL|macro|BIF_HEADER_RS
mdefine_line|#define BIF_HEADER_RS&t;0x00000100&t;/* bus release &t;&t;*/
DECL|macro|BIF_HEADER_IN
mdefine_line|#define BIF_HEADER_IN&t;0x00001000&t;/* interrupt bit&t;*/
DECL|macro|BIF_HEADER_BR
mdefine_line|#define BIF_HEADER_BR   0x00008000    /* broad bit    */
DECL|macro|BIF_INTR_HS
mdefine_line|#define BIF_INTR_HS&t;&t;0x00004000&t;/* header interrupt select  */
DECL|macro|HOST_CID
mdefine_line|#define HOST_CID      0x1000
DECL|macro|MAKE_HEADER
mdefine_line|#define MAKE_HEADER(cid) (BIF_HEADER_IN | &bslash;&n;&t;&t;&t;  ((cid)==-1?BIF_HEADER_BR:((cid)&lt;&lt;16) | (1&lt;&lt;13)))
DECL|macro|BIF_RDCSR
mdefine_line|#define BIF_RDCSR &t;(BIF+0x0074)&t;/* BIF data control reset reregister */
multiline_comment|/*&n; * Interrupt levels for AP+ devices&n; */
DECL|macro|APBIFGET_IRQ
mdefine_line|#define APBIFGET_IRQ&t;1&t;&t;/* have acquired B-net */
DECL|macro|APOPT0_IRQ
mdefine_line|#define APOPT0_IRQ&t;2&t;&t;/* option interrupt level 0 */
DECL|macro|APSYNC_IRQ
mdefine_line|#define APSYNC_IRQ&t;3&t;&t;/* sync (S-net) interrupt */
DECL|macro|APDMA_IRQ
mdefine_line|#define APDMA_IRQ&t;4&t;&t;/* DMA complete interrupt */
DECL|macro|APRTC_IRQ
mdefine_line|#define APRTC_IRQ&t;5&t;&t;/* RTC data transfer interrupt */
DECL|macro|APIPORT_IRQ
mdefine_line|#define APIPORT_IRQ&t;6&t;&t;/* Interrupt port interrupt */
DECL|macro|APOPT1_IRQ
mdefine_line|#define APOPT1_IRQ&t;7&t;&t;/* option interrupt level 1 */
DECL|macro|APBIF_IRQ
mdefine_line|#define APBIF_IRQ&t;8&t;&t;/* B-net interface interrupt */
DECL|macro|APMAS_IRQ
mdefine_line|#define APMAS_IRQ&t;9&t;&t;/* Send/Recv mem acc. seq. intr */
DECL|macro|APTIM1_IRQ
mdefine_line|#define APTIM1_IRQ&t;10&t;&t;/* Timer 1 interrupt */
DECL|macro|APMSC_IRQ
mdefine_line|#define APMSC_IRQ&t;11&t;&t;/* MSC+ ring buf/queue spill etc. */
DECL|macro|APLBUS_IRQ
mdefine_line|#define APLBUS_IRQ&t;12&t;&t;/* LBUS error interrupt */
DECL|macro|APATTN_IRQ
mdefine_line|#define APATTN_IRQ&t;13&t;&t;/* Attention interrupt */
DECL|macro|APTIM0_IRQ
mdefine_line|#define APTIM0_IRQ&t;14&t;&t;/* Timer 0 interrupt */
DECL|macro|APMEM_IRQ
mdefine_line|#define APMEM_IRQ&t;15&t;&t;/* Memory error interrupt */
multiline_comment|/*&n; * LBUS DMA controller register definitions&n; */
DECL|macro|DMA
mdefine_line|#define DMA     0xfff00000 /* dma controller address */
DECL|macro|DMA3
mdefine_line|#define DMA3    (DMA+0xc0) /* DMA channel 3 */
DECL|macro|DMA_DMST
mdefine_line|#define DMA_DMST    0x04
DECL|macro|DMA_MADDR
mdefine_line|#define DMA_MADDR   0x10
DECL|macro|DMA_HSKIP
mdefine_line|#define DMA_HSKIP   0x08
DECL|macro|DMA_HCNT
mdefine_line|#define DMA_HCNT    0x0a
DECL|macro|DMA_VSKIP
mdefine_line|#define DMA_VSKIP   0x0c
DECL|macro|DMA_VCNT
mdefine_line|#define DMA_VCNT    0x0e
DECL|macro|DMA_DCMD
mdefine_line|#define DMA_DCMD    0x00
DECL|macro|DMA_HDRP
mdefine_line|#define DMA_HDRP    0x28
DECL|macro|DMA_DSIZE
mdefine_line|#define DMA_DSIZE   0x02
DECL|macro|DMA_CSIZE
mdefine_line|#define DMA_CSIZE   0x06
DECL|macro|DMA_VCNT
mdefine_line|#define DMA_VCNT    0x0e
DECL|macro|DMA_BIF_BCMD
mdefine_line|#define DMA_BIF_BCMD&t;(DMA+0x120)&t;/* BIF receive command register&t;*/
DECL|macro|DMA_BIF_BRST
mdefine_line|#define&t;DMA_BIF_BRST&t;(DMA+0x124)&t;/* BIF receive status register */
DECL|macro|DMA_BCMD_SA
mdefine_line|#define&t;DMA_BCMD_SA&t;&t;0x40000000&t;/* software abort   */
DECL|macro|DMA_DMST_AC
mdefine_line|#define&t;DMA_DMST_AC&t;&t;0x80000000&t;/* channel active   */
DECL|macro|DMA_DMST_RST
mdefine_line|#define DMA_DMST_RST&t;&t;0xffe40000  /* reset bits and reqs */
DECL|macro|DMA_DCMD_ST
mdefine_line|#define&t;DMA_DCMD_ST&t;&t;0x80000000&t;/* start operation    */
DECL|macro|DMA_DCMD_TYP_AUTO
mdefine_line|#define&t;DMA_DCMD_TYP_AUTO&t;0x30000000&t;/* 11: auto  */
DECL|macro|DMA_DCMD_TD_MD
mdefine_line|#define&t;DMA_DCMD_TD_MD&t;&t;0x04000000&t;/* transfer mem-&gt;dev */
DECL|macro|DMA_DCMD_TD_DM
mdefine_line|#define&t;DMA_DCMD_TD_DM&t;&t;0x00000000&t;/* transfer direction dev-&gt;mem*/
DECL|macro|DMA_CH2
mdefine_line|#define DMA_CH2    (DMA+0x80)&t;/* DMA channel 2&t;*/
DECL|macro|DMA_CH3
mdefine_line|#define DMA_CH3    (DMA+0xc0)&t;/* DMA channel 3&t;*/
DECL|macro|DMA2_DMST
mdefine_line|#define DMA2_DMST  (DMA_CH2+0x04)&t;&t;/* DMA2 status register&t;  */
DECL|macro|DMA3_DMST
mdefine_line|#define DMA3_DMST  (DMA_CH3+0x04)&t;&t;/* DMA3 status register&t;  */
DECL|macro|DMA2_DCMD
mdefine_line|#define DMA2_DCMD   (DMA_CH2+0x00)&t;&t;/* DMA2 command register  */
DECL|macro|DMA_INTR_NORMAL_SH
mdefine_line|#define DMA_INTR_NORMAL_SH     19               /* normal DMA interrupt */
DECL|macro|DMA_INTR_ERROR_SH
mdefine_line|#define DMA_INTR_ERROR_SH      16               /* error DMA interrupt */
DECL|macro|DMA_DCMD_SA
mdefine_line|#define&t;DMA_DCMD_SA&t;&t;0x40000000&t;/* software abort     */
DECL|macro|DMA_MAX_TRANS_SIZE
mdefine_line|#define DMA_MAX_TRANS_SIZE&t;&t;(0xffff&lt;&lt;2)
DECL|macro|DMA_TRANS_BLOCK_SIZE
mdefine_line|#define DMA_TRANS_BLOCK_SIZE&t;(64&lt;&lt;2)
DECL|macro|WORD_SIZE
mdefine_line|#define WORD_SIZE 4
DECL|macro|B2W
mdefine_line|#define B2W(x)    (((x) + WORD_SIZE - 1) / WORD_SIZE)
DECL|macro|W2B
mdefine_line|#define W2B(x)    ((x) * WORD_SIZE)
DECL|macro|DMA_GEN
mdefine_line|#define DMA_GEN&t;&t;0xfff00180&t;&t;/* DMA general control reg */
multiline_comment|/* AP1000+ Message Controller (MSC+) */
DECL|macro|MSC_BASE0
mdefine_line|#define MSC_BASE0 0xfa008000
DECL|macro|MSC_SQCTRL
mdefine_line|#define MSC_SQCTRL&t;(MSC_BASE0 + 0x0)&t;/* Send Queue control */
multiline_comment|/* bits in MSC_SQCTRL */
DECL|macro|MSC_SQC_STABLE
mdefine_line|#define MSC_SQC_STABLE&t;0x400&t;&t;&t;/* Send Queue stable */
DECL|macro|MSC_SQC_MODE
mdefine_line|#define MSC_SQC_MODE&t;0x300&t;&t;&t;/* Send Queue mode: */
DECL|macro|MSC_SQC_MODE_BLOCK
mdefine_line|#define MSC_SQC_MODE_BLOCK&t;0&t;&t;&t;/* blocking */
DECL|macro|MSC_SQC_MODE_THRU
mdefine_line|#define MSC_SQC_MODE_THRU&t;0x100&t;&t;&t;/* through */
DECL|macro|MSC_SQC_MODE_NORMAL
mdefine_line|#define MSC_SQC_MODE_NORMAL&t;0x200&t;&t;&t;/* or normal */
DECL|macro|MSC_SQC_SPLF_SH
mdefine_line|#define MSC_SQC_SPLF_SH&t;&t;3&t;&t;/* bit# for spill flags */
DECL|macro|MSC_SQC_SPLF_M
mdefine_line|#define MSC_SQC_SPLF_M&t;&t;0x1f&t;&t;/* 5 bits wide */
DECL|macro|MSC_SQC_REPLYF
mdefine_line|#define MSC_SQC_REPLYF&t;0x080&t;&t;&t;/* Reply queue full */
DECL|macro|MSC_SQC_REMRF
mdefine_line|#define MSC_SQC_REMRF&t;0x040&t;&t;&t;/* Remote reply queue full */
DECL|macro|MSC_SQC_USERF
mdefine_line|#define MSC_SQC_USERF&t;0x020&t;&t;&t;/* User queue full */
DECL|macro|MSC_SQC_REMAF
mdefine_line|#define MSC_SQC_REMAF&t;0x010&t;&t;&t;/* Remote access queue full */
DECL|macro|MSC_SQC_SYSF
mdefine_line|#define MSC_SQC_SYSF&t;0x008&t;&t;&t;/* System queue full */
DECL|macro|MSC_SQC_PAUSE
mdefine_line|#define MSC_SQC_PAUSE&t;0x004&t;&t;&t;/* Send Queue pause */
DECL|macro|MSC_SQC_RMODE
mdefine_line|#define MSC_SQC_RMODE&t;0x003&t;&t;&t;/* Requested mode: */
DECL|macro|MSC_SQC_RMODE_BLOCK
mdefine_line|#define MSC_SQC_RMODE_BLOCK&t;0&t;&t;&t;/* blocking */
DECL|macro|MSC_SQC_RMODE_THRU
mdefine_line|#define MSC_SQC_RMODE_THRU&t;1&t;&t;&t;/* through */
DECL|macro|MSC_SQC_RMODE_NORMAL
mdefine_line|#define MSC_SQC_RMODE_NORMAL&t;2&t;&t;&t;/* or normal */
DECL|macro|MSC_SQPTR0
mdefine_line|#define MSC_SQPTR0&t;(MSC_BASE0 + 0x8)&t;/* Send Queue 0 pointers */
DECL|macro|MSC_SQPTR1
mdefine_line|#define MSC_SQPTR1&t;(MSC_BASE0 + 0x10)&t;/* Send Queue 1 pointers */
DECL|macro|MSC_SQPTR2
mdefine_line|#define MSC_SQPTR2&t;(MSC_BASE0 + 0x18)&t;/* Send Queue 2 pointers */
DECL|macro|MSC_SQPTR3
mdefine_line|#define MSC_SQPTR3&t;(MSC_BASE0 + 0x20)&t;/* Send Queue 3 pointers */
DECL|macro|MSC_SQPTR4
mdefine_line|#define MSC_SQPTR4&t;(MSC_BASE0 + 0x28)&t;/* Send Queue 4 pointers */
multiline_comment|/* bits in MSC_SQPTR[0-4] */
DECL|macro|MSC_SQP_MODE
mdefine_line|#define MSC_SQP_MODE&t;(1 &lt;&lt; 20)&t;&t;/* 64/32 word queue mode */
DECL|macro|MSC_SQP_BP_SH
mdefine_line|#define MSC_SQP_BP_SH&t;17&t;&t;&t;/* bit no. for base ptr */
DECL|macro|MSC_SQP_BP_M
mdefine_line|#define MSC_SQP_BP_M&t;7&t;&t;&t;/* (it&squot;s 3 bits wide) */
DECL|macro|MSC_SQP_CNT_SH
mdefine_line|#define MSC_SQP_CNT_SH&t;12&t;&t;&t;/* bit no. for count */
DECL|macro|MSC_SQP_CNT_M
mdefine_line|#define MSC_SQP_CNT_M&t;0x1f&t;&t;&t;/* (it&squot;s 5 bits wide) */
DECL|macro|MSC_SQP_RP_SH
mdefine_line|#define MSC_SQP_RP_SH&t;6&t;&t;&t;/* bit no. for read ptr */
DECL|macro|MSC_SQP_RP_M
mdefine_line|#define MSC_SQP_RP_M&t;0x3f&t;&t;&t;/* (it&squot;s 6 bits wide() */
DECL|macro|MSC_SQP_WP_SH
mdefine_line|#define MSC_SQP_WP_SH&t;0&t;&t;&t;/* bit no. for write ptr */
DECL|macro|MSC_SQP_WP_M
mdefine_line|#define MSC_SQP_WP_M&t;0x3f&t;&t;&t;/* (it&squot;s 6 bits wide() */
DECL|macro|MSC_OPTADR
mdefine_line|#define MSC_OPTADR&t;(MSC_BASE0 + 0x30)&t;/* option memory address */
DECL|macro|MSC_MASCTRL
mdefine_line|#define MSC_MASCTRL&t;(MSC_BASE0 + 0x38)&t;/* Mem Access Sequencer ctrl */
multiline_comment|/* Bits in MSC_MASCTRL */
DECL|macro|MSC_MASC_SPAUSE
mdefine_line|#define MSC_MASC_SPAUSE&t;0x80&t;&t;&t;/* Send MAS pause */
DECL|macro|MSC_MASC_RPAUSE
mdefine_line|#define MSC_MASC_RPAUSE&t;0x40&t;&t;&t;/* Recv MAS pause */
DECL|macro|MSC_MASC_SFEXIT
mdefine_line|#define MSC_MASC_SFEXIT&t;0x20&t;&t;&t;/* Send MAS fault/exit */
DECL|macro|MSC_MASC_RFEXIT
mdefine_line|#define MSC_MASC_RFEXIT&t;0x10&t;&t;&t;/* Recv MAS fault/exit */
DECL|macro|MSC_MASC_SREADY
mdefine_line|#define MSC_MASC_SREADY&t;0x08&t;&t;&t;/* Send MAS ready */
DECL|macro|MSC_MASC_RREADY
mdefine_line|#define MSC_MASC_RREADY&t;0x04&t;&t;&t;/* Recv MAS ready */
DECL|macro|MSC_MASC_SSTOP
mdefine_line|#define MSC_MASC_SSTOP&t;0x02&t;&t;&t;/* Send MAS is stopped */
DECL|macro|MSC_MASC_RSTOP
mdefine_line|#define MSC_MASC_RSTOP&t;0x01&t;&t;&t;/* Recv MAS is stopped */
DECL|macro|MSC_SMASADR
mdefine_line|#define MSC_SMASADR&t;(MSC_BASE0 + 0x40)&t;/* Send Mem Acc Seq address */
DECL|macro|MSC_RMASADR
mdefine_line|#define MSC_RMASADR&t;(MSC_BASE0 + 0x48)&t;/* Recv Mem Acc Seq address */
DECL|macro|MSC_PID
mdefine_line|#define MSC_PID&t;&t;(MSC_BASE0 + 0x50)&t;/* Context number (proc id) */
DECL|macro|MSC_QWORDCNT
mdefine_line|#define MSC_QWORDCNT&t;(MSC_BASE0 + 0x60)&t;/* Queue word counts */
multiline_comment|/* Fields in MSC_QWORDCNT */
DECL|macro|MSC_QWDC_SYSCNT_SH
mdefine_line|#define MSC_QWDC_SYSCNT_SH&t;24&t;&t;/* bit# for system count */
DECL|macro|MSC_QWDC_SYSCNT_M
mdefine_line|#define MSC_QWDC_SYSCNT_M&t;0x3f&t;&t;/* 6 bits wide */
DECL|macro|MSC_QWDC_SYSLEN_SH
mdefine_line|#define MSC_QWDC_SYSLEN_SH&t;16&t;&t;/* bit# for len of sys cmd */
DECL|macro|MSC_QWDC_SYSLEN_M
mdefine_line|#define MSC_QWDC_SYSLEN_M&t;0x3f&t;&t;/* 6 bits wide */
DECL|macro|MSC_QWDC_USRCNT_SH
mdefine_line|#define MSC_QWDC_USRCNT_SH&t;8&t;&t;/* bit# for user count */
DECL|macro|MSC_QWDC_USRCNT_M
mdefine_line|#define MSC_QWDC_USRCNT_M&t;0x3f&t;&t;/* 6 bits wide */
DECL|macro|MSC_QWDC_USRLEN_SH
mdefine_line|#define MSC_QWDC_USRLEN_SH&t;0&t;&t;/* bit# for len of user cmd */
DECL|macro|MSC_QWDC_USRLEN_M
mdefine_line|#define MSC_QWDC_USRLEN_M&t;0x3f&t;&t;/* 6 bits wide */
DECL|macro|MSC_INTR
mdefine_line|#define MSC_INTR&t;(MSC_BASE0 + 0x70)&t;/* Interrupt control/status */
multiline_comment|/* Bit offsets of interrupt fields in MSC_INTR */
DECL|macro|MSC_INTR_QBMFUL_SH
mdefine_line|#define MSC_INTR_QBMFUL_SH&t;28&t;&t;/* Queue buffer full intr */
DECL|macro|MSC_INTR_SQFILL_SH
mdefine_line|#define MSC_INTR_SQFILL_SH&t;24&t;&t;/* Send queue fill intr */
DECL|macro|MSC_INTR_RBMISS_SH
mdefine_line|#define MSC_INTR_RBMISS_SH&t;20&t;&t;/* Ring buffer miss intr */
DECL|macro|MSC_INTR_RBFULL_SH
mdefine_line|#define MSC_INTR_RBFULL_SH&t;16&t;&t;/* Ring buffer full intr */
DECL|macro|MSC_INTR_RMASF_SH
mdefine_line|#define MSC_INTR_RMASF_SH&t;12&t;&t;/* Recv MAS fault intr */
DECL|macro|MSC_INTR_RMASE_SH
mdefine_line|#define MSC_INTR_RMASE_SH&t;8&t;&t;/* Recv MAS error intr */
DECL|macro|MSC_INTR_SMASF_SH
mdefine_line|#define MSC_INTR_SMASF_SH&t;4&t;&t;/* Send MAS fault intr */
DECL|macro|MSC_INTR_SMASE_SH
mdefine_line|#define MSC_INTR_SMASE_SH&t;0&t;&t;/* Send MAS error intr */
DECL|macro|MSC_PPIO
mdefine_line|#define MSC_PPIO&t;(MSC_BASE0 + 0x1000)&t;/* PArallel port I/O */
DECL|macro|MSC_PACSELECT
mdefine_line|#define MSC_PACSELECT&t;(MSC_BASE0 + 0x1008)&t;/* Performance analyser sel. */
DECL|macro|MSC_CIDRANGE
mdefine_line|#define MSC_CIDRANGE&t;(MSC_BASE0 + 0x1010)&t;/* Rel. Cell-id range limits */
multiline_comment|/* Fields in MSC_CIDRANGE */
DECL|macro|MSC_CIDR_LRX_SH
mdefine_line|#define MSC_CIDR_LRX_SH&t;&t;24&t;&t;/* Rel. X lower limit bit# */
DECL|macro|MSC_CIDR_LRX_M
mdefine_line|#define MSC_CIDR_LRX_M&t;&t;0xFF&t;&t;/* it&squot;s 8 bits wide */
DECL|macro|MSC_CIDR_HRX_SH
mdefine_line|#define MSC_CIDR_HRX_SH&t;&t;16&t;&t;/* Rel. X upper limit bit# */
DECL|macro|MSC_CIDR_HRX_M
mdefine_line|#define MSC_CIDR_HRX_M&t;&t;0xFF&t;&t;/* it&squot;s 8 bits wide */
DECL|macro|MSC_CIDR_LRY_SH
mdefine_line|#define MSC_CIDR_LRY_SH&t;&t;8&t;&t;/* Rel. Y lower limit bit# */
DECL|macro|MSC_CIDR_LRY_M
mdefine_line|#define MSC_CIDR_LRY_M&t;&t;0xFF&t;&t;/* it&squot;s 8 bits wide */
DECL|macro|MSC_CIDR_HRY_SH
mdefine_line|#define MSC_CIDR_HRY_SH&t;&t;0&t;&t;/* Rel. Y upper limit bit# */
DECL|macro|MSC_CIDR_HRY_M
mdefine_line|#define MSC_CIDR_HRY_M&t;&t;0xFF&t;&t;/* it&squot;s 8 bits wide */
DECL|macro|MSC_QBMPTR
mdefine_line|#define MSC_QBMPTR&t;(MSC_BASE0 + 0x1018)&t;/* Queue buffer mgr. ptrs */
multiline_comment|/* Fields in MSC_QBMPTR */
DECL|macro|MSC_QBMP_LIM_SH
mdefine_line|#define MSC_QBMP_LIM_SH&t;&t;24&t;&t;/* Pointer limit bit# */
DECL|macro|MSC_QBMP_LIM_M
mdefine_line|#define MSC_QBMP_LIM_M&t;&t;0x3F&t;&t;/* (6 bits wide) */
DECL|macro|MSC_QBMP_BP_SH
mdefine_line|#define MSC_QBMP_BP_SH&t;&t;16&t;&t;/* Base pointer bit# */
DECL|macro|MSC_QBMP_BP_M
mdefine_line|#define MSC_QBMP_BP_M&t;&t;0xFF&t;&t;/* (8 bits wide) */
DECL|macro|MSC_QBMP_WP_SH
mdefine_line|#define MSC_QBMP_WP_SH&t;&t;0&t;&t;/* Write pointer bit# */
DECL|macro|MSC_QBMP_WP_M
mdefine_line|#define MSC_QBMP_WP_M&t;&t;0xFFFF&t;&t;/* (16 bits wide) */
DECL|macro|MSC_SMASTWP
mdefine_line|#define MSC_SMASTWP&t;(MSC_BASE0 + 0x1030)&t;/* Send MAS virt page etc. */
DECL|macro|MSC_SMASREG
mdefine_line|#define MSC_SMASREG&t;(MSC_BASE0 + 0x1038)&t;/* Send MAS context etc. */
DECL|macro|MSC_RMASTWP
mdefine_line|#define MSC_RMASTWP&t;(MSC_BASE0 + 0x1040)&t;/* Recv MAS virt page etc. */
DECL|macro|MSC_RMASREG
mdefine_line|#define MSC_RMASREG&t;(MSC_BASE0 + 0x1048)&t;/* Recv MAS context etc. */
multiline_comment|/* Bits in MSC_[SR]MASREG */
DECL|macro|MSC_MASR_CONTEXT_SH
mdefine_line|#define MSC_MASR_CONTEXT_SH&t;20&t;&t;/* Context at bit 20 */
DECL|macro|MSC_MASR_CONTEXT_M
mdefine_line|#define MSC_MASR_CONTEXT_M&t;0xfff&t;&t;/* 12 bits wide */
DECL|macro|MSC_MASR_AVIO
mdefine_line|#define MSC_MASR_AVIO&t;&t;8&t;&t;/* Address violation bit */
DECL|macro|MSC_MASR_CMD
mdefine_line|#define MSC_MASR_CMD&t;&t;7&t;&t;/* MAS command bits */
DECL|macro|MSC_MASR_CMD_XFER
mdefine_line|#define MSC_MASR_CMD_XFER&t;0&t;&t;/* transfer data cmd */
DECL|macro|MSC_MASR_CMD_FOP
mdefine_line|#define MSC_MASR_CMD_FOP&t;5&t;&t;/* fetch &amp; operate cmd */
DECL|macro|MSC_MASR_CMD_INC
mdefine_line|#define MSC_MASR_CMD_INC&t;6&t;&t;/* increment cmd (i.e. flag) */
DECL|macro|MSC_MASR_CMD_CSI
mdefine_line|#define MSC_MASR_CMD_CSI&t;7&t;&t;/* compare &amp; swap cmd */
DECL|macro|MSC_HDGERRPROC
mdefine_line|#define MSC_HDGERRPROC&t;(MSC_BASE0 + 0x1050)&t;/* Header gen. error process */
DECL|macro|MSC_RHDERRPROC
mdefine_line|#define MSC_RHDERRPROC&t;(MSC_BASE0 + 0x1058)&t;/* Recv. header decoder err. */
DECL|macro|MSC_SMASCNT
mdefine_line|#define MSC_SMASCNT&t;(MSC_BASE0 + 0x1060)&t;/* Send MAS counters */
multiline_comment|/* Bits in MSC_SMASCNT */
DECL|macro|MSC_SMCT_ACCSZ_SH
mdefine_line|#define MSC_SMCT_ACCSZ_SH&t;28&t;&t;/* Access size at bit 28 */
DECL|macro|MSC_SMCT_ACCSZ_M
mdefine_line|#define MSC_SMCT_ACCSZ_M&t;7&t;&t;/* 3 bits wide */
DECL|macro|MSC_SMCT_MCNT_SH
mdefine_line|#define MSC_SMCT_MCNT_SH&t;8&t;&t;/* M(?) count at bit 8 */
DECL|macro|MSC_SMCT_MCNT_M
mdefine_line|#define MSC_SMCT_MCNT_M&t;&t;0xfffff&t;&t;/* 20 bits wide */
DECL|macro|MSC_SMCT_ICNT_SH
mdefine_line|#define MSC_SMCT_ICNT_SH&t;0&t;&t;/* I(?) count at bit 0 */
DECL|macro|MSC_SMCT_ICNT_M
mdefine_line|#define MSC_SMCT_ICNT_M&t;&t;0xff&t;&t;/* 8 bits wide */
DECL|macro|MSC_IRL
mdefine_line|#define MSC_IRL&t;&t;(MSC_BASE0 + 0x1070)&t;/* highest current int req */
DECL|macro|MSC_SIMMCHK
mdefine_line|#define MSC_SIMMCHK&t;(MSC_BASE0 + 0x1078)&t;/* DRAM type installed */
DECL|macro|MSC_SIMMCHK_MASK
mdefine_line|#define MSC_SIMMCHK_MASK 0x00000008
DECL|macro|MSC_SQRAM
mdefine_line|#define MSC_SQRAM&t;(MSC_BASE0 + 0x2000)&t;/* Send Queue RAM (to +23f8) */
DECL|macro|MSC_VERSION
mdefine_line|#define MSC_VERSION&t;(MSC_BASE0 + 0x3000)&t;/* MSC+ version */
DECL|macro|MSC_NR_RBUFS
mdefine_line|#define MSC_NR_RBUFS 3
DECL|macro|MSC_RBMBWP0
mdefine_line|#define MSC_RBMBWP0&t;(MSC_BASE0 + 0x4000)&t;/* Ring buf 0 base/write ptr */
DECL|macro|MSC_RBMMODE0
mdefine_line|#define MSC_RBMMODE0&t;(MSC_BASE0 + 0x4008)&t;/* Ring buf 0 mode/context */
DECL|macro|MSC_RBMBWP1
mdefine_line|#define MSC_RBMBWP1&t;(MSC_BASE0 + 0x4010)&t;/* Ring buf 1 base/write ptr */
DECL|macro|MSC_RBMMODE1
mdefine_line|#define MSC_RBMMODE1&t;(MSC_BASE0 + 0x4018)&t;/* Ring buf 1 mode/context */
DECL|macro|MSC_RBMBWP2
mdefine_line|#define MSC_RBMBWP2&t;(MSC_BASE0 + 0x4020)&t;/* Ring buf 2 base/write ptr */
DECL|macro|MSC_RBMMODE2
mdefine_line|#define MSC_RBMMODE2&t;(MSC_BASE0 + 0x4028)&t;/* Ring buf 2 mode/context */
DECL|macro|MSC_RBMRP0
mdefine_line|#define MSC_RBMRP0&t;(MSC_BASE0 + 0x5000)&t;/* Ring buf 0 read pointer */
DECL|macro|MSC_RBMRP1
mdefine_line|#define MSC_RBMRP1&t;(MSC_BASE0 + 0x6000)&t;/* Ring buf 1 read pointer */
DECL|macro|MSC_RBMRP2
mdefine_line|#define MSC_RBMRP2&t;(MSC_BASE0 + 0x7000)&t;/* Ring buf 2 read pointer */
multiline_comment|/* locations of queues in virtual memory */
DECL|macro|MSC_QUEUE_BASE
mdefine_line|#define MSC_QUEUE_BASE   0xfa800000
DECL|macro|MSC_PUT_QUEUE_S
mdefine_line|#define MSC_PUT_QUEUE_S  (MSC_QUEUE_BASE + 0*PAGE_SIZE)
DECL|macro|MSC_GET_QUEUE_S
mdefine_line|#define MSC_GET_QUEUE_S  (MSC_QUEUE_BASE + 1*PAGE_SIZE)
DECL|macro|MSC_XYG_QUEUE_S
mdefine_line|#define MSC_XYG_QUEUE_S  (MSC_QUEUE_BASE + 2*PAGE_SIZE)
DECL|macro|MSC_SEND_QUEUE_S
mdefine_line|#define MSC_SEND_QUEUE_S  (MSC_QUEUE_BASE + 3*PAGE_SIZE)
DECL|macro|MSC_CPUT_QUEUE_S
mdefine_line|#define MSC_CPUT_QUEUE_S  (MSC_QUEUE_BASE + 4*PAGE_SIZE)
DECL|macro|MSC_BSEND_QUEUE_S
mdefine_line|#define MSC_BSEND_QUEUE_S  (MSC_QUEUE_BASE + 5*PAGE_SIZE)
DECL|macro|MSC_CXYG_QUEUE_S
mdefine_line|#define MSC_CXYG_QUEUE_S  (MSC_QUEUE_BASE + 6*PAGE_SIZE)
DECL|macro|MSC_CGET_QUEUE_S
mdefine_line|#define MSC_CGET_QUEUE_S  (MSC_QUEUE_BASE + 7*PAGE_SIZE)
multiline_comment|/* the 4 interrupt ports - physical addresses (on bus 8) */
DECL|macro|MC_INTP_0
mdefine_line|#define MC_INTP_0        0x80004000
DECL|macro|MC_INTP_1
mdefine_line|#define MC_INTP_1        0x80005000
DECL|macro|MC_INTP_2
mdefine_line|#define MC_INTP_2        0x80006000
DECL|macro|MC_INTP_3
mdefine_line|#define MC_INTP_3        0x80007000
multiline_comment|/* the address used to send a remote signal - note that 32 pages &n; are used here - none of them are mapped to anything though */
DECL|macro|MSC_REM_SIGNAL
mdefine_line|#define MSC_REM_SIGNAL          (MSC_QUEUE_BASE + 0x10 * PAGE_SIZE)
DECL|macro|MSC_PUT_QUEUE
mdefine_line|#define MSC_PUT_QUEUE   (MSC_QUEUE_BASE + 0x100*PAGE_SIZE)
DECL|macro|MSC_GET_QUEUE
mdefine_line|#define MSC_GET_QUEUE   (MSC_QUEUE_BASE + 0x101*PAGE_SIZE)
DECL|macro|MSC_SEND_QUEUE
mdefine_line|#define MSC_SEND_QUEUE  (MSC_QUEUE_BASE + 0x102*PAGE_SIZE)
DECL|macro|MSC_XY_QUEUE
mdefine_line|#define MSC_XY_QUEUE    (MSC_QUEUE_BASE + 0x103*PAGE_SIZE)
DECL|macro|MSC_X_QUEUE
mdefine_line|#define MSC_X_QUEUE     (MSC_QUEUE_BASE + 0x104*PAGE_SIZE)
DECL|macro|MSC_Y_QUEUE
mdefine_line|#define MSC_Y_QUEUE     (MSC_QUEUE_BASE + 0x105*PAGE_SIZE)
DECL|macro|MSC_XYG_QUEUE
mdefine_line|#define MSC_XYG_QUEUE   (MSC_QUEUE_BASE + 0x106*PAGE_SIZE)
DECL|macro|MSC_XG_QUEUE
mdefine_line|#define MSC_XG_QUEUE    (MSC_QUEUE_BASE + 0x107*PAGE_SIZE)
DECL|macro|MSC_YG_QUEUE
mdefine_line|#define MSC_YG_QUEUE    (MSC_QUEUE_BASE + 0x108*PAGE_SIZE)
DECL|macro|MSC_CSI_QUEUE
mdefine_line|#define MSC_CSI_QUEUE   (MSC_QUEUE_BASE + 0x109*PAGE_SIZE)
DECL|macro|MSC_FOP_QUEUE
mdefine_line|#define MSC_FOP_QUEUE   (MSC_QUEUE_BASE + 0x10a*PAGE_SIZE)
DECL|macro|SYSTEM_RINGBUF_BASE
mdefine_line|#define SYSTEM_RINGBUF_BASE    (MSC_QUEUE_BASE + 0x200*PAGE_SIZE)
DECL|macro|SYSTEM_RINGBUF_ORDER
mdefine_line|#define SYSTEM_RINGBUF_ORDER 5
DECL|macro|SYSTEM_RINGBUF_SIZE
mdefine_line|#define SYSTEM_RINGBUF_SIZE ((1&lt;&lt;SYSTEM_RINGBUF_ORDER)*PAGE_SIZE)
DECL|macro|MSC_SYSTEM_DIRECT
mdefine_line|#define MSC_SYSTEM_DIRECT&t;(MSC_QUEUE_BASE + 0x700 * PAGE_SIZE)
DECL|macro|MSC_USER_DIRECT
mdefine_line|#define MSC_USER_DIRECT&t;&t;(MSC_QUEUE_BASE + 0x701 * PAGE_SIZE)
DECL|macro|MSC_REMOTE_DIRECT
mdefine_line|#define MSC_REMOTE_DIRECT&t;(MSC_QUEUE_BASE + 0x702 * PAGE_SIZE)
DECL|macro|MSC_REPLY_DIRECT
mdefine_line|#define MSC_REPLY_DIRECT&t;(MSC_QUEUE_BASE + 0x703 * PAGE_SIZE)
DECL|macro|MSC_REMREPLY_DIRECT
mdefine_line|#define MSC_REMREPLY_DIRECT&t;(MSC_QUEUE_BASE + 0x704 * PAGE_SIZE)
DECL|macro|MSC_SYSTEM_DIRECT_END
mdefine_line|#define MSC_SYSTEM_DIRECT_END&t;(MSC_QUEUE_BASE + 0x708 * PAGE_SIZE)
DECL|macro|MSC_USER_DIRECT_END
mdefine_line|#define MSC_USER_DIRECT_END&t;(MSC_QUEUE_BASE + 0x709 * PAGE_SIZE)
DECL|macro|MSC_REMOTE_DIRECT_END
mdefine_line|#define MSC_REMOTE_DIRECT_END&t;(MSC_QUEUE_BASE + 0x70a * PAGE_SIZE)
DECL|macro|MSC_REPLY_DIRECT_END
mdefine_line|#define MSC_REPLY_DIRECT_END&t;(MSC_QUEUE_BASE + 0x70b * PAGE_SIZE)
DECL|macro|MSC_REMREPLY_DIRECT_END
mdefine_line|#define MSC_REMREPLY_DIRECT_END&t;(MSC_QUEUE_BASE + 0x70c * PAGE_SIZE)
multiline_comment|/* AP1000+ Memory Controller (MC+) */
DECL|macro|MC_BASE0
mdefine_line|#define MC_BASE0&t;0xfa000000
DECL|macro|MC_DRAM_CTRL
mdefine_line|#define MC_DRAM_CTRL&t;(MC_BASE0 + 0x0)&t;/* DRAM control */
DECL|macro|MC_DRAM_CHKBIT
mdefine_line|#define MC_DRAM_CHKBIT&t;(MC_BASE0 + 0x8)&t;/* DRAM check bits */
DECL|macro|MC_DRAM_ERRADR
mdefine_line|#define MC_DRAM_ERRADR&t;(MC_BASE0 + 0x10)&t;/* DRAM error address */
DECL|macro|MC_DRAM_ERRSYN
mdefine_line|#define MC_DRAM_ERRSYN&t;(MC_BASE0 + 0x18)&t;/* DRAM error syndrome */
DECL|macro|MC_FREERUN
mdefine_line|#define MC_FREERUN&t;(MC_BASE0 + 0x20)&t;/* Free run ctr (12.5MHz) */
DECL|macro|MC_ITIMER0
mdefine_line|#define MC_ITIMER0&t;(MC_BASE0 + 0x28)&t;/* Interval timer 0 */
DECL|macro|MC_ITIMER1
mdefine_line|#define MC_ITIMER1&t;(MC_BASE0 + 0x30)&t;/* Interval timer 1 */
DECL|macro|MC_INTR
mdefine_line|#define MC_INTR&t;&t;(MC_BASE0 + 0x38)&t;/* Interrupt control/status */
multiline_comment|/* Interrupt control/status fields in MC_INTR */
DECL|macro|MC_INTR_ECCD_SH
mdefine_line|#define MC_INTR_ECCD_SH&t;&t;12&t;&t;/* ECC double (uncorr.) err */
DECL|macro|MC_INTR_ECCS_SH
mdefine_line|#define MC_INTR_ECCS_SH&t;&t;8&t;&t;/* ECC single (corr.) error */
DECL|macro|MC_INTR_ITIM1_SH
mdefine_line|#define MC_INTR_ITIM1_SH&t;4&t;&t;/* Interval timer 1 intr */
DECL|macro|MC_INTR_ITIM0_SH
mdefine_line|#define MC_INTR_ITIM0_SH&t;0&t;&t;/* Interval timer 0 intr */
DECL|macro|MC_CTP
mdefine_line|#define MC_CTP&t;&t;(MC_BASE0 + 0x50)&t;/* Context table pointer */
DECL|macro|MC_VBUS_FAST
mdefine_line|#define MC_VBUS_FAST&t;(MC_BASE0 + 0x60)&t;/* VBus fast data mode ctrl */
DECL|macro|MC_INTR_PORT
mdefine_line|#define MC_INTR_PORT&t;(MC_BASE0 + 0x68)&t;/* Interrupt port ctrl/stat */
multiline_comment|/* Interrupt control/status fields in MC_INTR_PORT */
DECL|macro|MC_INTP_3_SH
mdefine_line|#define MC_INTP_3_SH&t;&t;12&t;&t;/* port 0 (880007000) */
DECL|macro|MC_INTP_2_SH
mdefine_line|#define MC_INTP_2_SH&t;&t;8&t;&t;/* port 1 (880006000) */
DECL|macro|MC_INTP_1_SH
mdefine_line|#define MC_INTP_1_SH&t;&t;4&t;&t;/* port 1 (880005000) */
DECL|macro|MC_INTP_0_SH
mdefine_line|#define MC_INTP_0_SH&t;&t;0&t;&t;/* port 1 (880004000) */
DECL|macro|MC_PAC_COUNT
mdefine_line|#define MC_PAC_COUNT&t;(MC_BASE0 + 0x1000)&t;/* Perf. an. counters */
DECL|macro|MC_PAC_SELECT
mdefine_line|#define MC_PAC_SELECT&t;(MC_BASE0 + 0x1008)&t;/* Perf. an. ctr. select */
DECL|macro|MC_VERSION
mdefine_line|#define MC_VERSION&t;(MC_BASE0 + 0x3000)&t;/* MC+ version/date */
DECL|macro|MC_MMU_TLB4K
mdefine_line|#define MC_MMU_TLB4K&t;(MC_BASE0 + 0x6000)&t;/* MC+ TLB for 4k pages */
DECL|macro|MC_MMU_TLB256K
mdefine_line|#define MC_MMU_TLB256K&t;(MC_BASE0 + 0x7000)&t;/* MC+ TLB for 256k pages */
DECL|macro|MC_MMU_TLB4K_SIZE
mdefine_line|#define MC_MMU_TLB4K_SIZE 256
DECL|macro|MC_MMU_TLB256K_SIZE
mdefine_line|#define MC_MMU_TLB256K_SIZE 64
multiline_comment|/*&n; * Bit values for a standard AP1000 3-bit interrupt control/status field.&n; */
DECL|macro|AP_INTR_REQ
mdefine_line|#define AP_INTR_REQ&t;&t;1&t;/* interrupt request bit */
DECL|macro|AP_INTR_MASK
mdefine_line|#define AP_INTR_MASK&t;&t;2&t;/* interrupt mask bit (1 disables) */
DECL|macro|AP_INTR_WENABLE
mdefine_line|#define AP_INTR_WENABLE&t;&t;4&t;/* enable write to mask/req bits */
DECL|macro|AP_CLR_INTR_REQ
mdefine_line|#define AP_CLR_INTR_REQ&t;&t;4&t;/* clear req. bit (dismiss intr) */
DECL|macro|AP_CLR_INTR_MASK
mdefine_line|#define AP_CLR_INTR_MASK&t;5&t;/* clear mask bit (enable ints) */
DECL|macro|AP_SET_INTR_REQ
mdefine_line|#define AP_SET_INTR_REQ&t;&t;6&t;/* set request bit */
DECL|macro|AP_SET_INTR_MASK
mdefine_line|#define AP_SET_INTR_MASK&t;7&t;/* set mask bit (disable ints) */
multiline_comment|/*&n; * Bit field extraction/insertion macros.&n; */
DECL|macro|EXTFIELD
mdefine_line|#define EXTFIELD(val, fld)&t;(((val) &gt;&gt; fld ## _SH) &amp; fld ## _M)
DECL|macro|MKFIELD
mdefine_line|#define MKFIELD(val, fld)&t;(((val) &amp; fld ## _M) &lt;&lt; fld ## _SH)
DECL|macro|INSFIELD
mdefine_line|#define INSFIELD(dst, val, fld)&t;(((dst) &amp; ~(fld ## _M &lt;&lt; fld ## _SH)) &bslash;&n;&t;&t;&t;&t; | MKFIELD(val, fld))
multiline_comment|/* &n; * RTC registers &n; */
DECL|macro|RTC
mdefine_line|#define RTC 0xfff10000&t;/*&t;RTC system mode&t;*/
DECL|macro|RTC_CSR
mdefine_line|#define RTC_CSR &t;(RTC+0x0010)&t;/* RTC control&t;register   */
DECL|macro|RTC_STR
mdefine_line|#define RTC_STR   &t;(RTC+0x0020)&t;/* RTC status register&t;  */
DECL|macro|RTC_ITRR
mdefine_line|#define RTC_ITRR   &t;(RTC+0x0030)&t;/* RTC interrupt register  */
DECL|macro|RTC_RSTR
mdefine_line|#define RTC_RSTR   &t;(RTC+0x0070)&t;/* RTC reset register&t;   */&t; 
DECL|macro|RTC_RSTR_TR
mdefine_line|#define RTC_RSTR_TR&t;&t;0x00008000&t;/* RTC through mode */
DECL|macro|RTC_RSTR_TS
mdefine_line|#define RTC_RSTR_TS&t;&t;0x00004000&t;/* RTC test mode    */
DECL|macro|RTC_RSTR_ED
mdefine_line|#define RTC_RSTR_ED&t;&t;0x00002000&t;/* RTC reverse mode    */
DECL|macro|RTC_RSTR_AC
mdefine_line|#define RTC_RSTR_AC&t;&t;0x00001000&t;/* RTC long mode&t;*/
DECL|macro|RTC_RSTR_SN
mdefine_line|#define RTC_RSTR_SN&t;&t;0x00000800&t;/* SOUTH/NORTH direction */
DECL|macro|RTC_RSTR_EW
mdefine_line|#define RTC_RSTR_EW&t;&t;0x00000400&t;/* EAST/WEST direction&t; */
DECL|macro|RTC_RSTR_NC
mdefine_line|#define RTC_RSTR_NC&t;&t;0x00000200&t;/* get NORTH channel   */
DECL|macro|RTC_RSTR_SC
mdefine_line|#define RTC_RSTR_SC&t;&t;0x00000100&t;/* get SOUTH channel&t;*/
DECL|macro|RTC_RSTR_WC
mdefine_line|#define RTC_RSTR_WC&t;&t;0x00000080&t;/* get WEST channel&t;*/
DECL|macro|RTC_RSTR_EC
mdefine_line|#define RTC_RSTR_EC&t;&t;0x00000040&t;/* get EAST channel&t;*/
DECL|macro|RTC_RSTR_BM
mdefine_line|#define RTC_RSTR_BM&t;&t;0x00000020&t;/* broad also my cell&t;*/
DECL|macro|RTC_RSTR_RT
mdefine_line|#define RTC_RSTR_RT&t;&t;0x00000020&t;/* reset  &t;&t;*/
DECL|macro|RTC_ITRR_PA
mdefine_line|#define RTC_ITRR_PA&t;&t;0x00040000&t;/* parity error for LBUS */
DECL|macro|RTC_ITRR_LR
mdefine_line|#define RTC_ITRR_LR&t;&t;0x00020000&t;/* MSC read but FIFO is empty*/
DECL|macro|RTC_ITRR_LW
mdefine_line|#define RTC_ITRR_LW&t;&t;0x00010000&t;/* MSC write but FIFO is full*/
DECL|macro|RTC_ITRR_AL
mdefine_line|#define RTC_ITRR_AL&t;&t;0x00008000&t;/* specify end data in data transfer */
DECL|macro|RTC_ITRR_DN
mdefine_line|#define RTC_ITRR_DN&t;&t;0x00002000&t;/* parity error in NORTH channel  */
DECL|macro|RTC_ITRR_DS
mdefine_line|#define RTC_ITRR_DS&t;&t;0x00001000&t;/* parity error in SOUTH channel&t;&t;*/
DECL|macro|RTC_ITRR_DW
mdefine_line|#define RTC_ITRR_DW&t;&t;0x00000800&t;/* parity error in WEST channel&t;&t;&t;*/
DECL|macro|RTC_ITRR_DE
mdefine_line|#define RTC_ITRR_DE&t;&t;0x00000400&t;/* parity error in EAST channel&t;&t;&t;*/
DECL|macro|RTC_ITRR_BD
mdefine_line|#define RTC_ITRR_BD&t;&t;0x00000200&t;/* receive 2 kind of broad data&t;&t;&t;*/
DECL|macro|RTC_ITRR_EW
mdefine_line|#define RTC_ITRR_EW&t;&t;0x00000100&t;/* control to write error bits&t;&t;&t;*/
DECL|macro|RTC_ITRR_EM
mdefine_line|#define RTC_ITRR_EM&t;&t;0x00000080&t;/* mask error interrupt request&t;&t;&t;*/
DECL|macro|RTC_ITRR_ER
mdefine_line|#define RTC_ITRR_ER&t;&t;0x00000040&t;/* error interrput request&t;&t;&t;&t;*/
DECL|macro|RTC_ITRR_SW
mdefine_line|#define RTC_ITRR_SW&t;&t;0x00000020&t;/* control to write SR, SM  */
DECL|macro|RTC_ITRR_SM
mdefine_line|#define RTC_ITRR_SM&t;&t;0x00000010&t;/* mask send interrupt&t;&t;&t;&t;&t;*/
DECL|macro|RTC_ITRR_SR
mdefine_line|#define RTC_ITRR_SR&t;&t;0x00000008&t;/* send interrupt request&t;&t;&t;&t;*/
DECL|macro|RTC_ITRR_RW
mdefine_line|#define RTC_ITRR_RW&t;&t;0x00000004&t;/* icontrol to read RR, RM&t;&t;&t;&t;*/
DECL|macro|RTC_ITRR_RM
mdefine_line|#define RTC_ITRR_RM&t;&t;0x00000002&t;/* mask read interrupt&t;&t;&t;&t;&t;*/
DECL|macro|RTC_ITRR_RR
mdefine_line|#define RTC_ITRR_RR&t;&t;0x00000001&t;/* receive interrupt request&t;&t;&t;*/
DECL|macro|RTC_ITRR_RWM
mdefine_line|#define RTC_ITRR_RWM (RTC_ITRR_RW|RTC_ITRR_RM)
DECL|macro|RTC_ITRR_SWM
mdefine_line|#define RTC_ITRR_SWM (RTC_ITRR_SW|RTC_ITRR_SM)
DECL|macro|RTC_ITRR_EWM
mdefine_line|#define RTC_ITRR_EWM (RTC_ITRR_EW|RTC_ITRR_EM)
DECL|macro|RTC_ITRR_RWR
mdefine_line|#define RTC_ITRR_RWR (RTC_ITRR_RW|RTC_ITRR_RR)
DECL|macro|RTC_ITRR_SWR
mdefine_line|#define RTC_ITRR_SWR (RTC_ITRR_SW|RTC_ITRR_SR)
DECL|macro|RTC_ITRR_EWR
mdefine_line|#define RTC_ITRR_EWR (RTC_ITRR_EW|RTC_ITRR_ER)
DECL|macro|RTC_ITRR_RRM
mdefine_line|#define RTC_ITRR_RRM (RTC_ITRR_RM|RTC_ITRR_RR)
DECL|macro|RTC_ITRR_SRM
mdefine_line|#define RTC_ITRR_SRM (RTC_ITRR_SM|RTC_ITRR_SR)
DECL|macro|RTC_ITRR_ERM
mdefine_line|#define RTC_ITRR_ERM (RTC_ITRR_EM|RTC_ITRR_ER)
DECL|macro|RTC_ITRR_RWMR
mdefine_line|#define RTC_ITRR_RWMR   (RTC_ITRR_RW|RTC_ITRR_RM|RTC_ITRR_RR)
DECL|macro|RTC_ITRR_SWMR
mdefine_line|#define RTC_ITRR_SWMR   (RTC_ITRR_SW|RTC_ITRR_SM|RTC_ITRR_SR)
DECL|macro|RTC_ITRR_EWMR
mdefine_line|#define RTC_ITRR_EWMR   (RTC_ITRR_EW|RTC_ITRR_EM|RTC_ITRR_ER)
DECL|macro|RTC_ITRR_ALLMSK
mdefine_line|#define RTC_ITRR_ALLMSK (RTC_ITRR_RWM|RTC_ITRR_SWM|RTC_ITRR_EWM)
DECL|macro|RTC_ITRR_ALLCLR
mdefine_line|#define RTC_ITRR_ALLCLR (RTC_ITRR_RW|RTC_ITRR_SW|RTC_ITRR_EW)
DECL|macro|RTC_ITRR_ALLWR
mdefine_line|#define RTC_ITRR_ALLWR  (RTC_ITRR_RWMR|RTC_ITRR_SWMR|RTC_ITRR_EWMR)
DECL|macro|RTC_ITRR_ALLRD
mdefine_line|#define RTC_ITRR_ALLRD  (RTC_ITRR_RRM|RTC_ITRR_SRM|RTC_ITRR_ERM)
multiline_comment|/*&n; * macros to manipulate context/task/pid numbers for parallel programs&n; */
DECL|macro|MPP_CONTEXT_BASE
mdefine_line|#define MPP_CONTEXT_BASE (AP_NUM_CONTEXTS - (NR_TASKS - MPP_TASK_BASE))
DECL|macro|MPP_TASK_TO_CTX
mdefine_line|#define MPP_TASK_TO_CTX(taskid) (((taskid) - MPP_TASK_BASE)+MPP_CONTEXT_BASE)
DECL|macro|MPP_CTX_TO_TASK
mdefine_line|#define MPP_CTX_TO_TASK(ctx) (((ctx)-MPP_CONTEXT_BASE)+MPP_TASK_BASE)
DECL|macro|MPP_IS_PAR_TASK
mdefine_line|#define MPP_IS_PAR_TASK(taskid) ((taskid) &gt;= MPP_TASK_BASE)
DECL|macro|MPP_IS_PAR_CTX
mdefine_line|#define MPP_IS_PAR_CTX(ctx) ((ctx) &gt;= MPP_CONTEXT_BASE)
multiline_comment|/*&n; * ioctls available on the ring buffer&n; */
DECL|macro|CAP_GETINIT
mdefine_line|#define CAP_GETINIT 1
DECL|macro|CAP_SYNC
mdefine_line|#define CAP_SYNC    2
DECL|macro|CAP_SETTASK
mdefine_line|#define CAP_SETTASK 3
DECL|macro|CAP_SETGANG
mdefine_line|#define CAP_SETGANG 4
DECL|macro|CAP_MAP
mdefine_line|#define CAP_MAP     5
multiline_comment|/*&n; * the structure shared by the kernel and the parallel tasks in the&n; * front of the cap_shared area&n; */
macro_line|#ifndef _ASM_
macro_line|#ifdef _APLIB_
DECL|struct|_kernel_cap_shared
r_struct
id|_kernel_cap_shared
(brace
DECL|member|rbuf_read_ptr
r_int
id|rbuf_read_ptr
suffix:semicolon
DECL|member|dummy
r_int
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* for future expansion */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * the mmap&squot;d ringbuffer region is layed out like this:&n;&n; shared page - one page&n; queue pages - 11 pages&n; ring buffer - xx pages&n; mirror of ring buffer - xx pages&n; */
DECL|macro|RBUF_VBASE
mdefine_line|#define RBUF_VBASE 0xd0000000
DECL|macro|RBUF_SHARED_PAGE_OFF
mdefine_line|#define RBUF_SHARED_PAGE_OFF 0
DECL|macro|RBUF_PUT_QUEUE
mdefine_line|#define RBUF_PUT_QUEUE             PAGE_SIZE
DECL|macro|RBUF_GET_QUEUE
mdefine_line|#define RBUF_GET_QUEUE           2*PAGE_SIZE
DECL|macro|RBUF_SEND_QUEUE
mdefine_line|#define RBUF_SEND_QUEUE          3*PAGE_SIZE
DECL|macro|RBUF_XY_QUEUE
mdefine_line|#define RBUF_XY_QUEUE            4*PAGE_SIZE
DECL|macro|RBUF_X_QUEUE
mdefine_line|#define RBUF_X_QUEUE             5*PAGE_SIZE
DECL|macro|RBUF_Y_QUEUE
mdefine_line|#define RBUF_Y_QUEUE             6*PAGE_SIZE
DECL|macro|RBUF_XYG_QUEUE
mdefine_line|#define RBUF_XYG_QUEUE           7*PAGE_SIZE
DECL|macro|RBUF_XG_QUEUE
mdefine_line|#define RBUF_XG_QUEUE            8*PAGE_SIZE
DECL|macro|RBUF_YG_QUEUE
mdefine_line|#define RBUF_YG_QUEUE            9*PAGE_SIZE
DECL|macro|RBUF_CSI_QUEUE
mdefine_line|#define RBUF_CSI_QUEUE          10*PAGE_SIZE
DECL|macro|RBUF_FOP_QUEUE
mdefine_line|#define RBUF_FOP_QUEUE          11*PAGE_SIZE
DECL|macro|RBUF_RING_BUFFER_OFFSET
mdefine_line|#define RBUF_RING_BUFFER_OFFSET 15*PAGE_SIZE
multiline_comment|/*&n; * number of MMU contexts to use&n; */
DECL|macro|AP_NUM_CONTEXTS
mdefine_line|#define AP_NUM_CONTEXTS 1024
DECL|macro|SYSTEM_CONTEXT
mdefine_line|#define SYSTEM_CONTEXT 1
multiline_comment|/*&n; * the default gang scheduling factor&n;*/
DECL|macro|DEF_GANG_FACTOR
mdefine_line|#define DEF_GANG_FACTOR 15
multiline_comment|/*&n; * useful for bypassing the cache&n;*/
macro_line|#ifdef _APLIB_
macro_line|#ifndef _ASM_
DECL|function|phys_8_in
r_static
r_inline
r_int
r_int
id|phys_8_in
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|word
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|paddr
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|0x28
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
multiline_comment|/*&n; * useful for bypassing the cache&n;*/
DECL|function|phys_9_in
r_static
r_inline
r_int
r_int
id|phys_9_in
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|word
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|paddr
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|0x29
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * DDV definitions &n;*/
DECL|macro|OBASE
mdefine_line|#define OBASE        (0xfff40010)
DECL|macro|OPTION_BASE
mdefine_line|#define OPTION_BASE 0xfc000000
DECL|macro|_OPIBUS_BASE
mdefine_line|#define _OPIBUS_BASE (OPTION_BASE + 0x800000)
macro_line|#ifdef CAP2_OPTION
DECL|macro|OPIBUS_BASE
mdefine_line|#define OPIBUS_BASE 0
macro_line|#else
DECL|macro|OPIBUS_BASE
mdefine_line|#define OPIBUS_BASE _OPIBUS_BASE
macro_line|#endif
DECL|macro|PBUF0
mdefine_line|#define PBUF0        (OPIBUS_BASE+0x7e0080)
DECL|macro|PBUF1
mdefine_line|#define PBUF1        (OPIBUS_BASE+0x7e0084)
DECL|macro|PBUF2
mdefine_line|#define PBUF2        (OPIBUS_BASE+0x7e0088)
DECL|macro|PBUF3
mdefine_line|#define PBUF3        (OPIBUS_BASE+0x7e008c)
DECL|macro|PIRQ
mdefine_line|#define PIRQ         (OPIBUS_BASE+0x7e0090)
DECL|macro|PRST
mdefine_line|#define PRST         (OPIBUS_BASE+0x7e0094)
DECL|macro|IRC0
mdefine_line|#define IRC0         (OPIBUS_BASE+0x7d00a0)
DECL|macro|IRC1
mdefine_line|#define IRC1         (OPIBUS_BASE+0x7d00a4)
DECL|macro|PRST_IRST
mdefine_line|#define PRST_IRST    (0x00000001)
DECL|macro|OPIU_RESET
mdefine_line|#define OPIU_RESET&t;&t;&t;(0x00000000)
DECL|macro|OPIU_OP
mdefine_line|#define OPIU_OP&t;&t;&t;&t;(PBUF0)
DECL|macro|LSTR
mdefine_line|#define LSTR(s) (_OPIBUS_BASE + (s))
macro_line|#endif /* _AP1000_APREG_H */
eof
