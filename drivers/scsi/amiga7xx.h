macro_line|#ifndef AMIGA7XX_H
macro_line|#include &lt;linux/types.h&gt;
r_int
id|amiga7xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|NCR53c7x0_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|NCR53c7xx_queue_command
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
id|NCR53c7xx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|NCR53c7x0_release
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|NCR53c7xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|NCR53c7x0_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 3
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 24
macro_line|#endif
macro_line|#if defined(HOSTS_C) || defined(MODULE)
macro_line|#include &lt;scsi/scsicam.h&gt;
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_amiga7xx
suffix:semicolon
DECL|macro|AMIGA7XX_SCSI
mdefine_line|#define AMIGA7XX_SCSI {/* next */                NULL,            &bslash;&n;&t;&t;      /* usage_count */         NULL,&t;         &bslash;&n;&t;&t;      /* proc_dir_entry */      NULL, &bslash;&n;&t;&t;      /* proc_info */           NULL,            &bslash;&n;&t;&t;      /* name */                &quot;Amiga NCR53c710 SCSI&quot;, &bslash;&n;&t;&t;      /* detect */              amiga7xx_detect,    &bslash;&n;&t;&t;      /* release */             NULL,   &bslash;&n;&t;&t;      /* info */                NULL,&t;         &bslash;&n;&t;&t;      /* command */             NULL,            &bslash;&n;&t;&t;      /* queuecommand */        NCR53c7xx_queue_command, &bslash;&n;&t;&t;      /* abort */               NCR53c7xx_abort,   &bslash;&n;&t;&t;      /* reset */               NCR53c7xx_reset,   &bslash;&n;&t;&t;      /* slave_attach */        NULL,            &bslash;&n;&t;&t;      /* bios_param */          scsicam_bios_param,   &bslash;&n;&t;&t;      /* can_queue */           24,       &bslash;&n;&t;&t;      /* this_id */             7,               &bslash;&n;&t;&t;      /* sg_tablesize */        127,          &bslash;&n;&t;&t;      /* cmd_per_lun */&t;        3,     &bslash;&n;&t;&t;      /* present */             0,               &bslash;&n;&t;&t;      /* unchecked_isa_dma */   0,               &bslash;&n;&t;&t;      /* use_clustering */      DISABLE_CLUSTERING }
macro_line|#endif
macro_line|#endif /* AMIGA7XX_H */
eof