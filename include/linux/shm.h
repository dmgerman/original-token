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
id|shm_desc
op_star
id|attaches
suffix:semicolon
multiline_comment|/* descriptors for attaches */
)brace
suffix:semicolon
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
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX 0x400000&t; /* &lt;= 4M */          /* max shared seg size (bytes) */
DECL|macro|SHMMIN
mdefine_line|#define SHMMIN 1&t; /* really PAGE_SIZE */  /* min shared seg size (bytes)*/
DECL|macro|SHMMNI
mdefine_line|#define SHMMNI 128       /* &lt;= 4096 */        /* max num of segs system wide */
DECL|macro|SHMALL
mdefine_line|#define SHMALL 0x10000 /* &lt;= SHMMAX*SHMMNI/PAGE_SIZE */  /* max shm system wide (pages) */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA 0x1000    /* = PAGE_SIZE */   /*  attach addr multiple */
DECL|macro|SHMSEG
mdefine_line|#define SHMSEG SHMMNI    /* &lt;= SHMMNI */    /* max shared segs per process */
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
multiline_comment|/*&n; * Per process internal structure for managing segments.&n; * A shmat will add to and shmdt will remove from the list.&n; */
DECL|struct|shm_desc
r_struct
id|shm_desc
(brace
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
multiline_comment|/* attacher */
DECL|member|shm_sgn
r_int
r_int
id|shm_sgn
suffix:semicolon
multiline_comment|/* signature for this attach */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* virt addr of attach, multiple of SHMLBA */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* multiple of SHMLBA */
DECL|member|task_next
r_struct
id|shm_desc
op_star
id|task_next
suffix:semicolon
multiline_comment|/* next attach for task */
DECL|member|seg_next
r_struct
id|shm_desc
op_star
id|seg_next
suffix:semicolon
multiline_comment|/* next attach for segment */
)brace
suffix:semicolon
multiline_comment|/* not present page table entry format bit 0 is 0, high byte defined in mm.h */
DECL|macro|SHM_IDX_SHIFT
mdefine_line|#define SHM_IDX_SHIFT 20
DECL|macro|SHM_IDX_MASK
mdefine_line|#define SHM_IDX_MASK  0x3FF
DECL|macro|SHM_ID_SHIFT
mdefine_line|#define SHM_ID_SHIFT  8
DECL|macro|SHM_ID_MASK
mdefine_line|#define SHM_ID_MASK   0xFFF
DECL|macro|SHM_READ_ONLY
mdefine_line|#define SHM_READ_ONLY 0x80000000
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SHM_H_ */
eof
