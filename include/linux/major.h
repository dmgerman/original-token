macro_line|#ifndef _LINUX_MAJOR_H
DECL|macro|_LINUX_MAJOR_H
mdefine_line|#define _LINUX_MAJOR_H
multiline_comment|/*&n; * This file has definitions for major device numbers.&n; * For the device number assignments, see Documentation/devices.txt.&n; */
multiline_comment|/* limits */
DECL|macro|MAX_CHRDEV
mdefine_line|#define MAX_CHRDEV 64
DECL|macro|MAX_BLKDEV
mdefine_line|#define MAX_BLKDEV 64
DECL|macro|UNNAMED_MAJOR
mdefine_line|#define UNNAMED_MAJOR&t;0
DECL|macro|MEM_MAJOR
mdefine_line|#define MEM_MAJOR&t;1
DECL|macro|RAMDISK_MAJOR
mdefine_line|#define RAMDISK_MAJOR&t;1
DECL|macro|FLOPPY_MAJOR
mdefine_line|#define FLOPPY_MAJOR&t;2
DECL|macro|PTY_MASTER_MAJOR
mdefine_line|#define PTY_MASTER_MAJOR 2
DECL|macro|IDE0_MAJOR
mdefine_line|#define IDE0_MAJOR&t;3
DECL|macro|PTY_SLAVE_MAJOR
mdefine_line|#define PTY_SLAVE_MAJOR 3
DECL|macro|HD_MAJOR
mdefine_line|#define HD_MAJOR&t;IDE0_MAJOR
DECL|macro|TTY_MAJOR
mdefine_line|#define TTY_MAJOR&t;4
DECL|macro|TTYAUX_MAJOR
mdefine_line|#define TTYAUX_MAJOR&t;5
DECL|macro|LP_MAJOR
mdefine_line|#define LP_MAJOR&t;6
DECL|macro|VCS_MAJOR
mdefine_line|#define VCS_MAJOR&t;7
DECL|macro|LOOP_MAJOR
mdefine_line|#define LOOP_MAJOR&t;7
DECL|macro|SCSI_DISK_MAJOR
mdefine_line|#define SCSI_DISK_MAJOR&t;8
DECL|macro|SCSI_TAPE_MAJOR
mdefine_line|#define SCSI_TAPE_MAJOR&t;9
DECL|macro|MD_MAJOR
mdefine_line|#define MD_MAJOR        9
DECL|macro|MOUSE_MAJOR
mdefine_line|#define MOUSE_MAJOR&t;10
DECL|macro|SCSI_CDROM_MAJOR
mdefine_line|#define SCSI_CDROM_MAJOR 11
DECL|macro|QIC02_TAPE_MAJOR
mdefine_line|#define QIC02_TAPE_MAJOR 12
DECL|macro|XT_DISK_MAJOR
mdefine_line|#define XT_DISK_MAJOR&t;13
DECL|macro|SOUND_MAJOR
mdefine_line|#define SOUND_MAJOR&t;14
DECL|macro|CDU31A_CDROM_MAJOR
mdefine_line|#define CDU31A_CDROM_MAJOR 15
DECL|macro|SOCKET_MAJOR
mdefine_line|#define SOCKET_MAJOR&t;16
DECL|macro|GOLDSTAR_CDROM_MAJOR
mdefine_line|#define GOLDSTAR_CDROM_MAJOR 16
DECL|macro|AF_UNIX_MAJOR
mdefine_line|#define AF_UNIX_MAJOR&t;17
DECL|macro|OPTICS_CDROM_MAJOR
mdefine_line|#define OPTICS_CDROM_MAJOR 17
DECL|macro|AF_INET_MAJOR
mdefine_line|#define AF_INET_MAJOR&t;18
DECL|macro|SANYO_CDROM_MAJOR
mdefine_line|#define SANYO_CDROM_MAJOR 18
DECL|macro|CYCLADES_MAJOR
mdefine_line|#define CYCLADES_MAJOR  19
DECL|macro|CYCLADESAUX_MAJOR
mdefine_line|#define CYCLADESAUX_MAJOR 20
DECL|macro|MITSUMI_X_CDROM_MAJOR
mdefine_line|#define MITSUMI_X_CDROM_MAJOR 20
DECL|macro|SCSI_GENERIC_MAJOR
mdefine_line|#define SCSI_GENERIC_MAJOR 21
DECL|macro|Z8530_MAJOR
mdefine_line|#define Z8530_MAJOR 34
DECL|macro|IDE1_MAJOR
mdefine_line|#define IDE1_MAJOR&t;22
DECL|macro|MITSUMI_CDROM_MAJOR
mdefine_line|#define MITSUMI_CDROM_MAJOR 23
DECL|macro|CDU535_CDROM_MAJOR
mdefine_line|#define CDU535_CDROM_MAJOR 24
DECL|macro|STL_SERIALMAJOR
mdefine_line|#define STL_SERIALMAJOR 24
DECL|macro|MATSUSHITA_CDROM_MAJOR
mdefine_line|#define MATSUSHITA_CDROM_MAJOR 25
DECL|macro|STL_CALLOUTMAJOR
mdefine_line|#define STL_CALLOUTMAJOR 25
DECL|macro|MATSUSHITA_CDROM2_MAJOR
mdefine_line|#define MATSUSHITA_CDROM2_MAJOR 26
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR 27
DECL|macro|MATSUSHITA_CDROM3_MAJOR
mdefine_line|#define MATSUSHITA_CDROM3_MAJOR 27
DECL|macro|MATSUSHITA_CDROM4_MAJOR
mdefine_line|#define MATSUSHITA_CDROM4_MAJOR 28
DECL|macro|STL_SIOMEMMAJOR
mdefine_line|#define STL_SIOMEMMAJOR 28
DECL|macro|AZTECH_CDROM_MAJOR
mdefine_line|#define AZTECH_CDROM_MAJOR 29
DECL|macro|CM206_CDROM_MAJOR
mdefine_line|#define CM206_CDROM_MAJOR 32
DECL|macro|IDE2_MAJOR
mdefine_line|#define IDE2_MAJOR&t;33
DECL|macro|IDE3_MAJOR
mdefine_line|#define IDE3_MAJOR&t;34
DECL|macro|NETLINK_MAJOR
mdefine_line|#define NETLINK_MAJOR&t;36
DECL|macro|IDETAPE_MAJOR
mdefine_line|#define IDETAPE_MAJOR&t;37
multiline_comment|/*&n; * Tests for SCSI devices.&n; */
DECL|macro|SCSI_MAJOR
mdefine_line|#define SCSI_MAJOR(M) &bslash;&n;  ((M) == SCSI_DISK_MAJOR&t;&bslash;&n;   || (M) == SCSI_TAPE_MAJOR&t;&bslash;&n;   || (M) == SCSI_CDROM_MAJOR&t;&bslash;&n;   || (M) == SCSI_GENERIC_MAJOR)
DECL|function|scsi_major
r_static
r_inline
r_int
id|scsi_major
c_func
(paren
r_int
id|m
)paren
(brace
r_return
id|SCSI_MAJOR
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
