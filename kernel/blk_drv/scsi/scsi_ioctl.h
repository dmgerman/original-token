macro_line|#ifndef _SCSI_IOCTL_H
DECL|macro|_SCSI_IOCTL_H
mdefine_line|#define _SCSI_IOCTL_H 
DECL|macro|SCSI_IOCTL_PROBE_HOST
mdefine_line|#define SCSI_IOCTL_PROBE_HOST 0
DECL|macro|SCSI_IOCTL_SEND_COMMAND
mdefine_line|#define SCSI_IOCTL_SEND_COMMAND 1
DECL|macro|SCSI_IOCTL_TEST_UNIT_READY
mdefine_line|#define SCSI_IOCTL_TEST_UNIT_READY 2
multiline_comment|/* The door lock/unlock constants are compatible with Sun constants for&n;   the cdrom */
DECL|macro|SCSI_IOCTL_DOORLOCK
mdefine_line|#define SCSI_IOCTL_DOORLOCK 0x5380&t;&t;/* lock the eject mechanism */
DECL|macro|SCSI_IOCTL_DOORUNLOCK
mdefine_line|#define SCSI_IOCTL_DOORUNLOCK 0x5381&t;&t;/* unlock the mechanism&t;  */
DECL|macro|SCSI_REMOVAL_PREVENT
mdefine_line|#define&t;SCSI_REMOVAL_PREVENT&t;1
DECL|macro|SCSI_REMOVAL_ALLOW
mdefine_line|#define&t;SCSI_REMOVAL_ALLOW&t;0
macro_line|#endif
eof
