multiline_comment|/*&n; * linux/fs/nfsd/nfsfh.c&n; *&n; * NFS server file handle treatment.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; * Portions Copyright (C) 1999 G. Allen Morris III &lt;gam3@acm.org&gt;&n; * Extensive cleanup by Neil Brown &lt;neilb@cse.unsw.edu.au&gt; Southern-Spring 1999&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_FH
DECL|macro|NFSD_PARANOIA
mdefine_line|#define NFSD_PARANOIA 1
multiline_comment|/* #define NFSD_DEBUG_VERBOSE 1 */
DECL|variable|nfsd_nr_verified
r_static
r_int
id|nfsd_nr_verified
op_assign
l_int|0
suffix:semicolon
DECL|variable|nfsd_nr_put
r_static
r_int
id|nfsd_nr_put
op_assign
l_int|0
suffix:semicolon
DECL|struct|nfsd_getdents_callback
r_struct
id|nfsd_getdents_callback
(brace
DECL|member|name
r_struct
id|qstr
op_star
id|name
suffix:semicolon
multiline_comment|/* name that was found. name-&gt;name already points to a buffer */
DECL|member|ino
r_int
r_int
id|ino
suffix:semicolon
multiline_comment|/* the inum we are looking for */
DECL|member|found
r_int
id|found
suffix:semicolon
multiline_comment|/* inode matched? */
DECL|member|sequence
r_int
id|sequence
suffix:semicolon
multiline_comment|/* sequence counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * A rather strange filldir function to capture&n; * the name matching the specified inode number.&n; */
DECL|function|filldir_one
r_static
r_int
id|filldir_one
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
id|off_t
id|pos
comma
id|ino_t
id|ino
)paren
(brace
r_struct
id|nfsd_getdents_callback
op_star
id|buf
op_assign
id|__buf
suffix:semicolon
r_struct
id|qstr
op_star
id|qs
op_assign
id|buf-&gt;name
suffix:semicolon
r_char
op_star
id|nbuf
op_assign
(paren
r_char
op_star
)paren
id|qs-&gt;name
suffix:semicolon
multiline_comment|/* cast is to get rid of &quot;const&quot; */
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;sequence
op_increment
suffix:semicolon
macro_line|#ifdef NFSD_DEBUG_VERBOSE
id|dprintk
c_func
(paren
l_string|&quot;filldir_one: seq=%d, ino=%ld, name=%s&bslash;n&quot;
comma
id|buf-&gt;sequence
comma
id|ino
comma
id|name
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|buf-&gt;ino
op_eq
id|ino
)paren
(brace
id|qs-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|nbuf
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|nbuf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|buf-&gt;found
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a directory and return the name of the specified entry.&n; */
DECL|function|get_ino_name
r_static
r_int
id|get_ino_name
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|name
comma
r_int
r_int
id|ino
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|file
id|file
suffix:semicolon
r_struct
id|nfsd_getdents_callback
id|buffer
suffix:semicolon
id|error
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
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
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;i_op
op_logical_or
op_logical_neg
id|dir-&gt;i_op-&gt;default_file_ops
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Open the directory ...&n;&t; */
id|error
op_assign
id|init_private_file
c_func
(paren
op_amp
id|file
comma
id|dentry
comma
id|FMODE_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file.f_op-&gt;readdir
)paren
r_goto
id|out_close
suffix:semicolon
id|buffer.name
op_assign
id|name
suffix:semicolon
id|buffer.ino
op_assign
id|ino
suffix:semicolon
id|buffer.found
op_assign
l_int|0
suffix:semicolon
id|buffer.sequence
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|old_seq
op_assign
id|buffer.sequence
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
id|error
op_assign
id|file.f_op
op_member_access_from_pointer
id|readdir
c_func
(paren
op_amp
id|file
comma
op_amp
id|buffer
comma
id|filldir_one
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_break
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer.found
)paren
r_break
suffix:semicolon
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|old_seq
op_eq
id|buffer.sequence
)paren
r_break
suffix:semicolon
)brace
id|out_close
suffix:colon
r_if
c_cond
(paren
id|file.f_op-&gt;release
)paren
id|file.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|dir
comma
op_amp
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* this should be provided by each filesystem in an nfsd_operations interface as&n; * iget isn&squot;t really the right interface&n; */
DECL|function|nfsd_iget
r_static
r_inline
r_struct
id|dentry
op_star
id|nfsd_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|ino
comma
id|__u32
id|generation
)paren
(brace
multiline_comment|/* iget isn&squot;t really right if the inode is currently unallocated!!&n;&t; * This should really all be done inside each filesystem&n;&t; *&n;&t; * ext2fs&squot; read_inode has been strengthed to return a bad_inode if the inode&n;&t; *   had been deleted.&n;&t; *&n;&t; * Currently we don&squot;t know the generation for parent directory, so a generation&n;&t; * of 0 means &quot;accept any&quot;&n;&t; */
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|list_head
op_star
id|lp
suffix:semicolon
r_struct
id|dentry
op_star
id|result
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|generation
op_logical_and
id|inode-&gt;i_generation
op_ne
id|generation
)paren
)paren
(brace
multiline_comment|/* we didn&squot;t find the right inode.. */
id|dprintk
c_func
(paren
l_string|&quot;fh_verify: Inode %lu, Bad count: %d %d or version  %u %u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_nlink
comma
id|inode-&gt;i_count
comma
id|inode-&gt;i_generation
comma
id|generation
)paren
suffix:semicolon
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
multiline_comment|/* now to find a dentry.&n;&t; * If possible, get a well-connected one&n;&t; */
r_for
c_loop
(paren
id|lp
op_assign
id|inode-&gt;i_dentry.next
suffix:semicolon
id|lp
op_ne
op_amp
id|inode-&gt;i_dentry
suffix:semicolon
id|lp
op_assign
id|lp-&gt;next
)paren
(brace
id|result
op_assign
id|list_entry
c_func
(paren
id|lp
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|result
)paren
op_logical_or
id|inode-&gt;i_sb-&gt;s_root
op_eq
id|result
)paren
(brace
id|dget
c_func
(paren
id|result
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
)brace
id|result
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|NULL
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|d_rehash
c_func
(paren
id|result
)paren
suffix:semicolon
multiline_comment|/* so a dput won&squot;t loose it */
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* this routine links an IS_ROOT dentry into the dcache tree.  It gains &quot;parent&quot;&n; * as a parent and &quot;name&quot; as a name&n; * It should possibly go in dcache.c&n; */
DECL|function|d_splice
r_int
id|d_splice
c_func
(paren
r_struct
id|dentry
op_star
id|target
comma
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|dentry
op_star
id|tdentry
suffix:semicolon
macro_line|#ifdef NFSD_PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|target
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;nfsd: d_splice with no-root target: %s/%s&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|name-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|name-&gt;hash
op_assign
id|full_name_hash
c_func
(paren
id|name-&gt;name
comma
id|name-&gt;len
)paren
suffix:semicolon
id|tdentry
op_assign
id|d_alloc
c_func
(paren
id|parent
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tdentry
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|d_move
c_func
(paren
id|target
comma
id|tdentry
)paren
suffix:semicolon
multiline_comment|/* tdentry will have been made a &quot;child&quot; of target (the parent of target)&n;&t; * make it an IS_ROOT instead&n;&t; */
id|list_del
c_func
(paren
op_amp
id|tdentry-&gt;d_child
)paren
suffix:semicolon
id|tdentry-&gt;d_parent
op_assign
id|tdentry
suffix:semicolon
id|d_rehash
c_func
(paren
id|target
)paren
suffix:semicolon
id|dput
c_func
(paren
id|tdentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this routine finds the dentry of the parent of a given directory&n; * it should be in the filesystem accessed by nfsd_operations&n; * it assumes lookup(&quot;..&quot;) works.&n; */
DECL|function|nfsd_findparent
r_struct
id|dentry
op_star
id|nfsd_findparent
c_func
(paren
r_struct
id|dentry
op_star
id|child
)paren
(brace
r_struct
id|dentry
op_star
id|tdentry
comma
op_star
id|pdentry
suffix:semicolon
id|tdentry
op_assign
id|d_alloc
c_func
(paren
id|child
comma
op_amp
(paren
r_const
r_struct
id|qstr
)paren
(brace
l_string|&quot;..&quot;
comma
l_int|2
comma
l_int|0
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tdentry
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
multiline_comment|/* I&squot;m going to assume that if the returned dentry is different, then&n;&t; * it is well connected.  But nobody returns different dentrys do they?&n;&t; */
id|pdentry
op_assign
id|child-&gt;d_inode-&gt;i_op
op_member_access_from_pointer
id|lookup
c_func
(paren
id|child-&gt;d_inode
comma
id|tdentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdentry
)paren
(brace
multiline_comment|/* I don&squot;t want to return a &quot;..&quot; dentry.&n;&t;&t; * I would prefer to return an unconnected &quot;IS_ROOT&quot; dentry,&n;&t;&t; * though a properly connected dentry is even better&n;&t;&t; */
multiline_comment|/* if first or last of alias list is not tdentry, use that&n;&t;&t; * else make a root dentry&n;&t;&t; */
r_struct
id|list_head
op_star
id|aliases
op_assign
op_amp
id|tdentry-&gt;d_inode-&gt;i_dentry
suffix:semicolon
r_if
c_cond
(paren
id|aliases-&gt;next
op_ne
id|aliases
)paren
(brace
id|pdentry
op_assign
id|list_entry
c_func
(paren
id|aliases-&gt;next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdentry
op_eq
id|tdentry
)paren
id|pdentry
op_assign
id|list_entry
c_func
(paren
id|aliases-&gt;prev
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdentry
op_eq
id|tdentry
)paren
id|pdentry
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pdentry
)paren
id|dget
c_func
(paren
id|pdentry
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdentry
op_eq
l_int|NULL
)paren
(brace
id|pdentry
op_assign
id|d_alloc_root
c_func
(paren
id|igrab
c_func
(paren
id|tdentry-&gt;d_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdentry
)paren
id|d_rehash
c_func
(paren
id|pdentry
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdentry
op_eq
l_int|NULL
)paren
id|pdentry
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|tdentry
)paren
suffix:semicolon
multiline_comment|/* it was never rehashed, it will be discarded */
r_return
id|pdentry
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the basic lookup mechanism for turning an NFS file handle&n; * into a dentry.&n; * We use nfsd_iget and if that doesn&squot;t return a suitably connected dentry,&n; * we try to find the parent, and the parent of that and so-on until a&n; * connection if made.&n; */
r_static
r_struct
id|dentry
op_star
DECL|function|find_fh_dentry
id|find_fh_dentry
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|knfs_fh
op_star
id|fh
comma
r_int
id|needpath
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
comma
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|qstr
id|qs
suffix:semicolon
r_char
id|namebuf
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|u32
id|err
suffix:semicolon
id|qs.name
op_assign
id|namebuf
suffix:semicolon
multiline_comment|/*&n;&t; * Attempt to find the inode.&n;&t; */
id|result
op_assign
id|nfsd_iget
c_func
(paren
id|sb
comma
id|fh-&gt;fh_ino
comma
id|fh-&gt;fh_generation
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|result
)paren
)paren
r_goto
id|err_out
suffix:semicolon
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;find_fh_dentry: No inode found.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|result
)paren
op_logical_or
id|result-&gt;d_inode-&gt;i_sb-&gt;s_root
op_eq
id|result
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* result is now a &quot;root&quot; dentry, which may be adequate as it stands, or else&n;&t; * will get spliced into the dcache tree */
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|result-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|needpath
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* It&squot;s a directory, or we are required to confirm the file&squot;s&n;&t; * location in the tree.&n;&t; */
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|result-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|fh-&gt;fh_dirino
op_eq
l_int|0
)paren
r_goto
id|err_result
suffix:semicolon
multiline_comment|/* don&squot;t know how to find parent */
r_else
(brace
multiline_comment|/* need to iget fh-&gt;fh_dirino and make sure this inode is in that directory */
id|dentry
op_assign
id|nfsd_iget
c_func
(paren
id|sb
comma
id|fh-&gt;fh_dirino
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|err_result
suffix:semicolon
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
r_goto
id|err_dentry
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|dentry
)paren
op_logical_or
id|dentry-&gt;d_inode-&gt;i_sb-&gt;s_root
op_eq
id|dentry
)paren
id|found
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|get_ino_name
c_func
(paren
id|dentry
comma
op_amp
id|qs
comma
id|result-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|err_dentry
suffix:semicolon
multiline_comment|/* OK, we have the name in parent of inode,  lets fill in the dentry */
id|err
op_assign
id|d_splice
c_func
(paren
id|result
comma
id|dentry
comma
op_amp
id|qs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|err_dentry
suffix:semicolon
)brace
)brace
r_else
id|dentry
op_assign
id|dget
c_func
(paren
id|result
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|found
)paren
(brace
multiline_comment|/* LOOP INVARIANT */
multiline_comment|/* haven&squot;t found a place in the tree yet, but we do have a path&n;&t;&t; * from dentry down to result, and dentry is a directory.&n;&t;&t; * Have a hold on dentry and result */
r_struct
id|dentry
op_star
id|pdentry
suffix:semicolon
r_struct
id|inode
op_star
id|parent
suffix:semicolon
id|pdentry
op_assign
id|nfsd_findparent
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|pdentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|pdentry
)paren
)paren
r_goto
id|err_dentry
suffix:semicolon
id|parent
op_assign
id|pdentry-&gt;d_inode
suffix:semicolon
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
id|dput
c_func
(paren
id|pdentry
)paren
suffix:semicolon
r_goto
id|err_dentry
suffix:semicolon
)brace
multiline_comment|/* I&squot;m not sure that this is the best test for&n;&t;&t; *  &quot;is it not a floating dentry?&quot;&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|pdentry
)paren
op_logical_or
id|parent-&gt;i_sb-&gt;s_root
op_eq
id|pdentry
)paren
id|found
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|get_ino_name
c_func
(paren
id|pdentry
comma
op_amp
id|qs
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|dput
c_func
(paren
id|pdentry
)paren
suffix:semicolon
r_goto
id|err_dentry
suffix:semicolon
)brace
id|err
op_assign
id|d_splice
c_func
(paren
id|dentry
comma
id|pdentry
comma
op_amp
id|qs
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd_fh: found name %s for ino %ld&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dentry
op_assign
id|pdentry
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
id|err_dentry
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|err_result
suffix:colon
id|dput
c_func
(paren
id|result
)paren
suffix:semicolon
id|err_out
suffix:colon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ESTALE
)paren
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform sanity checks on the dentry in a client&squot;s file handle.&n; *&n; * Note that the file handle dentry may need to be freed even after&n; * an error return.&n; *&n; * This is only called at the start of an nfsproc call, so fhp points to&n; * a svc_fh which is all 0 except for the over-the-wire file handle.&n; */
id|u32
DECL|function|fh_verify
id|fh_verify
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|fhp
comma
r_int
id|type
comma
r_int
id|access
)paren
(brace
r_struct
id|knfs_fh
op_star
id|fh
op_assign
op_amp
id|fhp-&gt;fh_handle
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|u32
id|error
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_verify(exp %s/%u file (%s/%u dir %u)&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|fh-&gt;fh_xdev
)paren
comma
id|fh-&gt;fh_xino
comma
id|kdevname
c_func
(paren
id|fh-&gt;fh_dev
)paren
comma
id|fh-&gt;fh_ino
comma
id|fh-&gt;fh_dirino
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Security: Check that the fh is internally consistant (from &lt;gam3@acm.org&gt;)&n;&t; */
r_if
c_cond
(paren
id|fh-&gt;fh_dev
op_ne
id|fh-&gt;fh_xdev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fh_verify: Security: export on other device (%s, %s).&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|fh-&gt;fh_dev
)paren
comma
id|kdevname
c_func
(paren
id|fh-&gt;fh_xdev
)paren
)paren
suffix:semicolon
id|error
op_assign
id|nfserr_stale
suffix:semicolon
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Look up the export entry.&n;&t; */
id|error
op_assign
id|nfserr_stale
suffix:semicolon
id|exp
op_assign
id|exp_get
c_func
(paren
id|rqstp-&gt;rq_client
comma
id|u32_to_kdev_t
c_func
(paren
id|fh-&gt;fh_xdev
)paren
comma
id|u32_to_ino_t
c_func
(paren
id|fh-&gt;fh_xino
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
)paren
(brace
multiline_comment|/* export entry revoked */
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Check if the request originated from a secure port. */
id|error
op_assign
id|nfserr_perm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rqstp-&gt;rq_secure
op_logical_and
id|EX_SECURE
c_func
(paren
id|exp
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: request from insecure port (%08lx:%d)!&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|rqstp-&gt;rq_addr.sin_port
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Set user creds if we haven&squot;t done so already. */
id|nfsd_setuser
c_func
(paren
id|rqstp
comma
id|exp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Look up the dentry using the NFS file handle.&n;&t; */
id|dentry
op_assign
id|find_fh_dentry
c_func
(paren
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_sb
comma
id|fh
comma
op_logical_neg
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
id|error
op_assign
id|nfserrno
c_func
(paren
op_minus
id|PTR_ERR
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fhp-&gt;fh_dentry
op_assign
id|dentry
suffix:semicolon
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
id|fhp-&gt;fh_dverified
op_assign
l_int|1
suffix:semicolon
id|nfsd_nr_verified
op_increment
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* Type check. The correct error return for type mismatches&n;&t; * does not seem to be generally agreed upon. SunOS seems to&n;&t; * use EISDIR if file isn&squot;t S_IFREG; a comment in the NFSv3&n;&t; * spec says this is incorrect (implementation notes for the&n;&t; * write call).&n;&t; */
multiline_comment|/* When is type ever negative? */
r_if
c_cond
(paren
id|type
OG
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_ne
id|type
)paren
(brace
id|error
op_assign
(paren
id|type
op_eq
id|S_IFDIR
)paren
ques
c_cond
id|nfserr_notdir
suffix:colon
id|nfserr_isdir
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
op_minus
id|type
)paren
(brace
id|error
op_assign
(paren
id|type
op_eq
op_minus
id|S_IFDIR
)paren
ques
c_cond
id|nfserr_notdir
suffix:colon
id|nfserr_isdir
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Security: Check that the export is valid for dentry &lt;gam3@acm.org&gt;&n;&t; */
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
(brace
r_if
c_cond
(paren
id|exp-&gt;ex_dentry
op_ne
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
id|tdentry
op_assign
id|dentry
suffix:semicolon
r_do
(brace
id|tdentry
op_assign
id|tdentry-&gt;d_parent
suffix:semicolon
r_if
c_cond
(paren
id|exp-&gt;ex_dentry
op_eq
id|tdentry
)paren
r_break
suffix:semicolon
multiline_comment|/* executable only by root and we can&squot;t be root */
r_if
c_cond
(paren
id|current-&gt;fsuid
op_logical_and
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_ROOTSQUASH
)paren
op_logical_and
op_logical_neg
(paren
id|tdentry-&gt;d_inode-&gt;i_uid
op_logical_and
(paren
id|tdentry-&gt;d_inode-&gt;i_mode
op_amp
id|S_IXUSR
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|tdentry-&gt;d_inode-&gt;i_gid
op_logical_and
(paren
id|tdentry-&gt;d_inode-&gt;i_mode
op_amp
id|S_IXGRP
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|tdentry-&gt;d_inode-&gt;i_mode
op_amp
id|S_IXOTH
)paren
)paren
(brace
id|error
op_assign
id|nfserr_stale
suffix:semicolon
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;fh_verify: no root_squashed access.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|tdentry
op_ne
id|tdentry-&gt;d_parent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp-&gt;ex_dentry
op_ne
id|tdentry
)paren
(brace
id|error
op_assign
id|nfserr_stale
suffix:semicolon
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;nfsd Security: %s/%s bad export.&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Finally, check access permissions. */
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|nfsd_permission
c_func
(paren
id|exp
comma
id|dentry
comma
id|access
)paren
suffix:semicolon
)brace
macro_line|#ifdef NFSD_PARANOIA
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fh_verify: %s/%s permission failure, acc=%x, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|access
comma
(paren
id|error
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Compose a file handle for an NFS reply.&n; *&n; * Note that when first composed, the dentry may not yet have&n; * an inode.  In this case a call to fh_update should be made&n; * before the fh goes out on the wire ...&n; */
r_void
DECL|function|fh_compose
id|fh_compose
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
comma
r_struct
id|svc_export
op_star
id|exp
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
op_assign
id|dentry-&gt;d_parent
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_compose(exp %x/%ld %s/%s, ino=%ld)&bslash;n&quot;
comma
id|exp-&gt;ex_dev
comma
id|exp-&gt;ex_ino
comma
id|parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
id|inode
ques
c_cond
id|inode-&gt;i_ino
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. We shouldn&squot;t need to init the fh -- the call to fh_compose&n;&t; * may not be done on error paths, but the cleanup must call fh_put.&n;&t; * Fix this soon!&n;&t; */
r_if
c_cond
(paren
id|fhp-&gt;fh_dverified
op_logical_or
id|fhp-&gt;fh_locked
op_logical_or
id|fhp-&gt;fh_dentry
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_compose: fh %s/%s not initialized!&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
id|fh_init
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dirino
op_assign
id|ino_t_to_u32
c_func
(paren
id|parent-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dev
op_assign
id|kdev_t_to_u32
c_func
(paren
id|parent-&gt;d_inode-&gt;i_dev
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_xdev
op_assign
id|kdev_t_to_u32
c_func
(paren
id|exp-&gt;ex_dev
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_xino
op_assign
id|ino_t_to_u32
c_func
(paren
id|exp-&gt;ex_ino
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dcookie
op_assign
(paren
r_struct
id|dentry
op_star
)paren
l_int|0xfeebbaca
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|fhp-&gt;fh_handle.fh_ino
op_assign
id|ino_t_to_u32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_generation
op_assign
id|inode-&gt;i_generation
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
id|fhp-&gt;fh_handle.fh_dirino
op_assign
l_int|0
suffix:semicolon
)brace
id|fhp-&gt;fh_dentry
op_assign
id|dentry
suffix:semicolon
multiline_comment|/* our internal copy */
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
multiline_comment|/* We stuck it there, we know it&squot;s good. */
id|fhp-&gt;fh_dverified
op_assign
l_int|1
suffix:semicolon
id|nfsd_nr_verified
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * Update file handle information after changing a dentry.&n; * This is only called by nfsd_create&n; */
r_void
DECL|function|fh_update
id|fh_update
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_dverified
)paren
r_goto
id|out_bad
suffix:semicolon
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_negative
suffix:semicolon
id|fhp-&gt;fh_handle.fh_ino
op_assign
id|ino_t_to_u32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_generation
op_assign
id|inode-&gt;i_generation
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
(paren
id|fhp-&gt;fh_export-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
id|fhp-&gt;fh_handle.fh_dirino
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
suffix:semicolon
id|out_bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_update: fh not verified!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_negative
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_update: %s/%s still negative!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Release a file handle.&n; */
r_void
DECL|function|fh_put
id|fh_put
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_dverified
)paren
(brace
id|fh_unlock
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|fhp-&gt;fh_dverified
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_count
)paren
r_goto
id|out_bad
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|nfsd_nr_put
op_increment
suffix:semicolon
)brace
r_return
suffix:semicolon
id|out_bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_put: %s/%s has d_count 0!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
