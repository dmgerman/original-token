multiline_comment|/*&n; *      sr.h by David Giller&n; *      CD-ROM disk driver header file&n; *      &n; *      adapted from:&n; *&t;sd.h Copyright (C) 1992 Drew Eckhardt &n; *&t;SCSI disk driver header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SR_H
DECL|macro|_SR_H
mdefine_line|#define _SR_H
macro_line|#include &quot;scsi.h&quot;
DECL|macro|MAX_SR
mdefine_line|#define MAX_SR 2
r_extern
r_int
id|NR_SR
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
multiline_comment|/* size in blocks &t;&t;&t;*/
DECL|member|sector_size
r_int
id|sector_size
suffix:semicolon
multiline_comment|/* size in bytes &t;&t;&t;*/
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
multiline_comment|/* sector size = 2^sector_bit_size&t;*/
DECL|member|sector_bit_shift
r_int
r_char
id|sector_bit_shift
suffix:semicolon
multiline_comment|/* sectors/FS block = 2^sector_bit_shift*/
DECL|member|ten
r_int
id|ten
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support ten byte commands&t;&t;*/
DECL|member|remap
r_int
id|remap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support remapping&t;&t;&t;*/
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* is this device still supportable&t;*/
DECL|member|changed
r_int
id|changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disk changed flag&t;&t;&t;*/
DECL|typedef|Scsi_CD
)brace
id|Scsi_CD
suffix:semicolon
r_extern
id|Scsi_CD
id|scsi_CDs
(braket
id|MAX_SR
)braket
suffix:semicolon
r_void
id|sr_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SR_HOST
mdefine_line|#define SR_HOST (scsi_CDs[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;host_no)
DECL|macro|SR_ID
mdefine_line|#define SR_ID (scsi_CDs[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;id)
DECL|macro|SR_LUN
mdefine_line|#define SR_LUN (scsi_CDs[DEVICE_NR(CURRENT-&gt;dev)].device-&gt;lun)
macro_line|#endif
eof
