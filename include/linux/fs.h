multiline_comment|/*&n; * This file has definitions for some important file table&n; * structures etc.&n; */
macro_line|#ifndef _FS_H
DECL|macro|_FS_H
mdefine_line|#define _FS_H
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/dirent.h&gt;
macro_line|#include &lt;sys/vfs.h&gt;
multiline_comment|/* devices are as follows: (same as minix, so we can use the minix&n; * file system. These are major numbers.)&n; *&n; * 0 - unused (nodev)&n; * 1 - /dev/mem&n; * 2 - /dev/fd&n; * 3 - /dev/hd&n; * 4 - /dev/ttyx&n; * 5 - /dev/tty&n; * 6 - /dev/lp&n; * 7 - unnamed pipes&n; * 8 - /dev/sd&n; * 9 - /dev/st&n; */
DECL|macro|IS_SEEKABLE
mdefine_line|#define IS_SEEKABLE(x) ((x)&gt;=1 &amp;&amp; (x)&lt;=3 || (x)==8)
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
r_void
id|buffer_init
c_func
(paren
r_int
id|buffer_end
)paren
suffix:semicolon
DECL|macro|MAJOR
mdefine_line|#define MAJOR(a) (((unsigned)(a))&gt;&gt;8)
DECL|macro|MINOR
mdefine_line|#define MINOR(a) ((a)&amp;0xff)
DECL|macro|NR_OPEN
mdefine_line|#define NR_OPEN 32
DECL|macro|NR_INODE
mdefine_line|#define NR_INODE 128
DECL|macro|NR_FILE
mdefine_line|#define NR_FILE 64
DECL|macro|NR_SUPER
mdefine_line|#define NR_SUPER 8
DECL|macro|NR_HASH
mdefine_line|#define NR_HASH 307
DECL|macro|NR_BUFFERS
mdefine_line|#define NR_BUFFERS nr_buffers
DECL|macro|BLOCK_SIZE
mdefine_line|#define BLOCK_SIZE 1024
DECL|macro|BLOCK_SIZE_BITS
mdefine_line|#define BLOCK_SIZE_BITS 10
DECL|macro|MAX_CHRDEV
mdefine_line|#define MAX_CHRDEV 16
DECL|macro|MAX_BLKDEV
mdefine_line|#define MAX_BLKDEV 16
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
DECL|macro|PIPE_READ_WAIT
mdefine_line|#define PIPE_READ_WAIT(inode) ((inode).i_wait)
DECL|macro|PIPE_WRITE_WAIT
mdefine_line|#define PIPE_WRITE_WAIT(inode) ((inode).i_wait2)
DECL|macro|PIPE_HEAD
mdefine_line|#define PIPE_HEAD(inode) ((inode).i_data[0])
DECL|macro|PIPE_TAIL
mdefine_line|#define PIPE_TAIL(inode) ((inode).i_data[1])
DECL|macro|PIPE_SIZE
mdefine_line|#define PIPE_SIZE(inode) ((PIPE_HEAD(inode)-PIPE_TAIL(inode))&amp;(PAGE_SIZE-1))
DECL|macro|PIPE_EMPTY
mdefine_line|#define PIPE_EMPTY(inode) (PIPE_HEAD(inode)==PIPE_TAIL(inode))
DECL|macro|PIPE_FULL
mdefine_line|#define PIPE_FULL(inode) (PIPE_SIZE(inode)==(PAGE_SIZE-1))
DECL|macro|NIL_FILP
mdefine_line|#define NIL_FILP&t;((struct file *)0)
DECL|macro|SEL_IN
mdefine_line|#define SEL_IN&t;&t;1
DECL|macro|SEL_OUT
mdefine_line|#define SEL_OUT&t;&t;2
DECL|macro|SEL_EX
mdefine_line|#define SEL_EX&t;&t;4
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
DECL|member|b_blocknr
r_int
r_int
id|b_blocknr
suffix:semicolon
multiline_comment|/* block number */
DECL|member|b_dev
r_int
r_int
id|b_dev
suffix:semicolon
multiline_comment|/* device (0 = free) */
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
DECL|member|b_count
r_int
r_char
id|b_count
suffix:semicolon
multiline_comment|/* users using this block */
DECL|member|b_lock
r_int
r_char
id|b_lock
suffix:semicolon
multiline_comment|/* 0 - ok, 1 -locked */
DECL|member|b_wait
r_struct
id|task_struct
op_star
id|b_wait
suffix:semicolon
DECL|member|b_prev
r_struct
id|buffer_head
op_star
id|b_prev
suffix:semicolon
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
DECL|member|b_next_free
r_struct
id|buffer_head
op_star
id|b_next_free
suffix:semicolon
DECL|member|b_reqnext
r_struct
id|buffer_head
op_star
id|b_reqnext
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|i_data
r_int
r_int
id|i_data
(braket
l_int|16
)braket
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
id|task_struct
op_star
id|i_wait
suffix:semicolon
DECL|member|i_wait2
r_struct
id|task_struct
op_star
id|i_wait2
suffix:semicolon
multiline_comment|/* for pipes */
DECL|member|i_count
r_int
r_int
id|i_count
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
DECL|member|i_mount
r_int
r_char
id|i_mount
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
)brace
suffix:semicolon
DECL|struct|file
r_struct
id|file
(brace
DECL|member|f_mode
r_int
r_int
id|f_mode
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
DECL|member|f_pos
id|off_t
id|f_pos
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|old_task
r_struct
id|task_struct
op_star
id|old_task
suffix:semicolon
DECL|member|wait_address
r_struct
id|task_struct
op_star
op_star
id|wait_address
suffix:semicolon
DECL|typedef|wait_entry
)brace
id|wait_entry
suffix:semicolon
DECL|struct|select_table_struct
r_typedef
r_struct
id|select_table_struct
(brace
DECL|member|nr
DECL|member|woken
r_int
id|nr
comma
id|woken
suffix:semicolon
DECL|member|current
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
DECL|member|next_table
r_struct
id|select_table_struct
op_star
id|next_table
suffix:semicolon
DECL|member|entry
id|wait_entry
id|entry
(braket
id|NR_OPEN
op_star
l_int|3
)braket
suffix:semicolon
DECL|typedef|select_table
)brace
id|select_table
suffix:semicolon
DECL|struct|super_block
r_struct
id|super_block
(brace
DECL|member|s_ninodes
r_int
r_int
id|s_ninodes
suffix:semicolon
DECL|member|s_nzones
r_int
r_int
id|s_nzones
suffix:semicolon
DECL|member|s_imap_blocks
r_int
r_int
id|s_imap_blocks
suffix:semicolon
DECL|member|s_zmap_blocks
r_int
r_int
id|s_zmap_blocks
suffix:semicolon
DECL|member|s_firstdatazone
r_int
r_int
id|s_firstdatazone
suffix:semicolon
DECL|member|s_log_zone_size
r_int
r_int
id|s_log_zone_size
suffix:semicolon
DECL|member|s_max_size
r_int
r_int
id|s_max_size
suffix:semicolon
DECL|member|s_magic
r_int
r_int
id|s_magic
suffix:semicolon
multiline_comment|/* These are only in memory */
DECL|member|s_imap
r_struct
id|buffer_head
op_star
id|s_imap
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|s_zmap
r_struct
id|buffer_head
op_star
id|s_zmap
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|s_dev
r_int
r_int
id|s_dev
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
DECL|member|s_time
r_int
r_int
id|s_time
suffix:semicolon
DECL|member|s_wait
r_struct
id|task_struct
op_star
id|s_wait
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
multiline_comment|/* TUBE */
DECL|member|s_op
r_struct
id|super_operations
op_star
id|s_op
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
id|count
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
r_struct
id|inode
op_star
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
id|inode
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
id|inode
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
id|inode
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
id|sb
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
id|sb
comma
r_struct
id|statfs
op_star
id|buf
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
id|sb
comma
r_void
op_star
id|mode
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|file_operations
op_star
id|chrdev_fops
(braket
id|MAX_CHRDEV
)braket
suffix:semicolon
r_extern
r_struct
id|file_operations
op_star
id|blkdev_fops
(braket
id|MAX_BLKDEV
)braket
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
r_struct
id|inode
id|inode_table
(braket
id|NR_INODE
)braket
suffix:semicolon
r_extern
r_struct
id|file
id|file_table
(braket
id|NR_FILE
)braket
suffix:semicolon
r_extern
r_struct
id|super_block
id|super_block
(braket
id|NR_SUPER
)braket
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|start_buffer
suffix:semicolon
r_extern
r_int
id|nr_buffers
suffix:semicolon
r_extern
r_void
id|check_disk_change
c_func
(paren
r_int
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
r_int
id|ticks_to_floppy_on
c_func
(paren
r_int
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|floppy_on
c_func
(paren
r_int
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|sync_inodes
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wait_on
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
r_struct
id|inode
op_star
id|namei
c_func
(paren
r_const
r_char
op_star
id|pathname
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|lnamei
c_func
(paren
r_const
r_char
op_star
id|pathname
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
r_struct
id|inode
op_star
id|_namei
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|inode
op_star
id|base
comma
r_int
id|follow_links
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
r_int
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
id|iget
c_func
(paren
r_int
id|dev
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
id|buffer_head
op_star
id|get_hash_table
c_func
(paren
r_int
id|dev
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|getblk
c_func
(paren
r_int
id|dev
comma
r_int
id|block
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
r_struct
id|buffer_head
op_star
id|bh
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
r_struct
id|buffer_head
op_star
id|bread
c_func
(paren
r_int
id|dev
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_void
id|bread_page
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|dev
comma
r_int
id|b
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|breada
c_func
(paren
r_int
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
r_int
id|sync_dev
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|get_super
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
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
r_void
id|lock_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|free_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
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
macro_line|#endif
eof
