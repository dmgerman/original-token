multiline_comment|/*&n; * linux/mm/slab.h&n; * Written by Mark Hemment, 1996.&n; * (markhe@nextd.demon.co.uk)&n; */
macro_line|#if&t;!defined(_LINUX_SLAB_H)
DECL|macro|_LINUX_SLAB_H
mdefine_line|#define&t;_LINUX_SLAB_H
macro_line|#if&t;defined(__KERNEL__)
DECL|typedef|kmem_cache_t
r_typedef
r_struct
id|kmem_cache_s
id|kmem_cache_t
suffix:semicolon
macro_line|#include&t;&lt;linux/mm.h&gt;
macro_line|#include&t;&lt;linux/cache.h&gt;
multiline_comment|/* flags for kmem_cache_alloc() */
DECL|macro|SLAB_BUFFER
mdefine_line|#define&t;SLAB_BUFFER&t;&t;GFP_BUFFER
DECL|macro|SLAB_ATOMIC
mdefine_line|#define&t;SLAB_ATOMIC&t;&t;GFP_ATOMIC
DECL|macro|SLAB_USER
mdefine_line|#define&t;SLAB_USER&t;&t;GFP_USER
DECL|macro|SLAB_KERNEL
mdefine_line|#define&t;SLAB_KERNEL&t;&t;GFP_KERNEL
DECL|macro|SLAB_NFS
mdefine_line|#define&t;SLAB_NFS&t;&t;GFP_NFS
DECL|macro|SLAB_DMA
mdefine_line|#define&t;SLAB_DMA&t;&t;GFP_DMA
DECL|macro|SLAB_LEVEL_MASK
mdefine_line|#define SLAB_LEVEL_MASK&t;&t;(__GFP_WAIT|__GFP_HIGH|__GFP_IO)
DECL|macro|SLAB_NO_GROW
mdefine_line|#define&t;SLAB_NO_GROW&t;&t;0x00001000UL&t;/* don&squot;t grow a cache */
multiline_comment|/* flags to pass to kmem_cache_create().&n; * The first 3 are only valid when the allocator as been build&n; * SLAB_DEBUG_SUPPORT.&n; */
DECL|macro|SLAB_DEBUG_FREE
mdefine_line|#define&t;SLAB_DEBUG_FREE&t;&t;0x00000100UL&t;/* Peform (expensive) checks on free */
DECL|macro|SLAB_DEBUG_INITIAL
mdefine_line|#define&t;SLAB_DEBUG_INITIAL&t;0x00000200UL&t;/* Call constructor (as verifier) */
DECL|macro|SLAB_RED_ZONE
mdefine_line|#define&t;SLAB_RED_ZONE&t;&t;0x00000400UL&t;/* Red zone objs in a cache */
DECL|macro|SLAB_POISON
mdefine_line|#define&t;SLAB_POISON&t;&t;0x00000800UL&t;/* Poison objects */
DECL|macro|SLAB_NO_REAP
mdefine_line|#define&t;SLAB_NO_REAP&t;&t;0x00001000UL&t;/* never reap from the cache */
DECL|macro|SLAB_HWCACHE_ALIGN
mdefine_line|#define&t;SLAB_HWCACHE_ALIGN&t;0x00002000UL&t;/* align objs on a h/w cache lines */
DECL|macro|SLAB_CACHE_DMA
mdefine_line|#define SLAB_CACHE_DMA&t;&t;0x00004000UL&t;/* use GFP_DMA memory */
multiline_comment|/* flags passed to a constructor func */
DECL|macro|SLAB_CTOR_CONSTRUCTOR
mdefine_line|#define&t;SLAB_CTOR_CONSTRUCTOR&t;0x001UL&t;&t;/* if not set, then deconstructor */
DECL|macro|SLAB_CTOR_ATOMIC
mdefine_line|#define SLAB_CTOR_ATOMIC&t;0x002UL&t;&t;/* tell constructor it can&squot;t sleep */
DECL|macro|SLAB_CTOR_VERIFY
mdefine_line|#define&t;SLAB_CTOR_VERIFY&t;0x004UL&t;&t;/* tell constructor it&squot;s a verify call */
multiline_comment|/* prototypes */
r_extern
r_void
id|kmem_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kmem_cache_sizes_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|kmem_find_general_cachep
c_func
(paren
r_int
comma
r_int
id|gfpflags
)paren
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|kmem_cache_create
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
comma
r_void
(paren
op_star
)paren
(paren
r_void
op_star
comma
id|kmem_cache_t
op_star
comma
r_int
r_int
)paren
comma
r_void
(paren
op_star
)paren
(paren
r_void
op_star
comma
id|kmem_cache_t
op_star
comma
r_int
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|kmem_cache_destroy
c_func
(paren
id|kmem_cache_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kmem_cache_shrink
c_func
(paren
id|kmem_cache_t
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_cache_alloc
c_func
(paren
id|kmem_cache_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kmem_cache_free
c_func
(paren
id|kmem_cache_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmalloc
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kfree
c_func
(paren
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kmem_cache_reap
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|slabinfo_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|slabinfo_write_proc
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* System wide caches */
r_extern
id|kmem_cache_t
op_star
id|vm_area_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|mm_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|names_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|files_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|filp_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|dquot_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|bh_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|fs_cachep
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|sigact_cachep
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_SLAB_H */
eof
