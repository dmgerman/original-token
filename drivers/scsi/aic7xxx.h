multiline_comment|/*+M*************************************************************************&n; * Adaptec AIC7xxx device driver for Linux.&n; *&n; * Copyright (c) 1994 John Aycock&n; *   The University of Calgary Department of Computer Science.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; * &n; * $Id: aic7xxx.h,v 3.2 1996/07/23 03:37:26 deang Exp $&n; *-M*************************************************************************/
macro_line|#ifndef _aic7xxx_h
DECL|macro|_aic7xxx_h
mdefine_line|#define _aic7xxx_h
DECL|macro|AIC7XXX_H_VERSION
mdefine_line|#define AIC7XXX_H_VERSION  &quot;3.2.4&quot;
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(x,y,z) (((x)&lt;&lt;16)+((y)&lt;&lt;8)+(z))
macro_line|#endif
macro_line|#if defined(__i386__)
DECL|macro|AIC7XXX_BIOSPARAM
macro_line|#  define AIC7XXX_BIOSPARAM aic7xxx_biosparam
macro_line|#else
DECL|macro|AIC7XXX_BIOSPARAM
macro_line|#  define AIC7XXX_BIOSPARAM NULL
macro_line|#endif
multiline_comment|/*&n; * Scsi_Host_Template (see hosts.h) for AIC-7xxx - some fields&n; * to do with card config are filled in after the card is detected.&n; */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,1,65)
DECL|macro|AIC7XXX
mdefine_line|#define AIC7XXX&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;next: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;module: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_dir: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_info: aic7xxx_proc_info,&t;&t;&t;&t;&bslash;&n;&t;name: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;detect: aic7xxx_detect,&t;&t;&t;&t;&t;&bslash;&n;&t;release: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;info: aic7xxx_info,&t;&t;&t;&t;&t;&bslash;&n;&t;command: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: aic7xxx_queue,&t;&t;&t;&t;&bslash;&n;&t;eh_strategy_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_abort_handler: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_bus_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_host_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;abort: aic7xxx_abort,&t;&t;&t;&t;&t;&bslash;&n;&t;reset: aic7xxx_reset,&t;&t;&t;&t;&t;&bslash;&n;&t;slave_attach: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;bios_param: AIC7XXX_BIOSPARAM,&t;&t;&t;&t;&bslash;&n;&t;can_queue: 255,&t;&t;/* max simultaneous cmds      */&bslash;&n;&t;this_id: -1,&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: 0,&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 3,&t;&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;present: 0,&t;&t;/* number of 7xxx&squot;s present   */&bslash;&n;&t;unchecked_isa_dma: 0,&t;/* no memory DMA restrictions */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&bslash;&n;&t;use_new_eh_code: 0&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|AIC7XXX
mdefine_line|#define AIC7XXX&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;next: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;usage_count: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;proc_dir: NULL, &t;&t;&t;&t;&t;&bslash;&n;&t;proc_info: aic7xxx_proc_info,&t;&t;&t;&t;&bslash;&n;&t;name: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;detect: aic7xxx_detect,&t;&t;&t;&t;&t;&bslash;&n;&t;release: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;info: aic7xxx_info,&t;&t;&t;&t;&t;&bslash;&n;&t;command: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: aic7xxx_queue,&t;&t;&t;&t;&bslash;&n;&t;abort: aic7xxx_abort,&t;&t;&t;&t;&t;&bslash;&n;&t;reset: aic7xxx_reset,&t;&t;&t;&t;&t;&bslash;&n;&t;slave_attach: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;bios_param: AIC7XXX_BIOSPARAM,&t;&t;&t;&t;&bslash;&n;&t;can_queue: 255,&t;&t;/* max simultaneous cmds      */&bslash;&n;&t;this_id: -1,&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: 0,&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 3,&t;&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;present: 0,&t;&t;/* number of 7xxx&squot;s present   */&bslash;&n;&t;unchecked_isa_dma: 0,&t;/* no memory DMA restrictions */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING&t;&t;&t;&bslash;&n;}
macro_line|#endif
r_extern
r_int
id|aic7xxx_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|aic7xxx_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_extern
r_int
id|aic7xxx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|aic7xxx_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|aic7xxx_reset
c_func
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
id|aic7xxx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|aic7xxx_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|aic7xxx_proc_info
c_func
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
macro_line|#endif /* _aic7xxx_h */
eof
