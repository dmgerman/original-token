multiline_comment|/***********************************************************************&n; *&t;FILE NAME : DC390.H&t;&t;&t;&t;&t;       *&n; *&t;     BY   : C.L. Huang&t;&t;&t;&t;&t;       *&n; *&t;Description: Device Driver for Tekram DC-390(T) PCI SCSI       *&n; *&t;&t;     Bus Master Host Adapter&t;&t;&t;       *&n; ***********************************************************************/
multiline_comment|/* Kernel version autodetection */
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/* Convert Linux Version, Patch-level, Sub-level to LINUX_VERSION_CODE. */
DECL|macro|ASC_LINUX_VERSION
mdefine_line|#define ASC_LINUX_VERSION(V, P, S)&t;(((V) * 65536) + ((P) * 256) + (S))
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(1,3,50)
DECL|macro|VERSION_ELF_1_2_13
mdefine_line|#define VERSION_ELF_1_2_13
macro_line|#elseif LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(1,3,95)
DECL|macro|VERSION_1_3_85
mdefine_line|#define VERSION_1_3_85
macro_line|#else
DECL|macro|VERSION_2_0_0
mdefine_line|#define VERSION_2_0_0
macro_line|#endif
multiline_comment|/*&n; * AMD 53C974 driver, header file&n; */
macro_line|#ifndef DC390_H
DECL|macro|DC390_H
mdefine_line|#define DC390_H
macro_line|#if defined(HOSTS_C) || defined(MODULE)
macro_line|#ifdef&t;VERSION_2_0_0
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#else
macro_line|#include &lt;linux/scsicam.h&gt;
macro_line|#endif
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
macro_line|#ifdef&t;VERSION_2_0_0
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
macro_line|#else
r_extern
r_int
id|DC390_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;VERSION_ELF_1_2_13
r_extern
r_int
id|DC390_bios_param
c_func
(paren
id|Disk
op_star
id|disk
comma
r_int
id|devno
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#else
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
macro_line|#endif
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
mdefine_line|#define DC390_release NULL
macro_line|#endif
macro_line|#ifndef VERSION_ELF_1_2_13
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_tmscsim
suffix:semicolon
r_extern
r_int
id|tmscsim_proc_info
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
macro_line|#endif
macro_line|#ifdef&t;VERSION_2_0_0
DECL|macro|DC390_T
mdefine_line|#define DC390_T    {&t;&t;&t;&bslash;&n;&t;NULL,&t;/* *next */&t;&t;&bslash;&n;&t;NULL,&t;/* *usage_count */&t;&bslash;&n;&t;&amp;proc_scsi_tmscsim,&t;/* *proc_dir */ &t;&bslash;&n;&t;tmscsim_proc_info,&t;/* (*proc_info)() */&t;&bslash;&n;&t;&quot;Tekram DC390(T) V1.10 Dec-05-1996&quot;,  /* *name */ &bslash;&n;&t;DC390_detect,&t;&t;&t;&bslash;&n;&t;DC390_release,&t;/* (*release)() */&t;&bslash;&n;&t;NULL,&t;/* *(*info)() */&t;&bslash;&n;&t;NULL,&t;/* (*command)() */&t;&bslash;&n;&t;DC390_queue_command,&t;&bslash;&n;&t;DC390_abort,&t;&t;&bslash;&n;&t;DC390_reset,&t;&t;&bslash;&n;&t;NULL, /* slave attach */&bslash;&n;&t;DC390_bios_param,&t;&bslash;&n;&t;10,/* can queue(-1) */&t;&bslash;&n;&t;7, /* id(-1) */ &t;&bslash;&n;&t;SG_ALL, &t;&t;&bslash;&n;&t;2, /* cmd per lun(2) */ &bslash;&n;&t;0, /* present */&t;&bslash;&n;&t;0, /* unchecked isa dma */ &bslash;&n;&t;DISABLE_CLUSTERING&t;&bslash;&n;&t;}
macro_line|#endif
macro_line|#ifdef&t;VERSION_1_3_85
DECL|macro|DC390_T
mdefine_line|#define DC390_T    {&t;&t;&t;&bslash;&n;&t;NULL,&t;/* *next */&t;&t;&bslash;&n;&t;NULL,&t;/* *usage_count */&t;&bslash;&n;&t;&amp;proc_scsi_tmscsim,&t;/* *proc_dir */ &t;&bslash;&n;&t;tmscsim_proc_info,&t;/* (*proc_info)() */&t;&bslash;&n;&t;&quot;Tekram DC390(T) V1.10 Dec-05-1996&quot;,  /* *name */ &bslash;&n;&t;DC390_detect,&t;&t;&t;&bslash;&n;&t;DC390_release,&t;/* (*release)() */&t;&bslash;&n;&t;NULL,&t;/* *(*info)() */&t;&bslash;&n;&t;NULL,&t;/* (*command)() */&t;&bslash;&n;&t;DC390_queue_command,&t;&bslash;&n;&t;DC390_abort,&t;&t;&bslash;&n;&t;DC390_reset,&t;&t;&bslash;&n;&t;NULL, /* slave attach */&bslash;&n;&t;DC390_bios_param,&t;&bslash;&n;&t;10,/* can queue(-1) */&t;&bslash;&n;&t;7, /* id(-1) */ &t;&bslash;&n;&t;SG_ALL, &t;&t;&bslash;&n;&t;2, /* cmd per lun(2) */ &bslash;&n;&t;0, /* present */&t;&bslash;&n;&t;0, /* unchecked isa dma */ &bslash;&n;&t;DISABLE_CLUSTERING&t;&bslash;&n;&t;}
macro_line|#endif
macro_line|#ifdef&t;VERSION_ELF_1_2_13
DECL|macro|DC390_T
mdefine_line|#define DC390_T     {&t;&t;&bslash;&n;&t;NULL,&t;&t;&t;&bslash;&n;&t;NULL,&t;&t;&t;&bslash;&n;&t;&quot;Tekram DC390(T) V1.10 Dec-05-1996&quot;,&bslash;&n;&t;DC390_detect,&t;&t;&bslash;&n;&t;DC390_release,&t;&t;&t;&bslash;&n;&t;NULL, /* info */&t;&bslash;&n;&t;NULL, /* command, deprecated */ &bslash;&n;&t;DC390_queue_command,&t;&bslash;&n;&t;DC390_abort,&t;&t;&bslash;&n;&t;DC390_reset,&t;&t;&bslash;&n;&t;NULL, /* slave attach */&bslash;&n;&t;DC390_bios_param,&t;&bslash;&n;&t;10,/* can queue(-1) */&t;&bslash;&n;&t;7, /* id(-1) */ &t;&bslash;&n;&t;16,/* old (SG_ALL) */&t;&bslash;&n;&t;2, /* cmd per lun(2) */ &bslash;&n;&t;0, /* present */&t;&bslash;&n;&t;0, /* unchecked isa dma */ &bslash;&n;&t;DISABLE_CLUSTERING&t;&bslash;&n;&t;}
macro_line|#endif
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */
macro_line|#endif /* DC390_H */
eof