macro_line|#ifndef __LINUX_DCACHE_H
DECL|macro|__LINUX_DCACHE_H
mdefine_line|#define __LINUX_DCACHE_H
multiline_comment|/*&n; * linux/include/linux/dcache.h&n; *&n; * Directory cache data structures&n; */
DECL|macro|D_MAXLEN
mdefine_line|#define D_MAXLEN 1024
DECL|macro|IS_ROOT
mdefine_line|#define IS_ROOT(x) ((x) == (x)-&gt;d_parent)
multiline_comment|/*&n; * &quot;quick string&quot; -- eases parameter passing, but more importantly&n; * saves &quot;metadata&quot; about the string (ie length and the hash).&n; */
DECL|struct|qstr
r_struct
id|qstr
(brace
DECL|member|name
r_const
r_int
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
DECL|member|hash
r_int
r_int
id|len
comma
id|hash
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Name hashing routines. Initial hash value */
DECL|macro|init_name_hash
mdefine_line|#define init_name_hash()&t;&t;0
multiline_comment|/* partial hash update function. Assume roughly 4 bits per character */
DECL|function|partial_name_hash
r_static
r_inline
r_int
r_int
id|partial_name_hash
c_func
(paren
r_int
r_char
id|c
comma
r_int
r_int
id|prevhash
)paren
(brace
id|prevhash
op_assign
(paren
id|prevhash
op_lshift
l_int|4
)paren
op_or
(paren
id|prevhash
op_rshift
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_minus
l_int|4
)paren
)paren
suffix:semicolon
r_return
id|prevhash
op_xor
id|c
suffix:semicolon
)brace
multiline_comment|/* Finally: cut down the number of bits to a int value (and try to avoid losing bits) */
DECL|function|end_name_hash
r_static
r_inline
r_int
r_int
id|end_name_hash
c_func
(paren
r_int
r_int
id|hash
)paren
(brace
r_if
c_cond
(paren
r_sizeof
(paren
id|hash
)paren
OG
r_sizeof
(paren
r_int
r_int
)paren
)paren
id|hash
op_add_assign
id|hash
op_rshift
l_int|4
op_star
r_sizeof
(paren
id|hash
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|hash
suffix:semicolon
)brace
DECL|struct|dentry
r_struct
id|dentry
(brace
DECL|member|d_count
r_int
id|d_count
suffix:semicolon
DECL|member|d_flags
r_int
r_int
id|d_flags
suffix:semicolon
DECL|member|d_inode
r_struct
id|inode
op_star
id|d_inode
suffix:semicolon
multiline_comment|/* Where the name belongs to - NULL is negative */
DECL|member|d_parent
r_struct
id|dentry
op_star
id|d_parent
suffix:semicolon
multiline_comment|/* parent directory */
DECL|member|d_mounts
r_struct
id|dentry
op_star
id|d_mounts
suffix:semicolon
multiline_comment|/* mount information */
DECL|member|d_covers
r_struct
id|dentry
op_star
id|d_covers
suffix:semicolon
DECL|member|d_hash
r_struct
id|list_head
id|d_hash
suffix:semicolon
multiline_comment|/* lookup hash list */
DECL|member|d_lru
r_struct
id|list_head
id|d_lru
suffix:semicolon
multiline_comment|/* d_count = 0 LRU list */
DECL|member|d_name
r_struct
id|qstr
id|d_name
suffix:semicolon
DECL|member|d_time
r_int
r_int
id|d_time
suffix:semicolon
multiline_comment|/* used by d_revalidate */
DECL|member|d_op
r_struct
id|dentry_operations
op_star
id|d_op
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dentry_operations
r_struct
id|dentry_operations
(brace
DECL|member|d_revalidate
r_int
(paren
op_star
id|d_revalidate
)paren
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|member|d_hash
r_int
(paren
op_star
id|d_hash
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|d_compare
r_int
(paren
op_star
id|d_compare
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|d_delete
r_void
(paren
op_star
id|d_delete
)paren
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the dentry parameter passed to d_hash and d_compare is the parent&n; * directory of the entries to be compared. It is used in case these&n; * functions need any directory specific information for determining&n; * equivalency classes.  Using the dentry itself might not work, as it&n; * might be a negative dentry which has no information associated with&n; * it */
multiline_comment|/* d_flags entries */
DECL|macro|DCACHE_AUTOFS_PENDING
mdefine_line|#define DCACHE_AUTOFS_PENDING 0x0001    /* autofs: &quot;under construction&quot; */
DECL|macro|DCACHE_NFSFS_RENAMED
mdefine_line|#define DCACHE_NFSFS_RENAMED  0x0002    /* this dentry has been &quot;silly&n;&t;&t;&t;&t;&t; * renamed&quot; and has to be&n;&t;&t;&t;&t;&t; * deleted on the last dput()&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * d_drop() unhashes the entry from the parent&n; * dentry hashes, so that it won&squot;t be found through&n; * a VFS lookup any more. Note that this is different&n; * from deleting the dentry - d_delete will try to&n; * mark the dentry negative if possible, giving a&n; * successful _negative_ lookup, while d_drop will&n; * just make the cache lookup fail.&n; *&n; * d_drop() is used mainly for stuff that wants&n; * to invalidate a dentry for some reason (NFS&n; * timeouts or autofs deletes).&n; */
DECL|function|d_drop
r_static
r_inline
r_void
id|d_drop
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the low-level FS interfaces to the dcache..&n; */
r_extern
r_void
id|d_instantiate
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|d_delete
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* allocate/de-allocate */
r_extern
r_struct
id|dentry
op_star
id|d_alloc
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_const
r_struct
id|qstr
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|shrink_dcache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|d_invalidate
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* only used at mount-time */
r_extern
r_struct
id|dentry
op_star
id|d_alloc_root
c_func
(paren
r_struct
id|inode
op_star
id|root_inode
comma
r_struct
id|dentry
op_star
id|old_root
)paren
suffix:semicolon
multiline_comment|/*&n; * This adds the entry to the hash queues and initializes &quot;d_inode&quot;.&n; * The entry was actually filled in earlier during &quot;d_alloc()&quot;&n; */
r_extern
r_void
id|d_add
c_func
(paren
r_struct
id|dentry
op_star
id|entry
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* used for rename() and baskets */
r_extern
r_void
id|d_move
c_func
(paren
r_struct
id|dentry
op_star
id|entry
comma
r_struct
id|dentry
op_star
id|newdentry
)paren
suffix:semicolon
multiline_comment|/* appendix may either be NULL or be used for transname suffixes */
r_extern
r_struct
id|dentry
op_star
id|d_lookup
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* validate &quot;insecure&quot; dentry pointer */
r_extern
r_int
id|d_validate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|dparent
comma
r_int
r_int
id|hash
comma
r_int
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* write full pathname into buffer and return start of pathname */
r_extern
r_char
op_star
id|d_path
c_func
(paren
r_struct
id|dentry
op_star
id|entry
comma
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
multiline_comment|/* Allocation counts.. */
DECL|function|dget
r_static
r_inline
r_struct
id|dentry
op_star
id|dget
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|dentry
)paren
id|dentry-&gt;d_count
op_increment
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
r_extern
r_void
id|dput
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __LINUX_DCACHE_H */
eof
