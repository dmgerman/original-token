macro_line|#ifndef _SCSI_IOCTL_H
DECL|macro|_SCSI_IOCTL_H
mdefine_line|#define _SCSI_IOCTL_H 
macro_line|#ifndef _CONFIG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
DECL|macro|SCSI_IOCTL_PROBE_HOST
mdefine_line|#define SCSI_IOCTL_PROBE_HOST 0
DECL|macro|SCSI_IOCTL_SEND_COMMAND
mdefine_line|#define SCSI_IOCTL_SEND_COMMAND 1
macro_line|#ifdef CONFIG_BLK_DEV_SD
multiline_comment|/* &t;Should start at 128&t;*/
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SD
multiline_comment|/* &t;Should start at 256&t;*/
macro_line|#endif
macro_line|#endif
eof
