multiline_comment|/*&n; * ARXE SCSI card driver&n; *&n; * Copyright (C) 1997 Russell King&n; * Changes to support ARXE 16-bit SCSI card by Stefan Hanske&n; */
macro_line|#ifndef ARXE_SCSI_H
DECL|macro|ARXE_SCSI_H
mdefine_line|#define ARXE_SCSI_H
DECL|macro|MANU_ARXE
mdefine_line|#define MANU_ARXE &t;0x0041
DECL|macro|PROD_ARXE_SCSI
mdefine_line|#define PROD_ARXE_SCSI&t;0x00be
r_extern
r_int
id|arxescsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arxescsi_release
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
id|arxescsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arxescsi_proc_info
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
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN&t;1
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
DECL|macro|ARXEScsi
mdefine_line|#define ARXEScsi {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;proc_info:&t;arxescsi_proc_info,&t;&t;&t;&t;&t;&t;&bslash;&n;name:&t;&t;&quot;ARXE SCSI card&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;detect:&t;&t;arxescsi_detect,&t;&t;/* detect&t;&t;*/&t;&bslash;&n;release:&t;arxescsi_release,&t;&t;/* release&t;&t;*/&t;&bslash;&n;info:&t;&t;arxescsi_info,&t;&t;&t;/* info&t;&t;&t;*/&t;&bslash;&n;command:&t;fas216_command,&t;&t;&t;/* command&t;&t;*/&t;&bslash;&n;queuecommand:&t;fas216_queue_command,&t;&t;/* queuecommand&t;&t;*/&t;&bslash;&n;abort:&t;&t;fas216_abort,&t;&t;&t;/* abort&t;&t;*/&t;&bslash;&n;reset:&t;&t;fas216_reset,&t;&t;&t;/* reset&t;&t;*/&t;&bslash;&n;bios_param:&t;scsicam_bios_param,&t;&t;/* biosparam&t;&t;*/&t;&bslash;&n;can_queue:&t;CAN_QUEUE,&t;&t;&t;/* can queue&t;&t;*/&t;&bslash;&n;this_id:&t;SCSI_ID,&t;&t;&t;/* scsi host id&t;&t;*/&t;&bslash;&n;sg_tablesize:&t;SG_ALL,&t;&t;&t;&t;/* sg_tablesize&t;&t;*/&t;&bslash;&n;cmd_per_lun:&t;CMD_PER_LUN,&t;&t;&t;/* cmd per lun&t;&t;*/&t;&bslash;&n;use_clustering:&t;DISABLE_CLUSTERING&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
multiline_comment|/* other info... */
DECL|member|cstatus
r_int
r_int
id|cstatus
suffix:semicolon
multiline_comment|/* card status register&t;*/
DECL|member|dmaarea
r_int
r_int
id|dmaarea
suffix:semicolon
multiline_comment|/* Pseudo DMA area&t;*/
DECL|typedef|ARXEScsi_Info
)brace
id|ARXEScsi_Info
suffix:semicolon
DECL|macro|CSTATUS_IRQ
mdefine_line|#define CSTATUS_IRQ&t;(1 &lt;&lt; 0)
DECL|macro|CSTATUS_DRQ
mdefine_line|#define CSTATUS_DRQ&t;(1 &lt;&lt; 0)
macro_line|#endif /* HOSTS_C */
macro_line|#endif /* ARXE_SCSI_H */
eof
