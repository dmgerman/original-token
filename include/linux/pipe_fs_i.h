macro_line|#ifndef _LINUX_PIPE_FS_I_H
DECL|macro|_LINUX_PIPE_FS_I_H
mdefine_line|#define _LINUX_PIPE_FS_I_H
DECL|struct|pipe_inode_info
r_struct
id|pipe_inode_info
(brace
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|lock
r_int
r_int
id|lock
suffix:semicolon
DECL|member|rd_openers
r_int
r_int
id|rd_openers
suffix:semicolon
DECL|member|wr_openers
r_int
r_int
id|wr_openers
suffix:semicolon
DECL|member|readers
r_int
r_int
id|readers
suffix:semicolon
DECL|member|writers
r_int
r_int
id|writers
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PIPE_WAIT
mdefine_line|#define PIPE_WAIT(inode)&t;((inode).u.pipe_i.wait)
DECL|macro|PIPE_BASE
mdefine_line|#define PIPE_BASE(inode)&t;((inode).u.pipe_i.base)
DECL|macro|PIPE_START
mdefine_line|#define PIPE_START(inode)&t;((inode).u.pipe_i.start)
DECL|macro|PIPE_LEN
mdefine_line|#define PIPE_LEN(inode)&t;&t;((inode).i_size)
DECL|macro|PIPE_RD_OPENERS
mdefine_line|#define PIPE_RD_OPENERS(inode)&t;((inode).u.pipe_i.rd_openers)
DECL|macro|PIPE_WR_OPENERS
mdefine_line|#define PIPE_WR_OPENERS(inode)&t;((inode).u.pipe_i.wr_openers)
DECL|macro|PIPE_READERS
mdefine_line|#define PIPE_READERS(inode)&t;((inode).u.pipe_i.readers)
DECL|macro|PIPE_WRITERS
mdefine_line|#define PIPE_WRITERS(inode)&t;((inode).u.pipe_i.writers)
DECL|macro|PIPE_LOCK
mdefine_line|#define PIPE_LOCK(inode)&t;((inode).u.pipe_i.lock)
DECL|macro|PIPE_SIZE
mdefine_line|#define PIPE_SIZE(inode)&t;PIPE_LEN(inode)
DECL|macro|PIPE_EMPTY
mdefine_line|#define PIPE_EMPTY(inode)&t;(PIPE_SIZE(inode)==0)
DECL|macro|PIPE_FULL
mdefine_line|#define PIPE_FULL(inode)&t;(PIPE_SIZE(inode)==PIPE_BUF)
DECL|macro|PIPE_FREE
mdefine_line|#define PIPE_FREE(inode)&t;(PIPE_BUF - PIPE_LEN(inode))
DECL|macro|PIPE_END
mdefine_line|#define PIPE_END(inode)&t;&t;((PIPE_START(inode)+PIPE_LEN(inode))&amp;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;   (PIPE_BUF-1))
DECL|macro|PIPE_MAX_RCHUNK
mdefine_line|#define PIPE_MAX_RCHUNK(inode)&t;(PIPE_BUF - PIPE_START(inode))
DECL|macro|PIPE_MAX_WCHUNK
mdefine_line|#define PIPE_MAX_WCHUNK(inode)&t;(PIPE_BUF - PIPE_END(inode))
macro_line|#endif
eof
