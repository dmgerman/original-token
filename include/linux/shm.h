macro_line|#ifndef _LINUX_SHM_H_
DECL|macro|_LINUX_SHM_H_
mdefine_line|#define _LINUX_SHM_H_
macro_line|#include &lt;linux/ipc.h&gt;
DECL|struct|shmid_ds
r_struct
id|shmid_ds
(brace
DECL|member|shm_perm
r_struct
id|ipc_perm
id|shm_perm
suffix:semicolon
multiline_comment|/* operation perms */
DECL|member|shm_segsz
r_int
id|shm_segsz
suffix:semicolon
multiline_comment|/* size of segment (bytes) */
DECL|member|shm_atime
id|time_t
id|shm_atime
suffix:semicolon
multiline_comment|/* last attach time */
DECL|member|shm_dtime
id|time_t
id|shm_dtime
suffix:semicolon
multiline_comment|/* last detach time */
DECL|member|shm_ctime
id|time_t
id|shm_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|shm_cpid
r_int
r_int
id|shm_cpid
suffix:semicolon
multiline_comment|/* pid of creator */
DECL|member|shm_lpid
r_int
r_int
id|shm_lpid
suffix:semicolon
multiline_comment|/* pid of last operator */
DECL|member|shm_nattch
r_int
id|shm_nattch
suffix:semicolon
multiline_comment|/* no. of current attaches */
multiline_comment|/* the following are private */
DECL|member|shm_npages
r_int
r_int
id|shm_npages
suffix:semicolon
multiline_comment|/* size of segment (pages) */
DECL|member|shm_pages
r_int
r_int
op_star
id|shm_pages
suffix:semicolon
multiline_comment|/* array of ptrs to frames -&gt; SHMMAX */
DECL|member|attaches
r_struct
id|vm_area_struct
op_star
id|attaches
suffix:semicolon
multiline_comment|/* descriptors for attaches */
)brace
suffix:semicolon
multiline_comment|/* permission flag for shmget */
DECL|macro|SHM_R
mdefine_line|#define SHM_R&t;&t;0400&t;/* or S_IRUGO from &lt;linux/stat.h&gt; */
DECL|macro|SHM_W
mdefine_line|#define SHM_W&t;&t;0200&t;/* or S_IWUGO from &lt;linux/stat.h&gt; */
multiline_comment|/* mode for attach */
DECL|macro|SHM_RDONLY
mdefine_line|#define&t;SHM_RDONLY&t;010000&t;/* read-only access */
DECL|macro|SHM_RND
mdefine_line|#define&t;SHM_RND&t;&t;020000&t;/* round attach address to SHMLBA boundary */
DECL|macro|SHM_REMAP
mdefine_line|#define&t;SHM_REMAP&t;040000&t;/* take-over region on attach */
multiline_comment|/* super user shmctl commands */
DECL|macro|SHM_LOCK
mdefine_line|#define SHM_LOCK &t;11
DECL|macro|SHM_UNLOCK
mdefine_line|#define SHM_UNLOCK &t;12
DECL|struct|shminfo
r_struct
id|shminfo
(brace
DECL|member|shmmax
r_int
id|shmmax
suffix:semicolon
DECL|member|shmmin
r_int
id|shmmin
suffix:semicolon
DECL|member|shmmni
r_int
id|shmmni
suffix:semicolon
DECL|member|shmseg
r_int
id|shmseg
suffix:semicolon
DECL|member|shmall
r_int
id|shmall
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* address range for shared memory attaches if no address passed to shmat() */
DECL|macro|SHM_RANGE_START
mdefine_line|#define SHM_RANGE_START&t;0x50000000
DECL|macro|SHM_RANGE_END
mdefine_line|#define SHM_RANGE_END&t;0x60000000
multiline_comment|/* format of page table entries that correspond to shared memory pages&n;   currently out in swap space (see also mm/swap.c):&n;   bit 0 (PAGE_PRESENT) is  = 0&n;   bits 7..1 (SWP_TYPE) are = SHM_SWP_TYPE&n;   bits 31..8 are used like this:&n;   bits 14..8 (SHM_ID) the id of the shared memory segment&n;   bits 29..15 (SHM_IDX) the index of the page within the shared memory segment&n;                    (actually only bits 24..15 get used since SHMMAX is so low)&n;   bit 31 (SHM_READ_ONLY) flag whether the page belongs to a read-only attach&n;*/
DECL|macro|SHM_ID_SHIFT
mdefine_line|#define SHM_ID_SHIFT&t;8
multiline_comment|/* Keep _SHM_ID_BITS as low as possible since SHMMNI depends on it and&n;   there is a static array of size SHMMNI. */
DECL|macro|_SHM_ID_BITS
mdefine_line|#define _SHM_ID_BITS&t;7
DECL|macro|SHM_ID_MASK
mdefine_line|#define SHM_ID_MASK&t;((1&lt;&lt;_SHM_ID_BITS)-1)
DECL|macro|SHM_IDX_SHIFT
mdefine_line|#define SHM_IDX_SHIFT&t;(SHM_ID_SHIFT+_SHM_ID_BITS)
DECL|macro|_SHM_IDX_BITS
mdefine_line|#define _SHM_IDX_BITS&t;15
DECL|macro|SHM_IDX_MASK
mdefine_line|#define SHM_IDX_MASK&t;((1&lt;&lt;_SHM_IDX_BITS)-1)
DECL|macro|SHM_READ_ONLY
mdefine_line|#define SHM_READ_ONLY&t;(1&lt;&lt;31)
multiline_comment|/* We must have SHM_ID_SHIFT + _SHM_ID_BITS + _SHM_IDX_BITS + 1 &lt;= 32&n;   and SHMMAX &lt;= (PAGE_SIZE &lt;&lt; _SHM_IDX_BITS). */
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX 0x3fa000&t;&t;&t;&t;/* max shared seg size (bytes) */
DECL|macro|SHMMIN
mdefine_line|#define SHMMIN 1&t; /* really PAGE_SIZE */&t;/* min shared seg size (bytes) */
DECL|macro|SHMMNI
mdefine_line|#define SHMMNI (1&lt;&lt;_SHM_ID_BITS)&t;&t;/* max num of segs system wide */
DECL|macro|SHMALL
mdefine_line|#define SHMALL (1&lt;&lt;(_SHM_IDX_BITS+_SHM_ID_BITS))/* max shm system wide (pages) */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA 0x1000&t;&t;&t;&t;/* attach addr a multiple of this */
DECL|macro|SHMSEG
mdefine_line|#define SHMSEG SHMMNI&t;&t;&t;&t;/* max shared segs per process */
macro_line|#ifdef __KERNEL__
multiline_comment|/* shm_mode upper byte flags */
DECL|macro|SHM_DEST
mdefine_line|#define&t;SHM_DEST&t;01000&t;/* segment will be destroyed on last detach */
DECL|macro|SHM_LOCKED
mdefine_line|#define SHM_LOCKED      02000   /* segment will not be swapped */
multiline_comment|/* ipcs ctl commands */
DECL|macro|SHM_STAT
mdefine_line|#define SHM_STAT &t;13
DECL|macro|SHM_INFO
mdefine_line|#define SHM_INFO &t;14
DECL|struct|shm_info
r_struct
id|shm_info
(brace
DECL|member|used_ids
r_int
id|used_ids
suffix:semicolon
DECL|member|shm_tot
id|ulong
id|shm_tot
suffix:semicolon
multiline_comment|/* total allocated shm */
DECL|member|shm_rss
id|ulong
id|shm_rss
suffix:semicolon
multiline_comment|/* total resident shm */
DECL|member|shm_swp
id|ulong
id|shm_swp
suffix:semicolon
multiline_comment|/* total swapped shm */
DECL|member|swap_attempts
id|ulong
id|swap_attempts
suffix:semicolon
DECL|member|swap_successes
id|ulong
id|swap_successes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SHM_H_ */
eof
