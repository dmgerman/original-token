macro_line|#ifndef _IBMMCA_H
DECL|macro|_IBMMCA_H
mdefine_line|#define _IBMMCA_H
multiline_comment|/*&n; * Low Level Driver for the IBM Microchannel SCSI Subsystem&n; */
multiline_comment|/*services provided to the higher level of Linux SCSI driver */
r_int
id|ibmmca_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|ibmmca_command
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ibmmca_queuecommand
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
id|ibmmca_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ibmmca_reset
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ibmmca_biosparam
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*structure for /proc filesystem */
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_ibmmca
suffix:semicolon
multiline_comment|/*initialization for Scsi_host_template type */
DECL|macro|IBMMCA
mdefine_line|#define IBMMCA {                                      &bslash;&n;          NULL,                 /*next*/              &bslash;&n;          NULL,                 /*module*/&t;      &bslash;&n;          &amp;proc_scsi_ibmmca,    /*proc_dir*/          &bslash;&n;          NULL,                 /*proc info fn*/      &bslash;&n;          &quot;IBMMCA&quot;,             /*name*/              &bslash;&n;          ibmmca_detect,        /*detect fn*/         &bslash;&n;          NULL,                 /*release fn*/        &bslash;&n;          NULL,                 /*info fn*/           &bslash;&n;          ibmmca_command,       /*command fn*/        &bslash;&n;          ibmmca_queuecommand,  /*queuecommand fn*/   &bslash;&n;          ibmmca_abort,         /*abort fn*/          &bslash;&n;          ibmmca_reset,         /*reset fn*/          &bslash;&n;          NULL,                 /*slave_attach fn*/   &bslash;&n;          ibmmca_biosparam,     /*bios fn*/           &bslash;&n;          16,                   /*can_queue*/         &bslash;&n;          7,                    /*set by detect*/     &bslash;&n;          16,                   /*sg_tablesize*/      &bslash;&n;          1,                    /*cmd_per_lun*/       &bslash;&n;          0,                    /*present*/           &bslash;&n;          0,                    /*unchecked_isa_dma*/ &bslash;&n;          ENABLE_CLUSTERING     /*use_clustering*/    &bslash;&n;        }
macro_line|#endif /* _IBMMCA_H */
eof
