multiline_comment|/*&n; *      sr.h by David Giller&n; *      CD-ROM disk driver header file&n; *      &n; *      adapted from:&n; *&t;sd.h Copyright (C) 1992 Drew Eckhardt &n; *&t;SCSI disk driver header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@tantalus.nrl.navy.mil to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SR_H
DECL|macro|_SR_H
mdefine_line|#define _SR_H
macro_line|#include &quot;scsi.h&quot;
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
DECL|member|mpcd_sector
r_int
r_int
id|mpcd_sector
suffix:semicolon
multiline_comment|/* for reading multisession-CD&squot;s        */
DECL|member|xa_flags
r_char
id|xa_flags
suffix:semicolon
multiline_comment|/* some flags for handling XA-CD&squot;s      */
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
DECL|member|needs_sector_size
r_int
id|needs_sector_size
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* needs to get sector size */
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
DECL|typedef|Scsi_CD
)brace
id|Scsi_CD
suffix:semicolon
r_extern
id|Scsi_CD
op_star
id|scsi_CDs
suffix:semicolon
macro_line|#endif
eof
