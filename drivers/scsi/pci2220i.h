multiline_comment|/****************************************************************************&n; * Perceptive Solutions, Inc. PCI-2220I device driver for Linux.&n; *&n; * pci2220i.h - Linux Host Driver for PCI-2220i EIDE Adapters&n; *&n; * Copyright (c) 1997-1999 Perceptive Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * Technical updates and product information at:&n; *  http://www.psidisk.com&n; *&n; * Please send questions, comments, bug reports to:&n; *  tech@psidisk.com Technical Support&n; *&n; ****************************************************************************/
macro_line|#ifndef _PCI2220I_H
DECL|macro|_PCI2220I_H
mdefine_line|#define _PCI2220I_H
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif 
DECL|macro|LINUXVERSION
mdefine_line|#define&t;LINUXVERSION(v,p,s)    (((v)&lt;&lt;16) + ((p)&lt;&lt;8) + (s))
singleline_comment|// function prototypes
r_int
id|Pci2220i_Detect
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_Command
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_QueueCommand
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
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
id|Pci2220i_Abort
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_Reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_int
id|Pci2220i_Release
(paren
r_struct
id|Scsi_Host
op_star
id|pshost
)paren
suffix:semicolon
r_int
id|Pci2220i_BiosParam
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
r_extern
r_struct
id|proc_dir_entry
id|Proc_Scsi_Pci2220i
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= LINUXVERSION(2,1,75)
DECL|macro|PCI2220I
mdefine_line|#define PCI2220I {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;next:&t;&t;&t;&t;&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;module:&t;&t;&t;&t;&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;proc_dir:&t;&t;&t;&t;&t;&amp;Proc_Scsi_Pci2220i,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;proc_info:&t;&t;&t;&t;&t;NULL,&t;/* let&squot;s not bloat the kernel */&bslash;&n;&t;&t;name:&t;&t;&t;&t;&t;&t;&quot;PCI-2220I/PCI-2240I&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;detect:&t;&t;&t;&t;&t;&t;Pci2220i_Detect,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;release:&t;&t;&t;&t;&t;Pci2220i_Release,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;info:&t;&t;&t;&t;&t;&t;NULL,&t;/* let&squot;s not bloat the kernel */&bslash;&n;&t;&t;command:&t;&t;&t;&t;&t;Pci2220i_Command,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;queuecommand:&t;&t;&t;&t;Pci2220i_QueueCommand,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;eh_strategy_handler:&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;eh_abort_handler:&t;&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;eh_device_reset_handler:&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;eh_bus_reset_handler:&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;eh_host_reset_handler:&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;abort:&t;&t;&t;&t;&t;&t;Pci2220i_Abort,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;reset:&t;&t;&t;&t;&t;&t;Pci2220i_Reset,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;slave_attach:&t;&t;&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;bios_param:&t;&t;&t;&t;&t;Pci2220i_BiosParam,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;can_queue:&t;&t;&t;&t;&t;1,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;this_id:&t;&t;&t;&t;&t;-1,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sg_tablesize:&t;&t;&t;&t;SG_ALL,&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cmd_per_lun:&t;&t;&t;&t;1,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;present:&t;&t;&t;&t;&t;0,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unchecked_isa_dma:&t;&t;&t;0,&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;use_clustering:&t;&t;&t;&t;DISABLE_CLUSTERING,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;use_new_eh_code:&t;&t;&t;0&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}
macro_line|#else
DECL|macro|PCI2220I
mdefine_line|#define PCI2220I { NULL, NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&amp;Proc_Scsi_Pci2220i,/* proc_dir_entry */&bslash;&n;&t;&t;&t;NULL,&t;&t;                &t;&t;&t;&bslash;&n;&t;&t;&t;&quot;PCI-2220I/PCI-2240I&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_Detect,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_Release,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;NULL,&t; &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_Command,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_QueueCommand,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_Abort,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_Reset,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;Pci2220i_BiosParam,                 &t;&bslash;&n;&t;&t;&t;1, &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;-1, &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SG_ALL,&t;&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;1, &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;0, &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;0, &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;DISABLE_CLUSTERING }
macro_line|#endif
macro_line|#endif
eof
