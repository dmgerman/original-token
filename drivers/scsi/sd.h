multiline_comment|/*&n; *&t;sd.h Copyright (C) 1992 Drew Eckhardt &n; *&t;SCSI disk driver header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *&t; Modified by Eric Youngdale eric@aib.com to&n; *&t; add scatter-gather, multiple outstanding request, and other&n; *&t; enhancements.&n; */
macro_line|#ifndef _SD_H
DECL|macro|_SD_H
mdefine_line|#define _SD_H
multiline_comment|/*&n;    $Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/sd.h,v 1.1 1992/07/24 06:27:38 root Exp root $&n;*/
macro_line|#ifndef _SCSI_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#endif
macro_line|#ifndef _GENDISK_H
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#endif
r_extern
r_struct
id|hd_struct
op_star
id|sd
suffix:semicolon
DECL|struct|scsi_disk
r_typedef
r_struct
id|scsi_disk
(brace
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
multiline_comment|/* size in blocks */
DECL|member|sector_size
r_int
id|sector_size
suffix:semicolon
multiline_comment|/* size in bytes */
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|sector_bit_size
r_int
r_char
id|sector_bit_size
suffix:semicolon
multiline_comment|/* sector_size = 2 to the  bit size power */
DECL|member|sector_bit_shift
r_int
r_char
id|sector_bit_shift
suffix:semicolon
multiline_comment|/* power of 2 sectors per FS block */
DECL|member|ten
r_int
id|ten
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support ten byte read / write */
DECL|member|remap
r_int
id|remap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support remapping  */
DECL|member|has_part_table
r_int
id|has_part_table
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* has partition table */
DECL|typedef|Scsi_Disk
)brace
id|Scsi_Disk
suffix:semicolon
r_extern
id|Scsi_Disk
op_star
id|rscsi_disks
suffix:semicolon
r_extern
r_int
id|revalidate_scsidisk
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|maxusage
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
