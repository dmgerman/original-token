multiline_comment|/*&n; * Cache operations for Coda.&n; * For Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
r_static
r_void
id|coda_ccinsert
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_void
id|coda_cninsert
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
comma
r_struct
id|coda_inode_info
op_star
id|cii
)paren
suffix:semicolon
r_static
r_void
id|coda_ccremove
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
)paren
suffix:semicolon
r_static
r_void
id|coda_cnremove
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
)paren
suffix:semicolon
r_static
r_void
id|coda_cache_create
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
r_static
r_struct
id|coda_cache
op_star
id|coda_cache_find
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* insert a acl-cache entry in sb list */
DECL|function|coda_ccinsert
r_static
r_void
id|coda_ccinsert
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
id|ENTRY
suffix:semicolon
multiline_comment|/* third test verifies cc was initialized before adding it &n;&t;   to the sblist. Probably superfluous */
r_if
c_cond
(paren
op_logical_neg
id|sbi
op_logical_or
op_logical_neg
id|el
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|el-&gt;cc_cclist
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_ccinsert: NULL sbi or el-&gt;cc_cclist not empty!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|el-&gt;cc_cclist
comma
op_amp
id|sbi-&gt;sbi_cchead
)paren
suffix:semicolon
)brace
multiline_comment|/* insert a acl-cache entry in the inode list */
DECL|function|coda_cninsert
r_static
r_void
id|coda_cninsert
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
comma
r_struct
id|coda_inode_info
op_star
id|cii
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cii
op_logical_or
op_logical_neg
id|el
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|el-&gt;cc_cnlist
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_cninsert: NULL cii or el-&gt;cc_cnlist not empty!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|el-&gt;cc_cnlist
comma
op_amp
id|cii-&gt;c_cnhead
)paren
suffix:semicolon
)brace
multiline_comment|/* remove a cache entry from the superblock list */
DECL|function|coda_ccremove
r_static
r_void
id|coda_ccremove
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|el-&gt;cc_cclist
)paren
)paren
id|list_del
c_func
(paren
op_amp
id|el-&gt;cc_cclist
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;coda_ccremove: loose cc entry!&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* remove a cache entry from the inode&squot;s list */
DECL|function|coda_cnremove
r_static
r_void
id|coda_cnremove
c_func
(paren
r_struct
id|coda_cache
op_star
id|el
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|el-&gt;cc_cnlist
)paren
)paren
id|list_del
c_func
(paren
op_amp
id|el-&gt;cc_cnlist
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;coda_cnremove: loose cn entry!&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* create a new cache entry and enlist it */
DECL|function|coda_cache_create
r_static
r_void
id|coda_cache_create
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
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
op_assign
l_int|NULL
suffix:semicolon
id|ENTRY
suffix:semicolon
id|CODA_ALLOC
c_func
(paren
id|cc
comma
r_struct
id|coda_cache
op_star
comma
r_sizeof
(paren
op_star
id|cc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Out of memory in coda_cache_enter!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cc-&gt;cc_cclist
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cc-&gt;cc_cnlist
)paren
suffix:semicolon
id|coda_load_creds
c_func
(paren
op_amp
id|cc-&gt;cc_cred
)paren
suffix:semicolon
id|cc-&gt;cc_mask
op_assign
id|mask
suffix:semicolon
id|coda_cninsert
c_func
(paren
id|cc
comma
id|cii
)paren
suffix:semicolon
id|coda_ccinsert
c_func
(paren
id|cc
comma
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/* see if there is a match for the current &n;   credentials already */
DECL|function|coda_cache_find
r_static
r_struct
id|coda_cache
op_star
id|coda_cache_find
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|le
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
op_assign
l_int|NULL
suffix:semicolon
id|le
op_assign
id|lh
op_assign
op_amp
id|cii-&gt;c_cnhead
suffix:semicolon
r_while
c_loop
(paren
(paren
id|le
op_assign
id|le-&gt;next
)paren
op_ne
id|lh
)paren
(brace
multiline_comment|/* compare name and creds */
id|cc
op_assign
id|list_entry
c_func
(paren
id|le
comma
r_struct
id|coda_cache
comma
id|cc_cnlist
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|coda_cred_ok
c_func
(paren
op_amp
id|cc-&gt;cc_cred
)paren
)paren
r_continue
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;HIT for ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
id|cc
suffix:semicolon
multiline_comment|/* cache hit */
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* create or extend an acl cache hit */
DECL|function|coda_cache_enter
r_void
id|coda_cache_enter
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
r_struct
id|coda_cache
op_star
id|cc
suffix:semicolon
id|cc
op_assign
id|coda_cache_find
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
)paren
(brace
id|cc-&gt;cc_mask
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
(brace
id|coda_cache_create
c_func
(paren
id|inode
comma
id|mask
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* remove all cached acl matches from an inode */
DECL|function|coda_cache_clear_inode
r_void
id|coda_cache_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|list_head
op_star
id|le
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;coda_cache_clear_inode: NULL inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|le
op_assign
id|cii-&gt;c_cnhead.next
suffix:semicolon
r_while
c_loop
(paren
id|le
op_ne
op_amp
id|cii-&gt;c_cnhead
)paren
(brace
id|cc
op_assign
id|list_entry
c_func
(paren
id|le
comma
r_struct
id|coda_cache
comma
id|cc_cnlist
)paren
suffix:semicolon
id|le
op_assign
id|le-&gt;next
suffix:semicolon
id|coda_cnremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|coda_ccremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|cc
comma
r_sizeof
(paren
op_star
id|cc
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* remove all acl caches */
DECL|function|coda_cache_clear_all
r_void
id|coda_cache_clear_all
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|list_head
op_star
id|le
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
suffix:semicolon
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_cache_clear_all: NULL sbi&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|sbi-&gt;sbi_cchead
)paren
)paren
r_return
suffix:semicolon
id|le
op_assign
id|sbi-&gt;sbi_cchead.next
suffix:semicolon
r_while
c_loop
(paren
id|le
op_ne
op_amp
id|sbi-&gt;sbi_cchead
)paren
(brace
id|cc
op_assign
id|list_entry
c_func
(paren
id|le
comma
r_struct
id|coda_cache
comma
id|cc_cclist
)paren
suffix:semicolon
id|le
op_assign
id|le-&gt;next
suffix:semicolon
id|coda_cnremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|coda_ccremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|cc
comma
r_sizeof
(paren
op_star
id|cc
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* remove all acl caches for a principal */
DECL|function|coda_cache_clear_cred
r_void
id|coda_cache_clear_cred
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|coda_cred
op_star
id|cred
)paren
(brace
r_struct
id|list_head
op_star
id|le
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
suffix:semicolon
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_cache_clear_all: NULL sbi&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|sbi-&gt;sbi_cchead
)paren
)paren
r_return
suffix:semicolon
id|le
op_assign
id|sbi-&gt;sbi_cchead.next
suffix:semicolon
r_while
c_loop
(paren
id|le
op_ne
op_amp
id|sbi-&gt;sbi_cchead
)paren
(brace
id|cc
op_assign
id|list_entry
c_func
(paren
id|le
comma
r_struct
id|coda_cache
comma
id|cc_cclist
)paren
suffix:semicolon
id|le
op_assign
id|le-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|coda_cred_eq
c_func
(paren
op_amp
id|cc-&gt;cc_cred
comma
id|cred
)paren
)paren
(brace
id|coda_cnremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|coda_ccremove
c_func
(paren
id|cc
)paren
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|cc
comma
r_sizeof
(paren
op_star
id|cc
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* check if the mask has been matched against the acl&n;   already */
DECL|function|coda_cache_check
r_int
id|coda_cache_check
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
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|le
suffix:semicolon
r_struct
id|coda_cache
op_star
id|cc
op_assign
l_int|NULL
suffix:semicolon
id|le
op_assign
id|lh
op_assign
op_amp
id|cii-&gt;c_cnhead
suffix:semicolon
r_while
c_loop
(paren
(paren
id|le
op_assign
id|le-&gt;next
)paren
op_ne
id|lh
)paren
(brace
multiline_comment|/* compare name and creds */
id|cc
op_assign
id|list_entry
c_func
(paren
id|le
comma
r_struct
id|coda_cache
comma
id|cc_cnlist
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cc-&gt;cc_mask
op_amp
id|mask
)paren
op_ne
id|mask
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|coda_cred_ok
c_func
(paren
op_amp
id|cc-&gt;cc_cred
)paren
)paren
r_continue
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;HIT for ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* cache hit */
)brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot;MISS for ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Purging dentries and children */
multiline_comment|/* The following routines drop dentries which are not&n;   in use and flag dentries which are in use to be &n;   zapped later.&n;&n;   The flags are detected by:&n;   - coda_dentry_revalidate (for lookups) if the flag is C_PURGE&n;   - coda_dentry_delete: to remove dentry from the cache when d_count&n;     falls to zero&n;   - an inode method coda_revalidate (for attributes) if the &n;     flag is C_VATTR&n;*/
multiline_comment|/* &n;   Some of this is pretty scary: what can disappear underneath us?&n;   - shrink_dcache_parent calls on purge_one_dentry which is safe:&n;     it only purges children.&n;   - dput is evil since it  may recurse up the dentry tree&n; */
DECL|function|coda_purge_dentries
r_void
id|coda_purge_dentries
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|head
op_assign
op_amp
id|inode-&gt;i_dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
multiline_comment|/* better safe than sorry: dput could kill us */
id|iget
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
multiline_comment|/* catch the dentries later if some are still busy */
id|coda_flag_inode
c_func
(paren
id|inode
comma
id|C_PURGE
)paren
suffix:semicolon
id|restart
suffix:colon
id|tmp
op_assign
id|head
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|tmp-&gt;next
)paren
op_ne
id|head
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|tmp
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
id|dentry-&gt;d_count
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_DOWNCALL
comma
l_string|&quot;coda_free_dentries: freeing %s/%s, i_count=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|inode-&gt;i_count
)paren
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* this won&squot;t do any harm: just flag all children */
DECL|function|coda_flag_children
r_static
r_void
id|coda_flag_children
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_int
id|flag
)paren
(brace
r_struct
id|list_head
op_star
id|child
suffix:semicolon
r_struct
id|dentry
op_star
id|de
suffix:semicolon
id|child
op_assign
id|parent-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|child
op_ne
op_amp
id|parent-&gt;d_subdirs
)paren
(brace
id|de
op_assign
id|list_entry
c_func
(paren
id|child
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
id|child
op_assign
id|child-&gt;next
suffix:semicolon
multiline_comment|/* don&squot;t know what to do with negative dentries */
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;d_inode
)paren
r_continue
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_DOWNCALL
comma
l_string|&quot;%d for %*s/%*s&bslash;n&quot;
comma
id|flag
comma
id|de-&gt;d_name.len
comma
id|de-&gt;d_name.name
comma
id|de-&gt;d_parent-&gt;d_name.len
comma
id|de-&gt;d_parent-&gt;d_name.name
)paren
suffix:semicolon
id|coda_flag_inode
c_func
(paren
id|de-&gt;d_inode
comma
id|flag
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|coda_flag_inode_children
r_void
id|coda_flag_inode_children
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
(brace
r_struct
id|list_head
op_star
id|alias
suffix:semicolon
r_struct
id|dentry
op_star
id|alias_de
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
suffix:semicolon
id|alias_de
op_assign
id|d_find_alias
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alias_de
)paren
r_return
suffix:semicolon
id|coda_flag_children
c_func
(paren
id|alias_de
comma
id|flag
)paren
suffix:semicolon
id|shrink_dcache_parent
c_func
(paren
id|alias_de
)paren
suffix:semicolon
id|dput
c_func
(paren
id|alias_de
)paren
suffix:semicolon
)brace
multiline_comment|/* this will not zap the inode away */
DECL|function|coda_flag_inode
r_void
id|coda_flag_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_CACHE
comma
l_string|&quot; no inode!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|cii-&gt;c_flags
op_or_assign
id|flag
suffix:semicolon
)brace
eof
