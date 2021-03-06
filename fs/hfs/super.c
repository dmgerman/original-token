multiline_comment|/*&n; * linux/fs/hfs/super.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file contains hfs_read_super(), some of the super_ops and&n; * init_module() and cleanup_module().&t;The remaining super_ops are in&n; * inode.c since they deal with inodes.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; * The code in this file initializes some structures which contain&n; * pointers by calling memset(&amp;foo, 0, sizeof(foo)).&n; * This produces the desired behavior only due to the non-ANSI&n; * assumption that the machine representation of NULL is all zeros.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_MAC_PARTITION */
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*================ Forward declarations ================*/
r_static
r_void
id|hfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|hfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|hfs_statfs
c_func
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
r_static
r_void
id|hfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/*================ Global variables ================*/
DECL|variable|hfs_super_operations
r_static
r_struct
id|super_operations
id|hfs_super_operations
op_assign
(brace
id|read_inode
suffix:colon
id|hfs_read_inode
comma
id|put_inode
suffix:colon
id|hfs_put_inode
comma
id|put_super
suffix:colon
id|hfs_put_super
comma
id|write_super
suffix:colon
id|hfs_write_super
comma
id|statfs
suffix:colon
id|hfs_statfs
comma
)brace
suffix:semicolon
multiline_comment|/*================ File-local variables ================*/
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|hfs_fs
comma
l_string|&quot;hfs&quot;
comma
id|hfs_read_super
)paren
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/* &n; * hfs_read_inode()&n; *&n; * this doesn&squot;t actually do much. hfs_iget actually fills in the &n; * necessary inode information.&n; */
DECL|function|hfs_read_inode
r_static
r_void
id|hfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_write_super()&n; *&n; * Description:&n; *   This function is called by the VFS only. When the filesystem&n; *   is mounted r/w it updates the MDB on disk.&n; * Input Variable(s):&n; *   struct super_block *sb: Pointer to the hfs superblock&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;sb&squot; points to a &quot;valid&quot; (struct super_block).&n; * Postconditions:&n; *   The MDB is marked &squot;unsuccessfully unmounted&squot; by clearing bit 8 of drAtrb&n; *   (hfs_put_super() must set this flag!). Some MDB fields are updated&n; *   and the MDB buffer is written to disk by calling hfs_mdb_commit().&n; */
DECL|function|hfs_write_super
r_static
r_void
id|hfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
suffix:semicolon
multiline_comment|/* is this a valid hfs superblock? */
r_if
c_cond
(paren
op_logical_neg
id|sb
op_logical_or
id|sb-&gt;s_magic
op_ne
id|HFS_SUPER_MAGIC
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
multiline_comment|/* sync everything to the buffers */
id|hfs_mdb_commit
c_func
(paren
id|mdb
comma
l_int|0
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_put_super()&n; *&n; * This is the put_super() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to release the resources&n; * associated with the superblock sb.&n; */
DECL|function|hfs_put_super
r_static
r_void
id|hfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|hfs_mdb_commit
c_func
(paren
id|mdb
comma
l_int|0
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* release the MDB&squot;s resources */
id|hfs_mdb_put
c_func
(paren
id|mdb
comma
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
multiline_comment|/* restore default blocksize for the device */
id|set_blocksize
c_func
(paren
id|sb-&gt;s_dev
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_statfs()&n; *&n; * This is the statfs() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to return various data about the&n; * filesystem.&n; *&n; * changed f_files/f_ffree to reflect the fs_ablock/free_ablocks.&n; */
DECL|function|hfs_statfs
r_static
r_int
id|hfs_statfs
c_func
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
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|HFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|HFS_SECTOR_SIZE
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|mdb-&gt;alloc_blksz
op_star
id|mdb-&gt;fs_ablocks
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|mdb-&gt;alloc_blksz
op_star
id|mdb-&gt;free_ablocks
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|mdb-&gt;fs_ablocks
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|mdb-&gt;free_ablocks
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|HFS_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * parse_options()&n; * &n; * adapted from linux/fs/msdos/inode.c written 1992,93 by Werner Almesberger&n; * This function is called by hfs_read_super() to parse the mount options.&n; */
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_struct
id|hfs_sb_info
op_star
id|hsb
comma
r_int
op_star
id|part
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
r_char
id|names
comma
id|fork
suffix:semicolon
multiline_comment|/* initialize the sb with defaults */
id|memset
c_func
(paren
id|hsb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|hsb
)paren
)paren
suffix:semicolon
id|hsb-&gt;magic
op_assign
id|HFS_SB_MAGIC
suffix:semicolon
id|hsb-&gt;s_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|hsb-&gt;s_gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|hsb-&gt;s_umask
op_assign
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|hsb-&gt;s_type
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_creator
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_lowercase
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_quiet
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_afpd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default version. 0 just selects the defaults */
id|hsb-&gt;s_version
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_conv
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|names
op_assign
l_char|&squot;?&squot;
suffix:semicolon
id|fork
op_assign
l_char|&squot;?&squot;
suffix:semicolon
op_star
id|part
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
r_for
c_loop
(paren
id|this_char
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_char
suffix:semicolon
id|this_char
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Numeric-valued options */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;version&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_version
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_umask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;part&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|part
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* String-valued options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;type&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|value
)paren
op_ne
l_int|4
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_type
op_assign
id|hfs_get_nl
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;creator&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|value
)paren
op_ne
l_int|4
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_creator
op_assign
id|hfs_get_nl
c_func
(paren
id|value
)paren
suffix:semicolon
multiline_comment|/* Boolean-valued options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;quiet&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_quiet
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;afpd&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_afpd
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Multiple choice options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;names&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|value
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;ntal78c&quot;
comma
op_star
id|value
)paren
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;netatalk&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;trivial&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;alpha&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;latin&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;7bit&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;8bit&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;cap&quot;
)paren
)paren
(brace
id|names
op_assign
op_star
id|value
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;fork&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|value
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;nsdc&quot;
comma
op_star
id|value
)paren
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;netatalk&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;single&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;double&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;cap&quot;
)paren
)paren
(brace
id|fork
op_assign
op_star
id|value
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;case&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|value
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;la&quot;
comma
op_star
id|value
)paren
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;lower&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;asis&quot;
)paren
)paren
(brace
id|hsb-&gt;s_lowercase
op_assign
(paren
op_star
id|value
op_eq
l_char|&squot;l&squot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;conv&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|value
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;bta&quot;
comma
op_star
id|value
)paren
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;binary&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;text&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;auto&quot;
)paren
)paren
(brace
id|hsb-&gt;s_conv
op_assign
op_star
id|value
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|done
suffix:colon
multiline_comment|/* Parse the &quot;fork&quot; and &quot;names&quot; options */
r_if
c_cond
(paren
id|fork
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|fork
op_assign
id|hsb-&gt;s_afpd
ques
c_cond
l_char|&squot;n&squot;
suffix:colon
l_char|&squot;c&squot;
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|fork
)paren
(brace
r_default
suffix:colon
r_case
l_char|&squot;c&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_cap_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_cap_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_cap_reserved2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: AppleSingle not yet implemented.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* break; */
r_case
l_char|&squot;d&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_dbl_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_dbl_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_dbl_reserved2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_nat_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_nat_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_nat_reserved2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|names
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|names
op_assign
id|fork
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|names
)paren
(brace
r_default
suffix:colon
r_case
l_char|&squot;n&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_colon2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2nat
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_colon2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2cap
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_triv2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2triv
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;7&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2seven
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;8&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2eight
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_latin2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2latin
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
multiline_comment|/* &squot;s&squot; and &squot;d&squot; are unadvertised aliases for &squot;alpha&squot;, */
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* since &squot;alpha&squot; is the default if fork=s or fork=d. */
r_case
l_char|&squot;d&squot;
suffix:colon
multiline_comment|/* (It is also helpful for poor typists!)           */
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2alpha
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_read_super()&n; *&n; * This is the function that is responsible for mounting an HFS&n; * filesystem.&t;It performs all the tasks necessary to get enough data&n; * from the disk to read the root inode.  This includes parsing the&n; * mount options, dealing with Macintosh partitions, reading the&n; * superblock and the allocation bitmap blocks, calling&n; * hfs_btree_init() to get the necessary data about the extents and&n; * catalog B-trees and, finally, reading the root inode into memory.&n; */
DECL|function|hfs_read_super
r_struct
id|super_block
op_star
id|hfs_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
suffix:semicolon
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
id|hfs_s32
id|part_size
comma
id|part_start
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_int
id|part
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
(paren
r_char
op_star
)paren
id|data
comma
id|HFS_SB
c_func
(paren
id|s
)paren
comma
op_amp
id|part
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to parse mount options.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail3
suffix:semicolon
)brace
multiline_comment|/* set the device driver to 512-byte blocks */
id|set_blocksize
c_func
(paren
id|dev
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAC_PARTITION
multiline_comment|/* check to see if we&squot;re in a partition */
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* erk. try parsing the partition table ourselves */
r_if
c_cond
(paren
op_logical_neg
id|mdb
)paren
(brace
r_if
c_cond
(paren
id|hfs_part_find
c_func
(paren
id|s
comma
id|part
comma
id|silent
comma
op_amp
id|part_size
comma
op_amp
id|part_start
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
id|part_start
)paren
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|hfs_part_find
c_func
(paren
id|s
comma
id|part
comma
id|silent
comma
op_amp
id|part_size
comma
op_amp
id|part_start
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
id|part_start
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|mdb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;VFS: Can&squot;t find a HFS filesystem on dev %s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
r_goto
id|bail2
suffix:semicolon
)brace
id|HFS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|s_mdb
op_assign
id|mdb
suffix:semicolon
r_if
c_cond
(paren
id|HFS_ITYPE
c_func
(paren
id|mdb-&gt;next_id
)paren
op_ne
l_int|0
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: too many files.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail1
suffix:semicolon
)brace
id|s-&gt;s_magic
op_assign
id|HFS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|HFS_SECTOR_SIZE
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|hfs_super_operations
suffix:semicolon
multiline_comment|/* try to get the root inode */
id|hfs_cat_build_key
c_func
(paren
id|htonl
c_func
(paren
id|HFS_POR_CNID
)paren
comma
(paren
r_struct
id|hfs_name
op_star
)paren
(paren
id|mdb-&gt;vname
)paren
comma
op_amp
id|key
)paren
suffix:semicolon
id|root_inode
op_assign
id|hfs_iget
c_func
(paren
id|hfs_cat_get
c_func
(paren
id|mdb
comma
op_amp
id|key
)paren
comma
id|HFS_ITYPE_NORM
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|bail_no_root
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
r_goto
id|bail_no_root
suffix:semicolon
multiline_comment|/* fix up pointers. */
id|HFS_I
c_func
(paren
id|root_inode
)paren
op_member_access_from_pointer
id|entry-&gt;sys_entry
(braket
id|HFS_ITYPE_TO_INT
c_func
(paren
id|HFS_ITYPE_NORM
)paren
)braket
op_assign
id|s-&gt;s_root
suffix:semicolon
id|s-&gt;s_root-&gt;d_op
op_assign
op_amp
id|hfs_dentry_operations
suffix:semicolon
multiline_comment|/* everything&squot;s okay */
r_return
id|s
suffix:semicolon
id|bail_no_root
suffix:colon
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: get root inode failed.&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|bail1
suffix:colon
id|hfs_mdb_put
c_func
(paren
id|mdb
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
id|bail2
suffix:colon
id|set_blocksize
c_func
(paren
id|dev
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|bail3
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|init_hfs_fs
r_static
r_int
id|__init
id|init_hfs_fs
c_func
(paren
r_void
)paren
(brace
id|hfs_cat_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|register_filesystem
c_func
(paren
op_amp
id|hfs_fs
)paren
suffix:semicolon
)brace
DECL|function|exit_hfs_fs
r_static
r_void
id|__exit
id|exit_hfs_fs
c_func
(paren
r_void
)paren
(brace
id|hfs_cat_free
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|hfs_fs
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_hfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_hfs_fs
)paren
macro_line|#if defined(DEBUG_ALL) || defined(DEBUG_MEM)
r_int
r_int
id|hfs_alloc
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
eof
