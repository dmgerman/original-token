multiline_comment|/*&n; *  linux/fs/namei.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * Some corrections by tytso.&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|macro|ACC_MODE
mdefine_line|#define ACC_MODE(x) (&quot;&bslash;000&bslash;004&bslash;002&bslash;006&quot;[(x)&amp;O_ACCMODE])
multiline_comment|/*&n; * comment out this line if you want names &gt; MINIX_NAME_LEN chars to be&n; * truncated. Else they will be disallowed.&n; */
multiline_comment|/* #define NO_TRUNCATE */
multiline_comment|/*&n; *&t;permission()&n; *&n; * is used to check for read/write/execute permissions on a file.&n; * I don&squot;t know if we should look at just the euid or both euid and&n; * uid, but that should be easily changed.&n; */
DECL|function|permission
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
(brace
r_int
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
multiline_comment|/* special case: not even root can read/write a deleted file */
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_logical_and
op_logical_neg
id|inode-&gt;i_nlink
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
id|inode-&gt;i_uid
)paren
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
id|mode
op_rshift_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|mode
op_amp
id|mask
op_amp
l_int|0007
)paren
op_eq
id|mask
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * lookup() looks up one part of a pathname, using the fs-dependent&n; * routines (currently minix_lookup) for it. It also checks for&n; * fathers (pseudo-roots, mount-points)&n; */
DECL|function|lookup
r_int
id|lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|2
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|dir
op_eq
id|current-&gt;root
)paren
id|len
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|sb
op_assign
id|dir-&gt;i_sb
)paren
op_logical_and
(paren
id|dir
op_eq
id|sb-&gt;s_mounted
)paren
)paren
(brace
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_assign
id|sb-&gt;s_covered
)paren
id|dir-&gt;i_count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_EXEC
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
op_star
id|result
op_assign
id|dir
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;lookup
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|lookup
c_func
(paren
id|dir
comma
id|name
comma
id|len
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|follow_link
r_int
id|follow_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|inode
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|inode
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;follow_link
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|inode-&gt;i_op
op_member_access_from_pointer
id|follow_link
c_func
(paren
id|dir
comma
id|inode
comma
id|flag
comma
id|mode
comma
id|res_inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;dir_namei()&n; *&n; * dir_namei() returns the inode of the directory of the&n; * specified name, and the name within that directory.&n; */
DECL|function|dir_namei
r_static
r_int
id|dir_namei
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
op_star
id|namelen
comma
r_const
r_char
op_star
op_star
id|name
comma
r_struct
id|inode
op_star
id|base
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
(brace
r_char
id|c
suffix:semicolon
r_const
r_char
op_star
id|thisname
suffix:semicolon
r_int
id|len
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|base
op_assign
id|current-&gt;pwd
suffix:semicolon
id|base-&gt;i_count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|pathname
)paren
)paren
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|iput
c_func
(paren
id|base
)paren
suffix:semicolon
id|base
op_assign
id|current-&gt;root
suffix:semicolon
id|pathname
op_increment
suffix:semicolon
id|base-&gt;i_count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|thisname
op_assign
id|pathname
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
(paren
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|pathname
op_increment
)paren
)paren
op_logical_and
(paren
id|c
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|len
op_increment
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
id|base-&gt;i_count
op_increment
suffix:semicolon
id|error
op_assign
id|lookup
c_func
(paren
id|base
comma
id|thisname
comma
id|len
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|iput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
id|follow_link
c_func
(paren
id|base
comma
id|inode
comma
l_int|0
comma
l_int|0
comma
op_amp
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
op_star
id|name
op_assign
id|thisname
suffix:semicolon
op_star
id|namelen
op_assign
id|len
suffix:semicolon
op_star
id|res_inode
op_assign
id|base
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|_namei
r_static
r_int
id|_namei
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
id|base
comma
r_int
id|follow_links
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|pathname
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
id|base
comma
op_amp
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|base-&gt;i_count
op_increment
suffix:semicolon
multiline_comment|/* lookup uses up base */
id|error
op_assign
id|lookup
c_func
(paren
id|base
comma
id|basename
comma
id|namelen
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|iput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|follow_links
)paren
(brace
id|error
op_assign
id|follow_link
c_func
(paren
id|base
comma
id|inode
comma
l_int|0
comma
l_int|0
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
r_else
id|iput
c_func
(paren
id|base
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lnamei
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
(brace
r_return
id|_namei
c_func
(paren
id|pathname
comma
l_int|NULL
comma
l_int|0
comma
id|res_inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;namei()&n; *&n; * is used by most simple commands to get the inode of a specified name.&n; * Open, link etc use their own routines, but this is enough for things&n; * like &squot;chmod&squot; etc.&n; */
DECL|function|namei
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
(brace
r_return
id|_namei
c_func
(paren
id|pathname
comma
l_int|NULL
comma
l_int|1
comma
id|res_inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;open_namei()&n; *&n; * namei for open - this is in fact almost the whole open-routine.&n; *&n; * Note that the low bits of &quot;flag&quot; aren&squot;t the same asin the open&n; * system call - they are 00 - no permissions needed&n; *&t;&t;&t;  01 - read permission needed&n; *&t;&t;&t;  10 - write permission needed&n; *&t;&t;&t;  11 - read/write permissions needed&n; * which is a lot more logical, and also allows the &quot;no perm&quot; needed&n; * for symlinks (where the permissions are checked later).&n; */
DECL|function|open_namei
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
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
comma
id|i
suffix:semicolon
r_struct
id|inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
id|mode
op_and_assign
l_int|07777
op_amp
op_complement
id|current-&gt;umask
suffix:semicolon
id|mode
op_or_assign
id|S_IFREG
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|pathname
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
id|base
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
multiline_comment|/* special case: &squot;/usr/&squot; etc */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flag
op_amp
l_int|2
)paren
)paren
(brace
op_star
id|res_inode
op_assign
id|dir
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
id|dir-&gt;i_count
op_increment
suffix:semicolon
multiline_comment|/* lookup eats the dir */
id|error
op_assign
id|lookup
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flag
op_amp
id|O_CREAT
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;create
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|create
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
id|mode
comma
id|res_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flag
op_amp
id|O_EXCL
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_assign
id|follow_link
c_func
(paren
id|dir
comma
id|inode
comma
id|flag
comma
id|mode
comma
op_amp
id|inode
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
(paren
id|flag
op_amp
l_int|2
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|ACC_MODE
c_func
(paren
id|flag
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|IS_NODEV
c_func
(paren
id|inode
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
op_logical_and
(paren
id|flag
op_amp
l_int|2
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|inode-&gt;i_count
OG
l_int|1
)paren
op_logical_and
(paren
id|flag
op_amp
l_int|2
)paren
)paren
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|executable
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ETXTBSY
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|numlibraries
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|inode
op_eq
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|libraries
(braket
id|i
)braket
dot
id|library
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ETXTBSY
suffix:semicolon
)brace
)brace
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_mknod
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
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|dir
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|filename
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;mknod
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|mknod
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|sys_mknod
r_int
id|sys_mknod
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
(brace
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|mode
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
r_return
id|do_mknod
c_func
(paren
id|filename
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|sys_mkdir
r_int
id|sys_mkdir
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
)paren
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|dir
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|pathname
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;mkdir
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|mkdir
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|sys_rmdir
r_int
id|sys_rmdir
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|dir
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|name
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;rmdir
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|rmdir
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
)paren
suffix:semicolon
)brace
DECL|function|sys_unlink
r_int
id|sys_unlink
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|dir
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|name
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;unlink
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|unlink
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
)paren
suffix:semicolon
)brace
DECL|function|sys_symlink
r_int
id|sys_symlink
c_func
(paren
r_const
r_char
op_star
id|oldname
comma
r_const
r_char
op_star
id|newname
)paren
(brace
r_struct
id|inode
op_star
id|dir
suffix:semicolon
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|newname
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;symlink
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|symlink
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
id|oldname
)paren
suffix:semicolon
)brace
DECL|function|sys_link
r_int
id|sys_link
c_func
(paren
r_const
r_char
op_star
id|oldname
comma
r_const
r_char
op_star
id|newname
)paren
(brace
r_struct
id|inode
op_star
id|oldinode
comma
op_star
id|dir
suffix:semicolon
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
id|error
op_assign
id|namei
c_func
(paren
id|oldname
comma
op_amp
id|oldinode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|newname
comma
op_amp
id|namelen
comma
op_amp
id|basename
comma
l_int|NULL
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir-&gt;i_dev
op_ne
id|oldinode-&gt;i_dev
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
r_return
op_minus
id|EXDEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;link
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|dir-&gt;i_op
op_member_access_from_pointer
id|link
c_func
(paren
id|oldinode
comma
id|dir
comma
id|basename
comma
id|namelen
)paren
suffix:semicolon
)brace
DECL|function|sys_rename
r_int
id|sys_rename
c_func
(paren
r_const
r_char
op_star
id|oldname
comma
r_const
r_char
op_star
id|newname
)paren
(brace
r_struct
id|inode
op_star
id|old_dir
comma
op_star
id|new_dir
suffix:semicolon
r_const
r_char
op_star
id|old_base
comma
op_star
id|new_base
suffix:semicolon
r_int
id|old_len
comma
id|new_len
comma
id|error
suffix:semicolon
id|error
op_assign
id|dir_namei
c_func
(paren
id|oldname
comma
op_amp
id|old_len
comma
op_amp
id|old_base
comma
l_int|NULL
comma
op_amp
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|old_dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|old_len
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|old_base
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|old_len
op_eq
l_int|1
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|old_base
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
id|old_len
op_eq
l_int|2
)paren
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|error
op_assign
id|dir_namei
c_func
(paren
id|newname
comma
op_amp
id|new_len
comma
op_amp
id|new_base
comma
l_int|NULL
comma
op_amp
id|new_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|new_dir
comma
id|MAY_WRITE
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_len
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|new_base
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|new_len
op_eq
l_int|1
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|new_base
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
id|new_len
op_eq
l_int|2
)paren
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_dir-&gt;i_dev
op_ne
id|old_dir-&gt;i_dev
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
op_minus
id|EXDEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|new_dir
)paren
op_logical_or
id|IS_RDONLY
c_func
(paren
id|old_dir
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|old_dir-&gt;i_op
op_logical_or
op_logical_neg
id|old_dir-&gt;i_op-&gt;rename
)paren
(brace
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|old_dir-&gt;i_op
op_member_access_from_pointer
id|rename
c_func
(paren
id|old_dir
comma
id|old_base
comma
id|old_len
comma
id|new_dir
comma
id|new_base
comma
id|new_len
)paren
suffix:semicolon
)brace
eof
