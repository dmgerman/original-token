multiline_comment|/*&n; *  linux/fs/msdos/misc.c&n; *&n; *  Written 1992 by Werner Almesberger&n; */
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|variable|bin_extensions
r_static
r_char
id|bin_extensions
(braket
)braket
op_assign
l_string|&quot;EXECOMAPPSYSOVLOBJLIB&quot;
multiline_comment|/* program code */
l_string|&quot;ARCZIPLHALZHZOOTARZ  ARJTZ &quot;
multiline_comment|/* common archivers */
l_string|&quot;GIFBMPTIFGL JPGPCX&quot;
multiline_comment|/* graphics */
l_string|&quot;TFMVF GF PK PXLDVI&quot;
suffix:semicolon
multiline_comment|/* TeX */
multiline_comment|/* Select binary/text conversion */
DECL|function|is_binary
r_int
id|is_binary
c_func
(paren
r_char
id|conversion
comma
r_char
op_star
id|extension
)paren
(brace
r_char
op_star
id|walk
suffix:semicolon
r_switch
c_cond
(paren
id|conversion
)paren
(brace
r_case
l_char|&squot;b&squot;
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
r_for
c_loop
(paren
id|walk
op_assign
id|bin_extensions
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_add_assign
l_int|3
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|extension
comma
id|walk
comma
l_int|3
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Invalid conversion mode&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|creation_wait
r_static
r_struct
id|wait_queue
op_star
id|creation_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|creation_lock
r_static
id|creation_lock
op_assign
l_int|0
suffix:semicolon
DECL|function|lock_creation
r_void
id|lock_creation
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|creation_lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|creation_wait
)paren
suffix:semicolon
id|creation_lock
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|unlock_creation
r_void
id|unlock_creation
c_func
(paren
r_void
)paren
(brace
id|creation_lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|creation_wait
)paren
suffix:semicolon
)brace
DECL|function|msdos_add_cluster
r_int
id|msdos_add_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_static
r_struct
id|wait_queue
op_star
id|wait
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|lock
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|previous
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* works best if one FS is being used */
r_int
id|count
comma
id|this
comma
id|limit
comma
id|last
comma
id|current
comma
id|sector
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
r_while
c_loop
(paren
id|lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
id|lock
op_assign
l_int|1
suffix:semicolon
id|limit
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|clusters
suffix:semicolon
id|this
op_assign
id|limit
suffix:semicolon
multiline_comment|/* to keep GCC happy */
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|limit
suffix:semicolon
id|count
op_increment
)paren
(brace
id|this
op_assign
(paren
(paren
id|count
op_plus
id|previous
)paren
op_mod
id|limit
)paren
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;free cluster: %d&bslash;r&bslash;n&quot;
comma
id|this
)paren
suffix:semicolon
macro_line|#endif
id|previous
op_assign
(paren
id|count
op_plus
id|previous
op_plus
l_int|1
)paren
op_mod
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|limit
)paren
(brace
id|lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|12
ques
c_cond
l_int|0xff8
suffix:colon
l_int|0xfff8
)paren
suffix:semicolon
id|lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;set to %x&bslash;r&bslash;n&quot;
comma
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
op_minus
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
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
id|last
op_assign
id|inode-&gt;i_size
ques
c_cond
id|get_cluster
c_func
(paren
id|inode
comma
(paren
id|inode-&gt;i_size
op_minus
l_int|1
)paren
op_div
id|SECTOR_SIZE
op_div
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|last
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current
op_assign
id|inode-&gt;i_data
(braket
id|D_START
)braket
)paren
(brace
id|cache_lookup
c_func
(paren
id|inode
comma
l_int|0x7fffffff
comma
op_amp
id|last
comma
op_amp
id|current
)paren
suffix:semicolon
r_while
c_loop
(paren
id|current
op_logical_and
id|current
op_ne
op_minus
l_int|1
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|current
op_assign
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|last
op_assign
id|current
comma
op_minus
l_int|1
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;File without EOF&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;last = %d&bslash;r&bslash;n&quot;
comma
id|last
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|last
)paren
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|last
comma
id|this
)paren
suffix:semicolon
r_else
(brace
id|inode-&gt;i_data
(braket
id|D_START
)braket
op_assign
id|this
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|last
)paren
id|printk
c_func
(paren
l_string|&quot;next set to %d&bslash;r&bslash;n&quot;
comma
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|last
comma
op_minus
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|current
op_assign
l_int|0
suffix:semicolon
id|current
OL
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
id|current
op_increment
)paren
(brace
id|sector
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|data_start
op_plus
(paren
id|this
op_minus
l_int|2
)paren
op_star
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
op_plus
id|current
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;zeroing sector %d&bslash;r&bslash;n&quot;
comma
id|sector
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|current
OL
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
op_minus
l_int|1
op_logical_and
op_logical_neg
(paren
id|sector
op_amp
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|sector
op_rshift
l_int|1
comma
id|BLOCK_SIZE
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;getblk failed&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|memset
c_func
(paren
id|bh-&gt;b_data
comma
l_int|0
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
)brace
id|current
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|msdos_sread
c_func
(paren
id|inode-&gt;i_dev
comma
id|sector
comma
op_amp
id|data
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;msdos_sread failed&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
id|SECTOR_SIZE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
)paren
(brace
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
)brace
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_size
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Odd directory size&quot;
)paren
suffix:semicolon
id|inode-&gt;i_size
op_add_assign
id|SECTOR_SIZE
op_star
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;size is %d now (%x)&bslash;r&bslash;n&quot;
comma
id|inode-&gt;i_size
comma
id|inode
)paren
suffix:semicolon
macro_line|#endif
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Linear day numbers of the respective 1sts in non-leap years. */
DECL|variable|day_n
r_static
r_int
id|day_n
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* JanFebMarApr May Jun Jul Aug Sep Oct Nov Dec */
multiline_comment|/* Convert a MS-DOS time/date pair to a UNIX date (seconds since 1 1 70). */
DECL|function|date_dos2unix
r_int
id|date_dos2unix
c_func
(paren
r_int
r_int
id|time
comma
r_int
r_int
id|date
)paren
(brace
r_int
id|month
comma
id|year
suffix:semicolon
id|month
op_assign
(paren
(paren
id|date
op_rshift
l_int|5
)paren
op_amp
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
id|year
op_assign
id|date
op_rshift
l_int|9
suffix:semicolon
r_return
(paren
id|time
op_amp
l_int|31
)paren
op_star
l_int|2
op_plus
l_int|60
op_star
(paren
(paren
id|time
op_rshift
l_int|5
)paren
op_amp
l_int|63
)paren
op_plus
(paren
id|time
op_rshift
l_int|11
)paren
op_star
l_int|3600
op_plus
l_int|86400
op_star
(paren
(paren
id|date
op_amp
l_int|31
)paren
op_minus
l_int|1
op_plus
id|day_n
(braket
id|month
)braket
op_plus
(paren
id|year
op_div
l_int|4
)paren
op_plus
id|year
op_star
l_int|365
op_minus
(paren
(paren
id|year
op_amp
l_int|3
)paren
op_eq
l_int|0
op_logical_and
id|month
OL
l_int|2
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_plus
l_int|3653
)paren
suffix:semicolon
multiline_comment|/* days since 1.1.70 plus 80&squot;s leap day */
)brace
multiline_comment|/* Convert linear UNIX date to a MS-DOS time/date pair. */
DECL|function|date_unix2dos
r_void
id|date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
r_int
r_int
op_star
id|time
comma
r_int
r_int
op_star
id|date
)paren
(brace
r_int
id|day
comma
id|year
comma
id|nl_day
comma
id|month
suffix:semicolon
op_star
id|time
op_assign
(paren
id|unix_date
op_mod
l_int|60
)paren
op_div
l_int|2
op_plus
(paren
(paren
(paren
id|unix_date
op_div
l_int|60
)paren
op_mod
l_int|60
)paren
op_lshift
l_int|5
)paren
op_plus
(paren
(paren
(paren
id|unix_date
op_div
l_int|3600
)paren
op_mod
l_int|24
)paren
op_lshift
l_int|11
)paren
suffix:semicolon
id|day
op_assign
id|unix_date
op_div
l_int|86400
op_minus
l_int|3652
suffix:semicolon
id|year
op_assign
id|day
op_div
l_int|365
suffix:semicolon
r_if
c_cond
(paren
(paren
id|year
op_plus
l_int|3
)paren
op_div
l_int|4
op_plus
l_int|365
op_star
id|year
OG
id|day
)paren
id|year
op_decrement
suffix:semicolon
id|day
op_sub_assign
(paren
id|year
op_plus
l_int|3
)paren
op_div
l_int|4
op_plus
l_int|365
op_star
id|year
suffix:semicolon
r_if
c_cond
(paren
id|day
op_eq
l_int|59
op_logical_and
op_logical_neg
(paren
id|year
op_amp
l_int|3
)paren
)paren
(brace
id|nl_day
op_assign
id|day
suffix:semicolon
id|month
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|nl_day
op_assign
(paren
id|year
op_amp
l_int|3
)paren
op_logical_or
id|day
op_le
l_int|59
ques
c_cond
id|day
suffix:colon
id|day
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|month
op_assign
l_int|0
suffix:semicolon
id|month
OL
l_int|12
suffix:semicolon
id|month
op_increment
)paren
r_if
c_cond
(paren
id|day_n
(braket
id|month
)braket
OG
id|nl_day
)paren
r_break
suffix:semicolon
)brace
op_star
id|date
op_assign
id|nl_day
op_minus
id|day_n
(braket
id|month
op_minus
l_int|1
)braket
op_plus
l_int|1
op_plus
(paren
id|month
op_lshift
l_int|5
)paren
op_plus
(paren
id|year
op_lshift
l_int|9
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the inode number of the directory entry at offset pos. If bh is&n;   non-NULL, it is brelse&squot;d before. Pos is incremented. The buffer header is&n;   returned in bh. */
DECL|function|msdos_get_entry
r_int
id|msdos_get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
op_star
id|pos
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
)paren
(brace
r_int
id|sector
comma
id|offset
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|offset
op_assign
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sector
op_assign
id|msdos_smap
c_func
(paren
id|dir
comma
op_star
id|pos
op_rshift
id|SECTOR_BITS
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sector
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* FAT error ... */
op_star
id|pos
op_add_assign
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bh
)paren
id|brelse
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bh
op_assign
id|msdos_sread
c_func
(paren
id|dir-&gt;i_dev
comma
id|sector
comma
op_amp
id|data
)paren
)paren
)paren
r_continue
suffix:semicolon
op_star
id|de
op_assign
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
(paren
id|data
op_plus
(paren
id|offset
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|sector
op_lshift
id|MSDOS_DPS_BITS
)paren
op_plus
(paren
(paren
id|offset
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|MSDOS_DIR_BITS
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Scans a directory for a given file (name points to its formatted name) or&n;   for an empty directory slot (name is NULL). Returns the inode number. */
DECL|function|msdos_scan
r_int
id|msdos_scan
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_char
op_star
id|name
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
comma
r_int
op_star
id|ino
)paren
(brace
r_int
id|pos
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
op_star
id|res_bh
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|ino
op_assign
id|msdos_get_entry
c_func
(paren
id|dir
comma
op_amp
id|pos
comma
id|res_bh
comma
op_amp
id|de
)paren
)paren
OG
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|name
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_logical_and
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|de-&gt;name
)paren
)paren
(braket
l_int|0
)braket
op_ne
id|DELETED_FLAG
op_logical_and
op_logical_neg
(paren
id|de-&gt;attr
op_amp
id|ATTR_VOLUME
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|de-&gt;name
comma
id|name
comma
id|MSDOS_NAME
)paren
)paren
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;name
(braket
l_int|0
)braket
op_logical_or
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|de-&gt;name
)paren
)paren
(braket
l_int|0
)braket
op_eq
id|DELETED_FLAG
)paren
(brace
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
op_star
id|ino
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_data
(braket
id|D_BUSY
)braket
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* skip deleted files that haven&squot;t been closed yet */
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|ino
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_star
id|res_bh
)paren
id|brelse
c_func
(paren
op_star
id|res_bh
)paren
suffix:semicolon
op_star
id|res_bh
op_assign
l_int|NULL
suffix:semicolon
r_return
id|name
ques
c_cond
op_minus
id|ENOENT
suffix:colon
op_minus
id|ENOSPC
suffix:semicolon
)brace
op_star
id|res_de
op_assign
id|de
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Now an ugly part: this set of directory scan routines works on clusters&n;   rather than on inodes and sectors. They are necessary to locate the &squot;..&squot;&n;   directory &quot;inode&quot;. */
DECL|function|raw_found
r_static
r_int
id|raw_found
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|sector
comma
r_char
op_star
id|name
comma
r_int
id|number
comma
r_int
op_star
id|ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|data
suffix:semicolon
r_int
id|entry
comma
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|msdos_sread
c_func
(paren
id|sb-&gt;s_dev
comma
id|sector
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|data
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|MSDOS_DPS
suffix:semicolon
id|entry
op_increment
)paren
r_if
c_cond
(paren
id|name
ques
c_cond
op_logical_neg
id|strncmp
c_func
(paren
id|data
(braket
id|entry
)braket
dot
id|name
comma
id|name
comma
id|MSDOS_NAME
)paren
suffix:colon
op_star
(paren
r_int
r_char
op_star
)paren
id|data
(braket
id|entry
)braket
dot
id|name
op_ne
id|DELETED_FLAG
op_logical_and
id|data
(braket
id|entry
)braket
dot
id|start
op_eq
id|number
)paren
(brace
r_if
c_cond
(paren
id|ino
)paren
op_star
id|ino
op_assign
id|sector
op_star
id|MSDOS_DPS
op_plus
id|entry
suffix:semicolon
id|start
op_assign
id|data
(braket
id|entry
)braket
dot
id|start
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|raw_scan_root
r_static
r_int
id|raw_scan_root
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|name
comma
r_int
id|number
comma
r_int
op_star
id|ino
)paren
(brace
r_int
id|count
comma
id|cluster
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_entries
op_div
id|MSDOS_DPS
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|cluster
op_assign
id|raw_found
c_func
(paren
id|sb
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_start
op_plus
id|count
comma
id|name
comma
id|number
comma
id|ino
)paren
)paren
op_ge
l_int|0
)paren
r_return
id|cluster
suffix:semicolon
)brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|raw_scan_nonroot
r_static
r_int
id|raw_scan_nonroot
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|start
comma
r_char
op_star
id|name
comma
r_int
id|number
comma
r_int
op_star
id|ino
)paren
(brace
r_int
id|count
comma
id|cluster
suffix:semicolon
r_do
(brace
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|cluster
op_assign
id|raw_found
c_func
(paren
id|sb
comma
(paren
id|start
op_minus
l_int|2
)paren
op_star
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|data_start
op_plus
id|count
comma
id|name
comma
id|number
comma
id|ino
)paren
)paren
op_ge
l_int|0
)paren
r_return
id|cluster
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|start
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|start
comma
op_minus
l_int|1
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;FAT error&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
op_ne
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|raw_scan
r_static
r_int
id|raw_scan
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|start
comma
r_char
op_star
id|name
comma
r_int
id|number
comma
r_int
op_star
id|ino
)paren
(brace
r_if
c_cond
(paren
id|start
)paren
r_return
id|raw_scan_nonroot
c_func
(paren
id|sb
comma
id|start
comma
id|name
comma
id|number
comma
id|ino
)paren
suffix:semicolon
r_else
r_return
id|raw_scan_root
c_func
(paren
id|sb
comma
id|name
comma
id|number
comma
id|ino
)paren
suffix:semicolon
)brace
DECL|function|msdos_parent_ino
r_int
id|msdos_parent_ino
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|locked
)paren
(brace
r_int
id|error
comma
id|current
comma
id|prev
comma
id|this
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Non-directory fed to m_p_i&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
r_return
id|dir-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|lock_creation
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent renames */
r_if
c_cond
(paren
(paren
id|current
op_assign
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|dir-&gt;i_data
(braket
id|D_START
)braket
comma
id|MSDOS_DOTDOT
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|current
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|current
)paren
id|this
op_assign
id|MSDOS_ROOT_INO
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
(paren
id|prev
op_assign
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|current
comma
id|MSDOS_DOTDOT
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|prev
comma
l_int|NULL
comma
id|current
comma
op_amp
id|this
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|this
suffix:semicolon
)brace
eof