macro_line|#ifndef _LINUX_PIPE_FS_I_H
DECL|macro|_LINUX_PIPE_FS_I_H
mdefine_line|#define _LINUX_PIPE_FS_I_H
DECL|struct|pipe_inode_info
r_struct
id|pipe_inode_info
(brace
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
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
DECL|macro|PIPE_READ_WAIT
mdefine_line|#define PIPE_READ_WAIT(inode)&t;((inode).u.pipe_i.read_wait)
DECL|macro|PIPE_WRITE_WAIT
mdefine_line|#define PIPE_WRITE_WAIT(inode)&t;((inode).u.pipe_i.write_wait)
DECL|macro|PIPE_BASE
mdefine_line|#define PIPE_BASE(inode)&t;((inode).u.pipe_i.base)
DECL|macro|PIPE_HEAD
mdefine_line|#define PIPE_HEAD(inode)&t;((inode).u.pipe_i.head)
DECL|macro|PIPE_TAIL
mdefine_line|#define PIPE_TAIL(inode)&t;((inode).u.pipe_i.tail)
DECL|macro|PIPE_READERS
mdefine_line|#define PIPE_READERS(inode)&t;((inode).u.pipe_i.readers)
DECL|macro|PIPE_WRITERS
mdefine_line|#define PIPE_WRITERS(inode)&t;((inode).u.pipe_i.writers)
DECL|macro|PIPE_SIZE
mdefine_line|#define PIPE_SIZE(inode)&t;((PIPE_HEAD(inode)-PIPE_TAIL(inode))&amp;(PAGE_SIZE-1))
DECL|macro|PIPE_EMPTY
mdefine_line|#define PIPE_EMPTY(inode)&t;(PIPE_HEAD(inode)==PIPE_TAIL(inode))
DECL|macro|PIPE_FULL
mdefine_line|#define PIPE_FULL(inode)&t;(PIPE_SIZE(inode)==(PAGE_SIZE-1))
macro_line|#endif
eof
