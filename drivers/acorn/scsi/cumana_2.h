multiline_comment|/*&n; * Cumana SCSI II driver&n; *&n; * Copyright (C) 1997-1998 Russell King&n; */
macro_line|#ifndef CUMANA_2_H
DECL|macro|CUMANA_2_H
mdefine_line|#define CUMANA_2_H
r_extern
r_int
id|cumanascsi_2_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cumanascsi_2_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|cumanascsi_2_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cumanascsi_2_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *)0)
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
multiline_comment|/*&n; * Default queue size&n; */
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE&t;1
macro_line|#endif
macro_line|#ifndef SCSI_ID
multiline_comment|/*&n; * Default SCSI host ID&n; */
DECL|macro|SCSI_ID
mdefine_line|#define SCSI_ID&t;&t;7
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#ifndef HOSTS_C
macro_line|#include &quot;fas216.h&quot;
macro_line|#endif
DECL|macro|CUMANASCSI_2
mdefine_line|#define CUMANASCSI_2 {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;proc_info:&t;&t;cumanascsi_2_proc_info,&t;&t;&t;&t;&bslash;&n;name:&t;&t;&t;&quot;Cumana SCSI II&quot;,&t;&t;&t;&t;&bslash;&n;detect:&t;&t;&t;cumanascsi_2_detect,&t;/* detect&t;&t;*/&t;&bslash;&n;release:&t;&t;cumanascsi_2_release,&t;/* release&t;&t;*/&t;&bslash;&n;info:&t;&t;&t;cumanascsi_2_info,&t;/* info&t;&t;&t;*/&t;&bslash;&n;command:&t;&t;fas216_command,&t;&t;/* command&t;&t;*/&t;&bslash;&n;queuecommand:&t;&t;fas216_queue_command,&t;/* queuecommand&t;&t;*/&t;&bslash;&n;abort:&t;&t;&t;fas216_abort,&t;&t;/* abort&t;&t;*/&t;&bslash;&n;reset:&t;&t;&t;fas216_reset,&t;&t;/* reset&t;&t;*/&t;&bslash;&n;bios_param:&t;&t;scsicam_bios_param,&t;/* biosparam&t;&t;*/&t;&bslash;&n;can_queue:&t;&t;CAN_QUEUE,&t;&t;/* can queue&t;&t;*/&t;&bslash;&n;this_id:&t;&t;SCSI_ID,&t;&t;/* scsi host id&t;&t;*/&t;&bslash;&n;sg_tablesize:&t;&t;SG_ALL,&t;&t;&t;/* sg_tablesize&t;&t;*/&t;&bslash;&n;cmd_per_lun:&t;&t;CAN_QUEUE,&t;&t;/* cmd per lun&t;&t;*/&t;&bslash;&n;unchecked_isa_dma:&t;0,&t;&t;&t;/* unchecked isa dma&t;*/&t;&bslash;&n;use_clustering:&t;&t;DISABLE_CLUSTERING&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
macro_line|#include &lt;asm/dma.h&gt;
DECL|macro|NR_SG
mdefine_line|#define NR_SG&t;256
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
multiline_comment|/* other info... */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* card status register&t;*/
DECL|member|alatch
r_int
r_int
id|alatch
suffix:semicolon
multiline_comment|/* Control register&t;*/
DECL|member|terms
r_int
r_int
id|terms
suffix:semicolon
multiline_comment|/* Terminator state&t;*/
DECL|member|dmaarea
r_int
r_int
id|dmaarea
suffix:semicolon
multiline_comment|/* Pseudo DMA area&t;*/
DECL|member|dmasg
id|dmasg_t
id|dmasg
(braket
id|NR_SG
)braket
suffix:semicolon
multiline_comment|/* Scatter DMA list&t;*/
DECL|typedef|CumanaScsi2_Info
)brace
id|CumanaScsi2_Info
suffix:semicolon
DECL|macro|CSTATUS_IRQ
mdefine_line|#define CSTATUS_IRQ&t;(1 &lt;&lt; 0)
DECL|macro|CSTATUS_DRQ
mdefine_line|#define CSTATUS_DRQ&t;(1 &lt;&lt; 1)
macro_line|#endif /* HOSTS_C */
macro_line|#endif /* CUMANASCSI_2_H */
eof
