multiline_comment|/*&n; *  linux/fs/fat/misc.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;msbuffer.h&quot;
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x)
DECL|macro|Printk
mdefine_line|#define Printk(x)&t;printk x
multiline_comment|/* Well-known binary file extensions - of course there are many more */
DECL|variable|bin_extensions
r_static
r_char
id|bin_extensions
(braket
)braket
op_assign
l_string|&quot;EXE&quot;
l_string|&quot;COM&quot;
l_string|&quot;BIN&quot;
l_string|&quot;APP&quot;
l_string|&quot;SYS&quot;
l_string|&quot;DRV&quot;
l_string|&quot;OVL&quot;
l_string|&quot;OVR&quot;
l_string|&quot;OBJ&quot;
l_string|&quot;LIB&quot;
l_string|&quot;DLL&quot;
l_string|&quot;PIF&quot;
multiline_comment|/* program code */
l_string|&quot;ARC&quot;
l_string|&quot;ZIP&quot;
l_string|&quot;LHA&quot;
l_string|&quot;LZH&quot;
l_string|&quot;ZOO&quot;
l_string|&quot;TAR&quot;
l_string|&quot;Z  &quot;
l_string|&quot;ARJ&quot;
multiline_comment|/* common archivers */
l_string|&quot;TZ &quot;
l_string|&quot;TAZ&quot;
l_string|&quot;TZP&quot;
l_string|&quot;TPZ&quot;
multiline_comment|/* abbreviations of tar.Z and tar.zip */
l_string|&quot;GZ &quot;
l_string|&quot;TGZ&quot;
l_string|&quot;DEB&quot;
multiline_comment|/* .gz, .tar.gz and Debian packages   */
l_string|&quot;GIF&quot;
l_string|&quot;BMP&quot;
l_string|&quot;TIF&quot;
l_string|&quot;GL &quot;
l_string|&quot;JPG&quot;
l_string|&quot;PCX&quot;
multiline_comment|/* graphics */
l_string|&quot;TFM&quot;
l_string|&quot;VF &quot;
l_string|&quot;GF &quot;
l_string|&quot;PK &quot;
l_string|&quot;PXL&quot;
l_string|&quot;DVI&quot;
suffix:semicolon
multiline_comment|/* TeX */
multiline_comment|/*&n; * fat_fs_panic reports a severe file system problem and sets the file system&n; * read-only. The file system can be made writable again by remounting it.&n; */
DECL|function|fat_fs_panic
r_void
id|fat_fs_panic
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_const
r_char
op_star
id|msg
)paren
(brace
r_int
id|not_ro
suffix:semicolon
id|not_ro
op_assign
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|not_ro
)paren
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Filesystem panic (dev %s, &quot;
comma
id|kdevname
c_func
(paren
id|s-&gt;s_dev
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mounted on %s:%ld)&bslash;n  %s&bslash;n&quot;
comma
multiline_comment|/* note: kdevname returns &amp; static char[] */
id|kdevname
c_func
(paren
id|s-&gt;s_covered-&gt;i_dev
)paren
comma
id|s-&gt;s_covered-&gt;i_ino
comma
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|not_ro
)paren
id|printk
c_func
(paren
l_string|&quot;  File system has been set read-only&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * is_binary selects optional text conversion based on the conversion mode and&n; * the extension part of the file name.&n; */
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
id|printk
c_func
(paren
l_string|&quot;Invalid conversion mode - defaulting to &quot;
l_string|&quot;binary.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* File creation lock. This is system-wide to avoid deadlocks in rename. */
multiline_comment|/* (rename might deadlock before detecting cross-FS moves.) */
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
r_int
id|creation_lock
op_assign
l_int|0
suffix:semicolon
DECL|function|fat_lock_creation
r_void
id|fat_lock_creation
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
DECL|function|fat_unlock_creation
r_void
id|fat_unlock_creation
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
DECL|function|lock_fat
r_void
id|lock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_while
c_loop
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_wait
)paren
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_lock
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|unlock_fat
r_void
id|unlock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fat_add_cluster tries to allocate a new cluster and adds it to the file&n; * represented by inode. The cluster is zero-initialized.&n; */
DECL|function|fat_add_cluster
r_int
id|fat_add_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|count
comma
id|nr
comma
id|limit
comma
id|last
comma
id|curr
comma
id|sector
comma
id|last_sector
comma
id|file_cluster
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|cluster_size
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
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
r_if
c_cond
(paren
op_logical_neg
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|lock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
id|limit
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
suffix:semicolon
id|nr
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
id|nr
op_assign
(paren
(paren
id|count
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
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
id|sb
comma
id|nr
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
id|PRINTK
(paren
(paren
l_string|&quot;cnt = %d --&quot;
comma
id|count
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;free cluster: %d&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
macro_line|#endif
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
op_assign
(paren
id|count
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
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
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_assign
l_int|0
suffix:semicolon
id|unlock_fat
c_func
(paren
id|sb
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
id|sb
comma
id|nr
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|12
ques
c_cond
id|EOF_FAT12
suffix:colon
id|EOF_FAT16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_ne
op_minus
l_int|1
)paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_decrement
suffix:semicolon
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;set to %x&bslash;n&quot;
comma
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
op_minus
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
id|last
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We must locate the last cluster of the file to add this&n;&t;   new one (nr) to the end of the link list (the FAT).&n;&t;   &n;&t;   Here file_cluster will be the number of the last cluster of the&n;&t;   file (before we add nr).&n;&t;   &n;&t;   last is the corresponding cluster number on the disk. We will&n;&t;   use last to plug the nr cluster. We will use file_cluster to&n;&t;   update the cache.&n;&t;*/
id|file_cluster
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|curr
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
op_ne
l_int|0
)paren
(brace
id|cache_lookup
c_func
(paren
id|inode
comma
id|INT_MAX
comma
op_amp
id|last
comma
op_amp
id|curr
)paren
suffix:semicolon
id|file_cluster
op_assign
id|last
suffix:semicolon
r_while
c_loop
(paren
id|curr
op_logical_and
id|curr
op_ne
op_minus
l_int|1
)paren
(brace
id|PRINTK
(paren
(paren
l_string|&quot;.&quot;
)paren
)paren
suffix:semicolon
id|file_cluster
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|curr
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|last
op_assign
id|curr
comma
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;File without EOF&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
)brace
id|PRINTK
(paren
(paren
l_string|&quot; --  &quot;
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;last = %d&bslash;n&quot;
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
id|sb
comma
id|last
comma
id|nr
)paren
suffix:semicolon
r_else
(brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
id|nr
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
l_string|&quot;next set to %d&bslash;n&quot;
comma
id|fat_access
c_func
(paren
id|sb
comma
id|last
comma
op_minus
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
id|sector
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|data_start
op_plus
(paren
id|nr
op_minus
l_int|2
)paren
op_star
id|cluster_size
suffix:semicolon
id|last_sector
op_assign
id|sector
op_plus
id|cluster_size
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|sector
OL
id|last_sector
suffix:semicolon
id|sector
op_increment
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;zeroing sector %d&bslash;n&quot;
comma
id|sector
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|fat_getblk
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;getblk failed&bslash;n&quot;
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
id|SECTOR_SIZE
)paren
suffix:semicolon
id|fat_set_uptodate
c_func
(paren
id|sb
comma
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|fat_mark_buffer_dirty
c_func
(paren
id|sb
comma
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|file_cluster
op_ne
id|inode-&gt;i_blocks
op_div
id|cluster_size
)paren
(brace
id|printk
(paren
l_string|&quot;file_cluster badly computed!!! %d &lt;&gt; %ld&bslash;n&quot;
comma
id|file_cluster
comma
id|inode-&gt;i_blocks
op_div
id|cluster_size
)paren
suffix:semicolon
)brace
r_else
(brace
id|cache_add
c_func
(paren
id|inode
comma
id|file_cluster
comma
id|nr
)paren
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_add_assign
id|cluster_size
suffix:semicolon
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
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;Odd directory size&quot;
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|SECTOR_SIZE
)paren
op_amp
op_complement
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|inode-&gt;i_size
op_add_assign
id|SECTOR_SIZE
op_star
id|cluster_size
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;size is %d now (%x)&bslash;n&quot;
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
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
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
comma
id|secs
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
id|secs
op_assign
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
id|secs
op_add_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|sys_tz.tz_dsttime
)paren
(brace
id|secs
op_sub_assign
l_int|3600
suffix:semicolon
)brace
r_return
id|secs
suffix:semicolon
)brace
multiline_comment|/* Convert linear UNIX date to a MS-DOS time/date pair. */
DECL|function|fat_date_unix2dos
r_void
id|fat_date_unix2dos
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
r_if
c_cond
(paren
id|sys_tz.tz_dsttime
)paren
(brace
id|unix_date
op_add_assign
l_int|3600
suffix:semicolon
)brace
id|unix_date
op_sub_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
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
DECL|function|fat_get_entry
r_int
id|fat_get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
id|loff_t
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_int
id|sector
comma
id|offset
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
id|PRINTK
(paren
(paren
l_string|&quot;get_entry offset %d&bslash;n&quot;
comma
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sector
op_assign
id|fat_smap
c_func
(paren
id|dir
comma
id|offset
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
id|PRINTK
(paren
(paren
l_string|&quot;get_entry sector %d %p&bslash;n&quot;
comma
id|sector
comma
op_star
id|bh
)paren
)paren
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
multiline_comment|/* beyond EOF */
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
id|fat_brelse
c_func
(paren
id|sb
comma
op_star
id|bh
)paren
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;get_entry sector apres brelse&bslash;n&quot;
)paren
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
id|fat_bread
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Directory sread (sector %d) failed&bslash;n&quot;
comma
id|sector
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|PRINTK
(paren
(paren
l_string|&quot;get_entry apres sread&bslash;n&quot;
)paren
)paren
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
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
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
multiline_comment|/*&n; * Now an ugly part: this set of directory scan routines works on clusters&n; * rather than on inodes and sectors. They are necessary to locate the &squot;..&squot;&n; * directory &quot;inode&quot;. raw_scan_sector operates in four modes:&n; *&n; * name     number   ino      action&n; * -------- -------- -------- -------------------------------------------------&n; * non-NULL -        X        Find an entry with that name&n; * NULL     non-NULL non-NULL Find an entry whose data starts at *number&n; * NULL     non-NULL NULL     Count subdirectories in *number. (*)&n; * NULL     NULL     non-NULL Find an empty entry&n; *&n; * (*) The return code should be ignored. It DOES NOT indicate success or&n; *     failure. *number has to be initialized to zero.&n; *&n; * - = not used, X = a value is returned unless NULL&n; *&n; * If res_bh is non-NULL, the buffer is not deallocated but returned to the&n; * caller on success. res_de is set accordingly.&n; *&n; * If cont is non-zero, raw_found continues with the entry after the one&n; * res_bh/res_de point to.&n; */
DECL|macro|RSS_NAME
mdefine_line|#define RSS_NAME /* search for name */ &bslash;&n;    done = !strncmp(data[entry].name,name,MSDOS_NAME) &amp;&amp; &bslash;&n;     !(data[entry].attr &amp; ATTR_VOLUME);
DECL|macro|RSS_START
mdefine_line|#define RSS_START /* search for start cluster */ &bslash;&n;    done = !IS_FREE(data[entry].name) &amp;&amp; CF_LE_W(data[entry].start) == *number;
DECL|macro|RSS_FREE
mdefine_line|#define RSS_FREE /* search for free entry */ &bslash;&n;    { &bslash;&n;&t;done = IS_FREE(data[entry].name); &bslash;&n;&t;if (done) { &bslash;&n;&t;    inode = iget(sb,sector*MSDOS_DPS+entry); &bslash;&n;&t;    if (inode) { &bslash;&n;&t;    /* Directory slots of busy deleted files aren&squot;t available yet. */ &bslash;&n;&t;&t;done = !MSDOS_I(inode)-&gt;i_busy; &bslash;&n;&t;&t;iput(inode); &bslash;&n;&t;    } &bslash;&n;&t;} &bslash;&n;    }
DECL|macro|RSS_COUNT
mdefine_line|#define RSS_COUNT /* count subdirectories */ &bslash;&n;    { &bslash;&n;&t;done = 0; &bslash;&n;&t;if (!IS_FREE(data[entry].name) &amp;&amp; (data[entry].attr &amp; ATTR_DIR)) &bslash;&n;&t;    (*number)++; &bslash;&n;    }
DECL|function|raw_scan_sector
r_static
r_int
id|raw_scan_sector
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
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
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
r_char
id|scantype
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
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|entry
comma
id|start
comma
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|fat_bread
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|data
op_assign
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
id|bh-&gt;b_data
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
(brace
multiline_comment|/* RSS_COUNT:  if (data[entry].name == name) done=true else done=false. */
r_if
c_cond
(paren
id|name
)paren
(brace
id|RSS_NAME
r_if
c_cond
(paren
id|done
op_logical_and
id|scantype
)paren
(brace
multiline_comment|/* scantype != SCAN_ANY */
id|done
op_assign
(paren
id|data
(braket
id|entry
)braket
dot
id|attr
op_amp
id|ATTR_HIDDEN
)paren
ques
c_cond
(paren
id|scantype
op_eq
id|SCAN_HID
)paren
suffix:colon
(paren
id|scantype
op_eq
id|SCAN_NOTHID
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
id|RSS_COUNT
r_else
(brace
r_if
c_cond
(paren
id|number
)paren
id|RSS_START
r_else
id|RSS_FREE
)brace
)brace
r_if
c_cond
(paren
id|done
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
id|CF_LE_W
c_func
(paren
id|data
(braket
id|entry
)braket
dot
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res_bh
)paren
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_else
(brace
op_star
id|res_bh
op_assign
id|bh
suffix:semicolon
op_star
id|res_de
op_assign
op_amp
id|data
(braket
id|entry
)braket
suffix:semicolon
)brace
r_return
id|start
suffix:semicolon
)brace
)brace
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/*&n; * raw_scan_root performs raw_scan_sector on the root directory until the&n; * requested entry is found or the end of the directory is reached.&n; */
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
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
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
r_char
id|scantype
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
id|raw_scan_sector
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
comma
id|res_bh
comma
id|res_de
comma
id|scantype
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
multiline_comment|/*&n; * raw_scan_nonroot performs raw_scan_sector on a non-root directory until the&n; * requested entry is found or the end of the directory is reached.&n; */
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
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
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
r_char
id|scantype
)paren
(brace
r_int
id|count
comma
id|cluster
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;raw_scan_nonroot: start=%d&bslash;n&quot;
comma
id|start
)paren
suffix:semicolon
macro_line|#endif
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
id|raw_scan_sector
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
comma
id|res_bh
comma
id|res_de
comma
id|scantype
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
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;FAT error&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;next start: %d&bslash;n&quot;
comma
id|start
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; * raw_scan performs raw_scan_sector on any sector.&n; *&n; * NOTE: raw_scan must not be used on a directory that is is the process of&n; *       being created.&n; */
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
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
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
r_char
id|scantype
)paren
(brace
r_if
c_cond
(paren
id|start
)paren
r_return
id|raw_scan_nonroot
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
comma
id|res_bh
comma
id|res_de
comma
id|scantype
)paren
suffix:semicolon
r_else
r_return
id|raw_scan_root
(paren
id|sb
comma
id|name
comma
id|number
comma
id|ino
comma
id|res_bh
comma
id|res_de
comma
id|scantype
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fat_parent_ino returns the inode number of the parent directory of dir.&n; * File creation has to be deferred while fat_parent_ino is running to&n; * prevent renames.&n; */
DECL|function|fat_parent_ino
r_int
id|fat_parent_ino
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
r_static
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
r_int
id|error
comma
id|curr
comma
id|prev
comma
id|nr
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
id|fat_lock_creation
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent renames */
r_if
c_cond
(paren
(paren
id|curr
op_assign
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
id|MSDOS_DOTDOT
comma
op_amp
id|zero
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|SCAN_ANY
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
id|fat_unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|curr
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|curr
)paren
id|nr
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
id|curr
comma
id|MSDOS_DOTDOT
comma
op_amp
id|zero
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|SCAN_ANY
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
id|fat_unlock_creation
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
op_amp
id|curr
comma
op_amp
id|nr
comma
l_int|NULL
comma
l_int|NULL
comma
id|SCAN_ANY
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
id|fat_unlock_creation
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
id|fat_unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * fat_subdirs counts the number of sub-directories of dir. It can be run&n; * on directories being created.&n; */
DECL|function|fat_subdirs
r_int
id|fat_subdirs
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
(paren
r_void
)paren
id|raw_scan_root
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|NULL
comma
op_amp
id|count
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|SCAN_ANY
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* in mkdir */
r_else
(paren
r_void
)paren
id|raw_scan_nonroot
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
l_int|NULL
comma
op_amp
id|count
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|SCAN_ANY
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Scans a directory for a given file (name points to its formatted name) or&n; * for an empty directory slot (name is NULL). Returns an error code or zero.&n; */
DECL|function|fat_scan
r_int
id|fat_scan
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
comma
r_char
id|scantype
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
(paren
id|name
)paren
ques
c_cond
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
id|name
comma
l_int|NULL
comma
id|ino
comma
id|res_bh
comma
id|res_de
comma
id|scantype
)paren
suffix:colon
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
l_int|NULL
comma
l_int|NULL
comma
id|ino
comma
id|res_bh
comma
id|res_de
comma
id|scantype
)paren
suffix:semicolon
r_return
id|res
OL
l_int|0
ques
c_cond
id|res
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
