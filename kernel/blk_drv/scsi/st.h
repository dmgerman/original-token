macro_line|#ifndef _ST_H
DECL|macro|_ST_H
mdefine_line|#define _ST_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/st.h,v 1.1 1992/04/24 18:01:50 root Exp root $&n;*/
macro_line|#ifndef _SCSI_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|mt_status
r_struct
id|mtget
op_star
id|mt_status
suffix:semicolon
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|buffer_blocks
r_int
id|buffer_blocks
suffix:semicolon
DECL|member|buffer_bytes
r_int
id|buffer_bytes
suffix:semicolon
DECL|member|read_pointer
r_int
id|read_pointer
suffix:semicolon
DECL|member|writing
r_int
id|writing
suffix:semicolon
DECL|member|last_result
r_int
id|last_result
suffix:semicolon
DECL|member|b_data
r_int
r_char
id|b_data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|ST_buffer
)brace
id|ST_buffer
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
DECL|member|waiting
r_struct
id|wait_queue
op_star
id|waiting
suffix:semicolon
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|dirty
r_int
id|dirty
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rw
r_int
id|rw
suffix:colon
l_int|2
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:colon
l_int|1
suffix:semicolon
DECL|member|write_prot
r_int
id|write_prot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:colon
l_int|1
suffix:semicolon
DECL|member|eof_hit
r_int
id|eof_hit
suffix:colon
l_int|2
suffix:semicolon
DECL|member|buffer
id|ST_buffer
op_star
id|buffer
suffix:semicolon
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|min_block
r_int
id|min_block
suffix:semicolon
DECL|member|max_block
r_int
id|max_block
suffix:semicolon
DECL|member|SCpnt
id|Scsi_Cmnd
id|SCpnt
suffix:semicolon
DECL|typedef|Scsi_Tape
)brace
id|Scsi_Tape
suffix:semicolon
multiline_comment|/* Positioning SCSI-commands for Tandberg, etc. drives */
DECL|macro|QFA_REQUEST_BLOCK
mdefine_line|#define&t;QFA_REQUEST_BLOCK&t;0x02
DECL|macro|QFA_SEEK_BLOCK
mdefine_line|#define&t;QFA_SEEK_BLOCK&t;&t;0x0c
macro_line|#endif
eof
