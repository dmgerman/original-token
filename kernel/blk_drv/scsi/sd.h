multiline_comment|/*&n; *&t;sd.h Copyright (C) 1992 Drew Eckhardt &n; *&t;SCSI disk driver header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SD_H
DECL|macro|_SD_H
mdefine_line|#define _SD_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/sd.h,v 1.1 1992/04/24 18:01:50 root Exp root $&n;*/
macro_line|#ifndef _SCSI_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#endif
DECL|macro|MAX_SD
mdefine_line|#define MAX_SD 2
DECL|struct|partition
r_typedef
r_struct
id|partition
(brace
DECL|member|boot_ind
r_int
r_char
id|boot_ind
suffix:semicolon
multiline_comment|/* 0x80 - active (unused) */
DECL|member|head
r_int
r_char
id|head
suffix:semicolon
multiline_comment|/* ? */
DECL|member|sector
r_int
r_char
id|sector
suffix:semicolon
multiline_comment|/* ? */
DECL|member|cyl
r_int
r_char
id|cyl
suffix:semicolon
multiline_comment|/* ? */
DECL|member|sys_ind
r_int
r_char
id|sys_ind
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_head
r_int
r_char
id|end_head
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_sector
r_int
r_char
id|end_sector
suffix:semicolon
multiline_comment|/* ? */
DECL|member|end_cyl
r_int
r_char
id|end_cyl
suffix:semicolon
multiline_comment|/* ? */
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector counting from 0 */
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
multiline_comment|/* nr of sectors in partition */
DECL|typedef|Partition
)brace
id|Partition
suffix:semicolon
r_extern
r_int
id|NR_SD
suffix:semicolon
r_extern
id|Partition
id|scsi_disks
(braket
id|MAX_SD
op_lshift
l_int|4
)braket
suffix:semicolon
r_typedef
r_struct
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
multiline_comment|/* support remapping */
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* after the initial inquiry, is &n;&t;&t;&t;&t;&t;&t;   the device still supported ? */
DECL|typedef|Scsi_Disk
)brace
id|Scsi_Disk
suffix:semicolon
r_extern
id|Scsi_Disk
id|rscsi_disks
(braket
id|MAX_SD
)braket
suffix:semicolon
r_void
id|sd_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|HOST
mdefine_line|#define HOST (rscsi_disks[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;host_no)
DECL|macro|ID
mdefine_line|#define ID (rscsi_disks[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;id)
DECL|macro|LUN
mdefine_line|#define LUN (rscsi_disks[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;lun)
macro_line|#endif
eof
