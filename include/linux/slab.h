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
multiline_comment|/* flags for kmem_cache_alloc() */
DECL|macro|SLAB_BUFFER
mdefine_line|#define&t;SLAB_BUFFER&t;&t;GFP_BUFFER&t;/* 0x00 */
DECL|macro|SLAB_ATOMIC
mdefine_line|#define&t;SLAB_ATOMIC&t;&t;GFP_ATOMIC&t;/* 0x01 */
DECL|macro|SLAB_USER
mdefine_line|#define&t;SLAB_USER&t;&t;GFP_USER&t;/* 0x02 */
DECL|macro|SLAB_KERNEL
mdefine_line|#define&t;SLAB_KERNEL&t;&t;GFP_KERNEL&t;/* 0x03 */
DECL|macro|SLAB_NOBUFFER
mdefine_line|#define&t;SLAB_NOBUFFER&t;&t;GFP_NOBUFFER&t;/* 0x04 */
DECL|macro|SLAB_NFS
mdefine_line|#define&t;SLAB_NFS&t;&t;GFP_NFS&t;&t;/* 0x05 */
DECL|macro|SLAB_DMA
mdefine_line|#define&t;SLAB_DMA&t;&t;GFP_DMA&t;&t;/* 0x08 */
DECL|macro|SLAB_LEVEL_MASK
mdefine_line|#define&t;SLAB_LEVEL_MASK&t;&t;GFP_LEVEL_MASK&t;/* 0x0f */
DECL|macro|SLAB_NO_GROW
mdefine_line|#define&t;SLAB_NO_GROW&t;&t;0x00001000UL&t;/* don&squot;t add another slab during an alloc */
multiline_comment|/* flags to pass to kmem_cache_create().&n; * The first 3 are only valid when the allocator has been build&n; * SLAB_DEBUG_SUPPORT.&n; */
DECL|macro|SLAB_DEBUG_FREE
mdefine_line|#define&t;SLAB_DEBUG_FREE&t;&t;0x00000100UL&t;/* Peform time consuming ptr checks on free */
DECL|macro|SLAB_DEBUG_INITIAL
mdefine_line|#define&t;SLAB_DEBUG_INITIAL&t;0x00000200UL&t;/* Call constructor, on release, to conform state */
DECL|macro|SLAB_RED_ZONE
mdefine_line|#define&t;SLAB_RED_ZONE&t;&t;0x00000400UL&t;/* Red zone objs in a cache */
DECL|macro|SLAB_HWCACHE_ALIGN
mdefine_line|#define&t;SLAB_HWCACHE_ALIGN&t;0x00000800UL&t;/* align objs on an hw cache line */
multiline_comment|/* flags passed to a constructor func */
DECL|macro|SLAB_CTOR_CONSTRUCTOR
mdefine_line|#define&t;SLAB_CTOR_CONSTRUCTOR&t;0x001UL&t;&t;/* if not set, then deconstructor */
DECL|macro|SLAB_CTOR_ATOMIC
mdefine_line|#define SLAB_CTOR_ATOMIC&t;0x002UL&t;&t;/* tell constructor it can&squot;t sleep */
DECL|macro|SLAB_DTOR_ATOMIC
mdefine_line|#define&t;SLAB_DTOR_ATOMIC&t;0x002UL&t;&t;/* tell deconstructor it can&squot;t sleep */
DECL|macro|SLAB_CTOR_VERIFY
mdefine_line|#define&t;SLAB_CTOR_VERIFY&t;0x004UL&t;&t;/* tell constructor it&squot;s a verify call */
multiline_comment|/* prototypes */
r_extern
r_int
id|kmem_cache_init
c_func
(paren
r_int
comma
r_int
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
r_struct
id|kmem_cache_s
op_star
id|kmem_cache_create
c_func
(paren
r_const
r_char
op_star
comma
r_int
r_int
comma
r_int
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
r_int
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
r_int
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
r_struct
id|kmem_cache_s
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kmem_cache_shrink
c_func
(paren
r_struct
id|kmem_cache_s
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_cache_alloc
c_func
(paren
r_struct
id|kmem_cache_s
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kmem_cache_free
c_func
(paren
r_struct
id|kmem_cache_s
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kmem_alloc
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kmem_free
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|kmem_cache_reap
c_func
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|get_slabinfo
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* System wide slabs. */
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
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_SLAB_H */
eof
