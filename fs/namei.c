macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;const.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
DECL|macro|ACC_MODE
mdefine_line|#define ACC_MODE(x) (&quot;&bslash;004&bslash;002&bslash;006&bslash;377&quot;[(x)&amp;O_ACCMODE])
multiline_comment|/*&n; * comment out this line if you want names &gt; NAME_LEN chars to be&n; * truncated. Else they will be disallowed.&n; */
multiline_comment|/* #define NO_TRUNCATE */
DECL|macro|MAY_EXEC
mdefine_line|#define MAY_EXEC 1
DECL|macro|MAY_WRITE
mdefine_line|#define MAY_WRITE 2
DECL|macro|MAY_READ
mdefine_line|#define MAY_READ 4
multiline_comment|/*&n; *&t;permission()&n; *&n; * is used to check for read/write/execute permissions on a file.&n; * I don&squot;t know if we should look at just the euid or both euid and&n; * uid, but that should be easily changed.&n; */
DECL|function|permission
r_static
r_int
id|permission
c_func
(paren
r_struct
id|m_inode
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
id|inode-&gt;i_nlinks
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;uid
op_logical_and
id|current-&gt;euid
)paren
)paren
id|mode
op_assign
l_int|0777
suffix:semicolon
r_else
r_if
c_cond
(paren
id|current-&gt;uid
op_eq
id|inode-&gt;i_uid
op_logical_or
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
id|current-&gt;gid
op_eq
id|inode-&gt;i_gid
op_logical_or
id|current-&gt;egid
op_eq
id|inode-&gt;i_gid
)paren
id|mode
op_rshift_assign
l_int|3
suffix:semicolon
r_return
id|mode
op_amp
id|mask
op_amp
l_int|0007
suffix:semicolon
)brace
multiline_comment|/*&n; * ok, we cannot use strncmp, as the name is not in our data space.&n; * Thus we&squot;ll have to use match. No big problem. Match also makes&n; * some sanity tests.&n; *&n; * NOTE! unlike strncmp, match returns 1 for success, 0 for failure.&n; */
DECL|function|match
r_static
r_int
id|match
c_func
(paren
r_int
id|len
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|dir_entry
op_star
id|de
)paren
(brace
r_register
r_int
id|same
id|__asm__
c_func
(paren
l_string|&quot;ax&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
op_logical_or
op_logical_neg
id|de-&gt;inode
op_logical_or
id|len
OG
id|NAME_LEN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|NAME_LEN
op_logical_and
id|de-&gt;name
(braket
id|len
)braket
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;fs ; repe ; cmpsb&bslash;n&bslash;t&quot;
l_string|&quot;setz %%al&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|same
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|name
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|de-&gt;name
)paren
comma
l_string|&quot;c&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|same
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;find_entry()&n; *&n; * finds and entry in the specified directory with the wanted name. It&n; * returns the cache buffer in which the entry was found, and the entry&n; * itself (as a parameter - res_dir). It does NOT read the inode of the&n; * entry - you&squot;ll have to do that yourself if you want to.&n; */
DECL|function|find_entry
r_static
r_struct
id|buffer_head
op_star
id|find_entry
c_func
(paren
r_struct
id|m_inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|dir_entry
op_star
op_star
id|res_dir
)paren
(brace
r_int
id|entries
suffix:semicolon
r_int
id|block
comma
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
macro_line|#ifdef NO_TRUNCATE
r_if
c_cond
(paren
id|namelen
OG
id|NAME_LEN
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|namelen
OG
id|NAME_LEN
)paren
id|namelen
op_assign
id|NAME_LEN
suffix:semicolon
macro_line|#endif
id|entries
op_assign
id|dir-&gt;i_size
op_div
(paren
r_sizeof
(paren
r_struct
id|dir_entry
)paren
)paren
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|dir-&gt;i_zone
(braket
l_int|0
)braket
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|block
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_ge
id|BLOCK_SIZE
op_plus
id|bh-&gt;b_data
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|bmap
c_func
(paren
id|dir
comma
id|i
op_div
id|DIR_ENTRIES_PER_BLOCK
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|block
)paren
)paren
)paren
(brace
id|i
op_add_assign
id|DIR_ENTRIES_PER_BLOCK
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
)brace
r_if
c_cond
(paren
id|match
c_func
(paren
id|namelen
comma
id|name
comma
id|de
)paren
)paren
(brace
op_star
id|res_dir
op_assign
id|de
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
id|de
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;add_entry()&n; *&n; * adds a file entry to the specified directory, using the same&n; * semantics as find_entry(). It returns NULL if it failed.&n; *&n; * NOTE!! The inode part of &squot;de&squot; is left at 0 - which means you&n; * may not sleep between calling this and putting something into&n; * the entry, as someone else might have used it while you slept.&n; */
DECL|function|add_entry
r_static
r_struct
id|buffer_head
op_star
id|add_entry
c_func
(paren
r_struct
id|m_inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|dir_entry
op_star
op_star
id|res_dir
)paren
(brace
r_int
id|block
comma
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef NO_TRUNCATE
r_if
c_cond
(paren
id|namelen
OG
id|NAME_LEN
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|namelen
OG
id|NAME_LEN
)paren
id|namelen
op_assign
id|NAME_LEN
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|dir-&gt;i_zone
(braket
l_int|0
)braket
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|block
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_ge
id|BLOCK_SIZE
op_plus
id|bh-&gt;b_data
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|block
op_assign
id|create_block
c_func
(paren
id|dir
comma
id|i
op_div
id|DIR_ENTRIES_PER_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|block
)paren
)paren
)paren
(brace
id|i
op_add_assign
id|DIR_ENTRIES_PER_BLOCK
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_star
r_sizeof
(paren
r_struct
id|dir_entry
)paren
op_ge
id|dir-&gt;i_size
)paren
(brace
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_size
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|dir_entry
)paren
suffix:semicolon
id|dir-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
)paren
(brace
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NAME_LEN
suffix:semicolon
id|i
op_increment
)paren
id|de-&gt;name
(braket
id|i
)braket
op_assign
(paren
id|i
OL
id|namelen
)paren
ques
c_cond
id|get_fs_byte
c_func
(paren
id|name
op_plus
id|i
)paren
suffix:colon
l_int|0
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
op_star
id|res_dir
op_assign
id|de
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
id|de
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;get_dir()&n; *&n; * Getdir traverses the pathname until it hits the topmost directory.&n; * It returns NULL on failure.&n; */
DECL|function|get_dir
r_static
r_struct
id|m_inode
op_star
id|get_dir
c_func
(paren
r_const
r_char
op_star
id|pathname
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
r_struct
id|m_inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|namelen
comma
id|inr
comma
id|idev
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;root
op_logical_or
op_logical_neg
id|current-&gt;root-&gt;i_count
)paren
id|panic
c_func
(paren
l_string|&quot;No root inode&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;pwd
op_logical_or
op_logical_neg
id|current-&gt;pwd-&gt;i_count
)paren
id|panic
c_func
(paren
l_string|&quot;No cwd inode&quot;
)paren
suffix:semicolon
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
id|inode
op_assign
id|current-&gt;root
suffix:semicolon
id|pathname
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
)paren
id|inode
op_assign
id|current-&gt;pwd
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* empty name is bad */
id|inode-&gt;i_count
op_increment
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
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
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|namelen
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
id|namelen
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
r_return
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|find_entry
c_func
(paren
id|inode
comma
id|thisname
comma
id|namelen
comma
op_amp
id|de
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
l_int|NULL
suffix:semicolon
)brace
id|inr
op_assign
id|de-&gt;inode
suffix:semicolon
id|idev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|idev
comma
id|inr
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;dir_namei()&n; *&n; * dir_namei() returns the inode of the directory of the&n; * specified name, and the name within that directory.&n; */
DECL|function|dir_namei
r_static
r_struct
id|m_inode
op_star
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
)paren
(brace
r_char
id|c
suffix:semicolon
r_const
r_char
op_star
id|basename
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
op_assign
id|get_dir
c_func
(paren
id|pathname
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|basename
op_assign
id|pathname
suffix:semicolon
r_while
c_loop
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
id|basename
op_assign
id|pathname
suffix:semicolon
op_star
id|namelen
op_assign
id|pathname
op_minus
id|basename
op_minus
l_int|1
suffix:semicolon
op_star
id|name
op_assign
id|basename
suffix:semicolon
r_return
id|dir
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;namei()&n; *&n; * is used by most simple commands to get the inode of a specified name.&n; * Open, link etc use their own routines, but this is enough for things&n; * like &squot;chmod&squot; etc.&n; */
DECL|function|namei
r_struct
id|m_inode
op_star
id|namei
c_func
(paren
r_const
r_char
op_star
id|pathname
)paren
(brace
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|inr
comma
id|dev
comma
id|namelen
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
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
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
multiline_comment|/* special case: &squot;/usr/&squot; etc */
r_return
id|dir
suffix:semicolon
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inr
op_assign
id|de-&gt;inode
suffix:semicolon
id|dev
op_assign
id|dir-&gt;i_dev
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|dir
op_assign
id|iget
c_func
(paren
id|dev
comma
id|inr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|dir-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|dir
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;open_namei()&n; *&n; * namei for open - this is in fact almost the whole open-routine.&n; */
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
id|m_inode
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
id|inr
comma
id|dev
comma
id|namelen
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flag
op_amp
id|O_TRUNC
)paren
op_logical_and
op_logical_neg
(paren
id|flag
op_amp
id|O_ACCMODE
)paren
)paren
id|flag
op_or_assign
id|O_WRONLY
suffix:semicolon
id|mode
op_and_assign
l_int|0777
op_amp
op_complement
id|current-&gt;umask
suffix:semicolon
id|mode
op_or_assign
id|I_REGULAR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
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
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
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
(paren
id|O_ACCMODE
op_or
id|O_CREAT
op_or
id|O_TRUNC
)paren
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
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
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
op_minus
id|ENOENT
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
id|inode
op_assign
id|new_inode
c_func
(paren
id|dir-&gt;i_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|bh
op_assign
id|add_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|inode-&gt;i_nlinks
op_decrement
suffix:semicolon
id|iput
c_func
(paren
id|inode
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
id|ENOSPC
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_num
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
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
id|inr
op_assign
id|de-&gt;inode
suffix:semicolon
id|dev
op_assign
id|dir-&gt;i_dev
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
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
id|flag
op_amp
id|O_EXCL
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dev
comma
id|inr
)paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
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
id|O_ACCMODE
)paren
)paren
op_logical_or
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
op_ne
id|ACC_MODE
c_func
(paren
id|flag
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
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|O_TRUNC
)paren
id|truncate
c_func
(paren
id|inode
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
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|dir_block
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_logical_and
id|current-&gt;uid
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
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
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
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
id|EPERM
suffix:semicolon
)brace
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
c_func
(paren
id|bh
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
id|EEXIST
suffix:semicolon
)brace
id|inode
op_assign
id|new_inode
c_func
(paren
id|dir-&gt;i_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|inode-&gt;i_size
op_assign
l_int|32
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_zone
(braket
l_int|0
)braket
op_assign
id|new_block
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_decrement
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir_block
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|free_block
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_decrement
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ERROR
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|dir_block-&gt;b_data
suffix:semicolon
id|de-&gt;inode
op_assign
id|inode-&gt;i_num
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|de
op_increment
suffix:semicolon
id|de-&gt;inode
op_assign
id|dir-&gt;i_num
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_assign
l_int|2
suffix:semicolon
id|dir_block-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|dir_block
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|I_DIRECTORY
op_or
(paren
id|mode
op_amp
l_int|0777
op_amp
op_complement
id|current-&gt;umask
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|bh
op_assign
id|add_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|free_block
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_num
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|dir-&gt;i_nlinks
op_increment
suffix:semicolon
id|dir-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
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
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * routine to check that the specified directory is empty (for rmdir)&n; */
DECL|function|empty_dir
r_static
r_int
id|empty_dir
c_func
(paren
r_struct
id|m_inode
op_star
id|inode
)paren
(brace
r_int
id|nr
comma
id|block
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
id|len
op_assign
id|inode-&gt;i_size
op_div
r_sizeof
(paren
r_struct
id|dir_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|2
op_logical_or
op_logical_neg
id|inode-&gt;i_zone
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_zone
(braket
l_int|0
)braket
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;warning - bad directory on dev %04x&bslash;n&quot;
comma
id|inode-&gt;i_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|de
(braket
l_int|0
)braket
dot
id|inode
op_ne
id|inode-&gt;i_num
op_logical_or
op_logical_neg
id|de
(braket
l_int|1
)braket
dot
id|inode
op_logical_or
id|strcmp
c_func
(paren
l_string|&quot;.&quot;
comma
id|de
(braket
l_int|0
)braket
dot
id|name
)paren
op_logical_or
id|strcmp
c_func
(paren
l_string|&quot;..&quot;
comma
id|de
(braket
l_int|1
)braket
dot
id|name
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;warning - bad directory on dev %04x&bslash;n&quot;
comma
id|inode-&gt;i_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|nr
op_assign
l_int|2
suffix:semicolon
id|de
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|nr
OL
id|len
)paren
(brace
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|de
op_ge
(paren
r_void
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|BLOCK_SIZE
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|block
op_assign
id|bmap
c_func
(paren
id|inode
comma
id|nr
op_div
id|DIR_ENTRIES_PER_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
(brace
id|nr
op_add_assign
id|DIR_ENTRIES_PER_BLOCK
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|de
op_increment
suffix:semicolon
id|nr
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
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
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_logical_and
id|current-&gt;uid
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
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
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
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
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
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
id|brelse
c_func
(paren
id|bh
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
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|de-&gt;inode
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
id|inode
op_eq
id|dir
)paren
(brace
multiline_comment|/* we may not delete &quot;.&quot;, but &quot;../dir&quot; is ok */
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOTDIR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|empty_dir
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
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOTEMPTY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_nlinks
op_ne
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;empty directory has nlink!=2 (%d)&quot;
comma
id|inode-&gt;i_nlinks
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|dir-&gt;i_nlinks
op_decrement
suffix:semicolon
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
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
l_int|0
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
suffix:semicolon
r_struct
id|m_inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
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
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
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
id|EPERM
suffix:semicolon
)brace
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
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
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|de-&gt;inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iget failed in delete (%04x:%d)&quot;
comma
id|dir-&gt;i_dev
comma
id|de-&gt;inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
id|inode-&gt;i_nlinks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Deleting nonexistent file (%04x:%d), %d&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_num
comma
id|inode-&gt;i_nlinks
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_assign
l_int|1
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode-&gt;i_nlinks
op_decrement
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
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
id|dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|m_inode
op_star
id|oldinode
comma
op_star
id|dir
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_const
r_char
op_star
id|basename
suffix:semicolon
r_int
id|namelen
suffix:semicolon
id|oldinode
op_assign
id|namei
c_func
(paren
id|oldname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldinode
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|oldinode-&gt;i_mode
)paren
)paren
(brace
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
id|dir
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
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
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
id|bh
op_assign
id|find_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
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
id|EEXIST
suffix:semicolon
)brace
id|bh
op_assign
id|add_entry
c_func
(paren
id|dir
comma
id|basename
comma
id|namelen
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
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
id|ENOSPC
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|oldinode-&gt;i_num
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|oldinode-&gt;i_nlinks
op_increment
suffix:semicolon
id|oldinode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|oldinode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|iput
c_func
(paren
id|oldinode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
