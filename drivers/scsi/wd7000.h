macro_line|#ifndef _WD7000_H
multiline_comment|/* $Id: $&n; *&n; * Header file for the WD-7000 driver for Linux&n; *&n; * $Log: $&n; * Revision 1.1  1992/07/24  06:27:38  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/07/05  08:32:32  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/05/15  18:38:05  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/04/02  03:23:13  drew&n; * Initial revision&n; *&n; * Revision 1.3  1992/01/27  14:46:29  tthorn&n; * *** empty log message ***&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|STATMASK
macro_line|#undef STATMASK
DECL|macro|CONTROL
macro_line|#undef CONTROL
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE &t;0x350
DECL|macro|IRQ_LVL
mdefine_line|#define IRQ_LVL &t;15
DECL|macro|DMA_CH
mdefine_line|#define DMA_CH  &t;6
DECL|macro|OGMB_CNT
mdefine_line|#define OGMB_CNT&t;8
DECL|macro|ICMB_CNT
mdefine_line|#define ICMB_CNT&t;16
multiline_comment|/* I/O Port interface 4.2 */
multiline_comment|/* READ */
DECL|macro|ASC_STAT
mdefine_line|#define ASC_STAT IO_BASE
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
multiline_comment|/* This register serves two purposes&n; * Diagnostics error code&n; * Interrupt Status&n; */
DECL|macro|INTR_STAT
mdefine_line|#define INTR_STAT ASC_STAT+1
DECL|macro|ANYINTR
mdefine_line|#define ANYINTR&t;0x80&t;&t;/* Mailbox Service possible/required */
DECL|macro|IMB
mdefine_line|#define IMB&t;0x40&t;&t;/* 1 Incoming / 0 Outgoing */
DECL|macro|MBMASK
mdefine_line|#define MBMASK 0x3f
multiline_comment|/* if MSb is zero, the lower bits are diagnostic status *&n; * Diagnostics:&n; * 01&t;No diagnostic error occurred&n; * 02&t;RAM failure&n; * 03&t;FIFO R/W failed&n; * 04   SBIC register read/write failed&n; * 05   Initialization D-FF failed&n; * 06   Host IRQ D-FF failed&n; * 07   ROM checksum error&n; * Interrupt status (bitwise):&n; * 10NNNNNN   outgoing mailbox NNNNNN is free&n; * 11NNNNNN   incoming mailbox NNNNNN needs service&n; */
multiline_comment|/* WRITE */
DECL|macro|COMMAND
mdefine_line|#define COMMAND ASC_STAT
multiline_comment|/*&n; *  COMMAND opcodes&n; */
DECL|macro|NO_OP
mdefine_line|#define NO_OP             0
DECL|macro|INITIALIZATION
mdefine_line|#define INITIALIZATION    1     /* initialization after reset (10 bytes) */
DECL|macro|DISABLE_UNS_INTR
mdefine_line|#define DISABLE_UNS_INTR  2     /* disable unsolicited interrupts */
DECL|macro|ENABLE_UNS_INTR
mdefine_line|#define ENABLE_UNS_INTR   3     /* enable unsolicited interrupts */
DECL|macro|INTR_ON_FREE_OGMB
mdefine_line|#define INTR_ON_FREE_OGMB 4     /* interrupt on free OGMB */
DECL|macro|SCSI_SOFT_RESET
mdefine_line|#define SCSI_SOFT_RESET   5     /* SCSI soft reset */
DECL|macro|SCSI_HARD_RESET
mdefine_line|#define SCSI_HARD_RESET   6     /* SCSI hard reset acknowledge */
DECL|macro|START_OGMB
mdefine_line|#define START_OGMB        0x80  /* start command in OGMB (n) */
DECL|macro|SCAN_OGMBS
mdefine_line|#define SCAN_OGMBS        0xc0  /* start multiple commands, signature (n) */
multiline_comment|/*    where (n) = lower 6 bits */
multiline_comment|/*&n; *  For INITIALIZATION:&n; */
DECL|macro|BUS_ON
mdefine_line|#define BUS_ON            48    /* x 125ns, 48 = 6000ns, BIOS uses 8000ns */
DECL|macro|BUS_OFF
mdefine_line|#define BUS_OFF           24    /* x 125ns, 24 = 3000ns, BIOS uses 1875ns */
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
multiline_comment|/* Mailbox Definition */
DECL|struct|wd_mailbox
r_struct
id|wd_mailbox
(brace
DECL|member|status
id|unchar
id|status
suffix:semicolon
DECL|member|scbptr
id|unchar
id|scbptr
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
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
r_typedef
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
DECL|member|cdb
id|unchar
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* SCSI Command Block */
DECL|member|status
id|unchar
id|status
suffix:semicolon
multiline_comment|/* SCSI Return Status */
DECL|member|vue
id|unchar
id|vue
suffix:semicolon
multiline_comment|/* Vendor Unique Error Code */
DECL|member|maxlen
id|unchar
id|maxlen
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
multiline_comment|/* end of hardware SCB */
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
multiline_comment|/* Scsi_Cmnd using this SCB */
DECL|member|next
r_struct
id|scb
op_star
id|next
suffix:semicolon
multiline_comment|/* for lists of scbs */
DECL|typedef|Scb
)brace
id|Scb
suffix:semicolon
multiline_comment|/*&n; *  WD7000-specific scatter/gather element structure&n; */
DECL|struct|sgb
r_typedef
r_struct
id|sgb
(brace
DECL|member|len
id|unchar
id|len
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ptr
id|unchar
id|ptr
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|Sgb
)brace
id|Sgb
suffix:semicolon
multiline_comment|/*&n; *  Note:  MAX_SCBS _must_ be defined large enough to keep ahead of the&n; *  demand for SCBs, which will be at most WD7000_Q * WD7000_SG.  1 is&n; *  added to each because they can be 0.&n; */
DECL|macro|MAX_SCBS
mdefine_line|#define MAX_SCBS  ((WD7000_Q+1) * (WD7000_SG+1))
multiline_comment|/*&n; *  The driver is written to allow host-only commands to be executed.  These&n; *  use a 16-byte block called an ICB.&n; *&n; *  (Currently, only wd7000_info uses this, to get the firmware rev. level.)&n; */
DECL|macro|ICB_STATUS
mdefine_line|#define ICB_STATUS  16          /* set to icmb status by wd7000_intr_handle */
DECL|macro|ICB_PHASE
mdefine_line|#define ICB_PHASE   17          /* set to 0 by wd7000_intr_handle */
DECL|macro|ICB_LEN
mdefine_line|#define ICB_LEN     18          /* actually 16; this includes the above */
r_int
id|wd7000_detect
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|wd7000_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|wd7000_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|wd7000_abort
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
)paren
suffix:semicolon
r_const
r_char
op_star
id|wd7000_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|wd7000_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|wd7000_biosparam
c_func
(paren
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/*&n; *  Define WD7000_SG to be the number of Sgbs that will fit in a block of&n; *  size WD7000_SCRIBBLE.  WD7000_SCRIBBLE must be 512, 1024, 2048, or 4096.&n; *&n; *  The sg_tablesize value will default to SG_NONE for older boards (before&n; *  rev 7.0), but will be changed to WD7000_SG when a newer board is&n; *  detected.&n; */
DECL|macro|WD7000_SCRIBBLE
mdefine_line|#define WD7000_SCRIBBLE  512
DECL|macro|WD7000_Q
mdefine_line|#define WD7000_Q    OGMB_CNT
DECL|macro|WD7000_SG
mdefine_line|#define WD7000_SG   (WD7000_SCRIBBLE / sizeof(Sgb))
DECL|macro|WD7000
mdefine_line|#define WD7000 {&bslash;&n;&t;&quot;Western Digital WD-7000&quot;,      &bslash;&n;&t;wd7000_detect,                  &bslash;&n;&t;wd7000_info, wd7000_command,&t;&bslash;&n;&t;wd7000_queuecommand,&t;        &bslash;&n;&t;wd7000_abort,&t;&t;&t;&bslash;&n;&t;wd7000_reset,&t;&t;&t;&bslash;&n;&t;NULL,                           &bslash;&n;&t;wd7000_biosparam,               &bslash;&n;&t;WD7000_Q, 7, SG_NONE, 1, 0, 1}
macro_line|#endif
eof
