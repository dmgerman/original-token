multiline_comment|/*&n; * atari_scsi.h -- Header file for the Atari native SCSI driver&n; *&n; * Copyright 1994 Roman Hodek &lt;Roman.Hodek@informatik.uni-erlangen.de&gt;&n; *&n; * (Loosely based on the work of Robert De Vries&squot; team)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#ifndef ATARI_SCSI_H
DECL|macro|ATARI_SCSI_H
mdefine_line|#define ATARI_SCSI_H
multiline_comment|/* (I_HAVE_OVERRUNS stuff removed) */
macro_line|#ifndef ASM
r_int
id|atari_scsi_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|atari_scsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|atari_scsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|atari_scsi_queue_command
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
id|atari_scsi_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|atari_scsi_proc_info
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|atari_scsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|atari_scsi_release
mdefine_line|#define atari_scsi_release NULL
macro_line|#endif
multiline_comment|/* The values for CMD_PER_LUN and CAN_QUEUE are somehow arbitrary. Higher&n; * values should work, too; try it! (but cmd_per_lun costs memory!) */
multiline_comment|/* But there seems to be a bug somewhere that requires CAN_QUEUE to be&n; * 2*CMD_OER_LUN. At least on a TT, no spurious timeouts seen since&n; * changed CMD_PER_LUN... */
multiline_comment|/* Note: The Falcon currently uses 8/1 setting due to unsolved problems with&n; * cmd_per_lun != 1 */
DECL|macro|ATARI_TT_CAN_QUEUE
mdefine_line|#define ATARI_TT_CAN_QUEUE&t;&t;16
DECL|macro|ATARI_TT_CMD_PER_LUN
mdefine_line|#define ATARI_TT_CMD_PER_LUN&t;&t;8
DECL|macro|ATARI_TT_SG_TABLESIZE
mdefine_line|#define ATARI_TT_SG_TABLESIZE&t;&t;SG_ALL
DECL|macro|ATARI_FALCON_CAN_QUEUE
mdefine_line|#define ATARI_FALCON_CAN_QUEUE&t;&t;8
DECL|macro|ATARI_FALCON_CMD_PER_LUN
mdefine_line|#define ATARI_FALCON_CMD_PER_LUN&t;1
DECL|macro|ATARI_FALCON_SG_TABLESIZE
mdefine_line|#define ATARI_FALCON_SG_TABLESIZE&t;SG_NONE
DECL|macro|DEFAULT_USE_TAGGED_QUEUING
mdefine_line|#define&t;DEFAULT_USE_TAGGED_QUEUING&t;0
macro_line|#if defined (HOSTS_C) || defined (MODULE)
DECL|macro|ATARI_SCSI
mdefine_line|#define ATARI_SCSI { NULL, NULL, NULL,&t;&t;&t;&t;&bslash;&n;  atari_scsi_proc_info,&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;Atari native SCSI&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_detect,&t;&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_release,&t;&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_info,&t;&t;&t;&t;&t;&t;&bslash;&n;  /* command */ NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_queue_command,&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_abort,&t;&t;&t;&t;&t;&t;&bslash;&n;  atari_scsi_reset,&t;&t;&t;&t;&t;&t;&bslash;&n;  /* slave_attach */&t;NULL,&t;&t;&t;&t;&t;&bslash;&n;  /* bios_param */&t;NULL,&t;&t;&t;&t;&t;&bslash;&n;  /* can queue */&t;0, /* initialized at run-time */&t;&bslash;&n;  /* host_id */&t;&t;0, /* initialized at run-time */&t;&bslash;&n;  /* scatter gather */&t;0, /* initialized at run-time */&t;&bslash;&n;  /* cmd per lun */&t;0, /* initialized at run-time */&t;&bslash;&n;  /* present */&t;&t;0,&t;&t;&t;&t;&t;&bslash;&n;  /* unchecked ISA DMA */ 0,&t;&t;&t;&t;&t;&bslash;&n;  /* use_clustering */&t;DISABLE_CLUSTERING }
macro_line|#endif
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define&t;NCR5380_implementation_fields&t;/* none */
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;  atari_scsi_reg_read( reg )
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) atari_scsi_reg_write( reg, value )
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr atari_scsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command atari_scsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort atari_scsi_abort
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info atari_scsi_proc_info
DECL|macro|NCR5380_dma_read_setup
mdefine_line|#define NCR5380_dma_read_setup(inst,d,c) atari_scsi_dma_setup (inst, d, c, 0)
DECL|macro|NCR5380_dma_write_setup
mdefine_line|#define NCR5380_dma_write_setup(inst,d,c) atari_scsi_dma_setup (inst, d, c, 1)
DECL|macro|NCR5380_dma_residual
mdefine_line|#define NCR5380_dma_residual(inst) atari_scsi_dma_residual( inst )
DECL|macro|NCR5380_dma_xfer_len
mdefine_line|#define&t;NCR5380_dma_xfer_len(i,cmd,phase) &bslash;&n;&t;atari_dma_xfer_len(cmd-&gt;SCp.this_residual,cmd,((phase) &amp; SR_IO) ? 0 : 1)
multiline_comment|/* Debugging printk definitions:&n; * DPRINTK() is the generic one, takes an NDEBUG_* mask as argument;&n; * all others are hardcoded to one NDEBUG_* code:&n; *&n; *  ARB  -&gt; arbitration&n; *  ASEN -&gt; auto-sense&n; *  DMA  -&gt; DMA&n; *  HSH  -&gt; PIO handshake&n; *  INF  -&gt; information transfer&n; *  INI  -&gt; initialization&n; *  INT  -&gt; interrupt&n; *  LNK  -&gt; linked commands&n; *  MAIN -&gt; NCR5380_main() control flow&n; *  NDAT -&gt; no data-out phase&n; *  NWR  -&gt; no write commands&n; *  PIO  -&gt; PIO transfers&n; *  PDMA -&gt; pseudo DMA (unused on Atari)&n; *  QU   -&gt; queues&n; *  RSL  -&gt; reselections&n; *  SEL  -&gt; selections&n; *  USL  -&gt; usleep cpde (unused on Atari)&n; *  LBS  -&gt; last byte sent (unused on Atari)&n; *  RSS  -&gt; restarting of selections&n; *  EXT  -&gt; extended messages&n; *  ABRT -&gt; aborting and resetting&n; *  TAG  -&gt; queue tag handling&n; *  MER  -&gt; merging of consec. buffers&n; *&n; */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(mask, format, args...)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (NDEBUG &amp; (mask))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_DEBUG format , ## args);&t;&bslash;&n;&t;} while(0)
DECL|macro|ARB_PRINTK
mdefine_line|#define ARB_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_ARBITRATION, format , ##args)
DECL|macro|ASEN_PRINTK
mdefine_line|#define ASEN_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_AUTOSENSE, format , ##args)
DECL|macro|DMA_PRINTK
mdefine_line|#define DMA_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_DMA, format , ##args)
DECL|macro|HSH_PRINTK
mdefine_line|#define HSH_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_HANDSHAKE, format , ##args)
DECL|macro|INF_PRINTK
mdefine_line|#define INF_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_INFORMATION, format , ##args)
DECL|macro|INI_PRINTK
mdefine_line|#define INI_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_INIT, format , ##args)
DECL|macro|INT_PRINTK
mdefine_line|#define INT_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_INTR, format , ##args)
DECL|macro|LNK_PRINTK
mdefine_line|#define LNK_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_LINKED, format , ##args)
DECL|macro|MAIN_PRINTK
mdefine_line|#define MAIN_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_MAIN, format , ##args)
DECL|macro|NDAT_PRINTK
mdefine_line|#define NDAT_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_NO_DATAOUT, format , ##args)
DECL|macro|NWR_PRINTK
mdefine_line|#define NWR_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_NO_WRITE, format , ##args)
DECL|macro|PIO_PRINTK
mdefine_line|#define PIO_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_PIO, format , ##args)
DECL|macro|PDMA_PRINTK
mdefine_line|#define PDMA_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_PSEUDO_DMA, format , ##args)
DECL|macro|QU_PRINTK
mdefine_line|#define QU_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_QUEUES, format , ##args)
DECL|macro|RSL_PRINTK
mdefine_line|#define RSL_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_RESELECTION, format , ##args)
DECL|macro|SEL_PRINTK
mdefine_line|#define SEL_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_SELECTION, format , ##args)
DECL|macro|USL_PRINTK
mdefine_line|#define USL_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_USLEEP, format , ##args)
DECL|macro|LBS_PRINTK
mdefine_line|#define LBS_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_LAST_BYTE_SENT, format , ##args)
DECL|macro|RSS_PRINTK
mdefine_line|#define RSS_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_RESTART_SELECT, format , ##args)
DECL|macro|EXT_PRINTK
mdefine_line|#define EXT_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_EXTENDED, format , ##args)
DECL|macro|ABRT_PRINTK
mdefine_line|#define ABRT_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_ABORT, format , ##args)
DECL|macro|TAG_PRINTK
mdefine_line|#define TAG_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_TAGS, format , ##args)
DECL|macro|MER_PRINTK
mdefine_line|#define MER_PRINTK(format, args...) &bslash;&n;&t;DPRINTK(NDEBUG_MERGING, format , ##args)
multiline_comment|/* conditional macros for NCR5380_print_{,phase,status} */
DECL|macro|NCR_PRINT
mdefine_line|#define NCR_PRINT(mask)&t;&bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print(instance) : (void)0)
DECL|macro|NCR_PRINT_PHASE
mdefine_line|#define NCR_PRINT_PHASE(mask) &bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print_phase(instance) : (void)0)
DECL|macro|NCR_PRINT_STATUS
mdefine_line|#define NCR_PRINT_STATUS(mask) &bslash;&n;&t;((NDEBUG &amp; (mask)) ? NCR5380_print_status(instance) : (void)0)
DECL|macro|NDEBUG_ANY
mdefine_line|#define NDEBUG_ANY&t;0xffffffff
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* ATARI_SCSI_H */
eof
