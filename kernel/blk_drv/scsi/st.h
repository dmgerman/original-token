macro_line|#ifndef _ST_H
DECL|macro|_ST_H
mdefine_line|#define _ST_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/st.h,v 1.1 1992/04/24 18:01:50 root Exp root $&n;*/
macro_line|#ifndef _SCSI_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#endif
DECL|macro|MAX_ST
mdefine_line|#define MAX_ST 1
r_typedef
r_struct
(brace
multiline_comment|/*&n;&t;&t;Undecided goodies go here!!!&n;&t;*/
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|typedef|Scsi_Tape
)brace
id|Scsi_Tape
suffix:semicolon
r_extern
r_int
id|NR_ST
suffix:semicolon
r_extern
id|Scsi_Tape
id|scsi_tapes
(braket
id|MAX_ST
)braket
suffix:semicolon
r_void
id|st_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
