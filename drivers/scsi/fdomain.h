multiline_comment|/* fdomain.h -- Header for Future Domain TMC-16x0 driver&n; * Created: Sun May  3 18:47:33 1992 by faith@cs.unc.edu&n; * Revised: Thu Oct 12 13:21:35 1995 by faith@acm.org&n; * Author: Rickard E. Faith, faith@cs.unc.edu&n; * Copyright 1992, 1993, 1994, 1995 Rickard E. Faith&n; *&n; * $Id: fdomain.h,v 5.12 1995/10/12 19:01:09 root Exp $&n;&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n;&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n;&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; */
macro_line|#ifndef _FDOMAIN_H
DECL|macro|_FDOMAIN_H
mdefine_line|#define _FDOMAIN_H
r_int
id|fdomain_16x0_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|fdomain_16x0_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|fdomain_16x0_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|fdomain_16x0_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|fdomain_16x0_reset
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
id|fdomain_16x0_queue
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
id|fdomain_16x0_biosparam
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
r_int
id|fdomain_16x0_proc_info
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
DECL|macro|FDOMAIN_16X0
mdefine_line|#define FDOMAIN_16X0 { proc_info:      fdomain_16x0_proc_info,           &bslash;&n;&t;&t;       detect:         fdomain_16x0_detect,              &bslash;&n;&t;&t;       info:           fdomain_16x0_info,                &bslash;&n;&t;&t;       command:        fdomain_16x0_command,             &bslash;&n;&t;&t;       queuecommand:   fdomain_16x0_queue,               &bslash;&n;&t;&t;       abort:          fdomain_16x0_abort,               &bslash;&n;&t;&t;       reset:          fdomain_16x0_reset,               &bslash;&n;&t;&t;       bios_param:     fdomain_16x0_biosparam,           &bslash;&n;&t;&t;       can_queue:      1, &t;&t;&t;&t; &bslash;&n;&t;&t;       this_id:        6, &t;&t;&t;&t; &bslash;&n;&t;&t;       sg_tablesize:   64, &t;&t;&t;&t; &bslash;&n;&t;&t;       cmd_per_lun:    1, &t;&t;&t;&t; &bslash;&n;&t;&t;       use_clustering: DISABLE_CLUSTERING }
macro_line|#endif
eof
