multiline_comment|/*&n; *  cache.c&n; *&n; * Copyright (C) 1997 by Bill Hawes&n; *&n; * Routines to support directory cacheing using the page cache.&n; * Right now this only works for smbfs, but will be generalized&n; * for use with other filesystems.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|SMBFS_PARANOIA
mdefine_line|#define SMBFS_PARANOIA 1
multiline_comment|/* #define SMBFS_DEBUG_VERBOSE 1 */
r_static
r_inline
r_struct
id|inode
op_star
DECL|function|get_cache_inode
id|get_cache_inode
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
)paren
(brace
r_return
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
(paren
r_int
r_int
)paren
id|cachep
)paren
)paren
op_member_access_from_pointer
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a pointer to the cache_head structure,&n; * mapped as the page at offset 0. The page is&n; * kept locked while we&squot;re using the cache.&n; */
r_struct
id|cache_head
op_star
DECL|function|smb_get_dircache
id|smb_get_dircache
c_func
(paren
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
id|cache_head
op_star
id|cachep
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_get_dircache: finding cache for %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
macro_line|#endif
id|cachep
op_assign
(paren
r_struct
id|cache_head
op_star
)paren
id|get_cached_page
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cachep
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|cachep-&gt;valid
)paren
(brace
r_struct
id|cache_index
op_star
id|index
op_assign
id|cachep-&gt;index
suffix:semicolon
r_struct
id|cache_block
op_star
id|block
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|i
suffix:semicolon
id|cachep-&gt;valid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Here we only want to find existing cache blocks,&n;&t;&t; * not add new ones.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cachep-&gt;pages
suffix:semicolon
id|i
op_increment
comma
id|index
op_increment
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
id|index-&gt;block
)paren
id|printk
c_func
(paren
l_string|&quot;smb_get_dircache: cache %s/%s has existing block!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
macro_line|#endif
id|offset
op_assign
id|PAGE_SIZE
op_plus
(paren
id|i
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|block
op_assign
(paren
r_struct
id|cache_block
op_star
)paren
id|get_cached_page
c_func
(paren
id|inode
comma
id|offset
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_goto
id|out
suffix:semicolon
id|index-&gt;block
op_assign
id|block
suffix:semicolon
)brace
id|cachep-&gt;valid
op_assign
l_int|1
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|cachep
suffix:semicolon
)brace
multiline_comment|/*&n; * Unlock and release the data blocks.&n; */
r_static
r_void
DECL|function|smb_free_cache_blocks
id|smb_free_cache_blocks
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
)paren
(brace
r_struct
id|cache_index
op_star
id|index
op_assign
id|cachep-&gt;index
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_free_cache_blocks: freeing %d blocks&bslash;n&quot;
comma
id|cachep-&gt;pages
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cachep-&gt;pages
suffix:semicolon
id|i
op_increment
comma
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|index-&gt;block
)paren
(brace
id|put_cached_page
c_func
(paren
(paren
r_int
r_int
)paren
id|index-&gt;block
)paren
suffix:semicolon
id|index-&gt;block
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Unlocks and releases the dircache.&n; */
r_void
DECL|function|smb_free_dircache
id|smb_free_dircache
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
)paren
(brace
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_free_dircache: freeing cache&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|smb_free_cache_blocks
c_func
(paren
id|cachep
)paren
suffix:semicolon
id|put_cached_page
c_func
(paren
(paren
r_int
r_int
)paren
id|cachep
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initializes the dircache. We release any existing data blocks,&n; * and then clear the cache_head structure.&n; */
r_void
DECL|function|smb_init_dircache
id|smb_init_dircache
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
)paren
(brace
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_init_dircache: initializing cache, %d blocks&bslash;n&quot;
comma
id|cachep-&gt;pages
)paren
suffix:semicolon
macro_line|#endif
id|smb_free_cache_blocks
c_func
(paren
id|cachep
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cachep
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cache_head
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a new entry to the cache.  This assumes that the&n; * entries are coming in order and are added to the end.&n; */
r_void
DECL|function|smb_add_to_cache
id|smb_add_to_cache
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
comma
r_struct
id|cache_dirent
op_star
id|entry
comma
id|off_t
id|fpos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|get_cache_inode
c_func
(paren
id|cachep
)paren
suffix:semicolon
r_struct
id|cache_index
op_star
id|index
suffix:semicolon
r_struct
id|cache_block
op_star
id|block
suffix:semicolon
r_int
r_int
id|page_off
suffix:semicolon
r_int
r_int
id|nent
comma
id|offset
comma
id|len
op_assign
id|entry-&gt;len
suffix:semicolon
r_int
r_int
id|needed
op_assign
id|len
op_plus
r_sizeof
(paren
r_struct
id|cache_entry
)paren
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_add_to_cache: cache inode %p, status %d, adding %s at %ld&bslash;n&quot;
comma
id|inode
comma
id|cachep-&gt;status
comma
id|entry-&gt;d_name
comma
id|fpos
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Don&squot;t do anything if we&squot;ve had an error ...&n;&t; */
r_if
c_cond
(paren
id|cachep-&gt;status
)paren
r_goto
id|out
suffix:semicolon
id|index
op_assign
op_amp
id|cachep-&gt;index
(braket
id|cachep-&gt;idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|index-&gt;block
)paren
r_goto
id|get_block
suffix:semicolon
multiline_comment|/* space available? */
r_if
c_cond
(paren
id|needed
OL
id|index-&gt;space
)paren
(brace
id|add_entry
suffix:colon
id|nent
op_assign
id|index-&gt;num_entries
suffix:semicolon
id|index-&gt;num_entries
op_increment
suffix:semicolon
id|index-&gt;space
op_sub_assign
id|needed
suffix:semicolon
id|offset
op_assign
id|index-&gt;space
op_plus
id|index-&gt;num_entries
op_star
r_sizeof
(paren
r_struct
id|cache_entry
)paren
suffix:semicolon
id|block
op_assign
id|index-&gt;block
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|block-&gt;cb_data.names
(braket
id|offset
)braket
comma
id|entry-&gt;name
comma
id|len
)paren
suffix:semicolon
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|namelen
op_assign
id|len
suffix:semicolon
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|offset
op_assign
id|offset
suffix:semicolon
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|ino
op_assign
id|entry-&gt;ino
suffix:semicolon
id|cachep-&gt;entries
op_increment
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_add_to_cache: added entry %s, len=%d, pos=%ld, entries=%d&bslash;n&quot;
comma
id|entry-&gt;d_name
comma
id|len
comma
id|fpos
comma
id|cachep-&gt;entries
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This block is full ... advance the index.&n;&t; */
id|cachep-&gt;idx
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cachep-&gt;idx
OG
id|NINDEX
)paren
multiline_comment|/* not likely */
r_goto
id|out_full
suffix:semicolon
id|index
op_increment
suffix:semicolon
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
id|index-&gt;block
)paren
id|printk
c_func
(paren
l_string|&quot;smb_add_to_cache: new index already has block!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Get the next cache block&n;&t; */
id|get_block
suffix:colon
id|cachep-&gt;pages
op_increment
suffix:semicolon
id|page_off
op_assign
id|PAGE_SIZE
op_plus
(paren
id|cachep-&gt;idx
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|block
op_assign
(paren
r_struct
id|cache_block
op_star
)paren
id|get_cached_page
c_func
(paren
id|inode
comma
id|page_off
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
)paren
(brace
id|index-&gt;block
op_assign
id|block
suffix:semicolon
id|index-&gt;space
op_assign
id|PAGE_SIZE
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_add_to_cache: inode=%p, pages=%d, block at %ld&bslash;n&quot;
comma
id|inode
comma
id|cachep-&gt;pages
comma
id|page_off
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|add_entry
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * On failure, just set the return status ...&n;&t; */
id|out_full
suffix:colon
id|cachep-&gt;status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|out
suffix:colon
r_return
suffix:semicolon
)brace
r_int
DECL|function|smb_find_in_cache
id|smb_find_in_cache
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
comma
id|off_t
id|pos
comma
r_struct
id|cache_dirent
op_star
id|entry
)paren
(brace
r_struct
id|cache_index
op_star
id|index
op_assign
id|cachep-&gt;index
suffix:semicolon
r_struct
id|cache_block
op_star
id|block
suffix:semicolon
r_int
r_int
id|i
comma
id|nent
comma
id|offset
op_assign
l_int|0
suffix:semicolon
id|off_t
id|next_pos
op_assign
l_int|2
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_find_in_cache: cache %p, looking for pos=%ld&bslash;n&quot;
comma
id|cachep
comma
id|pos
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cachep-&gt;pages
suffix:semicolon
id|i
op_increment
comma
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pos
OL
id|next_pos
)paren
r_break
suffix:semicolon
id|nent
op_assign
id|pos
op_minus
id|next_pos
suffix:semicolon
id|next_pos
op_add_assign
id|index-&gt;num_entries
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|next_pos
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The entry is in this block. Note: we return&n;&t;&t; * then name as a reference with _no_ null byte.&n;&t;&t; */
id|block
op_assign
id|index-&gt;block
suffix:semicolon
id|entry-&gt;ino
op_assign
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|ino
suffix:semicolon
id|entry-&gt;len
op_assign
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|namelen
suffix:semicolon
id|offset
op_assign
id|block-&gt;cb_data.table
(braket
id|nent
)braket
dot
id|offset
suffix:semicolon
id|entry-&gt;name
op_assign
op_amp
id|block-&gt;cb_data.names
(braket
id|offset
)braket
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_find_in_cache: found %s, len=%d, pos=%ld&bslash;n&quot;
comma
id|entry-&gt;name
comma
id|entry-&gt;len
comma
id|pos
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
r_int
DECL|function|smb_refill_dircache
id|smb_refill_dircache
c_func
(paren
r_struct
id|cache_head
op_star
id|cachep
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
r_int
id|result
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_refill_dircache: cache %s/%s, blocks=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|cachep-&gt;pages
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Fill the cache, starting at position 2.&n;&t; */
id|retry
suffix:colon
id|inode-&gt;u.smbfs_i.cache_valid
op_or_assign
id|SMB_F_CACHEVALID
suffix:semicolon
id|result
op_assign
id|smb_proc_readdir
c_func
(paren
id|dentry
comma
l_int|2
comma
id|cachep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_refill_dircache: readdir failed, result=%d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check whether the cache was invalidated while&n;&t; * we were doing the scan ...&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;u.smbfs_i.cache_valid
op_amp
id|SMB_F_CACHEVALID
)paren
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_refill_dircache: cache invalidated, retrying&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|retry
suffix:semicolon
)brace
id|result
op_assign
id|cachep-&gt;status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|cachep-&gt;valid
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_refill_cache: cache %s/%s status=%d, entries=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|cachep-&gt;status
comma
id|cachep-&gt;entries
)paren
suffix:semicolon
macro_line|#endif
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
r_void
DECL|function|smb_invalid_dir_cache
id|smb_invalid_dir_cache
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
(brace
multiline_comment|/*&n;&t; * Get rid of any unlocked pages, and clear the&n;&t; * &squot;valid&squot; flag in case a scan is in progress.&n;&t; */
id|invalidate_inode_pages
c_func
(paren
id|dir
)paren
suffix:semicolon
id|dir-&gt;u.smbfs_i.cache_valid
op_and_assign
op_complement
id|SMB_F_CACHEVALID
suffix:semicolon
id|dir-&gt;u.smbfs_i.oldmtime
op_assign
l_int|0
suffix:semicolon
)brace
eof