multiline_comment|/*&n; *  linux/fs/ufs/ufs_namei.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Clean swab support by Francois-Rene Rideau &lt;rideau@ens.fr&gt; 19970406&n; * Ported to 2.1.62 by Francois-Rene Rideau &lt;rideau@issy.cnet.fr&gt; 19971109&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;ufs_swab.h&quot;
multiline_comment|/*&n; * NOTE! unlike strncmp, ext2_match returns 1 for success, 0 for failure.&n; * stolen from ext2fs&n; */
DECL|function|ufs_match
r_static
r_int
id|ufs_match
(paren
r_int
id|len
comma
r_const
r_char
op_star
r_const
id|name
comma
r_struct
id|ufs_direct
op_star
id|d
comma
id|__u32
id|bytesex
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|d
op_logical_or
id|len
OG
id|UFS_MAXNAMLEN
)paren
multiline_comment|/* XXX - name space */
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;&quot; means &quot;.&quot; ---&gt; so paths like &quot;/usr/lib//libc.a&quot; work&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_and
(paren
id|SWAB16
c_func
(paren
id|d-&gt;d_namlen
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
id|d-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|d-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|SWAB16
c_func
(paren
id|d-&gt;d_namlen
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|d-&gt;d_name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|ufs_lookup
r_int
id|ufs_lookup
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
multiline_comment|/* XXX - this is all fucked up! */
multiline_comment|/* XXX - and it&squot;s been broken since linux has this new dentry interface:&n;   * allows reading of files, but screws the whole dcache, even outside&n;   * of the ufs partition, so that umount&squot;ing won&squot;t suffice to fix it --&n;   * reboot needed&n;   */
r_int
r_int
r_int
id|lfragno
comma
id|fragno
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_direct
op_star
id|d
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|__u32
id|bytesex
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* XXX - isn&squot;t that already done by the upper layer? */
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|bytesex
op_assign
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_BYTESEX
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
id|printk
c_func
(paren
l_string|&quot;Passed name: %s&bslash;nPassed length: %d&bslash;n&quot;
comma
id|name
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* debugging hacks:&n;&t; * Touching /xyzzy in a filesystem toggles debugging messages.&n;&t; */
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|5
)paren
op_logical_and
op_logical_neg
(paren
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;xyzzy&quot;
comma
id|len
)paren
)paren
op_logical_and
(paren
id|dir-&gt;i_ino
op_eq
id|UFS_ROOTINO
)paren
)paren
(brace
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_xor_assign
id|UFS_DEBUG
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;UFS debugging %s&bslash;n&quot;
comma
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
multiline_comment|/*return(-ENOENT);*/
)brace
multiline_comment|/*&n;&t; * Touching /xyzzy.i in a filesystem toggles debugging for ufs_inode.c.&n;&t; */
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|7
)paren
op_logical_and
op_logical_neg
(paren
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;xyzzy.i&quot;
comma
id|len
)paren
)paren
op_logical_and
(paren
id|dir-&gt;i_ino
op_eq
id|UFS_ROOTINO
)paren
)paren
(brace
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_xor_assign
id|UFS_DEBUG_INODE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;UFS inode debugging %s&bslash;n&quot;
comma
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG_INODE
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
multiline_comment|/*return(-ENOENT);*/
)brace
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|7
)paren
op_logical_and
op_logical_neg
(paren
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;xyzzy.n&quot;
comma
id|len
)paren
)paren
op_logical_and
(paren
id|dir-&gt;i_ino
op_eq
id|UFS_ROOTINO
)paren
)paren
(brace
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_xor_assign
id|UFS_DEBUG_NAMEI
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;UFS namei debugging %s&bslash;n&quot;
comma
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG_NAMEI
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
multiline_comment|/*return(-ENOENT);*/
)brace
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|7
)paren
op_logical_and
op_logical_neg
(paren
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;xyzzy.l&quot;
comma
id|len
)paren
)paren
op_logical_and
(paren
id|dir-&gt;i_ino
op_eq
id|UFS_ROOTINO
)paren
)paren
(brace
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_xor_assign
id|UFS_DEBUG_LINKS
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;UFS symlink debugging %s&bslash;n&quot;
comma
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG_LINKS
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
multiline_comment|/*return(-ENOENT);*/
)brace
multiline_comment|/* Now for the real thing */
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
(paren
id|UFS_DEBUG
op_or
id|UFS_DEBUG_NAMEI
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_lookup: called for ino %lu  name %s&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX - do I want i_blocks in 512-blocks or 1024-blocks? */
r_for
c_loop
(paren
id|lfragno
op_assign
l_int|0
suffix:semicolon
id|lfragno
OL
(paren
id|dir-&gt;i_blocks
)paren
op_rshift
l_int|1
suffix:semicolon
id|lfragno
op_increment
)paren
(brace
id|fragno
op_assign
id|ufs_bmap
c_func
(paren
id|dir
comma
id|lfragno
)paren
suffix:semicolon
multiline_comment|/* XXX - ufs_bmap() call needs error checking */
multiline_comment|/* XXX - s_blocksize is actually the UFS frag size */
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_lookup: ino %lu lfragno %lu  fragno %lu&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
id|lfragno
comma
id|fragno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fragno
op_eq
l_int|0
)paren
(brace
multiline_comment|/* XXX - bug bug bug */
r_goto
id|not_found
suffix:semicolon
multiline_comment|/*return(-ENOENT);*/
)brace
id|bh
op_assign
id|bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|fragno
comma
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_lookup: bread failed: &quot;
l_string|&quot;ino %lu, lfragno %lu&quot;
comma
id|dir-&gt;i_ino
comma
id|lfragno
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|d
op_assign
(paren
r_struct
id|ufs_direct
op_star
)paren
(paren
id|bh-&gt;b_data
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_char
op_star
)paren
id|d
op_minus
id|bh-&gt;b_data
op_plus
id|SWAB16
c_func
(paren
id|d-&gt;d_reclen
)paren
)paren
op_le
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
multiline_comment|/* XXX - skip block if d_reclen or d_namlen is 0 */
r_if
c_cond
(paren
(paren
id|d-&gt;d_reclen
op_eq
l_int|0
)paren
op_logical_or
(paren
id|d-&gt;d_namlen
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* no need to SWAB16(): test against 0 */
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_lookup: skipped space in directory, ino %lu&bslash;n&quot;
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lfragno 0x%lx  &quot;
l_string|&quot;direct d 0x%x  &quot;
l_string|&quot;d_ino %u  &quot;
l_string|&quot;d_reclen %u  &quot;
l_string|&quot;d_namlen %u  d_name `%s&squot;&bslash;n&quot;
comma
id|lfragno
comma
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|d
)paren
comma
id|SWAB32
c_func
(paren
id|d-&gt;d_ino
)paren
comma
id|SWAB16
c_func
(paren
id|d-&gt;d_reclen
)paren
comma
id|SWAB16
c_func
(paren
id|d-&gt;d_namlen
)paren
comma
id|d-&gt;d_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|SWAB16
c_func
(paren
id|d-&gt;d_namlen
)paren
op_eq
id|len
)paren
op_logical_and
multiline_comment|/* XXX - don&squot;t use strncmp() - see ext2fs */
(paren
id|ufs_match
c_func
(paren
id|len
comma
id|name
comma
id|d
comma
id|bytesex
)paren
)paren
)paren
(brace
multiline_comment|/* We have a match */
multiline_comment|/* XXX - I only superficially understand how things work,&n; * so use at your own risk... -- Fare&squot;&n; */
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|SWAB32
c_func
(paren
id|d-&gt;d_ino
)paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* XXX - bounds checking */
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_lookup: &quot;
l_string|&quot;wanted (%s,%d) got (%s,%d)&bslash;n&quot;
comma
id|name
comma
id|len
comma
id|d-&gt;d_name
comma
id|SWAB16
c_func
(paren
id|d-&gt;d_namlen
)paren
)paren
suffix:semicolon
)brace
)brace
id|d
op_assign
(paren
r_struct
id|ufs_direct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|d
op_plus
id|SWAB16
c_func
(paren
id|d-&gt;d_reclen
)paren
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|not_found
suffix:colon
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
