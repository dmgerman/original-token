multiline_comment|/***********************************************************************&n; *&t;FILE NAME : DC390.H&t;&t;&t;&t;&t;       *&n; *&t;     BY   : C.L. Huang&t;&t;&t;&t;&t;       *&n; *&t;Description: Device Driver for Tekram DC-390(T) PCI SCSI       *&n; *&t;&t;     Bus Master Host Adapter&t;&t;&t;       *&n; ***********************************************************************/
multiline_comment|/* $Id: dc390.h,v 2.12 1998/12/25 17:33:27 garloff Exp $ */
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/*&n; * DC390/AMD 53C974 driver, header file&n; */
macro_line|#ifndef DC390_H
DECL|macro|DC390_H
mdefine_line|#define DC390_H
DECL|macro|DC390_BANNER
mdefine_line|#define DC390_BANNER &quot;Tekram DC390/AM53C974&quot;
DECL|macro|DC390_VERSION
mdefine_line|#define DC390_VERSION &quot;2.0d 1998/12/25&quot;
macro_line|#if defined(HOSTS_C) || defined(MODULE)
macro_line|#include &lt;scsi/scsicam.h&gt;
r_extern
r_int
id|DC390_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|psht
)paren
suffix:semicolon
r_extern
r_int
id|DC390_queue_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
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
id|DC390_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|DC390_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
r_int
id|resetFlags
)paren
suffix:semicolon
r_extern
r_int
id|DC390_bios_param
c_func
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|devno
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_static
r_int
id|DC390_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|DC390_release
macro_line|# define DC390_release NULL
macro_line|#endif
r_extern
r_int
id|DC390_proc_info
c_func
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
DECL|macro|DC390_T
mdefine_line|#define DC390_T    {&t;&t;&t;&t;&t;&bslash;&n;   proc_name:      &quot;tmscsim&quot;,&t;&t;&t;&t;&bslash;&n;   proc_info:      DC390_proc_info,&t;&t;&t;&bslash;&n;   name:           DC390_BANNER &quot; V&quot; DC390_VERSION,&t;&bslash;&n;   detect:         DC390_detect,&t;&t;&t;&bslash;&n;   release:        DC390_release,&t;&t;&t;&bslash;&n;   queuecommand:   DC390_queue_command,&t;&t;&t;&bslash;&n;   abort:          DC390_abort,&t;&t;&t;&t;&bslash;&n;   reset:          DC390_reset,&t;&t;&t;&t;&bslash;&n;   bios_param:     DC390_bios_param,&t;&t;&t;&bslash;&n;   can_queue:      17,&t;&t;&t;&t;&t;&bslash;&n;   this_id:        7,&t;&t;&t;&t;&t;&bslash;&n;   sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;   cmd_per_lun:    8,&t;&t;&t;&t;&t;&bslash;&n;   use_clustering: DISABLE_CLUSTERING&t;&t;&t;&bslash;&n;   }
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */
macro_line|#endif /* DC390_H */
eof
