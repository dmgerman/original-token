multiline_comment|/*&n; *   u14-34f.h - used by the low-level driver for UltraStor 14F/34F&n; */
macro_line|#ifndef _U14_34F_H
DECL|macro|_U14_34F_H
mdefine_line|#define _U14_34F_H
r_int
id|u14_34f_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_queuecommand
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
id|u14_34f_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_biosparam
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|U14_34F_VERSION
mdefine_line|#define U14_34F_VERSION &quot;1.15.00&quot;
DECL|macro|ULTRASTOR_14_34F
mdefine_line|#define ULTRASTOR_14_34F {                                            &bslash;&n;                NULL, /* Ptr for modules */                           &bslash;&n;                NULL, /* usage count for modules */&t;              &bslash;&n;                &quot;UltraStor 14F/34F rev. &quot; U14_34F_VERSION &quot; &quot;,        &bslash;&n;                u14_34f_detect,                                       &bslash;&n;                NULL, /* Release */                                   &bslash;&n;                NULL,&t;&t;                                      &bslash;&n;                NULL,                                                 &bslash;&n;                u14_34f_queuecommand,                                 &bslash;&n;                u14_34f_abort,                                        &bslash;&n;                u14_34f_reset,                                        &bslash;&n;                NULL,                                                 &bslash;&n;                u14_34f_biosparam,                                    &bslash;&n;&t;&t;0,   /* can_queue, reset by detect */                 &bslash;&n;                7,   /* this_id, reset by detect */                   &bslash;&n;                0,   /* sg_tablesize, reset by detect */              &bslash;&n;                0,   /* cmd_per_lun, reset by detect */               &bslash;&n;&t;&t;0,   /* number of boards present */                   &bslash;&n;                1,   /* unchecked isa dma, reset by detect */         &bslash;&n;                0,   /* use_clustering, reset by detect */            &bslash;&n;                }
macro_line|#endif
eof
