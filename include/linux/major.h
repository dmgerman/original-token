macro_line|#ifndef _LINUX_MAJOR_H
DECL|macro|_LINUX_MAJOR_H
mdefine_line|#define _LINUX_MAJOR_H
multiline_comment|/*&n; * This file has definitions for major device numbers&n; */
multiline_comment|/* limits */
DECL|macro|MAX_CHRDEV
mdefine_line|#define MAX_CHRDEV 32
DECL|macro|MAX_BLKDEV
mdefine_line|#define MAX_BLKDEV 32
multiline_comment|/*&n; * assignments&n; *&n; * devices are as follows (same as minix, so we can use the minix fs):&n; *&n; *      character              block                  comments&n; *      --------------------   --------------------   --------------------&n; *  0 - unnamed                unnamed                minor 0 = true nodev&n; *  1 - /dev/mem               ramdisk&n; *  2 -                        floppy&n; *  3 -                        hd&n; *  4 - /dev/tty*&n; *  5 - /dev/tty; /dev/cua*&n; *  6 - lp&n; *  7 - /dev/vcs*&n; *  8 -                        scsi disk&n; *  9 - scsi tape&n; * 10 - mice&n; * 11 -                        scsi cdrom&n; * 12 - qic02 tape&n; * 13 -                        xt disk&n; * 14 - sound card&n; * 15 -                        cdu31a cdrom&n; * 16 - sockets&n; * 17 - af_unix&n; * 18 - af_inet&n; * 19 -                                               UNUSED&n; * 20 -                                               UNUSED&n; * 21 - scsi generic&n; * 22 -                        (at2disk)&n; * 23 -                        mitsumi cdrom&n; * 24 -&t;                       sony535 cdrom&n; * 25 -                        matsushita cdrom       minors 0..3&n; * 26 -                        matsushita cdrom 2     minors 0..3&n; * 27 - qic117 tape            matsushita cdrom 3     minors 0..3&n; * 28 -                        matsushita cdrom 4     minors 0..3&n; * 29 -                        aztech/orchid/okano/wearnes cdrom&n; */
DECL|macro|UNNAMED_MAJOR
mdefine_line|#define UNNAMED_MAJOR&t;0
DECL|macro|MEM_MAJOR
mdefine_line|#define MEM_MAJOR&t;1
DECL|macro|FLOPPY_MAJOR
mdefine_line|#define FLOPPY_MAJOR&t;2
DECL|macro|IDE0_MAJOR
mdefine_line|#define IDE0_MAJOR&t;3
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
DECL|macro|SCSI_DISK_MAJOR
mdefine_line|#define SCSI_DISK_MAJOR&t;8
DECL|macro|SCSI_TAPE_MAJOR
mdefine_line|#define SCSI_TAPE_MAJOR&t;9
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
DECL|macro|AF_UNIX_MAJOR
mdefine_line|#define AF_UNIX_MAJOR&t;17
DECL|macro|AF_INET_MAJOR
mdefine_line|#define AF_INET_MAJOR&t;18
multiline_comment|/* unused: 19, 20 */
DECL|macro|SCSI_GENERIC_MAJOR
mdefine_line|#define SCSI_GENERIC_MAJOR 21
DECL|macro|IDE1_MAJOR
mdefine_line|#define IDE1_MAJOR&t;22
DECL|macro|MITSUMI_CDROM_MAJOR
mdefine_line|#define MITSUMI_CDROM_MAJOR 23
DECL|macro|CDU535_CDROM_MAJOR
mdefine_line|#define CDU535_CDROM_MAJOR 24
DECL|macro|MATSUSHITA_CDROM_MAJOR
mdefine_line|#define MATSUSHITA_CDROM_MAJOR 25
DECL|macro|MATSUSHITA_CDROM2_MAJOR
mdefine_line|#define MATSUSHITA_CDROM2_MAJOR 26
DECL|macro|MATSUSHITA_CDROM3_MAJOR
mdefine_line|#define MATSUSHITA_CDROM3_MAJOR 27
DECL|macro|MATSUSHITA_CDROM4_MAJOR
mdefine_line|#define MATSUSHITA_CDROM4_MAJOR 28
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR 27
DECL|macro|AZTECH_CDROM_MAJOR
mdefine_line|#define AZTECH_CDROM_MAJOR 29
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
