macro_line|#ifndef _WD7000FASST_H
multiline_comment|/* $Id: 7000fasst.h,v 1.1 1992/07/24 06:27:38 root Exp root $&n; *&n; * Header file for the WD 7000-FASST driver for Linux&n; *&n; * $Log: 7000fasst.h,v $&n; * Revision 1.1  1992/07/24  06:27:38  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/07/05  08:32:32  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/05/15  18:38:05  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/04/02  03:23:13  drew&n; * Initial revision&n; *&n; * Revision 1.3  1992/01/27  14:46:29  tthorn&n; * *** empty log message ***&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|STATMASK
macro_line|#undef STATMASK
DECL|macro|CONTROL
macro_line|#undef CONTROL
DECL|macro|io_base
mdefine_line|#define io_base&t;&t;0x350
DECL|macro|intr_chan
mdefine_line|#define intr_chan&t;15
DECL|macro|dma_chan
mdefine_line|#define dma_chan&t;6
DECL|macro|OGMB_CNT
mdefine_line|#define OGMB_CNT&t;8
DECL|macro|ICMB_CNT
mdefine_line|#define ICMB_CNT&t;8
multiline_comment|/* I/O Port interface 4.2 */
multiline_comment|/* READ */
DECL|macro|ASC_STAT
mdefine_line|#define ASC_STAT io_base
DECL|macro|INT_IM
mdefine_line|#define INT_IM&t;0x80&t;&t;/* Interrupt Image Flag */
DECL|macro|CMD_RDY
mdefine_line|#define CMD_RDY&t;0x40&t;&t;/* Command Port Ready */
DECL|macro|CMD_REJ
mdefine_line|#define CMD_REJ&t;0x20&t;&t;/* Command Port Byte Rejected */
DECL|macro|ASC_INI
mdefine_line|#define ASC_INI&t;0x10&t;&t;/* ASC Initialized Flag */
DECL|macro|STATMASK
mdefine_line|#define STATMASK 0xf0&t;&t;/* The lower 4 Bytes are reserved */
multiline_comment|/* This register saves two purposes&n; * Diagnostics error&n; * Interrupt Status&n; */
DECL|macro|INTR_STAT
mdefine_line|#define INTR_STAT ASC_STAT+1
DECL|macro|ANYINTR
mdefine_line|#define ANYINTR&t;0x80&t;&t;/* Mailbox Service possible/required */
DECL|macro|IMB
mdefine_line|#define IMB&t;0x40&t;&t;/* 1 Incoming / 0 Outgoing */
DECL|macro|MBMASK
mdefine_line|#define MBMASK 0x3f
multiline_comment|/* if MSB is zero, the content of the lower ones keeps Diagnostic State *&n; * 00&t;Power-on, no diagnostics executed&n; * 01&t;No diagnostic Error Occured&n; * 02&t;RAM Failed&n; * 03&t;FIFO R/W Failed&n; * ...&n;*/
multiline_comment|/* WRITE */
DECL|macro|COMMAND
mdefine_line|#define COMMAND ASC_STAT
DECL|macro|INTR_ACK
mdefine_line|#define INTR_ACK ASC_STAT+1
DECL|macro|CONTROL
mdefine_line|#define CONTROL ASC_STAT+2
DECL|macro|INT_EN
mdefine_line|#define INT_EN&t;0x08&t;&t;/* Interrupt Enable&t;*/
DECL|macro|DMA_EN
mdefine_line|#define DMA_EN&t;0x04&t;&t;/* DMA Enable&t;&t;*/
DECL|macro|SCSI_RES
mdefine_line|#define SCSI_RES&t;0x02&t;/* SCSI Reset&t;&t;*/
DECL|macro|ASC_RES
mdefine_line|#define ASC_RES&t;0x01&t;&t;/* ASC Reset&t;&t;*/
multiline_comment|/* The DMA-Controller */
DECL|macro|DMA_MODE_REG
mdefine_line|#define DMA_MODE_REG&t;0xd6
DECL|macro|DMA_MASK_REG
mdefine_line|#define DMA_MASK_REG&t;0xd4
DECL|macro|S_DMA_MSK
mdefine_line|#define S_DMA_MSK&t;0x04
DECL|macro|DMA_CH
mdefine_line|#define DMA_CH&t;&t;0x02
DECL|macro|CASCADE
mdefine_line|#define&t;CASCADE&t;&t;0xc0
multiline_comment|/* Mailbox Definition 5.3 */
multiline_comment|/* These belong in scsi.h also */
DECL|macro|any2scsi
macro_line|#undef any2scsi
DECL|macro|any2scsi
mdefine_line|#define any2scsi(up, p)&t;&t;&t;&bslash;&n;(up)[0] = (((long)(p)) &gt;&gt; 16);&t;&bslash;&n;(up)[1] = ((long)(p)) &gt;&gt; 8;&t;&t;&bslash;&n;(up)[2] = ((long)(p));
DECL|macro|scsi2int
mdefine_line|#define scsi2int(up) ( (((long)*(up)) &lt;&lt; 16) + (((long)(up)[1]) &lt;&lt; 8) + ((long)(up)[2]) )
DECL|macro|xany2scsi
mdefine_line|#define xany2scsi(up, p)&t;&bslash;&n;(up)[0] = ((long)(p)) &gt;&gt; 24;&t;&bslash;&n;(up)[1] = ((long)(p)) &gt;&gt; 16;&t;&bslash;&n;(up)[2] = ((long)(p)) &gt;&gt; 8;&t;&bslash;&n;(up)[3] = ((long)(p));
DECL|macro|xscsi2int
mdefine_line|#define xscsi2int(up) ( (((long)(up)[0]) &lt;&lt; 24) + (((long)(up)[1]) &lt;&lt; 16) &bslash;&n;&t;&t;      + (((long)(up)[2]) &lt;&lt;  8) +  ((long)(up)[3]) )
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|macro|MAX_SENSE
mdefine_line|#define MAX_SENSE 14
DECL|struct|scb
r_struct
id|scb
(brace
multiline_comment|/* Command Control Block 5.4.1 */
DECL|member|op
id|unchar
id|op
suffix:semicolon
multiline_comment|/* Command Control Block Operation Code */
DECL|member|idlun
id|unchar
id|idlun
suffix:semicolon
multiline_comment|/* op=0,2:Target Id, op=1:Initiator Id */
multiline_comment|/* Outbound data transfer, length is checked*/
multiline_comment|/* Inbound data transfer, length is checked */
multiline_comment|/* Logical Unit Number */
DECL|member|scbdata
id|unchar
id|scbdata
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* SCSI Command Block */
DECL|member|sretstat
id|unchar
id|sretstat
suffix:semicolon
multiline_comment|/* SCSI Return Status */
DECL|member|vue
id|unchar
id|vue
suffix:semicolon
multiline_comment|/* Vendor Unique Error Code */
DECL|member|maxdata
id|unchar
id|maxdata
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Maximum Data Transfer Length */
DECL|member|dataptr
id|unchar
id|dataptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* SCSI Data Block Pointer */
DECL|member|linkptr
id|unchar
id|linkptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Next Command Link Pointer */
DECL|member|direc
id|unchar
id|direc
suffix:semicolon
multiline_comment|/* Transfer Direction */
DECL|member|reserved2
id|unchar
id|reserved2
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* SCSI Command Descriptor Block */
multiline_comment|/* REQUEST SENSE */
)brace
suffix:semicolon
r_int
id|wd7000fasst_detect
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|wd7000fasst_command
c_func
(paren
r_int
r_char
id|target
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buff
comma
r_int
id|bufflen
)paren
suffix:semicolon
r_int
id|wd7000fasst_queuecommand
c_func
(paren
id|unchar
id|target
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buff
comma
r_int
id|bufflen
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_int
comma
r_int
)paren
)paren
suffix:semicolon
r_int
id|wd7000fasst_abort
c_func
(paren
r_int
)paren
suffix:semicolon
r_char
op_star
id|wd7000fasst_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|wd7000fasst_reset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|macro|WD7000FASST
mdefine_line|#define WD7000FASST {&quot;Western Digital 7000FASST&quot;, wd7000fasst_detect,&t;&bslash;&n;&t;&t;wd7000fasst_info, wd7000fasst_command,&t;&t;&bslash;&n;&t;&t;wd7000fasst_queuecommand,&t;&t;&bslash;&n;&t;&t;wd7000fasst_abort,&t;&t;&t;&t;&bslash;&n;&t;&t;wd7000fasst_reset,&t;&t;&t;&t;&bslash;&n;&t;&t;1, 7, 0}
macro_line|#endif
eof
