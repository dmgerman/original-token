multiline_comment|/* &n; * Low Level Driver for the IBM Microchannel SCSI Subsystem&n; * (Headerfile, see README.ibmmca for description of the IBM MCA SCSI-driver&n; * For use under the GNU public license within the Linux-kernel project.&n; * This include file works only correctly with kernel 2.4.0 or higher!!! */
macro_line|#ifndef _IBMMCA_H
DECL|macro|_IBMMCA_H
mdefine_line|#define _IBMMCA_H
multiline_comment|/* Common forward declarations for all Linux-versions: */
multiline_comment|/* Interfaces to the midlevel Linux SCSI driver */
r_extern
r_int
id|ibmmca_proc_info
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
r_extern
r_int
id|ibmmca_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmmca_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmmca_command
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
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
r_extern
r_int
id|ibmmca_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmmca_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
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
multiline_comment|/*&n; * 2/8/98&n; * Note to maintainer of IBMMCA.  Do not change this initializer back to&n; * the old format.  Please ask eric@andante.jic.com if you have any questions&n; * about this, but it will break things in the future.&n; */
DECL|macro|IBMMCA
mdefine_line|#define IBMMCA {                                                      &bslash;&n;          proc_name:      &quot;ibmmca&quot;,             /*proc_name*/         &bslash;&n;&t;  proc_info:&t;  ibmmca_proc_info,     /*proc info fn*/      &bslash;&n;          name:           &quot;IBM SCSI-Subsystem&quot;, /*name*/              &bslash;&n;          detect:         ibmmca_detect,        /*detect fn*/         &bslash;&n;          release:        ibmmca_release,       /*release fn*/        &bslash;&n;          command:        ibmmca_command,       /*command fn*/        &bslash;&n;          queuecommand:   ibmmca_queuecommand,  /*queuecommand fn*/   &bslash;&n;          abort:          ibmmca_abort,         /*abort fn*/          &bslash;&n;          reset:          ibmmca_reset,         /*reset fn*/          &bslash;&n;          bios_param:     ibmmca_biosparam,     /*bios fn*/           &bslash;&n;          can_queue:      16,                   /*can_queue*/         &bslash;&n;          this_id:        7,                    /*set by detect*/     &bslash;&n;          sg_tablesize:   16,                   /*sg_tablesize*/      &bslash;&n;          cmd_per_lun:    1,                    /*cmd_per_lun*/       &bslash;&n;          unchecked_isa_dma: 0,                 /*32-Bit Busmaster */ &bslash;&n;          use_clustering: ENABLE_CLUSTERING     /*use_clustering*/    &bslash;&n;          }
macro_line|#endif /* _IBMMCA_H */
eof
