multiline_comment|/*&n; *&t;eata.h - used by the low-level driver for EATA/DMA SCSI host adapters.&n; *&n; */
macro_line|#ifndef _EATA_H
DECL|macro|_EATA_H
mdefine_line|#define _EATA_H
macro_line|#include &lt;linux/scsicam.h&gt;
DECL|macro|EATA_VERSION
mdefine_line|#define EATA_VERSION &quot;1.14.03&quot;
r_int
id|eata_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|eata_queuecommand
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
id|eata_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|macro|EATA
mdefine_line|#define EATA {  NULL, /* Ptr for modules */                    &bslash;&n;                NULL, /* usage count for modules */&t;       &bslash;&n;                &quot;EATA/DMA 2.0 rev. &quot; EATA_VERSION &quot; by &quot;       &bslash;&n;                &quot;Dario_Ballabio@milano.europe.dg.com.&quot;,        &bslash;&n;                eata_detect,&t;        &t;               &bslash;&n;                NULL, /* Release */     &t;               &bslash;&n;&t;&t;NULL,&t;                                       &bslash;&n;&t;&t;NULL,    &t;&t;&t;       &t;       &bslash;&n;&t;&t;eata_queuecommand,&t;&t;&t;       &bslash;&n;&t;&t;eata_abort,&t;&t;&t;&t;       &bslash;&n;&t;&t;eata_reset,&t;&t;&t;&t;       &bslash;&n;&t;        NULL,&t;&t;                               &bslash;&n;&t;&t;scsicam_bios_param,   &t;&t;&t;       &bslash;&n;&t;&t;0,   /* can_queue, reset by detect */          &bslash;&n;                7,   /* this_id, reset by detect */            &bslash;&n;                0,   /* sg_tablesize, reset by detect */       &bslash;&n;                0,   /* cmd_per_lun, reset by detect */        &bslash;&n;&t;&t;0,   /* number of boards present */            &bslash;&n;                1,   /* unchecked isa dma, reset by detect */  &bslash;&n;                ENABLE_CLUSTERING                              &bslash;&n;                }
macro_line|#endif
eof
