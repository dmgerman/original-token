macro_line|#ifndef _LINUX_FS_H
DECL|macro|_LINUX_FS_H
mdefine_line|#define _LINUX_FS_H
multiline_comment|/*&n; * This file has definitions for some important file table&n; * structures etc.&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/net.h&gt;
multiline_comment|/*&n; * It&squot;s silly to have NR_OPEN bigger than NR_FILE, but I&squot;ll fix&n; * that later. Anyway, now the file code is no longer dependent&n; * on bitmaps in unsigned longs, but uses the new fd_set structure..&n; *&n; * Some programs (notably those using select()) may have to be &n; * recompiled to take full advantage of the new limits..&n; */
DECL|macro|NR_OPEN
macro_line|#undef NR_OPEN
DECL|macro|NR_OPEN
mdefine_line|#define NR_OPEN 256
DECL|macro|NR_INODE
mdefine_line|#define NR_INODE 2048&t;/* this should be bigger than NR_FILE */
DECL|macro|NR_FILE
mdefine_line|#define NR_FILE 1024&t;/* this can well be larger on a larger system */
DECL|macro|NR_SUPER
mdefine_line|#define NR_SUPER 32
DECL|macro|NR_HASH
mdefine_line|#define NR_HASH 997
DECL|macro|NR_IHASH
mdefine_line|#define NR_IHASH 131
DECL|macro|NR_FILE_LOCKS
mdefine_line|#define NR_FILE_LOCKS 64
DECL|macro|BLOCK_SIZE
mdefine_line|#define BLOCK_SIZE 1024
DECL|macro|BLOCK_SIZE_BITS
mdefine_line|#define BLOCK_SIZE_BITS 10
DECL|macro|MAY_EXEC
mdefine_line|#define MAY_EXEC 1
DECL|macro|MAY_WRITE
mdefine_line|#define MAY_WRITE 2
DECL|macro|MAY_READ
mdefine_line|#define MAY_READ 4
DECL|macro|READ
mdefine_line|#define READ 0
DECL|macro|WRITE
mdefine_line|#define WRITE 1
DECL|macro|READA
mdefine_line|#define READA 2&t;&t;/* read-ahead - don&squot;t pause */
DECL|macro|WRITEA
mdefine_line|#define WRITEA 3&t;/* &quot;write-ahead&quot; - silly, but somewhat useful */
r_extern
r_void
id|buffer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|inode_init
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_int
r_int
id|file_table_init
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
DECL|macro|MAJOR
mdefine_line|#define MAJOR(a) (int)((unsigned short)(a) &gt;&gt; 8)
DECL|macro|MINOR
mdefine_line|#define MINOR(a) (int)((unsigned short)(a) &amp; 0xFF)
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
DECL|macro|NIL_FILP
mdefine_line|#define NIL_FILP&t;((struct file *)0)
DECL|macro|SEL_IN
mdefine_line|#define SEL_IN&t;&t;1
DECL|macro|SEL_OUT
mdefine_line|#define SEL_OUT&t;&t;2
DECL|macro|SEL_EX
mdefine_line|#define SEL_EX&t;&t;4
multiline_comment|/*&n; * These are the fs-independent mount-flags: up to 16 flags are supported&n; */
DECL|macro|MS_RDONLY
mdefine_line|#define MS_RDONLY    1 /* mount read-only */
DECL|macro|MS_NOSUID
mdefine_line|#define MS_NOSUID    2 /* ignore suid and sgid bits */
DECL|macro|MS_NODEV
mdefine_line|#define MS_NODEV     4 /* disallow access to device special files */
DECL|macro|MS_NOEXEC
mdefine_line|#define MS_NOEXEC    8 /* disallow program execution */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC     16 /* writes are synced at once */
DECL|macro|MS_REMOUNT
mdefine_line|#define&t;MS_REMOUNT  32 /* alter flags of a mounted FS */
multiline_comment|/*&n; * Flags that can be altered by MS_REMOUNT&n; */
DECL|macro|MS_RMT_MASK
mdefine_line|#define MS_RMT_MASK (MS_RDONLY)
multiline_comment|/*&n; * Magic mount flag number. Has to be or-ed to the flag values.&n; */
DECL|macro|MS_MGC_VAL
mdefine_line|#define MS_MGC_VAL 0xC0ED0000 /* magic flag number to indicate &quot;new&quot; flags */
DECL|macro|MS_MGC_MSK
mdefine_line|#define MS_MGC_MSK 0xffff0000 /* magic flag number mask */
multiline_comment|/*&n; * Note that read-only etc flags are inode-specific: setting some file-system&n; * flags just means all the inodes inherit those flags by default. It might be&n; * possible to overrride it sevelctively if you really wanted to with some&n; * ioctl() that is not currently implemented.&n; *&n; * Exception: MS_RDONLY is always applied to the entire file system.&n; */
DECL|macro|IS_RDONLY
mdefine_line|#define IS_RDONLY(inode) (((inode)-&gt;i_sb) &amp;&amp; ((inode)-&gt;i_sb-&gt;s_flags &amp; MS_RDONLY))
DECL|macro|IS_NOSUID
mdefine_line|#define IS_NOSUID(inode) ((inode)-&gt;i_flags &amp; MS_NOSUID)
DECL|macro|IS_NODEV
mdefine_line|#define IS_NODEV(inode) ((inode)-&gt;i_flags &amp; MS_NODEV)
DECL|macro|IS_NOEXEC
mdefine_line|#define IS_NOEXEC(inode) ((inode)-&gt;i_flags &amp; MS_NOEXEC)
DECL|macro|IS_SYNC
mdefine_line|#define IS_SYNC(inode) ((inode)-&gt;i_flags &amp; MS_SYNC)
multiline_comment|/* the read-only stuff doesn&squot;t really belong here, but any other place is&n;   probably as bad and I don&squot;t want to create yet another include file. */
DECL|macro|BLKROSET
mdefine_line|#define BLKROSET 4701 /* set device read-only (0 = read-write) */
DECL|macro|BLKROGET
mdefine_line|#define BLKROGET 4702 /* get read-only status (0 = read_write) */
DECL|macro|BLKRRPART
mdefine_line|#define BLKRRPART 4703 /* re-read partition table */
DECL|macro|BLKGETSIZE
mdefine_line|#define BLKGETSIZE 4704 /* return device size */
DECL|macro|BLKFLSBUF
mdefine_line|#define BLKFLSBUF 4705 /* flush buffer cache */
multiline_comment|/* These are a few other constants  only used by scsi  devices */
DECL|macro|SCSI_IOCTL_GET_IDLUN
mdefine_line|#define SCSI_IOCTL_GET_IDLUN 0x5382
multiline_comment|/* Used to turn on and off tagged queueing for scsi devices */
DECL|macro|SCSI_IOCTL_TAGGED_ENABLE
mdefine_line|#define SCSI_IOCTL_TAGGED_ENABLE 0x5383
DECL|macro|SCSI_IOCTL_TAGGED_DISABLE
mdefine_line|#define SCSI_IOCTL_TAGGED_DISABLE 0x5384
DECL|macro|BMAP_IOCTL
mdefine_line|#define BMAP_IOCTL 1&t;/* obsolete - kept for compatibility */
DECL|macro|FIBMAP
mdefine_line|#define FIBMAP&t;   1&t;/* bmap access */
DECL|macro|FIGETBSZ
mdefine_line|#define FIGETBSZ   2&t;/* get the block size used for bmap */
multiline_comment|/* these flags tell notify_change what is being changed */
DECL|macro|NOTIFY_SIZE
mdefine_line|#define NOTIFY_SIZE&t;1
DECL|macro|NOTIFY_MODE
mdefine_line|#define NOTIFY_MODE&t;2
DECL|macro|NOTIFY_TIME
mdefine_line|#define NOTIFY_TIME&t;4
DECL|macro|NOTIFY_UIDGID
mdefine_line|#define NOTIFY_UIDGID&t;8
DECL|typedef|buffer_block
r_typedef
r_char
id|buffer_block
(braket
id|BLOCK_SIZE
)braket
suffix:semicolon
DECL|struct|buffer_head
r_struct
id|buffer_head
(brace
DECL|member|b_data
r_char
op_star
id|b_data
suffix:semicolon
multiline_comment|/* pointer to data block (1024 bytes) */
DECL|member|b_size
r_int
r_int
id|b_size
suffix:semicolon
multiline_comment|/* block size */
DECL|member|b_blocknr
r_int
r_int
id|b_blocknr
suffix:semicolon
multiline_comment|/* block number */
DECL|member|b_dev
id|dev_t
id|b_dev
suffix:semicolon
multiline_comment|/* device (0 = free) */
DECL|member|b_count
r_int
r_int
id|b_count
suffix:semicolon
multiline_comment|/* users using this block */
DECL|member|b_uptodate
r_int
r_char
id|b_uptodate
suffix:semicolon
DECL|member|b_dirt
r_int
r_char
id|b_dirt
suffix:semicolon
multiline_comment|/* 0-clean,1-dirty */
DECL|member|b_lock
r_int
r_char
id|b_lock
suffix:semicolon
multiline_comment|/* 0 - ok, 1 -locked */
DECL|member|b_req
r_int
r_char
id|b_req
suffix:semicolon
multiline_comment|/* 0 if the buffer has been invalidated */
DECL|member|b_wait
r_struct
id|wait_queue
op_star
id|b_wait
suffix:semicolon
DECL|member|b_prev
r_struct
id|buffer_head
op_star
id|b_prev
suffix:semicolon
multiline_comment|/* doubly linked list of hash-queue */
DECL|member|b_next
r_struct
id|buffer_head
op_star
id|b_next
suffix:semicolon
DECL|member|b_prev_free
r_struct
id|buffer_head
op_star
id|b_prev_free
suffix:semicolon
multiline_comment|/* doubly linked list of buffers */
DECL|member|b_next_free
r_struct
id|buffer_head
op_star
id|b_next_free
suffix:semicolon
DECL|member|b_this_page
r_struct
id|buffer_head
op_star
id|b_this_page
suffix:semicolon
multiline_comment|/* circular list of buffers in one page */
DECL|member|b_reqnext
r_struct
id|buffer_head
op_star
id|b_reqnext
suffix:semicolon
multiline_comment|/* request queue */
)brace
suffix:semicolon
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
macro_line|#include &lt;linux/minix_fs_i.h&gt;
macro_line|#include &lt;linux/ext_fs_i.h&gt;
macro_line|#include &lt;linux/ext2_fs_i.h&gt;
macro_line|#include &lt;linux/hpfs_fs_i.h&gt;
macro_line|#include &lt;linux/msdos_fs_i.h&gt;
macro_line|#include &lt;linux/iso_fs_i.h&gt;
macro_line|#include &lt;linux/nfs_fs_i.h&gt;
macro_line|#include &lt;linux/xia_fs_i.h&gt;
DECL|struct|inode
r_struct
id|inode
(brace
DECL|member|i_dev
id|dev_t
id|i_dev
suffix:semicolon
DECL|member|i_ino
r_int
r_int
id|i_ino
suffix:semicolon
DECL|member|i_mode
id|umode_t
id|i_mode
suffix:semicolon
DECL|member|i_nlink
id|nlink_t
id|i_nlink
suffix:semicolon
DECL|member|i_uid
id|uid_t
id|i_uid
suffix:semicolon
DECL|member|i_gid
id|gid_t
id|i_gid
suffix:semicolon
DECL|member|i_rdev
id|dev_t
id|i_rdev
suffix:semicolon
DECL|member|i_size
id|off_t
id|i_size
suffix:semicolon
DECL|member|i_atime
id|time_t
id|i_atime
suffix:semicolon
DECL|member|i_mtime
id|time_t
id|i_mtime
suffix:semicolon
DECL|member|i_ctime
id|time_t
id|i_ctime
suffix:semicolon
DECL|member|i_blksize
r_int
r_int
id|i_blksize
suffix:semicolon
DECL|member|i_blocks
r_int
r_int
id|i_blocks
suffix:semicolon
DECL|member|i_op
r_struct
id|inode_operations
op_star
id|i_op
suffix:semicolon
DECL|member|i_sb
r_struct
id|super_block
op_star
id|i_sb
suffix:semicolon
DECL|member|i_wait
r_struct
id|wait_queue
op_star
id|i_wait
suffix:semicolon
DECL|member|i_flock
r_struct
id|file_lock
op_star
id|i_flock
suffix:semicolon
DECL|member|i_mmap
r_struct
id|vm_area_struct
op_star
id|i_mmap
suffix:semicolon
DECL|member|i_next
DECL|member|i_prev
r_struct
id|inode
op_star
id|i_next
comma
op_star
id|i_prev
suffix:semicolon
DECL|member|i_hash_next
DECL|member|i_hash_prev
r_struct
id|inode
op_star
id|i_hash_next
comma
op_star
id|i_hash_prev
suffix:semicolon
DECL|member|i_bound_to
DECL|member|i_bound_by
r_struct
id|inode
op_star
id|i_bound_to
comma
op_star
id|i_bound_by
suffix:semicolon
DECL|member|i_mount
r_struct
id|inode
op_star
id|i_mount
suffix:semicolon
DECL|member|i_socket
r_struct
id|socket
op_star
id|i_socket
suffix:semicolon
DECL|member|i_count
r_int
r_int
id|i_count
suffix:semicolon
DECL|member|i_flags
r_int
r_int
id|i_flags
suffix:semicolon
DECL|member|i_lock
r_int
r_char
id|i_lock
suffix:semicolon
DECL|member|i_dirt
r_int
r_char
id|i_dirt
suffix:semicolon
DECL|member|i_pipe
r_int
r_char
id|i_pipe
suffix:semicolon
DECL|member|i_seek
r_int
r_char
id|i_seek
suffix:semicolon
DECL|member|i_update
r_int
r_char
id|i_update
suffix:semicolon
r_union
(brace
DECL|member|pipe_i
r_struct
id|pipe_inode_info
id|pipe_i
suffix:semicolon
DECL|member|minix_i
r_struct
id|minix_inode_info
id|minix_i
suffix:semicolon
DECL|member|ext_i
r_struct
id|ext_inode_info
id|ext_i
suffix:semicolon
DECL|member|ext2_i
r_struct
id|ext2_inode_info
id|ext2_i
suffix:semicolon
DECL|member|hpfs_i
r_struct
id|hpfs_inode_info
id|hpfs_i
suffix:semicolon
DECL|member|msdos_i
r_struct
id|msdos_inode_info
id|msdos_i
suffix:semicolon
DECL|member|isofs_i
r_struct
id|iso_inode_info
id|isofs_i
suffix:semicolon
DECL|member|nfs_i
r_struct
id|nfs_inode_info
id|nfs_i
suffix:semicolon
DECL|member|xiafs_i
r_struct
id|xiafs_inode_info
id|xiafs_i
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file
r_struct
id|file
(brace
DECL|member|f_mode
id|mode_t
id|f_mode
suffix:semicolon
DECL|member|f_rdev
id|dev_t
id|f_rdev
suffix:semicolon
multiline_comment|/* needed for /dev/tty */
DECL|member|f_pos
id|off_t
id|f_pos
suffix:semicolon
DECL|member|f_flags
r_int
r_int
id|f_flags
suffix:semicolon
DECL|member|f_count
r_int
r_int
id|f_count
suffix:semicolon
DECL|member|f_reada
r_int
r_int
id|f_reada
suffix:semicolon
DECL|member|f_next
DECL|member|f_prev
r_struct
id|file
op_star
id|f_next
comma
op_star
id|f_prev
suffix:semicolon
DECL|member|f_inode
r_struct
id|inode
op_star
id|f_inode
suffix:semicolon
DECL|member|f_op
r_struct
id|file_operations
op_star
id|f_op
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_lock
r_struct
id|file_lock
(brace
DECL|member|fl_next
r_struct
id|file_lock
op_star
id|fl_next
suffix:semicolon
multiline_comment|/* singly linked list */
DECL|member|fl_owner
r_struct
id|task_struct
op_star
id|fl_owner
suffix:semicolon
multiline_comment|/* NULL if on free list, for sanity checks */
DECL|member|fl_fd
r_int
r_int
id|fl_fd
suffix:semicolon
multiline_comment|/* File descriptor for this lock */
DECL|member|fl_wait
r_struct
id|wait_queue
op_star
id|fl_wait
suffix:semicolon
DECL|member|fl_type
r_char
id|fl_type
suffix:semicolon
DECL|member|fl_whence
r_char
id|fl_whence
suffix:semicolon
DECL|member|fl_start
id|off_t
id|fl_start
suffix:semicolon
DECL|member|fl_end
id|off_t
id|fl_end
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;linux/minix_fs_sb.h&gt;
macro_line|#include &lt;linux/ext_fs_sb.h&gt;
macro_line|#include &lt;linux/ext2_fs_sb.h&gt;
macro_line|#include &lt;linux/hpfs_fs_sb.h&gt;
macro_line|#include &lt;linux/msdos_fs_sb.h&gt;
macro_line|#include &lt;linux/iso_fs_sb.h&gt;
macro_line|#include &lt;linux/nfs_fs_sb.h&gt;
macro_line|#include &lt;linux/xia_fs_sb.h&gt;
DECL|struct|super_block
r_struct
id|super_block
(brace
DECL|member|s_dev
id|dev_t
id|s_dev
suffix:semicolon
DECL|member|s_blocksize
r_int
r_int
id|s_blocksize
suffix:semicolon
DECL|member|s_blocksize_bits
r_int
r_char
id|s_blocksize_bits
suffix:semicolon
DECL|member|s_lock
r_int
r_char
id|s_lock
suffix:semicolon
DECL|member|s_rd_only
r_int
r_char
id|s_rd_only
suffix:semicolon
DECL|member|s_dirt
r_int
r_char
id|s_dirt
suffix:semicolon
DECL|member|s_op
r_struct
id|super_operations
op_star
id|s_op
suffix:semicolon
DECL|member|s_flags
r_int
r_int
id|s_flags
suffix:semicolon
DECL|member|s_magic
r_int
r_int
id|s_magic
suffix:semicolon
DECL|member|s_time
r_int
r_int
id|s_time
suffix:semicolon
DECL|member|s_covered
r_struct
id|inode
op_star
id|s_covered
suffix:semicolon
DECL|member|s_mounted
r_struct
id|inode
op_star
id|s_mounted
suffix:semicolon
DECL|member|s_wait
r_struct
id|wait_queue
op_star
id|s_wait
suffix:semicolon
r_union
(brace
DECL|member|minix_sb
r_struct
id|minix_sb_info
id|minix_sb
suffix:semicolon
DECL|member|ext_sb
r_struct
id|ext_sb_info
id|ext_sb
suffix:semicolon
DECL|member|ext2_sb
r_struct
id|ext2_sb_info
id|ext2_sb
suffix:semicolon
DECL|member|hpfs_sb
r_struct
id|hpfs_sb_info
id|hpfs_sb
suffix:semicolon
DECL|member|msdos_sb
r_struct
id|msdos_sb_info
id|msdos_sb
suffix:semicolon
DECL|member|isofs_sb
r_struct
id|isofs_sb_info
id|isofs_sb
suffix:semicolon
DECL|member|nfs_sb
r_struct
id|nfs_sb_info
id|nfs_sb
suffix:semicolon
DECL|member|xiafs_sb
r_struct
id|xiafs_sb_info
id|xiafs_sb
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_operations
r_struct
id|file_operations
(brace
DECL|member|lseek
r_int
(paren
op_star
id|lseek
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|readdir
r_int
(paren
op_star
id|readdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|dirent
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|select
r_int
(paren
op_star
id|select
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
id|select_table
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|fsync
r_int
(paren
op_star
id|fsync
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|inode_operations
r_struct
id|inode_operations
(brace
DECL|member|default_file_ops
r_struct
id|file_operations
op_star
id|default_file_ops
suffix:semicolon
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
DECL|member|link
r_int
(paren
op_star
id|link
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|unlink
r_int
(paren
op_star
id|unlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|symlink
r_int
(paren
op_star
id|symlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|member|mkdir
r_int
(paren
op_star
id|mkdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|rmdir
r_int
(paren
op_star
id|rmdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|mknod
r_int
(paren
op_star
id|mknod
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|rename
r_int
(paren
op_star
id|rename
)paren
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|readlink
r_int
(paren
op_star
id|readlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|follow_link
r_int
(paren
op_star
id|follow_link
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
DECL|member|bmap
r_int
(paren
op_star
id|bmap
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|truncate
r_void
(paren
op_star
id|truncate
)paren
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|permission
r_int
(paren
op_star
id|permission
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|super_operations
r_struct
id|super_operations
(brace
DECL|member|read_inode
r_void
(paren
op_star
id|read_inode
)paren
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|notify_change
r_int
(paren
op_star
id|notify_change
)paren
(paren
r_int
id|flags
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|write_inode
r_void
(paren
op_star
id|write_inode
)paren
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|put_inode
r_void
(paren
op_star
id|put_inode
)paren
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|put_super
r_void
(paren
op_star
id|put_super
)paren
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|member|write_super
r_void
(paren
op_star
id|write_super
)paren
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|member|statfs
r_void
(paren
op_star
id|statfs
)paren
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
DECL|member|remount_fs
r_int
(paren
op_star
id|remount_fs
)paren
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_system_type
r_struct
id|file_system_type
(brace
DECL|member|read_super
r_struct
id|super_block
op_star
(paren
op_star
id|read_super
)paren
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|requires_dev
r_int
id|requires_dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
id|asmlinkage
r_int
id|sys_open
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_close
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* yes, it&squot;s really unsigned */
r_extern
r_int
id|getname
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|result
)paren
suffix:semicolon
r_extern
r_void
id|putname
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|register_blkdev
c_func
(paren
r_int
r_int
comma
r_const
r_char
op_star
comma
r_struct
id|file_operations
op_star
)paren
suffix:semicolon
r_extern
r_int
id|blkdev_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|def_blk_fops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|blkdev_inode_operations
suffix:semicolon
r_extern
r_int
id|register_chrdev
c_func
(paren
r_int
r_int
comma
r_const
r_char
op_star
comma
r_struct
id|file_operations
op_star
)paren
suffix:semicolon
r_extern
r_int
id|chrdev_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|def_chr_fops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|chrdev_inode_operations
suffix:semicolon
r_extern
r_void
id|init_fifo
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|connecting_fifo_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|read_fifo_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|write_fifo_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|rdwr_fifo_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|read_pipe_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|write_pipe_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|rdwr_pipe_fops
suffix:semicolon
r_extern
r_struct
id|file_system_type
op_star
id|get_fs_type
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|fs_may_mount
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|fs_may_umount
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|inode
op_star
id|mount_root
)paren
suffix:semicolon
r_extern
r_int
id|fs_may_remount_ro
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|file
op_star
id|first_file
suffix:semicolon
r_extern
r_int
id|nr_files
suffix:semicolon
r_extern
r_struct
id|super_block
id|super_blocks
(braket
id|NR_SUPER
)braket
suffix:semicolon
r_extern
r_int
id|shrink_buffers
c_func
(paren
r_int
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_int
id|nr_buffers
suffix:semicolon
r_extern
r_int
id|buffermem
suffix:semicolon
r_extern
r_int
id|nr_buffer_heads
suffix:semicolon
r_extern
r_void
id|check_disk_change
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|invalidate_inodes
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|invalidate_buffers
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|floppy_change
c_func
(paren
r_struct
id|buffer_head
op_star
id|first_block
)paren
suffix:semicolon
r_extern
r_void
id|sync_inodes
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|sync_dev
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|fsync_dev
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|sync_supers
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_int
id|notify_change
c_func
(paren
r_int
id|flags
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|namei
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
suffix:semicolon
r_extern
r_int
id|lnamei
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
suffix:semicolon
r_extern
r_int
id|permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
r_extern
r_int
id|open_namei
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|flag
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|res_inode
comma
r_struct
id|inode
op_star
id|base
)paren
suffix:semicolon
r_extern
r_int
id|do_mknod
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|iput
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|__iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|crsmnt
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|get_empty_inode
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|insert_inode_hash
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|clear_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|get_pipe_inode
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|file
op_star
id|get_empty_filp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|get_hash_table
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|getblk
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|ll_rw_block
c_func
(paren
r_int
id|rw
comma
r_int
id|nr
comma
r_struct
id|buffer_head
op_star
id|bh
(braket
)braket
)paren
suffix:semicolon
r_extern
r_void
id|ll_rw_page
c_func
(paren
r_int
id|rw
comma
r_int
id|dev
comma
r_int
id|nr
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|ll_rw_swap_file
c_func
(paren
r_int
id|rw
comma
r_int
id|dev
comma
r_int
r_int
op_star
id|b
comma
r_int
id|nb
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|set_blocksize
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|bread
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
r_int
id|bread_page
c_func
(paren
r_int
r_int
id|addr
comma
id|dev_t
id|dev
comma
r_int
id|b
(braket
)braket
comma
r_int
id|size
comma
r_int
id|prot
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|breada
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|put_super
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
r_extern
id|dev_t
id|ROOT_DEV
suffix:semicolon
r_extern
r_void
id|mount_root
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|char_read
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|block_read
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|read_ahead
(braket
)braket
suffix:semicolon
r_extern
r_int
id|char_write
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|block_write
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|generic_mmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|block_fsync
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|file_fsync
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
