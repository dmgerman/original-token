macro_line|#ifndef _SYSV_FS_I
DECL|macro|_SYSV_FS_I
mdefine_line|#define _SYSV_FS_I
multiline_comment|/*&n; * SystemV/Coherent FS inode data in memory&n; */
DECL|struct|sysv_inode_info
r_struct
id|sysv_inode_info
(brace
DECL|member|i_data
r_int
r_int
id|i_data
(braket
l_int|10
op_plus
l_int|1
op_plus
l_int|1
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* zone numbers: max. 10 data blocks,&n;&t;&t;&t;&t;&t; * then 1 indirection block,&n;&t;&t;&t;&t;&t; * then 1 double indirection block,&n;&t;&t;&t;&t;&t; * then 1 triple indirection block.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* the following are only used if  block_size &lt; BLOCK_SIZE  */
DECL|member|i_lock
r_int
id|i_lock
suffix:semicolon
multiline_comment|/* lock to protect against simultaneous&t;*/
DECL|member|i_wait
r_struct
id|wait_queue
op_star
id|i_wait
suffix:semicolon
multiline_comment|/* write and truncate&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;*/
)brace
suffix:semicolon
macro_line|#endif
eof
