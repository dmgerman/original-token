multiline_comment|/*&n; *  linux/fs/ext2/dcache.c&n; *&n; *  Copyright (C) 1992, 1993  Remy Card (card@masi.ibp.fr)&n; *&n; */
multiline_comment|/*&n; * dcache.c contains the code that handles the directory cache used by&n; * lookup() and readdir()&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#ifndef DONT_USE_DCACHE
DECL|struct|dir_cache_entry
r_struct
id|dir_cache_entry
(brace
DECL|member|dev
r_int
r_int
id|dev
suffix:semicolon
DECL|member|dir
r_int
r_int
id|dir
suffix:semicolon
DECL|member|ino
r_int
r_int
id|ino
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|EXT2_NAME_LEN
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|queue_prev
r_struct
id|dir_cache_entry
op_star
id|queue_prev
suffix:semicolon
DECL|member|queue_next
r_struct
id|dir_cache_entry
op_star
id|queue_next
suffix:semicolon
DECL|member|prev
r_struct
id|dir_cache_entry
op_star
id|prev
suffix:semicolon
DECL|member|next
r_struct
id|dir_cache_entry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|first
r_static
r_struct
id|dir_cache_entry
op_star
id|first
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|last
r_static
r_struct
id|dir_cache_entry
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|first_free
r_static
r_struct
id|dir_cache_entry
op_star
id|first_free
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|cache_initialized
r_static
r_int
id|cache_initialized
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef EXT2FS_DEBUG_CACHE
DECL|variable|hits
r_static
r_int
id|hits
op_assign
l_int|0
suffix:semicolon
DECL|variable|misses
r_static
r_int
id|misses
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|macro|CACHE_SIZE
mdefine_line|#define CACHE_SIZE 128
DECL|variable|dcache
r_static
r_struct
id|dir_cache_entry
id|dcache
(braket
id|CACHE_SIZE
)braket
suffix:semicolon
DECL|macro|HASH_QUEUES
mdefine_line|#define HASH_QUEUES 16
DECL|variable|queue_head
r_static
r_struct
id|dir_cache_entry
op_star
id|queue_head
(braket
id|HASH_QUEUES
)braket
suffix:semicolon
DECL|variable|queue_tail
r_static
r_struct
id|dir_cache_entry
op_star
id|queue_tail
(braket
id|HASH_QUEUES
)braket
suffix:semicolon
DECL|macro|hash
mdefine_line|#define hash(dev,dir)&t;((dev ^ dir) % HASH_QUEUES)
multiline_comment|/*&n; * Initialize the cache&n; */
DECL|function|init_cache
r_static
r_void
id|init_cache
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|dcache
(braket
l_int|0
)braket
dot
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|dcache
(braket
l_int|0
)braket
dot
id|next
op_assign
op_amp
id|dcache
(braket
l_int|1
)braket
suffix:semicolon
id|dcache
(braket
l_int|0
)braket
dot
id|queue_next
op_assign
id|dcache
(braket
l_int|0
)braket
dot
id|queue_prev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|CACHE_SIZE
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dcache
(braket
id|i
)braket
dot
id|prev
op_assign
op_amp
id|dcache
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|dcache
(braket
id|i
)braket
dot
id|next
op_assign
op_amp
id|dcache
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|dcache
(braket
id|i
)braket
dot
id|queue_next
op_assign
id|dcache
(braket
id|i
)braket
dot
id|queue_prev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dcache
(braket
id|i
)braket
dot
id|prev
op_assign
op_amp
id|dcache
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|dcache
(braket
id|i
)braket
dot
id|next
op_assign
l_int|NULL
suffix:semicolon
id|dcache
(braket
id|i
)braket
dot
id|queue_next
op_assign
id|dcache
(braket
id|i
)braket
dot
id|queue_prev
op_assign
l_int|NULL
suffix:semicolon
id|first_free
op_assign
op_amp
id|dcache
(braket
l_int|0
)braket
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
id|HASH_QUEUES
suffix:semicolon
id|i
op_increment
)paren
id|queue_tail
(braket
id|i
)braket
op_assign
id|queue_head
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|cache_initialized
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a name in the cache&n; */
DECL|function|find_name
r_static
r_struct
id|dir_cache_entry
op_star
id|find_name
(paren
r_int
id|queue
comma
r_int
r_int
id|dev
comma
r_int
r_int
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|queue_head
(braket
id|queue
)braket
suffix:semicolon
id|p
op_ne
l_int|NULL
op_logical_and
(paren
id|p-&gt;dev
op_ne
id|dev
op_logical_or
id|p-&gt;dir
op_ne
id|dir
op_logical_or
id|p-&gt;len
op_ne
id|len
op_logical_or
id|strncmp
(paren
id|name
comma
id|p-&gt;name
comma
id|p-&gt;len
)paren
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;queue_next
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
multiline_comment|/*&n; * List the cache entries for debugging&n; */
DECL|function|show_cache
r_static
r_void
id|show_cache
(paren
r_const
r_char
op_star
id|func_name
)paren
(brace
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: cache status&bslash;n&quot;
comma
id|func_name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|first
suffix:semicolon
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
id|printk
(paren
l_string|&quot;dev:%04x, dir=%4d, name=%s&bslash;n&quot;
comma
id|p-&gt;dev
comma
id|p-&gt;dir
comma
id|p-&gt;name
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Add an entry at the beginning of the cache&n; */
DECL|function|add_to_cache
r_static
r_void
id|add_to_cache
(paren
r_struct
id|dir_cache_entry
op_star
id|p
)paren
(brace
id|p-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;next
op_assign
id|first
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
id|first-&gt;prev
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|last
)paren
id|last
op_assign
id|p
suffix:semicolon
id|first
op_assign
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Add an entry at the beginning of a queue&n; */
DECL|function|add_to_queue
r_static
r_void
id|add_to_queue
(paren
r_int
id|queue
comma
r_struct
id|dir_cache_entry
op_star
id|p
)paren
(brace
id|p-&gt;queue_prev
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;queue_next
op_assign
id|queue_head
(braket
id|queue
)braket
suffix:semicolon
r_if
c_cond
(paren
id|queue_head
(braket
id|queue
)braket
)paren
id|queue_head
(braket
id|queue
)braket
op_member_access_from_pointer
id|queue_prev
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_tail
(braket
id|queue
)braket
)paren
id|queue_tail
(braket
id|queue
)braket
op_assign
id|p
suffix:semicolon
id|queue_head
(braket
id|queue
)braket
op_assign
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove an entry from the cache&n; */
DECL|function|remove_from_cache
r_static
r_void
id|remove_from_cache
(paren
r_struct
id|dir_cache_entry
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;prev
)paren
id|p-&gt;prev-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
r_else
id|first
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;next
)paren
id|p-&gt;next-&gt;prev
op_assign
id|p-&gt;prev
suffix:semicolon
r_else
id|last
op_assign
id|p-&gt;prev
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove an entry from a queue&n; */
DECL|function|remove_from_queue
r_static
r_void
id|remove_from_queue
(paren
r_int
id|queue
comma
r_struct
id|dir_cache_entry
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;queue_prev
)paren
id|p-&gt;queue_prev-&gt;queue_next
op_assign
id|p-&gt;queue_next
suffix:semicolon
r_else
id|queue_head
(braket
id|queue
)braket
op_assign
id|p-&gt;queue_next
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;queue_next
)paren
id|p-&gt;queue_next-&gt;queue_prev
op_assign
id|p-&gt;queue_prev
suffix:semicolon
r_else
id|queue_tail
(braket
id|queue
)braket
op_assign
id|p-&gt;queue_prev
suffix:semicolon
)brace
multiline_comment|/*&n; * Invalidate all cache entries on a device (called by put_super() when&n; * a file system is unmounted)&n; */
DECL|function|ext2_dcache_invalidate
r_void
id|ext2_dcache_invalidate
(paren
r_int
r_int
id|dev
)paren
(brace
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
r_struct
id|dir_cache_entry
op_star
id|p2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_initialized
)paren
id|init_cache
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|first
suffix:semicolon
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
id|p2
)paren
(brace
id|p2
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;dev
op_eq
id|dev
)paren
(brace
id|remove_from_cache
(paren
id|p
)paren
suffix:semicolon
id|remove_from_queue
(paren
id|hash
(paren
id|p-&gt;dev
comma
id|p-&gt;dir
)paren
comma
id|p
)paren
suffix:semicolon
id|p-&gt;next
op_assign
id|first_free
suffix:semicolon
id|first_free
op_assign
id|p
suffix:semicolon
)brace
)brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|show_cache
(paren
l_string|&quot;dcache_invalidate&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Lookup a directory entry in the cache&n; *&n; * Note: the name is in the caller&squot;s address space&n; */
DECL|function|ext2_dcache_lookup
r_int
r_int
id|ext2_dcache_lookup
(paren
r_int
r_int
id|dev
comma
r_int
r_int
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_char
id|our_name
(braket
id|EXT2_NAME_LEN
)braket
suffix:semicolon
r_int
id|queue
suffix:semicolon
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_initialized
)paren
id|init_cache
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|EXT2_NAME_LEN
)paren
id|len
op_assign
id|EXT2_NAME_LEN
suffix:semicolon
id|memcpy
(paren
id|our_name
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
)paren
suffix:semicolon
id|our_name
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|printk
(paren
l_string|&quot;dcache_lookup (%04x, %d, %s, %d)&bslash;n&quot;
comma
id|dev
comma
id|dir
comma
id|our_name
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
id|queue
op_assign
id|hash
c_func
(paren
id|dev
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|find_name
(paren
id|queue
comma
id|dev
comma
id|dir
comma
id|our_name
comma
id|len
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|p
op_ne
id|first
)paren
(brace
id|remove_from_cache
(paren
id|p
)paren
suffix:semicolon
id|add_to_cache
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_ne
id|queue_head
(braket
id|queue
)braket
)paren
(brace
id|remove_from_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
id|add_to_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
)brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|hits
op_increment
suffix:semicolon
id|printk
(paren
l_string|&quot;dcache_lookup: %s,hit,inode=%d,hits=%d,misses=%d&bslash;n&quot;
comma
id|our_name
comma
id|p-&gt;ino
comma
id|hits
comma
id|misses
)paren
suffix:semicolon
id|show_cache
(paren
l_string|&quot;dcache_lookup&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|p-&gt;ino
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|misses
op_increment
suffix:semicolon
id|printk
(paren
l_string|&quot;dcache_lookup: %s,miss,hits=%d,misses=%d&bslash;n&quot;
comma
id|our_name
comma
id|hits
comma
id|misses
)paren
suffix:semicolon
id|show_cache
(paren
l_string|&quot;dcache_lookup&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Add a directory entry to the cache&n; *&n; * This function is called by ext2_lookup(), ext2_readdir()&n; * and the functions which create directory entries&n; *&n; * Note: the name is in the kernel address space&n; */
DECL|function|ext2_dcache_add
r_void
id|ext2_dcache_add
(paren
r_int
r_int
id|dev
comma
r_int
r_int
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
r_int
id|ino
)paren
(brace
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
r_int
id|queue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_initialized
)paren
id|init_cache
(paren
)paren
suffix:semicolon
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|printk
(paren
l_string|&quot;dcache_add (%04x, %d, %s, %d, %d)&bslash;n&quot;
comma
id|dev
comma
id|dir
comma
id|name
comma
id|len
comma
id|ino
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|len
OG
id|EXT2_NAME_LEN
)paren
id|len
op_assign
id|EXT2_NAME_LEN
suffix:semicolon
id|queue
op_assign
id|hash
c_func
(paren
id|dev
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|find_name
(paren
id|queue
comma
id|dev
comma
id|dir
comma
id|name
comma
id|len
)paren
)paren
)paren
(brace
id|p-&gt;dir
op_assign
id|dir
suffix:semicolon
id|p-&gt;ino
op_assign
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|first
)paren
(brace
id|remove_from_cache
(paren
id|p
)paren
suffix:semicolon
id|add_to_cache
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_ne
id|queue_head
(braket
id|queue
)braket
)paren
(brace
id|remove_from_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
id|add_to_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|first_free
)paren
(brace
id|p
op_assign
id|first_free
suffix:semicolon
id|first_free
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|last
)paren
id|panic
(paren
l_string|&quot;dcache_add: last == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|p
op_assign
id|last
suffix:semicolon
id|last
op_assign
id|p-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|last
)paren
id|last-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|remove_from_queue
(paren
id|hash
(paren
id|p-&gt;dev
comma
id|p-&gt;dir
)paren
comma
id|p
)paren
suffix:semicolon
)brace
)brace
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;dir
op_assign
id|dir
suffix:semicolon
id|p-&gt;ino
op_assign
id|ino
suffix:semicolon
id|strncpy
(paren
id|p-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|p-&gt;len
op_assign
id|len
suffix:semicolon
id|p-&gt;name
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|add_to_cache
(paren
id|p
)paren
suffix:semicolon
id|add_to_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
)brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|show_cache
(paren
l_string|&quot;dcache_add&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Remove a directory from the cache&n; *&n; * This function is called by the functions which remove directory entries&n; *&n; * Note: the name is in the kernel address space&n; */
DECL|function|ext2_dcache_remove
r_void
id|ext2_dcache_remove
(paren
r_int
r_int
id|dev
comma
r_int
r_int
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_struct
id|dir_cache_entry
op_star
id|p
suffix:semicolon
r_int
id|queue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_initialized
)paren
id|init_cache
(paren
)paren
suffix:semicolon
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|printk
(paren
l_string|&quot;dcache_remove (%04x, %d, %s, %d)&bslash;n&quot;
comma
id|dev
comma
id|dir
comma
id|name
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|len
OG
id|EXT2_NAME_LEN
)paren
id|len
op_assign
id|EXT2_NAME_LEN
suffix:semicolon
id|queue
op_assign
id|hash
c_func
(paren
id|dev
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|find_name
(paren
id|queue
comma
id|dev
comma
id|dir
comma
id|name
comma
id|len
)paren
)paren
)paren
(brace
id|remove_from_cache
(paren
id|p
)paren
suffix:semicolon
id|remove_from_queue
(paren
id|queue
comma
id|p
)paren
suffix:semicolon
id|p-&gt;next
op_assign
id|first_free
suffix:semicolon
id|first_free
op_assign
id|p
suffix:semicolon
)brace
macro_line|#ifdef EXT2FS_DEBUG_CACHE
id|show_cache
(paren
l_string|&quot;dcache_remove&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof
