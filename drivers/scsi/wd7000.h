macro_line|#ifndef _WD7000_H
multiline_comment|/* $Id: $&n; *&n; * Header file for the WD-7000 driver for Linux&n; *&n; * John Boyd &lt;boyd@cis.ohio-state.edu&gt;  Jan 1994:&n; * This file has been reduced to only the definitions needed for the&n; * WD7000 host structure.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
r_int
id|wd7000_detect
c_func
(paren
id|Scsi_Host_Template
op_star
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
)paren
suffix:semicolon
r_int
id|wd7000_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|wd7000_biosparam
c_func
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
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0L
macro_line|#endif
multiline_comment|/*&n; *  In this version, sg_tablesize now defaults to WD7000_SG, and will&n; *  be set to SG_NONE for older boards.  This is the reverse of the&n; *  previous default, and was changed so that the driver-level&n; *  Scsi_Host_Template would reflect the driver&squot;s support for scatter/&n; *  gather.&n; *&n; *  Also, it has been reported that boards at Revision 6 support scatter/&n; *  gather, so the new definition of an &quot;older&quot; board has been changed&n; *  accordingly.&n; */
DECL|macro|WD7000_Q
mdefine_line|#define WD7000_Q    16
DECL|macro|WD7000_SG
mdefine_line|#define WD7000_SG   16
DECL|macro|WD7000
mdefine_line|#define WD7000 {&t;&t;&t;&t;&t;   &bslash;&n;&t;name:              &quot;Western Digital WD-7000&quot;,      &bslash;&n;&t;detect:            wd7000_detect,                  &bslash;&n;&t;command:           wd7000_command,&t;&t;   &bslash;&n;&t;queuecommand:      wd7000_queuecommand,&t;&t;   &bslash;&n;&t;abort:             wd7000_abort,&t;&t;   &bslash;&n;&t;reset:             wd7000_reset,&t;&t;   &bslash;&n;&t;bios_param:        wd7000_biosparam,               &bslash;&n;&t;can_queue:         WD7000_Q,&t;&t;&t;   &bslash;&n;&t;this_id:           7,&t;&t;&t;&t;   &bslash;&n;&t;sg_tablesize:      WD7000_SG,&t;&t;&t;   &bslash;&n;&t;cmd_per_lun:       1,&t;&t;&t;&t;   &bslash;&n;&t;unchecked_isa_dma: 1,&t;&t;&t;&t;   &bslash;&n;&t;use_clustering:    ENABLE_CLUSTERING}
macro_line|#endif
eof
