macro_line|#ifndef _LINUX_LIMITS_H
DECL|macro|_LINUX_LIMITS_H
mdefine_line|#define _LINUX_LIMITS_H
DECL|macro|NAME_MAX
mdefine_line|#define NAME_MAX 255
DECL|macro|NR_OPEN
mdefine_line|#define NR_OPEN 32
DECL|macro|NR_INODE
mdefine_line|#define NR_INODE 128
DECL|macro|NR_FILE
mdefine_line|#define NR_FILE 128
DECL|macro|NR_SUPER
mdefine_line|#define NR_SUPER 8
DECL|macro|NR_HASH
mdefine_line|#define NR_HASH 307
DECL|macro|BLOCK_SIZE
mdefine_line|#define BLOCK_SIZE 1024
DECL|macro|BLOCK_SIZE_BITS
mdefine_line|#define BLOCK_SIZE_BITS 10
DECL|macro|MAX_CHRDEV
mdefine_line|#define MAX_CHRDEV 16
DECL|macro|MAX_BLKDEV
mdefine_line|#define MAX_BLKDEV 16
DECL|macro|NGROUPS_MAX
mdefine_line|#define NGROUPS_MAX       32&t;/* supplemental group IDs are available */
DECL|macro|ARG_MAX
mdefine_line|#define ARG_MAX        40960&t;/* # bytes of args + environ for exec() */
DECL|macro|CHILD_MAX
mdefine_line|#define CHILD_MAX        999    /* no limit :-) */
DECL|macro|OPEN_MAX
mdefine_line|#define OPEN_MAX          32&t;/* # open files a process may have */
DECL|macro|LINK_MAX
mdefine_line|#define LINK_MAX         127&t;/* # links a file may have */
DECL|macro|MAX_CANON
mdefine_line|#define MAX_CANON        255&t;/* size of the canonical input queue */
DECL|macro|MAX_INPUT
mdefine_line|#define MAX_INPUT        255&t;/* size of the type-ahead buffer */
DECL|macro|NAME_MAX
mdefine_line|#define NAME_MAX         255&t;/* # chars in a file name */
DECL|macro|PATH_MAX
mdefine_line|#define PATH_MAX        1024&t;/* # chars in a path name */
DECL|macro|PIPE_BUF
mdefine_line|#define PIPE_BUF        4095&t;/* # bytes in atomic write to a pipe */
macro_line|#endif
eof
