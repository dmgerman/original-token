multiline_comment|/*&n; * EESOX SCSI driver&n; *&n; * Copyright (C) 1997-1998 Russell King&n; */
macro_line|#ifndef EESOXSCSI_H
DECL|macro|EESOXSCSI_H
mdefine_line|#define EESOXSCSI_H
r_extern
r_int
id|eesoxscsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eesoxscsi_release
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
id|eesoxscsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eesoxscsi_proc_info
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
macro_line|#include &quot;fas216.h&quot;
DECL|macro|EESOXSCSI
mdefine_line|#define EESOXSCSI {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;proc_info:&t;eesoxscsi_proc_info,&t;&t;&t;&t;&t;&bslash;&n;name:&t;&t;&quot;EESOX SCSI&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;detect:&t;&t;eesoxscsi_detect,&t;/* detect&t;&t;*/&t;&bslash;&n;release:&t;eesoxscsi_release,&t;/* release&t;&t;*/&t;&bslash;&n;info:&t;&t;eesoxscsi_info,&t;&t;/* info&t;&t;&t;*/&t;&bslash;&n;command:&t;fas216_command,&t;&t;/* command&t;&t;*/&t;&bslash;&n;queuecommand:&t;fas216_queue_command,&t;/* queuecommand&t;&t;*/&t;&bslash;&n;abort:&t;&t;fas216_abort,&t;&t;/* abort&t;&t;*/&t;&bslash;&n;reset:&t;&t;fas216_reset,&t;&t;/* reset&t;&t;*/&t;&bslash;&n;bios_param:&t;scsicam_bios_param,&t;/* biosparam&t;&t;*/&t;&bslash;&n;can_queue:&t;CAN_QUEUE,&t;&t;/* can queue&t;&t;*/&t;&bslash;&n;this_id:&t;SCSI_ID,&t;&t;/* scsi host id&t;&t;*/&t;&bslash;&n;sg_tablesize:&t;SG_ALL,&t;&t;&t;/* sg_tablesize&t;&t;*/&t;&bslash;&n;cmd_per_lun:&t;CAN_QUEUE,&t;&t;/* cmd per lun&t;&t;*/&t;&bslash;&n;use_clustering:&t;DISABLE_CLUSTERING&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
macro_line|#include &lt;asm/dma.h&gt;
DECL|macro|NR_SG
mdefine_line|#define NR_SG&t;256
DECL|struct|control
r_struct
id|control
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
DECL|member|control
r_struct
id|control
id|control
suffix:semicolon
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
DECL|typedef|EESOXScsi_Info
)brace
id|EESOXScsi_Info
suffix:semicolon
macro_line|#endif /* HOSTS_C */
macro_line|#endif /* EESOXSCSI_H */
eof
